/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "IFS_impl.h"

namespace gr {
  namespace inets {

    IFS::sptr
    IFS::make(int develop_mode, int block_id, int SIFS, int slot_time, int interval_type, int customized_IFS, int AIFS_ac, float cs_threshold, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new IFS_impl(develop_mode, block_id, SIFS, slot_time, interval_type, customized_IFS, AIFS_ac, cs_threshold, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    IFS_impl::IFS_impl(int develop_mode, int block_id, int SIFS, int slot_time, int interval_type, int customized_IFS, int AIFS_ac, float cs_threshold, int system_time_granularity_us)
      : gr::block("IFS",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _slot_time(slot_time),
        _SIFS(SIFS),
        _interval_type(interval_type),
        _customized_IFS(customized_IFS),
        _AIFS_ac(AIFS_ac),
	_cs_threshold(cs_threshold),
        _system_time_granularity_us(system_time_granularity_us),
	_IFS_duration(0),
	_in_cca(false)
    {
      if(_develop_mode)
        std::cout << "develop_mode of IFS ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_in")); 
      set_msg_handler(pmt::mp("frame_in"), boost::bind(&IFS_impl::start_IFS, this, _1));
      message_port_register_out(pmt::mp("frame_info_pass_out"));
      message_port_register_out(pmt::mp("frame_info_fail_out"));
    }

    /*
     * Our virtual destructor.
     */
    IFS_impl::~IFS_impl()
    {
    }

    void 
    IFS_impl::start_IFS(pmt::pmt_t frame_in)
    {
      if(pmt::is_dict(frame_in))
      {
        if(_develop_mode == 1)
        {
          if(_interval_type == 1)
            std::cout << "++++ SIFS ID: " << _block_id <<  " ++++" << std::endl;
          else if(_interval_type == 2)
            std::cout << "++++ PIFS ID: " << _block_id <<  " ++++" << std::endl;
          else if(_interval_type == 3)
            std::cout << "++++ DIFS ID: " << _block_id <<  " ++++" << std::endl;
          else if(_interval_type == 4)
            std::cout << "++++ AIFS ID: " << _block_id <<  " ++++" << std::endl;
          else if(_interval_type == 5)
            std::cout << "++++ RIFS ID: " << _block_id <<  " ++++" << std::endl;
          else if(_interval_type == 6)
            std::cout << "++++ EIFS ID: " << _block_id <<  " ++++" << std::endl;
          else
            std::cout << "++++ Customized IFS ID: " << _block_id <<  " ++++" << std::endl;
        }
        /*
         * aSIFSTime = aRxRFDelay + aRxPLCPDelay + aMACProcessingDelay + aRxTxTurnaroundTime
         * aSlotTime = aCCATime + aRxTxTurnaroundTime + aAirPropagationTime + aMACProcessingDelay
      */
        // SIFS
        if(_interval_type == 1)
          _IFS_duration = _SIFS;
        // PIFS
        else if(_interval_type == 2)
          _IFS_duration = _SIFS + _slot_time; 
        // DIFS
        else if(_interval_type == 3)
          _IFS_duration = _SIFS + 2 * _slot_time; 
        // AIFS
        else if(_interval_type == 4)
          _IFS_duration = _SIFS;
        // RIFS
        else if(_interval_type == 5)
          _IFS_duration = _SIFS;
        // EIFS
        else if(_interval_type == 6)
          _IFS_duration = _SIFS;
        // Customized IFS
        else
          _IFS_duration = _customized_IFS;
        if(_develop_mode == 2)
        {
          struct timeval t; 
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
          std::cout << "* IFS ID: " << _block_id << " starts a IFS at time " << current_time << " s" << std::endl;
        }
	_frame_info = frame_in;
        boost::thread thrd(&IFS_impl::countdown_sensing, this);       
      }
      else if(pmt::is_real(frame_in))
      {
        double power = pmt::to_double(frame_in);
        _in_cca = (_cs_threshold > power);
        if(_develop_mode == 1 && _in_cca)
        {
          struct timeval t;
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
          std::cout << "in carrier sensing, average rx power is: " << power << ", received at " << current_time << " s" << std::endl;
        }
      }
    }

    void 
    IFS_impl::countdown_sensing()
    {
      _in_cca = true;
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      while((current_time < start_time + _IFS_duration / 1000) && _in_cca)
      {
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us)); 
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
      }
      if(_in_cca)
      {
        if(_develop_mode == 1)
          std::cout << "Carrier sensing passed. " << std::endl;
        message_port_pub(pmt::mp("frame_info_pass_out"), _frame_info);
      }
      else
      {
        if(_develop_mode == 1)
          std::cout << "Carrier sensing failed. " << std::endl;
        message_port_pub(pmt::mp("frame_info_fail_out"), _frame_info);
      }
      _in_cca = false;
      int cs_time = current_time - start_time;
      if(_develop_mode == 1)
        std::cout << "Carrier sensing time is: " << cs_time << " s" << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

