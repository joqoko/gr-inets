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

#ifndef INCLUDED_INETS_IDLE_IMPL_H
#define INCLUDED_INETS_IDLE_IMPL_H

#include <inets/idle.h>
#include <queue>

namespace gr {
  namespace inets {

    class idle_impl : public idle
    {
     private:
      std::vector<int> _develop_mode_list;
      float _experiment_duration_s;
      int _max_buffer_size; 
      int _develop_mode; 
      int _my_develop_mode; 
      int _my_address; 
      bool _experiment_running;
      bool _in_idle;
      std::queue<pmt::pmt_t> _tx_buff;
      int _max_num_retransmission;
      void reset_idle(pmt::pmt_t data);
      void state_transition(pmt::pmt_t data);

     public:
      idle_impl(std::vector<int> develop_mode_list, float experiment_duration_s, int max_num_retransmission, int max_buffer_size, int my_address);
      ~idle_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_IDLE_IMPL_H */

