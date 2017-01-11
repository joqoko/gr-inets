#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test_framing_cpp
# Author: PWA
# Generated: Wed Jan 11 17:05:57 2017
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

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from PyQt4 import Qt
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
from send_frame import send_frame  # grc-generated hier_block
import gnuradio
import inets
import pmt
from gnuradio import qtgui


class Test_framing_cpp(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Test_framing_cpp")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Test_framing_cpp")
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

        self.settings = Qt.QSettings("GNU Radio", "Test_framing_cpp")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.usrp_device_address = usrp_device_address = "addr=10.0.0.6"
        self.system_time_granularity_us = system_time_granularity_us = 1000
        self.sps = sps = 4
        self.source_address = source_address = 4
        self.samp_rate = samp_rate = 32000
        self.reserved_field_II = reserved_field_II = 6
        self.reserved_field_I = reserved_field_I = 5
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
        self.diff_preamble_128 = diff_preamble_128 = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1,1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0][0:128]
        self.develop_mode_list = develop_mode_list = [1, 2, 3]
        self.destination_address = destination_address = 3

        ##################################################
        # Blocks
        ##################################################
        self.send_frame_0 = send_frame(
            block_id=2,
            constellation=gnuradio.digital.constellation_qpsk().base(),
            destination_address=destination_address,
            develop_mode=1,
            frame_index=frame_index,
            frame_type=frame_type,
            increase_index=increase_index,
            len_destination_address=len_destination_address,
            len_frame_index=len_frame_index,
            len_frame_type=len_frame_type,
            len_payload_length=len_payload_length,
            len_reserved_field_I=len_reserved_field_I,
            len_reserved_field_II=len_reserved_field_II,
            len_source_address=len_source_address,
            preamble=diff_preamble_128,
            reserved_field_I=reserved_field_I,
            reserved_field_II=reserved_field_II,
            samp_rate=samp_rate,
            source_address=source_address,
            sps=sps,
            system_time_granularity_us=system_time_granularity_us,
            usrp_device_address=usrp_device_address,
        )
        self.inets_framing_0 = inets.framing(0, 17, len_frame_type, frame_index, len_frame_index, destination_address, len_destination_address, source_address, len_source_address, reserved_field_I, len_reserved_field_I, reserved_field_II, len_reserved_field_II, len_payload_length, 1)
        self.inets_frame_buffer_0 = inets.frame_buffer(1, 16, 10)
        self.blocks_socket_pdu_0 = blocks.socket_pdu("UDP_SERVER", 'localhost', '52001', 10000, False)
        self.blocks_message_strobe_random_0 = blocks.message_strobe_random(pmt.intern("TEST"), blocks.STROBE_POISSON, 1000, 100)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_random_0, 'strobe'), (self.inets_frame_buffer_0, 'dequeue'))
        self.msg_connect((self.blocks_socket_pdu_0, 'pdus'), (self.inets_framing_0, 'payload_in'))
        self.msg_connect((self.inets_frame_buffer_0, 'dequeue_element'), (self.send_frame_0, 'in'))
        self.msg_connect((self.inets_framing_0, 'frame_out'), (self.inets_frame_buffer_0, 'enqueue'))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "Test_framing_cpp")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_usrp_device_address(self):
        return self.usrp_device_address

    def set_usrp_device_address(self, usrp_device_address):
        self.usrp_device_address = usrp_device_address
        self.send_frame_0.set_usrp_device_address(self.usrp_device_address)

    def get_system_time_granularity_us(self):
        return self.system_time_granularity_us

    def set_system_time_granularity_us(self, system_time_granularity_us):
        self.system_time_granularity_us = system_time_granularity_us
        self.send_frame_0.set_system_time_granularity_us(self.system_time_granularity_us)

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.send_frame_0.set_sps(self.sps)

    def get_source_address(self):
        return self.source_address

    def set_source_address(self, source_address):
        self.source_address = source_address
        self.send_frame_0.set_source_address(self.source_address)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.send_frame_0.set_samp_rate(self.samp_rate)

    def get_reserved_field_II(self):
        return self.reserved_field_II

    def set_reserved_field_II(self, reserved_field_II):
        self.reserved_field_II = reserved_field_II
        self.send_frame_0.set_reserved_field_II(self.reserved_field_II)

    def get_reserved_field_I(self):
        return self.reserved_field_I

    def set_reserved_field_I(self, reserved_field_I):
        self.reserved_field_I = reserved_field_I
        self.send_frame_0.set_reserved_field_I(self.reserved_field_I)

    def get_len_source_address(self):
        return self.len_source_address

    def set_len_source_address(self, len_source_address):
        self.len_source_address = len_source_address
        self.send_frame_0.set_len_source_address(self.len_source_address)

    def get_len_reserved_field_II(self):
        return self.len_reserved_field_II

    def set_len_reserved_field_II(self, len_reserved_field_II):
        self.len_reserved_field_II = len_reserved_field_II
        self.send_frame_0.set_len_reserved_field_II(self.len_reserved_field_II)

    def get_len_reserved_field_I(self):
        return self.len_reserved_field_I

    def set_len_reserved_field_I(self, len_reserved_field_I):
        self.len_reserved_field_I = len_reserved_field_I
        self.send_frame_0.set_len_reserved_field_I(self.len_reserved_field_I)

    def get_len_payload_length(self):
        return self.len_payload_length

    def set_len_payload_length(self, len_payload_length):
        self.len_payload_length = len_payload_length
        self.send_frame_0.set_len_payload_length(self.len_payload_length)

    def get_len_frame_type(self):
        return self.len_frame_type

    def set_len_frame_type(self, len_frame_type):
        self.len_frame_type = len_frame_type
        self.send_frame_0.set_len_frame_type(self.len_frame_type)

    def get_len_frame_index(self):
        return self.len_frame_index

    def set_len_frame_index(self, len_frame_index):
        self.len_frame_index = len_frame_index
        self.send_frame_0.set_len_frame_index(self.len_frame_index)

    def get_len_destination_address(self):
        return self.len_destination_address

    def set_len_destination_address(self, len_destination_address):
        self.len_destination_address = len_destination_address
        self.send_frame_0.set_len_destination_address(self.len_destination_address)

    def get_increase_index(self):
        return self.increase_index

    def set_increase_index(self, increase_index):
        self.increase_index = increase_index
        self.send_frame_0.set_increase_index(self.increase_index)

    def get_frame_type(self):
        return self.frame_type

    def set_frame_type(self, frame_type):
        self.frame_type = frame_type
        self.send_frame_0.set_frame_type(self.frame_type)

    def get_frame_index(self):
        return self.frame_index

    def set_frame_index(self, frame_index):
        self.frame_index = frame_index
        self.send_frame_0.set_frame_index(self.frame_index)

    def get_diff_preamble_128(self):
        return self.diff_preamble_128

    def set_diff_preamble_128(self, diff_preamble_128):
        self.diff_preamble_128 = diff_preamble_128
        self.send_frame_0.set_preamble(self.diff_preamble_128)

    def get_develop_mode_list(self):
        return self.develop_mode_list

    def set_develop_mode_list(self, develop_mode_list):
        self.develop_mode_list = develop_mode_list

    def get_destination_address(self):
        return self.destination_address

    def set_destination_address(self, destination_address):
        self.destination_address = destination_address
        self.send_frame_0.set_destination_address(self.destination_address)


def main(top_block_cls=Test_framing_cpp, options=None):

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
