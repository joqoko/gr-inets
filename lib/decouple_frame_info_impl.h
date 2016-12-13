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

#ifndef INCLUDED_INETS_DECOUPLE_FRAME_INFO_IMPL_H
#define INCLUDED_INETS_DECOUPLE_FRAME_INFO_IMPL_H

#include <inets/decouple_frame_info.h>

namespace gr {
  namespace inets {

    class decouple_frame_info_impl : public decouple_frame_info
    {
     private:
      std::vector<int> _develop_mode_list;
      int _my_develop_mode;
      int _develop_mode;
      void decoupling(pmt::pmt_t frame_cluster);
     public:
      decouple_frame_info_impl(std::vector<int> develop_mode_list);
      ~decouple_frame_info_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_DECOUPLE_FRAME_INFO_IMPL_H */

