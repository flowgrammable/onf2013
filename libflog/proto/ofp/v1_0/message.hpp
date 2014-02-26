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

#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_0_HPP
#define FLOWGRAMMABLE_PROTO_OFP_V1_0_HPP

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

/// \file v1_0/message.hpp

namespace flog {
namespace ofp {
namespace v1_0 {

// Ensure overload resolution for primitive types.
using ofp::to_buffer;
using ofp::from_buffer;


// -------------------------------------------------------------------------- //
// Error code

/// Represents a specific failure in message processing. This enumeration is
/// used to describe the result values of to_buffer(), from_buffer(), and
/// is_valid().
enum Error_code { 
  // General codes
  FAILIURE = -1,           ///< General failure
  SUCCESS  = 0,            ///< Success

  // Basic codes (copied from Basic_error_code)
  AVAILABLE_BUFFER,        ///< Not enough bytes to read a buffer
  AVAILABLE_STRING,        ///< Not enough bytes to read a string

  EXCESS_SEQUENCE,         ///< Excess data in a sequence

  // Semantic codes (produced during validation)
  BAD_ACTION,              ///< Invalid value of Action_type
  BAD_ACTION_LENGTH,       ///< The action length is invalid
  BAD_ACTION_INIT,         ///< An uninitialized action was validated
  BAD_ACTION_ENQUEUE_PORT, ///< The port in Action_enqueue is invalid
  BAD_PORT_ID,             ///< The id in Port is invalid
  BAD_VERSION,             ///< The version number was not 1
  BAD_MESSAGE,             ///< Invalid vaue of Message_type
  BAD_MESSAGE_LENGTH,       ///< The header length is invalid
  BAD_MESSAGE_INIT,        ///< The message payload is not initialized
  BAD_ERROR_TYPE,          ///< Invalid value of Error::Type
  BAD_ERROR_DATA,          ///< Invalid size for Error data
  BAD_HELLO_FAILED,        ///< Invalid value of Error::Hello_failed
  BAD_BAD_REQUEST,         ///< Invalid value of Error::Bad_request
  BAD_BAD_ACTION,          ///< Invlaid value of Error::Bad_action
  BAD_FLOW_MOD_FAILED,     ///< Invlalid value of Error::Flow_mod_failed
  BAD_PORT_MOD_FAILED,     ///< Invalid value of Error::Port_mod_failed
  BAD_QUEUE_OP_FAILED,     ///< Invalid value of Error::Queue_op_failed
  BAD_FLOW_MOD_COMMAND,    ///< Invalid value of Flow_mod::Command
  BAD_FEATURE_RES_CAPABILITY,
  BAD_PACKET_IN_REASON,
  BAD_FLOW_REMOVED_REASON,
  BAD_PORT_STATUS_REASON,
  BAD_PACKET_OUT_LENGTH,
  BAD_STATS,
  BAD_STATS_INIT,
  BAD_QUEUE_PROPERTY,
  BAD_QUEUE_PROPERTY_LENGTH,
  BAD_QUEUE_PROPERTY_INIT,
  BAD_QUEUE_CONFIG_PORT,
  BAD_CONFIG,

  // Availability errors 
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
  AVAILABLE_PORT,

  AVAILABLE_HEADER,
  AVAILABLE_PAYLOAD,
  AVAILABLE_HELLO,
  AVAILABLE_ERROR,
  AVAILABLE_ECHO_REQ,
  AVAILABLE_ECHO_RES,
  AVAILABLE_VENDOR,
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
  AVAILABLE_PORT_MOD,

  AVAILABLE_STATS_REQ_DESC,
  AVAILABLE_STATS_REQ_FLOW,
  AVAILABLE_STATS_REQ_AGGREGATE,
  AVAILABLE_STATS_REQ_TABLE,
  AVAILABLE_STATS_REQ_PORT,
  AVAILABLE_STATS_REQ_QUEUE,
  AVAILABLE_STATS_REQ_VENDOR,
  AVAILABLE_STATS_REQ,

  AVAILABLE_STATS_RES_DESC,
  AVAILABLE_STATS_RES_FLOW,
  AVAILABLE_STATS_RES_FLOWS,
  AVAILABLE_STATS_RES_AGGREGATE,
  AVAILABLE_STATS_RES_TABLE,
  AVAILABLE_STATS_RES_TABLES,
  AVAILABLE_STATS_RES_PORT,
  AVAILABLE_STATS_RES_PORTS,
  AVAILABLE_STATS_RES_QUEUE,
  AVAILABLE_STATS_RES_QUEUES,
  AVAILABLE_STATS_RES_VENDOR,
  AVAILABLE_STATS_RES,

  AVAILABLE_QUEUE_PROPERTY_NONE,
  AVAILABLE_QUEUE_PROPERTY_MIN_RATE,
  AVAILABLE_QUEUE_PROPERTY_HEADER,
  AVAILABLE_QUEUE_PROPERTY_PAYLOAD,
  AVAILABLE_QUEUE_PROPERTIES,
  AVAILABLE_QUEUE,

  AVAILABLE_BARRIER_REQ,
  AVAILABLE_BARRIER_RES,
  AVAILABLE_QUEUE_GET_CONFIG_REQ,
  AVAILABLE_QUEUE_GET_CONFIG_RES,

  // View update errors
  EXCESS_ACTION,
  EXCESS_PACKET_OUT,
  EXCESS_QUEUE_PROPERTY,
  EXCESS_QUEUE,
  EXCESS_PAYLOAD
};

/// Represents the testable result of message processing functions. This
/// is the result type of the to_buffer(), from_buffer(), and is_valid()
/// operations.
using Error_condition = Condition<Error_code>;

/// Represents a variable declaration that captures an error condition.
using Error_decl = Condition_decl<Error_code>;

// -------------------------------------------------------------------------- //
// Structures
//
// The following classes are structures used by various messages:
//    - Match
//    - Port
//    - Action
//    - Queue
//    - Queue_property


// -------------------------------------------------------------------------- //
// Match

/// Represents a matching entry in a flow table. The Match class is used by
/// several messages in the protocol to refer to a single entry in in a flow 
/// table. The class specifies which fields of a packet will be matched by
/// the switch, any of which can be specified as a wildcard value.
///
/// \remark Defined in [OpenFlow v1.0, p20-21](http://...)
///
/// \todo We should have overloads for the the match itself. That is, a
/// function like matches_in_port(m) will probably be very helpful.
struct Match
{
  /// Flags that indicate which fields will match any values.
  ///
  /// \todo Document NW_SRC, NW_DST
  enum Wildcards : uint32_t
  {
    IN_PORT     = 0x00000001, ///< Any switch port
    DL_VLAN     = 0x00000002, ///< Any VLAN id
    DL_SRC      = 0x00000004, ///< Any Ethernet source address
    DL_DST      = 0x00000008, ///< Any Ethernet destination address
    DL_TYPE     = 0x00000010, ///< Any Ethernet frame type
    NW_PROTO    = 0x00000020, ///< Any IP protocol
    TP_SRC      = 0x00000040, ///< Any IP source port
    TP_DST      = 0x00000080, ///< Any IP target port
    NW_SRC      = 0x00003f00,
    NW_DST      = 0x000fb000,
    DL_VLAN_PCP = 0x00100000, ///< Any VLAN priority 
    NW_TOS      = 0x00200000, ///< Any IP ToS
    ALL         = 0x003fffff  ///< Anything
  };

