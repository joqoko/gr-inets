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
#include "frame_buffer_impl.h"
#include <queue>

namespace gr {
  namespace inets {

    frame_buffer::sptr
    frame_buffer::make(int develop_mode, int block_id, int buffer_size, int auto_dequeue_first, int keep_dequeue_state)
    {
      return gnuradio::get_initial_sptr
        (new frame_buffer_impl(develop_mode, block_id, buffer_size, auto_dequeue_first, keep_dequeue_state));
    }

    /*
     * The private constructor
     */
    frame_buffer_impl::frame_buffer_impl(int develop_mode, int block_id, int buffer_size, int auto_dequeue_first, int keep_dequeue_state)
      : gr::block("frame_buffer",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        _develop_mode(develop_mode),
        _block_id(block_id),
        _buffer_size(buffer_size),
	_auto_dequeue_first(auto_dequeue_first),
	_keep_dequeue_state(keep_dequeue_state),
	_dequeue_when_available(0),
	_dequeue_first(1)
  //      _output_dequeue_element(output_dequeue_element)
    {
      if(_develop_mode)
        std::cout << "develop_mode of buffer ID: " << _block_id << " is activated." << std::endl;
      message_port_register_in(pmt::mp("enqueue")); 
      set_msg_handler(pmt::mp("enqueue"), boost::bind(&frame_buffer_impl::enqueue, this, _1));
      message_port_register_in(pmt::mp("dequeue")); 
      set_msg_handler(pmt::mp("dequeue"), boost::bind(&frame_buffer_impl::dequeue, this, _1));
//      message_port_register_in(pmt::mp("preview")); 
//      set_msg_handler(pmt::mp("preview"), boost::bind(&frame_buffer_impl::preview, this, _1));
      message_port_register_in(pmt::mp("flush")); 
      set_msg_handler(pmt::mp("flush"), boost::bind(&frame_buffer_impl::flush, this, _1));
      message_port_register_out(pmt::mp("dequeue_element"));
    }

    /*
     * Our virtual destructor.
     */
    frame_buffer_impl::~frame_buffer_impl()
    {
    }

    void frame_buffer_impl::enqueue(pmt::pmt_t enqueue_element)
    {
      if(_develop_mode)
        std::cout << "++++++++++++ buffer ID: " << _block_id << " enqueue ++++++++++" << std::endl;
      if(_buffer.size() < _buffer_size)
      {
        _buffer.push(enqueue_element);
        if(_develop_mode)
          std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements after enqueue." << std::endl;

        if(_develop_mode == 2)
        {
          struct timeval t; 
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
          std::cout << "buffer ID: " << _block_id << " enqueue at time " << current_time << " s" << std::endl;
        }

        if((_dequeue_first && _auto_dequeue_first) || _dequeue_when_available)
        {
          message_port_pub(pmt::mp("dequeue_element"), _buffer.front());
          _buffer.pop();
          if(_develop_mode == 2)
          {
            struct timeval t; 
            gettimeofday(&t, NULL);
            double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
            std::cout << "buffer ID: " << _block_id << " dequeue at time " << current_time << " s" <<  std::endl;
          }
          if(_develop_mode && _dequeue_first && _auto_dequeue_first)
	  {
            std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements after auto-dequeue the first element." << std::endl;
            _dequeue_first = 0;
	  }
	  else if(_develop_mode && _dequeue_when_available)
	  {
            std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements after dequeue (postponed dequeue request)." << std::endl;
	    _dequeue_when_available = 0;
	  }
        }
      }
      else
        if(_develop_mode)
          std::cout << "buffer ID: " << _block_id << " is full. current element is discarded." << std::endl;
    }
    
    void frame_buffer_impl::dequeue(pmt::pmt_t dequeue_request)
    {
      if(_develop_mode)
        std::cout << "++++++++++++ buffer ID: " << _block_id << " dequeue ++++++++++" << std::endl;
      if(_buffer.size() > 0)
      {
 //       if(_output_dequeue_element)
        message_port_pub(pmt::mp("dequeue_element"), _buffer.front());
        _buffer.pop();
        if(_develop_mode)
          std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements after dequeue." << std::endl;
        if(_develop_mode == 2)
        {
          struct timeval t; 
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
          std::cout << "buffer ID: " << _block_id << " dequeue at time " << current_time << " s" << std::endl;
        }
      }
      else
      {
        if(_keep_dequeue_state)
	{
          _dequeue_when_available = 1;
	  if(_develop_mode)
            std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements. dequeue will be executed after next enqueue." << std::endl;
	}
        else
          if(_develop_mode)
            std::cout << "buffer ID: " << _block_id << " is empty. no element is popped." << std::endl;
      }
    }

/*
    void frame_buffer_impl::preview(pmt::pmt_t preview_request)
    {
      if(_develop_mode == 1)
        std::cout << "++++++++++++ buffer ID: " << _block_id << " preview ++++++++++" << std::endl;
      if(_buffer.size() > 0)
      {
        message_port_pub(pmt::mp("preview_element"), _buffer.front());
        if(_develop_mode == 1)
          std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements after preview." << std::endl;
      }
      else
        if(_develop_mode == 1)
          std::cout << "buffer ID: " << _block_id << " is empty. no element is previewed." << std::endl;
    }
*/
    void frame_buffer_impl::flush(pmt::pmt_t flush)
    {
      if(_develop_mode)
      {
        std::cout << "++++++++++++ buffer ID: " << _block_id << " flush ++++++++++++" << std::endl;
        std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements before flush." << std::endl;
      }
      int flush_length = _buffer.size();
      if(flush_length > 0)
      {
        for(int i = 0; i < flush_length; i++)
        {
          message_port_pub(pmt::mp("dequeue_element"), _buffer.front());
          _buffer.pop();
        }
        if(_develop_mode)
          std::cout << "buffer ID: " << _block_id << " has " << _buffer.size() << " elements after flush." << std::endl;
        if(_develop_mode == 2)
        {
          struct timeval t; 
          gettimeofday(&t, NULL);
          double current_time = t.tv_sec - double(int(t.tv_sec/10000)*10000) + t.tv_usec / 1000000.0;
          std::cout << "buffer ID: " << _block_id << " queue is flushed at time " << current_time << " s" << std::endl;
        }
      }
      else
        if(_develop_mode)
          std::cout << "buffer ID: " << _block_id << " is empty. no element is flushed." << std::endl;
    }
  } /* namespace inets */
} /* namespace gr */

