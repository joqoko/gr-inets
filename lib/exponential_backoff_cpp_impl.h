/* -*- c++ -*- */
/* 
 * Copyright 2016 <+inets+>.
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

#ifndef INCLUDED_INETS_EXPONENTIAL_BACKOFF_CPP_IMPL_H
#define INCLUDED_INETS_EXPONENTIAL_BACKOFF_CPP_IMPL_H

#include <inets/exponential_backoff_cpp.h>

namespace gr {
  namespace inets {

    class exponential_backoff_cpp_impl : public exponential_backoff_cpp
    {
     private:
       int _backoff_time_unit_ms;
       int _max_n_backoff;
       int _develop_mode;
       int _block_id;
       int _min_backoff_ms;
       pmt::pmt_t _frame_info;
       int _n_backoff;
       void start_backoff(pmt::pmt_t frame_info);
       void countdown_backoff();

     public:
      exponential_backoff_cpp_impl(int develop_mode, int block_id, int backoff_time_unit_ms, int max_n_backoff, int min_backoff_ms);
      ~exponential_backoff_cpp_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_EXPONENTIAL_BACKOFF_CPP_IMPL_H */

