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

#ifndef INCLUDED_INETS_GENERAL_TIMER_IMPL_H
#define INCLUDED_INETS_GENERAL_TIMER_IMPL_H

#include <inets/general_timer.h>

namespace gr {
  namespace inets {

    class general_timer_impl : public general_timer
    {
     private:
      int _develop_mode;
      int _block_id;
      int _timer_type;
      int _in_active;
      int _duration_ms;
      int _system_time_granularity_us;
      void countdown_timer();
      void start_timer(pmt::pmt_t trigger);
   
     public:
      general_timer_impl(int develop_mode, int block_id, int timer_type, int duration_ms, int system_time_granularity_us);
      ~general_timer_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_GENERAL_TIMER_IMPL_H */
