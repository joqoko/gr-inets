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

#ifndef INCLUDED_INETS_IFS_IMPL_H
#define INCLUDED_INETS_IFS_IMPL_H

#include <inets/IFS.h>

namespace gr {
  namespace inets {

    class IFS_impl : public IFS
    {
     private:
      int _develop_mode;
      int _block_id;
      int _slot_time;
      int _SIFS;
      int _interval_type;
      int _customized_IFS;
      float _cs_threshold;
      int _AIFS_ac;
      bool _in_cca;
      float _IFS_duration;
      double _wait_time;
      pmt::pmt_t _frame_info;
      int _system_time_granularity_us;
      void start_IFS(pmt::pmt_t frame_in);
      void countdown_sensing();

     public:
      IFS_impl(int develop_mode, int block_id, int SIFS, int slot_time, int interval_type, int customized_IFS, int AIFS_ac, float cs_threshold, int system_time_granularity_us);
      ~IFS_impl();


    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_IFS_IMPL_H */

