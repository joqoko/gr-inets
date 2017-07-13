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

#ifndef INCLUDED_INETS_PARAMETER_LIST_IMPL_H
#define INCLUDED_INETS_PARAMETER_LIST_IMPL_H

#include <inets/parameter_list.h>

namespace gr {
  namespace inets {

    class parameter_list_impl : public parameter_list
    {
     private:
      int _develop_mode;
      int _block_id;
      bool _output_n;
      std::vector<double> _list;
      void kick(pmt::pmt_t cmd_in);

     public:
      parameter_list_impl(int develop_mode, int block_id, const std::vector<double> list);
      ~parameter_list_impl();


    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_PARAMETER_LIST_IMPL_H */

