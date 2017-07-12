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
    inets_exponential_backoff_cpp.xml
    inets_decision_cpp.xml
    inets_idle_cpp.xml
    inets_wait_cpp.xml
    inets_pending_tx_finish.xml
    inets_t_control_tx_cc.xml
    inets_rx_switch_cc.xml
    inets_framing_cpp.xml
    inets_analyze_frame_cpp.xml
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
    inets_timeout.xml
    inets_carrier_sensing.xml
    inets_backoff.xml
    inets_beginnen.xml
    inets_address_check.xml
    inets_frame_probe.xml
    inets_frame_aggregation.xml
    inets_frame_analysis.xml
    inets_frame_check.xml
    inets_receiving.xml
    inets_dummy_source.xml
    inets_resend_check.xml
    inets_slide_window.xml
    inets_frame_filter.xml
    inets_frame_comparer.xml
    inets_frame_index_check.xml
    inets_beacon_interpreter.xml
    inets_general_timer.xml
    inets_rts_framing.xml
    inets_cts_framing.xml
    inets_get_payload.xml
    inets_frame_index_selector.xml
    inets_general_timeout.xml
    inets_general_timeout.xml
    inets_cogmac_ch_pool.xml
    inets_frame_replicate.xml
    inets_frame_and.xml
    inets_frame_path.xml
    inets_multichannel_receiving.xml
    inets_frame_to_boolean.xml
    inets_frame_counter.xml
    inets_reset_gain.xml
    inets_msg_strobe_filter.xml
    inets_run.xml
    inets_dice.xml
    inets_random_filter.xml
    inets_virtual_cs.xml
    inets_time_probe.xml
    inets_cogmac_rm_rep.xml
    inets_cogmac_timing.xml
    inets_unbundle.xml
    inets_cmd_path.xml
    inets_rand_generator.xml
    inets_standard_timer.xml
    inets_cmd_and.xml
    inets_cmd_switch.xml
    inets_cmd_port_control.xml
    inets_parameter_list.xml
    inets_frame_redundancy_remover.xml DESTINATION share/gnuradio/grc/blocks
)
