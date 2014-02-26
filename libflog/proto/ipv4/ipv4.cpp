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
#include "ipv4.hpp"

namespace flog {
namespace ipv4 {


// -------------------------------------------------------------------------- //
// Address

std::string
to_string(Address a)
{
  std::stringstream ss;
  ss << int((a.addr >> 24) & 0xff) << ".";
  ss << int((a.addr >> 16) & 0xff) << ".";
  ss << int((a.addr >> 8 ) & 0xff) << ".";
  ss << int(a.addr & 0xff);
  return ss.str();
}

Address
to_network(Address a, int vlsm)
{
  return { a.addr & prefix_1s<uint32_t>(vlsm) };
}


// -------------------------------------------------------------------------- //
// Differential Services Code Point

std::string to_string(const ipv4::DSCP& a)
{
  return std::to_string(int(a.DSCP));
}


// -------------------------------------------------------------------------- //
// Explicit Congestion Notification

std::string to_string(const ipv4::ECN& a)
{
  return std::to_string(int(a.ECN));
}


} // namespace ipv4
} // namespace flog
