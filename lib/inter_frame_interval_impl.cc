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
#include "inter_frame_interval_impl.h"

namespace gr {
  namespace inets {

    inter_frame_interval::sptr
    inter_frame_interval::make(int develop_mode, int block_id, int SIFS, int slot_time, int interval_type, int customized_IFS, int AIFS_ac, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new inter_frame_interval_impl(develop_mode, block_id, SIFS, slot_time, interval_type, customized_IFS, AIFS_ac, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    inter_frame_interval_impl::inter_frame_interval_impl(int develop_mode, int block_id, int SIFS, int slot_time, int interval_type, int customized_IFS, int AIFS_ac, int system_time_granularity_us)
      : gr::block("inter_frame_interval",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _slot_time(slot_time),
        _SIFS(SIFS),
        _interval_type(interval_type),
        _customized_IFS(customized_IFS),
        _AIFS_ac(AIFS_ac),
        _system_time_granularity_us(system_time_granularity_us)
    {
      if(_develop_mode)
        std::cout << "develop_mode of IFS ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_in")); 
      set_msg_handler(pmt::mp("frame_in"), boost::bind(&inter_frame_interval_impl::wait_for, this, _1));
      message_port_register_out(pmt::mp("frame_out"));
    }

    /*
     * Our virtual destructor.
     */
    inter_frame_interval_impl::~inter_frame_interval_impl()
    {
    }

    void 
    inter_frame_interval_impl::wait_for(pmt::pmt_t frame_in)
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
      if(pmt::is_pair(frame_in))
      {
      /*
       * aSIFSTime = aRxRFDelay + aRxPLCPDelay + aMACProcessingDelay + aRxTxTurnaroundTime
       * aSlotTime = aCCATime + aRxTxTurnaroundTime + aAirPropagationTime + aMACProcessingDelay
      */
        // SIFS
        if(_interval_type == 1)
          _wait_time = _SIFS;
        // PIFS
        else if(_interval_type == 2)
          _wait_time = _SIFS + _slot_time; 
        // DIFS
        else if(_interval_type == 3)
          _wait_time = _SIFS + 2 * _slot_time; 
        // AIFS
        else if(_interval_type == 4)
          _wait_time = _SIFS;
        // RIFS
        else if(_interval_type == 5)
          _wait_time = _SIFS;
        // EIFS
        else if(_interval_type == 6)
          _wait_time = _SIFS;
        // Customized IFS
        else
          _wait_time = _customized_IFS;
        boost::thread thrd(&inter_frame_interval_impl::countdown_waiting, this);       
      }
    }

    void inter_frame_interval_impl::countdown_waiting()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      if(_develop_mode == 2)
      {
        std::cout << "Start time: " << start_time << std::endl;
        std::cout << "wait time: " << _wait_time/1000 << std::endl;
      }
      while(current_time < start_time + _wait_time / 1000)
      {
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        if(_develop_mode)
        {
          std::cout << "Remaining time: " << _wait_time/1000 - (current_time - start_time) << std::endl;
        }
      }
      message_port_pub(pmt::mp("spark_out"), pmt::from_bool(true));
    }

  } /* namespace inets */
} /* namespace gr */

