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
    slide_window::make(int develop_mode, int block_id, int protocol, int window_size, float timeout_duration_ms, int system_time_granularity_us, int samp_rate, int sps, double bps, double interframe_interval_us)
    {
      return gnuradio::get_initial_sptr
        (new slide_window_impl(develop_mode, block_id, protocol, window_size, timeout_duration_ms, system_time_granularity_us, samp_rate, sps, bps, interframe_interval_us));
    }

    /*
     * The private constructor
     */
    slide_window_impl::slide_window_impl(int develop_mode, int block_id, int protocol, int window_size, float timeout_duration_ms, int system_time_granularity_us, int samp_rate, int sps, double bps, double interframe_interval_us)
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
      _samp_rate(samp_rate),
      _sps(sps),       
      _bps(bps),
      _acked(false),
      _in_timeout(false),
      _interframe_interval_us(interframe_interval_us),
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
      _tx_win = new frame_in_window;
      _tx_win->next = NULL;
      _tx_win->last = NULL;
      _tx_win->window_index = 0;
      _rx_win = new frame_in_window;
      _rx_win->next = NULL;
      _rx_win->last = NULL;
      _rx_win->window_index = 0;
    }

    /*
     * Our virtual destructor.
     */
    slide_window_impl::~slide_window_impl()
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
//            print_index(_tx_win);
//            window_count(_tx_win);
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
        pmt::pmt_t not_found;
        // get the number of totally pushed frame from the source
        int _n_dequeue = pmt::to_long(frame_in); 
        // after received the pushed frames, the current window size
        _n_window = window_count(_tx_win);
        // for debugging purpose, if the infinite source is chosen, _n_window should always equal to _window_size
        if(_develop_mode)
          std::cout << "window size and actual window size are: " << _n_window << _window_size << std::endl;
        if(_n_window == _window_size)
        {
          _in_timeout = true;
          for(int i = 0; i < _n_window; i++)
          {
            if(i > 0)
              boost::this_thread::sleep(boost::posix_time::microseconds(_tx_win->next->t_frame_ms * 1000 + _interframe_interval_us));
            if(!_in_timeout)
              break;
            else
            {
              message_port_pub(pmt::mp("frame_info_out"), _tx_win->next->frame);
              window_swap_element(_rx_win, _tx_win);
            }
            if(i == 0) 
              boost::thread thrd(&slide_window_impl::countdown_timeout, this);       
            // std::cout << "buffer ID: " << _block_id << " dequeue " << _n_dequeue << " elements at time " << current_time << " s" << std::endl;
          }
         // print_index(_tx_win);
         print_index(_rx_win);
         // double last_tx_time;
         // last_tx_time = time_frame(_rx_win, 5);
         // std::cout << "time different is: " << last_tx_time - _rx_win->next->tx_time << std::endl; 
          
        }
        else
          std::cout << "after reloading, temporary window size is not same as the pre-defined window size. Must be something wrong." << std::endl;
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
    
    void slide_window_impl::countdown_timeout()
    {
      struct timeval t;
      gettimeofday(&t, NULL);
      double current_time = t.tv_sec + t.tv_usec / 1000000.0;
      double start_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
      if(_develop_mode)
        std::cout << "timeout timer start time: " << start_time_show << std::endl;
      while(window_count(_rx_win))
      {
        while((current_time < _timeout_duration_ms / 1000 + _rx_win->next->tx_time) && !_acked && _in_timeout)
        {
          gettimeofday(&t, NULL);
          current_time = t.tv_sec + t.tv_usec / 1000000.0;
          boost::this_thread::sleep(boost::posix_time::microseconds(_system_time_granularity_us));
          // current_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
          // std::cout << "timeout is running at: " << current_time_show << std::endl;
        }
        if(_acked)
        {
          if(window_count(_rx_win) > 0)
            _rx_win = _rx_win->next;
          _acked = false;
        }
        else
        {
          break;
        }
        if(!_in_timeout)
          break;
      }
      if(_develop_mode)
      {
        gettimeofday(&t, NULL);
        double current_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        if(_in_timeout)
          std::cout << "* timeout ID: " << _block_id << " timeout timer is expired at time " << current_time_show << " s. " << " timeout duration is: " << _timeout_duration_ms << " [ms]. " << "at this moment, there is " << window_count(_rx_win) << " frame in the buffer. " << std::endl;
        else
          std::cout << "* timeout ID: " << _block_id << " timeout timer is killed at time " << current_time_show << " s. " << " actual timeout duration is: " << current_time_show - start_time_show << std::endl;
      }
      _acked = false;
      _in_timeout = false;
    }

    void 
    slide_window_impl::handle_ack(pmt::pmt_t ack_frame_info) 
    {
      if(_develop_mode)
        std::cout << "++++++  slide_window ID: " << _block_id << " handle_ack  ++++++" << std::endl;
      if(_develop_mode == 2)
      {
        struct timeval t; 
        gettimeofday(&t, NULL);
        double current_time_show = t.tv_sec - double(int(t.tv_sec/100)*100) + t.tv_usec / 1000000.0;
        std::cout << "* timeout ID: " << _block_id << " start killing the timer at time " << current_time_show << " s" << std::endl;
      }
      if(pmt::is_dict(ack_frame_info))
      {
        pmt::pmt_t not_found;
        // ack frame info
        int frame_type = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("frame_type"), not_found));
        int ack_dest = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("destination_address"), not_found));
        int ack_src = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("source_address"), not_found));
        int ack_index = pmt::to_long(pmt::dict_ref(ack_frame_info, pmt::string_to_symbol("frame_index"), not_found));
        // waiting frame info
        int wait_dest = pmt::to_long(pmt::dict_ref(_rx_win->next->frame, pmt::string_to_symbol("destination_address"), not_found));
        int wait_src = pmt::to_long(pmt::dict_ref(_rx_win->next->frame, pmt::string_to_symbol("source_address"), not_found));
        int wait_index = pmt::to_long(pmt::dict_ref(_rx_win->next->frame, pmt::string_to_symbol("frame_index"), not_found));
        if(!_acked)
        {
          if((frame_type == 2) && (ack_dest == wait_src) && (ack_src == wait_dest) && (ack_index == wait_index))
          { 
            _acked = true;
            message_port_pub(pmt::mp("frame_info_out"), ack_frame_info);
            if(_develop_mode == 1)
              std::cout << "timeout of window index: " << _rx_win->next->window_index << " is terminated by correctly received ack frame." << std::endl;
          }
          else if(frame_type != 2)
            if(_develop_mode == 1)
              std::cout << "Not an ack_frame_info dict." << std::endl;
          else if((ack_dest != wait_src) && (ack_src != wait_dest))
            if(_develop_mode == 1)
              std::cout << "address not correct." << std::endl;
          else if(ack_index != wait_index)
          {
            if(_develop_mode == 1)
              std::cout << "expecting the ack of the " << wait_index << "th frame but received the ack of the " << ack_index << "th frame." << std::endl;
            _in_timeout = false;
          }
          else
            std::cout << "handle_ack function is problematic. Please check your code." << std::endl;
        }
        else
          std::cout << "Receive a pmt dict out of timeout interval." << std::endl;
      }
      else
        std::cout << "ack_frame_info: wrong data type. please check your connection." << std::endl;
    }
    
    double
    slide_window_impl::time_frame(frame_in_window *first, int win_index)
    {
      frame_in_window *temp = first;
      while(temp->next != NULL)
      {
        if(temp->next->window_index == win_index)
          break;
        temp = temp->next;
      }
      return temp->next->tx_time;
      
    }

    void
    slide_window_impl::print_index(frame_in_window *first)
    {
      pmt::pmt_t not_found;
      frame_in_window *temp;
      temp = first;
      std::cout << "frame index: ";
      while(temp->next != NULL)
      {
        std::cout << pmt::to_long(pmt::dict_ref(temp->next->frame, pmt::string_to_symbol("frame_index"), not_found)) << " ";
        temp = temp->next;
      }
      std::cout << " " << std::endl;
    }
    
    // window move delete one element from the head of linked list source and add it to the tail of destination. source and destination are the head pointer of the two linked list.
    void
    slide_window_impl::window_swap_element(frame_in_window *destination, frame_in_window *source)
    { 
      frame_in_window *temp;
      temp = destination;
      while(temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = source->next; 
      if(source->next->next !=NULL)
        source->next->next->last = source;
      source->next =source->next->next;
      temp->next->next = NULL;
      temp->next->last = temp;
//      if(_develop_mode)
//        std::cout << "source: " << window_count(source) << " and destination: " << window_count(destination) << std::endl;
    }

    int
    slide_window_impl::window_count(frame_in_window *first)
    { 
      frame_in_window *temp;
      temp = first;
      // i is from -1 because *first is not a valid frame.
      int i = -1;
      while(temp != NULL)
      {
        i++;
        temp = temp->next;
      }
 //     if(_develop_mode)
 //       std::cout << "there is " << i << " frames in the window" << std::endl;
      return i;
    }

    void
    slide_window_impl::window_insert(frame_in_window *first, pmt::pmt_t frame)
    { 
      pmt::pmt_t not_found;
      frame_in_window *temp;
      temp = first;
      int win_index = 1;
      while(temp->next != NULL)
      {
        temp = temp->next;
        win_index++;
      }
      frame_in_window *new_frame = new frame_in_window;
      new_frame->last = temp;
      new_frame->next = NULL;
      new_frame->tx_time = 0;
      new_frame->frame = frame;
      new_frame->t_frame_ms = pmt::u8vector_elements(pmt::cdr(pmt::dict_ref(frame, pmt::string_to_symbol("frame_pmt"), not_found))).size() / _bps * 1000;
      new_frame->window_index = win_index;
      temp->next = new_frame;
 //     std::cout << "temp frame_index is: " << temp->next->frame_index << std::endl;
    }


  } /* namespace inets */
} /* namespace gr */

