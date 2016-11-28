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
#include "pending_tx_finish_impl.h"

namespace gr {
  namespace inets {

    pending_tx_finish::sptr
    pending_tx_finish::make(int develop_mode, float sample_rate, const std::string &lengthtagname)
    {
      return gnuradio::get_initial_sptr
        (new pending_tx_finish_impl(develop_mode, sample_rate, lengthtagname));
    }

    /*
     * The private constructor
     */
    pending_tx_finish_impl::pending_tx_finish_impl(int develop_mode, float sample_rate, const std::string &lengthtagname)
      : gr::sync_block("pending_tx_finish",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0)),
        _sample_rate(sample_rate),
        _d_lengthtagname(pmt::string_to_symbol(lengthtagname)),
        _develop_mode(develop_mode)
    {
      message_port_register_out(pmt::mp("spark_out"));
    }

    /*
     * Our virtual destructor.
     */
    pending_tx_finish_impl::~pending_tx_finish_impl()
    {
    }

    int
    pending_tx_finish_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];

      std::vector <tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items);// + packet_length);
      display_tags_info(tags);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void 
    pending_tx_finish_impl::display_tags_info(std::vector <tag_t> tags)
    {
      std::cout << "Number of tags: " << tags.size() << std::endl;
      if(_develop_mode)
      {
        if(tags.size() > 0)
        {
          std::cout << "I am here p1" << std::endl;
          for(int i = 0; i < tags.size(); i++)
          {
            std::cout << "Index of tags: " << i << std::endl;
            std::cout << "Offset: " << tags[i].offset << std::endl;
            std::cout << "Key: " << tags[i].key << std::endl;
            std::cout << "Value: " << tags[i].value << std::endl;
            std::cout << "Srcid: " << tags[i].srcid << std::endl;
          }
        }
      }
    }
  } /* namespace inets */
} /* namespace gr */

