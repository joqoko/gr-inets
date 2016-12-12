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
#include "null_message_source_impl.h"

namespace gr {
  namespace inets {

    null_message_source::sptr
    null_message_source::make()
    {
      return gnuradio::get_initial_sptr
        (new null_message_source_impl());
    }

    /*
     * The private constructor
     */
    null_message_source_impl::null_message_source_impl()
      : gr::block("null_message_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
      message_port_register_out(pmt::mp("null_message_out"));
    }

    /*
     * Our virtual destructor.
     */
    null_message_source_impl::~null_message_source_impl()
    {
    }

  } /* namespace inets */
} /* namespace gr */

