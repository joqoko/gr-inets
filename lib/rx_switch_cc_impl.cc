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
#include "rx_switch_cc_impl.h"

namespace gr {
  namespace inets {

    rx_switch_cc::sptr
    rx_switch_cc::make(int develop_mode)
    {
      return gnuradio::get_initial_sptr
        (new rx_switch_cc_impl(develop_mode));
    }

    /*
     * The private constructor
     */
    rx_switch_cc_impl::rx_switch_cc_impl(int develop_mode)
      : gr::sync_block("rx_switch_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        _develop_mode(develop_mode),
        _is_receiving(1)
    {
      message_port_register_in(pmt::mp("spark_in"));
      set_msg_handler(pmt::mp("spark_in"), boost::bind(&rx_switch_cc_impl::kai_guan, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    rx_switch_cc_impl::~rx_switch_cc_impl()
    {
    }

    int
    rx_switch_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

        
      /* 
       * signal is not changed if _is_receiving is true, otherwise just all zeros.
       */
      for(int i = 0; i < noutput_items; i++)
      {
        out[i] = in[i] * _is_receiving;
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void
    rx_switch_cc_impl::kai_guan(pmt::pmt_t spark)
    {
      // std::cout << "received a message" << std::endl;
      if(pmt::is_bool(spark))
      {
        // std::cout << "received a pmt bool" << std::endl;
        if(pmt::to_bool(spark))
        {
          if(_develop_mode)
          {
            if(_is_receiving)
              std::cout << "Continue receiving." << std::endl;
            else 
              std::cout << "Start receiving." << std::endl;
          }
          _is_receiving = 1;
        }
        else
        {
          if(_develop_mode)
          {
            if(_is_receiving)
              std::cout << "Stop receiving." << std::endl;
            else 
              std::cout << "Stay inactive mode." << std::endl;
          }
          _is_receiving = 0;
        }
      }
      else
      {
        // not a boolean pmt, most likely an import error
        if(_develop_mode)
          std::cout << "not a spark signal" << std::endl;
      }
    }
  } /* namespace inets */
} /* namespace gr */

