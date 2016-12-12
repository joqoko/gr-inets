#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test Tx buffer function
# Author: PWA
# Generated: Mon Dec 12 09:31:37 2016
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


class Test_tx_buff(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Test Tx buffer function")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test Tx buffer function")
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

        self.settings = Qt.QSettings("GNU Radio", "Test_tx_buff")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.max_buffer_size = max_buffer_size = 5
        self.develop_mode_list = develop_mode_list = [1,2,3,4,5,6]

        ##################################################
        # Blocks
        ##################################################
        self.inets_tx_buffer_0 = inets.tx_buffer((develop_mode_list), max_buffer_size, 1)
        self.inets_message_tomb_0 = inets.message_tomb()
        self.blocks_socket_pdu_0 = blocks.socket_pdu("UDP_SERVER", 'localhost', '52001', 10000, False)
        self.blocks_message_strobe_random_0 = blocks.message_strobe_random(pmt.from_bool(True), blocks.STROBE_POISSON, 2500, 100)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_random_0, 'strobe'), (self.inets_tx_buffer_0, 'spark_in'))    
        self.msg_connect((self.blocks_socket_pdu_0, 'pdus'), (self.inets_tx_buffer_0, 'payload_in'))    
        self.msg_connect((self.inets_tx_buffer_0, 'payload_out'), (self.inets_message_tomb_0, 'message_in'))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_tx_buff")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_max_buffer_size(self):
        return self.max_buffer_size

    def set_max_buffer_size(self, max_buffer_size):
        self.max_buffer_size = max_buffer_size

    def get_develop_mode_list(self):
        return self.develop_mode_list

    def set_develop_mode_list(self, develop_mode_list):
        self.develop_mode_list = develop_mode_list


def main(top_block_cls=Test_tx_buff, options=None):

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
