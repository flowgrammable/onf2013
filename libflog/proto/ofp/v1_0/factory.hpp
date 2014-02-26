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

#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_0_FACTORY_HPP
#define FLOWGRAMMABLE_PROTO_OFP_V1_0_FACTORY_HPP

#include <forward_list>

#include <libflog/proto/ofp/xid_gen.hpp>
#include <libflog/sequence.hpp>

namespace flog {
namespace ofp {
namespace v1_0 {


enum Message_type : uint8_t;

struct Message;
struct Port;

/// \brief The factory that generates version 1.0 messages
///
/// \todo Make the factory refer to an allocator, owned by the state
/// machine that intelligently allocates memory for messages.
struct Factory {
  // Constructor
  Factory(Xid_generator<uint32_t>& g) : gen(g) {}

  Message* make_hello(uint32_t version_bitmap);
  Message* make_hello_failed();
  Message* make_feature_req();
  Message* make_feature_res(const uint64_t datapath_id = 0,
                          const uint32_t n_buffers = 0,
                          const uint8_t n_tables = 0,
                          const uint32_t capabilities = 0,
                          const uint32_t actions = 0,
                          const Sequence<Port>& ports = {});
  Message* make_flow_mod();
  Message* make_packet_out();
  Message* make_echo_req();
  Message* make_echo_res();

  // Member
  Xid_generator<uint32_t>& gen;
};

} // namespace v1_0
} // namespace ofp
} // namespace flog



#endif
