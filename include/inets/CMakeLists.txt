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
    exponential_backoff_cpp.h
    decision_cpp.h
    idle_cpp.h
    wait_cpp.h
    pending_tx_finish.h
    t_control_tx_cc.h
    rx_switch_cc.h
    framing_cpp.h
    analyze_frame_cpp.h
    message_tomb.h
    frame_verification_cpp.h
    address_check_cpp.h
    timeout_cpp.h
    counter.h
    null_message_source.h
    idle.h
    decouple_frame_info.h
    frame_info_selector.h
    frame_type_check.h
    frame_buffer.h
    framing.h
    timeout.h
    carrier_sensing.h
    backoff.h
    beginnen.h
    address_check.h
    frame_probe.h
    frame_aggregation.h
    frame_analysis.h
    frame_check.h
    dummy_source.h
    resend_check.h
    slide_window.h
    frame_filter.h
    frame_comparer.h
    frame_index_check.h
    beacon_interpreter.h
    general_timer.h
    rts_framing.h
    cts_framing.h
    get_payload.h
    frame_index_selector.h
    general_timeout.h
    general_timeout.h
    cogmac_ch_pool.h
    frame_replicate.h
    frame_and.h
    frame_path.h
    frame_to_boolean.h
    frame_counter.h
    reset_gain.h
    msg_strobe_filter.h
    dice.h
    random_filter.h
    virtual_cs.h
    time_probe.h
    cogmac_rm_rep.h
    cogmac_timing.h
    unbundle.h
    cmd_path.h
    rand_generator.h
    standard_timer.h
    cmd_and.h
    cmd_switch.h
    cmd_port_control.h
    parameter_list.h DESTINATION include/inets

)
