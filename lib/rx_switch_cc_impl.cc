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
#include <numeric>

namespace gr {
  namespace inets {

    rx_switch_cc::sptr
    rx_switch_cc::make(int develop_mode, int block_id, int num_fetch_per_cs)
    {
      return gnuradio::get_initial_sptr
        (new rx_switch_cc_impl(develop_mode, block_id, num_fetch_per_cs));
    }

    /*
     * The private constructor
     */
    rx_switch_cc_impl::rx_switch_cc_impl(int develop_mode, int block_id, int num_fetch_per_cs)
      : gr::sync_block("rx_switch_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        _block_id(block_id),
        _develop_mode(develop_mode),
        _num_fetch_per_cs(num_fetch_per_cs),
        _is_receiving(1)
    {
      if(_develop_mode)
        std::cout << "develop_mode of rx_switch_cc ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("rx_switch_in"));
      message_port_register_out(pmt::mp("power_out"));
      set_msg_handler(pmt::mp("rx_switch_in"), boost::bind(&rx_switch_cc_impl::kai_guan, this, _1 ));
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
      gr_complex complex_zero(0, 0);
        
      /* 
       * signal is not changed if _is_receiving is true, otherwise just all zeros.
       */
      double pow_sum = 0;
      if(_is_receiving)
      {
     //   if(_develop_mode == 2)
     //   {
     //     struct timeval t; 
     //     gettimeofday(&t, NULL);
     //     double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
     //     std::cout << "rx_switch_cc ID: " << _block_id << " received " << noutput_items << " at time " << current_time << " s" << std::endl;
     //   }
        //std::cout << "noutput_items" << noutput_items << std::endl;
        for(int i = 0; i < noutput_items; i++)
        {
          out[i] = in[i];
          pow_sum = pow_sum + abs(out[i]);
        }
      }
      else
      {
        for(int i = 0; i < noutput_items; i++)
        {
          //out[i] = in[i] / 10000;
          out[i] = complex_zero;
        }
      }
      _vec_average_pow.push_back(pow_sum / noutput_items);

      if(_vec_average_pow.size() > _num_fetch_per_cs)
      {
        double pow_average_all_fetch = std::accumulate(_vec_average_pow.begin(), _vec_average_pow.end(), 0.0) / _num_fetch_per_cs;
        message_port_pub(pmt::mp("power_out"), pmt::from_double(pow_average_all_fetch));
        //std::cout << "average power at rx switch is: " << pow_average_all_fetch << std::endl;
        _vec_average_pow.clear();
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void
    rx_switch_cc_impl::kai_guan(pmt::pmt_t spark)
    {
      if(_develop_mode)
      {
	std::cout << "++++ rx_switch ID: " << _block_id;
      }
      struct timeval t;
      gettimeofday(&t, NULL);
      double start_time_show = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
      if(pmt::is_bool(spark))
      {
        // std::cout << "received a pmt bool" << std::endl;
        if(pmt::to_bool(spark))
        {
          if(_develop_mode)
          {
            if(_is_receiving)
              std::cout << " continue receiving at time ";
            else 
              std::cout << " start receiving at time ";
          }
          _is_receiving = 1;
        }
        else
        {
          if(_develop_mode)
          {
            if(_is_receiving)
              std::cout << " stop receiving at time ";
            else 
              std::cout << " stay inactive mode at time ";
          }
          _is_receiving = 0;
        }
      }
      else
      {
        // not a boolean pmt, most likely an import error
        std::cout << "++++ rx_switch ID: " << _block_id << " error: not a spark signal" << std::endl;
      }
      if(_develop_mode)
        std::cout << start_time_show << "s" << std::endl;
    }
  } /* namespace inets */
} /* namespace gr */

