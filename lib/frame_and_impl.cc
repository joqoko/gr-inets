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
#include "frame_and_impl.h"

namespace gr {
  namespace inets {

    frame_and::sptr
    frame_and::make(int develop_mode, int block_id, int output_mode)
    {
      return gnuradio::get_initial_sptr
        (new frame_and_impl(develop_mode, block_id, output_mode));
    }

    /*
     * The private constructor
     */
    frame_and_impl::frame_and_impl(int develop_mode, int block_id, int output_mode)
      : gr::block("frame_and",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _output_mode(output_mode)
    {
      if(_develop_mode)
        std::cout << "develop_mode of frame_and id: " << _block_id << " is activated." << std::endl;
      message_port_register_out(pmt::mp("frame_out"));
      message_port_register_in(pmt::mp("frame_I_in"));
      set_msg_handler(
        pmt::mp("frame_I_in"),
        boost::bind(&frame_and_impl::frame_I_in, this, _1)
      );
      message_port_register_in(pmt::mp("frame_II_in"));
      set_msg_handler(
        pmt::mp("frame_II_in"),
        boost::bind(&frame_and_impl::frame_II_in, this, _1)
      );
      message_port_register_in(pmt::mp("force_output"));
      set_msg_handler(
        pmt::mp("force_output"),
        boost::bind(&frame_and_impl::force_out, this, _1)
      );
      message_port_register_in(pmt::mp("reset_and"));
      set_msg_handler(
        pmt::mp("reset_and"),
        boost::bind(&frame_and_impl::reset, this, _1)
      );
      _frame_I = pmt::from_long(0);
      _frame_II = pmt::from_long(0);
    }

    /*
     * Our virtual destructor.
     */
    frame_and_impl::~frame_and_impl()
    {
    }

    void
    frame_and_impl::force_out(pmt::pmt_t pmt_in)
    {
      message_port_pub(pmt::mp("expired_frame_out"), pmt_in);
      _frame_I = pmt::from_long(0);
      _frame_II = pmt::from_long(0);
      if(_develop_mode)
        std::cout << "frame_and block ID " << _block_id << " is force to output a frame and reset" << std::endl;
      
    }

    void
    frame_and_impl::reset(pmt::pmt_t pmt_in)
    {
      _frame_I = pmt::from_long(0);
      _frame_II = pmt::from_long(0);
      if(_develop_mode)
        std::cout << "frame_and block ID " << _block_id << " is reset" << std::endl;
    }

    void
    frame_and_impl::frame_I_in(pmt::pmt_t frame_I)
    {
      _frame_I = frame_I;
      if(!pmt::is_integer(_frame_II))
      {
        // output_mode 0: output former
        if(_output_mode == 0)
        {  
          message_port_pub(pmt::mp("frame_out"), _frame_I);
          if(_develop_mode)
            std::cout << "frame_and block ID " << _block_id << " receives two frames and output the former one" << std::endl;
        }
        else
        {  
          message_port_pub(pmt::mp("frame_out"), _frame_II);
          if(_develop_mode)
            std::cout << "frame_and block ID " << _block_id << " receives two frames and output the latter one" << std::endl;
        }
        _frame_I = pmt::from_long(0);
        _frame_II = pmt::from_long(0);
      }
      else
      {
        if(_develop_mode)
          std::cout << "frame_and block ID " << _block_id << " receives frame_I" << std::endl;
      }
    }

    void
    frame_and_impl::frame_II_in(pmt::pmt_t frame_II)
    {
      _frame_II = frame_II;
      if(!pmt::is_integer(_frame_I))
      {
        // output_mode 0: output former
        if(_output_mode == 0)
        {  
          message_port_pub(pmt::mp("frame_out"), _frame_I);
          if(_develop_mode)
            std::cout << "frame_and block ID " << _block_id << " receives two frames and output the former one" << std::endl;
        }
        else
        {  
          message_port_pub(pmt::mp("frame_out"), _frame_II);
          if(_develop_mode)
            std::cout << "frame_and block ID " << _block_id << " receives two frames and output the latter one" << std::endl;
        }
        _frame_I = pmt::from_long(0);
        _frame_II = pmt::from_long(0);
      }
      else
      {
        if(_develop_mode)
          std::cout << "frame_and block ID " << _block_id << " receives frame_II" << std::endl;
      }
    }

  } /* namespace inets */
} /* namespace gr */

