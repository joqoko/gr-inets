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

namespace gr {
  namespace inets {

    class framing_cpp_impl : public framing_cpp
    {
     private:
      // Nothing to declare in this block.
      int _develop_mode;
      int _frame_type; 
      int _len_frame_type; // Bytes
      int _len_frame_index; // Bytes
      int _len_destination_address; // Bytes
      int _len_source_address; // Bytes
      int _len_reserved_field_I; // Bytes
      int _len_reserved_field_II; // Bytes
      int _len_payload_length; // Bytes

     public:
      framing_cpp_impl(int develop_mode, int frame_type, int len_frame_type, int len_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II);
      ~framing_cpp_impl();

      void frame_formation(pmt::pmt_t payload);
      std::vector<unsigned char> frame_header_formation();
      void intToByte(int i, std::vector<unsigned char> *bytes, int size);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAMING_CPP_IMPL_H */

