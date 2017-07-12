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
#include "frame_index_selector_impl.h"

namespace gr {
  namespace inets {

    frame_index_selector::sptr
    frame_index_selector::make(int develop_mode, int block_id, std::vector<unsigned int> selected_index, int output_unselected)
    {
      return gnuradio::get_initial_sptr
        (new frame_index_selector_impl(develop_mode, block_id, selected_index, output_unselected));
    }

    /*
     * The private constructor
     */
    frame_index_selector_impl::frame_index_selector_impl(int develop_mode, int block_id, std::vector<unsigned int> selected_index, int output_unselected)
      : gr::block("frame_index_selector",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _selected_index(selected_index),
        _output_unselected(output_unselected)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_index_selector ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_in"));
      set_msg_handler(pmt::mp("frame_in"), boost::bind(&frame_index_selector_impl::check_index, this, _1 ));
      message_port_register_in(pmt::mp("reset_index_in"));
      set_msg_handler(pmt::mp("reset_index_in"), boost::bind(&frame_index_selector_impl::reset_index, this, _1 ));
      message_port_register_out(pmt::mp("frame_out"));
      message_port_register_out(pmt::mp("unselected_frame_out"));
    }


    /*
     * Our virtual destructor.
     */
    frame_index_selector_impl::~frame_index_selector_impl()
    {
    }

    void
    frame_index_selector_impl::reset_index(pmt::pmt_t frame_in)
    {
      _selected_index[0] = int(pmt::to_double(frame_in));
    }

    void
    frame_index_selector_impl::check_index(pmt::pmt_t frame_in)
    {
      pmt::pmt_t not_found;
      if(pmt::is_dict(frame_in))
      {
        int index = pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("frame_index"), not_found));
        if(_develop_mode)
          std::cout << "frame_index_selector ID " << _block_id << " receives the " << index << "th frame. ";
	bool selected = false;
        for(int i = 0; i < _selected_index.size(); i++)
        {
          selected = (_selected_index[i] == index);
	  if(selected)
            break;
        }
	if(selected)
        {
          if(_develop_mode)
            std::cout << " it is selected. frame will output from frame_out port" << std::endl;
          message_port_pub(pmt::mp("frame_out"), frame_in);
        }
        else
        {
          if(_develop_mode)
          {
            std::cout << " it is not selected. ";
            if(!_output_unselected)
              std::cout << " frame output from unselected_frame_out port. " << std::endl;
	  }
          if(!_output_unselected)
            message_port_pub(pmt::mp("unselected_frame_out"), frame_in);
        }
      }
      else
        std::cout << "error: frame_index_selector ID " << _block_id << " receives wrong frame type. please check your implementations" << std::endl;
      
    }

  } /* namespace inets */
} /* namespace gr */

