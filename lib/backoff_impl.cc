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
#include "backoff_impl.h"
#include <stdlib.h>  
#include <math.h>
#include <time.h>

namespace gr {
  namespace inets {

    backoff::sptr
    backoff::make(int develop_mode, int block_id, int backoff_type, int backoff_time_unit_ms, int min_backoff_ms, int max_backoff_ms)
    {
      return gnuradio::get_initial_sptr
        (new backoff_impl(develop_mode, block_id, backoff_type, backoff_time_unit_ms, min_backoff_ms, max_backoff_ms));
    }

    /*
     * the private constructor
     */
    backoff_impl::backoff_impl(int develop_mode, int block_id, int backoff_type, int backoff_time_unit_ms, int min_backoff_ms, int max_backoff_ms)
      : gr::block("backoff",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _backoff_time_unit_ms(backoff_time_unit_ms),
        _block_id(block_id),
        _backoff_type(backoff_type),
        _develop_mode(develop_mode),
        _min_backoff_ms(min_backoff_ms),
        _max_backoff_ms(max_backoff_ms)
    {
      if(_develop_mode == 1)
        std::cout << "develop_mode of backoff is activated." << std::endl;
      _n_backoff = 0;
      std::srand((unsigned)time(NULL));  
      message_port_register_in(pmt::mp("frame_info_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
      set_msg_handler(
        pmt::mp("frame_info_in"),
        boost::bind(&backoff_impl::start_backoff, this, _1)
      );
    }

    /*
     * our virtual destructor.
     */
    backoff_impl::~backoff_impl()
    {
    }

    void backoff_impl::start_backoff(pmt::pmt_t frame_info)
    {
      if(_develop_mode == 1)
      {
        std::cout << "++++  backoff ID: " << _block_id << " ++++" << std::endl;
      }
      if(_develop_mode == 2)
      {
        struct timeval t;
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        std::cout << "* backoff ID: " << _block_id << " backoff timer is triggered at time " << current_time << " s" << std::endl;
      }
      _frame_info = frame_info;
      pmt::pmt_t not_found;
      /*
       * check the received message. misconnecting message port may lead to this error.
       */
      if(pmt::is_dict(frame_info))
      {
        /*
         * _backoff_type 1: exponential backoff.
         */
        if(_backoff_type == 1)
        {
          int num_transmission = pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("num_transmission"), not_found));
          _n_backoff = num_transmission;
          boost::thread thrd(&backoff_impl::countdown_exp_backoff, this);
        }
        /*
         * _backoff_type 2: constant backoff.
         */
        else if(_backoff_type == 2)
          boost::thread thrd(&backoff_impl::countdown_const_backoff, this);
        /*
         * _backoff_type 2: random backoff.
         */
        else if(_backoff_type == 3)
          boost::thread thrd(&backoff_impl::countdown_random_backoff, this);
      }
      else
      {
        // not a boolean pmt, most likely a gnuradio connection error
        std::cout << "not correct input signal at block ID: " << _block_id << std::endl;
      }
    }

    void 
    backoff_impl::countdown_const_backoff()
    {
      struct timeval t;
      boost::this_thread::sleep(boost::posix_time::milliseconds(_min_backoff_ms));
      if(_develop_mode == 2)
      {
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
        std::cout << "* backoff ID: " << _block_id << "backoff timer is expired at time " << current_time << " s" << std::endl;
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
    }

    void 
    backoff_impl::countdown_random_backoff()
    {
      struct timeval t;
      //float backoff_time = std::rand() % std::pow(2, _n_backoff) + _min_bakcoff_ms;
      float backoff_time = std::rand() % (_max_backoff_ms - _min_backoff_ms) + _min_backoff_ms;
      if(_develop_mode)
          std::cout << "in random backoff, the backoff time is: " << backoff_time << "[ms]." << std::endl;
      boost::this_thread::sleep(boost::posix_time::milliseconds(backoff_time));
      if(_develop_mode == 2)
      {
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
        std::cout << "backoff ID: " << _block_id << "backoff timer is expired at time " << current_time << " s" << std::endl;
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
    }

    void 
    backoff_impl::countdown_exp_backoff()
    {
      struct timeval t;
      if(_n_backoff)
      {
        //float backoff_time = std::rand() % std::pow(2, _n_backoff) + _min_bakcoff_ms;
        float backoff_time = std::rand() % (int)std::pow(2, _n_backoff) * _backoff_time_unit_ms + _min_backoff_ms;
        if(_develop_mode)
          std::cout << "in " << _n_backoff << "th backoff, the backoff time is: " << backoff_time << "[ms]." << std::endl;
        boost::this_thread::sleep(boost::posix_time::milliseconds(backoff_time));
      }
      else
        if(_develop_mode)
          std::cout << "backoff counter reset so no waiting this time." << std::endl; 
      if(_develop_mode == 2)
      {
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
        std::cout << "* backoff ID: " << _block_id << "backoff timer is expired at time " << current_time << " s" << std::endl;
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
    }
  } /* namespace inets */
} /* namespace gr */

