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

#ifndef INCLUDED_INETS_SLIDE_WINDOW_IMPL_H
#define INCLUDED_INETS_SLIDE_WINDOW_IMPL_H

#include <inets/slide_window.h>
#include <queue>

namespace gr {
  namespace inets {

    class slide_window_impl : public slide_window
    {
     private:
      int _develop_mode;
      int _block_id;
      int _window_size;
      int _protocol;
      int _txed_index;
      int _frame_index_length;
      int _max_index;
      double _bps;
      int _interframe_interval_us;
      std::queue<pmt::pmt_t> _window;  
      void ack_in(pmt::pmt_t ack_in);
      void frame_in(pmt::pmt_t frame_in);
      void transmit_window(std::queue<pmt::pmt_t> window, int index);
      void print_window(std::queue<pmt::pmt_t> window);
       
     public:
      slide_window_impl(int develop_mode, int block_id, int window_size, int protocol, double bps, int interframe_interval_us, int frame_index_length);
      ~slide_window_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_SLIDE_WINDOW_IMPL_H */

