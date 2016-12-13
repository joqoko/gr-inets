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
#include "idle_impl.h"
#include <queue>

namespace gr {
  namespace inets {

    idle::sptr
    idle::make(std::vector<int> develop_mode_list, float experiment_duration_s, int max_num_retransmission, int max_buffer_size, int my_address)
    {
      return gnuradio::get_initial_sptr
        (new idle_impl(develop_mode_list, experiment_duration_s, max_num_retransmission, max_buffer_size, my_address));
    }

    /*
     * The private constructor
     */
    idle_impl::idle_impl(std::vector<int> develop_mode_list, float experiment_duration_s, int max_num_retransmission, int max_buffer_size, int my_address)
      : gr::block("idle",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode_list(develop_mode_list),
        _my_develop_mode(1),
        _experiment_duration_s(experiment_duration_s),
        _max_buffer_size(max_buffer_size),
        _my_address(my_address),
        _experiment_running(true),
        _in_idle(true),
        _max_num_retransmission(max_num_retransmission)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of idle is activated." << std::endl;
      message_port_register_in(pmt::mp("data_in"));
      message_port_register_in(pmt::mp("reset_idle"));
      message_port_register_out(pmt::mp("data_out"));
      message_port_register_out(pmt::mp("successful_transmission"));
      set_msg_handler(pmt::mp("data_in"), boost::bind(&idle_impl::state_transition, this, _1 ));
      set_msg_handler(pmt::mp("reset_idle"), boost::bind(&idle_impl::reset_idle, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    idle_impl::~idle_impl()
    {
    }

    void
    idle_impl::reset_idle(pmt::pmt_t data)
    {
      _in_idle = true;
      if(_tx_buff.size())
      {
        message_port_pub(pmt::mp("data_out"), _tx_buff.front());
        _tx_buff.pop();
        _in_idle = false;
      }
    }

    void
    idle_impl::state_transition(pmt::pmt_t data)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++++++   idle   +++++++++++++++++" << std::endl;
      }
      /*
       * get a payload 
       */
      if(pmt::is_pair(data)) 
      {
        // we first check whether the queue is full. if we enqueue the data frame, we need to check the _in_idle state. If true, then we send the frame and set _in_idle to false.
        if(_tx_buff.size() < _max_buffer_size)
        {
          _tx_buff.push(data);
          if(_in_idle)
          {
            message_port_pub(pmt::mp("data_out"), _tx_buff.front());
            _tx_buff.pop();
            _in_idle = false;
          }
          if(_develop_mode)
            std::cout << "After enqueue, there are " << _tx_buff.size() << " payloads in the tx buffer." << std::endl;
        }
        else
        {
          if(_develop_mode)
            std::cout << "Tx buffer is full, current payload is discarded." << std::endl;
        }
      }
      /*
       * get a frame info 
       */
      else if(pmt::is_dict(data))
      {
        pmt::pmt_t not_found;
        int frame_type = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("frame_type"), not_found));
        int destination_address = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("destination_address"), not_found));
        int src_address = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("source_address"), not_found));
        int num_resend = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("num_resend"), not_found));
        // if the frame is sent by me
        if(src_address == _my_address)
        {
          // if I sent an ACK frame
          if(frame_type == 2) 
          {
            // activate _in_idle state
            if(_develop_mode)
              std::cout << "After sending an ACK frame, state to idle." << std::endl;
            _in_idle = true;
            if(_tx_buff.size())
            {
              message_port_pub(pmt::mp("data_out"), _tx_buff.front());
              _tx_buff.pop();
              _in_idle = false;
              if(_develop_mode)
                std::cout << "start sending a payload to send_frame." << std::endl;
            }
          }
          // if the data frame is sent by me
          else if(frame_type == 1)
          {
            // check the number of resend. If maximum retransmission reached, then reset idle and check the buffer. Otherwise simply forward the frame info to send frame and there the resend will be add one.
            if(num_resend >= _max_num_retransmission)
            {
              if(_develop_mode)
                std::cout << "Maximum retransmission reached. Reset _in_idle." << std::endl;
              _in_idle = true;
              if(_tx_buff.size())
              {
                message_port_pub(pmt::mp("data_out"), _tx_buff.front());
                _tx_buff.pop();
                _in_idle = false;
                if(_develop_mode)
                  std::cout << "start sending a payload to send_frame." << std::endl;
              }
            }
            // 
            else
            {
              message_port_pub(pmt::mp("data_out"), data);
            }
          }     
          else
            std::cout << "Warning: unknown frame_type. Please check your connections." << std::endl;
        }    
        // if the frame is not sent by me
        else
        {
          // if I am the destined node
          if(destination_address == _my_address)
          {
            // if it is an ACK frame. Note that we get this ACK frame because timeout give it to us. We can count one successful transmission, set _in_idle state to true and dequeue the first element in the buffer.
            if(frame_type == 2)
            {
              _in_idle = true;
              message_port_pub(pmt::mp("successful_transmission"), pmt::from_bool(true));
              if(_tx_buff.size())
              {
                message_port_pub(pmt::mp("data_out"), _tx_buff.front());
                _tx_buff.pop();
                _in_idle = false;
                if(_develop_mode)
                  std::cout << "start sending a payload to send_frame." << std::endl;
              }
            }
            // if it is a data frame, we need to set idle state to false and send ack back.
            else if(frame_type == 1)
            {
              _in_idle = false;
              message_port_pub(pmt::mp("data_out"), data);
            }
            else
              std::cout << "Warning: unknown frame_type. Please check your connections." << std::endl;
          }
          else
            std::cout << "Both source and destination address is not me. whos frame?" << std::endl;
        }
      }
      else 
        std::cout << "Warning: unknown message type. Please check your connection." << std::endl;
    }
  } /* namespace inets */
} /* namespace gr */

