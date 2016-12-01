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

#ifndef INCLUDED_INETS_T_CONTROL_TX_CC_IMPL_H
#define INCLUDED_INETS_T_CONTROL_TX_CC_IMPL_H

#include <inets/t_control_tx_cc.h>

namespace gr {
  namespace inets {

    class t_control_tx_cc_impl : public t_control_tx_cc
    {
     private:
      // Nothing to declare in this block.
      int _develop_mode;
      double _last_tx_time;
      double _bps;
      tag_t _packet_len_tag;
      int process_tags_info(std::vector <tag_t> tags);


     public:
      t_control_tx_cc_impl(int develop_mode, double bps);
      ~t_control_tx_cc_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_T_CONTROL_TX_CC_IMPL_H */