  Wildcards     wildcards;
  uint16_t      in_port;
  Ethernet_addr dl_src;
  Ethernet_addr dl_dst;
  uint16_t      dl_vlan;
  uint8_t       dl_pcp;
  uint16_t      dl_type;
  uint8_t       nw_tos;
  uint8_t       nw_proto;
  Ipv4_addr     nw_src;
  Ipv4_addr     nw_dst;
  uint16_t      tp_src;
  uint16_t      tp_dst;
};

/// Returns true when the arguments compare equal. Two match values 
/// compare equal when they match the same packets (i.e., all fields compare 
/// equal).
bool operator==(const Match& a, const Match& b);

/// Returns true when the arguments do not compare equal.
bool operator!=(const Match& a, const Match& b);

/// Returns the number of bytes needed to represent a Match value.
constexpr std::size_t bytes(const Match&);

/// Validates the value of a Match object.
Error_condition is_valid(const Match& m);

/// Writes a Match value into a Buffer_view. If the write does not succeed, 
/// the result will contain a code representing the specific cause of failure.
Error_condition to_buffer(Buffer_view& v, const Match& m);

/// Reads a Match value from a Buffer_view. If the read does not succeed, the 
/// result will contain a code representing the specific cause of failure.
Error_condition from_buffer(Buffer_view& v, Match& m);

/// Returns a formatted string representation of a Match value.
std::string to_string(const Match& m, Formatter&);

/// \relates Match
constexpr bool wildcard_in_port(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_dl_src(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_dl_dst(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_dl_vlan(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_dl_pcp(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_dl_type(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_nw_tos(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_nw_proto(Match::Wildcards w);

/// \relates Match
inline std::size_t wildcard_nw_src(Match::Wildcards w);

/// \relates Match
inline std::size_t wildcard_nw_dst(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_tp_src(Match::Wildcards w);

/// \relates Match
constexpr bool wildcard_tp_dst(Match::Wildcards w);

// -------------------------------------------------------------------------- //
// Port

/// Represents a physical or logical port on a switch. The Port
/// class contains configuration information that describes a physical
/// or logical port. This includes its id, Ethernet address, configuration,
/// state, and supported features.
///
/// \todo Provide overloads for the related query functions so that they
/// take a pot struture and not the underlying value. 
struct Port {
  /// Identifies the port number. The Id is a 16-bit integer value 
  /// representing a physical port. There are a number of special ports 
  /// indicated by named values.
  using Id = uint16_t;
  static constexpr Id MAX         = 0xff00;
  static constexpr Id IN_PORT     = 0xfff8;
  static constexpr Id TABLE       = 0xfff9;
  static constexpr Id NORMAL      = 0xfffa;
  static constexpr Id FLOOD       = 0xfffb;
  static constexpr Id ALL         = 0xfffc;
  static constexpr Id CONTROLLER  = 0xfffd;
  static constexpr Id LOCAL       = 0xfffe;
  static constexpr Id NONE        = 0xffff;

  /// Describes the configuration of a port.
  enum Config : uint32_t {
    PORT_DOWN = 0x00000001, NO_STP = 0x00000002, NO_RECV = 0x00000004,
    NO_RECV_STP = 0x00000008, NO_FLOOD = 0x00000010, NO_FWD = 0x00000020,
    NO_PACKET_IN = 0x00000040
  };

  /// Describes the current state of a port.
  enum State : uint32_t {
    STP_LISTEN = 0x00000000, LINK_DOWN = 0x00000001, STP_LEARN = 0x00000002,
    STP_FORWARD = 0x00000004, STP_BLOCK = 0x00000008, STP_MASK = 0x00000010
  };  

  /// Describes the features of a port.
  enum Features : uint32_t {
    TEN_MB_HD = 0x0000001, TEN_MB_FD = 0x00000002, 
    HUNDRED_MB_HD = 0x00000004, HUNDRED_MB_FD = 0x00000008, 
    ONE_GB_HD = 0x00000010, ONE_GB_FD = 0x00000020,
    TEN_GB_FD = 0x00000040, COPPER = 0x00000080, FIBER = 0x00000100,
    AUTO_NEG = 0x00000200, PAUSE = 0x00000400, PAUSE_ASYM = 0x00000800
  };

  Id            port_id;
  Ethernet_addr hw_addr;
  Stringbuf<16> name;
  Config        config;
  State         state;
  Features      current;
  Features      advertised;
  Features      supported;
  Features      peer;
};

/// \relates Port
inline bool operator==(const Port& a, const Port& b);

/// \relates Port
inline bool operator!=(const Port& a, const Port& b);

/// \relates Port
constexpr std::size_t bytes(const Port&);

/// \relates Port
constexpr Error_condition is_valid(Port::Id id);

/// \relates Port
constexpr Error_condition is_valid(Port::Config);

/// \relates Port
constexpr Error_condition is_valid(Port::State);

/// \relates Port
constexpr Error_condition is_valid(Port::Features);

/// \relates Port
Error_condition is_valid(const Port& p);

/// \relates Port
Error_condition to_buffer(Buffer_view&, const Port&);

/// \relates Port
Error_condition from_buffer(Buffer_view&, Port&);

/// \relates Port
std::string to_string(Port::Id);

/// \relates Port
std::string to_string(Port::Config);

/// \relates Port
std::string to_string(Port::State);

/// \relates Port
std::string to_string(Port::Features);

/// \relates Port
std::string to_string(const Port&, Formatter&);

/// \relates Port
constexpr bool port_config_port_down(uint32_t c);

/// \relates Port
constexpr bool port_config_no_stp(uint32_t c);

/// \relates Port
constexpr bool port_config_no_recv(uint32_t c);

/// \relates Port
constexpr bool port_config_no_recv_stp(uint32_t c);

/// \relates Port
constexpr bool port_config_no_flood(uint32_t c);

/// \relates Port
constexpr bool port_config_no_fwd(uint32_t c);

/// \relates Port
constexpr bool port_config_no_packet_in(uint32_t c);

/// \relates Port
constexpr bool port_state_stp_listen(uint32_t s);

/// \relates Port
constexpr bool port_state_link_down(uint32_t s);

/// \relates Port
constexpr bool port_state_stp_learn(uint32_t s);

/// \relates Port
constexpr bool port_state_stp_forward(uint32_t s);

/// \relates Port
constexpr bool port_state_stp_block(uint32_t s);

/// \relates Port
constexpr bool port_state_stp_mask(uint32_t s);

/// \relates Port
constexpr bool port_max(uint16_t p);

/// \relates Port
constexpr bool port_in_port(uint16_t p);

/// \relates Port
constexpr bool port_table(uint16_t p);

/// \relates Port
constexpr bool port_normal(uint16_t p);

/// \relates Port
constexpr bool port_flood(uint16_t p);

/// \relates Port
constexpr bool port_all(uint16_t p);

/// \relates Port
constexpr bool port_controller(uint16_t p);

/// \relates Port
constexpr bool port_local(uint16_t p);

/// \relates Port
constexpr bool port_none(uint16_t p);

/// \relates Port
constexpr bool port_feature_10mb_hd(uint32_t p);

/// \relates Port
constexpr bool port_feature_10mb_fd(uint32_t p);

/// \relates Port
constexpr bool port_feature_100mb_hd(uint32_t p);

/// \relates Port
constexpr bool port_feature_100mb_fd(uint32_t p);

/// \relates Port
constexpr bool port_feature_1gb_hd(uint32_t p);

/// \relates Port
constexpr bool port_feature_1gb_fd(uint32_t p);

/// \relates Port
constexpr bool port_feature_10gb_fd(uint32_t p);

/// \relates Port
constexpr bool port_feature_copper(uint32_t p);

/// \relates Port
constexpr bool port_feature_fiber(uint32_t p);

/// \relates Port
constexpr bool port_feature_auto_neg(uint32_t p);

/// \relates Port
constexpr bool port_feature_pause(uint32_t p);

/// \relates Port
constexpr bool port_feature_pause_asym(uint32_t p);

// -------------------------------------------------------------------------- //
// Action type

/// Values corresponding to the different kinds of actions supported
/// in the OpenFlow protocol. 
///
/// \remark This enumeration corresponds to the ofp_action_type described 
/// in the OpenFlow specification.
enum Action_type : uint16_t 
{
  ACTION_OUTPUT       = 0x0000, 
  ACTION_SET_VLAN_VID = 0x0001, 
  ACTION_SET_VLAN_PCP = 0x0002, 
  ACTION_STRIP_VLAN   = 0x0003, 
  ACTION_SET_DL_SRC   = 0x0004, 
  ACTION_SET_DL_DST   = 0x0005,
  ACTION_SET_NW_SRC   = 0x0006, 
  ACTION_SET_NW_DST   = 0x0007, 
  ACTION_SET_NW_TOS   = 0x0008,
  ACTION_SET_TP_SRC   = 0x0009, 
  ACTION_SET_TP_DST   = 0x000a, 
  ACTION_ENQUEUE      = 0x000b,
  ACTION_VENDOR       = 0xffff
};

/// \relates Action_type
Error_condition is_valid(Action_type t);

/// \relates Action_type
std::string to_string(Action_type);

// A base class for all action payload kinds.
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
  
  Action_output(Port::Id p, uint16_t m)
    : port(p), max_len(m) { }

  Port::Id port;      ///< \todo Port::Id?
  uint16_t max_len;
};

/// \relates Action_output
bool operator==(const Action_output& a, const Action_output& b);

/// \relates Action_output
bool operator!=(const Action_output& a, const Action_output& b);

/// \relates Action_output
constexpr std::size_t bytes(const Action_output& a);

/// \relates Action_output
constexpr Error_condition is_valid(const Action_output& a);

/// \relates Action_output
Error_condition to_buffer(Buffer_view&, const Action_output&);

/// \relates Action_output
Error_condition from_buffer(Buffer_view&, Action_output&);

/// \relates Action_output
std::string to_string(const Action_output&, Formatter&);

// -------------------------------------------------------------------------- //
// Action_set_vlan_pcp

/// Sets the VLAN prioroity.
///
/// \remark Corresponds to ofp_action_vlan_pcp in OpenFlow specification.
struct Action_set_vlan_pcp : Action_payload_base<ACTION_SET_VLAN_PCP>
{
  Action_set_vlan_pcp() = default;
  
  explicit Action_set_vlan_pcp(uint8_t v)
    : value(v) { }

  uint8_t value;
};

/// \relates Action_set_vlan_pcp
bool operator==(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b);

/// \relates Action_set_vlan_pcp
bool operator!=(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b);

/// \relates Action_set_vlan_pcp
constexpr std::size_t bytes(const Action_set_vlan_pcp&);

/// \relates Action_set_vlan_pcp
constexpr Error_condition is_valid(const Action_set_vlan_pcp& a);

/// \relates Action_set_vlan_pcp
Error_condition to_buffer(Buffer_view&, const Action_set_vlan_pcp&);

/// \relates Action_set_vlan_pcp
Error_condition from_buffer(Buffer_view&, Action_set_vlan_pcp&);

/// \relates Action_set_vlan_pcp
std::string to_string(const Action_set_vlan_pcp&, Formatter&);

// -------------------------------------------------------------------------- //
// Action_set_vlan_vid

/// Sets the VLAN VID. 
///
/// \remark Corresponds to the ofp_action_vlan_vid in OpenFlow specification.
struct Action_set_vlan_vid : Action_payload_base<ACTION_SET_VLAN_VID>
{ 
  Action_set_vlan_vid() = default;
  
  explicit Action_set_vlan_vid(uint16_t v)
    : vlan_vid(v) { }

  uint16_t vlan_vid;
};

/// \relates Action_set_vlan_vid
bool operator==(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b);

/// \relates Action_set_vlan_vid
bool operator!=(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b);

/// \relates Action_set_vlan_vid
constexpr std::size_t bytes(const Action_set_vlan_vid&);

/// \relates Action_set_vlan_vid
constexpr Error_condition is_valid(const Action_set_vlan_vid& a);

/// \relates Action_set_vlan_vid
Error_condition to_buffer(Buffer_view&, const Action_set_vlan_vid&);

/// \relates Action_set_vlan_vid
Error_condition from_buffer(Buffer_view&, Action_set_vlan_vid&);

/// \relates Action_set_vlan_vid
std::string to_string(const Action_set_vlan_vid&, Formatter&);

// -------------------------------------------------------------------------- //
// Action_strip_vlan

/// Strips the VLAN tag.
///
/// \remark Corresponds to ofp_strip_vlan in the OpenFlow specification.
struct Action_strip_vlan : Action_payload_base<ACTION_STRIP_VLAN> 
{
  using Action_payload_base<ACTION_STRIP_VLAN>::Action_payload_base; 
};

/// \relates Action_strip_vlan
constexpr std::size_t bytes(const Action_strip_vlan& a);

/// \relates Action_strip_vlan
constexpr Error_condition is_valid(const Action_strip_vlan& a);

/// \relates Action_strip_vlan
Error_condition to_buffer(Buffer_view&, const Action_strip_vlan&);

/// \relates Action_strip_vlan
Error_condition from_buffer(Buffer_view&, Action_strip_vlan&);


// -------------------------------------------------------------------------- //
// Action_dl_addr

/// Implementation of actions that modify the data link address.
///
/// \remark Corresponds to ofp_action_dl_addr in the OpenFlow specification.
template<Action_type K>
  struct Action_dl_addr : Action_payload_base<K>
  {
    Action_dl_addr() = default;
    
    explicit Action_dl_addr(Ethernet_addr a) 
      : dl_addr(a) { }

    Ethernet_addr dl_addr;
  };

/// \relates Action_dl_addr
template<Action_type K>
  constexpr std::size_t bytes(const Action_dl_addr<K>& a);

/// \relates Action_dl_addr
template<Action_type K>
  constexpr Error_condition is_valid(const Action_dl_addr<K>& a);

/// \relates Action_dl_addr
template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_dl_addr<K>& a);

/// \relates Action_dl_addr
template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_dl_addr<K>& a);

/// \relates Action_dl_addr
template<Action_type K>
  std::string to_string(const Action_dl_addr<K>& a,  Formatter& f);


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

/// \relates Action_set_dl_src
std::string to_string(const Action_set_dl_src&);

// -------------------------------------------------------------------------- //
// Action: Set dl dst

/// Sets the data link (Ethernet) source address.
struct Action_set_dl_dst : Action_dl_addr<ACTION_SET_DL_DST> 
{
  using Action_dl_addr<ACTION_SET_DL_DST>::Action_dl_addr;
};

/// \relates Action_set_dl_dst
std::string to_string(const Action_set_dl_dst&);

// -------------------------------------------------------------------------- //
// Action_set_nw_addr

/// Implementation of actions that modify the network address.
template<Action_type K>
  struct Action_set_nw_addr : Action_payload_base<K>
  {
    Action_set_nw_addr() = default;
    
    explicit Action_set_nw_addr(Ipv4_addr a) 
      : addr(a) { }

    Ipv4_addr addr;
  };

/// \relates Action_set_nw_addr
template<Action_type K>
  constexpr std::size_t bytes(const Action_set_nw_addr<K>& na);

/// \relates Action_set_nw_addr
template<Action_type K>
  constexpr Error_condition is_valid(const Action_set_nw_addr<K>& na);

/// \relates Action_set_nw_addr
template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_set_nw_addr<K>& a);

/// \relates Action_set_nw_addr
template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_set_nw_addr<K>& a);

/// \relates Action_set_nw_addr
template<Action_type K>
  std::string to_string(const Action_set_nw_addr<K>& a,  Formatter& f);

// -------------------------------------------------------------------------- //
// Action_set_nw_src

/// Sets the network (Ipv4) source address.
struct Action_set_nw_src : Action_set_nw_addr<ACTION_SET_NW_SRC> 
{ 
  using Action_set_nw_addr<ACTION_SET_NW_SRC>::Action_set_nw_addr;
};

/// \relates Action_set_nw_src
std::string to_string(const Action_set_nw_src&);

// -------------------------------------------------------------------------- //
// Action_set_nw_dst

/// Sets the network (Ipv4) destination address.
struct Action_set_nw_dst : Action_set_nw_addr<ACTION_SET_NW_DST> 
{ 
  using Action_set_nw_addr<ACTION_SET_NW_DST>::Action_set_nw_addr;
};

/// \relates Action_set_nw_dst
std::string to_string(const Action_set_nw_dst&);

// -------------------------------------------------------------------------- //
// Action_set_nw_tos

/// Sets the network type of service (ToS).
struct Action_set_nw_tos : Action_payload_base<ACTION_SET_NW_TOS>
{
  Action_set_nw_tos() = default;
  
  explicit Action_set_nw_tos(uint8_t v)
    : value(v) { }

  uint8_t value;
};

/// \relates Action_set_nw_tos
bool operator==(const Action_set_nw_tos& a, const Action_set_nw_tos& b);

/// \relates Action_set_nw_tos
bool operator!=(const Action_set_nw_tos& a, const Action_set_nw_tos& b);

/// \relates Action_set_nw_tos
constexpr std::size_t bytes(const Action_set_nw_tos& a);

/// \relates Action_set_nw_tos
constexpr Error_condition is_valid(const Action_set_nw_tos& a);

/// \relates Action_set_nw_tos
Error_condition to_buffer(Buffer_view&, const Action_set_nw_tos& a);

/// \relates Action_set_nw_tos
Error_condition from_buffer(Buffer_view&, Action_set_nw_tos& a);

/// \relates Action_set_nw_tos
std::string to_string(const Action_set_nw_tos& a, Formatter&);

// -------------------------------------------------------------------------- //
// Action_set_tp_port

/// Implementation of actions that set the transport port.
///
/// \todo The specification allows the lower 8 bits to be used for
/// an ICMP code rather than a port. We should provide abstractions
/// that simplify the setting of those bits.
template<Action_type K>
  struct Action_set_tp_port : Action_payload_base<K>
  {
    Action_set_tp_port() = default;
   
    explicit Action_set_tp_port(uint16_t v) 
      : value(v) { }

    uint16_t value;
  };

/// \relates Action_set_tp_port
template<Action_type K>
  bool operator==(const Action_set_tp_port<K>& a, const Action_set_tp_port<K>& b);

/// \relates Action_set_tp_port
template<Action_type K>
  bool operator!=(const Action_set_tp_port<K>& a, const Action_set_tp_port<K>& b);

/// \relates Action_set_tp_port
template<Action_type K>
  constexpr std::size_t bytes(const Action_set_tp_port<K>& a);

/// \relates Action_set_tp_port
template<Action_type K>
  Error_condition is_valid(const Action_set_tp_port<K>& a);

/// \relates Action_set_tp_port
template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_set_tp_port<K>& a);

/// \relates Action_set_tp_port
template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_set_tp_port<K>& a);

// -------------------------------------------------------------------------- //
// Action_set_tp_src

/// Sets the transport (TCP/UDP) source port.
struct Action_set_tp_src : Action_set_tp_port<ACTION_SET_TP_SRC> 
{ 
  using Action_set_tp_port<ACTION_SET_TP_SRC>::Action_set_tp_port;
};

/// \relates Action_set_tp_src
std::string to_string(const Action_set_tp_src&);


// -------------------------------------------------------------------------- //
// Action_set_tp_dst

/// Sets the transport (TCP/UDP) destination port.
struct Action_set_tp_dst : Action_set_tp_port<ACTION_SET_TP_DST> 
{
  using Action_set_tp_port<ACTION_SET_TP_DST>::Action_set_tp_port;
};

/// \relates Action_set_tp_dst
std::string to_string(const Action_set_tp_dst&);

// -------------------------------------------------------------------------- //
// Action_enqueue

/// Forwards a packet through a queue on a specified port.
struct Action_enqueue : Action_payload_base<ACTION_ENQUEUE>
{
  Action_enqueue() = default;
  
  Action_enqueue(uint16_t p, uint32_t qi)
    : port(p), queue_id(qi) { }

  uint16_t port;
  uint32_t queue_id;
};

/// \relates Action_enqueue
bool operator==(const Action_enqueue& a, const Action_enqueue& b);

/// \relates Action_enqueue
bool operator!=(const Action_enqueue& a, const Action_enqueue& b);

/// \relates Action_enqueue
constexpr std::size_t bytes(const Action_enqueue& a);

/// \relates Action_enqueue
Error_condition to_buffer(Buffer_view& v, const Action_enqueue& a);

/// \relates Action_enqueue
Error_condition from_buffer(Buffer_view& v, Action_enqueue& a);

/// \relates Action_enqueue
std::string to_string(const Action_enqueue& a, Formatter& f);

// -------------------------------------------------------------------------- //
// Action_vendor

/// Invokes a vendor-specific action.
struct Action_vendor : Action_payload_base<ACTION_VENDOR>
{
  Action_vendor() = default;
  
  explicit Action_vendor(uint32_t v)
    : vendor(v) { }

  uint32_t vendor;
};

/// \relates Action_vendor
bool operator==(const Action_vendor& a, const Action_vendor& b);

/// \relates Action_vendor
bool operator!=(const Action_vendor& a, const Action_vendor& b);

/// \relates Action_vendor
constexpr std::size_t bytes(const Action_vendor&);

/// \relates Action_vendor
constexpr Error_condition is_valid(const Action_vendor& a);

/// \relates Action_vendor
Error_condition to_buffer(Buffer_view&, const Action_vendor&);

/// \relates Action_vendor
Error_condition from_buffer(Buffer_view&, Action_vendor&);

/// \relates Action_vendor
std::string to_string(const Action_vendor&, Formatter&);

// -------------------------------------------------------------------------- //
// Action Payload

union Action_payload_data
{
  Action_output       output;
  Action_set_vlan_vid vlan_vid;
  Action_set_vlan_pcp vlan_pcp;
  Action_strip_vlan   strip_vlan;
  Action_set_dl_src   dl_src;
  Action_set_dl_dst   dl_dst;
  Action_set_nw_src   nw_src;
  Action_set_nw_dst   nw_dst;
  Action_set_nw_tos   nw_tos;
  Action_set_tp_src   tp_src;
  Action_set_tp_dst   tp_dst;
  Action_enqueue      enqueue;
  Action_vendor       vendor;
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
// Action_header

/// The header of an action. Describe ofp_action_header in OpenFlow protocol.
///
/// \remark Implement ofp_action_header in OpenFlow protocol
struct Action_header
{
  Action_header() = default;

  Action_header(Action_type t) : type(t) { }

  Action_header(Action_type t, uint16_t l) : type(t), length(l) { }

  template<typename T>
    explicit Action_header(const T& x)
      : Action_header(kind_of(x), 4 + bytes(x)) { }

  Action_type type;
  uint16_t    length;
};

/// \relates Action_header
bool operator==(const Action_header& a, const Action_header& b);

/// \relates Action_header
bool operator!=(const Action_header& a, const Action_header& b);

/// \relates Action_header
constexpr std::size_t bytes(const Action_header&);

/// \relates Action_header
constexpr Error_condition is_valid(const Action_header& h);

/// \relates Action_header
Error_condition to_buffer(Buffer_view&, const Action_header&);

/// \relates Action_header
Error_condition from_buffer(Buffer_view&, Action_header&);

/// \relates Action_header
std::string to_string(const Action_header&, Formatter&);

// -------------------------------------------------------------------------- //
// Action

/// Encapsulates a policy decision on what should be applied to a packet.
/// 
/// An action is a policy decision on what should be applied to a packet.
/// OpenFlow uses actions either in the inbound or outbound direction in matches
/// or in instructions; both of which are used in flow modifications.
/// 
/// \remark Defined in [OpenFlow v1.0, p21-24](http://...)
struct Action {
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
Error_condition to_buffer(Buffer_view& buf, const Action& a);

/// \relates Action
Error_condition from_buffer(Buffer_view& buf, const Action& a);

/// \relates Action
std::string to_string(const Action& a, Formatter&);


// -------------------------------------------------------------------------- //
// Messages
//
// The following messages are in the v1_0 protocol.
//
// Hello
// Error
// Echo_req
// Echo_res
// Vendor
// ...


// -------------------------------------------------------------------------- //
// Version Type

/// Represents the value of the protocol version. There is a single 
/// enumeration value, VERSION. 
enum Version_type : std::uint8_t {
  VERSION = 1
};

/// Validates the value of a Version_type object. Returns SUCCESS only when v 
/// compares equal to VERSION and BAD_VERSION otherwise.
///
/// \relates Version_type
Error_condition is_valid(Version_type v);

/// Returns a string representation of the value.
///
/// \relates Version_type
std::string to_string(Version_type v);

// -------------------------------------------------------------------------- //
// Message Type

/// Represents the type of message being sent or received.
enum Message_type : std::uint8_t {
  HELLO                = 0, 
  ERROR                = 1, 
  ECHO_REQ             = 2, 
  ECHO_RES             = 3, 
  VENDOR               = 4,
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
  PORT_MOD             = 15,
  STATS_REQ            = 16, 
  STATS_RES            = 17, 
  BARRIER_REQ          = 18, 
  BARRIER_RES          = 19,
  QUEUE_GET_CONFIG_REQ = 20, 
  QUEUE_GET_CONFIG_RES = 21
};

/// Validates the value of a Message_type object. Returns SUCCESS only when m 
/// is a declared value of Message_type and BAD_MESSAGE otherwise.
///
/// \relates Message_type
Error_condition is_valid(Message_type m);

/// Returns a string representation of the value.
/// \relates Message_type
std::string to_string(Message_type m);

// A helper type. The base class of all message payloads.
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
/// \remark Defined in [OpenFlow v1.0, p41](http:://...)
struct Hello : Payload_base<HELLO> 
{ 
  /// constructs a default Hello message.
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
std::size_t bytes(const Hello& m);

/// Validates the value of a Hello message. The result is always SUCCESS since 
/// a Hello message is valid by construction.
///
/// \relates Hello
constexpr Error_condition is_valid(const Hello& m);

/// Writes a Hello message into a Buffer_view. If the write does not succeed, 
/// the result will contain a code representing the specific cause of failure.
///
/// \relates Hello
Error_condition to_buffer(Buffer_view& v, const Hello& m);

/// Reads a Hello message from a Buffer_view .If the read does not succeed, 
/// the result will contain a code representing the specific cause of failure.
///
/// \relates Hello
Error_condition from_buffer(Buffer_view& v, Hello& m);

/// Returns a formatted string representation of the value.
///
/// \relates Hello
std::string to_string(const Hello& m, Formatter& f);


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
/// \invariant if m.type == FLOW_MOD_FAILED then is_valid(m.code.fmf)
/// \invariant if m.type == PORT_MOD_FAILED then is_valid(m.code.pmf)
/// \invariant if m.type == QUEUE_OP_FAILED then is_valid(m.code.qof)
/// \invariant if m.type != HELLO_FAILED then bytes(m.data) >= 64
///
/// \remark Defined in [OpenFlow v1.0, p38-41](http://...)
struct Error : Payload_base<ERROR>
{
  /// Describes the categories of error codes.
  enum Type : uint16_t {
    /// Hello protocol failed (see Error::Hello_failed).    
    HELLO_FAILED    = 0x0000, 
    
    /// Request was not understood (see Error::Bad_request).
    BAD_REQUEST     = 0x0001, 
    
    /// Error in action description (see Error::Bad_action).
    BAD_ACTION      = 0x0002, 
    
    /// Flow modification failed (see Error::Flow_mod_failed).
    FLOW_MOD_FAILED = 0x0003, 
    
    /// Port modification failed (see Error::Port_mod_failed).
    PORT_MOD_FAILED = 0x0004, 

    /// Queue operation failed (see Error::Queue_op_failed).
    QUEUE_OP_FAILED = 0x0005
  };

  /// Describes Hello protocol failures.
  enum Hello_failed : uint16_t {
    HF_INCOMPATIBLE = 0x0000, ///< No compatible version
    HF_EPERM        = 0x0001  ///< Permissions error
  };

  /// Describes bad requests.
  enum Bad_request : uint16_t {
    BR_BAD_VERSION    = 0x0000, ///< Header version not supprted
    BR_BAD_TYPE       = 0x0001, ///< Message type not supported
    BR_BAD_STAT       = 0x0002, ///< Stat request type not supported
    BR_BAD_VENDOR     = 0x0003, ///< Vendor not supported
    BR_BAD_SUBTYPE    = 0x0004, ///< Vendor subtype not supported
    BR_EPERM          = 0x0005, ///< Permisssions error
    BR_BAD_LEN        = 0x0006, ///< Wrong message length
    BR_BUFFER_EMPTY   = 0x0007, ///< Specified buffer has already been used
    BR_BUFFER_UNKNOWN = 0x0008  ///< Specified buffer does not exist
  };
  
  /// Describes bad actions.
  enum Bad_action : uint16_t {
    BA_BAD_TYPE        = 0x0000, ///< Unknown action type
    BA_BAD_LEN         = 0x0001, ///< Wrong length for action
    BA_BAD_VENDOR      = 0x0002, ///< Unknown vendor id
    BA_BAD_VENDOR_TYPE = 0x0003, ///< Unknown action type for vendor id
    BA_BAD_OUT_PORT    = 0x0004, ///< Problem validating output action
    BA_BAD_ARGUMENT    = 0x0005, ///< Bad action argument
    BA_EPERM           = 0x0006, ///< Permissions error
    BA_TOO_MANY        = 0x0007, ///< Too many actions
    BA_BAD_QUEUE       = 0x0008  ///< Problem validating the input queue
  };
  
  /// Describes flow modification failures.
  enum Flow_mod_failed : uint16_t {
    FMF_ALL_TABLES_FULL   = 0x0000, ///< All tables are full
    FMF_OVERLAP           = 0x0001, ///< Cannot add overlapped flow
    FMF_EPERM             = 0x0002, ///< Perminssions error
    FMF_BAD_EMERG_TIMEOUT = 0x0003, ///< Operation timed out
    FMF_BAD_COMMAND       = 0x0004, ///< Unknown command
    FMF_UNSUPPORTED       = 0x0005  ///< Unsupported action list
  };
  
  /// Describes port modification failures.
  enum Port_mod_failed : uint16_t {
    PMF_BAD_PORT    = 0x0000, ///< Invalid port
    PMF_BAD_HW_ADDR = 0x0001  ///< Hardware address is wrong
  };
  
  /// Describes queue operation failures.
  enum Queue_op_failed : uint16_t {
    QOF_BAD_PORT  = 0x0000, ///< Invalid port
    QOF_BAD_QUEUE = 0x0001, ///< Invalid queue
    QOF_EPERM     = 0x0002  ///< Permissions error
  };

  union Code {
    Code() = default;
    Code(Hello_failed f) : hf(f) { }
    Code(Bad_request f) : br(f) { }
    Code(Bad_action f) : ba(f) { }
    Code(Flow_mod_failed f) : fmf(f) { }
    Code(Port_mod_failed f) : pmf(f) { }
    Code(Queue_op_failed f) : qof(f) { }
    Code(uint16_t n) : value(n) { }

    Hello_failed    hf;
    Bad_request     br;
    Bad_action      ba;
    Flow_mod_failed fmf;
    Port_mod_failed pmf;
    Queue_op_failed qof;
    uint16_t        value; // Uninterpreted value
  };

  /// Constructs a default Error message.
  Error() = default;
  
  /// Constructs a hello failed Error message. Initialize the error message with
  /// a Hello_failed code f and the error buffer b.
  Error(Hello_failed c, const Greedy_buffer& b) 
    : type(HELLO_FAILED), code(c), data() { }
  
  /// Constructs a bad request Error message. Initialize the error message with
  /// a Bad_request code f and the error buffer b.
  Error(Bad_request c, const Greedy_buffer& b) 
    : type(BAD_REQUEST), code(c), data() { }
  
  /// Constructs a bad action Error message. Initialize the error message with
  /// a Bad_action code f and the error buffer b.
  Error(Bad_action c, const Greedy_buffer& b) 
    : type(BAD_ACTION), code(c), data() { }
  
  /// Constructs a flow modification Error message. Initialize the error message
  /// with a Flow_mod_failed code f and the error buffer b.
  Error(Flow_mod_failed c, const Greedy_buffer& b) 
    : type(FLOW_MOD_FAILED), code(c), data() { }
  
  /// Constructs a port modification Error message. Initialize the error message
  /// with a Port_mod_failed code f and the error buffer b.
  Error(Port_mod_failed c, const Greedy_buffer& b) 
    : type(PORT_MOD_FAILED), code(c), data() { }
  
  /// Constructs a queue operation Error message. Initialize the error message
  /// with a Queue_op_failed code f and the error buffer b.
  Error(Queue_op_failed c, const Greedy_buffer& b) 
    : type(QUEUE_OP_FAILED), code(c), data() { }

  /// Constructs an Error Message from an Error_code. Initialize the error
  /// message with a type and code based on the Error_code c.
  ///
  /// \todo Implement me.
  Error(Error_code c, const Greedy_buffer& b);

  /// Constructs an error from an Error::Type and code. Initialize the error
  /// message with error type t, the error Code c, and the error buffer b. Note
  /// that the value is ill-formed if c  is not a valid code for the error type
  /// t.
  Error(Type t, uint16_t c, const Greedy_buffer& b)
    : type(t), code(c), data(b) { assert(is_valid(*this)); }

  Type type;          ///< The error category
  Code code;          ///< The error code
  Greedy_buffer data; ///< The uninterpreted offending message
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

/// Returns the number of bytes needed to represent an Error message.
///
/// \relates Error
std::size_t bytes(const Error& m);

/// Validates the value of an Error::Type object.
///
/// \relates Error::Type
Error_condition is_valid(Error::Type t);

/// Validates the value of an Error::Hello_failed object.
///
/// \relates Error::Hello_failed
Error_condition is_valid(Error::Hello_failed c);

/// Validates the value of an Error::Bad_request object.
///
/// \relates Error::Bad_request
Error_condition is_valid(Error::Bad_request c);

/// Validates the value of an Error::Bad_action object.
///
/// \relates Error::Bad_action
Error_condition is_valid(Error::Bad_action c);

/// Validates the value of an Error::Flow_mod_failed object.
///
/// \relates Error::Flow_mod_failed
Error_condition is_valid(Error::Flow_mod_failed c);

/// Validates the value of an Error::Port_mod_failed object.
///
/// \relates Error::Port_mod_failed
Error_condition is_valid(Error::Port_mod_failed c);

/// Validates the value of an Error::Queue_op_failed object.
///
/// \relates Queue_op_failed
Error_condition is_valid(Error::Queue_op_failed c);

/// Validates the length of uninterpreted data
///
/// \\relates Error::Greedy_buffer
Error_condition is_valid(Error::Type t,const Greedy_buffer& data);

/// Validates the value of an Error message.
///
/// \relates Error
Error_condition is_valid(const Error& m);

/// Writes an Error message into a Buffer_view.
///
/// \relates Error
Error_condition to_buffer(Buffer_view& v, const Error& m);

/// Reads an Error message from a Buffer_view.
///
/// \relates Error
Error_condition from_buffer(Buffer_view& v, Error& m);

/// Returns a string representation of an Error::Type value.
///
/// \relates Error::Type
std::string to_string(Error::Type c);

/// Returns a string representation of an Error::Hello_failed value.
///
/// \relates Error::Hello_failed
std::string to_string(Error::Hello_failed c);

/// Returns a string representation of an Error::Bad_request value.
///
/// \relates Error::Bad_request
std::string to_string(Error::Bad_request c);

/// Returns a string representation of an Error::Bad_action value.
///
/// \relates Error::Bad_action
std::string to_string(Error::Bad_action c);

/// Returns a string representation of an Error::Flow_mod_failed value.
///
/// \relates Error::Flow_mod_failed
std::string to_string(Error::Flow_mod_failed c);

/// Returns a string representation of an Error::Port_mod_failed value.
///
/// \relates Error::Port_mod_failed
std::string to_string(Error::Port_mod_failed c);

/// Returns a string representation of an Error::Queue_op_failed value.
///
/// \relates Error::Queue_op_failed
std::string to_string(Error::Queue_op_failed c);

/// Returns a formatted string representation of an Error_message value.
///
/// \relates Error
std::string to_string(const Error& e, Formatter& f);

// -------------------------------------------------------------------------- //
// Echo Base

// A base class providing common features for Echo_req and Echo_res.
template<Message_type K>
  struct Echo_base : Payload_base<K>
  {
    Echo_base() = default;
    Echo_base(const Greedy_buffer& b) : data(b) { }
    
    Greedy_buffer data; ///< Uninterpreted echo data
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
  std::size_t bytes(const Echo_base<K>& m);

/// Validates the value of an Echo_req or Echo_res message.
///
/// \relates Echo_base
template<Message_type K>
  constexpr Error_condition is_valid(const Echo_base<K>& m);

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
/// \remark Defined in [OpenFlow v1.0, p41](http://...)
struct Echo_req : Echo_base<ECHO_REQ> 
{
  using Echo_base<ECHO_REQ>::Echo_base;
};

/// Returns a formatted string representation of an Echo_req message.
std::string to_string(const Echo_req&, Formatter&);

// -------------------------------------------------------------------------- //
// Echo Res

/// Sent by the switch to exchange information about latency, bandwidth, and
/// liveness. The EchoRes message is used to exchange information about latency,
/// bandwidth, and liveness. Request timeouts indicate a disconnection. The
/// response contains a copy of the data sent by the request.
///
/// \remark Defined in [OpenFlow v1.0, p41](http://...)
struct Echo_res : Echo_base<ECHO_RES> 
{
  using Echo_base<ECHO_RES>::Echo_base;
};

/// Returns a formatted string representation of an Echo_res value.
std::string to_string(const Echo_req&, Formatter&);


// -------------------------------------------------------------------------- //
// Vendor

/// Represents a proprietary messages within the protocol. the
/// Vendor/Experimenter message is a mechanism for creating proprietary messages
/// within the protocol. In v1.0 this was called Vendor; however, in subsequent
/// versions the name was changed to experimenter.
/// 
/// \remark Defined in [OpenFlow v1.0, p41-42](http://...)
struct Vendor : Payload_base<VENDOR>
{
  Vendor() = default;
  Vendor(uint32_t v, const Greedy_buffer& b)
    : vendor_id(v), data(b) { }

  uint32_t      vendor_id; ///< The vendor id
  Greedy_buffer data;      ///< Uninterpreted vendor data
};

/// Returns true when the arguments compare equal. Two Vendor messages, a
/// and b, compare equal when they have the same vendor id and uninterpreted
/// data.
///
/// \relates Vender
bool operator==(const Vendor& a, const Vendor& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Vender
bool operator!=(const Vendor& a, const Vendor& b);

std::size_t bytes(const Vendor& m);

/// Validates the value of a Vendor message. The result is always SUCCESS
/// since a Vendor message is valid on construction.
///
/// \relates Vender
constexpr Error_condition is_valid(const Vendor& m);

/// \relates Vender
Error_condition to_buffer(Buffer_view& v, const Vendor& m);

/// \relates Vender
Error_condition from_buffer(Buffer_view& v, Vendor& m);

/// \relates Vender
std::string to_string(const Vendor& m, Formatter& f);

// -------------------------------------------------------------------------- //
// Feature Request

struct Feature_req : Payload_base<FEATURE_REQ> { };


// -------------------------------------------------------------------------- //
// Feature Response

/// The Feature_res class...
///
/// \todo Consider the constructors more carefully. Maybe abstract all
/// the individual feature fields into a Feature_spec structure that
/// can be used to initialize the message more concisely.
struct Feature_res : Payload_base<FEATURE_RES>
{
  enum Capability : uint32_t {
    FLOW_STATS = 0x00000001, TABLE_STATS = 0x00000002, 
    PORT_STATS = 0x00000004, STP = 0x00000008, RESERVED = 0x00000010,
    IP_REASM = 0x00000020, QUEUE_STATS = 0x00000040, 
    ARP_MATCH_IP = 0x00000080 
  };
  
  /// \todo Check the VENDOR flag.
  enum Action : uint32_t {
    OUTPUT = 0x00000001, SET_VLAN_VID = 0x00000002, 
    SET_VLAN_PCP = 0x00000003, STRIP_VLAN = 0x00000008, 
    SET_DL_SRC = 0x00000010, SET_DL_DST = 0x00000020, 
    SET_NW_SRC = 0x00000040, SET_NW_DST = 0x00000080, 
    SET_NW_TOS = 0x00000100, SET_TP_SRC = 0x00000200, 
    SET_TP_DST = 0x00000400, ENQUEUE = 0x00000800 
    //, VENDOR = ???
  };

  Feature_res() = default;
  
  /// Construct Feature_res with all fields
  Feature_res(uint64_t id, uint32_t nbufs, uint8_t ntbls, 
              Capability c, Action a, const Sequence<Port>& p);

  /// Construct Feature_res with all fields and initializer list for port
  Feature_res(uint64_t id, uint32_t nbufs, uint8_t ntbls, 
              Capability c, Action a, std::initializer_list<Port> p);

  uint64_t       datapath_id;
  uint32_t       n_buffers;
  uint8_t        n_tbls;
  Capability     capabilities;
  Action         feature_actions; 
  Sequence<Port> ports;
};

/// \relates Feature_res
bool operator==(const Feature_res& a, const Feature_res& b);

/// \relates Feature_res
bool operator!=(const Feature_res& a, const Feature_res& b);

/// \relates Feature_res
std::size_t bytes(const Feature_res& fr);

/// \relates Feature_res
std::string to_string(const Feature_res&, Formatter&);

/// \relates Feature_res
Error_condition to_buffer(Buffer_view&, const Feature_res&);

/// \relates Feature_res
Error_condition from_buffer(Buffer_view&, Feature_res&);

/// \relates Feature_res
constexpr bool feature_has_flow_stats(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_has_table_stats(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_has_port_stats(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_has_stp(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_has_reserved(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_has_ip_reasm(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_has_queue_stats(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_has_arp_match_ip(Feature_res::Capability c);

/// \relates Feature_res
constexpr bool feature_can_output(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_vlan_vid(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_vlan_pcp(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_strip_vlan(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_dl_src(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_dl_dst(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_nw_src(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_nw_dst(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_nw_tos(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_tp_src(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_set_tp_dst(Feature_res::Action a);

/// \relates Feature_res
constexpr bool feature_can_enqueue(Feature_res::Action a);


// -------------------------------------------------------------------------- //
// Get Config Request

struct Get_config_req : Payload_base<GET_CONFIG_REQ> { };


// -------------------------------------------------------------------------- //
// Config_message_base

// The config message base provides a common structure and implementation 
// for the Get_config_res and Set_config messages.
template<Message_type T>
  struct Config_message_base : Payload_base<T>
  {
    enum Flags : uint16_t {
      FRAG_NORMAL = 0x0000, 
      FRAG_DROP   = 0x0001, 
      FRAG_REASM  = 0x0002, 
      FRAG_MASK   = 0x0003
    };

    Config_message_base() = default;
    
    /// Construct Config_message_base with all fields
    Config_message_base(Flags f, uint16_t msl)
      : flags(f), miss_send_len(msl) { }

    Flags    flags;
    uint16_t miss_send_len;
  };

/// \relates Config_message_base
template<Message_type T>
  bool operator==(const Config_message_base<T>& a, const Config_message_base<T>& b);

/// \relates Config_message_base
template<Message_type T>
  bool operator!=(const Config_message_base<T>& a, const Config_message_base<T>& b);

/// \relates Config_message_base
template<Message_type T>
  std::size_t bytes(const Config_message_base<T>& m);

/// \relates Config_message_base
template<Message_type T>
  constexpr Error_condition is_valid(typename Config_message_base<T>::Flags f);

/// \relates Config_message_base
template<Message_type T>
  constexpr Error_condition is_valid(const Config_message_base<T>& c);

/// \relates Config_message_base
template<Message_type T>
  Error_condition to_buffer(Buffer_view& b, const Config_message_base<T>& m);

/// \relates Config_message_base
template<Message_type T>
  Error_condition from_buffer(Buffer_view& b, Config_message_base<T>& m);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_normal(typename Config_message_base<T>::Flags f);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_drop(typename Config_message_base<T>::Flags f);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_reasm(typename Config_message_base<T>::Flags f);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_mask(typename Config_message_base<T>::Flags f);


// -------------------------------------------------------------------------- //
// Get Config Response

struct Get_config_res : Config_message_base<GET_CONFIG_RES> { };

/// \relates Get_config_res
std::string to_string(const Get_config_res&, Formatter&);


// -------------------------------------------------------------------------- //
// Set Config

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
/// \remark Defined in [OpenFlow v1.0, p36]
struct Packet_in : Payload_base<PACKET_IN>
{
  enum Reason : uint8_t {
    NO_MATCH = 0x00,  ///< Packet-in reason is table miss
    ACTION = 0x01     ///< Packet-in reason is by action
  };

  /// Construct an empty Packet_in message
  Packet_in() = default;
  
  /// Construct a Packet_in message with value of all the fields
  Packet_in(uint32_t id, uint16_t l, uint16_t p, Reason r, const Buffer& b)
    : buffer_id(id), total_len(l), in_port(p), reason(r), data(b) { }

  uint32_t buffer_id;
  uint16_t total_len;
  uint16_t in_port; 
  Reason   reason;
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
std::size_t bytes(const Packet_in& p);

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

// -------------------------------------------------------------------------- //
// Flow Removed

/// The message is sent by the switch to the controller to notify a flow being
/// removed from the tables in the switch. The possible reason for it could
/// be a timeout or a deletion operation.
///
/// \remark Defined in [OpenFlow v1.0, p37]
struct Flow_removed : Payload_base<FLOW_REMOVED>
{
  enum Reason : uint8_t {
    IDLE_TIMEOUT = 0x00,  ///< Flow idle time exceeded idle_timeout
		HARD_TIMEOUT = 0x01,  ///< Time exceeded hard_timeout
		DELETE = 0x02,        ///< Evicted by a DELETE flow mod
  };

  /// Construct an empty Flow_removed struct
  Flow_removed() = default;
  
  /// Construct a Flow_removed struct with values of all the fields
  Flow_removed(Match m, uint64_t c, uint16_t p, Reason r, uint32_t ds, 
                uint32_t dn, uint16_t it, uint64_t pc, uint64_t bc)
    : match(m), cookie(c), priority(p), reason(r), duration_sec(ds)
    , duration_nsec(dn), idle_timeout(it), packet_count(pc), byte_count(bc) { }

  Match    match;
  uint64_t cookie;
  uint16_t priority;
  Reason   reason;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  uint16_t idle_timeout;
  uint64_t packet_count;
  uint64_t byte_count;
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

Error_condition is_valid(Flow_removed::Reason r);

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
std::string to_string(Flow_removed::Reason);

std::string to_string(const Flow_removed&, Formatter&);


// -------------------------------------------------------------------------- //
// Port Status

/// The message is sent from the switch to the controller to inform addition,
/// remove or modification of ports from the datapath. 
///
/// \remark Defined in [OpenFlow v1.0, p38]
struct Port_status : Payload_base<PORT_STATUS>
{
  enum Reason : uint8_t {
    ADD = 0x00, 
    DELETE = 0x01, 
    MODIFY = 0x02
  };

  /// Contruct an empty Port_status
  Port_status() = default;

  /// Construct a Port_status with value of all the fields
  Port_status(Reason r, Port p) : reason(r), port(p) { }

  Reason reason;
  Port   port;
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

Error_condition is_valid(Port_status::Reason r);

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
/// \remark Defined in [OpenFlow v1.0, p35]
struct Packet_out : Payload_base<PACKET_OUT>
{
  /// Construct an empty Port_out message
  Packet_out() = default;
  
  /// Construct a Port_out message with value of all the fields
  Packet_out(uint32_t buf, Port::Id port, std::initializer_list<Action>);
  
  /// Construct a Port_out message with value of all the fields and an
  /// initializer list for actions
  Packet_out(Greedy_buffer pkt, Port::Id port, std::initializer_list<Action>);

  uint32_t buffer_id;
  Port::Id in_port;
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
/// \remark Defined in [OpenFlow v1.0, p13-15](http://...)
struct Flow_mod : Payload_base<FLOW_MOD>
{
  enum Command : uint16_t 
  {
    ADD           = 0x0000, 
    MODIFY        = 0x0001, 
    MODIFY_STRICT = 0x0002, 
    DELETE        = 0x0003,
    DELETE_STRICT = 0x0004
  };

  enum Flags : uint16_t 
  {
    SEND_FLOW_REM = 0x0001, 
    CHECK_OVERLAP = 0x0002, 
    EMERG         = 0x0003
  };

  Flow_mod() = default;
  
  Flow_mod(const Match& m, uint64_t ck, Command cmd, uint16_t it, 
           uint16_t ht, uint16_t p, uint32_t bid, uint16_t ip, 
           Flags f, const Sequence<Action>& a)
    : match(m), cookie(ck), command(cmd), idle_timeout(it), hard_timeout(ht)
    , priority(p), buffer_id(bid), out_port(ip), flags(f), actions(a) { } 

  Match            match;
  uint64_t         cookie;
  Command          command;
  uint16_t         idle_timeout;
  uint16_t         hard_timeout;
  uint16_t         priority;
  uint32_t         buffer_id;
  uint16_t         out_port;
  Flags            flags;
  Sequence<Action> actions;
};

/// Returns true when the messages compare equal.
///
/// \relates Flow_mod
bool operator==(const Flow_mod& a, const Flow_mod& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Flow_mod
bool operator!=(const Flow_mod& a, const Flow_mod& b);

/// Returns the number of bytes needed to represent a Flow_mod message.
///
/// \relates Flow_mod
std::size_t bytes(const Flow_mod& m);

/// Validates the value of a Flow_mod::Command object.
///
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod::Command t);

/// Validates the value of a Flow_mod::Flags object.
///
/// \relates Flow_mod
constexpr Error_condition is_valid(const Flow_mod::Flags t);

/// Validates the value of a Flow_mod message.
///
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod& m);

/// Writes a Flow_mod value to a Buffer_view.
///
/// \relates Flow_mod
Error_condition to_buffer(Buffer_view&, const Flow_mod&);

/// Reads a Flow_mod value from a Buffer_view.
///
/// \relates Flow_mod
Error_condition from_buffer(Buffer_view&, Flow_mod&);

/// Returns a string representation of a Flow_mod::Command value.
///
/// \relates Flow_mod
std::string to_string(Flow_mod::Command);

/// Returns a string representation of a Flow_mod::Flags value.
///
/// \relates Flow_mod
std::string to_string(Flow_mod::Flags);

/// Returns a formatted string representation of a Flow_mod message.
///
/// \relates Flow_mod
std::string to_string(const Flow_mod&, Formatter&);

// -------------------------------------------------------------------------- //
// Port Mod

/// The Port Mod message is sent by the controller to the switch to modify the
/// behavior of the port
/// 
/// \remark Defined in [OpenFlow v1.0 p29]
struct Port_mod : Payload_base<PORT_MOD>
{
  /// Port config 
  enum Config 
  {
    PORT_DOWN = 0x00000001, NO_STP = 0x00000002, NO_RECV = 0x00000004,
    NO_RECV_STP = 0x0000008, NO_FLOOD = 0x00000010, NO_FWD = 0x00000020,
    NO_PACKET_IN = 0x00000040
  };

  /// Port features 
  enum Features {
    TEN_MB_HD = 0x00000001, TEN_MB_FD = 0x00000002, 
    HUNDRED_MB_HD = 0x00000004, HUNDRED_MB_FD = 0x00000008, 
    ONE_GB_HD = 0x00000010, ONE_GB_FD = 0x00000020,
    TEN_GB_FD = 0x00000040, COPPER = 0x00000080, FIBER = 0x00000100, 
    AUTO_NEG = 0x00000200, PAUSE = 0x00000400, PAUSE_ASYM = 0x00000800
  };

  /// Construct an empty Port_mod message
  Port_mod() = default;
  
  /// Construct a Port_mod message with value of all the fields
  Port_mod(uint16_t p, Ethernet_addr addr, Config c, Config m, Features a)
    : port(p), hw_addr(addr), config(c), mask(m), advertise(a) { }

  uint16_t      port;
  Ethernet_addr hw_addr; 
  Config        config;
  Config        mask;
  Features      advertise;
};

/// Returns true when two Port_mod are totally equal. 
///
/// \relates Port_mod
inline bool 
operator==(const Port_mod& a, const Port_mod& b)
{
  return a.port == b.port
     and a.hw_addr == b.hw_addr
     and a.config == b.config
     and a.mask == b.mask
     and a.advertise == b.advertise;
}

/// Returns true when two Port_mod structs do not compare equal.
///
/// \relates Port_mod
inline bool 
operator!=(const Port_mod& a, const Port_mod& b)
{
  return a != b;
}

/// Return number of bytes of an Port_mod message.
///
/// \relates Port_mod
inline std::size_t 
bytes(const Port_mod&) { return 24; }

constexpr Error_condition
is_valid(Port_mod::Config c) { return SUCCESS; }

constexpr Error_condition
is_valid(Port_mod::Features f) { return SUCCESS; }

/// Validates the value of a Port_mod message. 
///
/// \relates Port_mod
inline Error_condition
is_valid(const Port_mod& p) 
{ 
  if (Error_decl err = is_valid(p.config))
    return err;
  if (Error_decl err = is_valid(p.mask))
    return err;
  if (Error_decl err = is_valid(p.advertise))
    return err;
  return SUCCESS;
}

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
std::string to_string(Port_mod::Config);
std::string to_string(Port_mod::Features);


// -------------------------------------------------------------------------- //
// Stats type

/// The Stats_type enumeration describes the types of requests and
/// responses for statistics.
enum Stats_type : uint16_t
{
  STATS_DESC      = 0,
  STATS_FLOW      = 1,
  STATS_AGGREGATE = 2,
  STATS_TABLE     = 3,
  STATS_PORT      = 4,
  STATS_QUEUE     = 5,
  STATS_VENDOR    = 0xffff
};

// Returns true when t is a valid stats request value.
constexpr Error_condition
is_valid(Stats_type t) {
  return ok(t <= STATS_QUEUE or t == STATS_VENDOR, BAD_STATS);
}

// To string
std::string to_string(const Stats_type& h, Formatter&);

// Payload base
template<Stats_type K>
  using Stats_payload_base = Basic_payload_base<Stats_type, K>;


// -------------------------------------------------------------------------- //
// Stats Header

/// The Stats_header class defines the header properties for stats
/// requests and responses.
struct Stats_header
{
  enum Flags : uint16_t {
    MORE = 0x0001
  };

  Stats_header() = default;

  Stats_header(Stats_type t) : type(t) { }
  
  Stats_header(Stats_type t, Flags f) : type(t), flags(f) { }

  template<typename T, typename = typename T::Tag>
    explicit Stats_header(const T& x) : type(kind_of(x)), flags() { }

  Stats_type type;
  Flags      flags;
};

// Equality comparison
inline bool
operator==(const Stats_header& a, const Stats_header& b) {
  return a.type == b.type and a.flags == b.flags;
}

inline bool
operator!=(const Stats_header& a, const Stats_header& b) {
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_header& h) { return 4; }

// Is valid
constexpr Error_decl
is_valid(Stats_header::Flags f) { return SUCCESS; }

inline Error_condition
is_valid(const Stats_header& h) { 
  if (Error_decl err = is_valid(h.type))
    return err;
  if (Error_decl err = is_valid(h.flags))
    return err;
  return SUCCESS;
}

// To/from buffer
Error_condition to_buffer(Buffer_view& buf, const Stats_header& h);
Error_condition from_buffer(Buffer_view& buf, Stats_header& h);

// To string
std::string to_string(Stats_header::Flags);
std::string to_string(const Stats_header&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats_req_desc

/// Description of the OpenFlow switch.
///
/// \remark Implements an OFPST_DESC stats request message
struct Stats_req_desc : Stats_payload_base<STATS_DESC> { };


// -------------------------------------------------------------------------- //
// Stats_req_flow_base
//

/// The Stats_req_flow_base provides common facilities for stats requests for 
/// single (flow) or multiple (aggregate) flows.
template<Stats_type K>
  struct Stats_req_flow_base : Stats_payload_base<K>
  {
    Stats_req_flow_base() = default;
    
    Stats_req_flow_base(const Match& m, uint8_t tid, uint16_t op)
      : match(m), table_id(tid), out_port(op) { }

    Match    match;
    uint8_t  table_id;
    uint16_t out_port;
  };

template<Stats_type K>
  bool operator==(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b);

template<Stats_type K>
  bool operator!=(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b);

template<Stats_type K>
  std::size_t bytes(const Stats_req_flow_base<K>& f);

template<Stats_type K>
  Error_condition is_valid(const Stats_req_flow_base<K>& f);

template<Stats_type K>
  Error_condition to_buffer(Buffer_view& v, const Stats_req_flow_base<K>& f);

template<Stats_type K>
  Error_condition from_buffer(Buffer_view& v, Stats_req_flow_base<K>& f);

// -------------------------------------------------------------------------- //
// Stats_req_flow

/// Individual flow statistics
///
/// \remark Implements an OFPST_FLOW stats request message.
struct Stats_req_flow : Stats_req_flow_base<STATS_FLOW> { };

std::string to_string(const Stats_req_flow&, Formatter&);

// -------------------------------------------------------------------------- //
// Stats_req_aggregate

/// Aggregate flow statistics
///
/// \remark Implements an OFPST_AGGREGATE stats request message.
struct Stats_req_aggregate : Stats_req_flow_base<STATS_AGGREGATE> { };

std::string to_string(const Stats_req_aggregate&, Formatter&);

// -------------------------------------------------------------------------- //
// Stats_req_table

/// Flow table statistics
///
/// \remark Implements an OFPST_TABLE stats request message.
struct Stats_req_table : Stats_payload_base<STATS_TABLE> { };


// -------------------------------------------------------------------------- //
// Stats_req_port

/// Port statistics
///
/// \remark Implements an OFPST_PORT stats request message.
struct Stats_req_port : Stats_payload_base<STATS_PORT>
{
  Stats_req_port() = default;
  explicit Stats_req_port(uint16_t p);

  uint16_t port_no;
};

inline
Stats_req_port::Stats_req_port(uint16_t p)
  : port_no(p)
{ }

// Equality comparison
inline bool
operator==(const Stats_req_port& a, const Stats_req_port& b)
{
  return a.port_no == b.port_no;
}

inline bool
operator!=(const Stats_req_port& a, const Stats_req_port& b)
{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Stats_req_port& p) { return 8; }

constexpr Error_condition
is_valid(const Stats_req_port& p) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view& buf, const Stats_req_port& p);
Error_condition from_buffer(Buffer_view& buf, Stats_req_port& p);

// To string
std::string to_string(const Stats_req_port& p, Formatter&);


// -------------------------------------------------------------------------- //
// Stats_req_queue

/// Queue statistics for a port
///
/// \remark Implements an OFPST_QUEUE stats request message.
struct Stats_req_queue : Stats_payload_base<STATS_QUEUE>
{
  Stats_req_queue() = default;
  Stats_req_queue(uint16_t p, uint32_t q);

  uint16_t port_no;
  uint32_t queue_id;
};

inline
Stats_req_queue::Stats_req_queue(uint16_t p, uint32_t q)
  : port_no(p), queue_id(q)
{ }

// Equality comparison
inline bool
operator==(const Stats_req_queue& a, const Stats_req_queue& b)
{
  return a.port_no == b.port_no and a.queue_id == b.queue_id;
}

inline bool
operator!=(const Stats_req_queue& a, const Stats_req_queue& b)
{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Stats_req_queue& q) { return 8; }

constexpr Error_condition
is_valid(const Stats_req_queue& m) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view& buf, const Stats_req_queue& q);
Error_condition from_buffer(Buffer_view& buf, Stats_req_queue& q);

// To string
std::string to_string(const Stats_req_queue& q, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Request Vendor

/// Vendor statistics
///
/// \remark Implements an OFPST_VENDOR stats request message.
struct Stats_req_vendor : Stats_payload_base<STATS_VENDOR>
{
  Stats_req_vendor() = default;
  Stats_req_vendor(uint32_t v, const Greedy_buffer& b)
    : vendor_id(v), data(b) { }

  uint32_t      vendor_id;
  Greedy_buffer data;
};

// Equality comparison
inline bool
operator==(const Stats_req_vendor& a, const Stats_req_vendor& b)
{
  return a.vendor_id == b.vendor_id and a.data == b.data;
}

inline bool
operator!=(const Stats_req_vendor& a, const Stats_req_vendor& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_req_vendor& v) { return 4 + bytes(v.data); }

constexpr Error_condition
is_valid(const Stats_req_vendor& r) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view& buf, const Stats_req_vendor& v);
Error_condition from_buffer(Buffer_view& buf, Stats_req_vendor& v);

// To string
std::string to_string(const Stats_req_vendor& v, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Request Payload

union Stats_req_payload_data
{
  Stats_req_payload_data() { }
  ~Stats_req_payload_data() { }

  Stats_req_desc      desc;
  Stats_req_flow      flow;
  Stats_req_aggregate aggr;
  Stats_req_table     table;
  Stats_req_port      port;
  Stats_req_queue     queue;
  Stats_req_vendor    vendor;
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
// Stats_req

/// The Stats Request message is sent by the controller to the switch to obtain
/// the state of the switch. 
/// 
/// \remark Defined in [OpenFlow v1.0 p30-35]
struct Stats_req : Payload_base<STATS_REQ>
{
  using Header = Stats_header;
  using Payload = Stats_req_payload;

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

  template<typename Tag, typename... Args>
    Stats_req(Tag t, Args&&... args)
      : header(t.value) { construct(payload, t, std::forward<Args>(args)...); }

  Header  header;
  Payload payload;
};

inline
Stats_req::~Stats_req()
{
  destroy(payload, header.type);
}

inline
Stats_req::Stats_req(Stats_req&& x)
  : header(std::move(x.header))
{ 
  construct(payload, std::move(x.payload), header.type); 
}

inline Stats_req&
Stats_req::operator=(Stats_req&& x)
{
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Stats_req::Stats_req(const Stats_req& x)
  : header(x.header)
{ 
  construct(payload, x.payload, header.type); 
}

inline Stats_req&
Stats_req::operator=(const Stats_req& x)
{
  header = x.header;
  assign(payload, x.payload, header.type); 
  return *this;
}

/// Returns true when two Stats_req are totally equal. 
///
/// \relates Stats_req
inline bool
operator==(const Stats_req& a, const Stats_req& b)
{
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

/// Returns true when two Stats_req structs do not compare equal.
///
/// \relates Stats_req
inline bool
operator!=(const Stats_req& a, const Stats_req& b)
{
  return !(a == b);
}

/// Return number of bytes of an Stats_req message.
///
/// \relates Stats_req
inline std::size_t
bytes(const Stats_req& r) 
{ 
  return bytes(r.header) + bytes(r.payload, r.header.type); 
}

/// Validates the value of a Stats_req message. 
///
/// \relates Stats_req
inline Error_condition
is_valid(const Stats_req& r) {
  if (Error_decl err = is_valid(r.header))
    return err;
  if (Error_decl err = is_valid(r.payload, r.header.type))
    return err;
  return SUCCESS;
}

/// Writes a Stats_req message into a Buffer_view. If the write does not
/// succeed, the result will containt a code representing the specific cause of
/// failure.
///
/// \relates Stats_req
Error_condition to_buffer(Buffer_view& buf, const Stats_req& r);

/// Reads a Stats_req message from a Buffer_view .If the read does not succeed, 
/// the result will containt a code representing the specific cause of failure.
///
/// \relates Stats_req
Error_condition from_buffer(Buffer_view& buf, Stats_req& r);

/// Returns a formatted string representation of Stats_req.
///
/// \relates Stats_req
std::string to_string(const Stats_req& r, Formatter& f);


// -------------------------------------------------------------------------- //
// Stats Response Description

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
    : mfr_desc(m), hw_desc(h), sw_desc(s), serial_num(sn), dp_desc(d)
  { }

  Desc_string   mfr_desc;
  Desc_string   hw_desc;
  Desc_string   sw_desc;
  Serial_string serial_num;
  Desc_string   dp_desc;
};


// Equality comparison
inline bool
operator==(const Stats_res_desc& a, const Stats_res_desc& b)
{

  return a.mfr_desc == b.mfr_desc
     and a.hw_desc == b.hw_desc
     and a.sw_desc == b.sw_desc
     and a.serial_num == b.serial_num
     and a.dp_desc == b.dp_desc;
}

inline bool
operator!=(const Stats_res_desc& a, const Stats_res_desc& b)
{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Stats_res_desc& d) 
{ 
  return 4 * Stats_res_desc::DESC_STR_LEN + Stats_res_desc::SERIAL_NUM_LEN; 
}

// Is valid
constexpr Error_condition
is_valid(const Stats_res_desc& d) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view& buf, const Stats_res_desc& d);
Error_condition from_buffer(Buffer_view& buf, Stats_res_desc& d);


// To string
std::string to_string(const Stats_res_desc& d, Formatter& f);


// -------------------------------------------------------------------------- //
// Stats Response Flow

/// Implements stats of each individual flow in an OFPST_FLOW Stats Response 
/// message.
struct Stats_res_flow 
{
  Stats_res_flow() = default;
  Stats_res_flow(uint16_t l, uint8_t t, const Match& m, uint32_t sec, 
                 uint32_t nsec, uint16_t pri, uint16_t it, uint16_t ht, 
                 uint64_t c, uint64_t pc, uint64_t bc)
    : length(l), table_id(t), match(m), duration_sec(sec), 
      duration_nsec(nsec), priority(pri), idle_timeout(it), hard_timeout(ht)
    , cookie(c), packet_count(pc), byte_count(bc)
  { }
  
  uint16_t         length;
  uint8_t          table_id;
  Match            match;
  uint32_t         duration_sec;
  uint32_t         duration_nsec;
  uint16_t         priority;
  uint16_t         idle_timeout;
  uint16_t         hard_timeout;
  uint64_t         cookie;
  uint64_t         packet_count;
  uint64_t         byte_count;
  Sequence<Action> actions;
};

// Equality comparison
inline bool
operator==(const Stats_res_flow& a, const Stats_res_flow& b)
{
  return a.length == b.length 
     and a.table_id == b.table_id
     and a.match == b.match
     and a.duration_sec == b.duration_sec 
     and a.duration_nsec == b.duration_nsec
     and a.priority == b.priority 
     and a.idle_timeout == b.idle_timeout
     and a.hard_timeout == b.hard_timeout 
     and a.cookie == b.cookie
     and a.packet_count == b.packet_count 
     and a.byte_count == b.byte_count
     and a.actions == b.actions;
}

inline bool
operator!=(const Stats_res_flow& a, const Stats_res_flow& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_flow& f) { return 88 + bytes(f.actions); }

// Is valid
inline Error_condition
is_valid(const Stats_res_flow& f) {
  if (Error_decl err = is_valid(f.match))
    return err;
  if (Error_decl err = is_valid(f.actions))
    return err;
  return SUCCESS;
}

// To/from buffer
Error_condition to_buffer(Buffer_view& v, const Stats_res_flow& f);
Error_condition from_buffer(Buffer_view& v, Stats_res_flow& f);

// To string
std::string to_string(const Stats_res_flow&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Flows

/// Individual flow statistics.
///
/// \remark Implements an OFPST_FLOW Stats Response message
struct Stats_res_flows : Stats_payload_base<STATS_FLOW>
{
  Stats_res_flows() = default;
  explicit Stats_res_flows(Sequence<Stats_res_flow> f);

  Sequence<Stats_res_flow> flows;
};

inline
Stats_res_flows::Stats_res_flows(Sequence<Stats_res_flow> f)
  : flows(f)
{ }

inline bool
operator==(const Stats_res_flows& a, const Stats_res_flows& b)
{
  return a.flows == b.flows;
}

inline bool
operator!=(const Stats_res_flows& a, const Stats_res_flows& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_flows& f)
{
  return bytes(f.flows);
}

// Is valid
inline Error_condition
is_valid(const Stats_res_flows& f) { return is_valid(f.flows); }

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_flows&);
Error_condition from_buffer(Buffer_view&, Stats_res_flows&);

std::string to_string(const Stats_res_flows&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response Aggregate

/// Aggregate flow statistics.
///
/// \remark Implements an OFPST_AGGREGATE Stats Response message
struct Stats_res_aggregate : Stats_payload_base<STATS_AGGREGATE>
{
  Stats_res_aggregate() = default;
  Stats_res_aggregate(uint64_t pc, uint64_t bc, uint32_t fc)
    : packet_count(pc), byte_count(bc), flow_count(fc)
  { }

  uint64_t packet_count;
  uint64_t byte_count;
  uint32_t flow_count;
};

// Equality comparison
inline bool
operator==(const Stats_res_aggregate& a, const Stats_res_aggregate& b)
{
  return a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.flow_count == b.flow_count;
}

inline bool
operator!=(const Stats_res_aggregate& a, const Stats_res_aggregate& b)
{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Stats_res_aggregate& a) { return 24; }

// Is valid
constexpr Error_condition
is_valid(const Stats_res_aggregate& a) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Stats_res_aggregate&);
Error_condition from_buffer(Buffer_view&, Stats_res_aggregate&);

// To string
std::string to_string(const Stats_res_aggregate&, Formatter& fmt);


// -------------------------------------------------------------------------- //
// Stats Response Port

/// Implements stats of each individual port an OFPST_PORT Stats Response
/// message
struct Stats_res_port 
{
  Stats_res_port() = default;
  Stats_res_port(uint16_t n, 
                 uint64_t rp, uint64_t tp,
                 uint64_t rb, uint64_t tb,
                 uint64_t rd, uint64_t td,
                 uint64_t re, uint64_t te,
                 uint64_t fe, uint64_t oe, uint64_t ce,
                 uint64_t c)
    : port_no(n)
    , rx_packets(rp), tx_packets(tp)
    , rx_bytes(rb), tx_bytes(tb)
    , rx_dropped(rd), tx_dropped(td)
    , rx_errors(re), tx_errors(te)
    , rx_frame_err(fe), rx_over_err(oe), rx_crc_err(ce)
    , collisions(c)
  { }

  uint16_t port_no;
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
inline bool
operator==(const Stats_res_port& a, const Stats_res_port& b)
{
  return a.port_no == b.port_no
     and a.rx_packets == b.rx_packets
     and a.tx_packets == b.tx_packets
     and a.rx_bytes == b.rx_bytes
     and a.tx_bytes == b.tx_bytes
     and a.rx_dropped == b.rx_dropped
     and a.tx_dropped == b.tx_dropped
     and a.rx_errors == b.rx_errors
     and a.tx_errors == b.tx_errors
     and a.rx_frame_err == b.rx_frame_err
     and a.rx_over_err == b.rx_over_err
     and a.rx_crc_err == b.rx_crc_err
     and a.collisions == b.collisions;
}

// Bytes
constexpr std::size_t 
bytes(const Stats_res_port&) { return 104; }

// Is valid
constexpr Error_condition
is_valid(const Stats_res_port&) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Stats_res_port&);
Error_condition from_buffer(Buffer_view&, Stats_res_port&);

// To string
std::string to_string(const Stats_res_port&);


// -------------------------------------------------------------------------- //
// Stats Response: Ports

/// Port statistics
///
/// \remark Implements an OFPST_PORT Stats Response message
struct Stats_res_ports : Stats_payload_base<STATS_PORT>
{
  Stats_res_ports() = default;
  explicit Stats_res_ports(Sequence<Stats_res_port> p);

  Sequence<Stats_res_port> ports;
};

inline
Stats_res_ports::Stats_res_ports(Sequence<Stats_res_port> p)
  : ports(p)
{ }

inline bool
operator==(const Stats_res_ports& a, const Stats_res_ports& b)
{
  return a.ports == b.ports;
}

inline bool
operator!=(const Stats_res_ports& a, const Stats_res_ports& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_ports& p) { return bytes(p.ports); }

// Is valid
inline Error_condition
is_valid(const Stats_res_ports& p) { return is_valid(p.ports); }

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_ports&);
Error_condition from_buffer(Buffer_view&, Stats_res_ports&);

std::string to_string(const Stats_res_ports&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response Queue

/// Describe stats of each individual queue in an OFPST_QUEUE Stats Response 
/// message.
struct Stats_res_queue 
{
  Stats_res_queue() = default;
  Stats_res_queue(uint16_t n, uint32_t q, uint64_t b, uint64_t p, uint64_t e)
    : port_no(n), queue_id(q), tx_bytes(b), tx_packets(p), tx_errors(e)
  { }

  uint16_t port_no;
  uint32_t queue_id;
  uint64_t tx_bytes;
  uint64_t tx_packets;
  uint64_t tx_errors;
};

// Equality comparison
inline bool
operator==(const Stats_res_queue& a, const Stats_res_queue& b)
{
  return a.port_no == b.port_no
     and a.queue_id == b.queue_id
     and a.tx_bytes == b.tx_bytes
     and a.tx_errors == b.tx_errors;
}

inline bool
operator!=(const Stats_res_queue& a, const Stats_res_queue& b)
{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Stats_res_queue&) { return 32; }

// is_valid
inline Error_condition
is_valid(const Stats_res_queue&) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Stats_res_queue&);
Error_condition from_buffer(Buffer_view&, Stats_res_queue&);

// To string
std::string to_string(const Stats_res_queue&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response: Queues

/// Queue statistics for a port
///
/// \remark Implements an OFPST_QUEUE Stats Response message
struct Stats_res_queues : Stats_payload_base<STATS_QUEUE>
{
  Stats_res_queues() = default;
  explicit Stats_res_queues(Sequence<Stats_res_queue> q);

  Sequence<Stats_res_queue> queues;
};

inline
Stats_res_queues::Stats_res_queues(Sequence<Stats_res_queue> q)
  : queues(q)
{ }

inline bool
operator==(const Stats_res_queues& a, const Stats_res_queues& b)
{
  return a.queues == b.queues;
}

inline bool
operator!=(const Stats_res_queues& a, const Stats_res_queues& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_queues& q) { return bytes(q.queues); }

// Is valid
inline Error_condition
is_valid(const Stats_res_queues& q) { return is_valid(q.queues); }

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_queues&);
Error_condition from_buffer(Buffer_view&, Stats_res_queues&);

std::string to_string(const Stats_res_queues&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response Table

/// Describe stats of each individual table in an OFPST_TABLE Stats Response 
/// message.
struct Stats_res_table 
{
  Stats_res_table() = default;
  Stats_res_table(uint8_t t, const char* n, 
                  uint32_t w, uint32_t e,
                  uint32_t ac, uint32_t lc, uint32_t mc)
    : table_id(t), name(n)
    , wildcards(w), max_entries(e)
    , active_count(ac), lookup_count(lc), matched_count(mc)
  { }

  uint8_t  table_id;
  Stringbuf<32> name;
  uint32_t wildcards;
  uint32_t max_entries;
  uint32_t active_count;
  uint64_t lookup_count;
  uint64_t matched_count;
};

// Equality comparable
inline bool
operator==(const Stats_res_table& a, const Stats_res_table& b)
{
  return a.table_id == b.table_id
     and a.name == b.name
     and a.wildcards == b.wildcards
     and a.max_entries == b.max_entries
     and a.active_count == b.active_count
     and a.lookup_count == b.lookup_count
     and a.matched_count == b.matched_count;
}

inline bool
operator!=(const Stats_res_table& a, const Stats_res_table& b)
{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Stats_res_table&) { return 64; }

// is_valid
constexpr Error_condition
is_valid(const Stats_res_table&) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Stats_res_table&);
Error_condition from_buffer(Buffer_view&, Stats_res_table&);

// To string
std::string to_string(const Stats_res_table&, Formatter& fmt);


// -------------------------------------------------------------------------- //
// Stats Response: Tables

/// Flow table statistics
///
/// \remark Implements an OFPST_TABLE Stats Response message
struct Stats_res_tables : Stats_payload_base<STATS_TABLE>
{
  Stats_res_tables() = default;
  explicit Stats_res_tables(Sequence<Stats_res_table> t);

  Sequence<Stats_res_table> tables;
};

inline
Stats_res_tables::Stats_res_tables(Sequence<Stats_res_table> t)
  : tables(t)
{ }

inline bool
operator==(const Stats_res_tables& a, const Stats_res_tables& b)
{
  return a.tables == b.tables;
}

inline bool
operator!=(const Stats_res_tables& a, const Stats_res_tables& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_tables& t) { return bytes(t.tables); }

// Is valid
inline Error_condition
is_valid(const Stats_res_tables& t) { return is_valid(t.tables); }

// To/from
Error_condition to_buffer(Buffer_view&, const Stats_res_tables&);
Error_condition from_buffer(Buffer_view&, Stats_res_tables&);

std::string to_string(const Stats_res_tables&, Formatter&);


// -------------------------------------------------------------------------- //
// Stats Response Vendor

/// Vendor statistics
///
/// \remark Implements an OFPST_VENDOR Stats Response messge
struct Stats_res_vendor : Stats_payload_base<STATS_VENDOR>
{
  Stats_res_vendor() = default;
  explicit Stats_res_vendor(std::uint32_t id, const Greedy_buffer& b)
    : vendor_id(id), data(b)
  { }

  uint32_t      vendor_id;
  Greedy_buffer data;
};

// Equality comparison
inline bool
operator==(const Stats_res_vendor& a, const Stats_res_vendor& b)
{
  return a.vendor_id == b.vendor_id and a.data == b.data;
}

inline bool
operator!=(const Stats_res_vendor& a, const Stats_res_vendor& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_vendor& r) { return 4 + bytes(r.data); }

// is_valid
constexpr Error_condition
is_valid(const Stats_res_vendor&) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Stats_res_vendor&);
Error_condition from_buffer(Buffer_view&, Stats_res_vendor&);

// To string
std::string to_string(const Stats_res_vendor&);


// -------------------------------------------------------------------------- //
// Stats Response Payload

// NOTE: Sttas_res_payload has contains a non-trivial union. The
// vendor field has a non-trivial default constructor.

union Stats_res_payload_data
{
  Stats_res_payload_data() { }
  ~Stats_res_payload_data() { }

  Stats_res_desc      desc;
  Stats_res_flows     flow;
  Stats_res_aggregate aggr;
  Stats_res_tables    table;
  Stats_res_ports     port;
  Stats_res_queues    queue;
  Stats_res_vendor    vendor;
};

struct Stats_res_payload
{
  using Data = Stats_res_payload_data;

  Stats_res_payload() : init (false) { }

  explicit operator bool() const { return init; }

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

inline
Stats_res::~Stats_res()
{
  destroy(payload, header.type);
}

inline
Stats_res::Stats_res(Stats_res&& x)
  : header(std::move(x.header))
{ 
  construct(payload, std::move(x.payload), header.type); 
}

inline Stats_res&
Stats_res::operator=(Stats_res&& x)
{
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Stats_res::Stats_res(const Stats_res& x)
  : header(x.header)
{ 
  construct(payload, x.payload, header.type); 
}

inline Stats_res&
Stats_res::operator=(const Stats_res& x)
{
  header = x.header;
  assign(payload, x.payload, header.type); 
  return *this;
}

// Equality comparison
inline bool
operator==(const Stats_res& a, const Stats_res& b)
{
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Stats_res& a, const Stats_res& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res& r) 
{ 
  return bytes(r.header) + bytes(r.payload, r.header.type); 
}

// Is valid
inline Error_condition
is_valid(const Stats_res& r) {
  return is_valid(r.header) and is_valid(r.payload, r.header.type); 
}

// To/from
Error_condition to_buffer(Buffer_view& buf, const Stats_res& r);
Error_condition from_buffer(Buffer_view& buf, Stats_res& r);

// To string
std::string to_string(const Stats_res& r, Formatter& f);


// -------------------------------------------------------------------------- //
// Barrier Request

/// The Barrier Request message is sent by the controller to the switch. Any 
/// message before the barrier request must be completed processing before
/// a Barrier Response is sent back to controller and before any message
/// that arrives later than the Barrier Request.
///
/// \remark Defined in [OpenFlow v1.0, p36]
struct Barrier_req : Payload_base<BARRIER_REQ> { };


// -------------------------------------------------------------------------- //
// Barrier Response

/// The Barrier Response message is sent by the switch to the controller as
/// response to a Barrier Request message. Any message before the barrier request
/// must be completed processing before a Barrier Response is sent back to
/// controller and before any message that arrives later than the Barrier Request.
///
/// \remark Defined in [OpenFlow v1.0, p36]
struct Barrier_res : Payload_base<BARRIER_RES> { };


// -------------------------------------------------------------------------- //
// Queue Get Config Request

/// The Queue Get Config Request is sent by the controller to the switch to
/// obtain configurations of the queues in the switch.
///
/// \remark defined in [OpenFlow v1.0, p29]
struct Queue_get_config_req : Payload_base<QUEUE_GET_CONFIG_REQ> 
{
  /// Construct an empty Group_mod message
  Queue_get_config_req() = default;
  
  /// Construct a Group_mod message with value of all the fields
  explicit Queue_get_config_req(uint16_t p);

  uint16_t port;
};

inline
Queue_get_config_req::Queue_get_config_req(uint16_t p) 
  : port(p) 
{ }

/// Returns true when two Queue_get_config_req are totally equal. 
///
/// \relates Queue_get_config_req
inline bool 
operator==(const Queue_get_config_req& a, const Queue_get_config_req& b)
{
  return a.port == b.port;
}

/// Returns true when two Queue_get_config_req structs do not compare equal.
///
/// \relates Queue_get_config_req
inline bool
operator!=(const Queue_get_config_req& a, const Queue_get_config_req& b)
{
  return !(a == b);
}

/// Return number of bytes of an Queue_get_config_req message.
///
/// \relates Queue_get_config_req
constexpr std::size_t
bytes(const Queue_get_config_req&) { return 4; }

/// Validates the value of a Queue_get_config_req message. 
///
/// \relates Queue_get_config_req
inline Error_condition
is_valid(const Queue_get_config_req& q) { 
  return ok(q.port < 0xFF00, BAD_QUEUE_CONFIG_PORT);
}

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
// Queue Property Type

enum Queue_property_type : uint16_t
{
  QUEUE_PROPERTY_NONE,
  QUEUE_PROPERTY_MIN_RATE
};

// Is valid
constexpr Error_condition
is_valid(Queue_property_type t) {
  return ok(t <= QUEUE_PROPERTY_MIN_RATE, BAD_QUEUE_PROPERTY);
}

// To string
std::string to_string(Queue_property_type);

template<Queue_property_type K>
  using Queue_property_base = Basic_payload_base<Queue_property_type, K>;


// -------------------------------------------------------------------------- //
// Queue Property None

struct Queue_property_none : Queue_property_base<QUEUE_PROPERTY_NONE> { };


// -------------------------------------------------------------------------- //
// Queue Property Min Rate

struct Queue_property_min_rate : Queue_property_base<QUEUE_PROPERTY_MIN_RATE>
{
  Queue_property_min_rate() = default;
  explicit Queue_property_min_rate(uint16_t r) : rate(r) { }
  
  uint16_t rate;
};

// Equality comparison
inline bool
operator==(const Queue_property_min_rate& a, const Queue_property_min_rate& b)
{
  return a.rate == b.rate;
}

inline bool
operator!=(const Queue_property_min_rate& a, const Queue_property_min_rate& b)

{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Queue_property_min_rate&) { return 8; }

// Is valid
constexpr Error_condition 
is_valid(const Queue_property_min_rate&) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Queue_property_min_rate&);
Error_condition from_buffer(Buffer_view&, Queue_property_min_rate&);

// To string
std::string to_string(const Queue_property_min_rate&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue Property Header

struct Queue_property_header
{
  Queue_property_type property;
  uint16_t            length;
};

// Equality comparison
inline bool
operator==(const Queue_property_header& a, const Queue_property_header& b)
{
  return a.property == b.property and a.length == b.length;
}

inline bool
operator!=(const Queue_property_header& a, const Queue_property_header& b)
{
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Queue_property_header& h) { return 8; }

// Is valid
constexpr Error_condition 
is_valid(const Queue_property_header& h) { return SUCCESS; }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Queue_property_header&);
Error_condition from_buffer(Buffer_view&, Queue_property_header&);

// To string
std::string to_string(const Queue_property_header&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue Property

union Queue_property_payload_data
{
  Queue_property_none     none;
  Queue_property_min_rate min_rate;
};

struct Queue_property_payload 
{
  using Data = Queue_property_payload_data;
  
  Queue_property_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

void
construct(Queue_property_payload&, 
                  Queue_property_type);

void 
construct(Queue_property_payload&, const Queue_property_payload&,
                  Queue_property_type);

Queue_property_payload& 
assign(Queue_property_payload&, const Queue_property_payload&,
               Queue_property_type);

bool 
equal(const Queue_property_payload&, const Queue_property_payload&,
              Queue_property_type, Queue_property_type);

std::size_t 
bytes(const Queue_property_payload&,
              Queue_property_type);

Error_condition is_valid(const Queue_property_payload&, Queue_property_type);

Error_condition to_buffer(Buffer_view&, const Queue_property_payload&, Queue_property_type);

Error_condition from_buffer(Buffer_view&, Queue_property_payload&, Queue_property_type);

std::string
to_string(const Queue_property_payload&, Formatter&
                  Queue_property_type);


// -------------------------------------------------------------------------- //
// Queue Property

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

inline
Queue_property::Queue_property(const Queue_property& x)
  : header(x.header)
{
  construct(payload, x.payload, header.property);
}

inline Queue_property&
Queue_property::operator=(const Queue_property& x)
{
  header = x.header;
  assign(payload, x.payload, x.header.property);
  return *this;
}

// Equality comparable
inline bool
operator==(const Queue_property& a, const Queue_property& b) 
{
  return a.header == b.header 
     and equal(a.payload, b.payload, a.header.property, b.header.property);
}

inline bool
operator!=(const Queue_property& a, const Queue_property& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Queue_property& p) 
{ 
  return bytes(p.header) 
       + bytes(p.payload, p.header.property);
}

// Is valid
inline Error_condition
is_valid(const Queue_property& p) {
  if (Error_decl err = is_valid(p.header))
    return err;
  if (Error_decl err = is_valid(p.payload, p.header.property))
    return err;
  return SUCCESS;
}

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Queue_property&);
Error_condition from_buffer(Buffer_view&, Queue_property&);

// To string
std::string to_string(const Queue_property&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue 

struct Queue
{
  using Property_sequence = Sequence<Queue_property>;

  Queue() = default;
  Queue(uint32_t id, uint16_t l) : queue_id(id), length(l) { }

  uint32_t queue_id;
  uint16_t length;
  Property_sequence properties;
};

// Equality comparison
inline bool
operator==(const Queue& a, const Queue& b)
{
  return a.queue_id == b.queue_id
     and a.length == b.length
     and a.properties == b.properties;
}

inline bool
operator!=(const Queue& a, const Queue& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Queue& q) { return 8 + bytes(q.properties); }

// Is valid
inline Error_condition
is_valid(const Queue& q) { return is_valid(q.properties); }

// To/from buffer
Error_condition to_buffer(Buffer_view&, const Queue&);
Error_condition from_buffer(Buffer_view&, Queue&);

// To string
std::string to_string(const Queue&, Formatter&);


// -------------------------------------------------------------------------- //
// Queue Get Config Response

/// The Queue Get Config Response message is sent by the switch to the
/// controller as response to a Queue Get Config Request message. It contains
/// the configuration information of queues associated with the port 
/// specified in the Queue Get Config Request message.
/// 
/// \remark Defined in [OpenFlow v1.0, p29]
struct Queue_get_config_res : Payload_base<QUEUE_GET_CONFIG_RES>
{
  /// Construct an empty Queue_get_config_res message
  Queue_get_config_res() = default;
  
  /// Construct a Queue_get_config_res message with value of all the fields
  Queue_get_config_res(uint16_t p, Sequence<Queue> q);

  uint16_t port;
  Sequence<Queue> queues;
};

inline
Queue_get_config_res::Queue_get_config_res(uint16_t p, Sequence<Queue> q)
  : port(p), queues(q) 
{ }

/// Returns true when two Queue_get_config_res are totally equal. 
///
/// \relates Queue_get_config_res
inline bool 
operator==(const Queue_get_config_res& a, const Queue_get_config_res& b)
{
  return a.port == b.port and a.queues == b.queues;
}

/// Returns true when two Queue_get_config_res structs do not compare equal.
///
/// \relates Queue_get_config_res
inline bool 
operator!=(const Queue_get_config_res& a, const Queue_get_config_res& b)
{
  return !(a == b);
}

/// Return number of bytes of an Queue_get_config_res message.
///
/// \relates Queue_get_config_res
inline std::size_t 
bytes(const Queue_get_config_res& qgcr) { return 8 + bytes(qgcr.queues); }

// FIXME: Shouldn't this also validate the port field?
/// Validates the value of a Queue_get_config_res message. 
///
/// \relates Queue_get_config_res
inline Error_condition
is_valid(const Queue_get_config_res& qgcr) { return is_valid(qgcr.queues); }

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
  Vendor               vendor;
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
  Port_mod             port_mod;
  Stats_req            stats_req;
  Stats_res            stats_res;
  Barrier_req          barrier_req;
  Barrier_res          barrier_res;
  Queue_get_config_req queue_get_config_req;
  Queue_get_config_res queue_get_config_res;
};

/// Describe the payload of an OpenFlow v1.0 message. An OpenFlow v1.0 Message
/// consists of a header and a payload. The payload is a variant
/// that can be any type of OpenFlow v1.1 message struct.
struct Payload 
{
  using Data = Payload_data;

  Payload() : init (false) { }

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

void destroy(Payload&, Message_type);

bool equal(const Payload&, const Payload&, Message_type, Message_type);

std::size_t bytes(const Payload&, Message_type);
Error_condition is_valid(const Payload&, Message_type);

Error_condition to_buffer(Buffer_view&, const Payload&, Message_type);
Error_condition from_buffer(Buffer_view&, Payload&, Message_type);

std::string to_string(const Payload&, Formatter&, Message_type);

// -------------------------------------------------------------------------- //
// Header

/// Every OpenFlow message begins with a fixed-sized header. This header 
/// describes the OpenFlow protocol version, the type of message, the length
/// in bytes (inclusive of the header), and the transaction id (used to match
/// responses to requests).
///
/// \remark [OpenFlow Switch Specification Version 1.0.0 p15-16](http://...)
struct Header
{
  Header() = default;
  
  Header(Message_type t)
    : version(VERSION), type(t) { }
  
  Header(Message_type t, uint16_t l, uint32_t id)
    : version(VERSION), type(t), length(l), xid(id) { }

  // Payload construction
  template<typename T, typename = typename T::Tag>
    explicit Header(const T& x)
      : version(VERSION), type(kind_of(x)), length(8 + bytes(x)) { }
  
  template<typename T, typename = typename T::Tag>
    Header(const T& x, uint32_t id)
      : version(VERSION), type(kind_of(x)), length(8 + bytes(x)), xid(id) { }

  Version_type version;
  Message_type type;
  uint16_t length;
  uint32_t xid; 
};

bool operator==(const Header& a, const Header& b);

bool operator!=(const Header& a, const Header& b);

constexpr std::size_t bytes(const Header&);

Error_condition is_valid(const Header& h);

Error_condition to_buffer(Buffer_view& buf, const Header& h);

Error_condition from_buffer(Buffer_view& buf, Header& h);

std::string to_string(const Header& h, Formatter&);


// -------------------------------------------------------------------------- //
// Message
//
// TODO: Add uninterpreted message data.

/// \brief Encapsulates an OpenFlow v1.0 message.
struct Message
{
  /// \brief Default construct the message.
  Message() = default;

  // Move semantics
  Message(Message&&);
  Message& operator=(Message&&);

  // Copy semantics
  Message(const Message&);
  Message& operator=(const Message&);

  // Payload construction
  template<typename T, typename Tag = typename T::Tag>
    explicit Message(T&&);

  // Payload construction
  template<typename T, typename Tag = typename T::Tag>
    Message(T&&, uint32_t id);

  // Payload forwarding constructor
  template<typename Tag, typename... Args>
    Message(uint32_t id, Tag t, Args&&... args);

  ~Message();

  static Factory factory(Xid_generator<uint32_t>& g) { return Factory(g); }

  Header  header;
  Payload payload;
};

/// \brief Returns true when the arguments compare equal.
bool operator==(const Message& a, const Message& b);

/// \brief Returns true when the arguments do not compare equal.
bool operator!=(const Message& a, const Message& b);

std::size_t bytes(const Message& m);

/// \brief Validates the representation of the object.
Error_condition is_valid(const Message& m);

/// \brief Writes the value into a buffer view.
Error_condition to_buffer(Buffer_view& b, const Message& m);

/// \brief Reads the value from a buffer view.
Error_condition from_buffer(Buffer_view& b, Message& m);

/// \brief Returns a formatted string representation of the value.
std::string to_string(const Message& m, Formatter&);

} // namespace v1_0
} // namespace ofp
} // namespace flog

#include "message.ipp"

#endif
