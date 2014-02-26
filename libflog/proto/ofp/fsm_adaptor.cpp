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

#include "fsm_adaptor.hpp"

namespace flog {
namespace ofp {

FSM_switch_agent::FSM_switch_agent(const FSM_config& fc, 
                                   Xid_generator<uint32_t>& g)
  : config(fc), established(false)
{
  switch(fc.version) {
    case FSM_config::v1_0:
      neg_v1_0 = Negotiation<v1_0::Message>(fc, g);
      break;
    case FSM_config::v1_1:
      neg_v1_1 = Negotiation<v1_1::Message>(fc, g);
      break;
    case FSM_config::v1_2:
      neg_v1_2 = Negotiation<v1_2::Message>(fc, g);
      break;
    case FSM_config::v1_3:
      neg_v1_3 = Negotiation<v1_3::Message>(fc, g);
      break;
    case FSM_config::v1_3_1:
      neg_v1_3_1 = Negotiation<v1_3_1::Message>(fc, g);
      break;
    default:
      break;
  }
}

std::string
to_string(const FSM_switch_agent& fsa)
{
  std::stringstream ss;
  return ss.str();
}

} // namespace ofp 
} // namespace flog
