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

#include <sstream>
#include <iomanip>

#include "mpls.hpp"

namespace flog {
namespace mpls {


// -------------------------------------------------------------------------- //
// Flow Label

std::string to_string(const Flow_label& fl)
{
  std::stringstream ss;
  ss << std::hex << std::setw(2) << std::setfill('0');
  ss << "0x" << int(fl.data[0]) << int(fl.data[1]) << int(fl.data[2]);
  ss << std::dec;
  return ss.str();
}



} // namespace mpls
} // namespace flog
