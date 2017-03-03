#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Fri Mar  3 16:37:58 2017
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


class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Top Block")
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

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Blocks
        ##################################################
        self.inets_general_timer_0 = inets.general_timer(0, 3, 1, 100, 1000)
        self.inets_framing_0 = inets.framing(0, 17, 3, 1, 0, 1, 2, 1, 1, 1, 318, 2, 524, 2, 2, 1, 1, 0, ([1,2,3,4,5]), ([11, 513, 257, 300,100]), 2)
        self.inets_frame_probe_0 = inets.frame_probe(1, 100, 1)
        self.inets_frame_analysis_0 = inets.frame_analysis(0, 7, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2)
        self.inets_dummy_source_0 = inets.dummy_source(0, 23, 10, 2, 1)
        self.inets_beacon_interpreter_0 = inets.beacon_interpreter(1, 29, 1, 2)
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("TEST"), 1000)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.inets_dummy_source_0, 'trigger'))
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.inets_general_timer_0, 'active_in'))
        self.msg_connect((self.inets_beacon_interpreter_0, 'tx_sequence_out'), (self.inets_frame_probe_0, 'info_in'))
        self.msg_connect((self.inets_dummy_source_0, 'output'), (self.inets_framing_0, 'data_in'))
        self.msg_connect((self.inets_frame_analysis_0, 'frame_info_out'), (self.inets_beacon_interpreter_0, 'beacon_frame_in'))
        self.msg_connect((self.inets_framing_0, 'frame_pmt_out'), (self.inets_frame_analysis_0, 'frame_in'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate


def main(top_block_cls=top_block, options=None):

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
