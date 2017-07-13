#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: csma_80211_rx
# Author: PWA
# Generated: Fri Jul 14 01:04:00 2017
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


class csma_80211_rx(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "csma_80211_rx")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("csma_80211_rx")
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

        self.settings = Qt.QSettings("GNU Radio", "csma_80211_rx")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.6"
        self.tx_center_frequency = tx_center_frequency = 3.9e8
        self.timeout_duration_ms = timeout_duration_ms = 1000
        self.system_time_granularity_us = system_time_granularity_us = 10
        self.source_address = source_address = 100
        self.slot_time = slot_time = 8
        self.samp_rate = samp_rate = 400000
        self.rx_gain = rx_gain = 10
        self.rx_center_frequency = rx_center_frequency = 3.9e8

        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)

        self.mu = mu = 0.6
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.destination_address = destination_address = 101
        self.cs_threshold = cs_threshold = 0.001
        self.Single_rxp_time_s = Single_rxp_time_s = 5
        self.SIFS = SIFS = 10

        ##################################################
        # Blocks
        ##################################################
        self.inets_sending_0 = inets.sending(develop_mode=0, block_id=11, constellation=gnuradio.digital.constellation_qpsk().base(), preamble=diff_preamble_128, samp_rate=samp_rate, sps=sps, system_time_granularity_us=system_time_granularity_us, usrp_device_address=usrp_device_address, center_frequency=tx_center_frequency, interframe_interval_s=0.005, t_pretx_interval_s=0, file_name_extension_t_control="t1TXs", file_name_extension_pending="Tfr", record_on=0, name_with_timestamp=0, tx_gain=10)
        self.inets_run_0 = inets.run(20, 10)
        self.inets_receiving_0 = inets.receiving(0, 21, gnuradio.digital.constellation_qpsk().base(), rrc, mu, diff_preamble_128, rx_gain, samp_rate, sps, 30, usrp_device_address, rx_center_frequency)
        self.inets_general_timer_0_1_0 = inets.general_timer(0, 3, 0, 0, 10, 0)
        self.inets_general_timer_0 = inets.general_timer(0, 5, 0, Single_rxp_time_s * 1000, 10, 0)
        self.inets_framing_0_0 = inets.framing(0, 17, 2, 1, 0, 1, destination_address, 1, source_address, 1, 318, 2, 524, 2, 2, 1, 1, 0, ([2, 3]), ([1000, 1000]), 2, 0, 300, 1)
        self.inets_frame_type_check_0 = inets.frame_type_check(0, 25, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1)
        self.inets_frame_probe_0 = inets.frame_probe(2, 100, 0, 1, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_counter_0 = inets.frame_counter(0, 36, 19, 0)
        self.inets_frame_check_0 = inets.frame_check(0, 9)
        self.inets_frame_analysis_0 = inets.frame_analysis(0, 7, 1, 1, 1, 1, 1, 2, 2, 2, 1, source_address)
        self.inets_counter_0_1 = inets.counter(1, 1, 1, "rx_node1_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_3 = inets.counter(1, 3, 1, "rx_node3_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_1 = inets.counter(1, 2, 1, "rx_node2_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_1 = inets.counter(1, 4, 1, "rx_node4_data", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0_0 = inets.counter(1, 10, 1, "sent_ACK", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0 = inets.counter(1, 1, 1, "bad_frame", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_0 = inets.counter(1, 2, 1, "good_frame", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_cmd_path_1_0 = inets.cmd_path(0, 44, 1)
        self.inets_cmd_path_1 = inets.cmd_path(0, 44, 1)
        self.inets_cmd_path_0 = inets.cmd_path(0, 44, 1)
        self.inets_address_check_2_2 = inets.address_check(0, 17, 4, 1)
        self.inets_address_check_2_1 = inets.address_check(0, 17, 3, 1)
        self.inets_address_check_2_0 = inets.address_check(0, 17, 2, 1)
        self.inets_address_check_2 = inets.address_check(0, 17, 1, 1)
        self.inets_address_check_0 = inets.address_check(0, 17, source_address, 0)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_address_check_0, 'address_check_pass_out'), (self.inets_cmd_path_1, 'cmd_in'))
        self.msg_connect((self.inets_address_check_0, 'address_check_pass_out'), (self.inets_frame_type_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_address_check_2, 'address_check_pass_out'), (self.inets_counter_0_1, 'message_in'))
        self.msg_connect((self.inets_address_check_2_0, 'address_check_pass_out'), (self.inets_counter_0_0_1, 'message_in'))
        self.msg_connect((self.inets_address_check_2_1, 'address_check_pass_out'), (self.inets_counter_0_0_3, 'message_in'))
        self.msg_connect((self.inets_address_check_2_2, 'address_check_pass_out'), (self.inets_counter_0_0_0_1, 'message_in'))
        self.msg_connect((self.inets_cmd_path_0, 'cmd_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_cmd_path_1, 'cmd_out'), (self.inets_address_check_2, 'frame_info_in'))
        self.msg_connect((self.inets_cmd_path_1, 'cmd_out'), (self.inets_address_check_2_0, 'frame_info_in'))
        self.msg_connect((self.inets_cmd_path_1, 'cmd_out'), (self.inets_address_check_2_1, 'frame_info_in'))
        self.msg_connect((self.inets_cmd_path_1, 'cmd_out'), (self.inets_address_check_2_2, 'frame_info_in'))
        self.msg_connect((self.inets_cmd_path_1_0, 'cmd_out'), (self.inets_counter_0_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_1_0, 'cmd_out'), (self.inets_counter_0_0_0_1, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_1_0, 'cmd_out'), (self.inets_counter_0_0_1, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_1_0, 'cmd_out'), (self.inets_counter_0_0_3, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_1_0, 'cmd_out'), (self.inets_counter_0_1, 'reset_counter'))
        self.msg_connect((self.inets_frame_analysis_0, 'frame_info_out'), (self.inets_frame_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_address_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_counter_0, 'message_in'))
        self.msg_connect((self.inets_frame_check_0, 'bad_frame_info_out'), (self.inets_counter_0_0, 'message_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_cmd_path_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_cmd_path_1_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_cmd_path_1_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_type_check_0, 'data_frame_info_out'), (self.inets_framing_0_0, 'data_in'))
        self.msg_connect((self.inets_framing_0_0, 'frame_out'), (self.inets_general_timer_0_1_0, 'active_in'))
        self.msg_connect((self.inets_general_timer_0, 'expire_signal_out'), (self.inets_frame_counter_0, 'counts_in'))
        self.msg_connect((self.inets_general_timer_0_1_0, 'expire_signal_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_frame_out'), (self.inets_frame_analysis_0, 'frame_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_switch_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_sending_0, 'ack_frame_out'), (self.inets_counter_0_0_0_0, 'message_in'))
        self.msg_connect((self.inets_sending_0, 'rx_control_out'), (self.inets_receiving_0, 'rx_switch_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "csma_80211_rx")
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


def main(top_block_cls=csma_80211_rx, options=None):

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
