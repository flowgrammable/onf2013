# Copyright (c) 2013 Flowgrammable, LLC.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an "AS IS"
# BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
# or implied. See the License for the specific language governing
# permissions and limitations under the License.

# Define the executable.
add_executable(ofp_test main.cpp)
target_link_libraries(ofp_test ${FLOG_LIBRARIES})

add_executable(ofp_to_string to_string.cpp)
target_link_libraries(ofp_to_string ${FLOG_LIBRARIES})

add_executable(ofp_stream stream.cpp)
target_link_libraries(ofp_stream ${FLOG_LIBRARIES})

add_executable(ofp_abs abstraction_layer.cpp)
target_link_libraries(ofp_abs ${FLOG_LIBRARIES})

#add_executable(ofp_sm_vn state_machine_version_negotiation.cpp)
#target_link_libraries(ofp_sm_vn ${FLOG_LIBRARIES})

add_executable(sm_test_v10 state_machine_test_v10.cpp)
target_link_libraries(sm_test_v10 ${FLOG_LIBRARIES})

add_executable(sm_test_v11 state_machine_test_v11.cpp)
target_link_libraries(sm_test_v11 ${FLOG_LIBRARIES})

add_executable(sm_test_v12 state_machine_test_v12.cpp)
target_link_libraries(sm_test_v12 ${FLOG_LIBRARIES})

add_executable(sm_test_v13 state_machine_test_v13.cpp)
target_link_libraries(sm_test_v13 ${FLOG_LIBRARIES})

add_executable(sm_test_v131 state_machine_test_v131.cpp)
target_link_libraries(sm_test_v131 ${FLOG_LIBRARIES})

add_executable(learning_bridge_test learning_bridge_interface_test_v10.cpp)
target_link_libraries(learning_bridge_test ${FLOG_LIBRARIES})

add_executable(learning_bridge_v1_0 learning_bridge_v1_0.cpp)
target_link_libraries(learning_bridge_v1_0 ${FLOG_LIBRARIES})

add_executable(learning_bridge_v1_1 learning_bridge_v1_1.cpp)
target_link_libraries(learning_bridge_v1_1 ${FLOG_LIBRARIES})

add_test(test_sm_v10 sm_test_v10)
add_test(test_sm_v11 sm_test_v11)
add_test(test_sm_v12 sm_test_v12)
add_test(test_sm_v13 sm_test_v13)
add_test(test_sm_v131 sm_test_v131)

add_test(test_learning_bridge_v1_0 learning_bridge_v1_0)
add_test(test_learning_bridge_v1_1 learning_bridge_v1_1)

# Configure an internal tool for testing.
# NOTE: The ofp_test.py may want an installation target. 
if(FLOG_BUILD_PYTHON_BINDINGS)
  message(STATUS "Configuring Python test tools")
  set(FLOG_PYTHON_PATH ${CMAKE_BINARY_DIR}/bindings/ofp)
  configure_file(ofp_test.sh.in ${CMAKE_CURRENT_BINARY_DIR}/ofp_test.sh)
  configure_file(ofp_test.py.in ${CMAKE_CURRENT_BINARY_DIR}/ofp_test.py)
endif()

