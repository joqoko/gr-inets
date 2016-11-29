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
#include "wait_cpp_impl.h"

namespace gr {
  namespace inets {

    wait_cpp::sptr
    wait_cpp::make(int develop_mode, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new wait_cpp_impl(develop_mode, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    wait_cpp_impl::wait_cpp_impl(int develop_mode, int system_time_granularity_us)
      : gr::block("wait_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _system_time_granularity_us(system_time_granularity_us)
    {
      _wait_time = 0;
      message_port_register_in(pmt::mp("wait_time_in"));
      message_port_register_out(pmt::mp("spark_out"));
      set_msg_handler(
        pmt::mp("wait_time_in"),
        boost::bind(&wait_cpp_impl::start_waiting, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    wait_cpp_impl::~wait_cpp_impl()
    {
    }

    void wait_cpp_impl::start_waiting(pmt::pmt_t msg) 
    {
      if(pmt::is_pair(msg))
      {
        pmt::pmt_t payload_pmt = pmt::cdr(msg);
        if(pmt::is_real(payload_pmt))
        {
          _wait_time = pmt::to_double(payload_pmt);
          boost::thread thrd(&wait_cpp_impl::countdown_sensing, this);       
        }
      }
    }
    
    void wait_cpp_impl::countdown_sensing()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      if(_develop_mode)
      {
        std::cout << "Start time: " << start_time << std::endl;
        std::cout << "wait time: " << _wait_time/1000 << std::endl;
      }
      while(current_time < start_time + _wait_time / 1000)
      {
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        if(_develop_mode)
        {
          std::cout << "Remaining time: " << _wait_time/1000 - (current_time - start_time) << std::endl;
        }
      }
      message_port_pub(pmt::mp("spark_out"), pmt::from_bool(true));
    }

  } /* namespace inets */
} /* namespace gr */

