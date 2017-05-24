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
#include "msg_strobe_filter_impl.h"
#include "math.h"

namespace gr {
  namespace inets {

    msg_strobe_filter::sptr
    msg_strobe_filter::make(int start_next_time_s, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new msg_strobe_filter_impl(start_next_time_s, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    msg_strobe_filter_impl::msg_strobe_filter_impl(int start_next_time_s, int system_time_granularity_us)
      : gr::block("msg_strobe_filter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _start_next_time_s(start_next_time_s),
        _system_time_granularity_us(system_time_granularity_us)
    {
      _started = false;
      message_port_register_in(pmt::mp("msg_in"));
      message_port_register_out(pmt::mp("start_out"));
      set_msg_handler(pmt::mp("msg_in"), boost::bind(&msg_strobe_filter_impl::check_start, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    msg_strobe_filter_impl::~msg_strobe_filter_impl()
    {
    }

    void
    msg_strobe_filter_impl::check_start(pmt::pmt_t msg)
    {
      if(!_started)
      {
        _started = true;
        struct timeval t; 
        gettimeofday(&t, NULL);
        double current_time_s = t.tv_sec;
        double start_time_s = t.tv_sec;
       
        while(current_time_s - _start_next_time_s * floor(start_time_s / _start_next_time_s) < _start_next_time_s)
        {
          boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
          gettimeofday(&t, NULL);
          current_time_s = t.tv_sec + t.tv_usec / 1000000.0;
        }
        message_port_pub(pmt::mp("start_out"), msg);
      }
    }

  } /* namespace inets */
} /* namespace gr */

