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
#include "message_strobe_filter_impl.h"

namespace gr {
  namespace inets {

    message_strobe_filter::sptr
    message_strobe_filter::make()
    {
      return gnuradio::get_initial_sptr
        (new message_strobe_filter_impl());
    }

    /*
     * The private constructor
     */
    message_strobe_filter_impl::message_strobe_filter_impl()
      : gr::block("message_strobe_filter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _started(false)
    {
      message_port_register_in(pmt::mp("message_strobe_in"));
      set_msg_handler(pmt::mp("message_strobe_in"), boost::bind(&message_strobe_filter_impl::filtering, this, _1 ));
      message_port_register_out(pmt::mp("trigger_out"));
    }

    /*
     * Our virtual destructor.
     */
    message_strobe_filter_impl::~message_strobe_filter_impl()
    {
    }

    void
    message_strobe_filter_impl::filtering(pmt::pmt_t msg)
    {
      if(!_started)
      {
        _started = true;
        message_port_pub(pmt::mp("trigger_out"), msg);
      }
    }

  } /* namespace inets */
} /* namespace gr */

