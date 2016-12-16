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
    timeout_cpp::make(int develop_mode, int block_id, float timeout_duration_ms, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new timeout_cpp_impl(develop_mode, block_id, timeout_duration_ms, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    timeout_cpp_impl::timeout_cpp_impl(int develop_mode, int block_id, float timeout_duration_ms, int system_time_granularity_us)
      : gr::block("timeout_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _timeout_duration_ms(float(timeout_duration_ms)),
        _in_timeout(false),
        _system_time_granularity_us(system_time_granularity_us)
    {
      if(_develop_mode == 1)
        std::cout << "develop_mode of timeout_cpp ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("data_frame_info_in"));
      message_port_register_in(pmt::mp("ack_frame_info_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
      set_msg_handler(
        pmt::mp("data_frame_info_in"),
        boost::bind(&timeout_cpp_impl::start_timeout, this, _1)
      );
      set_msg_handler(
        pmt::mp("ack_frame_info_in"),
        boost::bind(&timeout_cpp_impl::kill_timeout, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    timeout_cpp_impl::~timeout_cpp_impl()
    {
    }

    void timeout_cpp_impl::kill_timeout(pmt::pmt_t ack_frame_info) 
    {
      if(_develop_mode == 1)
      {
        std::cout << "++++++++++++  timeout_cpp ID: " << _block_id << "  +++++++++++++" << std::endl;
      }
      if(_develop_mode == 2)
      {
        struct timeval t; 
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        std::cout << "* timeout ID: " << _block_id << " start killing the timer at time " << current_time << " s" << std::endl;
      }
      if(pmt::is_dict(ack_frame_info))
      {
        pmt::pmt_t not_found;
        // ack frame info
        int frame_type = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("frame_type"), not_found));
        int ack_dest = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("destination_address"), not_found));
        int ack_src = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("source_address"), not_found));
        int ack_index = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("frame_index"), not_found));
        // waiting frame info
        int wait_dest = pmt::to_long(pmt::dict_ref(_waiting_frame_info, pmt::string_to_symbol("destination_address"), not_found));
        int wait_src = pmt::to_long(pmt::dict_ref(_waiting_frame_info, pmt::string_to_symbol("source_address"), not_found));
        int wait_index = pmt::to_long(pmt::dict_ref(_waiting_frame_info, pmt::string_to_symbol("frame_index"), not_found));
        if(_in_timeout)
        {
          if((frame_type == 2) && (ack_dest == wait_src) && (ack_src == wait_dest) && (ack_index == wait_index))
          { 
            _in_timeout = false;
            message_port_pub(pmt::mp("frame_info_out"), ack_frame_info);
            if(_develop_mode == 1)
              std::cout << "timeout is terminated by correctly received ack frame." << std::endl;
          }
          else if(frame_type != 2)
            if(_develop_mode == 1)
              std::cout << "Not an ack_frame_info dict." << std::endl;
          else if((ack_dest != wait_src) && (ack_src != wait_dest))
            if(_develop_mode == 1)
              std::cout << "address not correct." << std::endl;
          else
            if(_develop_mode == 1)
              std::cout << "expecting the ack of the " << wait_index << "th frame but received the ack of the " << ack_index << "th frame." << std::endl;
        }
        else
          std::cout << "Receive a pmt dict out of timeout interval." << std::endl;
      }
      else
        std::cout << "ack_frame_info: wrong data type. please check your connection." << std::endl;
    }

    void timeout_cpp_impl::start_timeout(pmt::pmt_t data_frame_info) 
    {
    
      if(_develop_mode == 2)
      {
        struct timeval t; 
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        std::cout << "* timeout ID: " << _block_id << " timeout timer is triggered at time " << current_time << " s" << std::endl;
      }
      if(_develop_mode == 1)
      {
        std::cout << "+++++++++++++   timeout_cpp   ++++++++++++++" << std::endl;
      }
      if(pmt::is_dict(data_frame_info))
      {
        if(!_in_timeout)
        {
          pmt::pmt_t not_found;
          int data_type = pmt::to_long(pmt::dict_ref(data_frame_info, pmt::string_to_symbol("frame_type"), not_found));
          if(data_type == 1)
          {
            _in_timeout = true;
            if(_develop_mode == 1)
              std::cout << "timeout timer is triggered." << std::endl;
            _waiting_frame_info = data_frame_info;
            boost::thread thrd(&timeout_cpp_impl::countdown_timeout, this);       
          }
          else
            std::cout << "Not a data_frame_info dict." << std::endl;
        }
        else
          std::cout << "Cannot trigger the timeout timer before finishing the last one." << std::endl;
      }
      else
        std::cout << "data_frame_info: wrong data type. please check your connection." << std::endl;
    }

    void timeout_cpp_impl::countdown_timeout()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      if(_develop_mode == 1)
      {
        std::cout << "timeout timer start time: " << start_time << std::endl;
        std::cout << "timeout wait time: " << _timeout_duration_ms/1000 << std::endl;
        std::cout << "_in_timeout: " << _in_timeout << std::endl;
      }
      while((current_time < start_time + _timeout_duration_ms / 1000) && _in_timeout)
      {
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        if(_develop_mode == 1)
        {
          //std::cout << "Remaining time: " << _timeout_duration_ms / 1000 - (current_time - start_time) << ". And the in_timeout state is: " << _in_timeout << std::endl;
        }
      }
      if(_develop_mode == 2)
      {
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        if(_in_timeout)
        std::cout << "* timeout ID: " << _block_id << " timeout timer is expired at time " << current_time << " s" << std::endl;
        else
        std::cout << "* timeout ID: " << _block_id << " timeout timer is killed  at time " << current_time << " s" << std::endl;
      }
      if(_in_timeout)
        message_port_pub(pmt::mp("frame_info_out"), _waiting_frame_info);
      _in_timeout = false;
    }
  } /* namespace inets */
} /* namespace gr */

