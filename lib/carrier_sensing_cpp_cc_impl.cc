/* -*- c++ -*- */
/* 
 * copyright 2016 <+you or your company+>.
 * 
 * this is free software; you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation; either version 3, or (at your option)
 * any later version.
 * 
 * this software is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 * 
 * you should have received a copy of the gnu general public license
 * along with this software; see the file copying.  if not, write to
 * the free software foundation, inc., 51 franklin street,
 * boston, ma 02110-1301, usa.
 */

#ifdef have_config_h
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "carrier_sensing_cpp_cc_impl.h"
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gr {
  namespace inets {

    carrier_sensing_cpp_cc::sptr
    carrier_sensing_cpp_cc::make(float cs_duration, float cs_threshold)
    {
      return gnuradio::get_initial_sptr
        (new carrier_sensing_cpp_cc_impl(cs_duration, cs_threshold));
    }

    /*
     * the private constructor
     */
    carrier_sensing_cpp_cc_impl::carrier_sensing_cpp_cc_impl(float cs_duration, float cs_threshold)
      : gr::sync_block("carrier_sensing_cpp_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        _cs_duration(cs_duration),
        _cs_threshold(cs_threshold)
    {
      _in_cca = false;
      _cs_time = 0;
      message_port_register_in(pmt::mp("spark_in"));
      message_port_register_out(pmt::mp("spark_out"));
      set_msg_handler(
        pmt::mp("spark_in"),
        boost::bind(&carrier_sensing_cpp_cc_impl::start_sensing, this, _1)
      );
    }

    /*
     * our virtual destructor.
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

      /*
       * variables for the power of input signal
       */
      double total_pow = 0;
      double avg_pow = 0;
      /* 
       * signal is not changed through carrier sensing block, i.e., it simply output its input.
       */
      for(int i = 0; i < noutput_items; i++)
      {
        out[i] = in[i];
      }
      /* 
       * if carrier sensing is required by other blocks, power of input signal is calculated 
       * and compared with a predefined threshold.
       */
      if(_in_cca)
      {
        std::cout << "in sensing mode" << std::endl;
        for(int i = 0; i < noutput_items; i++)
        {
          total_pow += std::abs(in[i]) * std::abs(in[i]);
        }
        avg_pow = total_pow / noutput_items;
        std::cout << "average power is:" << avg_pow << std::endl;
        if(avg_pow > _cs_threshold)
        {
          /*
           * spark_out message is sent if cca false
           */
          _in_cca = false;
          std::cout << "Signal detected at power: " << avg_pow << std::endl; 
        }
      }
      // tell runtime system how many output items we produced.
      return noutput_items;
    }

    void carrier_sensing_cpp_cc_impl::start_sensing(pmt::pmt_t msg)
    {
      // std::cout << "received a message" << std::endl;
      if(pmt::is_bool(msg))
      {
        // std::cout << "received a pmt bool" << std::endl;
        if(pmt::to_bool(msg))
        {
          // this function is fired
          // std::cout << "start sensing" << std::endl;
          _in_cca = true;
          std::cout << "start sensing" << std::endl;
          boost::thread thrd(&carrier_sensing_cpp_cc_impl::countdown_sensing, this);
          // thrd.join();
        }
      }
      else
      {
        // not a boolean pmt, most likely an import error
        std::cout << "not a spark signal" << std::endl;
      }
    }

    void carrier_sensing_cpp_cc_impl::countdown_sensing()
    {
      _in_cca = true;
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      std::cout << "start_countdown" << std::endl;
      std::cout << "cs duration is: " << _cs_duration << std::endl;
      std::cout << "current time is: " << current_time << std::endl;
      std::cout << "_in_cca is: " << _in_cca << std::endl;
      std::cout << "time condition is: " << (start_time + (_cs_duration / 1000) - current_time) << std::endl;
      std::cout << ((current_time < start_time + _cs_duration / 1000) && _in_cca) << std::endl;
      while((current_time < start_time + _cs_duration / 1000) && _in_cca)
      {
        boost::this_thread::sleep(boost::posix_time::milliseconds(5)); 
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        std::cout << "current sensing time is: " << current_time - start_time - _cs_duration / 1000 << std::endl;
        // std::cout << "sensing status is: " << _in_cca << std::endl;
        // std::cout << "in sensing " << start_time + _cs_duration / 1000 - current_time << std::endl;
      }
      message_port_pub(pmt::mp("spark_out"), pmt::from_bool(_in_cca));
      _in_cca = false;
      _cs_time = current_time - start_time;
    }

  } /* namespace inets */
} /* namespace gr */

