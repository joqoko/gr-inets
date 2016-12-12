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

#ifndef INCLUDED_INETS_NULL_MESSAGE_SOURCE_IMPL_H
#define INCLUDED_INETS_NULL_MESSAGE_SOURCE_IMPL_H

#include <inets/null_message_source.h>

namespace gr {
  namespace inets {

    class null_message_source_impl : public null_message_source
    {
     private:
      // Nothing to declare in this block.

     public:
      null_message_source_impl();
      ~null_message_source_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_NULL_MESSAGE_SOURCE_IMPL_H */

