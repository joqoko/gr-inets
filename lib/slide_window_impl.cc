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
#include "slide_window_impl.h"

namespace gr {
  namespace inets {

    slide_window::sptr
    slide_window::make(int develop_mode, int block_id, int window_size, int protocol, double bps, int interframe_interval_us, int frame_index_length)
    {
      return gnuradio::get_initial_sptr
        (new slide_window_impl(develop_mode, block_id, window_size, protocol, bps, interframe_interval_us, frame_index_length));
    }

    /*
     * The private constructor
     */
    slide_window_impl::slide_window_impl(int develop_mode, int block_id, int window_size, int protocol, double bps, int interframe_interval_us, int frame_index_length)
      : gr::block("slide_window",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _window_size(window_size),
        _protocol(protocol),
        _bps(bps),
        _txed_index(0),
        _frame_index_length(frame_index_length),
        _interframe_interval_us(interframe_interval_us)
    {
      if(_develop_mode)
        std::cout << "develop_mode of slide_window id: " << _block_id << " is activated." << std::endl;
      _max_index = 1 << (8 * _frame_index_length);
      std::cout << "_max_index is: " << _max_index << std::endl;
      message_port_register_in(pmt::mp("frame_info_in")); 
      set_msg_handler(pmt::mp("frame_info_in"), boost::bind(&slide_window_impl::frame_in, this, _1));
      message_port_register_in(pmt::mp("ack_info_in")); 
      set_msg_handler(pmt::mp("ack_info_in"), boost::bind(&slide_window_impl::ack_in, this, _1));
      message_port_register_out(pmt::mp("reload_request"));
      message_port_register_out(pmt::mp("frame_info_out"));
    }

    /*
     * Our virtual destructor.
     */
    slide_window_impl::~slide_window_impl()
    {
    }

    void
    slide_window_impl::frame_in(pmt::pmt_t frame_in)
    {
      if(_develop_mode)
        std::cout << "++++++++++++ slide_window ID: " << _block_id << " fill the window ++++++++++" << std::endl;
      if(_window.size() < _window_size)
      {
        _window.push(frame_in);
        if(_develop_mode)
          print_window(_window);
        if(_develop_mode == 2)
        {
          struct timeval t; 
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
          std::cout << "window ID: " << _block_id << " gets a frame at time " << current_time << " s" << std::endl;
        }
        if(_window.size() < _window_size)
        {
          message_port_pub(pmt::mp("reload_request"), frame_in);
        }
        else
        {
          // std::cout << "what is the _txed_index: " << _txed_index << std::endl;
          transmit_window(_window, _txed_index);
        //  std::cout << "what is the _txed_index after: " << _txed_index << std::endl;
        }
      }
      else
      {
        pmt::pmt_t not_found;
	int input_index = pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("frame_index"), not_found));
        std::cout << "the extra frame index is: " << input_index << std::endl;
        // if the whole logic is correct, the else case will never happen.
        print_window(_window);
        std::cout << "Input frames are more than the window size." << std::endl;
      }
    }

