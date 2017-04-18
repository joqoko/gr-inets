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
#include "dummy_source_impl.h"

namespace gr {
  namespace inets {

    dummy_source::sptr
    dummy_source::make(int develop_mode, int block_id, int payload_length, int source_type, double packet_rate)
    {
      return gnuradio::get_initial_sptr
        (new dummy_source_impl(develop_mode, block_id, payload_length, source_type, packet_rate));
    }

    /*
     * The private constructor
     */
    dummy_source_impl::dummy_source_impl(int develop_mode, int block_id, int payload_length, int source_type, double packet_rate)
      : gr::block("dummy_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _payload_length(payload_length),
        _source_type(source_type),
        _packet_rate(packet_rate),
        _start(0)
    {
      if(_develop_mode)
        std::cout << "develop_mode of dummy source ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("trigger")); 
      set_msg_handler(pmt::mp("trigger"), boost::bind(&dummy_source_impl::trigger, this, _1));
      message_port_register_out(pmt::mp("output"));
    }

    /*
     * Our virtual destructor.
     */
    dummy_source_impl::~dummy_source_impl()
    {
    }

    void
    dummy_source_impl::trigger (pmt::pmt_t trig)
    {
      /*
      if(_start == 0)
      { 
        std::string trigger;
        trigger = pmt::symbol_to_string(trig);
        if(trigger.compare("TEST") == 0)
        {
          std::cout << "trigger test failed " << trigger << std::endl;
          _start = 1;
        }
      }
       */
      /*
       * source_type 1: infinite source. This type of the source offers infinite number of payload. Other part of the protocol need to pull the payload.
       */
      if(_source_type == 1)
      {
        if(pmt::is_integer(trig))
        {
          for(int i = 0; i < pmt::to_long(trig); i++)
          {
            std::vector<unsigned char> payload(_payload_length);
            message_port_pub(pmt::mp("output"), pmt::cons(pmt::make_dict(), pmt::init_u8vector(payload.size(), payload)));
            if(_develop_mode)
              std::cout << "dummy infinite source ID: " << _block_id << " generate a payload." << std::endl;
          }
          if(_develop_mode)
            std::cout << "dummy infinite source ID: " << _block_id << " generate and output " << pmt::to_long(trig) << " payloads in a row." << std::endl;
          message_port_pub(pmt::mp("output"), trig);
        }
        else
        {
          std::vector<unsigned char> payload(_payload_length);
          message_port_pub(pmt::mp("output"), pmt::cons(pmt::make_dict(), pmt::init_u8vector(payload.size(), payload)));
        }
      }
      /*
       * source_type 2: constant rate source. 
       */
      else if(_source_type == 2)
      {  
        if(_develop_mode)
          std::cout << "dummy source ID: " << _block_id << "starts generating payload with constant data rate." << std::endl;
        struct timeval t;
        while(true)
        {
          boost::this_thread::sleep(boost::posix_time::microseconds(1 / _packet_rate * 1000000));
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec + t.tv_usec / 1000000.0;
          std::vector<unsigned char> payload(_payload_length);
          message_port_pub(pmt::mp("output"), pmt::cons(pmt::make_dict(), pmt::init_u8vector(payload.size(), payload)));
          if(_develop_mode)
            std::cout << "dummy constant rate source ID: " << _block_id << " generate a payload." << std::endl;
        }
      }
      else
        std::cout << "The chosen source is not supported yet. Your contribution is welcome." << std::endl; 
    }

  } /* namespace inets */
} /* namespace gr */

