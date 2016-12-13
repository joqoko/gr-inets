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
#include "frame_info_selector_impl.h"

namespace gr {
  namespace inets {

    frame_info_selector::sptr
    frame_info_selector::make()
    {
      return gnuradio::get_initial_sptr
        (new frame_info_selector_impl());
    }

    /*
     * The private constructor
     */
    frame_info_selector_impl::frame_info_selector_impl()
      : gr::block("frame_info_selector",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
      message_port_register_in(pmt::mp("frame_info_in"));
      message_port_register_out(pmt::mp("data_frame_info_out"));
      message_port_register_out(pmt::mp("ack_frame_info_out"));
      set_msg_handler(pmt::mp("frame_info_in"), boost::bind(&frame_info_selector_impl::selector, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    frame_info_selector_impl::~frame_info_selector_impl()
    {
    }

    void
    frame_info_selector_impl::selector(pmt::pmt_t info)
    { 
      pmt::pmt_t not_found;
      int frame_type = pmt::to_long(pmt::dict_ref(info, pmt::string_to_symbol("frame_type"), not_found));
      // data frame info
      if(frame_type == 1)
        message_port_pub(pmt::mp("data_frame_info_out"), info);
      else
        message_port_pub(pmt::mp("ack_frame_info_out"), info);
    }


  } /* namespace inets */
} /* namespace gr */

