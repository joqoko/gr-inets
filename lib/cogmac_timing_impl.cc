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

namespace gr {
  namespace inets {

    cogmac_timing::sptr
    cogmac_timing::make(int develop_mode, int block_id, int frame_length, double bps, float sample_rate, const std::vector<unsigned char> &preamble, int padding, int CCA2_ms, int PU_time_ms, int tx_mode_ms, int rx_mode_ms)
    {
      return gnuradio::get_initial_sptr
        (new cogmac_timing_impl(develop_mode, block_id, frame_length, bps, sample_rate, preamble, padding, CCA2_ms, PU_time_ms, tx_mode_ms, rx_mode_ms));
    }

    /*
     * The private constructor
     */
    cogmac_timing_impl::cogmac_timing_impl(int develop_mode, int block_id, int frame_length, double bps, float sample_rate, const std::vector<unsigned char> &preamble, int padding, int CCA2_ms, int PU_time_ms, int tx_mode_ms, int rx_mode_ms)
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
        _rx_mode_ms(rx_mode_ms)
    {
      if(_develop_mode)
        std::cout << "develop_mode of cogmac_timing ID: " << _block_id << " is activated." << std::endl;

      message_port_register_in(pmt::mp("trigger_in"));
      set_msg_handler(pmt::mp("trigger_in"), boost::bind(&cogmac_timing_impl::calc, this, _1 ));
      message_port_register_out(pmt::mp("packet_out"));

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
      message_port_pub(pmt::mp("packet_out"), pmt::make_dict());
    }

  } /* namespace inets */
} /* namespace gr */

