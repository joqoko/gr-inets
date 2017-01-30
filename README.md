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
 1		idle_cpp				inets_dmf_mac
 2		decouple_frame_info			inets_dmf_phy
 3		wait_cpp				inets_dmf_mac
 4		t_control_tx_cc				inets_dmf_phy
 5		pending_tx_finish			inets_dmf_phy
 6		rx_switch_cc				inets_dmf_phy
 7		frame_header_analysis_cpp		inets_dmf_mac
 8		address_check_cpp			inets_dmf_mac
 9		frame_verification_cpp			inets_dmf_mac
 10		timeout_cpp				inets_dmf_mac
 11		exponential_backoff_cpp			inets_dmf_mac
 12		carrier_sensing_cpp_cc			inets_dmf_mac
 13		counter					inets_dmf_tool	
 14		decision_cpp				inets_dmf_tool
 15             null_message_source			inets_dmf_tool
 16		frame_buffer				inets_dmf_mac
 17		framing					inets_dmf_mac
 18		frame_aggregation			inets_dmf_mac




 101		analyze_frame_cpp			inets_dmf_draft
 102		framing_cpp				inets_dmf_draft
 103            framing_py_v1				inets_dmf_draft
 104		idle_cpp				inets_dmf_draft
 105            tx_buffer				inets_dmf_draft
