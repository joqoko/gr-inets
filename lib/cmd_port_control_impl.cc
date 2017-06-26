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
#include "cmd_port_control_impl.h"

namespace gr {
  namespace inets {

    cmd_port_control::sptr
    cmd_port_control::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new cmd_port_control_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    cmd_port_control_impl::cmd_port_control_impl(int develop_mode, int block_id)
      : gr::block("cmd_port_control",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
       _develop_mode(develop_mode),
       _block_id(block_id),
       _switch(true)
    {
      if(_develop_mode)
        std::cout << "develop_mode of cmd_port control check ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("cmd_in"));
      message_port_register_out(pmt::mp("cmd_out"));
      set_msg_handler(pmt::mp("cmd_in"), boost::bind(&cmd_port_control_impl::passing, this, _1 ));
      message_port_register_in(pmt::mp("control_in"));
      set_msg_handler(pmt::mp("control_in"), boost::bind(&cmd_port_control_impl::control, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    cmd_port_control_impl::~cmd_port_control_impl()
    {
    }

    void
    cmd_port_control_impl::passing(pmt::pmt_t cmd_in)
    {
      if(_switch)
        message_port_pub(pmt::mp("cmd_out"), cmd_in);
    }

    void
    cmd_port_control_impl::control(pmt::pmt_t cmd_in)
    {
      _switch = !_switch;
    }
  } /* namespace inets */
} /* namespace gr */

