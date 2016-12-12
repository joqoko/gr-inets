/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
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
#include "timeout_cpp_impl.h"

namespace gr {
  namespace inets {

    timeout_cpp::sptr
    timeout_cpp::make(std::vector<int> develop_mode_list, int timeout_duration_ms, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new timeout_cpp_impl(develop_mode_list, timeout_duration_ms, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    timeout_cpp_impl::timeout_cpp_impl(std::vector<int> develop_mode_list, int timeout_duration_ms, int system_time_granularity_us)
      : gr::block("timeout_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode_list(develop_mode_list),
        _my_develop_mode(16),
        _timeout_duration_ms(float(timeout_duration_ms)),
        _in_timeout(false),
        _system_time_granularity_us(system_time_granularity_us)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of timeout_cpp is activated." << std::endl;
      message_port_register_in(pmt::mp("tx_frame_info_in"));
      message_port_register_in(pmt::mp("ack_info_in"));
      message_port_register_out(pmt::mp("spark_out"));
      set_msg_handler(
        pmt::mp("tx_frame_info_in"),
        boost::bind(&timeout_cpp_impl::start_timeout, this, _1)
      );
      set_msg_handler(
        pmt::mp("ack_info_in"),
        boost::bind(&timeout_cpp_impl::kill_timeout, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    timeout_cpp_impl::~timeout_cpp_impl()
    {
    }

    void timeout_cpp_impl::kill_timeout(pmt::pmt_t ack_info) 
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++   timeout_cpp   ++++++++++++++" << std::endl;
      }
      if(pmt::is_dict(ack_info))
      {
        if(_in_timeout)
        {
          pmt::pmt_t not_found;
          int data_type = pmt::to_long(pmt::dict_ref(ack_info, pmt::string_to_symbol("frame_type"), not_found));
          if(data_type == 2)
          { 
            _in_timeout = false;
            if(_develop_mode)
              std::cout << "timeout is terminated by correctly received ack frame." << std::endl;
          }
          else
            std::cout << "Not an ack_info dict." << std::endl;
        }
        else
          std::cout << "Receive a pmt dict out of timeout interval." << std::endl;
      }
      else
        std::cout << "ack_info: wrong data type. please check your connection." << std::endl;
    }

    void timeout_cpp_impl::start_timeout(pmt::pmt_t tx_frame_info) 
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++   timeout_cpp   ++++++++++++++" << std::endl;
      }
      if(pmt::is_dict(tx_frame_info))
      {
        if(!_in_timeout)
        {
          pmt::pmt_t not_found;
          int data_type = pmt::to_long(pmt::dict_ref(tx_frame_info, pmt::string_to_symbol("frame_type"), not_found));
          if(data_type == 1)
          {
            _in_timeout = true;
            if(_develop_mode)
              std::cout << "timeout timer is triggered." << std::endl;
            boost::thread thrd(&timeout_cpp_impl::countdown_timeout, this);       
          }
          else
            std::cout << "Not a tx_frame_info dict." << std::endl;
        }
        else
          std::cout << "Cannot trigger the timeout timer before finishing the last one." << std::endl;
      }
      else
        std::cout << "tx_frame_info: wrong data type. please check your connection." << std::endl;
    }

    void timeout_cpp_impl::countdown_timeout()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      if(_develop_mode)
      {
        std::cout << "timeout start time: " << start_time << std::endl;
        std::cout << "timeout wait time: " << _timeout_duration_ms/1000 << std::endl;
        std::cout << "_in_timeout: " << _in_timeout << std::endl;
      }
      while((current_time < start_time + _timeout_duration_ms / 1000) && _in_timeout)
      {
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        if(_develop_mode)
        {
          std::cout << "Remaining time: " << _timeout_duration_ms / 1000 - (current_time - start_time) << ". And the in_timeout state is: " << _in_timeout << std::endl;
        }
      }
      message_port_pub(pmt::mp("spark_out"), pmt::from_bool(_in_timeout));
      _in_timeout = false;
    }
  } /* namespace inets */
} /* namespace gr */

