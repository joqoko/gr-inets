#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2015 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

import string
import numpy
import time
import Queue
from gnuradio import gr
import pmt
from gnuradio import digital
import threading

class stop_and_wait_arq(gr.basic_block):
    """
    docstring for block stop_and_wait_arq
    """
    STATE_WAIT_FOR_ACK = 0
    STATE_IDLE = 1
    PACKET_TYPE_DATA = 0
    PACKET_TYPE_ACK = 1

    def __init__(self):
        gr.basic_block.__init__(self,
            name="stop_and_wait_arq",
            in_sig=[],
            out_sig=[])
        self.message_port_register_in(pmt.intern('from_app'))
        self.message_port_register_out(pmt.intern('to_app'))
        self.message_port_register_in(pmt.intern('from_phy'))
        self.message_port_register_out(pmt.intern('to_phy'))
        self.set_msg_handler(pmt.intern('from_app'), self.handle_app_message)
        self.set_msg_handler(pmt.intern('from_phy'), self.handle_phy_message)
        self.app_queue = Queue.Queue() 
        self.state = self.STATE_IDLE
        self.last_tx_time = 0
        self.last_tx_packet = 0
        self.ack_timeout = 1.0 #in fractional seconds
        self.max_mtu_size = 200
        self.wait_for_frag = False
        self.packet_buffer = []
        self.last_frag_index = 0
        self.tx_seq_num = 0
        self.thread_lock = threading.Lock()        

    def handle_app_message(self, msg_pmt):
        #print 'app interrupt'
        with self.thread_lock:
          packets_str = self.fragment_packet(msg_pmt)
          for packet_str in packets_str:
            packet_str_total = chr(self.tx_seq_num)
            
            if self.tx_seq_num < 255:
              self.tx_seq_num = self.tx_seq_num + 1
            else:
              self.tx_seq_num = 0

            packet_str_total += chr(self.PACKET_TYPE_DATA) 
            packet_str_total += packet_str 
            packet_str_total = digital.crc.gen_and_append_crc32(packet_str_total)
            packet_str_total = digital.packet_utils.whiten(packet_str_total, 0)
            
            send_pmt = pmt.make_u8vector(len(packet_str_total), ord(' '))
            for i in range(len(packet_str_total)):
              pmt.u8vector_set(send_pmt, i, ord(packet_str_total[i]))
            
            send_pmt = pmt.cons(pmt.PMT_NIL, send_pmt)
            self.app_queue.put(send_pmt)
            self.handle_queue()

    def handle_queue(self):
        if self.state == self.STATE_IDLE:
          if self.app_queue.empty() == False:
            print 'Sending packet. Queue fill level = ', self.app_queue.qsize()
            self.last_tx_packet = self.app_queue.get()
            self.last_tx_time = time.time()
            self.state = self.STATE_WAIT_FOR_ACK
            
            self.message_port_pub(pmt.intern('to_phy'), self.last_tx_packet)
                
        elif self.state == self.STATE_WAIT_FOR_ACK:
          #print 'Not sending packet yet. ACK pending'
          if (time.time() - self.last_tx_time) > self.ack_timeout:
            #retransmit 
            print 'ACK timeout. Retransmitting'
            self.last_tx_time = time.time()
            self.message_port_pub(pmt.intern('to_phy'), self.last_tx_packet)

    def handle_phy_message(self, msg_pmt):        
        with self.thread_lock:
          print 'phy interrupt'
          meta = pmt.to_python(pmt.car(msg_pmt))
          msg = pmt.cdr(msg_pmt)
          msg_str = "".join([chr(x) for x in pmt.u8vector_elements(msg)])
          packet_str = digital.packet_utils.dewhiten(msg_str, 0)
          (ok, packet_str) = digital.crc.check_crc32(packet_str)
          if not ok:
            print '#######################################################'
            print '################## ERROR: Bad CRC #####################'
            print '#######################################################'
            return
          if ok:
            packet_rx_seq_byte = ord(packet_str[0])
            packet_str = packet_str[1:]
            packet_type_byte = ord(packet_str[0])
            packet_str = packet_str[1:]
            print 'packet received. seq = ', packet_rx_seq_byte, ' type = ', packet_type_byte
            if packet_type_byte == self.PACKET_TYPE_DATA:
              #send ACK packet
              print 'Sending ACK'
              ack_pdu = self.generate_ack_packet_pdu(packet_rx_seq_byte)
              self.message_port_pub(pmt.intern('to_phy'), ack_pdu)
              #process fragment
              self.process_fragment(packet_str)
            elif packet_type_byte == self.PACKET_TYPE_ACK:
              #mark curr packet as transmitted
              self.state = self.STATE_IDLE
              self.handle_queue()
    
    def generate_ack_packet_pdu(self, seq_num):
        packet_str = chr(seq_num)
        packet_str += chr(self.PACKET_TYPE_ACK) 
        #add dummy data. Otherwise FEC will make problems
        packet_str += 'aaa'
        packet_str = digital.crc.gen_and_append_crc32(packet_str)
        packet_str = digital.packet_utils.whiten(packet_str, 0)
         
        send_pmt = pmt.make_u8vector(len(packet_str), ord(' '))
        
        for i in range(len(packet_str)):
          pmt.u8vector_set(send_pmt, i, ord(packet_str[i]))
        
        return pmt.cons(pmt.PMT_NIL, send_pmt)

    def process_fragment(self, packet_str):
        frag_byte = ord(packet_str[0])  
        frag_index = frag_byte >> 2
        if frag_byte & 0x01 == 1 :
          self.last_frag_index = frag_index
          if frag_byte & 0x02 == 0 :
            self.wait_for_frag = True
            self.packet_buffer += packet_str[1:] 
            return
          else:
            self.wait_for_frag = False
            self.packet_buffer += packet_str[1:]
            packet_str = self.packet_buffer
            self.packet_buffer = ''
        else:
          packet_str = packet_str[1:]
          self.wait_for_frag = False
        if not self.wait_for_frag:
          send_pmt = pmt.make_u8vector(len(packet_str), ord(' '))
          for i in range(len(packet_str)):
            pmt.u8vector_set(send_pmt, i, ord(packet_str[i]))
          self.message_port_pub(pmt.intern('to_app'), pmt.cons(pmt.PMT_NIL, send_pmt))
      
    def fragment_packet(self, msg_pmt):
        meta = pmt.to_python(pmt.car(msg_pmt))
        msg = pmt.cdr(msg_pmt)
        if not pmt.is_u8vector(msg):
            print "ERROR wrong pmt format"
            return

        msg_str = "".join([chr(x) for x in pmt.u8vector_elements(msg)])

        num_mtus = (len(msg_str) // self.max_mtu_size)
        if len(msg_str) % self.max_mtu_size != 0:
          num_mtus = num_mtus + 1
          
        mtu_index_start = 0
        mtu_index_end = 0
        last = False
        frag = False
        frag_index = 0

        packet_list = []

        if num_mtus > 1:
          frag = True;
          
        for i in range(num_mtus):
          
          if (len(msg_str) - mtu_index_start) > self.max_mtu_size:
            mtu_index_end = mtu_index_start + self.max_mtu_size
          else:
            mtu_index_end = len(msg_str)
            last = True

          fragment_str = msg_str[mtu_index_start:mtu_index_end]
         
          packet = self.add_frag_hdr(fragment_str, frag, last, i)
          
          mtu_index_start += self.max_mtu_size

          # Send the message:
          packet_list.append(packet)
        
        return packet_list
    
    def add_frag_hdr(self, payload_str, frag, last_frag, frag_index): 
        hdr_str = ''
        if not frag:
          hdr_str = '\x00'
        else:
          frag_byte = 0
          if not last_frag:
            frag_byte = 1 | frag_index << 2 
          else:
            frag_byte = 3 | frag_index << 2
          hdr_str = chr(frag_byte)
        
        packet_str = hdr_str + payload_str
        return packet_str

    def get_packet_type(msg_pmt):
        meta = pmt.to_python(pmt.car(msg_pmt))
        msg = pmt.cdr(msg_pmt)
        data = pmt.u8vector_elements(msg)
        packet_type = data[0]

            
