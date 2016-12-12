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
    address_check_cpp::make(std::vector<int> develop_mode_list, int my_address, int apply_address_check)
    {
      return gnuradio::get_initial_sptr
        (new address_check_cpp_impl(develop_mode_list, my_address, apply_address_check));
    }

    /*
     * The private constructor
     */
    address_check_cpp_impl::address_check_cpp_impl(std::vector<int> develop_mode_list, int my_address, int apply_address_check)
      : gr::block("address_check_cpp",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _my_develop_mode(13),
        _develop_mode_list(develop_mode_list),
        _my_address(my_address),
        _apply_address_check(apply_address_check)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of address_check_cpp is activated." << std::endl;
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
        if(_develop_mode)
        {
          std::cout << "++++++++++   address_check_cpp   +++++++++++" << std::endl;
        }
        pmt::pmt_t not_found;
        int received_frame_address = pmt::to_long(pmt::dict_ref(frame_info, pmt::string_to_symbol("destination_address"), not_found));
        int is_my_address = (_my_address == received_frame_address);
        if(_develop_mode)
          std::cout << "My address is " << _my_address << " and rx frame address is " << received_frame_address << ". Frame check is: " << is_my_address << std::endl;
        frame_info = pmt::dict_delete(frame_info, pmt::string_to_symbol("address_check"));
        frame_info = pmt::dict_add(frame_info, pmt::string_to_symbol("address_check"), pmt::from_long(is_my_address));
      }
      else
        if(_develop_mode)
          std::cout << "+++++++   address_check_cpp is off   +++++++" << std::endl;
      message_port_pub(pmt::mp("frame_info_out"), frame_info);
    }

  } /* namespace inets */
} /* namespace gr */

