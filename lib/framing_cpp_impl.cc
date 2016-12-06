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
#include "framing_cpp_impl.h"

namespace gr {
  namespace inets {

    framing_cpp::sptr
    framing_cpp::make(int develop_mode, int frame_type, int len_frame_type, int len_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II)
    {
      return gnuradio::get_initial_sptr
        (new framing_cpp_impl(develop_mode, frame_type, len_frame_type, len_index, len_destination_address, len_source_address, len_reserved_field_I, len_reserved_field_II));
    }

    /*
     * The private constructor
     */
    framing_cpp_impl::framing_cpp_impl(int develop_mode, int frame_type, int len_frame_type, int len_frame_index, int len_destination_address, int len_source_address, int len_reserved_field_I, int len_reserved_field_II)
      : gr::block("framing_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _len_frame_type(len_frame_type), // Bytes
        _len_frame_index(len_frame_index), // Bytes
        _len_destination_address(len_destination_address), // Bytes
        _len_source_address(len_source_address), // Bytes
        _len_reserved_field_I(len_reserved_field_I), // Bytes
        _len_reserved_field_II(len_reserved_field_II), // Bytes
        _len_payload_length(0), // Bytes
       _frame_type(frame_type)
    {
      message_port_register_in(pmt::mp("payload_in"));
      message_port_register_out(pmt::mp("frame_out"));
      set_msg_handler(pmt::mp("payload_in"), boost::bind(&framing_cpp_impl::frame_formation, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    framing_cpp_impl::~framing_cpp_impl()
    {
    }

    void 
    framing_cpp_impl::frame_formation(pmt::pmt_t payload)
    {
        std::cout << "Here 1" << std::endl;
        if(pmt::is_pair(payload)) {

            std::cout << "Here 2" << std::endl;

            pmt::pmt_t payload_pmt = pmt::cdr(payload);

            std::vector<unsigned char> frame_header = frame_header_formation();
            /*
            if(pmt::is_u8vector(payload_pmt)){
                const std::vector< unsigned char > payload_raw = pmt::u8vector_elements(payload_pmt);
                std::vector< unsigned char > packet;
                
                packet.insert(packet.end(), _random.begin(), _random.begin() + _padding);
                packet.insert(packet.end(), _preamble_packed.begin(), _preamble_packed.end());
    
                unsigned char hdr[32]; 
                _header_generator->header_formatter(payload.size(), hdr, std::vector<tag_t>());
                std::vector<unsigned char> hdr_packed;
                //Big Endian. MSB to lowest position
                for(int i = 0; i < 32; i += 8) {
                    unsigned char curr_byte = 0;
                    for(int j = 0; j < 8; j++) {
                        curr_byte += hdr[i + j] << (7 - j);
                    }
                    hdr_packed.push_back(curr_byte);
                }

                packet.insert(packet.end(), hdr_packed.begin(), hdr_packed.end());
                packet.insert(packet.end(), payload.begin(), payload.end());
                packet.insert(packet.end(), _random.begin(), _random.begin() + _padding);

                // Add key to the tx_time tag
                static const pmt::pmt_t time_key = pmt::string_to_symbol("tx_time");
                // Get the time
                struct timeval t;
                gettimeofday(&t, NULL);
                double tx_time = t.tv_sec + t.tv_usec / 1000000.0;
                double min_time_diff = (1000 * 8.0) / _bps; //Max packet len [bit] / bit rate 
                // Ensure that frames are not overlap each other
                if((tx_time - _last_tx_time) <= min_time_diff) {
                    tx_time = _last_tx_time + min_time_diff;
                } else {
                    //std::cout << "in time packet" << std::endl;
                }
                //std::cout << "tx time = " << std::fixed << tx_time << std::endl;
                // update the tx_time to the current packet
                _last_tx_time = tx_time;
                // question 1: why add 0.05?
                uhd::time_spec_t now = uhd::time_spec_t(tx_time)
                    + uhd::time_spec_t(0.05);
                // the value of the tag is a tuple
                const pmt::pmt_t time_value = pmt::make_tuple(
                    pmt::from_uint64(now.get_full_secs()),
                    pmt::from_double(now.get_frac_secs())
                );

                pmt::pmt_t out_pmt_vector = pmt::init_u8vector(packet.size(), packet);
                pmt::pmt_t meta = pmt::make_dict();
                //meta = pmt::dict_add(meta, pmt::mp("tx_time"), time_value);
                pmt::pmt_t pdu = pmt::cons(meta, out_pmt_vector);

                message_port_pub(pmt::mp("packet_out"), pdu);
            } else { std::cout << "no u8 vector " << std::endl; }
           */
          message_port_pub(pmt::mp("frame_out"), pmt::init_u8vector(frame_header.size(), frame_header));  
        } 
        else 
        {
            std::cout << "pmt is not a pair" << std::endl;
        }
    }

    std::vector<unsigned char>
    framing_cpp_impl::frame_header_formation()
    {
      std::cout << "frame header is generated" << std::endl;
      std::vector< unsigned char > vec_frame_header;
      std::vector< unsigned char > vec_frame_type;
      std::vector< unsigned char > vec_frame_index;
      std::vector< unsigned char > vec_destination_address;
      std::vector< unsigned char > vec_source_address;
      std::vector< unsigned char > vec_reserved_field_I;
      std::vector< unsigned char > vec_reserved_field_II;
      /* 
        frame type (1 Bytes)
        frame index (1 Bytes)
        Destination address (1 Bytes)
        Source address (1 Bytes)
        Reserved field 1 (2 Bytes)
        Reserved field 2 (2 Bytes)
        Payload length (1 Bytes)
       */
      // Frame type 
      intToByte(_frame_type, &vec_frame_type, 2);
      for (int i = 0; i < vec_frame_type.size(); i++) {
        std::cout <<  static_cast<unsigned>(vec_frame_type[i])  << " " << std::endl;
      }
      return vec_frame_header;
    }

    void 
    framing_cpp_impl::intToByte(int i, std::vector<unsigned char> *bytes, int size)
    {
      std::cout << "Type is about to converted" << std::endl;
      bytes->insert(bytes->end(), (unsigned char) (0xff & i));
      std::cout << "First byte is converted" << std::endl;
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
