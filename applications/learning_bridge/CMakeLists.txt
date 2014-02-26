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

add_library(bridge_v1_0 SHARED v1_0/bridge.cpp)
target_link_libraries(bridge_v1_0 dl ${FLOG_LIBRARIES})

add_library(bridge_v1_1 SHARED v1_1/bridge.cpp)
target_link_libraries(bridge_v1_1 dl ${FLOG_LIBRARIES})
