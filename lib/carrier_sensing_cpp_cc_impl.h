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

#ifndef INCLUDED_INETS_CARRIER_SENSING_CPP_CC_IMPL_H
#define INCLUDED_INETS_CARRIER_SENSING_CPP_CC_IMPL_H

#include <inets/carrier_sensing_cpp_cc.h>

namespace gr {
  namespace inets {

    class carrier_sensing_cpp_cc_impl : public carrier_sensing_cpp_cc
    {
     private:
      // Nothing to declare in this block.
      bool _in_cca;
      float _cs_duration;
      double _cs_time; 
      float _cs_threshold;

     public:
      carrier_sensing_cpp_cc_impl(float cs_duration, float cs_threshold);
      ~carrier_sensing_cpp_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
	 gr_vector_const_void_star &input_items,
	 gr_vector_void_star &output_items);
      void start_sensing(pmt::pmt_t msg);
      void countdown_sensing();
    };


  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_CARRIER_SENSING_CPP_CC_IMPL_H */

