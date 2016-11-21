
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

#ifndef INCLUDED_INETS_IDLE_CPP_IMPL_H
#define INCLUDED_INETS_IDLE_CPP_IMPL_H

#include <inets/idle_cpp.h>

namespace gr {
  namespace inets {

    class idle_cpp_impl : public idle_cpp
    {
     private:
      bool _in_idle;
      bool _experiment_running;
      int _experiment_duration;
      void activate_idle(pmt::pmt_t msg);
      void handler_data_from_network_layer(pmt::pmt_t msg);
      void handler_good_packet_from_phy(pmt::pmt_t msg);

     public:
      idle_cpp_impl(int experiment_duration);
      ~idle_cpp_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_IDLE_CPP_IMPL_H */

