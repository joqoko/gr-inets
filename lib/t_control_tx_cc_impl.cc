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
#include "t_control_tx_cc_impl.h"

namespace gr {
  namespace inets {

    t_control_tx_cc::sptr
    t_control_tx_cc::make(int develop_mode)
    {
      return gnuradio::get_initial_sptr
        (new t_control_tx_cc_impl(develop_mode));
    }

    /*
     * The private constructor
     */
    t_control_tx_cc_impl::t_control_tx_cc_impl(int develop_mode)
      : gr::block("t_control_tx_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        _develop_mode(develop_mode)
    {
      _packet_len_tag();
    }

    /*
     * Our virtual destructor.
     */
    t_control_tx_cc_impl::~t_control_tx_cc_impl()
    {
    }

    void
    t_control_tx_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
      ninput_items_required[0] = noutput_items;
    }

    int
    t_control_tx_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      /* 
       * signal is not changed through carrier sensing block, i.e., it simply output its input.
       */
      for(int i = 0; i < noutput_items; i++)
      {
        out[i] = in[i];
      }

      std::vector <tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items);// + packet_length);

      if(process_tags_info(tags))
      {
        std::cout << "Executed 1" << std::endl;
      }
      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    t_control_tx_cc_impl::process_tags_info(std::vector <tag_t> tags)
    {
      int tag_detected = 0; 
      for(int i = 0; i < tags.size(); i++)
      {
        if(_develop_mode > 1)
        {
          std::cout << "Index of tags: " << i << std::endl;
          std::cout << "Offset: " << tags[i].offset << std::endl;
          std::cout << "Key: " << tags[i].key << std::endl;
          std::cout << "Value: " << tags[i].value << std::endl;
          std::cout << "Srcid: " << tags[i].srcid << std::endl;
        }
          
          // std::cout << "string comapre: " << pmt::symbol_to_string(tags[i].key) << "packet_len" <<  (pmt::symbol_to_string(tags[i].key) == "packet_len") << std::endl;
        if(pmt::symbol_to_string(tags[i].key) == "tx_time")
        {
          tag_detected = 1;
          if(_develop_mode > 0)
          {
            std::cout << "tx_time tag found: " << tag_detected << std::endl;
          }
          break;
        }
      }
      return tag_detected;
    }

  } /* namespace inets */
} /* namespace gr */

