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

#ifndef FLOWGRAMMABLE_BRIDGE_V1_1_HPP
#define FLOWGRAMMABLE_BRIDGE_V1_1_HPP

#include <unordered_map>
#include <map>

#include <libflog/proto/ofp/v1_1/application.hpp>

// NOTE: the filename, hpp and cpp,  must match the application's type name in 
// case otherwise it cannot be loaded properly

// Select the verison of openflow you which to use
using namespace flog::ofp::v1_1;
using namespace flog;

namespace std {
  template <>
    class hash<ethernet::Address> {
    public:
    size_t operator() (const ethernet::Address &addr) const {
      return hash<int>()(addr.data[0]) ^ hash<int>()(addr.data[1]) ^
             hash<int>()(addr.data[2]) ^ hash<int>()(addr.data[3]) ^
             hash<int>()(addr.data[4]) ^ hash<int>()(addr.data[5]);
    }
  };
}

/// Learning bridge application for v1_0. The learning table in the controller
/// is updated from the Packet_in messages it receives from the switch 
struct Bridge : Application
{
  using Record = std::pair<uint16_t, Time>;
  using Ethernet_addr = ethernet::Address;
  using Iterator = std::unordered_map<Ethernet_addr, Record>::iterator;

  Bridge();
  ~Bridge();

  void init(const Time& t); // Provide callback function implementations ...
  
  /// Handles Packet_in packets that come from the switch. Depending on whether
  /// the destination address is already in the table, the controller install 
  /// different flow_entries into the switch through Flow_mod messages
  void packet_in(const Packet_in& pi, const Time& t); 

  void flow_mod_none(const Time& t);
  void flow_mod_src(const Ethernet_addr& addr, uint16_t port, const Time& t);
  void flow_mod_dst(const Ethernet_addr& addr, uint16_t port, const Time& t);
  void flow_mod_full(const Ethernet_addr& src, const Ethernet_addr& dst, uint16_t port, const Time& t);

  bool alive(const Ethernet_addr& addr, const Time& t);
  void learn(const Ethernet_addr& addr, uint16_t port, const Time& t);
  bool is_unicast(const Ethernet_addr& addr);

  std::unordered_map<Ethernet_addr, Record> table;
  Factory* factory;
  uint32_t timeout;
  uint16_t none_priority;
  uint16_t src_priority;
  uint16_t dst_priority;
  uint16_t full_priority;
};

// Export your application's interface
EXPORT_INTERFACE(Bridge)

#endif
