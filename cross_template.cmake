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

#-DCMAKE_CXX_FLAGS -DCMAKE_TOOLCHAIN_FILE=this.cmake
SET(CMAKE_SYSTEM_NAME Linux)

SET(CMAKE_C_COMPILER   /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /usr /usr)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CTEST_EXE_PREFIX "/usr/bin/qemu-i386")
#SET(CTEST_EXE_PREFIX "/usr/bin/qemu-arm;-cpu;cortex-a8")
