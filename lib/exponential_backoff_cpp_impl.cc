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
    exponential_backoff_cpp::make(int develop_mode, int block_id, int backoff_time_unit_ms, int max_n_backoff, int min_backoff_ms)
    {
      return gnuradio::get_initial_sptr
        (new exponential_backoff_cpp_impl(develop_mode, block_id, backoff_time_unit_ms, max_n_backoff, min_backoff_ms));
    }

    /*
     * the private constructor
     */
    exponential_backoff_cpp_impl::exponential_backoff_cpp_impl(int develop_mode, int block_id, int backoff_time_unit_ms, int max_n_backoff, int min_backoff_ms)
      : gr::block("exponential_backoff_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _backoff_time_unit_ms(backoff_time_unit_ms),
        _block_id(block_id),
        _develop_mode(develop_mode),
        _max_n_backoff(max_n_backoff),
        _min_backoff_ms(min_backoff_ms)
    {
      if(_develop_mode == 1)
        std::cout << "develop_mode of exponential_backoff_cpp is activated." << std::endl;
      _n_backoff = 0;
      std::srand((unsigned)time(NULL));  
      message_port_register_in(pmt::mp("frame_info_trigger_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
      set_msg_handler(
        pmt::mp("frame_info_trigger_in"),
        boost::bind(&exponential_backoff_cpp_impl::start_backoff, this, _1)
      );
    }

    /*
     * our virtual destructor.
     */
    exponential_backoff_cpp_impl::~exponential_backoff_cpp_impl()
    {
    }

    void exponential_backoff_cpp_impl::start_backoff(pmt::pmt_t frame_info)
    {
      if(_develop_mode == 1)
      {
        std::cout << "++++++++  exponential_backoff_cpp  +++++++++" << std::endl;
      }
      /*
       * check the received message. misconnecting message port may lead to this error.
       */
      if(pmt::is_dict(frame_info))
      {
        /*
         * if the received message is ture (in boolean form), then start the cs countdown.
         */
        _frame_info = frame_info;
        pmt::pmt_t not_found;
        int num_transmission = pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("num_transmission"), not_found));
        _n_backoff = num_transmission;
        if(_n_backoff > _max_n_backoff)
          _n_backoff = 0;
        else
        {
          if(_develop_mode == 2)
          {
            struct timeval t;
            gettimeofday(&t, NULL);
            double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
            std::cout << "* timeout ID: " << _block_id << " timeout timer is triggered at time " << current_time << " s" << std::endl;
          }
        }
        boost::thread thrd(&exponential_backoff_cpp_impl::countdown_backoff, this);
      }
      else
      {
        // not a boolean pmt, most likely a gnuradio connection error
        std::cout << "not correct input signal at block ID: " << _block_id << std::endl;
      }
    }

    void 
    exponential_backoff_cpp_impl::countdown_backoff()
    {
      struct timeval t;
      if(_n_backoff)
     {
        //float backoff_time = std::rand() % std::pow(2, _n_backoff) + _min_bakcoff_ms;
        float backoff_time = std::rand() % (int)std::pow(2, _n_backoff) * _backoff_time_unit_ms + _min_backoff_ms;
        if(_develop_mode == 1)
          std::cout << "in " << _n_backoff << "th backoff, the backoff time is: " << backoff_time << "[ms]." << std::endl;
        boost::this_thread::sleep(boost::posix_time::milliseconds(backoff_time));
      }
      else
        if(_develop_mode == 1)
          std::cout << "backoff counter reset so no waiting this time." << std::endl; 
      if(_develop_mode == 2)
      {
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        std::cout << "* backoff ID: " << _block_id << "backoff timer is expired at time " << current_time << " s" << std::endl;
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
    }
  } /* namespace inets */
} /* namespace gr */

