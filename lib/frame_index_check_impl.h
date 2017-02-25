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

#ifndef INCLUDED_INETS_FRAME_INDEX_CHECK_IMPL_H
#define INCLUDED_INETS_FRAME_INDEX_CHECK_IMPL_H

#include <inets/frame_index_check.h>

namespace gr {
  namespace inets {

    class frame_index_check_impl : public frame_index_check
    {
     private:
      int _develop_mode;
      int _block_id;
      int _difference;
      pmt::pmt_t _frame_A;
      pmt::pmt_t _frame_B;
      int _output_fail;
      int _no_wait;
      int _reset_1st;
      int _length_frame_index;
      void start_check(pmt::pmt_t frame);
      void compare();

     public:
      frame_index_check_impl(int develop_mode, int block_id, int difference, int no_wait, int output_fail, int reset_1st, int length_frame_index);
      ~frame_index_check_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAME_INDEX_CHECK_IMPL_H */

