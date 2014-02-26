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

#ifndef FLOWGRAMMABLE_ETHERNET_H
#define FLOWGRAMMABLE_ETHERNET_H

#include <cstdint>
#include <algorithm>

namespace flog {
namespace ethernet {

// -------------------------------------------------------------------------- //
// Address

struct Address
{
  /// Returns the ith component of the ethernet address
  uint8_t&       operator[](std::size_t i)       { return data[i]; }
  const uint8_t& operator[](std::size_t i) const { return data[i]; }

  uint8_t data[6];
};

// Equality comparison
inline bool
operator==(const Address& a, const Address& b)
{
  return std::equal(a.data, a.data + 6, b.data);
}

inline bool
operator!=(const Address& a, const Address& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t 
bytes(const ethernet::Address& a)
{
    return 6;
}

// To string
std::string to_string(const Address& addr);

// Well-known addresses.
constexpr Address broadcast {{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }};


// -------------------------------------------------------------------------- //
// Frame Type

enum Ethertype : uint16_t
{
  ET_IPV4 = 0x0800, /*Internet Protocol version 4 (IPv4)*/
  ET_ARP = 0x0806, /*Address Resolution Protocol (ARP)*/
  ET_WOL = 0x0842, /*Wake-on-LAN[3]*/
  ET_TRILL = 0x22f3, /*IETF TRILL Protocol*/
  ET_DEC_PH4 = 0x6003, /*DECnet Phase IV*/
  ET_RARP = 0x8035, /*Reverse Address Resolution Protocol*/
  ET_ETALK = 0x809b, /*AppleTalk (Ethertalk)*/
  ET_AARP = 0x80f3, /*AppleTalk Address Resolution Protocol (AARP)*/
  ET_VLAN = 0x8100, /*VLAN-tagged frame (IEEE 802.1Q) & Shortest Path Bridging IEEE 802.1aq[4]*/
  ET_IPX_7 = 0x8137, /*IPX*/
  ET_IPX_8 = 0x8138, /*IPX*/
  ET_QNX_QNET = 0x8204, /*QNX Qnet*/
  ET_IPV6 = 0x86dd, /*Internet Protocol Version 6 (IPv6)*/
  ET_EFLOW_CONTROL = 0x8808, /*Ethernet flow control*/
  ET_SLOW = 0x8809, /*Slow Protocols (IEEE 802.3)*/
  ET_COBRA_NET = 0x8819, /*CobraNet*/
  ET_MPLS_UNI = 0x8847, /*MPLS unicast*/
  ET_MPLS_MULT = 0x8848, /*MPLS multicast*/
  ET_PPPOE_DISC = 0x8863, /*PPPoE Discovery Stage*/
  ET_PPPOE_SES = 0x8864, /*PPPoE Session Stage*/
  ET_JUMBO = 0x8870, /*Jumbo Frames*/
  ET_HP_MME = 0x887b, /*HomePlug 1.0 MME*/
  ET_EAP = 0x888e, /*EAP over LAN (IEEE 802.1X)*/
  ET_PROFINET = 0x8892, /*PROFINET Protocol*/
  ET_HSCSI = 0x889a, /*HyperSCSI (SCSI over Ethernet)*/
  ET_ATAOE = 0x88a2, /*ATA over Ethernet*/
  ET_ETHERCAT = 0x88a4, /*EtherCAT Protocol*/
  ET_BRIDGE = 0x88a8, /*Provider Bridging (IEEE 802.1ad) & Shortest Path Bridging IEEE 802.1aq[5]*/
  ET_EPOWERLINK = 0x88ab, /*Ethernet Powerlink[citation needed]*/
  ET_LLDP = 0x88cc, /*Link Layer Discovery Protocol (LLDP)*/
  ET_SERCOS3 = 0x88cd, /*SERCOS III*/
  ET_HP_AV_MME = 0x88e1, /*HomePlug AV MME[citation needed]*/
  ET_MRP = 0x88e3, /*Media Redundancy Protocol (IEC62439-2)*/
  ET_MAC_SEC = 0x88e5, /*MAC security (IEEE 802.1AE)*/
  ET_PTP = 0x88f7, /*Precision Time Protocol (IEEE 1588)*/
  ET_CFM_OAM = 0x8902, /*IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM)*/
  ET_FCOE = 0x8906, /*Fibre Channel over Ethernet (FCoE)*/
  ET_FCOE_INIT = 0x8914, /*FCoE Initialization Protocol*/
  ET_ROCE = 0x8915, /*RDMA over Converged Ethernet (RoCE)*/
  ET_HSR = 0x892f, /*High-availability Seamless Redundancy (HSR)*/
  ET_ECTP = 0x9000, /*Ethernet Configuration Testing Protocol[6]*/
  ET_Q_IN_Q = 0x9100, /*Q-in-Q*/
  ET_LLT = 0xcafe, /*Veritas Low Latency Transport (LLT)[7] for Veritas Cluster Server*/
};

// Equality comparison

// Bytes
inline std::size_t 
bytes(const ethernet::Ethertype& et)
{
    return 2;
}

// To string
std::string to_string(const ethernet::Ethertype& et);

} // namespace ethernet
} // namespace flog

#endif
