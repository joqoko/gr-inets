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

#ifndef INCLUDED_INETS_GENERAL_TIMEOUT_IMPL_H
#define INCLUDED_INETS_GENERAL_TIMEOUT_IMPL_H

#include <inets/general_timeout.h>
#include <queue>

namespace gr {
  namespace inets {

    class general_timeout_impl : public general_timeout
    {
     private:
      // Nothing to declare in this block.
      int _develop_mode;
      int _block_id;
      bool _in_timeout;
      int _timeout_mode;
      int _output_former;
      double _start_time;
      float _timeout_duration_ms;
      int _system_time_granularity_us;
      pmt::pmt_t _waiting_frame_info;
      void start_timeout(pmt::pmt_t frame_in);
      void countdown_timeout();
      void reset_timeout();

     public:
      general_timeout_impl(int develop_mode, int block_id, float timeout_duration_ms, int system_time_granularity_us, int timeout_mode, int output_former);
      ~general_timeout_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_GENERAL_TIMEOUT_IMPL_H */

