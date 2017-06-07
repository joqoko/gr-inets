#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: CogMAC
# Author: PWA
# Generated: Wed Jun  7 19:35:45 2017
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


class CogMAC(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "CogMAC")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("CogMAC")
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

        self.settings = Qt.QSettings("GNU Radio", "CogMAC")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.range_rx_gain = range_rx_gain = 0
        self.range_mu = range_mu = 0.6
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.6"
        self.tx_center_frequency = tx_center_frequency = 4e8
        self.system_time_granularity_us = system_time_granularity_us = 1000
        self.source_address = source_address = 1
        self.samp_rate = samp_rate = 400000
        self.rx_gain = rx_gain = range_rx_gain
        self.rx_center_frequency = rx_center_frequency = 4e8

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
        self.inets_time_probe_0 = inets.time_probe(1, 200)
        self.inets_sending_0 = inets.sending(develop_mode=0, block_id=11, constellation=gnuradio.digital.constellation_qpsk().base(), preamble=diff_preamble_128, samp_rate=samp_rate, sps=sps, system_time_granularity_us=system_time_granularity_us, usrp_device_address=usrp_device_address, center_frequency=tx_center_frequency, interframe_interval_s=0.005, t_pretx_interval_s=0, file_name_extension_t_control="t1TXs", file_name_extension_pending="Tfr", record_on=0, name_with_timestamp=1, tx_gain=0)
        self.inets_run_0 = inets.run(1, 10)
        self.inets_receiving_0 = inets.receiving(0, 21, gnuradio.digital.constellation_qpsk().base(), rrc, mu, diff_preamble_128, rx_gain, samp_rate, sps, 30, usrp_device_address, rx_center_frequency)
        self.inets_general_timer_2_0_0 = inets.general_timer(0, 3, 0, 0, 10, 0)
        self.inets_general_timer_2_0 = inets.general_timer(0, 3, 0, 1000, 10, 0)
        self.inets_general_timer_2 = inets.general_timer(0, 3, 0, 200, 10, 0)
        self.inets_general_timer_1 = inets.general_timer(0, 3, 0, 5, 10, 0)
        self.inets_general_timer_0 = inets.general_timer(0, 3, 0, 100000, 10, 0)
        self.inets_framing_0 = inets.framing(0, 17, 1, 1, 10, 1, destination_address, 1, source_address, 1, 318, 2, 524, 2, 2, -1, 1, 0, ([2, 3]), ([1000, 1000]), 2, 0, 300, 1)
        self.inets_frame_replicate_0 = inets.frame_replicate(0, 37, 4)
        self.inets_frame_probe_0_1 = inets.frame_probe(1, 99, 0, 0, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_probe_0_0 = inets.frame_probe(2, 101, 0, 0, 0.01, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_probe_0 = inets.frame_probe(2, 100, 0, 0, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_path_1_1_0_0_1 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1_0_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_1 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0_1 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0_0_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1_0_0 = inets.frame_path(0, 39)
        self.inets_frame_path_1 = inets.frame_path(0, 39)
        self.inets_frame_path_0 = inets.frame_path(0, 39)
        self.inets_frame_index_selector_0_1 = inets.frame_index_selector(0, 33, (1, ), 1)
        self.inets_frame_index_selector_0_0_0 = inets.frame_index_selector(0, 33, (10, ), 0)
        self.inets_frame_index_selector_0_0 = inets.frame_index_selector(0, 33, (1, ), 0)
        self.inets_frame_index_selector_0 = inets.frame_index_selector(0, 33, (10, ), 0)
        self.inets_frame_counter_1 = inets.frame_counter(0, 36, 4)
        self.inets_frame_counter_0 = inets.frame_counter(1, 36, 4)
        self.inets_frame_check_0 = inets.frame_check(0, 9)
        self.inets_frame_buffer_0_0_0 = inets.frame_buffer(0, 16, 20, 1, 1, 0)
        self.inets_frame_buffer_0_0 = inets.frame_buffer(0, 16, 13, 0, 0, 0)
        self.inets_frame_buffer_0 = inets.frame_buffer(0, 16, 10, 0, 0, 1)
        self.inets_frame_and_0_0 = inets.frame_and(0, 38, 0)
        self.inets_frame_analysis_0 = inets.frame_analysis(0, 7, 1, 1, 1, 1, 1, 2, 2, 2, 1, source_address)
        self.inets_dummy_source_0 = inets.dummy_source(0, 23, 137, 3, 1)
        self.inets_cogmac_ch_pool_0 = inets.cogmac_ch_pool(0, 35, 1, 400000000, 0, 10000000)
        self.inets_carrier_sensing_0_1 = inets.carrier_sensing(0, 11, 2, 500, 0.005, system_time_granularity_us, 100, 25)
        self.inets_carrier_sensing_0_0 = inets.carrier_sensing(0, 11, 2, 10, 0.005, system_time_granularity_us, 100, 25)
        self.inets_carrier_sensing_0 = inets.carrier_sensing(0, 11, 2, 60, 0.005, system_time_granularity_us, 100, 25)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_carrier_sensing_0, 'frame_info_pass_out'), (self.inets_frame_counter_0, 'counts_in'))
        self.msg_connect((self.inets_carrier_sensing_0, 'frame_info_fail_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_carrier_sensing_0_0, 'frame_info_fail_out'), (self.inets_frame_path_1_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_carrier_sensing_0_0, 'frame_info_pass_out'), (self.inets_frame_probe_0_0, 'info_in'))
        self.msg_connect((self.inets_carrier_sensing_0_0, 'frame_info_fail_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_carrier_sensing_0_0, 'frame_info_pass_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_carrier_sensing_0_1, 'frame_info_pass_out'), (self.inets_frame_and_0_0, 'frame_I_in'))
        self.msg_connect((self.inets_carrier_sensing_0_1, 'frame_info_fail_out'), (self.inets_frame_path_1_0_0_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_one_f_out'), (self.inets_frame_path_1_0_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_CH_f_out'), (self.inets_frame_path_1_0_0_1, 'frame_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_one_f_out'), (self.inets_frame_path_1_0_0_1, 'frame_in'))
        self.msg_connect((self.inets_cogmac_ch_pool_0, 'CCA_CH_f_out'), (self.inets_general_timer_1, 'active_in'))
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
        self.msg_connect((self.inets_frame_check_0, 'good_frame_info_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_frame_path_1_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_frame_path_1_1_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_frame_path_1_1_0_0_1, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_1, 'select_out'), (self.inets_carrier_sensing_0_0, 'info_in'))
        self.msg_connect((self.inets_frame_counter_1, 'select_out'), (self.inets_frame_path_1_1_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_counter_1, 'select_out'), (self.inets_frame_probe_0_0, 'info_in'))
        self.msg_connect((self.inets_frame_counter_1, 'unselect_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_frame_index_selector_0, 'unselected_frame_out'), (self.inets_frame_path_1, 'frame_in'))
        self.msg_connect((self.inets_frame_index_selector_0, 'frame_out'), (self.inets_frame_replicate_0, 'frame_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0, 'unselected_frame_out'), (self.inets_frame_index_selector_0_0_0, 'frame_in'))
        self.msg_connect((self.inets_frame_index_selector_0_0_0, 'unselected_frame_out'), (self.inets_frame_buffer_0, 'dequeue'))
        self.msg_connect((self.inets_frame_index_selector_0_1, 'frame_out'), (self.inets_general_timer_2, 'active_in'))
        self.msg_connect((self.inets_frame_path_0, 'frame_out'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_frame_path_1, 'frame_out'), (self.inets_frame_buffer_0_0, 'enqueue'))
        self.msg_connect((self.inets_frame_path_1_0_0, 'frame_out'), (self.inets_cogmac_ch_pool_0, 'CCA_CH_in'))
        self.msg_connect((self.inets_frame_path_1_0_0_0, 'frame_out'), (self.inets_frame_buffer_0_0_0, 'flush'))
        self.msg_connect((self.inets_frame_path_1_0_0_0_0, 'frame_out'), (self.inets_carrier_sensing_0_1, 'info_in'))
        self.msg_connect((self.inets_frame_path_1_0_0_0_0_0, 'frame_out'), (self.inets_general_timer_2_0, 'active_in'))
        self.msg_connect((self.inets_frame_path_1_0_0_1, 'frame_out'), (self.inets_receiving_0, 'reconfig_in'))
        self.msg_connect((self.inets_frame_path_1_0_0_1, 'frame_out'), (self.inets_sending_0, 'reconfig_in'))
        self.msg_connect((self.inets_frame_path_1_1, 'frame_out'), (self.inets_frame_buffer_0_0, 'dequeue'))
        self.msg_connect((self.inets_frame_path_1_1_0_0, 'frame_out'), (self.inets_frame_counter_0, 'reset_in'))
        self.msg_connect((self.inets_frame_path_1_1_0_0_0, 'frame_out'), (self.inets_frame_counter_1, 'reset_in'))
        self.msg_connect((self.inets_frame_path_1_1_0_0_1, 'frame_out'), (self.inets_cogmac_ch_pool_0, 'CCA_one_in'))
        self.msg_connect((self.inets_frame_replicate_0, 'complete_out'), (self.inets_frame_buffer_0, 'dequeue'))
        self.msg_connect((self.inets_frame_replicate_0, 'replicate_out'), (self.inets_frame_path_1, 'frame_in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_frame_buffer_0, 'enqueue'))
        self.msg_connect((self.inets_general_timer_0, 'expire_signal_out'), (self.inets_dummy_source_0, 'stop_in'))
        self.msg_connect((self.inets_general_timer_1, 'expire_signal_out'), (self.inets_carrier_sensing_0, 'info_in'))
        self.msg_connect((self.inets_general_timer_2, 'expire_signal_out'), (self.inets_cogmac_ch_pool_0, 'CCA_CH_in'))
        self.msg_connect((self.inets_general_timer_2, 'expire_signal_out'), (self.inets_frame_counter_1, 'reset_in'))
        self.msg_connect((self.inets_general_timer_2, 'expire_signal_out'), (self.inets_frame_path_0, 'frame_in'))
        self.msg_connect((self.inets_general_timer_2_0, 'expire_signal_out'), (self.inets_frame_path_1_0_0, 'frame_in'))
        self.msg_connect((self.inets_general_timer_2_0_0, 'expire_signal_out'), (self.inets_frame_buffer_0_0_0, 'dequeue'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0_1, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_frame_out'), (self.inets_frame_analysis_0, 'frame_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_cogmac_ch_pool_0, 'CCA_CH_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_frame_index_selector_0_1, 'frame_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_frame_probe_0, 'info_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_general_timer_2_0_0, 'active_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "CogMAC")
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


def main(top_block_cls=CogMAC, options=None):

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
