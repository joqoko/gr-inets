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
#include "frame_comparer_impl.h"

namespace gr {
  namespace inets {

    frame_comparer::sptr
    frame_comparer::make(int develop_mode, int block_id, int what_to_compare, int single_input)
    {
      return gnuradio::get_initial_sptr
        (new frame_comparer_impl(develop_mode, block_id, what_to_compare, single_input));
    }

    /*
     * The private constructor
     */
    frame_comparer_impl::frame_comparer_impl(int develop_mode, int block_id, int what_to_compare, int single_input)
      : gr::block("frame_comparer",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _what_to_compare(what_to_compare),
        _single_input(_single_input)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_comparer ID: " << _block_id << " is activated." << std::endl;
      _frame_A = pmt::from_long(0);
      _frame_B = pmt::from_long(0);
      message_port_register_in(pmt::mp("frame_A_in"));
      message_port_register_in(pmt::mp("frame_B_in"));
      message_port_register_out(pmt::mp("higher_indexed_frame"));
      message_port_register_out(pmt::mp("lower_indexed_frame"));
      message_port_register_out(pmt::mp("same_indexed_frame"));
      message_port_register_out(pmt::mp("higher_reI_frame"));
      message_port_register_out(pmt::mp("lower_reI_frame"));
      message_port_register_out(pmt::mp("same_reI_frame"));
      message_port_register_out(pmt::mp("higher_reII_frame"));
      message_port_register_out(pmt::mp("lower_reII_frame"));
      message_port_register_out(pmt::mp("same_reII_frame"));
      set_msg_handler(
        pmt::mp("frame_A_in"),
        boost::bind(&frame_comparer_impl::start_compare_A, this, _1)
      );
      set_msg_handler(
        pmt::mp("frame_B_in"),
        boost::bind(&frame_comparer_impl::start_compare_B, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_comparer_impl::~frame_comparer_impl()
    {
    }

    void
    frame_comparer_impl::start_compare_B(pmt::pmt_t frame_B)
    {
      if(pmt::is_dict(frame_B))
      {
        _frame_B = frame_B;
        if(pmt::is_dict(_frame_A))
          compare();
      }
      else
        std::cout << "Error: frame_comparer ID: " << _block_id << " received unknown data type for port frame_A_info_in, please check your connections. " << std::endl;
    }

    void
    frame_comparer_impl::start_compare_A(pmt::pmt_t frame_A)
    {
      // _single_input true means two port are activated.
      if(_single_input)
      {
        if(pmt::is_dict(frame_A))
        {
          _frame_A = frame_A;
          if(pmt::is_dict(_frame_B))
          {
            compare();
          }
        }
        else
          std::cout << "error: frame_comparer id: " << _block_id << " received unknown data type for port frame_a_info_in, please check your connections. " << std::endl;
      }
      else
      {
        if(pmt::is_dict(frame_A))
        {
          if(pmt::is_dict(_frame_A))
          {
            if(_develop_mode)
              std::cout << "two frames are received. execute the comparison." << std::endl;
            _frame_B = frame_A;
            compare(); 
          } 
          else
          {
            if(_develop_mode)
              std::cout << "one frame is received. wait for another." << std::endl;
            _frame_A = frame_A;
          }
        }
        else
          std::cout << "Error: frame_comparer ID: " << _block_id << " received unknown data type for port frame_A_info_in, please check your connections. " << std::endl;
      }
    }

    void
    frame_comparer_impl::compare()
    {
      pmt::pmt_t not_found;
      if(_develop_mode)
        std::cout << "frame_comparer ID: " << _block_id << " compares the ";
      switch(_what_to_compare)
      {
        // case 0: frame_index
        case 0 :  
          {
            int frame_A_data = pmt::to_long(pmt::dict_ref(_frame_A, pmt::string_to_symbol("frame_index"), not_found));
            int frame_B_data = pmt::to_long(pmt::dict_ref(_frame_B, pmt::string_to_symbol("frame_index"), not_found));
            if(_develop_mode)
              std::cout << "frame index" << std::endl;
            if(frame_A_data > frame_B_data)
            {
              if(_develop_mode)
                std::cout << "index of frame A is lower than frame B" << std::endl;
              message_port_pub(pmt::mp("higher_indexed_frame"), _frame_B);
              message_port_pub(pmt::mp("lower_indexed_frame"), _frame_A);
            }
            else if(frame_A_data < frame_B_data)
            {
              if(_develop_mode)
                std::cout << "index of frame B is lower than frame A" << std::endl;
              message_port_pub(pmt::mp("higher_indexed_frame"), _frame_A);
              message_port_pub(pmt::mp("lower_indexed_frame"), _frame_B);
            }
            else
            {
              message_port_pub(pmt::mp("same_indexed_frame"), _frame_A);
              if(_develop_mode)
                std::cout << "index of both frames are same" << std::endl;
            }
            break;
          }
        // case 1: reserved_field_I 
        case 1 :  
          {
            int frame_A_data = pmt::to_long(pmt::dict_ref(_frame_A, pmt::string_to_symbol("reserved_field_I"), not_found));
            int frame_B_data = pmt::to_long(pmt::dict_ref(_frame_B, pmt::string_to_symbol("reserved_field_I"), not_found));
            if(_develop_mode)
              std::cout << "reserved_field_I" << std::endl;
            if(frame_A_data > frame_B_data)
            {
              if(_develop_mode)
                std::cout << "reserved field I of frame A is smaller than frame B" << std::endl;
              message_port_pub(pmt::mp("higher_reI_frame"), _frame_B);
              message_port_pub(pmt::mp("lower_reI_frame"), _frame_A);
            }
            else if(frame_A_data < frame_B_data)
            {
              if(_develop_mode)
                std::cout << "reserved field_I of frame B is smaller than frame A" << std::endl;
              message_port_pub(pmt::mp("higher_reI_frame"), _frame_A);
              message_port_pub(pmt::mp("lower_reI_frame"), _frame_B);
            }
            else
            {
              message_port_pub(pmt::mp("same_reI_frame"), _frame_A);
              if(_develop_mode)
                std::cout << "reserved field I of both frames are same" << std::endl;
            }
            break;
          }
        // case 2: reserved_field_II
        case 2 :  
          {
            int frame_A_data = pmt::to_long(pmt::dict_ref(_frame_A, pmt::string_to_symbol("reserved_field_II"), not_found));
            int frame_B_data = pmt::to_long(pmt::dict_ref(_frame_B, pmt::string_to_symbol("reserved_field_II"), not_found));
            if(_develop_mode)
              std::cout << "reserved_field_II" << std::endl;
            if(frame_A_data > frame_B_data)
            {
              if(_develop_mode)
                std::cout << "reserved field II of frame A is smaller than frame B" << std::endl;
              message_port_pub(pmt::mp("higher_reII_frame"), _frame_B);
              message_port_pub(pmt::mp("lower_reII_frame"), _frame_A);
            }
            else if(frame_A_data < frame_B_data)
            {
              if(_develop_mode)
                std::cout << "reserved field_II of frame B is smaller than frame A" << std::endl;
              message_port_pub(pmt::mp("higher_reII_frame"), _frame_A);
              message_port_pub(pmt::mp("lower_reII_frame"), _frame_B);
            }
            else
            {
              message_port_pub(pmt::mp("same_reII_frame"), _frame_A);
              if(_develop_mode)
                std::cout << "reserved field II of both frames are same" << std::endl;
            }
            break;
          }
        default:
          {
            if(_develop_mode)
              std::cout << "No frame is filtered. " << std::endl;
          }
      }
      if(_single_input)
      {
        _frame_A = pmt::from_long(0);
        _frame_B = pmt::from_long(0);
      }
      else
      {
        _frame_A = _frame_B;
        _frame_B = pmt::from_long(0);
      }
    }

  } /* namespace inets */
} /* namespace gr */

