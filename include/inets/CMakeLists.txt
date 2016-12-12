# Copyright 2011,2012 Free Software Foundation, Inc.
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

########################################################################
# Install public header files
########################################################################
install(FILES
    api.h
    frame_sync_cc.h
    timing_recovery_cc.h
    packetizer.h
    variable_rotator.h
    baseband_derotation.h
    rssi.h
    carrier_sensing_cpp_cc.h
    exponential_backoff_cpp.h
    decision_cpp.h
    idle_cpp.h
    wait_cpp.h
    pending_tx_finish.h
    t_control_tx_cc.h
    tx_buffer.h
    rx_switch_cc.h
    framing_cpp.h
    analyze_frame_cpp.h
    frame_header_analysis_cpp.h
    message_tomb.h
    frame_verification_cpp.h
    address_check_cpp.h
    timeout_cpp.h DESTINATION include/inets

)
