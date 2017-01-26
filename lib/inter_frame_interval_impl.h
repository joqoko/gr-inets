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

#ifndef INCLUDED_INETS_INTER_FRAME_INTERVAL_IMPL_H
#define INCLUDED_INETS_INTER_FRAME_INTERVAL_IMPL_H

#include <inets/inter_frame_interval.h>

namespace gr {
  namespace inets {

    class inter_frame_interval_impl : public inter_frame_interval
    {
     private:
      int _develop_mode;
      int _block_id;
      int _slot_time;
      int _SIFS;
      int _interval_type;
      int _customized_IFS;
      int _AIFS_ac;
      double _wait_time;
      int _system_time_granularity_us;
      void wait_for(pmt::pmt_t frame_in);
      void countdown_waiting();

     public:
      inter_frame_interval_impl(int develop_mode, int block_id, int SIFS, int slot_time, int interval_type, int customized_IFS, int AIFS_ac, int system_time_granularity_us);
      ~inter_frame_interval_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_INTER_FRAME_INTERVAL_IMPL_H */

