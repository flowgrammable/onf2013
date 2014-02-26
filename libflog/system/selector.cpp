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
#include "selector.hpp"

namespace flog {

std::string
to_string(const Selector& s)
{
  std::stringstream ss;

  ss << "[";
  ss << s.max << ", ";
  ss << "{";
  bool first = true;
  for(int i = 0; i < s.max+1;++i) {
    if(FD_ISSET(i, &s.read_set)) {
      ss << i;
      if(first) first = false;
      else ss << ",";
    }
  }
  ss << "}, ";
  ss << "{";
  first = true;
  for(int i = 0; i < s.max+1;++i) {
    if(FD_ISSET(i, &s.write_set)) {
      ss << i;
      if(first) first = false;
      else ss << ",";
    }
  }
  ss << "}";
  ss << "]";

  return ss.str();
}

} // namespace flog
