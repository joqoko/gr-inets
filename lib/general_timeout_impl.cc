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
#include "general_timeout_impl.h"

namespace gr {
  namespace inets {

    general_timeout::sptr
    general_timeout::make(int develop_mode, int block_id, float timeout_duration_ms, int system_time_granularity_us, int timeout_mode, int output_former)
    {
      return gnuradio::get_initial_sptr
        (new general_timeout_impl(develop_mode, block_id, timeout_duration_ms, system_time_granularity_us, timeout_mode, output_former));
    }

    /*
     * The private constructor
     */
    general_timeout_impl::general_timeout_impl(int develop_mode, int block_id, float timeout_duration_ms, int system_time_granularity_us, int timeout_mode, int output_former)
      : gr::block("general_timeout",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _timeout_duration_ms(float(timeout_duration_ms)),
        _in_timeout(false),
        _system_time_granularity_us(system_time_granularity_us),
	_output_former(output_former),
        _timeout_mode(timeout_mode)
    {
      if(_develop_mode)
        std::cout << "develop_mode of general_timeout id: " << _block_id << " is activated." << std::endl;
      struct timeval t;
      gettimeofday(&t, NULL);
      _start_time = t.tv_sec + t.tv_usec / 1000000.0;
      message_port_register_out(pmt::mp("expired_frame_out"));
      message_port_register_out(pmt::mp("killed_frame_out"));
      message_port_register_in(pmt::mp("frame_in"));
      set_msg_handler(
        pmt::mp("frame_in"),
        boost::bind(&general_timeout_impl::start_timeout, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    general_timeout_impl::~general_timeout_impl()
    {
    }

    void
    general_timeout_impl::start_timeout(pmt::pmt_t frame_in)
    {
      if(!_in_timeout)
      {
        if(_develop_mode)
          std::cout << "+++  general_timeout ID: " << _block_id << " starts  +++";
        _waiting_frame_info = frame_in;
        _in_timeout = true;
        boost::thread thrd(&general_timeout_impl::countdown_timeout, this);       
      }
      else
      {
        if(_timeout_mode == 0)
        {
          _in_timeout = false;
          if(_output_former)
          {
            message_port_pub(pmt::mp("killed_frame_out"), _waiting_frame_info);
          }
          else
          {
            message_port_pub(pmt::mp("killed_frame_out"), frame_in);
          }
          if(_develop_mode)
          {
            std::cout << "general_timeout is killed";
            if(_develop_mode == 2)
            {
              struct timeval t; 
              gettimeofday(&t, NULL);
              double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
              std::cout << " at time " << current_time << " s" << std::endl;
            }
            else
              std::cout << " " << std::endl;
          }
        }
        else if(_timeout_mode == 1)
        {
	  reset_timeout();
          if(_output_former)
          {
            message_port_pub(pmt::mp("killed_frame_out"), _waiting_frame_info);
          }
          else
          {
            message_port_pub(pmt::mp("killed_frame_out"), frame_in);
          }
          if(_develop_mode)
          {
            std::cout << "general_timeout is prolonged";
            if(_develop_mode == 2)
            {
              struct timeval t; 
              gettimeofday(&t, NULL);
              double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
              std::cout << " at time " << current_time << " s" << std::endl;
            }
            else
              std::cout << " " << std::endl;
          }
        }
        _waiting_frame_info = frame_in;
      }
    }

    void general_timeout_impl::reset_timeout()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      _start_time = t.tv_sec + t.tv_usec / 1000000.0;
    }

    void general_timeout_impl::countdown_timeout()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
      _start_time = current_time;
      double current_time_show = start_time_show;
      if(_develop_mode)
        std::cout << "timeout timer start time: " << start_time_show << std::endl;
      while((current_time < _start_time + _timeout_duration_ms / 1000) && _in_timeout)
      {
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        current_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        // std::cout << "timeout is running at: " << current_time_show << std::endl;
      }
      if(_develop_mode)
      {
        gettimeofday(&t, NULL);
        double current_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        if(_in_timeout)
        std::cout << "* timeout ID: " << _block_id << " timeout timer is expired at time " << current_time_show << " s. " << " timeout duration is: " << _timeout_duration_ms << " [ms]" << std::endl;
        else
        std::cout << "* timeout ID: " << _block_id << " timeout timer is killed  at time " << current_time_show << " s. " << " actual timeout duration is: " << current_time_show - start_time_show << " s" << std::endl;
      }
      if(_in_timeout)
      {
        message_port_pub(pmt::mp("expired_frame_out"), _waiting_frame_info);
      }
      _in_timeout = false;
    }
  } /* namespace inets */
} /* namespace gr */

