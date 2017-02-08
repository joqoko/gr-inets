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
#include "dummy_source_impl.h"

namespace gr {
  namespace inets {

    dummy_source::sptr
    dummy_source::make(int develop_mode, int block_id, int payload_length, int source_type)
    {
      return gnuradio::get_initial_sptr
        (new dummy_source_impl(develop_mode, block_id, payload_length, source_type));
    }

    /*
     * The private constructor
     */
    dummy_source_impl::dummy_source_impl(int develop_mode, int block_id, int payload_length, int source_type)
      : gr::block("dummy_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _payload_length(payload_length),
        _source_type(source_type),
        _start(0)
    {
      if(_develop_mode)
        std::cout << "develop_mode of dummy source ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("trigger")); 
      set_msg_handler(pmt::mp("trigger"), boost::bind(&dummy_source_impl::trigger, this, _1));
      message_port_register_out(pmt::mp("output"));
    }

    /*
     * Our virtual destructor.
     */
    dummy_source_impl::~dummy_source_impl()
    {
    }

    void
    dummy_source_impl::trigger (pmt::pmt_t trig)
    {
      if(_start == 0)
        _start = 1;
      else
      {
        std::vector<unsigned char> payload(_payload_length);
        message_port_pub(pmt::mp("output"), pmt::cons(pmt::make_dict(), pmt::init_u8vector(payload.size(), payload)));
      }
    }

  } /* namespace inets */
} /* namespace gr */

