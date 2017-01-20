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
#include "start_impl.h"

namespace gr {
  namespace inets {

    start::sptr
    start::make(int develop_mode, int block_id, int time_to_start_s)
    {
      return gnuradio::get_initial_sptr
        (new start_impl(develop_mode, block_id, time_to_start_s));
    }

    /*
     * The private constructor
     */
    start_impl::start_impl(int develop_mode, int block_id, int time_to_start_s)
      : gr::block("start",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _time_to_start_s(time_to_start_s)
    {
      if(_develop_mode)
        std::cout << "develop_mode of start ID: " << _block_id << " is activated." << std::endl;
      message_port_register_out(pmt::mp("out"));
//      start_out();
    }

    /*
     * Our virtual destructor.
     */
    start_impl::~start_impl()
    {
    }

    void
    start_impl::start_out()
    {
      boost::this_thread::sleep(boost::posix_time::microseconds(_time_to_start_s));
      message_port_pub(pmt::mp("out"), pmt::string_to_symbol("Start!"));
    }

  } /* namespace inets */
} /* namespace gr */

