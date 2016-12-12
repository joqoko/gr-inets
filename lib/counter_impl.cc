/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
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
#include "counter_impl.h"

namespace gr {
  namespace inets {

    counter::sptr
    counter::make(std::vector<int> develop_mode_list, int counter_id)
    {
      return gnuradio::get_initial_sptr
        (new counter_impl(develop_mode_list, counter_id));
    }

    /*
     * The private constructor
     */
    counter_impl::counter_impl(std::vector<int> develop_mode_list, int counter_id)
      : gr::block("counter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode_list(develop_mode_list),
        _counter_id(counter_id),
        _counter(0)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _counter_id) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "the " << _counter_id << "th message counter is activated." << std::endl;
      message_port_register_in(pmt::mp("message_in"));
      set_msg_handler(pmt::mp("message_in"), boost::bind(&counter_impl::counting, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    counter_impl::~counter_impl()
    {
    }

    void counter_impl::counting(pmt::pmt_t message)
    {
      _counter++;
      if(_develop_mode)
        std::cout << "the " << _counter_id << "th message counter has been visited " << _counter << " times." << std::endl; 
    }

  } /* namespace inets */
} /* namespace gr */

