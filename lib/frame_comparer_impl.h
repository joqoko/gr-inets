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

#ifndef INCLUDED_INETS_FRAME_COMPARER_IMPL_H
#define INCLUDED_INETS_FRAME_COMPARER_IMPL_H

#include <inets/frame_comparer.h>

namespace gr {
  namespace inets {

    class frame_comparer_impl : public frame_comparer
    {
     private:
      int _develop_mode;
      int _block_id;
      int _what_to_compare;
      int _single_input;
      pmt::pmt_t _frame_A;
      pmt::pmt_t _frame_B;

      void start_compare_A(pmt::pmt_t frame_A);
      void start_compare_B(pmt::pmt_t frame_B);
      void compare();
     
     public:
      frame_comparer_impl(int develop_mode, int block_id, int what_to_compare, int single_input);
      ~frame_comparer_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAME_COMPARER_IMPL_H */