    void
    slide_window_impl::ack_in(pmt::pmt_t ack_in)
    {
      if(_develop_mode)
        std::cout << "++++++++++++ slide_window ID: " << _block_id << " get an ack ++++++++++" << std::endl;
      
      if(pmt::is_dict(ack_in))
      {
        std::cout << "ack 1" << std::endl;
        pmt::pmt_t not_found;
        int frame_type = pmt::to_long(pmt::dict_ref(ack_in, pmt::string_to_symbol("frame_type"), not_found));
        int ack_dest = pmt::to_long(pmt::dict_ref(ack_in, pmt::string_to_symbol("destination_address"), not_found));
        int ack_src = pmt::to_long(pmt::dict_ref(ack_in, pmt::string_to_symbol("source_address"), not_found));
        int ack_index = pmt::to_long(pmt::dict_ref(ack_in, pmt::string_to_symbol("frame_index"), not_found));

        std::cout << "ack 2 and window size is: " << _window.size() << std::endl;
        print_window(_window);
        int wait_index = pmt::to_long(pmt::dict_ref(_window.front(), pmt::string_to_symbol("frame_index"), not_found));
        std::cout << "ack 3" << std::endl;
        if(_develop_mode)
          std::cout << "acked_index is: " << ack_index << " and wait_index is: " << wait_index << " and the frame_type is: " << frame_type << std::endl;
        if(frame_type == 2)
        {
          if((ack_index >= wait_index) || ((ack_index >= (wait_index - _max_index)) && (ack_index < (wait_index - _window_size))))
          {
            for(int i = 0; i < ack_index - wait_index + 1; i++)
            {
              _window.pop();
            }
            message_port_pub(pmt::mp("reload_request"), ack_in);
            if(_develop_mode)
            {
              std::cout << "frame with index: " << ack_index << " is removed from the window because it is correctly acked. " << std::endl;
              print_window(_window);
            }
          } 
          else
          {
            if(_develop_mode)
            {
              std::cout << "ack_index is: " << ack_index << " and wait_index is: " << wait_index << std::endl;
              std::cout << "retransmit the whole window due to lost frames." << std::endl;
            }
            transmit_window(_window, _txed_index);
          }
        }
        else if(frame_type == pmt::to_long(pmt::dict_ref(_window.front(), pmt::string_to_symbol("frame_type"), not_found)))
        {
          if(_develop_mode)
          {
            std::cout << "retransmit the whole window because the timeout timer expired." << std::endl;
          }
          _txed_index = wait_index - 1;
          transmit_window(_window, _txed_index);
        }
        else
        {
          std::cout << "slide_window: please only connect correct type of frame to the ack_frame_in port" << std::endl;
        }
      }
      
    }
    
    void
    slide_window_impl::print_window(std::queue<pmt::pmt_t> window)
    {
      pmt::pmt_t not_found;
      if(_develop_mode)
        std::cout << "current window: [";
      int real_win_size = window.size();
      for(int i = 0; i < real_win_size; i++)
      {
        std::cout << " " << pmt::to_long(pmt::dict_ref(window.front(), pmt::string_to_symbol("frame_index"), not_found)) << " ";
        window.pop();
      }
      std::cout << "]" << std::endl;
    }

    void
    slide_window_impl::transmit_window(std::queue<pmt::pmt_t> window, int txed_index)
    {
      pmt::pmt_t not_found;
      int real_win_size = window.size();
      for(int i = 0; i < real_win_size; i++)
      {
        int index = pmt::to_long(pmt::dict_ref(window.front(), pmt::string_to_symbol("frame_index"), not_found));
        // std::cout << "index is: " << index << " and txed_index is: " << txed_index << std::endl;
        if(((index > txed_index) && index <= (txed_index + _window_size)) || (((index - _max_index) > txed_index) && ((index - _max_index) <= (txed_index + _window_size)) && (index < txed_index)))
        {
          // std::cout  << " i is : " << i << ", current check index is: " << index << " and the last acked index is: " << txed_index << std::endl;
          if(_develop_mode)
          {
            switch(i)
            {
              case 0 : std::cout << "the 1st frame in window is transmitted" << std::endl;break;
              case 1 : std::cout << "the 2nd frame in window is transmitted" << std::endl;break;
              default : std::cout << "the " << i + 1 << "th frame in window is transmitted" << std::endl;
            }
          }
          double t_frame_us = pmt::u8vector_elements(pmt::cdr(pmt::dict_ref(window.front(), pmt::string_to_symbol("frame_pmt"), not_found))).size() / _bps * 1000000;
          if(i > 0)
            boost::this_thread::sleep(boost::posix_time::microseconds(t_frame_us + _interframe_interval_us));
          message_port_pub(pmt::mp("frame_info_out"), window.front());
        }
        _txed_index = pmt::to_long(pmt::dict_ref(window.front(), pmt::string_to_symbol("frame_index"), not_found));
        window.pop();
      }
    }

  } /* namespace inets */
} /* namespace gr */

