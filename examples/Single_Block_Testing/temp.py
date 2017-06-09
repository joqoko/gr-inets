#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: temp
# Generated: Thu Jun  8 17:26:36 2017
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


class temp(gr.top_block, Qt.QWidget):

    def __init__(self, constellation=gnuradio.digital.constellation_qpsk().base()):
        gr.top_block.__init__(self, "temp")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("temp")
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

        self.settings = Qt.QSettings("GNU Radio", "temp")
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
        self.tx_center_frequency = tx_center_frequency = 4e8
        self.system_time_granularity_us = system_time_granularity_us = 1000
        self.source_address = source_address = 1
        self.samp_rate = samp_rate = 400000
        self.rx_mode_ms = rx_mode_ms = 5
        self.rx_gain = rx_gain = range_rx_gain
        self.rx_center_frequency = rx_center_frequency = 4e8

        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)

        self.mu = mu = range_mu
        self.inter_fr_ms = inter_fr_ms = 5
        self.frame_length = frame_length = 837
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.destination_address = destination_address = 3
        self.cs_threshold = cs_threshold = 0.005
        self.ch_switch_ms = ch_switch_ms = 5
        self.PU_time_ms = PU_time_ms = 300
        self.CCA2_ms = CCA2_ms = 20

        ##################################################
        # Blocks
        ##################################################
        self._range_rx_gain_range = Range(0, 60, 1, 0, 200)
        self._range_rx_gain_win = RangeWidget(self._range_rx_gain_range, self.set_range_rx_gain, 'Rx Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_rx_gain_win, 1,0,1,1)
        self._range_mu_range = Range(0, 1, 0.01, 0.6, 200)
        self._range_mu_win = RangeWidget(self._range_mu_range, self.set_range_mu, 'BB Derotation Gain', "counter_slider", float)
        self.top_grid_layout.addWidget(self._range_mu_win, 2,0,1,1)
        self.inets_run_0 = inets.run(1, 10)
        self.inets_frame_probe_0 = inets.frame_probe(2, 100, 0, 0, 0.01, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_cogmac_timing_0 = inets.cogmac_timing(1, 37, frame_length, constellation.bits_per_symbol() * (samp_rate / sps), samp_rate, (diff_preamble_128), 64, CCA2_ms, PU_time_ms, tx_mode_ms, rx_mode_ms, 15, 148, inter_fr_ms, 4, ch_switch_ms)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_cogmac_timing_0, 'trigger_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "temp")
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

    def get_tx_center_frequency(self):
        return self.tx_center_frequency

    def set_tx_center_frequency(self, tx_center_frequency):
        self.tx_center_frequency = tx_center_frequency

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

    def get_PU_time_ms(self):
        return self.PU_time_ms

    def set_PU_time_ms(self, PU_time_ms):
        self.PU_time_ms = PU_time_ms

    def get_CCA2_ms(self):
        return self.CCA2_ms

    def set_CCA2_ms(self, CCA2_ms):
        self.CCA2_ms = CCA2_ms


def argument_parser():
    parser = OptionParser(usage="%prog: [options]", option_class=eng_option)
    return parser


def main(top_block_cls=temp, options=None):
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
