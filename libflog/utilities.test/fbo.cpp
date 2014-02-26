// Copyright (c) 2013 Flowgrammable, LLC.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at:
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an "AS IS"
// BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing
// permissions and limitations under the License.

#include <cassert>

#include <libflog/utilities.hpp>

using namespace flog;

int main()
{
  Foreign_byte_order fbo;

  uint8_t x8 = 0x01;
  assert(fbo.msbf(x8) == x8);
  assert(fbo.lsbf(x8) == x8);

  // TODO: Write tests for 16, 32, and 64-bit data.
}
