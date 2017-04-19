OOT Module for GNU Radio
This OOT module includes blocks to build a packetized transceiver system using USRPs. 
It was developed as part of a M.Sc thesis at RWTH-Aachen University. This transceiver is part of a mm-wave research platform used at the Institute for Networked System.

##Install
```
mkdir build
cd build
cmake ..
make && make install
```

##Usage
For an example which uses most of the parts of this project see the `transceiver.grc` in the `examples` folder.

This flowgraph sets up a transceiver that accepts UDP input and forwards output also via UDP. It is intended for use with a USRP x3x0 SDR device.

In oder to use this example you have to compile the following hierarchical blocks using GRC:
* `grc/inets_tx_phy.grc`
* `grc/inets_rx_phy.grc`
* `grc/inets_radio.grc`

How to use develop_mode to debug:

1. Set parameter 'develop_mode' to the index of the blocks to display the debugging information. 

Index		block name				Categories
 2		decouple_frame_info			inets_dmf_phy
 3		general_timer				inets_dmf_mac
 4		t_control_tx_cc				inets_dmf_phy
 5		pending_tx_finish			inets_dmf_phy
 6		rx_switch_cc				inets_dmf_phy
 7		frame_analysis				inets_dmf_mac
 8		address_check_cpp			inets_dmf_mac
 9		frame_check				inets_dmf_mac
                (frame_verification_cpp)
 10		timeout_cpp				inets_dmf_mac
 11		backoff					inets_dmf_mac
 12		carrier_sensing_cpp_cc			inets_dmf_mac
 14		decision_cpp				inets_dmf_tool
 15             null_message_source			inets_dmf_tool
 16		frame_buffer				inets_dmf_mac
 17		framing					inets_dmf_mac
 18		frame_aggregation			inets_dmf_mac
 19		IFS					inets_dmf_mac
 20		sending					inets_dmf_mac
 21		receiving				inets_dmf_mac
 22		slide_window				inets_dmf_mac
 23		dummy_source				inets_dmf_tool
 24		resend_check				inets_dmf_mac
 25             frame_type_check			inets_dmf_mac
 26		frame_filtering				inets_dmf_tool
 27		frame_comparer				inets_dmf_tool
 28		frame_index_check			inets_dmf_tool
 29		beacon_interpreter			inets_dmf_mac
 30		rts_framing				inets_dmf_mac
 31		cts_framing				inets_dmf_mac
 32		packetizer				inets_dmf_phy
 33		frame_index_selector			inets_dmf_mac
 34		general_timeout				inets_dmf_mac
 35		cogmac_ch_pool				inets_dmf_mac
 36		frame_counter				inets_dmf_mac
 37		frame_replicate				inets_dmf_mac
 100+		frame_probe				inets_dmf_tool
 100+		counter					inets_dmf_tool	


 x1		idle_cpp				inets_dmf_mac
 x101		analyze_frame_cpp			inets_dmf_draft
 x102		framing_cpp				inets_dmf_draft
 x103            framing_py_v1				inets_dmf_draft
 x104		idle_cpp				inets_dmf_draft
 x105            tx_buffer				inets_dmf_draft
