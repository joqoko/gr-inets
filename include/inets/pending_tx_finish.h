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


#ifndef INCLUDED_INETS_PENDING_TX_FINISH_H
#define INCLUDED_INETS_PENDING_TX_FINISH_H

#include <inets/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace inets {

    /*!
     * \brief <+description of block+>
     * \ingroup inets
     *
     */
    class INETS_API pending_tx_finish : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<pending_tx_finish> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of inets::pending_tx_finish.
       *
       * To avoid accidental use of raw pointers, inets::pending_tx_finish's
       * constructor is in a private implementation
       * class. inets::pending_tx_finish::make is the public interface for
       * creating new instances.
       */
      static sptr make(int develop_mode, int block_id, int system_time_granularity_us, float sample_rate, const std::string& lengthtagname, double interframe_interval_s, int record_on);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_PENDING_TX_FINISH_H */

