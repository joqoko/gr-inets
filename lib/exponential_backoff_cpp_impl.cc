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
#include "exponential_backoff_cpp_impl.h"
#include <stdlib.h>  
#include <math.h>
#include <time.h>

namespace gr {
  namespace inets {

    exponential_backoff_cpp::sptr
    exponential_backoff_cpp::make(int backoff_time_unit, int max_n_backoff, int min_backoff)
    {
      return gnuradio::get_initial_sptr
        (new exponential_backoff_cpp_impl(backoff_time_unit, max_n_backoff, min_backoff));
    }

    /*
     * the private constructor
     */
    exponential_backoff_cpp_impl::exponential_backoff_cpp_impl(int backoff_time_unit, int max_n_backoff, int min_backoff)
      : gr::block("exponential_backoff_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _backoff_time_unit(backoff_time_unit),
        _max_n_backoff(max_n_backoff),
        _min_backoff(min_backoff)
    {
      _n_backoff = 0;
      std::srand((unsigned)time(NULL));  
      message_port_register_in(pmt::mp("spark_in"));
      message_port_register_out(pmt::mp("spark_out"));
      set_msg_handler(
        pmt::mp("spark_in"),
        boost::bind(&exponential_backoff_cpp_impl::start_backoff, this, _1)
      );
    }

    /*
     * our virtual destructor.
     */
    exponential_backoff_cpp_impl::~exponential_backoff_cpp_impl()
    {
    }

    void exponential_backoff_cpp_impl::start_backoff(pmt::pmt_t msg)
    {
      /*
       * check the received message. misconnecting message port may lead to this error.
       */
      if(pmt::is_bool(msg))
      {
        /*
         * if the received message is ture (in boolean form), then start the cs countdown.
         */
        if(pmt::to_bool(msg))
        {
          boost::thread thrd(&exponential_backoff_cpp_impl::countdown_backoff, this);
          if(_n_backoff >= _max_n_backoff)
          {
            _n_backoff = 1;
          } 
          else
          {
            _n_backoff++;
          }
        }
        else
        {
          message_port_pub(pmt::mp("spark_out"), pmt::from_bool(false));
          std::cout << "inets dmf error: received a false spark signal, please check previous blocks" << std::endl;
        }
      }
      else
      {
        // not a boolean pmt, most likely a gnuradio connection error
        std::cout << "not a spark signal" << std::endl;
      }
    }

    void exponential_backoff_cpp_impl::countdown_backoff()
    {
      //float backoff_time = std::rand() % std::pow(2, _n_backoff) + _min_backoff;
      float backoff_time = std::rand() % (int)std::pow(2, _n_backoff) * _backoff_time_unit + _min_backoff;
      std::cout << "in " << _n_backoff << "th backoff, the backoff time is: " << backoff_time << std::endl;
      boost::this_thread::sleep(boost::posix_time::milliseconds(backoff_time));
      message_port_pub(pmt::mp("spark_out"), pmt::from_bool(true));
    }

  } /* namespace inets */
} /* namespace gr */

