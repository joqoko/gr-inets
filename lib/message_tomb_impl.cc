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
#include "message_tomb_impl.h"

namespace gr {
  namespace inets {

    message_tomb::sptr
    message_tomb::make()
    {
      return gnuradio::get_initial_sptr
        (new message_tomb_impl());
    }

    /*
     * The private constructor
     */
    message_tomb_impl::message_tomb_impl()
      : gr::block("message_tomb",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
      message_port_register_in(pmt::mp("message_in"));
      set_msg_handler(pmt::mp("message_in"), boost::bind(&message_tomb_impl::kill_message, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    message_tomb_impl::~message_tomb_impl()
    {
    }
  
    void message_tomb_impl::kill_message(pmt::pmt_t msg) 
    {
      
    }

  } /* namespace inets */
} /* namespace gr */

