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
#include "tx_buffer_impl.h"
#include <gnuradio/msg_queue.h>
#include <queue>

namespace gr {
  namespace inets {

    tx_buffer::sptr
    tx_buffer::make(std::vector<int> develop_mode_list, int max_buffer_size, int policy)
    {
      return gnuradio::get_initial_sptr
        (new tx_buffer_impl(develop_mode_list, max_buffer_size, policy));
    }

    /*
     * The private constructor
     */
    tx_buffer_impl::tx_buffer_impl(std::vector<int> develop_mode_list, int max_buffer_size, int policy)
      : gr::block("tx_buffer",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _max_buffer_size(max_buffer_size),
        _policy(policy),
        _develop_mode_list(develop_mode_list),
        _my_develop_mode(6)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of tx_buffer is activated." << std::endl;
      message_port_register_in(pmt::mp("payload_in"));
      message_port_register_in(pmt::mp("spark_in"));
      message_port_register_out(pmt::mp("payload_out"));
      set_msg_handler(pmt::mp("payload_in"), boost::bind(&tx_buffer_impl::enqueue, this, _1 ));
      set_msg_handler(pmt::mp("spark_in"), boost::bind(&tx_buffer_impl::dequeue, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    tx_buffer_impl::~tx_buffer_impl()
    {
    }

    int tx_buffer_impl::enqueue(pmt::pmt_t payload)
    {
      if(_develop_mode)
      {
        std::cout << "++++++++++++++   tx_buffer  ++++++++++++++++" << std::endl;
      }
      if(_tx_buff.size() < _max_buffer_size)
      {
        _tx_buff.push(payload);
        if(_develop_mode)
          std::cout << "After enqueue, there are " << _tx_buff.size() << " payloads in the tx buffer." << std::endl;
      }
      else
      {
        if(_develop_mode)
          std::cout << "Tx buffer is full, current payload is discarded." << std::endl;
      }
      return 1;
    }

    int tx_buffer_impl::dequeue(pmt::pmt_t spark)
    {
      // std::cout << "received a message" << std::endl;
      if(pmt::is_bool(spark))
      {
        // std::cout << "received a pmt bool" << std::endl;
        if(pmt::to_bool(spark))
        {
          // this function is fired
          if(_tx_buff.size() > 0)
          {
            if(_develop_mode)
              std::cout << "Before dequeue, there are " << _tx_buff.size() << " payloads in the tx buffer." << std::endl;
            message_port_pub(pmt::mp("payload_out"), _tx_buff.front());
            _tx_buff.pop();
            if(_develop_mode)
               std::cout << "After dequeue, there are " << _tx_buff.size() << " payloads in the tx buffer." << std::endl;
          }
        }
      }
      else
      {
        // not a boolean pmt, most likely an import error
        if(_develop_mode)
          std::cout << "not a spark signal" << std::endl;
      }
      return 0;
    }

  } /* namespace inets */
} /* namespace gr */
