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
from receiving_phy import receiving_phy # grc-generated hier_block
import inets
import numpy
import time
import pmt

class multichannel_receiving(gr.basic_block):
    """
    docstring for block multichannel_receiving
    """
    def __init__(self, develop_mode, block_id, constellation, matched_filter_coeff, mu, preamble, rx_gain, samp_rate, sps, threshold, usrp_device_address, center_frequency):
        gr.basic_block.__init__(self,
            name="multichannel_receiving",
            in_sig=[],
            out_sig=[])

        self.message_port_register_in(pmt.intern('rx_switch_in'))
        self.message_port_register_in(pmt.intern("rx_frequency_in"))
        self.message_port_register_out(pmt.intern('rx_frame_out'))
        self.message_port_register_out(pmt.intern('snr_out'))
        self.message_port_register_out(pmt.intern('rx_power_out'))
        self.set_msg_handler(pmt.intern('rx_frequency_in'), self.handle_reset_frequency)

    def handle_reset_frequency(self, msg_pmt):
        self.center_frequency = pmt.to_long(msg_pmt)

        ##################################################
        # Blocks
        ##################################################
        self.receiving_phy_0 = receiving_phy(
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
            center_frequency=center_frequency,
        )

        self.msg_connect((self.receiving_phy_0, 'rx_frame_out'), (self, 'rx_frame_out'))    
        self.msg_connect((self.receiving_phy_0, 'snr_out'), (self, 'snr_out'))    
        self.msg_connect((self.receiving_phy_0, 'rx_power_out'), (self, 'rx_power_out'))    
        self.msg_connect((self, 'rx_switch_in'), (self.receiving_phy_0, 'rx_switch_in'))    
