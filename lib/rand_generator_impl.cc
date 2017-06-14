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
#include "rand_generator_impl.h"

namespace gr {
  namespace inets {

    rand_generator::sptr
    rand_generator::make(int develop_mode, int block_id, int mode, double min, double max, int distribution)
    {
      return gnuradio::get_initial_sptr
        (new rand_generator_impl(develop_mode, block_id, mode, min, max, distribution));
    }

    /*
     * The private constructor
     */
    rand_generator_impl::rand_generator_impl(int develop_mode, int block_id, int mode, double min, double max, int distribution)
      : gr::block("rand_generator",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _mode(mode),
        _min(min),
        _max(max),
        _distribution(distribution)
    {
      if(_develop_mode == 1)
        std::cout << "develop_mode of rand_generator ID " << _block_id << " is activated." << std::endl;
      if(max < min)
        std::cout << "warning rand_generator ID " << _block_id << " max is smaller than min. " << std::endl;
      std::srand((unsigned)time(NULL));  
      message_port_register_in(pmt::mp("cmd_in"));
      message_port_register_out(pmt::mp("cmd_out"));
      set_msg_handler(
        pmt::mp("cmd_in"),
        boost::bind(&rand_generator_impl::creation, this, _1)
      );
    }


    /*
     * Our virtual destructor.
     */
    rand_generator_impl::~rand_generator_impl()
    {
    }

    void
    rand_generator_impl::creation(pmt::pmt_t cmd_in)
    {
      double rand_f =  (double)rand()/(double)(RAND_MAX);
      // random float
      if(_mode == 0)
      {
        double rand_out = rand_f * (_max - _min) + _min;
        message_port_pub(pmt::mp("cmd_out"), pmt::from_double(rand_out));
      } 
      // random int
      else if(_mode == 1)
      {
        int rand_out = int(round(rand_f * (_max - _min) + _min));
        message_port_pub(pmt::mp("cmd_out"), pmt::from_long(rand_out));
      }
      else
        std::cout << " error rand_generator ID " << _block_id << " unsupported mode." << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

