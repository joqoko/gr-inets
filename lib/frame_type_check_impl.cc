/* -*- c++ -*- */
/* 
 * Copyright 2016 <INETS>.
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
#include "frame_type_check_impl.h"

namespace gr {
  namespace inets {

    frame_type_check::sptr
    frame_type_check::make(int develop_mode, int block_id, int data_frame, int ack_frame, int beacon_frame, int rts_frame, int cts_frame, int ampdu_frame, int amsdu_frame,int ampdu_subframe, int amsdu_subframe, int other_frame)
    {
      return gnuradio::get_initial_sptr
        (new frame_type_check_impl(develop_mode, block_id, data_frame, ack_frame, beacon_frame, rts_frame, cts_frame, ampdu_frame, amsdu_frame, ampdu_subframe, amsdu_subframe, other_frame));
    }

    /*
     * The private constructor
     */
    frame_type_check_impl::frame_type_check_impl(int develop_mode, int block_id, int data_frame, int ack_frame, int beacon_frame, int rts_frame, int cts_frame, int ampdu_frame, int amsdu_frame, int ampdu_subframe, int amsdu_subframe, int other_frame)
      : gr::block("frame_type_check",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_type check ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_info_in"));
      message_port_register_out(pmt::mp("data_frame_info_out"));
      message_port_register_out(pmt::mp("ack_frame_info_out"));
      message_port_register_out(pmt::mp("beacon_frame_info_out"));
      message_port_register_out(pmt::mp("rts_frame_info_out"));
      message_port_register_out(pmt::mp("cts_frame_info_out"));
      message_port_register_out(pmt::mp("ampdu_frame_info_out"));
      message_port_register_out(pmt::mp("amsdu_frame_info_out"));
      message_port_register_out(pmt::mp("ampdu_subframe_info_out"));
      message_port_register_out(pmt::mp("amsdu_subframe_info_out"));
      message_port_register_out(pmt::mp("other_frame_info_out"));
      set_msg_handler(pmt::mp("frame_info_in"), boost::bind(&frame_type_check_impl::selector, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    frame_type_check_impl::~frame_type_check_impl()
    {
    }

    void
    frame_type_check_impl::selector(pmt::pmt_t info)
    {  
      if(_develop_mode == 2)
      {
        struct timeval t; 
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        std::cout << "at time " << current_time << " s, ";
      }
      if(_develop_mode)
        std::cout << "frame_type_check ID: " << _block_id << " detects ";
      pmt::pmt_t not_found;
      int frame_type = pmt::to_long(pmt::dict_ref(info, pmt::string_to_symbol("frame_type"), not_found));
      // data frame info
      if(frame_type == 1)
      {
        if(_develop_mode)
          std::cout << "a data frame" << std::endl;
        message_port_pub(pmt::mp("data_frame_info_out"), info);
      } 
      else if(frame_type == 2)
      {
        if(_develop_mode)
          std::cout << "an ack frame" << std::endl;
        message_port_pub(pmt::mp("ack_frame_info_out"), info);
      } 
      else if(frame_type == 3)
      {
        if(_develop_mode)
          std::cout << "a beacon frame" << std::endl;
        message_port_pub(pmt::mp("beacon_frame_info_out"), info);
      } 
      else if(frame_type == 4)
      {
        if(_develop_mode)
          std::cout << "a rts frame" << std::endl;
        message_port_pub(pmt::mp("rts_frame_info_out"), info);
      } 
      else if(frame_type == 5)
      {
        if(_develop_mode)
          std::cout << "a cts frame" << std::endl;
        message_port_pub(pmt::mp("cts_frame_info_out"), info);
      } 
      else if(frame_type == 6)
      {
        if(_develop_mode)
          std::cout << "an ampdu frame" << std::endl;
        message_port_pub(pmt::mp("ampdu_frame_info_out"), info);
      } 
      else if(frame_type == 7)
      {
        if(_develop_mode)
          std::cout << "an amsdu frame" << std::endl;
        message_port_pub(pmt::mp("amsdu_frame_info_out"), info);
      } 
      else if(frame_type == 8)
      {
        if(_develop_mode)
          std::cout << "an ampdu subframe" << std::endl;
        message_port_pub(pmt::mp("ampdu_subframe_info_out"), info);
      } 
      else if(frame_type == 9)
      {
        if(_develop_mode)
          std::cout << "an amsdu subframe" << std::endl;
        message_port_pub(pmt::mp("amsdu_subframe_info_out"), info);
      } 
      else
      {
        if(_develop_mode)
          std::cout << "an unknown frame" << std::endl;
        message_port_pub(pmt::mp("other_frame_info_out"), info);
      } 
    }


  } /* namespace inets */
} /* namespace gr */

