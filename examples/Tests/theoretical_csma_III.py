#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: theoretical_csma_III
# Author: PWA
# Generated: Thu Jun 29 14:57:39 2017
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


class theoretical_csma_III(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "theoretical_csma_III")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("theoretical_csma_III")
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

        self.settings = Qt.QSettings("GNU Radio", "theoretical_csma_III")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.14"
        self.tx_center_frequency = tx_center_frequency = 4.3e8
        self.timeout_duration_ms = timeout_duration_ms = 1000
        self.system_time_granularity_us = system_time_granularity_us = 10
        self.source_address = source_address = 3
        self.samp_rate = samp_rate = 400000
        self.rx_gain = rx_gain = 0
        self.rx_center_frequency = rx_center_frequency = 4.3e8

        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)

        self.mu = mu = 0.6
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.destination_address = destination_address = 2
        self.cs_threshold = cs_threshold = 0.005

        ##################################################
        # Blocks
        ##################################################
        self.inets_time_probe_0 = inets.time_probe(1, 200, 0)
        self.inets_standard_timer_0 = inets.standard_timer(0, 51, 8, 10)
        self.inets_sending_0 = inets.sending(develop_mode=0, block_id=11, constellation=gnuradio.digital.constellation_qpsk().base(), preamble=diff_preamble_128, samp_rate=samp_rate, sps=sps, system_time_granularity_us=system_time_granularity_us, usrp_device_address=usrp_device_address, center_frequency=tx_center_frequency, interframe_interval_s=0, t_pretx_interval_s=0, file_name_extension_t_control="t1TXs", file_name_extension_pending="Tfr", record_on=0, name_with_timestamp=0, tx_gain=0)
        self.inets_run_0 = inets.run(20, 10)
        self.inets_receiving_0 = inets.receiving(0, 21, gnuradio.digital.constellation_qpsk().base(), rrc, mu, diff_preamble_128, rx_gain, samp_rate, sps, 30, usrp_device_address, rx_center_frequency)
        self.inets_random_filter_1 = inets.random_filter(0, 3, 0.019645)
        self.inets_random_filter_0 = inets.random_filter(0, 3, 0.03)
        self.inets_parameter_list_0 = inets.parameter_list(0, 49, [0.738905609893065,   0.448168907033806, 0.271828182845905,   0.164872127070013, 0.100000000000000, 0.060653065971263,   0.036787944117144,   0.022313016014843, 0.013533528323661,   0.008208499862390,   0.004978706836786, 0.003019738342232, 0.001831563888873])
        self.inets_general_timer_0_0 = inets.general_timer(1, 1, 0, 600000, 10, 0)
        self.inets_general_timer_0 = inets.general_timer(0, 5, 0, 8, 10, 0)
        self.inets_framing_0 = inets.framing(0, 17, 1, 1, 0, 1, destination_address, 1, source_address, 1, 318, 2, 524, 2, 2, 1, 1, 0, ([2, 3]), ([1000, 1000]), 2, 0, 300, 1)
        self.inets_frame_probe_1 = inets.frame_probe(2, 100, 0, 0, 0.01, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_probe_0 = inets.frame_probe(2, 100, 0, 1, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_counter_0 = inets.frame_counter(0, 36, 13, 0)
        self.inets_frame_buffer_1_0 = inets.frame_buffer(0, 16, 10, 0, 0, 0)
        self.inets_frame_buffer_0 = inets.frame_buffer(0, 16, 1, 0, 0, 0)
        self.inets_dummy_source_0 = inets.dummy_source(0, 23, 770, 3, 1)
        self.inets_counter_0_0_0_0 = inets.counter(3, 1, 1, "sent_3", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0 = inets.counter(1, 1, 1, "", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_counter_0 = inets.counter(1, 2, 1, "", 0, "/home/inets/source/gr-inets/results/", 1)
        self.inets_cmd_path_0_0_0 = inets.cmd_path(0, 44, 1)
        self.inets_cmd_path_0 = inets.cmd_path(0, 44, 1)
        self.inets_carrier_sensing_0 = inets.carrier_sensing(0, 11, 3, 3, 0.0015, system_time_granularity_us, -1, 20)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_pass_out'), (self.inets_frame_buffer_1_0, 'enqueue'))
        self.msg_connect((self.inets_cmd_path_0, 'cmd_out'), (self.inets_frame_buffer_0, 'dequeue'))
        self.msg_connect((self.inets_cmd_path_0, 'cmd_out'), (self.inets_frame_buffer_1_0, 'dequeue'))
        self.msg_connect((self.inets_cmd_path_0_0_0, 'cmd_out'), (self.inets_counter_0_0_0_0, 'message_in'))
        self.msg_connect((self.inets_cmd_path_0_0_0, 'cmd_out'), (self.inets_random_filter_1, 'cmd_in'))
        self.msg_connect((self.inets_dummy_source_0, 'output'), (self.inets_framing_0, 'data_in'))
        self.msg_connect((self.inets_frame_buffer_0, 'dequeue_element'), (self.inets_random_filter_1, 'cmd_in'))
        self.msg_connect((self.inets_frame_buffer_1_0, 'dequeue_element'), (self.inets_random_filter_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_general_timer_0_0, 'active_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_standard_timer_0, 'disable_timer_in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_carrier_sensing_0, 'cmd_in'))
        self.msg_connect((self.inets_general_timer_0, 'expire_signal_out'), (self.inets_carrier_sensing_0, 'cmd_in'))
        self.msg_connect((self.inets_general_timer_0_0, 'expire_signal_out'), (self.inets_counter_0_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_general_timer_0_0, 'expire_signal_out'), (self.inets_frame_counter_0, 'counts_in'))
        self.msg_connect((self.inets_general_timer_0_0, 'expire_signal_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_parameter_list_0, 'parameter_out'), (self.inets_random_filter_1, 'set_threshold'))
        self.msg_connect((self.inets_random_filter_0, 'lose_cmd_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_random_filter_0, 'win_cmd_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_random_filter_1, 'win_cmd_out'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_random_filter_1, 'lose_cmd_out'), (self.inets_frame_buffer_0, 'enqueue'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_switch_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_general_timer_0_0, 'active_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_standard_timer_0, 'active_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_cmd_path_0_0_0, 'cmd_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_counter_0, 'message_in'))
        self.msg_connect((self.inets_sending_0, 'rx_control_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_standard_timer_0, 'expire_cmd_out'), (self.inets_cmd_path_0, 'cmd_in'))
        self.msg_connect((self.inets_standard_timer_0, 'expire_cmd_out'), (self.inets_random_filter_1, 'cmd_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "theoretical_csma_III")
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


def main(top_block_cls=theoretical_csma_III, options=None):

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
