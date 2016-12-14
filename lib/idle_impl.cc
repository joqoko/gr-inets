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
#include "idle_impl.h"
#include <queue>
#include <gnuradio/digital/crc32.h> 
#include <volk/volk.h>
#include <boost/crc.hpp>

namespace gr {
  namespace inets {

    idle::sptr
    idle::make(std::vector<int> develop_mode_list, float experiment_duration_s, int max_num_retransmission, int max_buffer_size, int frame_type, int len_frame_type, int frame_index, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int increase_index, int len_num_transmission)
    {
      return gnuradio::get_initial_sptr
        (new idle_impl(develop_mode_list, experiment_duration_s, max_num_retransmission, max_buffer_size, frame_type, len_frame_type, frame_index, len_frame_index, destination_address, len_destination_address, source_address, len_source_address, reserved_field_I, len_reserved_field_I, reserved_field_II, len_reserved_field_II, len_payload_length, increase_index, len_num_transmission));
    }

    /*
     * The private constructor
     */
    idle_impl::idle_impl(std::vector<int> develop_mode_list, float experiment_duration_s, int max_num_retransmission, int max_buffer_size, int frame_type, int len_frame_type, int frame_index, int len_frame_index, int destination_address, int len_destination_address, int source_address, int len_source_address, int reserved_field_I, int len_reserved_field_I, int reserved_field_II, int len_reserved_field_II, int len_payload_length, int increase_index, int len_num_transmission)
      : gr::block("idle",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode_list(develop_mode_list),
        _my_develop_mode(1),
        _experiment_duration_s(experiment_duration_s),
        _max_buffer_size(max_buffer_size),
        _experiment_running(true),
        _in_idle(true),
        _len_frame_type(len_frame_type), // Bytes
        _frame_index(frame_index),
        _len_frame_index(len_frame_index), // Bytes
        _destination_address(destination_address),
        _len_destination_address(len_destination_address), // Bytes
        _source_address(source_address), 
        _len_source_address(len_source_address), // Bytes
        _len_num_transmission(len_num_transmission),
        _reserved_field_I(reserved_field_I), 
        _len_reserved_field_I(len_reserved_field_I), // Bytes
        _reserved_field_II(reserved_field_II),
        _len_reserved_field_II(len_reserved_field_II), // Bytes
        _len_payload_length(len_payload_length), // Bytes
        _frame_type(frame_type),
        _increase_index(increase_index),
        _max_num_retransmission(max_num_retransmission)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of idle is activated." << std::endl;
      message_port_register_in(pmt::mp("data_in"));
      message_port_register_in(pmt::mp("reset_idle"));
      message_port_register_out(pmt::mp("data_out"));
      message_port_register_out(pmt::mp("successful_transmission"));
      set_msg_handler(pmt::mp("data_in"), boost::bind(&idle_impl::state_transition, this, _1 ));
      set_msg_handler(pmt::mp("reset_idle"), boost::bind(&idle_impl::reset_idle, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    idle_impl::~idle_impl()
    {
    }


    void 
    idle_impl::send_data_frame_to_send_frame()
    {
      pmt::pmt_t not_found;
      _sending_data_frame = _tx_buff.front();
      message_port_pub(pmt::mp("data_out"), _sending_data_frame);
      _tx_buff.pop();

      struct timeval t; 
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
      std::cout << "idle node " << _source_address << " at time " << current_time << std::endl;

      _in_idle = false;
      if(_develop_mode)
        std::cout << "send the " << pmt::dict_ref(_sending_data_frame, pmt::string_to_symbol("frame_index"), not_found) << "th frame to send_frame. " << _tx_buff.size() << " frames in buffer." << std::endl;
    }

    void
    idle_impl::reset_idle(pmt::pmt_t data)
    {
      if(pmt::to_bool(data))
      {
        _in_idle = true;
        if(_develop_mode)
          std::cout << "reset idle at node " << _source_address << " to true." << std::endl;
        if(_tx_buff.size())
        {
          send_data_frame_to_send_frame();
        }
      }
      else
        std::cout << "Warning: you cannot use false to reset idle to true." << std::endl;
    }

    void
    idle_impl::state_transition(pmt::pmt_t data)
    {
      if(_develop_mode)
      {
        std::cout << "++++++++++++ node " << _source_address << " - idle  +++++++++++++++++" << std::endl;
      }
      /*
       * get frame payload 
       */
      pmt::pmt_t meta = pmt::car(data);
      pmt::pmt_t data_pmt = pmt::cdr(data);
      // early debugging code -> std::cout << "Test pair, dict and u8vector. is pair" << pmt::is_pair(data) << "is dict:" << pmt::is_dict(data)  << "is u8:" << pmt::is_u8vector(data_pmt) << "dict has key: " << pmt::dict_has_key(data, pmt::string_to_symbol("frame_type")) << std::endl;
      if(pmt::is_u8vector(data_pmt))
      {
        // we first check whether the queue is full. if we enqueue the data frame, we need to check the _in_idle state. If true, then we transmission the frame and set _in_idle to false.
        if(_develop_mode)
          std::cout << "payload comes. " << std::endl;
        if(_tx_buff.size() < _max_buffer_size)
        {
          pmt::pmt_t data_frame = data_frame_framing(data);
          _tx_buff.push(data_frame);
          if(_in_idle)
          {
            idle_impl::send_data_frame_to_send_frame();
          }
          else
            if(_develop_mode)
              std::cout << "payload comes but not in idle. there are " << _tx_buff.size() << " frames in the tx buffer."<< std::endl;
        }
        else
          if(_develop_mode)
            std::cout << "payload comes. However the tx buffer is full, discard the payload." << std::endl;
      }
      /*
       * get a frame info 
       */
      else if(pmt::dict_has_key(data, pmt::string_to_symbol("frame_type")))
      {
        if(_develop_mode)
          std::cout << "get a frame info dict." << std::endl;
        pmt::pmt_t not_found;
        int frame_type = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("frame_type"), not_found));
        int destination_address = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("destination_address"), not_found));
        int src_address = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("source_address"), not_found));
        // if the frame is sent by me
        if(src_address == _source_address)
        {
          // if I sent an ACK frame. QUESTION MARK HERE. I should not get the ack information which is sent by me. So do nothing here.
          if(frame_type == 2) 
          {
            std::cout << "Warning: get frame info of an ack sent by me. please check your connection." << std::endl;
            // activate _in_idle state
          //  if(_develop_mode)
          //    std::cout << "get info of the ACK sent by me, state to idle." << std::endl;
         //   _in_idle = true;
         //   if(_tx_buff.size())
         //   {
        //      send_data_frame_to_send_frame();
         //   }
          }
          // if the data frame is sent by me
          else if(frame_type == 1)
          {
            // check the number of transmission. If maximum retransmission reached, then reset idle and check the buffer. Otherwise simply forward the frame info to transmission frame and there the transmission will be add one.
            int num_transmission = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("num_transmission"), not_found));
            if(_develop_mode)
              std::cout << "get info of the data frame sent by me, number of retransmission is: " << num_transmission << std::endl;
            if(num_transmission >= _max_num_retransmission)
            {
              if(_develop_mode)
                std::cout << "maximum retransmission reached. reset _in_idle." << std::endl;
              _in_idle = true;
              if(_tx_buff.size())
              {
                send_data_frame_to_send_frame();
              }
            }
            // 
            else
            {
              num_transmission++;
              if(_develop_mode)
                std::cout << "transmission the data frame. current number of transmission is: " << num_transmission << std::endl;
              _sending_data_frame = pmt::dict_delete(_sending_data_frame, pmt::string_to_symbol("num_transmission"));
              _sending_data_frame = pmt::dict_add(_sending_data_frame, pmt::string_to_symbol("num_transmission"), pmt::from_long(num_transmission));
              message_port_pub(pmt::mp("data_out"), _sending_data_frame);
            }
          }     
          else
            std::cout << "Warning: unknown frame_type. Please check your connections." << std::endl;
        }    
        // if the frame is not sent by me
        else
        {
          // if I am the destined node
          if(destination_address == _source_address)
          {
            // if it is an ACK frame. Note that we need to compare the frame index to the frame index of the last send data frame. 
            if(frame_type == 2)
            {
              //int frame_index = pmt::to_long(pmt::dict_ref(data, pmt::string_to_symbol("frame_index"), not_found));
             // if(frame_index == _last_frame_index)
              //{ 
                _in_idle = true;
                message_port_pub(pmt::mp("successful_transmission"), pmt::from_bool(true));
                if(_develop_mode)
                  std::cout << "successfully sent one frame. back to idle. next one!" << std::endl;
                if(_tx_buff.size())
                {
                  send_data_frame_to_send_frame();
                }
              //}
             // else
             //     std::cout << "Received an ack of the " << frame_index << "th frame, but we are expecting the ack of the " << _last_frame_index << "th frame. please check your setup." << std::endl;
            }
            // if it is a data frame, we need to set idle state to false and transmission ack back.
            else if(frame_type == 1)
            {
              if(_develop_mode)
                std::cout << "received a data frame. let the transmissioner know now!" << std::endl;
              _in_idle = false;
              pmt::pmt_t ack_frame = ack_frame_framing(data);
              message_port_pub(pmt::mp("data_out"), ack_frame);
            }
            else
              std::cout << "Warning: unknown frame_type. Please check your connections." << std::endl;
          }
          else
            std::cout << "Both source and destination address are not me. whos frame?" << std::endl;
        }
      }
      else 
        std::cout << "Warning: unknown message type. Please check your connection." << std::endl;
    }

    pmt::pmt_t
    idle_impl::data_frame_framing(pmt::pmt_t rx_payload)
    {
      if(_develop_mode)
      {
        std::cout << "       +++++  data_frame framing  +++++      " << std::endl;
      }
      /*
       * Generate a data frame
       */
      pmt::pmt_t frame_info;
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
          if(_increase_index)
            _frame_index++;
          frame_info = frame_header_formation(&frame_header, 1, _frame_index, _destination_address, _source_address, _reserved_field_I, _reserved_field_II, _payload_length);
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
          frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_pmt"), frame_after_crc);
          std::vector<unsigned char> frame_after_crc_vector = pmt::u8vector_elements(pmt::cdr(frame_after_crc));
          if(_develop_mode)
            std::cout << "frame header with payload with crc, length " << frame_after_crc_vector.size() << std::endl;
        }
        else
          std::cout << "pmt is not a u8vector" << std::endl;
      }
      else 
        std::cout << "pmt is not a pair" << std::endl;
      return frame_info;
    }

    pmt::pmt_t
    idle_impl::ack_frame_framing(pmt::pmt_t rx_payload)
    {
      if(_develop_mode)
      {
        std::cout << "       +++++  ack_frame framing  +++++      " << std::endl;
      }
      /*
       * Generate an ack frame
       */
      pmt::pmt_t frame_info;
      if(pmt::is_dict(rx_payload))
      {
        pmt::pmt_t meta = pmt::make_dict();
        pmt::pmt_t not_found;
        // generate an ack frame
        int ack_address = pmt::to_long(pmt::dict_ref(rx_payload, pmt::string_to_symbol("source_address"), not_found));
        //int src_address = pmt::to_long(pmt::dict_ref(rx_payload, pmt::string_to_symbol("destination_address"), not_found));
        int ack_index = pmt::to_long(pmt::dict_ref(rx_payload, pmt::string_to_symbol("frame_index"), not_found));
        std::vector<unsigned char> frame_header;
        frame_info = frame_header_formation(&frame_header, 2, ack_index, ack_address, _source_address, _reserved_field_I, _reserved_field_II, 0);
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
        frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_pmt"), frame_after_crc);
        std::vector<unsigned char> frame_after_crc_vector = pmt::u8vector_elements(pmt::cdr(frame_after_crc));
        if(_develop_mode)
          std::cout << "ack frame with crc (no payload), length " << frame_after_crc_vector.size() << std::endl;
      }
      else 
        std::cout << "Error: pmt is not a dict, cannot generate an ack frame. please check your connections." << std::endl;
      return frame_info;
    }

    pmt::pmt_t
    idle_impl::frame_header_formation(std::vector<unsigned char> *frame_header, int frame_type, int frame_index, int destination_address, int source_address, int reserved_field_I, int reserved_field_II, int payload_length)
    {
      std::vector< unsigned char > vec_frame_header;
      std::vector< unsigned char > vec_frame_type;
      std::vector< unsigned char > vec_frame_index;
      std::vector< unsigned char > vec_destination_address;
      std::vector< unsigned char > vec_source_address;
      std::vector< unsigned char > vec_transmission;
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
      intToByte(frame_type, &vec_frame_type, _len_frame_type);
      // Frame index
      intToByte(frame_index, &vec_frame_index, _len_frame_index);
      // Destination address
      intToByte(destination_address, &vec_destination_address, _len_destination_address);
      // Payload length
      intToByte(payload_length, &vec_payload_length, _len_payload_length);
      // Source address
      intToByte(source_address, &vec_source_address, _len_source_address);
      // num_Retransmission 
      intToByte(0, &vec_transmission, _len_num_transmission);
      // Reserved field I
      intToByte(reserved_field_I, &vec_reserved_field_I, _len_reserved_field_I);
      // Reserved field II
      intToByte(reserved_field_II, &vec_reserved_field_II, _len_reserved_field_II);

      //std::cout  << "Frame header length before frame type: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_frame_type.begin(), vec_frame_type.begin() + _len_frame_type);
      //std::cout  << "Frame header length after frame type: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_frame_index.begin(), vec_frame_index.begin() + _len_frame_index);
      //std::cout  << "Frame header length after frame index: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_destination_address.begin(), vec_destination_address.begin() + _len_destination_address);
      //std::cout  << "Frame header length after dest: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_source_address.begin(), vec_source_address.begin() + _len_source_address);
      //std::cout  << "Frame header length after src: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_transmission.begin(), vec_transmission.begin() + _len_num_transmission);
      //std::cout  << "Frame header length after transmission: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_reserved_field_I.begin(), vec_reserved_field_I.begin() + _len_reserved_field_I);
      //std::cout  << "Frame header length after re1: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_reserved_field_II.begin(), vec_reserved_field_II.begin() + _len_reserved_field_II);
      //std::cout  << "Frame header length after re2: " << frame_header->size() << std::endl;
      frame_header->insert(frame_header->end(), vec_payload_length.begin(), vec_payload_length.begin() + _len_payload_length);

      pmt::pmt_t frame_info  = pmt::make_dict();
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_type"), pmt::from_long(frame_type));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("frame_index"), pmt::from_long(frame_index));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("destination_address"), pmt::from_long(destination_address));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("source_address"), pmt::from_long(source_address));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("num_transmission"), pmt::from_long(0));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("reserved_field_I"), pmt::from_long(reserved_field_I));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("reserved_field_II"), pmt::from_long(reserved_field_II));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("payload_length"), pmt::from_long(payload_length));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("header_length"), pmt::from_long(get_frame_header_length()));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("address_check"),pmt::from_long(0));
      frame_info  = pmt::dict_add(frame_info, pmt::string_to_symbol("good_frame"),pmt::from_long(0));
      return frame_info;
    }

    void 
    idle_impl::intToByte(int i, std::vector<unsigned char> *bytes, int size)
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
    idle_impl::crc32_bb_calc(pmt::pmt_t msg)
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

    int
    idle_impl::get_frame_header_length()
    {
      return _len_frame_type + _len_frame_index + _len_destination_address + _len_source_address + _len_num_transmission + _len_reserved_field_I + _len_reserved_field_II + _len_payload_length;
    } 
  } /* namespace inets */
} /* namespace gr */

