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

#include <iostream>

#include <libflog/proto/ofp/v1_0/message.hpp>

using namespace std;
using namespace flog;
using namespace flog::ofp::v1_0;

bool error = false;

void
check(bool b, const char* msg) {
  if (not b) {
    cerr << msg << '\n';
    error = true;
  }
}

void
check_feature_res_list() {
  Feature_res::Capability c = Feature_res::FLOW_STATS;
  Feature_res::Action a = Feature_res::OUTPUT;
  Feature_res p(0, 0, 0, c, a, {Port(), Port(), Port()});
  check(p.ports.size() == 3, "Port test mismatch");
}

void 
check_packet_out_packet() {
  Greedy_buffer buf(10);
  Packet_out p(buf, 10, {Action_output(10, 2048), Action_strip_vlan()});
  check(p.data == buf,         "Packet data mismatch");
  check(p.buffer_id == -1u,    "Invalid buffer");
  check(p.in_port == 10,       "Port mismatch");
  check(p.actions.size() == 2, "Action count mismatch");

  // TODO: Validate actions.
}

void
check_packet_out_buffer() {
  Packet_out p(10, 20, {Action_output(Port::CONTROLLER, 2048), Action_strip_vlan()});
  check(p.data.empty(),        "Invalid packet data");
  check(p.buffer_id == 10,     "Buffer mismatch");
  check(p.in_port == 20,       "Port mismatch");
  check(p.actions.size() == 2, "Action count mismatch");

  // TODO: Validate actions.
}


int main() {
  check_packet_out_packet();
  check_packet_out_buffer();

  return error ? -1 : 0;
}

