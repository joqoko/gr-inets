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
#include "frame_verification_cpp_impl.h"
#include <gnuradio/digital/crc32.h>
#include <volk/volk.h>
#include <boost/crc.hpp>

namespace gr {
  namespace inets {

    frame_verification_cpp::sptr
    frame_verification_cpp::make(int develop_mode)
    {
      return gnuradio::get_initial_sptr
        (new frame_verification_cpp_impl(develop_mode));
    }

    /*
     * The private constructor
     */
    frame_verification_cpp_impl::frame_verification_cpp_impl(int develop_mode)
      : gr::block("frame_verification_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
       _develop_mode(develop_mode)
    {
      message_port_register_in(pmt::mp("frame_info_in"));
      message_port_register_out(pmt::mp("good_frame"));
      message_port_register_out(pmt::mp("payload_out"));
      set_msg_handler(pmt::mp("frame_info_in"), boost::bind(&frame_verification_cpp_impl::check_frame, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    frame_verification_cpp_impl::~frame_verification_cpp_impl()
    {
    }

    void 
    frame_verification_cpp_impl::check_frame(pmt::pmt_t frame_info)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "Frame verification" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
      }
      if(pmt::is_dict(frame_info)) 
      {
        bool good_frame;
        pmt::pmt_t not_found;
        // frame_type
        pmt::pmt_t frame_type_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_type"), not_found);
        int frame_type = pmt::to_long(frame_type_pmt);
        // frame_index
        pmt::pmt_t frame_index_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_index"), not_found);
        int frame_index = pmt::to_long(frame_index_pmt);
        // destination_address
        pmt::pmt_t destination_address_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("destination_address"), not_found);
        int destination_address = pmt::to_long(destination_address_pmt);
        // source_address
        pmt::pmt_t source_address_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("source_address"), not_found);
        int source_address = pmt::to_long(source_address_pmt);
        // payload_length
        pmt::pmt_t payload_length_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("payload_length"), not_found);
        int payload_length = pmt::to_long(payload_length_pmt);
        if(_develop_mode)
        {
          std::cout << "dict has key frame_type: " << pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_type")) << " with value: " << frame_type << std::endl;
          std::cout << "dict has key frame_index: " << pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_index")) << " with value: " << frame_index << std::endl;
          std::cout << "dict has key destination_address: " << pmt::dict_has_key(frame_info, pmt::string_to_symbol("destination_address")) << " with value: " << destination_address << std::endl;
          std::cout << "dict has key source address: " << pmt::dict_has_key(frame_info, pmt::string_to_symbol("source_address")) << " with value: " << source_address << std::endl;
          std::cout << "dict has key payload_length: " << pmt::dict_has_key(frame_info, pmt::string_to_symbol("payload_length")) << " with value: " << payload_length << std::endl;
        }
      }
      else 
        std::cout << "pmt is not a dict" << std::endl;
    }
    

    void 
    frame_verification_cpp_impl::check_frame_v0(pmt::pmt_t rx_frame)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "Frame verification" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
      }
      if(pmt::is_dict(rx_frame)) 
      {
        bool good_frame;
        pmt::pmt_t meta = pmt::car(rx_frame);
        pmt::pmt_t frame_pmt = pmt::cdr(rx_frame);
        std::vector<unsigned char> frame_array; 
        if(pmt::is_u8vector(frame_pmt))
        {
          std::vector<unsigned char> frame_array = pmt::u8vector_elements(frame_pmt);
          int _frame_length = frame_array.size(); 
          /*
           * CRC
           */
          std::vector<unsigned char> frame_array_for_crc;
          frame_array_for_crc.insert(frame_array_for_crc.begin(), frame_array.begin(), frame_array.end() - 4); 
          // only for test
          //frame_array_for_crc.insert(frame_array_for_crc.begin(), frame_array.begin() + 4, frame_array.end()); 
          
          pmt::pmt_t frame_before_recrc_u8vector = pmt::init_u8vector(frame_array_for_crc.size(), frame_array_for_crc);
          pmt::pmt_t frame_array_before_recrc = pmt::cons(meta, frame_before_recrc_u8vector); 
          pmt::pmt_t frame_array_recrc = crc32_bb_calc(frame_array_before_recrc);
          frame_array_for_crc = pmt::u8vector_elements(pmt::cdr(frame_array_recrc));
          good_frame = (frame_array_for_crc == frame_array);
          /*
           * payload
           */
          std::vector<unsigned char> payload_array;
          payload_array.insert(payload_array.begin(), frame_array.begin() + 9, frame_array.end());
          pmt::pmt_t payload_array_u8vector = pmt::init_u8vector(payload_array.size(), payload_array);
          pmt::pmt_t payload_array_pmt = pmt::cons(meta, payload_array_u8vector);
          if(_develop_mode)
          {
            std::cout << "Frame verification is: " << good_frame << " (1: passed, 0: failed)." << std::endl;
            std::cout << "length of payload array is: " << payload_array.size() << std::endl;
          }
          message_port_pub(pmt::mp("good_frame_received"), pmt::from_bool(good_frame));
          message_port_pub(pmt::mp("payload_out"), payload_array_pmt);
        }
        else
          std::cout << "pmt is not a u8vector" << std::endl;
      }
      else 
        std::cout << "pmt is not a pair" << std::endl;
    }
    
    pmt::pmt_t
    frame_verification_cpp_impl::crc32_bb_calc(pmt::pmt_t msg)
    {
      // extract input pdu
      pmt::pmt_t meta(pmt::car(msg));
      pmt::pmt_t bytes(pmt::cdr(msg));

      unsigned int crc;
      size_t pkt_len(0);
      const uint8_t* bytes_in = pmt::u8vector_elements(bytes, pkt_len);
      uint8_t* bytes_out = (uint8_t*)volk_malloc(4 + pkt_len*sizeof(uint8_t),
                                                 volk_get_alignment());

      _crc_impl.reset();
      _crc_impl.process_bytes(bytes_in, pkt_len);
      crc = _crc_impl();
      memcpy((void*)bytes_out, (const void*)bytes_in, pkt_len);
      memcpy((void*)(bytes_out + pkt_len), &crc, 4); // FIXME big-endian/little-endian, this might be wrong

      pmt::pmt_t output = pmt::init_u8vector(pkt_len+4, bytes_out); // this copies the values from bytes_out into the u8vector
      return pmt::cons(meta, output);
    } 

  } /* namespace inets */
} /* namespace gr */

