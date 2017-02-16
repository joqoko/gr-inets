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


#ifndef INCLUDED_INETS_FRAME_TYPE_CHECK_H
#define INCLUDED_INETS_FRAME_TYPE_CHECK_H

#include <inets/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace inets {

    /*!
     * \brief <+description of block+>
     * \ingroup inets
     *
     */
    class INETS_API frame_type_check : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<frame_type_check> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of inets::frame_type_check.
       *
       * To avoid accidental use of raw pointers, inets::frame_type_check's
       * constructor is in a private implementation
       * class. inets::frame_type_check::make is the public interface for
       * creating new instances.
       */
      static sptr make(int develop_mode, int block_id, int data_frame, int ack_frame, int beacon_frame, int rts_frame, int cts_frame, int ampdu_frame, int amsdu_frame, int ampdu_subframe, int amsdu_subframe, int other_frame);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAME_TYPE_CHECK_H */

