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
#include "frame_path_impl.h"

namespace gr {
  namespace inets {

    frame_path::sptr
    frame_path::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new frame_path_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    frame_path_impl::frame_path_impl(int develop_mode, int block_id)
      : gr::block("frame_path",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_path id: " << _block_id << " is activated." << std::endl;
      message_port_register_out(pmt::mp("frame_out"));
      message_port_register_in(pmt::mp("frame_in"));
      set_msg_handler(
        pmt::mp("frame_in"),
        boost::bind(&frame_path_impl::autobahn, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_path_impl::~frame_path_impl()
    {
    }

    void
    frame_path_impl::autobahn(pmt::pmt_t frame_in)
    {
      message_port_pub(pmt::mp("frame_out"), frame_in);
    }

  } /* namespace inets */
} /* namespace gr */

