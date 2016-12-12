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

Index		block name
 1		idle_cpp
 2		framing_cpp
 3		packetizer
 4		t_control_tx_cc
 5		pending_tx_finish
 6		tx_buffer
 7		wait_cpp
 8		wait_frame_transmission_c (deleted. Refer to t_control_tx_cc and pending_tx_finish)
 9		message_tomb (not necessary to provide develop mode)
 10		rx_switch_cc
 11		frame_header_analysis_cpp
 12		frame_verification_cpp
 13		address_check_cpp
 14		decision_cpp
 15     	exponential_backoff_cpp

