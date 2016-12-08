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

namespace gr {
  namespace inets {

    analyze_frame_cpp::sptr
    analyze_frame_cpp::make(int develop_mode,  len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II, int len_payload_length)
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
              gr::io_signature::make(0, 0, 0))
    {
      message_port_register_in(pmt::mp("frame_in"));
      message_port_register_out(pmt::mp("frame_header_out"));
      message_port_register_out(pmt::mp("payload_out"));
      set_msg_handler(pmt::mp("frame_in"), boost::bind(&framing_cpp_impl::frame_formation, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    analyze_frame_cpp_impl::~analyze_frame_cpp_impl()
    {
    }

    void analyze_frame_cpp_impl::frame_analysis(pmt::pmt_t rx_frame)
    {
      if(pmt::is_pair(rx_frame)) 
      {
        pmt::pmt_t meta = pmt::car(rx_frame);
        pmt::pmt_t frame_pmt = pmt::cdr(rx_frame);
        std::vector<unsigned char> frame_array; 
        if(pmt::is_u8vector(frame_pmt))
        {
          frame_array = pmt::u8vector_elements(frame_pmt);
          _frame_length = frame_array.size(); 
          _header_length = get_frame_header_length();
          std::vector<unsigned char> frame_header;
          payload_array = frame_array.assign(_header_length + 1, frame_array.end());
          frame_header_array = frame_array.erase(_header_length + 1, frame_array.end());
          message_port_pub(pmt::mp("frame_header_out"),frame_header_array);
          message_port_pub(pmt::mp("payload_out"), payload_array);
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
      return len_frame_type + len_frame_index + len_destination_address + len_source_address + len_reserved_field_I + len_reserved_field_II + len_payload_length;

    } 


    void 
    framing_cpp_impl::intToByte(int i, std::vector<unsigned char> *bytes, int size)
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



  } /* namespace inets */
} /* namespace gr */

