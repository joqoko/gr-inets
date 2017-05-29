/* -*- c++ -*- */

#define INETS_API
#define DIGITAL_API
%include "gnuradio.i"			// the common stuff
//load generated python docstrings
%include "inets_swig_doc.i"

%{
#include "gnuradio/digital/constellation.h"
#include "inets/frame_sync_cc.h"
#include "inets/timing_recovery_cc.h"
#include "inets/packetizer.h"
#include "inets/variable_rotator.h"
#include "inets/baseband_derotation.h"
#include "inets/rssi.h"
#include "inets/carrier_sensing_cpp_cc.h"
#include "inets/exponential_backoff_cpp.h"
#include "inets/decision_cpp.h"
#include "inets/idle_cpp.h"
#include "inets/wait_cpp.h"
#include "inets/pending_tx_finish.h"
#include "inets/t_control_tx_cc.h"
#include "inets/rx_switch_cc.h"
#include "inets/framing_cpp.h"
#include "inets/analyze_frame_cpp.h"
#include "inets/message_tomb.h"
#include "inets/frame_verification_cpp.h"
#include "inets/address_check_cpp.h"
#include "inets/timeout_cpp.h"
#include "inets/counter.h"
#include "inets/null_message_source.h"
#include "inets/idle.h"
#include "inets/decouple_frame_info.h"
#include "inets/frame_info_selector.h"
#include "inets/frame_type_check.h"
#include "inets/frame_buffer.h"
#include "inets/framing.h"
#include "inets/timeout.h"
#include "inets/carrier_sensing.h"
#include "inets/backoff.h"
#include "inets/beginnen.h"
#include "inets/address_check.h"
#include "inets/frame_probe.h"
#include "inets/frame_aggregation.h"
#include "inets/frame_analysis.h"
#include "inets/frame_check.h"
#include "inets/IFS.h"
#include "inets/dummy_source.h"
#include "inets/resend_check.h"
#include "inets/slide_window.h"
#include "inets/frame_filter.h"
#include "inets/frame_comparer.h"
#include "inets/frame_index_check.h"
#include "inets/beacon_interpreter.h"
#include "inets/general_timer.h"
#include "inets/rts_framing.h"
#include "inets/cts_framing.h"
#include "inets/get_payload.h"
#include "inets/frame_index_selector.h"
#include "inets/general_timeout.h"
#include "inets/cogmac_ch_pool.h"
#include "inets/frame_replicate.h"
#include "inets/frame_and.h"
#include "inets/frame_path.h"
#include "inets/frame_to_boolean.h"
#include "inets/frame_counter.h"
#include "inets/msg_strobe_filter.h"
#include "inets/dice.h"
#include "inets/random_filter.h"
#include "inets/general_timeout.h"
#include "inets/cogmac_ch_pool.h"
#include "inets/frame_replicate.h"
#include "inets/frame_and.h"
#include "inets/frame_path.h"
#include "inets/frame_to_boolean.h"
#include "inets/frame_counter.h"
#include "inets/msg_strobe_filter.h"
#include "inets/dice.h"
#include "inets/random_filter.h"
%}
%include "gnuradio/digital/constellation.h"


%include "inets/frame_sync_cc.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_sync_cc);
%include "inets/timing_recovery_cc.h"
GR_SWIG_BLOCK_MAGIC2(inets, timing_recovery_cc);
%include "inets/packetizer.h"
GR_SWIG_BLOCK_MAGIC2(inets, packetizer);
%include "inets/variable_rotator.h"
GR_SWIG_BLOCK_MAGIC2(inets, variable_rotator);
%include "inets/baseband_derotation.h"
GR_SWIG_BLOCK_MAGIC2(inets, baseband_derotation);
%include "inets/rssi.h"
GR_SWIG_BLOCK_MAGIC2(inets, rssi);

%include "inets/carrier_sensing_cpp_cc.h"
GR_SWIG_BLOCK_MAGIC2(inets, carrier_sensing_cpp_cc);
%include "inets/exponential_backoff_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, exponential_backoff_cpp);
%include "inets/decision_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, decision_cpp);
%include "inets/idle_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, idle_cpp);

%include "inets/wait_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, wait_cpp);

