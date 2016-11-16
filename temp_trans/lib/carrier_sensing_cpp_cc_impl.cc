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
#include "carrier_sensing_cpp_cc_impl.h"

namespace gr {
  namespace inets {

    carrier_sensing_cpp_cc::sptr
    carrier_sensing_cpp_cc::make(float cs_duration, float cs_threshold)
    {
      return gnuradio::get_initial_sptr
        (new carrier_sensing_cpp_cc_impl(cs_duration, cs_threshold));
    }

    /*
     * The private constructor
     */
    carrier_sensing_cpp_cc_impl::carrier_sensing_cpp_cc_impl(float cs_duration, float cs_threshold)
      : gr::sync_block("carrier_sensing_cpp_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        _cs_duration(cs_duration),
        _cs_threshold(cs_threshold)
    {
      _in_CCA = false;
      _cs_time = 0;
      message_port_register_in(pmt::mp("spark_in"));
      message_port_register_out(pmt::mp("spark_out"));
      set_msg_handler(
        pmt::mp("spark_in"),
        boost::bind(&carrier_sensing_cpp_cc_impl::start_sensing, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    carrier_sensing_cpp_cc_impl::~carrier_sensing_cpp_cc_impl()
    {
    }

    int
    carrier_sensing_cpp_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // variables for the power of input signal
      double total_pow = 0;
      double avg_pow = 0;
      // std::cout << "Noutput_items is: " << noutput_items << std::endl;
      for(int i = 0; i < noutput_items; i++)
      {
        out[i] = in[i];
      }
      // std::cout << "Frequently here?" << std::endl;
      std::cout << "_in_CCA status: " << _in_CCA << std::endl;
      if(_in_CCA)
      {
        std::cout << "In sensing mode" << std::endl;
        // the total power of input signal
        for(int i = 0; i < noutput_items; i++)
        {
          total_pow += std::abs(in[i]) * std::abs(in[i]);
        }
        // average power of input signal
        avg_pow = total_pow / noutput_items;
        std::cout << "Average power is:" << avg_pow << std::endl;
        if(avg_pow > _cs_threshold)
        {
          // here we need to output a message of CCA false
          _in_CCA = false;
          message_port_pub(pmt::mp("spark_out"), pmt::from_bool(_in_CCA));
        }
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void carrier_sensing_cpp_cc_impl::start_sensing(pmt::pmt_t msg)
    {
      // std::cout << "Received a message" << std::endl;
      if(pmt::is_bool(msg))
      {
        // std::cout << "Received a pmt bool" << std::endl;
        if(pmt::to_bool(msg))
        {
          // This function is fired
          // std::cout << "Start sensing" << std::endl;
          _in_CCA = true;
          _cs_time = countdown_sensing();
          std::cout << "Sensing time is:" << _cs_time << std::endl;
        }
      }
      else
      {
        // Not a boolean pmt, most likely an import error
        std::cout << "Not a spark signal" << std::endl;
      }
    }

    double carrier_sensing_cpp_cc_impl::countdown_sensing()
    {
      _in_CCA = true;
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      // std::cout << "Start_countdown" << std::endl;
      // std::cout << "cs duration is: " << _cs_duration << std::endl;
      // std::cout << "current time is: " << current_time << std::endl;
      // std::cout << "_in_CCA is: " << _in_CCA << std::endl;
      // std::cout << "Time condition is: " << (start_time + (_cs_duration / 1000) - current_time) << std::endl;
      while((current_time < start_time + _cs_duration / 1000) && _in_CCA)
      {
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        // std::cout << "sensing time is: " << current_time - start_time - _cs_duration / 1000 << std::endl;
        // std::cout << "in sensing " << start_time + _cs_duration / 1000 - current_time << std::endl;
      }
      _in_CCA = false;
      return current_time - start_time;
    }

  } /* namespace inets */
} /* namespace gr */

