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
#include "analyze_frame_cpp_impl.h"
#include <gnuradio/digital/crc32.h>
#include <volk/volk.h>
#include <boost/crc.hpp>

namespace gr {
  namespace inets {

    analyze_frame_cpp::sptr
    analyze_frame_cpp::make(int develop_mode, int len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II, int len_payload_length)
    {
      return gnuradio::get_initial_sptr
        (new analyze_frame_cpp_impl(develop_mode, len_frame_type, len_frame_index, len_destination_address, len_source_address, len_reserved_field_I, len_reserved_field_II, len_payload_length));
    }

    /*
     * The private constructor
     */
    analyze_frame_cpp_impl::analyze_frame_cpp_impl(int develop_mode, int len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II, int len_payload_length)
      : gr::block("analyze_frame_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _len_frame_type(len_frame_type), // Bytes
        _len_frame_index(len_frame_index), // Bytes
        _len_destination_address(len_destination_address), // Bytes
        _len_source_address(len_source_address), // Bytes
        _len_reserved_field_I(len_reserved_field_I), // Bytes
        _len_reserved_field_II(len_reserved_field_II), // Bytes
        _len_payload_length(len_payload_length) // Bytes
    {
      message_port_register_in(pmt::mp("frame_in"));
      message_port_register_out(pmt::mp("good_frame_received"));
      message_port_register_out(pmt::mp("frame_header_out"));
      message_port_register_out(pmt::mp("payload_out"));
      set_msg_handler(pmt::mp("frame_in"), boost::bind(&analyze_frame_cpp_impl::frame_analysis, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    analyze_frame_cpp_impl::~analyze_frame_cpp_impl()
    {
    }

    void analyze_frame_cpp_impl::frame_analysis(pmt::pmt_t rx_frame)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "Frame analysis" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
      }
      if(pmt::is_pair(rx_frame)) 
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
           * frame header
           */
          int _header_length = get_frame_header_length();
          std::vector<unsigned char> frame_header_array;
          frame_header_array.insert(frame_header_array.end(), frame_array.begin(), frame_array.begin() + _header_length);
          std::cout << "length of frame_header_array is: " << frame_header_array.size() << std::endl;
          pmt::pmt_t frame_header_array_u8vector = pmt::init_u8vector(_header_length, frame_header_array);
          pmt::pmt_t frame_header_array_pmt = pmt::cons(meta, frame_header_array_u8vector);
          
          int frame_type(0);
          frame_type = frame_header_array[0];
          std::cout << "frame type is: " << frame_type << std::endl;
          /*
           * Paylaod
           */
          std::vector<unsigned char> payload_array;
          payload_array.insert(payload_array.begin(), frame_array.begin() + _header_length, frame_array.end());
          std::cout << "length of payload array is: " << payload_array.size() << std::endl;
          pmt::pmt_t payload_array_u8vector = pmt::init_u8vector(payload_array.size(), payload_array);
          pmt::pmt_t payload_array_pmt = pmt::cons(meta, payload_array_u8vector);
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
          if(_develop_mode)
            std::cout << "Transmission is: " << good_frame << std::endl;
          message_port_pub(pmt::mp("good_frame_received"), pmt::from_bool(good_frame));
          message_port_pub(pmt::mp("frame_header_out"), frame_header_array_pmt);
          message_port_pub(pmt::mp("payload_out"), payload_array_pmt);
        }
        else
          std::cout << "pmt is not a u8vector" << std::endl;
      }
      else 
        std::cout << "pmt is not a pair" << std::endl;
    }

    int
    analyze_frame_cpp_impl::get_frame_header_length()
    {
      return _len_frame_type + _len_frame_index + _len_destination_address + _len_source_address + _len_reserved_field_I + _len_reserved_field_II + _len_payload_length;

    } 

    void 
    analyze_frame_cpp_impl::intToByte(int i, std::vector<unsigned char> *bytes, int size)
    {
//      std::cout << "Type is about to converted" << std::endl;
      bytes->insert(bytes->end(), (unsigned char) (0xff & i));
//      std::cout << "First byte is converted" << std::endl;
      if(size > 1)
      {
        bytes->insert(bytes->end(), (unsigned char) ((0xff00 & i) >> 8));
        if(size > 2)
        {
          bytes->insert(bytes->end(), (unsigned char) ((0xff0000 & i) >> 16));
          if(size > 3)
          {
            bytes->insert(bytes->end(), (unsigned char) ((0xff000000 & i) >> 24));
          }
        }
      }
    }

    pmt::pmt_t
    analyze_frame_cpp_impl::crc32_bb_calc(pmt::pmt_t msg)
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

    void 
    analyze_frame_cpp_impl::disp_vec(std::vector<unsigned char> vec)
    {
      std::cout << "display unsigned char vector:" << ' ';
      for(int i=0; i<vec.size(); ++i)
        std::cout << vec[i] << ' ';
    }

  } /* namespace inets */
} /* namespace gr */

