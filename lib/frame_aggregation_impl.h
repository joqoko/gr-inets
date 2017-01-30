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

#ifndef INCLUDED_INETS_FRAME_AGGREGATION_IMPL_H
#define INCLUDED_INETS_FRAME_AGGREGATION_IMPL_H

#include <inets/frame_aggregation.h>

namespace gr {
  namespace inets {

    class frame_aggregation_impl : public frame_aggregation
    {
     private:
      int _develop_mode;
      int _block_id;
      int _number_aggregation;
      int _aggregation_type;
      int _aggregation_n;
      int _frame_type;
      pmt::pmt_t _frame_info;
      pmt::pmt_t _aggregated_frame;
      void aggregating(pmt::pmt_t subframe);
      void create_ampdu(pmt::pmt_t subframe);
      void create_amsdu(pmt::pmt_t subframe);
      void insert_ampdu(pmt::pmt_t subframe);
      void insert_amsdu(pmt::pmt_t subframe);

     public:
      frame_aggregation_impl(int develop_mode, int block_id, int aggregation_type);
      ~frame_aggregation_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAME_AGGREGATION_IMPL_H */

