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
#include "number_recorder_impl.h"

namespace gr {
  namespace inets {

    number_recorder::sptr
    number_recorder::make(int develop_mode, int block_id, std::string recorder_name, std::string record_path, int name_with_timestamp)
    {
      return gnuradio::get_initial_sptr
        (new number_recorder_impl(develop_mode, block_id, recorder_name, record_path, name_with_timestamp));
    }

    /*
     * The private constructor
     */
    number_recorder_impl::number_recorder_impl(int develop_mode, int block_id, std::string recorder_name, std::string record_path, int name_with_timestamp)
      : gr::block("number_recorder",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _recorder_name(recorder_name),
        _name_with_timestamp(name_with_timestamp)
    {
      if(_develop_mode)
        std::cout << "the " << _block_id << "th message recorder is activated." << std::endl;
      message_port_register_in(pmt::mp("cmd_in"));
      set_msg_handler(pmt::mp("cmd_in"), boost::bind(&number_recorder_impl::recording, this, _1 ));
      message_port_register_in(pmt::mp("change_file_name_in"));
      set_msg_handler(pmt::mp("change_file_name_in"), boost::bind(&number_recorder_impl::change_file_name, this, _1 ));
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

    /*
     * Our virtual destructor.
     */
    number_recorder_impl::~number_recorder_impl()
    {
    }

    void
    number_recorder_impl::recording(pmt::pmt_t cmd_in)
    { 
      if(pmt::is_number(cmd_in))
      {
        double new_n = pmt::to_double(cmd_in);
        std::ofstream ofs (_file_name_str.c_str(), std::ofstream::app);
        ofs << new_n << "\n";
        ofs.close();
        if(_develop_mode)
          std::cout << "new value at number_recorder ID " << _block_id << " is " << new_n << std::endl;
      }
      else
      {
        if(_develop_mode)
          std::cout << "error number_recorder ID " << _block_id << " receives non-number inputs. " << std::endl;
      }
    }

    void
    number_recorder_impl::change_file_name(pmt::pmt_t new_name)
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

