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

#ifndef INCLUDED_INETS_COUNTER_IMPL_H
#define INCLUDED_INETS_COUNTER_IMPL_H

#include <inets/counter.h>

namespace gr {
  namespace inets {

    class counter_impl : public counter
    {
     private:
      int _develop_mode;
      int _counter_id;
      int _counter;
      int _in_counting;
      int _virgin;
      double _start_time;
      void counting(pmt::pmt_t message);
      void start_counting(pmt::pmt_t message);
      void stop_counting(pmt::pmt_t message);

     public:
      counter_impl(int develop_mode, int counter_id, int interval_mode);
      ~counter_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_COUNTER_IMPL_H */

