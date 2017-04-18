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

#ifndef INCLUDED_INETS_FRAME_BUFFER_IMPL_H
#define INCLUDED_INETS_FRAME_BUFFER_IMPL_H

#include <inets/frame_buffer.h>
#include <queue>

namespace gr {
  namespace inets {

    class frame_buffer_impl : public frame_buffer
    {
     private:
      int _develop_mode;
      int _block_id;
      int _buffer_size;
      int _keep_dequeue_state;
      int _dequeue_when_available;
      int _auto_dequeue_first;
      int _dequeue_first;
      int _auto_dequeue_full;
      int _show_am_empty;
//      int _output_dequeue_element;
      std::queue<pmt::pmt_t> _buffer;
      void enqueue(pmt::pmt_t enqueue_element);
      void indicate(pmt::pmt_t trigger);
      void dequeue(pmt::pmt_t dequeue_request);
//      void preview(pmt::pmt_t preview_request);
      void flush(pmt::pmt_t flush_request);

     public:
      frame_buffer_impl(int develop_mode, int block_id, int buffer_size, int auto_dequeue_first, int keep_dequeue_state, int auto_dequeue_full);
      ~frame_buffer_impl();
    };
  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_FRAME_BUFFER_IMPL_H */

