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

#ifndef INCLUDED_INETS_IDLE_IMPL_H
#define INCLUDED_INETS_IDLE_IMPL_H

#include <inets/idle.h>
#include <queue>
#include <gnuradio/digital/crc32.h>
#include <boost/crc.hpp>

namespace gr {
  namespace inets {

    class idle_impl : public idle
    {
     private:
      float _experiment_duration_s;
      int _max_buffer_size; 
      int _develop_mode; 
      int _block_id; 
      bool _experiment_running;
      bool _in_idle;
      std::queue<pmt::pmt_t> _tx_buff;
      int _max_num_retransmission;
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
      int _num_transmission; 
      int _len_num_transmission; // Bytes
      int _reserved_field_I;
      int _len_reserved_field_I; // Bytes
      int _reserved_field_II;
      int _len_reserved_field_II; // Bytes
      int _payload_length;
      int _len_payload_length; // Bytes
      int _increase_index;
      int _last_frame_index;
      pmt::pmt_t _sending_data_frame;
      boost::crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true> _crc_impl; 
      void reset_idle(pmt::pmt_t data);
      void state_transition(pmt::pmt_t data);
      pmt::pmt_t data_frame_framing(pmt::pmt_t rx_payload);
      pmt::pmt_t ack_frame_framing(pmt::pmt_t rx_payload);
      pmt::pmt_t frame_header_formation(std::vector<unsigned char> *frame_header, int frame_type, int frame_index, int destination_address, int source_address, int reserved_field_I, int reserved_field_II, int payload_length, int num_transmission);
      void intToByte(int i, std::vector<unsigned char> *bytes, int size);
      pmt::pmt_t crc32_bb_calc(pmt::pmt_t msg);
      int get_frame_header_length();
      void send_data_frame_to_send_frame();

     public:
      idle_impl(int develop_mode, int block_id, float experiment_duration_s, int max_num_retransmission, int max_buffer_size, int frame_type, int len_frame_type, int frame_index, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int increase_index, int len_num_transmission);
      ~idle_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_IDLE_IMPL_H */

