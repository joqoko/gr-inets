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

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))
from gnuradio import blocks
from gnuradio import digital
from gnuradio import filter
from gnuradio import gr
from gnuradio import uhd
from gnuradio.filter import firdes
import gnuradio
from receive_frame import receive_frame  # grc-generated hier_block
import inets
import numpy
import time

class receiving(gr.hier_block2):
    """
    docstring for block receiving
    """
    def __init__(self, n):
        gr.hier_block2.__init__(self,
            "receiving",
            gr.io_signature(0, 0, 0),  # Input signature
            gr.io_signature(0, 0, 0)
        ) # Output signature

        self.message_port_register_hier_in("rx_switch_in")
        self.message_port_register_hier_out("rx_frame_info_out")
        self.message_port_register_hier_out("rx_power_out")

        ##################################################
        # Blocks
        ##################################################
        self.receive_frame_0 = receive_frame(
            block_id=block_id,
            constellation=constellation,
            develop_mode=develop_mode,
            preamble=preamble,
            samp_rate=samp_rate,
            sps=sps,
            system_time_granularity_us=system_time_granularity_us,
            usrp_device_address=usrp_device_address,
        )
            # Define blocks and connect them
            self.connect()