%include "inets/pending_tx_finish.h"
GR_SWIG_BLOCK_MAGIC2(inets, pending_tx_finish);

%include "inets/t_control_tx_cc.h"
GR_SWIG_BLOCK_MAGIC2(inets, t_control_tx_cc);

%include "inets/rx_switch_cc.h"
GR_SWIG_BLOCK_MAGIC2(inets, rx_switch_cc);

%include "inets/framing_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, framing_cpp);

%include "inets/analyze_frame_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, analyze_frame_cpp);

%include "inets/message_tomb.h"
GR_SWIG_BLOCK_MAGIC2(inets, message_tomb);

%include "inets/frame_verification_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_verification_cpp);
%include "inets/address_check_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, address_check_cpp);
%include "inets/timeout_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, timeout_cpp);
%include "inets/counter.h"
GR_SWIG_BLOCK_MAGIC2(inets, counter);
%include "inets/null_message_source.h"
GR_SWIG_BLOCK_MAGIC2(inets, null_message_source);
%include "inets/idle.h"
GR_SWIG_BLOCK_MAGIC2(inets, idle);
%include "inets/decouple_frame_info.h"
GR_SWIG_BLOCK_MAGIC2(inets, decouple_frame_info);
%include "inets/frame_info_selector.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_info_selector);
%include "inets/frame_type_check.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_type_check);

%include "inets/frame_buffer.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_buffer);
%include "inets/framing.h"
GR_SWIG_BLOCK_MAGIC2(inets, framing);

%include "inets/timeout.h"
GR_SWIG_BLOCK_MAGIC2(inets, timeout);
%include "inets/carrier_sensing.h"
GR_SWIG_BLOCK_MAGIC2(inets, carrier_sensing);
%include "inets/backoff.h"
GR_SWIG_BLOCK_MAGIC2(inets, backoff);

%include "inets/beginnen.h"
GR_SWIG_BLOCK_MAGIC2(inets, beginnen);
%include "inets/address_check.h"
GR_SWIG_BLOCK_MAGIC2(inets, address_check);

%include "inets/frame_probe.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_probe);

%include "inets/frame_aggregation.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_aggregation);

%include "inets/frame_analysis.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_analysis);
%include "inets/frame_check.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_check);
%include "inets/IFS.h"
GR_SWIG_BLOCK_MAGIC2(inets, IFS);

%include "inets/dummy_source.h"
GR_SWIG_BLOCK_MAGIC2(inets, dummy_source);
%include "inets/resend_check.h"
GR_SWIG_BLOCK_MAGIC2(inets, resend_check);
%include "inets/slide_window.h"
GR_SWIG_BLOCK_MAGIC2(inets, slide_window);
%include "inets/frame_filter.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_filter);
%include "inets/frame_comparer.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_comparer);
%include "inets/frame_index_check.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_index_check);
%include "inets/beacon_interpreter.h"
GR_SWIG_BLOCK_MAGIC2(inets, beacon_interpreter);
%include "inets/general_timer.h"
GR_SWIG_BLOCK_MAGIC2(inets, general_timer);
%include "inets/rts_framing.h"
GR_SWIG_BLOCK_MAGIC2(inets, rts_framing);
%include "inets/cts_framing.h"
GR_SWIG_BLOCK_MAGIC2(inets, cts_framing);
%include "inets/get_payload.h"
GR_SWIG_BLOCK_MAGIC2(inets, get_payload);
%include "inets/frame_index_selector.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_index_selector);
%include "inets/general_timeout.h"
GR_SWIG_BLOCK_MAGIC2(inets, general_timeout);

%include "inets/cogmac_ch_pool.h"
GR_SWIG_BLOCK_MAGIC2(inets, cogmac_ch_pool);

%include "inets/frame_replicate.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_replicate);

%include "inets/frame_and.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_and);
%include "inets/frame_path.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_path);
%include "inets/frame_to_boolean.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_to_boolean);
%include "inets/frame_counter.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_counter);
%include "inets/msg_strobe_filter.h"
GR_SWIG_BLOCK_MAGIC2(inets, msg_strobe_filter);

%include "inets/dice.h"
GR_SWIG_BLOCK_MAGIC2(inets, dice);
%include "inets/random_filter.h"
GR_SWIG_BLOCK_MAGIC2(inets, random_filter);
