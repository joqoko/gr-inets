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
#include "idle_cpp_impl.h"
#include <algorithm>

namespace gr {
  namespace inets {

    idle_cpp::sptr
    idle_cpp::make(std::vector<int> develop_mode_list, int experiment_duration)
    {
      return gnuradio::get_initial_sptr
        (new idle_cpp_impl(develop_mode_list, experiment_duration));
    }

    /*
     * The private constructor
     */
    idle_cpp_impl::idle_cpp_impl(std::vector<int> develop_mode_list, int experiment_duration)
      : gr::block("idle_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _experiment_duration(experiment_duration),
        _develop_mode_list(develop_mode_list),
        _my_develop_mode(1),
        _develop_mode(0)
    {
      _experiment_running = true;
      _in_idle = true;
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
      {
        std::cout << "Experiment is started. The whole experiment will take " << _experiment_duration << " seconds." << std::endl;
        std::cout << "develop_mode of idle_cpp is activated." << std::endl;
      }
      message_port_register_in(pmt::mp("spark_in"));
      message_port_register_in(pmt::mp("payload_from_network_layer_in"));
      message_port_register_in(pmt::mp("frame_from_phy_in"));
      message_port_register_out(pmt::mp("spark_out"));
      message_port_register_out(pmt::mp("payload_pmt_out"));
      message_port_register_out(pmt::mp("frame_pmt_out"));
      set_msg_handler(
        pmt::mp("spark_in"),
        boost::bind(&idle_cpp_impl::activate_idle, this, _1)
      );
      set_msg_handler(
        pmt::mp("frame_from_phy_in"),
        boost::bind(&idle_cpp_impl::handler_good_packet_from_phy, this, _1)
      );
      set_msg_handler(
        pmt::mp("payload_from_network_layer_in"),
        boost::bind(&idle_cpp_impl::handler_data_from_network_layer, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    idle_cpp_impl::~idle_cpp_impl()
    {
    }

    void idle_cpp_impl::activate_idle(pmt::pmt_t msg)
    {
      /*
       * Check the received message. Misconnecting message port may lead to this error.
       */
      if(_develop_mode)
      {
        std::cout << "+++++++++++++     idle_cpp     +++++++++++++" << std::endl;
      }
      if(pmt::is_bool(msg))
      {
        /*
         * If the received message is ture (in boolean form), then activate the idle state.
         */
        if(pmt::to_bool(msg))
        {
          if(!_in_idle)
          {
            _in_idle = true; // Enabling _in_idle state
            if(_develop_mode)
              std::cout << "Idle state is activated." << std::endl;
          }
        }
        else
        {
          if(_in_idle)
          {
            _in_idle = false;
            if(_develop_mode)
              std::cout << "Idle state is deactivated." << std::endl;
          }
        }
        message_port_pub(pmt::mp("spark_out"), pmt::from_bool(_in_idle));
      }
      else
      {
        // Not a boolean pmt, most likely a gnuradio connection error
        if(_develop_mode)
          std::cout << "Error: Input pmt is not a spark signal." << std::endl;
      }

    }

    void idle_cpp_impl::handler_data_from_network_layer(pmt::pmt_t msg)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++     idle_cpp     +++++++++++++" << std::endl;
      }
      if(!_in_idle)
      {
        if(_develop_mode)
          std::cout << "Warning: data is inputed into idle state. Please check your buffer control" << std::endl;
      }
      if(_experiment_running)
      {
        if(pmt::is_pair(msg)) 
        {
          pmt::pmt_t payload_pmt = pmt::cdr(msg);

          if(pmt::is_u8vector(payload_pmt))
          { 
            if(_develop_mode)
              std::cout << "Idle state is deactivated by receiving payload from network layer." << std::endl;
            _in_idle = false;
            message_port_pub(pmt::mp("payload_pmt_out"), msg);
          } 
          else 
          { 
            if(_develop_mode)
              std::cout << "Payload is not an u8 vector." << std::endl; 
          }
          message_port_pub(pmt::mp("spark_out"), pmt::from_bool(_in_idle));
        } 
        else 
        {
          if(_develop_mode)
            std::cout << "Error: input pmt is not a pair." << std::endl;
        }
      }
      else
        std::cout << "Experiment ends. Please collect your data and buy one drum of whisky." << std::endl;
    }      

    void idle_cpp_impl::handler_good_packet_from_phy(pmt::pmt_t msg)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++++     idle_cpp     +++++++++++++" << std::endl;
      }
      if(!_in_idle)
      {
        if(_develop_mode)
          std::cout << "Warning: data is inputed into idle state. Please check your buffer control" << std::endl;
      }
      if(_experiment_running)
      {
        if(pmt::is_pair(msg)) 
        {
          pmt::pmt_t payload_pmt = pmt::cdr(msg);

          if(pmt::is_u8vector(payload_pmt))
          { 
            if(_develop_mode)
              std::cout << "Idle state is deactivated by receiving packet from PHY." << std::endl;
            _in_idle = false;
            message_port_pub(pmt::mp("frame_pmt_out"), msg);
          } 
          else 
          { 
            if(_develop_mode)
              std::cout << "Payload is not an u8 vector." << std::endl; 
          }
          message_port_pub(pmt::mp("spark_out"), pmt::from_bool(_in_idle));
        } 
        else 
        {
          if(_develop_mode)
            std::cout << "Error: input pmt is not a pair." << std::endl;
        }
      }
      else
        std::cout << "Experiment ends. Please collect your data and buy one drum of whisky." << std::endl;
    }      
  } /* namespace inets */
} /* namespace gr */

