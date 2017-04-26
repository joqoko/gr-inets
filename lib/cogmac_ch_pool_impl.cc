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
#include "cogmac_ch_pool_impl.h"

namespace gr {
  namespace inets {

    cogmac_ch_pool::sptr
    cogmac_ch_pool::make(int develop_mode, int block_id, int channel_number, int first_channel, int algorithm, int channel_gap)
    {
      return gnuradio::get_initial_sptr
        (new cogmac_ch_pool_impl(develop_mode, block_id, channel_number, first_channel, algorithm, channel_gap));
    }

    /*
     * The private constructor
     */
    cogmac_ch_pool_impl::cogmac_ch_pool_impl(int develop_mode, int block_id, int channel_number, int first_channel, int algorithm, int channel_gap)
      : gr::block("cogmac_ch_pool",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _channel_number(channel_number),
        _first_channel(first_channel),
        _channel_gap(channel_gap),
        _algorithm(algorithm)
    {
      if(_develop_mode)
        std::cout << "develop mode of cogmac_ch_pool ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("change_in"));
      set_msg_handler(pmt::mp("change_in"), boost::bind(&cogmac_ch_pool_impl::next_channel, this, _1 ));
      message_port_register_out(pmt::mp("next_frequency_out"));
      _channel = 0;
      for(int i = 0; i < _channel_number; i++)
      {
        _channel_pool.push_back(_first_channel + i * _channel_gap);
      }
    }

    /*
     * Our virtual destructor.
     */
    cogmac_ch_pool_impl::~cogmac_ch_pool_impl()
    {
    }

    void
    cogmac_ch_pool_impl::next_channel(pmt::pmt_t change_in)
    {
      
      if(_develop_mode)
        std::cout << "+++  cogmac_ch_pool ID: " << _block_id << " next channel +++" << std::endl;
      if(_channel < _channel_number - 1)
        _channel++;
      else
      {
        _channel = 0;
      }
      int frequency = _channel_pool[_channel];
      std::cout << "frequency is: " << frequency << std::endl;
      pmt::pmt_t command = pmt::make_dict(); 
      command = pmt::dict_add(command, pmt::mp("freq"), pmt::mp(frequency));
      command = pmt::dict_add(command, pmt::mp("chan"), pmt::mp(0));
      message_port_pub(pmt::mp("next_frequency_out"), command);
    }

  } /* namespace inets */
} /* namespace gr */

