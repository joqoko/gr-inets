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


#ifndef INCLUDED_INETS_TX_BUFFER_H
#define INCLUDED_INETS_TX_BUFFER_H

#include <inets/api.h>
#include <gnuradio/block.h>
#include <gnuradio/msg_queue.h>

namespace gr {
  namespace inets {

    /*!
     * \brief <+description of block+>
     * \ingroup inets
     *
     */
    class INETS_API tx_buffer : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<tx_buffer> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of inets::tx_buffer.
       *
       * To avoid accidental use of raw pointers, inets::tx_buffer's
       * constructor is in a private implementation
       * class. inets::tx_buffer::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::vector<int> _develop_mode_list, int max_buffer_size, int policy);
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_TX_BUFFER_H */

