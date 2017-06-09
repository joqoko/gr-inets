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

#ifndef INCLUDED_INETS_COGMAC_TIMING_IMPL_H
#define INCLUDED_INETS_COGMAC_TIMING_IMPL_H

#include <inets/cogmac_timing.h>

namespace gr {
  namespace inets {

    class cogmac_timing_impl : public cogmac_timing
    {
     private:
      int _develop_mode;
      int _block_id;
      int _frame_length;
      int _bps;
      int _sample_rate;
      int _padding;
      std::vector<unsigned char> _preamble;
      int _CCA2_ms;
      int _PU_time_ms;
      int _tx_mode_ms;
      int _rx_mode_ms;
      int _len_mac_hdr;
      int _len_phy_overhead;
      int _inter_fr_ms;
      int _ch_pool_size;
      int _ch_switch_ms;
      void calc(pmt::pmt_t trigger);

     public:
      cogmac_timing_impl(int develop_mode, int block_id, int frame_length, double bps, float sample_rate, const std::vector<unsigned char> &preamble, int padding, int CCA2_ms, int PU_time_ms, int tx_mode_ms, int rx_mode_ms, int len_mac_hdr, int len_phy_overhead, int inter_fr_ms, int ch_pool_size, int ch_switch_ms);
      ~cogmac_timing_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_COGMAC_TIMING_IMPL_H */

