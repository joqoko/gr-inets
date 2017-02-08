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
#include "slide_window_impl.h"
#include <queue>

namespace gr {
  namespace inets {

    slide_window::sptr
    slide_window::make(int develop_mode, int block_id, int protocol, int window_size, float timeout_duration_ms, int system_time_granularity_us)
    {
      return gnuradio::get_initial_sptr
        (new slide_window_impl(develop_mode, block_id, protocol, window_size, timeout_duration_ms, system_time_granularity_us));
    }

    /*
     * The private constructor
     */
    slide_window_impl::slide_window_impl(int develop_mode, int block_id, int protocol, int window_size, float timeout_duration_ms, int system_time_granularity_us)
      : gr::block("slide_window",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
      _develop_mode(develop_mode),
      _block_id(block_id),
      _protocol(protocol),
      _window_size(window_size),
      _timeout_duration_ms(float(timeout_duration_ms)),
      _system_time_granularity_us(system_time_granularity_us),
      _n_window(0),
      _start(0)
    {
      if(_develop_mode)
        std::cout << "develop_mode of slide_window ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("data_frame_in")); 
      set_msg_handler(pmt::mp("data_frame_in"), boost::bind(&slide_window_impl::handle_data, this, _1));
      message_port_register_in(pmt::mp("ack_frame_in")); 
      set_msg_handler(pmt::mp("ack_frame_in"), boost::bind(&slide_window_impl::handle_ack, this, _1));
      message_port_register_out(pmt::mp("frame_info_out"));
      message_port_register_out(pmt::mp("frame_pull_request"));
      _tx_win = NULL;
    }

    /*
     * Our virtual destructor.
     */
    slide_window_impl::~slide_window_impl()
    {
    }
     
    void
    slide_window_impl::handle_ack(pmt::pmt_t frame_in)
    {
    }

    void
    slide_window_impl::handle_data(pmt::pmt_t frame_in)
    {
      // if a frame comes, simple add it to the window.
      if(pmt::is_dict(frame_in))
      {
        /*
         * protocol == 1: go-back-n
         */
        if(_protocol == 1)
        {
          // add the new frame to the linked list
	  window_insert(_tx_win, frame_in);
          if(_develop_mode)
	  {
	    print_index(_tx_win);
	    window_count(_tx_win);
	  }
        }
        /*
         * protocol == 2: selective repeat
         */
        else if(_protocol == 2)
        {
          // add the new frame to the linked list
	  window_insert(_tx_win, frame_in);
          if(_develop_mode)
            std::cout << "selective repeat tx window " << _block_id << " has " << _tx_window.size() << " elements after enqueue." << std::endl;
        }
        else
          std::cout << "Chosen slide window protocol is not supported yet. You are welcome to have some contribution here. " << std::endl; 
      }
      // the coming of a number means that the pull requests is responded and finished. The number indicated the pulled frames. In current step, we also deal with infinite source, i.e., 1, we can always get the number of frames that we request; 2. the window size is always feed to the original size.
      else if(pmt::is_integer(frame_in))
      {
        struct timeval t; 
        // get the number of totally pushed frame from the source
        int _n_dequeue = pmt::to_long(frame_in); 
        // after received the pushed frames, the current window size
        _n_window = window_count(_tx_win);
        // for debugging purpose, if the infinite source is chosen, _n_window should always equal to _window_size
        if(_n_window != _window_size)
        {
          for(int i = 0; i < _n_window; i++)
          {
            // first dequeue the element
            // message_port_pub(pmt::mp("dequeue_element"), _tx_window.front());
            // _tx_window.pop(); 
            // then record the time to check the timeout timer
            gettimeofday(&t, NULL);
            double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
            // std::cout << "buffer ID: " << _block_id << " dequeue " << _n_dequeue << " elements at time " << current_time << " s" << std::endl;
          }
        }
        else
          std::cout << "temporary window size is greater than the pre-defined window size. Must be something wrong." << std::endl;
      }
      else
      {
        if(_start == 0)
        {
          if(_develop_mode)
            std::cout << "slide window protocol starts. ask for the source to reload" << std::endl;
          message_port_pub(pmt::mp("frame_pull_request"), pmt::from_long(_window_size));
	  _start = 1;
        }
      } 
    }

    void
    slide_window_impl::print_index(frame_in_window *first)
    {
      frame_in_window *temp;
      temp = first;
      std::cout << "index: ";
      while(temp != NULL)
      {
        std::cout << temp->frame_index << " ";
        temp = temp->next;
      }
      std::cout << " " << std::endl;
    }
    
    int
    slide_window_impl::window_count(frame_in_window *first)
    { 
      frame_in_window *temp;
      temp = first;
      int i = 0;
      while(temp != NULL)
      {
        i++;
        temp = temp->next;
      }
      if(_develop_mode)
        std::cout << "there is " << i << " frames in the window" << std::endl;
      return i;
    }

    void
    slide_window_impl::window_insert(frame_in_window *first, pmt::pmt_t frame)
    { 
      pmt::pmt_t not_found;
      frame_in_window *temp;
      *temp = *first;
      std::cout << "temp is: " << temp << std::endl;
      std::cout << "first is: " << first << std::endl;
      while(temp != NULL)
      {
        std::cout << "temp frame_indexxxxx is: " << temp->frame_index << std::endl;
        temp = temp->next;
      }
      frame_in_window new_frame;
      new_frame.last = temp;
      new_frame.next = NULL;
      new_frame.frame = frame;
      new_frame.frame_index = pmt::to_long(pmt::dict_ref(frame, pmt::string_to_symbol("frame_index"), not_found));
      temp = &new_frame;
      std::cout << "temp frame_index is: " << temp->frame_index << std::endl;
      std::cout << "first frame_index is: " << first << std::endl;
    }

  } /* namespace inets */
} /* namespace gr */

