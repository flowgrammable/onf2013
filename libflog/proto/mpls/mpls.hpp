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

#ifndef FLOWGRAMMABLE_MPLS_H
#define FLOWGRAMMABLE_MPLS_H

#include <cstdint>
#include <algorithm>

namespace flog {
namespace mpls {


// -------------------------------------------------------------------------- //
// Flow Label

struct Flow_label{
  /// Returns the ith component of the mpls address
  uint8_t&       operator[](std::size_t i)       { return data[i]; }
  const uint8_t& operator[](std::size_t i) const { return data[i]; }

  uint8_t data[3];
};

// Equality comparison
inline bool
operator==(const Flow_label& a, const Flow_label& b)
{
  return a.data[0]==b.data[0] and a.data[1]==b.data[1] and a.data[2]==b.data[2];
}

inline bool
operator!=(const Flow_label& a, const Flow_label& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t 
bytes(const mpls::Flow_label& a)
{
    return 3;
}

// To string
std::string to_string(const Flow_label& data);


} // namespace mpls
} // namespace flog

#endif
