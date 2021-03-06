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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "address_check_cpp_impl.h"

namespace gr {
  namespace inets {

    address_check_cpp::sptr
    address_check_cpp::make(int develop_mode, int block_id, int my_address, int apply_address_check)
    {
      return gnuradio::get_initial_sptr
        (new address_check_cpp_impl(develop_mode, block_id, my_address, apply_address_check));
    }

    /*
     * The private constructor
     */
    address_check_cpp_impl::address_check_cpp_impl(int develop_mode, int block_id, int my_address, int apply_address_check)
      : gr::block("address_check_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _block_id(block_id),
        _develop_mode(develop_mode),
        _my_address(my_address),
        _apply_address_check(apply_address_check)
    {
      if(_develop_mode == 1)
        std::cout << "develop_mode of address_check_cpp ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_info_in"));
      message_port_register_out(pmt::mp("frame_info_out"));
      set_msg_handler(pmt::mp("frame_info_in"), boost::bind(&address_check_cpp_impl::check_address, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    address_check_cpp_impl::~address_check_cpp_impl()
    {
    }

    void
    address_check_cpp_impl::check_address(pmt::pmt_t frame_info)
    {
      if(_apply_address_check)
      {
        if(_develop_mode == 1)
        {
          std::cout << "++++++++   address_check_cpp ID: " << _block_id << "   +++++++++" << std::endl;
        }
        pmt::pmt_t not_found;
        int received_frame_address = pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("destination_address"), not_found));
        int is_my_address = (_my_address == received_frame_address);
        if(_develop_mode == 1)
          std::cout << "My address is " << _my_address << " and rx frame address is " << received_frame_address << ". Frame check is: " << is_my_address << std::endl;
        frame_info = pmt::dict_delete(frame_info, pmt::string_to_symbol("address_check"));
        frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("address_check"), pmt::from_long(is_my_address));
      }
      else
        if(_develop_mode == 1)
          std::cout << "+++++++   address_check_cpp ID: " << _block_id << " is off   +++++++" << std::endl;
      message_port_pub(pmt::mp("frame_info_out"), frame_info);
      if(_develop_mode == 2)
      {
        struct timeval t; 
        gettimeofday(&t, NULL);
        double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        std::cout << "* address check ID: " << _block_id << " finish header analysis at time " << current_time << " s" << std::endl;
      }
    }

  } /* namespace inets */
} /* namespace gr */

