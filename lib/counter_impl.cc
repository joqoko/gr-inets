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
    counter::make(int develop_mode, int counter_id, int interval_mode)
    {
      return gnuradio::get_initial_sptr
        (new counter_impl(develop_mode, counter_id, interval_mode));
    }

    /*
     * The private constructor
     */
    counter_impl::counter_impl(int develop_mode, int counter_id, int interval_mode)
      : gr::block("counter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _counter_id(counter_id),
        _counter(0),
        _virgin(0)
    {
      if(_develop_mode)
        std::cout << "the " << _counter_id << "th message counter is activated." << std::endl;
      message_port_register_in(pmt::mp("message_in"));
      set_msg_handler(pmt::mp("message_in"), boost::bind(&counter_impl::counting, this, _1 ));
      message_port_register_in(pmt::mp("start_counter_in"));
      set_msg_handler(pmt::mp("start_counter_in"), boost::bind(&counter_impl::start_counting, this, _1 ));
      message_port_register_in(pmt::mp("stop_counter_in"));
      set_msg_handler(pmt::mp("stop_counter_in"), boost::bind(&counter_impl::stop_counting, this, _1 ));
      if(interval_mode)
        _in_counting = 1;
      else
        _in_counting = 1;
        struct timeval t; 
        gettimeofday(&t, NULL);
        _start_time = t.tv_sec + t.tv_usec / 1000000.0;
    }

    /*
     * Our virtual destructor.
     */
    counter_impl::~counter_impl()
    {
    }
 
    void counter_impl::stop_counting(pmt::pmt_t message)
    {
      _in_counting = 0;
      struct timeval t; 
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double current_time_show = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
      double interval = current_time - _start_time;
      std::cout << "counter ID " << _counter_id << " stop counting at time " << current_time_show << "s. in " << interval << "s, counter is visited " << _counter << " times" << std::endl;
    }

    void counter_impl::start_counting(pmt::pmt_t message)
    {
      if(_virgin == 0)
      {
        _in_counting = 1;
        _virgin = 1;
        struct timeval t; 
        gettimeofday(&t, NULL);
        _start_time = t.tv_sec + t.tv_usec / 1000000.0;
        double start_time_show = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
        std::cout << "counter ID " << _counter_id << " start counting at time " << start_time_show << "s" << std::endl;
      }
    }

    void counter_impl::counting(pmt::pmt_t message)
    {
      if(_in_counting)
      {
        _counter++;
        if(_develop_mode)
          // add the function that user can add name for counter
          std::cout << "the " << _counter_id << "th message counter has been visited " << _counter << " times "; 
        {
          if(_develop_mode == 2)
          {
            struct timeval t; 
            gettimeofday(&t, NULL);
            double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
            std::cout << " at time " << current_time << " s" << std::endl;
          }
          else
            std::cout << " " << std::endl;
        }
      }
    }

  } /* namespace inets */
} /* namespace gr */

