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
#include "ethernet.hpp"

namespace flog {
namespace ethernet {

std::string
to_string(const Address& m)
{
  std::stringstream ss;
  ss << std::hex;
  ss << int(m[0]) << "::" << int(m[1]) << "::" << int(m[2]) << "::";
  ss << int(m[3]) << "::" << int(m[4]) << "::" << int(m[5]);
  ss << std::dec;
  return ss.str();
}

std::string
to_string(const Ethertype& et)
{
  switch (et) {
    case 0x0800:
      return "ET_IPV4"; /*Internet Protocol version 4 (IPv4)*/
    case 0x0806:
      return "ET_ARP"; /*Address Resolution Protocol (ARP)*/
    case 0x0842:
      return "ET_WOL"; /*Wake-on-LAN[3]*/
    case 0x22f3:
      return "ET_TRILL"; /*IETF TRILL Protocol*/
    case 0x6003:
      return "ET_DEC_PH4"; /*DECnet Phase IV*/
    case 0x8035:
      return "ET_RARP"; /*Reverse Address Resolution Protocol*/
    case 0x809b:
      return "ET_ETALK"; /*AppleTalk (Ethertalk)*/
    case 0x80f3:
      return "ET_AARP"; /*AppleTalk Address Resolution Protocol (AARP)*/
    case 0x8100:
      return "ET_VLAN"; /*VLAN-tagged frame (IEEE 802.1Q) & Shortest Path
                         * Bridging IEEE 802.1aq[4]*/
    case 0x8137:
      return "ET_IPX_7"; /*IPX*/
    case 0x8138:
      return "ET_IPX_8"; /*IPX*/
    case 0x8204:
      return "ET_QNX_QNET"; /*QNX Qnet*/
    case 0x86dd:
      return "ET_IPV6"; /*Internet Protocol Version 6 (IPv6)*/
    case 0x8808:
      return "ET_EFLOW_CONTROL"; /*Ethernet flow control*/
    case 0x8809:
      return "ET_SLOW"; /*Slow Protocols (IEEE 802.3)*/
    case 0x8819:
      return "ET_COBRA_NET"; /*CobraNet*/
    case 0x8847:
      return "ET_MPLS_UNI"; /*MPLS unicast*/
    case 0x8848:
      return "ET_MPLS_MULT"; /*MPLS multicast*/
    case 0x8863:
      return "ET_PPPOE_DISC"; /*PPPoE Discovery Stage*/
    case 0x8864:
      return "ET_PPPOE_SES"; /*PPPoE Session Stage*/
    case 0x8870:
      return "ET_JUMBO"; /*Jumbo Frames*/
    case 0x887b:
      return "ET_HP_MME"; /*HomePlug 1.0 MME*/
    case 0x888e:
      return "ET_EAP"; /*EAP over LAN (IEEE 802.1X)*/
    case 0x8892:
      return "ET_PROFINET"; /*PROFINET Protocol*/
    case 0x889a:
      return "ET_HSCSI"; /*HyperSCSI (SCSI over Ethernet)*/
    case 0x88a2:
      return "ET_ATAOE"; /*ATA over Ethernet*/
    case 0x88a4:
      return "ET_ETHERCAT"; /*EtherCAT Protocol*/
    case 0x88a8:
      return "ET_BRIDGE"; /*Provider Bridging (IEEE 802.1ad) & Shortest Path
                           * Bridging IEEE 802.1aq[5]*/
    case 0x88ab:
      return "ET_EPOWERLINK"; /*Ethernet Powerlink[citation needed]*/
    case 0x88cc:
      return "ET_LLDP"; /*Link Layer Discovery Protocol (LLDP)*/
    case 0x88cd:
      return "ET_SERCOS3"; /*SERCOS III*/
    case 0x88e1:
      return "ET_HP_AV_MME"; /*HomePlug AV MME[citation needed]*/
    case 0x88e3:
      return "ET_MRP"; /*Media Redundancy Protocol (IEC62439-2)*/
    case 0x88e5:
      return "ET_MAC_SEC"; /*MAC security (IEEE 802.1AE)*/
    case 0x88f7:
      return "ET_PTP"; /*Precision Time Protocol (IEEE 1588)*/
    case 0x8902:
      return "ET_CFM_OAM"; /*IEEE 802.1ag Connectivity Fault Management (CFM)
                            * Protocol / ITU-T Recommendation Y.1731 (OAM)*/
    case 0x8906:
      return "ET_FCOE"; /*Fibre Channel over Ethernet (FCoE)*/
    case 0x8914:
      return "ET_FCOE_INIT"; /*FCoE Initialization Protocol*/
    case 0x8915:
      return "ET_ROCE"; /*RDMA over Converged Ethernet (RoCE)*/
    case 0x892f:
      return "ET_HSR"; /*High-availability Seamless Redundancy (HSR)*/
    case 0x9000:
      return "ET_ECTP"; /*Ethernet Configuration Testing Protocol[6]*/
    case 0x9100:
      return "ET_Q_IN_Q"; /*Q-in-Q*/
    case 0xcafe:
      return "ET_LLT"; /*Veritas Low Latency Transport (LLT)[7] for Veritas Cluster Server*/
    default:
      return "";
  }
}

} // namespace ethernet
} // namespace flog
