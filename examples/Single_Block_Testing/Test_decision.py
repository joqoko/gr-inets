#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test_decision
# Author: PWA
# Generated: Mon Dec 12 22:39:41 2016
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


class Test_decision(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Test_decision")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test_decision")
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

        self.settings = Qt.QSettings("GNU Radio", "Test_decision")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 320000
        self.develop_mode_list = develop_mode_list = [1, 3, 4, 14, 21, 22]

        ##################################################
        # Blocks
        ##################################################
        self.inets_null_message_source_0 = inets.null_message_source()
        self.inets_decision_cpp_0 = inets.decision_cpp((develop_mode_list), 14)
        self.inets_counter_0_0 = inets.counter((develop_mode_list), 22)
        self.inets_counter_0 = inets.counter((develop_mode_list), 21)
        self.blocks_message_strobe_random_0_0 = blocks.message_strobe_random(pmt.from_bool(False), blocks.STROBE_POISSON, 2000, 500)
        self.blocks_message_strobe_random_0 = blocks.message_strobe_random(pmt.from_bool(True), blocks.STROBE_POISSON, 3000, 500)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.inets_decision_cpp_0, 'spark_out_t'), (self.inets_counter_0, 'message_in'))    
        self.msg_connect((self.inets_decision_cpp_0, 'spark_out_f'), (self.inets_counter_0_0, 'message_in'))    
        self.msg_connect((self.inets_null_message_source_0, 'null_message_out'), (self.inets_decision_cpp_0, 'spark_in'))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_decision")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_develop_mode_list(self):
        return self.develop_mode_list

    def set_develop_mode_list(self, develop_mode_list):
        self.develop_mode_list = develop_mode_list


def main(top_block_cls=Test_decision, options=None):

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
