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
#include "rts_framing_impl.h"

namespace gr {
  namespace inets {

    rts_framing::sptr
    rts_framing::make(int develop_mode, int block_id, int len_frame_type, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int len_num_transmission)
    {
      return gnuradio::get_initial_sptr
        (new rts_framing_impl(develop_mode, block_id, len_frame_type, len_frame_index, destination_address, len_destination_address, source_address, len_source_address, reserved_field_I, len_reserved_field_I, reserved_field_II, len_reserved_field_II, len_payload_length, len_num_transmission));
    }

    /*
     * The private constructor
     */
    rts_framing_impl::rts_framing_impl(int develop_mode, int block_id, int len_frame_type, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int len_num_transmission)
      : gr::block("rts_framing",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _len_frame_type(len_frame_type), // Bytes
        _len_frame_index(len_frame_index), // Bytes
        _destination_address(destination_address),
        _len_destination_address(len_destination_address), // Bytes
        _source_address(source_address), 
        _len_source_address(len_source_address), // Bytes
        _reserved_field_I(reserved_field_I), 
        _len_reserved_field_I(len_reserved_field_I), // Bytes
        _reserved_field_II(reserved_field_II),
        _len_reserved_field_II(len_reserved_field_II), // Bytes
        _len_payload_length(len_payload_length), // Bytes
	_len_num_transmission(len_num_transmission)
    {
      if(_develop_mode)
        std::cout << "develop_mode of rts_framing ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("data_frame_in"));
      set_msg_handler(pmt::mp("data_frame_in"), boost::bind(&rts_framing_impl::framing, this, _1 ));
      message_port_register_out(pmt::mp("frame_out"));
      // only in develop_mode
      message_port_register_out(pmt::mp("frame_pmt_out"));
      if(_frame_index > 255 || _frame_index < 0)
      {
        if(_develop_mode)
          std::cout << "frame index should in range [0, 255]. Frame index is set to 0." << std::endl;
        _frame_index = 0;
      }
    }

    /*
     * Our virtual destructor.
     */
    rts_framing_impl::~rts_framing_impl()
    {
    }

    void
    rts_framing_impl::framing(pmt::pmt_t data_frame)
    {
      pmt::pmt_t not_found;
      int nav_rts_us;
      // first calculate tx time of a data frame
      int header_length = pmt::to_long(pmt::dict_ref(data_frame, pmt::string_to_symbol("header_length"), not_found));
      int payload_length = pmt::to_long(pmt::dict_ref(data_frame, pmt::string_to_symbol("payload_length"), not_found));
      int mpdu_length = header_length + payload_length + 4;
      std::cout << "calculated mpdu length is: " << mpdu_length << " and measured mpdu length is: " << pmt::u8vector_elements(pmt::cdr(pmt::dict_ref(data_frame, pmt::string_to_symbol("frame_pmt"), not_found))).size() << std::endl;
      // then calculate tx time of a cts frame
 
      // then calculate tx time of an ack frame

      // plus three SIFS durations
      
       
      
    }

  } /* namespace inets */
} /* namespace gr */

