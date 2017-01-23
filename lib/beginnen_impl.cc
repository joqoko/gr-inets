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
#include "beginnen_impl.h"

namespace gr {
  namespace inets {

    beginnen::sptr
    beginnen::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new beginnen_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    beginnen_impl::beginnen_impl(int develop_mode, int block_id)
      : gr::block("beginnen",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _started(false)
    { 
      if(_develop_mode == 1)
        std::cout << "develop_mode of Beginnen ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("trigger_in"));
      set_msg_handler(pmt::mp("trigger_in"), boost::bind(&beginnen_impl::trigger, this, _1 ));
      message_port_register_out(pmt::mp("out"));
    }

    /*
     * Our virtual destructor.
     */
    beginnen_impl::~beginnen_impl()
    {
    }

    void 
    beginnen_impl::trigger(pmt::pmt_t msg)
    {
      if(!_started)
      {
        std::cout << "Here 0" << std::endl;
        message_port_pub(pmt::mp("out"), pmt::string_to_symbol("Start"));
        std::cout << "Here 1" << std::endl;
        _started = true;
      }
    }

  } /* namespace inets */
} /* namespace gr */

