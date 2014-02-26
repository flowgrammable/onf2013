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

#include "factory.hpp"
#include "message.hpp"

namespace flog {
namespace ofp {
namespace v1_3 {

// A helper function for creating objects.
template<typename T, typename... Args>
  Message* 
  make(uint32_t xid, Args&&... args) { 
    using Tag = typename T::Tag;
    return new Message(xid, Tag(), std::forward<Args>(args)...); 
  }

/// \brief Make a version 1.3 hello message
///
/// The param version_bitmap is not used in this version
Message*
Factory::make_hello(uint32_t version_bitmap) { return make<Hello>(gen()); }

/// \brief Make a version 1.3 hello error message
///
/// TODO This needs to take buf as an argument.
Message*
Factory::make_hello_failed() {
  Buffer buf;
  return make<Error>(gen(), Error::HELLO_FAILED, Error::HF_INCOMPATIBLE, buf);
}

/// \brief Make a version 1.3 request error message due to slave role
Message* 
Factory::make_is_slave_error() {
  Buffer buf;
  return make<Error>(gen(), Error::BAD_REQUEST, Error::BR_IS_SLAVE, buf);
}

/// \brief Make a version 1.3 features request message
Message*
Factory::make_feature_req() { return make<Feature_req>(gen()); }

/// \brief Make a version 1.3 features response message
Message* 
Factory::make_feature_res(const uint64_t datapath_id,
                          const uint32_t n_buffers,
                          const uint8_t n_tables,
                          const uint32_t aux_id,
                          const uint32_t capabilities) {
  return make<Feature_res>(gen(),
                           datapath_id,
                           n_buffers,
                           n_tables,
                           aux_id,
                           Feature_res::Capability_type(capabilities),
                           0);
}


/// \brief Make a version 1.3 flow mod message
Message*
Factory::make_flow_mod() {
  // TODO need to add fields
  return make<Flow_mod>(gen());
}

/// \brief Make a version 1.3 packet out message
Message*
Factory::make_packet_out() {
  // TODO need to add fields
  return make<Packet_out>(gen());
}

/// \brief Make a version 1.3 echo request message
Message*
Factory::make_echo_req() {
  return make<Echo_req>(gen());
}

/// \brief Make a version 1.3 echo response message
Message*
Factory::make_echo_res() {
  return make<Echo_res>(gen());
}

} // namespace v1_3
} // namespace ofp
} // namespace flog
