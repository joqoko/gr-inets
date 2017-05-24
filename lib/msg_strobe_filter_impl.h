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

#ifndef INCLUDED_INETS_MSG_STROBE_FILTER_IMPL_H
#define INCLUDED_INETS_MSG_STROBE_FILTER_IMPL_H

#include <inets/msg_strobe_filter.h>

namespace gr {
  namespace inets {

    class msg_strobe_filter_impl : public msg_strobe_filter
    {
     private:
      bool _started;
      int _start_next_time_s;
      int _system_time_granularity_us;
      void check_start(pmt::pmt_t msg);

     public:
      msg_strobe_filter_impl(int start_next_time_s, int system_time_granularity_us);
      ~msg_strobe_filter_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_MSG_STROBE_FILTER_IMPL_H */

