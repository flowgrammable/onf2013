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

#include "fsm_config.hpp"

namespace flog {
namespace ofp {

std::string
to_string(const Timer_config& tc)
{
  std::stringstream ss;
  ss << "Hello Wait: " << to_string(tc.hello_wait) << "\n";
  ss << "Echo Request Interval: " << to_string(tc.echo_req_interval) << "\n";
  ss << "Echo Response Wait: " << to_string(tc.echo_res_wait) << "\n";
  ss << "Feature Request Wait: " << to_string(tc.feature_req_wait) << "\n";
  ss << "Feature Response Wait: " << to_string(tc.feature_res_wait) << "\n";
  ss << "Barrier Response Wait: " << to_string(tc.barrier_res_wait) << "\n";
  return ss.str();
}

std::string
to_string(FSM_config::Version v)
{
  switch(v) {
    case FSM_config::v1_0: return "1.0";
    case FSM_config::v1_1: return "1.1";
    case FSM_config::v1_2: return "1.2";
    case FSM_config::v1_3: return "1.3";
    case FSM_config::v1_3_1: return "1.3.1";
    default: return "unknown";
  }
}

std::string
to_string(FSM_config::Supported a)
{
  bool first = false;
  std::stringstream ss;
  ss << "{";
  if (a & FSM_config::a1_0) {
    if(first) first = true;
    ss << "1.0";
  //} else if (a & FSM_config::a1_1) {
  } if (a & FSM_config::a1_1) {
    if(first) first = true;
    else ss << ", ";
    ss << "1.1";
  //} else if (a & FSM_config::a1_2) {
  } if (a & FSM_config::a1_2) {
    if(first) first = true;
    else ss << ", ";
    ss << "1.2";
  //} else if (a & FSM_config::a1_3) {
  } if (a & FSM_config::a1_3) {
    if(first) first = true;
    else ss << ", ";
    ss << "1.3";
  }
  ss << "}";
  return ss.str();
}

std::string 
to_string(const FSM_config& fc)
{
  std::stringstream ss;
  ss << "Version: " << to_string(fc.version);
  //if(fc.version == FSM_config::v1_3_1)
    ss << to_string(fc.supported);
  ss << "\n";
  ss << to_string(fc.timers);
  return ss.str();
}

} // namespace ofp
} // namespace flog
