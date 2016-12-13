#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test_idle
# Author: PWA
# Generated: Tue Dec 13 01:26:17 2016
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
import inets
import pmt
import sys
from gnuradio import qtgui


class Test_idle(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Test_idle")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test_idle")
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

        self.settings = Qt.QSettings("GNU Radio", "Test_idle")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 320000
        self.my_address = my_address = 1
        self.max_num_retransmission = max_num_retransmission = 5
        self.max_buffer_size = max_buffer_size = 10
        self.experiment_duration_s = experiment_duration_s = 1000
        self.develop_mode_list = develop_mode_list = [1, 2, 3]

        ##################################################
        # Blocks
        ##################################################
        self.inets_null_message_source_0 = inets.null_message_source()
        self.inets_message_tomb_0 = inets.message_tomb()
        self.inets_idle_0 = inets.idle((develop_mode_list), experiment_duration_s, max_num_retransmission, max_buffer_size, my_address)
        self.blocks_socket_pdu_0 = blocks.socket_pdu("UDP_SERVER", 'localhost', '52001', 10000, False)
        self.blocks_message_strobe_random_0_0 = blocks.message_strobe_random(pmt.from_bool(True), blocks.STROBE_POISSON, 2000, 2000)
        self.blocks_message_debug_0 = blocks.message_debug()

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_socket_pdu_0, 'pdus'), (self.inets_idle_0, 'data_in'))    
        self.msg_connect((self.inets_idle_0, 'data_out'), (self.blocks_message_debug_0, 'print'))    
        self.msg_connect((self.inets_idle_0, 'successful_transmission'), (self.inets_message_tomb_0, 'message_in'))    
        self.msg_connect((self.inets_null_message_source_0, 'null_message_out'), (self.inets_idle_0, 'reset_idle'))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_idle")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_my_address(self):
        return self.my_address

    def set_my_address(self, my_address):
        self.my_address = my_address

    def get_max_num_retransmission(self):
        return self.max_num_retransmission

    def set_max_num_retransmission(self, max_num_retransmission):
        self.max_num_retransmission = max_num_retransmission

    def get_max_buffer_size(self):
        return self.max_buffer_size

    def set_max_buffer_size(self, max_buffer_size):
        self.max_buffer_size = max_buffer_size

    def get_experiment_duration_s(self):
        return self.experiment_duration_s

    def set_experiment_duration_s(self, experiment_duration_s):
        self.experiment_duration_s = experiment_duration_s

    def get_develop_mode_list(self):
        return self.develop_mode_list

    def set_develop_mode_list(self, develop_mode_list):
        self.develop_mode_list = develop_mode_list


def main(top_block_cls=Test_idle, options=None):

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
