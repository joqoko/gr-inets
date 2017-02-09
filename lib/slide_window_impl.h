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
      int _protocol;
      int _window_size;
      int _n_window;
      int _start;
      float _timeout_duration_ms;
      int _system_time_granularity_us;
      int _samp_rate;
      int _sps;
      double _bps;
      std::queue<double> _timer;
      std::queue<pmt::pmt_t> _tx_window;
      std::queue<pmt::pmt_t> _rx_window;
      struct frame_in_window{
        double current_time;
        pmt::pmt_t frame;
	int frame_index;
        frame_in_window *next;
	frame_in_window *last;
      };
      frame_in_window *_tx_win;
      frame_in_window *_rx_win;
      void handle_data(pmt::pmt_t frame_in);
      void handle_ack(pmt::pmt_t frame_in);
      void print_index(frame_in_window *first);
      void window_insert(frame_in_window *first, pmt::pmt_t frame);
      int window_count(frame_in_window *first);

     public:
      slide_window_impl(int develop_mode, int block_id, int protocol, int window_size, float timeout_duration_ms, int system_time_granularity_us, int samp_rate, int sps, double bps);
      ~slide_window_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_SLIDE_WINDOW_IMPL_H */

