#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: new_theoretical_CSMA_II
# Author: PWA
# Generated: Tue Jul  4 10:28:18 2017
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
from optparse import OptionParser
import gnuradio
import inets
import sys
from gnuradio import qtgui


class new_theoretical_CSMA_II(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "new_theoretical_CSMA_II")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("new_theoretical_CSMA_II")
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

        self.settings = Qt.QSettings("GNU Radio", "new_theoretical_CSMA_II")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.6"
        self.tx_center_frequency = tx_center_frequency = 4.3e8
        self.timeout_duration_ms = timeout_duration_ms = 1000
        self.system_time_granularity_us = system_time_granularity_us = 10
        self.source_address = source_address = 3
        self.slot_time = slot_time = 4
        self.samp_rate = samp_rate = 400000
        self.rx_gain = rx_gain = 0
        self.rx_center_frequency = rx_center_frequency = 4.3e8

        self.rrc = rrc = firdes.root_raised_cosine(1.0, sps, 1, 0.5, 11*sps)

        self.mu = mu = 0.6
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.destination_address = destination_address = 2
        self.cs_threshold = cs_threshold = 0.001
        self.Single_rxp_time_s = Single_rxp_time_s = 500

        ##################################################
        # Blocks
        ##################################################
        self.inets_standard_timer_0 = inets.standard_timer(0, 51, slot_time, 10)
        self.inets_sending_0 = inets.sending(develop_mode=0, block_id=11, constellation=gnuradio.digital.constellation_qpsk().base(), preamble=diff_preamble_128, samp_rate=samp_rate, sps=sps, system_time_granularity_us=system_time_granularity_us, usrp_device_address=usrp_device_address, center_frequency=tx_center_frequency, interframe_interval_s=0.004, t_pretx_interval_s=0, file_name_extension_t_control="t1TXs", file_name_extension_pending="Tfr", record_on=0, name_with_timestamp=1, tx_gain=0)
        self.inets_run_0 = inets.run(20, 10)
        self.inets_receiving_0 = inets.receiving(1, 21, gnuradio.digital.constellation_qpsk().base(), rrc, mu, diff_preamble_128, rx_gain, samp_rate, sps, 30, usrp_device_address, rx_center_frequency)
        self.inets_random_filter_0_0 = inets.random_filter(0, 3, 0.03)
        self.inets_random_filter_0 = inets.random_filter(0, 3, 0.95)
        self.inets_parameter_list_0_0 = inets.parameter_list(0, 49, [13.3333, 10, 5])
        self.inets_parameter_list_0 = inets.parameter_list(0, 49, [1, 0.761405872543967,   0.461816006183166,   0.280105566896129, 0.169892614278690,   0.103045079418758 ,  0.062500000000000, 0.037908166232040, 0.022992465073215,   0.013945635009277, 0.008458455202288,   0.005130312413994, 0.003111691772991 , 0.001887336463895,   0.001144727430546, 1, 1, 0.923632012366331,0.560211133792258, 0.339785228557381, 0.206090158837516, 0.125, 0.075816332464079, 0.045984930146430 , 0.027891270018554, 0.016916910404577, 0.010260624827987 ,0.006223383545983, 0.00377467292779, 0.002289454861092, 1, 1, 1, 0.746948178389677, 0.453046971409841, 0.274786878450021, 0.166666666666667, 0.101088443285439, 0.061313240195240, 0.037188360024738, 0.022555880539435, 0.013680833103983, 0.008297844727977, 0.005032897237053, 0.003052606481456])
        self.inets_general_timer_1 = inets.general_timer(0, 5, 0, slot_time, 10, 0)
        self.inets_general_timer_0 = inets.general_timer(0, 5, 0, Single_rxp_time_s * 1000, 10, 0)
        self.inets_framing_0 = inets.framing(0, 17, 1, 1, 0, 1, destination_address, 1, source_address, 1, 318, 2, 524, 2, 2, 1, 1, 0, ([2, 3]), ([1000, 1000]), 2, 0, 300, 1)
        self.inets_frame_probe_0 = inets.frame_probe(2, 100, 0, 1, 0.001, 0, "/home/inets/source/gr-inets/results/", "", 1)
        self.inets_frame_counter_0_0 = inets.frame_counter(0, 36, 3, 0)
        self.inets_frame_counter_0 = inets.frame_counter(0, 36, 15, 0)
        self.inets_dummy_source_0 = inets.dummy_source(0, 23, 770, 3, 1)
        self.inets_counter_0_0_0_0 = inets.counter(3, 1, 1, "sent_3", 1, "/home/inets/source/gr-inets/results/", 0)
        self.inets_counter_0_0_0 = inets.counter(1, 1, 1, "tx_frame", 0, "/home/inets/source/gr-inets/results/", 0)
        self.inets_cmd_switch_0 = inets.cmd_switch(0, 47)
        self.inets_cmd_path_0_1 = inets.cmd_path(0, 44, 1)
        self.inets_cmd_path_0_0_0 = inets.cmd_path(0, 44, 1)
        self.inets_cmd_path_0_0 = inets.cmd_path(0, 44, 1)
        self.inets_cmd_path_0 = inets.cmd_path(0, 44, 1)
        self.inets_carrier_sensing_0 = inets.carrier_sensing(0, 11, 3, 100, cs_threshold, system_time_granularity_us, -1, 20)
        self.blocks_message_debug_0 = blocks.message_debug()

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_carrier_sensing_0, 'cmd_pass_out'), (self.inets_random_filter_0_0, 'cmd_in'))
        self.msg_connect((self.inets_cmd_path_0, 'cmd_out'), (self.inets_counter_0_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_cmd_path_0, 'cmd_out'), (self.inets_standard_timer_0, 'disable_timer_in'))
        self.msg_connect((self.inets_cmd_path_0_0, 'cmd_out'), (self.inets_cmd_switch_0, 'switch_on'))
        self.msg_connect((self.inets_cmd_path_0_0_0, 'cmd_out'), (self.inets_counter_0_0_0_0, 'message_in'))
        self.msg_connect((self.inets_cmd_path_0_1, 'cmd_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_cmd_path_0_1, 'cmd_out'), (self.inets_parameter_list_0_0, 'trigger_in'))
        self.msg_connect((self.inets_cmd_switch_0, 'cmd_out'), (self.inets_random_filter_0, 'cmd_in'))
        self.msg_connect((self.inets_dummy_source_0, 'output'), (self.inets_framing_0, 'data_in'))
        self.msg_connect((self.inets_frame_counter_0, 'select_out'), (self.inets_frame_counter_0_0, 'counts_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_frame_counter_0, 'unselect_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_frame_counter_0_0, 'select_out'), (self.inets_cmd_path_0, 'cmd_in'))
        self.msg_connect((self.inets_frame_counter_0_0, 'unselect_out'), (self.inets_cmd_path_0_1, 'cmd_in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_carrier_sensing_0, 'cmd_in'))
        self.msg_connect((self.inets_general_timer_0, 'expire_signal_out'), (self.inets_frame_counter_0, 'counts_in'))
        self.msg_connect((self.inets_general_timer_1, 'expire_signal_out'), (self.inets_carrier_sensing_0, 'cmd_in'))
        self.msg_connect((self.inets_parameter_list_0, 'parameter_out'), (self.inets_counter_0_0_0_0, 'reset_counter'))
        self.msg_connect((self.inets_parameter_list_0, 'parameter_out'), (self.inets_random_filter_0, 'set_threshold'))
        self.msg_connect((self.inets_parameter_list_0_0, 'parameter_out'), (self.inets_general_timer_1, 'reset_duration_in'))
        self.msg_connect((self.inets_parameter_list_0_0, 'parameter_out'), (self.inets_parameter_list_0, 'trigger_in'))
        self.msg_connect((self.inets_parameter_list_0_0, 'parameter_out'), (self.inets_standard_timer_0, 'reset_duration_in'))
        self.msg_connect((self.inets_random_filter_0, 'win_cmd_out'), (self.inets_cmd_switch_0, 'switch_off'))
        self.msg_connect((self.inets_random_filter_0, 'win_cmd_out'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_random_filter_0_0, 'win_cmd_out'), (self.inets_cmd_path_0_0_0, 'cmd_in'))
        self.msg_connect((self.inets_random_filter_0_0, 'lose_cmd_out'), (self.inets_general_timer_1, 'active_in'))
        self.msg_connect((self.inets_random_filter_0_0, 'win_cmd_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_power_out'), (self.inets_carrier_sensing_0, 'power_in'))
        self.msg_connect((self.inets_receiving_0, 'rx_switch_out'), (self.inets_sending_0, 'in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_parameter_list_0_0, 'trigger_in'))
        self.msg_connect((self.inets_run_0, 'trigger_out'), (self.inets_standard_timer_0, 'active_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_cmd_path_0_0, 'cmd_in'))
        self.msg_connect((self.inets_sending_0, 'data_frame_out'), (self.inets_counter_0_0_0, 'message_in'))
        self.msg_connect((self.inets_sending_0, 'rx_control_out'), (self.inets_receiving_0, 'rx_switch_in'))
        self.msg_connect((self.inets_standard_timer_0, 'expire_cmd_out'), (self.inets_cmd_switch_0, 'cmd_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "new_theoretical_CSMA_II")
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


def main(top_block_cls=new_theoretical_CSMA_II, options=None):

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
