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
#include "resend_check_impl.h"

namespace gr {
  namespace inets {

    resend_check::sptr
    resend_check::make(int develop_mode, int block_id, int max_resend)
    {
      return gnuradio::get_initial_sptr
        (new resend_check_impl(develop_mode, block_id, max_resend));
    }

    /*
     * The private constructor
     */
    resend_check_impl::resend_check_impl(int develop_mode, int block_id, int max_resend)
      : gr::block("resend_check",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _max_resend(max_resend)
    {
      if(_develop_mode)
        std::cout << "develop mode of resend_check ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_info_in"));
      message_port_register_out(pmt::mp("resend_check_pass_out"));
      message_port_register_out(pmt::mp("resend_check_fail_out"));
      set_msg_handler(pmt::mp("frame_info_in"), boost::bind(&resend_check_impl::check_resend, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    resend_check_impl::~resend_check_impl()
    {
    }

    void
    resend_check_impl::check_resend(pmt::pmt_t frame_in)
    {
      pmt::pmt_t not_found;
      int n_transmission = pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("num_transmission"), not_found));
      if(n_transmission >= _max_resend)
      {
        if(_develop_mode)
          std::cout << "frame dropped because maximal retransmissions is reached. the frame index of the dropped frame is from node: " << pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("source_address"), not_found)) << " with frame index: " << pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("frame_index"), not_found)) << std::endl;
        message_port_pub(pmt::mp("resend_check_fail_out"),frame_in);
      }
      else
      {
        if(_develop_mode)
          std::cout << "frame from node: " << pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("source_address"), not_found)) << " with frame index: " << pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("frame_index"), not_found)) << " will be retransmitted the " << n_transmission + 1 << "th time" << std::endl;
          frame_in = pmt::dict_delete(frame_in, pmt::string_to_symbol("num_transmission"));
          frame_in = pmt::dict_add(frame_in, pmt::string_to_symbol("num_transmission"), pmt::from_long(n_transmission + 1));
        message_port_pub(pmt::mp("resend_check_pass_out"),frame_in);
      }
    }

  } /* namespace inets */
} /* namespace gr */

