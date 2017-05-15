#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2017 <+YOU OR YOUR COMPANY+>.
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

from gnuradio import gr
from gnuradio import blocks
import inets
import pmt
import sys

class start(gr.hier_block2):
    """
    docstring for block start
    """
    def __init__(self):
        gr.hier_block2.__init__(self,
            "start",
            gr.io_signature(0, 0, 0),  # Input signature
            gr.io_signature(0, 0, 0)) # Output signature

        self.message_port_register_hier_out("trigger_out")
        ##################################################
        # Blocks
        ##################################################

        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("START"), 100)
        self.inets_message_strobe_filter_0 = inets.message_strobe_filter()
        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.inets_message_strobe_filter_0, 'message_strobe_in'))
        self.msg_connect((self.inets_message_strobe_filter_0, 'trigger_out'), (self, 'trigger_out'))    
