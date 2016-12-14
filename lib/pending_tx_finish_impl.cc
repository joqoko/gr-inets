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
    pending_tx_finish::make(std::vector<int> develop_mode_list, int system_time_granularity_us, float sample_rate, const std::string &lengthtagname)
    {
      return gnuradio::get_initial_sptr
        (new pending_tx_finish_impl(develop_mode_list, system_time_granularity_us, sample_rate, lengthtagname));
    }

    /*
     * The private constructor
     */
    pending_tx_finish_impl::pending_tx_finish_impl(std::vector<int> develop_mode_list, int system_time_granularity_us, float sample_rate, const std::string &lengthtagname)
      : gr::sync_block("pending_tx_finish",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0)),
        _sample_rate(sample_rate),
        _d_lengthtagname(pmt::string_to_symbol(lengthtagname)),
        _develop_mode_list(develop_mode_list),
        _my_develop_mode(5),
        _system_time_granularity_us(system_time_granularity_us)
    {
      _develop_mode = (std::find(_develop_mode_list.begin(), _develop_mode_list.end(), _my_develop_mode) != _develop_mode_list.end());
      if(_develop_mode)
        std::cout << "develop_mode of pending_tx_finish is activated." << std::endl;
      _wait_time = 0;
      message_port_register_in(pmt::mp("tx_frame_info_in"));
      message_port_register_out(pmt::mp("tx_frame_info_out"));
      set_msg_handler(pmt::mp("tx_frame_info_in"), boost::bind(&pending_tx_finish_impl::buffer_tx_frame_info, this, _1 ));
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
      // If tag(s) is detected, we need to wait then send the spark signal.
      if(process_tags_info(tags))
      {
        boost::thread thrd(&pending_tx_finish_impl::countdown_waiting, this);
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void
    pending_tx_finish_impl::buffer_tx_frame_info(pmt::pmt_t tx_frame_info)
    {
      if(pmt::is_dict(tx_frame_info))
      {
        _tx_frame_info = tx_frame_info;
        if(_develop_mode)
          std::cout << "tx_frame_info received." << std::endl;
      }
      else
        std::cout << "tx_frame_info is not a dict. Please check your connection." << std::endl;
    }

    int
    pending_tx_finish_impl::process_tags_info(std::vector <tag_t> tags)
    {
      if(_develop_mode)
      {
        std::cout << "+++++++++++  pending_tx_finish  ++++++++++++" << std::endl;
        std::cout << "Number of tags: " << tags.size() << std::endl;
      }
      if(tags.size() > 0)
      {
        for(int i = 0; i < tags.size(); i++)
        {
          if(_develop_mode)
          {
            std::cout << "Index of tags: " << i << std::endl;
            std::cout << "Offset: " << tags[i].offset << std::endl;
            std::cout << "Key: " << tags[i].key << std::endl;
            std::cout << "Value: " << tags[i].value << std::endl;
            std::cout << "Srcid: " << tags[i].srcid << std::endl;
          }
          
          // std::cout << "string comapre: " << pmt::symbol_to_string(tags[i].key) << "packet_len" <<  (pmt::symbol_to_string(tags[i].key) == "packet_len") << std::endl;
          if(pmt::symbol_to_string(tags[i].key) == "packet_len")
          {
            _wait_time = pmt::to_double(tags[i].value) / _sample_rate;     
            if(_develop_mode)
            {
              std::cout << "Frame transmission time is: " << _wait_time << std::endl;
            }
            break;
          }
        }
      }
      else
      {
      }
      return tags.size();
    }

    void pending_tx_finish_impl::countdown_waiting()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time = t.tv_sec + t.tv_usec / 1000000.0;

      if(_develop_mode)
      {
        std::cout << "Start time: " << start_time << std::endl;
        std::cout << "wait time: " << _wait_time << std::endl;
      }
      int count = 0;
      while(current_time < start_time + _wait_time)
      {
        boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
        gettimeofday(&t, NULL);
        current_time = t.tv_sec + t.tv_usec / 1000000.0;
        if(_develop_mode)
        {
        //  std::cout << "Remaining time: " << _wait_time - (current_time - start_time) << "Count is: "<< count << std::endl;
          count = count + 1; 
        }
      }
      if(_develop_mode)
        std::cout << "Count is: " << count << std::endl;
      _wait_time = 0;
      message_port_pub(pmt::mp("tx_frame_info_out"), _tx_frame_info);

      gettimeofday(&t, NULL);
      current_time = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
      std::cout << "after pending tx at time " << current_time << std::endl;
    }


  } /* namespace inets */
} /* namespace gr */

