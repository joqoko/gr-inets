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
#include "frame_probe_impl.h"

namespace gr {
  namespace inets {

    frame_probe::sptr
    frame_probe::make(int develop_mode, int block_id, int print_frame)
    {
      return gnuradio::get_initial_sptr
        (new frame_probe_impl(develop_mode, block_id, print_frame));
    }

    /*
     * The private constructor
     */
    frame_probe_impl::frame_probe_impl(int develop_mode, int block_id, int print_frame)
      : gr::block("frame_probe",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
	_print_frame(print_frame)
    {
      message_port_register_in(pmt::mp("info_in"));
      set_msg_handler(
        pmt::mp("info_in"),
        boost::bind(&frame_probe_impl::read_info, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_probe_impl::~frame_probe_impl()
    {
    }

    void
    frame_probe_impl::read_info(pmt::pmt_t frame_info)
    { 
      pmt::pmt_t not_found;
      int find_frame = 0;
      std::cout << "+++++++++ frame_probe ID: " << _block_id << " +++++++++" << std::endl;    
      int frame_type = 0;
      if(pmt::is_dict(frame_info))
      {
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_type")))
	{
          frame_type = pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_type"), not_found));
          if(frame_type == 1)
            std::cout << "data frame detected -- ";
          else if(frame_type == 2)
            std::cout << "ack frame detected -- ";
          else if(frame_type == 3)
            std::cout << "beacon frame detected -- ";
          else if(frame_type == 4)
            std::cout << "rts frame detected -- ";
          else if(frame_type == 5)
            std::cout << "cts frame detected -- ";
          else if(frame_type == 6)
            std::cout << "ampdu frame detected -- ";
          else if(frame_type == 7)
            std::cout << "amsdu frame detected -- ";
          else if(frame_type == 8)
            std::cout << "ampdu subframe detected -- ";
          else if(frame_type == 9)
            std::cout << "amsdu subframe detected -- ";
          else
            std::cout << "Unknown frame type" << std::endl;
	  // show detail of DATA, ACK, BEACON, RTS, CTS
	  if(frame_type <= 5 && frame_type > 0)
          {
            find_frame = 1;
            show_detail(frame_info);
          }
	  else if(frame_type == 6)
	  { 
            find_frame = 1;
	    show_detail(frame_info);
	  }
	  else if(frame_type == 8)
	  { 
            find_frame = 1;
	    show_detail(frame_info);
	  }
	}

        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("slot_time")))
	{
          find_frame = 1;
          std::cout << "tdma scheduling info detected. " << std::endl;
          if(!pmt::is_integer(pmt::dict_ref(frame_info, pmt::string_to_symbol("destination_address"), not_found)))
          {
            std::vector<uint32_t> node_id_list = pmt::u32vector_elements(pmt::dict_ref(frame_info, pmt::string_to_symbol("node_id"), not_found)); 
            std::vector<uint32_t> slot_time_list = pmt::u32vector_elements(pmt::dict_ref(frame_info, pmt::string_to_symbol("slot_time"), not_found)); 
            for(int i = 0; i < node_id_list.size(); i++)
            {
              std::cout << "time slot of node " << node_id_list[i] << " is " << slot_time_list[i] << " [ms]" << std::endl;
            }
          }
          else
          {
            int node_id = pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("destination_address"), not_found)); 
            double slot_time = pmt::to_double(pmt::dict_ref(frame_info, pmt::string_to_symbol("slot_time"), not_found)); 
            std::cout << "time slot of node " << node_id << " is " << slot_time << " [ms]" << std::endl;
          }
        }
	// show detail of ampdu subframe from the transmitter side
	if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("mpdu_info")))
	{
          find_frame = 1;
          pmt::pmt_t mpdu_info = pmt::dict_ref(frame_info, pmt::string_to_symbol("mpdu_info"), not_found);
          show_detail(mpdu_info);
          if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("subframe_pmt")))
          {
            pmt::pmt_t subframe_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("subframe_pmt"), not_found);
            std::vector<unsigned char> frame_array = pmt::u8vector_elements(pmt::cdr(subframe_pmt));
            std::cout << "subframe info contains a subframe with length " << frame_array.size() << " bytes: ";
            if(_print_frame) 
              disp_vec(frame_array);
	  }
	}
        // pure number
	if(pmt::is_integer(frame_info))
	{
          std::cout << " input pmt is: " << pmt::to_long(frame_info) << std::endl;
          find_frame = 1;
        }
	// show pure vector pmt
	if(pmt::is_u8vector(pmt::cdr(frame_info)))
	{
          find_frame = 1;
          std::vector<unsigned char> array = pmt::u8vector_elements(pmt::cdr(frame_info));
          std::cout << "Input mac frame has length: " << array.size() << std::endl;
          if(_print_frame) 
            disp_vec(array);
	}  
        if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("time_stamp")))
	{
          find_frame = 1;
          double time = pmt::to_double(pmt::dict_ref(frame_info, pmt::string_to_symbol("time_stamp"), not_found));
          std::cout << "input time_stamp is: " << time - double(int(time/100)*100);
        }
	if(find_frame == 0)
          std::cout << "Error. Unknow frame type. Please check your connections." << std::endl;
	std::cout << std::endl;
      }
      else
        std::cout << "Error. Input is not a frame_info structure. Please check your connections." << std::endl;
    }
  
    void
    frame_probe_impl::show_detail(pmt::pmt_t frame_info)
    {
      pmt::pmt_t not_found;
      pmt::pmt_t frame_pmt;
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_index")))
        std::cout << "frame index is:            " << pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_index"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("destination_address")))
        std::cout << "destination address is:    " << pmt::dict_ref(frame_info, pmt::string_to_symbol("destination_address"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("source_address")))
        std::cout << "source address is:         " << pmt::dict_ref(frame_info, pmt::string_to_symbol("source_address"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("num_transmission")))
        std::cout << "number of transmission is: " << pmt::dict_ref(frame_info, pmt::string_to_symbol("num_transmission"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("reserved_field_I")))
        std::cout << "reserved field I is:       " << pmt::dict_ref(frame_info, pmt::string_to_symbol("reserved_field_I"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("reserved_field_II")))
        std::cout << "reserved field II is:      " << pmt::dict_ref(frame_info, pmt::string_to_symbol("reserved_field_II"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("payload_length")))
        std::cout << "payload length is:           " << pmt::dict_ref(frame_info, pmt::string_to_symbol("payload_length"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("header_length")))
        std::cout << "header length is:          " << pmt::dict_ref(frame_info, pmt::string_to_symbol("header_length"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("address_check")))
        std::cout << "address check is:          " << pmt::dict_ref(frame_info, pmt::string_to_symbol("address_check"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("good_frame")))
        std::cout << "good frame is:             " << pmt::dict_ref(frame_info, pmt::string_to_symbol("good_frame"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("analysis_time")))
        std::cout << "analysis time is:             " << pmt::dict_ref(frame_info, pmt::string_to_symbol("analysis_time"), not_found) << ";    ";
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_pmt")))
        frame_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_pmt"), not_found);
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("subframe_pmt")))
        frame_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("subframe_pmt"), not_found);
      if(pmt::dict_has_key(frame_info, pmt::string_to_symbol("ampdu_frame_pmt")))
        frame_pmt = pmt::dict_ref(frame_info, pmt::string_to_symbol("ampdu_frame_pmt"), not_found);
      if((pmt::dict_has_key(frame_info, pmt::string_to_symbol("frame_pmt"))) || (pmt::dict_has_key(frame_info, pmt::string_to_symbol("subframe_pmt"))) || (pmt::dict_has_key(frame_info, pmt::string_to_symbol("ampdu_frame_pmt"))))
      {
        std::vector<unsigned char> frame_array = pmt::u8vector_elements(pmt::cdr(frame_pmt));
        std::cout << "frame info contains a frame with length " << frame_array.size() << " bytes: ";
        if(_print_frame) 
          disp_vec(frame_array);
      }
    }

    void 
    frame_probe_impl::disp_int_vec(std::vector<uint32_t> vec)
    {
      for(int i=0; i<vec.size(); ++i)
      {
        std::cout << vec[i] << ' ';
      }
      std::cout << ". total length is :" << vec.size() << "." << std::endl;
    }
 
    void 
    frame_probe_impl::disp_vec(std::vector<unsigned char> vec)
    {
      for(int i=0; i<vec.size(); ++i)
        std::cout << static_cast<unsigned>(vec[i]) << ' ';
      std::cout << ". total length is: " << vec.size() << std::endl;
    }
  } /* namespace inets */
} /* namespace gr */

