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

#ifndef INCLUDED_INETS_STANDARD_TIMER_IMPL_H
#define INCLUDED_INETS_STANDARD_TIMER_IMPL_H

#include <inets/standard_timer.h>

namespace gr {
  namespace inets {

    class standard_timer_impl : public standard_timer
    {
     private:
      int _develop_mode;
      int _block_id;
      int _disable_timer;
      bool _in_active;
      double _duration_ms;
      pmt::pmt_t _frame_info;
      int _system_time_granularity_us;
      void start_timer(pmt::pmt_t trigger);
      void suspend_timer(pmt::pmt_t trigger);
      void resume_timer(pmt::pmt_t trigger);
      void reset_duration(pmt::pmt_t cmd_in);
      void disable_timer(pmt::pmt_t trigger);
      void countdown_standard_timer();

     public:
      standard_timer_impl(int develop_mode, int block_id, double duration, int system_time_granularity_us);
      ~standard_timer_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_STANDARD_TIMER_IMPL_H */

