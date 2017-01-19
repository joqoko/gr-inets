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

#ifndef INCLUDED_INETS_BACKOFF_IMPL_H
#define INCLUDED_INETS_BACKOFF_IMPL_H

#include <inets/backoff.h>

namespace gr {
  namespace inets {

    class backoff_impl : public backoff
    {
     private:
       int _backoff_time_unit_ms;
       int _max_n_backoff;
       int _develop_mode;
       int _block_id;
       int _min_backoff_ms;
       int _max_backoff_ms;
       int _backoff_time_ms;
       int _backoff_type;
       pmt::pmt_t _frame_info;
       int _n_backoff;
       void start_backoff(pmt::pmt_t frame_info);
       void countdown_exp_backoff();
       void countdown_const_backoff();
       void countdown_random_backoff();

     public:
      backoff_impl(int develop_mode, int block_id, int backoff_type, int backoff_time_unit_ms, int max_n_backoff, int min_backoff_ms, int max_backoff_ms, int backoff_time);
      ~backoff_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_BACKOFF_IMPL_H */

