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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "frame_aggregation_impl.h"

namespace gr {
  namespace inets {

    frame_aggregation::sptr
    frame_aggregation::make(int develop_mode, int block_id, int number_aggregation)
    {
      return gnuradio::get_initial_sptr
        (new frame_aggregation_impl(develop_mode, block_id, number_aggregation));
    }

    /*
     * The private constructor
     */
    frame_aggregation_impl::frame_aggregation_impl(int develop_mode, int block_id, int number_aggregation)
      : gr::block("frame_aggregation",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _aggregation_type(0),
	_frame_type(0),
        _number_aggregation(number_aggregation),
        _aggregation_n(0)
    {
      if(_develop_mode == 1)
        std::cout << "develop_mode of Framing ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("subframe_in"));
      set_msg_handler(pmt::mp("subframe_in"), boost::bind(&frame_aggregation_impl::aggregating, this, _1 ));
      message_port_register_out(pmt::mp("aggregated_frame_out"));
    }

    /*
     * Our virtual destructor.
     */
    frame_aggregation_impl::~frame_aggregation_impl()
    {
    }

    void
    frame_aggregation_impl::aggregating(pmt::pmt_t subframe)
    {
      pmt::pmt_t not_found;
      if(_develop_mode == 1)
        std::cout << "+++++++++ frame_aggregation ID: " << _block_id << " +++++++++" << std::endl;    
      if(pmt::dict_has_key(subframe, pmt::string_to_symbol("mpdu_info")))
      {
        pmt::pmt_t mpdu_info = pmt::dict_ref(subframe, pmt::string_to_symbol("mpdu_info"), not_found);
        int frame_type = pmt::to_long(pmt::dict_ref(mpdu_info, pmt::string_to_symbol("frame_type"), not_found));
        // first subframe of the aggregated frame
        if(_aggregation_n == 0)
        {
          _aggregation_type = frame_type; 
          // ampdu
          if(frame_type == 8)
	  {
            create_ampdu(subframe);
	    _aggregation_n = 1;
	  }
          // other frames cannot be aggregated
          else
            std::cout << "Other frame aggretation is not supported yet." << std::endl;
        }
        else if(_aggregation_n > 0)
        {
          // check is the frame type of the new comer is the same as the  existing aggregated frames.
          if(_aggregation_type == frame_type)
          {
            if(frame_type == 8)
	    {
              insert_ampdu(subframe); 
	      _aggregation_n++;
	    }
            else
              std::cout << "Other frame aggretation is not supported yet." << std::endl;
          }
          else
            std::cout << "aggregation of different type of subframe is not allowed." << std::endl;
          if(_aggregation_n == _number_aggregation)
          {
            if(_develop_mode == 1)
	      std::cout << "all frames are aggregated." << std::endl;
            message_port_pub(pmt::mp("aggregated_frame_out"), _frame_info);
            _aggregation_n = 0;
          }
        }
        else
          std::cout << "subframe does not have frame type info. Please check your frame generation code." << std::endl;
      }
      else
        std::cout << "input pmt is not a dictionary. Please check your connections." << std::endl;
    } 

    void
    frame_aggregation_impl::create_ampdu(pmt::pmt_t subframe)
    {
      if(_develop_mode == 1)
      {
        std::cout << "+++ frame_aggregation ID: " << _block_id << " create ampdu+++" << std::endl;
      }
      pmt::pmt_t not_found;
      /*
       * Generate the first piece of ampdu 
       */
      if(pmt::is_dict(subframe)) 
      {
	if(pmt::dict_has_key(subframe, pmt::string_to_symbol("subframe_pmt")))
	{
          pmt::pmt_t subframe_pmt = pmt::dict_ref(subframe, pmt::string_to_symbol("subframe_pmt"), not_found);
          pmt::pmt_t meta = pmt::car(subframe_pmt);
          pmt::pmt_t payload_pmt = pmt::cdr(subframe_pmt);
	  _frame_info = pmt::dict_ref(subframe, pmt::string_to_symbol("mpdu_info"), not_found);
          _frame_info = pmt::dict_delete(_frame_info, pmt::string_to_symbol("frame_index"));
          _frame_info = pmt::dict_delete(_frame_info, pmt::string_to_symbol("frame_type"));
          _frame_info = pmt::dict_add(_frame_info, pmt::string_to_symbol("frame_type"), pmt::from_long(6));
          _frame_info = pmt::dict_delete(_frame_info, pmt::string_to_symbol("reserved_field_I"));
          _frame_info = pmt::dict_delete(_frame_info, pmt::string_to_symbol("reserved_field_II"));
          _frame_info = pmt::dict_add(_frame_info, pmt::string_to_symbol("ampdu_frame_pmt"), subframe_pmt);
	}
        else
          std::cout << "pmt is not a subframe" << std::endl;
      }
      else 
        std::cout << "pmt is not a pair" << std::endl;
    }

    void
    frame_aggregation_impl::insert_ampdu(pmt::pmt_t subframe)
    {
      if(_develop_mode == 1)
      {
        std::cout << "+++ frame_aggregation ID: " << _block_id << " insert subframe +++" << std::endl;
      }
      pmt::pmt_t not_found;
      /*
       * Generate a data frame
       */
      if(pmt::is_dict(subframe)) 
      {
	if(pmt::dict_has_key(subframe, pmt::string_to_symbol("subframe_pmt")))
	{
          pmt::pmt_t subframe_pmt = pmt::dict_ref(subframe, pmt::string_to_symbol("subframe_pmt"), not_found);
          pmt::pmt_t meta = pmt::car(subframe_pmt);
          pmt::pmt_t payload_pmt = pmt::cdr(subframe_pmt);
	  std::vector<unsigned char> aggregated_array;
	  std::vector<unsigned char> subframe_array;
	  aggregated_array = pmt::u8vector_elements(pmt::cdr(pmt::dict_ref(_frame_info, pmt::string_to_symbol("ampdu_frame_pmt"), not_found)));
	  subframe_array = pmt::u8vector_elements(payload_pmt);
          aggregated_array.insert(aggregated_array.end(), subframe_array.begin(), subframe_array.end());
	  _frame_info = pmt::dict_delete(_frame_info, pmt::string_to_symbol("ampdu_frame_pmt"));
          _frame_info = pmt::dict_add(_frame_info, pmt::string_to_symbol("ampdu_frame_pmt"), pmt::cons(meta, pmt::init_u8vector(aggregated_array.size(), aggregated_array)));
	  
	}
        else
          std::cout << "pmt is not a u8vector" << std::endl;
      }
      else 
        std::cout << "pmt is not a pair" << std::endl;
    }

    void
    frame_aggregation_impl::create_amsdu(pmt::pmt_t subframe)
    {
      std::cout << "amsdu is still under construction" << std::endl;
    }
    
    void
    frame_aggregation_impl::insert_amsdu(pmt::pmt_t subframe)
    {
      std::cout << "amsdu is still under construction" << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

