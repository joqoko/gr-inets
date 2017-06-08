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


#ifndef INCLUDED_INETS_COGMAC_TIMING_H
#define INCLUDED_INETS_COGMAC_TIMING_H

#include <inets/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace inets {

    /*!
     * \brief <+description of block+>
     * \ingroup inets
     *
     */
    class INETS_API cogmac_timing : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<cogmac_timing> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of inets::cogmac_timing.
       *
       * To avoid accidental use of raw pointers, inets::cogmac_timing's
       * constructor is in a private implementation
       * class. inets::cogmac_timing::make is the public interface for
       * creating new instances.
       */
      static sptr make(int develop_mode, int block_id, int frame_length, double bps, float sample_rate, const std::vector<unsigned char> &preamble, int padding, int CCA2_ms, int PU_time_ms, int tx_mode_ms, int rx_mode_ms);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_COGMAC_TIMING_H */

