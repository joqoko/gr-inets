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


#ifndef INCLUDED_INETS_PACKET_TX_TIMING_C_H
#define INCLUDED_INETS_PACKET_TX_TIMING_C_H

#include <inets/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace inets {

    /*!
     * \brief <+description of block+>
     * \ingroup inets
     *
     */
    class INETS_API packet_tx_timing_c : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<packet_tx_timing_c> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of inets::packet_tx_timing_c.
       *
       * To avoid accidental use of raw pointers, inets::packet_tx_timing_c's
       * constructor is in a private implementation
       * class. inets::packet_tx_timing_c::make is the public interface for
       * creating new instances.
       */
      static sptr make(float sample_rate, const std::string& lengthtagname="packet_len");
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_PACKET_TX_TIMING_C_H */

