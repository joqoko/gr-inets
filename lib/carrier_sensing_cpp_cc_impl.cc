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
    carrier_sensing_cpp_cc::make(int develop_mode, int block_id, double cs_duration, float cs_threshold, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new carrier_sensing_cpp_cc_impl(develop_mode, block_id, cs_duration, cs_threshold, system_time_granularity_us));
    }

    /*
     * the private constructor
     */
    carrier_sensing_cpp_cc_impl::carrier_sensing_cpp_cc_impl(int develop_mode, int block_id, double cs_duration, float cs_threshold, int system_time_granularity_us)
      : gr::block("carrier_sensing_cpp_cc",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _cs_duration(cs_duration),
        _system_time_granularity_us(system_time_granularity_us),
        _cs_threshold(cs_threshold)
    {
      _in_cca = false;
      _cs_time = 0;
      message_port_register_in(pmt::mp("info_in"));
      message_port_register_out(pmt::mp("frame_info_fail_out"));
      message_port_register_out(pmt::mp("frame_info_pass_out"));
      set_msg_handler(
        pmt::mp("info_in"),
        boost::bind(&carrier_sensing_cpp_cc_impl::start_sensing, this, _1)
      );
    }

    /*
     * our virtual destructor.
     */
    carrier_sensing_cpp_cc_impl::~carrier_sensing_cpp_cc_impl()
    {
    }

    void carrier_sensing_cpp_cc_impl::start_sensing(pmt::pmt_t info_in)
    {
      // std::cout << "received a message" << std::endl;
      if(pmt::is_dict(info_in))
      {
        if(_develop_mode == 1 || _develop_mode == 2)
          std::cout << "+++++++++ carrier sensing ID: " << _block_id << "  +++++++++++++++" << std::endl;    
        // this function is fired
        pmt::pmt_t not_found;
        int frame_type = pmt::to_long(pmt::dict_ref(info_in, pmt::string_to_symbol("frame_type"), not_found)); 
        if(frame_type == 1)
        {
          _frame_info = info_in;
          _in_cca = true;
          if(_develop_mode == 1)
            std::cout << "before sending a data frame, start sensing" << std::endl;
          boost::thread thrd(&carrier_sensing_cpp_cc_impl::countdown_sensing, this);
        }
        else
        {
          if(_develop_mode == 1)
            std::cout << "before sending a ack frame, no sensing" << std::endl;
          message_port_pub(pmt::mp("frame_info_pass_out"), info_in);
        }
      }
      else if(pmt::is_real(info_in))
      {
        double power = pmt::to_double(info_in);
        _in_cca = (_cs_threshold > power);
        if(_develop_mode == 1 && !_in_cca)
        {
          struct timeval t;
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
          std::cout << "in carrier sensing, average rx power is: " << power << ", received at " << current_time << " s" << std::endl;
        }
      }
      else
      {
        // not a dict pmt, most likely an import error
        std::cout << "Warning: is not a valid input pmt. Please check your connections." << std::endl;
      }
    }

    void carrier_sensing_cpp_cc_impl::countdown_sensing()
    {
      _in_cca = true;
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;
      // std::cout << "start_countdown" << std::endl;
      // std::cout << "cs duration is: " << _cs_duration << " in second: " << _cs_duration /1000 << std::endl;
      // std::cout << "current time is: " << current_time << std::endl;
      // std::cout << "_in_cca is: " << _in_cca << std::endl;
      // std::cout << "time condition is: " << (start_time + (_cs_duration / 1000) - current_time) << std::endl;
      // std::cout << ((current_time < start_time + _cs_duration / 1000) && _in_cca) << std::endl;
      while((current_time < start_time + _cs_duration / 1000) && _in_cca)
      {
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us)); 
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
//        std::cout << "current sensing time is: " << current_time - start_time - _cs_duration / 1000 << std::endl;
        // std::cout << "sensing status is: " << _in_cca << std::endl;
//        std::cout << "in sensing " << start_time + _cs_duration / 1000 - current_time << std::endl;
      }
      if(_in_cca)
      {
        if(_develop_mode == 1)
          std::cout << "Carrier sensing passed. " << std::endl;
        message_port_pub(pmt::mp("frame_info_pass_out"), _frame_info);
      }
      else
      {
        if(_develop_mode == 1)
          std::cout << "Carrier sensing failed. " << std::endl;
        message_port_pub(pmt::mp("frame_info_fail_out"), _frame_info);
      }
      _in_cca = false;
      _cs_time = current_time - start_time;
      if(_develop_mode == 1)
        std::cout << "Carrier sensing time is: " << _cs_time << " s" << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

