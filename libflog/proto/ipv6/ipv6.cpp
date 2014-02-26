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
#include "ipv6.hpp"

namespace flog {
namespace ipv6 {


// -------------------------------------------------------------------------- //
// Address

//TODO: consider whether or not to rwrite this using the shorter form
std::string
to_string(const Address& m)
{
  std::stringstream ss;
  ss << std::hex << std::setw(2) << std::setfill('0');
  ss << int(m[0]) << int(m[1]) << ":" << int(m[2]) << int(m[3]) << ":";
  ss << int(m[4]) << int(m[5]) << ":" << int(m[6]) << int(m[7]) << ":";
  ss << int(m[8]) << int(m[9]) << ":" << int(m[10]) << int(m[11]) << ":";
  ss << int(m[12]) << int(m[13]) << ":" << int(m[14]) << int(m[15]);
  ss << std::dec;
  return ss.str();
}

// -------------------------------------------------------------------------- //
// IPv6 Flow Label

std::string to_string(const Flow_label& fl)
{
  std::stringstream ss;
  ss << std::hex << std::setw(2) << std::setfill('0');
  ss << "0x" << int(fl.data[0]) << int(fl.data[1]) << int(fl.data[2]);
  ss << std::dec;
  return ss.str();
}



} // namespace ipv6
} // namespace flog
