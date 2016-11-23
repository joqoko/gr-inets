/* -*- c++ -*- */
/* 
 * copyright 2016 <+inets+>.
 * 
 * this is free software; you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation; either version 3, or (at your option)
 * any later version.
 * 
 * this software is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 * 
 * you should have received a copy of the gnu general public license
 * along with this software; see the file copying.  if not, write to
 * the free software foundation, inc., 51 franklin street,
 * boston, ma 02110-1301, usa.
 */

#ifdef have_config_h
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "packet_tx_timing_c_impl.h"

namespace gr {
  namespace inets {

    packet_tx_timing_c::sptr
    packet_tx_timing_c::make(float sample_rate, const std::string &lengthtagname)
    {
      return gnuradio::get_initial_sptr
        (new packet_tx_timing_c_impl(sample_rate, lengthtagname));
    }

    /*
     * the private constructor
     */
    packet_tx_timing_c_impl::packet_tx_timing_c_impl(float sample_rate, const std::string &lengthtagname)
      : gr::tagged_stream_block("packet_tx_timing_c",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              lengthtagname),
        _sample_rate(sample_rate)
    {
      message_port_register_out(pmt::mp("spark_out")); 
    }

    /*
     * our virtual destructor.
     */
    packet_tx_timing_c_impl::~packet_tx_timing_c_impl()
    {
    }

    int
    packet_tx_timing_c_impl::calculate_output_stream_length(const gr_vector_int &ninput_items) {
      return ninput_items[0];
    }


    int
    packet_tx_timing_c_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) input_items[0]; 
      long packet_length = ninput_items[0];
      std::vector <tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0));// + packet_length);
      // tags[0] 
      std::cout << "finally i am here" << _sample_rate << std::endl;
      message_port_pub(pmt::mp("spark_out"), pmt::from_bool(true));
      return packet_length;
    }

  } /* namespace inets */
} /* namespace gr */

