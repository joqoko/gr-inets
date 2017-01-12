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
#include "send_impl.h"

namespace gr {
  namespace inets {

    send::sptr
    send::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new send_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    send_impl::send_impl(int develop_mode, int block_id)
      : gr::hier_block2("send",
              gr::io_signature::make(<+MIN_IN+>, <+MAX_IN+>, sizeof(<+ITYPE+>)),
              gr::io_signature::make(<+MIN_OUT+>, <+MAX_OUT+>, sizeof(<+OTYPE+>)))
    {
      connect(self(), 0, d_firstblock, 0);
      // connect other blocks
      connect(d_lastblock, 0, self(), 0);
    }

    /*
     * Our virtual destructor.
     */
    send_impl::~send_impl()
    {
    }


  } /* namespace inets */
} /* namespace gr */

