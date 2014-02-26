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

SET(CMAKE_SYSTEM_NAME Linux)

SET(CMAKE_C_COMPILER   /opt/x-tools/powerpc-e300c3-linux-gnu/bin/powerpc-e300c3-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER /opt/x-tools/powerpc-e300c3-linux-gnu/bin/powerpc-e300c3-linux-gnu-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /opt/x-tools/powerpc-e300c3-linux-gnu /opt/x-tools/powerpc-e300c3-linux-gnu)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CTEST_EXE_PREFIX "/usr/bin/qemu-ppc;-cpu;e300c3")
