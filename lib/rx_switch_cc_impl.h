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

#ifndef INCLUDED_INETS_RX_SWITCH_CC_IMPL_H
#define INCLUDED_INETS_RX_SWITCH_CC_IMPL_H

#include <inets/rx_switch_cc.h>

namespace gr {
  namespace inets {

    class rx_switch_cc_impl : public rx_switch_cc
    {
     private:
     int _develop_mode;
     int _my_develop_mode;
     std::vector<int> _develop_mode_list;
     int _is_receiving;
     void kai_guan(pmt::pmt_t spark);

     public:
      rx_switch_cc_impl(std::vector<int> _develop_mode_list);
      ~rx_switch_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_RX_SWITCH_CC_IMPL_H */

