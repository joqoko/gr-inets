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
 * but WITHOUT ANY WARRANTY without even the implied warranty of
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
#include <uhd/types/time_spec.hpp>
#include <sys/time.h>

namespace gr {
  namespace inets {

    t_control_tx_cc::sptr
    t_control_tx_cc::make(int develop_mode, int block_id, double bps, double t_pretx_interval_s)
    {
      return gnuradio::get_initial_sptr
        (new t_control_tx_cc_impl(develop_mode, block_id, bps, t_pretx_interval_s));
    }

    /*
     * The private constructor
     */
    t_control_tx_cc_impl::t_control_tx_cc_impl(int develop_mode, int block_id, double bps, double t_pretx_interval_s)
      : gr::block("t_control_tx_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _last_tx_time(0),
        _t_pretx_interval_s(t_pretx_interval_s),
        _bps(bps)
    {
      if(_develop_mode)
        std::cout << "develop_mode of t_control_tx ID: " << _block_id << " is activated." << "and t_re is " << _t_pretx_interval_s << std::endl;
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
        if(_develop_mode)
        {
          //std::cout << "++++++++++   t_control_tx_cc ID: " << _block_id << "  ++++++++++" << std::endl;
        }
        /*
          JUA parketizer code starts 
        */ 
        // Add key to the tx_time tag
        static const pmt::pmt_t time_key = pmt::string_to_symbol("tx_time");
        // Get the time
        struct timeval t;
        gettimeofday(&t, NULL);
        double tx_time = t.tv_sec + t.tv_usec / 1000000.0;
        // double min_time_diff = pmt::to_double(_packet_len_tag.value) / _bps; //Max packet len [bit] / bit rate 
        double min_time_diff = (1000 * 8.0) / _bps; //Max packet len [bit] / bit rate 
        // Ensure that frames are not overlap each other
        if((tx_time - _last_tx_time) <= min_time_diff) {
          tx_time = _last_tx_time + min_time_diff;
          if(_develop_mode)
            std::cout << "t_control ID " << _block_id << " in time packet" << std::endl;
        }
        //std::cout << "tx time = " << std::fixed << tx_time << std::endl;
        // update the tx_time to the current packet
        _last_tx_time = tx_time;
        // question 1: why add 0.05?
        std::cout << "t pretx is: " << _t_pretx_interval_s << std::endl;
        uhd::time_spec_t now = uhd::time_spec_t(tx_time)
          + uhd::time_spec_t(_t_pretx_interval_s);
        // the value of the tag is a tuple
        const pmt::pmt_t time_value = pmt::make_tuple(
          pmt::from_uint64(now.get_full_secs()),
          pmt::from_double(now.get_frac_secs())
        );
        
        add_item_tag(0, _packet_len_tag.offset, time_key, time_value);
        
       /* 
         JUA parketizer code starts 
       */
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
        /*
        if(_develop_mode)
        {
          std::cout << "Index of tags: " << i << std::endl;
          std::cout << "Offset: " << tags[i].offset << std::endl;
          std::cout << "Key: " << tags[i].key << std::endl;
          std::cout << "Value: " << tags[i].value << std::endl;
          std::cout << "Srcid: " << tags[i].srcid << std::endl;
        }
        */
          
          // std::cout << "string comapre: " << pmt::symbol_to_string(tags[i].key) << "packet_len" <<  (pmt::symbol_to_string(tags[i].key) == "packet_len") << std::endl;
        if(pmt::symbol_to_string(tags[i].key) == "packet_len")
        {
          _packet_len_tag = tags[i];          
          tag_detected = 1;
          if(_develop_mode)
          {
            std::cout << "++++ t_control ID: " << _block_id << " gets a packet (packet_len tag) to send ";
          }
          if(_develop_mode == 2)
          {
            struct timeval t; 
            gettimeofday(&t, NULL);
            double current_time_show = t.tv_sec - double(int(t.tv_sec/10)*10) + t.tv_usec / 1000000.0;
            std::cout << " at time " << current_time_show << " s" << std::endl;
          }
          else
            std::cout << "." << std::endl;
          break;
        }
      }

      return tag_detected;
    }

  } /* namespace inets */
} /* namespace gr */

