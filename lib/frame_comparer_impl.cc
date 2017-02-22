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
    frame_comparer::make(int develop_mode, int block_id, int what_to_compare)
    {
      return gnuradio::get_initial_sptr
        (new frame_comparer_impl(develop_mode, block_id, what_to_compare));
    }

    /*
     * The private constructor
     */
    frame_comparer_impl::frame_comparer_impl(int develop_mode, int block_id, int what_to_compare)
      : gr::block("frame_comparer",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _what_to_compare(what_to_compare)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_comparer ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_one_info_in"));
      message_port_register_in(pmt::mp("frame_two_info_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
      set_msg_handler(
        pmt::mp("frame_one_info_in"),
        boost::bind(&timeout_impl::start_compare, this, _1)
      );
      set_msg_handler(
        pmt::mp("frame_two_info_in"),
        boost::bind(&timeout_impl::do_compare, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_comparer_impl::~frame_comparer_impl()
    {
    }

    void
    frame_comparer_impl::start_compare(pmt::pmt_t frame_one)
    {
      if(pmt::is_dict(frame_one))
        _frame_one = frame_one;
      else
        std::cout << "Error: frame_comparer ID: " << _block_id << " received unknown data type for port frame_one_info_in, please check your connections. " << std::endl;
    }

    void
    frame_comparer_impl::do_compare(pmt::pmt_t frame_two)
    {
      // frame_two should be a valid frame
      if(pmt::is_dict(frame_two))
      {
        // presaved frame_one should be a valid frame also
        if(pmt::is_dict(_frame_one))
        {
          
          switch(_drop_type)
          {
            // case 0: frame_index
            case 0 :  
              {
                if(pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("frame_index"), not_found)) != _frame_index)
                {
                  message_port_pub(pmt::mp("frame_info_out"), frame_in);
                }
                else
                {
                  if(_develop_mode)
                  std::cout << "successfully filtered one targeted frame." << std::endl;
                  _number_of_filtering--;
                  message_port_pub(pmt::mp("filtered_frame_info_out"), frame_in);
                }
                break;
              }
            default:
              {
                if(_develop_mode)
                  std::cout << "No frame is filtered. " << std::endl;
                message_port_pub(pmt::mp("frame_info_out"), frame_in);
              }
          }
        }
        else
          std::cout << "Error: frame_comparer ID: " << _block_id << " is not initialized, please check your connections. " << std::endl;
      }
      else
        std::cout << "Error: frame_comparer ID: " << _block_id << " received unknown data type for port frame_one_info_in, please check your connections. " << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

