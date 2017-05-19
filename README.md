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
 1		sending					inets_dmf_mac
 1.1		t_control_tx_cc				inets_dmf_phy
 1.2		pending_tx_finish			inets_dmf_phy
 1.3		decouple_frame_info			inets_dmf_phy
 1.4		packetizer				inets_dmf_phy
 2		receiving				inets_dmf_mac
 2.1		rx_switch_cc				inets_dmf_phy

 3		framing					inets_dmf_mac
 3.1		rts_framing				inets_dmf_mac
 3.2		cts_framing				inets_dmf_mac
 4		frame_buffer				inets_dmf_mac
 37		frame_replicate				inets_dmf_mac

 18		frame_aggregation			inets_dmf_mac

 x		carrier_sensing				inets_dmf_mac
 7		frame_analysis				inets_dmf_mac
 8		address_check				inets_dmf_mac
 25             frame_type_check			inets_dmf_mac
 9		frame_check				inets_dmf_mac
 28		frame_index_check			inets_dmf_tool
 33		frame_index_selector			inets_dmf_mac
 24		resend_check				inets_dmf_mac
 27		frame_comparer				inets_dmf_tool

 23		dummy_source				inets_dmf_tool

 3		general_timer				inets_dmf_mac
 34		general_timeout				inets_dmf_mac
 11		backoff					inets_dmf_mac
 19		IFS					inets_dmf_mac

 22		slide_window				inets_dmf_mac
 29		beacon_interpreter			inets_dmf_mac
 35		cogmac_ch_pool				inets_dmf_mac

 36		frame_counter				inets_dmf_mac
 38		frame_and				inets_dmf_tool
 39		frame_path				inets_dmf_tool
 40		frame_to_boolean			inets_dmf_tool
 41		dice					inets_dmf_tool


 100+		frame_probe				inets_dmf_tool
 100+		counter					inets_dmf_tool	

 14		decision_cpp				inets_dmf_tool
 15             null_message_source			inets_dmf_tool
 26		frame_filtering				inets_dmf_tool

