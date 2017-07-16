#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: general_receiver
# Author: PWA
# Generated: Sun Jul 16 11:56:26 2017
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
from gnuradio.qtgui import Range, RangeWidget
from optparse import OptionParser
import gnuradio
import inets
import sys
from gnuradio import qtgui


class general_receiver(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "general_receiver")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("general_receiver")
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

        self.settings = Qt.QSettings("GNU Radio", "general_receiver")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.range_rx_gain = range_rx_gain = 0
        self.range_mu = range_mu = 0.6
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.14"
        self.system_time_granularity_us = system_time_granularity_us = 1000
        self.source_address = source_address = 12
        self.samp_rate = samp_rate = 400000
        self.rx_gain = rx_gain = range_rx_gain
        self.rx_center_frequency = rx_center_frequency = 3.9e8

        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)

        self.mu = mu = range_mu
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.destination_address = destination_address = 3
        self.cs_threshold = cs_threshold = 0.005

        ##################################################
        # Blocks
        ##################################################
        self._range_rx_gain_range = Range(0, 60, 1, 0, 200)
        self._range_rx_gain_win = RangeWidget(self._range_rx_gain_range, self.set_range_rx_gain, 'Rx Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_rx_gain_win, 1,0,1,1)
        self._range_mu_range = Range(0, 1, 0.01, 0.6, 200)
        self._range_mu_win = RangeWidget(self._range_mu_range, self.set_range_mu, 'BB Derotation Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_mu_win, 2,0,1,1)
        self.inets_time_probe_0 = inets.time_probe(0, 200, 1, 0, "", "/home/inets/source/gr-inets/results/", 1)
        self.inets_receiving_0 = inets.receiving(0, 21, gnuradio.digital.constellation_qpsk().base(), rrc, mu, diff_preamble_128, rx_gain, samp_rate, sps, 30, usrp_device_address, rx_center_frequency)
        self.inets_frame_probe_0_0_0 = inets.frame_probe(2, 100, 0, 1, 0.001, 0, "/home/inets/source/gr-inets/results/", "tcogmac", 0)
        self.inets_frame_probe_0_0 = inets.frame_probe(1, 100, 0, 1, 0.001, 0, "/home/inets/source/gr-inets/results/", "tcogmac", 0)
        self.inets_frame_path_0 = inets.frame_path(0, 39)
        self.inets_frame_index_selector_0_2 = inets.frame_index_selector(0, 33, (5, ), 1)
        self.inets_frame_index_selector_0_1_0_0 = inets.frame_index_selector(0, 33, (9, ), 1)
        self.inets_frame_index_selector_0_1_0 = inets.frame_index_selector(0, 33, (7, ), 1)
        self.inets_frame_index_selector_0_1 = inets.frame_index_selector(0, 33, (3, ), 1)
        self.inets_frame_index_selector_0_0_1 = inets.frame_index_selector(0, 33, (6, ), 1)
        self.inets_frame_index_selector_0_0_0_0_0 = inets.frame_index_selector(0, 33, (10, ), 1)
        self.inets_frame_index_selector_0_0_0_0 = inets.frame_index_selector(0, 33, (8, ), 1)
        self.inets_frame_index_selector_0_0_0 = inets.frame_index_selector(0, 33, (4, ), 1)
        self.inets_frame_index_selector_0_0 = inets.frame_index_selector(0, 33, (2, ), 1)
        self.inets_frame_index_selector_0 = inets.frame_index_selector(0, 33, (1, ), 1)
        self.inets_frame_check_0 = inets.frame_check(0, 9)
        self.inets_frame_analysis_0 = inets.frame_analysis(0, 7, 1, 1, 1, 1, 1, 2, 2, 2, 1, source_address)
        self.inets_counter_7 = inets.counter(1, 100, 1, "5", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_6 = inets.counter(1, 100, 1, "3", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_5_0 = inets.counter(1, 100, 1, "9", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_5 = inets.counter(1, 100, 1, "7", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_4 = inets.counter(1, 100, 1, "2", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_3 = inets.counter(1, 100, 1, "4", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_2_0 = inets.counter(1, 100, 1, "10", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_2 = inets.counter(1, 100, 1, "8", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_1 = inets.counter(1, 100, 1, "6", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_0 = inets.counter(1, 100, 1, "1", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_cogmac_rm_rep_0 = inets.cogmac_rm_rep(0, 37)
        self.inets_cmd_path_0 = inets.cmd_path(0, 44, 1)
        self.inets_carrier_sensing_0 = inets.carrier_sensing(3, 11, 4, 100, 0.005, system_time_granularity_us, 100, 20)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_cmd_path_0, 'cmd_out'), (self.inets_frame_analysis_0, 'frame_in'))
        self.msg_connect((self.inets_frame_analysis_0, 'frame_info_out'), (self.inets_frame_check_0, 'frame_info_in'))
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_frame_path_0, 'frame_in'))
        self.msg_connect((self.inets_frame_index_selector_0, 'frame_out'), (self.inets_counter_0, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0, 'frame_out'), (self.inets_counter_4, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0_0, 'frame_out'), (self.inets_counter_3, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0_0_0, 'frame_out'), (self.inets_counter_2, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0_0_0_0, 'frame_out'), (self.inets_counter_2_0, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0_1, 'frame_out'), (self.inets_counter_1, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_1, 'frame_out'), (self.inets_counter_6, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_1_0, 'frame_out'), (self.inets_counter_5, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_1_0_0, 'frame_out'), (self.inets_counter_5_0, 'message_in'))
        self.msg_connect((self.inets_frame_index_selector_0_2, 'frame_out'), (self.inets_counter_7, 'message_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_0_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_0_1, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_1, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_1_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_1_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_frame_index_selector_0_2, 'frame_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_frame_out'), (self.inets_cmd_path_0, 'cmd_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_frame_probe_0_0_0, 'info_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "general_receiver")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

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


def main(top_block_cls=general_receiver, options=None):

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
