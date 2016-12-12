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
    frame_header_analysis_cpp::make(std::vector<int> develop_mode_list, int len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II, int len_payload_length, int apply_address_check)
    {
      return gnuradio::get_initial_sptr
        (new frame_header_analysis_cpp_impl(develop_mode_list, len_frame_type, len_frame_index, len_destination_address, len_source_address, len_reserved_field_I, len_reserved_field_II, len_payload_length, apply_address_check));
    }

    /*
     * The private constructor
     */
    frame_header_analysis_cpp_impl::frame_header_analysis_cpp_impl(std::vector<int> develop_mode_list, int len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II, int len_payload_length, int apply_address_check)
      : gr::block("frame_header_analysis_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _my_develop_mode(11),
        _develop_mode_list(develop_mode_list),
        _len_frame_type(len_frame_type), // Bytes
        _len_frame_index(len_frame_index), // Bytes
        _len_destination_address(len_destination_address), // Bytes
        _len_source_address(len_source_address), // Bytes
        _len_reserved_field_I(len_reserved_field_I), // Bytes
        _len_reserved_field_II(len_reserved_field_II), // Bytes
        _len_payload_length(len_payload_length), // Bytes
        _apply_address_check(apply_address_check)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of frame_header_analysis_cpp is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
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
        std::cout << "++++++++  frame_header_analysis_cpp  +++++++" << std::endl;
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
          pmt::pmt_t frame_header_array_u8vector = pmt::init_u8vector(_header_length, frame_header_array);
          pmt::pmt_t frame_header_array_pmt = pmt::cons(meta, frame_header_array_u8vector);
          

          int frame_type = frame_header_array[0];
          int frame_index = frame_header_array[1];
          int destination_address = frame_header_array[2];
          int source_address = frame_header_array[3];
          int payload_length = frame_header_array[8];
          int address_check = !(_apply_address_check);
          int is_good_frame = 0;
          pmt::pmt_t frame_info  = pmt::make_dict();
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_type"), pmt::from_long(frame_type));
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_index"), pmt::from_long(frame_index));
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("destination_address"), pmt::from_long(destination_address));
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("source_address"), pmt::from_long(source_address));
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("payload_length"), pmt::from_long(payload_length));
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("header_length"), pmt::from_long(_header_length));
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_pmt"), frame_pmt);
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("address_check"),pmt::from_long(address_check));
          frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("good_frame"),pmt::from_long(is_good_frame));

          if(_develop_mode)
          {
            std::cout << "length of frame_header_array is: " << frame_header_array.size() << std::endl;
            std::cout << "frame type is: " << frame_type << std::endl;
            std::cout << "frame index is: " << frame_index << std::endl;
            std::cout << "destination address is: " << destination_address << std::endl;
            std::cout << "source address is: " << source_address << std::endl;
            std::cout << "payload length is: " << payload_length << std::endl;
            std::cout << "frame header length is: " << _header_length << std::endl;
            std::cout << "address check is initialized to: " << address_check << std::endl;
            std::cout << "frame verification (good_frame) is initialized to: " << is_good_frame << std::endl;
          }
          message_port_pub(pmt::mp("frame_info_out"), frame_info);
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

