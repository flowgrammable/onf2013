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

#ifndef FLOWGRAMMABLE_XID_GEN_H
#define FLOWGRAMMABLE_XID_GEN_H

#include <cstdint>

namespace flog {
namespace ofp {


template<typename T>
  struct Xid_generator 
  {
    Xid_generator() 
      : id(0) 
    { }

    T operator()(){
      return id++;
    };

    T id;
  };

} // namespace ofp
} // flog

#endif
