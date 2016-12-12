#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test_timeout_cpp
# Author: PWA
# Generated: Mon Dec 12 14:01:21 2016
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


class Test_timeout_cpp(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Test_timeout_cpp")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test_timeout_cpp")
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

        self.settings = Qt.QSettings("GNU Radio", "Test_timeout_cpp")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.timeout_duration_ms = timeout_duration_ms = 1000
        self.system_time_granularity_us = system_time_granularity_us = 1000
        self.samp_rate = samp_rate = 320000
        self.develop_mode_list = develop_mode_list = [1, 3, 4, 16]

        ##################################################
        # Blocks
        ##################################################
        self.inets_timeout_cpp_0 = inets.timeout_cpp((develop_mode_list), timeout_duration_ms, system_time_granularity_us)
        self.inets_message_tomb_0 = inets.message_tomb()
        self.inets_decision_cpp_0 = inets.decision_cpp((develop_mode_list), 14)
        self.blocks_message_strobe_random_0_0 = blocks.message_strobe_random(pmt.make_dict(), blocks.STROBE_POISSON, 2000, 1000)
        self.blocks_message_strobe_random_0 = blocks.message_strobe_random(pmt.make_dict(), blocks.STROBE_POISSON, 5000, 1000)
        self.blocks_message_debug_0 = blocks.message_debug()

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_random_0, 'strobe'), (self.inets_timeout_cpp_0, 'tx_frame_info_in'))    
        self.msg_connect((self.blocks_message_strobe_random_0_0, 'strobe'), (self.inets_timeout_cpp_0, 'ack_info_in'))    
        self.msg_connect((self.inets_decision_cpp_0, 'spark_out_t'), (self.blocks_message_debug_0, 'print'))    
        self.msg_connect((self.inets_decision_cpp_0, 'spark_out_f'), (self.inets_message_tomb_0, 'message_in'))    
        self.msg_connect((self.inets_timeout_cpp_0, 'spark_out'), (self.inets_decision_cpp_0, 'spark_in'))    
        self.msg_connect((self.inets_timeout_cpp_0, 'spark_out'), (self.inets_message_tomb_0, 'message_in'))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_timeout_cpp")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_timeout_duration_ms(self):
        return self.timeout_duration_ms

    def set_timeout_duration_ms(self, timeout_duration_ms):
        self.timeout_duration_ms = timeout_duration_ms

    def get_system_time_granularity_us(self):
        return self.system_time_granularity_us

    def set_system_time_granularity_us(self, system_time_granularity_us):
        self.system_time_granularity_us = system_time_granularity_us

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_develop_mode_list(self):
        return self.develop_mode_list

    def set_develop_mode_list(self, develop_mode_list):
        self.develop_mode_list = develop_mode_list


def main(top_block_cls=Test_timeout_cpp, options=None):

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
