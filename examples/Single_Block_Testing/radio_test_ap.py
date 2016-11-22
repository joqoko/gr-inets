#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Radio Test AP
# Author: Julian Arnold
# Generated: Tue Nov 22 23:57:54 2016
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
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import gnuradio
import inets
import numpy
import sip
import sys


class radio_test_ap(gr.top_block, Qt.QWidget):

    def __init__(self, constellation=gnuradio.digital.constellation_qpsk().base()):
        gr.top_block.__init__(self, "Radio Test AP")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Radio Test AP")
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

        self.settings = Qt.QSettings("GNU Radio", "radio_test_ap")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Parameters
        ##################################################
        self.constellation = constellation

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 4
        self.samp_rate = samp_rate = 4e6
        self.preamble = preamble = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0]

        ##################################################
        # Blocks
        ##################################################
        self.root_raised_cosine_filter_0 = filter.interp_fir_filter_ccf(sps, firdes.root_raised_cosine(
        	1, sps, 1.0, 0.8, 11*sps))
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
        	1024, #size
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(False)
        
        if not True:
          self.qtgui_const_sink_x_0.disable_legend()
        
        labels = ["", "", "", "", "",
                  "", "", "", "", ""]
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
                  "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_const_sink_x_0_win)
        self.inets_packetizer_0 = inets.packetizer((preamble), 64, constellation.bits_per_symbol() * (samp_rate / sps))
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bc((constellation.points()), 1)
        self.digital_burst_shaper_xx_0 = digital.burst_shaper_cc((gnuradio.fft.window.hanning(1024)), 0, 0, False, "packet_len")
        self.blocks_tagged_stream_multiply_length_0 = blocks.tagged_stream_multiply_length(gr.sizeof_gr_complex*1, "packet_len", sps)
        self.blocks_socket_pdu_0 = blocks.socket_pdu("UDP_SERVER", "localhost", "52001", 10000, False)
        self.blocks_repack_bits_bb_0 = blocks.repack_bits_bb(8, constellation.bits_per_symbol(), "packet_len", False, gr.GR_MSB_FIRST)
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.byte_t, "packet_len")
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_gr_complex*1)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vcc((0.6, ))

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_socket_pdu_0, 'pdus'), (self.inets_packetizer_0, 'payload_in'))    
        self.msg_connect((self.inets_packetizer_0, 'packet_out'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))    
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.digital_burst_shaper_xx_0, 0))    
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.blocks_repack_bits_bb_0, 0))    
        self.connect((self.blocks_repack_bits_bb_0, 0), (self.digital_chunks_to_symbols_xx_0, 0))    
        self.connect((self.blocks_tagged_stream_multiply_length_0, 0), (self.blocks_multiply_const_vxx_0, 0))    
        self.connect((self.digital_burst_shaper_xx_0, 0), (self.blocks_null_sink_0, 0))    
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.qtgui_const_sink_x_0, 0))    
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.root_raised_cosine_filter_0, 0))    
        self.connect((self.root_raised_cosine_filter_0, 0), (self.blocks_tagged_stream_multiply_length_0, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "radio_test_ap")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()


    def get_constellation(self):
        return self.constellation

    def set_constellation(self, constellation):
        self.constellation = constellation
        self.blocks_repack_bits_bb_0.set_k_and_l(8,self.constellation.bits_per_symbol())
        self.digital_chunks_to_symbols_xx_0.set_symbol_table((self.constellation.points()))

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.blocks_tagged_stream_multiply_length_0.set_scalar(self.sps)
        self.root_raised_cosine_filter_0.set_taps(firdes.root_raised_cosine(1, self.sps, 1.0, 0.8, 11*self.sps))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_preamble(self):
        return self.preamble

    def set_preamble(self, preamble):
        self.preamble = preamble


def argument_parser():
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    return parser


def main(top_block_cls=radio_test_ap, options=None):
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
