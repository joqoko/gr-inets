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
#include "frame_counter_impl.h"

namespace gr {
  namespace inets {

    frame_counter::sptr
    frame_counter::make(int develop_mode, int block_id, int counts, int mode)
    {
      return gnuradio::get_initial_sptr
        (new frame_counter_impl(develop_mode, block_id, counts, mode));
    }

    /*
     * The private constructor
     */
    frame_counter_impl::frame_counter_impl(int develop_mode, int block_id, int counts, int mode)
      : gr::block("frame_counter",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _counts(counts),
        _mode(mode),
        _current_count(0)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_counter id: " << _block_id << " is activated." << std::endl;
      message_port_register_out(pmt::mp("select_out"));
      message_port_register_out(pmt::mp("unselect_out"));
      message_port_register_in(pmt::mp("counts_in"));
      set_msg_handler(
        pmt::mp("counts_in"),
        boost::bind(&frame_counter_impl::counting, this, _1)
      );
      message_port_register_in(pmt::mp("reset_in"));
      set_msg_handler(
        pmt::mp("reset_in"),
        boost::bind(&frame_counter_impl::reset, this, _1)
      );
      message_port_register_in(pmt::mp("set_n_counts_in"));
      set_msg_handler(
        pmt::mp("set_n_counts_in"),
        boost::bind(&frame_counter_impl::set_counts, this, _1)
      );
    }

    /*
     * Our virtual destructor.
     */
    frame_counter_impl::~frame_counter_impl()
    {
    }

    void
    frame_counter_impl::set_counts(pmt::pmt_t pmt_in)
    {
      if(pmt::is_integer(pmt_in))
      {
        _counts = pmt::to_long(pmt_in);
        if(_develop_mode)
          std::cout << "the number of counts in frame_counter block ID " << _block_id << " is reset to " << _counts << std::endl;
      }
      else if(pmt::dict_has_key(pmt_in, pmt::mp("N_PU")))
      {
        pmt::pmt_t not_found;
        _counts = pmt::to_long(pmt::dict_ref(pmt_in, pmt::string_to_symbol("N_PU"), not_found));
        if(_develop_mode)
          std::cout << "the number of counts in frame_counter block ID " << _block_id << " is reset to " << _counts << " according to CogMAC protocol " << std::endl;
      }
      else   
      {
        std::cout << "error: frame_counter block ID " << _block_id << " can only reassign number of replicates to a integer number." << std::endl;
      }
    }

    void
    frame_counter_impl::reset(pmt::pmt_t pmt_in)
    {
      if(_mode == 0)
      {
        if(_develop_mode)
          std::cout << "current counts is reset to 0 " << std::endl;
        _current_count = 0;
      }
      else
        _current_count = _counts;
    }

    void
    frame_counter_impl::counting(pmt::pmt_t pmt_in)
    {
      // normal mode
      if(_mode == 0)
      {
        _current_count++;
        if(_current_count < _counts)
        {
          if(_develop_mode)
            std::cout << "current counts is :" << _current_count << ". target is " << _counts << std::endl;
          message_port_pub(pmt::mp("unselect_out"), pmt_in);
        }
        else
        {
          if(_develop_mode)
            std::cout << "current counts is :" << _current_count << ". target is " << _counts << std::endl;
          message_port_pub(pmt::mp("select_out"), pmt_in);
        } 
      }
      // countdown mode
      else
      {
        if(_current_count > 0)
        {
          _current_count--;
          message_port_pub(pmt::mp("unfinished_out"), pmt_in);
        }
        else
        {
          message_port_pub(pmt::mp("finished_out"), pmt_in);
        } 
      }
    }

  } /* namespace inets */
} /* namespace gr */

