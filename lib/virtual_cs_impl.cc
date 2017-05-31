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
#include "virtual_cs_impl.h"

namespace gr {
  namespace inets {

    virtual_cs::sptr
    virtual_cs::make(int develop_mode, int block_id, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new virtual_cs_impl(develop_mode, block_id, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    virtual_cs_impl::virtual_cs_impl(int develop_mode, int block_id, int system_time_granularity_us)
      : gr::block("virtual_cs",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _system_time_granularity_us(system_time_granularity_us),
        _block_id(block_id)
    {
      _tx_frame = pmt::from_long(0);
      _nav_us = 0;
      message_port_register_out(pmt::mp("frame_cmd_out"));
      message_port_register_in(pmt::mp("frame_cmd_in"));
      set_msg_handler(
        pmt::mp("frame_cmd_in"),
        boost::bind(&virtual_cs_impl::check_nav, this, _1)
      ); 

      message_port_register_in(pmt::mp("nav_cmd_in"));
      set_msg_handler(
        pmt::mp("nav_cmd_in"),
        boost::bind(&virtual_cs_impl::set_nav, this, _1)
      ); 
    }

    /*
     * Our virtual destructor.
     */
    virtual_cs_impl::~virtual_cs_impl()
    {
    }

    void
    virtual_cs_impl::check_nav(pmt::pmt_t command)
    {
      if(_nav_us <= 0)
      {
        if(_develop_mode)
          std::cout << "virtual_cs ID " << _block_id << " is not in NAV, forward frame immediately" << std::endl;
        message_port_pub(pmt::mp("frame_cmd_out"), command);
      }
      else
      {
        if(_develop_mode)
          std::cout << "virtual_cs ID " << _block_id << " is in NAV, frame is stored" << std::endl;
        if(pmt::is_dict(_tx_frame))
          std::cout << "error: virtual_cs block ID " << _block_id << " has unsend frame in buffer. " << std::endl;
        _tx_frame = command;
      }
    }

    void
    virtual_cs_impl::set_nav(pmt::pmt_t command)
    {
      if(pmt::dict_has_key(command, pmt::string_to_symbol("nav_time")))
      {
        pmt::pmt_t not_found;
        _nav_us = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("nav_time"), not_found));
        int frame_type = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("frame_type"), not_found));
        if(frame_type == 4)
        {
          _rts_index = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("frame_index"), not_found));
          _rts_src_addr = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("source_address"), not_found));
          _rts_dest_addr = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("destination_address"), not_found));
          if(_develop_mode)
          {
            std::cout << "virtual_cs ID " << _block_id << " set NAV to " << _nav_us << " [us]" << " for the rts frame with frame index " << _rts_index << "sent by node " << _rts_src_addr << " to node " << _rts_dest_addr;
          }
          boost::thread thrd(&virtual_cs_impl::countdown_nav, this);       
        }
        else if(frame_type == 5)
        {
          int frame_index = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("frame_index"), not_found));
          int src_addr = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("source_address"), not_found));
          int dest_addr = pmt::to_long(pmt::dict_ref(command, pmt::string_to_symbol("destination_address"), not_found));
          if(_rts_src_addr == dest_addr && _rts_dest_addr == src_addr && _rts_index == frame_index)
          {
            if(_develop_mode)
            {
              std::cout << "virtual_cs ID " << _block_id << " received a cts which is the responce of the last rts. new NAV is " << _nav_us << " [us]" << " and the last NAV still has " << _last_nav_s * 1000000 << " [us] to counting down." << std::endl;
            }
          }
          else
          {
            if(_develop_mode)
            {
              std::cout << "virtual_cs ID " << _block_id << " set NAV to " << _nav_us << " [us]" << " for the cts frame with frame index " << frame_index << " sent by node " << src_addr << " to node " << dest_addr;
            }
            boost::thread thrd(&virtual_cs_impl::countdown_nav, this);       
          }
        }
        else
          std::cout << "error: virtual_cs ID " << _block_id << " received wrong frame type (type no. " << frame_type << ")."<<  std::endl;
      } 
    }

    void
    virtual_cs_impl::countdown_nav()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = current_time;
      double start_time_show = t.tv_sec - double(int(t.tv_sec/1000)*1000) + t.tv_usec / 1000000.0;
      double current_time_show = start_time_show;
      if(_develop_mode)
        std::cout << " at " << start_time_show;
      while((current_time < start_time + double(_nav_us) / 1000000))
      {
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        _last_nav_s = double(_nav_us)/1000000 - (current_time - start_time);
        // std::cout << "timeout is running at: " << current_time_show << std::endl;
      }
      _nav_us = 0;
      gettimeofday(&t, NULL);
      current_time = t.tv_sec + t.tv_usec / 1000000.0;
      if(_develop_mode)
      {
        current_time_show = t.tv_sec - double(int(t.tv_sec/1000)*1000) + t.tv_usec / 1000000.0;
        std::cout << "[s] and expired at time " << current_time_show << " [s]. " << " actual duration is: " << current_time - start_time << " [s]." << std::endl;
      }
      if(pmt::is_dict(_tx_frame))
      {
        if(_develop_mode)
        {
          std::cout << "virtual_cs ID: " << _block_id << " exports stored frame." << std::endl;
        }
        message_port_pub(pmt::mp("frame_cmd_out"), _tx_frame);
        _tx_frame = pmt::from_long(0);
      }
    }

  } /* namespace inets */
} /* namespace gr */

