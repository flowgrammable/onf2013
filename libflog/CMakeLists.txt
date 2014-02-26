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

set(src 
  utilities.cpp 
  string.cpp 
  error.cpp 
  buffer.cpp 
  sequence.cpp 
  message.cpp
  connection.cpp
  proto/internet.cpp
  proto/ofp/ofp.cpp
  proto/ofp/message.cpp
  proto/ofp/application.cpp
  proto/ofp/xid_gen.cpp
  proto/ofp/fsm_config.cpp
  proto/ofp/fsm_negotiation.cpp
  proto/ofp/fsm_adaptor.cpp
  proto/ofp/v1_0/message.cpp
  proto/ofp/v1_0/state.cpp
  proto/ofp/v1_0/application.cpp
  proto/ofp/v1_0/factory.cpp
  proto/ofp/v1_1/message.cpp
  proto/ofp/v1_1/state.cpp
  proto/ofp/v1_1/application.cpp
  proto/ofp/v1_1/factory.cpp
  proto/ofp/v1_2/message.cpp
  proto/ofp/v1_2/state.cpp
  proto/ofp/v1_2/application.cpp
  proto/ofp/v1_2/factory.cpp
  proto/ofp/v1_3/state.cpp
  proto/ofp/v1_3/application.cpp
  proto/ofp/v1_3/factory.cpp
  proto/ofp/v1_3/message.cpp
  proto/ofp/v1_3_1/state.cpp
  proto/ofp/v1_3_1/application.cpp
  proto/ofp/v1_3_1/factory.cpp
  proto/ofp/v1_3_1/message.cpp
  proto/ethernet/ethernet.cpp
  proto/ipv4/ipv4.cpp
  proto/ipv6/ipv6.cpp
  proto/mpls/mpls.cpp
  system/time.cpp
  system/plugin.cpp
  system/exporter.cpp
  system/logger.cpp
  system/config.cpp
  system/pipe.cpp
  system/socket.cpp
  system/ssl_wrapper.cpp
  system/selector.cpp
  system/reactor.cpp
  system/manager.cpp
  system/acceptor.cpp
  system/connection.cpp
)

# Define the core library.
add_library(flog STATIC ${src})

# Add unit tests.
add_subdirectory(utilities.test)
add_subdirectory(buffer.test)

# Installation
install(TARGETS flog EXPORT flog ARCHIVE DESTINATION lib)
install(EXPORT flog NAMESPACE FLOG_ DESTINATION lib/flog)

install(FILES utilities.hpp
              string.hpp
              error.hpp
              buffer.hpp
              sequence.hpp
              message.hpp
              connection.hpp
              connection.ipp
        DESTINATION include/libflog)

install(FILES proto/internet.hpp
        DESTINATION include/libflog/proto)

install(FILES proto/ofp/ofp.hpp
              proto/ofp/application.hpp
              proto/ofp/xid_gen.hpp
              proto/ofp/fsm_config.hpp
              proto/ofp/fsm_negotiation.hpp
              proto/ofp/fsm_negotiation.ipp
              proto/ofp/fsm_adaptor.hpp
              proto/ofp/fsm_adaptor.ipp
        DESTINATION include/libflog/proto/ofp)

install(FILES proto/ofp/v1_0/message.hpp
              proto/ofp/v1_0/message.ipp
              proto/ofp/v1_0/state.hpp
              proto/ofp/v1_0/application.hpp
              proto/ofp/v1_0/factory.hpp
        DESTINATION include/libflog/proto/ofp/v1_0)

install(FILES proto/ofp/v1_1/message.hpp
              proto/ofp/v1_1/message.ipp
              proto/ofp/v1_1/state.hpp
              proto/ofp/v1_1/application.hpp
              proto/ofp/v1_1/factory.hpp
        DESTINATION include/libflog/proto/ofp/v1_1)

install(FILES proto/ofp/v1_2/message.hpp
              proto/ofp/v1_2/message.ipp
              proto/ofp/v1_2/state.hpp
              proto/ofp/v1_2/application.hpp
              proto/ofp/v1_2/factory.hpp
        DESTINATION include/libflog/proto/ofp/v1_2)

install(FILES proto/ofp/v1_3/message.hpp
              proto/ofp/v1_3/message.ipp
              proto/ofp/v1_3/state.hpp              
              proto/ofp/v1_3/application.hpp
              proto/ofp/v1_3/factory.hpp
        DESTINATION include/libflog/proto/ofp/v1_3)

install(FILES proto/ofp/v1_3_1/message.hpp
              proto/ofp/v1_3_1/message.ipp
              proto/ofp/v1_3_1/state.hpp
              proto/ofp/v1_3_1/application.hpp
              proto/ofp/v1_3_1/factory.hpp
        DESTINATION include/libflog/proto/ofp/v1_3_1)

install(FILES proto/ethernet/ethernet.hpp 
        DESTINATION include/libflog/proto/ethernet)

install(FILES proto/ipv4/ipv4.hpp 
        DESTINATION include/libflog/proto/ipv4)
  
install(FILES proto/ipv6/ipv6.hpp 
        DESTINATION include/libflog/proto/ipv6)

install(FILES proto/mpls/mpls.hpp 
        DESTINATION include/libflog/proto/mpls)

install(FILES proto/ipv6/ipv6.hpp 
              system/time.hpp
              system/plugin.hpp
              system/plugin.ipp
              system/exporter.hpp
              system/logger.hpp
              system/config.hpp
              system/socket.hpp
              system/ssl_wrapper.hpp
              system/selector.hpp
              system/reactor.hpp
              system/manager.hpp
              system/acceptor.hpp
              system/connection.hpp
        DESTINATION include/libflog/system)
