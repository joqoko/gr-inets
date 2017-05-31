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

#ifndef INCLUDED_INETS_VIRTUAL_CS_IMPL_H
#define INCLUDED_INETS_VIRTUAL_CS_IMPL_H

#include <inets/virtual_cs.h>

namespace gr {
  namespace inets {

    class virtual_cs_impl : public virtual_cs
    {
     private:
      int _develop_mode;
      int _block_id;
      int _nav_us;
      double _last_nav_s;
      int _frame_type;
      int _rts_index;
      int _rts_src_addr;
      int _rts_dest_addr;
      double _timer_bias_s;
      int _system_time_granularity_us;
      pmt::pmt_t _tx_frame;
      void check_nav(pmt::pmt_t command);
      void set_nav(pmt::pmt_t command);
      void countdown_nav();

     public:
      virtual_cs_impl(int develop_mode, int block_id, int system_time_granularity_us);
      ~virtual_cs_impl();

      // Where all the action really happens
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_VIRTUAL_CS_IMPL_H */

