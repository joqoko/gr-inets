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
#include "get_payload_impl.h"

namespace gr {
  namespace inets {

    get_payload::sptr
    get_payload::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new get_payload_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    get_payload_impl::get_payload_impl(int develop_mode, int block_id)
      : gr::block("get_payload",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id)
    {
      if(_develop_mode)
        std::cout << "develop_mode of get_payload ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_info_in"));
      set_msg_handler(pmt::mp("frame_info_in"), boost::bind(&get_payload_impl::cut_payload, this, _1 ));
      message_port_register_out(pmt::mp("payload_out"));
      
    }

    /*
     * Our virtual destructor.
     */
    get_payload_impl::~get_payload_impl()
    {
    }

    void
    get_payload_impl::cut_payload(pmt::pmt_t frame_info_in)
    {
      pmt::pmt_t not_found;
      struct timeval t; 
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
      if(_develop_mode)
        std::cout << "+++  get_payload ID: " << _block_id << "  get an input ";
      if(pmt::dict_has_key(frame_info_in, pmt::string_to_symbol("payload")))
      {
        pmt::pmt_t payload = pmt::dict_ref(frame_info_in, pmt::string_to_symbol("payload"), not_found); 
        if(_develop_mode)
          std::cout << " with payload at time " << current_time << " s" << std::endl;
        pmt::pmt_t meta = pmt::make_dict();
        pmt::pmt_t pdu = pmt::cons(meta, payload);
        message_port_pub(pmt::mp("payload_out"), pdu);
      }
      else
      {
        if(_develop_mode)
        {
          std::cout << " without payload at time " << current_time << " s" << std::endl; 
        }
      }
    }

  } /* namespace inets */
} /* namespace gr */

