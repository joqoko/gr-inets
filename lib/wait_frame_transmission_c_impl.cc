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
#include "wait_frame_transmission_c_impl.h"

namespace gr {
  namespace inets {

    wait_frame_transmission_c::sptr
    wait_frame_transmission_c::make(float sample_rate, const std::string &lengthtagname)
    {
      return gnuradio::get_initial_sptr
        (new wait_frame_transmission_c_impl(sample_rate, lengthtagname));
    }

    /*
     * The private constructor
     */
    wait_frame_transmission_c_impl::wait_frame_transmission_c_impl(float sample_rate, const::std::string &lengthtagname)
      : gr::block("wait_frame_transmission_c",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0)),
        _sample_rate(sample_rate),
        _d_lengthtagname(pmt::string_to_symbol(lengthtagname))
    {
      message_port_register_out(pmt::mp("spark_out"));
    }

    /*
     * Our virtual destructor.
     */
    wait_frame_transmission_c_impl::~wait_frame_transmission_c_impl()
    {
    }

    void
    wait_frame_transmission_c_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      
    }

    int
    wait_frame_transmission_c_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      std::vector <tag_t> tags;
      std::cout << "Number of input is: " << ninput_items[0];
      get_tags_in_range(tags, 0, 0, ninput_items[0]);// + packet_length);
      display_tags_info(tags);
      consume_each (noutput_items);
      std::cout << "Temp: outnumber: " << noutput_items << std::endl;
//      message_port_pub(pmt::mp("spark_out"), pmt::from_bool(true));
      // Tell runtime system how many output items we produced.
      return 0;
    }

    void wait_frame_transmission_c_impl::display_tags_info(std::vector <tag_t> tags)
    {
      std::cout << "Number of tags: " << tags.size() << std::endl;
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
  } /* namespace inets */
} /* namespace gr */

