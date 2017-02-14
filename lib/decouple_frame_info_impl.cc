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
#include "decouple_frame_info_impl.h"

namespace gr {
  namespace inets {

    decouple_frame_info::sptr
    decouple_frame_info::make(int develop_mode, int block_id)
    {
      return gnuradio::get_initial_sptr
        (new decouple_frame_info_impl(develop_mode, block_id));
    }

    /*
     * The private constructor
     */
    decouple_frame_info_impl::decouple_frame_info_impl(int develop_mode, int block_id)
      : gr::block("decouple_frame_info",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id)
    { 
      if(_develop_mode == 1)
        std::cout << "develop_mode of decouple_frame_info ID " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("frame_cluster_in"));
      message_port_register_out(pmt::mp("frame_pmt_out"));
      message_port_register_out(pmt::mp("frame_info_out"));
      set_msg_handler(pmt::mp("frame_cluster_in"), boost::bind(&decouple_frame_info_impl::decoupling, this, _1 ));
    }

    /*
     * Our virtual destructor.
     */
    decouple_frame_info_impl::~decouple_frame_info_impl()
    {
    }

    void decouple_frame_info_impl::decoupling(pmt::pmt_t frame_cluster)
    {

      if(_develop_mode == 1)
        std::cout << "++++++++  decouple_frame_info ID: " << _block_id << "  +++++++++++++" << std::endl;
      pmt::pmt_t not_found;
      if(_develop_mode == 1)
        pmt::print(frame_cluster);
      if(pmt::is_dict(frame_cluster))
      {
        if(pmt::dict_has_key(frame_cluster, pmt::string_to_symbol("frame_pmt")))
        { 
          if(_develop_mode == 2)
          {
            struct timeval t; 
            gettimeofday(&t, NULL);
            double current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
            std::cout << "* decouple ID: " << _block_id << " receives data frame at time " << current_time << " s" << std::endl;
          }
          pmt::pmt_t frame_pmt = pmt::dict_ref(frame_cluster, pmt::string_to_symbol("frame_pmt"), not_found);
          pmt::pmt_t frame_info = pmt::dict_delete(frame_cluster, pmt::string_to_symbol("frame_pmt"));
          message_port_pub(pmt::mp("frame_pmt_out"), frame_pmt);
          message_port_pub(pmt::mp("frame_info_out"), frame_info);
        }
        else
          std::cout << "Warning: frame_cluster does does not have payload. Please check your connection." << std::endl;
      }
      else
        std::cout << "Warning: wrong pmt type. Please check your connection." << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

