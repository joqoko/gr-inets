#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test tx rx
# Author: PWA
# Generated: Tue Dec 13 16:53:57 2016
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from PyQt4 import Qt
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.qtgui import Range, RangeWidget
from optparse import OptionParser
from receive_frame import receive_frame  # grc-generated hier_block
from send_frame import send_frame  # grc-generated hier_block
import gnuradio
import inets
import numpy
import pmt
from gnuradio import qtgui


class Test_tx_rx(gr.top_block, Qt.QWidget):

    def __init__(self, apply_address_check=1, destination_address=3, frame_index=2, frame_type=1, increase_index=1, len_destination_address=1, len_frame_index=1, len_frame_type=1, len_payload_length=1, len_reserved_field_I=2, len_reserved_field_II=2, len_source_address=1, reserved_field_I=5, reserved_field_II=6, source_address=4, system_time_granularity_us=5):
        gr.top_block.__init__(self, "Test tx rx")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test tx rx")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "Test_tx_rx")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Parameters
        ##################################################
        self.apply_address_check = apply_address_check
        self.destination_address = destination_address
        self.frame_index = frame_index
        self.frame_type = frame_type
        self.increase_index = increase_index
        self.len_destination_address = len_destination_address
        self.len_frame_index = len_frame_index
        self.len_frame_type = len_frame_type
        self.len_payload_length = len_payload_length
        self.len_reserved_field_I = len_reserved_field_I
        self.len_reserved_field_II = len_reserved_field_II
        self.len_source_address = len_source_address
        self.reserved_field_I = reserved_field_I
        self.reserved_field_II = reserved_field_II
        self.source_address = source_address
        self.system_time_granularity_us = system_time_granularity_us

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.range_rx_gain = range_rx_gain = 15
        self.range_mu = range_mu = 0.6
        self.threshold = threshold = 40
        self.samp_rate = samp_rate = 4e6
        self.rx_gain = rx_gain = range_rx_gain
        
        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)
          
        self.range_noise = range_noise = 0
        self.qpsk_mod = qpsk_mod = gnuradio.digital.constellation_qpsk().base()
        self.preamble = preamble = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0]
        self.mu = mu = range_mu
        self.max_num_retransmission = max_num_retransmission = 5
        self.max_buffer_size = max_buffer_size = 10
        self.len_num_transmission = len_num_transmission = 1
        self.experiment_duration_s = experiment_duration_s = 1000
        self.diff_preamble_256 = diff_preamble_256 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0]
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.develop_mode_list = develop_mode_list = [0]
        self.bpsk_mod = bpsk_mod = gnuradio.digital.constellation_bpsk().base()

        ##################################################
        # Blocks
        ##################################################
        self.tab = Qt.QTabWidget()
        self.tab_widget_0 = Qt.QWidget()
        self.tab_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab_widget_0)
        self.tab_grid_layout_0 = Qt.QGridLayout()
        self.tab_layout_0.addLayout(self.tab_grid_layout_0)
        self.tab.addTab(self.tab_widget_0, 'TX')
        self.tab_widget_1 = Qt.QWidget()
        self.tab_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab_widget_1)
        self.tab_grid_layout_1 = Qt.QGridLayout()
        self.tab_layout_1.addLayout(self.tab_grid_layout_1)
        self.tab.addTab(self.tab_widget_1, 'RX')
        self.tab_widget_2 = Qt.QWidget()
        self.tab_layout_2 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab_widget_2)
        self.tab_grid_layout_2 = Qt.QGridLayout()
        self.tab_layout_2.addLayout(self.tab_grid_layout_2)
        self.tab.addTab(self.tab_widget_2, 'Demod')
        self.top_layout.addWidget(self.tab)
        self.send_frame_0 = send_frame(
            constellation=gnuradio.digital.constellation_qpsk().base(),
            destination_address=destination_address,
            develop_mode_list=develop_mode_list,
            frame_index=frame_index,
            frame_type=frame_type,
            increase_index=increase_index,
            len_destination_address=len_destination_address,
            len_frame_index=len_frame_index,
            len_frame_type=len_frame_type,
            len_payload_length=len_payload_length,
            len_reserved_field_I=len_reserved_field_I,
            len_reserved_field_II=len_reserved_field_II,
            len_source_address=len_source_address,
            preamble=diff_preamble_128,
            reserved_field_I=reserved_field_I,
            reserved_field_II=reserved_field_II,
            samp_rate=samp_rate,
            source_address=source_address,
            sps=sps,
            system_time_granularity_us=system_time_granularity_us,
        )
        self.receive_frame_0 = receive_frame(
            apply_address_check=apply_address_check,
            constellation=gnuradio.digital.constellation_qpsk().base(),
            develop_mode_list=[10],
            len_destination_address=len_destination_address,
            len_frame_index=len_frame_index,
            len_frame_type=len_frame_type,
            len_payload_length=len_payload_length,
            len_reserved_field_I=len_reserved_field_I,
            len_reserved_field_II=len_reserved_field_II,
            len_source_address=len_source_address,
            matched_filter_coeff=rrc,
            mu=mu,
            my_address=destination_address,
            preamble=diff_preamble_128,
            rx_gain=rx_gain,
            samp_rate=samp_rate,
            sps=sps,
            threshold=30,
        )
        self._range_rx_gain_range = Range(0, 60, 1, 15, 200)
        self._range_rx_gain_win = RangeWidget(self._range_rx_gain_range, self.set_range_rx_gain, 'Rx Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_rx_gain_win, 1,0,1,1)
        self._range_noise_range = Range(0, 0.01, 0.00001, 0, 200)
        self._range_noise_win = RangeWidget(self._range_noise_range, self.set_range_noise, 'noise', "counter_slider", float)
        self.top_layout.addWidget(self._range_noise_win)
        self._range_mu_range = Range(0, 1, 0.01, 0.6, 200)
        self._range_mu_win = RangeWidget(self._range_mu_range, self.set_range_mu, 'BB Derotation Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_mu_win, 2,0,1,1)
        self.inets_null_message_source_0 = inets.null_message_source()
        self.inets_message_tomb_0 = inets.message_tomb()
        self.inets_idle_0 = inets.idle((develop_mode_list), experiment_duration_s, max_num_retransmission, max_buffer_size, frame_type, len_frame_type, frame_index, len_frame_index, destination_address, len_destination_address, source_address, len_source_address, reserved_field_I, len_reserved_field_I, reserved_field_II, len_reserved_field_II, len_payload_length, increase_index, len_num_transmission)
        self.blocks_socket_pdu_0_0 = blocks.socket_pdu("UDP_SERVER", 'localhost', '52001', 10000, False)
        self.blocks_socket_pdu_0 = blocks.socket_pdu("UDP_SERVER", 'localhost', '52001', 10000, False)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_gr_complex*1)
        self.blocks_message_strobe_random_0 = blocks.message_strobe_random(pmt.from_bool(True), blocks.STROBE_POISSON, 10000, 5000)
        self.blocks_message_strobe_0_0 = blocks.message_strobe(pmt.from_bool(True), 1000)
        self.blocks_message_debug_0_0 = blocks.message_debug()

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_random_0, 'strobe'), (self.receive_frame_0, 'rx_switch_in'))    
        self.msg_connect((self.blocks_socket_pdu_0_0, 'pdus'), (self.inets_idle_0, 'data_in'))    
        self.msg_connect((self.inets_idle_0, 'successful_transmission'), (self.inets_message_tomb_0, 'message_in'))    
        self.msg_connect((self.inets_idle_0, 'data_out'), (self.send_frame_0, 'in'))    
        self.msg_connect((self.inets_null_message_source_0, 'null_message_out'), (self.inets_idle_0, 'reset_idle'))    
        self.msg_connect((self.receive_frame_0, 'rx_frame_info_out'), (self.blocks_message_debug_0_0, 'print'))    
        self.msg_connect((self.send_frame_0, 'tx_frame_info_out'), (self.inets_message_tomb_0, 'message_in'))    
        self.connect((self.send_frame_0, 0), (self.blocks_null_sink_0, 0))    
        self.connect((self.send_frame_0, 0), (self.receive_frame_0, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_tx_rx")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_apply_address_check(self):
        return self.apply_address_check

    def set_apply_address_check(self, apply_address_check):
        self.apply_address_check = apply_address_check
        self.receive_frame_0.set_apply_address_check(self.apply_address_check)

    def get_destination_address(self):
        return self.destination_address

    def set_destination_address(self, destination_address):
        self.destination_address = destination_address
        self.send_frame_0.set_destination_address(self.destination_address)
        self.receive_frame_0.set_my_address(self.destination_address)

    def get_frame_index(self):
        return self.frame_index

    def set_frame_index(self, frame_index):
        self.frame_index = frame_index
        self.send_frame_0.set_frame_index(self.frame_index)

    def get_frame_type(self):
        return self.frame_type

    def set_frame_type(self, frame_type):
        self.frame_type = frame_type
        self.send_frame_0.set_frame_type(self.frame_type)

    def get_increase_index(self):
        return self.increase_index

    def set_increase_index(self, increase_index):
        self.increase_index = increase_index
        self.send_frame_0.set_increase_index(self.increase_index)

    def get_len_destination_address(self):
        return self.len_destination_address

    def set_len_destination_address(self, len_destination_address):
        self.len_destination_address = len_destination_address
        self.send_frame_0.set_len_destination_address(self.len_destination_address)
        self.receive_frame_0.set_len_destination_address(self.len_destination_address)

    def get_len_frame_index(self):
        return self.len_frame_index

    def set_len_frame_index(self, len_frame_index):
        self.len_frame_index = len_frame_index
        self.send_frame_0.set_len_frame_index(self.len_frame_index)
        self.receive_frame_0.set_len_frame_index(self.len_frame_index)

    def get_len_frame_type(self):
        return self.len_frame_type

    def set_len_frame_type(self, len_frame_type):
        self.len_frame_type = len_frame_type
        self.send_frame_0.set_len_frame_type(self.len_frame_type)
        self.receive_frame_0.set_len_frame_type(self.len_frame_type)

    def get_len_payload_length(self):
        return self.len_payload_length

    def set_len_payload_length(self, len_payload_length):
        self.len_payload_length = len_payload_length
        self.send_frame_0.set_len_payload_length(self.len_payload_length)
        self.receive_frame_0.set_len_payload_length(self.len_payload_length)

    def get_len_reserved_field_I(self):
        return self.len_reserved_field_I

    def set_len_reserved_field_I(self, len_reserved_field_I):
        self.len_reserved_field_I = len_reserved_field_I
        self.send_frame_0.set_len_reserved_field_I(self.len_reserved_field_I)
        self.receive_frame_0.set_len_reserved_field_I(self.len_reserved_field_I)

    def get_len_reserved_field_II(self):
        return self.len_reserved_field_II

    def set_len_reserved_field_II(self, len_reserved_field_II):
        self.len_reserved_field_II = len_reserved_field_II
        self.send_frame_0.set_len_reserved_field_II(self.len_reserved_field_II)
        self.receive_frame_0.set_len_reserved_field_II(self.len_reserved_field_II)

    def get_len_source_address(self):
        return self.len_source_address

    def set_len_source_address(self, len_source_address):
        self.len_source_address = len_source_address
        self.send_frame_0.set_len_source_address(self.len_source_address)
        self.receive_frame_0.set_len_source_address(self.len_source_address)

    def get_reserved_field_I(self):
        return self.reserved_field_I

    def set_reserved_field_I(self, reserved_field_I):
        self.reserved_field_I = reserved_field_I
        self.send_frame_0.set_reserved_field_I(self.reserved_field_I)

    def get_reserved_field_II(self):
        return self.reserved_field_II

    def set_reserved_field_II(self, reserved_field_II):
        self.reserved_field_II = reserved_field_II
        self.send_frame_0.set_reserved_field_II(self.reserved_field_II)

    def get_source_address(self):
        return self.source_address

    def set_source_address(self, source_address):
        self.source_address = source_address
        self.send_frame_0.set_source_address(self.source_address)

    def get_system_time_granularity_us(self):
        return self.system_time_granularity_us

    def set_system_time_granularity_us(self, system_time_granularity_us):
        self.system_time_granularity_us = system_time_granularity_us
        self.send_frame_0.set_system_time_granularity_us(self.system_time_granularity_us)

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.send_frame_0.set_sps(self.sps)
        self.receive_frame_0.set_sps(self.sps)

    def get_range_rx_gain(self):
        return self.range_rx_gain

    def set_range_rx_gain(self, range_rx_gain):
        self.range_rx_gain = range_rx_gain
        self.set_rx_gain(self.range_rx_gain)

    def get_range_mu(self):
        return self.range_mu

    def set_range_mu(self, range_mu):
        self.range_mu = range_mu
        self.set_mu(self.range_mu)

    def get_threshold(self):
        return self.threshold

    def set_threshold(self, threshold):
        self.threshold = threshold

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.send_frame_0.set_samp_rate(self.samp_rate)
        self.receive_frame_0.set_samp_rate(self.samp_rate)

    def get_rx_gain(self):
        return self.rx_gain

    def set_rx_gain(self, rx_gain):
        self.rx_gain = rx_gain
        self.receive_frame_0.set_rx_gain(self.rx_gain)

    def get_rrc(self):
        return self.rrc

    def set_rrc(self, rrc):
        self.rrc = rrc
        self.receive_frame_0.set_matched_filter_coeff(self.rrc)

    def get_range_noise(self):
        return self.range_noise

    def set_range_noise(self, range_noise):
        self.range_noise = range_noise

    def get_qpsk_mod(self):
        return self.qpsk_mod

    def set_qpsk_mod(self, qpsk_mod):
        self.qpsk_mod = qpsk_mod

    def get_preamble(self):
        return self.preamble

    def set_preamble(self, preamble):
        self.preamble = preamble

    def get_mu(self):
        return self.mu

    def set_mu(self, mu):
        self.mu = mu
        self.receive_frame_0.set_mu(self.mu)

    def get_max_num_retransmission(self):
        return self.max_num_retransmission

    def set_max_num_retransmission(self, max_num_retransmission):
        self.max_num_retransmission = max_num_retransmission

    def get_max_buffer_size(self):
        return self.max_buffer_size

    def set_max_buffer_size(self, max_buffer_size):
        self.max_buffer_size = max_buffer_size

    def get_len_num_transmission(self):
        return self.len_num_transmission

    def set_len_num_transmission(self, len_num_transmission):
        self.len_num_transmission = len_num_transmission

    def get_experiment_duration_s(self):
        return self.experiment_duration_s

    def set_experiment_duration_s(self, experiment_duration_s):
        self.experiment_duration_s = experiment_duration_s

    def get_diff_preamble_256(self):
        return self.diff_preamble_256

    def set_diff_preamble_256(self, diff_preamble_256):
        self.diff_preamble_256 = diff_preamble_256

    def get_diff_preamble_128(self):
        return self.diff_preamble_128

    def set_diff_preamble_128(self, diff_preamble_128):
        self.diff_preamble_128 = diff_preamble_128
        self.send_frame_0.set_preamble(self.diff_preamble_128)
        self.receive_frame_0.set_preamble(self.diff_preamble_128)

    def get_develop_mode_list(self):
        return self.develop_mode_list

    def set_develop_mode_list(self, develop_mode_list):
        self.develop_mode_list = develop_mode_list
        self.send_frame_0.set_develop_mode_list(self.develop_mode_list)

    def get_bpsk_mod(self):
        return self.bpsk_mod

    def set_bpsk_mod(self, bpsk_mod):
        self.bpsk_mod = bpsk_mod


def argument_parser():
    parser = OptionParser(usage="%prog: [options]", option_class=eng_option)
    parser.add_option(
        "", "--apply-address-check", dest="apply_address_check", type="intx", default=1,
        help="Set apply_address_check [default=%default]")
    parser.add_option(
        "", "--destination-address", dest="destination_address", type="intx", default=3,
        help="Set destination_address [default=%default]")
    parser.add_option(
        "", "--frame-index", dest="frame_index", type="intx", default=2,
        help="Set frame_index [default=%default]")
    parser.add_option(
        "", "--frame-type", dest="frame_type", type="intx", default=1,
        help="Set frame_type [default=%default]")
    parser.add_option(
        "", "--increase-index", dest="increase_index", type="intx", default=1,
        help="Set increase_index [default=%default]")
    parser.add_option(
        "", "--len-destination-address", dest="len_destination_address", type="intx", default=1,
        help="Set len_destination_address [default=%default]")
    parser.add_option(
        "", "--len-frame-index", dest="len_frame_index", type="intx", default=1,
        help="Set len_frame_index [default=%default]")
    parser.add_option(
        "", "--len-frame-type", dest="len_frame_type", type="intx", default=1,
        help="Set len_frame_type [default=%default]")
    parser.add_option(
        "", "--len-payload-length", dest="len_payload_length", type="intx", default=1,
        help="Set len_payload_length [default=%default]")
    parser.add_option(
        "", "--len-reserved-field-I", dest="len_reserved_field_I", type="intx", default=2,
        help="Set len_reserved_field_I [default=%default]")
    parser.add_option(
        "", "--len-reserved-field-II", dest="len_reserved_field_II", type="intx", default=2,
        help="Set len_reserved_field_II [default=%default]")
    parser.add_option(
        "", "--len-source-address", dest="len_source_address", type="intx", default=1,
        help="Set len_source_address [default=%default]")
    parser.add_option(
        "", "--reserved-field-I", dest="reserved_field_I", type="intx", default=5,
        help="Set reserved_field_I [default=%default]")
    parser.add_option(
        "", "--reserved-field-II", dest="reserved_field_II", type="intx", default=6,
        help="Set reserved_field_II [default=%default]")
    parser.add_option(
        "", "--source-address", dest="source_address", type="intx", default=4,
        help="Set source_address [default=%default]")
    parser.add_option(
        "", "--system-time-granularity-us", dest="system_time_granularity_us", type="intx", default=5,
        help="Set system time granularity us [default=%default]")
    return parser


def main(top_block_cls=Test_tx_rx, options=None):
    if options is None:
        options, _ = argument_parser().parse_args()

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls(apply_address_check=options.apply_address_check, destination_address=options.destination_address, frame_index=options.frame_index, frame_type=options.frame_type, increase_index=options.increase_index, len_destination_address=options.len_destination_address, len_frame_index=options.len_frame_index, len_frame_type=options.len_frame_type, len_payload_length=options.len_payload_length, len_reserved_field_I=options.len_reserved_field_I, len_reserved_field_II=options.len_reserved_field_II, len_source_address=options.len_source_address, reserved_field_I=options.reserved_field_I, reserved_field_II=options.reserved_field_II, source_address=options.source_address, system_time_granularity_us=options.system_time_granularity_us)
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
