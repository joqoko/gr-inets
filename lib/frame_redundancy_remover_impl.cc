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
#include "frame_redundancy_remover_impl.h"

namespace gr {
  namespace inets {

    frame_redundancy_remover::sptr
    frame_redundancy_remover::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new frame_redundancy_remover_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    frame_redundancy_remover_impl::frame_redundancy_remover_impl(int develop_mode, int block_id)
      : gr::block("frame_redundancy_remover",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _last_index(0)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_redundancy_remover ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("cmd_in"));
      message_port_register_out(pmt::mp("cmd_out"));
      message_port_register_out(pmt::mp("redundancy_out"));
      set_msg_handler(pmt::mp("cmd_in"), boost::bind(&frame_redundancy_remover_impl::check_redundancy, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    frame_redundancy_remover_impl::~frame_redundancy_remover_impl()
    {
    }

    void
    frame_redundancy_remover_impl::check_redundancy(pmt::pmt_t cmd_in)
    {
      pmt::pmt_t not_found;
      if(pmt::dict_has_key(cmd_in, pmt::string_to_symbol("frame_index")))
      {
        int index = pmt::to_long(pmt::dict_ref(cmd_in, pmt::string_to_symbol("frame_index"), not_found));
        if(_last_index != index)
        {
          if(_develop_mode)
            std::cout << "new frame arrives at frame_redundancy_remover ID " << _block_id << ". It is exported." << std::endl;
          message_port_pub(pmt::mp("cmd_out"), cmd_in);
        }
        else
        {
          if(_develop_mode)
            std::cout << "same frame arrives at frame_redundancy_remover ID " << _block_id << ". It isdisgarded." << std::endl;
          message_port_pub(pmt::mp("redundancy_out"), cmd_in);
        }
        _last_index = index;
      }
      else
        std::cout << "error frame_redundancy_remover ID " << _block_id << " has unkown input cmd." << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

