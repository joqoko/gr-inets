#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: csma_80211_II
# Author: PWA
# Generated: Sun Jul 23 22:38:48 2017
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

from PyQt4 import Qt
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import gnuradio
import inets
import sys
from gnuradio import qtgui


class csma_80211_II(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "csma_80211_II")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("csma_80211_II")
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

        self.settings = Qt.QSettings("GNU Radio", "csma_80211_II")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.16"
        self.tx_center_frequency = tx_center_frequency = 3.9e8
        self.timeout_duration_ms = timeout_duration_ms = 100
        self.system_time_granularity_us = system_time_granularity_us = 10
        self.source_address = source_address = 2
        self.slot_time = slot_time = 8
        self.samp_rate = samp_rate = 400000
        self.rx_gain = rx_gain = 10
        self.rx_center_frequency = rx_center_frequency = 3.9e8

        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)

        self.mu = mu = 0.6
        self.min_window_size = min_window_size = 1
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.destination_address = destination_address = 100
        self.cs_threshold = cs_threshold = 0.001
        self.Single_rxp_time_s = Single_rxp_time_s = 60
        self.SIFS = SIFS = 10

        ##################################################
        # Blocks
        ##################################################
        self.inets_unbundle_0 = inets.unbundle(0, 16, "num_transmission")
        self.inets_timeout_0 = inets.timeout(0, 10, timeout_duration_ms, 1000, 0)
        self.inets_standard_timer_0 = inets.standard_timer(0, 51, slot_time, 10)
        self.inets_sending_0 = inets.sending(develop_mode=0, block_id=11, constellation=gnuradio.digital.constellation_qpsk().base(), preamble=diff_preamble_128, samp_rate=samp_rate, sps=sps, system_time_granularity_us=system_time_granularity_us, usrp_device_address=usrp_device_address, center_frequency=tx_center_frequency, interframe_interval_s=0.005, t_pretx_interval_s=0.0002, file_name_extension_t_control="t1TXs", file_name_extension_pending="Tfr", record_on=0, name_with_timestamp=0, tx_gain=10)
        self.inets_run_0_0 = inets.run(20, 10)
        self.inets_resend_check_0 = inets.resend_check(1, 24, 6)
        self.inets_receiving_0 = inets.receiving(0, 21, gnuradio.digital.constellation_qpsk().base(), rrc, mu, diff_preamble_128, rx_gain, samp_rate, sps, 30, usrp_device_address, rx_center_frequency)
        self.inets_random_filter_0 = inets.random_filter(0, 3, 0.95)
        self.inets_parameter_list_0 = inets.parameter_list(0, 49, [1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667, 1, 0.738905609893065, 0.448168907033806, 0.271828182845905, 0.164872127070013, 0.100000000000000, 0.060653065971263, 0.036787944117144, 0.022313016014843, 0.013533528323661, 0.008208499862390, 0.004978706836786, 0.003019738342232, 0.001831563888873, 0.001110899653824, 0.000673794699909, 0.000408677143846, 0.000247875217667])
        self.inets_number_recorder_0_1 = inets.number_recorder(0, 50, "node"+str(source_address)+"_bof_time", "/home/inets/source/gr-inets/results/", 0)
        self.inets_number_recorder_0_0 = inets.number_recorder(0, 50, "node"+str(source_address)+"_num_transmission", "/home/inets/source/gr-inets/results/", 0)
        self.inets_number_recorder_0 = inets.number_recorder(0, 50, "node"+str(source_address)+"_bof_busy", "/home/inets/source/gr-inets/results/", 0)
        self.inets_general_timer_0_2 = inets.general_timer(0, 5, 0, Single_rxp_time_s * 1000, 10, 0)
        self.inets_general_timer_0_1_0 = inets.general_timer(0, 3, 0, 0, 10, 0)
        self.inets_general_timer_0_1 = inets.general_timer(0, 3, 0, SIFS+slot_time * 2, 10, 0)
        self.inets_framing_0_0 = inets.framing(0, 17, 2, 1, 0, 1, destination_address, 1, source_address, 1, 318, 2, 524, 2, 2, 1, 1, 0, ([2, 3]), ([1000, 1000]), 2, 0, 300, 1)
        self.inets_framing_0 = inets.framing(0, 17, 1, 1, 0, 1, destination_address, 1, source_address, 1, 318, 2, 524, 2, 2, 1, 1, 0, ([2, 3]), ([1000, 1000]), 2, 0, 300, 1)
        self.inets_frame_type_check_1 = inets.frame_type_check(0, 25, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1)
        self.inets_frame_type_check_0_0 = inets.frame_type_check(0, 25, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1)
        self.inets_frame_type_check_0 = inets.frame_type_check(0, 25, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1)
        self.inets_frame_probe_1_0 = inets.frame_probe(1, 666, 0, 0, 0.01, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_probe_1 = inets.frame_probe(1, 999, 0, 0, 0.01, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_probe_0 = inets.frame_probe(1, 100, 0, 0, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_path_1_0_1 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0 = inets.frame_path(0, 39)
        self.inets_frame_lifetime_0_0 = inets.frame_lifetime(0, 201, 1, 1, "node"+str(source_address)+"_roundtime_fail", "/home/inets/source/gr-inets/results/", 0)
        self.inets_frame_lifetime_0 = inets.frame_lifetime(0, 202, 1, 1, "node"+str(source_address)+"_roundtime_success", "/home/inets/source/gr-inets/results/", 0)
        self.inets_frame_counter_0 = inets.frame_counter(0, 36, 14, 0)
        self.inets_frame_check_0 = inets.frame_check(0, 9)
        self.inets_frame_analysis_0 = inets.frame_analysis(0, 7, 1, 1, 1, 1, 1, 2, 2, 2, 1, source_address)
        self.inets_dummy_source_0 = inets.dummy_source(0, 23, 837, 3, 1)
        self.inets_counter_0_1_0 = inets.counter(1, 1, 1, "node"+str(source_address)+"_node1_ack", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_1 = inets.counter(1, 1, 1, "node"+str(source_address)+"_node1_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_3_0 = inets.counter(1, 3, 1, "node"+str(source_address)+"_node3_ack", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_3 = inets.counter(1, 3, 1, "node"+str(source_address)+"_node3_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_1_0 = inets.counter(1, 2, 1, "node"+str(source_address)+"_node2_ack", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_1 = inets.counter(1, 2, 1, "node"+str(source_address)+"_node2_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_1_0 = inets.counter(1, 4, 1, "node"+str(source_address)+"_node4_ack", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_1 = inets.counter(1, 4, 1, "node"+str(source_address)+"_node4_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_0_1 = inets.counter(0, 11, 1, "node"+str(source_address)+"_gen", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_0_0_1 = inets.counter(1, 11, 1, "node"+str(source_address)+"_dropped", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_0_0_0 = inets.counter(1, 11, 1, "node"+str(source_address)+"_retransmission", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_0_0 = inets.counter(1, 11, 1, "node"+str(source_address)+"_busy", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_0 = inets.counter(1, 11, 1, "node"+str(source_address)+"_sent", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0 = inets.counter(1, 10, 1, "node"+str(source_address)+"_acked", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0 = inets.counter(1, 1, 1, "node"+str(source_address)+"_bad_frame", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_cmd_switch_0 = inets.cmd_switch(0, 47)
        self.inets_cmd_path_1 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_path_0_0_2_0 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_path_0_0_2 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_path_0_0_1 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_path_0_0_0_0 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_path_0_0_0 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_path_0_0 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_path_0 = inets.cmd_path(0, 44, 1, "")
        self.inets_cmd_editor_0 = inets.cmd_editor(0, 52, "num_transmission", 1, 1)
        self.inets_carrier_sensing_0 = inets.carrier_sensing(0, 11, 4, 100, 0.005, system_time_granularity_us, 100, 5)
        self.inets_backoff_1 = inets.backoff(0, 11, 1, slot_time, slot_time, 100, 0, 0.005, 10, 1, min_window_size)
        self.inets_backoff_0 = inets.backoff(0, 11, 1, slot_time, slot_time, 400, 0, 0.005, 10, 1, min_window_size)
        self.inets_address_check_2_3 = inets.address_check(0, 17, 1, 0)
        self.inets_address_check_2_2_0 = inets.address_check(0, 17, 4, 0)
        self.inets_address_check_2_2 = inets.address_check(0, 17, 4, 1)
        self.inets_address_check_2_1_0 = inets.address_check(0, 17, 3, 0)
        self.inets_address_check_2_1 = inets.address_check(0, 17, 3, 1)
        self.inets_address_check_2_0_0 = inets.address_check(0, 17, 2, 0)
        self.inets_address_check_2_0 = inets.address_check(0, 17, 2, 1)
        self.inets_address_check_2 = inets.address_check(0, 17, 1, 1)
        self.inets_address_check_0 = inets.address_check(0, 17, source_address, 0)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_address_check_0, 'address_check_pass_out'), (self.inets_frame_type_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_address_check_2, 'address_check_pass_out'), (self.inets_counter_0_1, 'message_in'))
        self.msg_connect((self.inets_address_check_2_0, 'address_check_pass_out'), (self.inets_counter_0_0_1, 'message_in'))
        self.msg_connect((self.inets_address_check_2_0_0, 'address_check_pass_out'), (self.inets_counter_0_0_1_0, 'message_in'))
        self.msg_connect((self.inets_address_check_2_1, 'address_check_pass_out'), (self.inets_counter_0_0_3, 'message_in'))
        self.msg_connect((self.inets_address_check_2_1_0, 'address_check_pass_out'), (self.inets_counter_0_0_3_0, 'message_in'))
        self.msg_connect((self.inets_address_check_2_2, 'address_check_pass_out'), (self.inets_counter_0_0_0_1, 'message_in'))
        self.msg_connect((self.inets_address_check_2_2_0, 'address_check_pass_out'), (self.inets_counter_0_0_0_1_0, 'message_in'))
        self.msg_connect((self.inets_address_check_2_3, 'address_check_pass_out'), (self.inets_counter_0_1_0, 'message_in'))
        self.msg_connect((self.inets_backoff_0, 'frame_info_out'), (self.inets_cmd_editor_0, 'cmd_in'))
        self.msg_connect((self.inets_backoff_0, 'busy_time_out'), (self.inets_number_recorder_0, 'cmd_in'))
        self.msg_connect((self.inets_backoff_0, 'bof_time_out'), (self.inets_number_recorder_0_1, 'cmd_in'))
        self.msg_connect((self.inets_backoff_1, 'frame_info_out'), (self.inets_cmd_switch_0, 'switch_on'))
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_fail_out'), (self.inets_backoff_0, 'frame_info_in'))
        self.msg_connect((self.inets_carrier_sensing_0, 'cs_threshold_out'), (self.inets_backoff_0, 'cs_threshold_in'))
        self.msg_connect((self.inets_carrier_sensing_0, 'cs_threshold_out'), (self.inets_cmd_path_0_0_0_0, 'cmd_in'))
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_fail_out'), (self.inets_counter_0_0_0_0_0, 'message_in'))
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_fail_out'), (self.inets_frame_probe_1_0, 'info_in'))
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_pass_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_cmd_editor_0, 'cmd_out'), (self.inets_resend_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_cmd_path_0, 'cmd_out'), (self.inets_standard_timer_0, 'disable_timer_in'))
        self.msg_connect((self.inets_cmd_path_0_0, 'cmd_out'), (self.inets_cmd_path_0_0_2, 'cmd_in'))
        self.msg_connect((self.inets_cmd_path_0_0, 'cmd_out'), (self.inets_counter_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0, 'cmd_out'), (self.inets_counter_0_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0, 'cmd_out'), (self.inets_counter_0_0_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0, 'cmd_out'), (self.inets_counter_0_0_0_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0, 'cmd_out'), (self.inets_counter_0_0_0_0_1, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_0, 'cmd_out'), (self.inets_backoff_1, 'power_in'))
        self.msg_connect((self.inets_cmd_path_0_0_0_0, 'cmd_out'), (self.inets_backoff_1, 'cs_threshold_in'))
        self.msg_connect((self.inets_cmd_path_0_0_1, 'cmd_out'), (self.inets_frame_lifetime_0, 'change_file_name_in'))
        self.msg_connect((self.inets_cmd_path_0_0_1, 'cmd_out'), (self.inets_frame_lifetime_0_0, 'change_file_name_in'))
        self.msg_connect((self.inets_cmd_path_0_0_1, 'cmd_out'), (self.inets_number_recorder_0, 'change_file_name_in'))
        self.msg_connect((self.inets_cmd_path_0_0_1, 'cmd_out'), (self.inets_number_recorder_0_0, 'change_file_name_in'))
        self.msg_connect((self.inets_cmd_path_0_0_1, 'cmd_out'), (self.inets_number_recorder_0_1, 'change_file_name_in'))
        self.msg_connect((self.inets_cmd_path_0_0_2, 'cmd_out'), (self.inets_cmd_path_0_0_2_0, 'cmd_in'))
        self.msg_connect((self.inets_cmd_path_0_0_2, 'cmd_out'), (self.inets_counter_0_0_0_1, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_2, 'cmd_out'), (self.inets_counter_0_0_1, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_2, 'cmd_out'), (self.inets_counter_0_0_3, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_2, 'cmd_out'), (self.inets_counter_0_1, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_2_0, 'cmd_out'), (self.inets_counter_0_0_0_1_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_2_0, 'cmd_out'), (self.inets_counter_0_0_1_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_2_0, 'cmd_out'), (self.inets_counter_0_0_3_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0_0_2_0, 'cmd_out'), (self.inets_counter_0_1_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_1, 'cmd_out'), (self.inets_frame_type_check_1, 'frame_info_in'))
        self.msg_connect((self.inets_cmd_switch_0, 'cmd_out'), (self.inets_random_filter_0, 'cmd_in'))
        self.msg_connect((self.inets_dummy_source_0, 'output'), (self.inets_framing_0, 'data_in'))
        self.msg_connect((self.inets_frame_analysis_0, 'frame_info_out'), (self.inets_frame_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_address_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_cmd_path_1, 'cmd_in'))
        self.msg_connect((self.inets_frame_check_0, 'bad_frame_info_out'), (self.inets_counter_0_0, 'message_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_cmd_path_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_general_timer_0_2, 'active_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_frame_path_1_0, 'frame_out'), (self.inets_carrier_sensing_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_path_1_0, 'frame_out'), (self.inets_general_timer_0_1, 'active_in'))
        self.msg_connect((self.inets_frame_path_1_0_1, 'frame_out'), (self.inets_backoff_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_path_1_0_1, 'frame_out'), (self.inets_frame_probe_1, 'info_in'))
        self.msg_connect((self.inets_frame_type_check_0, 'data_frame_info_out'), (self.inets_framing_0_0, 'data_in'))
        self.msg_connect((self.inets_frame_type_check_0, 'ack_frame_info_out'), (self.inets_timeout_0, 'ack_frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_0_0, 'ack_frame_info_out'), (self.inets_backoff_1, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_0_0, 'ack_frame_info_out'), (self.inets_counter_0_0_0, 'message_in'))
        self.msg_connect((self.inets_frame_type_check_0_0, 'ack_frame_info_out'), (self.inets_frame_lifetime_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_type_check_0_0, 'data_frame_info_out'), (self.inets_frame_path_1_0_1, 'frame_in'))
        self.msg_connect((self.inets_frame_type_check_0_0, 'ack_frame_info_out'), (self.inets_unbundle_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'data_frame_info_out'), (self.inets_address_check_2, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'data_frame_info_out'), (self.inets_address_check_2_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'ack_frame_info_out'), (self.inets_address_check_2_0_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'data_frame_info_out'), (self.inets_address_check_2_1, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'ack_frame_info_out'), (self.inets_address_check_2_1_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'data_frame_info_out'), (self.inets_address_check_2_2, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'ack_frame_info_out'), (self.inets_address_check_2_2_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_type_check_1, 'ack_frame_info_out'), (self.inets_address_check_2_3, 'frame_info_in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_counter_0_0_0_0_1, 'message_in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_frame_path_1_0, 'frame_in'))
        self.msg_connect((self.inets_framing_0_0, 'frame_out'), (self.inets_general_timer_0_1_0, 'active_in'))
        self.msg_connect((self.inets_general_timer_0_1, 'expire_signal_out'), (self.inets_carrier_sensing_0, 'stop_in'))
        self.msg_connect((self.inets_general_timer_0_1_0, 'expire_signal_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_general_timer_0_2, 'expire_signal_out'), (self.inets_cmd_path_0_0, 'cmd_in'))
        self.msg_connect((self.inets_general_timer_0_2, 'expire_signal_out'), (self.inets_counter_0_0_0_0_0_1, 'reset_counter'))
        self.msg_connect((self.inets_general_timer_0_2, 'expire_signal_out'), (self.inets_frame_counter_0, 'counts_in'))
        self.msg_connect((self.inets_parameter_list_0, 'parameter_out'), (self.inets_cmd_path_0_0_1, 'cmd_in'))
        self.msg_connect((self.inets_parameter_list_0, 'n_parameter_out'), (self.inets_frame_counter_0, 'set_n_counts_in'))
        self.msg_connect((self.inets_parameter_list_0, 'parameter_out'), (self.inets_random_filter_0, 'set_threshold'))
        self.msg_connect((self.inets_random_filter_0, 'win_cmd_out'), (self.inets_cmd_switch_0, 'switch_off'))
        self.msg_connect((self.inets_random_filter_0, 'win_cmd_out'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_backoff_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_cmd_path_0_0_0, 'cmd_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_frame_out'), (self.inets_frame_analysis_0, 'frame_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_switch_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_resend_check_0, 'resend_check_fail_out'), (self.inets_cmd_switch_0, 'switch_on'))
        self.msg_connect((self.inets_resend_check_0, 'resend_check_pass_out'), (self.inets_counter_0_0_0_0_0_0, 'message_in'))
        self.msg_connect((self.inets_resend_check_0, 'resend_check_fail_out'), (self.inets_counter_0_0_0_0_0_1, 'message_in'))
        self.msg_connect((self.inets_resend_check_0, 'resend_check_fail_out'), (self.inets_frame_lifetime_0_0, 'cmd_in'))
        self.msg_connect((self.inets_resend_check_0, 'resend_check_pass_out'), (self.inets_frame_path_1_0, 'frame_in'))
        self.msg_connect((self.inets_resend_check_0, 'resend_check_fail_out'), (self.inets_unbundle_0, 'cmd_in'))
        self.msg_connect((self.inets_run_0_0, 'trigger_out'), (self.inets_general_timer_0_2, 'active_in'))
        self.msg_connect((self.inets_run_0_0, 'trigger_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_run_0_0, 'trigger_out'), (self.inets_standard_timer_0, 'active_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_counter_0_0_0_0, 'message_in'))
        self.msg_connect((self.inets_sending_0, 'rx_control_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_timeout_0, 'data_frame_info_in'))
        self.msg_connect((self.inets_standard_timer_0, 'expire_cmd_out'), (self.inets_cmd_switch_0, 'cmd_in'))
        self.msg_connect((self.inets_timeout_0, 'frame_info_out'), (self.inets_frame_type_check_0_0, 'frame_info_in'))
        self.msg_connect((self.inets_unbundle_0, 'cmd_out'), (self.inets_number_recorder_0_0, 'cmd_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "csma_80211_II")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps

    def get_usrp_device_address(self):
        return self.usrp_device_address

    def set_usrp_device_address(self, usrp_device_address):
        self.usrp_device_address = usrp_device_address

    def get_tx_center_frequency(self):
        return self.tx_center_frequency

    def set_tx_center_frequency(self, tx_center_frequency):
        self.tx_center_frequency = tx_center_frequency

    def get_timeout_duration_ms(self):
        return self.timeout_duration_ms

    def set_timeout_duration_ms(self, timeout_duration_ms):
        self.timeout_duration_ms = timeout_duration_ms

    def get_system_time_granularity_us(self):
        return self.system_time_granularity_us

    def set_system_time_granularity_us(self, system_time_granularity_us):
        self.system_time_granularity_us = system_time_granularity_us

    def get_source_address(self):
        return self.source_address

    def set_source_address(self, source_address):
        self.source_address = source_address

    def get_slot_time(self):
        return self.slot_time

    def set_slot_time(self, slot_time):
        self.slot_time = slot_time

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_rx_gain(self):
        return self.rx_gain

    def set_rx_gain(self, rx_gain):
        self.rx_gain = rx_gain

    def get_rx_center_frequency(self):
        return self.rx_center_frequency

    def set_rx_center_frequency(self, rx_center_frequency):
        self.rx_center_frequency = rx_center_frequency

    def get_rrc(self):
        return self.rrc

    def set_rrc(self, rrc):
        self.rrc = rrc

    def get_mu(self):
        return self.mu

    def set_mu(self, mu):
        self.mu = mu

    def get_min_window_size(self):
        return self.min_window_size

    def set_min_window_size(self, min_window_size):
        self.min_window_size = min_window_size

    def get_diff_preamble_128(self):
        return self.diff_preamble_128

    def set_diff_preamble_128(self, diff_preamble_128):
        self.diff_preamble_128 = diff_preamble_128

    def get_destination_address(self):
        return self.destination_address

    def set_destination_address(self, destination_address):
        self.destination_address = destination_address

    def get_cs_threshold(self):
        return self.cs_threshold

    def set_cs_threshold(self, cs_threshold):
        self.cs_threshold = cs_threshold

    def get_Single_rxp_time_s(self):
        return self.Single_rxp_time_s

    def set_Single_rxp_time_s(self, Single_rxp_time_s):
        self.Single_rxp_time_s = Single_rxp_time_s

    def get_SIFS(self):
        return self.SIFS

    def set_SIFS(self, SIFS):
        self.SIFS = SIFS


def main(top_block_cls=csma_80211_II, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
