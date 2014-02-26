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

#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_2_H
#define FLOWGRAMMABLE_PROTO_OFP_V1_2_H

#include <cassert>
#include <cstdint>
#include <string>
#include <sstream>

#include <libflog/utilities.hpp>
#include <libflog/error.hpp>
#include <libflog/buffer.hpp>
#include <libflog/message.hpp>
#include <libflog/sequence.hpp>
#include <libflog/proto/ofp/ofp.hpp>

#include "factory.hpp"

/// \file v1_2/message.hpp

namespace flog {
namespace ofp {
namespace v1_2 {

// Ensure overload resolution for primitive types.
using ofp::to_buffer;
using ofp::from_buffer;


template<typename T, T K> struct available_error;

// -------------------------------------------------------------------------- //
// Error code

/// Represents a specific failure in message processing. This enumeration is
/// used to describe the result values of to_buffer(), from_buffer(), and
/// is_valid().
enum Error_code { 
  // General codes
  FAILURE = -1,           ///< General failure
  SUCCESS  = 0,            ///< Success

  // Basic codes (copied from Basic_error_code)
  AVAILABLE_BUFFER,        ///< Not enough bytes to read a buffer
  AVAILABLE_STRING,        ///< Not enough bytes to read a string

  EXCESS_SEQUENCE,         ///< Excess data in a sequence

  // Semantic codes (produced during validaation)
  BAD_OXM_FIELD,           ///< Invalid value of OXM_field
  BAD_OXM_CLASS,           ///< Invalid value of OXM_class
  BAD_OXM_EF_IN_PORT,      ///< Invalid value of Oxm_In_Port
  BAD_OXM_EF_IN_PHY_PORT,  ///< Invalid value of Oxm_In_Phy_Port
  BAD_OXM_INIT,		   ///< Invalid OXM payload
  BAD_MATCH_TYPE,	   ///< Invalid value of Match Type
  BAD_MATCH_LENGTH,        ///< Invalid Match Length
  BAD_ACTION,              ///< Invalid value of Action_type
  BAD_ACTION_LENGTH,       ///< The action length is invalid
  BAD_ACTION_INIT,         ///< An uninitialized action was validated
  BAD_ACTION_ENQUEUE_PORT, ///< The port in Action_enqueue is invalid
  BAD_INSTRUCTION,	   ///< Invalid value for Instruction_type
  BAD_INSTRUCTION_LENGTH,  ///< The instruction length is invalid
  BAD_PORT_ID,             ///< The id in Port is invalid
  BAD_QUEUE_PROPERTY_INIT, ///< An uninitializes queue_property was validated
  BAD_QUEUE_PROPERTY,	   ///< Invalid value for Queue Property type
  BAD_QUEUE_PROPERTY_LENGTH, ///The Queue length is invalid
  BAD_BUCKET_LENGTH,        ///< The bucket length is invalid
  BAD_VERSION,             ///< The version number was not 3
  BAD_MESSAGE,             ///< Invalid vaue of Message_type
  BAD_MESSAGE_LENGTH,      ///< Message length/Header length is invalid
  BAD_MESSAGE_INIT,        ///< An uninitialised Header message 
  BAD_HEADER_LENGTH,       ///< The header length is invalid
  BAD_ERROR_TYPE,          ///< Invalid value of Error::Type
  BAD_HELLO_FAILED,        ///< Invalid value of Error::Hello_failed
  BAD_BAD_REQUEST,         ///< Invalid value of Error::Bad_request
  BAD_BAD_MATCH,           ///< Invalid value of Error::Bad_action
  BAD_BAD_ACTION,          ///< Invlaid value of Error::Bad_action
  BAD_BAD_INSTRUCTION,     ///< Invalid value of Error::Bad_instruction
  BAD_FLOW_MOD_FAILED,     ///< Invalid value of Error::Flow_mod_failed
  BAD_GROUP_MOD_FAILED,    ///< Invalid value of Error::Group_mod_failed
  BAD_PORT_MOD_FAILED,     ///< Invalid value of Error::Port_mod_failed
  BAD_QUEUE_OP_FAILED,     ///< Invalid value of Error::Queue_op_failed
  BAD_TABLE_MOD_FAILED,    ///< Invalid value of Error::Table_mod_failed
  BAD_SWITCH_CONFIG_FAILED,///< Invalid value of Error::Switch_config_failed
  BAD_ROLE_REQUEST_FAILED, ///< Invalid value of Error::Role_request_failed
  BAD_CONFIG_FLAGS,        ///< Invalid value for config flags
  BAD_FEATURE_RES_CAPABILITY,
  BAD_PACKET_IN_REASON,    ///< Invalid value of Packet_in::Reason
  BAD_FLOW_REMOVED_REASON, ///< Invalid value of Flow_removed::Reason
  BAD_PORT_STATUS_REASON,  ///< Invalid value of Port_status::Reason
  BAD_PACKET_OUT_LENGTH,   ///< Packet Out Legth is invalid
  BAD_FLOW_MOD_COMMAND,    ///< Invalid value of Flow_mod::Command
  BAD_FLOW_MOD_FLAGS,      ///< Invalid value for Flow_mod::Flags
  BAD_GROUP_MOD_COMMAND,   ///< Invalid value of Group_mod::Command
  BAD_GROUP_MOD_TYPE,      ///< Invalid value of Group_mod::Type
  BAD_TABLE_MOD_CONFIG,	   ///< Invalid value of Table_mod::Config
  BAD_STATS_TYPE,	   ///< Invalid value of Stats::Type
  BAD_STATS_REQ,           ///< Invalid Stats Request Type
  BAD_STATS_REQ_INIT,      ///< An uninitialised Stats request is validated
  BAD_STATS_RES,           ///< Invalid Stats Response Type
  BAD_STATS_RES_INIT,      ///< An uninitialised Stats response is validated
  BAD_QUEUE_GET_CONFIG_REQ_PORT, ///<An invalid port number 
  BAD_ROLE,                ///< Invalid Role	

  // Availability errors 
  AVAILABLE_OXM_EXPERIMENTER,
  AVAILABLE_OXM_EF_IPV6_SRC_MASK,
  AVAILABLE_OXM_EF_IPV6_DST_MASK,
  AVAILABLE_OXM_EF_IPV6_SRC,
  AVAILABLE_OXM_EF_IPV6_DST,
  AVAILABLE_OXM_EF_IPV6_ND_TARGET,
  AVAILABLE_OXM_EF_METADATA_MASK,
  AVAILABLE_OXM_EF_METADATA,
  AVAILABLE_OXM_EF_ETH_SRC_MASK,
  AVAILABLE_OXM_EF_ETH_DST_MASK,
  AVAILABLE_OXM_EF_ARP_SHA_MASK,
  AVAILABLE_OXM_EF_ARP_THA_MASK,
  AVAILABLE_OXM_EF_ETH_SRC,
  AVAILABLE_OXM_EF_ETH_DST,
  AVAILABLE_OXM_EF_ARP_SHA,
  AVAILABLE_OXM_EF_ARP_THA,
  AVAILABLE_OXM_EF_IPV4_SRC_MASK,
  AVAILABLE_OXM_EF_IPV4_DST_MASK,
  AVAILABLE_OXM_EF_ARP_SPA_MASK,
  AVAILABLE_OXM_EF_ARP_TPA_MASK,
  AVAILABLE_OXM_EF_IPV6_ND_SLL,
  AVAILABLE_OXM_EF_IPV6_ND_TLL,
  AVAILABLE_OXM_EF_IPV6_FLABEL_MASK,
  AVAILABLE_OXM_EF_IN_PORT,
  AVAILABLE_OXM_EF_IN_PHY_PORT,
  AVAILABLE_OXM_EF_MPLS_LABEL,
  AVAILABLE_OXM_EF_IPV6_FLABEL,
  AVAILABLE_OXM_EF_IPV4_SRC,
  AVAILABLE_OXM_EF_IPV4_DST,
  AVAILABLE_OXM_EF_ARP_SPA,
  AVAILABLE_OXM_EF_ARP_TPA,
  AVAILABLE_OXM_EF_VLAN_VID_MASK,
  AVAILABLE_OXM_EF_VLAN_PCP,      
  AVAILABLE_OXM_EF_IP_DSCP,       
  AVAILABLE_OXM_EF_IP_ECN,      
  AVAILABLE_OXM_EF_IP_PROTO,      
  AVAILABLE_OXM_EF_ICMPV4_TYPE,      
  AVAILABLE_OXM_EF_ICMPV4_CODE,      
  AVAILABLE_OXM_EF_ICMPV6_TYPE,      
  AVAILABLE_OXM_EF_ICMPV6_CODE,      
  AVAILABLE_OXM_EF_MPLS_TC,     
  AVAILABLE_OXM_EF_VLAN_VID,     
  AVAILABLE_OXM_EF_ETH_TYPE,     
  AVAILABLE_OXM_EF_TCP_SRC,     
  AVAILABLE_OXM_EF_TCP_DST,     
  AVAILABLE_OXM_EF_UDP_SRC,     
  AVAILABLE_OXM_EF_UDP_DST,     
  AVAILABLE_OXM_EF_SCTP_SRC,     
  AVAILABLE_OXM_EF_SCTP_DST,     
  AVAILABLE_OXM_EF_ARP_OP,   
  AVAILABLE_OXM_ENTRY_PAYLOAD,  
  AVAILABLE_OXM_ENTRY_HEADER,    ///< Not enough bytes for OXM Header

  AVAILABLE_MATCH,
  AVAILABLE_MATCH_PADDING, 

  AVAILABLE_ACTION_EXPERIMENTER,
  AVAILABLE_ACTION_SET_FIELD_PADDING,
  AVAILABLE_ACTION_SET_FIELD,
  AVAILABLE_ACTION_SET_NW_TTL,
  AVAILABLE_ACTION_DEC_NW_TTL,
  AVAILABLE_ACTION_GROUP,
  AVAILABLE_ACTION_SET_QUEUE,
  AVAILABLE_ACTION_PUSH_VLAN,
  AVAILABLE_ACTION_POP_VLAN,
  AVAILABLE_ACTION_PUSH_MPLS,
  AVAILABLE_ACTION_POP_MPLS,
  AVAILABLE_ACTION_DEC_MPLS_TTL,
  AVAILABLE_ACTION_SET_MPLS_TTL,
  AVAILABLE_ACTION_COPY_TTL_IN,
  AVAILABLE_ACTION_COPY_TTL_OUT,
  AVAILABLE_ACTION_OUTPUT,       ///< Not enough bytes for an Action_output
  AVAILABLE_ACTION_SET_VLAN_VID, ///< Not enough bytes for an Action_set_vlan_vid
  AVAILABLE_ACTION_SET_VLAN_PCP, ///< ...
  AVAILABLE_ACTION_STRIP_VLAN,
  AVAILABLE_ACTION_SET_DL_SRC,
  AVAILABLE_ACTION_SET_DL_DST,
  AVAILABLE_ACTION_SET_NW_SRC,
  AVAILABLE_ACTION_SET_NW_DST,
  AVAILABLE_ACTION_SET_NW_TOS,
  AVAILABLE_ACTION_SET_TP_SRC,
  AVAILABLE_ACTION_SET_TP_DST,
  AVAILABLE_ACTION_ENQUEUE,
  AVAILABLE_ACTION_VENDOR,
  AVAILABLE_ACTION_HEADER,
  AVAILABLE_ACTION_PAYLOAD,
  
  AVAILABLE_INSTRUCTION_GOTO_TABLE,
  AVAILABLE_INSTRUCTION_WRITE_METADATA,
  AVAILABLE_INSTRUCTION_WRITE_ACTIONS,
  AVAILABLE_INSTRUCTION_APPLY_ACTIONS,
  AVAILABLE_INSTRUCTION_CLEAR_ACTIONS,
  AVAILABLE_INSTRUCTION_EXPERIMENTER,
  AVAILABLE_INSTRUCTION_PAYLOAD,
  AVAILABLE_INSTRUCTION_HEADER,

  AVAILABLE_PORT,

  AVAILABLE_QUEUE_PROPERTY_MIN_RATE,
  AVAILABLE_QUEUE_PROPERTY_MAX_RATE,
  AVAILABLE_QUEUE_PROPERTY_EXPERIMENTER,
  AVAILABLE_QUEUE_PROPERTY_HEADER,
  AVAILABLE_QUEUE_PROPERTY_PAYLOAD,
  AVAILABLE_QUEUE_PROPERTIES,
  AVAILABLE_QUEUE,
 
  AVAILABLE_BUCKET,
  AVAILABLE_BUCKET_COUNTER,
  
  AVAILABLE_HEADER,
  AVAILABLE_PAYLOAD,
  AVAILABLE_HELLO,
  AVAILABLE_ERROR,
  AVAILABLE_ECHO_REQ,
  AVAILABLE_ECHO_RES,
  AVAILABLE_EXPERIMENTER,
  AVAILABLE_FEATURE_REQ,
  AVAILABLE_FEATURE_RES,
  AVAILABLE_GET_CONFIG_REQ,
  AVAILABLE_GET_CONFIG_RES,
  AVAILABLE_SET_CONFIG,
  AVAILABLE_PACKET_IN,
  AVAILABLE_PACKET_IN_PADDING,
  AVAILABLE_FLOW_REMOVED,
  AVAILABLE_PORT_STATUS,
  AVAILABLE_PACKET_OUT,
  AVAILABLE_FLOW_MOD,
  AVAILABLE_GROUP_MOD,
  AVAILABLE_PORT_MOD,
  AVAILABLE_TABLE_MOD,
  
  AVAILABLE_STATS_REQ,
  AVAILABLE_STATS_REQ_HEADER,
  AVAILABLE_STATS_REQ_FLOW,
  AVAILABLE_STATS_REQ_AGGREGATE, 
  AVAILABLE_STATS_REQ_PORT,
  AVAILABLE_STATS_REQ_GROUP,
  AVAILABLE_STATS_REQ_QUEUE,
  AVAILABLE_STATS_REQ_EXPERIMENTER,   

  AVAILABLE_STATS_RES,
  AVAILABLE_STATS_RES_HEADER,
  AVAILABLE_STATS_RES_DESC,
  AVAILABLE_STATS_RES_FLOW,
  AVAILABLE_STATS_RES_FLOWS,
  AVAILABLE_STATS_RES_AGGREGATE,
  AVAILABLE_STATS_RES_PORT,
  AVAILABLE_STATS_RES_PORTS,
  AVAILABLE_STATS_RES_QUEUE,
  AVAILABLE_STATS_RES_QUEUES,
  AVAILABLE_STATS_RES_TABLE,
  AVAILABLE_STATS_RES_TABLES,
  AVAILABLE_STATS_RES_GROUP,
  AVAILABLE_STATS_RES_GROUPS,
  AVAILABLE_STATS_RES_GROUP_DESC,
  AVAILABLE_STATS_RES_GROUP_DESCS,
  AVAILABLE_STATS_RES_GROUP_FEATURES,
  AVAILABLE_STATS_RES_EXPERIMENTER,

  AVAILABLE_BARRIER_REQ,
  AVAILABLE_BARRIER_RES,
  AVAILABLE_QUEUE_GET_CONFIG_REQ,
  AVAILABLE_QUEUE_GET_CONFIG_RES,
  AVAILABLE_ROLE_REQ,
  AVAILABLE_ROLE_RES,

  // View update errors
  EXCESS_OXM,
  EXCESS_MATCH,
  EXCESS_ACTION,
  EXCESS_INSTRUCTION,
  EXCESS_QUEUE,
  EXCESS_QUEUE_PROPERTY,
  EXCESS_BUCKET,
  EXCESS_PACKET_OUT,
  EXCESS_STATS_RES_FLOW,
  EXCESS_STATS_RES_GROUP,
  EXCESS_STATS_GROUP_DESC,
  EXCESS_PAYLOAD
};

/// Represents the testable result of message processing functions. This
/// is the result type of the to_buffer(), from_buffer(), and is_valid()
/// operations.
using Error_condition = Condition<Error_code>;

/// Represents a variable declaration that captures an error conditition.
using Error_decl = Condition_decl<Error_code>;

// -------------------------------------------------------------------------- //
// Structures
//
// The following classes are structures used by various messages:
//    - Oxm
//    - Match
//    - Action
//    - Instruction
//    - Port
//    - Queue
//    - Bucket
//    - Bucket Counter
// -------------------------------------------------------------------------- //
// OXM entry class

enum OXM_entry_class : uint16_t
{
  NXM_0 = 0x0000, NXM_1 = 0x0001, OPEN_FLOW_BASIC = 0x8000,
  OXM_EXPERIMENTER = 0xffff
};

Error_condition is_valid(const OXM_entry_class& c);

std::string to_string(const OXM_entry_class c);

// -------------------------------------------------------------------------- //
// OXM_entry_field

enum OXM_entry_field : uint8_t
{
  OXM_EF_IN_PORT = 0x00, OXM_EF_IN_PHY_PORT = 0x02, OXM_EF_METADATA = 0x04,
  OXM_EF_METADATA_MASK = 0x05, OXM_EF_ETH_DST = 0x06,
  OXM_EF_ETH_DST_MASK = 0x07, OXM_EF_ETH_SRC = 0x08,
  OXM_EF_ETH_SRC_MASK = 0x09, OXM_EF_ETH_TYPE = 0x0a, OXM_EF_VLAN_VID = 0x0c,
  OXM_EF_VLAN_VID_MASK = 0x0d, OXM_EF_VLAN_PCP = 0x0e, OXM_EF_IP_DSCP = 0x10,
  OXM_EF_IP_ECN = 0x12, OXM_EF_IP_PROTO = 0x14, OXM_EF_IPV4_SRC = 0x16,
  OXM_EF_IPV4_SRC_MASK = 0x17, OXM_EF_IPV4_DST = 0x18,
  OXM_EF_IPV4_DST_MASK = 0x19, OXM_EF_TCP_SRC = 0x1a, OXM_EF_TCP_DST = 0x1c,
  OXM_EF_UDP_SRC = 0x1e, OXM_EF_UDP_DST = 0x20, OXM_EF_SCTP_SRC = 0x22,
  OXM_EF_SCTP_DST = 0x24, OXM_EF_ICMPV4_TYPE = 0x26,
  OXM_EF_ICMPV4_CODE = 0x28, OXM_EF_ARP_OP = 0x2a, OXM_EF_ARP_SPA = 0x2c,
  OXM_EF_ARP_SPA_MASK = 0x2d, OXM_EF_ARP_TPA = 0x2e,
  OXM_EF_ARP_TPA_MASK = 0x2f, OXM_EF_ARP_SHA = 0x30,
  OXM_EF_ARP_SHA_MASK = 0x31, OXM_EF_ARP_THA = 0x32,
  OXM_EF_ARP_THA_MASK = 0x33, OXM_EF_IPV6_SRC = 0x34,
  OXM_EF_IPV6_SRC_MASK = 0x35, OXM_EF_IPV6_DST = 0x36,
  OXM_EF_IPV6_DST_MASK = 0x37, OXM_EF_IPV6_FLABEL = 0x38,
  OXM_EF_IPV6_FLABEL_MASK = 0x39, OXM_EF_ICMPV6_TYPE = 0x3a,
  OXM_EF_ICMPV6_CODE = 0x3c, OXM_EF_IPV6_ND_TARGET = 0x3e,
  OXM_EF_IPV6_ND_SLL = 0x40, OXM_EF_IPV6_ND_TLL = 0x42,
  OXM_EF_MPLS_LABEL = 0x44, OXM_EF_MPLS_TC = 0x46,
};

// Returns true when f is a valid OXM entry field value.
Error_condition is_valid(OXM_entry_field f);

// To string
std::string to_string(const OXM_entry_field f);

// Payload base
template<OXM_entry_field K>
  using OXM_entry_payload_base = Basic_payload_base<OXM_entry_field, K>;

// -------------------------------------------------------------------------- //
// OXM entry payload: 8 bits

/// OpenFlow extensible match classes
///
/// \relates OXM_entry_header
template<OXM_entry_field K>
  struct OXM_entry_base8 : OXM_entry_payload_base<K>
  {
    OXM_entry_base8() = default;
    explicit OXM_entry_base8(uint8_t v) : value(v) { }

    uint8_t value;
  };

template<OXM_entry_field K>
  bool operator==(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b);

template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b);

template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base8<K>&); 

template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_base8<K>&);

template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base8<K>& b);

template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base8<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : VLAN PCP

/// Match priority field for VLAN. (see OXM_entry_payload)
struct OXM_entry_vlan_pcp : OXM_entry_base8<OXM_EF_VLAN_PCP> { };

