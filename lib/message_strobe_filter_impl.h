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

#ifndef INCLUDED_INETS_MESSAGE_STROBE_FILTER_IMPL_H
#define INCLUDED_INETS_MESSAGE_STROBE_FILTER_IMPL_H

#include <inets/message_strobe_filter.h>

namespace gr {
  namespace inets {

    class message_strobe_filter_impl : public message_strobe_filter
    {
     private:
      bool _started;
      void filtering(pmt::pmt_t msg); 

     public:
      message_strobe_filter_impl();
      ~message_strobe_filter_impl();
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_MESSAGE_STROBE_FILTER_IMPL_H */
