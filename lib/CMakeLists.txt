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
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND inets_sources
    frame_sync_cc_impl.cc
    timing_recovery_cc_impl.cc
    packetizer_impl.cc
    variable_rotator_impl.cc
    baseband_derotation_impl.cc
    rssi_impl.cc
    carrier_sensing_cpp_cc_impl.cc
    exponential_backoff_cpp_impl.cc
    decision_cpp_impl.cc
    idle_cpp_impl.cc
    wait_cpp_impl.cc
    pending_tx_finish_impl.cc
    t_control_tx_cc_impl.cc
    tx_buffer_impl.cc
    rx_switch_cc_impl.cc
    framing_cpp_impl.cc
    analyze_frame_cpp_impl.cc
    frame_header_analysis_cpp_impl.cc
    message_tomb_impl.cc
    frame_verification_cpp_impl.cc
    address_check_cpp_impl.cc
    timeout_cpp_impl.cc
    counter_impl.cc
    null_message_source_impl.cc )

set(inets_sources "${inets_sources}" PARENT_SCOPE)
if(NOT inets_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT inets_sources)

add_library(gnuradio-inets SHARED ${inets_sources})
target_link_libraries(gnuradio-inets ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} ${UHD_LIBRARIES})
set_target_properties(gnuradio-inets PROPERTIES DEFINE_SYMBOL "gnuradio_inets_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-inets PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-inets
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_inets_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_inets.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_inets.cc
)

add_executable(test-inets ${test_inets_sources})

target_link_libraries(
  test-inets
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-inets
)

GR_ADD_TEST(test_inets test-inets)
