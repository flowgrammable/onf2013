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

#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_1_H
#define FLOWGRAMMABLE_PROTO_OFP_V1_1_H

#include <cassert>
#include <cstdint>
#include <string>
#include <sstream>

#include <libflog/utilities.hpp>
#include <libflog/buffer.hpp>
#include <libflog/message.hpp>
#include <libflog/sequence.hpp>
#include <libflog/proto/ofp/ofp.hpp>

#include "factory.hpp"

/// \file v1_1/message.hpp

namespace flog {
namespace ofp {
namespace v1_1 {

/// Ensure overload resolution for primitive types.
using ofp::to_buffer;
using ofp::from_buffer;


// -------------------------------------------------------------------------- //
// Error code

/// Represents a specific failure in message processing. This enumeration is
/// used to describe the result values of to_buffer(), from_buffer(), and
/// is_valid().
enum Error_code {
  FAILURE = -1,       ///< General failure
  SUCCESS = 0,        ///< Success

  // Basic codes (copied from Basic_error_code)
  AVAILABLE_BUFFER,        ///< Not enough bytes to read a buffer
  AVAILABLE_STRING,        ///< Not enough bytes to read a string

  EXCESS_SEQUENCE,         ///< Excess data in a sequence

  // Semantic codes (produced during validation)
  BAD_ACTION,              ///< Invalid value of Action_type
  BAD_ACTION_LENGTH,       ///< The action length is invalid
  BAD_ACTION_INIT,         ///< An uninitialized action was validated
  BAD_ACTION_ENQUEUE_PORT, ///< The port in Action_enqueue is invalid
  BAD_INSTRUCTION,         ///< Invalid value of Instruction_type
  BAD_INSTRUCTION_LENGTH,  ///< The instruction length is invalid
  BAD_INSTRUCTION_INIT,    ///< An uninitialized action was validated
  BAD_PORT_ID,             ///< The id in Port is invalid
  BAD_VERSION,             ///< The version number was not 1
  BAD_MESSAGE,             ///< Invalid vaue of Message_type
  BAD_MESSAGE_LENGTH,      ///< The header length is invalid
  BAD_MESSAGE_INIT,        ///< The message payload is not initialized
  BAD_HEADER_LENGTH,       ///< The header length is invalid
  BAD_ERROR_TYPE,          ///< Invalid value of Error::Type
  BAD_HELLO_FAILED,        ///< Invalid value of Error::Hello_failed
  BAD_BAD_REQUEST,         ///< Invalid value of Error::Bad_request
  BAD_BAD_ACTION,          ///< Invalid value of Error::Bad_action
  BAD_BAD_INSTRUCTION,     ///< Invalid value of Error::Bad_instruction
  BAD_BAD_MATCH,           ///< Invalid value of Error::Bad_match
  BAD_FLOW_MOD_FAILED,     ///< Invalid value of Error::Flow_mod_failed
  BAD_BUCKET_LENGTH,       ///< The Bucket length is invalid
  BAD_GROUP_MOD_FAILED,    ///< Invalid value of Error::Group_mod_failed
  BAD_PORT_MOD_FAILED,     ///< Invalid value of Error::Port_mod_failed
  BAD_TABLE_MOD_FAILED,    ///< Invalid value of Error::Table_mod_failed
  BAD_QUEUE_OP_FAILED,     ///< Invalid value of Error::Queue_op_failed
  BAD_SWITCH_CONFIG_FAILED,///< Invalid value of Error::Switch_config_failed
  BAD_CONFIG_FLAGS,        ///< Invalid value of flags in Get_config_res or Set_config
  BAD_FLOW_MOD_COMMAND,    ///< Invalid value of Flow_mod::Command
  BAD_FLOW_MOD_FLAGS,      ///< Invalid value of Flow_mod::Flags
  BAD_GROUP_MOD_COMMAND,   ///< Invalid value of Group_mod::Command
  BAD_GROUP_MOD_TYPE,      ///< Invalid value of Group_mod::Type
  BAD_TABLE_MOD_CONFIG,    ///< Invalid value of Group_mod::Config
  BAD_FEATURE_RES_CAPABILITY,
  BAD_PACKET_IN_REASON,
  BAD_FLOW_REMOVED_REASON,
  BAD_PORT_STATUS_REASON,
  BAD_PACKET_OUT_LENGTH,
  BAD_STATS,
  BAD_STATS_INIT,
  BAD_STATS_RES_GROUP_LENGTH,
  BAD_STATS_RES_GROUP_DESC_LENGTH,
  BAD_QUEUE_PROPERTY,      ///< Invalid value of Queue_property_type
  BAD_QUEUE_PROPERTY_LENGTH,
  BAD_QUEUE_PROPERTY_INIT,
  BAD_QUEUE_CONFIG_PORT,

  // Availability errors
  AVAILABLE_ACTION_OUTPUT,       ///< Not enough bytes for an Action_output
  AVAILABLE_ACTION_SET_VLAN_VID, ///< Not enough bytes for an Action_set_vlan_vid
  AVAILABLE_ACTION_SET_VLAN_PCP, ///< ...
  AVAILABLE_ACTION_SET_DL_SRC,
  AVAILABLE_ACTION_SET_DL_DST,
  AVAILABLE_ACTION_SET_NW_SRC,
  AVAILABLE_ACTION_SET_NW_DST,
  AVAILABLE_ACTION_SET_NW_TOS,
  AVAILABLE_ACTION_SET_NW_ECN,
  AVAILABLE_ACTION_SET_TP_SRC,
  AVAILABLE_ACTION_SET_TP_DST,
  AVAILABLE_ACTION_COPY_TTL_OUT,
  AVAILABLE_ACTION_COPY_TTL_IN,
  AVAILABLE_ACTION_SET_MPLS_LABEL,
  AVAILABLE_ACTION_SET_MPLS_TC,
  AVAILABLE_ACTION_SET_MPLS_TTL,
  AVAILABLE_ACTION_DEC_MPLS_TTL,
  AVAILABLE_ACTION_PUSH_VLAN,
  AVAILABLE_ACTION_POP_VLAN,
  AVAILABLE_ACTION_PUSH_MPLS,
  AVAILABLE_ACTION_POP_MPLS,
  AVAILABLE_ACTION_SET_QUEUE,
  AVAILABLE_ACTION_GROUP,
  AVAILABLE_ACTION_SET_NW_TTL,
  AVAILABLE_ACTION_DEC_NW_TTL,
  AVAILABLE_ACTION_EXPERIMENTER,
  AVAILABLE_ACTION_HEADER,
  AVAILABLE_ACTION_PAYLOAD,
  
  AVAILABLE_QUEUE_PROPERTY_NONE,
  AVAILABLE_QUEUE_PROPERTY_MIN_RATE,
  AVAILABLE_QUEUE_PROPERTY_HEADER,
  AVAILABLE_QUEUE_PROPERTY_PAYLOAD,
  AVAILABLE_QUEUE_PROPERTIES,
  AVAILABLE_QUEUE,
  
  AVAILABLE_INSTRUCTION_GOTO_TABLE,
  AVAILABLE_INSTRUCTION_WRITE_METADATA,
  AVAILABLE_INSTRUCTION_WRITE_ACTIONS,
  AVAILABLE_INSTRUCTION_APPLY_ACTIONS,
  AVAILABLE_INSTRUCTION_CLEAR_ACTIONS,
  AVAILABLE_INSTRUCTION_EXPERIMENTER,
  AVAILABLE_INSTRUCTION_HEADER,
  AVAILABLE_INSTRUCTION_PAYLOAD,
  AVAILABLE_INSTRUCTION,
  
  AVAILABLE_PORT,
  
  AVAILABLE_BUCKET,

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
  AVAILABLE_FLOW_REMOVED,
  AVAILABLE_PORT_STATUS,
  AVAILABLE_PACKET_OUT,
  AVAILABLE_FLOW_MOD,
  AVAILABLE_GROUP_MOD,
  AVAILABLE_PORT_MOD,
  AVAILABLE_TABLE_MOD,

  AVAILABLE_STATS_REQ_DESC,
  AVAILABLE_STATS_REQ_FLOW,
  AVAILABLE_STATS_REQ_AGGREGATE,
  AVAILABLE_STATS_REQ_TABLE,
  AVAILABLE_STATS_REQ_PORT,
  AVAILABLE_STATS_REQ_QUEUE,
  AVAILABLE_STATS_REQ_GROUP,
  AVAILABLE_STATS_REQ_GROUP_DESC,
  AVAILABLE_STATS_REQ_EXPERIMENTER,
  AVAILABLE_STATS_REQ,
  
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
  AVAILABLE_BUCKET_COUNTER,
  AVAILABLE_STATS_RES_GROUP,
  AVAILABLE_STATS_RES_GROUPS,
  AVAILABLE_STATS_RES_GROUP_DESC,
  AVAILABLE_STATS_RES_GROUP_DESCS,
  AVAILABLE_STATS_RES_EXPERIMENTER,
  AVAILABLE_STATS_RES,

  AVAILABLE_BARRIER_REQ,
  AVAILABLE_BARRIER_RES,
  AVAILABLE_QUEUE_GET_CONFIG_REQ,
  AVAILABLE_QUEUE_GET_CONFIG_RES,

  // View update errors
  EXCESS_ACTION,
  EXCESS_INSTRUCTION,
  EXCESS_QUEUE_PROPERTY,
  EXCESS_QUEUE,
  EXCESS_PACKET_OUT,
  EXCESS_BUCKET,
  EXCESS_STATS_RES_FLOW,
  EXCESS_STATS_RES_GROUP,
  EXCESS_STATS_RES_GROUP_DESC,
  EXCESS_PAYLOAD
};

/// Represents the testable result of message processing functions. This
/// is the result type of the to_buffer(), from_buffer(), and is_valid()
/// operations.
using Error_condition = Condition<Error_code>;

// -------------------------------------------------------------------------- //
// Structures
//
// The following classes are structures used by various messages:
//    - Match
//    - Port
//    - Queue
//    - Action
//    - Instruction
//    - Bucket

// -------------------------------------------------------------------------- //
// Match

//// Represents a matching entry in a flow table. The Match class is used by
/// several messages in the protocol to refer to a single entry in in a flow 
/// table. The class specifies which fields of a packet will be matched by
/// the switch, any of which can be specified as a wildcard value.
///
/// \remark Defined in [OpenFlow v1.0, p20-21](http://...)
struct Match
{
  enum Type : uint16_t {
    STANDARD = 0x0000
  };

  enum Wildcards : uint32_t {
    IN_PORT = 0x00000001, DL_VLAN = 0x00000002,
    DL_PCP = 0x00000004, DL_TYPE = 0x00000008,
    NW_TOS = 0x00000010, NW_PROTO = 0x00000020,
    TP_SRC = 0x00000040, TP_DST = 0x00000080,
    MPLS_LABEL = 0x00000100, MPLS_TC = 0x00000200,
    ALL = 0x000003ff
  };

