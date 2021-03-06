/* -*- c++ -*- */
/* 
 * Copyright 2016 <inets>.
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
#include <gnuradio/digital/crc32.h> 
#include <volk/volk.h>
#include <boost/crc.hpp>
namespace gr {
  namespace inets {

    framing_cpp::sptr
    framing_cpp::make(std::vector<int> develop_mode_list, int frame_type, int len_frame_type, int frame_index, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int increase_index)
    {
      return gnuradio::get_initial_sptr
        (new framing_cpp_impl(develop_mode_list, frame_type, len_frame_type, frame_index, len_frame_index, destination_address, len_destination_address, source_address, len_source_address, reserved_field_I, len_reserved_field_I, reserved_field_II, len_reserved_field_II, len_payload_length, increase_index));
    }

    /*
     * The private constructor
     */
    framing_cpp_impl::framing_cpp_impl(std::vector<int> develop_mode_list, int frame_type, int len_frame_type, int frame_index, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int increase_index)
      : gr::block("framing_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode_list(develop_mode_list),
        _my_develop_mode(2),
        _len_frame_type(len_frame_type), // Bytes
        _frame_index(frame_index),
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
        _frame_type(frame_type),
        _increase_index(increase_index)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of framing_cpp is activated." << std::endl;
      message_port_register_in(pmt::mp("payload_in"));
      message_port_register_out(pmt::mp("frame_out"));
      message_port_register_out(pmt::mp("tx_frame_info_out"));
      set_msg_handler(pmt::mp("payload_in"), boost::bind(&framing_cpp_impl::frame_formation, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    framing_cpp_impl::~framing_cpp_impl()
    {
    }

    void 
    framing_cpp_impl::frame_formation(pmt::pmt_t rx_payload)
    {
      if(_develop_mode)
      {
        std::cout << "++++++++++++++   Framing_cpp  ++++++++++++++" << std::endl;
      }
      /*
       * Generate a data frame
       */
      if(pmt::is_pair(rx_payload)) 
      {
        pmt::pmt_t meta = pmt::car(rx_payload);
        pmt::pmt_t payload_pmt = pmt::cdr(rx_payload);
        std::vector<unsigned char> payload_array; 
        if(pmt::is_u8vector(payload_pmt))
        {
          _frame_type = 1;
          payload_array = pmt::u8vector_elements(payload_pmt);
          _payload_length = payload_array.size(); 
          std::vector<unsigned char> frame_header;
          frame_header_formation(&frame_header);
          std::vector<unsigned char> frame;
          frame.insert(frame.end(), frame_header.begin(), frame_header.end());
          if(_develop_mode)
            std::cout << "frame header, length " << frame.size() << std::endl;
          frame.insert(frame.end(), payload_array.begin(), payload_array.end());
          if(_develop_mode)
            std::cout << "frame header with payload, length " << frame.size() << std::endl;
          // crc
          // crc32_bb_calc(&frame);
          // change frame to pmt::pmt_t
          pmt::pmt_t frame_before_crc_u8vector = pmt::init_u8vector(frame.size(), frame);
          pmt::pmt_t frame_before_crc = pmt::cons(meta, frame_before_crc_u8vector); 
          pmt::pmt_t frame_after_crc = crc32_bb_calc(frame_before_crc);
          std::vector<unsigned char> frame_after_crc_vector = pmt::u8vector_elements(pmt::cdr(frame_after_crc));
          if(_develop_mode)
            std::cout << "frame header with payload with crc, length " << frame_after_crc_vector.size() << std::endl;
          message_port_pub(pmt::mp("frame_out"), frame_after_crc);
        }
        else
          std::cout << "pmt is not a u8vector" << std::endl;
      }
      /*
       * Generate an ack frame
       */
      else if(pmt::is_dict(rx_payload))
      {
        pmt::pmt_t meta = pmt::make_dict();
        pmt::pmt_t not_found;
        int _frame_type = pmt::to_long(pmt::dict_ref(rx_payload, pmt::string_to_symbol("frame_type"), not_found));
        // generate an ack frame
        if(_frame_type == 2)
        { 
          int _ack_address = pmt::to_long(pmt::dict_ref(rx_payload, pmt::string_to_symbol("destination_address"), not_found));
          int _ack_index = pmt::to_long(pmt::dict_ref(rx_payload, pmt::string_to_symbol("frame_index"), not_found));
          std::vector<unsigned char> frame_header;
          frame_header_formation(&frame_header);
          std::vector<unsigned char> frame;
          frame.insert(frame.end(), frame_header.begin(), frame_header.end());
          if(_develop_mode)
            std::cout << "frame header, length " << frame.size() << std::endl;
          // crc
          // crc32_bb_calc(&frame);
          // change frame to pmt::pmt_t
          pmt::pmt_t frame_before_crc_u8vector = pmt::init_u8vector(frame.size(), frame);
          pmt::pmt_t frame_before_crc = pmt::cons(meta, frame_before_crc_u8vector); 
          pmt::pmt_t frame_after_crc = crc32_bb_calc(frame_before_crc);
          std::vector<unsigned char> frame_after_crc_vector = pmt::u8vector_elements(pmt::cdr(frame_after_crc));
          if(_develop_mode)
            std::cout << "ack frame with crc(no payload), length " << frame_after_crc_vector.size() << std::endl;
          message_port_pub(pmt::mp("frame_out"), frame_after_crc);
        }
        /*
         * unknown frame type 
         */
        else
          std::cout << "frame type of received frame_info is: " << _frame_type << ". do nothing here now." << std::endl;
      }
      else 
        std::cout << "pmt is not a pair" << std::endl;
    }

    void 
    framing_cpp_impl::frame_header_formation(std::vector<unsigned char> *frame_header)
    {
      std::vector< unsigned char > vec_frame_header;
      std::vector< unsigned char > vec_frame_type;
      std::vector< unsigned char > vec_frame_index;
      std::vector< unsigned char > vec_destination_address;
      std::vector< unsigned char > vec_source_address;
      std::vector< unsigned char > vec_reserved_field_I;
      std::vector< unsigned char > vec_reserved_field_II;
      std::vector< unsigned char > vec_payload_length;
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
      intToByte(_frame_type, &vec_frame_type, _len_frame_type);
      if(_frame_type == 1)
      {
        // Frame index
        if(_increase_index)
          _frame_index++;
        intToByte(_frame_index, &vec_frame_index, _len_frame_index);
        // Destination address
        intToByte(_destination_address, &vec_destination_address, _len_destination_address);
        // Payload length
        intToByte(_payload_length, &vec_payload_length, _len_payload_length);
      }
      else if(_frame_type == 2)
      {
        // Frame index
        intToByte(_ack_index, &vec_frame_index, _len_frame_index);
        // Destination address
        intToByte(_ack_address, &vec_destination_address, _len_destination_address);
        // Payload length
        intToByte(0, &vec_payload_length, _len_payload_length);
      }
      else
      {
        std::cout << "Framing: unknown frame type. Please check your connections." << std::endl;
        // Frame index
        if(_increase_index)
          _frame_index++;
        intToByte(_frame_index, &vec_frame_index, _len_frame_index);
        // Destination address
        intToByte(_destination_address, &vec_destination_address, _len_destination_address);
        // Payload length
        intToByte(_payload_length, &vec_payload_length, _len_payload_length);
      }
      // Source address
      intToByte(_source_address, &vec_source_address, _len_source_address);
      // Reserved field I
      intToByte(_reserved_field_I, &vec_reserved_field_I, _len_reserved_field_I);
      // Reserved field II
      intToByte(_reserved_field_II, &vec_reserved_field_II, _len_reserved_field_II);

      //std::cout  << "Frame header length before frame type: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_frame_type.begin(), vec_frame_type.begin() + _len_frame_type);
      //std::cout  << "Frame header length after frame type: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_frame_index.begin(), vec_frame_index.begin() + _len_frame_index);
      frame_header->insert(frame_header->end(), vec_destination_address.begin(), vec_destination_address.begin() + _len_destination_address);
      frame_header->insert(frame_header->end(), vec_source_address.begin(), vec_source_address.begin() + _len_source_address);
      frame_header->insert(frame_header->end(), vec_reserved_field_I.begin(), vec_reserved_field_I.begin() + _len_reserved_field_I);
      frame_header->insert(frame_header->end(), vec_reserved_field_II.begin(), vec_reserved_field_II.begin() + _len_reserved_field_II);
      frame_header->insert(frame_header->end(), vec_payload_length.begin(), vec_payload_length.begin() + _len_payload_length);

      pmt::pmt_t frame_info = pmt::make_dict();
      frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_type"), pmt::from_long(_frame_type));
      frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_index"), pmt::from_long(_frame_index));
      frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("destination_address"), pmt::from_long(_destination_address));
      frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("source_address"), pmt::from_long(_source_address));
      frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("payload_length"), pmt::from_long(_payload_length));

      if(_develop_mode)
      {
        std::cout << "frame type is: " << _frame_type << std::endl;
        std::cout << "frame index is: " << _frame_index << std::endl;
        std::cout << "destination address is: " << _destination_address << std::endl;
        std::cout << "source address is: " << _source_address << std::endl;
        std::cout << "payload length is: " << _payload_length << std::endl;
      }
      message_port_pub(pmt::mp("tx_frame_info_out"), frame_info);
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
    
    pmt::pmt_t
    framing_cpp_impl::crc32_bb_calc(pmt::pmt_t msg)
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
    framing_cpp_impl::disp_vec(std::vector<unsigned char> vec)
    {
      std::cout << "display unsigned char vector:" << ' ';
      for(int i=0; i<vec.size(); ++i)
        std::cout << vec[i] << ' ';
    }



  } /* namespace inets */
} /* namespace gr */
