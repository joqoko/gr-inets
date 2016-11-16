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
from gnuradio import uhd

class CarrierSensing(gr.basic_block):
    """
    docstring for block CarrierSensing
    """
    def __init__(self, cs_duration):
        gr.basic_block.__init__(self,
            name="CarrierSensing",
            in_sig=[],
            out_sig=[])
        self.message_port_register_in(pmt.intern('start_cs'))
        self.message_port_register_out(pmt.intern('CCA'))
        self.set_msg_handler(pmt.intern('start_cs'), self.handle_carrier_sensing)
        self.cs_duration = cs_duration 

    def handle_carrier_sensing(self)
        
