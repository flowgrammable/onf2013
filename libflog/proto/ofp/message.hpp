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

#ifndef FLOG_PROTO_OFP_MESSAGE_HPP
#define FLOG_PROTO_OFP_MESSAGE_HPP

#include <libflog/proto/ofp/v1_0/message.hpp>
#include <libflog/proto/ofp/v1_1/message.hpp>
#include <libflog/proto/ofp/v1_2/message.hpp>
#include <libflog/proto/ofp/v1_3/message.hpp>
#include <libflog/proto/ofp/v1_3_1/message.hpp>

namespace flog {
namespace ofp {

/// The common message provides an abstrat view of all message
/// types. This allows version-specific state machines to return
/// messages to a version-neutral connection manager.
///
/// \todo This is a pointer union. Redesign the class to make it
/// match those semantics more precisely.
struct Common_message {
  struct Delete;
  Common_message() = default;

  template<typename T>
    Common_message(const T* m)
      : version(m->header.version), patch(0), ptr(m) { }

  Common_message(const v1_3_1::Message* m)
    : version(4), patch(1), ptr(m) { }

  uint8_t version;
  uint8_t patch;
  
  union Kind {
    Kind(const v1_0::Message* p) : m1(p) { }
    Kind(const v1_1::Message* p) : m2(p) { }
    Kind(const v1_2::Message* p) : m3(p) { }
    Kind(const v1_3::Message* p) : m4(p) { }
    Kind(const v1_3_1::Message* p) : m5(p) { }

    const v1_0::Message* m1;
    const v1_1::Message* m2;
    const v1_2::Message* m3;
    const v1_3::Message* m4;
    const v1_3_1::Message* m5;
  } ptr;
};

/// Provides a destructor for common messages.
struct Common_message::Delete {
  void 
  operator()(Common_message& m) {
    switch (m.version) {
    case 1: 
      delete m.ptr.m1; 
      break;
    case 2: 
      delete m.ptr.m2; 
      break;
    case 3: 
      delete m.ptr.m3; 
      break;
    case 4: 
      if (m.patch == 0)
        delete m.ptr.m4;
      else
        delete m.ptr.m5;
      break;
    }
  }
};

/// The result of all state changing operations is a sequence of
/// messages and some additional state information.
using State_result = flog::State_result<Common_message, Common_message::Delete>;
using Message_vector = State_result::Message_vector;

} // namespace ofp
} // namespace flog

#endif
