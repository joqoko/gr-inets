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
    backoff::make(int develop_mode, int block_id, int backoff_type, int backoff_time_unit_ms, int min_backoff_ms, int max_backoff_ms, int apply_cs, double cs_threshold, int system_time_granularity_us, int virtual_cs, int min_window_size)
    {
      return gnuradio::get_initial_sptr
        (new backoff_impl(develop_mode, block_id, backoff_type, backoff_time_unit_ms, min_backoff_ms, max_backoff_ms, apply_cs, cs_threshold, system_time_granularity_us, virtual_cs, min_window_size));
    }

    /*
     * the private constructor
     */
    backoff_impl::backoff_impl(int develop_mode, int block_id, int backoff_type, int backoff_time_unit_ms, int min_backoff_ms, int max_backoff_ms, int apply_cs, double cs_threshold, int system_time_granularity_us, int virtual_cs, int min_window_size)
      : gr::block("backoff",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _backoff_time_unit_ms(backoff_time_unit_ms),
        _block_id(block_id),
        _backoff_type(backoff_type),
        _develop_mode(develop_mode),
        _min_backoff_ms(min_backoff_ms),
        _max_backoff_ms(max_backoff_ms),
        _apply_cs(!apply_cs),
        _cs_threshold(cs_threshold),
        _system_time_granularity_us(system_time_granularity_us),
        _ch_busy(false),
        _timer_bias_s(0),
        _power(0),
        _in_backoff(false),
        _nav_us(0),
        _min_window_size(min_window_size),
        _virtual_cs(!virtual_cs)
    {
      if(_develop_mode == 1)
        std::cout << "develop_mode of backoff ID " << _block_id << " is activated." << std::endl;
      _n_backoff = 0;
      std::srand((unsigned)time(NULL));  
      message_port_register_in(pmt::mp("frame_info_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
      message_port_register_out(pmt::mp("busy_time_out"));
      message_port_register_out(pmt::mp("bof_time_out"));
      set_msg_handler(
        pmt::mp("frame_info_in"),
        boost::bind(&backoff_impl::start_backoff, this, _1)
      );
      message_port_register_in(pmt::mp("virtual_cs_frame_in"));
      set_msg_handler(
        pmt::mp("virtual_cs_frame_in"),
        boost::bind(&backoff_impl::start_virtual_cs, this, _1)
      );
      message_port_register_in(pmt::mp("power_in"));
      set_msg_handler(
        pmt::mp("power_in"),
        boost::bind(&backoff_impl::carrier_sensing, this, _1)
      );
      message_port_register_in(pmt::mp("cs_threshold_in"));
      set_msg_handler(
        pmt::mp("cs_threshold_in"),
        boost::bind(&backoff_impl::set_cs_threshold, this, _1)
      );
      struct timeval t;
      gettimeofday(&t, NULL);
      _start_busy = t.tv_sec + t.tv_usec / 1000000.0;
      _ch_busy = false;
    }

    /*
     * our virtual destructor.
     */
    backoff_impl::~backoff_impl()
    {
    }

    void backoff_impl::set_cs_threshold(pmt::pmt_t cs_threshold_in)
    {
      if(pmt::is_real(cs_threshold_in))
      {
        _cs_threshold = pmt::to_double(cs_threshold_in);
        if(_develop_mode)
          std::cout << "backoff ID " << _block_id << " carrier sensing threshold is reset to " << _cs_threshold << std::endl;
      }
      else
        std::cout << "++++ backoff ID " << _block_id << " error: port cs_threshold_in receives unknown data type. please check your connections." << std::endl;
    }

    void backoff_impl::carrier_sensing(pmt::pmt_t power_in)
    {
      if(pmt::is_real(power_in))
      {
        if(_backoff_type == 1 && _apply_cs)
        {
          _power = pmt::to_double(power_in);
          bool ch_busy_now = (_power > _cs_threshold);
          if(_in_backoff && ch_busy_now && !_ch_busy)
          {
            struct timeval t;
            gettimeofday(&t, NULL);
            _start_busy = t.tv_sec + t.tv_usec / 1000000.0;
          }
          if(_in_backoff && !ch_busy_now && _ch_busy)
          {
            struct timeval t;
            gettimeofday(&t, NULL);
            double end_busy = t.tv_sec + t.tv_usec / 1000000.0;
            message_port_pub(pmt::mp("busy_time_out"), pmt::from_double(end_busy - _start_busy));
          }
          _ch_busy = ch_busy_now;
        }
        else
          _ch_busy = false;
      }
      else
        std::cout << "++++ backoff ID " << _block_id << " error: port power_in receives unknown data type. please check your connections." << std::endl;
    }

    void backoff_impl::start_virtual_cs(pmt::pmt_t rcts)
    {
      if(pmt::is_dict(rcts))
      {
        if(_develop_mode)
        {
          std::cout << "++++ backoff ID: " << _block_id << " start virtual carrier sensing ";
          if(_develop_mode == 2)
          {
            struct timeval t;
            gettimeofday(&t, NULL);
            double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
            std::cout << "at time " << current_time << " s  ++++" << std::endl;
          }
          else
            std::cout << " ++++" << std::endl;
        }
        pmt::pmt_t not_found;
        /*
         * check the received message. misconnecting message port may lead to this error.
         */
        int frame_type;
        frame_type = pmt::to_long(pmt::dict_ref(rcts, pmt::string_to_symbol("frame_type"), not_found));
        if(frame_type == 4 || frame_type == 5)
        {
          _nav_us = pmt::to_long(pmt::dict_ref(rcts, pmt::string_to_symbol("nav_time"), not_found));
          if(!_in_backoff)
          {
            start_backoff(rcts);
          }
          // no else case here because _nav_us will be added in to the existing timer automatically.
        }
        else
          std::cout << "backoff ID " << _block_id << " error: port virtual_cs_frame_in receives non-rts/cts frame. please check your connections." << std::endl;
      }
      else
        std::cout << "backoff ID " << _block_id << " error: port virtual_cs_frame_in receives unknown data type. please check your connections." << std::endl;
    }

    void backoff_impl::start_backoff(pmt::pmt_t frame_info)
    {
      if(!_in_backoff)
      {
        if(pmt::is_dict(frame_info))
        {
/*     
          if(_develop_mode)
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
*/     
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
              if(pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("frame_type"), not_found)) == 2)
              {
                // ACK frame
                _n_backoff = 1;
                if(_develop_mode)
                  std::cout << "backoff ID " << _block_id << " is trigger by ACK frame means the last DATA frame is successfully acked. " << std::endl;
              }
              else
              {
                // other frames
                int num_transmission = pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("num_transmission"), not_found));
                _n_backoff = num_transmission;
              }
              _n_backoff = _n_backoff + _min_window_size;
//              if(_apply_cs)
                boost::thread thrd(&backoff_impl::countdown_exp_backoff_cs, this);
//              else
//                boost::thread thrd(&backoff_impl::countdown_exp_backoff, this);
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
            std::cout << "not correct input signal at backoff ID: " << _block_id << std::endl;
          }
        }
        else
          std::cout << "backoff ID " << _block_id << " error: port frame_info_in receives unknown data type. please check your connections." << std::endl;
      }
      else
         std::cout << "backoff ID " << _block_id << " warning: port frame_info_in received correct data type but in _in_backoff states. backoff timer cannot be triggered twice." << std::endl;
        
    }

    void 
    backoff_impl::countdown_const_backoff()
    {
      _in_backoff = true;
      struct timeval t;
      boost::this_thread::sleep(boost::posix_time::milliseconds(_min_backoff_ms));
      if(_develop_mode == 2)
      {
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
        std::cout << "++++ backoff ID: " << _block_id << "backoff timer is expired at time " << current_time << " s" << std::endl;
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
      _in_backoff = false;
    }

    void 
    backoff_impl::countdown_random_backoff()
    {
      _in_backoff = true;
      struct timeval t;
      //float backoff_time = std::rand() % std::pow(2, _n_backoff) + _min_bakcoff_ms;
      float backoff_time = std::rand() % (_max_backoff_ms - _min_backoff_ms) + _min_backoff_ms;
      if(_develop_mode)
          std::cout << "++++ backoff ID: " << _block_id  << "the random backoff duration is: " << backoff_time << "ms." << std::endl;
      boost::this_thread::sleep(boost::posix_time::milliseconds(backoff_time));
      if(_develop_mode == 2)
      {
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
        std::cout << "++++ backoff ID: " << _block_id << "backoff timer is expired at time " << current_time << " s" << std::endl;
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
      _in_backoff = false;
    }
/*
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
        double current_time = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
        std::cout << "* backoff ID: " << _block_id << "backoff timer is expired at time " << current_time << " s" << std::endl;
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
    }
*/
    void 
    backoff_impl::countdown_exp_backoff_cs()
    {
      struct timeval t;
      _in_backoff = true;
      gettimeofday(&t, NULL);
      double begin_time = t.tv_sec + t.tv_usec / 1000000.0;
      if(_n_backoff)
      {
        //float backoff_time = std::rand() % std::pow(2, _n_backoff) + _min_bakcoff_ms;
        double backoff_time_s;
        gettimeofday(&t, NULL);
        double start_time = t.tv_sec + t.tv_usec / 1000000.0;
        double current_time = start_time;
        double start_time_show = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
        double previous_time = t.tv_sec + t.tv_usec / 1000000.0;
        if(_nav_us == 0)
        {
          backoff_time_s = double(std::rand() % (int)std::pow(2, _n_backoff) * _backoff_time_unit_ms + _min_backoff_ms) / 1000;
          if(_develop_mode)
          std::cout << "++++ backoff ID: " << _block_id << " starts the " << _n_backoff << "th backoff";
          if(_develop_mode == 2)
            std::cout << " at " << start_time_show << "s and the backoff duration is: " << backoff_time_s << "s." << std::endl;
          else if(_develop_mode == 1)
            std::cout << ". " << std::endl;
        }
        else
        {
          backoff_time_s = double(_nav_us) / 1000000;
          std::cout << "++++ backoff ID: " << _block_id << " starts a " << double(_nav_us) / 1000000 << "s NAV at " << start_time_show << "s" << std::endl;
        }
        _nav_us = 0;
        double remain_time_s = backoff_time_s;
        while(remain_time_s - _timer_bias_s > 0)
        {
          gettimeofday(&t, NULL);
          if(_nav_us > 0)
          { 

            double current_time_show = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
            std::cout << "++++ backoff ID: " << _block_id << " starts a " << double(_nav_us) / 1000000 << "s NAV when " << remain_time_s << "s left at time " << current_time_show << "s. ";
            remain_time_s = remain_time_s + double(_nav_us) / 1000000;
            std::cout << " backoff timer is extended to " << remain_time_s << "s" << std::endl;
            _nav_us = 0;
          }
          boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
          current_time = t.tv_sec + t.tv_usec / 1000000.0;
          if(!_ch_busy || !_apply_cs)
          {
            _timer_bias_s = current_time - previous_time;
            remain_time_s = remain_time_s - _timer_bias_s;
          }
          else
          {
            if(_develop_mode == 2)
            {
              double current_time_show = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
              std::cout << "++++ backoff ID: " << _block_id << " at time " << current_time_show << "s channel is busy (" << _power << "/" << _cs_threshold << "), so backoff timer is froze." << std::endl;
            }
          }
          //std::cout << "remain_time_s is: " << remain_time_s << std::endl;
          previous_time = current_time;
        }
   
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        //_timer_bias_s = _timer_bias_s / 2 + (current_time - start_time - backoff_time_s) / 2;
        if(_develop_mode)
        {
          double current_time_show = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
          std::cout << "++++ backoff ID: " << _block_id << " is expired at time " << current_time_show << " s. " << " actual duration is: " << current_time - start_time << "s and the timer bias is " << _timer_bias_s << "s" << std::endl;
        }
      }
      else
      {
        if(_develop_mode)
          std::cout << "backoff counter reset so no waiting this time." << std::endl; 
      }
      message_port_pub(pmt::mp("frame_info_out"), _frame_info);
      gettimeofday(&t, NULL);
      double end_time = t.tv_sec + t.tv_usec / 1000000.0;
      message_port_pub(pmt::mp("bof_time_out"),pmt::from_double(end_time - begin_time));
      _in_backoff = false;
    }
  } /* namespace inets */
} /* namespace gr */

