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

#ifndef INCLUDED_INETS_CARRIER_SENSING_IMPL_H
#define INCLUDED_INETS_CARRIER_SENSING_IMPL_H

#include <inets/carrier_sensing.h>

namespace gr {
  namespace inets {

    class carrier_sensing_impl : public carrier_sensing
    {
     private:
      // Nothing to declare in this block.
      int _develop_mode;
      int _block_id;
      int _cs_mode;
      int _system_time_granularity_us;
      int _nf_initial_n;
      bool _in_cca;
      bool _cca;
      bool _stop_sensing;
      std::vector<double> _noise_floor;
      double _cs_duration;
      double _cs_time; 
      pmt::pmt_t _frame_info;
      float _cs_threshold;
      int _rx_sensitivity_dB;
      void start_sensing(pmt::pmt_t frame_info);
      void stop_sensing(pmt::pmt_t frame_info);
      void sensing(pmt::pmt_t power_in);
      void kill_sensing(pmt::pmt_t power_info);
      void countdown_sensing();
      void oneshot_sensing();
      void continuous_sensing();
      void unlimited_sensing();

     public:
      carrier_sensing_impl(int develop_mode, int block_id, int cs_mode, double cs_duration, float cs_threshold, int system_time_granularity_us, int nf_initial_n, int rx_sensitivity_dB);
      ~carrier_sensing_impl();

    };


  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_CARRIER_SENSING_IMPL_H */

