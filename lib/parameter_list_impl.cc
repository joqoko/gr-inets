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
#include "parameter_list_impl.h"

namespace gr {
  namespace inets {

    parameter_list::sptr
    parameter_list::make(int develop_mode, int block_id, const std::vector<double> list)
    {
      return gnuradio::get_initial_sptr
        (new parameter_list_impl(develop_mode, block_id, list));
    }

    /*
     * The private constructor
     */
    parameter_list_impl::parameter_list_impl(int develop_mode, int block_id, const std::vector<double> list)
      : gr::block("parameter_list",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _output_n(true),
        _list(list)
    {
      if(_develop_mode)
        std::cout << "develop_mode of parameter_list check ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("trigger_in"));
      message_port_register_out(pmt::mp("parameter_out"));
      message_port_register_out(pmt::mp("n_parameter_out"));
      set_msg_handler(pmt::mp("trigger_in"), boost::bind(&parameter_list_impl::kick, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    parameter_list_impl::~parameter_list_impl()
    {
    }

    void
    parameter_list_impl::kick(pmt::pmt_t cmd_in)
    {
      if(_output_n)
      {
        message_port_pub(pmt::mp("n_parameter_out"), pmt::from_long(_list.size()));
        _output_n = false;
      }
      if(_develop_mode)
        std::cout << "parameter_list ID: " << _block_id;
      if(_list.size() > 0) 
      {
        message_port_pub(pmt::mp("parameter_out"), pmt::from_double(_list.back()));
        if(_develop_mode)
          std::cout << "exported parameter is: " << _list.back() << std::endl;
        _list.pop_back();
      }
      else 
      {
        if(_develop_mode)
          std::cout << " no paramter left. no output " << std::endl;
      }
    }

  } /* namespace inets */
} /* namespace gr */

