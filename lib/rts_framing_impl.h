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

#ifndef INCLUDED_INETS_RTS_FRAMING_IMPL_H
#define INCLUDED_INETS_RTS_FRAMING_IMPL_H

#include <inets/rts_framing.h>

namespace gr {
  namespace inets {

    class rts_framing_impl : public rts_framing
    {
     private:
      int _develop_mode;
      int _block_id;
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
      int _reserved_field_ampdu; // Bytes
      int _payload_length;
      int _len_payload_length; // Bytes
      int _len_num_transmission;
      void framing(pmt::pmt_t data_frame);
 
     public:
      rts_framing_impl(int develop_mode, int block_id, int len_frame_type, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int len_num_transmission);
      ~rts_framing_impl();
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_RTS_FRAMING_IMPL_H */

