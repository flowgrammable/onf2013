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

#ifndef FLOWGRAMMABLE_FSM_CONFIG_H
#define FLOWGRAMMABLE_FSM_CONFIG_H

#include <vector>

#include <libflog/system/time.hpp>

namespace flog {
namespace ofp {

struct Timer_config {
  Time hello_wait;          // Time until declaring missed hello
  Time echo_req_interval;   // Time between echo requests
  Time echo_res_wait;       // Time until declaring missed echo response
  Time feature_req_wait;    // Time until declaring missed feature request
  Time feature_res_wait;    // Time until declaring missed feature response
  Time barrier_res_wait;    // Tim euntil declaring missed barrier response
};

struct Phy_ports {
  uint16_t    port_no;
  uint8_t     hw_addr[6];
  char        name[16];

  uint32_t    config;
  uint32_t    state;

  uint32_t    curr;
  uint32_t    advertised;
  uint32_t    supported;
  uint32_t    peer;

  uint32_t    curr_speed;
  uint32_t    max_speed;
};

struct Switch_feature {
  uint64_t  datapath_id;
  uint32_t  n_buffers;
  uint8_t   n_tables;
  uint32_t  capabilities;
  uint32_t  actions;
};

std::string to_string(const Timer_config& tc);

struct FSM_config {
  enum Version : uint32_t 
  { 
    Unsup = 0, v1_0 = 1, v1_1 = 2, v1_2 = 3, v1_3 = 4, v1_3_1 = 5 
  };

  enum Supported : uint32_t 
  { 
    None = 0, a1_0 = 1, a1_1 = 2, a1_2 = 4, a1_3 = 8 
  };

  FSM_config(Version v, Supported a, const Timer_config& tc);

  Version version;
  Supported supported;
  Timer_config timers;
  Switch_feature feature;
  std::vector<Phy_ports> ports;
  uint8_t auxiliary_id;
};

std::string to_string(FSM_config::Version v);
std::string to_string(FSM_config::Supported a);
std::string to_string(const FSM_config& fc);

inline
FSM_config::FSM_config(Version v, Supported a, const Timer_config& tc)
  : version(v), supported(a), timers(tc)
{ }

} // namespace ofp
} // namespace flog

#endif

