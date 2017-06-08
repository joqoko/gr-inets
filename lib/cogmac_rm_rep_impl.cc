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
#include "cogmac_rm_rep_impl.h"

namespace gr {
  namespace inets {

    cogmac_rm_rep::sptr
    cogmac_rm_rep::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new cogmac_rm_rep_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    cogmac_rm_rep_impl::cogmac_rm_rep_impl(int develop_mode, int block_id)
      : gr::block("cogmac_rm_rep",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _last_index(-1)
    {
      if(_develop_mode)
        std::cout << "develop_mode of cogmac_rm_rep ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_cmd_in"));
      set_msg_handler(pmt::mp("frame_cmd_in"), boost::bind(&cogmac_rm_rep_impl::filtering, this, _1 ));
      message_port_register_out(pmt::mp("new_cmd_out"));
      message_port_register_out(pmt::mp("same_cmd_out"));
    }
    /*
     * Our virtual destructor.
     */
    cogmac_rm_rep_impl::~cogmac_rm_rep_impl()
    {
    }

    void
    cogmac_rm_rep_impl::filtering(pmt::pmt_t frame_in)
    {
      pmt::pmt_t not_found;
      if(pmt::dict_has_key(frame_in, pmt::string_to_symbol("frame_index")))
      {
        int index = pmt::to_long(pmt::dict_ref(frame_in, pmt::string_to_symbol("frame_index"), not_found));
        if(_last_index != index)
        {
          message_port_pub(pmt::mp("new_cmd_out"), frame_in);
          if(_develop_mode)
            std::cout << "cogmac_rm_rep ID " << _block_id << " receives frame with new index." << std::endl;
        }
        else
        {
          message_port_pub(pmt::mp("same_cmd_out"), frame_in);
          if(_develop_mode)
            std::cout << "cogmac_rm_rep ID " << _block_id << " receives frame with same index." << std::endl;
        }
        _last_index = index;
      }
      else
        std::cout << "error: cogmac_rm_rep ID " << _block_id << " has no field frame_index in the input cmd. " << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

