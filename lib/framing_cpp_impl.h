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

#ifndef INCLUDED_INETS_FRAMING_CPP_IMPL_H
#define INCLUDED_INETS_FRAMING_CPP_IMPL_H

#include <inets/framing_cpp.h>
#include <gnuradio/digital/crc32.h>
#include <boost/crc.hpp>

namespace gr {
  namespace inets {

    class framing_cpp_impl : public framing_cpp
    {
     private:
      // Nothing to declare in this block.
      std::vector<int> _develop_mode_list;
      int _develop_mode;
      int _my_develop_mode;
      int _frame_type; 
      int _len_frame_type; // Bytes
      int _frame_index;
      int _ack_index;
      int _len_frame_index; // Bytes
      int _destination_address;
      int _ack_address;
      int _len_destination_address; // Bytes
      int _source_address; 
      int _len_source_address; // Bytes
      int _reserved_field_I;
      int _len_reserved_field_I; // Bytes
      int _reserved_field_II;
      int _len_reserved_field_II; // Bytes
      int _payload_length;
      int _len_payload_length; // Bytes
      int _increase_index;
      boost::crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true> _crc_impl; 
      pmt::pmt_t crc32_bb_calc(pmt::pmt_t msg);
      void frame_formation(pmt::pmt_t rx_payload);
      void frame_header_formation(std::vector<unsigned char> *frame_header);
      void intToByte(int i, std::vector<unsigned char> *bytes, int size);
      void disp_vec(std::vector<unsigned char> vec);

     public:
      framing_cpp_impl(std::vector<int> develop_mode_list, int frame_type, int len_frame_type, int frame_index, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int increase_index);
      ~framing_cpp_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAMING_CPP_IMPL_H */

