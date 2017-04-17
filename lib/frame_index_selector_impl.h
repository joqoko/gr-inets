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

#ifndef INCLUDED_INETS_FRAME_INDEX_SELECTOR_IMPL_H
#define INCLUDED_INETS_FRAME_INDEX_SELECTOR_IMPL_H

#include <inets/frame_index_selector.h>

namespace gr {
  namespace inets {

    class frame_index_selector_impl : public frame_index_selector
    {
     private:
      int _develop_mode;
      int _block_id;
      const std::vector<unsigned int> _selected_index;
      int _output_unselected;
      void check_index(pmt::pmt_t frame_in);

     public:
      frame_index_selector_impl(int develop_mode, int block_id, const std::vector<unsigned int> selected_index, int output_unselected);
      ~frame_index_selector_impl();
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAME_INDEX_SELECTOR_IMPL_H */

