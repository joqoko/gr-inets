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
#include "dice_impl.h"

namespace gr {
  namespace inets {

    dice::sptr
    dice::make(int develop_mode, int block_id, int probability)
    {
      return gnuradio::get_initial_sptr
        (new dice_impl(develop_mode, block_id, probability));
    }

    /*
     * The private constructor
     */
    dice_impl::dice_impl(int develop_mode, int block_id, int probability)
      : gr::block("dice",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
       _block_id(block_id),
       _develop_mode(develop_mode),
       _probability(probability)
    {
      if(_develop_mode)
        std::cout << "develop_mode of dice ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("in"));
      message_port_register_out(pmt::mp("win_out"));
      message_port_register_out(pmt::mp("lost_out"));
      set_msg_handler(pmt::mp("in"), boost::bind(&dice_impl::check_probability, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    dice_impl::~dice_impl()
    {
    }

    void
    dice_impl::check_probability(pmt::pmt_t msg)
    {
      double p = ((double) rand() / (RAND_MAX)) + 1;
      if(p < _probability)
      {
        if(_develop_mode)
          std::cout << "p is " << p << " and the probability is " << _probability << " so you lost" << std::endl;
        message_port_pub(pmt::mp("lost_out"), msg);
      }
      else
      {
        if(_develop_mode)
          std::cout << "p is " << p << " and the probability is " << _probability << " so you win" << std::endl;
        message_port_pub(pmt::mp("win_out"), msg);
      }
    }

  } /* namespace inets */
} /* namespace gr */

