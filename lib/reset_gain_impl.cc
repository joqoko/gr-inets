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
#include "reset_gain_impl.h"

namespace gr {
  namespace inets {

    reset_gain::sptr
    reset_gain::make(int develop_mode, int block_id, int mode, int step, int gain)
    {
      return gnuradio::get_initial_sptr
        (new reset_gain_impl(develop_mode, block_id, mode, step, gain));
    }

    /*
     * The private constructor
     */
    reset_gain_impl::reset_gain_impl(int develop_mode, int block_id, int mode, int step, int gain)
      : gr::block("reset_gain",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _mode(mode),
        _step(step),
        _gain(gain)
    {
      if(_develop_mode)
        std::cout << "develop mode of reset_gain ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("trigger_in"));
      set_msg_handler(pmt::mp("trigger_in"), boost::bind(&reset_gain_impl::output_gain, this, _1 ));
      message_port_register_out(pmt::mp("gain_out"));
      for(int i = 0; i < 25; i = i + _step)
      {
        _gain_list.push_back(i);
      }
    }

    /*
     * Our virtual destructor.
     */
    reset_gain_impl::~reset_gain_impl()
    {
    }

    void
    reset_gain_impl::output_gain(pmt::pmt_t trigger)
    {
      int gain;
      if(!_gain_list.empty() && (_mode == 1 || _mode == 0)) 
      {
        // mode 1: output gain ascendantly
        if(_mode == 1)
        {
          gain = _gain_list.front();
          _gain_list.erase(_gain_list.begin());
        }
        else
        {
          gain = _gain_list.back();
          _gain_list.pop_back(); 
        }
        if(_develop_mode)
          std::cout << "reset_gain block ID " << _block_id << "set new gain to: " << gain << "dB." << std::endl; 
        pmt::pmt_t command = pmt::make_dict();
        command = pmt::dict_add(command, pmt::mp("gain"), pmt::mp(gain));
        message_port_pub(pmt::mp("gain_out"), command);
      }
      else if(_mode != 1 && _mode != 0)
      { 
        if(_develop_mode)
          std::cout << "reset_gain block ID " << _block_id << "set fixed gain to: " << _gain << "dB." << std::endl; 
        gain = _gain;
        pmt::pmt_t command = pmt::make_dict();
        command = pmt::dict_add(command, pmt::mp("gain"), pmt::mp(gain));
        message_port_pub(pmt::mp("gain_out"), command);
      }
    }


  } /* namespace inets */
} /* namespace gr */

