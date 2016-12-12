#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test_deframing_related
# Author: pwa
# Generated: Mon Dec 12 10:29:17 2016
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
import sys
from gnuradio import qtgui


class Test_deframing_related(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Test_deframing_related")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test_deframing_related")
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

        self.settings = Qt.QSettings("GNU Radio", "Test_deframing_related")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.source_address = source_address = 4
        self.samp_rate = samp_rate = 32000
        self.reserved_field_II = reserved_field_II = 6
        self.reserved_field_I = reserved_field_I = 5
        self.my_address = my_address = 3
        self.len_source_address = len_source_address = 1
        self.len_reserved_field_II = len_reserved_field_II = 2
        self.len_reserved_field_I = len_reserved_field_I = 2
        self.len_payload_length = len_payload_length = 1
        self.len_frame_type = len_frame_type = 1
        self.len_frame_index = len_frame_index = 1
        self.len_destination_address = len_destination_address = 1
        self.increase_index = increase_index = 1
        self.frame_type = frame_type = 1
        self.frame_index = frame_index = 2
        self.develop_mode_list = develop_mode_list = [1, 3, 4, 11]
        self.destination_address = destination_address = 3
        self.apply_address_check = apply_address_check = 0

        ##################################################
        # Blocks
        ##################################################
        self.inets_message_tomb_0 = inets.message_tomb()
        self.inets_framing_cpp_0 = inets.framing_cpp((develop_mode_list), frame_type, len_frame_type, frame_index, len_frame_index, destination_address, len_destination_address, source_address, len_source_address, reserved_field_I, len_reserved_field_I, reserved_field_II, len_reserved_field_II, len_payload_length, increase_index)
        self.inets_frame_verification_cpp_0 = inets.frame_verification_cpp(0)
        self.inets_frame_header_analysis_cpp_0 = inets.frame_header_analysis_cpp((develop_mode_list), len_frame_type, len_frame_index, len_destination_address, len_source_address, len_reserved_field_I, len_reserved_field_II, len_payload_length, apply_address_check)
        self.inets_address_check_cpp_0 = inets.address_check_cpp(0, my_address, apply_address_check)
        self.blocks_socket_pdu_0 = blocks.socket_pdu("UDP_SERVER", 'localhost', '52001', 10000, False)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_socket_pdu_0, 'pdus'), (self.inets_framing_cpp_0, 'payload_in'))    
        self.msg_connect((self.inets_address_check_cpp_0, 'frame_info_out'), (self.inets_frame_verification_cpp_0, 'frame_info_in'))    
        self.msg_connect((self.inets_frame_header_analysis_cpp_0, 'frame_info_out'), (self.inets_address_check_cpp_0, 'frame_info_in'))    
        self.msg_connect((self.inets_frame_header_analysis_cpp_0, 'frame_out'), (self.inets_message_tomb_0, 'message_in'))    
        self.msg_connect((self.inets_frame_verification_cpp_0, 'frame_info_out'), (self.inets_message_tomb_0, 'message_in'))    
        self.msg_connect((self.inets_frame_verification_cpp_0, 'good_frame'), (self.inets_message_tomb_0, 'message_in'))    
        self.msg_connect((self.inets_frame_verification_cpp_0, 'payload_out'), (self.inets_message_tomb_0, 'message_in'))    
        self.msg_connect((self.inets_framing_cpp_0, 'frame_out'), (self.inets_frame_header_analysis_cpp_0, 'frame_in'))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_deframing_related")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_source_address(self):
        return self.source_address

    def set_source_address(self, source_address):
        self.source_address = source_address

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_reserved_field_II(self):
        return self.reserved_field_II

    def set_reserved_field_II(self, reserved_field_II):
        self.reserved_field_II = reserved_field_II

    def get_reserved_field_I(self):
        return self.reserved_field_I

    def set_reserved_field_I(self, reserved_field_I):
        self.reserved_field_I = reserved_field_I

    def get_my_address(self):
        return self.my_address

    def set_my_address(self, my_address):
        self.my_address = my_address

    def get_len_source_address(self):
        return self.len_source_address

    def set_len_source_address(self, len_source_address):
        self.len_source_address = len_source_address

    def get_len_reserved_field_II(self):
        return self.len_reserved_field_II

    def set_len_reserved_field_II(self, len_reserved_field_II):
        self.len_reserved_field_II = len_reserved_field_II

    def get_len_reserved_field_I(self):
        return self.len_reserved_field_I

    def set_len_reserved_field_I(self, len_reserved_field_I):
        self.len_reserved_field_I = len_reserved_field_I

    def get_len_payload_length(self):
        return self.len_payload_length

    def set_len_payload_length(self, len_payload_length):
        self.len_payload_length = len_payload_length

    def get_len_frame_type(self):
        return self.len_frame_type

    def set_len_frame_type(self, len_frame_type):
        self.len_frame_type = len_frame_type

    def get_len_frame_index(self):
        return self.len_frame_index

    def set_len_frame_index(self, len_frame_index):
        self.len_frame_index = len_frame_index

    def get_len_destination_address(self):
        return self.len_destination_address

    def set_len_destination_address(self, len_destination_address):
        self.len_destination_address = len_destination_address

    def get_increase_index(self):
        return self.increase_index

    def set_increase_index(self, increase_index):
        self.increase_index = increase_index

    def get_frame_type(self):
        return self.frame_type

    def set_frame_type(self, frame_type):
        self.frame_type = frame_type

    def get_frame_index(self):
        return self.frame_index

    def set_frame_index(self, frame_index):
        self.frame_index = frame_index

    def get_develop_mode_list(self):
        return self.develop_mode_list

    def set_develop_mode_list(self, develop_mode_list):
        self.develop_mode_list = develop_mode_list

    def get_destination_address(self):
        return self.destination_address

    def set_destination_address(self, destination_address):
        self.destination_address = destination_address

    def get_apply_address_check(self):
        return self.apply_address_check

    def set_apply_address_check(self, apply_address_check):
        self.apply_address_check = apply_address_check


def main(top_block_cls=Test_deframing_related, options=None):

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
