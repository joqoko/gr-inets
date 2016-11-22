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

#ifndef INCLUDED_INETS_PACKET_TX_TIMING_C_IMPL_H
#define INCLUDED_INETS_PACKET_TX_TIMING_C_IMPL_H

#include <inets/packet_tx_timing_c.h>

namespace gr {
  namespace inets {

    class packet_tx_timing_c_impl : public packet_tx_timing_c
    {
     private:
      // Nothing to declare in this block.
      int _sample_rate;

     public:
      packet_tx_timing_c_impl(float sample_rate, const std::string& lengthtagname);
      ~packet_tx_timing_c_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_PACKET_TX_TIMING_C_IMPL_H */