  Type type;
  uint16_t length;
  uint32_t in_port;
  Wildcards wildcards;
  Ethernet_addr dl_src;
  Ethernet_addr dl_src_mask;
  Ethernet_addr dl_dst;
  Ethernet_addr dl_dst_mask;
  uint16_t dl_vlan;
  uint8_t dl_pcp;
  uint16_t dl_type;
  uint8_t nw_tos;
  uint8_t nw_proto;
  Ipv4_addr nw_src;
  Ipv4_addr nw_src_mask;
  Ipv4_addr nw_dst;
  Ipv4_addr nw_dst_mask;
  uint16_t tp_src;
  uint16_t tp_dst;
  uint32_t mpls_label;
  uint8_t mpls_tc;
  uint64_t metadata;
  uint64_t metadata_mask;
};

/// Returns true when the arguments compare equal. Two match values
/// compare equal when they match the same packets (i.e., all fields compare
/// equal).
bool operator==(const Match& a, const Match& b);

/// Returns true when the arguments do not compare equal.
bool operator!=(const Match& a, const Match& b);

/// Returns the number of bytes needed to represent a Match value.
constexpr std::size_t bytes(const Match&);

/// Validates the value of wildcards field.
Error_condition is_valid(const Match::Wildcards w);

/// Validates the value of a Match object.
Error_condition is_valid(const Match& m);

/// Writes a Match value into a Buffer_view. If the write does not succeed,
/// the result will containt a code representing the specific cause of failure.
Error_condition to_buffer(Buffer_view&, const Match&);

/// Reads a Match value from a Buffer_view. If the read does not succeed, the
/// result will containt a code representing the specific cause of failure.
Error_condition from_buffer(Buffer_view&, Match&);

/// Returns a formatted string representation of a Match value.
std::string to_string(const Match&, Formatter&);

/// Returns true if wildcard OFPFW_IN_PORT is set
constexpr bool wildcard_in_port(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_DL_VLAN is set
constexpr bool wildcard_dl_vlan(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_DL_VLAN_PCP is set
constexpr bool wildcard_dl_pcp(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_DL_TYPE is set
constexpr bool wildcard_dl_type(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_NW_TOS is set
constexpr bool wildcard_nw_tos(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_NW_PROTO is set
constexpr bool wildcard_nw_proto(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_TP_SRC is set
constexpr bool wildcard_tp_src(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_TP_DST is set
constexpr bool wildcard_tp_dst(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_MPLS_LABEL is set
constexpr bool wildcard_mpls_label(Match::Wildcards wt);

/// Returns true if wildcard OFPFW_MPLS_TC is set
constexpr bool wildcard_mpls_tc(Match::Wildcards wt);


// -------------------------------------------------------------------------- //
// Action type

/// Values corresponding to the different kinds of actions supported
/// in the OpenFlow protocol. 
///
/// \remark This enumeration corresponds to the ofp_action_type described 
/// in the OpenFlow specification.
enum Action_type : uint16_t
{
  ACTION_OUTPUT         = 0x0000,
  ACTION_SET_VLAN_VID   = 0x0001,
  ACTION_SET_VLAN_PCP   = 0x0002,
  ACTION_SET_DL_SRC     = 0x0003,
  ACTION_SET_DL_DST     = 0x0004,
  ACTION_SET_NW_SRC     = 0x0005,
  ACTION_SET_NW_DST     = 0x0006,
  ACTION_SET_NW_TOS     = 0x0007,
  ACTION_SET_NW_ECN     = 0x0008,
  ACTION_SET_TP_SRC     = 0x0009,
  ACTION_SET_TP_DST     = 0x000a,
  ACTION_COPY_TTL_OUT   = 0x000b,
  ACTION_COPY_TTL_IN    = 0x000c,
  ACTION_SET_MPLS_LABEL = 0x000d,
  ACTION_SET_MPLS_TC    = 0x000e,
  ACTION_SET_MPLS_TTL   = 0x000f,
  ACTION_DEC_MPLS_TTL   = 0x0010,
  ACTION_PUSH_VLAN      = 0x0011,
  ACTION_POP_VLAN       = 0x0012,
  ACTION_PUSH_MPLS      = 0x0013,
  ACTION_POP_MPLS       = 0x0014,
  ACTION_SET_QUEUE      = 0x0015,
  ACTION_GROUP          = 0x0016,
  ACTION_SET_NW_TTL     = 0x0017,
  ACTION_DEC_NW_TTL     = 0x0018,
  ACTION_EXPERIMENTER   = 0xffff
};

/// Validates an action type
Error_condition is_valid(const Action_type at);

/// Return a formatted string representation for the corresponding action
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
  Action_output(uint32_t p, uint16_t m) : port(p), max_len(m) { }

  uint32_t port;
  uint16_t max_len;
};

/// \relates Action_output
bool operator==(const Action_output& a, const Action_output& b);

/// \relates Action_output
bool operator!=(const Action_output& a, const Action_output& b);

/// \relates Action_output
constexpr std::size_t bytes(const Action_output&);

/// \relates Action_output
constexpr Error_condition is_valid(const Action_output&);

/// \relates Action_output
Error_condition to_buffer(Buffer_view&, const Action_output&);

/// \relates Action_output
Error_condition from_buffer(Buffer_view&, Action_output&);

/// \relates Action_output
std::string to_string(const Action_output&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Vlan VID


/// Sets the VLAN VID. 
///
/// \remark Corresponds to the ofp_action_vlan_vid in OpenFlow specification.
struct Action_set_vlan_vid : Action_payload_base<ACTION_SET_VLAN_VID>
{
  Action_set_vlan_vid() = default;
  explicit Action_set_vlan_vid(uint16_t vv) : vlan_vid(vv) { }

  uint16_t vlan_vid;
};

/// \relates Action_set_vlan_vid
bool operator==(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b);

/// \relates Action_set_vlan_vid
bool operator!=(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b);

/// \relates Action_set_vlan_vid
constexpr std::size_t bytes(const Action_set_vlan_vid&);

/// \relates Action_set_vlan_vid
constexpr Error_condition is_valid(const Action_set_vlan_vid&);

/// \relates Action_set_vlan_vid
Error_condition to_buffer(Buffer_view&, const Action_set_vlan_vid&);

/// \relates Action_set_vlan_vid
Error_condition from_buffer(Buffer_view&, Action_set_vlan_vid&);

/// \relates Action_set_vlan_vid
std::string to_string(const Action_set_vlan_vid&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Vlan PCP

/// Sets the VLAN prioroity.
///
/// \remark Corresponds to ofp_action_vlan_pcp in OpenFlow specification.
struct Action_set_vlan_pcp : Action_payload_base<ACTION_SET_VLAN_PCP>
{
  Action_set_vlan_pcp() = default;
  explicit Action_set_vlan_pcp(uint8_t vp) : vlan_pcp(vp) { }

  uint8_t vlan_pcp;
};

/// \relates Action_set_vlan_pcp
bool operator==(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b);

/// \relates Action_set_vlan_pcp
bool operator!=(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b);

/// \relates Action_set_vlan_pcp
constexpr std::size_t bytes(const Action_set_vlan_pcp&);

/// \relates Action_set_vlan_pcp
constexpr Error_condition is_valid(const Action_set_vlan_pcp&);

/// \relates Action_set_vlan_pcp
Error_condition to_buffer(Buffer_view&, const Action_set_vlan_pcp&);

/// \relates Action_set_vlan_pcp
Error_condition from_buffer(Buffer_view&, Action_set_vlan_pcp&);

/// \relates Action_set_vlan_pcp
std::string to_string(const Action_set_vlan_pcp&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Dl Addr

/// Implementation of actions that modify the data link address.
///
/// \remark Corresponds to ofp_action_dl_addr in the OpenFlow specification.
template<Action_type K>
  struct Action_dl_addr : Action_payload_base<K>
  {
    Action_dl_addr() = default;
    explicit Action_dl_addr(Ethernet_addr da) : dl_addr(da) { }

    Ethernet_addr dl_addr;
  };

/// \relates Action_dl_addr
template<Action_type K>
  bool operator==(const Action_dl_addr<K>& a, const Action_dl_addr<K>& b);

/// \relates Action_dl_addr
template<Action_type K>
  bool operator!=(const Action_dl_addr<K>& a, const Action_dl_addr<K>& b);

/// \relates Action_dl_addr
template<Action_type K>
  constexpr std::size_t bytes(const Action_dl_addr<K>&);

/// \relates Action_dl_addr
template<Action_type K>
  constexpr Error_condition is_valid(const Action_dl_addr<K>&);

/// \relates Action_dl_addr
template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_dl_addr<K>& da);

/// \relates Action_dl_addr
template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_dl_addr<K>& da);

// -------------------------------------------------------------------------- //
// Action: Set dl src

/// Sets the data link (Ethernet) source address.
///
/// \remark Implements the OFPAT_SET_DL_SRC action described in
/// the OpenFlow specification.
struct Action_set_dl_src : Action_dl_addr<ACTION_SET_DL_SRC>
{
  using Action_dl_addr<ACTION_SET_DL_SRC>::Action_dl_addr;
};

/// \relates Action_set_dl_src.
std::string to_string(const Action_set_dl_src&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Set dl dst

/// Sets the data link (Ethernet) destination address.
///
/// \remark Implements the OFPAT_SET_DL_DST action described in
/// the OpenFlow specification.
struct Action_set_dl_dst : Action_dl_addr<ACTION_SET_DL_DST>
{
  using Action_dl_addr<ACTION_SET_DL_DST>::Action_dl_addr;
};

std::string to_string(const Action_set_dl_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Nw Addr

/// Implementation of actions that modify the network (IPv4) address.
///
/// \remark Corresponds to ofp_action_nw_addr in the OpenFlow specification.
template<Action_type K>
  struct Action_nw_addr : Action_payload_base<K>
  {
    Action_nw_addr() = default;
    explicit Action_nw_addr(Ipv4_addr na) : nw_addr(na) { }

    Ipv4_addr nw_addr;
  };

/// \relates Action_nw_addr
template<Action_type K>
  bool operator==(const Action_nw_addr<K>& a, const Action_nw_addr<K>& b);

/// \relates Action_nw_addr
template<Action_type K>
  bool operator!=(const Action_nw_addr<K>& a, const Action_nw_addr<K>& b);

/// \relates Action_nw_addr
template<Action_type K>
  constexpr std::size_t bytes(const Action_nw_addr<K>&);

/// \relates Action_nw_addr
template<Action_type K>
  constexpr Error_condition is_valid(const Action_nw_addr<K>&);

/// \relates Action_nw_addr
template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_nw_addr<K>& na);

/// \relates Action_nw_addr
template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_nw_addr<K>& na);

// -------------------------------------------------------------------------- //
// Action: Set nw src

/// Sets the network (Ipv4) source address.
///
/// \remark Implements the OFPAT_SET_NW_DST action described in the 
/// OpenFlow spec.
struct Action_set_nw_src : Action_nw_addr<ACTION_SET_NW_SRC>
{
  using Action_nw_addr<ACTION_SET_NW_SRC>::Action_nw_addr;
};

/// \relates Action_set_nw_src
std::string to_string(const Action_set_nw_src&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Set nw dst

/// Sets the network (Ipv4) destination address.
///
/// \remark Implements the OFPAT_SET_NW_DST action described in the 
/// OpenFlow spec.
struct Action_set_nw_dst : Action_nw_addr<ACTION_SET_NW_DST>
{
  using Action_nw_addr<ACTION_SET_NW_DST>::Action_nw_addr;
};

/// \relates Action_set_nw_dst
std::string to_string(const Action_set_nw_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: NW Tos

/// Sets the network (Ipv4) TOS field
///
/// \remark Implements the ofp_action_nw_tos (OFPAT_SET_NW_TOS action) in 
/// OpenFlow protocol
struct Action_set_nw_tos : Action_payload_base<ACTION_SET_NW_TOS>
{
  Action_set_nw_tos() = default;
  explicit Action_set_nw_tos(uint8_t snt) : nw_tos(snt) { }

  uint8_t nw_tos;
};

bool operator==(const Action_set_nw_tos& a, const Action_set_nw_tos& b);

bool operator!=(const Action_set_nw_tos& a, const Action_set_nw_tos& b);

constexpr std::size_t bytes(const Action_set_nw_tos&);

constexpr Error_condition is_valid(const Action_set_nw_tos&);

Error_condition to_buffer(Buffer_view&, const Action_set_nw_tos&);

Error_condition from_buffer(Buffer_view&, Action_set_nw_tos&);

std::string to_string(const Action_set_nw_tos&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: NW Ecn

/// Sets the network (ipv4) ECN field
///
/// \remark Implements cfp_action_nw_ecn (OFPAT_SET_NW_ECN action) in OpenFlow 
/// protocol
struct Action_set_nw_ecn : Action_payload_base<ACTION_SET_NW_ECN>
{
  Action_set_nw_ecn() = default;
  explicit Action_set_nw_ecn(uint8_t sne) : nw_ecn(sne) { }

  uint8_t nw_ecn;
};

bool operator==(const Action_set_nw_ecn& a, const Action_set_nw_ecn& b);

bool operator!=(const Action_set_nw_ecn& a, const Action_set_nw_ecn& b);

constexpr std::size_t bytes(const Action_set_nw_ecn&);

constexpr Error_condition is_valid(const Action_set_nw_ecn&);

Error_condition to_buffer(Buffer_view&, const Action_set_nw_ecn&);

Error_condition from_buffer(Buffer_view&, Action_set_nw_ecn&);

std::string to_string(const Action_set_nw_ecn&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: TP Addr

/// Base class for setting the transport layer address
/// 
/// \remark Implements ofp_action_tp_addr in OpenFlow protocol
template<Action_type K>
  struct Action_tp_addr : Action_payload_base<K>
  {
    Action_tp_addr() = default;
    explicit Action_tp_addr(uint16_t tp) : tp_port(tp) { }

    uint16_t tp_port;
  };

template<Action_type K>
  bool operator==(const Action_tp_addr<K>& a, const Action_tp_addr<K>& b);

template<Action_type K>
  bool operator!=(const Action_tp_addr<K>& a, const Action_tp_addr<K>& b);

template<Action_type K>
  constexpr std::size_t bytes(const Action_tp_addr<K>&);

template<Action_type K>
  constexpr Error_condition is_valid(const Action_tp_addr<K>&);

template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_tp_addr<K>& ta);

template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_tp_addr<K>& ta);

// -------------------------------------------------------------------------- //
// Action: Set tp src

/// Set transport layer source address
///
/// \remark Implements OFPAT_SET_TP_SRC action
struct Action_set_tp_src : Action_tp_addr<ACTION_SET_TP_SRC>
{
  using Action_tp_addr<ACTION_SET_TP_SRC>::Action_tp_addr;
};

std::string to_string(const Action_set_tp_src&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Set tp dst

/// Set transport layer destination address
///
/// \remark Implements OFPAT_SET_TP_DST action
struct Action_set_tp_dst : Action_tp_addr<ACTION_SET_TP_DST>
{
  using Action_tp_addr<ACTION_SET_TP_DST>::Action_tp_addr;
};

std::string to_string(const Action_set_tp_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Copy ttl out

/// Copy TTL "outwards" -- Copy TTL "outwards" -- from next-to-outermost to 
/// outermost
///
/// \remark Implements OFPAT_COPY_TTL_OUT action
struct Action_copy_ttl_out : Action_payload_base<ACTION_COPY_TTL_OUT> { };

constexpr std::size_t bytes(const Action_copy_ttl_out&);

constexpr Error_condition is_valid(const Action_copy_ttl_out&);

Error_condition to_buffer(Buffer_view&, const Action_copy_ttl_out&);

Error_condition from_buffer(Buffer_view&, Action_copy_ttl_out&);

// -------------------------------------------------------------------------- //
// Action: Copy ttl in

/// Copy TTL "inwards" -- from outermost to next-to-outermost
///
/// \remark Implements OFPAT_COPY_TTL_IN action
struct Action_copy_ttl_in : Action_payload_base<ACTION_COPY_TTL_IN> { };

constexpr std::size_t bytes(const Action_copy_ttl_in&);

constexpr Error_condition is_valid(const Action_copy_ttl_in&);

Error_condition to_buffer(Buffer_view&, const Action_copy_ttl_in&);

Error_condition from_buffer(Buffer_view&, Action_copy_ttl_in&);

// -------------------------------------------------------------------------- //
// Action: Set MPLS Label

/// Set value of an MPLS Label
///
/// \remark Implements ofp_action_mpls_label (OFP_SET_MPLS_LABEL action) in 
/// OpenFlow protocol
struct Action_set_mpls_label : Action_payload_base<ACTION_SET_MPLS_LABEL>
{
  Action_set_mpls_label() = default;
  explicit Action_set_mpls_label(uint32_t ml) : mpls_label(ml) { }

  uint32_t mpls_label;
};

bool operator==(const Action_set_mpls_label& a, const Action_set_mpls_label& b);

bool operator!=(const Action_set_mpls_label& a, const Action_set_mpls_label& b);

constexpr std::size_t bytes(const Action_set_mpls_label&);

constexpr Error_condition is_valid(const Action_set_mpls_label&);

Error_condition to_buffer(Buffer_view&, const Action_set_mpls_label&);

Error_condition from_buffer(Buffer_view&, Action_set_mpls_label&);

std::string to_string(const Action_set_mpls_label&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Set MPLS TC

/// Set MPLS TC field
///
/// \remark Implements ofp_action_mpls_tc (OFP_SET_MPLS_TC action) in OpenFlow 
/// protocol
struct Action_set_mpls_tc : Action_payload_base<ACTION_SET_MPLS_TC>
{
  Action_set_mpls_tc() = default;
  explicit Action_set_mpls_tc(uint8_t mt) : mpls_tc(mt) { }

  uint8_t mpls_tc;
};

bool operator==(const Action_set_mpls_tc& a, const Action_set_mpls_tc& b);

bool operator!=(const Action_set_mpls_tc& a, const Action_set_mpls_tc& b);

constexpr std::size_t bytes(const Action_set_mpls_tc&);

constexpr Error_condition is_valid(const Action_set_mpls_tc&);

Error_condition to_buffer(Buffer_view&, const Action_set_mpls_tc&);

Error_condition from_buffer(Buffer_view&, Action_set_mpls_tc&);

std::string to_string(const Action_set_mpls_tc&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: MPLS TTL

/// Base class for MPLS TTL field related actions
///
/// \remark Implements ofp_action_mpls_ttl in OpenFlow protocol
template<Action_type K>
  struct Action_mpls_ttl : Action_payload_base<ACTION_SET_MPLS_TTL>
  {
    Action_mpls_ttl() = default;
    explicit Action_mpls_ttl(uint8_t mt) : mpls_ttl(mt) { }

    uint8_t mpls_ttl;
  };

template<Action_type K>
  bool operator==(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b);

template<Action_type K>
  bool operator!=(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b);

template<Action_type K>
  constexpr std::size_t bytes(const Action_mpls_ttl<K>&);

template<Action_type K>
  constexpr Error_condition is_valid(const Action_mpls_ttl<K>&);

template<Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_mpls_ttl<K>& mt);

template<Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_mpls_ttl<K>& mt);

// -------------------------------------------------------------------------- //
// Action: Set Mpls ttl

/// Set MPLS Time-To-Live field
/// 
/// \remark Implements OFP_SET_MPLS_TTL action 
struct Action_set_mpls_ttl : Action_mpls_ttl<ACTION_SET_MPLS_TTL>
{
  using Action_mpls_ttl<ACTION_SET_MPLS_TTL>::Action_mpls_ttl;
};

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

std::string to_string(const Action_dec_mpls_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push Pop

/// Base class for push and pop actions
/// \remark Implements ofp_action_push and ofp_action_pop_mpls in OpenFlow 
/// protocol
template<Action_type K>
  struct Action_push_pop : Action_payload_base<K>
  {
    Action_push_pop() = default;
    explicit Action_push_pop(uint16_t et) : ether_type(et) { }

    uint16_t ether_type;
  };

template<Action_type K>
  bool operator==(const Action_push_pop<K>& a, const Action_push_pop<K>& b);

template<Action_type K>
  bool operator!=(const Action_push_pop<K>& a, const Action_push_pop<K>& b);

template<Action_type K>
  constexpr std::size_t bytes(const Action_push_pop<K>&);

template<Action_type K>
  Error_condition is_valid(const Action_push_pop<K>&);

template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_push_pop<K>& pp);

template<Action_type K>
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

std::string to_string(const Action_push_vlan&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push Vlan

/// Pop the outer VLAN tag
///
/// \remark Implements OFPAT_POP_VLAN action
struct Action_pop_vlan : Action_push_pop<ACTION_POP_VLAN>
{
  using Action_push_pop<ACTION_POP_VLAN>::Action_push_pop;
};

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
  explicit Action_set_queue(uint32_t qid) : queue_id(qid) { }

  uint32_t queue_id;
};

bool operator==(const Action_set_queue& a, const Action_set_queue& b);

bool operator!=(const Action_set_queue& a, const Action_set_queue& b);

constexpr std::size_t bytes(const Action_set_queue&);

constexpr Error_condition is_valid(const Action_set_queue&);

Error_condition to_buffer(Buffer_view&, const Action_set_queue&);

Error_condition from_buffer(Buffer_view&, Action_set_queue&);

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
  explicit Action_group(uint32_t gid) : group_id(gid) { }

  uint32_t group_id;
};

bool operator==(const Action_group& a, const Action_group& b);

bool operator!=(const Action_group& a, const Action_group& b);

constexpr std::size_t bytes(const Action_group&);

constexpr Error_condition is_valid(const Action_group&);

Error_condition to_buffer(Buffer_view&, const Action_group&);

Error_condition from_buffer(Buffer_view&, Action_group&);

std::string to_string(const Action_group&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: NW TTL

/// Base class for network TTL actions
///
/// \remark Implements ofp_action_nw_ttl in OpenFlow protocol
template<Action_type K>
  struct Action_nw_ttl : Action_payload_base<ACTION_SET_NW_TTL>
  {
    Action_nw_ttl() = default;
    explicit Action_nw_ttl(uint8_t nt) : nw_ttl(nt) { }

    uint8_t nw_ttl;
  };

template<Action_type K>
  bool operator==(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b);

template<Action_type K>
  bool operator!=(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b);

template<Action_type K>
  constexpr std::size_t bytes(const Action_nw_ttl<K>& nt);

template<Action_type K>
  constexpr Error_condition is_valid(const Action_nw_ttl<K>&);

template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_nw_ttl<K>& nt);

template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_nw_ttl<K>& nt);

// -------------------------------------------------------------------------- //
// Action: Set Nw ttl

/// Set network layer ttl field
///
/// \remark Implements OFPAT_SET_NW_TTL action
struct Action_set_nw_ttl : Action_nw_ttl<ACTION_SET_NW_TTL>
{
  using Action_nw_ttl<ACTION_SET_NW_TTL>::Action_nw_ttl;
};

std::string to_string(const Action_set_nw_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Dec Nw ttl

/// Decrease network layer TTL by 1
///
/// \remark Implements OFPAT_DEC_NW_TTL action
struct Action_dec_nw_ttl : Action_nw_ttl<ACTION_DEC_NW_TTL>
{
  using Action_nw_ttl<ACTION_DEC_NW_TTL>::Action_nw_ttl;
};

std::string to_string(const Action_dec_nw_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Experimenter

/// Experimenter action
///
/// \remark Implements ofp_action_experimenter_header in OpenFlow protocol
struct Action_experimenter : Action_payload_base<ACTION_EXPERIMENTER>
{
  Action_experimenter() = default;
  explicit Action_experimenter(uint32_t e) : experimenter(e) { }

  uint32_t experimenter;
};

bool operator==(const Action_experimenter& a, const Action_experimenter& b);

bool operator!=(const Action_experimenter& a, const Action_experimenter& b);

constexpr std::size_t bytes(const Action_experimenter&);

constexpr Error_condition is_valid(const Action_experimenter&);

std::string to_string(const Action_experimenter&, Formatter&);

Error_condition to_buffer(Buffer_view&, const Action_experimenter&);

Error_condition from_buffer(Buffer_view&, Action_experimenter&);

// -------------------------------------------------------------------------- //
// Action Payload

union Action_payload_data
{
  Action_output         output;
  Action_set_vlan_vid   set_vlan_vid;
  Action_set_vlan_pcp   set_vlan_pcp;
  Action_set_dl_src     set_dl_src;
  Action_set_dl_dst     set_dl_dst;
  Action_set_nw_src     set_nw_src;
  Action_set_nw_dst     set_nw_dst;
  Action_set_nw_tos     set_nw_tos;
  Action_set_nw_ecn     set_nw_ecn;
  Action_set_tp_src     set_tp_src;
  Action_set_tp_dst     set_tp_dst;
  Action_copy_ttl_out   copy_ttl_out;
  Action_copy_ttl_in    copy_ttl_in;
  Action_set_mpls_label set_mpls_label;
  Action_set_mpls_tc    set_mpls_tc;
  Action_set_mpls_ttl   set_mpls_ttl;
  Action_dec_mpls_ttl   dec_mpls_ttl;
  Action_push_vlan      push_vlan;
  Action_pop_vlan       pop_vlan;
  Action_push_mpls      push_mpls;
  Action_pop_mpls       pop_mpls;
  Action_set_queue      set_queue;
  Action_group          group;
  Action_set_nw_ttl     set_nw_ttl;
  Action_dec_nw_ttl     dec_nw_ttl;
  Action_experimenter   experimenter;
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

void construct(Action_payload&, Action_type);
void construct(Action_payload&, const Action_payload&, Action_type);

template<typename Tag, typename... Args>
  void construct(Action_payload& p, Tag t, Args&&... args) = delete;

Action_payload& assign(Action_payload&, const Action_payload&, Action_type);

bool equal(const Action_payload&, const Action_payload&, Action_type,
           Action_type);

std::size_t bytes(const Action_payload&, Action_type);
Error_condition is_valid(const Action_payload&, Action_type);

Error_condition to_buffer(Buffer_view&, const Action_payload&, Action_type);

Error_condition from_buffer(Buffer_view&, Action_payload&, Action_type);

std::string to_string(const Action_payload&, Formatter&, Action_type);

// -------------------------------------------------------------------------- //
// Action_header

/// Contains the header fields of an action. 
///
/// \remark Implement ofp_action_header in OpenFlow protocol
struct Action_header
{
  Action_header() = default;
  Action_header(Action_type t, uint16_t l) : type(t), length(l) { }

  template<typename T>
    Action_header(const T& value) : type(T::kind), length(4 + bytes(value)) { }

  Action_type type;
  uint16_t length;
};

bool operator==(const Action_header& a, const Action_header& b);

bool operator!=(const Action_header& a, const Action_header& b);

constexpr std::size_t bytes(const Action_header&);

Error_condition is_valid(const Action_header& h);

Error_condition to_buffer(Buffer_view&, const Action_header&);

Error_condition from_buffer(Buffer_view&, Action_header&);

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
/// \remark Defined in [OpenFlow v1.1, p31-36]
struct Action
{
  using Header = Action_header;
  using Payload = Action_payload;

  Action() = default;

  Action(const Action& x) : header(x.header) {
    construct(payload, x.payload, header.type);
  };
  
  template<typename T, typename Tag = typename T::Tag>
    Action(T&& x);

  template<typename Tag, typename... Args>
    Action(Tag t, Args&&... args);
  
  Action& operator=(const Action&);

  Header  header;
  Payload payload;
};

bool operator==(const Action& a, const Action& b);

bool operator!=(const Action& a, const Action& b);

std::size_t bytes(const Action& a);

Error_condition is_valid(const Action& a);

Error_condition to_buffer(Buffer_view& v, const Action& a);

Error_condition from_buffer(Buffer_view& v, const Action& a);

std::string to_string(const Action& a, Formatter& f);

// -------------------------------------------------------------------------- //
// Instruction type

enum Instruction_type : uint16_t
{
  INSTRUCTION_GOTO_TABLE     = 0x0001,
  INSTRUCTION_WRITE_METADATA = 0x0002,
  INSTRUCTION_WRITE_ACTIONS  = 0x0003,
  INSTRUCTION_APPLY_ACTIONS  = 0x0004,
  INSTRUCTION_CLEAR_ACTIONS  = 0x0005,
  INSTRUCTION_EXPERIMENTER   = 0xffff
};

Error_condition is_valid(const Instruction_type it);

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
  explicit Instruction_goto_table(uint8_t tid) : table_id(tid) {}

  uint8_t table_id;
};

bool
operator==(const Instruction_goto_table& a, const Instruction_goto_table& b);

bool
operator!=(const Instruction_goto_table& a, const Instruction_goto_table& b);

constexpr std::size_t bytes(const Instruction_goto_table&);

Error_condition is_valid(const Instruction_goto_table&);

Error_condition to_buffer(Buffer_view&, const Instruction_goto_table&);

Error_condition from_buffer(Buffer_view&, Instruction_goto_table&);

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

bool operator==(const Instruction_write_metadata& a,
                const Instruction_write_metadata& b);

bool operator!=(const Instruction_write_metadata& a,
                const Instruction_write_metadata& b);

constexpr std::size_t bytes(const Instruction_write_metadata&);

Error_condition is_valid(const Instruction_write_metadata&);

Error_condition to_buffer(Buffer_view&, const Instruction_write_metadata&);

Error_condition from_buffer(Buffer_view&, Instruction_write_metadata&);

std::string to_string(const Instruction_write_metadata&, Formatter&);

// -------------------------------------------------------------------------- //
// Instruction: Action

/// Base class for all action instructions
///
/// \remark Implements ofp_instruction_actions in OpenFlow protocol
template<Instruction_type K>
  struct Instruction_action : Instruction_payload_base<K>
  {
    Instruction_action() = default;

    explicit Instruction_action(const Sequence<Action>& a) : actions(a) { }

    Sequence<Action> actions;
  };

template<Instruction_type K>
  bool operator==(const Instruction_action<K>& a, const Instruction_action<K>& b);

template<Instruction_type K>
  bool
  operator!=(const Instruction_action<K>& a, const Instruction_action<K>& b);

template<Instruction_type K>
  std::size_t bytes(const Instruction_action<K>& ia);

template<Instruction_type K>
  constexpr Error_condition is_valid(const Instruction_action<K>&);

template<Instruction_type K>
  Error_condition to_buffer(Buffer_view& v, const Instruction_action<K>& ia);

template<Instruction_type K>
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

std::string to_string(const Instruction_clear_actions&, Formatter&);

// -------------------------------------------------------------------------- //
// Instruction: Experimenter

/// Describe an experimenter insruction
struct Instruction_experimenter
  : Instruction_payload_base<INSTRUCTION_EXPERIMENTER>
{
  Instruction_experimenter() = default;
  explicit Instruction_experimenter(uint32_t e) : experimenter_id(e) {}

  uint32_t experimenter_id;
};

bool operator==(const Instruction_experimenter& a,
                const Instruction_experimenter& b);

bool operator!=(const Instruction_experimenter& a,
                const Instruction_experimenter& b);

constexpr std::size_t bytes(const Instruction_experimenter&);

Error_condition is_valid(const Instruction_experimenter&);

Error_condition to_buffer(Buffer_view&, const Instruction_experimenter&);

Error_condition from_buffer(Buffer_view&, Instruction_experimenter&);

std::string to_string(const Instruction_experimenter&, Formatter& f);

// -------------------------------------------------------------------------- //
// Instruction Payload

union Instruction_payload_data
{
  Instruction_payload_data() {}
  ~Instruction_payload_data() {}

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

void construct(Instruction_payload&, Instruction_type);
void construct(Instruction_payload&, Instruction_payload&&,
               Instruction_type);
void construct(Instruction_payload&, const Instruction_payload&,
               Instruction_type);

template<typename Tag, typename... Args>
  void construct(Instruction_payload& p, Tag t, Args&&... args) = delete;

Instruction_payload& assign(Instruction_payload&, Instruction_payload&&,
                            Instruction_type);
Instruction_payload& assign(Instruction_payload&, const Instruction_payload&,
                            Instruction_type);

void destroy(Instruction_payload&, Instruction_type);

bool equal(const Instruction_payload&, const Instruction_payload&,
           Instruction_type, Instruction_type);

std::size_t bytes(const Instruction_payload&, Instruction_type);

Error_condition is_valid(const Instruction_payload&, Instruction_type);

Error_condition to_buffer(Buffer_view&, const Instruction_payload&, Instruction_type);

Error_condition from_buffer(Buffer_view&, Instruction_payload&, Instruction_type);

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
  Instruction_header(Instruction_type t, uint16_t l) : type(t), length(l) { }

  template<typename T>
    explicit Instruction_header(const T& value)
      : Instruction_header(T::kind, 4 + bytes(value)) { }

  Instruction_type type;
  uint16_t length;
};

bool operator==(const Instruction_header& a, const Instruction_header& b);

bool operator!=(const Instruction_header& a, const Instruction_header& b);

constexpr std::size_t bytes(const Instruction_header&);

Error_condition is_valid(const Instruction_header& h);

Error_condition to_buffer(Buffer_view&, const Instruction_header&);

Error_condition from_buffer(Buffer_view&, Instruction_header&);

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
/// \remark Defined in [OpenFlow v1.1, p30-31]
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

bool operator==(const Instruction& a, const Instruction& b);

bool operator!=(const Instruction& a, const Instruction& b);

std::size_t bytes(const Instruction& a);

Error_condition is_valid(const Instruction& a);

Error_condition is_valid(const Sequence<Instruction> i);

Error_condition to_buffer(Buffer_view& v, const Instruction& a);

Error_condition from_buffer(Buffer_view& v, const Instruction& a);

std::string to_string(const Instruction& a, Formatter&);

// -------------------------------------------------------------------------- //
// Port

/// The Port structure describes the property and configuration of a physical 
/// port.
///
/// \remark Defined in [OpenFlow v1.1, p25]
struct Port
{
  static constexpr std::size_t NAME_STR_LEN = 16;

  using Name_string = Stringbuf<NAME_STR_LEN>;

  enum Config : uint32_t {
    PORT_DOWN = 0x00000001, NO_RECV = 0x00000004, NO_FWD = 0x00000020,
    NO_PACKET_IN = 0x00000040
  };

  enum State : uint32_t {
    LINK_DOWN = 0x00000001, BLOCKED = 0x00000002, LIVE = 0x00000004
  };

  enum Id : uint32_t {
    MAX = 0xffffff00, IN_PORT = 0xfffffff8, TABLE = 0xfffffff9,
    NORMAL = 0xfffffffa, FLOOD = 0xfffffffb, ALL = 0xfffffffc,
    CONTROLLER = 0xfffffffd, LOCAL = 0xfffffffe, ANY = 0xffffffff
  };

  enum Features : uint32_t {
    TEN_MB_HD = 0x0000001, TEN_MB_FD = 0x00000002,
    HUNDRED_MB_HD = 0x00000004, HUNDRED_MB_FD = 0x00000008,
    ONE_GB_HD = 0x00000010, ONE_GB_FD = 0x00000020,
    TEN_GB_FD = 0x00000040, FORTY_GB_FD = 0x00000080,
    HUNDRED_GB_FD = 0x00000100, ONE_TB_FD = 0x00000200,
    OTHER = 0x00000400, COPPER = 0x00000800, FIBER = 0x00001000,
    AUTO_NEG = 0x00002000, PAUSE = 0x00004000, PAUSE_ASYM = 0x00008000
  };

  Port() = default;
  Port(Id pid, Ethernet_addr ha, const char* n, Config c,
       State s, Features cu, Features a,
       Features su, Features p, uint32_t cs,
       uint32_t ms)
    : port_id(pid), hw_addr(ha), name(n), config(c), state(s), current(cu),
    advertised(a), supported(su), peer(p), curr_speed(cs), max_speed(ms) { }

  Id port_id;
  Ethernet_addr hw_addr;
  Name_string name;
  Config config;
  State state;
  Features current;
  Features advertised;
  Features supported;
  Features peer;
  uint32_t curr_speed;
  uint32_t max_speed;
};

bool operator==(const Port& a, const Port& b);

bool operator!=(const Port& a, const Port& b);

constexpr std::size_t bytes(const Port&);

Error_condition is_valid(const Port::Id id);

Error_condition is_valid(const Port::Config);

Error_condition is_valid(const Port::State);

Error_condition is_valid(const Port::Features);

Error_condition is_valid(const Port& p) ;

std::string to_string(const Port&, Formatter&);
std::string to_string(Port::Id);
std::string to_string(Port::Config);
std::string to_string(Port::State);
std::string to_string(Port::Features);

Error_condition to_buffer(Buffer_view&, const Port&);

Error_condition from_buffer(Buffer_view&, Port&);

constexpr bool port_config_port_down(uint32_t c);

constexpr bool port_config_no_recv(uint32_t c);

constexpr bool port_config_no_fwd(uint32_t c);

constexpr bool port_config_no_packet_in(uint32_t c);

constexpr bool port_state_blocked(uint32_t s);

constexpr bool port_state_live(uint32_t s);

constexpr bool port_max(uint16_t p);

constexpr bool port_in_port(uint16_t p);

constexpr bool port_table(uint16_t p);

constexpr bool port_normal(uint16_t p);

constexpr bool port_flood(uint16_t p);

constexpr bool port_all(uint16_t p);

constexpr bool port_controller(uint16_t p);

constexpr bool port_local(uint16_t p);

constexpr bool port_any(uint16_t p);

constexpr bool port_feature_10mb_hd(uint32_t p);

constexpr bool port_feature_10mb_fd(uint32_t p);

constexpr bool port_feature_100mb_hd(uint32_t p);

constexpr bool port_feature_100mb_fd(uint32_t p);

constexpr bool port_feature_1gb_hd(uint32_t p);

constexpr bool port_feature_1gb_fd(uint32_t p);

constexpr bool port_feature_10gb_fd(uint32_t p);

constexpr bool port_feature_40gb_fd(uint32_t p);

constexpr bool port_feature_100gb_fd(uint32_t p);

constexpr bool port_feature_1tb_fd(uint32_t p);

constexpr bool port_feature_other(uint32_t p);

constexpr bool port_feature_copper(uint32_t p);

constexpr bool port_feature_fiber(uint32_t p);

constexpr bool port_feature_auto_neg(uint32_t p);

constexpr bool port_feature_pause(uint32_t p);

// -------------------------------------------------------------------------- //
// Queue property type

enum Queue_property_type : uint16_t
{
  QUEUE_PROPERTY_NONE = 0,
  QUEUE_PROPERTY_MIN_RATE = 1,
};

constexpr Error_condition is_valid(const Queue_property_type t);

std::string to_string(Queue_property_type);

/// A base class for all queue property payload kinds
template<Queue_property_type K>
  using Queue_property_payload_base
    = Basic_payload_base<Queue_property_type, K>;


// -------------------------------------------------------------------------- //
// Queue property: None

/// No property defined for queue (default).
///
/// \remark Implement OFPQT_NONE property.
struct Queue_property_none : Queue_property_payload_base<QUEUE_PROPERTY_NONE>
{ };

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
  explicit Queue_property_min_rate(uint16_t r) : rate(r) { }

  uint16_t rate;
};

bool
operator==(const Queue_property_min_rate& a, const Queue_property_min_rate& b);

bool
operator!=(const Queue_property_min_rate& a, const Queue_property_min_rate& b);

constexpr std::size_t bytes(const Queue_property_min_rate&);

constexpr Error_condition is_valid(const Queue_property_min_rate&);

Error_condition to_buffer(Buffer_view&, const Queue_property_min_rate&);

Error_condition from_buffer(Buffer_view&, Queue_property_min_rate&);

std::string to_string(const Queue_property_min_rate&, Formatter&);

// -------------------------------------------------------------------------- //
// Queue property payload

union Queue_property_payload_data
{
  Queue_property_none     none;
  Queue_property_min_rate min_rate;
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

void construct(Queue_property_payload&, Queue_property_type);
void construct(Queue_property_payload&, const Queue_property_payload&,
               Queue_property_type);
Queue_property_payload&
assign(Queue_property_payload&, const Queue_property_payload&,
       Queue_property_type);

bool equal(const Queue_property_payload&, const Queue_property_payload&,
           Queue_property_type, Queue_property_type);

std::size_t bytes(const Queue_property_payload&, Queue_property_type);

Error_condition is_valid(const Queue_property_payload&, Queue_property_type);

Error_condition to_buffer(Buffer_view&, const Queue_property_payload&,
               Queue_property_type);
Error_condition from_buffer(Buffer_view&, Queue_property_payload&,
                 Queue_property_type);

std::string to_string(const Queue_property_payload&, Formatter&
                      Queue_property_type);

// -------------------------------------------------------------------------- //
// Queue property header

/// The header of a queue property. 
///
/// \remark Implements ofp_queue_prop_header in OpenFlow protocol.
struct Queue_property_header
{
  Queue_property_header() = default;
  Queue_property_header(Queue_property_type p, uint16_t l)
    : property(p), length(l) { }

  template<typename T>
    Queue_property_header(const T& value);

  Queue_property_type property;
  uint16_t length;
};

bool
operator==(const Queue_property_header& a, const Queue_property_header& b);

bool
operator!=(const Queue_property_header& a, const Queue_property_header& b);

constexpr std::size_t bytes(const Queue_property_header&);

Error_condition is_valid(const Queue_property_header& h);

Error_condition to_buffer(Buffer_view&, const Queue_property_header&);

Error_condition from_buffer(Buffer_view&, Queue_property_header&);

std::string to_string(const Queue_property_header&, Formatter&);

// -------------------------------------------------------------------------- //
// Queue property

/// Describe a queue property.
///
/// A queue property  consists of one header and one payload. The type of
/// payload is determined by value of header. 
/// 
/// The description of a queue in OpenFlow protocols contain a list of 
/// queue_property as parameter. The list of actions is described in this
/// driver as Sequence of Action (Sequence<Action>).
///
/// \remark Defined in [OpenFlow v1.1, p27-28]
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

bool operator==(const Queue_property& a, const Queue_property& b);

bool operator!=(const Queue_property& a, const Queue_property& b);

std::size_t bytes(const Queue_property& p);

Error_condition is_valid(const Queue_property& p);

Error_condition to_buffer(Buffer_view& v, const Queue_property& qp);

Error_condition from_buffer(Buffer_view& v, const Queue_property& qp);

std::string to_string(const Queue_property&,  Formatter&);

// -------------------------------------------------------------------------- //
// Queue

/// A queue in OpenFlow is a structure that is attached to a port and provide
/// datarate garantee to any data flow through it.
///
/// \remark Defined in [OpenFlow v1.1, p28]
struct Queue
{
  Queue() = default;
  Queue(uint32_t qid, uint32_t l, Sequence<Queue_property> p)
    : queue_id(qid), length(l), properties(p) { }

  uint32_t queue_id;
  uint16_t length;
  Sequence<Queue_property> properties;
};

bool operator==(const Queue& a, const Queue& b);

bool operator!=(const Queue& a, const Queue& b);

std::size_t bytes(const Queue& q);

Error_condition is_valid(const Queue& q);

Error_condition to_buffer(Buffer_view&, const Queue&);

Error_condition from_buffer(Buffer_view&, Queue&);

std::string to_string(const Queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Bucket

/// A bucket is a set of actions that is associated with a group. The actions
/// are applied to any packet directed to this group
///
/// \remark Defined in [OpenFlow v1.1, p41]
struct Bucket
{
  Bucket() = default;
  Bucket(uint16_t l, uint16_t w, uint32_t wp, uint32_t wg,
         const Sequence<Action> a)
    : len(l), weight(w), watch_port(wp), watch_group(wg), actions(a) { }

  uint16_t len;
  uint16_t weight;
  uint32_t watch_port;
  uint32_t watch_group;
  Sequence<Action> actions;
};

bool operator==(const Bucket& a, const Bucket& b);

bool operator!=(const Bucket& a, const Bucket& b);

std::size_t bytes(const Bucket& b);

Error_condition is_valid(const Bucket& b);

Error_condition to_buffer(Buffer_view&, const Bucket&);

Error_condition from_buffer(Buffer_view&, Bucket&);

std::string to_string(const Bucket&, Formatter&);

// -------------------------------------------------------------------------- //
// Version Type

enum Version_type : std::uint8_t
{
  VERSION = 2
};

Error_condition
is_valid(const Version_type t);

/// Returns a string representation of the version type.
std::string to_string(Version_type t);

// -------------------------------------------------------------------------- //
// Message Type

enum Message_type : std::uint8_t
{
  HELLO                = 0,
  ERROR                = 1,
  ECHO_REQ             = 2,
  ECHO_RES             = 3,
  EXPERIMENTER         = 4,
  FEATURE_REQ          = 5,
  FEATURE_RES          = 6,
  GET_CONFIG_REQ       = 7,
  GET_CONFIG_RES       = 8,
  SET_CONFIG           = 9,
  PACKET_IN            = 10,
  FLOW_REMOVED         = 11,
  PORT_STATUS          = 12,
  PACKET_OUT           = 13,
  FLOW_MOD             = 14,
  GROUP_MOD            = 15,
  PORT_MOD             = 16,
  TABLE_MOD            = 17,
  STATS_REQ            = 18,
  STATS_RES            = 19,
  BARRIER_REQ          = 20,
  BARRIER_RES          = 21,
  QUEUE_GET_CONFIG_REQ = 22,
  QUEUE_GET_CONFIG_RES = 23
};

/// Returns true if n is a valid value of Message_type.
Error_condition is_valid(const Message_type t);

/// Returns a string representation of the message type.
std::string to_string(Message_type t);

/// A helper type for primary message payloads.
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
/// \remark Defined in [OpenFlow v1.1, p55](http:://...)
struct Hello : Payload_base<HELLO>
{
  Hello() = default;

  /// Constructs a Hello message containing uninterpreted data. Initializes
  /// the uninterpreted data to the contents of the buffer b.
  explicit Hello(Greedy_buffer b) : data(b) { }
 
  Greedy_buffer data;
};

/// Returns true when the arguments compare equal. Two Hello messages a and b 
/// compare equal when a.data compares equal to b.data.
///
/// \relates Hello
bool operator==(const Hello& a, const Hello& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Hello
bool operator!=(const Hello& a, const Hello& b);

/// Returns the number of bytes needed to represent a Hello value. The number 
/// of bytes depends on the number of bytes in m.data.
///
/// \relates Hello
std::size_t bytes(const Hello& h);

/// Validates the value of a Hello message. The result is always SUCCESS since 
/// a Hello message is valid by construction.
///
/// \relates Hello
constexpr Error_condition is_valid(const Hello& h);

/// Writes a Hello message into a Buffer_view. If the write does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Hello
Error_condition to_buffer(Buffer_view&, const Hello&);

/// Reads a Hello message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Hello
Error_condition from_buffer(Buffer_view&, Hello&);

/// Returns a formatted string representation of the value.
///
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
/// \remark Defined in [OpenFlow v1.1, p52-55](http://...)
struct Error : Payload_base<ERROR>
{
  /// Describes the categories of error codes.
  enum Type : uint16_t {
    /// Hello protocol failed (see Error::Hello_failed).    
    HELLO_FAILED = 0x0000, 

    /// Request was not understood (see Error::Bad_request).
    BAD_REQUEST = 0x0001, 
    
    /// Error in action description (see Error::Bad_action).
    BAD_ACTION = 0x0002,

    /// Error in instruction description (see Error::Bad_instruction).
    BAD_INSTRUCTION = 0x0003, 

    /// Error in match description (see Error::Bad_match).
    BAD_MATCH = 0x0004,

    /// Flow modification failed (see Error::Flow_mod_failed).
    FLOW_MOD_FAILED = 0x0005, 

    /// Group modification failed (see Error::Group_mod_failed).
    GROUP_MOD_FAILED = 0x0006,

    /// Port modification failed (see Error::Port_mod_failed).
    PORT_MOD_FAILED = 0x0007, 

    /// Table modification failed (see Error::Table_mod_failed).
    TABLE_MOD_FAILED = 0x0008,

    /// Queue operation failed (see Error::Queue_op_failed).
    QUEUE_OP_FAILED = 0x0009, 

    /// Fail to configure switch (see Error::Swtich_config_failed).
    SWITCH_CONFIG_FAILED = 0x000a
  };

  // Type-based Code values
  enum Hello_failed : uint16_t {
    HF_INCOMPATIBLE = 0x0000, ///< No compatible version
    HF_EPERM = 0x0001 ///< Permissions error
  };

  enum Bad_request : uint16_t {
    BR_BAD_VERSION = 0x0000,        ///< Unknown action type
    BR_BAD_TYPE = 0x0001,           ///< Message type not supported
    BR_BAD_STAT = 0x0002,           ///< Stat request type not supported
    BR_BAD_EXPERIMENTER = 0x0003,   ///< Experimenter ID not supported
    BR_BAD_SUBTYPE = 0x0004,        ///< Vendor subtype not supported
    BR_EPERM = 0x0005,              ///< Permisssions error
    BR_BAD_LEN = 0x0006,            ///< Wrong message length
    BR_BUFFER_EMPTY = 0x0007,       ///< Specified buffer has already been used
    BR_BUFFER_UNKNOWN = 0x0008,     ///< Specified buffer does not exist
    BR_BAD_TABLE_ID = 0x0009        ///< Table ID not valid
  };

  enum Bad_action : uint16_t {
    BA_BAD_TYPE = 0x0000,               ///< Unknown action type
    BA_BAD_LEN = 0x0001,                ///< Wrong length for action
    BA_BAD_EXPERIMENTER = 0x0002,       ///< Unknown experimenter id specified
    BA_BAD_EXPERIMENTER_TYPE = 0x0003,  ///< Unknown action type for experimenter id
    BA_BAD_OUT_PORT = 0x0004,           ///< Problem validating output port
    BA_BAD_ARGUMENT = 0x0005,           ///< Bad action argument
    BA_EPERM = 0x0006,                  ///< Permissions error
    BA_TOO_MANY = 0x0007,               ///< Can't handle this many actions
    BA_BAD_QUEUE = 0x0008,              ///< Problem validating output queue
    BA_BAD_OUT_GROUP = 0x0009e,         ///< Invalid group id in forward action
    BA_MATCH_INCONSISTENT = 0x000a,     ///< Action can't apply for this match
    BA_UNSUPPORTED_ORDER = 0x000b,      ///< Action order is unsupported for the action
                                        ///< list in an Apply-Actions instruction
    BA_BAD_TAG = 0x000c                 ///< Actions uses an unsupported tag/encap.
  };

  enum Bad_instruction : uint16_t {
    BI_UNKNOWN_INST = 0x0000,         ///< Unknown instruction
    BI_UNSUP_INST = 0x0001,           ///< Switch or table does not support the instruction
    BI_BAD_TABLE_ID = 0x0002,         ///< Invalid Table-ID specified
    BI_UNSUP_METADATA = 0x0003,       ///< Metadata value unsupported by datapath
    BI_UNSUP_METADATA_MASK = 0x0004,  ///< Metadata mask value unsupported by datapath
    BI_UNSUP_EXP_LIST = 0x0005,       ///< Specific experimenter instruction unsupported
  };

  enum Bad_match : uint16_t {
    BM_BAD_TYPE = 0x0000,         ///< Unsupported match type specified by the match
    BM_BAD_LEN = 0x0001,          ///< Length problem in match
    BM_BAD_TAG = 0x0002,          ///< Match uses an unsupported tag/encap
    BM_BAD_DL_ADDR_MASK = 0x0003, ///< Unsupported datalink addr mask - switch does
                                  ///< not support arbitrary datalink address
                                  ///< mask.
    BM_BAD_HW_ADDR_MASK = 0x0004, ///< Unsupported network addr mask - switch does
                                  ///< not support arbitrary network address
                                  ///< mask.
    BM_BAD_WILDCARDS = 0x0005,    ///< Unsupported wildcard specified in the match
    BM_BAD_FIELD = 0x0006,        ///< Unsupported field in the match
    BM_BAD_VALUE = 0x0007         ///< Unsupported value in a match field
  };

  enum Flow_mod_failed : uint16_t {
    FMF_UNKNOWN = 0x0000,       ///< Unspecified error
    FMF_TABLE_FULL = 0x0001,    ///< Flow not added because table was full
    FMF_BAD_TABLE_ID = 0x0002,  ///< Table does not exist
    FMF_OVERLAP = 0x0003,       ///< Attempted to add overlapping flow with
                                ///< CHECK_OVERLAP flag set.
    FMF_EPERM = 0x0004,         ///< Permissions error
    FMF_BAD_TIMEOUT = 0x0005,   ///< Flow not added because of unsupported
                                ///< idle/hard timeout.
    FMF_BAD_COMMAND = 0x0006,   ///< Unsupported or unknown command
  };

  enum Group_mod_failed : uint16_t {
    GMF_GROUP_EXISTS = 0x0000,          ///< Group not added because a group ADD
                                        ///< attempted to replace an
                                        ///< already-present group
    GMF_INVALID_GROUP = 0x0001,         ///< Group not added because Group specified
                                        ///< is invalid.
    GMF_WEIGHT_UNSUPPORTED = 0x0002,    ///< Switch does not support unequal load
                                        ///< sharing with select groups
    GMF_OUT_OF_GROUPS = 0x0003,         ///< The group table is full
    GMF_OUT_OF_BUCKETS = 0x0004,        ///< The maximum number of action buckets
                                        ///< for a group has been exceeded.
    GMF_CHAINING_UNSUPPORTED = 0x0005,  ///< Switch does not support groups that
                                        ///< forward to groups
    GMF_WATCH_UNSUPPORTED = 0x0006,     ///< This group cannot watch the
                                        ///< watch_port or watch_group specified
    GMF_LOOP = 0x0007,                  ///< Group entry would cause a loop
    GMF_UNKNOWN_GROUP = 0x0008          ///< Group not modified because a group
                                        ///< MODIFY attempted to modify a
                                        ///< non-existent group
  };

  enum Port_mod_failed : uint16_t {
    PMF_BAD_PORT = 0x0000,      ///< Specified port number does not exist
    PMF_BAD_HW_ADDR = 0x0001,   ///< Specified hardware address does not
                                ///< match the port number
    PMF_BAD_CONFIG = 0x0002,    ///< Specified config is invalid
    PMF_BAD_ADVERTISE = 0x0003  ///< Specified advertise is invalid
  };

  enum Table_mod_failed : uint16_t {
    TMF_BAD_TABLE = 0x0000,   ///< Specified table does not exist
		TMF_BAD_CONFIG = 0x0001   ///< Specified config is invalid
  };

  enum Queue_op_failed : uint16_t {
    QOF_BAD_PORT = 0x0000,    ///< Invalid port (or port does not exist)
		QOF_BAD_QUEUE = 0x0001,   ///< Queue does not exist
		QOF_EPERM = 0x0002        ///< Permissions error
  };

  enum Switch_config_failed : uint16_t {
    SCF_BAD_FLAGS = 0x0000,   ///< Specified flags is invalid
		SCF_BAD_LEN = 0x0001      ///< Specified len is invalid
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
    uint16_t             value; // Uninterpreted value
  };

  Error() = default;
  
  /// Constructs a hello failed Error message. Initialize the error message with
  /// a Hello_failed code f and the error buffer b.
  Error(Hello_failed f, const Greedy_buffer& b)
    : type(HELLO_FAILED), code(f), data() { }
  
  /// Constructs a bad request Error message. Initialize the error message with
  /// a Bad_request code f and the error buffer b.
  Error(Bad_request f, const Greedy_buffer& b)
    : type(BAD_REQUEST), code(f), data() { }
  
  /// Constructs a bad action Error messasge. Initialize the error message with
  /// a Bad_action code f and the error buffer b.
  Error(Bad_action f, const Greedy_buffer& b)
    : type(BAD_ACTION), code(f), data() { }
  
  /// Constructs a bad instruction Error messasge. Initialize the error message with
  /// a Bad_instruction code f and the error buffer b.
  Error(Bad_instruction f, const Greedy_buffer& b)
    : type(BAD_INSTRUCTION), code(f), data() { }
  
  /// Constructs a bad match Error messasge. Initialize the error message with
  /// a Bad_match code f and the error buffer b.
  Error(Bad_match f, const Greedy_buffer& b)
    : type(BAD_MATCH), code(f), data() { }
  
  /// Constructs a flow modification Error message. Initialize the error message
  /// with a Flow_mod_failed code f and the error buffer b.
  Error(Flow_mod_failed f, const Greedy_buffer& b)
    : type(FLOW_MOD_FAILED), code(f), data() { }
  
  /// Constructs a group modification Error message. Initialize the error message
  /// with a Group_mod_failed code f and the error buffer b.
  Error(Group_mod_failed f, const Greedy_buffer& b)
    : type(GROUP_MOD_FAILED), code(f), data() { }
  
  /// Constructs a port modification Error message. Initialize the error message
  /// with a Port_mod_failed code f and the error buffer b.
  Error(Port_mod_failed f, const Greedy_buffer& b)
    : type(PORT_MOD_FAILED), code(f), data() { }
  
  /// Constructs a table modification Error message. Initialize the error message
  /// with a Table_mod_failed code f and the error buffer b.
  Error(Table_mod_failed f, const Greedy_buffer& b)
    : type(TABLE_MOD_FAILED), code(f), data() { }
  
  /// Constructs a queue operation Error message. Initialize the error message
  /// with a Queue_op_failed code f and the error buffer b.
  Error(Queue_op_failed f, const Greedy_buffer& b)
    : type(QUEUE_OP_FAILED), code(f), data() { }

  /// Constructs a Switch config failed Error message. Initialize the error message
  /// with a Switch_config_failed code f and the error buffer b.
  Error(Switch_config_failed f, const Greedy_buffer& b)
    : type(SWITCH_CONFIG_FAILED), code(f), data() { }
  
  /// Constructs an error from an Error::Type and code. Initialize the error
  /// message with error type t, the error Code c, and the error buffer b. Note
  /// that the value is ill-formed if c  is not a valid code for the error type
  /// t.
  Error(Type t, uint16_t c, const Greedy_buffer& b)
    : type(t), code(c), data(b) { assert(is_valid(*this)); }

  Type type;
  Code code;
  Greedy_buffer data; ///<Variable-length data. Interpreted based on the type and code.
};

/// Returns true when the arguments compare equal. Two Error messages compare
/// equal when they report the same error for the same uninterpreted data.
///
/// \relates Error
bool operator==(const Error& a, const Error& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Error
bool operator!=(const Error& a, const Error& b);

/// Returns the number of bytes needed to repersent an Error message.
///
/// \relates Error
std::size_t bytes(const Error& e);

/// Validates the value of an Error::Type object.
///
/// \relates Error::Type
Error_condition is_valid(const Error::Type t);

/// Validates the value of an Error::Hello_failed object.
///
/// \relates Error::Hello_failed
Error_condition is_valid(const Error::Hello_failed c);

/// Validates the value of an Error::Bad_request object.
///
/// \relates Error::Bad_request
Error_condition is_valid(const Error::Bad_request c);

/// Validates the value of an Error::Bad_action object.
///
/// \relates Error::Bad_action
Error_condition is_valid(const Error::Bad_action c);

/// Validates the value of an Error::Bad_instruction object.
///
/// \relates Error::Bad_instruction
Error_condition is_valid(const Error::Bad_instruction c);

/// Validates the value of an Error::Bad_match object.
///
/// \relates Error::Bad_match
Error_condition is_valid(const Error::Bad_match c);

/// Validates the value of an Error::Flow_mod_failed object.
///
/// \relates Error::Flow_mod_failed
Error_condition is_valid(const Error::Flow_mod_failed c);

/// Validates the value of an Error::Group_mod_failed object.
///
/// \relates Error::Group_mod_failed
Error_condition is_valid(const Error::Group_mod_failed c);

/// Validates the value of an Error::Port_mod_failed object.
///
/// \relates Error::Port_mod_failed
Error_condition is_valid(const Error::Port_mod_failed c);

/// Validates the value of an Error::Table_mod_failed object.
///
/// \relates Error::Table_mod_failed
Error_condition is_valid(const Error::Table_mod_failed c);

/// Validates the value of an Error::Queue_op_failed object.
///
/// \relates Error::Queue_op_failed
Error_condition is_valid(const Error::Queue_op_failed c);

/// Validates the value of an Error::Swtich_config_failed object.
///
/// \relates Error::Swtich_config_failed
Error_condition is_valid(const Error::Switch_config_failed c);

/// Validates the value of an Error message based on error type and code
///
/// \relates Error
Error_condition is_valid(const Error::Type t, const Error::Code c);

/// Validates the value of an Error message.
///
/// \relates Error
Error_condition is_valid(const Error& e);

/// Writes an Error message into a Buffer_view.
///
/// \relates Error
Error_condition to_buffer(Buffer_view&, const Error&);

/// Reads an Error message from a Buffer_view.
///
/// \relates Error
Error_condition from_buffer(Buffer_view&, Error&);

/// Returns a formatted string representation of an Error_message value.
///
/// \relates Error
std::string to_string(const Error&, Formatter&);

/// Returns a string representation of an Error::Type value.
///
/// \relates Error::Type
std::string to_string(Error::Type);

/// Returns a string representation of an Error::Hello_failed value.
///
/// \relates Error::Hello_failed
std::string to_string(Error::Hello_failed);

/// Returns a string representation of an Error::Bad_request value.
///
/// \relates Error::Bad_request
std::string to_string(Error::Bad_request);

/// Returns a string representation of an Error::Bad_action value.
///
/// \relates Error::Bad_action
std::string to_string(Error::Bad_action);

/// Returns a string representation of an Error::Bad_instruction value.
///
/// \relates Error::Bad_instruction
std::string to_string(Error::Bad_instruction);

/// Returns a string representation of an Error::Bad_match value.
///
/// \relates Error::Bad_match
std::string to_string(Error::Bad_match);

/// Returns a string representation of an Error::Flow_mod_failed value.
///
/// \relates Error::Flow_mod_failed
std::string to_string(Error::Flow_mod_failed);

/// Returns a string representation of an Error::Group_mod_failed value.
///
/// \relates Error::Group_mod_failed
std::string to_string(Error::Group_mod_failed);

/// Returns a string representation of an Error::Port_mod_failed value.
///
/// \relates Error::Port_mod_failed
std::string to_string(Error::Port_mod_failed);

/// Returns a string representation of an Error::Table_mod_failed value.
///
/// \relates Error::Table_mod_failed
std::string to_string(Error::Table_mod_failed);

/// Returns a string representation of an Error::Queue_op_failed value.
///
/// \relates Error::Queue_op_failed
std::string to_string(Error::Queue_op_failed);

/// Returns a string representation of an Error::Swtich_config_failed value.
///
/// \relates Error::Switch_config_failed
std::string to_string(Error::Switch_config_failed);

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

/// Returns true when the arguments compare equal. Two Echo_base messages
/// compare equal when they have same data
/// 
/// \relates Echo_base
template<Message_type K>
  bool operator==(const Echo_base<K>& a, const Echo_base<K>& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Echo_base
template<Message_type K>
  bool operator!=(const Echo_base<K>& a, const Echo_base<K>& b);

/// Returns the number of bytes needed to repersent an Echo_req or 
/// Echo_res message.
///
/// \relates Echo_base
template<Message_type K>
  std::size_t bytes(const Echo_base<K>& e);

/// Validates the value of an Echo_req or Echo_res message.
///
/// \relates Echo_base
template<Message_type K>
  constexpr Error_condition is_valid(const Echo_base<K>&);

/// Writes an Echo_req or Echo_res message into a Buffer_view.
///
/// \relates Echo_base
template<Message_type K>
  Error_condition to_buffer(Buffer_view& v, const Echo_base<K>& e);

/// Reads an Echo_req or Echo_res message from a Buffer_view.
///
/// \relates Echo_base
template<Message_type K>
  Error_condition from_buffer(Buffer_view& v, Echo_base<K>& e);

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
/// \remark Defined in [OpenFlow v1.1, p55](http://...)
struct Echo_req : Echo_base<ECHO_REQ> 
{ 
  using Echo_base<ECHO_REQ>::Echo_base;
};

// -------------------------------------------------------------------------- //
// Echo Res

/// Sent by the switch to exchange information about latency, bandwidth, and
/// liveness. The EchoRes message is used to exchange information about latency,
/// bandwidth, and liveness. Request timeouts indicate a disconnection. The
/// response contains a copy of the data sent by the request.
///
///
/// \remark Defined in [OpenFlow v1.1, p56](http://...)
struct Echo_res : Echo_base<ECHO_RES> 
{ 
  using Echo_base<ECHO_RES>::Echo_base;
};

// -------------------------------------------------------------------------- //
// Experimenter

/// Represents a proprietary messages within the protocol. the
/// Vendor/Experimenter message is a mechanism for creating proprietary messages
/// within the protocol. In v1.0 this was called Vendor; however, in subsequent
/// versions the name was changed to experimenter.
/// 
/// \remark Defined in [OpenFlow v1.1, p56](http://...)
struct Experimenter : Payload_base<EXPERIMENTER>
{
  Experimenter() = default;
  
  /// Construct the experimenter struct with an exerpimenter_id and buffer of
  /// data
  Experimenter(uint32_t eid, Greedy_buffer b)
    : experimenter_id(eid), data(b) { }

  uint32_t experimenter_id;
  Greedy_buffer data;
};

/// Returns true when the arguments compare equal. Two Experimenter messages, a
/// and b, compare equal when they have the same vendor id and uninterpeted
/// data.
///
/// \relates Experimenter
bool operator==(const Experimenter& a, const Experimenter& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Experimenter
bool operator!=(const Experimenter& a, const Experimenter& b);

/// Return number of bytes of an Experimenter message.
///
/// \relates Experimenter
std::size_t bytes(const Experimenter& e);

/// Validates the value of a Experimenter message. 
///
/// \relates Experimenter
constexpr Error_condition is_valid(const Experimenter&);

/// Writes a Experimenter message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Experimenter
Error_condition to_buffer(Buffer_view&, const Experimenter&);

/// Reads a Experimenter message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Experimenter
Error_condition from_buffer(Buffer_view&, Experimenter&);

/// Returns a formatted string representation of the value.
///
/// \relates Experimenter
std::string to_string(const Experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// Features Request

/// Sent by the controller to the switch. A Features Request is required by 
/// OpenFlow protocol to be sent at handshake phase. The controller respond
/// with a Features Reply that contains the features of switch
///
/// The Features Request message contains nothing but an OpenFlow header
///
/// \remark Defined in [OpenFlow v1.1, p36]
struct Feature_req : Payload_base<FEATURE_REQ> { };

// -------------------------------------------------------------------------- //
// Feature Response

/// Sent by the switch to the controller as reply to a Features Request message.
/// Contains the features supported by the switch.
///
/// \remark Defined in [OpenFlow v1.1, p36]
struct Feature_res : Payload_base<FEATURE_RES>
{
  enum Capability : uint32_t {
    FLOW_STATS = 0x00000001,    ///< Flow statistics
		TABLE_STATS = 0x00000002,   ///< Table statistics
    PORT_STATS = 0x00000004,    ///< Port statistics
		GROUP_STATS = 0x00000008,   ///< Group statistics
    IP_REASM = 0x00000020,      ///< Can reassemble IP fragments
		QUEUE_STATS = 0x00000040,   ///< Queue statistics
    ARP_MATCH_IP = 0x00000080   ///< Match IP addresses in ARP pkts
  };

  Feature_res() = default;

  /// Construct Feature_res with datapath_id, n_buffers, n_tables, 
  /// capabilities, reserved and port values
  Feature_res(uint64_t did, uint32_t nb, uint8_t nt, Capability c,
              uint32_t r, const Sequence<Port>& p)
    : datapath_id(did), n_buffers(nb), n_tbls(nt), capabilities(c),
      reserved(r), ports(p) { }

  uint64_t datapath_id;
  uint32_t n_buffers;
  uint8_t n_tbls;
  Capability capabilities;
  uint32_t reserved;
  Sequence<Port> ports;
};

/// Returns true when the arguments compare equal. Two Feature_res messages 
/// a and b compare equal when all the fields compare equal.
///
/// \relates Feature_res
bool operator==(const Feature_res& a, const Feature_res& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Feature_res
bool operator!=(const Feature_res& a, const Feature_res& b);

/// Returns the number of bytes needed to represent a Feature_res Message.  
///
/// \relates Feature_res
std::size_t bytes(const Feature_res& fr);

Error_condition is_valid(const Feature_res::Capability& c);

/// Validates the value of a Feature_res message. 
///
/// \relates Feature_res
Error_condition is_valid(const Feature_res& fr);

/// Writes a Feature_res message into a Buffer_view. If the write does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Feature_res
Error_condition to_buffer(Buffer_view&, const Feature_res&);

/// Reads a Feature_res message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Feature_res
Error_condition from_buffer(Buffer_view&, Feature_res&);

/// Returns a formatted string representation of the value.
///
/// \relates Hello
std::string to_string(const Feature_res&, Formatter&);

std::string to_string(Feature_res::Capability);

bool feature_res_capabilities_flow_stats(uint32_t c);

bool feature_res_capabilities_table_stats(uint32_t c);

bool feature_res_capabilities_port_stats(uint32_t c);

bool feature_res_capabilities_group_stats(uint32_t c);

bool feature_res_capabilities_ip_reasm(uint32_t c);

bool feature_res_capabilities_queue_stats(uint32_t c);

bool feature_res_capabilities_arp_match_ip(uint32_t c);

// -------------------------------------------------------------------------- //
// Get Config Request

/// Sent by the controller to the switch to request current configuration
/// of the switch.
///
/// Get_config_req message contains nothing but OpenFlow header.
///
/// \remark Defined in [OpenFlow v1.1, p37]
struct Get_config_req : Payload_base<GET_CONFIG_REQ> { };

// -------------------------------------------------------------------------- //
// Config Message Base

/// The base class for Get Config Response and Set Config messages. 
///
/// \remark Describes ofp_switch_config in OpenFlow protocol
template<Message_type T>
  struct Config_message_base
  {
    enum Flags : uint16_t {
      FRAG_NORMAL = 0x0000,               ///< No special handling for fragments
      FRAG_DROP = 0x0001,                 ///< Drop fragments.
      FRAG_REASM = 0x0002,                ///< Reassemble (only if OFPC_IP_REASM set)
      FRAG_MASK = 0x0003,                
      INVALID_TTL_TO_CONTROLLER = 0x0004  ///< Send packets with invalid TTL
                                          ///< ie. 0 or 1 to controller
    };

    Config_message_base() = default;

    /// Construct a Config_message_base struct with flags and miss_send_len
    Config_message_base(Flags f, uint16_t msl)
      : flags(f), miss_send_len(msl) { }

    Flags flags;              ///< OFPC_* flags
    uint16_t miss_send_len;   ///< Max bytes of new flow that datapath should
                              ///< send to the controller
  };

/// Returns true when the arguments compare equal. 
///
/// \relates Config_message_base
template<Message_type T>
  bool
  operator==(const Config_message_base<T>& a, const Config_message_base<T>& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Config_message_base
template<Message_type T>
  bool
  operator!=(const Config_message_base<T>& a, const Config_message_base<T>& b);

/// Returns the number of bytes needed to represent a Hello value. 
///
/// \relates Config_message_base
template<Message_type T>
  constexpr std::size_t bytes(const Config_message_base<T>&);

/// Validates the value of a Config_message_base message. 
///
/// \relates Config_message_base
template<Message_type T>
  Error_condition is_valid(const Config_message_base<T>& c);

/// Writes a Config_message_base message into a Buffer_view. If the write does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Config_message_base
template<Message_type T>
  Error_condition to_buffer(Buffer_view& v, const Config_message_base<T>& m);

/// Reads a Config_message_base message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Config_message_base
template<Message_type T>
  Error_condition from_buffer(Buffer_view& v, Config_message_base<T>& m);

template<Message_type T>
  bool config_frag_normal(typename Config_message_base<T>::Flags ft);

template<Message_type T>
  bool config_frag_drop(typename Config_message_base<T>::Flags ft);

template<Message_type T>
  bool config_frag_reasm(typename Config_message_base<T>::Flags ft);

template<Message_type T>
  bool config_invalid_ttl_to_controller(typename
                                        Config_message_base<T>::Flags ft);

// -------------------------------------------------------------------------- //
// Get Config Response

/// Sent by the switch to the controller as reply to Get Config Request
/// message. It contiains the current configuration of the switch
///
/// \remark Defined in [OpenFlow v1.1, p37]
struct Get_config_res : Config_message_base<GET_CONFIG_RES> { };

std::string to_string(const Get_config_res&, Formatter& f);

// -------------------------------------------------------------------------- //
// Set Config

/// Sent by the controller to the switch to modify the current configuration
/// of the switch
///
/// \remark Defined in [OpenFlow v1.1, p37]
struct Set_config : Config_message_base<SET_CONFIG> { };

std::string to_string(const Set_config&, Formatter& f);

// -------------------------------------------------------------------------- //
// Packet In

/// Sent by the switch to the controller as a consequence of Output action
/// towards the controller or a table miss.
///
/// Packet In message contains the packet (or part of the packet) and some
/// information related to the packet (incoming port, length, reason of forwarding
/// to controller, etc).
///
/// \remark Defined in [OpenFlow v1.1, p50]
struct Packet_in : Payload_base<PACKET_IN>
{
  enum Reason : uint8_t {
    NO_MATCH = 0x00,  ///< Packet-in reason is table miss
    ACTION = 0x01     ///< Packet-in reason is by action
  };

  /// Construct an empty Packet_in message
  Packet_in() = default;

  /// Construct a Packet_in message with value of all the fields
  Packet_in(uint32_t bid, uint32_t ip, uint32_t ipp, uint16_t tl,
            Reason r, uint8_t tid, Buffer d)
    : buffer_id(bid), in_port(ip), in_phy_port(ipp), total_len(tl),
      reason(r), tbl_id(tid), data(d) { }

  uint32_t buffer_id;
  uint32_t in_port;
  uint32_t in_phy_port;
  uint16_t total_len;
  Reason   reason;
  uint8_t  tbl_id;
  Buffer   data;
};

/// Returns true when two Packet_in are totally equal. 
///
/// \relates Packet_in
bool operator==(const Packet_in& a, const Packet_in& b);

/// Returns true when two Packet_in structs do not compare equal.
///
/// \relates Packet_in
bool operator!=(const Packet_in& a, const Packet_in& b);

/// Return number of bytes of an Packet_in message.
///
/// \relates Packet_in
std::size_t bytes(const Packet_in& pi);

Error_condition is_valid(const Packet_in::Reason r);

/// Validates the value of a Packet_in message. 
///
/// \relates Packet_in
Error_condition is_valid(const Packet_in& p);

/// Writes a Packet_in message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Packet_in
Error_condition to_buffer(Buffer_view&, const Packet_in&);

/// Reads a Packet_in message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Packet_in
Error_condition from_buffer(Buffer_view&, Packet_in&);

/// Returns a formatted string representation of Packet_in.
///
/// \relates Packet_in
std::string to_string(const Packet_in&, Formatter&);

std::string to_string(Packet_in::Reason);

// -------------------------------------------------------------------------- //
// Flow Removed

/// The message is sent by the switch to the controller to notify a flow being
/// removed from the tables in the switch. The possible reason for it could
/// be a timeout or a deletion operation.
///
/// \remark Defined in [OpenFlow v1.1, p51]
struct Flow_removed : Payload_base<FLOW_REMOVED>
{
  enum Reason : uint8_t {
    IDLE_TIMEOUT = 0x00,  ///< Flow idle time exceeded idle_timeout
		HARD_TIMEOUT = 0x01,  ///< Time exceeded hard_timeout
		DELETE = 0x02,        ///< Evicted by a DELETE flow mod
    GROUP_DELETE = 0x03   ///< Group was removed
  };

  /// Construct an empty Flow_removed struct
  Flow_removed() = default;

  /// Construct a Flow_removed struct with values of all the fields
  Flow_removed(uint64_t c, uint16_t p, Reason r, uint8_t tid,
               uint32_t ds, uint32_t dn, uint16_t it, uint64_t pc,
               uint64_t bc, Match m)
    : cookie(c), priority(p), reason(r), table_id(tid), duration_sec(ds),
      duration_nsec(dn), idle_timeout(it), packet_count(pc), byte_count(bc),
      match(m) { };

  uint64_t cookie;        ///< Opaque controller-issued identifier
  uint16_t priority;      ///< Priority level of flow entry
  Reason reason;          ///< One of OFPRR_*
  uint8_t table_id;       ///< ID of the table
  uint32_t duration_sec;  ///< Time flow was alive in seconds
  uint32_t duration_nsec; ///< Time flow was alive in nanoseconds beyond duration_sec
  uint16_t idle_timeout;  ///< Idle timeout from original flow mod
  uint64_t packet_count;  ///< Number of packets associated with the flow
  uint64_t byte_count;    ///< Number of bytes associated with the flow
  Match match;            ///< Description of fields
};

/// Returns true when two Flow_removed structs do not compare equal.
///
/// \relates Flow_removed
bool operator==(const Flow_removed& a, const Flow_removed& b);

/// Returns true when two Flow_removed structs do not compare equal.
///
/// \relates Flow_removed
bool operator!=(const Flow_removed& a, const Flow_removed& b);

/// Return number of bytes of an Flow_removed message.
///
/// \relates Flow_removed
std::size_t bytes(const Flow_removed& fr);

Error_condition is_valid(const Flow_removed::Reason r);

/// Validates the value of a Flow_removed message. 
///
/// \relates Flow_removed
Error_condition is_valid(const Flow_removed& f);

/// Writes a Flow_removed message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Flow_removed
Error_condition to_buffer(Buffer_view&, const Flow_removed&);

/// Reads a Flow_removed message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Flow_removed
Error_condition from_buffer(Buffer_view&, Flow_removed&);

/// Returns a formatted string representation of Flow_removed.
///
/// \relates Flow_removed
std::string to_string(const Flow_removed&, Formatter&);

std::string to_string(Flow_removed::Reason);

// -------------------------------------------------------------------------- //
// Port Status

/// The message is sent from the switch to the controller to inform addition,
/// remove or modification of ports from the datapath. 
///
/// \remark Defined in [OpenFlow v1.1, p51]
struct Port_status : Payload_base<PORT_STATUS>
{
  enum Reason : uint8_t {
    ADD = 0x00, DELETE = 0x01, MODIFY = 0x02
  };

  /// Contruct an empty Port_status
  Port_status() = default;

  /// Construct a Port_status with value of all the fields
  Port_status(Reason r, Port p) : reason(r), port(p) { }

  Reason reason;
  Port port;
};

/// Returns true when two Port_status are totally equal. 
///
/// \relates Port_status
bool operator==(const Port_status& a, const Port_status& b);

/// Returns true when two Port_status structs do not compare equal.
///
/// \relates Port_status
bool operator!=(const Port_status& a, const Port_status& b);

/// Return number of bytes of an Port_status message.
///
/// \relates Port_status
std::size_t bytes(const Port_status& ps);

Error_condition is_valid(const Port_status::Reason r);

/// Validates the value of a Port_status message. 
///
/// \relates Port_status
Error_condition is_valid(const Port_status& p);

/// Writes a Port_status message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Port_status
Error_condition to_buffer(Buffer_view&, const Port_status&);

/// Reads a Port_status message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Port_status
Error_condition from_buffer(Buffer_view&, Port_status&);

/// Returns a formatted string representation of Port_status.
///
/// \relates Port_status
std::string to_string(const Port_status&, Formatter&);
std::string to_string(Port_status::Reason);

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
/// \remark Defined in [OpenFlow v1.1, p49]
struct Packet_out : Payload_base<PACKET_OUT>
{
  /// Construct an empty Port_out message
  Packet_out() = default;

  /// Construct a Port_out message with value of all the fields
  Packet_out(uint32_t bid, uint32_t ip, uint16_t al, Sequence<Action> a,
             Greedy_buffer d)
    : buffer_id(bid), in_port(ip), actions_len(al), actions(a), data(d) { }

  uint32_t buffer_id;
  uint32_t in_port;
  uint16_t actions_len;
  Sequence<Action> actions;
  Greedy_buffer data;
};


/// Returns true when two Packet_out are totally equal. 
///
/// \relates Packet_out
bool operator==(const Packet_out& a, const Packet_out& b);

/// Returns true when two Packet_out structs do not compare equal.
///
/// \relates Packet_out
bool operator!=(const Packet_out& a, const Packet_out& b);

/// Return number of bytes of an Packet_out message.
///
/// \relates Packet_out
std::size_t bytes(const Packet_out& po);

/// Validates the value of a Packet_out message. 
///
/// \relates Packet_out
Error_condition is_valid(const Packet_out& p);

/// Writes a Packet_out message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Packet_out
Error_condition to_buffer(Buffer_view&, const Packet_out&);

/// Reads a Packet_out message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Packet_out
Error_condition from_buffer(Buffer_view&, Packet_out&);

/// Returns a formatted string representation of Packet_out.
///
/// \relates Packet_out
std::string to_string(const Packet_out&, Formatter&);

// -------------------------------------------------------------------------- //
// Flow_mod

/// Sent by the controller to modify the state of an OpenFlow switch. This is 
/// one of the main messages, it allows the controller to modify the
/// state of an OpenFlow switch.
/// 
/// \remark Defined in [OpenFlow v1.1, p39]
struct Flow_mod : Payload_base<FLOW_MOD>
{
  enum Command : uint8_t {
    ADD = 0x00,
		MODIFY = 0x01,
		MODIFY_STRICT = 0x02,
		DELETE = 0x03,
    DELETE_STRICT = 0x04
  };

  enum Flags : uint16_t {
    SEND_FLOW_REM = 0x0001,
		CHECK_OVERLAP = 0x0002
  };

  /// Construct an empty Flow_mod message
  Flow_mod() = default;

  /// Construct a Flow_mod message with value of all the fields
  Flow_mod(uint64_t ck, uint64_t ckm, uint8_t tid, Command cmd,
           uint16_t it, uint16_t ht, uint16_t p, uint32_t bid, uint32_t op,
           uint32_t og, Flags f, const Match& m,
           const Sequence<Instruction>& i)
    : cookie(ck), cookie_mask(ckm), table_id(tid), command(cmd),
      idle_timeout(it), hard_timeout(ht), priority(p), buffer_id(bid),
      out_port(op), out_group(og), flags(f), match(m), instructions(i) { }

  uint64_t cookie;
  uint64_t cookie_mask;
  uint8_t table_id;
  Command command;
  uint16_t idle_timeout;
  uint16_t hard_timeout;
  uint16_t priority;
  uint32_t buffer_id;
  uint32_t out_port;
  uint32_t out_group;
  Flags flags;
  Match match;
  Sequence<Instruction> instructions;
};

/// Returns true when two Flow_mod are totally equal. 
///
/// \relates Flow_mod
bool operator==(const Flow_mod& a, const Flow_mod& b);

/// Returns true when two Flow_mod structs do not compare equal.
///
/// \relates Flow_mod
bool operator!=(const Flow_mod& a, const Flow_mod& b);

/// Return number of bytes of an Flow_mod message.
///
/// \relates Flow_mod
std::size_t bytes(const Flow_mod& fm);

Error_condition is_valid(const Flow_mod::Command t);

Error_condition is_valid(const Flow_mod::Flags t);

/// Validates the value of a Flow_mod message. 
///
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod& f);

/// Writes a Flow_mod message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Flow_mod
Error_condition to_buffer(Buffer_view&, const Flow_mod&);

/// Reads a Flow_mod message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Flow_mod
Error_condition from_buffer(Buffer_view&, Flow_mod&);

/// Returns a formatted string representation of Flow_mod.
///
/// \relates Flow_mod
std::string to_string(const Flow_mod&, Formatter&);
std::string to_string(Flow_mod::Command);
std::string to_string(Flow_mod::Flags);

// -------------------------------------------------------------------------- //
// Group Mod

/// The Group Mod message is sent by the controller to the switch to modify
/// the group table of the switch.
///
/// \remark Defined in [OpenFlow v1.1, p41]
struct Group_mod : Payload_base<GROUP_MOD>
{
  enum Command : uint16_t {
    ADD = 0x0000,
		MODIFY = 0x0001,
		DELETE = 0x0002
  };

  enum Type : uint8_t {
    ALL = 0x00,
		SELECT = 0x01,
		INDIRECT = 0x02,
		FF = 0x03
  };

  /// Construct an empty Group_mod message
  Group_mod() = default;

  /// Construct a Group_mod message with value of all the fields
  Group_mod(Command c, Type t, uint32_t gid,
            const Sequence<Bucket>& b)
    : command(c), type(t), group_id(gid), buckets(b) { };

  Command command;
  Type type;
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

Error_condition is_valid(const Group_mod::Command c);

Error_condition is_valid(const Group_mod::Type v);

/// Validates the value of a Group_mod message. 
///
/// \relates Group_mod
Error_condition is_valid(const Group_mod& gm);
 
/// Returns a formatted string representation of Group_mod.
///
/// \relates Group_mod
std::string to_string(const Group_mod&, Formatter&);
std::string to_string(Group_mod::Command);
std::string to_string(Group_mod::Type);

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

// -------------------------------------------------------------------------- //
// Port Mod

/// The Port Mod message is sent by the controller to the switch to modify the
/// behavior of the port
/// 
/// \remark Defined in [OpenFlow v1.1 p42]
struct Port_mod : Payload_base<PORT_MOD>
{
  enum Config : uint32_t {
    PORT_DOWN = 0x00000001,
		NO_RECV = 0x00000004,
		NO_FWD = 0x00000020,
    NO_PACKET_IN = 0x00000040
  };

  /// Port features 
  enum Features : uint32_t {
    TEN_MB_HD = 0x00000001,
		TEN_MB_FD = 0x00000002,
    HUNDRED_MB_HD = 0x00000004,
		HUNDRED_MB_FD = 0x00000008,
    ONE_GB_HD = 0x00000010,
		ONE_GB_FD = 0x00000020,
    TEN_GB_FD = 0x00000040,
		FOURTY_GB_FD = 0x00000080,
    HUNDRED_GB_FD = 0x00000100,
		ONE_TB_FD = 0x00000200,
    OTHER = 0x00000400,
		COPPER = 0x00000800,
		FIBER = 0x00001000,
    AUTO_NEG = 0x00002000,
		PAUSE = 0x00004000,
		PAUSE_ASYM = 0x00008000
  };

  /// Construct an empty Port_mod message
  Port_mod() = default;

  /// Construct a Port_mod message with value of all the fields
  Port_mod(uint32_t p, Ethernet_addr ha, Config c, uint32_t m,
           Features a)
    : port(p), hw_addr(ha), config(c), mask(m), advertise(a) { };

  uint32_t port;
  Ethernet_addr hw_addr;
  Config config;
  uint32_t mask;
  Features advertise;
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
constexpr std::size_t bytes(const Port_mod&);

/// Validates the value of a Port_mod message. 
///
/// \relates Port_mod
constexpr Error_condition is_valid(const Port_mod& p);
 
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
std::string to_string(const Port_mod::Config);
std::string to_string(const Port_mod::Features);

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
/// \remark Defined in [OpenFlow v1.1, p38]
struct Table_mod : Payload_base<TABLE_MOD>
{
  enum Config : uint32_t {
    MISS_CONTROLLER = 0x00000000,
		MISS_CONTINUE = 0x00000001,
    MISS_DROP = 0x00000002,
		MISS_MASK = 0x00000003
  };

  /// Construct an empty Table_mod message
  Table_mod() = default;

  /// Construct a Table_mod message with value of all the fields
  Table_mod(uint8_t tid, Config ct)
    : table_id(tid), config(ct) { };

  uint8_t table_id;
  Config config;
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
constexpr std::size_t bytes(const Table_mod&);

Error_condition is_valid(const Table_mod::Config c);

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
std::string to_string(const Table_mod::Config);

// -------------------------------------------------------------------------- //
// Stats type

enum Stats_type : uint16_t
{
  STATS_DESC         = 0,
  STATS_FLOW         = 1,
  STATS_AGGREGATE    = 2,
  STATS_TABLE        = 3,
  STATS_PORT         = 4,
  STATS_QUEUE        = 5,
  STATS_GROUP        = 6,
  STATS_GROUP_DESC   = 7,
  STATS_EXPERIMENTER = 0xffff
};

constexpr Error_condition is_valid(const Stats_type t);

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
        cookie_mask(cm), match(m) { };

    uint8_t  table_id;
    uint32_t out_port;
    uint32_t out_group;
    uint64_t cookie;
    uint64_t cookie_mask;
    Match match;
  };

template<Stats_type K>
  bool
  operator==(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b);

template<Stats_type K>
  bool
  operator!=(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b);

template<Stats_type K>
  std::size_t bytes(const Stats_req_flow_base<K>& f);

template<Stats_type K>
  Error_condition is_valid(const Stats_req_flow_base<K>& f);

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
  explicit Stats_req_port(uint32_t p) : port_no(p) { }

  uint32_t port_no;
};

bool operator==(const Stats_req_port& a, const Stats_req_port& b);

bool operator!=(const Stats_req_port& a, const Stats_req_port& b);

constexpr std::size_t bytes(const Stats_req_port&);

constexpr Error_condition is_valid(const Stats_req_port&);

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
  Stats_req_queue(uint32_t p, uint32_t q) : port_no(p), queue_id(q) {}

  uint32_t port_no;
  uint32_t queue_id;
};

bool operator==(const Stats_req_queue& a, const Stats_req_queue& b);

bool operator!=(const Stats_req_queue& a, const Stats_req_queue& b);

constexpr std::size_t bytes(const Stats_req_queue& q);

constexpr Error_condition is_valid(const Stats_req_queue& q);

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
  explicit Stats_req_group(uint32_t gid) : group_id(gid) { }

  uint32_t group_id;
};

bool operator==(const Stats_req_group& a, const Stats_req_group& b);

bool operator!=(const Stats_req_group& a, const Stats_req_group& b);

constexpr std::size_t bytes(const Stats_req_group&);

constexpr Error_condition is_valid(const Stats_req_group&);

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
// Stats Request: Experimenter

/// Experimenter statistics
///
/// \remark Implements an OFPST_EXPERIMENTER stats request message.
struct Stats_req_experimenter : Stats_payload_base<STATS_EXPERIMENTER>
{
  Stats_req_experimenter() = default;
  Stats_req_experimenter(uint32_t eid, Greedy_buffer b)
    : experimenter_id(eid), data(b) { }

  uint32_t experimenter_id;
  Greedy_buffer data;
};

bool operator==(const Stats_req_experimenter& a,
                const Stats_req_experimenter& b);

bool operator!=(const Stats_req_experimenter& a,
                const Stats_req_experimenter& b);

std::size_t bytes(const Stats_req_experimenter& e);

constexpr Error_condition is_valid(const Stats_req_experimenter&);

Error_condition to_buffer(Buffer_view& v, const Stats_req_experimenter& e);

Error_condition from_buffer(Buffer_view& v, Stats_req_experimenter& e);

std::string to_string(const Stats_req_experimenter&,  Formatter&);

// -------------------------------------------------------------------------- //
// Stats Request: Payload

union Stats_req_payload_data
{
  Stats_req_payload_data() { }
  ~Stats_req_payload_data() { }

  Stats_req_desc         desc;
  Stats_req_flow         flow;
  Stats_req_aggregate    aggregate;
  Stats_req_table        table;
  Stats_req_port         port;
  Stats_req_queue        queue;
  Stats_req_group        group;
  Stats_req_group_desc   group_desc;
  Stats_req_experimenter experimenter;
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
Stats_req_payload& assign(Stats_req_payload&, const Stats_req_payload&,
                          Stats_type);

void destroy(Stats_req_payload&, Stats_type);

bool equal(const Stats_req_payload&, const Stats_req_payload&, Stats_type,
           Stats_type);

std::size_t bytes(const Stats_req_payload&, Stats_type);
Error_condition is_valid(const Stats_req_payload&, Stats_type);

Error_condition to_buffer(Buffer_view&, const Stats_req_payload&, Stats_type);
Error_condition from_buffer(Buffer_view&, Stats_req_payload&, Stats_type);

std::string to_string(const Stats_req_payload&, Stats_type);

// -------------------------------------------------------------------------- //
// Stats Header

/// Describe the header of a Stats Request message
///
/// Defined in [OpenFlow v1.1, p43]
struct Stats_header
{
  enum Flags : uint16_t
  {
    MORE = 0x01
  };

  Stats_header() = default;
  Stats_header(Stats_type t, Flags f) : type(t), flags(f) { };

  template<typename T>
    Stats_header(const T& value) : type(T::kind), flags() { };

  template<typename T, typename = typename T::Tag>
    explicit Stats_header(const T& x) : type(kind_of(x)), flags() { }
  
  Stats_type type;
  Flags flags;
};

bool operator==(const Stats_header& a, const Stats_header& b);

bool operator!=(const Stats_header& a, const Stats_header& b);

constexpr std::size_t bytes(const Stats_header& h);

constexpr Error_condition is_valid(const Stats_header::Flags f);

Error_condition is_valid(const Stats_header& h);

Error_condition to_buffer(Buffer_view& v, const Stats_header& h);

Error_condition from_buffer(Buffer_view& v, Stats_header& h);

std::string to_string(const Stats_header& h,  Formatter&);
std::string to_string(Stats_header::Flags);

// -------------------------------------------------------------------------- //
// Stats Request

/// The Stats Request message is sent by the controller to the switch to obtain
/// the state of the switch. 
/// 
/// \remark Defined in [OpenFlow v1.1 p43-49]
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

bool operator==(const Stats_res_desc& a, const Stats_res_desc& b);

bool operator!=(const Stats_res_desc& a, const Stats_res_desc& b);

std::size_t bytes(const Stats_res_desc& d);

constexpr Error_condition is_valid(const Stats_res_desc& d);

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
      packet_count(pc), byte_count(bc), match(m), instructions(i) { };

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

bool operator==(const Stats_res_flow& a, const Stats_res_flow& b);

bool operator!=(const Stats_res_flow& a, const Stats_res_flow& b);

std::size_t bytes(const Stats_res_flow& f);

Error_condition is_valid(const Stats_res_flow& f);

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
  explicit Stats_res_flows(Sequence<Stats_res_flow> f) : flows(f) { }

  Sequence<Stats_res_flow> flows;
};

bool operator==(const Stats_res_flows& a, const Stats_res_flows& b);

bool operator!=(const Stats_res_flows& a, const Stats_res_flows& b);

std::size_t bytes(const Stats_res_flows& f);

Error_condition is_valid(const Stats_res_flows& f);

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
    : packet_count(pc), byte_count(bc), flow_count(fc) { };

  uint64_t packet_count;
  uint64_t byte_count;
  uint32_t flow_count;
};

bool operator==(const Stats_res_aggregate& a, const Stats_res_aggregate& b);

bool operator!=(const Stats_res_aggregate& a, const Stats_res_aggregate& b);

constexpr std::size_t bytes(const Stats_res_aggregate&);

constexpr Error_condition is_valid(const Stats_res_aggregate& a);

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

bool operator==(const Stats_res_port& a, const Stats_res_port& b);

bool operator!=(const Stats_res_port& a, const Stats_res_port& b);

constexpr std::size_t bytes(const Stats_res_port&);

constexpr Error_condition is_valid(const Stats_res_port&);

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
  explicit Stats_res_ports(Sequence<Stats_res_port> p) : ports(p) { };

  Sequence<Stats_res_port> ports;
};

bool operator==(const Stats_res_ports& a, const Stats_res_ports& b);

bool operator!=(const Stats_res_ports& a, const Stats_res_ports& b);

std::size_t bytes(const Stats_res_ports& p);

Error_condition is_valid(const Stats_res_ports& p);

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

bool operator==(const Stats_res_queue& a, const Stats_res_queue& b);

bool operator!=(const Stats_res_queue& a, const Stats_res_queue& b);

constexpr std::size_t bytes(const Stats_res_queue&);

Error_condition is_valid(const Stats_res_queue&);

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
  explicit Stats_res_queues(Sequence<Stats_res_queue> q) : queues(q) { }

  Sequence<Stats_res_queue> queues;
};

bool operator==(const Stats_res_queues& a, const Stats_res_queues& b);

bool operator!=(const Stats_res_queues& a, const Stats_res_queues& b);

std::size_t bytes(const Stats_res_queues& q);

Error_condition is_valid(const Stats_res_queues& q);

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
  Stats_res_table(uint8_t tid, const char* n, uint32_t w, uint32_t m,
                  uint32_t i, uint32_t wa, uint32_t aa, uint32_t c,
                  uint32_t me, uint32_t ac, uint64_t lc, uint64_t mc)
    : table_id(tid), name(n), wildcards(w), match(m), instructions(i),
      write_actions(wa), apply_actions(aa), config(c), max_entries(me),
      active_count(ac), lookup_count(lc), matched_count(mc) { }

  uint8_t table_id;
  Name_string name;
  uint32_t wildcards;
  uint32_t match;
  uint32_t instructions;
  uint32_t write_actions;
  uint32_t apply_actions;
  uint32_t config;
  uint32_t max_entries;
  uint32_t active_count;
  uint64_t lookup_count;
  uint64_t matched_count;
};

bool operator==(const Stats_res_table& a, const Stats_res_table& b);

bool operator!=(const Stats_res_table& a, const Stats_res_table& b);

constexpr std::size_t bytes(const Stats_res_table&);

Error_condition is_valid(const Stats_res_table&);

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
  explicit Stats_res_tables(Sequence<Stats_res_table> t) : tables(t) { };

  Sequence<Stats_res_table> tables;
};

bool operator==(const Stats_res_tables& a, const Stats_res_tables& b);

bool operator!=(const Stats_res_tables& a, const Stats_res_tables& b);

std::size_t bytes(const Stats_res_tables& t);

Error_condition is_valid(const Stats_res_tables& t);

Error_condition to_buffer(Buffer_view&, const Stats_res_tables&);

Error_condition from_buffer(Buffer_view&, Stats_res_tables&);

std::string to_string(const Stats_res_tables&, Formatter&);

// -------------------------------------------------------------------------- //
// Bucket

/// Describe stats of an individual bucket in an OFPST_GROUP Stats Response
/// message.
struct Bucket_counter
{
  Bucket_counter() = default;
  Bucket_counter(uint64_t pc, uint64_t bc)
    : packet_count(pc), byte_count(bc) { }

  uint64_t packet_count;
  uint64_t byte_count;
};

bool operator==(const Bucket_counter& a, const Bucket_counter& b);

bool operator!=(const Bucket_counter& a, const Bucket_counter& b);

constexpr std::size_t bytes(const Bucket_counter&);

constexpr Error_condition is_valid(const Bucket_counter&);

Error_condition to_buffer(Buffer_view& v, const Bucket_counter& bc);

Error_condition from_buffer(Buffer_view& v, Bucket_counter& bc);

std::string to_string(const Bucket_counter&, Formatter&);

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

bool operator==(const Stats_res_group& a, const Stats_res_group& b);

bool operator!=(const Stats_res_group& a, const Stats_res_group& b);

std::size_t bytes(const Stats_res_group& g);

Error_condition is_valid(const Stats_res_group& g);

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
  explicit Stats_res_groups(Sequence<Stats_res_group> gd) : groups(gd) { }

  Sequence<Stats_res_group> groups;
};

bool operator==(const Stats_res_groups& a, const Stats_res_groups& b);

bool operator!=(const Stats_res_groups& a, const Stats_res_groups& b);

std::size_t bytes(const Stats_res_groups& gd);

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

bool operator==(const Stats_res_group_desc& a, const Stats_res_group_desc& b);

bool operator!=(const Stats_res_group_desc& a, const Stats_res_group_desc& b);

std::size_t bytes(const Stats_res_group_desc& gd);

Error_condition is_valid(const Stats_res_group_desc& gd);

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
    : group_descs(gd) { }

  Sequence<Stats_res_group_desc> group_descs;
};

bool operator==(const Stats_res_group_descs& a, const Stats_res_group_descs& b);

bool operator!=(const Stats_res_group_descs& a, const Stats_res_group_descs& b);

std::size_t bytes(const Stats_res_group_descs& gd);

Error_condition to_buffer(Buffer_view&, const Stats_res_group_descs&);

Error_condition from_buffer(Buffer_view&, Stats_res_group_descs&);

std::string to_string(const Stats_res_group_descs&, Formatter&);

// -------------------------------------------------------------------------- //
// Stats Response: Experimenter

/// Experiimenter statistics
///
/// \remark Implements an OFPST_EXPERIMENTER Stats Response messge
struct Stats_res_experimenter : Stats_payload_base<STATS_EXPERIMENTER>
{
  Stats_res_experimenter() = default;
  Stats_res_experimenter(uint32_t eid, Greedy_buffer b)
    : experimenter_id(eid), data(b) { }
  
  uint32_t experimenter_id;
  Greedy_buffer data;
};

bool
operator==(const Stats_res_experimenter& a, const Stats_res_experimenter& b);

bool
operator!=(const Stats_res_experimenter& a, const Stats_res_experimenter& b);

std::size_t bytes(const Stats_res_experimenter& e);

Error_condition is_valid(const Stats_res_experimenter&);

Error_condition to_buffer(Buffer_view& v, const Stats_res_experimenter& e);

Error_condition from_buffer(Buffer_view& v, Stats_res_experimenter& e);

std::string to_string(const Stats_res_experimenter&,  Formatter&);

// -------------------------------------------------------------------------- //
// Stats Response: Payload

union Stats_res_payload_data
{
  Stats_res_payload_data() {}
  ~Stats_res_payload_data() {}

  Stats_res_desc         desc;
  Stats_res_flows        flow;
  Stats_res_aggregate    aggregate;
  Stats_res_tables       table;
  Stats_res_ports        port;
  Stats_res_queues       queue;
  Stats_res_groups       group;
  Stats_res_group_descs  group_desc;
  Stats_res_experimenter experimenter;
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

template<typename Tag, typename... Args>
  void construct(Stats_res_payload& p, Tag t, Args&&... args) = delete;

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

  template<typename T, typename Tag = typename T::Tag>
    explicit Stats_res(T&& x)
      : header(x) { construct(payload, Tag(), std::forward<T>(x)); }

  template<typename Tag, typename... Args>
    Stats_res(Tag t, Args&&... args)
      : header(t.value) { construct(payload, t, std::forward<Args>(args)...); }

  Header  header;
  Payload payload;
};

bool operator==(const Stats_res& a, const Stats_res& b);

bool operator!=(const Stats_res& a, const Stats_res& b);

std::size_t bytes(const Stats_res& r);

Error_condition is_valid(const Stats_res& r);

Error_condition to_buffer(Buffer_view& v, const Stats_res& r);

Error_condition from_buffer(Buffer_view& v, Stats_res& r);

std::string to_string(const Stats_res& r,  Formatter&);

// -------------------------------------------------------------------------- //
// Barrier Request

/// The Barrier Request message is sent by the controller to the switch. Any 
/// message before the barrier request must be completed processing before
/// a Barrier Response is sent back to controller and before any message
/// that arrives later than the Barrier Request.
///
/// \remark Defined in [OpenFlow v1.1, p50]
struct Barrier_req : Payload_base<BARRIER_REQ> { };

// -------------------------------------------------------------------------- //
// Barrier Response

/// The Barrier Response message is sent by the switch to the controller as
/// response to a Barrier Request message. Any message before the barrier request
/// must be completed processing before a Barrier Response is sent back to
/// controller and before any message that arrives later than the Barrier Request.
///
/// \remark Defined in [OpenFlow v1.1, p50]
struct Barrier_res : Payload_base<BARRIER_RES> { };

// -------------------------------------------------------------------------- //
// Queue Get Config Request

/// The Queue Get Config Request is sent by the controller to the switch to
/// obtain configurations of the queues in the switch.
///
/// \remark defined in [OpenFlow v1.1, p42]
struct Queue_get_config_req : Payload_base<QUEUE_GET_CONFIG_REQ>
{
  /// Construct an empty Group_mod message
  Queue_get_config_req() = default;

  /// Construct a Group_mod message with value of all the fields
  explicit Queue_get_config_req(uint32_t p) : port(p) { }

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
constexpr std::size_t bytes(const Queue_get_config_req&);

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
// Queue Get Config Repsonse

/// The Queue Get Config Response message is sent by the switch to the
/// controller as response to a Queue Get Config Request message. It contains
/// the configuration information of queues associated with the port 
/// specified in the Queue Get Config Request message.
/// 
/// \remark Defined in [OpenFlow v1.1, p43]
struct Queue_get_config_res : Payload_base<QUEUE_GET_CONFIG_RES>
{
  /// Construct an empty Queue_get_config_res message
  Queue_get_config_res() = default;

  /// Construct a Queue_get_config_res message with value of all the fields
  Queue_get_config_res(uint32_t p, Sequence<Queue> q) : port(p), queues(q) { }

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

/// Validates the value of a Queue_get_config_res message. 
///
/// \relates Queue_get_config_res
Error_condition is_valid(const Queue_get_config_res& qgcr);

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

/// Construct a payload with given Hello struct
void construct(Payload&, Hello&&);

/// Construct a payload with given Error struct
void construct(Payload&, Error&&);

/// Construct a payload with given Echo_req struct
void construct(Payload&, Echo_req&&);

/// Construct a payload with given Echo_res struct
void construct(Payload&, Echo_res&&);

/// Construct a payload with given Experimenter struct
void construct(Payload&, Experimenter&&);

/// Construct a payload with given Feature_req struct
void construct(Payload&, Feature_req&&);

/// Construct a payload with given Feature_res struct
void construct(Payload&, Feature_res&&);

/// Construct a payload with given Get_config_req struct
void construct(Payload&, Get_config_req&&);

/// Construct a payload with given Get_config_res struct
void construct(Payload&, Get_config_res&&);

/// Construct a payload with given Set_config struct
void construct(Payload&, Set_config&&);

/// Construct a payload with given Packet_in struct
void construct(Payload&, Packet_in&&);

/// Construct a payload with given Packet_out struct
void construct(Payload&, Packet_out&&);

/// Construct a payload with given Flow_mod struct
void construct(Payload&, Flow_mod&&);

/// Construct a payload with given Group_mod struct
void construct(Payload&, Group_mod&&);

/// Construct a payload with given Port_mod struct
void construct(Payload&, Port_mod&&);

/// Construct a payload with given Table_mod struct
void construct(Payload&, Table_mod&&);

/// Construct a payload with given Stats_req struct
void construct(Payload&, Stats_req&&);

/// Construct a payload with given Stats_res struct
void construct(Payload&, Stats_res&&);

/// Construct a payload with given Barrier_req struct
void construct(Payload&, Barrier_req&&);

/// Construct a payload with given Barrier_res struct
void construct(Payload&, Barrier_res&&);

/// Construct a payload with given Queue_get_config_req struct
void construct(Payload&, Queue_get_config_req&&);

/// Construct a payload with given Queue_get_config_res struct
void construct(Payload&, Queue_get_config_res&&);

/// Construct a payload with given Hello struct
void construct(Payload&, const Hello&);

/// Construct a payload with given Error struct
void construct(Payload&, const Error&);

/// Construct a payload with given Echo_req struct
void construct(Payload&, const Echo_req&);

/// Construct a payload with given Echo_res struct
void construct(Payload&, const Echo_res&);

/// Construct a payload with given Experimenter struct
void construct(Payload&, const Experimenter&);

/// Construct a payload with given Feature_req struct
void construct(Payload&, const Feature_req&);

/// Construct a payload with given Feature_res struct
void construct(Payload&, const Feature_res&);

/// Construct a payload with given Get_config_req struct
void construct(Payload&, const Get_config_req&);

/// Construct a payload with given Get_config_res struct
void construct(Payload&, const Get_config_res&);

/// Construct a payload with given Set_config struct
void construct(Payload&, const Set_config&);

/// Construct a payload with given Packet_in struct
void construct(Payload&, const Packet_in&);

/// Construct a payload with given Packet_out struct
void construct(Payload&, const Packet_out&);

/// Construct a payload with given Flow_mod struct
void construct(Payload&, const Flow_mod&);

/// Construct a payload with given Group_mod struct
void construct(Payload&, const Group_mod&);

/// Construct a payload with given Port_mod struct
void construct(Payload&, const Port_mod&);

/// Construct a payload with given Table_mod struct
void construct(Payload&, const Table_mod&);

/// Construct a payload with given Stats_req struct
void construct(Payload&, const Stats_req&);

/// Construct a payload with given Stats_res struct
void construct(Payload&, const Stats_res&);

/// Construct a payload with given Barrier_req struct
void construct(Payload&, const Barrier_req&);

/// Construct a payload with given Barrier_res struct
void construct(Payload&, const Barrier_res&);

/// Construct a payload with given Queue_get_config_req struct
void construct(Payload&, const Queue_get_config_req&);

/// Construct a payload with given Queue_get_config_res struct
void construct(Payload&, const Queue_get_config_res&);

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

template<typename T>
  struct enable_if_payload : std::enable_if<is_payload<T>::value> { };

// -------------------------------------------------------------------------- //
// Header

/// Describe the header of an OpenFlow v1.1 Message. Every OpenFlow
/// message begins with a fixed-sized header. This header describes the
/// OpenFlow protocol version, the type of message, the length in bytes
/// (inclusive of the header), and the transaction id (used to match
/// responses to requests).
///
/// \remark Defined in [OpenFlow v1.1, p24]
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
constexpr std::size_t bytes(const Header&);

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

/// Describe an OpenFlow v1.1 message. Every message consists of a
/// header and a payload. The type of payload is determined by the
/// value of the header.
struct Message
{
  /// Construct an empty Message
  Message() = default;

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

  /// Payload construction
  template<typename Tag, typename... Args>
    Message(uint32_t id, Tag t, Args&&... args);

  ~Message();

  /// Return a factory that generates OpenFlow v1.1 message
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

} // namespace v1_1
} // namespace ofp
} // namespace flog

#include "message.ipp"

#endif
