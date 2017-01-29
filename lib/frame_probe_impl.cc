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
#include "frame_probe_impl.h"

namespace gr {
  namespace inets {

    frame_probe::sptr
    frame_probe::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new frame_probe_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    frame_probe_impl::frame_probe_impl(int develop_mode, int block_id)
      : gr::block("frame_probe",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id)
    {
      message_port_register_in(pmt::mp("info_in"));
      set_msg_handler(
        pmt::mp("info_in"),
        boost::bind(&frame_probe_impl::read_info, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_probe_impl::~frame_probe_impl()
    {
    }

    void
    frame_probe_impl::read_info(pmt::pmt_t frame_info)
    { 
      pmt::pmt_t not_found;
      if(_develop_mode == 1)
        std::cout << "+++++++++ frame_probe ID: " << _block_id << " +++++++++" << std::endl;    
      if(pmt::is_dict(frame_info))
      {
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_type")))
          std::cout << "frame type is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_type"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_index")))
          std::cout << "frame index is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_index"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("destination_address")))
          std::cout << "destination address is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("destination_address"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("source_address")))
          std::cout << "source address is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("source_address"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("num_transmission")))
          std::cout << "number of transmission is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("num_transmission"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("reserved_field_I")))
          std::cout << "reserved field I is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("reserved_field_I"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("reserved_field_II")))
          std::cout << "reserved field II is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("reserved_field_II"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("payload_length")))
          std::cout << "frame length is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("payload_length"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("header_length")))
          std::cout << "header length is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("header_length"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("address_check")))
          std::cout << "address check is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("address_check"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("good_frame")))
          std::cout << "good frame is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("good_frame"), not_found) << std::endl;
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("reserved_field_ampdu")))
        {
          std::cout << "reserved field of ampdu subframe is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("reserved_field_ampdu"), not_found) << std::endl;
          std::cout << "frame type is AMPDU subframe" << std::endl;
        }
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_pmt")))
        {
          pmt::pmt_t frame_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_pmt"), not_found);
          std::vector<unsigned char> frame_array = pmt::u8vector_elements(pmt::cdr(frame_pmt));
          std::cout << "frame info contains a frame with length " << frame_array.size() << "bytes" << std::endl;
        }
      }
    }


  } /* namespace inets */
} /* namespace gr */

