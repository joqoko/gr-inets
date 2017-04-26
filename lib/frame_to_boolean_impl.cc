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
#include "frame_to_boolean_impl.h"

namespace gr {
  namespace inets {

    frame_to_boolean::sptr
    frame_to_boolean::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new frame_to_boolean_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    frame_to_boolean_impl::frame_to_boolean_impl(int develop_mode, int block_id)
      : gr::block("frame_to_boolean",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_to_boolean id: " << _block_id << " is activated." << std::endl;
      message_port_register_out(pmt::mp("boolean_out"));
      message_port_register_in(pmt::mp("true_in"));
      set_msg_handler(
        pmt::mp("true_in"),
        boost::bind(&frame_to_boolean_impl::set_true, this, _1)
      );
      message_port_register_in(pmt::mp("false_in"));
      set_msg_handler(
        pmt::mp("false_in"),
        boost::bind(&frame_to_boolean_impl::set_false, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_to_boolean_impl::~frame_to_boolean_impl()
    {
    }

    void
    frame_to_boolean_impl::set_true(pmt::pmt_t true_in)
    {
      message_port_pub(pmt::mp("boolean_out"), pmt::PMT_T);
    }

    void
    frame_to_boolean_impl::set_false(pmt::pmt_t false_in)
    {
      message_port_pub(pmt::mp("boolean_out"), pmt::PMT_F);
    }

  } /* namespace inets */
} /* namespace gr */

