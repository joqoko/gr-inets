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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "cogmac_timing_impl.h"
#include "math.h"
#include <algorithm> 

namespace gr {
  namespace inets {

    cogmac_timing::sptr
    cogmac_timing::make(int develop_mode, int block_id, int frame_length, double bps, float sample_rate, const std::vector<unsigned char> &preamble, int padding, int CCA2_ms, int PU_time_ms, int tx_mode_ms, int rx_mode_ms, int len_mac_hdr, int len_phy_overhead, int inter_fr_ms, int ch_pool_size, int ch_switch_ms)
    {
      return gnuradio::get_initial_sptr
        (new cogmac_timing_impl(develop_mode, block_id, frame_length, bps, sample_rate, preamble, padding, CCA2_ms, PU_time_ms, tx_mode_ms, rx_mode_ms, len_mac_hdr, len_phy_overhead, inter_fr_ms, ch_pool_size, ch_switch_ms));
    }

    /*
     * The private constructor
     */
    cogmac_timing_impl::cogmac_timing_impl(int develop_mode, int block_id, int frame_length, double bps, float sample_rate, const std::vector<unsigned char> &preamble, int padding, int CCA2_ms, int PU_time_ms, int tx_mode_ms, int rx_mode_ms, int len_mac_hdr, int len_phy_overhead, int inter_fr_ms, int ch_pool_size, int ch_switch_ms)
      : gr::block("cogmac_timing",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)), 
        _develop_mode(develop_mode),
        _block_id(block_id),
        _frame_length(frame_length),
        _bps(bps),
        _sample_rate(sample_rate),
        _preamble(preamble), 
        _padding(padding),
        _CCA2_ms(CCA2_ms),
        _PU_time_ms(PU_time_ms),
        _tx_mode_ms(tx_mode_ms),
        _rx_mode_ms(rx_mode_ms),
        _len_mac_hdr(len_mac_hdr),
        _len_phy_overhead(len_phy_overhead),
        _inter_fr_ms(inter_fr_ms),
        _ch_pool_size(ch_pool_size),
        _ch_switch_ms(ch_switch_ms)
    {
      if(_develop_mode)
        std::cout << "develop_mode of cogmac_timing ID: " << _block_id << " is activated." << std::endl;

      message_port_register_in(pmt::mp("trigger_in"));
      set_msg_handler(pmt::mp("trigger_in"), boost::bind(&cogmac_timing_impl::calc, this, _1 ));
      message_port_register_out(pmt::mp("cogmac_config_out"));
      message_port_register_out(pmt::mp("cmd_out"));
    }

    /*
     * Our virtual destructor.
     */
    cogmac_timing_impl::~cogmac_timing_impl()
    {
    }

    void
    cogmac_timing_impl::calc(pmt::pmt_t trigger)
    {
      int CCA1_ms = _CCA2_ms + _tx_mode_ms + _rx_mode_ms;
      double frame_tx_time_ms = double(_frame_length + _len_mac_hdr + _len_phy_overhead) * 8 * 1000 / _bps;

      int N_PU = floor((_PU_time_ms - _rx_mode_ms - _tx_mode_ms + _inter_fr_ms) / (frame_tx_time_ms + _inter_fr_ms));
      int t_probing_ms = N_PU * frame_tx_time_ms + (N_PU - 1) * _inter_fr_ms + _tx_mode_ms + _rx_mode_ms;
      int g_PU = floor(((_ch_pool_size - 1) * (CCA1_ms + _ch_switch_ms) + _ch_switch_ms) / (t_probing_ms + _CCA2_ms));
      int n_re = ceil(((_ch_pool_size - 1) * (CCA1_ms + _ch_switch_ms) + _ch_switch_ms) / (frame_tx_time_ms + _inter_fr_ms) - (g_PU * (_PU_time_ms - _CCA2_ms) - _inter_fr_ms) / (frame_tx_time_ms + _inter_fr_ms));
      int N_Re_fr = g_PU * N_PU + !(n_re<N_PU)?N_PU:n_re + 1;
      
      if(_develop_mode)
      {
        std::cout << "Frame transmission time is " << frame_tx_time_ms << " [ms]" << std::endl;
        std::cout << "CCA1 is " << CCA1_ms << " [ms]" << std::endl;
        std::cout << "CCA2 is " << _CCA2_ms << " [ms]" << std::endl;
        std::cout << "PU allowance time is " << _PU_time_ms << " [ms]" << std::endl;
        std::cout << "TX mode time is " << _tx_mode_ms << " [ms]" << std::endl;
        std::cout << "RX mode time is " << _rx_mode_ms << " [ms]" << std::endl;
        std::cout << "N_PU is " << N_PU << std::endl;
        std::cout << "t_probing is " << t_probing_ms << " [ms]" << std::endl;
        std::cout << "g_PU is " << g_PU << std::endl;
        std::cout << "n_re is " << n_re << std::endl;
        std::cout << "N_Re_fr is " << N_Re_fr << std::endl;
      }
      pmt::pmt_t cogmac_cmd = pmt::make_dict();
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("frame_time_ms"), pmt::from_double(frame_tx_time_ms));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("CCA1_ms"), pmt::from_long(CCA1_ms));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("CCA2_ms"), pmt::from_long(_CCA2_ms));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("PU_time_ms"), pmt::from_long(_PU_time_ms));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("tx_mode_ms"), pmt::from_long(_tx_mode_ms));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("rx_mode_ms"), pmt::from_long(_rx_mode_ms));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("N_PU"), pmt::from_long(N_PU));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("t_probing_ms"), pmt::from_long(t_probing_ms));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("g_PU"), pmt::from_long(g_PU));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("n_re"), pmt::from_long(n_re));
      cogmac_cmd = pmt::dict_add(cogmac_cmd, pmt::string_to_symbol("N_Re_fr"), pmt::from_long(N_Re_fr));
      message_port_pub(pmt::mp("cogmac_config_out"), cogmac_cmd);
      boost::this_thread::sleep(boost::posix_time::microseconds(100000));
      message_port_pub(pmt::mp("cmd_out"), trigger);
    }

  } /* namespace inets */
} /* namespace gr */

