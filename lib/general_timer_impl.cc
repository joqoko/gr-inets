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
#include "general_timer_impl.h"

namespace gr {
  namespace inets {

    general_timer::sptr
    general_timer::make(int develop_mode, int block_id, int timer_type, int duration_ms, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new general_timer_impl(develop_mode, block_id, timer_type, duration_ms, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    general_timer_impl::general_timer_impl(int develop_mode, int block_id, int timer_type, int duration_ms, int system_time_granularity_us)
      : gr::block("general_timer",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _timer_type(timer_type),
        _duration_ms(duration_ms),
        _system_time_granularity_us(system_time_granularity_us),
        _in_active(false)
    {
      if(_develop_mode)
        std::cout << "develop_mode of general_timer ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("active_in"));
      set_msg_handler(pmt::mp("active_in"), boost::bind(&general_timer_impl::start_timer, this, _1 ));
      message_port_register_out(pmt::mp("expire_signal_out"));
    }

    /*
     * Our virtual destructor.
     */
    general_timer_impl::~general_timer_impl()
    {
    }

    void
    general_timer_impl::start_timer(pmt::pmt_t trigger)
    {
       if(_develop_mode)
       {
         struct timeval t; 
         gettimeofday(&t, NULL);
         double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
         std::cout << "* timeout ID: " << _block_id << " general timer " << _block_id << " is triggered at time " << current_time << " s" << std::endl;
       }
       if(!_in_active)
       {
         _in_active = true;
         boost::thread thrd(&general_timer_impl::countdown_timer, this);       
       }
       else
         std::cout << "timer cannot trigger twice. please check your connections." << std::endl;
    }
 
    void
    general_timer_impl::countdown_timer()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = current_time;
      double start_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
      double current_time_show = start_time_show;
      if(_develop_mode)
        std::cout << "timeout timer start time: " << start_time_show << std::endl;
      while((current_time < start_time + _duration_ms / 1000) && _in_active)
      {
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        current_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        // std::cout << "timeout is running at: " << current_time_show << std::endl;
      }
      gettimeofday(&t, NULL);
      current_time = t.tv_sec + t.tv_usec / 1000000.0;
      if(_develop_mode)
      {
        current_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        if(_in_active)
          std::cout << "* general timer ID: " << _block_id << " is expired at time " << current_time_show << " s. " << " duration is: " << _duration_ms << " [ms]" << std::endl;
        else
          std::cout << "* general timer ID: " << _block_id << " is killed at time " << current_time_show << " s. " << " actual timeout duration is: " << current_time_show - start_time_show << " s" << std::endl;
      }
      pmt::pmt_t expire = pmt::make_dict();
      expire = pmt::dict_add(expire, pmt::string_to_symbol("time_stamp"), pmt::from_double(current_time));
      message_port_pub(pmt::mp("expire_signal_out"), expire);
      _in_active = false;
    }
  

  } /* namespace inets */
} /* namespace gr */

