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

namespace gr {
  namespace inets {

    tx_buffer::sptr
    tx_buffer::make(int buffer_size, int policy)
    {
      return gnuradio::get_initial_sptr
        (new tx_buffer_impl(buffer_size, policy));
    }

    /*
     * The private constructor
     */
    tx_buffer_impl::tx_buffer_impl(int max_buffer_size, int policy)
      : gr::block("tx_buffer",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _max_buffer_size(max_buffer_size),
        _policy(policy)
    {
      message_port_register_in(pmt::mp("payload_in"));
      set_msg_handler(pmt::mp("payload_in"), boost::bind(&tx_buffer_impl::enqueue, this, _1 ));
      message_port_register_in(pmt::mp("spark_in"));
      set_msg_handler(pmt::mp("spark_in"), boost::bind(&tx_buffer_impl::dequeue, this, _1 ));
      message_port_register_out(pmt::mp("payload_out"));
    }

    /*
     * Our virtual destructor.
     */
    tx_buffer_impl::~tx_buffer_impl()
    {
    }

    int tx_buffer_impl::enqueue(pmt::pmt_t msg)
    {
      if(_policy < 1)
      {
        if(_tx_buff.size() < _buffer_size)
        {
          _tx_buff.push(msg);
        }        
      }
      return _tx_buff.size();
    }

    int tx_buffer_impl::dequeue()
    {
      if(_tx_buff.size() > 0)
      {
        message_port_pub(pmt::mp("payload_out", _tx_buff.front()));
        _tx_buff.pop();
        return 1;
      }
      else
        return 0;
    }

  } /* namespace inets */
} /* namespace gr */

