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
#include "frame_header_analysis_cpp_impl.h"
#include <gnuradio/digital/crc32.h>
#include <volk/volk.h>
#include <boost/crc.hpp>

namespace gr {
  namespace inets {

    frame_header_analysis_cpp::sptr
    frame_header_analysis_cpp::make(int develop_mode, int len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II, int len_payload_length)
    {
      return gnuradio::get_initial_sptr
        (new frame_header_analysis_cpp_impl(develop_mode, len_frame_type, len_frame_index, len_destination_address, len_source_address, len_reserved_field_I, len_reserved_field_II, len_payload_length));
    }

    /*
     * The private constructor
     */
    frame_header_analysis_cpp_impl::frame_header_analysis_cpp_impl(int develop_mode, int len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II, int len_payload_length)
      : gr::block("frame_header_analysis_cpp",
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
      message_port_register_out(pmt::mp("frame_type_out"));
      message_port_register_out(pmt::mp("frame_index_out"));
      message_port_register_out(pmt::mp("destination_address_out"));
      message_port_register_out(pmt::mp("source_address_out"));
      message_port_register_out(pmt::mp("reserved_field_I_out"));
      message_port_register_out(pmt::mp("reserved_field_II_out"));
      message_port_register_out(pmt::mp("payload_length_out"));
      message_port_register_out(pmt::mp("frame_header_out"));
      message_port_register_out(pmt::mp("frame_out"));
      set_msg_handler(pmt::mp("frame_in"), boost::bind(&frame_header_analysis_cpp_impl::frame_analysis, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    frame_header_analysis_cpp_impl::~frame_header_analysis_cpp_impl()
    {
    }

    void frame_header_analysis_cpp_impl::frame_analysis(pmt::pmt_t rx_frame)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "Frame header analysis" << std::endl;
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
          

          int frame_type = frame_header_array[0];
          int frame_index = frame_header_array[1];
          int destination_address = frame_header_array[2];
          int source_address = frame_header_array[3];
          int payload_length = frame_header_array[8];
          if(_develop_mode)
          {
            std::cout << "frame type is: " << frame_type << std::endl;
            std::cout << "frame index is: " << frame_index << std::endl;
            std::cout << "destination address is: " << destination_address << std::endl;
            std::cout << "source address is: " << source_address << std::endl;
            std::cout << "paylaod length is: " << payload_length << std::endl;
          }
          message_port_pub(pmt::mp("frame_type_out"), pmt::from_long(frame_type));
          message_port_pub(pmt::mp("frame_index_out"), pmt::from_long(frame_index));
          message_port_pub(pmt::mp("destination_address_out"), pmt::from_long(destination_address));
          message_port_pub(pmt::mp("source_address_out"), pmt::from_long(source_address));
          message_port_pub(pmt::mp("payload_length_out"), pmt::from_long(payload_length));
          message_port_pub(pmt::mp("frame_header_out"), frame_header_array_pmt);
          message_port_pub(pmt::mp("frame_out"), rx_frame);
        }
        else
          std::cout << "pmt is not a u8vector" << std::endl;
      }
      else 
        std::cout << "pmt is not a pair" << std::endl;
    }

    int
    frame_header_analysis_cpp_impl::get_frame_header_length()
    {
      return _len_frame_type + _len_frame_index + _len_destination_address + _len_source_address + _len_reserved_field_I + _len_reserved_field_II + _len_payload_length;

    } 

  } /* namespace inets */
} /* namespace gr */

