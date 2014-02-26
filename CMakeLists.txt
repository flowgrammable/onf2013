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

# Basic CMake configuration
cmake_minimum_required(VERSION 2.8)

# Put our local cmake files in the search path.
set(FLOG_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${FLOG_MODULE_PATH})

# Compiler configuration
# Minimally, -std=c++11 and -Wall must be enabled.
#
# For Clang-3.3 installed via MacPorts on MacOS 10.6.8, also be sure to
# include the following:
#
#   -stdlib=libc++ -U__STRICT_ANSI__
#
# Currently, this must be done by setting CXX_FLAGS or setting this variable
# using ccmake. Note unsetting __STRICT_ANSI__ will cause some checks to
# be disabled.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC -g")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -U__STRICT_ANSI__")

## Build options
option(FLOG_BUILD_TESTS     "Build unit tests"             ON)
option(FLOG_BUILD_BINDINGS  "Build language bindings"      ON)
option(FLOG_ENABLE_VALGRIND "Enable testing with valgrind" OFF)

## Build configuration)
include(FlogConfig)
include(FlogBind)
include(FlogTest)
include(FlogDoc)


# Build the library and associated tools.
add_subdirectory(libflog)
add_subdirectory(applications)
add_subdirectory(tools)

# Only build the bindings when configured to do so.
if (FLOG_BUILD_BINDINGS)
 add_subdirectory(bindings)
endif()

# Add test suites that depend on the creation of various
# tools (e.g., all of the message tests).
add_subdirectory(libflog/proto/ofp/v1_0.test)
add_subdirectory(libflog/proto/ofp/v1_1.test)
add_subdirectory(libflog/proto/ofp/v1_2.test)
add_subdirectory(libflog/proto/ofp/v1_3.test)
add_subdirectory(libflog/proto/ofp/v1_3_1.test)
