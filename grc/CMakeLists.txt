# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
install(FILES
    inets_frame_sync_cc.xml
    inets_timing_recovery_cc.xml
    inets_packetizer.xml
    inets_packetizer_python.xml
    inets_unmake_packet_python.xml
    inets_variable_rotator.xml
    inets_baseband_derotation.xml
    inets_stop_and_wait_arq.xml
    inets_rrrm.xml
    inets_per_logger.xml 
    inets_rssi.xml
    inets_framing_py_v1.xml
    inets_carrier_sensing_cpp_cc.xml
    inets_exponential_backoff_cpp.xml
    inets_decision_cpp.xml
    inets_idle_cpp.xml
    inets_wait_cpp.xml
    inets_pending_tx_finish.xml
    inets_t_control_tx_cc.xml
    inets_rx_switch_cc.xml
    inets_framing_cpp.xml
    inets_analyze_frame_cpp.xml
    inets_frame_header_analysis_cpp.xml
    inets_message_tomb.xml
    inets_frame_verification_cpp.xml
    inets_address_check_cpp.xml
    inets_timeout_cpp.xml
    inets_counter.xml
    inets_null_message_source.xml
    inets_idle.xml
    inets_decouple_frame_info.xml
    inets_frame_info_selector.xml
    inets_frame_type_check.xml
    inets_frame_buffer.xml
    inets_framing.xml
    inets_sending.xml
    inets_receiving.xml
    inets_timeout.xml
    inets_carrier_sensing.xml
    inets_backoff.xml
    inets_beginnen.xml
    inets_address_check.xml
    DESTINATION share/gnuradio/grc/blocks
)
