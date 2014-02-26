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

# Global build configuration

# TODO: Check that we have viable C++11 compiler. That means either
# GCC or Clang (not that Clang may require Clang's libstdc++).

# Other dependencies
find_package(OpenSSL)
find_package(Threads)

# Set up global include directories for the compiler.
include_directories(${OPENSSL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR})

# The complete set of libraries needed to build an application.
set(FLOG_LIBRARIES ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} flog)
