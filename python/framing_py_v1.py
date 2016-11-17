#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
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
from gnuradio import digital
import pmt
import threading

class framing_py_v1(gr.basic_block):
    """
    docstring for block framing_py_v1
    """
    DATA_FRAME = 1
    BROADCAST_ADDR = 0
    
    def __init__(self, fr_seq, src_addr):
        gr.basic_block.__init__(self,
            name="framing_py_v1",
            in_sig=[],
            out_sig=[])
        self.message_port_register_in(pmt.intern('payload_in'))
        self.message_port_register_out(pmt.intern('frame_out'))
        self.set_msg_handler(pmt.intern('payload_in'), self.handle_payload_message)
        self.fr_seq = 0
        self.src_addr = src_addr
        self.dest_addr = self.BROADCAST_ADDR

    def handle_payload_message(self, msg_pmt):
        # Get the payload from the pmt from the msg_pmt
        msg_str = self.get_data_str_from_pmt(msg_pmt)
        # Generate the whole MAC frame for the payload and other information
        send_pmt = self.frame_generation(msg_str)
        # Send the generated frame to PHY layer as a message
        self.message_port_pub(pmt.intern('frame_out'), send_pmt)

    # Attention: only the DATA frame is generated here
    def frame_generation(self, msg_str):
        # data frame
            # DATA frame structure: [fr_type fr_seq src_addr dest_addr payload_len payload CRC]
        msg_str = chr(len(msg_str)/256) + chr(int(len(msg_str) -float( len(msg_str))/256*256)) + msg_str
        msg_str = chr(self.dest_addr) + msg_str
        msg_str = chr(self.src_addr) + msg_str
        msg_str = chr(self.fr_seq) + msg_str
        msg_str = chr(self.DATA_FRAME) + msg_str
        msg_str = digital.crc.gen_and_append_crc32(msg_str)
        ## ACK frame structure: [fr_type src_addr dest_addr ACKed_DATA_seq CRC]
       # elif self.fr_type == ACK_FRAME:
       #     msg_str = chr(8) + msg_str
       #     msg_str = chr(self.dest_addr) + msg_str
       #     msg_str = chr(self.src_addr) + msg_str
       #     msg_str = chr(self.fr_seq) + msg_str
       #     msg_str = digital.crc.gen_and_append_crc(msg_str)

        send_pmt = self.get_pmt_from_data_str(msg_str)
        return send_pmt

    ##################### PMT helper function ########################
    # Get the first half, i.e., the name part of the pmt
    def get_meta_dict_from_pmt(self, msg_pmt):
        meta = pmt.to_python(pmt.car(msg_pmt))
        return meta

    # Get the second half, i.e., the real data part of the pmt
    def get_data_str_from_pmt(self, msg_pmt):
        msg = pmt.cdr(msg_pmt)
        msg_str = "".join([chr(x) for x in pmt.u8vector_elements(msg)])
        return msg_str

    # Create pmt according to a data string
    def get_pmt_from_data_str(self, msg_str):
        send_pmt = pmt.make_u8vector(len(msg_str), ord(' '))
        for i in range(len(msg_str)):
            pmt.u8vector_set(send_pmt, i, ord(msg_str[i]))
        send_pmt = pmt.cons(pmt.PMT_NIL, send_pmt)
        return send_pmt

