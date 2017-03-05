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
#include "beacon_interpreter_impl.h"

namespace gr {
  namespace inets {

    beacon_interpreter::sptr
    beacon_interpreter::make(int develop_mode, int block_id, int len_address, int len_slot_time_beacon)
    {
      return gnuradio::get_initial_sptr
        (new beacon_interpreter_impl(develop_mode, block_id, len_address, len_slot_time_beacon));
    }

    /*
     * The private constructor
     */
    beacon_interpreter_impl::beacon_interpreter_impl(int develop_mode, int block_id, int len_address, int len_slot_time_beacon)
      : gr::block("beacon_interpreter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _len_address(len_address),
        _len_slot_time_beacon(len_slot_time_beacon)
    {
      if(_develop_mode)
        std::cout << "develop_mode of beacon_interpreter ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("beacon_frame_in"));
      set_msg_handler(pmt::mp("beacon_frame_in"), boost::bind(&beacon_interpreter_impl::interpretation, this, _1 ));
      message_port_register_out(pmt::mp("tx_sequence_out"));
    }

    /*
     * Our virtual destructor.
     */
    beacon_interpreter_impl::~beacon_interpreter_impl()
    {
    }

    void
    beacon_interpreter_impl::interpretation(pmt::pmt_t beacon)
    {
      if(_develop_mode)
      {
        std::cout << "++++++++  beacon_interpreter ID: " << _block_id << "  +++++++" << std::endl;
      }
      pmt::pmt_t not_found;
      int frame_type = pmt::to_long(pmt::dict_ref(beacon, pmt::string_to_symbol("frame_type"), not_found));
      if(frame_type != 3)
        std::cout << "beacon_interpreter ID: " << _block_id << " has wrong input data type. please check your connections. " << std::endl;
      else
      {
        std::vector<unsigned char> payload = pmt::u8vector_elements(pmt::dict_ref(beacon, pmt::string_to_symbol("payload"), not_found));
        if(_develop_mode)
        {
          std::cout << "beacon payload : ";
          disp_vec(payload);
        }
        std::vector<uint32_t> address_array;
        std::vector<uint32_t> slot_time_array;
        if(payload.size() % (_len_address + _len_slot_time_beacon) == 0)
        {
          int n_node = payload.size() / (_len_address + _len_slot_time_beacon);
          pmt::pmt_t tdma_time_info; 
          for(int i = 0; i < n_node; i++)
          {
            tdma_time_info = pmt::make_dict();
            int pos = i * (_len_slot_time_beacon + _len_address);
            std::vector<unsigned char> address_current;
            address_current.insert(address_current.begin(), payload.begin() + pos, payload.begin() + pos + _len_address);
            uint32_t address = BytesToint(address_current);
            address_array.push_back(address);
            std::vector<unsigned char> slot_time_current;
            slot_time_current.insert(slot_time_current.begin(), payload.begin() + pos + _len_address, payload.begin() + pos + _len_address + _len_slot_time_beacon);
            uint32_t slot_time = BytesToint(slot_time_current);
            slot_time_array.push_back(slot_time);
            tdma_time_info = pmt::dict_add(tdma_time_info, pmt::string_to_symbol("destination_address"), pmt::from_long(address));
            tdma_time_info = pmt::dict_add(tdma_time_info, pmt::string_to_symbol("slot_time"), pmt::from_long(slot_time));
            message_port_pub(pmt::mp("tx_sequence_out"), tdma_time_info);
            boost::this_thread::sleep(boost::posix_time::milliseconds(10));
          }  
          if(_develop_mode)
          {
            disp_int_vec(address_array);
            disp_int_vec(slot_time_array);
          }
        }
        else
          std::cout << "beacon_interpreter ID: " << _block_id << " has wrong payload length. please check your connections" << std::endl;
        
      }
    }

    void 
    beacon_interpreter_impl::disp_int_vec(std::vector<uint32_t> vec)
    {
      for(int i=0; i<vec.size(); ++i)
      {
        std::cout << vec[i] << ' ';
      }
      std::cout << "total length is :" << vec.size() << "." << std::endl;
    }

    void 
    beacon_interpreter_impl::disp_vec(std::vector<unsigned char> vec)
    {
      for(int i=0; i<vec.size(); ++i)
        std::cout << static_cast<unsigned>(vec[i]) << ' ';
      std::cout << "total length is :" << vec.size() << " bytes." << std::endl;
    }

    int 
    beacon_interpreter_impl::BytesToint(std::vector<unsigned char> bytes)
    {
      int int_num = 0;
      int size = bytes.size();
      for(int i = 0; i < size; ++i)  
      {
        int_num = static_cast<int>(bytes.back() << ((size - i - 1) * 8)) + int_num;
        bytes.pop_back();
      } 
      return int_num;
    }
    

  } /* namespace inets */
} /* namespace gr */

