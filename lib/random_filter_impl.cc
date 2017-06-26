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
#include "random_filter_impl.h"

namespace gr {
  namespace inets {

    random_filter::sptr
    random_filter::make(int develop_mode, int block_id, double threshold)
    {
      return gnuradio::get_initial_sptr
        (new random_filter_impl(develop_mode, block_id, threshold));
    }

    /*
     * The private constructor
     */
    random_filter_impl::random_filter_impl(int develop_mode, int block_id, double threshold)
      : gr::block("random_filter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
	_threshold(threshold)
    {
      if(_develop_mode)
        std::cout << "develop_mode of random_filter ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("cmd_in")); 
      set_msg_handler(pmt::mp("cmd_in"), boost::bind(&random_filter_impl::rolling, this, _1));
      message_port_register_in(pmt::mp("set_threshold")); 
      set_msg_handler(pmt::mp("set_threshold"), boost::bind(&random_filter_impl::set_threshold, this, _1));
      message_port_register_out(pmt::mp("win_cmd_out"));
      message_port_register_out(pmt::mp("lose_cmd_out"));
    }

    /*
     * Our virtual destructor.
     */
    random_filter_impl::~random_filter_impl()
    {
    }

    void
    random_filter_impl::set_threshold(pmt::pmt_t cmd_in)
    {
      _threshold = pmt::to_double(cmd_in);
    }

    void
    random_filter_impl::rolling(pmt::pmt_t pmt_in)
    {
      double exp =  (double)rand()/(double)(RAND_MAX);
      if(exp < _threshold)
      {
        message_port_pub(pmt::mp("win_cmd_out"),pmt_in);
        if(_develop_mode)
          std::cout << "generated random number is" << exp << " and the threshold is " << _threshold << ". good luck. " << std::endl;
      }
      else
      {
        message_port_pub(pmt::mp("lose_cmd_out"),pmt_in);
        if(_develop_mode)
          std::cout << "generated random number is" << exp << " and the threshold is " << _threshold << ". bad luck and try next time. " << std::endl;
      }
    }

  } /* namespace inets */
} /* namespace gr */

