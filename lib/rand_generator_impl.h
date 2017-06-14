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

#ifndef INCLUDED_INETS_RAND_GENERATOR_IMPL_H
#define INCLUDED_INETS_RAND_GENERATOR_IMPL_H

#include <inets/rand_generator.h>

namespace gr {
  namespace inets {

    class rand_generator_impl : public rand_generator
    {
     private:
      int _develop_mode;
      int _block_id;
      int _mode;
      double _min;
      double _max;
      double _distribution;
      void creation(pmt::pmt_t cmd_in);

     public:
      rand_generator_impl(int develop_mode, int block_id, int mode, double min, double max, int distribution);
      ~rand_generator_impl();

    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_RAND_GENERATOR_IMPL_H */

