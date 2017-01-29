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
#include "inets/frame_header_analysis_cpp.h"
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
%include "inets/frame_header_analysis_cpp.h"
GR_SWIG_BLOCK_MAGIC2(inets, frame_header_analysis_cpp);
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
