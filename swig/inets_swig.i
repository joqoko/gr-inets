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
#include "inets/wait_frame_transmission_c.h"
#include "inets/pending_tx_finish.h"
#include "inets/t_control_tx_cc.h"
#include "inets/tx_buffer.h"
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


%include "inets/wait_frame_transmission_c.h"
GR_SWIG_BLOCK_MAGIC2(inets, wait_frame_transmission_c);
%include "inets/pending_tx_finish.h"
GR_SWIG_BLOCK_MAGIC2(inets, pending_tx_finish);

%include "inets/t_control_tx_cc.h"
GR_SWIG_BLOCK_MAGIC2(inets, t_control_tx_cc);
%include "inets/tx_buffer.h"
GR_SWIG_BLOCK_MAGIC2(inets, tx_buffer);
