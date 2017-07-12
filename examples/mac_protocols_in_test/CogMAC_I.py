#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: CogMAC_I
# Author: PWA
# Generated: Tue Jul 11 17:18:13 2017
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
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.qtgui import Range, RangeWidget
from optparse import OptionParser
import gnuradio
import inets
import sys
from gnuradio import qtgui


class CogMAC_I(gr.top_block, Qt.QWidget):

    def __init__(self, constellation=gnuradio.digital.constellation_qpsk().base()):
        gr.top_block.__init__(self, "CogMAC_I")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("CogMAC_I")
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

        self.settings = Qt.QSettings("GNU Radio", "CogMAC_I")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Parameters
        ##################################################
        self.constellation = constellation

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.range_rx_gain = range_rx_gain = 0
        self.range_mu = range_mu = 0.6
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.6"
        self.tx_mode_ms = tx_mode_ms = 5
        self.system_time_granularity_us = system_time_granularity_us = 1000
        self.source_address = source_address = 1
        self.samp_rate = samp_rate = 400000
        self.rx_mode_ms = rx_mode_ms = 150
        self.rx_gain = rx_gain = range_rx_gain

        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)

        self.padding = padding = 64
        self.mu = mu = range_mu
        self.inter_fr_ms = inter_fr_ms = 20
        self.frame_length = frame_length = 837
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.destination_address = destination_address = 3
        self.cs_threshold = cs_threshold = 0.005
        self.ch_switch_ms = ch_switch_ms = 15
        self.ch_pool_size = ch_pool_size = 2
        self.center_frequency = center_frequency = 400000000
        self.PU_time_ms = PU_time_ms = 500
        self.N_Mul_Fr = N_Mul_Fr = 25
        self.CCA2_ms = CCA2_ms = 30

        ##################################################
        # Blocks
        ##################################################
        self._range_rx_gain_range = Range(0, 60, 1, 0, 200)
        self._range_rx_gain_win = RangeWidget(self._range_rx_gain_range, self.set_range_rx_gain, 'Rx Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_rx_gain_win, 1,0,1,1)
        self._range_mu_range = Range(0, 1, 0.01, 0.6, 200)
        self._range_mu_win = RangeWidget(self._range_mu_range, self.set_range_mu, 'BB Derotation Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_mu_win, 2,0,1,1)
        self.inets_unbundle_0_0_0_0_0 = inets.unbundle(0, 16, 'N_Mul_Fr')
        self.inets_unbundle_0_0_0_0 = inets.unbundle(0, 16, 'N_Fr')
        self.inets_unbundle_0_0_0 = inets.unbundle(0, 16, 'CCA1_ms')
        self.inets_unbundle_0_0 = inets.unbundle(0, 16, 'N_PU')
        self.inets_unbundle_0 = inets.unbundle(0, 16, 'N_Re_fr')
        self.inets_sending_0 = inets.sending(develop_mode=0, block_id=11, constellation=gnuradio.digital.constellation_qpsk().base(), preamble=diff_preamble_128, samp_rate=samp_rate, sps=sps, system_time_granularity_us=system_time_granularity_us, usrp_device_address=usrp_device_address, center_frequency=center_frequency, interframe_interval_s=inter_fr_ms / 1000, t_pretx_interval_s=0, file_name_extension_t_control="t1TXs", file_name_extension_pending="Tfr", record_on=0, name_with_timestamp=1, tx_gain=0)
        self.inets_run_0 = inets.run(1, 10)
        self.inets_receiving_0 = inets.receiving(0, 21, gnuradio.digital.constellation_qpsk().base(), rrc, mu, diff_preamble_128, rx_gain, samp_rate, sps, 30, usrp_device_address, center_frequency)
        self.inets_parameter_list_0 = inets.parameter_list(1, 49, [25,23,21,19,17,15,13,11,9,7,5,3])
        self.inets_general_timer_4 = inets.general_timer(0, 5, 0, 200000, 10, 0)
        self.inets_general_timer_3 = inets.general_timer(0, 3, 0, rx_mode_ms, 10, 0)
        self.inets_general_timer_2_0 = inets.general_timer(0, 3, 0, 100, 10, 0)
        self.inets_general_timer_2 = inets.general_timer(0, 3, 0, 200, 10, 0)
        self.inets_general_timer_1_0 = inets.general_timer(0, 3, 0, ch_switch_ms, 10, 0)
        self.inets_general_timer_1 = inets.general_timer(0, 3, 0, ch_switch_ms, 10, 0)
        self.inets_general_timer_0 = inets.general_timer(0, 5, 0, 20, 10, 0)
        self.inets_framing_0 = inets.framing(0, 17, 1, 1, 10, 1, destination_address, 1, source_address, 1, 318, 2, 524, 2, 2, -1, 1, 0, ([2, 3]), ([1000, 1000]), 2, 0, 300, 1)
        self.inets_frame_replicate_0 = inets.frame_replicate(0, 39, 4)
        self.inets_frame_redundancy_remover_0 = inets.frame_redundancy_remover(0, 49)
        self.inets_frame_probe_1 = inets.frame_probe(2, 999, 0, 0, 0.01, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_probe_0_1 = inets.frame_probe(1, 99, 0, 0, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_probe_0 = inets.frame_probe(1, 100, 0, 0, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_path_3_0 = inets.frame_path(0, 39)
        self.inets_frame_path_2_0 = inets.frame_path(0, 39)
        self.inets_frame_path_2 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1_0_0_1_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1_0_0_1 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1_0_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0_1_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0_1 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1 = inets.frame_path(0, 39)
        self.inets_frame_path_0 = inets.frame_path(0, 39)
        self.inets_frame_index_selector_0_1 = inets.frame_index_selector(0, 33, (1, ), 1)
        self.inets_frame_index_selector_0_0_0 = inets.frame_index_selector(0, 33, (10, ), 0)
        self.inets_frame_index_selector_0_0 = inets.frame_index_selector(0, 33, (1, ), 0)
        self.inets_frame_index_selector_0 = inets.frame_index_selector(0, 33, (10, ), 0)
        self.inets_frame_counter_2 = inets.frame_counter(0, 36, 15, 0)
        self.inets_frame_counter_1 = inets.frame_counter(0, 36, 4, 0)
        self.inets_frame_counter_0 = inets.frame_counter(1, 36, ch_pool_size, 0)
        self.inets_frame_check_0 = inets.frame_check(0, 9)
        self.inets_frame_buffer_0_0_0 = inets.frame_buffer(0, 16, 100, 1, 1, 0)
        self.inets_frame_buffer_0_0 = inets.frame_buffer(0, 16, 13, 0, 0, 0)
        self.inets_frame_buffer_0 = inets.frame_buffer(0, 15, 10, 0, 0, 1)
        self.inets_frame_and_0_0 = inets.frame_and(0, 38, 0)
        self.inets_frame_analysis_0 = inets.frame_analysis(0, 7, 1, 1, 1, 1, 1, 2, 2, 2, 1, source_address)
        self.inets_dummy_source_0 = inets.dummy_source(0, 23, frame_length, 3, 1)
        self.inets_counter_0 = inets.counter(0, 100, 1, "cogmac_tx", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_cogmac_timing_0 = inets.cogmac_timing(0, 37, frame_length, constellation.bits_per_symbol() * (samp_rate / sps), samp_rate, (diff_preamble_128), 64, CCA2_ms, PU_time_ms, tx_mode_ms, rx_mode_ms, 15, 148, inter_fr_ms, ch_pool_size, ch_switch_ms, N_Mul_Fr)
        self.inets_cogmac_rm_rep_0 = inets.cogmac_rm_rep(0, 37)
        self.inets_cogmac_ch_pool_0 = inets.cogmac_ch_pool(0, 35, ch_pool_size, 350000000, 0, 10000000)
        self.inets_carrier_sensing_0_1 = inets.carrier_sensing(0, 11, 2, 500, 0.005, system_time_granularity_us, 100, 15)
        self.inets_carrier_sensing_0_0 = inets.carrier_sensing(0, 13, 2, CCA2_ms, 0.005, system_time_granularity_us, 100, 15)
        self.inets_carrier_sensing_0 = inets.carrier_sensing(0, 111, 2, 60, 0.005, system_time_granularity_us, 100, 15)
        self.blocks_message_debug_0 = blocks.message_debug()

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_pass_out'), (self.inets_frame_counter_0, 'counts_in'))
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_fail_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_carrier_sensing_0_0, 'cmd_fail_out'), (self.inets_frame_path_1_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_carrier_sensing_0_0, 'cmd_pass_out'), (self.inets_frame_path_1_0_0_1_0, 'frame_in'))
        self.msg_connect((self.inets_carrier_sensing_0_0, 'cmd_fail_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_carrier_sensing_0_1, 'cmd_pass_out'), (self.inets_frame_and_0_0, 'frame_I_in'))
        self.msg_connect((self.inets_carrier_sensing_0_1, 'cmd_fail_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_CH_f_out'), (self.inets_frame_path_1_0_0_1, 'frame_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_one_f_out'), (self.inets_frame_path_1_0_0_1, 'frame_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_CH_f_out'), (self.inets_general_timer_1, 'active_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_one_f_out'), (self.inets_general_timer_1_0, 'active_in'))
        self.msg_connect((self.inets_cogmac_rm_rep_0, 'new_cmd_out'), (self.inets_frame_probe_0_1, 'info_in'))
        self.msg_connect((self.inets_cogmac_timing_0, 'cmd_out'), (self.inets_frame_path_1_1_0_0_1_0, 'frame_in'))
        self.msg_connect((self.inets_cogmac_timing_0, 'cmd_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_cogmac_timing_0, 'cogmac_config_out'), (self.inets_unbundle_0, 'cmd_in'))
        self.msg_connect((self.inets_cogmac_timing_0, 'cogmac_config_out'), (self.inets_unbundle_0_0, 'cmd_in'))
        self.msg_connect((self.inets_cogmac_timing_0, 'cogmac_config_out'), (self.inets_unbundle_0_0_0, 'cmd_in'))
        self.msg_connect((self.inets_cogmac_timing_0, 'cogmac_config_out'), (self.inets_unbundle_0_0_0_0, 'cmd_in'))
        self.msg_connect((self.inets_cogmac_timing_0, 'cogmac_config_out'), (self.inets_unbundle_0_0_0_0_0, 'cmd_in'))
        self.msg_connect((self.inets_dummy_source_0, 'output'), (self.inets_framing_0, 'data_in'))
        self.msg_connect((self.inets_frame_analysis_0, 'frame_info_out'), (self.inets_frame_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_and_0_0, 'frame_out'), (self.inets_frame_buffer_0_0, 'dequeue'))
        self.msg_connect((self.inets_frame_and_0_0, 'frame_out'), (self.inets_framing_0, 'reset_index'))
        self.msg_connect((self.inets_frame_buffer_0, 'dequeue_element'), (self.inets_frame_index_selector_0, 'frame_in'))
        self.msg_connect((self.inets_frame_buffer_0, 'dequeue_element'), (self.inets_frame_index_selector_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_buffer_0, 'buffer_not_full'), (self.inets_frame_path_0, 'frame_in'))
        self.msg_connect((self.inets_frame_buffer_0_0, 'buffer_full'), (self.inets_frame_and_0_0, 'frame_II_in'))
        self.msg_connect((self.inets_frame_buffer_0_0, 'dequeue_element'), (self.inets_frame_buffer_0_0_0, 'enqueue'))
        self.msg_connect((self.inets_frame_buffer_0_0, 'dequeue_element'), (self.inets_frame_path_1_1, 'frame_in'))
        self.msg_connect((self.inets_frame_buffer_0_0_0, 'dequeue_element'), (self.inets_frame_counter_1, 'counts_in'))
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_cogmac_rm_rep_0, 'frame_cmd_in'))
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_frame_path_1_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_frame_path_1_1_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_frame_path_1_1_0_0_1, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_1, 'unselect_out'), (self.inets_frame_path_1_0_0_1_0, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_1, 'select_out'), (self.inets_frame_path_1_1_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_1, 'select_out'), (self.inets_general_timer_3, 'active_in'))
        self.msg_connect((self.inets_frame_counter_2, 'select_out'), (self.inets_counter_0, 'reset_counter'))
        self.msg_connect((self.inets_frame_counter_2, 'unselect_out'), (self.inets_counter_0, 'reset_counter'))
        self.msg_connect((self.inets_frame_counter_2, 'select_out'), (self.inets_dummy_source_0, 'stop_in'))
        self.msg_connect((self.inets_frame_counter_2, 'unselect_out'), (self.inets_general_timer_4, 'active_in'))
        self.msg_connect((self.inets_frame_index_selector_0, 'unselected_frame_out'), (self.inets_frame_path_1, 'frame_in'))
        self.msg_connect((self.inets_frame_index_selector_0, 'frame_out'), (self.inets_frame_replicate_0, 'frame_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0, 'unselected_frame_out'), (self.inets_frame_index_selector_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0_0, 'unselected_frame_out'), (self.inets_frame_buffer_0, 'dequeue'))
        self.msg_connect((self.inets_frame_index_selector_0_1, 'frame_out'), (self.inets_general_timer_2, 'active_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_frame_path_1, 'frame_out'), (self.inets_frame_buffer_0_0, 'enqueue'))
        self.msg_connect((self.inets_frame_path_1_0_0, 'frame_out'), (self.inets_frame_path_1_1_0_0_1_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_1_0_0_0, 'frame_out'), (self.inets_frame_buffer_0_0_0, 'flush'))
        self.msg_connect((self.inets_frame_path_1_0_0_1, 'frame_out'), (self.inets_receiving_0, 'reconfig_in'))
        self.msg_connect((self.inets_frame_path_1_0_0_1, 'frame_out'), (self.inets_sending_0, 'reconfig_in'))
        self.msg_connect((self.inets_frame_path_1_0_0_1_0, 'frame_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_frame_path_1_1, 'frame_out'), (self.inets_frame_buffer_0_0, 'dequeue'))
        self.msg_connect((self.inets_frame_path_1_1_0_0, 'frame_out'), (self.inets_frame_counter_0, 'reset_in'))
        self.msg_connect((self.inets_frame_path_1_1_0_0_0, 'frame_out'), (self.inets_frame_counter_1, 'reset_in'))
        self.msg_connect((self.inets_frame_path_1_1_0_0_1, 'frame_out'), (self.inets_cogmac_ch_pool_0, 'CCA_one_in'))
        self.msg_connect((self.inets_frame_path_1_1_0_0_1_0, 'frame_out'), (self.inets_cogmac_ch_pool_0, 'CCA_CH_in'))
        self.msg_connect((self.inets_frame_path_2, 'frame_out'), (self.inets_frame_buffer_0_0_0, 'dequeue'))
        self.msg_connect((self.inets_frame_path_2_0, 'frame_out'), (self.inets_frame_counter_1, 'reset_in'))
        self.msg_connect((self.inets_frame_path_3_0, 'frame_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_frame_redundancy_remover_0, 'cmd_out'), (self.inets_counter_0, 'message_in'))
        self.msg_connect((self.inets_frame_replicate_0, 'complete_out'), (self.inets_frame_buffer_0, 'dequeue'))
        self.msg_connect((self.inets_frame_replicate_0, 'replicate_out'), (self.inets_frame_path_1, 'frame_in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_frame_buffer_0, 'enqueue'))
        self.msg_connect((self.inets_general_timer_0, 'expire_signal_out'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_general_timer_1, 'expire_signal_out'), (self.inets_carrier_sensing_0, 'cmd_in'))
        self.msg_connect((self.inets_general_timer_1_0, 'expire_signal_out'), (self.inets_carrier_sensing_0_1, 'cmd_in'))
        self.msg_connect((self.inets_general_timer_2, 'expire_signal_out'), (self.inets_frame_path_0, 'frame_in'))
        self.msg_connect((self.inets_general_timer_2, 'expire_signal_out'), (self.inets_frame_path_1_1_0_0_1_0, 'frame_in'))
        self.msg_connect((self.inets_general_timer_2, 'expire_signal_out'), (self.inets_frame_path_2_0, 'frame_in'))
        self.msg_connect((self.inets_general_timer_2_0, 'expire_signal_out'), (self.inets_frame_path_1_0_0, 'frame_in'))
        self.msg_connect((self.inets_general_timer_3, 'expire_signal_out'), (self.inets_carrier_sensing_0_0, 'cmd_in'))
        self.msg_connect((self.inets_general_timer_4, 'expire_signal_out'), (self.inets_frame_counter_2, 'counts_in'))
        self.msg_connect((self.inets_general_timer_4, 'expire_signal_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_parameter_list_0, 'parameter_out'), (self.inets_cogmac_timing_0, 'reset_N_Mul_Fr_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0_1, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_frame_out'), (self.inets_frame_analysis_0, 'frame_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_switch_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_cogmac_timing_0, 'trigger_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_frame_path_3_0, 'frame_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_general_timer_4, 'active_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_frame_index_selector_0_1, 'frame_in'))
        self.msg_connect((self.inets_sending_0, 'rx_control_out'), (self.inets_frame_path_2, 'frame_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_frame_probe_0, 'info_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_frame_redundancy_remover_0, 'cmd_in'))
        self.msg_connect((self.inets_sending_0, 'rx_control_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_unbundle_0, 'cmd_out'), (self.inets_frame_replicate_0, 'reset_number_in'))
        self.msg_connect((self.inets_unbundle_0_0, 'cmd_out'), (self.inets_frame_counter_1, 'set_n_counts_in'))
        self.msg_connect((self.inets_unbundle_0_0_0, 'cmd_out'), (self.inets_carrier_sensing_0, 'reset_duration_in'))
        self.msg_connect((self.inets_unbundle_0_0_0, 'cmd_out'), (self.inets_carrier_sensing_0_1, 'reset_duration_in'))
        self.msg_connect((self.inets_unbundle_0_0_0_0, 'cmd_out'), (self.inets_frame_buffer_0_0, 'reset_size_in'))
        self.msg_connect((self.inets_unbundle_0_0_0_0_0, 'cmd_out'), (self.inets_frame_buffer_0, 'reset_size_in'))
        self.msg_connect((self.inets_unbundle_0_0_0_0_0, 'cmd_out'), (self.inets_frame_index_selector_0, 'reset_index_in'))
        self.msg_connect((self.inets_unbundle_0_0_0_0_0, 'cmd_out'), (self.inets_frame_index_selector_0_0_0, 'reset_index_in'))
        self.msg_connect((self.inets_unbundle_0_0_0_0_0, 'cmd_out'), (self.inets_framing_0, 'reset_initial_index'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "CogMAC_I")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_constellation(self):
        return self.constellation

    def set_constellation(self, constellation):
        self.constellation = constellation

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps

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

    def get_usrp_device_address(self):
        return self.usrp_device_address

    def set_usrp_device_address(self, usrp_device_address):
        self.usrp_device_address = usrp_device_address

    def get_tx_mode_ms(self):
        return self.tx_mode_ms

    def set_tx_mode_ms(self, tx_mode_ms):
        self.tx_mode_ms = tx_mode_ms

    def get_system_time_granularity_us(self):
        return self.system_time_granularity_us

    def set_system_time_granularity_us(self, system_time_granularity_us):
        self.system_time_granularity_us = system_time_granularity_us

    def get_source_address(self):
        return self.source_address

    def set_source_address(self, source_address):
        self.source_address = source_address

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_rx_mode_ms(self):
        return self.rx_mode_ms

    def set_rx_mode_ms(self, rx_mode_ms):
        self.rx_mode_ms = rx_mode_ms

    def get_rx_gain(self):
        return self.rx_gain

    def set_rx_gain(self, rx_gain):
        self.rx_gain = rx_gain

    def get_rrc(self):
        return self.rrc

    def set_rrc(self, rrc):
        self.rrc = rrc

    def get_padding(self):
        return self.padding

    def set_padding(self, padding):
        self.padding = padding

    def get_mu(self):
        return self.mu

    def set_mu(self, mu):
        self.mu = mu

    def get_inter_fr_ms(self):
        return self.inter_fr_ms

    def set_inter_fr_ms(self, inter_fr_ms):
        self.inter_fr_ms = inter_fr_ms

    def get_frame_length(self):
        return self.frame_length

    def set_frame_length(self, frame_length):
        self.frame_length = frame_length

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

    def get_ch_switch_ms(self):
        return self.ch_switch_ms

    def set_ch_switch_ms(self, ch_switch_ms):
        self.ch_switch_ms = ch_switch_ms

    def get_ch_pool_size(self):
        return self.ch_pool_size

    def set_ch_pool_size(self, ch_pool_size):
        self.ch_pool_size = ch_pool_size

    def get_center_frequency(self):
        return self.center_frequency

    def set_center_frequency(self, center_frequency):
        self.center_frequency = center_frequency

    def get_PU_time_ms(self):
        return self.PU_time_ms

    def set_PU_time_ms(self, PU_time_ms):
        self.PU_time_ms = PU_time_ms

    def get_N_Mul_Fr(self):
        return self.N_Mul_Fr

    def set_N_Mul_Fr(self, N_Mul_Fr):
        self.N_Mul_Fr = N_Mul_Fr

    def get_CCA2_ms(self):
        return self.CCA2_ms

    def set_CCA2_ms(self, CCA2_ms):
        self.CCA2_ms = CCA2_ms


def argument_parser():
    parser = OptionParser(usage="%prog: [options]", option_class=eng_option)
    return parser


def main(top_block_cls=CogMAC_I, options=None):
    if options is None:
        options, _ = argument_parser().parse_args()

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
