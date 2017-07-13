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

#ifndef INCLUDED_INETS_NUMBER_RECORDER_IMPL_H
#define INCLUDED_INETS_NUMBER_RECORDER_IMPL_H

#include <inets/number_recorder.h>

namespace gr {
  namespace inets {

    class number_recorder_impl : public number_recorder
    {
     private:
      int _develop_mode;
      int _block_id;
      int _name_with_timestamp;
      std::string _recorder_name;
      std::string _file_name_str;
      void recording(pmt::pmt_t cmd_in);
      void change_file_name(pmt::pmt_t new_name);


     public:
      number_recorder_impl(int develop_mode, int block_id, std::string recorder_name, std::string record_path, int name_with_timestamp);
      ~number_recorder_impl();

      // Where all the action really happens
    };

  } // namespace inets
} // namespace gr

#endif /* INCLUDED_INETS_NUMBER_RECORDER_IMPL_H */