/// \relates OXM_entry_vlan_pcp
std::string to_string(const OXM_entry_vlan_pcp&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IP DSCP

/// Match differentiated services code point field for IP. (see
/// OXM_entry_payload)
struct OXM_entry_ip_dscp : OXM_entry_base8<OXM_EF_IP_DSCP> { };

/// \relates OXM_entry_ip_dscp
std::string to_string(const OXM_entry_ip_dscp&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IP ECN

/// Match explicit congestion notification field for IP. (see OXM_entry_payload)
struct OXM_entry_ip_ecn : OXM_entry_base8<OXM_EF_IP_ECN> { };

/// \relates OXM_entry_ip_ecn
std::string to_string(const OXM_entry_ip_ecn&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IP PROTO

/// Match protocol field for IP. (see OXM_entry_payload)
struct OXM_entry_ip_proto : OXM_entry_base8<OXM_EF_IP_PROTO> { };

/// \relates OXM_entry_ip_proto
std::string to_string(const OXM_entry_ip_proto&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ICMPv4 type

/// Match type field for Internet control message protocol (ICMP) for IPv4. (see OXM_entry_payload)
struct OXM_entry_icmpv4_type : OXM_entry_base8<OXM_EF_ICMPV4_TYPE> { };

/// \relates OXM_entry_icmpv4_type
std::string to_string(const OXM_entry_icmpv4_type&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ICMPv4 code

/// Match code field for ICMP for IPv4. (see OXM_entry_payload)
struct OXM_entry_icmpv4_code : OXM_entry_base8<OXM_EF_ICMPV4_CODE> { };

/// \relates OXM_entry_icmpv4_code
std::string to_string(const OXM_entry_icmpv4_code&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ICMPv6 type

/// Match type field for ICMP for IPv6. (see OXM_entry_payload)
struct OXM_entry_icmpv6_type : OXM_entry_base8<OXM_EF_ICMPV6_TYPE> { };

/// \relates OXM_entry_icmpv6_type
std::string to_string(const OXM_entry_icmpv6_type&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ICMPv6 code

/// Match code field for ICMP for IPv6. (see OXM_entry_payload)
struct OXM_entry_icmpv6_code : OXM_entry_base8<OXM_EF_ICMPV6_CODE> { };

/// \relates OXM_entry_icmpv6_code
std::string to_string(const OXM_entry_icmpv6_code&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : MPLS TC

/// Match traffic class (TC) field for multiprotocol label switching (MPLS).
/// (see OXM_entry_payload)
struct OXM_entry_mpls_tc : OXM_entry_base8<OXM_EF_MPLS_TC> { };

/// \relates OXM_entry_mpls_tc
std::string to_string(const OXM_entry_mpls_tc&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload: 16 bits

/// Base class for 16-bit OXM entries. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base16 : OXM_entry_payload_base<K>
  {
    OXM_entry_base16() = default;
    explicit OXM_entry_base16(uint16_t v): value(v) { }

    uint16_t value;
  };

/// \relates OXM_entry_base16
template<OXM_entry_field K>
  bool operator==(const OXM_entry_base16<K>& a, const OXM_entry_base16<K>& b);

/// \relates OXM_entry_base16
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base16<K>& a, const OXM_entry_base16<K>& b);

/// \relates OXM_entry_base16
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base16<K>&);

/// \relates OXM_entry_base16
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_base16<K>&);

/// \relates OXM_entry_base16
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base16<K>& b);

/// \relates OXM_entry_base16
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base16<K>& b);


// -------------------------------------------------------------------------- //
// OXM entry payload : VLAN VID

/// Match VID of the outer VLAN tag
struct OXM_entry_vlan_vid : OXM_entry_base16<OXM_EF_VLAN_VID> { };

/// \relates OXM_entry_vlan_vid
std::string to_string(const OXM_entry_vlan_vid&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : Eth type

/// Match Ethernet type.
struct OXM_entry_eth_type : OXM_entry_base16<OXM_EF_ETH_TYPE> { };

/// \relates OXM_entry_eth_type
std::string to_string(const OXM_entry_eth_type&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : TCP src

/// Match TCP source address
struct OXM_entry_tcp_src : OXM_entry_base16<OXM_EF_TCP_SRC> { };

/// \relates OXM_entry_tcp_src
std::string to_string(const OXM_entry_tcp_src&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : TCP dst

/// Match TCP destination address
struct OXM_entry_tcp_dst : OXM_entry_base16<OXM_EF_TCP_DST> { };

/// \relates OXM_entry_tcp_dst
std::string to_string(const OXM_entry_tcp_dst&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : UDP src

/// Match UDP source address
struct OXM_entry_udp_src : OXM_entry_base16<OXM_EF_UDP_SRC> { };

/// \relates OXM_entry_udp_src
std::string to_string(const OXM_entry_udp_src&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : UDP dst

/// Match UDP destination address
struct OXM_entry_udp_dst : OXM_entry_base16<OXM_EF_UDP_DST> { };

/// \relates OXM_entry_udp_dst
std::string to_string(const OXM_entry_udp_dst&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : SCTP src

/// Match SCTP source address
struct OXM_entry_sctp_src : OXM_entry_base16<OXM_EF_SCTP_SRC> { };

/// \relates OXM_entry_sctp_src
std::string to_string(const OXM_entry_sctp_src&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : SCTP dst

/// Match SCTP destination address
struct OXM_entry_sctp_dst : OXM_entry_base16<OXM_EF_SCTP_DST> { };

/// \relates OXM_entry_sctp_dst
std::string to_string(const OXM_entry_sctp_dst&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ARP op

/// Match ARP op field
struct OXM_entry_arp_op : OXM_entry_base16<OXM_EF_ARP_OP> { };

/// \relates OXM_entry_arp_op
std::string to_string(const OXM_entry_arp_op&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 16 bits

/// Base class for 16-bit OXM entries with a bit mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base16_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_base16_mask() = default;
    OXM_entry_base16_mask(uint16_t v, uint16_t m) : value(v), mask(m) { }

    uint16_t value;
    uint16_t mask;
  };

/// \relates OXM_entry_base16_mask
template<OXM_entry_field K>
 bool operator==(const OXM_entry_base16_mask<K>& a,
                 const OXM_entry_base16_mask<K>& b);

/// \relates OXM_entry_base16_mask
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base16_mask<K>& a,
                  const OXM_entry_base16_mask<K>& b);

/// \relates OXM_entry_base16_mask
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base16_mask<K>&);

/// \relates OXM_entry_base16_mask
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_base16_mask<K>&);

/// \relates OXM_entry_base16_mask
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base16_mask<K>& b);

/// \relates OXM_entry_base16_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base16_mask<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : VLAN VID mask

/// Match VLAN VID with mask
struct OXM_entry_vlan_vid_mask
  : OXM_entry_base16_mask<OXM_EF_VLAN_VID_MASK> { };
std::string to_string(const OXM_entry_vlan_vid_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload: 32 bits

/// Base class for 32-bit OXM entries. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base32 : OXM_entry_payload_base<K>
  {
    OXM_entry_base32() = default;
    explicit OXM_entry_base32(uint32_t v) : value(v) { }

    uint32_t value;
  };

/// \relates OXM_entry_base32
template<OXM_entry_field K>
  bool operator==(const OXM_entry_base32<K>& a, const OXM_entry_base32<K>& b);

/// \relates OXM_entry_base32
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base32<K>& a, const OXM_entry_base32<K>& b);

/// \relates OXM_entry_base32
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base32<K>&);

/// \relates OXM_entry_base32
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_base32<K>&);

/// \relates OXM_entry_base32
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base32<K>& b);

/// \relates OXM_entry_base32
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base32<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : in port

/// Match the incoming port of the packet
struct OXM_entry_in_port : OXM_entry_base32<OXM_EF_IN_PORT> { };

/// \relates OXM_entry_in_port
std::string to_string(const OXM_entry_in_port&, Formatter&);
inline Error_condition is_valid(const OXM_entry_in_port& p);
 
// -------------------------------------------------------------------------- //
// OXM entry payload : in phy port

/// Match the incoming physical port of the packet
struct OXM_entry_in_phy_port : OXM_entry_base32<OXM_EF_IN_PHY_PORT> { };

/// \relates OXM_entry_in_phy_port
std::string to_string(const OXM_entry_in_phy_port&, Formatter&);
inline Error_condition is_valid(const OXM_entry_in_phy_port& p); 

// -------------------------------------------------------------------------- //
// OXM entry payload : mpls label

/// Match the outer MPLS label
struct OXM_entry_mpls_label : OXM_entry_base32<OXM_EF_MPLS_LABEL> { };

/// \relates OXM_entry_mpls_label
std::string to_string(const OXM_entry_mpls_label&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 flabel

/// Match IPv6
struct OXM_entry_ipv6_flabel : OXM_entry_base32<OXM_EF_IPV6_FLABEL> { };

/// \relates OXM_entry_ipv6_flabel
std::string to_string(const OXM_entry_ipv6_flabel&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload: IPv4

/// Base class for OXM entries with an Internet Protocol version 4 (IPv4)
/// address. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ipv4 : OXM_entry_payload_base<K>
  {
    OXM_entry_ipv4() = default;
    explicit OXM_entry_ipv4(Ipv4_addr v) : value(v) { }

    Ipv4_addr value;
  };

/// \relates OXM_entry_ipv4
template<OXM_entry_field K>
  bool operator==(const OXM_entry_ipv4<K>& a, const OXM_entry_ipv4<K>& b);

/// \relates OXM_entry_ipv4
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_ipv4<K>& a, const OXM_entry_ipv4<K>& b);

/// \relates OXM_entry_ipv4
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_ipv4<K>&);

/// \relates OXM_entry_ipv4
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_ipv4<K>&);

/// \relates OXM_entry_ipv4
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ipv4<K>& b);

/// \relates OXM_entry_ipv4
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ipv4<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv4 src

/// Match IPv4 source address
struct OXM_entry_ipv4_src : OXM_entry_ipv4<OXM_EF_IPV4_SRC> { };

/// \relates OXM_entry_ipv4_src
std::string to_string(const OXM_entry_ipv4_src&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv4 dst

/// Match IPv4 destination address
struct OXM_entry_ipv4_dst : OXM_entry_ipv4<OXM_EF_IPV4_DST> { };

// OXM entry payload : IPv4 dst
std::string to_string(const OXM_entry_ipv4_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : ARP SPA

/// Match source IPv4 address in the ARP payload
struct OXM_entry_arp_spa : OXM_entry_ipv4<OXM_EF_ARP_SPA> { };

/// \relates OXM_entry_arp_spa
std::string to_string(const OXM_entry_arp_spa&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : ARP TPA

/// Match destination IPv4 address in the ARP payload
struct OXM_entry_arp_tpa : OXM_entry_ipv4<OXM_EF_ARP_TPA> { };

/// \relates OXM_entry_arp_tpa
std::string to_string(const OXM_entry_arp_tpa&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 32 bits

/// Base class for OXM entries with an Internet Protocol version 4 (IPv4)
/// address with a bit mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base32_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_base32_mask() = default;
    OXM_entry_base32_mask(uint32_t v, uint32_t m): value(v), mask(m) { }

    uint32_t value;
    uint32_t mask;
  };

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  bool operator==(const OXM_entry_base32_mask<K>& a,
                  const OXM_entry_base32_mask<K>& b);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base32_mask<K>& a,
                  const OXM_entry_base32_mask<K>& b);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base32_mask<K>&);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_base32_mask<K>&);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base32_mask<K>& b);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base32_mask<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 flabel mask

/// Match an IPv6 flow label with mask
struct OXM_entry_ipv6_flabel_mask
  : OXM_entry_base32_mask<OXM_EF_IPV6_FLABEL_MASK> { };

/// \relates OXM_entry_ipv6_flabel_mas
std::string to_string(const OXM_entry_ipv6_flabel_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload with mask: IP

/// Base class for OXM entries with an Internet Protocol version 4 (IPv4)
/// address with a bit mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ipv4_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_ipv4_mask() = default;
    OXM_entry_ipv4_mask(uint32_t v, uint32_t m): value(v), mask(m) { }

    Ipv4_addr value;
    Ipv4_addr mask;
  };

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  bool operator==(const OXM_entry_ipv4_mask<K>& a,
                  const OXM_entry_ipv4_mask<K>& b);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_ipv4_mask<K>& a,
                  const OXM_entry_ipv4_mask<K>& b);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_ipv4_mask<K>&);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_ipv4_mask<K>&);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ipv4_mask<K>& b);

/// \relates OXM_entry_ipv4_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ipv4_mask<K>& b);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv4 src mask

/// Match source address for IPv4 with bit mask. (see OXM_entry_payload)
struct OXM_entry_ipv4_src_mask
  : OXM_entry_ipv4_mask<OXM_EF_IPV4_SRC_MASK> { };

/// \relates OXM_entry_ipv4_src_mask
std::string to_string(const OXM_entry_ipv4_src_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv4 dst mask

/// Match destination address for IPv4 with bit mask. (see OXM_entry_payload)
struct OXM_entry_ipv4_dst_mask
  : OXM_entry_ipv4_mask<OXM_EF_IPV4_DST_MASK> { };

/// \relates OXM_entry_ipv4_dst_mask
std::string to_string(const OXM_entry_ipv4_dst_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ARP SPA mask

/// Match source IPv4 address for ARP with bit mask. (see OXM_entry_payload)
struct OXM_entry_arp_spa_mask
  : OXM_entry_ipv4_mask<OXM_EF_ARP_SPA_MASK> { };

/// \relates OXM_entry_arp_spa_mask
std::string to_string(const OXM_entry_arp_spa_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ARP TPA mask

/// Match destination IPv4 address for ARP with bit mask.
/// (see OXM_entry_payload)
struct OXM_entry_arp_tpa_mask
  : OXM_entry_ipv4_mask<OXM_EF_ARP_TPA_MASK> { };

/// \relates OXM_entry_arp_tpa
std::string to_string(const OXM_entry_arp_tpa&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload: ethernet

/// Base class for OXM entries with an Ethernet hardware address.
/// (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ethernet : OXM_entry_payload_base<K>
  {
    OXM_entry_ethernet() = default;
    explicit OXM_entry_ethernet(Ethernet_addr v): value(v) { }

    Ethernet_addr value;
  };

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  bool operator==(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b);

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b);

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_ethernet<K>&);

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_ethernet<K>&);

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ethernet<K>& b);

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ethernet<K>& b);


// -------------------------------------------------------------------------- //
// OXM entry payload : Eth dst

/// Match destination address for Ethernet. (see OXM_entry_payload)
struct OXM_entry_eth_dst : OXM_entry_ethernet<OXM_EF_ETH_DST> { };

/// \relates OXM_entry_eth_dst
std::string to_string(const OXM_entry_eth_dst&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : Eth src

/// Match source address for Ethernet. (see OXM_entry_payload)
struct OXM_entry_eth_src : OXM_entry_ethernet<OXM_EF_ETH_SRC> { };

/// \relates OXM_entry_eth_src
std::string to_string(const OXM_entry_eth_src&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ARP SHA

/// Match source Ethernet address for ARP. (see OXM_entry_payload)
struct OXM_entry_arp_sha : OXM_entry_ethernet<OXM_EF_ARP_SHA> { };

/// \relates OXM_entry_arp_sha
std::string to_string(const OXM_entry_arp_sha&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ARP THA

/// Match destination Ethernet address for ARP. (see OXM_entry_payload)
struct OXM_entry_arp_tha : OXM_entry_ethernet<OXM_EF_ARP_THA> { };

/// \relates OXM_entry_arp_tha
std::string to_string(const OXM_entry_arp_tha&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 ND SLL

/// Match source link layer address for IPv6 neighbor discovery. (see
/// OXM_entry_payload)
struct OXM_entry_ipv6_nd_sll : OXM_entry_ethernet<OXM_EF_IPV6_ND_SLL> { };

/// \relates OXM_entry_ipv6_nd_sll
std::string to_string(const OXM_entry_ipv6_nd_sll&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 ND TLL

/// Match destination link layer address for IPv6 neighbor discovery. (see
/// OXM_entry_payload)
struct OXM_entry_ipv6_nd_tll : OXM_entry_ethernet<OXM_EF_IPV6_ND_TLL> { };

/// \relates OXM_entry_ipv6_nd_tll
std::string to_string(const OXM_entry_ipv6_nd_tll&, Formatter&);



// -------------------------------------------------------------------------- //
// OXM entry payload with mask: Ethernet

/// Base class for OXM entries with an Ethernet hardware address with a bit
/// mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ethernet_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_ethernet_mask() = default;
    OXM_entry_ethernet_mask(Ethernet_addr v, Ethernet_addr m): value(v), mask(m) {}

    Ethernet_addr value;
    Ethernet_addr mask;
  };

/// \relates OXM_entry_ethernet_mask
template<OXM_entry_field K>
  bool operator==(const OXM_entry_ethernet_mask<K>& a,
                  const OXM_entry_ethernet_mask<K>& b);

/// \relates OXM_entry_ethernet_mask
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_ethernet_mask<K>& a,
                  const OXM_entry_ethernet_mask<K>& b);

/// \relates OXM_entry_ethernet_mask
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_ethernet_mask<K>&);

/// \relates OXM_entry_ethernet_mask
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_ethernet_mask<K>&);

/// \relates OXM_entry_ethernet_mask
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ethernet_mask<K>& b);

/// \relates OXM_entry_ethernet_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ethernet_mask<K>& b);


// -------------------------------------------------------------------------- //
// OXM entry payload : Eth dst mask

/// Match destination address for Ethernet with bit mask. (see OXM_entry_payload)
struct OXM_entry_eth_dst_mask
  : OXM_entry_ethernet_mask<OXM_EF_ETH_DST_MASK> { };

/// \relates OXM_entry_eth_dst_mask
std::string to_string(const OXM_entry_eth_dst_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : Eth src mask

/// Match source address for Ethernet with bit mask. (see OXM_entry_payload)
struct OXM_entry_eth_src_mask
  : OXM_entry_ethernet_mask<OXM_EF_ETH_SRC_MASK> { };

/// \relates OXM_entry_eth_src_mask
std::string to_string(const OXM_entry_eth_src_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ARP SHA mask

/// Match source Ethernet address for ARP with bit mask. (see OXM_entry_payload)
struct OXM_entry_arp_sha_mask
  : OXM_entry_ethernet_mask<OXM_EF_ARP_SHA_MASK> { };

/// \relates OXM_entry_arp_sha_mask
std::string to_string(const OXM_entry_arp_sha_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : ARP THA mask

/// Match destination Ethernet address for ARP with bit mask. (see OXM_entry_payload)
struct OXM_entry_arp_tha_mask
  : OXM_entry_ethernet_mask<OXM_EF_ARP_THA_MASK> { };

/// \relates OXM_entry_arp_tha_mask
std::string to_string(const OXM_entry_arp_tha_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : metadata

/// Match the metadata passed between tables
struct OXM_entry_metadata : OXM_entry_payload_base<OXM_EF_METADATA>
{
  OXM_entry_metadata() = default;
  explicit OXM_entry_metadata(uint64_t v): value(v) {}

  uint64_t value;
};

/// \relates OXM_entry_metadata
bool operator==(const OXM_entry_metadata& a, const OXM_entry_metadata& b);

/// \relates OXM_entry_metadata
bool operator!=(const OXM_entry_metadata& a, const OXM_entry_metadata& b);

/// \relates OXM_entry_metadata
std::size_t bytes(const OXM_entry_metadata&);

/// \relates OXM_entry_metadata
Error_condition is_valid(const OXM_entry_metadata&);

/// \relates OXM_entry_metadata
Error_condition to_buffer(Buffer_view& v, const OXM_entry_metadata& m);

/// \relates OXM_entry_metadata
Error_condition from_buffer(Buffer_view& v, OXM_entry_metadata& m);

/// \relates OXM_entry_metadata
std::string to_string(const OXM_entry_metadata& m, Formatter& f);


// -------------------------------------------------------------------------- //
// OXM entry payload : metadata mask

/// Match the metadata passed between tables with mask
struct OXM_entry_metadata_mask : OXM_entry_payload_base<OXM_EF_METADATA_MASK>
{
  OXM_entry_metadata_mask() = default;
  OXM_entry_metadata_mask(uint64_t v, uint64_t m): value(v), mask(m) {}

  uint64_t value;
  uint64_t mask;
};

/// \relates OXM_entry_metadata_mask
bool operator==(const OXM_entry_metadata_mask& a,
                const OXM_entry_metadata_mask& b);

/// \relates OXM_entry_metadata_mask
bool operator!=(const OXM_entry_metadata_mask& a,
                const OXM_entry_metadata_mask& b);

/// \relates OXM_entry_metadata_mask
std::size_t bytes(const OXM_entry_metadata_mask&);

/// \relates OXM_entry_metadata_mask
Error_condition is_valid(const OXM_entry_metadata_mask&);

/// \relates OXM_entry_metadata_mask
Error_condition to_buffer(Buffer_view& v, const OXM_entry_metadata_mask& m);

/// \relates OXM_entry_metadata_mask
Error_condition from_buffer(Buffer_view& v, OXM_entry_metadata_mask& m);

/// \relates OXM_entry_metadata_mask
std::string to_string(const OXM_entry_metadata& m, Formatter& f);


// -------------------------------------------------------------------------- //
// OXM entry payload: IPv6

/// Base class for OXM entries with an Internet Protocol version 6 (IPv6)
/// address. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ipv6 : OXM_entry_payload_base<K>
  {
    OXM_entry_ipv6() = default;
    explicit OXM_entry_ipv6(Ipv6_addr v): value(v) { }

    Ipv6_addr value;
  };

/// \relates OXM_entry_ipv6
template<OXM_entry_field K>
  bool operator==(const OXM_entry_ipv6<K>& a, const OXM_entry_ipv6<K>& b);

/// \relates OXM_entry_ipv6
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_ipv6<K>& a, const OXM_entry_ipv6<K>& b);

/// \relates OXM_entry_ipv6
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_ipv6<K>&);

/// \relates OXM_entry_ipv6
template<OXM_entry_field K>
  Error_condition is_valid(const OXM_entry_ipv6<K>&);

/// \relates OXM_entry_ipv6
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ipv6<K>& b);

/// \relates OXM_entry_ipv6
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ipv6<K>& b);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 src

/// Match IPv6 source address
struct OXM_entry_ipv6_src : OXM_entry_ipv6<OXM_EF_IPV6_SRC> { };

/// \relates OXM_entry_ipv6_src
std::string to_string(const OXM_entry_ipv6_src&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 dst

/// Match IPv6 destination address
struct OXM_entry_ipv6_dst : OXM_entry_ipv6<OXM_EF_IPV6_DST> { };

/// \relates OXM_entry_ipv6_dst
std::string to_string(const OXM_entry_ipv6_dst&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 ND Target

/// Match target address of IPv6 neighbour discovery
struct OXM_entry_ipv6_nd_target : OXM_entry_ipv6<OXM_EF_IPV6_ND_TARGET> { };

/// \relates OXM_entry_ipv6_nd_target
std::string to_string(const OXM_entry_ipv6_nd_target&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload with mask: IPv6

/// Base class for OXM entries with an Internet Protocol version 6 (IPv6)
/// address with a bit mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ipv6_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_ipv6_mask() = default;
    OXM_entry_ipv6_mask(Ipv6_addr v, Ipv6_addr m): value(v),mask(m) { }

    Ipv6_addr value;
    Ipv6_addr mask;
  };

/// \relates OXM_entry_ipv6_mask
template<OXM_entry_field K>
  bool operator==(const OXM_entry_ipv6_mask<K>& a,
                  const OXM_entry_ipv6_mask<K>& b);

/// \relates OXM_entry_ipv6_mask
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_ipv6_mask<K>& a,
                  const OXM_entry_ipv6_mask<K>& b);

/// \relates OXM_entry_ipv6_mask
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_ipv6_mask<K>&);

/// \relates OXM_entry_ipv6_mask
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ipv6_mask<K>& b);

/// \relates OXM_entry_ipv6_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ipv6_mask<K>& b);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 src mask

/// Match IPv6 source address with mask
struct OXM_entry_ipv6_src_mask
  : OXM_entry_ipv6_mask<OXM_EF_IPV6_SRC_MASK> { };

