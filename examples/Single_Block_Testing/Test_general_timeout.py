#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test_general_timeout
# Author: PWA
# Generated: Mon Apr 17 17:22:49 2017
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


class Test_general_timeout(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Test_general_timeout")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test_general_timeout")
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

        self.settings = Qt.QSettings("GNU Radio", "Test_general_timeout")
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
        self.inets_general_timeout_0 = inets.general_timeout(1, 43, 1000, 1000, 1, 1)
        self.inets_framing_0 = inets.framing(0, 17, 1, 1, 0, 1, 1, 1, 2, 1, 318, 2, 524, 2, 2, 1, 1, 0, ([2, 3]), ([1000, 1000]), 2)
        self.inets_frame_probe_0_0 = inets.frame_probe(1, 101, 0, 0, 0.01)
        self.inets_frame_probe_0 = inets.frame_probe(0, 100, 0, 0, 0.01)
        self.inets_frame_index_selector_0 = inets.frame_index_selector(0, 41, ([1,2,3,4,5]), 0)
        self.inets_dummy_source_0 = inets.dummy_source(0, 23, 100, 1, 1)
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("TEST"), 1000)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.inets_dummy_source_0, 'output'), (self.inets_framing_0, 'data_in'))
        self.msg_connect((self.inets_frame_index_selector_0, 'frame_out'), (self.inets_general_timeout_0, 'frame_in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_frame_index_selector_0, 'frame_in'))
        self.msg_connect((self.inets_general_timeout_0, 'expired_frame_out'), (self.inets_frame_probe_0, 'info_in'))
        self.msg_connect((self.inets_general_timeout_0, 'killed_frame_out'), (self.inets_frame_probe_0_0, 'info_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_general_timeout")
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


def main(top_block_cls=Test_general_timeout, options=None):

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
