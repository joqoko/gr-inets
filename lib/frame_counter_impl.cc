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
#include "frame_counter_impl.h"

namespace gr {
  namespace inets {

    frame_counter::sptr
    frame_counter::make(int develop_mode, int block_id, int counts)
    {
      return gnuradio::get_initial_sptr
        (new frame_counter_impl(develop_mode, block_id, counts));
    }

    /*
     * The private constructor
     */
    frame_counter_impl::frame_counter_impl(int develop_mode, int block_id, int counts)
      : gr::block("frame_counter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _counts(counts),
        _current_count(0)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_counter id: " << _block_id << " is activated." << std::endl;
      message_port_register_out(pmt::mp("select_out"));
      message_port_register_out(pmt::mp("unselect_out"));
      message_port_register_in(pmt::mp("counts_in"));
      set_msg_handler(
        pmt::mp("counts_in"),
        boost::bind(&frame_counter_impl::counting, this, _1)
      );
      message_port_register_in(pmt::mp("reset_in"));
      set_msg_handler(
        pmt::mp("reset_in"),
        boost::bind(&frame_counter_impl::reset, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_counter_impl::~frame_counter_impl()
    {
    }

    void
    frame_counter_impl::reset(pmt::pmt_t pmt_in)
    {
      _current_count = 0;
    }

    void
    frame_counter_impl::counting(pmt::pmt_t pmt_in)
    {
      if(_current_count < _counts - 1)
      {
        _current_count++;
        message_port_pub(pmt::mp("unselect_out"), pmt_in);
      }
      else
      {
        _current_count = 0;
        message_port_pub(pmt::mp("select_out"), pmt_in);
      } 
    }

  } /* namespace inets */
} /* namespace gr */

