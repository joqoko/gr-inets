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

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <queue>
#include <gnuradio/io_signature.h>
#include "time_probe_impl.h"

namespace gr {
  namespace inets {

    time_probe::sptr
    time_probe::make(int develop_mode, int block_id, int mode, int record_on, std::string recorder_name, std::string record_path, int name_with_timestamp)
    {
      return gnuradio::get_initial_sptr
        (new time_probe_impl(develop_mode, block_id, mode, record_on, recorder_name, record_path, name_with_timestamp));
    }

    /*
     * The private constructor
     */
    time_probe_impl::time_probe_impl(int develop_mode, int block_id, int mode, int record_on, std::string recorder_name, std::string record_path, int name_with_timestamp)
      : gr::block("time_probe",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _recorder_name(recorder_name),
        _name_with_timestamp(name_with_timestamp),
        _record_on(record_on),
        _mode(mode)
    {
      if(_develop_mode)
        std::cout << "develop mode of time_probe ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("time_former_in"));
      set_msg_handler(pmt::mp("time_former_in"), boost::bind(&time_probe_impl::get_former, this, _1 ));
      message_port_register_in(pmt::mp("time_later_in"));
      set_msg_handler(pmt::mp("time_later_in"), boost::bind(&time_probe_impl::calc_duration, this, _1 ));
      message_port_register_in(pmt::mp("change_file_name_in"));
      set_msg_handler(pmt::mp("change_file_name_in"), boost::bind(&time_probe_impl::change_file_name, this, _1 ));
      if(_mode == 1)
      {
        struct timeval t;
        gettimeofday(&t, NULL);
        _former_time = t.tv_sec + t.tv_usec / 1000000.0;
      }
      if(_record_on)
      {
        struct timeval t; 
        gettimeofday(&t, NULL);
        time_t tt = time(0);   // get time now
        struct tm * now = localtime( & tt );
        std::ostringstream file_name;
        if(_name_with_timestamp)
          file_name << "/home/inets/source/gr-inets/results/" << (now->tm_year + 1900) << "_" << (now->tm_mon + 1) << "_" << now->tm_mday << "_" << now->tm_hour << "_" << now->tm_min << "_" << now->tm_sec << "_recorder" << block_id << "_" << _recorder_name << ".txt";
        else
          file_name << "/home/inets/source/gr-inets/results/" << _recorder_name << ".txt";
        _file_name_str = file_name.str();
      }
    }

    /*
     * Our virtual destructor.
     */
    time_probe_impl::~time_probe_impl()
    {
    }

    void
    time_probe_impl::get_former(pmt::pmt_t cmd_in)
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      _former_time = t.tv_sec + t.tv_usec / 1000000.0;
    }

    void
    time_probe_impl::calc_duration(pmt::pmt_t cmd_in)
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double later_time = t.tv_sec + t.tv_usec / 1000000.0;
      double duration = later_time - _former_time;
      std::cout << "time_probe ID " << _block_id << " duration is " << duration << " [s]" << std::endl;
      if(_mode == 1)
        _former_time = later_time;
      if(_record_on)
      {
        std::ofstream ofs (_file_name_str.c_str(), std::ofstream::app);
        ofs << duration << "\n";
        ofs.close();
      }
    }

    void
    time_probe_impl::change_file_name(pmt::pmt_t new_name)
    { 
      // currently only accept double as input
      if(pmt::is_real(new_name))
      {
        time_t tt = time(0);   // get time now
        struct tm * now = localtime( & tt );
        std::ostringstream file_name;
        if(_name_with_timestamp)
          file_name << "/home/inets/source/gr-inets/results/" << (now->tm_year + 1900) << "_" << (now->tm_mon + 1) << "_" << now->tm_mday << "_" << now->tm_hour << "_" << now->tm_min << "_" << now->tm_sec << "_block" << _block_id << "_" << _recorder_name << new_name << ".txt";
        else
          file_name << "/home/inets/source/gr-inets/results/" << _recorder_name << new_name << ".txt";
        _file_name_str = file_name.str();
      }
    }
  } /* namespace inets */
} /* namespace gr */

