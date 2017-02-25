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
#include "frame_index_check_impl.h"

namespace gr {
  namespace inets {

    frame_index_check::sptr
    frame_index_check::make(int develop_mode, int block_id, int difference, int no_wait, int output_fail, int reset_1st, int length_frame_index)
    {
      return gnuradio::get_initial_sptr
        (new frame_index_check_impl(develop_mode, block_id, difference, no_wait, output_fail, reset_1st, length_frame_index));
    }

    /*
     * The private constructor
     */
    frame_index_check_impl::frame_index_check_impl(int develop_mode, int block_id, int difference, int no_wait, int output_fail, int reset_1st, int length_frame_index)
      : gr::block("frame_index_check",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _difference(difference),
        _no_wait(no_wait),
        _output_fail(output_fail),
        _reset_1st(reset_1st),
        _length_frame_index(length_frame_index)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_index_check ID: " << _block_id << " is activated." << std::endl;
      _max_index = 1 << (8 * _length_frame_index);
      _frame_A = pmt::from_long(0);
      _frame_B = pmt::from_long(0);
      message_port_register_in(pmt::mp("frame_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
      set_msg_handler(
        pmt::mp("frame_in"),
        boost::bind(&frame_index_check_impl::start_check, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_index_check_impl::~frame_index_check_impl()
    {
    }

    void
    frame_index_check_impl::start_check(pmt::pmt_t frame)
    {
      pmt::pmt_t not_found;
      if(pmt::is_dict(frame))
      {
        if(_reset_1st)
        {
          int index = pmt::to_long(pmt::dict_ref(frame, pmt::string_to_symbol("frame_index"), not_found));
          if(index == 1)
          {
            _frame_A = pmt::from_long(0);
            _frame_B = pmt::from_long(0);
          }
        }
        if(pmt::is_dict(_frame_A))
        {
          if(_develop_mode)
            std::cout << "two frames are received. execute the comparison." << std::endl;
          _frame_B = frame;
          compare(); 
        } 
        else
        {
          if(_develop_mode)
            std::cout << "one frame is received. wait for another." << std::endl;
          _frame_A = frame;
          if(_no_wait)
            message_port_pub(pmt::mp("frame_info_out"), _frame_A);
        }
      }
      else
        std::cout << "Error: frame_index_check ID: " << _block_id << " received unknown data type for port frame_A_info_in, please check your connections. " << std::endl;
    }

    void
    frame_index_check_impl::compare()
    {
      pmt::pmt_t not_found;
      int frame_A_data = pmt::to_long(pmt::dict_ref(_frame_A, pmt::string_to_symbol("frame_index"), not_found));
      int frame_B_data = pmt::to_long(pmt::dict_ref(_frame_B, pmt::string_to_symbol("frame_index"), not_found));
      std::cout << "frame_A index: " << frame_A_data << "frame B index: " << frame_B_data << std::endl;
      if(((frame_B_data - frame_A_data) == _difference) || ((frame_B_data - frame_A_data) == (1 - _max_index)))
      {
        if(_develop_mode)
          std::cout << "the difference of index of the comming frames is" << _difference << std::endl;
        message_port_pub(pmt::mp("frame_info_out"), _frame_B);
      }
      else
      {
        if(_develop_mode)
          std::cout << "the difference of frame_index between frame A and frame B is not " << _difference << std::endl;
        if(_output_fail)
          message_port_pub(pmt::mp("frame_info_out"), _frame_A);
          
      }
      _frame_A = _frame_B;
      _frame_B = pmt::from_long(0);
    }

  } /* namespace inets */
} /* namespace gr */