/// \relates OXM_entry_ipv6_mask
std::string to_string(const OXM_entry_ipv6_src_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 dst mask

/// Match IPv6 destination address with mask
struct OXM_entry_ipv6_dst_mask
  : OXM_entry_ipv6_mask<OXM_EF_IPV6_DST_MASK> { };

/// \relates OXM_entry_ipv6_src_mask
std::string to_string(const OXM_entry_ipv6_dst_mask&, Formatter&);


// -------------------------------------------------------------------------- //
// OXM entry payload

union OXM_entry_payload_data
{
  OXM_entry_payload_data() { }
  ~OXM_entry_payload_data() { }

  OXM_entry_in_port          in_port;
  OXM_entry_in_phy_port      in_phy_port;
  OXM_entry_metadata         metadata;
  OXM_entry_metadata_mask    metadata_mask;
  OXM_entry_eth_dst          eth_dst;
  OXM_entry_eth_dst_mask     eth_dst_mask;
  OXM_entry_eth_src          eth_src;
  OXM_entry_eth_src_mask     eth_src_mask;
  OXM_entry_eth_type         eth_type;
  OXM_entry_vlan_vid         vlan_vid;
  OXM_entry_vlan_vid_mask    vlan_vid_mask;
  OXM_entry_vlan_pcp         vlan_pcp;
  OXM_entry_ip_dscp          ip_dscp;
  OXM_entry_ip_ecn           ip_ecn;
  OXM_entry_ip_proto         ip_proto;
  OXM_entry_ipv4_src         ipv4_src;
  OXM_entry_ipv4_src_mask    ipv4_src_mask;
  OXM_entry_ipv4_dst         ipv4_dst;
  OXM_entry_ipv4_dst_mask    ipv4_dst_mask;
  OXM_entry_tcp_src          tcp_src;
  OXM_entry_tcp_dst          tcp_dst;
  OXM_entry_udp_src          udp_src;
  OXM_entry_udp_dst          udp_dst;
  OXM_entry_sctp_src         sctp_src;
  OXM_entry_sctp_dst         sctp_dst;
  OXM_entry_icmpv4_type      icmpv4_type;
  OXM_entry_icmpv4_code      icmpv4_code;
  OXM_entry_arp_op           arp_op;
  OXM_entry_arp_spa          arp_spa;
  OXM_entry_arp_spa_mask     arp_spa_mask;
  OXM_entry_arp_tpa          arp_tpa;
  OXM_entry_arp_tpa_mask     arp_tpa_mask;
  OXM_entry_arp_sha          arp_sha;
  OXM_entry_arp_sha_mask     arp_sha_mask;
  OXM_entry_arp_tha          arp_tha;
  OXM_entry_arp_tha_mask     arp_tha_mask;
  OXM_entry_ipv6_src         ipv6_src;
  OXM_entry_ipv6_src_mask    ipv6_src_mask;
  OXM_entry_ipv6_dst         ipv6_dst;
  OXM_entry_ipv6_dst_mask    ipv6_dst_mask;
  OXM_entry_ipv6_flabel      ipv6_flabel;
  OXM_entry_ipv6_flabel_mask ipv6_flabel_mask;
  OXM_entry_icmpv6_type      icmpv6_type;
  OXM_entry_icmpv6_code      icmpv6_code;
  OXM_entry_ipv6_nd_target   ipv6_nd_target;
  OXM_entry_ipv6_nd_sll      ipv6_nd_sll;
  OXM_entry_ipv6_nd_tll      ipv6_nd_tll;
  OXM_entry_mpls_label       mpls_label;
  OXM_entry_mpls_tc          mpls_tc;
};

/// The payload of an OXM Entry. It is a variant that can be any type of 
/// OXM entry struct
struct OXM_entry_payload
{
  using Data = OXM_entry_payload_data;

  OXM_entry_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

/// \relates OXM_entry_payload
void construct(OXM_entry_payload&, OXM_entry_field);

/// \relates OXM_entry_payload
void construct(OXM_entry_payload&, const OXM_entry_payload&,
                  OXM_entry_field);

/// \relates OXM_entry_payload
OXM_entry_payload& assign(OXM_entry_payload&, const OXM_entry_payload&,
                          OXM_entry_field);

/// \relates OXM_entry_payload
bool equal(const OXM_entry_payload&, const OXM_entry_payload&,
           OXM_entry_field, OXM_entry_field);

/// \relates OXM_entry_payload
std::size_t bytes(const OXM_entry_payload&, OXM_entry_field);

/// \relates OXM_entry_payload
Error_condition is_valid(const OXM_entry_payload&, OXM_entry_field);

/// \relates OXM_entry_payload
Error_condition to_buffer(Buffer_view&, const OXM_entry_payload&, 
                          OXM_entry_field);

/// \relates OXM_entry_payload
Error_condition from_buffer(Buffer_view&, OXM_entry_payload&, 
                            OXM_entry_field);
 
/// \relates OXM_entry_payload
std::string to_string(const OXM_entry_payload&, Formatter&, OXM_entry_field);


// -------------------------------------------------------------------------- //
// OXM Experimenter

/// OXM Experimenter contains the extra field required when the OXM entry
/// is an experimenter entry
struct OXM_experimenter
{
  OXM_experimenter() = default;
  explicit OXM_experimenter(uint32_t e): experimenter(e) { }

  uint32_t experimenter;
};

/// \relates OXM_experimenter
bool operator==(const OXM_experimenter& a, const OXM_experimenter& b);

/// \relates OXM_experimenter
bool operator!=(const OXM_experimenter& a, const OXM_experimenter& b);

/// \relates OXM_experimenter
std::size_t bytes(const OXM_experimenter&);

/// \relates OXM_experimenter
Error_condition to_buffer(Buffer_view&, const OXM_experimenter&);

/// \relates OXM_experimenter
Error_condition from_buffer(Buffer_view&, OXM_experimenter&);

/// \relates OXM_experimenter
std::string to_string(const OXM_experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry: Header

/// Contain the header fields of an OXM TLV entry
///
/// \remark Implement OXM TLV header
struct OXM_entry_header
{
  OXM_entry_header() = default;
  OXM_entry_header(OXM_entry_class c, OXM_entry_field f, uint8_t l)
   : oxm_class(c), field(f), length(l) { }

  template<typename T>
    OXM_entry_header(const T& value): field(T::kind), length(bytes(value)) { }

  OXM_entry_class oxm_class;
  OXM_entry_field field;
  uint8_t length;
};

/// \relates OXM_entry_header
bool operator==(const OXM_entry_header& a, const OXM_entry_header& b);

/// \relates OXM_entry_header
bool operator!=(const OXM_entry_header& a, const OXM_entry_header& b);

/// \relates OXM_entry_header
std::size_t bytes(const OXM_entry_header& h);

/// \relates OXM_entry_header
Error_condition is_valid(const OXM_entry_header& e);

/// \relates OXM_entry_header
Error_condition to_buffer(Buffer_view&, const OXM_entry_header&);

/// \relates OXM_entry_header
Error_condition from_buffer(Buffer_view&, OXM_entry_header&);

/// \relates OXM_entry_header
std::string to_string(const OXM_entry_header&, Formatter&);
//std::string to_string(const OXM_entry_header::OXM_entry_class);


// -------------------------------------------------------------------------- //
// OXM

/// Implements the OXM TLV. The OXM TLV structure descirbes the fields in a
/// match. 
///
/// \remark Defined in [OpenFlow v1.2, p32-38]
struct OXM_entry
{
  using Header = OXM_entry_header;
  using Payload = OXM_entry_payload;

  OXM_entry() = default;
  
  OXM_entry(OXM_entry&&);
  OXM_entry& operator=(OXM_entry&&);
  
  OXM_entry(const OXM_entry&);
  OXM_entry& operator=(const OXM_entry&);
  
  Header           header;
  Payload          payload;    
  OXM_experimenter experimenter;
};

/// \relates OXM_entry
bool operator==(const OXM_entry& a, const OXM_entry& b);

/// \relates OXM_entry
bool operator!=(const OXM_entry& a, const OXM_entry& b);

/// \relates OXM_entry
std::size_t bytes(const OXM_entry& a);

/// \relates OXM_entry
Error_condition is_valid(const OXM_entry& e);

/// \relates OXM_entry
uint64_t OXM_entry_field_flag(const OXM_entry_field& f);

/// \relates OXM_entry
Error_condition is_valid(const Sequence<OXM_entry> r); 

/// \relates OXM_entry
Error_condition to_buffer(Buffer_view&, const OXM_entry&);

/// \relates OXM_entry
Error_condition from_buffer(Buffer_view&, OXM_entry&);

/// \relates OXM_entry
std::string to_string(const OXM_entry&, Formatter&);


// -------------------------------------------------------------------------- //
// Match


//// Represents a matching entry in a flow table. The Match class is used by
/// several messages in the protocol to refer to a single entry in in a flow 
/// table. The class specifies which fields of a packet will be matched by
/// the switch.
///
/// \remark Defined in [OpenFlow v1.0, p20-21]
struct Match
{
  enum Type_value : uint16_t
  {
    MT_STANDARD = 0x0000, //this is deprecated as of v1.2
    MT_OXM = 0x0001
  };

  Match() = default;
  Match(Type_value t, uint16_t l): type(t), length(l) { }

  // - Packet data
  Type_value type;
  uint16_t length;
  Sequence<OXM_entry> rules;
};

/// \relates Match
bool operator==(const Match& a, const Match& b);

/// \relates Match
bool operator!=(const Match& a, const Match& b);

/// \relates Match
std::size_t bytes(const Match& m);

/// \relates Match
Error_condition is_valid(const Match::Type_value t);

/// \relates Match
Error_condition is_valid(const Match& m);

/// \relates Match
Error_condition to_buffer(Buffer_view&, const Match& m);

/// \relates Match
Error_condition from_buffer(Buffer_view&, Match& m);

/// \relates Match
std::string to_string(const Match&, Formatter&);

// -------------------------------------------------------------------------- //
// Action type

enum Action_type : uint16_t
{
  ACTION_OUTPUT       = 0x0000,
  ACTION_COPY_TTL_OUT = 0x000b,
  ACTION_COPY_TTL_IN  = 0x000c,
  ACTION_SET_MPLS_TTL = 0x000f,
  ACTION_DEC_MPLS_TTL = 0x0010,
  ACTION_PUSH_VLAN    = 0x0011,
  ACTION_POP_VLAN     = 0x0012,
  ACTION_PUSH_MPLS    = 0x0013,
  ACTION_POP_MPLS     = 0x0014,
  ACTION_SET_QUEUE    = 0x0015,
  ACTION_GROUP        = 0x0016,
  ACTION_SET_NW_TTL   = 0x0017,
  ACTION_DEC_NW_TTL   = 0x0018,
  ACTION_SET_FIELD    = 0x0019,
  ACTION_EXPERIMENTER = 0xffff
};

/// \relates Action_type
Error_condition is_valid(const Action_type t);

/// \relates Action_type
std::string to_string(Action_type);

/// A base class for all action payload kinds.
template<Action_type K>
  using Action_payload_base = Basic_payload_base<Action_type, K>;

// -------------------------------------------------------------------------- //
// Action: Output

/// Requests packet output. The action requires the switch to ends a 
/// maximum number of bytes to a specified port.
///
/// \remark Corresponds to the ofp_action_output in OpenFlow specification.
struct Action_output : Action_payload_base<ACTION_OUTPUT>
{
  Action_output() = default;
  Action_output(uint32_t p, uint16_t m): port(p), max_len(m) { }

  uint32_t port;
  uint16_t max_len;
};

/// \relates to Action_output
bool operator==(const Action_output& a, const Action_output& b);

/// \relates to Action_output
bool operator!=(const Action_output& a, const Action_output& b);

/// \relates to Action_output
std::size_t bytes(const Action_output&);

/// \relates to Action_output
Error_condition is_valid(const Action_output&);

/// \relates to Action_output
Error_condition to_buffer(Buffer_view&, const Action_output&);

/// \relates to Action_output
Error_condition from_buffer(Buffer_view&, Action_output&);

/// \relates to Action_output
std::string to_string(const Action_output&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Copy ttl out

/// Copy TTL "outwards" -- Copy TTL "outwards" -- from next-to-outermost to 
/// outermost
///
/// \remark Implements OFPAT_COPY_TTL_OUT action
struct Action_copy_ttl_out : Action_payload_base<ACTION_COPY_TTL_OUT> { };

/// \relates Action_copy_ttl_out
std::size_t bytes(const Action_copy_ttl_out&);

/// \relates Action_copy_ttl_out
Error_condition to_buffer(Buffer_view&, const Action_copy_ttl_out&);

/// \relates Action_copy_ttl_out
Error_condition from_buffer(Buffer_view&, Action_copy_ttl_out&);

// -------------------------------------------------------------------------- //
// Action: Copy ttl in

/// Copy TTL "inwards" -- from outermost to next-to-outermost
///
/// \remark Implements OFPAT_COPY_TTL_IN action
struct Action_copy_ttl_in : Action_payload_base<ACTION_COPY_TTL_IN> { };

/// \relates Action_copy_ttl_in
std::size_t bytes(const Action_copy_ttl_in&);

/// \relates Action_copy_ttl_in
Error_condition to_buffer(Buffer_view&, const Action_copy_ttl_in&);

/// \relates Action_copy_ttl_in
Error_condition from_buffer(Buffer_view&, Action_copy_ttl_in&);

// -------------------------------------------------------------------------- //
// Action: MPLS TTL

/// Base class for MPLS Time-To-Live field related actions
///
/// \remark Implements ofp_action_mpls_ttl in OpenFlow protocol
template <Action_type K>
  struct Action_mpls_ttl : Action_payload_base<ACTION_SET_MPLS_TTL>
  {
    Action_mpls_ttl() = default;
    explicit Action_mpls_ttl(uint8_t mt)
      : mpls_ttl(mt)
    { }

    uint8_t mpls_ttl;
  };

/// \relates Action_mpls_ttl
template <Action_type K>
  bool operator==(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b);

/// \relates Action_mpls_ttl
template <Action_type K>
  bool operator!=(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b);

/// \relates Action_mpls_ttl
template <Action_type K>
  std::size_t bytes(const Action_mpls_ttl<K>&);

/// \relates Action_mpls_ttl
template<Action_type K>
  Error_condition is_valid(const Action_mpls_ttl<K>&);

/// \relates Action_mpls_ttl
template <Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_mpls_ttl<K>& mt);

/// \relates Action_mpls_ttl
template <Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_mpls_ttl<K>& mt);

// -------------------------------------------------------------------------- //
// Action: Set Mpls ttl

/// Set MPLS Time-To-Live field
/// 
/// \remark Implements OFP_SET_MPLS_TTL action 
struct Action_set_mpls_ttl : Action_mpls_ttl<ACTION_SET_MPLS_TTL>
{
  using Action_mpls_ttl<ACTION_SET_MPLS_TTL>::Action_mpls_ttl;
};

/// \relates Action_set_mpls_ttl
std::string to_string(const Action_set_mpls_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Dec Mpls ttl

/// Decrease MPLS Time-To-Live field by 1 
/// 
/// \remark Implements OFP_DEC_MPLS_TTL action
struct Action_dec_mpls_ttl : Action_mpls_ttl<ACTION_DEC_MPLS_TTL>
{
  using Action_mpls_ttl<ACTION_DEC_MPLS_TTL>::Action_mpls_ttl;
};

/// \relates Action_dec_mpls_ttl
std::string to_string(const Action_dec_mpls_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push Pop

/// Base class for push and pop actions
///
/// \remark Implements ofp_action_push and ofp_action_pop_mpls in OpenFlow
/// protocol
template <Action_type K>
  struct Action_push_pop : Action_payload_base<K>
  {
    Action_push_pop() = default;
    explicit Action_push_pop(uint16_t et)
      : ether_type(et)
    { }

    uint16_t ether_type;
  };

/// \relates Action_push_pop
template <Action_type K>
  bool operator==(const Action_push_pop<K>& a, const Action_push_pop<K>& b);

/// \relates Action_push_pop
template <Action_type K>
  bool operator!=(const Action_push_pop<K>& a, const Action_push_pop<K>& b);

/// \relates Action_push_pop
template <Action_type K>
  std::size_t bytes(const Action_push_pop<K>&);

/// \relates Action_push_pop
template<Action_type K>
  Error_condition is_valid(const Action_push_pop<K>&);

/// \relates Action_push_pop
template <Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_push_pop<K>& pp);

/// \relates Action_push_pop
template <Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_push_pop<K>& pp);

// -------------------------------------------------------------------------- //
// Action: Push Vlan

/// Push a new VLAN tag
///
/// \remark Implements OFPAT_PUSH_VLAN action
struct Action_push_vlan : Action_push_pop<ACTION_PUSH_VLAN>
{
  using Action_push_pop<ACTION_PUSH_VLAN>::Action_push_pop;
};

/// \relates Action_push_vlan
std::string to_string(const Action_push_vlan&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Pop Vlan

/// Pop the outer VLAN tag
///
/// \remark Implements OFPAT_POP_VLAN action
struct Action_pop_vlan : Action_push_pop<ACTION_POP_VLAN>
{
  using Action_push_pop<ACTION_POP_VLAN>::Action_push_pop;
};

/// \relates Action_pop_vlan
std::string to_string(const Action_pop_vlan&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push Mpls

/// Push a new MPLS tag
///
/// Describe OFPAT_PUSH_MPLS action
struct Action_push_mpls : Action_push_pop<ACTION_PUSH_MPLS>
{
  using Action_push_pop<ACTION_PUSH_MPLS>::Action_push_pop;
};

/// \relates Action_push_mpls
std::string to_string(const Action_push_mpls&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Pop Mpls

/// Pop the outer MPLS tag
///
/// \remark Implements OFPAT_POP_MPLS action
struct Action_pop_mpls : Action_push_pop<ACTION_POP_MPLS>
{
  using Action_push_pop<ACTION_POP_MPLS>::Action_push_pop;
};

/// \relates Action_pop_mpls
std::string to_string(const Action_pop_mpls&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: SetQueue

/// Set the queue id when outputting to a port
///
/// \remark Implements ofp_action_set_queue (OFPAT_SET_QUEUE action) in OpenFlow 
/// protocol
struct Action_set_queue : Action_payload_base<ACTION_SET_QUEUE>
{
  Action_set_queue() = default;
  explicit Action_set_queue(uint32_t qid): queue_id(qid) { }

  uint32_t queue_id;
};

/// \relates Action_set_queue
bool operator==(const Action_set_queue& a, const Action_set_queue& b);

/// \relates Action_set_queue
bool operator!=(const Action_set_queue& a, const Action_set_queue& b);

/// \relates Action_set_queue
std::size_t bytes(const Action_set_queue&);

/// \relates Action_set_queue
Error_condition is_valid(const Action_set_queue&);

/// \relates Action_set_queue
Error_condition to_buffer(Buffer_view&, const Action_set_queue&);

/// \relates Action_set_queue
Error_condition from_buffer(Buffer_view&, Action_set_queue&);

/// \relates Action_set_queue
std::string to_string(const Action_set_queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Group

/// Apply a group to packet
///
/// \remark Implements ofp_action_group (OFPAT_GROUP action) in OpenFlow 
/// protocol
struct Action_group : Action_payload_base<ACTION_GROUP>
{
  Action_group() = default;
  explicit Action_group(uint32_t gid): group_id(gid) { }

  uint32_t group_id;
};

/// \relates Action_group
bool operator==(const Action_group& a, const Action_group& b);

/// \relates Action_group
bool operator!=(const Action_group& a, const Action_group& b);

/// \relates Action_group
std::size_t bytes(const Action_group&);

/// \relates Action_group
Error_condition is_valid(const Action_group&);

/// \relates Action_group
Error_condition to_buffer(Buffer_view&, const Action_group&);

/// \relates Action_group
Error_condition from_buffer(Buffer_view&, Action_group&);

/// \relates Action_group
std::string to_string(const Action_group&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: NW TTL

/// Base class for network TTL actions
///
/// \remark Implements ofp_action_nw_ttl in OpenFlow protocol
template <Action_type K>
  struct Action_nw_ttl : Action_payload_base<ACTION_SET_NW_TTL>
  {
    Action_nw_ttl() = default;
    explicit Action_nw_ttl(uint8_t nt)
      : nw_ttl(nt)
    { }

    uint8_t nw_ttl;
  };

/// \relates Action_nw_ttl
template <Action_type K>
  bool operator==(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b);

/// \relates Action_nw_ttl
template <Action_type K>
  bool operator!=(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b);

/// \relates Action_nw_ttl
template <Action_type K>
  std::size_t bytes(const Action_nw_ttl<K>& nt);

/// \relates Action_nw_ttl
template<Action_type K>
  Error_condition is_valid(const Action_nw_ttl<K>&);

/// \relates Action_nw_ttl
template <Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_nw_ttl<K>& nt);

/// \relates Action_nw_ttl
template <Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_nw_ttl<K>& nt);

// -------------------------------------------------------------------------- //
// Action: Set Nw ttl

/// Set network layer Time-To-Live field
struct Action_set_nw_ttl : Action_nw_ttl<ACTION_SET_NW_TTL>
{
  using Action_nw_ttl<ACTION_SET_NW_TTL>::Action_nw_ttl;
};

/// \relates Action_set_nw_ttl
std::string to_string(const Action_set_nw_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Dec Nw ttl

/// Decrease network layer Time-To-Live by 1
struct Action_dec_nw_ttl : Action_nw_ttl<ACTION_DEC_NW_TTL>
{
  using Action_nw_ttl<ACTION_DEC_NW_TTL>::Action_nw_ttl;
};

/// \relates Action_dec_nw_ttl
std::string to_string(const Action_dec_nw_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Set Field

/// Set a header field using OXM TLV format
struct Action_set_field : Action_payload_base<ACTION_SET_FIELD>
{
  Action_set_field() = default;
  explicit Action_set_field(OXM_entry oe): oxm(oe) { }

  OXM_entry oxm;
};

/// \relates Action_set_field
bool operator==(const Action_set_field& a, const Action_set_field& b);

/// \relates Action_set_field
bool operator!=(const Action_set_field& a, const Action_set_field& b);

/// \relates Action_set_field
std::size_t bytes(const Action_set_field& asf);

/// \relates Action_set_field
Error_condition is_valid(const Action_set_field& asf);

/// \relates Action_set_field
Error_condition to_buffer(Buffer_view&, const Action_set_field&);

/// \relates Action_set_field
Error_condition from_buffer(Buffer_view&, Action_set_field&);

/// \relates Action_set_field
std::string to_string(const Action_set_field&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Experimenter

/// Experimenter action
struct Action_experimenter : Action_payload_base<ACTION_EXPERIMENTER>
{
  Action_experimenter() = default;
  explicit Action_experimenter(uint32_t e)
    : experimenter(e)
  {}

  uint32_t experimenter;
};

/// \relates Action_experimenter
bool operator==(const Action_experimenter& a, const Action_experimenter& b);

/// \relates Action_experimenter
bool operator!=(const Action_experimenter& a, const Action_experimenter& b);

/// \relates Action_experimenter
std::size_t bytes(const Action_experimenter&);

/// \relates Action_experimenter
Error_condition is_valid(const Action_experimenter&);

/// \relates Action_experimenter
Error_condition to_buffer(Buffer_view&, const Action_experimenter&);

/// \relates Action_experimenter
Error_condition from_buffer(Buffer_view&, Action_experimenter&);

/// \relates Action_experimenter
std::string to_string(const Action_experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// Action Payload

/// \relates Action_payload
union Action_payload_data
{
  Action_payload_data() { }
  ~Action_payload_data() { }

  Action_output        output;
  Action_copy_ttl_out  copy_ttl_out;
  Action_copy_ttl_in   copy_ttl_in;
  Action_set_mpls_ttl  set_mpls_ttl;
  Action_dec_mpls_ttl  dec_mpls_ttl;
  Action_push_vlan     push_vlan;
  Action_pop_vlan      pop_vlan;
  Action_push_mpls     push_mpls;
  Action_pop_mpls      pop_mpls;
  Action_set_queue     set_queue;
  Action_group         group;
  Action_set_nw_ttl    set_nw_ttl;
  Action_dec_nw_ttl    dec_nw_ttl;
  Action_set_field     set_field;
  Action_experimenter  experimenter;
};

/// The payload of an action. 
/// An action consists of header and payload. The payload is a variant that
/// can be any type of action structre. 
struct Action_payload
{
  using Data = Action_payload_data;

  Action_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

/// \relates Action_payload
void construct(Action_payload&, Action_type);
/// \relates Action_payload
void construct(Action_payload&, const Action_payload&, Action_type);

/// \relates Action_payload
template<typename Tag, typename... Args>
  void construct(Action_payload& p, Tag t, Args&&... args) = delete;

/// \relates Action_payload
Action_payload& assign(Action_payload&, const Action_payload&, Action_type);

/// \relates Action_payload
bool equal(const Action_payload&, const Action_payload&, Action_type, 
               Action_type);

/// \relates Action_payload
std::size_t bytes(const Action_payload&, Action_type);
/// \relates Action_payload
Error_condition is_valid(const Action_payload&, Action_type);

/// \relates Action_payload
Error_condition to_buffer(Buffer_view&, const Action_payload&, Action_type);
/// \relates Action_payload
Error_condition from_buffer(Buffer_view&, Action_payload&, Action_type);

/// \relates Action_payload
std::string to_string(const Action_payload&, Formatter&, Action_type);

// -------------------------------------------------------------------------- //
// Action header

/// Contains the header fields of an action. 
///
/// \remark Implement ofp_action_header in OpenFlow protocol
struct Action_header
{
  Action_header() = default;
  Action_header(Action_type t, uint16_t l): type(t), length(l){ }

  template<typename T>
    Action_header(const T& value)
      : type(T::kind), length(4 + bytes(value)) { }

  Action_type type;
  uint16_t length;
};

/// \relates Action_header
bool operator==(const Action_header& a, const Action_header& b);

/// \relates Action_header
bool operator!=(const Action_header& a, const Action_header& b);

/// \relates Action_header
std::size_t bytes(const Action_header&);

/// \relates Action_header
Error_condition is_valid(const Action_header& h);

/// \relates Action_header
Error_condition to_buffer(Buffer_view&, const Action_header&);

/// \relates Action_header
Error_condition from_buffer(Buffer_view&, Action_header&);

/// \relates Action_header
std::string to_string(const Action_header&, Formatter&);


// -------------------------------------------------------------------------- //
// Action
/// Describe an action.
///
/// An Action consists of one header and one payload. The type of
/// payload is determined by value of header. 
/// 
/// One or more messages in OpenFlow protocols contain a list of 
/// actions as parameter. The list of actions is described in this driver
/// as Sequence of Action (Sequence<Action>).
/// 
/// \remark Defined in [OpenFlow v1.2, p39-43]
struct Action
{
  using Header = Action_header;
  using Payload = Action_payload;

  Action() = default;

  Action(const Action&);
  Action& operator=(const Action&);

  template<typename T, typename Tag = typename T::Tag>
    Action(T&& x);

  template<typename Tag, typename... Args>
    Action(Tag t, Args&&... args);
  
  Header  header;
  Payload payload;
};

/// \relates Action
bool operator==(const Action& a, const Action& b);

/// \relates Action
bool operator!=(const Action& a, const Action& b);

/// \relates Action
std::size_t bytes(const Action& a);

/// \relates Action
Error_condition is_valid(const Action& a);

/// \relates Action
Error_condition to_buffer(Buffer_view& v, const Action& a);

/// \relates Action
Error_condition from_buffer(Buffer_view& v, const Action& a);

// To string
std::string to_string(const Action& a, Formatter& f);

// -------------------------------------------------------------------------- //
// Instruction type

/// \relates Instruction
enum Instruction_type : uint16_t
{
  INSTRUCTION_GOTO_TABLE     = 0x0001,
  INSTRUCTION_WRITE_METADATA = 0x0002,
  INSTRUCTION_WRITE_ACTIONS  = 0x0003,
  INSTRUCTION_APPLY_ACTIONS  = 0x0004,
  INSTRUCTION_CLEAR_ACTIONS  = 0x0005,
  INSTRUCTION_EXPERIMENTER   = 0xffff
};

/// \relates Instruction_goto_table
Error_condition is_valid(const Instruction_type it);

/// \relates Instruction_goto_table
std::string to_string(Instruction_type);

/// A base class for all instruction payload kinds
template<Instruction_type K>
  using Instruction_payload_base = Basic_payload_base<Instruction_type, K>;

// -------------------------------------------------------------------------- //
// Instruction: Goto table

/// Setup the next table in the lookup pipeline
///
/// \remark Implements ofp_instruction_goto_table (OFPIT_GOTO_TABLE instruction) 
/// in OpenFlow protocol
struct Instruction_goto_table
  : Instruction_payload_base<INSTRUCTION_GOTO_TABLE>
{
  Instruction_goto_table() = default;
  explicit Instruction_goto_table(uint8_t tid);

  uint8_t table_id;
};

/// \relates Instruction_goto_table
bool operator==(const Instruction_goto_table& a, const Instruction_goto_table& b);

/// \relates Instruction_goto_table
bool operator!=(const Instruction_goto_table& a, const Instruction_goto_table& b);

/// \relates Instruction_goto_table
std::size_t bytes(const Instruction_goto_table&);

/// \relates Instruction_goto_table
Error_condition is_valid(const Instruction_goto_table&);

/// \relates Instruction_goto_table
Error_condition to_buffer(Buffer_view&, const Instruction_goto_table&);
/// \relates Instruction_goto_table
Error_condition from_buffer(Buffer_view&, Instruction_goto_table&);

/// \relates Instruction_goto_table
std::string to_string(const Instruction_goto_table&, Formatter&);


// -------------------------------------------------------------------------- //
// Instruction: Goto write metadata

/// Setup the metadata field for use later in pipeline
/// 
/// \remark implements ofp_instruction_write_metadata (OFPIT_WRITE_METADATA 
/// instruction) in OpenFlow protocol
struct Instruction_write_metadata
  : Instruction_payload_base<INSTRUCTION_WRITE_METADATA>
{
  Instruction_write_metadata() = default;
  Instruction_write_metadata(uint64_t m, uint64_t mm);

  uint64_t metadata;
  uint64_t metadata_mask;
};

/// \relates Instruction_write_metadata
bool operator==(const Instruction_write_metadata& a,
                const Instruction_write_metadata& b);

/// \relates Instruction_write_metadata
bool operator!=(const Instruction_write_metadata& a,
                const Instruction_write_metadata& b);

/// \relates Instruction_write_metadata
std::size_t bytes(const Instruction_write_metadata&);

/// \relates Instruction_write_metadata
Error_condition is_valid(const Instruction_write_metadata&);

/// \relates Instruction_write_metadata
Error_condition to_buffer(Buffer_view&, const Instruction_write_metadata&);
/// \relates Instruction_write_metadata
Error_condition from_buffer(Buffer_view&, Instruction_write_metadata&);

/// \relates Instruction_write_metadata
std::string to_string(const Instruction_write_metadata&, Formatter&);


// -------------------------------------------------------------------------- //
// Instruction: Action

/// Base class for all action instructions
///
/// \remark Implements ofp_instruction_actions in OpenFlow protocol
template <Instruction_type K>
  struct Instruction_action : Instruction_payload_base<K>
  {
    Instruction_action() = default;

    explicit Instruction_action(const Sequence<Action>& a)
      : actions(a)
    { }

    Sequence<Action> actions;
  };

/// \relates Instruction_action
template <Instruction_type K>
  bool operator==(const Instruction_action<K>& a, const Instruction_action<K>& b);

/// \relates Instruction_action
template <Instruction_type K>
  bool operator!=(const Instruction_action<K>& a, const Instruction_action<K>& b);

/// \relates Instruction_action
template <Instruction_type K>
  std::size_t bytes(const Instruction_action<K>& ia);

/// \relates Instruction_action
template<Instruction_type K>
  Error_condition is_valid(const Instruction_action<K>&);

/// \relates Instruction_action
template <Instruction_type K>
  Error_condition to_buffer(Buffer_view& v, const Instruction_action<K>& ia);

/// \relates Instruction_action
template <Instruction_type K>
  Error_condition from_buffer(Buffer_view& v, Instruction_action<K>& ia);

// -------------------------------------------------------------------------- //
// Instruction : Write actions

/// Write the action(s) onto the datapath action
///
/// \remark Implements OFPIT_WRITE_ACTIONS instruction
struct Instruction_write_actions
  : Instruction_action<INSTRUCTION_WRITE_ACTIONS>
{
  using Instruction_action<INSTRUCTION_WRITE_ACTIONS>::Instruction_action;
};

/// \relates Instruction_write_actions
std::string to_string(const Instruction_write_actions&, Formatter&);


// -------------------------------------------------------------------------- //
// Instruction : Apply actions

/// Applies the action(s) immediately
///
/// \remark Implements OFPIT_APPLY_ACTIONS instruction
struct Instruction_apply_actions
  : Instruction_action<INSTRUCTION_APPLY_ACTIONS>
{
  using Instruction_action<INSTRUCTION_APPLY_ACTIONS>::Instruction_action;
};

/// \relates Instruction_apply_actions
std::string to_string(const Instruction_apply_actions&, Formatter&);


// -------------------------------------------------------------------------- //
// Instruction : Clear actions

/// Clears all actions from the datapath action set
///
/// \remark Implements OFPIT_CLEAR_ACTIONS instruction
struct Instruction_clear_actions
  : Instruction_action<INSTRUCTION_CLEAR_ACTIONS>
{
  using Instruction_action<INSTRUCTION_CLEAR_ACTIONS>::Instruction_action;
};

/// \relates Instruction_clear_actions
std::string to_string(const Instruction_clear_actions&, Formatter&);


// -------------------------------------------------------------------------- //
// Instruction: Experimenter

/// Describe an experimenter insruction
struct Instruction_experimenter
  : Instruction_payload_base<INSTRUCTION_EXPERIMENTER>
{
  Instruction_experimenter() = default;
  explicit Instruction_experimenter(uint32_t e)
    : experimenter_id(e)
  {}

  uint32_t experimenter_id;
};

/// \relates Instruction_experimenter
bool operator==(const Instruction_experimenter& a,
                const Instruction_experimenter& b);

/// \relates Instruction_experimenter
bool operator!=(const Instruction_experimenter& a,
                const Instruction_experimenter& b);

/// \relates Instruction_experimenter
std::size_t bytes(const Instruction_experimenter&);

/// \relates Instruction_experimenter
Error_condition is_valid(const Instruction_experimenter&);

/// \relates Instruction_experimenter
Error_condition to_buffer(Buffer_view&, const Instruction_experimenter&);
/// \relates Instruction_experimenter
Error_condition from_buffer(Buffer_view&, Instruction_experimenter&);

/// \relates Instruction_experimenter
std::string to_string(const Instruction_experimenter&, Formatter&);


// -------------------------------------------------------------------------- //
// Instruction Payload

/// \relates Instruction
union Instruction_payload_data
{
  Instruction_payload_data() { }
  ~Instruction_payload_data() { }

  Instruction_goto_table      goto_table;
  Instruction_write_metadata  write_metadata;
  Instruction_write_actions   write_actions;
  Instruction_apply_actions   apply_actions;
  Instruction_clear_actions   clear_actions;
  Instruction_experimenter    experimenter;
};

/// The payload of an instruction. 
/// An instruction consists of header and payload. The payload is a variant that
/// can be any type of instruction structre. 
struct Instruction_payload
{
  using Data = Instruction_payload_data;

  Instruction_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

/// Instruction_payload
void construct(Instruction_payload&, Instruction_type);
/// Instruction_payload
void construct(Instruction_payload&, Instruction_payload&&, 
               Instruction_type);
/// Instruction_payload
void construct(Instruction_payload&, const Instruction_payload&, 
               Instruction_type);

/// Instruction_payload
template<typename Tag, typename... Args>
  void construct(Instruction_payload& p, Tag t, Args&&... args) = delete;

/// Instruction_payload
Instruction_payload& assign(Instruction_payload&, Instruction_payload&&, 
                            Instruction_type);
/// Instruction_payload
Instruction_payload& assign(Instruction_payload&, const Instruction_payload&, 
                            Instruction_type);

/// Instruction_payload
void destroy(Instruction_payload&, Instruction_type);

/// Instruction_payload
bool equal(const Instruction_payload&, const Instruction_payload&,
           Instruction_type, Instruction_type);

/// Instruction_payload
std::size_t bytes(const Instruction_payload&, Instruction_type);

/// Instruction_payload
Error_condition is_valid(const Instruction_payload&, Instruction_type);

/// Instruction_payload
Error_condition to_buffer(Buffer_view&, const Instruction_payload&, Instruction_type);
/// Instruction_payload
Error_condition from_buffer(Buffer_view&, Instruction_payload&, Instruction_type);

/// Instruction_payload
std::string to_string(const Instruction_payload&, Formatter&, 
                      Instruction_type);

// -------------------------------------------------------------------------- //
// Instruction header

/// The header of an instruction. 
///
/// \remark Implements ofp_instruction in OpenFlow protocol.
struct Instruction_header
{
  Instruction_header() = default;
  Instruction_header(Instruction_type t, uint16_t l)
  : type(t), length(l)
  { }

  template<typename T>
   explicit Instruction_header(const T& value)
    : Instruction_header(T::kind, 4 + bytes(value))
  { }


  Instruction_type type;
  uint16_t length;
};

/// \relates Instruction_header
bool operator==(const Instruction_header& a, const Instruction_header& b);
/// \relates Instruction_header
bool operator!=(const Instruction_header& a, const Instruction_header& b);

/// \relates Instruction_header
std::size_t bytes(const Instruction_header&);

/// \relates Instruction_header
Error_condition is_valid(const Instruction_header& h);

/// \relates Instruction_header
Error_condition to_buffer(Buffer_view&, const Instruction_header&);
/// \relates Instruction_header
Error_condition from_buffer(Buffer_view&, Instruction_header&);

/// \relates Instruction_header
std::string to_string(const Instruction_header&, Formatter&);



// -------------------------------------------------------------------------- //
// Instruction

/// Describe an instruction
///
/// An Instruction consists of one header and one payload. The type of
/// payload is determined by value of header. 
/// 
/// One or more messages in OpenFlow protocols contain a list of 
/// instructions as parameter. The list of instructions is described in 
/// this driver as Sequence of Instruction (Sequence<Instruction>).
///
/// \remark Defined in [OpenFlow v1.2, p38-39]
struct Instruction
{
  using Header = Instruction_header;
  using Payload = Instruction_payload;

  Instruction() = default;
  ~Instruction();

  Instruction(Instruction&&);
  Instruction& operator=(Instruction&&);

  Instruction(const Instruction&);
  Instruction& operator=(const Instruction&);
  
  template<typename T, typename Tag = typename T::Tag>
    Instruction(T&& x);

  template<typename Tag, typename... Args>
    Instruction(Tag t, Args&&... args);

  Header  header;
  Payload payload;
};

/// \relates Instruction
bool operator==(const Instruction& a, const Instruction& b);
bool operator!=(const Instruction& a, const Instruction& b);

/// \relates Instruction
std::size_t bytes(const Instruction& a);

/// \relates Instruction
Error_condition is_valid(const Instruction& a);
/// \relates Instruction
Error_condition is_valid(const Sequence<Instruction> i);

/// \relates Instruction
Error_condition to_buffer(Buffer_view& v, const Instruction& a);
/// \relates Instruction
Error_condition from_buffer(Buffer_view& v, const Instruction& a);

/// \relates Instruction
std::string to_string(const Instruction& a, Formatter&);

// -------------------------------------------------------------------------- //
// Port

/// The Port structure describes the property and configuration of a physical 
/// port.
///
/// \remark Defined in [OpenFlow v1.2, p28-31]
struct Port
{
  static constexpr std::size_t NAME_STR_LEN = 16;

  using Name_string = Stringbuf<NAME_STR_LEN>;

  // - config values
  enum Config_value : uint32_t {
    PORT_DOWN = 0x00000001, NO_RECV = 0x00000004, NO_FWD = 0x00000020,
    NO_PACKET_IN = 0x00000040
  };

  // - state value
  enum State_value : uint32_t {
    LINK_DOWN = 0x00000001, BLOCKED = 0x00000002, LIVE = 0x00000004
  };

  // - id valuea
  enum Id_value : uint32_t {
    MAX = 0xffffff00, IN_PORT = 0xfffffff8, TABLE = 0xfffffff9,
    NORMAL = 0xfffffffa, FLOOD = 0xfffffffb, ALL = 0xfffffffc,
    CONTROLLER = 0xfffffffd, LOCAL = 0xfffffffe, ANY = 0xffffffff
  };

  // - features value
  enum Features_value : uint32_t {
    TEN_MB_HD = 0x0000001, TEN_MB_FD = 0x00000002,
    HUNDRED_MB_HD = 0x00000004, HUNDRED_MB_FD = 0x00000008,
    ONE_GB_HD = 0x00000010, ONE_GB_FD = 0x00000020,
    TEN_GB_FD = 0x00000040, FOURTY_GB_FD = 0x00000080,
    HUNDRED_GB_FD = 0x00000100, ONE_TB_FD = 0x00000200,
    OTHER = 0x00000400, COPPER = 0x00000800, FIBER = 0x00001000,
    AUTO_NEG = 0x00002000, PAUSE = 0x00004000, PAUSE_ASYM = 0x00008000
  };

  // - Ctors
  Port() = default;
  Port(Id_value pid, Ethernet_addr ha, const char* n, Config_value c,
       State_value s, Features_value cu, Features_value a,
       Features_value su, Features_value p, uint32_t cs,
       uint32_t ms)
   : port_id(pid), hw_addr(ha), name(n), config(c), state(s), curr(cu),
    advertised(a), supported(su), peer(p), curr_speed(cs), max_speed(ms){ }

  Id_value port_id;
  Ethernet_addr hw_addr;
  Name_string name;
  Config_value config;
  State_value state;
  Features_value curr;
  Features_value advertised;
  Features_value supported;
  Features_value peer;
  uint32_t curr_speed;
  uint32_t max_speed;
};

/// \relates Port
bool operator==(const Port& a, const Port& b);
/// \relates Port
bool operator!=(const Port& a, const Port& b);

/// \relates Port
std::size_t bytes(const Port&);

/// \relates Port
Error_condition is_valid(const Port::Id_value id);
/// \relates Port
Error_condition is_valid(const Port::Config_value);
/// \relates Port
Error_condition is_valid(const Port::State_value);
/// \relates Port
Error_condition is_valid(const Port::Features_value);
/// \relates Port
Error_condition is_valid(const Port& p);

/// \relates Port
std::string to_string(const Port&, Formatter&);
/// \relates Port
std::string to_string(Port::Id_value);
/// \relates Port
std::string to_string(Port::Config_value);
/// \relates Port
std::string to_string(Port::State_value);
/// \relates Port
std::string to_string(Port::Features_value);

/// \relates Port
Error_condition to_buffer(Buffer_view&, const Port&);
/// \relates Port
Error_condition from_buffer(Buffer_view&, Port&);

/// \relates Port
constexpr bool
port_config_port_down(uint32_t c);

/// \relates Port
constexpr bool
port_config_no_recv(uint32_t c);

/// \relates Port
constexpr bool
port_config_no_fwd(uint32_t c);

/// \relates Port
constexpr bool 
port_config_no_packet_in(uint32_t c);

/// \relates Port
constexpr bool
port_state_blocked(uint32_t s);

/// \relates Port
constexpr bool
port_state_live(uint32_t s);

/// \relates Port
constexpr bool
port_max(uint16_t p);

/// \relates Port
constexpr bool
port_in_port(uint16_t p);

/// \relates Port
constexpr bool
port_table(uint16_t p);

/// \relates Port
constexpr bool
port_normal(uint16_t p);

/// \relates Port
constexpr bool
port_flood(uint16_t p);

/// \relates Port
constexpr bool
port_all(uint16_t p);

/// \relates Port
constexpr bool
port_controller(uint16_t p);

/// \relates Port
constexpr bool
port_local(uint16_t p);

/// \relates Port
constexpr bool
port_any(uint16_t p);

/// \relates Port
constexpr bool
port_feature_10mb_hd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_10mb_fd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_100mb_hd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_100mb_fd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_1gb_hd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_1gb_fd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_10gb_fd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_40gb_fd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_100gb_fd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_1tb_fd(uint32_t p);

/// \relates Port
constexpr bool
port_feature_other(uint32_t p);

/// \relates Port
constexpr bool
port_feature_copper(uint32_t p);

/// \relates Port
constexpr bool
port_feature_fiber(uint32_t p);

/// \relates Port
constexpr bool
port_feature_auto_neg(uint32_t p);

/// \relates Port
constexpr bool
port_feature_pause(uint32_t p);

// -------------------------------------------------------------------------- //
// Queue property type

enum Queue_property_type : uint16_t
{
  QUEUE_PROPERTY_MIN_RATE = 1,
  QUEUE_PROPERTY_MAX_RATE = 2,
  QUEUE_PROPERTY_EXPERIMENTER = 0xffff,
};

Error_condition is_valid(const Queue_property_type t);

// To string
std::string to_string(Queue_property_type);

/// A base class for all queue property payload kinds
template<Queue_property_type K>
  using Queue_property_payload_base
    = Basic_payload_base<Queue_property_type, K>;


// -------------------------------------------------------------------------- //
// Queue property: Min rate

/// Minimum datarate guaranteed by the queue.
///
/// Implement ofp_queue_prop_min_rate (OFPQT_MIN_RATE property) in OpenFlow 
/// protocol.
struct Queue_property_min_rate
  : Queue_property_payload_base<QUEUE_PROPERTY_MIN_RATE>
{
  Queue_property_min_rate() = default;
  explicit Queue_property_min_rate(uint16_t r): rate(r) { }

  uint16_t rate;
};

/// \relates Queue_property_min_rate
bool operator==(const Queue_property_min_rate& a, const Queue_property_min_rate& b);
/// \relates Queue_property_min_rate
bool operator!=(const Queue_property_min_rate& a, const Queue_property_min_rate& b);

/// \relates Queue_property_min_rate
std::size_t bytes(const Queue_property_min_rate&);

/// \relates Queue_property_min_rate
Error_condition is_valid(const Queue_property_min_rate&);

/// \relates Queue_property_min_rate
Error_condition to_buffer(Buffer_view&, const Queue_property_min_rate&);
/// \relates Queue_property_min_rate
Error_condition from_buffer(Buffer_view&, Queue_property_min_rate&);

/// \relates Queue_property_min_rate
std::string to_string(const Queue_property_min_rate&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue property: Max rate

/// Maximum datarate guaranteed by the queue.
struct Queue_property_max_rate
  : Queue_property_payload_base<QUEUE_PROPERTY_MAX_RATE>
{
  Queue_property_max_rate() = default;
  explicit Queue_property_max_rate(uint16_t r): rate(r) { }

  uint16_t rate;
};

/// \relates Queue_property_max_rate
bool operator==(const Queue_property_max_rate& a, const Queue_property_max_rate& b);
/// \relates Queue_property_max_rate
bool operator!=(const Queue_property_max_rate& a, const Queue_property_max_rate& b);

/// \relates Queue_property_max_rate
std::size_t bytes(const Queue_property_max_rate&);

/// \relates Queue_property_max_rate
Error_condition to_buffer(Buffer_view&, const Queue_property_max_rate&);
/// \relates Queue_property_max_rate
Error_condition from_buffer(Buffer_view&, Queue_property_max_rate&);

/// \relates Queue_property_max_rate
std::string to_string(const Queue_property_max_rate&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue property: Experimenter

/// Experimenter queue property
struct Queue_property_experimenter
  : Queue_property_payload_base<QUEUE_PROPERTY_EXPERIMENTER>
{
  Queue_property_experimenter() = default;
  explicit Queue_property_experimenter(uint32_t e, Greedy_buffer b)
  : experimenter(e), data(b) { }

  uint32_t experimenter;
  Greedy_buffer data;
};

/// \relates Queue_property_experimenter
bool 
operator==(const Queue_property_experimenter& a, const Queue_property_experimenter& b);

/// \relates Queue_property_experimenter
bool
operator!=(const Queue_property_experimenter& a, const Queue_property_experimenter& b);

/// \relates Queue_property_experimenter
std::size_t bytes(const Queue_property_experimenter& e);

/// \relates Queue_property_experimenter
Error_condition is_valid(const Queue_property_experimenter& e); 

/// \relates Queue_property_experimenter
Error_condition to_buffer(Buffer_view&, const Queue_property_experimenter&);
/// \relates Queue_property_experimenter
Error_condition from_buffer(Buffer_view&, Queue_property_experimenter&);

/// \relates Queue_property_experimenter
std::string to_string(const Queue_property_experimenter&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue property payload

/// \relates Queue_property_payload
union Queue_property_payload_data
{
  Queue_property_payload_data() { }  
  ~Queue_property_payload_data() { }  
 
  Queue_property_min_rate min_rate;
  Queue_property_max_rate max_rate;
  Queue_property_experimenter experimenter;
};

/// The payload of a queue property. 
///
/// A queue property consists of header and payload. The payload is a variant 
/// that can be any type of queue property structre. 
struct Queue_property_payload
{
  using Data = Queue_property_payload_data;

  Queue_property_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

/// \relates Queue_property_payload
void construct(Queue_property_payload&, Queue_property_type);
/// \relates Queue_property_payload
void construct(Queue_property_payload&, const Queue_property_payload&,
                  Queue_property_type);

/// \relates Queue_property_payload
Queue_property_payload&
assign(Queue_property_payload&, const Queue_property_payload&,
               Queue_property_type);

/// \relates Queue_property_payload
bool equal(const Queue_property_payload&, const Queue_property_payload&,
              Queue_property_type, Queue_property_type);

/// \relates Queue_property_payload
std::size_t bytes(const Queue_property_payload&, Queue_property_type);

/// \relates Queue_property_payload
Error_condition is_valid(const Queue_property_payload&, Queue_property_type);

/// \relates Queue_property_payload
Error_condition to_buffer(Buffer_view&, const Queue_property_payload&,
                  Queue_property_type);
/// \relates Queue_property_payload
Error_condition from_buffer(Buffer_view&, Queue_property_payload&,
                    Queue_property_type);

/// \relates Queue_property_payload
std::string to_string(const Queue_property_payload&, Formatter&
                  Queue_property_type);


// -------------------------------------------------------------------------- //
// Queue property header

struct Queue_property_header
{
  Queue_property_header() = default;
  Queue_property_header(Queue_property_type p, uint16_t l)
   : property(p), length(l){ }

  template<typename T>
    Queue_property_header(const T& value)
    : property(T::kind), length(8 + bytes(value)) { }

  Queue_property_type property;
  uint16_t length;
};

// Equality comparison
bool operator==(const Queue_property_header& a, const Queue_property_header& b);
bool operator!=(const Queue_property_header& a, const Queue_property_header& b);

//Bytes
std::size_t bytes(const Queue_property_header&);

Error_condition is_valid(const Queue_property_header& h);

Error_condition to_buffer(Buffer_view&, const Queue_property_header&);
Error_condition from_buffer(Buffer_view&, Queue_property_header&);

std::string to_string(const Queue_property_header&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue property

/// The header of a queue property. 
///
/// \remark Implements ofp_queue_prop_header in OpenFlow protocol.
struct Queue_property
{
  using Header = Queue_property_header;
  using Payload = Queue_property_payload;

  Queue_property() = default;

  Queue_property(const Queue_property&);
  Queue_property& operator=(const Queue_property&);

  Header  header;
  Payload payload;
};

/// \relates Queue_property_header
bool operator==(const Queue_property& a, const Queue_property& b);
/// \relates Queue_property_header
bool operator!=(const Queue_property& a, const Queue_property& b);

/// \relates Queue_property_header
std::size_t bytes(const Queue_property& p);

/// \relates Queue_property_header
Error_condition to_buffer(Buffer_view& v, const Queue_property& qp);
/// \relates Queue_property_header
Error_condition from_buffer(Buffer_view& v, const Queue_property& qp);

/// \relates Queue_property_header
std::string to_string(const Queue_property&,  Formatter&);


// -------------------------------------------------------------------------- //
// Queue

/// A queue in OpenFlow is a structure that is attached to a port and provide
/// datarate garantee to any data flow through it.
///
/// \remark Defined in [OpenFlow v1.2, p31]
struct Queue
{
  Queue() = default;
  Queue(uint32_t qid, uint32_t prt, uint32_t l, Sequence<Queue_property> p)
  : queue_id(qid), port(prt), length(l), properties(p) { }

  uint32_t queue_id;
  uint32_t port;
  uint16_t length;
  Sequence<Queue_property> properties;
};

/// \relates Queue
bool operator==(const Queue& a, const Queue& b);
/// \relates Queue
bool operator!=(const Queue& a, const Queue& b);

/// \relates Queue
std::size_t bytes(const Queue& q);

/// \relates Queue
Error_condition to_buffer(Buffer_view&, const Queue&);
/// \relates Queue
Error_condition from_buffer(Buffer_view&, Queue&);

/// \relates Queue
std::string to_string(const Queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Bucket

/// A bucket is a set of actions that is associated with a group. The actions
/// are applied to any packet directed to this group
///
/// \remark Defined in [OpenFlow v1.2, p49]
struct Bucket
{
  Bucket() = default;
  Bucket(uint16_t l, uint16_t w, uint32_t wp, uint32_t wg,
         const Sequence<Action> a)
  : len(l), weight(w), watch_port(wp), watch_group(wg), actions(a){ }

  uint16_t len;
  uint16_t weight;
  uint32_t watch_port;
  uint32_t watch_group;
  Sequence<Action> actions;
};

/// \relates Bucket
bool operator==(const Bucket& a, const Bucket& b);
/// \relates Bucket
bool operator!=(const Bucket& a, const Bucket& b);

/// \relates Bucket
std::size_t bytes(const Bucket& b);

/// \relates Bucket
Error_condition is_valid(const Bucket& b);

/// \relates Bucket
Error_condition to_buffer(Buffer_view&, const Bucket&);
/// \relates Bucket
Error_condition from_buffer(Buffer_view&, Bucket&);

/// \relates Bucket
std::string to_string(const Bucket&, Formatter&);

// -------------------------------------------------------------------------- //
// Bucket Counter

/// The counters associated with a bucket
///
/// \remark Describe ofp_bucket_counter in OpenFlow protocol
struct Bucket_counter
{
  Bucket_counter() = default;
  Bucket_counter(uint64_t pc, uint64_t bc)
   : packet_count(pc), byte_count(bc){ }

  uint64_t packet_count;
  uint64_t byte_count;
};

// Equality comparison
/// \relates Bucket_counter
bool operator==(const Bucket_counter& a, const Bucket_counter& b);
/// \relates Bucket_counter
bool operator!=(const Bucket_counter& a, const Bucket_counter& b);

// Bytes
/// \relates Bucket_counter
std::size_t bytes(const Bucket_counter&);

// To/from
/// \relates Bucket_counter
Error_condition to_buffer(Buffer_view& v, const Bucket_counter& bc);
/// \relates Bucket_counter
Error_condition from_buffer(Buffer_view& v, Bucket_counter& bc);

/// \relates Bucket_counter
std::string to_string(const Bucket_counter&, Formatter&);


// ------------------------------------------------------------------------- //
// Messages

// The following messages are in the v1_2 protocol.
//
// Hello
// Error
// Echo_req
// Echo_res
// Experimenter
// ...


// -------------------------------------------------------------------------- //
// Version Type

enum Version_type : std::uint8_t
{
  VERSION = 3
};

// Is valid
Error_condition is_valid(const Version_type t);

/// Returns a string representation of the version type.
std::string to_string(Version_type t);


// -------------------------------------------------------------------------- //
// Message Type

enum Message_type : std::uint8_t
{
  HELLO = 0,
  ERROR = 1,
  ECHO_REQ = 2,
  ECHO_RES = 3,
  EXPERIMENTER = 4,

  FEATURE_REQ = 5,
  FEATURE_RES = 6,
  GET_CONFIG_REQ = 7,
  GET_CONFIG_RES = 8,
  SET_CONFIG = 9,

  PACKET_IN = 10,
  FLOW_REMOVED = 11,
  PORT_STATUS = 12,
  PACKET_OUT = 13,
  FLOW_MOD = 14,
  GROUP_MOD = 15,
  PORT_MOD = 16,
  TABLE_MOD = 17,

  STATS_REQ = 18,
  STATS_RES = 19,
  BARRIER_REQ = 20,
  BARRIER_RES = 21,

  QUEUE_GET_CONFIG_REQ = 22,
  QUEUE_GET_CONFIG_RES = 23,

  ROLE_REQ = 24,
  ROLE_RES = 25
};

/// Returns true if n is a valid value of Message_type.
/// \relates Message_type
Error_condition is_valid(const Message_type t);

/// Returns a string representation of the message type.
/// \relates Message_type
std::string to_string(Message_type t);

/// A helper type for primary message payloads.
/// \relates Message_type
template<Message_type K>
  using Payload_base = Basic_payload_base<Message_type, K>;


// -------------------------------------------------------------------------- //
// Hello

/// Sent by both controller and switch to negotiate the protocol version.
/// The Hello is used by either controller or switch during connection 
/// for version negotiation. When a connection is established, each side must 
/// immediately send a Hello message with the version field set to the highest 
/// version supported by the sender. 
///
/// If the version negotiation fails, an Error message is sent with type 
/// Error::HELLO_FAILED and code Error::HF_INCOMPATIBLE.
///
/// \remark Defined in [OpenFlow v1.2, p66](http:://...)
struct Hello : Payload_base<HELLO> 
{ 
  Hello() = default;
  explicit Hello(Greedy_buffer b): data(b) { }
 
  Greedy_buffer data;
};

// Equality comparison
/// \relates Hello
bool operator==(const Hello& a, const Hello& b);
/// \relates Hello
bool operator!=(const Hello& a, const Hello& b);

// Bytes
/// \relates Hello
std::size_t bytes(const Hello& h);

// Is valid
/// \relates Hello
Error_condition is_valid(const Hello& h);

// To/from buffer
/// \relates Hello
Error_condition to_buffer(Buffer_view&, const Hello&);
/// \relates Hello
Error_condition from_buffer(Buffer_view&, Hello&);

// To string
/// \relates Hello
std::string to_string(const Hello&, Formatter&);


// -------------------------------------------------------------------------- //
// Error

/// Sent by the switch to report an error condition. The Error message consists
/// of an error type, an error code, and a variable length data field that
/// contains at least 64 bytes of failed request other than type
/// Error::HELLO_FAILED. Type indicates the high level nature  of the error and
/// the combination of type and code determines the detailed content of the
/// error. If the error message is in response to a message from  the
/// controller, the transaction id in the header of the error message should
/// match that of the message from the controller.
///
/// \invariant if m.type == HELLO_FAILED then is_valid(m.code.hf)
/// \invariant if m.type == BAD_REQUEST then is_valid(m.code.br)
/// \invariant if m.type == BAD_ACTION then is_valid(m.code.ba)
/// \invariant if m.type == BAD_INSTRUCTION then is_valid(m.code.bi)
/// \invariant if m.type == BAD_MATCH then is_valid(m.code.bm)
/// \invariant if m.type == FLOW_MOD_FAILED then is_valid(m.code.fmf)
/// \invariant if m.type == GROUP_MOD_FAILED then is_valid(m.code.gmf)
/// \invariant if m.type == PORT_MOD_FAILED then is_valid(m.code.pmf)
/// \invariant if m.type == TABLE_MOD_FAILED then is_valid(m.code.tmf)
/// \invariant if m.type == QUEUE_OP_FAILED then is_valid(m.code.qof)
/// \invariant if m.type == SWITCH_CONFIG_FAILED then is_valid(m.code.scf);
/// \invariant if m.type != HELLO_FAILED then bytes(m.data) >= 64
///
/// \remark Defined in [OpenFlow v1.2, p62-66](http://...)
struct Error : Payload_base<ERROR>
{
  enum Type : uint16_t {
    HELLO_FAILED = 0x0000, BAD_REQUEST = 0x0001, BAD_ACTION = 0x0002,
    BAD_INSTRUCTION = 0x0003, BAD_MATCH = 0x0004,
    FLOW_MOD_FAILED = 0x0005, GROUP_MOD_FAILED = 0x0006,
    PORT_MOD_FAILED = 0x0007, TABLE_MOD_FAILED = 0x0008,
    QUEUE_OP_FAILED = 0x0009, SWITCH_CONFIG_FAILED = 0x000a,
    ROLE_REQUEST_FAILED = 0x000b, EXPERIMENTER = 0xffff
  };

  enum Hello_failed : uint16_t {
    HF_INCOMPATIBLE = 0x0000, HF_EPERM = 0x0001
  };

  enum Bad_request : uint16_t {
    BR_BAD_VERSION = 0x0000, BR_BAD_TYPE = 0x0001, BR_BAD_STAT = 0x0002,
    BR_BAD_EXPERIMENTER = 0x0003, BR_BAD_EXPERIMENTER_TYPE = 0x0004,
    BR_EPERM = 0x0005, BR_BAD_LEN = 0x0006, BR_BUFFER_EMPTY = 0x0007,
    BR_BUFFER_UNKNOWN = 0x0008, BR_BAD_TABLE_ID = 0x0009,
    BR_IS_SLAVE = 0x000a, BR_BAD_PORT = 0x00B, BR_BAD_PACKET = 0x000c
  };

  enum Bad_action : uint16_t {
    BA_BAD_TYPE = 0x0000, BA_BAD_LEN = 0x0001, BA_BAD_EXPERIMENTER = 0x0002,
    BA_BAD_EXPERIMENTER_TYPE = 0x0003, BA_BAD_OUT_PORT = 0x0004,
    BA_BAD_ARGUMENT = 0x0005, BA_RPERM = 0x0006, BA_TOO_MANY = 0x0007,
    BA_BAD_QUEUE = 0x0008, BA_BAD_OUT_GROUP = 0x0009,
    BA_MATCH_INCONSISTENT = 0x000a, BA_UNSUPPORTED_ORDER = 0x000b,
    BA_BAD_TAG = 0x000c, BA_BAD_SET_TYPE = 0x000d, BA_BAD_SET_LEN = 0x000e,
    BA_BAD_SET_ARGUMENT = 0x000f
  };

  enum Bad_instruction : uint16_t {
    BI_UNKNOWN_INST = 0x0000, BI_UNSUP_INST = 0x0001,
    BI_BAD_TABLE_ID = 0x0002, BI_UNSUP_METADATA = 0x0003,
    BI_UNSUP_METADATA_MASK = 0x0004, BI_BAD_EXPERIMENTER = 0x0005,
    BI_BAD_EXP_TYPE = 0x0006, BI_BAD_LEN = 0x0007, BI_EPERM = 0x0008
  };

  enum Bad_match : uint16_t {
    BM_BAD_TYPE = 0x0000, BM_BAD_LEN = 0x0001, BM_BAD_TAG = 0x0002,
    BM_BAD_DL_ADDR_MASK = 0x0003, BM_BAD_HW_ADDR_MASK = 0x0004,
    BM_BAD_WILDCARDS = 0x0005, BM_BAD_FIELD = 0x0006, BM_BAD_VALUE = 0x0007,
    BM_BAD_MASK = 0x0008, BM_BAD_PREREQ = 0x0009, BM_DUP_FIELD = 0x000a,
    BM_EPERM = 0x000b
  };

  enum Flow_mod_failed : uint16_t {
    FMF_UNKNOWN = 0x0000, FMF_TABLE_FULL = 0x0001, FMF_BAD_TABLE_ID = 0x0002,
    FMF_OVERLAP = 0x0003, FMF_EPERM = 0x0004, FMF_BAD_TIMEOUT = 0x0005,
    FMF_BAD_COMMAND = 0x0006, FMF_BAD_FLAGS = 0x0007
  };

  enum Group_mod_failed : uint16_t {
    GMF_GROUP_EXISTS = 0x0000, GMF_INVALID_GROUP = 0x0001,
    GMF_WEIGHT_UNSUPPORTED = 0x0002, GMF_OUT_OF_GROUPS = 0x0003,
    GMF_OUT_OF_BUCKETS = 0x0004, GMF_CHAINING_UNSUPPORTED = 0x0005,
    GMF_WATCH_UNSUPPORTED = 0x0006, GMF_LOOP = 0x0007,
    GMF_UNKNOWN_GROUP = 0x0008, GMF_CHAINED_GROUP = 0x0009,
    GMF_BAD_TYPE = 0x000a, GMF_BAD_COMMAND = 0x000b, GMF_BAD_BUCKET = 0x000c,
    GMF_BAD_WATCH = 0x000d, GMF_EPERM = 0x000e
  };

  enum Port_mod_failed : uint16_t {
    PMF_BAD_PORT = 0x0000, PMF_BAD_HW_ADDR = 0x0001, PMF_BAD_CONFIG = 0x0002,
    PMF_BAD_ADVERTISE = 0x0003, PMF_EPERM = 0x0004
  };

  enum Table_mod_failed : uint16_t {
    TMF_BAD_TABLE = 0x0000, TMF_BAD_CONFIG = 0x0001, TMF_EPERM = 0x0002
  };

  enum Queue_op_failed : uint16_t {
    QOF_BAD_PORT = 0x0000, QOF_BAD_QUEUE = 0x0001, QOF_EPERM = 0x0002
  };

  enum Switch_config_failed : uint16_t {
    SCF_BAD_FLAGS = 0x0000, SCF_BAD_LEN = 0x0001, SCF_EPERM = 0x0002
  };

  enum Role_request_failed : uint16_t {
    RRF_STALE = 0x0000, RRF_UNSUP = 0x0001, RRF_BAD_ROLE = 0x0002
  };

  union Code {
    Code() = default;
    Code(Hello_failed f) : hf(f) { }
    Code(Bad_request f) : br(f) { }
    Code(Bad_action f) : ba(f) { }
    Code(Bad_instruction f) : bi(f) { }
    Code(Bad_match f) : bm(f) { }
    Code(Flow_mod_failed f) : fmf(f) { }
    Code(Group_mod_failed f) : gmf(f) { }
    Code(Port_mod_failed f) : pmf(f) { }
    Code(Table_mod_failed f) : tmf(f) { }
    Code(Queue_op_failed f) : qof(f) { }
    Code(Switch_config_failed f) : scf(f) { }
    Code(Role_request_failed f) : rrf(f) { }
    Code(uint16_t n) : value(n) { }

    Hello_failed         hf;
    Bad_request          br;
    Bad_action           ba;
    Bad_instruction      bi;
    Bad_match            bm;
    Flow_mod_failed      fmf;
    Group_mod_failed     gmf;
    Port_mod_failed      pmf;
    Table_mod_failed     tmf;
    Queue_op_failed      qof;
    Switch_config_failed scf;
    Role_request_failed  rrf;
    uint16_t             value; // Uninterpreted value
  };

  Error() = default;

  Error(Hello_failed f, const Greedy_buffer& b) 
    : type(HELLO_FAILED), code(f), data() { }
  
  Error(Bad_request f, const Greedy_buffer& b) 
    : type(BAD_REQUEST), code(f), data() { }
  
  Error(Bad_action f, const Greedy_buffer& b) 
    : type(BAD_ACTION), code(f), data() { }
  
  Error(Bad_instruction f, const Greedy_buffer& b) 
    : type(BAD_INSTRUCTION), code(f), data() { }
  
  Error(Bad_match f, const Greedy_buffer& b) 
    : type(BAD_MATCH), code(f), data() { }
  
  Error(Flow_mod_failed f, const Greedy_buffer& b) 
    : type(FLOW_MOD_FAILED), code(f), data() { }
  
  Error(Group_mod_failed f, const Greedy_buffer& b) 
    : type(GROUP_MOD_FAILED), code(f), data() { }
  
  Error(Port_mod_failed f, const Greedy_buffer& b) 
    : type(PORT_MOD_FAILED), code(f), data() { }
  
  Error(Table_mod_failed f, const Greedy_buffer& b) 
    : type(TABLE_MOD_FAILED), code(f), data() { }
  
  Error(Queue_op_failed f, const Greedy_buffer& b) 
    : type(QUEUE_OP_FAILED), code(f), data() { }
  
  Error(Switch_config_failed f, const Greedy_buffer& b) 
    : type(SWITCH_CONFIG_FAILED), code(f), data() { }
  
  Error(Role_request_failed f, const Greedy_buffer& b) 
    : type(ROLE_REQUEST_FAILED), code(f), data() { }

  /// Initialize the error message with error type t and the error
  /// code c. Note that the value is ill-formed if c is not a valid
  /// code for the error type t.
  Error(Type t, uint16_t c, const Greedy_buffer& b)
    : type(t), code(c), data(b) { assert(is_valid(*this)); }

  Type type;
  Code code;
  uint32_t experimenter_id; //only used for experimenter error
  Greedy_buffer data;
};

// Equality comparison
/// \relates Error
bool operator==(const Error& a, const Error& b);
/// \relates Error
bool operator!=(const Error& a, const Error& b);

// Bytes
/// \relates Error
std::size_t bytes(const Error& e);

// Is valid
/// \relates Error
Error_condition is_valid(const Error::Type t);

/// \relates Error
Error_condition is_valid(const Error::Hello_failed c);

/// \relates Error
Error_condition is_valid(const Error::Bad_request c);

/// \relates Error
Error_condition is_valid(const Error::Bad_action c);

/// \relates Error
Error_condition is_valid(const Error::Bad_instruction c);

/// \relates Error
Error_condition is_valid(const Error::Bad_match c);

/// \relates Error
Error_condition is_valid(const Error::Flow_mod_failed c);

/// \relates Error
Error_condition is_valid(const Error::Group_mod_failed c);

/// \relates Error
Error_condition is_valid(const Error::Port_mod_failed c);

/// \relates Error
Error_condition is_valid(const Error::Table_mod_failed c);

/// \relates Error
Error_condition is_valid(const Error::Queue_op_failed c);

/// \relates Error
Error_condition is_valid(const Error::Switch_config_failed c);

/// \relates Error
Error_condition is_valid(const Error::Role_request_failed c);

/// \relates Error
Error_condition is_valid(const Error::Type t, Error::Code c);

/// \relates Error
Error_condition is_valid(const Error& e);

// To/from buffer
/// \relates Error
Error_condition to_buffer(Buffer_view&, const Error&);
/// \relates Error
Error_condition from_buffer(Buffer_view&, Error&);

// To string
/// \relates Error
std::string to_string(const Error&, Formatter&);
/// \relates Error
std::string to_string(Error::Type);
/// \relates Error
std::string to_string(Error::Hello_failed);
/// \relates Error
std::string to_string(Error::Bad_request);
/// \relates Error
std::string to_string(Error::Bad_action);
/// \relates Error
std::string to_string(Error::Bad_instruction);
/// \relates Error
std::string to_string(Error::Bad_match);
/// \relates Error
std::string to_string(Error::Flow_mod_failed);
/// \relates Error
std::string to_string(Error::Group_mod_failed);
/// \relates Error
std::string to_string(Error::Port_mod_failed);
/// \relates Error
std::string to_string(Error::Table_mod_failed);
/// \relates Error
std::string to_string(Error::Queue_op_failed);
/// \relates Error
std::string to_string(Error::Switch_config_failed);
/// \relates Error
std::string to_string(Error::Role_request_failed);
/// \relates Error
std::string to_string(Error::Type, Error::Code);


// -------------------------------------------------------------------------- //
// Echo Base

// A base class providing common features for Echo_req and Echo_res.
template<Message_type K>
  struct Echo_base : Payload_base<ECHO_REQ>
  {
    Echo_base() = default;
    Echo_base(const Greedy_buffer& b) : data(b) { }

    Greedy_buffer data;
  };

// Equality comparable
/// \relates Echo_base
template<Message_type K>
  bool operator==(const Echo_base<K>& a, const Echo_base<K>& b);

/// \relates Echo_base
template<Message_type K>
  bool operator!=(const Echo_base<K>& a, const Echo_base<K>& b);

// Bytes
/// \relates Echo_base
template<Message_type K>
  std::size_t bytes(const Echo_base<K>& e);

// Is valid
/// \relates Echo_base
template<Message_type K>
  Error_condition is_valid(const Echo_base<K>&);

// To/from buffer
/// \relates Echo_base
template<Message_type K>
  Error_condition to_buffer(Buffer_view& v, const Echo_base<K>& e);

/// \relates Echo_base
template<Message_type K>
  Error_condition from_buffer(Buffer_view& v, Echo_base<K>& e);

// To string
/// \relates Echo_base
template<Message_type K>
  std::string to_string(const Echo_base<K>& e, Formatter& f);


// -------------------------------------------------------------------------- //
// Echo Req

/// Sent by the controller to exchange information about latency, bandwidth,
/// and liveness. The EchoReq message is used to exchange information about
/// latency,  bandwidth, and liveness. Request timeouts indicate a
/// disconnection. The request contains a header and a variable length field
/// containing arbitrary information, such as latency (timestamp), bandwidth,
/// liveness, etc. Requests to this message must contain a copy of this variable
/// data.
///
/// \remark Defined in [OpenFlow v1.2, p66]
struct Echo_req : Echo_base<ECHO_REQ> { };


// -------------------------------------------------------------------------- //
// Echo Res

/// Sent by the switch to exchange information about latency, bandwidth, and
/// liveness. The EchoRes message is used to exchange information about latency,
/// bandwidth, and liveness. Request timeouts indicate a disconnection. The
/// response contains a copy of the data sent by the request.
///
///
/// \remark Defined in [OpenFlow v1.2, p66]
struct Echo_res : Echo_base<ECHO_RES> { };


// -------------------------------------------------------------------------- //
// Experimenter

/// Represents a proprietary messages within the protocol. the
/// Vendor/Experimenter message is a mechanism for creating proprietary messages
/// within the protocol. In v1.0 this was called Vendor; however, in subsequent
/// versions the name was changed to experimenter.
/// 
/// \remark Defined in [OpenFlow v1.2, p67]
struct Experimenter : Payload_base<EXPERIMENTER>
{
  Experimenter() = default;
  Experimenter(uint32_t e, uint32_t t, Greedy_buffer d)
   : experimenter_id(e), experimenter_type(t), data(d) { }

  uint32_t experimenter_id;
  uint32_t experimenter_type;
  Greedy_buffer data;
};

// Equality comparison
/// \relates Experimenter
bool operator==(const Experimenter& a, const Experimenter& b);
/// \relates Experimenter
bool operator!=(const Experimenter& a, const Experimenter& b);

// Bytes
/// \relates Experimenter
std::size_t bytes(const Experimenter& e);

/// \relates Experimenter
Error_condition is_valid(const Experimenter&);

// To/from
/// \relates Experimenter
Error_condition to_buffer(Buffer_view&, const Experimenter&);
/// \relates Experimenter
Error_condition from_buffer(Buffer_view&, Experimenter&);

/// \relates Experimenter
std::string to_string(const Experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// Feature Request

/// Sent by the controller to the switch. A Features Request is required by 
/// OpenFlow protocol to be sent at handshake phase. The controller respond
/// with a Features Reply that contains the features of switch
///
/// The Features Request message contains nothing but an OpenFlow header
///
/// \remark Defined in [OpenFlow v1.2, p43]
struct Feature_req : Payload_base<FEATURE_REQ> { };


// -------------------------------------------------------------------------- //
// Feature Response

/// Sent by the switch to the controller as reply to a Features Request message.
/// Contains the features supported by the switch.
///
/// \remark Defined in [OpenFlow v1.2, p43-44]
struct Feature_res : Payload_base<FEATURE_RES>
{
  enum Capability_type : uint32_t
  {
    FLOW_STATS = 0x00000001, TABLE_STATS = 0x00000002,
    PORT_STATS = 0x00000004, GROUP_STATS = 0x00000008,
    IP_REASM = 0x00000020, QUEUE_STATS = 0x00000040,
    PORT_BLOCKED = 0x00000100
  };

  Feature_res() = default;
  Feature_res(uint64_t did, uint32_t nb, uint8_t nt, Capability_type c,
              uint32_t r, const Sequence<Port>& p)
     : datapath_id(did), n_buffers(nb), n_tbls(nt), capabilities(c)
     , reserved(r), ports(p) { }


  uint64_t datapath_id;
  uint32_t n_buffers;
  uint8_t n_tbls;
  Capability_type capabilities;
  uint32_t reserved;
  Sequence<Port> ports;
};


// Equality comparable
/// \relates Feature_res
bool operator==(const Feature_res& a, const Feature_res& b);
/// \relates Feature_res
bool operator!=(const Feature_res& a, const Feature_res& b);

// Bytes
/// \relates Feature_res
std::size_t bytes(const Feature_res& fr);

// is_valid
/// \relates Feature_res
Error_condition is_valid(const Feature_res::Capability_type& c); 
/// \relates Feature_res
Error_condition is_valid(const Feature_res& fr);

// To/from
/// \relates Feature_res
Error_condition to_buffer(Buffer_view&, const Feature_res&);
/// \relates Feature_res
Error_condition from_buffer(Buffer_view&, Feature_res&);

/// \relates Feature_res
std::string to_string(const Feature_res&, Formatter&);
/// \relates Feature_res
std::string to_string(const Feature_res::Capability_type);

/// \relates Feature_res
bool feature_res_capabilities_flow_stats(uint32_t c);

/// \relates Feature_res
bool feature_res_capabilities_table_stats(uint32_t c);

/// \relates Feature_res
bool feature_res_capabilities_port_stats(uint32_t c);

/// \relates Feature_res
bool feature_res_capabilities_group_stats(uint32_t c);

/// \relates Feature_res
bool feature_res_capabilities_ip_reasm(uint32_t c);

/// \relates Feature_res
bool feature_res_capabilities_queue_stats(uint32_t c);

/// \relates Feature_res
bool feature_res_capabilities_port_blocked(uint32_t c);

// -------------------------------------------------------------------------- //
// Get Config Request

/// Sent by the controller to the switch to request current configuration
/// of the switch.
///
/// Get_config_req message contains nothing but OpenFlow header.
///
/// \remark Defined in [OpenFlow v1.2, p44]
struct Get_config_req : Payload_base<GET_CONFIG_REQ> { };


// -------------------------------------------------------------------------- //
// Config Message Base

/// The base class for Get Config Response and Set Config messages. 
/// 
/// \remark Describes ofp_switch_config in OpenFlow protocol
template<Message_type T>
  struct Config_message_base
  {
    enum Flag_type : uint16_t {
      FRAG_NORMAL = 0x0000, FRAG_DROP = 0x0001, FRAG_REASM = 0x0002,
      FRAG_MASK = 0x0003, INVALID_TTL_TO_CONTROLLER = 0x0004
    };

    Config_message_base() = default;
    Config_message_base(Flag_type f, uint16_t msl)
    : flags(f), miss_send_len(msl)  { }

    Flag_type flags;
    uint16_t miss_send_len;
  };


// Equality comparison
/// \relates Config_message_base
template<Message_type T>
  bool operator==(const Config_message_base<T>& a, const Config_message_base<T>& b);

/// \relates Config_message_base
template<Message_type T>
  bool operator!=(const Config_message_base<T>& a, const Config_message_base<T>& b);

// Bytes
/// \relates Config_message_base
template<Message_type T>
  std::size_t bytes(const Config_message_base<T>&);

/// \relates Config_message_base
template<Message_type T>
  Error_condition is_valid(const Config_message_base<T>& c);

/// \relates Config_message_base
template<Message_type T>
  Error_condition to_buffer(Buffer_view& v, const Config_message_base<T>& m);

/// \relates Config_message_base
template<Message_type T>
  Error_condition from_buffer(Buffer_view& v, Config_message_base<T>& m);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_normal(typename Config_message_base<T>::Flag_type ft);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_drop(typename Config_message_base<T>::Flag_type ft);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_reasm(typename Config_message_base<T>::Flag_type ft); 

/// \relates Config_message_base
template<Message_type T>
  bool
  config_invalid_ttl_to_controller(typename Config_message_base<T>::Flag_type 
                                            ft); 


// -------------------------------------------------------------------------- //
// Get Config Response

/// Sent by the switch to the controller as reply to Get Config Request
/// message. It contiains the current configuration of the switch
///
/// \remark Defined in [OpenFlow v1.2, p44-45]
struct Get_config_res : Config_message_base<GET_CONFIG_RES> { };

/// \relates Get_config_res
std::string to_string(const Get_config_res&, Formatter&);


// -------------------------------------------------------------------------- //
// Set Config

/// Sent by the controller to the switch to modify the current configuration
/// of the switch
///
/// \remark Defined in [OpenFlow v1.2, p44-45]
struct Set_config : Config_message_base<SET_CONFIG> { };

/// \relates Set_config
std::string to_string(const Set_config&, Formatter&);


// -------------------------------------------------------------------------- //
// Packet In

/// Sent by the switch to the controller as a consequence of Output action
/// towards the controller or a table miss.
///
/// Packet In message contains the packet (or part of the packet) and some
/// information related to the packet (incoming port, length, reason of forwarding
/// to controller, etc).
///
/// \remark Defined in [OpenFlow v1.2, p59-60]
struct Packet_in : Payload_base<PACKET_IN>
{
  enum Reason_type : uint8_t 
  {
    NO_MATCH = 0x00, ACTION = 0x01, INVALID_TTL = 0x02
  };

  Packet_in() = default;
  Packet_in(uint32_t bid, uint16_t tl,
            Reason_type r, uint8_t tid, Match m, Buffer d)
  : buffer_id(bid), total_len(tl), reason(r), tbl_id(tid), match(m), data(d) { }

  uint32_t buffer_id;
  uint16_t total_len;
  Reason_type reason;
  uint8_t tbl_id;
  Match match;
  Buffer data;
};

// Equality comparison
/// \relates Packet_in
bool operator==(const Packet_in& a, const Packet_in& b);
/// \relates Packet_in
bool operator!=(const Packet_in& a, const Packet_in& b);

// Bytes
/// \relates Packet_in
std::size_t bytes(const Packet_in& pi);

// Is valid
/// \relates Packet_in
Error_condition is_valid(const Packet_in::Reason_type r);
/// \relates Packet_in
Error_condition is_valid(const Packet_in& p);

// To/from
/// \relates Packet_in
Error_condition to_buffer(Buffer_view&, const Packet_in&);
/// \relates Packet_in
Error_condition from_buffer(Buffer_view&, Packet_in&);

/// \relates Packet_in
std::string to_string(const Packet_in&, Formatter&);
/// \relates Packet_in
std::string to_string(Packet_in::Reason_type);


// -------------------------------------------------------------------------- //
// Flow Removed

/// The message is sent by the switch to the controller to notify a flow being
/// removed from the tables in the switch. The possible reason for it could
/// be a timeout or a deletion operation.
///
/// \remark Defined in [OpenFlow v1.2, p61]
struct Flow_removed : Payload_base<FLOW_REMOVED>
{
  enum Reason_type : uint8_t
  {
    IDLE_TIMEOUT = 0x00, HARD_TIMEOUT = 0x01, DELETE = 0x02,
    GROUP_DELETE = 0x03
  };

  Flow_removed() = default;
  Flow_removed(uint64_t c, uint16_t p, Reason_type r, uint8_t tid,
               uint32_t ds, uint32_t dn, uint16_t it, uint16_t ht, uint64_t pc,
               uint64_t bc, Match m)
  : cookie(c), priority(p), reason(r), table_id(tid), duration_sec(ds),
    duration_nsec(dn), idle_timeout(it), hard_timeout(ht), packet_count(pc),
    byte_count(bc), match(m) { }

  uint64_t cookie;
  uint16_t priority;
  Reason_type reason;
  uint8_t table_id;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  uint16_t idle_timeout;
  uint16_t hard_timeout;
  uint64_t packet_count;
  uint64_t byte_count;
  Match match;
};

// Equality Comparable
/// \relates Flow_removed
bool operator==(const Flow_removed& a, const Flow_removed& b);
/// \relates Flow_removed
bool operator!=(const Flow_removed& a, const Flow_removed& b);

// Bytes
/// \relates Flow_removed
std::size_t bytes(const Flow_removed& fr);

// Is valid
/// \relates Flow_removed
Error_condition is_valid(const Flow_removed::Reason_type r);
/// \relates Flow_removed
Error_condition is_valid(const Flow_removed& f); 

// To/from
/// \relates Flow_removed
Error_condition to_buffer(Buffer_view&, const Flow_removed&);
/// \relates Flow_removed
Error_condition from_buffer(Buffer_view&, Flow_removed&);

/// \relates Flow_removed
std::string to_string(const Flow_removed&, Formatter&);
/// \relates Flow_removed
std::string to_string(Flow_removed::Reason_type);


// -------------------------------------------------------------------------- //
// Port Status

/// The message is sent from the switch to the controller to inform addition,
/// remove or modification of ports from the datapath. 
///
/// \remark Defined in [OpenFlow v1.2, p61]
struct Port_status : Payload_base<PORT_STATUS>
{
  enum Reason_type : uint8_t {
    ADD = 0x00, DELETE = 0x01, MODIFY = 0x02
  };

  Port_status() = default;
  Port_status(Reason_type r, Port p): reason(r), port(p) { }

  Reason_type reason;
  Port port;
};

// Equality comparison
/// \relates Port_status
bool operator==(const Port_status& a, const Port_status& b);
/// \relates Port_status
bool operator!=(const Port_status& a, const Port_status& b);

// Bytes
/// \relates Port_status
std::size_t bytes(const Port_status& ps);

// Is valid
/// \relates Port_status
Error_condition is_valid(const Port_status::Reason_type r);
/// \relates Port_status
Error_condition is_valid(const Port_status& p);

// To/from
/// \relates Port_status
Error_condition to_buffer(Buffer_view&, const Port_status&);
/// \relates Port_status
Error_condition from_buffer(Buffer_view&, Port_status&);

/// \relates Port_status
std::string to_string(const Port_status&, Formatter&);
/// \relates Port_status
std::string to_string(Port_status::Reason_type);


// -------------------------------------------------------------------------- //
// Packet Out

/// The Packet Out message is sent from the controller to the switch when
/// the controller want the switch to perform any action on a packet. 
///
/// The packet is given either by the data buffer of the Packet Out message or
/// by referring to the buffer_id of a packet that is sent to controller earlier
/// by Packet In message.
///
/// The action list associated with Packet Out message refer to the actions
/// the switch should perform on the packet. The packet is dropped if an empty
/// action list is given.
///
/// \remark Defined in [OpenFlow v1.2, p58]
struct Packet_out : Payload_base<PACKET_OUT>
{
  Packet_out() = default;
  Packet_out(uint32_t bid, uint32_t ip, uint16_t al, Sequence<Action> a,
             Greedy_buffer d) 
  : buffer_id(bid), in_port(ip), actions_len(al), actions(a), data(d) { }

  uint32_t buffer_id;
  uint32_t in_port;
  uint16_t actions_len;
  Sequence<Action> actions;
  Greedy_buffer data;
};

// Equality comparison
/// \relates Packet_out
bool operator==(const Packet_out& a, const Packet_out& b);
/// \relates Packet_out
bool operator!=(const Packet_out& a, const Packet_out& b);

// Bytes
/// \relates Packet_out
std::size_t bytes(const Packet_out& po);

// Is valid
/// \relates Packet_out
Error_condition is_valid(const Packet_out& p);

// To/from
/// \relates Packet_out
Error_condition to_buffer(Buffer_view&, const Packet_out&);
/// \relates Packet_out
Error_condition from_buffer(Buffer_view&, Packet_out&);

// To string
/// \relates Packet_out
std::string to_string(const Packet_out&, Formatter&);

// -------------------------------------------------------------------------- //
// Flow_mod

/// Sent by the controller to modify the state of an OpenFlow switch. This is 
/// one of the main messages, it allows the controller to modify the
/// state of an OpenFlow switch.
/// 
/// \remark Defined in [OpenFlow v1.2, p46-48]
struct Flow_mod : Payload_base<FLOW_MOD>
{
  enum Command_type : uint8_t {
    ADD = 0x00, MODIFY = 0x01, MODIFY_STRICT = 0x02, DELETE = 0x03,
    DELETE_STRICT = 0x04
  };

  enum Flag_type : uint16_t {
    SEND_FLOW_REM = 0x0001, CHECK_OVERLAP = 0x0002, RESET_COUNTS = 0x0004
  };

  Flow_mod() = default;
  Flow_mod(uint64_t ck, uint64_t ckm, uint8_t tid, Command_type cmd,
           uint16_t it, uint16_t ht, uint16_t p, uint32_t bid, uint32_t op,
           uint32_t og, Flag_type f, const Match& m,
           const Sequence<Instruction>& i)
  : cookie(ck), cookie_mask(ckm), table_id(tid), command(cmd),
    idle_timeout(it), hard_timeout(ht), priority(p), buffer_id(bid),
    out_port(op), out_group(og), flags(f), match(m), instructions(i) { }

  uint64_t cookie;
  uint64_t cookie_mask;
  uint8_t table_id;
  Command_type command;
  uint16_t idle_timeout;
  uint16_t hard_timeout;
  uint16_t priority;
  uint32_t buffer_id;
  uint32_t out_port;
  uint32_t out_group;
  Flag_type flags;
  Match match;
  Sequence<Instruction> instructions;
};

// Equality comparison
/// \relates Flow_mod
bool operator==(const Flow_mod& a, const Flow_mod& b);
/// \relates Flow_mod
bool operator!=(const Flow_mod& a, const Flow_mod& b);

// Bytes
/// \relates Flow_mod
std::size_t bytes(const Flow_mod& fm);

// Is Valid
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod::Command_type t);
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod::Command_type c, const uint8_t table_id);
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod::Flag_type t);
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod& f);

// To/from
/// \relates Flow_mod
Error_condition to_buffer(Buffer_view&, const Flow_mod&);
/// \relates Flow_mod
Error_condition from_buffer(Buffer_view&, Flow_mod&);

// To string
/// \relates Flow_mod
std::string to_string(const Flow_mod&, Formatter&);
/// \relates Flow_mod
std::string to_string(Flow_mod::Command_type);
/// \relates Flow_mod
std::string to_string(Flow_mod::Flag_type);

// -------------------------------------------------------------------------- //
// Group Mod

/// The Group Mod message is sent by the controller to the switch to modify
/// the group table of the switch.
///
/// \remark Defined in [OpenFlow v1.2, p49]
struct Group_mod : Payload_base<GROUP_MOD>
{
  enum Command_type : uint16_t {
    ADD = 0x0000, MODIFY = 0x0001, DELETE = 0x0002
  };

  enum Type_value : uint8_t {
    ALL = 0x00, SELECT = 0x01, INDIRECT = 0x02, FF = 0x03
  };

  /// Construct an empty Group_mod message
  Group_mod() = default;
  
  /// Construct a Group_mod message with value of all the fields
  Group_mod(Command_type c, Type_value t, uint32_t gid,
            const Sequence<Bucket>& b) 
  : command(c), type(t), group_id(gid), buckets(b) { }

  Command_type command;
  Type_value type;
  uint32_t group_id;
  Sequence<Bucket> buckets;
};

/// Returns true when two Group_mod are totally equal. 
///
/// \relates Group_mod
bool operator==(const Group_mod& a, const Group_mod& b);

/// Returns true when two Group_mod structs do not compare equal.
///
/// \relates Group_mod
bool operator!=(const Group_mod& a, const Group_mod& b);

/// Return number of bytes of an Group_mod message.
///
/// \relates Group_mod
std::size_t bytes(const Group_mod& gm);

/// Validates the value of a Group_mod message. 
///
/// \relates Group_mod
Error_condition is_valid(const Group_mod::Command_type c);
Error_condition is_valid(const Group_mod::Type_value v);
Error_condition is_valid(const Group_mod& gm);
 
/// Writes a Group_mod message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Group_mod
Error_condition to_buffer(Buffer_view&, const Group_mod&);

/// Reads a Group_mod message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Group_mod
Error_condition from_buffer(Buffer_view&, Group_mod&);

/// Returns a formatted string representation of Group_mod.
///
/// \relates Group_mod
std::string to_string(const Group_mod&, Formatter&);
std::string to_string(Group_mod::Command_type);
std::string to_string(Group_mod::Type_value);



// -------------------------------------------------------------------------- //
// Port Mod

/// The Port Mod message is sent by the controller to the switch to modify the
/// behavior of the port
/// 
/// \remark Defined in [OpenFlow v1.2 p49]
struct Port_mod : Payload_base<PORT_MOD>
{
  /// Port config 
  enum Config_type : uint32_t {
    PORT_DOWN = 0x00000001, NO_RECV = 0x00000004, NO_FWD = 0x00000020,
    NO_PACKET_IN = 0x00000040
  };

  /// Port features 
  enum Features_type : uint32_t {
    TEN_MB_HD = 0x00000001, TEN_MB_FD = 0x00000002,
    HUNDRED_MB_HD = 0x00000004, HUNDRED_MB_FD = 0x00000008,
    ONE_GB_HD = 0x00000010, ONE_GB_FD = 0x00000020,
    TEN_GB_FD = 0x00000040, FOURTY_GB_FD = 0x00000080,
    HUNDRED_GB_FD = 0x00000100, ONE_TB_FD = 0x00000200,
    OTHER = 0x00000400, COPPER = 0x00000800, FIBER = 0x00001000,
    AUTO_NEG = 0x00002000, PAUSE = 0x00004000, PAUSE_ASYM = 0x00008000
  };

  /// Construct an empty Port_mod message
  Port_mod() = default;
  
  /// Construct a Port_mod message with value of all the fields
  Port_mod(uint32_t p, Ethernet_addr ha, Config_type c, uint32_t m,
           Features_type a)
  : port(p), hw_addr(ha), config(c), mask(m), advertise(a) { }

  // - Packet data
  uint32_t port;
  Ethernet_addr hw_addr;
  Config_type config;
  uint32_t mask;
  Features_type advertise;
};

/// Returns true when two Port_mod are totally equal. 
///
/// \relates Port_mod
bool operator==(const Port_mod& a, const Port_mod& b);

/// Returns true when two Port_mod structs do not compare equal.
///
/// \relates Port_mod
bool operator!=(const Port_mod& a, const Port_mod& b);

/// Return number of bytes of an Port_mod message.
///
/// \relates Port_mod
std::size_t bytes(const Port_mod&);

/// Validates the value of a Port_mod message. 
///
/// \relates Port_mod
Error_condition is_valid(const Port_mod& p);
 
/// Writes a Port_mod message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Port_mod
Error_condition to_buffer(Buffer_view&, const Port_mod&);

/// Reads a Port_mod message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Port_mod
Error_condition from_buffer(Buffer_view&, Port_mod&);

/// Returns a formatted string representation of Port_mod.
///
/// \relates Port_mod
std::string to_string(const Port_mod&, Formatter&);
std::string to_string(const Port_mod::Config_type);
std::string to_string(const Port_mod::Features_type);

bool port_mod_config_port_down(uint32_t c);

bool port_mod_config_no_recv(uint32_t c);

bool port_mod_config_no_fwd(uint32_t c);

bool port_mod_config_no_packet_in(uint32_t c);

bool port_mod_features_10mb_hd(uint32_t f);

bool port_mod_features_10mb_fd(uint32_t f);

bool port_mod_features_100mb_hd(uint32_t f);

bool port_mod_features_100mb_fd(uint32_t f);

bool port_mod_features_1gb_hd(uint32_t f);

bool port_mod_features_1gb_fd(uint32_t f);

bool port_mod_features_10gb_fd(uint32_t f);

bool port_mod_features_40gb_fd(uint32_t f);

bool port_mod_features_100gb_fd(uint32_t f);

bool port_mod_features_1tb_fd(uint32_t f);

bool port_mod_features_other(uint32_t f);

bool port_mod_features_copper(uint32_t f);

bool port_mod_features_fiber(uint32_t f);

bool port_mod_features_auto_neg(uint32_t f);

bool port_mod_features_pause(uint32_t f);

bool port_mod_features_pause_asym(uint32_t f);


// -------------------------------------------------------------------------- //
// Table Mod

/// The Table Mod message is sent by the controller to the switch to configure
/// and query the table state.
///
/// \remark Defined in [OpenFlow v1.2, p45]
struct Table_mod : Payload_base<TABLE_MOD>
{
  enum Config_type : uint32_t
  {
    MISS_CONTROLLER = 0x00000000, MISS_CONTINUE = 0x00000001,
    MISS_DROP = 0x00000002, MISS_MASK = 0x00000003
  };

  enum Table_IDs : uint8_t { TID_MAX = 0xfe, TID_ALL = 0xff };

  /// Construct an empty Table_mod message
  Table_mod() = default;
  
  /// Construct a Table_mod message with value of all the fields
  Table_mod(Table_IDs tid, Config_type ct) 
    : table_id(tid), config(ct) { }

  // - Packet data
  Table_IDs table_id;
  Config_type config;
};

/// Returns true when two Table_mod are totally equal. 
///
/// \relates Table_mod
bool operator==(const Table_mod& a, const Table_mod& b);

/// Returns true when two Table_mod structs do not compare equal.
///
/// \relates Table_mod
bool operator!=(const Table_mod& a, const Table_mod& b);

/// Return number of bytes of an Table_mod message.
///
/// \relates Table_mod
std::size_t bytes(const Table_mod&);

Error_condition is_valid(const Table_mod::Config_type c);

/// Validates the value of a Table_mod message. 
///
/// \relates Table_mod
Error_condition is_valid(const Table_mod tm);

/// Writes a Table_mod message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Table_mod
Error_condition to_buffer(Buffer_view&, const Table_mod&);

/// Reads a Table_mod message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Table_mod
Error_condition from_buffer(Buffer_view&, Table_mod&);

/// Returns a formatted string representation of Table_mod.
///
/// \relates Table_mod
std::string to_string(const Table_mod&, Formatter&);
std::string to_string(const Table_mod::Config_type);
std::string to_string(const Table_mod::Table_IDs);


// -------------------------------------------------------------------------- //
// Stats type

enum Stats_type : uint16_t
{
  STATS_DESC           = 0,
  STATS_FLOW           = 1,
  STATS_AGGREGATE      = 2,
  STATS_TABLE          = 3,
  STATS_PORT           = 4,
  STATS_QUEUE          = 5,
  STATS_GROUP          = 6,
  STATS_GROUP_DESC     = 7,
  STATS_GROUP_FEATURES = 8,
  STATS_EXPERIMENTER   = 0xffff
};

// Returns true whe t is a valid stats request value.
Error_condition is_valid(const Stats_type t);

// To string
std::string to_string(const Stats_type& h,  Formatter&);

// Payload base
template<Stats_type K>
  using Stats_payload_base = Basic_payload_base<Stats_type, K>;


// -------------------------------------------------------------------------- //
// Stats Request: Desc

/// Description of the OpenFlow switch.
///
/// \remark Implements an OFPST_DESC stats request message
struct Stats_req_desc : Stats_payload_base<STATS_DESC> { };


// -------------------------------------------------------------------------- //
// Stats Request Flow Base
//
// Provides common facilities for stats requests for single (flow) or
// multiple (aggregate) flows.

/// Base class for OFPST_FLOW and OFPST_AGGREGATE stats request message.
///
/// \remark Implements ofp_flow_stats_request in OpenFlow protocol.
template<Stats_type K>
  struct Stats_req_flow_base : Stats_payload_base<K>
  {
    Stats_req_flow_base() = default;
    Stats_req_flow_base(uint8_t tid, uint32_t op, uint32_t og, uint64_t c,
                        uint64_t cm, const Match& m)
    : table_id(tid), out_port(op), out_group(og), cookie(c),
      cookie_mask(cm), match(m)  { }

    uint8_t  table_id;
    uint32_t out_port;
    uint32_t out_group;
    uint64_t cookie;
    uint64_t cookie_mask;
    Match match;
  };

// Equality comparison
template<Stats_type K>
  bool operator==(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b);

template<Stats_type K>
  bool operator!=(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b);

// Bytes
template<Stats_type K>
  std::size_t bytes(const Stats_req_flow_base<K>& f);

template<Stats_type K>
  Error_condition is_valid(const Stats_req_flow_base<K>& f);

// To/from buffer
template<Stats_type K>
  Error_condition to_buffer(Buffer_view& v, const Stats_req_flow_base<K>& f);

template<Stats_type K>
  Error_condition from_buffer(Buffer_view& v, Stats_req_flow_base<K>& f);


// -------------------------------------------------------------------------- //
// Stats Request: Flow

/// Individual flow statistics
///
/// \remark Implements an OFPST_FLOW stats request message.
struct Stats_req_flow : Stats_req_flow_base<STATS_FLOW> { };
std::string to_string(const Stats_req_flow&, Formatter&);

// -------------------------------------------------------------------------- //
// Stats Request Aggregate

/// Aggregate flow statistics
///
/// \remark Implements an OFPST_AGGREGATE stats request message.
struct Stats_req_aggregate : Stats_req_flow_base<STATS_AGGREGATE> { };
std::string to_string(const Stats_req_aggregate&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Request: Table

/// Flow table statistics
///
/// \remark Implements an OFPST_TABLE stats request message.
struct Stats_req_table : Stats_payload_base<STATS_TABLE> { };

// -------------------------------------------------------------------------- //
// Stats Request: Port

/// Port statistics
///
/// \remark Implements an OFPST_PORT stats request message.
struct Stats_req_port : Stats_payload_base<STATS_PORT>
{
  Stats_req_port() = default;
  explicit Stats_req_port(uint32_t p)
  : port_no(p) { }

  uint32_t port_no;
};

// Equality comparison
bool operator==(const Stats_req_port& a, const Stats_req_port& b);
bool operator!=(const Stats_req_port& a, const Stats_req_port& b);

// Bytes
std::size_t bytes(const Stats_req_port& p);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_req_port& p);
Error_condition from_buffer(Buffer_view& v, Stats_req_port& p);

std::string to_string(const Stats_req_port& p,  Formatter&);


// -------------------------------------------------------------------------- //
// Stats Request: Queue

/// Queue statistics for a port
///
/// \remark Implements an OFPST_QUEUE stats request message.
struct Stats_req_queue : Stats_payload_base<STATS_QUEUE>
{
  Stats_req_queue() = default;
  Stats_req_queue(uint32_t p, uint32_t q)
  : port_no(p), queue_id(q) { }

  uint32_t port_no;
  uint32_t queue_id;
};

// Equality comparison
bool operator==(const Stats_req_queue& a, const Stats_req_queue& b);
bool operator!=(const Stats_req_queue& a, const Stats_req_queue& b);

// Bytes
std::size_t bytes(const Stats_req_queue& q);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_req_queue& q);
Error_condition from_buffer(Buffer_view& v, Stats_req_queue& q);
std::string to_string(const Stats_req_queue& q,  Formatter&);


// -------------------------------------------------------------------------- //
// Stats Request: Group

/// Group counter statistics
///
/// \remark Implements an OFPST_GROUP stats request message.
struct Stats_req_group : Stats_payload_base<STATS_GROUP>
{
  Stats_req_group() = default;
  explicit Stats_req_group(uint32_t gid): group_id(gid) { }
  
  uint32_t group_id;
};

// Equality comparison
bool operator==(const Stats_req_group& a, const Stats_req_group& b);
bool operator!=(const Stats_req_group& a, const Stats_req_group& b);

// Bytes
std::size_t bytes(const Stats_req_group&);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_req_group&);
Error_condition from_buffer(Buffer_view& v, Stats_req_group&);
std::string to_string(const Stats_req_group&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Request: Group desc

/// Group description statistics
///
/// \remark Implements an OFPST_GROUP_DESC stats request message.
struct Stats_req_group_desc : Stats_payload_base<STATS_GROUP_DESC> { };


// -------------------------------------------------------------------------- //
// Stats Request: Group features

/// Group features statistics
///
/// \remark Implements an OFPST_GROUP_FEATURES stats request message.
struct Stats_req_group_features
  : Stats_payload_base<STATS_GROUP_FEATURES> { };


// -------------------------------------------------------------------------- //
// Stats Request: Experimenter

/// Experimenter statistics
///
/// \remark Implements an OFPST_EXPERIMENTER stats request message.
struct Stats_req_experimenter : Stats_payload_base<STATS_EXPERIMENTER>
{
  Stats_req_experimenter() = default;
  Stats_req_experimenter(uint32_t eid, uint32_t et, Greedy_buffer data)
  : experimenter_id(eid), exp_type(et), data(data) { }

  uint32_t experimenter_id;
  uint32_t exp_type;
  Greedy_buffer data;
};

// Equality comparison
bool operator==(const Stats_req_experimenter& a, const Stats_req_experimenter& b);
bool operator!=(const Stats_req_experimenter& a, const Stats_req_experimenter& b);

// Bytes
std::size_t bytes(const Stats_req_experimenter& e);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_req_experimenter& e);
Error_condition from_buffer(Buffer_view& v, Stats_req_experimenter& e);

std::string to_string(const Stats_req_experimenter&,  Formatter&);


// -------------------------------------------------------------------------- //
// Stats Request: Payload

union Stats_req_payload_data
{
  Stats_req_payload_data() { }
  ~Stats_req_payload_data() { }

  Stats_req_desc           desc;
  Stats_req_flow           flow;
  Stats_req_aggregate      aggregate;
  Stats_req_table          table;
  Stats_req_port           port;
  Stats_req_queue          queue;
  Stats_req_group          group;
  Stats_req_group_desc     group_desc;
  Stats_req_group_features group_features;
  Stats_req_experimenter   experimenter;
};

/// Describe the payload of a Stats Request message. The payload is a variant
/// that can be any type of Stats Request struct.
struct Stats_req_payload
{
  using Data = Stats_req_payload_data;

  Stats_req_payload() : init(false) { }

  explicit operator bool() const { return init; }

  // Mutators
  void initialize(Stats_type t);

  bool init;
  Data data;
};

void construct(Stats_req_payload&, Stats_type);
void construct(Stats_req_payload&, Stats_req_payload&&, Stats_type);
void construct(Stats_req_payload&, const Stats_req_payload&, Stats_type);

template<typename Tag, typename... Args>
  void construct(Stats_req_payload& p, Tag t, Args&&... args) = delete;

Stats_req_payload& assign(Stats_req_payload&, Stats_req_payload&&, Stats_type);
Stats_req_payload& assign(Stats_req_payload&, const Stats_req_payload&, Stats_type);

void destroy(Stats_req_payload&, Stats_type);

bool equal(const Stats_req_payload&, const Stats_req_payload&, Stats_type, Stats_type);

std::size_t bytes(const Stats_req_payload&, Stats_type);
Error_condition is_valid(const Stats_req_payload&, Stats_type);

Error_condition to_buffer(Buffer_view&, const Stats_req_payload&, Stats_type);
Error_condition from_buffer(Buffer_view&, Stats_req_payload&, Stats_type);

std::string to_string(const Stats_req_payload&, Stats_type);


// -------------------------------------------------------------------------- //
// Stats Header

/// Describe the header of a Stats Request message
///
/// Defined in [OpenFlow v1.2, p50]
struct Stats_header
{
  enum Flag_type : uint16_t
  {
    MORE = 0x01
  };

  Stats_header() = default;
  Stats_header(Stats_type t, Flag_type f)
  : type(t), flags(f) { }

  template<typename T>
    Stats_header(const T& value)
    : type(T::kind), flags() { }

  template<typename T, typename = typename T::Tag>
    explicit Stats_header(const T& x) : type(kind_of(x)), flags() { }
  
  Stats_type type;
  Flag_type flags;
};

// Equality comparable
bool operator==(const Stats_header& a, const Stats_header& b);
bool operator!=(const Stats_header& a, const Stats_header& b);

// Bytes
std::size_t bytes(const Stats_header& h);

// Is valid
Error_condition is_valid(const Stats_header& h);

// To/from buffer
Error_condition to_buffer(Buffer_view& v, const Stats_header& h);
Error_condition from_buffer(Buffer_view& v, Stats_header& h);

// To string
std::string to_string(const Stats_header& h,  Formatter&);
std::string to_string(Stats_header::Flag_type);



// -------------------------------------------------------------------------- //
// Stats Request

/// The Stats Request message is sent by the controller to the switch to obtain
/// the state of the switch. 
/// 
/// \remark Defined in [OpenFlow v1.2 p50-57]
struct Stats_req : Payload_base<STATS_REQ>
{
  using Header = Stats_header;
  using Payload = Stats_req_payload;

  /// Construct an empty Stats_req message
  Stats_req() = default;
  ~Stats_req();

  // Move semantics
  Stats_req(Stats_req&&);
  Stats_req& operator=(Stats_req&&);

  // Copy semantics
  Stats_req(const Stats_req&);
  Stats_req& operator=(const Stats_req&);
  
  template<typename T, typename Tag = typename T::Tag>
    explicit Stats_req(T&& x)
      : header(x) { construct(payload, Tag(), std::forward<T>(x)); }

  /// Construct a Stats_req message with payload
  template<typename Tag, typename... Args>
    Stats_req(Tag t, Args&&... args)
      : header(t.value) { construct(payload, t, std::forward<Args>(args)...); }

  Header  header;
  Payload payload;
};

/// Returns true when two Stats_req are totally equal. 
///
/// \relates Stats_req
bool operator==(const Stats_req& a, const Stats_req& b);

/// Returns true when two Stats_req structs do not compare equal.
///
/// \relates Stats_req
bool operator!=(const Stats_req& a, const Stats_req& b);

/// Return number of bytes of an Stats_req message.
///
/// \relates Stats_req
std::size_t bytes(const Stats_req& r);

/// Validates the value of a Stats_req message. 
///
/// \relates Stats_req
Error_condition is_valid(const Stats_req& r);

/// Writes a Stats_req message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Stats_req
Error_condition to_buffer(Buffer_view& v, const Stats_req& r);

/// Reads a Stats_req message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Stats_req
Error_condition from_buffer(Buffer_view& v, Stats_req& r);

/// Returns a formatted string representation of Stats_req.
///
/// \relates Stats_req
std::string to_string(const Stats_req& r,  Formatter&);


// -------------------------------------------------------------------------- //
// Stats response type

enum Stats_res_flag : uint16_t
{
  STATS_RES_REPLY_MORE = 1
};


// -------------------------------------------------------------------------- //
// Stats Response: Desc

/// Description of this OpenFlow switch
///
/// \remark Implements an OFPST_DESC Stats Response message
struct Stats_res_desc : Stats_payload_base<STATS_DESC>
{
  static constexpr std::size_t DESC_STR_LEN   = 256;
  static constexpr std::size_t SERIAL_NUM_LEN = 32;

  using Desc_string = Stringbuf<DESC_STR_LEN>;
  using Serial_string = Stringbuf<SERIAL_NUM_LEN>;

  Stats_res_desc() = default;
  Stats_res_desc(const char* m, const char* h, const char* s, const char* sn,
                 const char* d)
  : mfr_desc(m), hw_desc(h), sw_desc(s), serial_num(sn), dp_desc(d) { }

  Desc_string   mfr_desc;
  Desc_string   hw_desc;
  Desc_string   sw_desc;
  Serial_string serial_num;
  Desc_string   dp_desc;
};

// Equality comparison
bool operator==(const Stats_res_desc& a, const Stats_res_desc& b);
bool operator!=(const Stats_res_desc& a, const Stats_res_desc& b);

// Bytes
std::size_t bytes(const Stats_res_desc& d);

// Is valid
Error_condition is_valid(const Stats_res_desc& d);

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_desc&);
Error_condition from_buffer(Buffer_view&, Stats_res_desc&);
std::string to_string(const Stats_res_desc&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Flow

/// Implements stats of each individual flow in an OFPST_FLOW Stats Response 
/// message.
struct Stats_res_flow
{
  Stats_res_flow() = default;
  Stats_res_flow(uint16_t l, uint8_t tid, uint32_t ds, uint32_t dn,
                 uint16_t p, uint16_t it, uint16_t ht, uint64_t c,
                 uint64_t pc, uint64_t bc, const Match& m,
                 const Sequence<Instruction>& i)
  : length(l), table_id(tid), duration_sec(ds), duration_nsec(dn),
    priority(p), idle_timeout(it), hard_timeout(ht), cookie(c),
    packet_count(pc), byte_count(bc), match(m), instructions(i) { }

  uint16_t length;
  uint8_t table_id;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  uint16_t priority;
  uint16_t idle_timeout;
  uint16_t hard_timeout;
  uint64_t cookie;
  uint64_t packet_count;
  uint64_t byte_count;
  Match match;
  Sequence<Instruction> instructions;
};

// Equality comparison
bool operator==(const Stats_res_flow& a, const Stats_res_flow& b);
bool operator!=(const Stats_res_flow& a, const Stats_res_flow& b);

// Bytes
std::size_t bytes(const Stats_res_flow& f);

// Is valid
Error_condition is_valid(const Stats_res_flow& f);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_flow&);
Error_condition from_buffer(Buffer_view& v, Stats_res_flow&);

std::string to_string(const Stats_res_flow&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Flows

/// Individual flow statistics.
///
/// \remark Implements an OFPST_FLOW Stats Response message
struct Stats_res_flows : Stats_payload_base<STATS_FLOW>
{
  Stats_res_flows() = default;
  explicit Stats_res_flows(Sequence<Stats_res_flow> f)
  : flows(f) { }

  Sequence<Stats_res_flow> flows;
};

bool operator==(const Stats_res_flows& a, const Stats_res_flows& b);
bool operator!=(const Stats_res_flows& a, const Stats_res_flows& b);

// Bytes
std::size_t bytes(const Stats_res_flows& f);

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_flows&);
Error_condition from_buffer(Buffer_view&, Stats_res_flows&);

std::string to_string(const Stats_res_flows&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Aggregate

/// Aggregate flow statistics.
///
/// \remark Implements an OFPST_AGGREGATE Stats Response message
struct Stats_res_aggregate : Stats_payload_base<STATS_AGGREGATE>
{
  Stats_res_aggregate() = default;
  Stats_res_aggregate(uint64_t pc, uint64_t bc, uint32_t fc)
  : packet_count(pc), byte_count(bc), flow_count(fc) { }

  uint64_t packet_count;
  uint64_t byte_count;
  uint32_t flow_count;
};

// Equality comparison
bool operator==(const Stats_res_aggregate& a, const Stats_res_aggregate& b);
bool operator!=(const Stats_res_aggregate& a, const Stats_res_aggregate& b);

// Bytes
std::size_t bytes(const Stats_res_aggregate&);

// Is valid
Error_condition is_valid(const Stats_res_aggregate& a);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_aggregate& s);
Error_condition from_buffer(Buffer_view& v, Stats_res_aggregate& s);

std::string to_string(const Stats_res_aggregate&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Port

/// Implements stats of each individual port an OFPST_PORT Stats Response
/// message
struct Stats_res_port
{
  Stats_res_port() = default;
  Stats_res_port(uint32_t pn, uint64_t rp, uint64_t tp, uint64_t rb,
                 uint64_t tb, uint64_t rd, uint64_t td, uint64_t re,
                 uint64_t te, uint64_t rfe, uint64_t roe, uint64_t rce,
                 uint64_t c)
  : port_no(pn), rx_packets(rp), tx_packets(tp), rx_bytes(rb), tx_bytes(tb),
    rx_dropped(rd), tx_dropped(td), rx_errors(re), tx_errors(te),
    rx_frame_err(rfe), rx_over_err(roe), rx_crc_err(rce), collisions(c) { }


  uint32_t port_no;
  uint64_t rx_packets;
  uint64_t tx_packets;
  uint64_t rx_bytes;
  uint64_t tx_bytes;
  uint64_t rx_dropped;
  uint64_t tx_dropped;
  uint64_t rx_errors;
  uint64_t tx_errors;
  uint64_t rx_frame_err;
  uint64_t rx_over_err;
  uint64_t rx_crc_err;
  uint64_t collisions;
};


// Equality comparison
bool operator==(const Stats_res_port& a, const Stats_res_port& b);
bool operator!=(const Stats_res_port& a, const Stats_res_port& b);

// Bytes
std::size_t bytes(const Stats_res_port&);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_port& p);
Error_condition from_buffer(Buffer_view& v, Stats_res_port& p);

std::string to_string(const Stats_res_port& p, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Ports

/// Port statistics
///
/// \remark Implements an OFPST_PORT Stats Response message
struct Stats_res_ports : Stats_payload_base<STATS_PORT>
{
  Stats_res_ports() = default;
  explicit Stats_res_ports(Sequence<Stats_res_port> p)
  : ports(p) { }

  Sequence<Stats_res_port> ports;
};

bool operator==(const Stats_res_ports& a, const Stats_res_ports& b);
bool operator!=(const Stats_res_ports& a, const Stats_res_ports& b);

// Bytes
std::size_t bytes(const Stats_res_ports& p);

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_ports&);
Error_condition from_buffer(Buffer_view&, Stats_res_ports&);

std::string to_string(const Stats_res_ports&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Queue

/// Describe stats of each individual queue in an OFPST_QUEUE Stats Response 
/// message.
struct Stats_res_queue
{
  Stats_res_queue() = default;
  Stats_res_queue(uint32_t pn, uint32_t qid, uint64_t tb, uint64_t tp,
                  uint64_t te)
   : port_no(pn), queue_id(qid), tx_bytes(tb), tx_packets(tp), tx_errors(te) { }

  uint32_t port_no;
  uint32_t queue_id;
  uint64_t tx_bytes;
  uint64_t tx_packets;
  uint64_t tx_errors;
};

// Equality comparison
bool operator==(const Stats_res_queue& a, const Stats_res_queue& b);
bool operator!=(const Stats_res_queue& a, const Stats_res_queue& b);

// Bytes
std::size_t bytes(const Stats_res_queue&);

// is_valid
Error_condition is_valid(const Stats_res_queue&);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_queue& q);
Error_condition from_buffer(Buffer_view& v, Stats_res_queue& q);

std::string to_string(const Stats_res_queue&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Queues

/// Queue statistics for a port
///
/// \remark Implements an OFPST_QUEUE Stats Response message
struct Stats_res_queues : Stats_payload_base<STATS_QUEUE>
{
  Stats_res_queues() = default;
  explicit Stats_res_queues(Sequence<Stats_res_queue> q)
  : queues(q) { }

  Sequence<Stats_res_queue> queues;
};

bool operator==(const Stats_res_queues& a, const Stats_res_queues& b);
bool operator!=(const Stats_res_queues& a, const Stats_res_queues& b);

// Bytes
std::size_t bytes(const Stats_res_queues& q);

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_queues&);
Error_condition from_buffer(Buffer_view&, Stats_res_queues&);

std::string to_string(const Stats_res_queues&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Table

/// Describe stats of each individual table in an OFPST_TABLE Stats Response 
/// message.
struct Stats_res_table
{
  static constexpr std::size_t NAME_STR_LEN = 32;

  using Name_string = Stringbuf<NAME_STR_LEN>;

  Stats_res_table() = default;
  Stats_res_table(uint8_t tid, const char* n, uint32_t m, uint32_t w,
                  uint32_t wa, uint32_t aa, uint64_t ws, uint64_t as,
                  uint64_t mm, uint64_t mw, uint32_t i, uint32_t c,
                  uint32_t me, uint32_t ac, uint64_t lc, uint64_t mc)
  : table_id(tid), match(m), wildcards(w), write_actions(wa),
    apply_actions(aa), write_setfields(ws), apply_setfields(as),
    metadata_match(mm), metadata_write(mw), instructions(i), config(c),
    max_entries(me), active_count(ac), lookup_count(lc), matched_count(mc)
  { }

  uint8_t table_id;
  Name_string name;
  uint64_t match;
  uint64_t wildcards;
  uint32_t write_actions;
  uint32_t apply_actions;
  uint64_t write_setfields;
  uint64_t apply_setfields;
  uint64_t metadata_match;
  uint64_t metadata_write;
  uint32_t instructions;
  uint32_t config;
  uint32_t max_entries;
  uint32_t active_count;
  uint64_t lookup_count;
  uint64_t matched_count;
};

// Equality comparison
bool operator==(const Stats_res_table& a, const Stats_res_table& b);
bool operator!=(const Stats_res_table& a, const Stats_res_table& b);

// Bytes
std::size_t bytes(const Stats_res_table&);

// is_valid
Error_condition is_valid(const Stats_res_table&);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_table& t);
Error_condition from_buffer(Buffer_view& v, Stats_res_table& t);

std::string to_string(const Stats_res_table&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Tables

/// Flow table statistics
///
/// \remark Implements an OFPST_TABLE Stats Response message
struct Stats_res_tables : Stats_payload_base<STATS_TABLE>
{
  Stats_res_tables() = default;
  explicit Stats_res_tables(Sequence<Stats_res_table> t)
  : tables(t) { }

  Sequence<Stats_res_table> tables;
};

bool operator==(const Stats_res_tables& a, const Stats_res_tables& b);
bool operator!=(const Stats_res_tables& a, const Stats_res_tables& b);

// Bytes
std::size_t bytes(const Stats_res_tables& t); 

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_tables&);
Error_condition from_buffer(Buffer_view&, Stats_res_tables&);

std::string to_string(const Stats_res_tables&, Formatter&);

// -------------------------------------------------------------------------- //
// Stats Response: Group

/// Describe stats of an individual group in an OFPST_GROUP Stats Response
/// message.
struct Stats_res_group
{
  Stats_res_group() = default;
  Stats_res_group(uint16_t l, uint32_t gid, uint32_t rc, uint64_t pc,
                  uint64_t bc, const Sequence<Bucket_counter>& bs)
  : length(l), group_id(gid), ref_count(rc), packet_count(pc),
    byte_count(bc), bucket_stats(bs) { }

  uint16_t length;
  uint32_t group_id;
  uint32_t ref_count;
  uint64_t packet_count;
  uint64_t byte_count;
  Sequence<Bucket_counter> bucket_stats;
};

// Equality comparison
bool operator==(const Stats_res_group& a, const Stats_res_group& b);
bool operator!=(const Stats_res_group& a, const Stats_res_group& b);

std::size_t bytes(const Stats_res_group& g);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_group& g);
Error_condition from_buffer(Buffer_view& v, Stats_res_group& g);

std::string to_string(const Stats_res_group&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Groups

/// Group counter statistics
///
/// \remark Implements an OFPST_GROUP Stats Response message
struct Stats_res_groups : Stats_payload_base<STATS_GROUP>
{
  Stats_res_groups() = default;
  explicit Stats_res_groups(Sequence<Stats_res_group> gd): groups(gd) { }

  Sequence<Stats_res_group> groups;
};

bool operator==(const Stats_res_groups& a, const Stats_res_groups& b);
bool operator!=(const Stats_res_groups& a, const Stats_res_groups& b);

// Bytes
std::size_t bytes(const Stats_res_groups& gd);

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_groups&);
Error_condition from_buffer(Buffer_view&, Stats_res_groups&);

std::string to_string(const Stats_res_groups&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Group desc

/// Describe stats of an individual group in an OFPST_GROUP Stats Response
/// message.
struct Stats_res_group_desc
{
  Stats_res_group_desc() = default;
  Stats_res_group_desc(uint16_t l, uint8_t t, uint32_t gid,
                       const Sequence<Bucket>& b)
  : length(l), type(t), group_id(gid), buckets(b) { }

  uint16_t length;
  uint8_t type;
  uint32_t group_id;
  Sequence<Bucket> buckets;
};

// Equality comparison
bool operator==(const Stats_res_group_desc& a, const Stats_res_group_desc& b);
bool operator!=(const Stats_res_group_desc& a, const Stats_res_group_desc& b);

std::size_t bytes(const Stats_res_group_desc& gd);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_group_desc& gd);
Error_condition from_buffer(Buffer_view& v, Stats_res_group_desc& dg);
std::string to_string(const Stats_res_group_desc&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Group descs

/// Group description statistics
///
/// \remark: Implements an OFPST_GROUP_DESC Stats Response messge
struct Stats_res_group_descs : Stats_payload_base<STATS_GROUP_DESC>
{
  Stats_res_group_descs() = default;
  explicit Stats_res_group_descs(Sequence<Stats_res_group_desc> gd)
  : group_descs(gd){ }

  Sequence<Stats_res_group_desc> group_descs;
};

bool operator==(const Stats_res_group_descs& a, const Stats_res_group_descs& b);
bool operator!=(const Stats_res_group_descs& a, const Stats_res_group_descs& b);

// Bytes
std::size_t bytes(const Stats_res_group_descs& gd);

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_group_descs&);
Error_condition from_buffer(Buffer_view&, Stats_res_group_descs&);

std::string to_string(const Stats_res_group_descs&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Group features

/// Group features statistics
///
/// \remark: Implements an OFPST_GROUP_FEATURES Stats Response messge
struct Stats_res_group_features
  : Stats_payload_base<STATS_GROUP_FEATURES>
{
  enum Capabilities_type : uint32_t
  {
    SELECT_WEIGHT = 0x0001, SELECT_LIVENESS = 0x0010,
    CHAINING = 0x0100, CHAINING_CHECKS = 0x1000
  };

  Stats_res_group_features() = default;
  Stats_res_group_features(uint32_t t, Capabilities_type c, uint32_t mga, 
                           uint32_t mgs, uint32_t mgi, uint32_t mgf, 
                           uint32_t aa, uint32_t as, uint32_t ai, uint32_t af)
  : types(t), capabilities(c), max_groups_all(mga), max_groups_select(mgs),
    max_groups_indirect(mgi), max_groups_ff(mgf), actions_all(aa),
    actions_select(as), actions_indirect(ai), actions_ff(af) { }

  uint32_t types;
  Capabilities_type capabilities;
  uint32_t max_groups_all;
  uint32_t max_groups_select;
  uint32_t max_groups_indirect;
  uint32_t max_groups_ff;
  uint32_t actions_all;
  uint32_t actions_select;
  uint32_t actions_indirect;
  uint32_t actions_ff;
};

// Equality comparison
bool operator==(const Stats_res_group_features& a,
                const Stats_res_group_features& b);

bool operator!=(const Stats_res_group_features& a,
                const Stats_res_group_features& b);

std::size_t bytes(const Stats_res_group_features);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_group_features& gd);
Error_condition from_buffer(Buffer_view& v, Stats_res_group_features& dg);

std::string to_string(const Stats_res_group_features&, Formatter&);

bool capabilities_select_weight(Stats_res_group_features::Capabilities_type ct);

bool capabilities_select_liveness(Stats_res_group_features::Capabilities_type ct);

bool capabilities_chaining(Stats_res_group_features::Capabilities_type ct);

bool capabilities_chaining_checks(Stats_res_group_features::Capabilities_type ct);


// -------------------------------------------------------------------------- //
// Stats Response: Experimenter

/// Experiimenter statistics
///
/// \remark Implements an OFPST_EXPERIMENTER Stats Response messge
struct Stats_res_experimenter : Stats_payload_base<STATS_EXPERIMENTER>
{
  Stats_res_experimenter() = default;
  Stats_res_experimenter(uint32_t eid, uint32_t et, Greedy_buffer dt)
  : experimenter_id(eid), exp_type(et), data(dt) { }

  uint32_t experimenter_id;
  uint32_t exp_type;
  Greedy_buffer data;
};


// Equality comparison
bool operator==(const Stats_res_experimenter& a, const Stats_res_experimenter& b);
bool operator!=(const Stats_res_experimenter& a, const Stats_res_experimenter& b);

// Bytes
std::size_t bytes(const Stats_res_experimenter& e);

// is_valid
Error_condition is_valid(const Stats_res_experimenter&);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res_experimenter& e);
Error_condition from_buffer(Buffer_view& v, Stats_res_experimenter& e);

std::string to_string(const Stats_res_experimenter&,  Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Payload

union Stats_res_payload_data
{
  Stats_res_payload_data() { }
  ~Stats_res_payload_data() { }

  Stats_res_desc           desc;
  Stats_res_flows          flow;
  Stats_res_aggregate      aggregate;
  Stats_res_tables         table;
  Stats_res_ports          port;
  Stats_res_queues         queue;
  Stats_res_groups         group;
  Stats_res_group_descs    group_desc;
  Stats_res_group_features group_features;
  Stats_res_experimenter   experimenter;
};

/// Describe the payload of a Stats Response message. The payload is a variant
/// that can be any type of Stats Response struct.
struct Stats_res_payload
{
  using Data = Stats_res_payload_data;

  Stats_res_payload() : init(false) { }

  explicit operator bool() const { return init; }

  // Mutators
  void initialize(Stats_type t);

  bool init;
  Data data;
};


void construct(Stats_res_payload&, Stats_type);
void construct(Stats_res_payload&, Stats_res_payload&&, Stats_type);
void construct(Stats_res_payload&, const Stats_res_payload&, Stats_type);

Stats_res_payload& assign(Stats_res_payload&, Stats_res_payload&&, Stats_type);
Stats_res_payload& assign(Stats_res_payload&, const Stats_res_payload&, Stats_type);

void destroy(Stats_res_payload&, Stats_type);

bool equal(const Stats_res_payload&, const Stats_res_payload&, Stats_type, Stats_type);

std::size_t bytes(const Stats_res_payload&, Stats_type);
Error_condition is_valid(const Stats_res_payload&, Stats_type);

Error_condition to_buffer(Buffer_view&, const Stats_res_payload&, Stats_type);
Error_condition from_buffer(Buffer_view&, Stats_res_payload&, Stats_type);

std::string to_string(const Stats_res_payload&, Stats_type);


// -------------------------------------------------------------------------- //
// Stats Response

/// Describe the header of a Stats Response message
struct Stats_res : Payload_base<STATS_RES>
{
  using Header = Stats_header;
  using Payload = Stats_res_payload;

  Stats_res() = default;
  ~Stats_res();

  // Move semantics
  Stats_res(Stats_res&&);
  Stats_res& operator=(Stats_res&&);

  // Copy semantics
  Stats_res(const Stats_res&);
  Stats_res& operator=(const Stats_res&);

  Header  header;
  Payload payload;
};

// Equality comparison
bool operator==(const Stats_res& a, const Stats_res& b);
bool operator!=(const Stats_res& a, const Stats_res& b);

// Bytes
std::size_t bytes(const Stats_res& r);

// Is valid
Error_condition is_valid(const Stats_res& r);

// To/from
Error_condition to_buffer(Buffer_view& v, const Stats_res& r);
Error_condition from_buffer(Buffer_view& v, Stats_res& r);

// To string
std::string to_string(const Stats_res& r,  Formatter&);


// -------------------------------------------------------------------------- //
// Barrier Request

/// The Barrier Request message is sent by the controller to the switch. Any 
/// message before the barrier request must be completed processing before
/// a Barrier Response is sent back to controller and before any message
/// that arrives later than the Barrier Request.
///
/// \remark Defined in [OpenFlow v1.2, p58]
struct Barrier_req : Payload_base<BARRIER_REQ> { };


// -------------------------------------------------------------------------- //
// Barrier Response

/// The Barrier Response message is sent by the switch to the controller as
/// response to a Barrier Request message. Any message before the barrier request
/// must be completed processing before a Barrier Response is sent back to
/// controller and before any message that arrives later than the Barrier Request.
///
/// \remark Defined in [OpenFlow v1.2, p58]
struct Barrier_res : Payload_base<BARRIER_RES> { };


// -------------------------------------------------------------------------- //
// Queue Get Config Request

/// The Queue Get Config Request is sent by the controller to the switch to
/// obtain configurations of the queues in the switch.
///
/// \remark defined in [OpenFlow v1.2, p57]
struct Queue_get_config_req : Payload_base<QUEUE_GET_CONFIG_REQ>
{
  /// Construct an empty Group_mod message
  Queue_get_config_req() = default;
  
  /// Construct a Group_mod message with value of all the fields
  explicit Queue_get_config_req(uint32_t p): port(p) { }

  uint32_t port;
};

/// Returns true when two Queue_get_config_req are totally equal. 
///
/// \relates Queue_get_config_req
bool operator==(const Queue_get_config_req& a, const Queue_get_config_req& b);

/// Returns true when two Queue_get_config_req structs do not compare equal.
///
/// \relates Queue_get_config_req
bool operator!=(const Queue_get_config_req& a, const Queue_get_config_req& b);

/// Return number of bytes of an Queue_get_config_req message.
///
/// \relates Queue_get_config_req
std::size_t bytes(const Queue_get_config_req&);

/// Validates the value of a Queue_get_config_req message. 
///
/// \relates Queue_get_config_req
Error_condition is_valid(const Queue_get_config_req& q);

/// Writes a Queue_get_config_req message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Queue_get_config_req
Error_condition to_buffer(Buffer_view&, const Queue_get_config_req&);

/// Reads a Queue_get_config_req message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Queue_get_config_req
Error_condition from_buffer(Buffer_view&, Queue_get_config_req&);

/// Returns a formatted string representation of Queue_get_config_req.
///
/// \relates Queue_get_config_req
std::string to_string(const Queue_get_config_req&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue Get Config Response

/// The Queue Get Config Response message is sent by the switch to the
/// controller as response to a Queue Get Config Request message. It contains
/// the configuration information of queues associated with the port 
/// specified in the Queue Get Config Request message.
/// 
/// \remark Defined in [OpenFlow v1.2, p57]
struct Queue_get_config_res : Payload_base<QUEUE_GET_CONFIG_RES>
{
  /// Construct an empty Queue_get_config_res message
  Queue_get_config_res() = default;
  
  /// Construct a Queue_get_config_res message with value of all the fields
  Queue_get_config_res(uint32_t p, Sequence<Queue> q)
  : port(p), queues(q) { }

  uint32_t port;
  Sequence<Queue> queues;
};

/// Returns true when two Queue_get_config_res are totally equal. 
///
/// \relates Queue_get_config_res
bool operator==(const Queue_get_config_res& a, const Queue_get_config_res& b);

/// Returns true when two Queue_get_config_res structs do not compare equal.
///
/// \relates Queue_get_config_res
bool operator!=(const Queue_get_config_res& a, const Queue_get_config_res& b);

/// Return number of bytes of an Queue_get_config_res message.
///
/// \relates Queue_get_config_res
std::size_t bytes(const Queue_get_config_res& qgcr);

/// Writes a Queue_get_config_res message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Queue_get_config_res
Error_condition to_buffer(Buffer_view&, const Queue_get_config_res&);

/// Reads a Queue_get_config_res message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Queue_get_config_res
Error_condition from_buffer(Buffer_view&, Queue_get_config_res&);

/// Returns a formatted string representation of Queue_get_config_res.
///
/// \relates Queue_get_config_res
std::string to_string(const Queue_get_config_res&, Formatter&);


// -------------------------------------------------------------------------- //
// Role enum

enum Role : uint32_t {
  R_NO_CHANGE = 0x00000000, R_EQUAL = 0x00000001, R_MASTER = 0x00000002,
  R_SLAVE = 0x00000003
};

Error_condition is_valid(const Role t);

std::string to_string(const Role);


// -------------------------------------------------------------------------- //
// Role Base

template <Message_type K>
  struct Role_base : Payload_base<K>
  {
    Role_base() = default;
    Role_base(Role r, uint64_t gid) 
      : role(r), generation_id(gid) 
    { }

    Role role;
    uint64_t generation_id;
  };

// Equality comparison
template <Message_type K>
  bool operator==(const Role_base<K>& a, const Role_base<K>& b);

template <Message_type K>
  bool operator!=(const Role_base<K>& a, const Role_base<K>& b);

// Bytes
template <Message_type K>
  std::size_t bytes(const Role_base<K>&);

// Is valid
template <Message_type K>
  Error_condition is_valid(const Role_base<K>& rb);

template <Message_type K>
  Error_condition to_buffer(Buffer_view& v, const Role_base<K>& rb);

template <Message_type K>
  Error_condition from_buffer(Buffer_view& v, Role_base<K>& rb);


// -------------------------------------------------------------------------- //
// Role Req

struct Role_req : Role_base<ROLE_REQ> { };

std::string to_string(const Role_req&, Formatter&);


// -------------------------------------------------------------------------- //
// Role Res

struct Role_res : Role_base<ROLE_RES> { };

std::string to_string(const Role_res&, Formatter&);


// -------------------------------------------------------------------------- //
// Payload

union Payload_data
{
  Payload_data() { }
  Payload_data(Payload_data&&) { }
  ~Payload_data() { }
    
  Hello                hello;
  Error                error;
  Echo_req             echo_req;
  Echo_res             echo_res;
  Experimenter         experimenter;
  Flow_mod             flow_mod;
  Feature_req          feature_req;
  Feature_res          feature_res;
  Get_config_req       get_config_req;
  Get_config_res       get_config_res;
  Set_config           set_config;
  Packet_in            packet_in;
  Flow_removed         flow_removed;
  Port_status          port_status;
  Packet_out           packet_out;
  Group_mod            group_mod;
  Port_mod             port_mod;
  Table_mod            table_mod;
  Stats_req            stats_req;
  Stats_res            stats_res;
  Barrier_req          barrier_req;
  Barrier_res          barrier_res;
  Queue_get_config_req queue_get_config_req;
  Queue_get_config_res queue_get_config_res;
  Role_req             role_req;
  Role_res             role_res;
};

/// Describe the payload of an OpenFlow v1.1 message. An OpenFlow v1.1 Message
/// consists of a header and a payload. The payload is a variant
/// that can be any type of OpenFlow v1.1 message struct.
struct Payload
{
  using Data = Payload_data;

  Payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;  ///< True when initialized
  Data data;  ///< The underlying data
};

/// Construct an empty payload of given type of message.
void construct(Payload&, Message_type);

/// Construct a payload by copying another Message payload of given type.
void construct(Payload&, Payload&&, Message_type);

/// Construct a payload by copying another Message payload of given type.
void construct(Payload&, const Payload&, Message_type);

/// Construct a payload with the given arguments. The Tag argument, t,
/// must be of the form M::Tag where M is a messaage class in this
/// implementation. The arguments args, must conform to a constructor
/// of the class M.
template<typename Tag, typename... Args>
  void construct(Payload& p, Tag t, Args&&... args) = delete;

Payload& assign(Payload&, Payload&&, Message_type);
Payload& assign(Payload&, const Payload&, Message_type);

/// Destroy the current payload.
void destroy(Payload&, Message_type);

bool equal(const Payload&, const Payload&, Message_type, Message_type);

/// Return number of bytes of a Payload.
std::size_t bytes(const Payload&, Message_type);

/// Validate the value of a Payload.
Error_condition is_valid(const Payload&, Message_type);

/// Writes a Payload into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
Error_condition to_buffer(Buffer_view&, const Payload&, Message_type);

/// Reads a Payload message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
Error_condition from_buffer(Buffer_view&, Payload&, Message_type);

/// Returns a formatted string representation of Payload.
std::string to_string(const Payload&, Formatter&, Message_type);

// Is payload
template<typename T> struct is_payload : std::false_type { };
template<typename T> struct is_payload<T&> : is_payload<T> { };
template<typename T> struct is_payload<const T> : is_payload<T> { };
template<> struct is_payload<Hello> : std::true_type { };
template<> struct is_payload<Error> : std::true_type { };
template<> struct is_payload<Echo_req> : std::true_type { };
template<> struct is_payload<Echo_res> : std::true_type { };
template<> struct is_payload<Experimenter> : std::true_type { };
template<> struct is_payload<Feature_req> : std::true_type { };
template<> struct is_payload<Feature_res> : std::true_type { };
template<> struct is_payload<Get_config_req> : std::true_type { };
template<> struct is_payload<Get_config_res> : std::true_type { };
template<> struct is_payload<Set_config> : std::true_type { };
template<> struct is_payload<Packet_in> : std::true_type { };
template<> struct is_payload<Flow_removed> : std::true_type { };
template<> struct is_payload<Port_status> : std::true_type { };
template<> struct is_payload<Packet_out> : std::true_type { };
template<> struct is_payload<Flow_mod> : std::true_type { };
template<> struct is_payload<Group_mod> : std::true_type { };
template<> struct is_payload<Port_mod> : std::true_type { };
template<> struct is_payload<Table_mod> : std::true_type { };
template<> struct is_payload<Stats_req> : std::true_type { };
template<> struct is_payload<Stats_res> : std::true_type { };
template<> struct is_payload<Barrier_req> : std::true_type { };
template<> struct is_payload<Barrier_res> : std::true_type { };
template<> struct is_payload<Queue_get_config_req> : std::true_type { };
template<> struct is_payload<Queue_get_config_res> : std::true_type { };
template<> struct is_payload<Role_req> : std::true_type { };
template<> struct is_payload<Role_res> : std::true_type { };

template<typename T>
  struct enable_if_payload : std::enable_if<is_payload<T>::value> { };

/// Describe the header of an OpenFlow v1.2 Message. Every OpenFlow
/// message begins with a fixed-sized header. This header describes the
/// OpenFlow protocol version, the type of message, the length in bytes
/// (inclusive of the header), and the transaction id (used to match
/// responses to requests).
///
/// \remark Defined in [OpenFlow v1.2, p27]
struct Header
{
  /// Construct an emtpy Message header
  Header() = default;
  
  /// Construct a Message header with given Message_type
  Header(Message_type t)
    : version(VERSION), type(t) { }
  
  /// Consstruct a Message header with given Message_type, length and
  /// xid
  Header(Message_type t, uint16_t l, uint32_t id)
    : version(VERSION), type(t), length(l), xid(id) { }
  
  /// Construct a Message header with values of all fields
  Header(Version_type v, Message_type t, uint16_t l, uint32_t id)
    : version(v), type(t), length(l), xid(id) { }

  template<typename T, typename = typename T::Tag>
    explicit Header(const T& x)
      : version(VERSION), type(kind_of(x)), length(8+bytes(x)) {}

  template<typename T, typename = typename T::Tag>
    Header(const T& x, uint32_t id)
      : version(VERSION), type(kind_of(x)), length(8 + bytes(x)), xid(id) { }

  template<typename T>
    Header(const T& value, uint32_t id)
    : version(VERSION), type(T::kind), length(8 + bytes(value)), xid(id) { }

  Version_type version;
  Message_type type;
  uint16_t length;
  uint32_t xid;
};

/// Compares two Header's. Return true if all fields of a and b are the
/// same.
bool operator==(const Header& a, const Header& b);

/// Compares two Header's. Return true if a and b are not the same
bool operator!=(const Header& a, const Header& b);

/// Return number of bytes of the header
std::size_t bytes(const Header&);

/// Validates the value of a Group_mod message. 
Error_condition is_valid(const Header& h);

/// Writes a Header into a Buffer_view. If the write does not succeed, the
/// result will containt a code representing the specific cause of
/// failure.
Error_condition to_buffer(Buffer_view& buf, const Header& h);

/// Reads a Header from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause 
/// of failure.
Error_condition from_buffer(Buffer_view& buf, Header& h);

/// Returns a formatted string representation of Group_mod.
std::string to_string(const Header& h, Formatter&);


// -------------------------------------------------------------------------- //
// Message
//

/// Describe an OpenFlow v1.2 message. Every message consists of a
/// header and a payload. The type of payload is determined by the
/// value of the header.
struct Message
{
  /// Construct an empty Message
  Message() = default;

  //static Message* mk_hello(uint32_t sv);
  //static Message* mk_hello_failed();

  /// Move semantics
  Message(Message&&);
  
  /// Move semantics
  Message& operator=(Message&&);

  /// Copy semantics
  Message(const Message&);
  
  /// Copy semantics
  Message& operator=(const Message&);

  /// Payload construction
  template<typename T, typename = typename enable_if_payload<T>::type>
    explicit Message(T&&);

  /// Payload construction
  template<typename T, typename = typename enable_if_payload<T>::type>
    Message(T&&, uint32_t id);

  //void construct_hello();

  /// Payload construction
  template<typename Tag, typename... Args>
    Message(uint32_t id, Tag t, Args&&... args);
  
  ~Message();
   
  /// Return a factory that generates OpenFlow v1.2 message
  static Factory factory(Xid_generator<uint32_t>& gen) { return Factory(gen); } 

  Header  header;
  Payload payload;
};

/// Compares two Message's. Returns true when two Messages are equal. 
bool operator==(const Message& a, const Message& b);

/// Compares two Message's. Returns true when two Messages are not equal.
bool operator!=(const Message& a, const Message& b);

/// Return number of bytes of a Message.
std::size_t bytes(const Message& m);

/// Validates the value of a Message. 
Error_condition is_valid(const Message& m);

/// Writes a Message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
Error_condition to_buffer(Buffer_view&, const Message&);

/// Reads a Message from a Buffer_view. If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
Error_condition from_buffer(Buffer_view&, Message&);

/// Returns a formatted string representation of a Message.
std::string to_string(const Message&, Formatter&);


} // namespace v1_2
} // namespace ofp
} // namespace flog

#include "message.ipp"

#endif
