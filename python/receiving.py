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
from receive_frame_phy import receive_frame_phy  # grc-generated hier_block
import inets
import numpy
import time

class receiving(gr.hier_block2):
    """
    docstring for block receiving
    """
    def __init__(self, develop_mode=1, block_id=3, constellation=gnuradio.digital.constellation_qpsk().base(), matched_filter_coeff=(), mu=0, preamble=[], rx_gain=0, samp_rate=4e6, sps=4, threshold=30, usrp_device_address="addr=10.0.0.6"):
        gr.hier_block2.__init__(self,
            "receiving",
            gr.io_signature(0, 0, 0),  # Input signature
            gr.io_signaturev(4, 4, [gr.sizeof_gr_complex*1, gr.sizeof_gr_complex*1, gr.sizeof_float*1, gr.sizeof_gr_complex*1]),
        ) # Output signature

        self.message_port_register_hier_in("rx_switch_in")
        self.message_port_register_hier_out("rx_frame_out")
        self.message_port_register_hier_out("snr_out")
        self.message_port_register_hier_out("rx_power_out")

        ##################################################
        # Blocks
        ##################################################
        self.receive_frame_phy_0 = receive_frame_phy(
            block_id=block_id,
            constellation=constellation,
            develop_mode=develop_mode,
            matched_filter_coeff=matched_filter_coeff,
            mu=mu,
            preamble=preamble,
            rx_gain=rx_gain,
            samp_rate=samp_rate,
            sps=sps,
            threshold=threshold,
            usrp_device_address=usrp_device_address,
        )
        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.receive_frame_phy_0, 'rx_frame_out'), (self, 'rx_frame_out'))    
        self.msg_connect((self.receive_frame_phy_0, 'rx_power_out'), (self, 'rx_power_out'))    
        self.msg_connect((self.receive_frame_phy_0, 'snr_out'), (self, 'snr_out'))    
        self.msg_connect((self, 'rx_switch_in'), (self.receive_frame_phy_0, 'rx_switch_in'))    
        self.connect((self.receive_frame_phy_0, 0), (self, 0))
        self.connect((self.receive_frame_phy_0, 1), (self, 1))
        self.connect((self.receive_frame_phy_0, 2), (self, 2))
        self.connect((self.receive_frame_phy_0, 3), (self, 3))
