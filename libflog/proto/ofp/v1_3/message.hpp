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

#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_3_H
#define FLOWGRAMMABLE_PROTO_OFP_V1_3_H

#include <cassert>
#include <cstdint>
#include <string>
#include <sstream>

#include <libflog/utilities.hpp>
#include <libflog/buffer.hpp>
#include <libflog/message.hpp>
#include <libflog/sequence.hpp>
#include <libflog/proto/ofp/ofp.hpp>
#include <libflog/proto/ofp/xid_gen.hpp>

#include "factory.hpp"

/// \file v1_3/message.hpp

namespace flog {
namespace ofp {
namespace v1_3 {

using ofp::to_buffer;
using ofp::from_buffer;


// -------------------------------------------------------------------------- //
// Error code

/// Represents a specific failure in message processing. This enumeration is
/// used to describe the result values of to_buffer(), from_buffer(), and
/// is_valid().
enum Error_code {
  FAILURE = -1, ///< General failure
  SUCCESS = 0,  ///< Success

  // Basic codes (copied from Basic_error_code)
  AVAILABLE_BUFFER, ///< Not enough bytes to read a buffer
  AVAILABLE_STRING, ///< Not enough bytes to read a string

  EXCESS_SEQUENCE,  ///< Excess data in a sequence

  // Semantic codes (produced during validation)
  BAD_OXM_CLASS,             ///< Invalid value of Match::Type
  BAD_OXM_FIELD,             ///< Invalid value of OXM_entry_field
  BAD_OXM_INIT,              ///< An uninitialized OXM_entry was validated
  BAD_MATCH_TYPE,            ///< Invalid value of Match::Type
  BAD_MATCH_LENGTH,          ///< The match length is invalid
  BAD_ACTION,                ///< Invalid value of Action_type
  BAD_ACTION_LENGTH,         ///< The action length is invalid
  BAD_ACTION_INIT,           ///< An uninitialized action was validated
  BAD_ACTION_ENQUEUE_PORT,   ///< The port in Action_enqueue is invalid
  BAD_INSTRUCTION,           ///< Invalid value of Instruction_type
  BAD_INSTRUCTION_LENGTH,    ///< The instruction length is invalid
  BAD_INSTRUCTION_INIT,      ///< An uninitialized action was validated
  BAD_PORT_ID,               ///< The id in Port is invalid
  BAD_BUCKET_LENGTH,         ///< The Bucket length is invalid
  BAD_VERSION,               ///< The version number was not 1
  BAD_MESSAGE,               ///< Invalid value of Message_type
  BAD_MESSAGE_LENGTH,        ///< The header length is invalid
  BAD_MESSAGE_INIT,          ///< The message payload is not initialized
  BAD_HEADER_LENGTH,         ///< The header length is invalid
  BAD_ERROR_TYPE,            ///< Invalid value of Error::Type
  BAD_HELLO_FAILED,          ///< Invalid value of Error::Hello_failed
  BAD_BAD_REQUEST,           ///< Invalid value of Error::Bad_request
  BAD_BAD_ACTION,            ///< Invalid value of Error::Bad_action
  BAD_BAD_INSTRUCTION,       ///< Invalid value of Error::Bad_instruction
  BAD_BAD_MATCH,             ///< Invalid value of Error::Bad_match
  BAD_FLOW_MOD_FAILED,       ///< Invalid value of Error::Flow_mod_failed
  BAD_GROUP_MOD_FAILED,      ///< Invalid value of Error::Group_mod_failed
  BAD_PORT_MOD_FAILED,       ///< Invalid value of Error::Port_mod_failed
  BAD_TABLE_MOD_FAILED,      ///< Invalid value of Error::Table_mod_failed
  BAD_QUEUE_OP_FAILED,       ///< Invalid value of Error::Queue_op_failed
  BAD_SWITCH_CONFIG_FAILED,  ///< Invalid value of Error::Switch_config_failed
  BAD_ROLE_REQUEST_FAILED,   ///< Invalid value of Error::Role_request_failed
  BAD_METER_MOD_FAILED,      ///< Invalid value of Error::Meter_mod_failed
  BAD_TABLE_FEATURES_FAILED, ///< Invalid value of Error::Table_features_failed
  ///Invalid value of flags in Get_config_res or Set_config
  BAD_CONFIG_FLAGS,          ///< Invalid value of Config_message_base::Flags
  BAD_FLOW_MOD_COMMAND,      ///< Invalid value of Flow_mod::Command
  BAD_FLOW_MOD_FLAGS,        ///< Invalid value of Flow_mod::Flags
  BAD_GROUP_MOD_COMMAND,     ///< Invalid value of Group_mod::Command
  BAD_GROUP_MOD_TYPE,        ///< Invalid value of Group_mod::Type
  BAD_TABLE_MOD_CONFIG,      ///< Invalid value of Group_mod::Config
  BAD_FEATURE_RES_CAPABILITY,///< Invalid value of Feature_res::Capability_type
  BAD_PACKET_IN_REASON,      ///< Invalid value of Packet_in::Reason_type
  BAD_FLOW_REMOVED_REASON,   ///< Invalid value of Flow_removed::Reason_type
  BAD_PORT_STATUS_REASON,    ///< Invalid value of Port_status::Reason_type
  BAD_PACKET_OUT_LENGTH,     ///< The Packet_out length is invalid
  BAD_MULTIPART,             ///< Invalid value of Multipart_type
  BAD_MULTIPART_INIT,        ///< An uninitialized Multipart was validated
  BAD_TABLE_FEATURE_PROPERTY,///< Invalid value of Table_feature_property_type
  /// An uninitialized Table_feature_property was validated
  BAD_TABLE_FEATURE_PROPERTY_INIT,
  /// The Multipart_res_group length is invalid
  BAD_MULTIPART_RES_GROUP_LENGTH,
  /// The Multipart_res_group_desc length is invalid
  BAD_MULTIPART_RES_GROUP_DESC_LENGTH,
  BAD_METER_BAND,            ///< Invalid value of Meter_band_type
  BAD_METER_BAND_INIT,       ///< An uninitialized Meter_band was validated
  BAD_ROLE,                  ///< Invalid value of Role
  BAD_METER_MOD_COMMAND,     ///< Invalid value of Meter_mod::command
  BAD_METER_MOD_ID,          ///< Invalid value of Meter_mod::Id_value
  BAD_QUEUE_PROPERTY,        ///< Invalid value of Queue_property_type
  BAD_QUEUE_PROPERTY_LENGTH, ///< The Queue_property length is invalid
  BAD_QUEUE_PROPERTY_INIT,   ///< An uninitialized Queue_property was validated
  BAD_QUEUE_CONFIG_PORT,     ///< Invalid value of Queue_get_config_req::port

  // Availability errors
  AVAILABLE_ACTION_OUTPUT,      ///< Not enough bytes for an Action_output
  AVAILABLE_ACTION_COPY_TTL_OUT,///< Not enough bytes for an Action_copy_ttl_out
  AVAILABLE_ACTION_COPY_TTL_IN, ///< Not enough bytes for an Action_copy_ttl_in
  AVAILABLE_ACTION_MPLS_TTL,    ///< Not enough bytes for an Action_mpls_ttl
  AVAILABLE_ACTION_SET_MPLS_TTL,///< Not enough bytes for an Action_set_mpls_ttl
  AVAILABLE_ACTION_DEC_MPLS_TTL,///< Not enough bytes for an Action_dec_mpls_ttl
  AVAILABLE_ACTION_PUSH_POP,    ///< Not enough bytes for an Action_push_pop
  AVAILABLE_ACTION_PUSH_VLAN,   ///< Not enough bytes for an Action_push_vlan
  AVAILABLE_ACTION_POP_VLAN,    ///< Not enough bytes for an Action_pop_vlan
  AVAILABLE_ACTION_PUSH_MPLS,   ///< Not enough bytes for an Action_push_mpls
  AVAILABLE_ACTION_POP_MPLS,    ///< Not enough bytes for an Action_pop_mpls
  AVAILABLE_ACTION_PUSH_PBB,    ///< Not enough bytes for an Action_push_pbb
  AVAILABLE_ACTION_SET_QUEUE,   ///< Not enough bytes for an Action_set_queue
  AVAILABLE_ACTION_GROUP,       ///< Not enough bytes for an Action_group
  AVAILABLE_ACTION_NW_TTL,      ///< Not enough bytes for an Action_nw_ttl
  AVAILABLE_ACTION_SET_NW_TTL,  ///< Not enough bytes for an Action_set_nw_ttl
  AVAILABLE_ACTION_DEC_NW_TTL,  ///< Not enough bytes for an Action_dec_nw_ttl
  AVAILABLE_ACTION_SET_FIELD,   ///< Not enough bytes for an Action_set_field
  /// Not enough bytes for an Action_set_field_padding
  AVAILABLE_ACTION_SET_FIELD_PADDING, 
  AVAILABLE_ACTION_POP_PBB,     ///< Not enough bytes for an Action_pop_pbb
  AVAILABLE_ACTION_EXPERIMENTER,///< Not enough bytes for an Action_experimenter
  AVAILABLE_ACTION_HEADER,      ///< Not enough bytes for an Action_header
  AVAILABLE_ACTION_PAYLOAD,     ///< Not enough bytes for an Action_payload

  AVAILABLE_OXM_ENTRY_VLAN_PCP, ///< Not enough bytes for an Oxm_entry_vlan_pcp
  AVAILABLE_OXM_ENTRY_IP_DSCP,  ///< Not enough bytes for an Oxm_entry_ip_dscp
  AVAILABLE_OXM_ENTRY_IP_ECN,   ///< Not enough bytes for an Oxm_entry_ip_ecn
  AVAILABLE_OXM_ENTRY_IP_PROTO, ///< Not enough bytes for an Oxm_entry_ip_proto
  /// Not enough bytes for an Oxm_entry_icmpv4_type
  AVAILABLE_OXM_ENTRY_ICMPV4_TYPE,
  /// Not enough bytes for an Oxm_entry_icmpv4_code
  AVAILABLE_OXM_ENTRY_ICMPV4_CODE,
  /// Not enough bytes for an Oxm_entry_icmpv6_type
  AVAILABLE_OXM_ENTRY_ICMPV6_TYPE,
  /// Not enough bytes for an Oxm_entry_icmpv6_code
  AVAILABLE_OXM_ENTRY_ICMPV6_CODE,
  AVAILABLE_OXM_ENTRY_MPLS_TC,  ///< Not enough bytes for an Oxm_entry_mpls_tc
  AVAILABLE_OXM_ENTRY_MPLS_BOS, ///< Not enough bytes for an Oxm_entry_mpls_bos
  AVAILABLE_OXM_ENTRY_VLAN_VID, ///< Not enough bytes for an Oxm_entry_vlan_vid
  AVAILABLE_OXM_ENTRY_ETH_TYPE, ///< Not enough bytes for an Oxm_entry_eth_type
  AVAILABLE_OXM_ENTRY_TCP_SRC,  ///< Not enough bytes for an Oxm_entry_tcp_src
  AVAILABLE_OXM_ENTRY_TCP_DST,  ///< Not enough bytes for an Oxm_entry_tcp_dst
  AVAILABLE_OXM_ENTRY_UDP_SRC,  ///< Not enough bytes for an Oxm_entry_udp_src
  AVAILABLE_OXM_ENTRY_UDP_DST,  ///< Not enough bytes for an Oxm_entry_udp_dst
  AVAILABLE_OXM_ENTRY_SCTP_SRC, ///< Not enough bytes for an Oxm_entry_sctp_src
  AVAILABLE_OXM_ENTRY_SCTP_DST, ///< Not enough bytes for an Oxm_entry_sctp_dst
  AVAILABLE_OXM_ENTRY_ARP_OP,   ///< Not enough bytes for an Oxm_entry_arp_op
  /// Not enough bytes for an Oxm_entry_vlan_vid_mask
  AVAILABLE_OXM_ENTRY_VLAN_VID_MASK,
  AVAILABLE_OXM_ENTRY_IN_PORT,  ///< Not enough bytes for an Oxm_entry_in_port
  /// Not enough bytes for an Oxm_entry_in_phy_port
  AVAILABLE_OXM_ENTRY_IN_PHY_PORT,
  /// Not enough bytes for an Oxm_entry_mpls_label
  AVAILABLE_OXM_ENTRY_MPLS_LABEL,
  /// Not enough bytes for an Oxm_entry_ipv6_flabel
  AVAILABLE_OXM_ENTRY_IPV6_FLABEL,
  AVAILABLE_OXM_ENTRY_PBB_ISID, ///< Not enough bytes for an Oxm_entry_pbb_isid
  /// Not enough bytes for an Oxm_entry_ipv6_flabel_mask
  AVAILABLE_OXM_ENTRY_IPV6_FLABEL_MASK,
  /// Not enough bytes for an Oxm_entry_pbb_isid_mask
  AVAILABLE_OXM_ENTRY_PBB_ISID_MASK,
  AVAILABLE_OXM_ENTRY_IPV4_SRC, ///< Not enough bytes for an Oxm_entry_ipv4_src
  AVAILABLE_OXM_ENTRY_IPV4_DST, ///< Not enough bytes for an Oxm_entry_ipv4_dst
  AVAILABLE_OXM_ENTRY_ARP_SPA,  ///< Not enough bytes for an Oxm_entry_arp_spa
  AVAILABLE_OXM_ENTRY_ARP_TPA,  ///< Not enough bytes for an Oxm_entry_arp_tpa
  /// Not enough bytes for an Oxm_entry_ipv4_src_mask
  AVAILABLE_OXM_ENTRY_IPV4_SRC_MASK,
  /// Not enough bytes for an Oxm_entry_ipv4_dst_mask
  AVAILABLE_OXM_ENTRY_IPV4_DST_MASK,
  /// Not enough bytes for an Oxm_entry_arp_spa_mask
  AVAILABLE_OXM_ENTRY_ARP_SPA_MASK,
  /// Not enough bytes for an Oxm_entry_arp_tpa_mask
  AVAILABLE_OXM_ENTRY_ARP_TPA_MASK,
  AVAILABLE_OXM_ENTRY_ETH_DST,  ///< Not enough bytes for an Oxm_entry_eth_dst
  AVAILABLE_OXM_ENTRY_ETH_SRC,  ///< Not enough bytes for an Oxm_entry_eth_src
  AVAILABLE_OXM_ENTRY_ARP_SHA,  ///< Not enough bytes for an Oxm_entry_arp_sha
  AVAILABLE_OXM_ENTRY_ARP_THA,  ///< Not enough bytes for an Oxm_entry_arp_tha
  /// Not enough bytes for an Oxm_entry_ipv6_nd_sll
  AVAILABLE_OXM_ENTRY_IPV6_ND_SLL,
  /// Not enough bytes for an Oxm_entry_ipv6_nd_tll
  AVAILABLE_OXM_ENTRY_IPV6_ND_TLL,
  /// Not enough bytes for an Oxm_entry_eth_dst_mask
  AVAILABLE_OXM_ENTRY_ETH_DST_MASK,
  /// Not enough bytes for an Oxm_entry_eth_src_mask
  AVAILABLE_OXM_ENTRY_ETH_SRC_MASK,
  /// Not enough bytes for an Oxm_entry_arp_sha_mask
  AVAILABLE_OXM_ENTRY_ARP_SHA_MASK,
  /// Not enough bytes for an Oxm_entry_arp_tha_mask
  AVAILABLE_OXM_ENTRY_ARP_THA_MASK,
  AVAILABLE_OXM_ENTRY_METADATA, ///< Not enough bytes for an Oxm_entry_metadata
  AVAILABLE_OXM_ENTRY_TUNNEL_ID,///< Not enough bytes for an Oxm_entry_tunnel_id
  /// Not enough bytes for an Oxm_entry_metadata_mask
  AVAILABLE_OXM_ENTRY_METADATA_MASK,
  /// Not enough bytes for an Oxm_entry_tunnel_id_mask
  AVAILABLE_OXM_ENTRY_TUNNEL_ID_MASK,
  AVAILABLE_OXM_ENTRY_IPV6_SRC, ///< Not enough bytes for an Oxm_entry_ipv6_src
  AVAILABLE_OXM_ENTRY_IPV6_DST, ///< Not enough bytes for an Oxm_entry_ipv6_dst
  /// Not enough bytes for an Oxm_entry_ipv6_nd_target
  AVAILABLE_OXM_ENTRY_IPV6_ND_TARGET,
  /// Not enough bytes for an Oxm_entry_ipv6_src_mask
  AVAILABLE_OXM_ENTRY_IPV6_SRC_MASK,
  /// Not enough bytes for an Oxm_entry_ipv6_dst_mask
  AVAILABLE_OXM_ENTRY_IPV6_DST_MASK,
  /// Not enough bytes for an Oxm_entry_ipv6_exthdr
  AVAILABLE_OXM_ENTRY_IPV6_EXTHDR,
  ///Not enough bytes for an Oxm_entry_ipv6_exthdr_mask
  AVAILABLE_OXM_ENTRY_IPV6_EXTHDR_MASK,
  AVAILABLE_OXM_ENTRY_PAYLOAD,  ///< Not enough bytes for an Oxm_entry_payload
  AVAILABLE_OXM_ENTRY_HEADER,   ///< Not enough bytes for an Oxm_entry_header
  AVAILABLE_OXM_EXPERIMENTER,   ///< Not enough bytes for an Oxm_experimenter
  AVAILABLE_OXM_ENTRY,          ///< Not enough bytes for an Oxm_entry
  AVAILABLE_MATCH,              ///< Not enough bytes for an Match
  AVAILABLE_MATCH_PADDING,      ///< Not enough bytes for an Match_padding

  /// Not enough bytes for an Instruction_goto_table
  AVAILABLE_INSTRUCTION_GOTO_TABLE,
  /// Not enough bytes for an Instruction_write_metadata
  AVAILABLE_INSTRUCTION_WRITE_METADATA,
  AVAILABLE_INSTRUCTION_ACTION, ///< Not enough bytes for an Instruction_action
  /// Not enough bytes for an Instruction_write_actions
  AVAILABLE_INSTRUCTION_WRITE_ACTIONS,
  /// Not enough bytes for an Instruction_apply_actions
  AVAILABLE_INSTRUCTION_APPLY_ACTIONS,
  /// Not enough bytes for an Instruction_clear_actions
  AVAILABLE_INSTRUCTION_CLEAR_ACTIONS,
  AVAILABLE_INSTRUCTION_METER,  ///< Not enough bytes for an Instruction_meter
  /// Not enough bytes for an Instruction_experimenter
  AVAILABLE_INSTRUCTION_EXPERIMENTER,
  AVAILABLE_INSTRUCTION_HEADER, ///< Not enough bytes for an Instruction_header
  AVAILABLE_INSTRUCTION_PAYLOAD,///< Not enough bytes for an Instruction_payload
  AVAILABLE_INSTRUCTION,        ///< Not enough bytes for an Instruction

  /// Not enough bytes for an Queue_property_min_rate
  AVAILABLE_QUEUE_PROPERTY_MIN_RATE,
  /// Not enough bytes for an Queue_property_max_rate
  AVAILABLE_QUEUE_PROPERTY_MAX_RATE,
  /// Not enough bytes for an Queue_property_experimenter
  AVAILABLE_QUEUE_PROPERTY_EXPERIMENTER,
  /// Not enough bytes for an Queue_property_header
  AVAILABLE_QUEUE_PROPERTY_HEADER,
  /// Not enough bytes for an Queue_property_payload
  AVAILABLE_QUEUE_PROPERTY_PAYLOAD,
  AVAILABLE_QUEUE_PROPERTIES,   ///< Not enough bytes for an Queue_properties
  AVAILABLE_QUEUE,              ///< Not enough bytes for an Queue

  AVAILABLE_PORT,               ///< Not enough bytes for an Port

  AVAILABLE_BUCKET,             ///< Not enough bytes for an Bucket

  AVAILABLE_HEADER,             ///< Not enough bytes for an Header
  AVAILABLE_PAYLOAD,            ///< Not enough bytes for an Payload
  AVAILABLE_HELLO,              ///< Not enough bytes for an Hello
  AVAILABLE_ERROR,              ///< Not enough bytes for an Error
  AVAILABLE_ECHO_REQ,           ///< Not enough bytes for an Echo_req
  AVAILABLE_ECHO_RES,           ///< Not enough bytes for an Echo_res
  AVAILABLE_EXPERIMENTER,       ///< Not enough bytes for an Experimenter
  AVAILABLE_FEATURE_REQ,        ///< Not enough bytes for an Feature_req
  AVAILABLE_FEATURE_RES,        ///< Not enough bytes for an Feature_res
  AVAILABLE_GET_CONFIG_REQ,     ///< Not enough bytes for an Get_config_req
  AVAILABLE_GET_CONFIG_RES,     ///< Not enough bytes for an Get_config_res
  AVAILABLE_SET_CONFIG,         ///< Not enough bytes for an Set_config
  AVAILABLE_PACKET_IN,          ///< Not enough bytes for an Packet_in
  AVAILABLE_PACKET_IN_PADDING,  ///< Not enough bytes for an Packet_in_padding
  AVAILABLE_FLOW_REMOVED,       ///< Not enough bytes for an Flow_removed
  AVAILABLE_PORT_STATUS,        ///< Not enough bytes for an Port_status
  AVAILABLE_PACKET_OUT,         ///< Not enough bytes for an Packet_out
  AVAILABLE_FLOW_MOD,           ///< Not enough bytes for an Flow_mod
  AVAILABLE_GROUP_MOD,          ///< Not enough bytes for an Group_mod
  AVAILABLE_PORT_MOD,           ///< Not enough bytes for an Port_mod
  AVAILABLE_TABLE_MOD,          ///< Not enough bytes for an Table_mod

  AVAILABLE_MULTIPART_REQ_DESC, ///< Not enough bytes for an Multipart_req_desc
  /// Not enough bytes for an Multipart_req_flow_base
  AVAILABLE_MULTIPART_REQ_FLOW_BASE,
  AVAILABLE_MULTIPART_REQ_FLOW, ///< Not enough bytes for an Multipart_req_flow
  /// Not enough bytes for an Multipart_req_aggregate
  AVAILABLE_MULTIPART_REQ_AGGREGATE,
  AVAILABLE_MULTIPART_REQ_TABLE,///< Not enough bytes for an Multipart_req_table
  AVAILABLE_MULTIPART_REQ_PORT, ///< Not enough bytes for an Multipart_req_port
  AVAILABLE_MULTIPART_REQ_QUEUE,///< Not enough bytes for an Multipart_req_queue
  AVAILABLE_MULTIPART_REQ_GROUP,///< Not enough bytes for an Multipart_req_group
  /// Not enough bytes for an Multipart_req_group_desc
  AVAILABLE_MULTIPART_REQ_GROUP_DESC,
  /// Not enough bytes for an Multipart_req_group_features
  AVAILABLE_MULTIPART_REQ_GROUP_FEATURES,
  /// Not enough bytes for an Multipart_req_meter_base
  AVAILABLE_MULTIPART_REQ_METER_BASE,
  AVAILABLE_MULTIPART_REQ_METER,///< Not enough bytes for an Multipart_req_meter
  /// Not enough bytes for an Multipart_req_meter_config
  AVAILABLE_MULTIPART_REQ_METER_CONFIG,
  /// Not enough bytes for an Multipart_req_meter_features
  AVAILABLE_MULTIPART_REQ_METER_FEATURES,
  /// Not enough bytes for an Table_feature_property_instructions_base
  AVAILABLE_TABLE_FEATURE_PROPERTY_INSTRUCTIONS_BASE,
  /// Not enough bytes for an Table_feature_property_instructions
  AVAILABLE_TABLE_FEATURE_PROPERTY_INSTRUCTIONS,
  /// Not enough bytes for an Table_feature_property_instructions_miss
  AVAILABLE_TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS,
  AVAILABLE_TABLE_ID,           ///< Not enough bytes for an Table_id
  /// Not enough bytes for an Table_feature_property_next_tables_base
  AVAILABLE_TABLE_FEATURE_PROPERTY_NEXT_TABLES_BASE,
  /// Not enough bytes for an Table_feature_property_next_tables
  AVAILABLE_TABLE_FEATURE_PROPERTY_NEXT_TABLES,
  /// Not enough bytes for an Table_feature_property_next_tables_miss
  AVAILABLE_TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS,
  /// Not enough bytes for an Table_feature_property_actions_base
  AVAILABLE_TABLE_FEATURE_PROPERTY_ACTIONS_BASE,
  /// Not enough bytes for an Table_feature_property_write_actions
  AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_ACTIONS,
  /// Not enough bytes for an Table_feature_property_write_actions_miss
  AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS,
  /// Not enough bytes for an Table_feature_property_apply_actions
  AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_ACTIONS,
  /// Not enough bytes for an Table_feature_property_apply_actions_miss
  AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS,
  /// Not enough bytes for an Table_feature_property_oxm_base
  AVAILABLE_TABLE_FEATURE_PROPERTY_OXM_BASE,
  /// Not enough bytes for an Table_feature_property_match
  AVAILABLE_TABLE_FEATURE_PROPERTY_MATCH,
  /// Not enough bytes for an Table_feature_property_wildcards
  AVAILABLE_TABLE_FEATURE_PROPERTY_WILDCARDS,
  /// Not enough bytes for an Table_feature_property_write_setfield
  AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_SETFIELD,
  /// Not enough bytes for an Table_feature_property_write_setfield_miss
  AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS,
  /// Not enough bytes for an Table_feature_property_apply_setfield
  AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_SETFIELD,
  /// Not enough bytes for an Table_feature_property_apply_setfield_miss
  AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS,
  /// Not enough bytes for an Table_feature_property_experimenter_base
  AVAILABLE_TABLE_FEATURE_PROPERTY_EXPERIMENTER_BASE,
  /// Not enough bytes for an Table_feature_property_experimenter
  AVAILABLE_TABLE_FEATURE_PROPERTY_EXPERIMENTER,
  /// Not enough bytes for an Table_feature_property_experimenter_miss
  AVAILABLE_TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS,
  /// Not enough bytes for an Table_feature_property_header
  AVAILABLE_TABLE_FEATURE_PROPERTY_HEADER,
  /// Not enough bytes for an Table_feature_property_payload
  AVAILABLE_TABLE_FEATURE_PROPERTY_PAYLOAD,
  /// Not enough bytes for an Table_feature_property
  AVAILABLE_TABLE_FEATURE_PROPERTY,
  /// Not enough bytes for an Multipart_req_table_feature
  AVAILABLE_MULTIPART_REQ_TABLE_FEATURE,
  /// Not enough bytes for an Multipart_req_table_feature_padding
  AVAILABLE_MULTIPART_REQ_TABLE_FEATURE_PADDING,
  /// Not enough bytes for an Multipart_req_table_features
  AVAILABLE_MULTIPART_REQ_TABLE_FEATURES,
  /// Not enough bytes for an Multipart_req_port_desc
  AVAILABLE_MULTIPART_REQ_PORT_DESC,
  /// Not enough bytes for an Multipart_req_experimenter
  AVAILABLE_MULTIPART_REQ_EXPERIMENTER,
  AVAILABLE_MULTIPART_HEADER,   ///< Not enough bytes for an Multipart_header
  /// Not enough bytes for an Multipart_req_payload
  AVAILABLE_MULTIPART_REQ_PAYLOAD,
  AVAILABLE_MULTIPART_REQ,      ///< Not enough bytes for an Multipart_req
  AVAILABLE_MULTIPART_RES_DESC, ///< Not enough bytes for an Multipart_res_desc
  AVAILABLE_MULTIPART_RES_FLOW, ///< Not enough bytes for an Multipart_res_flow
  AVAILABLE_MULTIPART_RES_FLOWS,///< Not enough bytes for an multipart_res_flows
  /// Not enough bytes for an Multipart_res_aggregate
  AVAILABLE_MULTIPART_RES_AGGREGATE,
  AVAILABLE_MULTIPART_RES_PORT, ///< Not enough bytes for an Multipart_res_port
  AVAILABLE_MULTIPART_RES_PORTS,///< Not enough bytes for an Multipart_res_ports
  AVAILABLE_MULTIPART_RES_QUEUE,///< Not enough bytes for an Multipart_res_queue
  /// Not enough bytes for an Multipart_res_queues
  AVAILABLE_MULTIPART_RES_QUEUES,
  AVAILABLE_MULTIPART_RES_TABLE,///< Not enough bytes for an Multipart_res_table
  /// Not enough bytes for an Multipart_res_tables
  AVAILABLE_MULTIPART_RES_TABLES,
  AVAILABLE_BUCKET_COUNTER,     ///< Not enough bytes for an Bucket_counter
  AVAILABLE_MULTIPART_RES_GROUP,///< Not enough bytes for an Multipart_res_group
  /// Not enough bytes for an Multipart_res_groups
  AVAILABLE_MULTIPART_RES_GROUPS,
  /// Not enough bytes for an Multipart_res_group_desc
  AVAILABLE_MULTIPART_RES_GROUP_DESC,
  /// Not enough bytes for an Multipart_res_group_descs
  AVAILABLE_MULTIPART_RES_GROUP_DESCS,
  /// Not enough bytes for an Multipart_res_group_features
  AVAILABLE_MULTIPART_RES_GROUP_FEATURES,
  AVAILABLE_METER_BAND_STATS,   ///< Not enough bytes for an Meter_band_stats
  AVAILABLE_MULTIPART_RES_METER,///< Not enough bytes for an Multipart_res_meter
  /// Not enough bytes for an Multipart_res_meters
  AVAILABLE_MULTIPART_RES_METERS,
  AVAILABLE_METER_BAND_DROP,    ///< Not enough bytes for an Meter_band_drop
  /// Not enough bytes for an Meter_band_dscp_remark
  AVAILABLE_METER_BAND_DSCP_REMARK,
  /// Not enough bytes for an Meter_band_experimenter
  AVAILABLE_METER_BAND_EXPERIMENTER,
  AVAILABLE_METER_BAND_HEADER,  ///< Not enough bytes for an Meter_band_header
  AVAILABLE_METER_BAND_PAYLOAD, ///< Not enough bytes for an Meter_band_payload
  AVAILABLE_METER_BAND,         ///< Not enough bytes for an Meter_band
  /// Not enough bytes for an Multipart_res_meter_config
  AVAILABLE_MULTIPART_RES_METER_CONFIG,
  /// Not enough bytes for an Multipart_res_meter_configs
  AVAILABLE_MULTIPART_RES_METER_CONFIGS,
  /// Not enough bytes for an Multipart_res_meter_features
  AVAILABLE_MULTIPART_RES_METER_FEATURES,
  /// Not enough bytes for an Multipart_res_table_feature
  AVAILABLE_MULTIPART_RES_TABLE_FEATURE,
  /// Not enough bytes for an Multipart_res_table_feature_padding
  AVAILABLE_MULTIPART_RES_TABLE_FEATURE_PADDING,
  /// Not enough bytes for an Multipart_res_table_features
  AVAILABLE_MULTIPART_RES_TABLE_FEATURES,
  /// Not enough bytes for an Multipart_res_port_desc
  AVAILABLE_MULTIPART_RES_PORT_DESC,
  /// Not enough bytes for an Multipart_res_experimenter
  AVAILABLE_MULTIPART_RES_EXPERIMENTER,
  /// Not enough bytes for an Multipart_res_payload
  AVAILABLE_MULTIPART_RES_PAYLOAD,
  AVAILABLE_MULTIPART_RES,      ///< Not enough bytes for an Multipart_res

  AVAILABLE_BARRIER_REQ,        ///< Not enough bytes for an Barrier_req
  AVAILABLE_BARRIER_RES,        ///< Not enough bytes for an Barrier_res

  /// Not enough bytes for an Queue_get_config_req
  AVAILABLE_QUEUE_GET_CONFIG_REQ,

  /// Not enough bytes for an Queue_get_config_res
  AVAILABLE_QUEUE_GET_CONFIG_RES,
  AVAILABLE_ROLE_REQ,           ///< Not enough bytes for an Role_req
  AVAILABLE_ROLE_RES,           ///< Not enough bytes for an Role_res
  AVAILABLE_GET_ASYNC_REQ,      ///< Not enough bytes for an Get_async_req
  AVAILABLE_GET_ASYNC_RES,      ///< Not enough bytes for an Get_async_res
  AVAILABLE_SET_ASYNC,          ///< Not enough bytes for an Set_async
  AVAILABLE_METER_MOD,          ///< Not enough bytes for an Meter_mod

  // View update errors
  /// Extra bytes when processing a sequence of type OXM_entry
  EXCESS_OXM,
  /// Extra bytes when processing a sequence of type Match
  EXCESS_MATCH,
  /// Extra bytes when processing a sequence of type Action
  EXCESS_ACTION,
  /// Extra bytes when processing a sequence of type Instruction
  EXCESS_INSTRUCTION,
  /// Extra bytes when processing a sequence of type Queue_property
  EXCESS_QUEUE_PROPERTY,
  /// Extra bytes when processing a sequence of type Queue
  EXCESS_QUEUE,
  /// Extra bytes when processing a sequence of type Packet_out
  EXCESS_PACKET_OUT,
  /// Extra bytes when processing a sequence of type Bucket
  EXCESS_BUCKET,
  /// Extra bytes when processing a sequence of type Table_feature_property
  EXCESS_TABLE_FEATURE_PROPERTY,
  /// Extra bytes when processing a sequence of type Multipart_req_table_feature
  EXCESS_MULTIPART_REQ_TABLE_FEATURE,
  /// Extra bytes when processing a sequence of type Multipart_res_flow
  EXCESS_MULTIPART_RES_FLOW,
  /// Extra bytes when processing a sequence of type Multipart_res_group
  EXCESS_MULTIPART_RES_GROUP,
  /// Extra bytes when processing a sequence of type Multipart_res_group_desc
  EXCESS_MULTIPART_RES_GROUP_DESC,
  /// Extra bytes when processing a sequence of type Multipart_res_meter
  EXCESS_MULTIPART_RES_METER,
  /// Extra bytes when processing a sequence of type Meter_band
  EXCESS_METER_BAND,
  /// Extra bytes when processing a sequence of type Multipart_res_meter_config
  EXCESS_MULTIPART_RES_METER_CONFIG,
  /// Extra bytes when processing a sequence of type Multipart_res_table_feature
  EXCESS_MULTIPART_RES_TABLE_FEATURE,
  /// Extra bytes when processing a sequence of type Payload
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
//    - OXM
//    - Match
//    - Port
//    - Queue
//    - Action
//    - Instruction
//    - Bucket

// -------------------------------------------------------------------------- //
// OXM entry class

/// OpenFlow extensible match classes
/// \relates OXM_entry_header
enum OXM_entry_class : uint16_t
{
  NXM_0            = 0x0000, ///< For compatibility with Nicira Extensible Match
  NXM_1            = 0x0001, ///< For compatibility with Nicira Extensible Match 
  OPEN_FLOW_BASIC  = 0x8000, ///< Basic OXM entry class for OpenFlow
  OXM_EXPERIMENTER = 0xffff  ///< For experimental use
};

/// \relates OXM_entry_header
Error_condition is_valid(const OXM_entry_class& c);

/// \relates OXM_entry_header
std::string to_string(const OXM_entry_class c);

// -------------------------------------------------------------------------- //
// OXM entry field

/// \relates OXM_entry_header
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
  OXM_EF_MPLS_LABEL = 0x44, OXM_EF_MPLS_TC = 0x46, OXM_EF_MPLS_BOS = 0x48,
  OXM_EF_PBB_ISID = 0x4a, OXM_EF_PBB_ISID_MASK = 0x4b,
  OXM_EF_TUNNEL_ID = 0x4c, OXM_EF_TUNNEL_ID_MASK = 0x4d,
  OXM_EF_IPV6_EXTHDR = 0x4e, OXM_EF_IPV6_EXTHDR_MASK = 0x4f
};

/// Returns true when f is a valid OXM entry field value.
/// \relates OXM_entry_header
Error_condition is_valid(const OXM_entry_field f);

/// \relates OXM_entry_header
std::string to_string(const OXM_entry_field f);

template<OXM_entry_field K>
  using OXM_entry_payload_base = Basic_payload_base<OXM_entry_field, K>;

// -------------------------------------------------------------------------- //
// OXM entry payload: 8 bits

/// Base class for 8-bit OXM entries. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base8 : OXM_entry_payload_base<K>
  {
    OXM_entry_base8() = default;
    explicit OXM_entry_base8(uint8_t v) : value(v) { }

    uint8_t value;
  };

/// \relates OXM_entry_base8
template<OXM_entry_field K>
  bool operator==(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b);

/// \relates OXM_entry_base8
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b);

/// \relates OXM_entry_base8
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base8<K>&);

/// \relates OXM_entry_base8
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base8<K>& b);

/// \relates OXM_entry_base8
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base8<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : VLAN PCP

/// Match 3-bit priority field for VLAN. (see OXM_entry_payload)
struct OXM_entry_vlan_pcp : OXM_entry_base8<OXM_EF_VLAN_PCP> { };

/// \relates OXM_entry_vlan_pcp
std::string to_string(const OXM_entry_vlan_pcp&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IP DSCP

/// Match 6-bit differentiated services code point field for IP. (see
/// OXM_entry_payload)
struct OXM_entry_ip_dscp : OXM_entry_base8<OXM_EF_IP_DSCP> { };

/// \relates OXM_entry_ip_dscp
std::string to_string(const OXM_entry_ip_dscp&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IP ECN

/// Match 2-bit explicit congestion notification field for IP. (see OXM_entry_payload)
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

/// Match type field for Internet Control Message Protocol (ICMP) for IPv4. (see OXM_entry_payload)
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

/// Match 3-bit traffic class (TC) field for Multiprotocol Label Switching (MPLS).
/// (see OXM_entry_payload)
struct OXM_entry_mpls_tc : OXM_entry_base8<OXM_EF_MPLS_TC> { };

/// \relates OXM_entry_mpls_tc
std::string to_string(const OXM_entry_mpls_tc&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : MPLS BoS

/// Match 1-bit bottom of stack bit for MPLS. (see OXM_entry_payload)
struct OXM_entry_mpls_bos : OXM_entry_base8<OXM_EF_MPLS_BOS> { };

/// \relates OXM_entry_mpls_bos
std::string to_string(const OXM_entry_mpls_bos&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload: 16 bits

/// Base class for 16-bit OXM entries. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base16 : OXM_entry_payload_base<K>
  {
    OXM_entry_base16() = default;
    explicit OXM_entry_base16(uint16_t v) : value(v) { }

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
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base16<K>& b);

/// \relates OXM_entry_base16
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base16<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : VLAN VID

/// Match 12+1 bit VID field (VLAN identification) for VLAN. (see OXM_entry_payload)
struct OXM_entry_vlan_vid : OXM_entry_base16<OXM_EF_VLAN_VID> { };

/// \relates OXM_entry_vlan_vid
std::string to_string(const OXM_entry_vlan_vid&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : Eth type

/// Match type field for Ethernet. (see OXM_entry_payload)
struct OXM_entry_eth_type : OXM_entry_base16<OXM_EF_ETH_TYPE> { };

/// \relates OXM_entry_eth_type
std::string to_string(const OXM_entry_eth_type&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : TCP src

/// Match source port for Transmission Control Protocol (TCP). (see
/// OXM_entry_payload)
struct OXM_entry_tcp_src : OXM_entry_base16<OXM_EF_TCP_SRC> { };

/// \relates OXM_entry_tcp_src
std::string to_string(const OXM_entry_tcp_src&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : TCP dst

/// Match destination port for TCP. (see OXM_entry_payload)
struct OXM_entry_tcp_dst : OXM_entry_base16<OXM_EF_TCP_DST> { };

/// \relates OXM_entry_tcp_dst
std::string to_string(const OXM_entry_tcp_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : UDP src

/// Match source port for User Datagram Protocol (UDP). (see
/// OXM_entry_payload)
struct OXM_entry_udp_src : OXM_entry_base16<OXM_EF_UDP_SRC> { };

/// \relates OXM_entry_udp_src
std::string to_string(const OXM_entry_udp_src&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : UDP dst

/// Match destination port for UDP. (see OXM_entry_payload)
struct OXM_entry_udp_dst : OXM_entry_base16<OXM_EF_UDP_DST> { };

/// \relates OXM_entry_udp_dst
std::string to_string(const OXM_entry_udp_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : SCTP src

/// Match source port for Stream Control Transmission Protocol (SCTP). (see
/// OXM_entry_payload)
struct OXM_entry_sctp_src : OXM_entry_base16<OXM_EF_SCTP_SRC> { };

/// \relates OXM_entry_sctp_src
std::string to_string(const OXM_entry_sctp_src&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : SCTP dst

/// Match destination port for SCTP. (see OXM_entry_payload)
struct OXM_entry_sctp_dst : OXM_entry_base16<OXM_EF_SCTP_DST> { };

/// \relates OXM_entry_sctp_dst
std::string to_string(const OXM_entry_sctp_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : ARP op

/// Match operation field for Address Resolution Protocol (ARP). (see
/// OXM_entry_payload)
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
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base16_mask<K>& b);

/// \relates OXM_entry_base16_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base16_mask<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : VLAN VID mask

/// Match 12+1 bit VID field (VLAN identification) for VLAN with a bit mask.
/// (see OXM_entry_payload)
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
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base32<K>& b);

/// \relates OXM_entry_base32
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base32<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : in port

/// Match ingress port of switch numbered started at 1. (see OXM_entry_payload)
struct OXM_entry_in_port : OXM_entry_base32<OXM_EF_IN_PORT> { };

/// \relates OXM_entry_in_port
std::string to_string(const OXM_entry_in_port&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : in phy port

/// Match physical port. (see OXM_entry_payload)
struct OXM_entry_in_phy_port : OXM_entry_base32<OXM_EF_IN_PHY_PORT> { };

/// \relates OXM_entry_in_phy_port
std::string to_string(const OXM_entry_in_phy_port&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : mpls label

/// Match label field for MPLS. (see OXM_entry_payload)
struct OXM_entry_mpls_label : OXM_entry_base32<OXM_EF_MPLS_LABEL> { };

/// \relates OXM_entry_mpls_label
std::string to_string(const OXM_entry_mpls_label&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 flabel

/// Match 20-bit flow label field for IPv6. (see OXM_entry_payload)
struct OXM_entry_ipv6_flabel : OXM_entry_base32<OXM_EF_IPV6_FLABEL> { };

/// \relates OXM_entry_ipv6_flabel
std::string to_string(const OXM_entry_ipv6_flabel&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : PBB I-SID

/// Match 24-bit I-SID for Provider Backbone Bridges (PBB)
struct OXM_entry_pbb_isid
{
  OXM_entry_pbb_isid() = default;
  explicit OXM_entry_pbb_isid(uint32_t v) : value(v) { }

  uint32_t value;
};

/// \relates OXM_entry_pbb_isid
bool operator==(const OXM_entry_pbb_isid& a, const OXM_entry_pbb_isid& b);

/// \relates OXM_entry_pbb_isid
bool operator!=(const OXM_entry_pbb_isid& a, const OXM_entry_pbb_isid& b);

/// \relates OXM_entry_pbb_isid
constexpr std::size_t bytes(const OXM_entry_pbb_isid&);

/// \relates OXM_entry_pbb_isid
constexpr Error_condition is_valid(const OXM_entry_pbb_isid&);

/// \relates OXM_entry_pbb_isid
Error_condition to_buffer(Buffer_view&, const OXM_entry_pbb_isid&);

/// \relates OXM_entry_pbb_isid
Error_condition from_buffer(Buffer_view&, OXM_entry_pbb_isid&);

/// \relates OXM_entry_pbb_isid
std::string to_string(const OXM_entry_pbb_isid&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 32 bits

/// Base class for 32-bit OXM entries with a bit mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base32_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_base32_mask() = default;
    OXM_entry_base32_mask(uint32_t v, uint32_t m) : value(v), mask(m) { }

    uint32_t value;
    uint32_t mask;
  };

/// \relates OXM_entry_base32_mask
template<OXM_entry_field K>
  bool operator==(const OXM_entry_base32_mask<K>& a,
                  const OXM_entry_base32_mask<K>& b);

/// \relates OXM_entry_base32_mask
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base32_mask<K>& a,
                  const OXM_entry_base32_mask<K>& b);

/// \relates OXM_entry_base32_mask
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base32_mask<K>&);

/// \relates OXM_entry_base32_mask
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base32_mask<K>& b);

/// \relates OXM_entry_base32_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base32_mask<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 flabel mask

/// Match 20-bit flow label field for IPv6 with bit mask. (see
/// OXM_entry_payload)
struct OXM_entry_ipv6_flabel_mask
  : OXM_entry_base32_mask<OXM_EF_IPV6_FLABEL_MASK> { };
std::string to_string(const OXM_entry_ipv6_flabel_mask&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : PBB I-SID mask

/// Match 24-bit I-SID for PBB with bit mask.
struct OXM_entry_pbb_isid_mask
{
  OXM_entry_pbb_isid_mask() = default;
  explicit OXM_entry_pbb_isid_mask(uint32_t v,uint32_t m) : value(v), mask(m) {}

  uint32_t value;
  uint32_t mask;
};

/// \relates OXM_entry_pbb_isid_mask
bool
operator==(const OXM_entry_pbb_isid_mask& a, const OXM_entry_pbb_isid_mask& b);

/// \relates OXM_entry_pbb_isid_mask
bool
operator!=(const OXM_entry_pbb_isid_mask& a, const OXM_entry_pbb_isid_mask& b);

/// \relates OXM_entry_pbb_isid_mask
constexpr std::size_t bytes(const OXM_entry_pbb_isid_mask&);

/// \relates OXM_entry_pbb_isid_mask
constexpr Error_condition is_valid(const OXM_entry_pbb_isid_mask&);

/// \relates OXM_entry_pbb_isid_mask
Error_condition to_buffer(Buffer_view&, const OXM_entry_pbb_isid_mask&);

/// \relates OXM_entry_pbb_isid_mask
Error_condition from_buffer(Buffer_view&, OXM_entry_pbb_isid_mask&);

/// \relates OXM_entry_pbb_isid_mask
std::string to_string(const OXM_entry_pbb_isid_mask&, Formatter&);

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
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ipv4<K>& b);

/// \relates OXM_entry_ipv4
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ipv4<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv4 src

/// Match source address for IPv4. (see OXM_entry_payload)
struct OXM_entry_ipv4_src : OXM_entry_ipv4<OXM_EF_IPV4_SRC> { };

/// \relates OXM_entry_ipv4_src
std::string to_string(const OXM_entry_ipv4_src&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv4 dst

/// Match destination address for IPv4. (see OXM_entry_payload)
struct OXM_entry_ipv4_dst : OXM_entry_ipv4<OXM_EF_IPV4_DST> { };

/// \relates OXM_entry_ipv4_dst
std::string to_string(const OXM_entry_ipv4_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : ARP SPA

/// Match source IPv4 address for ARP. (see OXM_entry_payload)
struct OXM_entry_arp_spa : OXM_entry_ipv4<OXM_EF_ARP_SPA> { };

/// \relates OXM_entry_arp_spa
std::string to_string(const OXM_entry_arp_spa&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : ARP TPA

/// Match destination IPv4 address for ARP. (see OXM_entry_payload)
struct OXM_entry_arp_tpa : OXM_entry_ipv4<OXM_EF_ARP_TPA> { };

/// \relates OXM_entry_arp_tpa
std::string to_string(const OXM_entry_arp_tpa&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: IP

/// Base class for OXM entries with an Internet Protocol version 4 (IPv4)
/// address with a bit mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ipv4_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_ipv4_mask() = default;
    OXM_entry_ipv4_mask(uint32_t v, uint32_t m) : value(v), mask(m) { }

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
    explicit OXM_entry_ethernet(Ethernet_addr v) : value(v) { }

    Ethernet_addr value;
  };

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  bool
  operator==(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b);

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  bool
  operator!=(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b);

/// \relates OXM_entry_ethernet
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_ethernet<K>&);

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
    OXM_entry_ethernet_mask(Ethernet_addr v, Ethernet_addr m)
      : value(v), mask(m) { }

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
  Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ethernet_mask<K>& b);

/// \relates OXM_entry_ethernet_mask
template<OXM_entry_field K>
  Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ethernet_mask<K>& b);

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
// OXM entry payload: 64 bits

/// Base class for 64-bit OXM entries. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base64 : OXM_entry_payload_base<K>
  {
    OXM_entry_base64() = default;
    explicit OXM_entry_base64(uint64_t v) : value(v) { }

    uint64_t value;
  };

/// \relates OXM_entry_base64
template<OXM_entry_field K>
  bool operator==(const OXM_entry_base64<K>& a, const OXM_entry_base64<K>& b);

/// \relates OXM_entry_base64
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base64<K>& a, const OXM_entry_base64<K>& b);

/// \relates OXM_entry_base64
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base64<K>&);

/// \relates OXM_entry_base64
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base64<K>& b);

/// \relates OXM_entry_base64
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base64<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : Metadata

struct OXM_entry_metadata : OXM_entry_base64<OXM_EF_METADATA> { };

/// \relates OXM_entry_metadata
std::string to_string(const OXM_entry_metadata&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : Tunnel ID

struct OXM_entry_tunnel_id : OXM_entry_base64<OXM_EF_TUNNEL_ID> { };

/// \relates OXM_entry_tunnel_id
std::string to_string(const OXM_entry_tunnel_id&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 64 bits

/// Base class for 64-bit OXM entries with a bit mask. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_base64_mask : OXM_entry_payload_base<K>
  {
    OXM_entry_base64_mask() = default;
    explicit OXM_entry_base64_mask(uint64_t v, uint64_t m)
      : value(v), mask(m) { }

    uint64_t value;
    uint64_t mask;
  };

/// \relates OXM_entry_base64_mask
template<OXM_entry_field K>
  bool operator==(const OXM_entry_base64_mask<K>& a,
                  const OXM_entry_base64_mask<K>& b);

/// \relates OXM_entry_base64_mask
template<OXM_entry_field K>
  bool operator!=(const OXM_entry_base64_mask<K>& a,
                  const OXM_entry_base64_mask<K>& b);

/// \relates OXM_entry_base64_mask
template<OXM_entry_field K>
  std::size_t bytes(const OXM_entry_base64_mask<K>&);

/// \relates OXM_entry_base64_mask
template<OXM_entry_field K>
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_base64_mask<K>& b);

/// \relates OXM_entry_base64_mask
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_base64_mask<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : Metadata mask

struct OXM_entry_metadata_mask
  : OXM_entry_base64_mask<OXM_EF_METADATA_MASK> { };

/// \relates OXM_entry_metadata_mask
std::string to_string(const OXM_entry_metadata_mask&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : Tunnel ID mask

struct OXM_entry_tunnel_id_mask
  : OXM_entry_base64_mask<OXM_EF_TUNNEL_ID_MASK> { };

/// \relates OXM_entry_tunnel_id_mask
std::string to_string(const OXM_entry_tunnel_id_mask&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload: IPv6

/// Base class for OXM entries with an Internet Protocol version 6 (IPv6)
/// address. (see OXM_entry_payload)
template<OXM_entry_field K>
  struct OXM_entry_ipv6 : OXM_entry_payload_base<K>
  {
    OXM_entry_ipv6() = default;
    explicit OXM_entry_ipv6(Ipv6_addr v) : value(v) { }

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
  Error_condition to_buffer(Buffer_view& v, const OXM_entry_ipv6<K>& b);

/// \relates OXM_entry_ipv6
template<OXM_entry_field K>
  Error_condition from_buffer(Buffer_view& v, OXM_entry_ipv6<K>& b);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 src

struct OXM_entry_ipv6_src : OXM_entry_ipv6<OXM_EF_IPV6_SRC> { };

/// \relates OXM_entry_ipv6_src
std::string to_string(const OXM_entry_ipv6_src&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 dst

struct OXM_entry_ipv6_dst : OXM_entry_ipv6<OXM_EF_IPV6_DST> { };

/// \relates OXM_entry_ipv6_dst
std::string to_string(const OXM_entry_ipv6_dst&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 ND Target

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
    OXM_entry_ipv6_mask(Ipv6_addr v, Ipv6_addr m) : value(v), mask(m) { }

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

struct OXM_entry_ipv6_src_mask
  : OXM_entry_ipv6_mask<OXM_EF_IPV6_SRC_MASK> { };

/// \relates OXM_entry_ipv6_src_mask
std::string to_string(const OXM_entry_ipv6_src_mask&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : IPv6 dst

struct OXM_entry_ipv6_dst_mask
  : OXM_entry_ipv6_mask<OXM_EF_IPV6_DST_MASK> { };

/// \relates OXM_entry_ipv6_dst_mask
std::string to_string(const OXM_entry_ipv6_dst_mask&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : Ipv6 ext header flags

enum Ipv6_exthdr_flags : uint16_t
{
  NONEXT = 0x0001, ESP = 0x0002, AUTH = 0x0004, DEST = 0x0008,
  FRAG = 0x0010, ROUTER = 0x0020, HOP = 0x0040, UNREP = 0x0080,
  UNSEQ = 0x0100
};

std::string to_string(Ipv6_exthdr_flags);

// -------------------------------------------------------------------------- //
// OXM entry payload : Ipv6 ext header

struct OXM_entry_ipv6_exthdr : OXM_entry_payload_base<OXM_EF_IPV6_EXTHDR>
{
  OXM_entry_ipv6_exthdr() = default;
  explicit OXM_entry_ipv6_exthdr(Ipv6_exthdr_flags f) : flag(f) { }

  Ipv6_exthdr_flags flag;
};

/// \relates OXM_entry_ipv6_exthdr
bool
operator==(const OXM_entry_ipv6_exthdr& a, const OXM_entry_ipv6_exthdr& b);

/// \relates OXM_entry_ipv6_exthdr
bool
operator!=(const OXM_entry_ipv6_exthdr& a, const OXM_entry_ipv6_exthdr& b);

/// \relates OXM_entry_ipv6_exthdr
constexpr std::size_t bytes(const OXM_entry_ipv6_exthdr&);

/// \relates OXM_entry_ipv6_exthdr
Error_condition to_buffer(Buffer_view&, const OXM_entry_ipv6_exthdr&);

/// \relates OXM_entry_ipv6_exthdr
Error_condition from_buffer(Buffer_view&, OXM_entry_ipv6_exthdr&);

/// \relates OXM_entry_ipv6_exthdr
std::string to_string(const OXM_entry_ipv6_exthdr&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload : Ipv6 ext header mask

struct OXM_entry_ipv6_exthdr_mask
  : OXM_entry_payload_base<OXM_EF_IPV6_EXTHDR_MASK>
{
  OXM_entry_ipv6_exthdr_mask() = default;
  OXM_entry_ipv6_exthdr_mask(Ipv6_exthdr_flags f, uint16_t m)
    : flag(f), mask(m) { }

  Ipv6_exthdr_flags flag;
  uint16_t mask;
};

/// \relates OXM_entry_ipv6_exthdr_mask
bool operator==(const OXM_entry_ipv6_exthdr_mask& a,
                const OXM_entry_ipv6_exthdr_mask& b);

/// \relates OXM_entry_ipv6_exthdr_mask
bool operator!=(const OXM_entry_ipv6_exthdr_mask& a,
                const OXM_entry_ipv6_exthdr_mask& b);

/// \relates OXM_entry_ipv6_exthdr_mask
constexpr std::size_t bytes(const OXM_entry_ipv6_exthdr_mask&);

/// \relates OXM_entry_ipv6_exthdr_mask
Error_condition to_buffer(Buffer_view&, const OXM_entry_ipv6_exthdr_mask&);

/// \relates OXM_entry_ipv6_exthdr_mask
Error_condition from_buffer(Buffer_view&, OXM_entry_ipv6_exthdr_mask&);

/// \relates OXM_entry_ipv6_exthdr_mask
std::string to_string(const OXM_entry_ipv6_exthdr_mask&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry payload

/// \relates OXM_entry_payload
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
  OXM_entry_mpls_bos         mpls_bos;
  OXM_entry_pbb_isid         pbb_isid;
  OXM_entry_pbb_isid_mask    pbb_isid_mask;
  OXM_entry_tunnel_id        tunnel_id;
  OXM_entry_tunnel_id_mask   tunnel_id_mask;
  OXM_entry_ipv6_exthdr      ipv6_exthdr;
  OXM_entry_ipv6_exthdr_mask ipv6_exthdr_mask;
};

/// Object used to handle the initialization of the payload of a OXM_entry
/// object
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
void construct(OXM_entry_payload&, OXM_entry_payload&&, OXM_entry_field);

/// \relates OXM_entry_payload
void construct(OXM_entry_payload&, const OXM_entry_payload&,
               OXM_entry_field);

/// \relates OXM_entry_payload
OXM_entry_payload& assign(OXM_entry_payload&, OXM_entry_payload&&,
                          OXM_entry_field);

/// \relates OXM_entry_payload
OXM_entry_payload& assign(OXM_entry_payload&, const OXM_entry_payload&,
                          OXM_entry_field);

/// \relates OXM_entry_payload
void destroy(OXM_entry_payload&, OXM_entry_field);

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
Error_condition from_buffer(Buffer_view&, OXM_entry_payload&, OXM_entry_field);

/// \relates OXM_entry_payload
std::string to_string(const OXM_entry_payload&, Formatter&, OXM_entry_field);

// -------------------------------------------------------------------------- //
// OXM Experimenter

struct OXM_experimenter
{
  OXM_experimenter() = default;
  explicit OXM_experimenter(uint32_t e) : experimenter(e) { }

  uint32_t experimenter;
};

/// \relates OXM_experimenter
bool operator==(const OXM_experimenter& a, const OXM_experimenter& b);

/// \relates OXM_experimenter
bool operator!=(const OXM_experimenter& a, const OXM_experimenter& b);

/// \relates OXM_experimenter
constexpr std::size_t bytes(const OXM_experimenter&);

/// \relates OXM_experimenter
Error_condition to_buffer(Buffer_view&, const OXM_experimenter&);

/// \relates OXM_experimenter
Error_condition from_buffer(Buffer_view&, OXM_experimenter&);

/// \relates OXM_experimenter
std::string to_string(const OXM_experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// OXM entry: Header

struct OXM_entry_header
{
  OXM_entry_header() = default;
  OXM_entry_header(OXM_entry_class c, OXM_entry_field f, uint8_t l)
    : oxm_class(c), field(f), length(l) { }

  template<typename T>
    OXM_entry_header(const T& value) : field(T::kind), length(bytes(value)) { }

  OXM_entry_class oxm_class;
  OXM_entry_field field;
  uint8_t length;
};

/// \relates OXM_entry_header
bool operator==(const OXM_entry_header& a, const OXM_entry_header& b);

/// \relates OXM_entry_header
bool operator!=(const OXM_entry_header& a, const OXM_entry_header& b);

/// \relates OXM_entry_header
Error_condition is_valid(const OXM_entry_header& e);

/// \relates OXM_entry_header
std::size_t bytes(const OXM_entry_header& h);

/// \relates OXM_entry_header
Error_condition to_buffer(Buffer_view&, const OXM_entry_header&);

/// \relates OXM_entry_header
Error_condition from_buffer(Buffer_view&, OXM_entry_header&);

/// \relates OXM_entry_header
std::string to_string(const OXM_entry_header&,  Formatter&);

// -------------------------------------------------------------------------- //
// OXM

/// The OpenFlow Extensible Match (OXM) is a structure that matches a particular
/// protocol field. A complicated match rule is then defined a sequence of OXMs,
/// which all must match. OXM's are segregated by class, and then field. For
/// this specification there is only one class to worry about, OpenFlowBasic.
/// Fields are then defined to handle very specific protocol matching. The
/// length field of an OXM is exclusive, it specifies only the number of bytes
/// in the OXM payload. The OXM header has a single bit that indicates whether
/// a bitmask is present in the payload.
///
/// \remark Defined in [OpenFlow v1.3, p39-47](http://...)
struct OXM_entry
{
  using Header = OXM_entry_header;
  using Payload = OXM_entry_payload;

  OXM_entry() = default;
  ~OXM_entry();

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

/// Represents a matching entry in a flow table. The Match class is used by
/// several messages in the protocol to refer to a single entry in in a flow 
/// table. The class specifies which fields of a packet will be matched by
/// the switch, any of which can be specified as a wildcard value.
///
/// \remark Defined in [OpenFlow v1.3, p38-39](http://...)
struct Match
{
  enum Type : uint16_t {
    MT_STANDARD = 0x0000, ///< This is deprecated as of v1.2
    MT_OXM = 0x0001
  };

  Match() = default;
  Match(Type t, uint16_t l, const Sequence<OXM_entry> r)
    : type(t), length(l), rules(r) { }

  Type type;
  uint16_t length;
  Sequence<OXM_entry> rules;
};

/// Returns true when the arguments compare equal. Two match values 
/// compare equal when they match the same packets (i.e., all fields compare 
/// equal).
bool operator==(const Match& a, const Match& b);

/// Returns true when the arguments do not compare equal.
bool operator!=(const Match& a, const Match& b);

/// Returns the number of bytes needed to represent a Match value.
std::size_t bytes(const Match& m);

Error_condition is_valid(const Match::Type);

/// Validates the value of a Match object.
Error_condition is_valid(const Match&);

/// Writes a Match value into a Buffer_view. If the write does not succeed, 
/// the result will containt a code representing the specific cause of failure.
Error_condition to_buffer(Buffer_view&, const Match& m);

/// Reads a Match value from a Buffer_view. If the read does not succeed, the 
/// result will containt a code representing the specific cause of failure.
Error_condition from_buffer(Buffer_view&, Match& m);

/// Returns a formatted string representation of a Match value.
std::string to_string(const Match&, Formatter&);

// -------------------------------------------------------------------------- //
// Action type

/// \relates Action_header
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
  ACTION_PUSH_PBB     = 0x001a,
  ACTION_POP_PBB      = 0x001b,
  ACTION_EXPERIMENTER = 0xffff
};

/// \relates Action_header
Error_condition is_valid(const Action_type at);

/// \relates Action_header
std::string to_string(Action_type);

// A base class for all action payload kinds.
template<Action_type K>
  using Action_payload_base = Basic_payload_base<Action_type, K>;

// -------------------------------------------------------------------------- //
// Action: Output

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
// Action: Copy ttl out

struct Action_copy_ttl_out : Action_payload_base<ACTION_COPY_TTL_OUT> { };

/// \relates Action_copy_ttl_out
constexpr std::size_t bytes(const Action_copy_ttl_out&);

/// \relates Action_copy_ttl_out
constexpr Error_condition is_valid(const Action_copy_ttl_out&);

/// \relates Action_copy_ttl_out
Error_condition to_buffer(Buffer_view&, const Action_copy_ttl_out&);

/// \relates Action_copy_ttl_out
Error_condition from_buffer(Buffer_view&, Action_copy_ttl_out&);

// -------------------------------------------------------------------------- //
// Action: Copy ttl in

struct Action_copy_ttl_in : Action_payload_base<ACTION_COPY_TTL_IN> { };

/// \relates Action_copy_ttl_in
constexpr std::size_t bytes(const Action_copy_ttl_in&);

/// \relates Action_copy_ttl_in
constexpr Error_condition is_valid(const Action_copy_ttl_in&);

/// \relates Action_copy_ttl_in
Error_condition to_buffer(Buffer_view&, const Action_copy_ttl_in&);

/// \relates Action_copy_ttl_in
Error_condition from_buffer(Buffer_view&, Action_copy_ttl_in&);

// -------------------------------------------------------------------------- //
// Action: MPLS TTL

template <Action_type K>
  struct Action_mpls_ttl : Action_payload_base<ACTION_SET_MPLS_TTL>
  {
    Action_mpls_ttl() = default;
    explicit Action_mpls_ttl(uint8_t mt) : mpls_ttl(mt) { }

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
  constexpr std::size_t bytes(const Action_mpls_ttl<K>&);

/// \relates Action_mpls_ttl
template<Action_type K>
  constexpr Error_condition is_valid(const Action_mpls_ttl<K>&);

/// \relates Action_mpls_ttl
template <Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_mpls_ttl<K>& mt);

/// \relates Action_mpls_ttl
template <Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_mpls_ttl<K>& mt);

// -------------------------------------------------------------------------- //
// Action: Set Mpls ttl

struct Action_set_mpls_ttl : Action_mpls_ttl<ACTION_SET_MPLS_TTL>
{
  using Action_mpls_ttl<ACTION_SET_MPLS_TTL>::Action_mpls_ttl;
};


/// \relates Action_set_mpls_ttl
std::string to_string(const Action_set_mpls_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Dec Mpls ttl

struct Action_dec_mpls_ttl : Action_mpls_ttl<ACTION_DEC_MPLS_TTL>
{
  using Action_mpls_ttl<ACTION_DEC_MPLS_TTL>::Action_mpls_ttl;
};


/// \relates Action_dec_mpls_ttl
std::string to_string(const Action_dec_mpls_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push Pop

template <Action_type K>
  struct Action_push_pop : Action_payload_base<K>
  {
    Action_push_pop() = default;
    explicit Action_push_pop(uint16_t et) : ether_type(et) { }

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
  constexpr std::size_t bytes(const Action_push_pop<K>&);

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

struct Action_push_vlan : Action_push_pop<ACTION_PUSH_VLAN>
{
  using Action_push_pop<ACTION_PUSH_VLAN>::Action_push_pop;
};

/// \relates Action_push_vlan
std::string to_string(const Action_push_vlan&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push Vlan

struct Action_pop_vlan : Action_push_pop<ACTION_POP_VLAN>
{
  using Action_push_pop<ACTION_POP_VLAN>::Action_push_pop;
};

/// \relates Action_pop_vlan
std::string to_string(const Action_pop_vlan&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push Mpls

struct Action_push_mpls : Action_push_pop<ACTION_PUSH_MPLS>
{
  using Action_push_pop<ACTION_PUSH_MPLS>::Action_push_pop;
};

/// \relates Action_push_mpls
std::string to_string(const Action_push_mpls&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Pop Mpls

struct Action_pop_mpls : Action_push_pop<ACTION_POP_MPLS>
{
  using Action_push_pop<ACTION_POP_MPLS>::Action_push_pop;
};

/// \relates Action_pop_mpls
std::string to_string(const Action_pop_mpls&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Push pbb

struct Action_push_pbb : Action_push_pop<ACTION_PUSH_PBB>
{
  using Action_push_pop<ACTION_PUSH_PBB>::Action_push_pop;
};

/// \relates Action_push_pbb
std::string to_string(const Action_push_pbb&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: SetQueue

struct Action_set_queue : Action_payload_base<ACTION_SET_QUEUE>
{
  Action_set_queue() = default;
  explicit Action_set_queue(uint32_t qid) : queue_id(qid) { }

  uint32_t queue_id;
};

/// \relates Action_set_queue
bool operator==(const Action_set_queue& a, const Action_set_queue& b);

/// \relates Action_set_queue
bool operator!=(const Action_set_queue& a, const Action_set_queue& b);

/// \relates Action_set_queue
constexpr std::size_t bytes(const Action_set_queue&);

/// \relates Action_set_queue
constexpr Error_condition is_valid(const Action_set_queue&);

/// \relates Action_set_queue
Error_condition to_buffer(Buffer_view&, const Action_set_queue&);

/// \relates Action_set_queue
Error_condition from_buffer(Buffer_view&, Action_set_queue&);

/// \relates Action_set_queue
std::string to_string(const Action_set_queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Group

struct Action_group : Action_payload_base<ACTION_GROUP>
{
  Action_group() = default;
  explicit Action_group(uint32_t gid) : group_id(gid) { }

  uint32_t group_id;
};

/// \relates Action_group
bool operator==(const Action_group& a, const Action_group& b);

/// \relates Action_group
bool operator!=(const Action_group& a, const Action_group& b);

/// \relates Action_group
constexpr std::size_t bytes(const Action_group&);

/// \relates Action_group
constexpr Error_condition is_valid(const Action_group&);

/// \relates Action_group
Error_condition to_buffer(Buffer_view&, const Action_group&);

/// \relates Action_group
Error_condition from_buffer(Buffer_view&, Action_group&);

/// \relates Action_group
std::string to_string(const Action_group&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: NW TTL

template <Action_type K>
  struct Action_nw_ttl : Action_payload_base<ACTION_SET_NW_TTL>
  {
    Action_nw_ttl() = default;
    explicit Action_nw_ttl(uint8_t nt) : nw_ttl(nt) { }

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
  constexpr std::size_t bytes(const Action_nw_ttl<K>& nt);

/// \relates Action_nw_ttl
template<Action_type K>
  constexpr Error_condition is_valid(const Action_nw_ttl<K>&);

/// \relates Action_nw_ttl
template <Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_nw_ttl<K>& nt);

/// \relates Action_nw_ttl
template <Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_nw_ttl<K>& nt);

// -------------------------------------------------------------------------- //
// Action: Set Nw ttl

struct Action_set_nw_ttl : Action_nw_ttl<ACTION_SET_NW_TTL>
{
  using Action_nw_ttl<ACTION_SET_NW_TTL>::Action_nw_ttl;
};

/// \relates Action_set_nw_ttl
std::string to_string(const Action_set_nw_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Dec Nw ttl

struct Action_dec_nw_ttl : Action_nw_ttl<ACTION_DEC_NW_TTL>
{
  using Action_nw_ttl<ACTION_DEC_NW_TTL>::Action_nw_ttl;
};

/// \relates Action_dec_nw_ttl
std::string to_string(const Action_dec_nw_ttl&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Set Field

struct Action_set_field : Action_payload_base<ACTION_SET_FIELD>
{
  Action_set_field() = default;
  explicit Action_set_field(OXM_entry oe) : oxm(oe) { }

  OXM_entry oxm;
};

/// \relates Action_set_field
bool operator==(const Action_set_field& a, const Action_set_field& b);

/// \relates Action_set_field
bool operator!=(const Action_set_field& a, const Action_set_field& b);

/// \relates Action_set_field
std::size_t bytes(const Action_set_field& asf);

/// \relates Action_set_field
constexpr Error_condition is_valid(const Action_set_field&);

/// \relates Action_set_field
Error_condition to_buffer(Buffer_view&, const Action_set_field&);

/// \relates Action_set_field
Error_condition from_buffer(Buffer_view&, Action_set_field&);

/// \relates Action_set_field
std::string to_string(const Action_set_field&, Formatter&);

// -------------------------------------------------------------------------- //
// Action: Pop pbb

struct Action_pop_pbb : Action_payload_base<ACTION_POP_PBB> { };

/// \relates Action_pop_pbb
constexpr std::size_t bytes(const Action_pop_pbb&);

/// \relates Action_pop_pbb
constexpr Error_condition is_valid(const Action_pop_pbb&);

/// \relates Action_pop_pbb
Error_condition to_buffer(Buffer_view&, const Action_pop_pbb&);

/// \relates Action_pop_pbb
Error_condition from_buffer(Buffer_view&, Action_pop_pbb&);

// -------------------------------------------------------------------------- //
// Action: Experimenter

struct Action_experimenter : Action_payload_base<ACTION_EXPERIMENTER> { };

// -------------------------------------------------------------------------- //
// Action Payload

/// \relates Action_payload
union Action_payload_data
{
  Action_payload_data() { }
  ~Action_payload_data() { }

  Action_output         output;
  Action_copy_ttl_out   copy_ttl_out;
  Action_copy_ttl_in    copy_ttl_in;
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
  Action_set_field      set_field;
  Action_experimenter   experimenter;
  Action_push_pbb       push_pbb;
  Action_pop_pbb        pop_pbb;
};

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
Action_payload& assign(Action_payload&, const Action_payload&,
                       Action_type);

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
// Action Header

struct Action_header
{
  Action_header() = default;
  Action_header(Action_type t, uint16_t l) : type(t), length(l) { }
  Action_header(Action_type t, uint16_t l, uint32_t e)
    : type(t), length(l), experimenter(e) { }

  template<typename T>
    Action_header(const T& value);

  Action_type type;
  uint16_t length;
  uint32_t experimenter;
};

/// \relates Action_header
bool operator==(const Action_header& a, const Action_header& b);

/// \relates Action_header
bool operator!=(const Action_header& a, const Action_header& b);

/// \relates Action_header
std::size_t bytes(const Action_header& h);

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

/// Encapsulates a policy decision on what should be applied to a packet.
/// 
/// An action is a policy decision on what should be applied to a packet.
/// OpenFlow uses actions either in the inbound or outbound direction in matches
/// or in instructions; both of which are used in flow modifications.
/// 
/// \remark Defined in [OpenFlow v1.3, p48-51](http://...)
struct Action
{
  using Header = Action_header;
  using Payload = Action_payload;

  Action() = default;

  Action(const Action& x) : header(x.header) {
    construct(payload, x.payload, header.type);
  };
  
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

/// \relates Action
std::string to_string(const Action& a, Formatter& f);

// -------------------------------------------------------------------------- //
// Instruction type

/// \relates Instruction_header
enum Instruction_type : uint16_t
{
  INSTRUCTION_GOTO_TABLE     = 0x0001,
  INSTRUCTION_WRITE_METADATA = 0x0002,
  INSTRUCTION_WRITE_ACTIONS  = 0x0003,
  INSTRUCTION_APPLY_ACTIONS  = 0x0004,
  INSTRUCTION_CLEAR_ACTIONS  = 0x0005,
  INSTRUCTION_METER          = 0x0006,
  INSTRUCTION_EXPERIMENTER   = 0xffff
};

/// \relates Instruction_header
Error_condition is_valid(const Instruction_type it);

/// \relates Instruction_header
std::string to_string(Instruction_type);

template<Instruction_type K>
  using Instruction_payload_base = Basic_payload_base<Instruction_type, K>;

// -------------------------------------------------------------------------- //
// Instruction: Goto table

struct Instruction_goto_table
  : Instruction_payload_base<INSTRUCTION_GOTO_TABLE>
{
  Instruction_goto_table() = default;
  explicit Instruction_goto_table(uint8_t tid) : table_id(tid) {}

  uint8_t table_id;
};

/// \relates Instruction_goto_table
bool
operator==(const Instruction_goto_table& a, const Instruction_goto_table& b);

/// \relates Instruction_goto_table
bool
operator!=(const Instruction_goto_table& a, const Instruction_goto_table& b);

/// \relates Instruction_goto_table
constexpr std::size_t bytes(const Instruction_goto_table&);

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
constexpr std::size_t bytes(const Instruction_write_metadata&);

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

template <Instruction_type K>
  struct Instruction_action : Instruction_payload_base<K>
  {
    Instruction_action() = default;

    explicit Instruction_action(const Sequence<Action>& a) : actions(a) { }

    Sequence<Action> actions;
  };

/// \relates Instruction_action
template <Instruction_type K>
  bool operator==(const Instruction_action<K>& a, const Instruction_action<K>& b);

/// \relates Instruction_action
template <Instruction_type K>
  bool
  operator!=(const Instruction_action<K>& a, const Instruction_action<K>& b);

/// \relates Instruction_action
template <Instruction_type K>
  std::size_t bytes(const Instruction_action<K>& ia);

/// \relates Instruction_action
template<Instruction_type K>
  constexpr Error_condition is_valid(const Instruction_action<K>&);

/// \relates Instruction_action
template <Instruction_type K>
  Error_condition to_buffer(Buffer_view& v, const Instruction_action<K>& ia);

/// \relates Instruction_action
template <Instruction_type K>
  Error_condition from_buffer(Buffer_view& v, Instruction_action<K>& ia);

// -------------------------------------------------------------------------- //
// Instruction : Write actions

struct Instruction_write_actions
  : Instruction_action<INSTRUCTION_WRITE_ACTIONS>
{
  using Instruction_action<INSTRUCTION_WRITE_ACTIONS>::Instruction_action;
};

/// \relates Instruction_write_actions
std::string to_string(const Instruction_write_actions&, Formatter&);

// -------------------------------------------------------------------------- //
// Instruction : Apply actions

struct Instruction_apply_actions
  : Instruction_action<INSTRUCTION_APPLY_ACTIONS>
{
  using Instruction_action<INSTRUCTION_APPLY_ACTIONS>::Instruction_action;
};

/// \relates Instruction_apply_actions
std::string to_string(const Instruction_apply_actions&, Formatter&);

// -------------------------------------------------------------------------- //
// Instruction : Clear actions

struct Instruction_clear_actions
  : Instruction_action<INSTRUCTION_CLEAR_ACTIONS>
{
  using Instruction_action<INSTRUCTION_CLEAR_ACTIONS>::Instruction_action;
};

/// \relates Instruction_clear_actions
std::string to_string(const Instruction_clear_actions&, Formatter&);

// -------------------------------------------------------------------------- //
// Instruction: Meter

struct Instruction_meter : Instruction_payload_base<INSTRUCTION_METER>
{
  Instruction_meter() = default;
  explicit Instruction_meter(uint32_t mid) : meter_id(mid) {}

  uint32_t meter_id;
};

/// \relates Instruction_meter
bool operator==(const Instruction_meter& a, const Instruction_meter& b);

/// \relates Instruction_meter
bool operator!=(const Instruction_meter& a, const Instruction_meter& b);

/// \relates Instruction_meter
constexpr std::size_t bytes(const Instruction_meter&);

/// \relates Instruction_meter
constexpr Error_condition is_valid(const Instruction_meter&);

/// \relates Instruction_meter
Error_condition to_buffer(Buffer_view&, const Instruction_meter&);

/// \relates Instruction_meter
Error_condition from_buffer(Buffer_view&, Instruction_meter&);

/// \relates Instruction_meter
std::string to_string(const Instruction_meter&, Formatter&);

// -------------------------------------------------------------------------- //
// Instruction: Experimenter

struct Instruction_experimenter
  : Instruction_payload_base<INSTRUCTION_EXPERIMENTER>
{ };

// -------------------------------------------------------------------------- //
// Instruction Payload

union Instruction_payload_data
{
  Instruction_payload_data() { }
  ~Instruction_payload_data() { }

  Instruction_goto_table      goto_table;
  Instruction_write_metadata  write_metadata;
  Instruction_write_actions   write_actions;
  Instruction_apply_actions   apply_actions;
  Instruction_clear_actions   clear_actions;
  Instruction_meter           meter;
  Instruction_experimenter    experimenter;
};

struct Instruction_payload
{
  using Data = Instruction_payload_data;

  Instruction_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

/// \relates Instruction_payload
void construct(Instruction_payload&, Instruction_type);

/// \relates Instruction_payload
void construct(Instruction_payload&, Instruction_payload&&,
               Instruction_type);

/// \relates Instruction_payload
void construct(Instruction_payload&, const Instruction_payload&,
               Instruction_type);

/// \relates Instruction_payload
template<typename Tag, typename... Args>
  void construct(Instruction_payload& p, Tag t, Args&&... args) = delete;

/// \relates Instruction_payload
Instruction_payload& assign(Instruction_payload&, Instruction_payload&&,
                            Instruction_type);

/// \relates Instruction_payload                            
Instruction_payload& assign(Instruction_payload&, const Instruction_payload&,
                            Instruction_type);

/// \relates Instruction_payload
void destroy(Instruction_payload&, Instruction_type);

/// \relates Instruction_payload
bool equal(const Instruction_payload&, const Instruction_payload&,
           Instruction_type, Instruction_type);

/// \relates Instruction_payload
std::size_t bytes(const Instruction_payload&, Instruction_type);

/// \relates Instruction_payload
Error_condition is_valid(const Instruction_payload&, Instruction_type);

/// \relates Instruction_payload
Error_condition to_buffer(Buffer_view&, const Instruction_payload&, Instruction_type);

/// \relates Instruction_payload
Error_condition from_buffer(Buffer_view&, Instruction_payload&, Instruction_type);

/// \relates Instruction_payload
std::string to_string(const Instruction_payload&, Formatter&,
                      Instruction_type);

// -------------------------------------------------------------------------- //
// Instruction header

struct Instruction_header
{
  Instruction_header() = default;
  Instruction_header(Instruction_type t, uint16_t l) : type(t), length(l) { }
  Instruction_header(Instruction_type t, uint16_t l, uint32_t eid)
    : type(t), length(l), experimenter_id(eid) { }

  template<typename T>
    explicit Instruction_header(const T& value);

  Instruction_type type;
  uint16_t length;
  uint32_t experimenter_id;
};

/// \relates Instruction_header
bool operator==(const Instruction_header& a, const Instruction_header& b);

/// \relates Instruction_header
bool operator!=(const Instruction_header& a, const Instruction_header& b);

/// \relates Instruction_header
std::size_t bytes(const Instruction_header& h);

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

/// Instruction is the top-level structure that is the policy result of a flow
/// table match. The instruction can forward the packet to another table, goto,
/// update metadata, or apply a sequence of actions.
/// 
/// \remark Defined in [OpenFlow v1.3, p46-47](http://...)
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

/// \relates Instruction
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

struct Port
{
  static constexpr std::size_t NAME_STR_LEN = 16;

  using Name_string = Stringbuf<NAME_STR_LEN>;

  enum Config_value : uint32_t {
    PORT_DOWN = 0x00000001, NO_RECV = 0x00000004, NO_FWD = 0x00000020,
    NO_PACKET_IN = 0x00000040
  };

  enum State_value : uint32_t {
    LINK_DOWN = 0x00000001, BLOCKED = 0x00000002, LIVE = 0x00000004
  };

  enum Id_value : uint32_t {
    MAX = 0xffffff00, IN_PORT = 0xfffffff8, TABLE = 0xfffffff9,
    NORMAL = 0xfffffffa, FLOOD = 0xfffffffb, ALL = 0xfffffffc,
    CONTROLLER = 0xfffffffd, LOCAL = 0xfffffffe, ANY = 0xffffffff
  };

  enum Features_value : uint32_t {
    TEN_MB_HD = 0x0000001, TEN_MB_FD = 0x00000002,
    HUNDRED_MB_HD = 0x00000004, HUNDRED_MB_FD = 0x00000008,
    ONE_GB_HD = 0x00000010, ONE_GB_FD = 0x00000020,
    TEN_GB_FD = 0x00000040, FORTY_GB_FD = 0x00000080,
    HUNDRED_GB_FD = 0x00000100, ONE_TB_FD = 0x00000200,
    OTHER = 0x00000400, COPPER = 0x00000800, FIBER = 0x00001000,
    AUTO_NEG = 0x00002000, PAUSE = 0x00004000, PAUSE_ASYM = 0x00008000
  };

  Port() = default;
  Port(Id_value pid, Ethernet_addr ha, const char* n, Config_value c,
       State_value s, Features_value cu, Features_value a,
       Features_value su, Features_value p, uint32_t cs,
       uint32_t ms)
    : port_id(pid), hw_addr(ha), name(n), config(c), state(s), curr(cu),
    advertised(a), supported(su), peer(p), curr_speed(cs), max_speed(ms) { }

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
constexpr std::size_t bytes(const Port&);

/// \relates Port
Error_condition is_valid(const Port::Id_value id);

/// \relates Port
Error_condition is_valid(const Port::Config_value);

/// \relates Port
Error_condition is_valid(const Port::State_value);

/// \relates Port
Error_condition is_valid(const Port::Features_value);

/// \relates Port
Error_condition is_valid(const Port& p) ;

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
constexpr bool port_config_port_down(uint32_t c);

/// \relates Port
constexpr bool port_config_no_recv(uint32_t c);

/// \relates Port
constexpr bool port_config_no_fwd(uint32_t c);

/// \relates Port
constexpr bool port_config_no_packet_in(uint32_t c);

/// \relates Port
constexpr bool port_state_blocked(uint32_t s);

/// \relates Port
constexpr bool port_state_live(uint32_t s);

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
constexpr bool port_any(uint16_t p);

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
constexpr bool port_feature_40gb_fd(uint32_t p);

/// \relates Port
constexpr bool port_feature_100gb_fd(uint32_t p);

/// \relates Port
constexpr bool port_feature_1tb_fd(uint32_t p);

/// \relates Port
constexpr bool port_feature_other(uint32_t p);

/// \relates Port
constexpr bool port_feature_copper(uint32_t p);

/// \relates Port
constexpr bool port_feature_fiber(uint32_t p);

/// \relates Port
constexpr bool port_feature_auto_neg(uint32_t p);

/// \relates Port
constexpr bool port_feature_pause(uint32_t p);

// -------------------------------------------------------------------------- //
// Queue property type

enum Queue_property_type : uint16_t
{
  QUEUE_PROPERTY_MIN_RATE = 1,
  QUEUE_PROPERTY_MAX_RATE = 2,
  QUEUE_PROPERTY_EXPERIMENTER = 0xffff,
};

/// \relates Queue_property_header
constexpr Error_condition is_valid(const Queue_property_type t);

/// \relates Queue_property_header
std::string to_string(Queue_property_type);

// A base class for all queue property payload kinds
template<Queue_property_type K>
  using Queue_property_payload_base
    = Basic_payload_base<Queue_property_type, K>;

// -------------------------------------------------------------------------- //
// Queue property: Min rate

struct Queue_property_min_rate
  : Queue_property_payload_base<QUEUE_PROPERTY_MIN_RATE>
{
  Queue_property_min_rate() = default;
  explicit Queue_property_min_rate(uint16_t r) : rate(r) { }

  uint16_t rate;
};

/// \relates Queue_property_min_rate
bool
operator==(const Queue_property_min_rate& a, const Queue_property_min_rate& b);

/// \relates Queue_property_min_rate
bool
operator!=(const Queue_property_min_rate& a, const Queue_property_min_rate& b);

/// \relates Queue_property_min_rate
constexpr std::size_t bytes(const Queue_property_min_rate&);

/// \relates Queue_property_min_rate
constexpr Error_condition is_valid(const Queue_property_min_rate&);

/// \relates Queue_property_min_rate
Error_condition to_buffer(Buffer_view&, const Queue_property_min_rate&);

/// \relates Queue_property_min_rate
Error_condition from_buffer(Buffer_view&, Queue_property_min_rate&);

/// \relates Queue_property_min_rate
std::string to_string(const Queue_property_min_rate&, Formatter&);

// -------------------------------------------------------------------------- //
// Queue property: Max rate

struct Queue_property_max_rate
  : Queue_property_payload_base<QUEUE_PROPERTY_MIN_RATE>
{
  Queue_property_max_rate() = default;
  explicit Queue_property_max_rate(uint16_t r) : rate(r) { }

  uint16_t rate;
};

/// \relates Queue_property_max_rate
bool
operator==(const Queue_property_max_rate& a, const Queue_property_max_rate& b);

/// \relates Queue_property_max_rate
bool
operator!=(const Queue_property_max_rate& a, const Queue_property_max_rate& b);

/// \relates Queue_property_max_rate
constexpr std::size_t bytes(const Queue_property_max_rate&);

/// \relates Queue_property_max_rate
constexpr Error_condition is_valid(const Queue_property_max_rate&);

/// \relates Queue_property_max_rate
Error_condition to_buffer(Buffer_view&, const Queue_property_max_rate&);

/// \relates Queue_property_max_rate
Error_condition from_buffer(Buffer_view&, Queue_property_max_rate&);

/// \relates Queue_property_max_rate
std::string to_string(const Queue_property_max_rate&, Formatter&);

// -------------------------------------------------------------------------- //
// Queue property: Experimenter

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
bool operator==(const Queue_property_experimenter& a,
                const Queue_property_experimenter& b);

/// \relates Queue_property_experimenter
bool operator!=(const Queue_property_experimenter& a,
                const Queue_property_experimenter& b);

/// \relates Queue_property_experimenter
std::size_t bytes(const Queue_property_experimenter& e);

/// \relates Queue_property_experimenter
constexpr Error_condition is_valid(const Queue_property_experimenter& e);

/// \relates Buffer_view
Error_condition to_buffer(Buffer_view&, const Queue_property_experimenter&);

/// \relates Buffer_view
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

/// Object used to handle the initialization of the payload of a Queue_property
/// object
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
Queue_property_payload& assign(Queue_property_payload&,
                               const Queue_property_payload&,
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
    : property(p), length(l) { }

  template<typename T>
    Queue_property_header(const T& value);

  Queue_property_type property;
  uint16_t length;
};

/// \relates Queue_property_header
bool
operator==(const Queue_property_header& a, const Queue_property_header& b);

/// \relates Queue_property_header
bool
operator!=(const Queue_property_header& a, const Queue_property_header& b);

/// \relates Queue_property_header
constexpr std::size_t bytes(const Queue_property_header&);

/// \relates Queue_property_header
Error_condition is_valid(const Queue_property_header& h);

/// \relates Queue_property_header
Error_condition to_buffer(Buffer_view&, const Queue_property_header&);

/// \relates Queue_property_header
Error_condition from_buffer(Buffer_view&, Queue_property_header&);

/// \relates Queue_property_header
std::string to_string(const Queue_property_header&, Formatter&);

// -------------------------------------------------------------------------- //
// Queue property

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

/// \relates Queue_property
bool operator==(const Queue_property& a, const Queue_property& b);

/// \relates Queue_property
bool operator!=(const Queue_property& a, const Queue_property& b);

/// \relates Queue_property
std::size_t bytes(const Queue_property& p);

/// \relates Queue_property
Error_condition is_valid(const Queue_property& p);

/// \relates Queue_property
Error_condition to_buffer(Buffer_view& v, const Queue_property& qp);

/// \relates Queue_property
Error_condition from_buffer(Buffer_view& v, const Queue_property& qp);

/// \relates Queue_property
std::string to_string(const Queue_property&,  Formatter&);

// -------------------------------------------------------------------------- //
// Queue

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
Error_condition is_valid(const Queue& q);

/// \relates Queue
Error_condition to_buffer(Buffer_view&, const Queue&);

/// \relates Queue
Error_condition from_buffer(Buffer_view&, Queue&);

/// \relates Queue
std::string to_string(const Queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Bucket

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
// Messages
//
// The following messages are in the v1_3 protocol.
//
// Hello
// Error
// Echo_req
// Echo_res
// Experimenter
// ...


// -------------------------------------------------------------------------- //
// Version Type

/// Represents the value of the protocol version. There is a single 
/// enumeration value, VERSION. 
enum Version_type : std::uint8_t
{
  VERSION = 4
};

/// Validates the value of a Version_type object. Returns SUCCESS only when v 
/// compares equal to VERSION and BAD_VERSION otherwise.
///
/// \relates Version_type
Error_condition is_valid(const Version_type t);

/// Returns a string representation of the value.
///
/// \relates Version_type
std::string to_string(Version_type t);

// -------------------------------------------------------------------------- //
// Message Type

/// Represents the type of message being sent or received.
/// 
/// \relates Message
enum Message_type : std::uint8_t
{
  HELLO                = 0, ///< see Hello
  ERROR                = 1, ///< see Error
  ECHO_REQ             = 2, ///< see Echo_req
  ECHO_RES             = 3, ///< see Echo_res
  EXPERIMENTER         = 4, ///< see Experimenter
  FEATURE_REQ          = 5, ///< see Feature_req
  FEATURE_RES          = 6, ///< see Feature_res
  GET_CONFIG_REQ       = 7, ///< see Get_config_req
  GET_CONFIG_RES       = 8, ///< see Get_config_res
  SET_CONFIG           = 9, ///< see Set_config
  PACKET_IN            = 10, ///< see Packet_in
  FLOW_REMOVED         = 11, ///< see Flow_removed
  PORT_STATUS          = 12, ///< see Port_status
  PACKET_OUT           = 13, ///< see Packet_out
  FLOW_MOD             = 14, ///< see Flow_mod
  GROUP_MOD            = 15, ///< see Group_mod
  PORT_MOD             = 16, ///< see Port_mod
  TABLE_MOD            = 17, ///< see Table_mod
  MULTIPART_REQ        = 18, ///< see Multipart_req
  MULTIPART_RES        = 19, ///< see Multipart_res
  BARRIER_REQ          = 20, ///< see Barrier_req
  BARRIER_RES          = 21, ///< see Barrier_res
  QUEUE_GET_CONFIG_REQ = 22, ///< see Queue_get_config_req
  QUEUE_GET_CONFIG_RES = 23, ///< see Queue_get_config_res
  ROLE_REQ             = 24, ///< see Role_req
  ROLE_RES             = 25, ///< see Role_res
  GET_ASYNC_REQ        = 26, ///< see Get_async_req
  GET_ASYNC_RES        = 27, ///< see Get_async_res
  SET_ASYNC            = 28, ///< see Set_async
  METER_MOD            = 29  ///< see Meter_mod
};

/// Validates the value of a Message_type object. Returns SUCCESS only when m 
/// is a declared value of Message_type and BAD_MESSAGE otherwise.
///
/// \relates Message_type
Error_condition is_valid(const Message_type t);

/// Returns a string representation of the value.
/// \relates Message_type
std::string to_string(Message_type t);

// A helper type for primary message payloads.
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
/// \remark Defined in [OpenFlow v1.3, p84](http://...)
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
std::size_t bytes(const Hello& h);

/// Validates the value of a Hello message. The result is always SUCCESS since 
/// a Hello message is valid by construction.
///
/// \relates Hello
constexpr Error_condition is_valid(const Hello& h);

/// Writes a Hello message into a Buffer_view. If the write does not succeed, 
/// the result will contain a code representing the specific cause of failure.
///
/// \relates Hello
Error_condition to_buffer(Buffer_view&, const Hello&);

/// Reads a Hello message from a Buffer_view. If the read does not succeed, 
/// the result will contain a code representing the specific cause of failure.
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
/// \invariant if m.type == SWITCH_CONFIG_FAILED then is_valid(m.code.scf)
/// \invariant if m.type == ROLE_REQUEST_FAILED then is_valid(m.code.rrf)
/// \invariant if m.type == METER_MOD_FAILED then is_valid(m.code.mmf)
/// \invariant if m.type == TABLE_FEATURES_FAILED then is_valid(m.code.tff)
///
/// \remark Defined in [OpenFlow v1.3, p79-84](http://...)
struct Error : Payload_base<ERROR>
{
  /// Describes the categories of error codes.
  enum Type : uint16_t {
    /// Hello protocol failed (see Error::Hello_failed).   
    HELLO_FAILED          = 0x0000,
    
    /// Request was not understood (see Error::Bad_request).
    BAD_REQUEST           = 0x0001,
    
    /// Error in action description (see Error::Bad_action).
    BAD_ACTION            = 0x0002,
    
    /// Error in instruction description (see Error::Bad_instruction).
    BAD_INSTRUCTION       = 0x0003,
    
    /// Error in match description (see Error::Bad_match).
    BAD_MATCH             = 0x0004,
    
    /// Flow modification failed (see Error::Flow_mod_failed).
    FLOW_MOD_FAILED       = 0x0005,
    
    /// Group modification failed (see Error::Group_mod_failed).
    GROUP_MOD_FAILED      = 0x0006,
    
    /// Port modification failed (see Error::Port_mod_failed).
    PORT_MOD_FAILED       = 0x0007,
    
    /// Table modification failed (see Error::Table_mod_failed).
    TABLE_MOD_FAILED      = 0x0008,

    /// Queue operation failed (see Error::Queue_op_failed).
    QUEUE_OP_FAILED       = 0x0009,
    
    /// Switch configuration failed (see Error::Switch_config_failed).
    SWITCH_CONFIG_FAILED  = 0x000a,
    
    /// Role request failed (see Error::Role_request_failed).
    ROLE_REQUEST_FAILED   = 0x000b,
    
    /// Meter modification failed (see Error::Meter_mod_failed).
    METER_MOD_FAILED      = 0X000c,
    
    /// Setting table features failed (see Error::Table_features_failed).
    TABLE_FEATURES_FAILED = 0X000d,
    
    /// Allows for extensibility (see Error::Experimenter).
    EXPERIMENTER          = 0xffff
  };

  /// Describes Hello protocol failures.
  enum Hello_failed : uint16_t {
    HF_INCOMPATIBLE = 0x0000, ///< No compatible version
    HF_EPERM        = 0x0001  ///< Permissions error
  };

  /// Describes bad requests.
  enum Bad_request : uint16_t {
    BR_BAD_VERSION               = 0x0000, ///< Header version not supprted
    BR_BAD_TYPE                  = 0x0001, ///< Message type not supported
    BR_BAD_STAT                  = 0x0002, ///< Stat request type not supported
    BR_BAD_EXPERIMENTER          = 0x0003, ///< Experimenter id not supported
    /// Experimenter subtype not supported
    BR_BAD_EXP_TYPE              = 0x0004,
    BR_EPERM                     = 0x0005, ///< Permisssions error
    BR_BAD_LEN                   = 0x0006, ///< Wrong message length
    /// Specified buffer has already been used
    BR_BUFFER_EMPTY              = 0x0007,
    BR_BUFFER_UNKNOWN            = 0x0008, ///< Specified buffer does not exist
    /// Specified table id is invalid or does not exist
    BR_BAD_TABLE_ID              = 0x0009,
    /// Denied because controller is slave
    BR_IS_SLAVE                  = 0x000a,
    BR_BAD_PORT                  = 0x000b, ///< Invalid port
    BR_BAD_PACKET                = 0x000c, ///< Invalid packet in packet-out
    /// Multipart request overflowed the assigned buffer
    BR_MULTIPART_BUFFER_OVERFLOW = 0X000d
  };

  /// Describes bad actions.
  enum Bad_action : uint16_t {
    BA_BAD_TYPE              = 0x0000, ///< Unknown action type
    BA_BAD_LEN               = 0x0001, ///< Wrong length for action
    BA_BAD_EXPERIMENTER      = 0x0002, ///< Unknown experimenter id
    /// Unknown action type for experimenter id
    BA_BAD_EXPERIMENTER_TYPE = 0x0003,
    BA_BAD_OUT_PORT          = 0x0004, ///< Problem validating output port
    BA_BAD_ARGUMENT          = 0x0005, ///< Bad action argument
    BA_EPERM                 = 0x0006, ///< Permissions error
    BA_TOO_MANY              = 0x0007, ///< Too many actions
    BA_BAD_QUEUE             = 0x0008, ///< Problem validating the output queue
    BA_BAD_OUT_GROUP         = 0x0009, ///< Invalid group id in forward action
    /// Action cannot apply this match or set-field missing prerequisite
    BA_MATCH_INCONSISTENT    = 0x000a,
    /// Action order is unsupported for the action list in an apply actions
    /// instruction
    BA_UNSUPPORTED_ORDER     = 0x000b,
    BA_BAD_TAG               = 0x000c, ///< Action uses an unsupported tag
    BA_BAD_SET_TYPE          = 0x000d, ///< Unsupported type in SET_FIELD action
    BA_BAD_SET_LEN           = 0x000e, ///< Bad length in SET_FIELD action
    BA_BAD_SET_ARGUMENT      = 0x000f  ///< Bad argument in SET_FIELD action
  };

  /// Describes bad instructions.
  enum Bad_instruction : uint16_t {
    BI_UNKNOWN_INST        = 0x0000, ///< Unknown instruction
    /// Instruction not supported by the switch table
    BI_UNSUP_INST          = 0x0001,
    BI_BAD_TABLE_ID        = 0x0002, ///< Invalid table id
    /// Metadata value not supported by datapath
    BI_UNSUP_METADATA      = 0x0003,
    /// Metadata mask value not supported by datapath
    BI_UNSUP_METADATA_MASK = 0x0004,
    BI_BAD_EXPERIMENTER    = 0x0005, ///< Unknown experimenter id
    /// Unknown instruction for experimenter id
    BI_BAD_EXP_TYPE        = 0x0006,
    BI_BAD_LEN             = 0x0007, ///< Length problems in instructions
    BI_EPERM               = 0x0008  ///< Permissions error
  };

  /// Describes bad matches.
  enum Bad_match : uint16_t {
    BM_BAD_TYPE         = 0x0000, ///< Invalid match type
    BM_BAD_LEN          = 0x0001, ///< Wrong length for match
    BM_BAD_TAG          = 0x0002, ///< Unsupported tag
    BM_BAD_DL_ADDR_MASK = 0x0003, ///< Unsupported datalink addr mask
    BM_BAD_HW_ADDR_MASK = 0x0004, ///< Unsupported network addr mask
    /// Unsupported combination of fields masked or omitted in the match
    BM_BAD_WILDCARDS    = 0x0005,
    BM_BAD_FIELD        = 0x0006, ///< Unsupported field type in the match
    BM_BAD_VALUE        = 0x0007, ///< Unsupported value in a match field
    /// Unsupported mask specified in the match, field is not dl-address or
    /// nw-address.
    BM_BAD_MASK         = 0x0008,
    BM_BAD_PREREQ       = 0x0009, ///< Prerequisite not met
    BM_DUP_FIELD        = 0x000a, ///< A field type was duplicated
    BM_EPERM            = 0x000b  ///< Permissions error
  };

  /// Describes flow modification failures.
  enum Flow_mod_failed : uint16_t {
    FMF_UNKNOWN      = 0x0000, ///< Unspecified error
    FMF_TABLE_FULL   = 0x0001, ///< Cannot add the flow because table is full
    FMF_BAD_TABLE_ID = 0x0002, ///< Table id does not exist
    /// Attempted to add overlapping flow with CHECK_OVERLAP flag set
    FMF_OVERLAP      = 0x0003,
    FMF_EPERM        = 0x0004, ///< Perminssions error
    FMF_BAD_TIMEOUT  = 0x0005, ///< Operation timed out
    FMF_BAD_COMMAND  = 0x0006, ///< Unknown command
    FMF_BAD_FLAGS    = 0x0007  ///< Unsupported or unknown flags
  };

  /// Describes group modification failures.
  enum Group_mod_failed : uint16_t {
    /// Failed because add would replace existing group
    GMF_GROUP_EXISTS         = 0x0000,
    GMF_INVALID_GROUP        = 0x0001, ///< Group specified was invalid
    GMF_WEIGHT_UNSUPPORTED   = 0x0002, ///< Unequal load sharing not supported
    GMF_OUT_OF_GROUPS        = 0x0003, ///< Group table full
    GMF_OUT_OF_BUCKETS       = 0x0004, ///< No more action buckets for group
    /// Group to group forwarding not supported
    GMF_CHAINING_UNSUPPORTED = 0x0005,
    /// This group cannot watch the port or group specified
    GMF_WATCH_UNSUPPORTED    = 0x0006,
    GMF_LOOP                 = 0x0007, ///< Group entry would cause a loop
    /// Not modified because group non-existent
    GMF_UNKNOWN_GROUP        = 0x0008,
    /// Not deleted because another group is forwarding to it
    GMF_CHAINED_GROUP        = 0x0009,
    GMF_BAD_TYPE             = 0x000a, ///< Unsupported group type
    GMF_BAD_COMMAND          = 0x000b, ///< Unsupported command
    GMF_BAD_BUCKET           = 0x000c, ///< Invalid bucket
    GMF_BAD_WATCH            = 0x000d, ///< Invalid watch in port or group
    GMF_EPERM                = 0x000e  ///< Permissions error
  };

  /// Describes port modification failures.
  enum Port_mod_failed : uint16_t {
    PMF_BAD_PORT      = 0x0000, ///< Specified port does not exist
    PMF_BAD_HW_ADDR   = 0x0001, ///< Hardware address does not match the port
    PMF_BAD_CONFIG    = 0x0002, ///< Invalid configuration
    PMF_BAD_ADVERTISE = 0x0003, ///< Invalid advertise
    PMF_EPERM         = 0x0004  ///< Permissions error
  };

  /// Describes table modification failures.
  enum Table_mod_failed : uint16_t {
    TMF_BAD_TABLE  = 0x0000, ///< Table does not exist
    TMF_BAD_CONFIG = 0x0001, ///< Invalid configuration
    TMF_EPERM      = 0x0002  ///< Permissions error
  };
 
  /// Describes queue operation failures.
  enum Queue_op_failed : uint16_t {
    QOF_BAD_PORT  = 0x0000, ///< Invalid port
    QOF_BAD_QUEUE = 0x0001, ///< Queue does not exist
    QOF_EPERM     = 0x0002  ///< Permissions error
  };

  /// Describes switch configuration failures.
  enum Switch_config_failed : uint16_t {
    SCF_BAD_FLAGS = 0x0000, ///< Invalid flag
    SCF_BAD_LEN   = 0x0001, ///< Invalid length
    SCF_EPERM     = 0x0002  ///< Permissions error
  };

  /// Describes role request failures.
  enum Role_request_failed : uint16_t {
    RRF_STALE    = 0x0000, ///< Stale message
    RRF_UNSUP    = 0x0001, ///< Controller role change unsupported
    RRF_BAD_ROLE = 0x0002  ///< Invalid role
  };

  /// Describes meter modification failures.
  enum Meter_mod_failed : uint16_t {
    MMF_UNKNOWN        = 0x0000, ///< Unspecified error
    /// Failed because add would replace existing meter
    MMF_METER_EXISTS   = 0x0001,
    MMF_INVALID_METER  = 0x0002, ///< Not added because meter invalid
    MMF_UNKNOWN_METER  = 0x0003, ///< Not modified because meter non-existent
    MMF_BAD_COMMAND    = 0x0004, ///< Unsupported or unknown command
    MMF_BAD_FLAGS      = 0x0005, ///< Unsupported flag configuration
    MMF_BAD_RATE       = 0x0006, ///< Unsupported rate
    MMF_BAD_BURST      = 0x0007, ///< Unsupported burst size
    MMF_BAD_BAND       = 0x0008, ///< Unsupported band
    MMF_BAD_BAND_VALUE = 0x0009, ///< Unsupported band value
    MMF_OUT_OF_METERS  = 0x000a, ///< No meters available
    /// Exceeded maximum number of properties for a meter
    MMF_OUT_OF_BANDS   = 0x000b
  };

  /// Describes table feature failures.
  enum Table_features_failed : uint16_t {
    TFF_BAD_TABLE         = 0x0000, ///< Table does not exist
    TFF_BAD_METADATA      = 0x0001, ///< Invalid metadata mask
    TFF_BAD_TYPE          = 0x0002, ///< Unknown property type
    TFF_BAD_LENGTH        = 0x0003, ///< Invalid property length
    TFF_BAD_ARGUMENT      = 0x0004, ///< Unsupported property value
    TFF_PERMISSIONS_ERROR = 0x0005  ///< Permissions error
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
    Code(Meter_mod_failed f) : mmf(f) { }
    Code(Table_features_failed f) : tff(f) { }
    Code(uint16_t n) : value(n) { }

    Hello_failed          hf;
    Bad_request           br;
    Bad_action            ba;
    Bad_instruction       bi;
    Bad_match             bm;
    Flow_mod_failed       fmf;
    Group_mod_failed      gmf;
    Port_mod_failed       pmf;
    Table_mod_failed      tmf;
    Queue_op_failed       qof;
    Switch_config_failed  scf;
    Role_request_failed   rrf;
    Meter_mod_failed      mmf;
    Table_features_failed tff;
    uint16_t              value; // Uninterpreted value
  };

  /// Constructs a default Error message.
  Error() = default;

  /// Constructs a hello failed Error message. Initialize the error message with
  /// a Hello_failed code f and the error buffer b.
  Error(Hello_failed f, const Greedy_buffer& b)
    : type(HELLO_FAILED), code(f), data() { }

  /// Constructs a bad request Error message. Initialize the error message with
  /// a Bad_request code f and the error buffer b.
  Error(Bad_request f, const Greedy_buffer& b)
    : type(BAD_REQUEST), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Bad_action code f and the error buffer b.
  Error(Bad_action f, const Greedy_buffer& b)
    : type(BAD_ACTION), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Bad_instruction code f and the error buffer b.
  Error(Bad_instruction f, const Greedy_buffer& b)
    : type(BAD_INSTRUCTION), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Bad_match code f and the error buffer b.
  Error(Bad_match f, const Greedy_buffer& b)
    : type(BAD_MATCH), code(f), data() { }

  /// Constructs a flow modification Error message. Initialize the error message
  /// with a Flow_mod_failed code f and the error buffer b.
  Error(Flow_mod_failed f, const Greedy_buffer& b)
    : type(FLOW_MOD_FAILED), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Group_mod_failed code f and the error buffer b.
  Error(Group_mod_failed f, const Greedy_buffer& b)
    : type(GROUP_MOD_FAILED), code(f), data() { }

  /// Constructs a port modification Error message. Initialize the error message
  /// with a Port_mod_failed code f and the error buffer b.
  Error(Port_mod_failed f, const Greedy_buffer& b)
    : type(PORT_MOD_FAILED), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Table_mod_failed code f and the error buffer b.
  Error(Table_mod_failed f, const Greedy_buffer& b)
    : type(TABLE_MOD_FAILED), code(f), data() { }

  /// Constructs a queue operation Error message. Initialize the error message
  /// with a Queue_op_failed code f and the error buffer b.
  Error(Queue_op_failed f, const Greedy_buffer& b)
    : type(QUEUE_OP_FAILED), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Switch_config_failed code f and the error buffer b.
  Error(Switch_config_failed f, const Greedy_buffer& b)
    : type(SWITCH_CONFIG_FAILED), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Role_request_failed code f and the error buffer b.
  Error(Role_request_failed f, const Greedy_buffer& b)
    : type(ROLE_REQUEST_FAILED), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Meter_mod_failed code f and the error buffer b.
  Error(Meter_mod_failed f, const Greedy_buffer& b)
    : type(METER_MOD_FAILED), code(f), data() { }

  /// Constructs a bad action Error message. Initialize the error message with
  /// a Table_features_failed code f and the error buffer b.
  Error(Table_features_failed f, const Greedy_buffer& b)
    : type(TABLE_FEATURES_FAILED), code(f), data() { }

  /// Initialize the error message with error type t and the error
  /// code c. Note that the value is ill-formed if c is not a valid
  /// code for the error type t.
  Error(Type t, uint16_t c, const Greedy_buffer& b)
    : type(t), code(c), data(b) { assert(is_valid(*this)); }

  Type type;
  uint16_t code;
  uint32_t experimenter_id; //only used for experimenter error
  Greedy_buffer data;
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
/// \relates Queue_op_failed
Error_condition is_valid(const Error::Queue_op_failed c);

/// Validates the value of an Error::Switch_config_failed object.
///
/// \relates Error::Switch_config_failed
Error_condition is_valid(const Error::Switch_config_failed c);

/// Validates the value of an Error::Role_request_failed object.
///
/// \relates Error::Role_request_failed
Error_condition is_valid(const Error::Role_request_failed c);

/// Validates the value of an Error::Meter_mod_failed object.
///
/// \relates Error::Meter_mod_failed
Error_condition is_valid(const Error::Meter_mod_failed c);

/// Validates the value of an Error::Table_features_failed object.
///
/// \relates Error::Table_features_failed
Error_condition is_valid(const Error::Table_features_failed c);

/// Validates the value of an Error::Code for a specified Error::type
///
/// \relates Error
Error_condition is_valid(const Error::Type t, Error::Code c);

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

/// Returns a string representation of an Error::Table_mod_failed value.
///
/// \relates Error::Table_mod_failed
std::string to_string(Error::Table_mod_failed);

/// Returns a string representation of an Error::Port_mod_failed value.
///
/// \relates Error::Port_mod_failed
std::string to_string(Error::Port_mod_failed);

/// Returns a string representation of an Error::Queue_op_failed value.
///
/// \relates Error::Queue_op_failed
std::string to_string(Error::Queue_op_failed);

/// Returns a string representation of an Error::Switch_config_failed value.
///
/// \relates Error::Switch_config_failed
std::string to_string(Error::Switch_config_failed);

/// Returns a string representation of an Error::Role_request_failed value.
///
/// \relates Error::Role_request_failed
std::string to_string(Error::Role_request_failed);

/// Returns a string representation of an Error::Meter_mod_failed value.
///
/// \relates Error::Meter_mod_failed
std::string to_string(Error::Meter_mod_failed);

/// Returns a string representation of an Error::Table_features_failed value.
///
/// \relates Error::Table_features_failed
std::string to_string(Error::Table_features_failed);

/// Returns a string representation of an Error::Code value given the
/// corresponding Error::type.
///
/// \relates Error::Flow_mod_failed
std::string to_string(Error::Type, Error::Code);

/// Returns a formatted string representation of an Error_message value.
///
/// \relates Error
std::string to_string(const Error&, Formatter&);

// -------------------------------------------------------------------------- //
// Echo Base

template<Message_type K>
  struct Echo_base : Payload_base<ECHO_REQ>
  {
    Echo_base() = default;
    Echo_base(const Greedy_buffer& b) : data(b) { }

    Greedy_buffer data;
  };

/// \relates Echo_base
template<Message_type K>
  bool operator==(const Echo_base<K>& a, const Echo_base<K>& b);

/// \relates Echo_base
template<Message_type K>
  bool operator!=(const Echo_base<K>& a, const Echo_base<K>& b);

/// \relates Echo_base
template<Message_type K>
  std::size_t bytes(const Echo_base<K>& e);

/// \relates Echo_base
template<Message_type K>
  constexpr Error_condition is_valid(const Echo_base<K>&);

/// \relates Echo_base
template<Message_type K>
  Error_condition to_buffer(Buffer_view& v, const Echo_base<K>& e);

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
/// \remark Defined in [OpenFlow v1.3, p84](http://...)
struct Echo_req : Echo_base<ECHO_REQ> { };

// -------------------------------------------------------------------------- //
// Echo Res

/// Sent by the switch to exchange information about latency, bandwidth, and
/// liveness. The EchoRes message is used to exchange information about latency,
/// bandwidth, and liveness. Request timeouts indicate a disconnection. The
/// response contains a copy of the data sent by the request.
///
/// \remark Defined in [OpenFlow v1.3, p84](http://...)
struct Echo_res : Echo_base<ECHO_RES> { };

// -------------------------------------------------------------------------- //
// Experimenter

/// Represents a proprietary messages within the protocol. the
/// Vendor/Experimenter message is a mechanism for creating proprietary messages
/// within the protocol. In v1.0 this was called Vendor; however, in subsequent
/// versions the name was changed to experimenter.
/// 
/// \remark Defined in [OpenFlow v1.3, p84-85](http://...)
struct Experimenter : Payload_base<EXPERIMENTER>
{
  Experimenter() = default;
  Experimenter(uint32_t e, uint32_t t, Greedy_buffer d)
    : experimenter_id(e), experimenter_type(t), data(d) { }

  uint32_t experimenter_id;
  uint32_t experimenter_type;
  Greedy_buffer data;
};

/// Returns true when the arguments compare equal. Two Experimenter messages, a
/// and b, compare equal when they have both the same experimenter id and
/// the same uninterpreted data.
///
/// \relates Experimenter
bool operator==(const Experimenter& a, const Experimenter& b);

/// Returns true when the arguments do not compare equal.
///
/// \relates Experimenter
bool operator!=(const Experimenter& a, const Experimenter& b);

/// Returns the number of bytes needed to represent the particular Experimenter
/// message.
///
/// \relates Experimenter
std::size_t bytes(const Experimenter& e);

/// Validates the value of a Vendor message. The result is always SUCCESS
/// since a Vendor message is valid on construction.
///
/// \relates Experimenter
constexpr Error_condition is_valid(const Experimenter&);

/// Writes an Experimenter message into a Buffer_view.
///
/// \relates Experimenter
Error_condition to_buffer(Buffer_view&, const Experimenter&);

/// Reads an Experimenter message from a Buffer_view.
///
/// \relates Experimenter
Error_condition from_buffer(Buffer_view&, Experimenter&);

/// Returns a formatted string representation of the value.
///
/// \relates Experimenter
std::string to_string(const Experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// Feature Request

/// When a transport channel (TCP, SCTP, TLS) is established between the switch
/// and controller, first the set of available features needs to be determined.
/// The controller sends a Feature_req message to the switch over the transport
/// channel. The feature request only consists of an OpenFlow header message
/// with the type field set for a Feature_req. The switch responds to this
/// request with its capabilities. This basic sequence does not change across
/// OF versions; however, FeatureRes does.
/// 
/// \remark Defined in [OpenFlow v1.3, p52-53](http://...)
struct Feature_req : Payload_base<FEATURE_REQ> { };

// -------------------------------------------------------------------------- //
// Feature Response

/// The FeatureRes is the switch's reply to the controller enumerating its
/// abilities (After receiving a Feature_req message). The datapath-id is a
/// 64-bit field that should be thought of as analogous to the MAC of an
/// Ethernet switch's bridge. It is a unique identifier for the specific packet
/// processing pipeline being managed. One physical switch may have more than
/// one datapath-id (this can be seen as a virtualization of the switch). The
/// Feature_res::n_buffers field identifies how many packets the switch can
/// queue for PacketIn (capture and forward to the controller) activities. The
/// number of tables in the switch is captured by Feature_res::n_tbls. Pads are
/// used to maintain byte alignment where necessary. Capabilities and actions
/// are expressed as a bit mask. Also, actions are removed from Feature_res in
/// all subsequent versions (>= OF 1.1). Finally, a sequence of ports is present
/// in the trailer of message.
///
/// \remark Defined in [OpenFlow v1.3, p52-53](http://...)
struct Feature_res : Payload_base<FEATURE_RES>
{
  /// Capabilities supported by the datapath represented as a bitmap.
  enum Capability_type : uint32_t {
    FLOW_STATS   = 0x00000001, ///< Flow statistics supported
    TABLE_STATS  = 0x00000002, ///< Table statistics supported
    PORT_STATS   = 0x00000004, ///< Port statistics supported
    GROUP_STATS  = 0x00000008, ///< Group statistics supported
    IP_REASM     = 0x00000020, ///< Can reassemble IP fragments
    QUEUE_STATS  = 0x00000040, ///< Queue statistics supported
    PORT_BLOCKED = 0x00000100  ///< Switch will block looping ports
  };

  Feature_res() = default;
  Feature_res(uint64_t did, uint32_t nb, uint8_t nt, uint8_t aid,
              Capability_type c, uint32_t r)
    : datapath_id(did), n_buffers(nb), n_tbls(nt), aux_id(aid),
      capabilities(c), reserved(r) { }

  uint64_t datapath_id;
  uint32_t n_buffers;
  uint8_t n_tbls;
  uint8_t aux_id;
  Capability_type capabilities;
  uint32_t reserved;
};

/// Returns true when the messages compare equal.
///
/// \relates Feature_res
bool operator==(const Feature_res& a, const Feature_res& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Feature_res
bool operator!=(const Feature_res& a, const Feature_res& b);

/// Returns the number of bytes needed to represent a particular Feature_res
/// message.
///
/// \relates Feature_res
constexpr std::size_t bytes(const Feature_res&);

/// Validates the value of a Feature_res::Capability_type object.
///
/// \relates Feature_res
Error_condition is_valid(const Feature_res::Capability_type& c);

/// Validates the value of a Feature_res message.
///
/// \relates Feature_res
Error_condition is_valid(const Feature_res& fr);

/// Writes a Feature_res value to a Buffer_view.
///
/// \relates Feature_res
Error_condition to_buffer(Buffer_view&, const Feature_res&);

/// Reads a Feature_res value from a Buffer_view.
///
/// \relates Feature_res
Error_condition from_buffer(Buffer_view&, Feature_res&);

/// Returns a string representation of a Feature_res::Capability_type value.
///
/// \relates Feature_res
std::string to_string(const Feature_res::Capability_type);

/// Returns a formatted string representation of a Feature_res message.
///
/// \relates Feature_res
std::string to_string(const Feature_res&, Formatter&);

/// Returns true if the Feature_res::FLOW_STATS flag is set.
///
/// \relates Feature_res
bool feature_res_capabilities_flow_stats(uint32_t c);

/// Returns true if the Feature_res::TABLE_STATS flag is set.
///
/// \relates Feature_res
bool feature_res_capabilities_table_stats(uint32_t c);

/// Returns true if the Feature_res::PORT_STATS flag is set.
///
/// \relates Feature_res
bool feature_res_capabilities_port_stats(uint32_t c);

/// Returns true if the Feature_res::GROUP_STATS flag is set.
///
/// \relates Feature_res
bool feature_res_capabilities_group_stats(uint32_t c);

/// Returns true if the Feature_res::IP_REASM flag is set.
///
/// \relates Feature_res
bool feature_res_capabilities_ip_reasm(uint32_t c);

/// Returns true if the Feature_res::QUEUE_STATS flag is set.
///
/// \relates Feature_res
bool feature_res_capabilities_queue_stats(uint32_t c);

/// Returns true if the Feature_res::PORT_BLOCKED flag is set.
///
/// \relates Feature_res
bool feature_res_capabilities_port_blocked(uint32_t c);

// -------------------------------------------------------------------------- //
// Get Config Request

/// One of the messages is used to query and set the fragmentation handling
/// properties of the packet processing pipeline. Determines if packets that are
/// fragmented are: matched as-is, dropped, reassembled and matched, etc.
/// Additionally, this message helps determine how much of packet will be shared
/// with the controller. Get_config_req is an acknowledged message
/// (Get_config_res) and is only initiated by the controller. The controller may
/// alter this state with a Set_config message. Set_config can only be initiated
/// by the controller, and is unacknowledged.
/// 
/// \remark Defined in [OpenFlow v1.3, p53](http://...)
struct Get_config_req : Payload_base<GET_CONFIG_REQ> { };

// -------------------------------------------------------------------------- //
// Config Message Base

/// Provides common functions and fields used by both Get_config_res and
/// Set_config.
template<Message_type T>
  struct Config_message_base
  {
    /// Describes the handling of IP fragments.
    enum Flags : uint16_t {
      FRAG_NORMAL = 0x0000, ///< No special handling for fragments
      FRAG_DROP   = 0x0001, ///< Drop fragments
      /// Reassemble if Feature_res::Capability_type::IP_REASM set
      FRAG_REASM  = 0x0002,
      FRAG_MASK   = 0x0003
    };

    Config_message_base() = default;
    Config_message_base(Flags f, uint16_t msl)
      : flags(f), miss_send_len(msl) { }

    Flags flags;
    uint16_t miss_send_len;
  };

/// \relates Config_message_base
template<Message_type T>
  bool
  operator==(const Config_message_base<T>& a, const Config_message_base<T>& b);

/// \relates Config_message_base
template<Message_type T>
  bool
  operator!=(const Config_message_base<T>& a, const Config_message_base<T>& b);

/// \relates Config_message_base
template<Message_type T>
  constexpr std::size_t bytes(const Config_message_base<T>&);

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
  bool config_frag_normal(typename Config_message_base<T>::Flags ft);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_drop(typename Config_message_base<T>::Flags ft);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_reasm(typename Config_message_base<T>::Flags ft);

/// \relates Config_message_base
template<Message_type T>
  bool config_frag_mask(typename Config_message_base<T>::Flags ft);

// -------------------------------------------------------------------------- //
// Get Config Response

/// One of the messages is used to query and set the fragmentation handling
/// properties of the packet processing pipeline. Determines if packets that are
/// fragmented are: matched as-is, dropped, reassembled and matched, etc.
/// Additionally, this message helps determine how much of packet will be shared
/// with the controller. Get_config_req is an acknowledged message
/// (Get_config_res) and is only initiated by the controller. The controller may
/// alter this state with a Set_config message. Set_config can only be initiated
/// by the controller, and is unacknowledged.
/// 
/// See Config_message_base
/// 
/// \remark Defined in [OpenFlow v1.3, p53](http://...)
struct Get_config_res : Config_message_base<GET_CONFIG_RES> { };

/// Returns a formatted string representation of a Get_config_res message.
///
/// \relates Get_config_res
std::string to_string(const Get_config_res&, Formatter&);

// -------------------------------------------------------------------------- //
// Set Config

/// One of the messages is used to query and set the fragmentation handling
/// properties of the packet processing pipeline. Determines if packets that are
/// fragmented are: matched as-is, dropped, reassembled and matched, etc.
/// Additionally, this message helps determine how much of packet will be shared
/// with the controller. Get_config_req is an acknowledged message
/// (Get_config_res) and is only initiated by the controller. The controller may
/// alter this state with a Set_config message. Set_config can only be initiated
/// by the controller, and is unacknowledged.
/// 
/// See Config_message_base
/// 
/// \remark Defined in [OpenFlow v1.3, p53](http://...)
struct Set_config : Config_message_base<SET_CONFIG> { };

/// Returns a formatted string representation of a Set_config message.
///
/// \relates Set_config
std::string to_string(const Set_config&, Formatter&);

// -------------------------------------------------------------------------- //
// Packet In

/// The PacketIin message is one way the switch sends a captured packet to the
/// controller. There are two reasons why this might happen; there could be an
/// explicit action as a result of a match asking for this behavior, they could
/// be a miss in the match tables, or a TTL error.
/// 
/// \remark Defined in [OpenFlow v1.3, pp. 76-77](http://...)
struct Packet_in : Payload_base<PACKET_IN>
{
  /// Indicates the reason a packet was forwarded to the controller.
  enum Reason_type : uint8_t {
    NO_MATCH    = 0x00, ///< No matching flow
    ACTION      = 0x01, ///< Action explicitly output to controller
    INVALID_TTL = 0x02  ///< Packet has invalid ttl
  };

  Packet_in() = default;
  Packet_in(uint32_t bid, uint16_t tl, Reason_type r, uint8_t tid,
            uint64_t c, Match m, Buffer b)
    : buffer_id(bid), total_len(tl), reason(r), tbl_id(tid), cookie(c),
      match(m), data(b) { }

  uint32_t buffer_id;
  uint16_t total_len;
  Reason_type reason;
  uint8_t tbl_id;
  uint64_t cookie;
  Match match;
  Buffer data;
};

/// Returns true when the messages compare equal.
///
/// \relates Packet_in
bool operator==(const Packet_in& a, const Packet_in& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Packet_in
bool operator!=(const Packet_in& a, const Packet_in& b);

/// Returns the number of bytes needed to represent a Packet_in message.
///
/// \relates Packet_in
std::size_t bytes(const Packet_in& pi);

/// Validates the value of a Packet_in::Reason_type object.
///
/// \relates Packet_in
Error_condition is_valid(const Packet_in::Reason_type r);

/// Validates the value of a Packet_in message.
///
/// \relates Packet_in
Error_condition is_valid(const Packet_in& p);

/// Writes a Packet_in value to a Buffer_view.
///
/// \relates Packet_in
Error_condition to_buffer(Buffer_view&, const Packet_in&);

/// Reads a Packet_in value from a Buffer_view.
///
/// \relates Packet_in
Error_condition from_buffer(Buffer_view&, Packet_in&);

/// Returns a string representation of a Packet_in::Reason_type.
///
/// \relates Packet_in
std::string to_string(Packet_in::Reason_type);

/// Returns a formatted string representation of a Packet_in message.
///
/// \relates Packet_in
std::string to_string(const Packet_in&, Formatter&);

// -------------------------------------------------------------------------- //
// Flow Removed

/// A Flow_removed message is sent to the controller by the switch when a flow
/// entry in a flow table is removed. It happens when a timeout occurs, either
/// due to inactivity or hard timeout. An idle timeout happens when no packets
/// are matched in a period of time. A hard timeout happens when a certain
/// period of time elapses, regardless of the number of matching packets.
/// Whether the switch sends a Flow_removed message after a timeout is specified
/// by the Flow_mod. Flow entry removal with a Flow_mod message from the
/// controller can also lead to a Flow_removed message.
/// 
/// \remark Defined in [OpenFlow v1.3, pp. 77-78](http://...)
struct Flow_removed : Payload_base<FLOW_REMOVED>
{
  /// Indicates the reason a flow was removed.
  enum Reason_type : uint8_t {
    IDLE_TIMEOUT = 0x00, ///< Flow idle timeout exceeded
    HARD_TIMEOUT = 0x01, ///< Hard timeout exceeded
    DELETE       = 0x02, ///< Evicted by a Flow_mod::Command::DELETE
    GROUP_DELETE = 0x03  ///< Group was removed
  };

  Flow_removed() = default;
  Flow_removed(uint64_t c, uint16_t p, Reason_type r, uint8_t tid,
               uint32_t ds, uint32_t dn, uint16_t it, uint16_t ht,
               uint64_t pc, uint64_t bc, Match m)
    : cookie(c), priority(p), reason(r), table_id(tid), duration_sec(ds),
      duration_nsec(dn), idle_timeout(it), hard_timeout(ht),
      packet_count(pc), byte_count(bc), match(m) { }
  
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

/// Returns true when the messages compare equal.
///
/// \relates Flow_removed
bool operator==(const Flow_removed& a, const Flow_removed& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Flow_removed
bool operator!=(const Flow_removed& a, const Flow_removed& b);

/// Returns the number of bytes needed to represent a Flow_mod message.
///
/// \relates Flow_removed
std::size_t bytes(const Flow_removed& pi);

/// Validates the value of a Flow_removed::Reason_type object.
///
/// \relates Flow_removed
Error_condition is_valid(const Flow_removed::Reason_type r);

/// Validates the value of a Flow_removed message.
///
/// \relates Flow_removed
Error_condition is_valid(const Flow_removed& p);

/// Writes a Flow_removed value to a Buffer_view.
///
/// \relates Flow_removed
Error_condition to_buffer(Buffer_view&, const Flow_removed&);

/// Reads a Flow_removed value from a Buffer_view.
///
/// \relates Flow_removed
Error_condition from_buffer(Buffer_view&, Flow_removed&);

/// Returns a string representation of a Flow_removed::Reason_type value.
///
/// \relates Flow_removed
std::string to_string(Flow_removed::Reason_type);

/// Returns a formatted string representation of a Flow_removed message.
///
/// \relates Flow_removed
std::string to_string(const Flow_removed&, Formatter&);

// -------------------------------------------------------------------------- //
// Port Status

/// These messages convey asynchronous events from the switch to the
/// controller indicating a change of status for the indicated port.
/// 
/// \remark Defined in [OpenFlow v1.3, p78-79](http://...)
struct Port_status : Payload_base<PORT_STATUS>
{
  /// Indicates what about the physical ports have changed.
  enum Reason_type : uint8_t {
    ADD    = 0x00, ///< The port was added
    DELETE = 0x01, ///< The port was removed
    MODIFY = 0x02  ///< Some attribute of the port was changed
  };

  Port_status() = default;
  Port_status(Reason_type r, Port p) : reason(r), port(p) { }

  Reason_type reason;
  Port port;
};

/// Returns true when the messages compare equal.
///
/// \relates Port_status
bool operator==(const Port_status& a, const Port_status& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Port_status
bool operator!=(const Port_status& a, const Port_status& b);

/// Returns the number of bytes needed to represent a Flow_mod message.
///
/// \relates Port_status
std::size_t bytes(const Port_status& ps);

/// Validates the value of a Port_status::Reason_type object.
///
/// \relates Port_status
Error_condition is_valid(const Port_status::Reason_type r);

/// Validates the value of a Port_status message.
///
/// \relates Port_status
Error_condition is_valid(const Port_status& p);

/// Writes a Port_status value to a Buffer_view.
///
/// \relates Port_status
Error_condition to_buffer(Buffer_view&, const Port_status&);

/// Reads a Port_status value from a Buffer_view.
///
/// \relates Port_status
Error_condition from_buffer(Buffer_view&, Port_status&);

/// Returns a string representation of a Port_status::Reason_type.
///
/// \relates Port_status
std::string to_string(Port_status::Reason_type);

/// Returns a formatted string representation of a Port_status message.
///
/// \relates Port_status
std::string to_string(const Port_status&, Formatter&);

// -------------------------------------------------------------------------- //
// Packet Out

/// The Controller sends packets to the switch using a Packet_out message. The
/// message either contains the packet or the buffer ID of the packet in the
/// switch. The message includes the list of actions that need to be executed in
/// order. An empty action list means the packet will be dropped.
/// 
/// \remark Defined in [OpenFlow v1.3, p74](http://...)
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

/// Returns true when the messages compare equal.
///
/// \relates Packet_out
bool operator==(const Packet_out& a, const Packet_out& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Packet_out
bool operator!=(const Packet_out& a, const Packet_out& b);

/// Returns the number of bytes needed to represent a Packet_out message.
///
/// \relates Packet_out
std::size_t bytes(const Packet_out& po);

/// Validates the value of a Packet_out message.
///
/// \relates Packet_out
Error_condition is_valid(const Packet_out& p);

/// Writes a Packet_out value to a Buffer_view.
///
/// \relates Packet_out
Error_condition to_buffer(Buffer_view&, const Packet_out&);

/// Reads a Packet_out value from a Buffer_view.
///
/// \relates Packet_out
Error_condition from_buffer(Buffer_view&, Packet_out&);

/// Returns a formatted string representation of a Packet_out message.
///
/// \relates Packet_out
std::string to_string(const Packet_out&, Formatter&);

// -------------------------------------------------------------------------- //
// Flow_mod

/// Sent by the controller to modify the state of an OpenFlow switch. This is 
/// one of the main messages, it allows the controller to modify the
/// state of an OpenFlow switch.
/// 
/// \remark Defined in [OpenFlow v1.3, pp. 54-56](http://...)
struct Flow_mod : Payload_base<FLOW_MOD>
{
  enum Command : uint8_t {
    ADD = 0x00, MODIFY = 0x01, MODIFY_STRICT = 0x02, DELETE = 0x03,
    DELETE_STRICT = 0x04
  };

  enum Flags : uint16_t {
    SEND_FLOW_REM = 0x0001, CHECK_OVERLAP = 0x0002, RESET_COUNTS = 0x0004,
    NO_PACKET_COUNTS = 0x0008, NO_BYTE_COUNTS = 0x0010
  };

  Flow_mod() = default;
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
std::size_t bytes(const Flow_mod& fm);

/// Validates the value of a Flow_mod::Command object.
///
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod::Command t);

/// Validates the value of an table_id with respect to a Flow_mod::Command
/// object.
///
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod::Command c, const uint8_t table_id);

/// Validates the value of a Flow_mod::Flags object.
///
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod::Flags t);

/// Validates the value of a Flow_mod message.
///
/// \relates Flow_mod
Error_condition is_valid(const Flow_mod& f);

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
// Group Mod

/// The controller uses GroupMod messages to modify group tables.
/// 
/// \remark Defined in [OpenFlow v1.3, p56-57](http://...)
struct Group_mod : Payload_base<GROUP_MOD>
{
  /// Group commands
  enum Command : uint16_t {
    ADD    = 0x0000, ///< New group
    MODIFY = 0x0001, ///< Modify all matching groups
    DELETE = 0x0002  ///< Delete all matching groups
  };

  /// Group types. Values in the range [128, 255] are reserved for experimental
  /// use.
  enum Type : uint8_t {
    ALL      = 0x00, ///< Multicast or broadcast group
    SELECT   = 0x01, ///< Select group
    INDIRECT = 0x02, ///< Indirect group
    FF       = 0x03  ///< Fast failover group
  };

  Group_mod() = default;
  Group_mod(Command c, Type t, uint32_t gid,
            const Sequence<Bucket>& b)
    : command(c), type(t), group_id(gid), buckets(b) { }

  Command command;
  Type type;
  uint32_t group_id;
  Sequence<Bucket> buckets;
};

/// Returns true when the messages compare equal.
///
/// \relates Group_mod
bool operator==(const Group_mod& a, const Group_mod& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Group_mod
bool operator!=(const Group_mod& a, const Group_mod& b);

/// Returns the number of bytes needed to represent a Group_mod message.
///
/// \relates Group_mod
std::size_t bytes(const Group_mod& gm);

/// Validates the value of a Group_mod::Command object.
///
/// \relates Group_mod
Error_condition is_valid(const Group_mod::Command c);

/// Validates the value of a Group_mod::Type object.
///
/// \relates Group_mod
Error_condition is_valid(const Group_mod::Type v);

/// Validates the value of a Group_mod message.
///
/// \relates Group_mod
Error_condition is_valid(const Group_mod& gm);

/// Writes a Group_mod value to a Buffer_view.
///
/// \relates Group_mod
Error_condition to_buffer(Buffer_view&, const Group_mod&);

/// Reads a Group_mod value from a Buffer_view.
///
/// \relates Group_mod
Error_condition from_buffer(Buffer_view&, Group_mod&);

/// Returns a string representation of a Group_mod::Command value.
///
/// \relates Group_mod
std::string to_string(Group_mod::Command);

/// Returns a string representation of a Group_mod::Type value.
///
/// \relates Group_mod
std::string to_string(Group_mod::Type);

/// Returns a formatted string representation of a Group_mod message.
///
/// \relates Group_mod
std::string to_string(const Group_mod&, Formatter&);

// -------------------------------------------------------------------------- //
// Port Mod

/// This sequence is how the controller can modify the state of an OpenFlow
/// port.
/// 
/// \remark Defined in [OpenFlow v1.3, p57-58](http://...)
struct Port_mod : Payload_base<PORT_MOD>
{
  /// Port configuration flags
  enum Config_type : uint32_t {
    PORT_DOWN    = 0x00000001, ///< Port is administratively down
    NO_RECV      = 0x00000004, ///< Drop most packets received on port
    NO_FWD       = 0x00000020, ///< Drop packets forwarded to port
    NO_PACKET_IN = 0x00000040  ///< Do not send Packet_in messages for port
  };

  /// see Port::Features_value
  enum Features_type : uint32_t {
    TEN_MB_HD     = 0x00000001, ///< 10Mb half-duplex rate support
    TEN_MB_FD     = 0x00000002, ///< 10Mb full-duplex rate support
    HUNDRED_MB_HD = 0x00000004, ///< 100Mb half-duplex rate support
    HUNDRED_MB_FD = 0x00000008, ///< 100Mb full-duplex rate support
    ONE_GB_HD     = 0x00000010, ///< 1Gb half-duplex rate support
    ONE_GB_FD     = 0x00000020, ///< 1Gb full-duplex rate support
    TEN_GB_FD     = 0x00000040, ///< 10Gb full-duplex rate support
    FORTY_GB_FD   = 0x00000080, ///< 40Gb full-duplex rate support
    HUNDRED_GB_FD = 0x00000100, ///< 100Gb full-duplex rate support
    ONE_TB_FD     = 0x00000200, ///< 1Tb full-duplex rate support
    OTHER         = 0x00000400, ///< Other rate, not in the list
    COPPER        = 0x00000800, ///< Copper medium
    FIBER         = 0x00001000, ///< Fiber medium
    AUTO_NEG      = 0x00002000, ///< Auto-negotiation
    PAUSE         = 0x00004000, ///< Pause
    PAUSE_ASYM    = 0x00008000  ///< Asymmetric pause
  };

  Port_mod() = default;
  Port_mod(uint32_t p, Ethernet_addr ha, Config_type c, uint32_t m,
           Features_type a)
    : port(p), hw_addr(ha), config(c), mask(m), advertise(a) { };

  // - Packet data
  uint32_t port;
  Ethernet_addr hw_addr;
  Config_type config;
  uint32_t mask;
  Features_type advertise;
};

/// Returns true when the messages compare equal.
///
/// \relates Port_mod
bool operator==(const Port_mod& a, const Port_mod& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Port_mod
bool operator!=(const Port_mod& a, const Port_mod& b);

/// Returns the number of bytes needed to represent a Port_mod message.
///
/// \relates Port_mod
constexpr std::size_t bytes(const Port_mod&);

/// Validates the value of a Port_mod message.
///
/// \relates Port_mod
constexpr Error_condition is_valid(const Port_mod& p);

/// Writes a Port_mod value to a Buffer_view.
///
/// \relates Port_mod
Error_condition to_buffer(Buffer_view&, const Port_mod&);

/// Reads a Port_mod value from a Buffer_view.
///
/// \relates Port_mod
Error_condition from_buffer(Buffer_view&, Port_mod&);

/// Returns a string representation of a Port_mod::Config_type.
///
/// \relates Port_mod
std::string to_string(const Port_mod::Config_type);

/// Returns a string representation of a Port_mod::Features_type.
///
/// \relates Port_mod
std::string to_string(const Port_mod::Features_type);

/// Returns a formatted string representation of a Port_mod message.
///
/// \relates Port_mod
std::string to_string(const Port_mod&, Formatter&);

/// Returns true if Port_mod::Config_type::PORT_DOWN is set
///
/// \relates Port_mod
bool port_mod_config_port_down(uint32_t c);

/// Returns true if Port_mod::Config_type::NO_RECV is set
///
/// \relates Port_mod
bool port_mod_config_no_recv(uint32_t c);

/// Returns true if Port_mod::Config_type::NO_FWD is set
///
/// \relates Port_mod
bool port_mod_config_no_fwd(uint32_t c);

/// Returns true if Port_mod::Config_type::NO_PACKET_IN is set
///
/// \relates Port_mod
bool port_mod_config_no_packet_in(uint32_t c);

/// Returns true if Port_mod::Features_type::TEN_MB_HD is set
///
/// \relates Port_mod
bool port_mod_features_10mb_hd(uint32_t f);

/// Returns true if Port_mod::Features_type::TEN_MB_FD is set
///
/// \relates Port_mod
bool port_mod_features_10mb_fd(uint32_t f);

/// Returns true if Port_mod::Features_type::HUNDRED_MB_HD is set
///
/// \relates Port_mod
bool port_mod_features_100mb_hd(uint32_t f);

/// Returns true if Port_mod::Features_type::HUNDRED_MB_FD is set
///
/// \relates Port_mod
bool port_mod_features_100mb_fd(uint32_t f);

/// Returns true if Port_mod::Features_type::ONE_GB_HD is set
///
/// \relates Port_mod
bool port_mod_features_1gb_hd(uint32_t f);

/// Returns true if Port_mod::Features_type::ONE_GB_FD is set
///
/// \relates Port_mod
bool port_mod_features_1gb_fd(uint32_t f);

/// Returns true if Port_mod::Features_type::TEN_GB_FD is set
///
/// \relates Port_mod
bool port_mod_features_10gb_fd(uint32_t f);

/// Returns true if Port_mod::Features_type::FORTY_GB_FD is set
///
/// \relates Port_mod
bool port_mod_features_40gb_fd(uint32_t f);

/// Returns true if Port_mod::Features_type::HUNDRED_GB_FD is set
///
/// \relates Port_mod
bool port_mod_features_100gb_fd(uint32_t f);

/// Returns true if Port_mod::Features_type::ONE_TB_FD is set
///
/// \relates Port_mod
bool port_mod_features_1tb_fd(uint32_t f);

/// Returns true if Port_mod::Features_type::OTHER is set
///
/// \relates Port_mod
bool port_mod_features_other(uint32_t f);

/// Returns true if Port_mod::Features_type::COPPER is set
///
/// \relates Port_mod
bool port_mod_features_copper(uint32_t f);

/// Returns true if Port_mod::Features_type::FIBER is set
///
/// \relates Port_mod
bool port_mod_features_fiber(uint32_t f);

/// Returns true if Port_mod::Features_type::AUTO_NEG is set
///
/// \relates Port_mod
bool port_mod_features_auto_neg(uint32_t f);

/// Returns true if Port_mod::Features_type::PAUSE is set
///
/// \relates Port_mod
bool port_mod_features_pause(uint32_t f);

/// Returns true if Port_mod::Features_type::PAUSE_ASYM is set
///
/// \relates Port_mod
bool port_mod_features_pause_asym(uint32_t f);

// -------------------------------------------------------------------------- //
// Table Mod

/// This message is used to determine a packet's fate when it misses in the
/// table. It can be forwarded to the controller, dropped, or sent to the next
/// table.
/// 
/// \remark Defined in [OpenFlow v1.3, p53-54](http://...)
struct Table_mod : Payload_base<TABLE_MOD>
{
  /// This type is deprecated
  enum Config_type : uint32_t {
    MISS_CONTROLLER = 0x00000000, MISS_CONTINUE = 0x00000001,
    MISS_DROP = 0x00000002, MISS_MASK = 0x00000003
  };

  /// Table numbering
  enum Table_IDs : uint8_t {
    TID_MAX = 0xfe, ///< Last usable table id
    /// Wildcard table used for table config, flow stats, and flow deletes
    TID_ALL = 0xff
  };

  Table_mod() = default;
  Table_mod(Table_IDs tid, Config_type ct) : table_id(tid), config(ct) { }

  Table_IDs table_id;
  Config_type config; ///< This field is deprecated
};

/// Returns true when the messages compare equal.
///
/// \relates Table_mod
bool operator==(const Table_mod& a, const Table_mod& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Table_mod
bool operator!=(const Table_mod& a, const Table_mod& b);

/// Returns the number of bytes needed to represent a Table_mod message.
///
/// \relates Table_mod
constexpr std::size_t bytes(const Table_mod&);

/// Validates the value of a Table_mod::Config_type object.
///
/// \relates Table_mod
Error_condition is_valid(const Table_mod::Config_type c);

/// Validates the value of a Table_mod message.
///
/// \relates Table_mod
Error_condition is_valid(const Table_mod tm);

/// Writes a Table_mod value to a Buffer_view.
///
/// \relates Table_mod
Error_condition to_buffer(Buffer_view&, const Table_mod&);

/// Reads a Table_mod value from a Buffer_view.
///
/// \relates Table_mod
Error_condition from_buffer(Buffer_view&, Table_mod&);

/// Returns a string representation of a Table_mod::Config_type.
///
/// \relates Table_mod
std::string to_string(const Table_mod::Config_type);

/// Returns a string representation of a Table_mod::TableIDs.
///
/// \relates Table_mod
std::string to_string(const Table_mod::Table_IDs);

/// Returns a formatted string representation of a Table_mod message.
///
/// \relates Table_mod
std::string to_string(const Table_mod&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart type

/// The Multipart_type enumeration describes the types of requests and
/// responses for statistics.
enum Multipart_type : uint16_t
{
  MULTIPART_DESC           = 0x0000, ///< Description of this OpenFlow switch
  MULTIPART_FLOW           = 0x0001, ///< Individual flow statistics
  MULTIPART_AGGREGATE      = 0x0002, ///< Aggregate flow statistics
  MULTIPART_TABLE          = 0x0003, ///< Flow table statistics
  MULTIPART_PORT           = 0x0004, ///< Port statistics
  MULTIPART_QUEUE          = 0x0005, ///< Queue statistics for a port
  MULTIPART_GROUP          = 0x0006, ///< Group counter statistics
  MULTIPART_GROUP_DESC     = 0x0007, ///< Group description
  MULTIPART_GROUP_FEATURES = 0x0008, ///< Group features
  MULTIPART_METER          = 0x0009, ///< Meter statistics
  MULTIPART_METER_CONFIG   = 0x000a, ///< Meter configuration
  MULTIPART_METER_FEATURES = 0x000b, ///< Meter features
  MULTIPART_TABLE_FEATURES = 0x000c, ///< Table features
  MULTIPART_PORT_DESC      = 0x000d, ///< Port description
  MULTIPART_EXPERIMENTER   = 0xffff  ///< Experimenter extension
};

/// Returns true when t is a valid multipart kind.
///
/// \relates Multipart_type
constexpr Error_condition is_valid(const Multipart_type t);

/// Returns a string representation of an Multipart_type value.
///
/// \relates Multipart_type
std::string to_string(const Multipart_type& h,  Formatter&);

// Payload base
template<Multipart_type K>
  using Multipart_payload_base = Basic_payload_base<Multipart_type, K>;

// -------------------------------------------------------------------------- //
// Multipart Request: Desc

struct Multipart_req_desc : Multipart_payload_base<MULTIPART_DESC> { };

// -------------------------------------------------------------------------- //
// Multipart Request Flow Base

/// The Multipart_req_flow_base provides common facilities for multipart
/// requests for single (flow) or multiple (aggregate) flows.
template<Multipart_type K>
  struct Multipart_req_flow_base : Multipart_payload_base<K>
  {
    Multipart_req_flow_base() = default;
    Multipart_req_flow_base(uint8_t tid, uint32_t op, uint32_t og, uint64_t c,
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

/// \relates Multipart_req_flow_base
template<Multipart_type K>
  bool
  operator==(const Multipart_req_flow_base<K>& a, const Multipart_req_flow_base<K>& b);

/// \relates Multipart_req_flow_base
template<Multipart_type K>
  bool
  operator!=(const Multipart_req_flow_base<K>& a, const Multipart_req_flow_base<K>& b);

/// \relates Multipart_req_flow_base
template<Multipart_type K>
  std::size_t bytes(const Multipart_req_flow_base<K>& f);

/// \relates Multipart_req_flow_base
template<Multipart_type K>
  Error_condition is_valid(const Multipart_req_flow_base<K>& f);

/// \relates Multipart_req_flow_base
template<Multipart_type K>
  Error_condition to_buffer(Buffer_view& v, const Multipart_req_flow_base<K>& f);

/// \relates Multipart_req_flow_base
template<Multipart_type K>
  Error_condition from_buffer(Buffer_view& v, Multipart_req_flow_base<K>& f);

// -------------------------------------------------------------------------- //
// Multipart Request: Flow

struct Multipart_req_flow : Multipart_req_flow_base<MULTIPART_FLOW> { };

/// \relates Multipart_req_flow
std::string to_string(const Multipart_req_flow&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request Aggregate

struct Multipart_req_aggregate
  : Multipart_req_flow_base<MULTIPART_AGGREGATE> { };

/// \relates Multipart_req_aggregate
std::string to_string(const Multipart_req_aggregate&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Table

struct Multipart_req_table
  : Multipart_payload_base<MULTIPART_TABLE> { };

// -------------------------------------------------------------------------- //
// Multipart Request: Port

struct Multipart_req_port : Multipart_payload_base<MULTIPART_PORT>
{
  Multipart_req_port() = default;
  explicit Multipart_req_port(uint32_t p) : port_no(p) { }

  uint32_t port_no;
};

/// \relates Multipart_req_port
bool operator==(const Multipart_req_port& a, const Multipart_req_port& b);

/// \relates Multipart_req_port
bool operator!=(const Multipart_req_port& a, const Multipart_req_port& b);

/// \relates Multipart_req_port
constexpr std::size_t bytes(const Multipart_req_port&);

/// \relates Multipart_req_port
constexpr Error_condition is_valid(const Multipart_req_port&);

/// \relates Multipart_req_port
Error_condition to_buffer(Buffer_view& v, const Multipart_req_port& p);

/// \relates Multipart_req_port
Error_condition from_buffer(Buffer_view& v, Multipart_req_port& p);

/// \relates Multipart_req_port
std::string to_string(const Multipart_req_port& p,  Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Queue

struct Multipart_req_queue : Multipart_payload_base<MULTIPART_QUEUE>
{
  Multipart_req_queue() = default;
  Multipart_req_queue(uint32_t p, uint32_t q) : port_no(p), queue_id(q) {}

  uint32_t port_no;
  uint32_t queue_id;
};

/// \relates Multipart_req_queue
bool operator==(const Multipart_req_queue& a, const Multipart_req_queue& b);

/// \relates Multipart_req_queue
bool operator!=(const Multipart_req_queue& a, const Multipart_req_queue& b);

/// \relates Multipart_req_queue
constexpr std::size_t bytes(const Multipart_req_queue& q);

/// \relates Multipart_req_queue
constexpr Error_condition is_valid(const Multipart_req_queue& q);

/// \relates Multipart_req_queue
Error_condition to_buffer(Buffer_view& v, const Multipart_req_queue& q);

/// \relates Multipart_req_queue
Error_condition from_buffer(Buffer_view& v, Multipart_req_queue& q);

/// \relates Multipart_req_queue
std::string to_string(const Multipart_req_queue& q,  Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Group

struct Multipart_req_group : Multipart_payload_base<MULTIPART_GROUP>
{
  Multipart_req_group() = default;
  explicit Multipart_req_group(uint32_t gid) : group_id(gid) { }

  uint32_t group_id;
};

/// \relates Multipart_req_group
bool operator==(const Multipart_req_group& a, const Multipart_req_group& b);

/// \relates Multipart_req_group
bool operator!=(const Multipart_req_group& a, const Multipart_req_group& b);

/// \relates Multipart_req_group
constexpr std::size_t bytes(const Multipart_req_group&);

/// \relates Multipart_req_group
constexpr Error_condition is_valid(const Multipart_req_group&);

/// \relates Multipart_req_group
Error_condition to_buffer(Buffer_view& v, const Multipart_req_group&);

/// \relates Multipart_req_group
Error_condition from_buffer(Buffer_view& v, Multipart_req_group&);

/// \relates Multipart_req_group
std::string to_string(const Multipart_req_group&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Group desc

struct Multipart_req_group_desc
  : Multipart_payload_base<MULTIPART_GROUP_DESC> { };

// -------------------------------------------------------------------------- //
// Multipart Request: Group features

struct Multipart_req_group_features
  : Multipart_payload_base<MULTIPART_GROUP_FEATURES> { };

// -------------------------------------------------------------------------- //
// Multipart Request: Meter base

template <Multipart_type K>
  struct Multipart_req_meter_base : Multipart_payload_base<K>
  {
    Multipart_req_meter_base() = default;
    explicit Multipart_req_meter_base(uint32_t mid) : meter_id(mid) { }

    uint32_t meter_id;
  };

/// \relates Multipart_req_meter_base
template <Multipart_type K>
  bool operator==(const Multipart_req_meter_base<K>& a,
                  const Multipart_req_meter_base<K>& b);

/// \relates Multipart_req_meter_base
template <Multipart_type K>
  bool operator!=(const Multipart_req_meter_base<K>& a,
                  const Multipart_req_meter_base<K>& b);

/// \relates Multipart_req_meter_base
template <Multipart_type K>
  constexpr std::size_t bytes(const Multipart_req_meter_base<K>&);

/// \relates Multipart_req_meter_base
template <Multipart_type K>
  constexpr Error_condition is_valid(const Multipart_req_meter_base<K>&);

/// \relates Multipart_req_meter_base
template <Multipart_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Multipart_req_meter_base<K>& mb);

/// \relates Multipart_req_meter_base
template <Multipart_type K>
  Error_condition
  from_buffer(Buffer_view& v, Multipart_req_meter_base<K>& mb);

// -------------------------------------------------------------------------- //
// Multipart Request: Meter

struct Multipart_req_meter : Multipart_req_meter_base<MULTIPART_METER> { };

/// \relates Multipart_req_meter
std::string to_string(const Multipart_req_meter&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Meter config

struct Multipart_req_meter_config
  : Multipart_req_meter_base<MULTIPART_METER_CONFIG> { };

/// \relates Multipart_req_meter_config
std::string to_string(const Multipart_req_meter_config&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Meter features

struct Multipart_req_meter_features
  : Multipart_payload_base<MULTIPART_METER_FEATURES> { };

// -------------------------------------------------------------------------- //
// Multipart Request: Table feature property type

/// \relates Table_features_property_header
enum Table_feature_property_type : uint16_t
{
  TABLE_FEATURE_PROPERTY_INSTRUCTIONS        = 0,
  TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS   = 1,
  TABLE_FEATURE_PROPERTY_NEXT_TABLES         = 2,
  TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS    = 3,
  TABLE_FEATURE_PROPERTY_WRITE_ACTIONS       = 4,
  TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS  = 5,
  TABLE_FEATURE_PROPERTY_APPLY_ACTIONS       = 6,
  TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS  = 7,
  TABLE_FEATURE_PROPERTY_MATCH               = 8,
  TABLE_FEATURE_PROPERTY_WILDCARDS           = 10,
  TABLE_FEATURE_PROPERTY_WRITE_SETFIELD      = 12,
  TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS = 13,
  TABLE_FEATURE_PROPERTY_APPLY_SETFIELD      = 14,
  TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS = 15,
  TABLE_FEATURE_PROPERTY_EXPERIMENTER        = 0xfffe,
  TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS   = 0xffff,
};

/// \relates Table_features_property_header
Error_condition is_valid(const Table_feature_property_type tfpt);

/// \relates Table_features_property_header
std::string to_string(Table_feature_property_type tfpt);

template<Table_feature_property_type K>
  using Table_feature_property_payload_base
      = Basic_payload_base<Table_feature_property_type, K>;

// -------------------------------------------------------------------------- //
// Table feature property: instructions base

template<Table_feature_property_type K>
  struct Table_feature_property_instructions_base
    : Table_feature_property_payload_base<K>
  {
    Table_feature_property_instructions_base() = default;
    explicit Table_feature_property_instructions_base
       (Sequence<Instruction_header> i)
      : instructions(i) { }

    Sequence<Instruction_header> instructions;
  };

/// \relates Table_feature_property_instructions_base
template<Table_feature_property_type K>
  bool operator==(const Table_feature_property_instructions_base<K>& a,
                  const Table_feature_property_instructions_base<K>& b);

/// \relates Table_feature_property_instructions_base
template<Table_feature_property_type K>
  bool operator!=(const Table_feature_property_instructions_base<K>& a,
                  const Table_feature_property_instructions_base<K>& b);

/// \relates Table_feature_property_instructions_base
template<Table_feature_property_type K>
  std::size_t bytes(const Table_feature_property_instructions_base<K>& ib);

/// \relates Table_feature_property_instructions_base
template<Table_feature_property_type K>
  Error_condition is_valid(const Table_feature_property_instructions_base<K>& ib);

/// \relates Table_feature_property_instructions_base
template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_instructions_base<K>& ib);

/// \relates Table_feature_property_instructions_base
template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_instructions_base<K>& ib);

// -------------------------------------------------------------------------- //
// Table feature property: instructions

struct Table_feature_property_instructions 
  : Table_feature_property_instructions_base
      <TABLE_FEATURE_PROPERTY_INSTRUCTIONS>
{ };

/// \relates Table_feature_property_instructions
std::string to_string(const Table_feature_property_instructions&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: instructions miss

struct Table_feature_property_instructions_miss 
  : Table_feature_property_instructions_base
      <TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS>
{ };

/// \relates Table_feature_property_instructions_miss
std::string to_string(const Table_feature_property_instructions_miss&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table id

struct Table_id
{
  uint8_t table;
};

/// \relates Table_id
bool operator==(const Table_id& a, const Table_id& b);

/// \relates Table_id
bool operator!=(const Table_id& a, const Table_id& b);

/// \relates Table_id
constexpr std::size_t bytes(const Table_id&);

/// \relates Table_id
constexpr Error_condition is_valid(const Table_id&);

/// \relates Table_id
Error_condition to_buffer(Buffer_view& v, const Table_id& ti);

/// \relates Table_id
Error_condition from_buffer(Buffer_view& v, Table_id& ti);

/// \relates Table_id
std::string to_string(const Table_id& ti, Formatter& f);

// -------------------------------------------------------------------------- //
// Table feature property: instructions base

template<Table_feature_property_type K>
  struct Table_feature_property_next_tables_base
    : Table_feature_property_payload_base<K>
  {
    Table_feature_property_next_tables_base() = default;
    explicit Table_feature_property_next_tables_base(Sequence<Table_id> nti)
      : next_table_ids(nti) { }

    Sequence<Table_id> next_table_ids;
  };

/// \relates Table_feature_property_next_tables_base
template<Table_feature_property_type K>
  bool operator==(const Table_feature_property_next_tables_base<K>& a,
                  const Table_feature_property_next_tables_base<K>& b);

/// \relates Table_feature_property_next_tables_base
template<Table_feature_property_type K>
  bool operator!=(const Table_feature_property_next_tables_base<K>& a,
                  const Table_feature_property_next_tables_base<K>& b);

/// \relates Table_feature_property_next_tables_base
template<Table_feature_property_type K>
  std::size_t bytes(const Table_feature_property_next_tables_base<K>& ntb);

/// \relates Table_feature_property_next_tables_base
template<Table_feature_property_type K>
  Error_condition is_valid(
                 const Table_feature_property_next_tables_base<K>& ntb);

/// \relates Table_feature_property_next_tables_base
template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_next_tables_base<K>& ntb);

/// \relates Table_feature_property_next_tables_base
template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_next_tables_base<K>& ntb);

// -------------------------------------------------------------------------- //
// Table feature property: next tables

struct Table_feature_property_next_tables
  : Table_feature_property_next_tables_base<TABLE_FEATURE_PROPERTY_NEXT_TABLES>
{ };

/// \relates Table_feature_property_next_tables
std::string to_string(const Table_feature_property_next_tables&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: next tables miss

struct Table_feature_property_next_tables_miss
  : Table_feature_property_next_tables_base
    <TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS>
{ };

/// \relates Table_feature_property_next_tables_miss
std::string to_string(const Table_feature_property_next_tables_miss&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: actions base

template<Table_feature_property_type K>
  struct Table_feature_property_actions_base
    : Table_feature_property_payload_base<K>
  {
    Table_feature_property_actions_base() = default;
    explicit Table_feature_property_actions_base(Sequence<Action_header> a)
      : actions(a) { }

    Sequence<Action_header> actions;
  };

/// \relates Table_feature_property_actions_base
template<Table_feature_property_type K>
  bool operator==(const Table_feature_property_actions_base<K>& a,
                  const Table_feature_property_actions_base<K>& b);

/// \relates Table_feature_property_actions_base
template<Table_feature_property_type K>
  bool operator!=(const Table_feature_property_actions_base<K>& a,
                  const Table_feature_property_actions_base<K>& b);

/// \relates Table_feature_property_actions_base
template<Table_feature_property_type K>
  std::size_t bytes(const Table_feature_property_actions_base<K>& ab);

/// \relates Table_feature_property_actions_base
template<Table_feature_property_type K>
  Error_condition is_valid(const Table_feature_property_actions_base<K>& ab);

/// \relates Table_feature_property_actions_base
template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_actions_base<K>& ab);

/// \relates Table_feature_property_actions_base
template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_actions_base<K>& ab);

// -------------------------------------------------------------------------- //
// Table feature property: write actions

struct Table_feature_property_write_actions
  : Table_feature_property_actions_base<TABLE_FEATURE_PROPERTY_WRITE_ACTIONS>
{ };

/// \relates Table_feature_property_write_actions
std::string to_string(const Table_feature_property_write_actions&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: write actions miss

struct Table_feature_property_write_actions_miss
  : Table_feature_property_actions_base
    <TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS>
{ };

/// \relates Table_feature_property_write_actions_miss
std::string to_string(const Table_feature_property_write_actions_miss&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: apply actions

struct Table_feature_property_apply_actions
  : Table_feature_property_actions_base<TABLE_FEATURE_PROPERTY_APPLY_ACTIONS>
{ };

/// \relates Table_feature_property_apply_actions
std::string to_string(const Table_feature_property_apply_actions&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: apply actions miss

struct Table_feature_property_apply_actions_miss
  : Table_feature_property_actions_base
    <TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS>
{ };

/// \relates Table_feature_property_apply_actions_miss
std::string to_string(const Table_feature_property_apply_actions_miss&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: oxm base

template<Table_feature_property_type K>
  struct Table_feature_property_oxm_base
    : Table_feature_property_payload_base<K>
  {
    Table_feature_property_oxm_base() = default;
    explicit Table_feature_property_oxm_base(Sequence<OXM_entry_header> o)
      : oxms(o) { }

    Sequence<OXM_entry_header> oxms;
  };

/// \relates Table_feature_property_oxm_base
template<Table_feature_property_type K>
  bool operator==(const Table_feature_property_oxm_base<K>& a,
                  const Table_feature_property_oxm_base<K>& b);

/// \relates Table_feature_property_oxm_base
template<Table_feature_property_type K>
  bool operator!=(const Table_feature_property_oxm_base<K>& a,
                  const Table_feature_property_oxm_base<K>& b);

/// \relates Table_feature_property_oxm_base
template<Table_feature_property_type K>
  std::size_t bytes(const Table_feature_property_oxm_base<K>& ob);

/// \relates Table_feature_property_oxm_base
template<Table_feature_property_type K>
  Error_condition is_valid(const Table_feature_property_oxm_base<K>& ob);

/// \relates Table_feature_property_oxm_base
template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_oxm_base<K>& ob);

/// \relates Table_feature_property_oxm_base
template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_oxm_base<K>& ob);

// -------------------------------------------------------------------------- //
// Table feature property: Match

struct Table_feature_property_match
  : Table_feature_property_oxm_base<TABLE_FEATURE_PROPERTY_MATCH>
{ };

/// \relates Table_feature_property_match
std::string to_string(const Table_feature_property_match&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: wildcards

struct Table_feature_property_wildcards
  : Table_feature_property_oxm_base<TABLE_FEATURE_PROPERTY_WILDCARDS>
{ };

/// \relates Table_feature_property_match
std::string to_string(const Table_feature_property_match&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: write setfield

struct Table_feature_property_write_setfield
  : Table_feature_property_oxm_base<TABLE_FEATURE_PROPERTY_WRITE_SETFIELD>
{ };

/// \relates Table_feature_property_write_setfield
std::string to_string(const Table_feature_property_write_setfield&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: write setfield miss

struct Table_feature_property_write_setfield_miss
  : Table_feature_property_oxm_base
     <TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS>
{ };

/// \relates Table_feature_property_write_setfield_miss
std::string to_string(const Table_feature_property_write_setfield_miss&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: apply setfield

struct Table_feature_property_apply_setfield
  : Table_feature_property_oxm_base<TABLE_FEATURE_PROPERTY_APPLY_SETFIELD>
{ };

/// \relates Table_feature_property_apply_setfield
std::string to_string(const Table_feature_property_apply_setfield&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: apply setfield miss

struct Table_feature_property_apply_setfield_miss
  : Table_feature_property_oxm_base
     <TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS>
{ };

/// \relates Table_feature_property_apply_setfield_miss
std::string to_string(const Table_feature_property_apply_setfield_miss&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: experimenter base

template<Table_feature_property_type K>
  struct Table_feature_property_experimenter_base
    : Table_feature_property_payload_base<K>
  {
    Table_feature_property_experimenter_base() = default;
    explicit Table_feature_property_experimenter_base(Greedy_buffer b)
      : data(b) { }

    Greedy_buffer data;
  };

/// \relates Table_feature_property_experimenter_base
template<Table_feature_property_type K>
  bool operator==(const Table_feature_property_experimenter_base<K>& a,
                  const Table_feature_property_experimenter_base<K>& b);

/// \relates Table_feature_property_experimenter_base
template<Table_feature_property_type K>
  bool operator!=(const Table_feature_property_experimenter_base<K>& a,
                  const Table_feature_property_experimenter_base<K>& b);

/// \relates Table_feature_property_experimenter_base
template<Table_feature_property_type K>
  std::size_t bytes(const Table_feature_property_experimenter_base<K>& eb);

/// \relates Table_feature_property_experimenter_base
template<Table_feature_property_type K>
  Error_condition
  is_valid(const Table_feature_property_experimenter_base<K>& eb);

/// \relates Table_feature_property_experimenter_base
template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_experimenter_base<K>& eb);

/// \relates Table_feature_property_experimenter_base
template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_experimenter_base<K>& eb);

// -------------------------------------------------------------------------- //
// Table feature property: experimenter miss

struct Table_feature_property_experimenter
  : Table_feature_property_experimenter_base
     <TABLE_FEATURE_PROPERTY_EXPERIMENTER>
{ };

/// \relates Table_feature_property_experimenter
std::string to_string(const Table_feature_property_experimenter&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property: experimenter miss

struct Table_feature_property_experimenter_miss
  : Table_feature_property_experimenter_base
     <TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS>
{ };

/// \relates Table_feature_property_experimenter_miss
std::string to_string(const Table_feature_property_experimenter_miss&,
                      Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property payload

union Table_feature_property_payload_data
{
  Table_feature_property_payload_data() { }
  ~Table_feature_property_payload_data() { }

  Table_feature_property_instructions        instructions;
  Table_feature_property_instructions_miss   instructions_miss;
  Table_feature_property_next_tables         next_tables;
  Table_feature_property_next_tables_miss    next_tables_miss;
  Table_feature_property_write_actions       write_actions;
  Table_feature_property_write_actions_miss  write_actions_miss;
  Table_feature_property_apply_actions       apply_actions;
  Table_feature_property_apply_actions_miss  apply_actions_miss;
  Table_feature_property_match               match;
  Table_feature_property_wildcards           wildcards;
  Table_feature_property_write_setfield      write_setfield;
  Table_feature_property_write_setfield_miss write_setfield_miss;
  Table_feature_property_apply_setfield      apply_setfield;
  Table_feature_property_apply_setfield_miss apply_setfield_miss;
  Table_feature_property_experimenter        experimenter;
  Table_feature_property_experimenter_miss   experimenter_miss;
};

struct Table_feature_property_payload
{
  using Data = Table_feature_property_payload_data;

  Table_feature_property_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

/// \relates Table_feature_property_payload
void construct(Table_feature_property_payload&, Table_feature_property_type);

/// \relates Table_feature_property_payload
void construct(Table_feature_property_payload&,
               Table_feature_property_payload&&, Table_feature_property_type);

/// \relates Table_feature_property_payload
void construct(Table_feature_property_payload&,
               const Table_feature_property_payload&,
               Table_feature_property_type);

/// \relates Table_feature_property_payload
Table_feature_property_payload&
assign(Table_feature_property_payload&, Table_feature_property_payload&&,
       Table_feature_property_type);

/// \relates Table_feature_property_payload
Table_feature_property_payload&
assign(Table_feature_property_payload&, const Table_feature_property_payload&,
       Table_feature_property_type);

/// \relates Table_feature_property_payload
void destroy(Table_feature_property_payload&, Table_feature_property_type);

/// \relates Table_feature_property_payload
bool equal(const Table_feature_property_payload&,
           const Table_feature_property_payload&,
           Table_feature_property_type, Table_feature_property_type);

/// \relates Table_feature_property_payload
std::size_t bytes(const Table_feature_property_payload&,
                  Table_feature_property_type);

/// \relates Table_feature_property_payload
Error_condition is_valid(const Table_feature_property_payload&,
              Table_feature_property_type);

/// \relates Table_feature_property_payload
Error_condition to_buffer(Buffer_view&, const Table_feature_property_payload&);

/// \relates Table_feature_property_payload
Error_condition from_buffer(Buffer_view&, Table_feature_property_payload&);

/// \relates Table_feature_property_payload
std::string to_string(const Table_feature_property_payload&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property header

struct Table_feature_property_header
{
  Table_feature_property_header() = default;
  Table_feature_property_header(Table_feature_property_type t, uint16_t l)
    : type(t), length(l) { }

  template<typename T>
    Table_feature_property_header(const T& value)
      : type(T::kind), length(4 + bytes(value)) { }

  Table_feature_property_type type;
  uint16_t length;
};

/// \relates Table_feature_property_header
bool operator==(const Table_feature_property_header& a,
                const Table_feature_property_header& b);

/// \relates Table_feature_property_header
bool operator!=(const Table_feature_property_header& a,
                const Table_feature_property_header& b);

/// \relates Table_feature_property_header
constexpr std::size_t bytes(const Table_feature_property_header&);

/// \relates Table_feature_property_header
Error_condition is_valid(const Table_feature_property_header& h);

/// \relates Table_feature_property_header
Error_condition to_buffer(Buffer_view&, const Table_feature_property_header&);

/// \relates Table_feature_property_header
Error_condition from_buffer(Buffer_view&, Table_feature_property_header&);

/// \relates Table_feature_property_header
std::string to_string(const Table_feature_property_header&, Formatter&);

// -------------------------------------------------------------------------- //
// Table feature property

struct Table_feature_property
{
  using Header = Table_feature_property_header;
  using Payload = Table_feature_property_payload;

  Table_feature_property() = default;
  ~Table_feature_property();

  Table_feature_property(Table_feature_property&&);
  Table_feature_property& operator=(Table_feature_property&&);

  Table_feature_property(const Table_feature_property&);
  Table_feature_property& operator=(const Table_feature_property&);

  Header header;
  Payload payload;
};

/// \relates Table_feature_property
inline bool
operator==(const Table_feature_property& a, const Table_feature_property& b);

/// \relates Table_feature_property
inline bool
operator!=(const Table_feature_property& a, const Table_feature_property& b);

/// \relates Table_feature_property
inline std::size_t
bytes(const Table_feature_property& tfp);

/// \relates Table_feature_property
inline Error_condition
is_valid(const Table_feature_property& tfp);

/// \relates Table_feature_property
Error_condition to_buffer(Buffer_view& v, const Table_feature_property& tfp);

/// \relates Table_feature_property
Error_condition from_buffer(Buffer_view& v, Table_feature_property& tfp);

/// \relates Table_feature_property
std::string to_string(const Table_feature_property& tfp, Formatter& f);

// -------------------------------------------------------------------------- //
// Multipart Request: Table feature

struct Multipart_req_table_feature
{
  static constexpr std::size_t NAME_STR_LEN = 32;

  using Name_string = Stringbuf<NAME_STR_LEN>;

  Multipart_req_table_feature() = default;
  Multipart_req_table_feature(uint16_t l, uint8_t tid, const char* n,
                              uint64_t mm, uint64_t mw, uint32_t c,
                              uint32_t me,
                              Sequence<Table_feature_property> p)        
    : length(l), table_id(tid), name(n), metadata_match(mm),
      metadata_write(mw), config(c), max_entries(me), properties(p) { }

  uint16_t length;
  uint8_t table_id;
  Name_string name;
  uint64_t metadata_match;
  uint64_t metadata_write;
  uint32_t config;
  uint32_t max_entries;
  Sequence<Table_feature_property> properties;
};

/// \relates Multipart_req_table_feature
bool operator==(const Multipart_req_table_feature& a,
                const Multipart_req_table_feature& b);

/// \relates Multipart_req_table_feature
bool operator!=(const Multipart_req_table_feature& a,
                const Multipart_req_table_feature& b);

/// \relates Multipart_req_table_feature
std::size_t bytes(const Multipart_req_table_feature& tf);

/// \relates Multipart_req_table_feature
Error_condition is_valid(const Multipart_req_table_feature& tf);

/// \relates Multipart_req_table_feature
Error_condition to_buffer(Buffer_view&, const Multipart_req_table_feature&);

/// \relates Multipart_req_table_feature
Error_condition from_buffer(Buffer_view&, Multipart_req_table_feature&);

/// \relates Multipart_req_table_feature
std::string to_string(const Multipart_req_table_feature&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Table features

struct Multipart_req_table_features
  : Multipart_payload_base<MULTIPART_TABLE_FEATURES>
{
  Multipart_req_table_features() = default;
  explicit Multipart_req_table_features
    (Sequence<Multipart_req_table_feature> tf) : table_features(tf) { }

  Sequence<Multipart_req_table_feature> table_features;
};

/// \relates Multipart_req_table_features
bool operator==(const Multipart_req_table_features& a,
                const Multipart_req_table_features& b);

/// \relates Multipart_req_table_features
bool operator!=(const Multipart_req_table_features& a,
                const Multipart_req_table_features& b);

/// \relates Multipart_req_table_features
std::size_t bytes(const Multipart_req_table_features& tf);

/// \relates Multipart_req_table_features
Error_condition is_valid(const Multipart_req_table_features& tf);

/// \relates Multipart_req_table_features
Error_condition to_buffer(Buffer_view&, const Multipart_req_table_features&);

/// \relates Multipart_req_table_features
Error_condition from_buffer(Buffer_view&, Multipart_req_table_features&);

/// \relates Multipart_req_table_features
std::string to_string(const Multipart_req_table_features&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Port desc

struct Multipart_req_port_desc
  : Multipart_payload_base<MULTIPART_PORT_DESC> { };

// -------------------------------------------------------------------------- //
// Multipart Request: Experimenter

struct Multipart_req_experimenter
  : Multipart_payload_base<MULTIPART_EXPERIMENTER>
{
  Multipart_req_experimenter() = default;
  Multipart_req_experimenter(uint32_t eid, uint32_t e, Greedy_buffer b)
    : experimenter_id(eid), exp_type(e), data(b) { }

  uint32_t experimenter_id;
  uint32_t exp_type;
  Greedy_buffer data;
};

/// \relates Multipart_req_experimenter
bool operator==(const Multipart_req_experimenter& a,
                const Multipart_req_experimenter& b);

/// \relates Multipart_req_experimenter
bool operator!=(const Multipart_req_experimenter& a,
                const Multipart_req_experimenter& b);

/// \relates Multipart_req_experimenter
std::size_t bytes(const Multipart_req_experimenter& e);

/// \relates Multipart_req_experimenter
constexpr Error_condition is_valid(const Multipart_req_experimenter&);

/// \relates Multipart_req_experimenter
Error_condition to_buffer(Buffer_view& v, const Multipart_req_experimenter& e);

/// \relates Multipart_req_experimenter
Error_condition from_buffer(Buffer_view& v, Multipart_req_experimenter& e);

/// \relates Multipart_req_experimenter
std::string to_string(const Multipart_req_experimenter&,  Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Request: Payload

union Multipart_req_payload_data
{
  Multipart_req_payload_data() { }
  ~Multipart_req_payload_data() { }

  Multipart_req_desc           desc;
  Multipart_req_flow           flow;
  Multipart_req_aggregate      aggregate;
  Multipart_req_table          table;
  Multipart_req_port           port;
  Multipart_req_queue          queue;
  Multipart_req_group          group;
  Multipart_req_group_desc     group_desc;
  Multipart_req_group_features group_features;
  Multipart_req_meter          meter;
  Multipart_req_meter_config   meter_config;
  Multipart_req_meter_features meter_features;
  Multipart_req_table_features table_features;
  Multipart_req_port_desc      port_desc;
  Multipart_req_experimenter   experimenter;
};

struct Multipart_req_payload
{
  using Data = Multipart_req_payload_data;

  Multipart_req_payload() : init(false) { }

  explicit operator bool() const { return init; }

  // Mutators
  void initialize(Multipart_type t);

  bool init;
  Data data;
};

/// \relates Multipart_req_payload
void construct(Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
void construct(Multipart_req_payload&,
               Multipart_req_payload&&, Multipart_type);

/// \relates Multipart_req_payload
void construct(Multipart_req_payload&,
               const Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
template<typename Tag, typename... Args>
  void construct(Multipart_req_payload& p, Tag t, Args&&... args) = delete;

/// \relates Multipart_req_payload
Multipart_req_payload& assign(Multipart_req_payload&,
                              Multipart_req_payload&&, Multipart_type);

/// \relates Multipart_req_payload
Multipart_req_payload& assign(Multipart_req_payload&,
                              const Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
void destroy(Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
bool equal(const Multipart_req_payload&,
           const Multipart_req_payload&, Multipart_type, Multipart_type);

/// \relates Multipart_req_payload
std::size_t bytes(const Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
Error_condition is_valid(const Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
Error_condition to_buffer(Buffer_view&, const Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
Error_condition from_buffer(Buffer_view&, Multipart_req_payload&, Multipart_type);

/// \relates Multipart_req_payload
std::string to_string(const Multipart_req_payload&, Multipart_type);

// -------------------------------------------------------------------------- //
// Multipart: Header

/// The Multipart_header class defines the header properties for Multipart
/// requests and responses.
struct Multipart_header
{
  enum Flags : uint16_t {
    MORE = 0x0001
  };

  Multipart_header() = default;
  Multipart_header(Multipart_type t, Flags f) : type(t), flags(f) { }

  template<typename T>
    Multipart_header(const T& value) : type(T::kind), flags() { }

  template<typename T, typename = typename T::Tag>
    explicit Multipart_header(const T& x) : type(kind_of(x)), flags() { }
  
  Multipart_type type;
  Flags flags;
};

/// \relates Multipart_header
bool operator==(const Multipart_header& a, const Multipart_header& b);

/// \relates Multipart_header
bool operator!=(const Multipart_header& a, const Multipart_header& b);

/// \relates Multipart_header
constexpr std::size_t bytes(const Multipart_header& h);

/// \relates Multipart_header
constexpr Error_condition is_valid(const Multipart_header::Flags f);

/// \relates Multipart_header
Error_condition is_valid(const Multipart_header& h);

/// \relates Multipart_header
Error_condition to_buffer(Buffer_view& v, const Multipart_header& h);

/// \relates Multipart_header
Error_condition from_buffer(Buffer_view& v, Multipart_header& h);

/// \relates Multipart_header
std::string to_string(const Multipart_header& h,  Formatter&);

/// \relates Multipart_header
std::string to_string(Multipart_header::Flags);

// -------------------------------------------------------------------------- //
// Multipart Request

/// This message is used by the controller to request statistics and information
/// from the switch.
/// 
/// \remark Defined in [OpenFlow v1.3, p60-73](http://...)
struct Multipart_req : Payload_base<MULTIPART_REQ>
{
  using Header = Multipart_header;
  using Payload = Multipart_req_payload;

  Multipart_req() = default;
  ~Multipart_req();

  // Move semantics
  Multipart_req(Multipart_req&&);
  Multipart_req& operator=(Multipart_req&&);

  // Copy semantics
  Multipart_req(const Multipart_req&);
  Multipart_req& operator=(const Multipart_req&);

  template<typename T, typename Tag = typename T::Tag>
    explicit Multipart_req(T&& x)
      : header(x) { construct(payload, Tag(), std::forward<T>(x)); }

  template<typename Tag, typename... Args>
    Multipart_req(Tag t, Args&&... args)
      : header(t.value) { construct(payload, t, std::forward<Args>(args)...); }

  Header  header;
  Payload payload;
};

/// Returns true when the messages compare equal.
///
/// \relates Multipart_req
bool operator==(const Multipart_req& a, const Multipart_req& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Multipart_req
bool operator!=(const Multipart_req& a, const Multipart_req& b);

/// Returns the number of bytes needed to represent a Multipart_req message.
///
/// \relates Multipart_req
std::size_t bytes(const Multipart_req& r);

/// Validates the value of a Multipart_req message.
///
/// \relates Multipart_req
Error_condition is_valid(const Multipart_req& r);

/// Writes a Multipart_req value to a Buffer_view.
///
/// \relates Multipart_req
Error_condition to_buffer(Buffer_view& buf, const Multipart_req& r);

/// Reads a Multipart_req value from a Buffer_view.
///
/// \relates Multipart_req
Error_condition from_buffer(Buffer_view& buf, Multipart_req& r);

/// Returns a formatted string representation of a Multipart_req message.
///
/// \relates Multipart_req
std::string to_string(const Multipart_req& r, Formatter& f);

// -------------------------------------------------------------------------- //
// Multipart Response: Desc

struct Multipart_res_desc : Multipart_payload_base<MULTIPART_DESC>
{
  static constexpr std::size_t DESC_STR_LEN   = 256;
  static constexpr std::size_t SERIAL_NUM_LEN = 32;

  using Desc_string = Stringbuf<DESC_STR_LEN>;
  using Serial_string = Stringbuf<SERIAL_NUM_LEN>;

  Multipart_res_desc() = default;
  Multipart_res_desc(const char* m, const char* h, const char* s, const char* sn,
                 const char* d)
    : mfr_desc(m), hw_desc(h), sw_desc(s), serial_num(sn), dp_desc(d) { }

  Desc_string   mfr_desc;
  Desc_string   hw_desc;
  Desc_string   sw_desc;
  Serial_string serial_num;
  Desc_string   dp_desc;
};

/// \relates Multipart_res_desc
bool operator==(const Multipart_res_desc& a, const Multipart_res_desc& b);

/// \relates Multipart_res_desc
bool operator!=(const Multipart_res_desc& a, const Multipart_res_desc& b);

/// \relates Multipart_res_desc
std::size_t bytes(const Multipart_res_desc& d);

/// \relates Multipart_res_desc
constexpr Error_condition is_valid(const Multipart_res_desc& d);

/// \relates Multipart_res_desc
Error_condition to_buffer(Buffer_view&, const Multipart_res_desc&);

/// \relates Multipart_res_desc
Error_condition from_buffer(Buffer_view&, Multipart_res_desc&);

/// \relates Multipart_res_desc
std::string to_string(const Multipart_res_desc&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Flow

struct Multipart_res_flow
{
  Multipart_res_flow() = default;
  Multipart_res_flow(uint16_t l, uint8_t tid, uint32_t ds, uint32_t dn,
                     uint16_t p, uint16_t it, uint16_t ht, uint16_t f,
                     uint64_t c, uint64_t pc, uint64_t bc, const Match& m,
                     const Sequence<Instruction>& i)
    : length(l), table_id(tid), duration_sec(ds), duration_nsec(dn),
      priority(p), idle_timeout(it), hard_timeout(ht), flags(f), cookie(c),
      packet_count(pc), byte_count(bc), match(m), instructions(i) { }

  uint16_t length;
  uint8_t table_id;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  uint16_t priority;
  uint16_t idle_timeout;
  uint16_t hard_timeout;
  uint16_t flags;
  uint64_t cookie;
  uint64_t packet_count;
  uint64_t byte_count;
  Match match;
  Sequence<Instruction> instructions;
};

/// \relates Multipart_res_flow
bool operator==(const Multipart_res_flow& a, const Multipart_res_flow& b);

/// \relates Multipart_res_flow
bool operator!=(const Multipart_res_flow& a, const Multipart_res_flow& b);

/// \relates Multipart_res_flow
std::size_t bytes(const Multipart_res_flow& f);

/// \relates Multipart_res_flow
Error_condition is_valid(const Multipart_res_flow& f);

/// \relates Multipart_res_flow
Error_condition to_buffer(Buffer_view& v, const Multipart_res_flow&);

/// \relates Multipart_res_flow
Error_condition from_buffer(Buffer_view& v, Multipart_res_flow&);

/// \relates Multipart_res_flow
std::string to_string(const Multipart_res_flow&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Flows

struct Multipart_res_flows : Multipart_payload_base<MULTIPART_FLOW>
{
  Multipart_res_flows() = default;
  explicit Multipart_res_flows(Sequence<Multipart_res_flow> f) : flows(f) { }

  Sequence<Multipart_res_flow> flows;
};

/// \relates Multipart_res_flows
bool operator==(const Multipart_res_flows& a, const Multipart_res_flows& b);

/// \relates Multipart_res_flows
bool operator!=(const Multipart_res_flows& a, const Multipart_res_flows& b);

/// \relates Multipart_res_flows
std::size_t bytes(const Multipart_res_flows& f);

/// \relates Multipart_res_flows
Error_condition is_valid(const Multipart_res_flows& f);

/// \relates Multipart_res_flows
Error_condition to_buffer(Buffer_view&, const Multipart_res_flows&);

/// \relates Multipart_res_flows
Error_condition from_buffer(Buffer_view&, Multipart_res_flows&);

/// \relates Multipart_res_flows
std::string to_string(const Multipart_res_flows&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Aggregate

struct Multipart_res_aggregate : Multipart_payload_base<MULTIPART_AGGREGATE>
{
  Multipart_res_aggregate() = default;
  Multipart_res_aggregate(uint64_t pc, uint64_t bc, uint32_t fc)
    : packet_count(pc), byte_count(bc), flow_count(fc) { };

  uint64_t packet_count;
  uint64_t byte_count;
  uint32_t flow_count;
};

/// \relates Multipart_res_aggregate
bool operator==(const Multipart_res_aggregate& a, const Multipart_res_aggregate& b);

/// \relates Multipart_res_aggregate
bool operator!=(const Multipart_res_aggregate& a, const Multipart_res_aggregate& b);

/// \relates Multipart_res_aggregate
constexpr std::size_t bytes(const Multipart_res_aggregate&);

/// \relates Multipart_res_aggregate
constexpr Error_condition is_valid(const Multipart_res_aggregate& a);

/// \relates Multipart_res_aggregate
Error_condition to_buffer(Buffer_view& v, const Multipart_res_aggregate& s);

/// \relates Multipart_res_aggregate
Error_condition from_buffer(Buffer_view& v, Multipart_res_aggregate& s);

/// \relates Multipart_res_aggregate
std::string to_string(const Multipart_res_aggregate&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Port

struct Multipart_res_port
{
  Multipart_res_port() = default;
  Multipart_res_port(uint32_t pn, uint64_t rp, uint64_t tp, uint64_t rb,
                     uint64_t tb, uint64_t rd, uint64_t td, uint64_t re,
                     uint64_t te, uint64_t rfe, uint64_t roe, uint64_t rce,
                     uint64_t c, uint32_t ds, uint32_t dn)
    : port_no(pn), rx_packets(rp), tx_packets(tp), rx_bytes(rb), tx_bytes(tb),
      rx_dropped(rd), tx_dropped(td), rx_errors(re), tx_errors(te),
      rx_frame_err(rfe), rx_over_err(roe), rx_crc_err(rce), collisions(c),
      duration_sec(ds), duration_nsec(dn) { }

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
  uint32_t duration_sec;
  uint32_t duration_nsec;
};

/// \relates Multipart_res_port
bool operator==(const Multipart_res_port& a, const Multipart_res_port& b);

/// \relates Multipart_res_port
bool operator!=(const Multipart_res_port& a, const Multipart_res_port& b);

/// \relates Multipart_res_port
constexpr std::size_t bytes(const Multipart_res_port&);

/// \relates Multipart_res_port
constexpr Error_condition is_valid(const Multipart_res_port&);

/// \relates Multipart_res_port
Error_condition to_buffer(Buffer_view& v, const Multipart_res_port& p);

/// \relates Multipart_res_port
Error_condition from_buffer(Buffer_view& v, Multipart_res_port& p);

/// \relates Multipart_res_port
std::string to_string(const Multipart_res_port& p, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Ports

struct Multipart_res_ports : Multipart_payload_base<MULTIPART_PORT>
{
  Multipart_res_ports() = default;
  explicit Multipart_res_ports(Sequence<Multipart_res_port> p) : ports(p) { };

  Sequence<Multipart_res_port> ports;
};

/// \relates Multipart_res_ports
bool operator==(const Multipart_res_ports& a, const Multipart_res_ports& b);

/// \relates Multipart_res_ports
bool operator!=(const Multipart_res_ports& a, const Multipart_res_ports& b);

/// \relates Multipart_res_ports
std::size_t bytes(const Multipart_res_ports& p);

/// \relates Multipart_res_ports
Error_condition is_valid(const Multipart_res_ports& p);

/// \relates Multipart_res_ports
Error_condition to_buffer(Buffer_view&, const Multipart_res_ports&);

/// \relates Multipart_res_ports
Error_condition from_buffer(Buffer_view&, Multipart_res_ports&);

/// \relates Multipart_res_ports
std::string to_string(const Multipart_res_ports&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Queue

struct Multipart_res_queue
{
  Multipart_res_queue() = default;
  Multipart_res_queue(uint32_t pn, uint32_t qid, uint64_t tb, uint64_t tp,
                      uint64_t te, uint32_t ds, uint32_t dn)
    : port_no(pn), queue_id(qid), tx_bytes(tb), tx_packets(tp), tx_errors(te),
      duration_sec(ds), duration_nsec(dn) { }

  uint32_t port_no;
  uint32_t queue_id;
  uint64_t tx_bytes;
  uint64_t tx_packets;
  uint64_t tx_errors;
  uint32_t duration_sec;
  uint32_t duration_nsec;
};

/// \relates Multipart_res_queue
bool operator==(const Multipart_res_queue& a, const Multipart_res_queue& b);

/// \relates Multipart_res_queue
bool operator!=(const Multipart_res_queue& a, const Multipart_res_queue& b);

/// \relates Multipart_res_queue
constexpr std::size_t bytes(const Multipart_res_queue&);

/// \relates Multipart_res_queue
Error_condition is_valid(const Multipart_res_queue&);

/// \relates Multipart_res_queue
Error_condition to_buffer(Buffer_view& v, const Multipart_res_queue& q);

/// \relates Multipart_res_queue
Error_condition from_buffer(Buffer_view& v, Multipart_res_queue& q);

/// \relates Multipart_res_queue
std::string to_string(const Multipart_res_queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Queues

struct Multipart_res_queues : Multipart_payload_base<MULTIPART_QUEUE>
{
  Multipart_res_queues() = default;
  explicit Multipart_res_queues(Sequence<Multipart_res_queue> q) : queues(q) { }

  Sequence<Multipart_res_queue> queues;
};

/// \relates Multipart_res_queues
bool operator==(const Multipart_res_queues& a, const Multipart_res_queues& b);

/// \relates Multipart_res_queues
bool operator!=(const Multipart_res_queues& a, const Multipart_res_queues& b);

/// \relates Multipart_res_queues
std::size_t bytes(const Multipart_res_queues& q);

/// \relates Multipart_res_queues
Error_condition is_valid(const Multipart_res_queues& q);

/// \relates Multipart_res_queues
Error_condition to_buffer(Buffer_view&, const Multipart_res_queues&);

/// \relates Multipart_res_queues
Error_condition from_buffer(Buffer_view&, Multipart_res_queues&);

/// \relates Multipart_res_queues
std::string to_string(const Multipart_res_queues&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Table

struct Multipart_res_table : Multipart_payload_base<MULTIPART_TABLE>
{
  Multipart_res_table() = default;
  Multipart_res_table(uint8_t tid, uint32_t ac, uint64_t lc, uint64_t mc)
    : table_id(tid), active_count(ac), lookup_count(lc), matched_count(mc) { }

  uint8_t table_id;
  uint32_t active_count;
  uint64_t lookup_count;
  uint64_t matched_count;
};

/// \relates Multipart_res_table
bool operator==(const Multipart_res_table& a, const Multipart_res_table& b);

/// \relates Multipart_res_table
bool operator!=(const Multipart_res_table& a, const Multipart_res_table& b);

/// \relates Multipart_res_table
constexpr std::size_t bytes(const Multipart_res_table&);

/// \relates Multipart_res_table
Error_condition is_valid(const Multipart_res_table&);

/// \relates Multipart_res_table
Error_condition to_buffer(Buffer_view& v, const Multipart_res_table& t);

/// \relates Multipart_res_table
Error_condition from_buffer(Buffer_view& v, Multipart_res_table& t);

/// \relates Multipart_res_table
std::string to_string(const Multipart_res_table&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Tables

struct Multipart_res_tables : Multipart_payload_base<MULTIPART_TABLE>
{
  Multipart_res_tables() = default;
  explicit Multipart_res_tables(Sequence<Multipart_res_table> t) : tables(t) { };

  Sequence<Multipart_res_table> tables;
};

/// \relates Multipart_res_tables
bool operator==(const Multipart_res_tables& a, const Multipart_res_tables& b);

/// \relates Multipart_res_tables
bool operator!=(const Multipart_res_tables& a, const Multipart_res_tables& b);

/// \relates Multipart_res_tables
std::size_t bytes(const Multipart_res_tables& t);

/// \relates Multipart_res_tables
Error_condition is_valid(const Multipart_res_tables& t);

/// \relates Multipart_res_tables
Error_condition to_buffer(Buffer_view&, const Multipart_res_tables&);

/// \relates Multipart_res_tables
Error_condition from_buffer(Buffer_view&, Multipart_res_tables&);

/// \relates Multipart_res_tables
std::string to_string(const Multipart_res_tables&, Formatter&);

// -------------------------------------------------------------------------- //
// Bucket

struct Bucket_counter
{
  Bucket_counter() = default;
  Bucket_counter(uint64_t pc, uint64_t bc)
    : packet_count(pc), byte_count(bc) { }

  uint64_t packet_count;
  uint64_t byte_count;
};

/// \relates Bucket_counter
bool operator==(const Bucket_counter& a, const Bucket_counter& b);

/// \relates Bucket_counter
bool operator!=(const Bucket_counter& a, const Bucket_counter& b);

/// \relates Bucket_counter
constexpr std::size_t bytes(const Bucket_counter&);

/// \relates Bucket_counter
constexpr Error_condition is_valid(const Bucket_counter&);

/// \relates Bucket_counter
Error_condition to_buffer(Buffer_view& v, const Bucket_counter& bc);

/// \relates Bucket_counter
Error_condition from_buffer(Buffer_view& v, Bucket_counter& bc);

/// \relates Bucket_counter
std::string to_string(const Bucket_counter&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Group

struct Multipart_res_group
{
  Multipart_res_group() = default;
  Multipart_res_group(uint16_t l, uint32_t gid, uint32_t rc, uint64_t pc,
                      uint64_t bc, uint32_t ds, uint32_t dn,
                      const Sequence<Bucket_counter>& bs)
    : length(l), group_id(gid), ref_count(rc), packet_count(pc), byte_count(bc),
      duration_sec(ds), duration_nsec(dn), bucket_multipart(bs) { }

  uint16_t length;
  uint32_t group_id;
  uint32_t ref_count;
  uint64_t packet_count;
  uint64_t byte_count;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  Sequence<Bucket_counter> bucket_multipart;
};

/// \relates Multipart_res_group
bool operator==(const Multipart_res_group& a, const Multipart_res_group& b);

/// \relates Multipart_res_group
bool operator!=(const Multipart_res_group& a, const Multipart_res_group& b);

/// \relates Multipart_res_group
std::size_t bytes(const Multipart_res_group& g);

/// \relates Multipart_res_group
Error_condition is_valid(const Multipart_res_group& g);

/// \relates Multipart_res_group
Error_condition to_buffer(Buffer_view& v, const Multipart_res_group& g);

/// \relates Multipart_res_group
Error_condition from_buffer(Buffer_view& v, Multipart_res_group& g);

/// \relates Multipart_res_group
std::string to_string(const Multipart_res_group&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Groups

struct Multipart_res_groups : Multipart_payload_base<MULTIPART_GROUP>
{
  Multipart_res_groups() = default;
  explicit Multipart_res_groups(Sequence<Multipart_res_group> gd) : groups(gd) { }

  Sequence<Multipart_res_group> groups;
};

/// \relates Multipart_res_groups
bool operator==(const Multipart_res_groups& a, const Multipart_res_groups& b);

/// \relates Multipart_res_groups
bool operator!=(const Multipart_res_groups& a, const Multipart_res_groups& b);

/// \relates Multipart_res_groups
std::size_t bytes(const Multipart_res_groups& gd);

/// \relates Multipart_res_groups
Error_condition is_valid(const Multipart_res_groups& g);

/// \relates Multipart_res_groups
Error_condition to_buffer(Buffer_view&, const Multipart_res_groups&);

/// \relates Multipart_res_groups
Error_condition from_buffer(Buffer_view&, Multipart_res_groups&);

/// \relates Multipart_res_groups
std::string to_string(const Multipart_res_groups&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Group desc

struct Multipart_res_group_desc : Multipart_payload_base<MULTIPART_GROUP_DESC>
{
  Multipart_res_group_desc() = default;
  Multipart_res_group_desc(uint16_t l, uint8_t t, uint32_t gid,
                       const Sequence<Bucket>& b)
    : length(l), type(t), group_id(gid), buckets(b) { }

  uint16_t length;
  uint8_t type;
  uint32_t group_id;
  Sequence<Bucket> buckets;
};

/// \relates Multipart_res_group_desc
bool operator==(const Multipart_res_group_desc& a, const Multipart_res_group_desc& b);

/// \relates Multipart_res_group_desc
bool operator!=(const Multipart_res_group_desc& a, const Multipart_res_group_desc& b);

/// \relates Multipart_res_group_desc
std::size_t bytes(const Multipart_res_group_desc& gd);

/// \relates Multipart_res_group_desc
Error_condition is_valid(const Multipart_res_group_desc& gd);

/// \relates Multipart_res_group_desc
Error_condition to_buffer(Buffer_view& v, const Multipart_res_group_desc& gd);

/// \relates Multipart_res_group_desc
Error_condition from_buffer(Buffer_view& v, Multipart_res_group_desc& dg);

/// \relates Multipart_res_group_desc
std::string to_string(const Multipart_res_group_desc&, Formatter&);

/// \relates Multipart_res_group_desc
Error_condition to_buffer(Buffer_view& v, const Multipart_res_group_desc& gd);

/// \relates Multipart_res_group_desc
Error_condition from_buffer(Buffer_view& v, Multipart_res_group_desc& dg);

/// \relates Multipart_res_group_desc
std::string to_string(const Multipart_res_group_desc&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Group descs

struct Multipart_res_group_descs : Multipart_payload_base<MULTIPART_GROUP_DESC>
{
  Multipart_res_group_descs() = default;
  explicit Multipart_res_group_descs(Sequence<Multipart_res_group_desc> gd)
    : group_descs(gd) { }

  Sequence<Multipart_res_group_desc> group_descs;
};

/// \relates Multipart_res_group_descs
bool operator==(const Multipart_res_group_descs& a, const Multipart_res_group_descs& b);

/// \relates Multipart_res_group_descs
bool operator!=(const Multipart_res_group_descs& a, const Multipart_res_group_descs& b);

/// \relates Multipart_res_group_descs
std::size_t bytes(const Multipart_res_group_descs& gd);

/// \relates Multipart_res_group_descs
Error_condition is_valid(const Multipart_res_group_descs& gd);

/// \relates Multipart_res_group_descs
Error_condition to_buffer(Buffer_view&, const Multipart_res_group_descs&);

/// \relates Multipart_res_group_descs
Error_condition from_buffer(Buffer_view&, Multipart_res_group_descs&);

/// \relates Multipart_res_group_descs
std::string to_string(const Multipart_res_group_descs&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Group features

struct Multipart_res_group_features 
  : Multipart_payload_base<MULTIPART_GROUP_FEATURES>
{
  enum Capability_type : uint32_t {
    SELECT_WEIGHT = 0x00000001, SELECT_LIVENESS = 0x00000002,
    CHAINING = 0x00000004, CHAINING_CHECKS = 0x00000008
  };

  Multipart_res_group_features() = default;
  Multipart_res_group_features(uint32_t t, Capability_type c, uint32_t mga,
                               uint32_t mgs, uint32_t mgi, uint32_t mgf,
                               uint32_t aa, uint32_t as, uint32_t ai,
                               uint32_t af)
    : types(t), capabilities(c), max_groups_all(mga), max_groups_select(mgs),
      max_groups_indirect(mgi), max_groups_ff(mgf), actions_all(aa),
      actions_select(as), actions_indirect(ai), actions_ff(af) {  }

  uint32_t types;
  Capability_type capabilities;
  uint32_t max_groups_all;
  uint32_t max_groups_select;
  uint32_t max_groups_indirect;
  uint32_t max_groups_ff;
  uint32_t actions_all;
  uint32_t actions_select;
  uint32_t actions_indirect;
  uint32_t actions_ff;
};

/// \relates Multipart_res_group_features
bool operator==(const Multipart_res_group_features& a,
                const Multipart_res_group_features& b);

/// \relates Multipart_res_group_features
bool operator!=(const Multipart_res_group_features& a,
                const Multipart_res_group_features& b);

/// \relates Multipart_res_group_features
constexpr std::size_t bytes(const Multipart_res_group_features&);

/// \relates Multipart_res_group_features
constexpr Error_condition is_valid(const Multipart_res_group_features&);

/// \relates Multipart_res_group_features
Error_condition to_buffer(Buffer_view&, const Multipart_res_group_features&);

/// \relates Multipart_res_group_features
Error_condition from_buffer(Buffer_view&, Multipart_res_group_features&);

/// \relates Multipart_res_group_features
std::string to_string(Multipart_res_group_features::Capability_type);

/// \relates Multipart_res_group_features
std::string to_string(const Multipart_res_group_features&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Meter band stats 

struct Meter_band_stats
{
  Meter_band_stats() = default;
  Meter_band_stats(uint64_t pbc, uint64_t bbc)
    : packet_band_count(pbc), byte_band_count(bbc) { }

  uint64_t packet_band_count;
  uint64_t byte_band_count;
};

/// \relates Meter_band_stats
bool operator==(const Meter_band_stats& a, const Meter_band_stats& b);

/// \relates Meter_band_stats
bool operator!=(const Meter_band_stats& a, const Meter_band_stats& b);

/// \relates Meter_band_stats
constexpr std::size_t bytes(const Meter_band_stats&);

/// \relates Meter_band_stats
constexpr Error_condition is_valid(const Meter_band_stats&);

/// \relates Meter_band_stats
Error_condition to_buffer(Buffer_view&, const Meter_band_stats&);

/// \relates Meter_band_stats
Error_condition from_buffer(Buffer_view&, Meter_band_stats&);

/// \relates Meter_band_stats
std::string to_string(const Meter_band_stats&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Meter

struct Multipart_res_meter
{

  Multipart_res_meter() = default;
  Multipart_res_meter(uint32_t mid, uint16_t l, uint32_t fc, uint64_t pic,
                      uint64_t bic, uint32_t ds, uint32_t dn,
                      Sequence<Meter_band_stats> mbs)
    : meter_id(mid), len(l), flow_count(fc), packet_in_count(pic),
      byte_in_count(bic), duration_sec(ds), duration_nsec(dn),
      meter_band_stats(mbs) { }

  uint32_t meter_id;
  uint16_t len;
  uint32_t flow_count;
  uint64_t packet_in_count;
  uint64_t byte_in_count;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  Sequence<Meter_band_stats> meter_band_stats;
};

/// \relates Multipart_res_meter
bool operator==(const Multipart_res_meter& a, const Multipart_res_meter& b);

/// \relates Multipart_res_meter
bool operator!=(const Multipart_res_meter& a, const Multipart_res_meter& b);

/// \relates Multipart_res_meter
std::size_t bytes(const Multipart_res_meter& m);

/// \relates Multipart_res_meter
Error_condition is_valid(const Multipart_res_meter& m);

/// \relates Multipart_res_meter
Error_condition to_buffer(Buffer_view&, const Multipart_res_meter&);

/// \relates Multipart_res_meter
Error_condition from_buffer(Buffer_view&, Multipart_res_meter&);

/// \relates Multipart_res_meter
std::string to_string(const Multipart_res_meter&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Meters

struct Multipart_res_meters : Multipart_payload_base<MULTIPART_METER>
{
  Multipart_res_meters() = default;
  explicit Multipart_res_meters(Sequence<Multipart_res_meter> m) : meters(m) { }

  Sequence<Multipart_res_meter> meters;
};

/// \relates Multipart_res_meters
bool operator==(const Multipart_res_meters& a, const Multipart_res_meters& b);

/// \relates Multipart_res_meters
bool operator!=(const Multipart_res_meters& a, const Multipart_res_meters& b);

/// \relates Multipart_res_meters
std::size_t bytes(const Multipart_res_meters& m);

/// \relates Multipart_res_meters
Error_condition is_valid(const Multipart_res_meters& m);

/// \relates Multipart_res_meters
Error_condition to_buffer(Buffer_view&, const Multipart_res_meters&);

/// \relates Multipart_res_meters
Error_condition from_buffer(Buffer_view&, Multipart_res_meters&);

/// \relates Multipart_res_meters
std::string to_string(const Multipart_res_meters&, Formatter&);

// -------------------------------------------------------------------------- //
// Meter band type

/// \relates Meter_band_header
enum Meter_band_type : uint16_t
{
  METER_BAND_DROP = 1,
  METER_BAND_DSCP_REMARK = 2,
  METER_BAND_EXPERIMENTER = 0xffff
};

/// \relates Meter_band_header
Error_condition is_valid(const Meter_band_type mbt);

/// \relates Meter_band_header
std::string to_string(Meter_band_type);

template<Meter_band_type K>
  using Meter_band_payload_base = Basic_payload_base<Meter_band_type, K>;

// -------------------------------------------------------------------------- //
// Meter band: drop

struct Meter_band_drop : Meter_band_payload_base<METER_BAND_DROP> { };

/// \relates Meter_band_drop
constexpr std::size_t
bytes(const Meter_band_drop&);

/// \relates Meter_band_drop
constexpr Error_condition
is_valid(const Meter_band_drop&);

/// \relates Meter_band_drop
Error_condition to_buffer(Buffer_view&, const Meter_band_drop&);

/// \relates Meter_band_drop
Error_condition from_buffer(Buffer_view&, Meter_band_drop&);

// -------------------------------------------------------------------------- //
// Meter band: dscp remark

struct Meter_band_dscp_remark
  : Meter_band_payload_base<METER_BAND_DSCP_REMARK>
{
  Meter_band_dscp_remark() = default;
  explicit Meter_band_dscp_remark(uint8_t pl) : prec_level(pl) { }

  uint8_t prec_level;
};

/// \relates Meter_band_dscp_remark
bool operator==(const Meter_band_dscp_remark& a,
                const Meter_band_dscp_remark& b);

/// \relates Meter_band_dscp_remark
bool operator!=(const Meter_band_dscp_remark& a,
                const Meter_band_dscp_remark& b);

/// \relates Meter_band_dscp_remark
constexpr std::size_t bytes(const Meter_band_dscp_remark&);

/// \relates Meter_band_dscp_remark
constexpr Error_condition is_valid(const Meter_band_dscp_remark&);

/// \relates Meter_band_dscp_remark
Error_condition to_buffer(Buffer_view&, const Meter_band_dscp_remark&);

/// \relates Meter_band_dscp_remark
Error_condition from_buffer(Buffer_view&, Meter_band_dscp_remark&);

/// \relates Meter_band_dscp_remark
std::string to_string(const Meter_band_dscp_remark&, Formatter&);

// -------------------------------------------------------------------------- //
// Meter band: experimenter

struct Meter_band_experimenter
  : Meter_band_payload_base<METER_BAND_EXPERIMENTER>
{
  Meter_band_experimenter() = default;
  explicit Meter_band_experimenter(uint32_t eid) : experimenter_id(eid) { }

  uint32_t experimenter_id;
};

/// \relates Meter_band_experimenter
bool operator==(const Meter_band_experimenter& a,
                const Meter_band_experimenter& b);

/// \relates Meter_band_experimenter
bool operator!=(const Meter_band_experimenter& a,
                const Meter_band_experimenter& b);

/// \relates Meter_band_experimenter
constexpr std::size_t bytes(const Meter_band_experimenter&);

/// \relates Meter_band_experimenter
constexpr Error_condition is_valid(const Meter_band_experimenter&);

/// \relates Meter_band_experimenter
Error_condition to_buffer(Buffer_view&, const Meter_band_experimenter&);

/// \relates Meter_band_experimenter
Error_condition from_buffer(Buffer_view&, Meter_band_experimenter&);

/// \relates Meter_band_experimenter
std::string to_string(const Meter_band_experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// Meter band payload

union Meter_band_payload_data
{
  Meter_band_drop         drop;
  Meter_band_dscp_remark  dscp_remark;
  Meter_band_experimenter experimenter;
};

struct Meter_band_payload
{
  using Data = Meter_band_payload_data;

  Meter_band_payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;
  Data data;
};

/// \relates Meter_band_payload
void construct(Meter_band_payload&, Meter_band_type);

/// \relates Meter_band_payload
void construct(Meter_band_payload&, const Meter_band_payload&,
               Meter_band_type);

Meter_band_payload& assign(Meter_band_payload&, const Meter_band_payload&,
                           Meter_band_type);

/// \relates Meter_band_payload
bool equal(const Meter_band_payload&, const Meter_band_payload&,
           Meter_band_type, Meter_band_type);

/// \relates Meter_band_payload
std::size_t bytes(const Meter_band_payload&, Meter_band_type);

/// \relates Meter_band_payload
Error_condition is_valid(const Meter_band_payload&, Meter_band_type);

/// \relates Meter_band_payload
Error_condition to_buffer(Buffer_view&, const Meter_band_payload&, Meter_band_type);

/// \relates Meter_band_payload
Error_condition from_buffer(Buffer_view&, Meter_band_payload&, Meter_band_type);

/// \relates Meter_band_payload
std::string to_string(const Meter_band_payload&, Formatter&, Meter_band_type);

// -------------------------------------------------------------------------- //
// Meter band header

struct Meter_band_header
{
  Meter_band_header() = default;
  Meter_band_header(Meter_band_type t, uint16_t l, uint32_t r, uint32_t bs)
    : type(t), len(l), rate(r), burst_size(bs) { }

  template<typename T>
    explicit Meter_band_header(const T& value)
      : type(T::kind), len(12 + bytes(value)), rate(0), burst_size(0) { }

  Meter_band_type type;
  uint16_t len;
  uint32_t rate;
  uint32_t burst_size;
};

/// \relates Meter_band_header
bool operator==(const Meter_band_header& a, const Meter_band_header& b);

/// \relates Meter_band_header
bool operator!=(const Meter_band_header& a, const Meter_band_header& b);

/// \relates Meter_band_header
constexpr std::size_t bytes(const Meter_band_header&);

/// \relates Meter_band_header
Error_condition is_valid(const Meter_band_header& h);

/// \relates Meter_band_header
Error_condition to_buffer(Buffer_view&, const Meter_band_header&);

/// \relates Meter_band_header
Error_condition from_buffer(Buffer_view&, Meter_band_header&);

/// \relates Meter_band_header
std::string to_string(const Meter_band_header&, Formatter&);

// -------------------------------------------------------------------------- //
// Meter band

struct Meter_band
{
  using Header = Meter_band_header;
  using Payload = Meter_band_payload;

  Meter_band() = default;

  Meter_band(const Meter_band&);
  Meter_band& operator=(const Meter_band&);

  Header header;
  Payload payload;
};

/// \relates Meter_band
bool operator==(const Meter_band& a, const Meter_band& b);

/// \relates Meter_band
bool operator!=(const Meter_band& a, const Meter_band& b);

/// \relates Meter_band
std::size_t bytes(const Meter_band& mb);

/// \relates Meter_band
Error_condition is_valid(const Meter_band& mb);

/// \relates Meter_band
Error_condition to_buffer(Buffer_view&, const Meter_band&);

/// \relates Meter_band
Error_condition from_buffer(Buffer_view&, Meter_band&);

/// \relates Meter_band
std::string to_string(const Meter_band&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Meter config

struct Multipart_res_meter_config
{
  Multipart_res_meter_config() = default;
  inline Multipart_res_meter_config(uint16_t l, uint16_t f, uint32_t mid,
                             Sequence<Meter_band> mb)
    : len(l), flags(f), meter_id(mid), meter_bands(mb) { }

  uint16_t len;
  uint16_t flags;
  uint32_t meter_id;
  Sequence<Meter_band> meter_bands;
};

/// \relates Multipart_res_meter_config
bool operator==(const Multipart_res_meter_config& a,
                const Multipart_res_meter_config& b);

/// \relates Multipart_res_meter_config
bool operator!=(const Multipart_res_meter_config& a,
                const Multipart_res_meter_config& b);

/// \relates Multipart_res_meter_config
std::size_t bytes(const Multipart_res_meter_config& mc);

/// \relates Multipart_res_meter_config
Error_condition is_valid(const Multipart_res_meter_config& mc);

/// \relates Multipart_res_meter_config
Error_condition to_buffer(Buffer_view&, const Multipart_res_meter_config&);

/// \relates Multipart_res_meter_config
Error_condition from_buffer(Buffer_view&, Multipart_res_meter_config&);

/// \relates Multipart_res_meter_config
std::string to_string(const Multipart_res_meter_config&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Meter configs

struct Multipart_res_meter_configs 
  : Multipart_payload_base<MULTIPART_METER_CONFIG>
{
  Multipart_res_meter_configs() = default;
  explicit Multipart_res_meter_configs(Sequence<Multipart_res_meter_config> mc)
    : meter_configs(mc) { }

  Sequence<Multipart_res_meter_config> meter_configs;
};

/// \relates Multipart_res_meter_configs
bool operator==(const Multipart_res_meter_configs& a,
                const Multipart_res_meter_configs& b);

/// \relates Multipart_res_meter_configs
bool operator!=(const Multipart_res_meter_configs& a,
                const Multipart_res_meter_configs& b);

/// \relates Multipart_res_meter_configs
std::size_t bytes(const Multipart_res_meter_configs& mc);

/// \relates Multipart_res_meter_configs
Error_condition is_valid(const Multipart_res_meter_configs& mc);

/// \relates Multipart_res_meter_configs
Error_condition to_buffer(Buffer_view&, const Multipart_res_meter_configs&);

/// \relates Multipart_res_meter_configs
Error_condition from_buffer(Buffer_view&, Multipart_res_meter_configs&);

// -------------------------------------------------------------------------- //
// Multipart Response: Meter features

struct Multipart_res_meter_features
  : Multipart_payload_base<MULTIPART_METER_FEATURES>
{

  Multipart_res_meter_features() = default;
  Multipart_res_meter_features(uint32_t mm, uint32_t bt, uint32_t c,
                               uint8_t mb, uint8_t mc)
    : max_meter(mm), band_type(bt), capabilities(c), max_bands(mb),
      max_color(mc) { }

  uint32_t max_meter;
  uint32_t band_type;
  uint32_t capabilities;
  uint8_t max_bands;
  uint8_t max_color;
};

/// \relates Multipart_res_meter_features
bool operator==(const Multipart_res_meter_features& a,
                const Multipart_res_meter_features& b);

/// \relates Multipart_res_meter_features
bool operator!=(const Multipart_res_meter_features& a,
                const Multipart_res_meter_features& b);

/// \relates Multipart_res_meter_features
constexpr std::size_t bytes(const Multipart_res_meter_features&);

/// \relates Multipart_res_meter_features
constexpr Error_condition is_valid(const Multipart_res_meter_features&);

/// \relates Multipart_res_meter_features
Error_condition to_buffer(Buffer_view&, const Multipart_res_meter_features&);

/// \relates Multipart_res_meter_features
Error_condition from_buffer(Buffer_view&, Multipart_res_meter_features&);

/// \relates Multipart_res_meter_features
std::string to_string(const Multipart_res_meter_features&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Table feature

struct Multipart_res_table_feature
{
  static constexpr std::size_t NAME_STR_LEN = 32;

  using Name_string = Stringbuf<NAME_STR_LEN>;

  Multipart_res_table_feature() = default;
  Multipart_res_table_feature(uint16_t l, uint8_t tid, const char* n,
                              uint64_t mm, uint64_t mw, uint32_t c,
                              uint32_t me,
                              Sequence<Table_feature_property> p)
    : length(l), table_id(tid), name(n), metadata_match(mm),
      metadata_write(mw), config(c), max_entries(me), properties(p) { }

  uint16_t length;
  uint8_t table_id;
  Name_string name;
  uint64_t metadata_match;
  uint64_t metadata_write;
  uint32_t config;
  uint32_t max_entries;
  Sequence<Table_feature_property> properties;
};

/// \relates Multipart_res_table_feature
bool operator==(const Multipart_res_table_feature& a,
                const Multipart_res_table_feature& b);

/// \relates Multipart_res_table_feature
bool operator!=(const Multipart_res_table_feature& a,
                const Multipart_res_table_feature& b);

/// \relates Multipart_res_table_feature
std::size_t bytes(const Multipart_res_table_feature& tf);

/// \relates Multipart_res_table_feature
Error_condition is_valid(const Multipart_res_table_feature& tf);

/// \relates Multipart_res_table_feature
Error_condition to_buffer(Buffer_view&, const Multipart_res_table_feature&);

/// \relates Multipart_res_table_feature
Error_condition from_buffer(Buffer_view&, Multipart_res_table_feature&);

/// \relates Multipart_res_table_feature
std::string to_string(const Multipart_res_table_feature&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Table features

struct Multipart_res_table_features
  : Multipart_payload_base<MULTIPART_TABLE_FEATURES>
{
  Multipart_res_table_features() = default;
  explicit Multipart_res_table_features
    (Sequence<Multipart_res_table_feature> tf) : table_features(tf) { }

  Sequence<Multipart_res_table_feature> table_features;
};

/// \relates Multipart_res_table_features
inline bool
operator==(const Multipart_res_table_features& a,
           const Multipart_res_table_features& b);

/// \relates Multipart_res_table_features
inline bool
operator!=(const Multipart_res_table_features& a,
           const Multipart_res_table_features& b);

/// \relates Multipart_res_table_features
std::size_t bytes(const Multipart_res_table_features& tf);

/// \relates Multipart_res_table_features
Error_condition is_valid(const Multipart_res_table_features& tf);

/// \relates Multipart_res_table_features
Error_condition to_buffer(Buffer_view&, const Multipart_res_table_features&);

/// \relates Multipart_res_table_features
Error_condition from_buffer(Buffer_view&, Multipart_res_table_features&);

/// \relates Multipart_res_table_features
std::string to_string(const Multipart_res_table_features&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Port desc

struct Multipart_res_port_desc
  : Multipart_payload_base<MULTIPART_PORT_DESC>
{
  Multipart_res_port_desc() = default;
  explicit Multipart_res_port_desc(Sequence<Port> p) : ports(p) { }

  Sequence<Port> ports;
};

/// \relates Multipart_res_port_desc
bool operator==(const Multipart_res_port_desc& a,
                const Multipart_res_port_desc& b);

/// \relates Multipart_res_port_desc
bool operator!=(const Multipart_res_port_desc& a,
                const Multipart_res_port_desc& b);

/// \relates Multipart_res_port_desc
std::size_t bytes(const Multipart_res_port_desc& pd);

/// \relates Multipart_res_port_desc
Error_condition is_valid(const Multipart_res_port_desc& pd);

/// \relates Multipart_res_port_desc
Error_condition to_buffer(Buffer_view&, const Multipart_res_port_desc&);

/// \relates Multipart_res_port_desc
Error_condition from_buffer(Buffer_view&, Multipart_res_port_desc&);

/// \relates Multipart_res_port_desc
std::string to_string(const Multipart_res_port_desc&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Experimenter

struct Multipart_res_experimenter
  : Multipart_payload_base<MULTIPART_EXPERIMENTER>
{
  Multipart_res_experimenter() = default;
  Multipart_res_experimenter(uint32_t eid, uint32_t e, Greedy_buffer b)
    : experimenter_id(eid), exp_type(e), data(b) { }

  uint32_t experimenter_id;
  uint32_t exp_type;
  Greedy_buffer data;
};

/// \relates Multipart_res_experimenter
bool operator==(const Multipart_res_experimenter& a,
                const Multipart_res_experimenter& b);

/// \relates Multipart_res_experimenter
bool operator!=(const Multipart_res_experimenter& a,
                const Multipart_res_experimenter& b);

/// \relates Multipart_res_experimenter
std::size_t bytes(const Multipart_res_experimenter& e);

/// \relates Multipart_res_experimenter
Error_condition is_valid(const Multipart_res_experimenter&);

/// \relates Multipart_res_experimenter
Error_condition to_buffer(Buffer_view& v, const Multipart_res_experimenter& e);

/// \relates Multipart_res_experimenter
Error_condition from_buffer(Buffer_view& v, Multipart_res_experimenter& e);

/// \relates Multipart_res_experimenter
std::string to_string(const Multipart_res_experimenter&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Payload

/// \relates Multipart_res_payload
union Multipart_res_payload_data
{
  Multipart_res_payload_data() { }
  ~Multipart_res_payload_data() { }

  Multipart_res_desc           desc;
  Multipart_res_flows          flow;
  Multipart_res_aggregate      aggregate;
  Multipart_res_tables         table;
  Multipart_res_ports          port;
  Multipart_res_queues         queue;
  Multipart_res_groups         group;
  Multipart_res_group_descs    group_desc;
  Multipart_res_group_features group_features;
  Multipart_res_meters         meter;
  Multipart_res_meter_configs  meter_config;
  Multipart_res_meter_features meter_features;
  Multipart_res_table_features table_features;
  Multipart_res_port_desc      port_desc;
  Multipart_res_experimenter   experimenter;
};

/// Object used to handle the initialization of the payload of a Multipart_res
/// message
struct Multipart_res_payload
{
  using Data = Multipart_res_payload_data;

  Multipart_res_payload() : init(false) { }

  explicit operator bool() const { return init; }

  // Mutators
  void initialize(Multipart_type t);

  bool init;
  Data data;
};

/// \relates Multipart_res_payload
void construct(Multipart_res_payload&, Multipart_type);

/// \relates Multipart_res_payload
void construct(Multipart_res_payload&, Multipart_res_payload&&,
               Multipart_type);

/// \relates Multipart_res_payload
void construct(Multipart_res_payload&, const Multipart_res_payload&,
               Multipart_type);

/// \relates Multipart_res_payload
Multipart_res_payload& assign(Multipart_res_payload&,
                              Multipart_res_payload&&, Multipart_type);

/// \relates Multipart_res_payload
Multipart_res_payload& assign(Multipart_res_payload&,
                              const Multipart_res_payload&, Multipart_type);

/// \relates Multipart_res_payload
void destroy(Multipart_res_payload&, Multipart_type);

/// \relates Multipart_res_payload
bool equal(const Multipart_res_payload&, const Multipart_res_payload&,
           Multipart_type, Multipart_type);

/// \relates Multipart_res_payload
std::size_t bytes(const Multipart_res_payload&, Multipart_type);

/// \relates Multipart_res_payload
Error_condition is_valid(const Multipart_res_payload&, Multipart_type);

/// \relates Multipart_res_payload
Error_condition to_buffer(Buffer_view&, const Multipart_res_payload&, Multipart_type);

/// \relates Multipart_res_payload
Error_condition from_buffer(Buffer_view&, Multipart_res_payload&, Multipart_type);

/// \relates Multipart_res_payload
std::string to_string(const Multipart_res_payload&, Multipart_type);

// -------------------------------------------------------------------------- //
// Multipart Response

/// This message is a response from the switch conveying statistics or other
/// information requested by the controller.
/// 
/// \remark Defined in [OpenFlow v1.3, p60-73](http://...)
struct Multipart_res : Payload_base<MULTIPART_RES>
{
  using Header = Multipart_header;
  using Payload = Multipart_res_payload;

  Multipart_res() = default;
  ~Multipart_res();

  // Move semantics
  Multipart_res(Multipart_res&&);
  Multipart_res& operator=(Multipart_res&&);

  // Copy semantics
  Multipart_res(const Multipart_res&);
  Multipart_res& operator=(const Multipart_res&);

  Header  header;
  Payload payload;
};

/// Returns true when the messages compare equal.
///
/// \relates Multipart_res
bool operator==(const Multipart_res& a, const Multipart_res& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Multipart_res
bool operator!=(const Multipart_res& a, const Multipart_res& b);

/// Returns the number of bytes needed to represent a Multipart_res message.
///
/// \relates Multipart_res
std::size_t bytes(const Multipart_res& r);

/// Validates the value of a Multipart_res message.
///
/// \relates Multipart_res
Error_condition is_valid(const Multipart_res& r);

/// Writes a Multipart_res value to a Buffer_view.
///
/// \relates Multipart_res
Error_condition to_buffer(Buffer_view& v, const Multipart_res& r);

/// Reads a Multipart_res value from a Buffer_view.
///
/// \relates Multipart_res
Error_condition from_buffer(Buffer_view& v, Multipart_res& r);

/// Returns a formatted string representation of a Multipart_res message.
///
/// \relates Multipart_res
std::string to_string(const Multipart_res& r,  Formatter&);

// -------------------------------------------------------------------------- //
// Barrier Request

/// A barrier request is used by the controller to set a synchronization point,
/// ensuring that all previous state messages are completed before the barrier
/// response is sent back to the controller. This is needed because state
/// modification messages sent by the controller may be executed in an
/// arbitrary order.
/// 
/// \remark Defined in [OpenFlow v1.3, p74](http://...)
struct Barrier_req : Payload_base<BARRIER_REQ> { };

// -------------------------------------------------------------------------- //
// Barrier Response

/// A barrier response is sent by the switch to the controller to acknowledge
/// that the previously received messages have been processed.
/// 
/// \remark Defined in [OpenFlow v1.3, p74](http://...)
struct Barrier_res : Payload_base<BARRIER_RES> { };

// -------------------------------------------------------------------------- //
// Queue Get Config Request

/// Queues can not be configured through OpenFlow; however, they can be queried.
/// The objective of the Queue_get_config_req and Queue_get_config_res messages
/// is to allow for the controller to query the state of queues associated with
/// various ports on the OpenFlow switch.
/// 
/// \remark Defined in [OpenFlow v1.3, p73-74](http://...)
struct Queue_get_config_req : Payload_base<QUEUE_GET_CONFIG_REQ>
{
  Queue_get_config_req() = default;
  explicit Queue_get_config_req(uint32_t p) : port(p) { }

  uint32_t port;
};

/// Returns true when the messages compare equal.
///
/// \relates Queue_get_config_req
bool operator==(const Queue_get_config_req& a, const Queue_get_config_req& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Queue_get_config_req
bool operator!=(const Queue_get_config_req& a, const Queue_get_config_req& b);

/// Returns the number of bytes needed to represent a Queue_get_config_req
/// message.
///
/// \relates Queue_get_config_req
constexpr std::size_t bytes(const Queue_get_config_req&);

/// Validates the value of a Queue_get_config_req message.
///
/// \relates Queue_get_config_req
Error_condition is_valid(const Queue_get_config_req& q);

/// Writes a Queue_get_config_req value to a Buffer_view.
///
/// \relates Queue_get_config_req
Error_condition to_buffer(Buffer_view&, const Queue_get_config_req&);

/// Reads a Queue_get_config_req value from a Buffer_view.
///
/// \relates Queue_get_config_req
Error_condition from_buffer(Buffer_view&, Queue_get_config_req&);

/// Returns a formatted string representation of a Queue_get_config_req message.
///
/// \relates Queue_get_config_req
std::string to_string(const Queue_get_config_req&, Formatter&);

// -------------------------------------------------------------------------- //
// Queue Get Config Repsonse

/// Queues can not be configured through OpenFlow; however, they can be queried.
/// The objective of the Queue_get_config_req and Queue_get_config_res messages
/// is to allow for the controller to query the state of queues associated with
/// various ports on the OpenFlow switch.
/// 
/// \remark Defined in [OpenFlow v1.3, p73-74](http://...)
struct Queue_get_config_res : Payload_base<QUEUE_GET_CONFIG_RES>
{
  Queue_get_config_res() = default;
  Queue_get_config_res(uint32_t p, Sequence<Queue> q) : port(p), queues(q) { }

  uint32_t port;
  Sequence<Queue> queues;
};

/// Returns true when the messages compare equal.
///
/// \relates Queue_get_config_res
bool operator==(const Queue_get_config_res& a, const Queue_get_config_res& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Queue_get_config_res
bool operator!=(const Queue_get_config_res& a, const Queue_get_config_res& b);

/// Returns the number of bytes needed to represent a Queue_get_config_res
/// message.
///
/// \relates Queue_get_config_res
std::size_t bytes(const Queue_get_config_res& qgcr);

/// Validates the value of a Queue_get_config_res message.
///
/// \relates Queue_get_config_res
Error_condition is_valid(const Queue_get_config_res& qgcr);

/// Writes a Queue_get_config_res value to a Buffer_view.
///
/// \relates Queue_get_config_res
Error_condition to_buffer(Buffer_view&, const Queue_get_config_res&);

/// Reads a Queue_get_config_res value from a Buffer_view.
///
/// \relates Queue_get_config_res
Error_condition from_buffer(Buffer_view&, Queue_get_config_res&);

/// Returns a formatted string representation of a Queue_get_config_res message.
///
/// \relates Queue_get_config_res
std::string to_string(const Queue_get_config_res&, Formatter&);

// -------------------------------------------------------------------------- //
// Role enum

/// Roles controllers can hold
enum Role : uint32_t
{
  R_NO_CHANGE = 0x00000000, ///< Leave the current role unchanged
  R_EQUAL     = 0x00000001, ///< Full access (default)
  R_MASTER    = 0x00000002, ///< Full access with one master (at most)
  R_SLAVE     = 0x00000003  ///< Read only access
};

/// Validates the value of a Role object. Returns SUCCESS only when r is a
/// declared value of Role and BAD_ROLE otherwise.
///
/// \relates Role
constexpr Error_condition is_valid(const Role r);

/// Returns a string representation of the value.
/// \relates Role
std::string to_string(const Role);

// -------------------------------------------------------------------------- //
// Role Base

/// Base object which provides common fields and functions for Role_req
/// and Role_res.
template <Message_type K>
  struct Role_base : Payload_base<K>
  {
    Role_base() = default;
    Role_base(Role r, uint64_t gid)
      : role(r), generation_id(gid) { }

    Role role;
    uint64_t generation_id;
  };

/// \relates Role_base
template <Message_type K>
  bool operator==(const Role_base<K>& a, const Role_base<K>& b);

/// \relates Role_base
template <Message_type K>
  bool operator!=(const Role_base<K>& a, const Role_base<K>& b);

/// \relates Role_base
template <Message_type K>
  constexpr std::size_t bytes(const Role_base<K>&);

/// \relates Role_base
template <Message_type K>
  constexpr Error_condition is_valid(const Role_base<K>& rb);

/// \relates Role_base
template <Message_type K>
  Error_condition to_buffer(Buffer_view& v, const Role_base<K>& rb);

/// \relates Role_base
template <Message_type K>
  Error_condition from_buffer(Buffer_view& v, Role_base<K>& rb);

// -------------------------------------------------------------------------- //
// Role Req

/// A message sent by a controller in order to change its role.
/// (see Role_base)
///
/// \remark Defined in [OpenFlow v1.0, p74-75](http:://...)
struct Role_req : Role_base<ROLE_REQ> { };

/// Returns a formatted string representation of the value.
///
/// \relates Role_req
std::string to_string(const Role_req&, Formatter&);

// -------------------------------------------------------------------------- //
// Role Res

/// A message sent to acknowledge a Role_req in order to change its role.
/// (see Role_base)
///
/// \remark Defined in [OpenFlow v1.0, p74-75](http:://...)
struct Role_res : Role_base<ROLE_RES> { };

/// Returns a formatted string representation of the value.
///
/// \relates Role_res
std::string to_string(const Role_res&, Formatter&);

// -------------------------------------------------------------------------- //
// Get Async Request

/// Get_async_req, Get_async_res, Set_async is used by the controller to set
/// which asynchronous messages it should send, as well as to query the switch
/// for which asynchronous messages it will send.
///
/// \remark Defined in [OpenFlow v1.0, p75-76](http:://...)
struct Get_async_req : Payload_base<GET_ASYNC_REQ> { };

// -------------------------------------------------------------------------- //
// Async base

/// Base object which provides common fields and functions for Get_async_res
/// and Set_async.
template<Message_type T>
  struct Async_message_base
  {
    Async_message_base() = default;
    Async_message_base(uint32_t pim, uint32_t pims, uint32_t psm,
                       uint32_t psms, uint32_t frm, uint32_t frms)
      : packet_in_mask(pim), packet_in_mask_slave(pims), port_status_mask(psm),
        port_status_mask_slave(psms), flow_removed_mask(frm),
        flow_removed_mask_slave(frms) { }

    uint32_t packet_in_mask;
    uint32_t packet_in_mask_slave;
    uint32_t port_status_mask;
    uint32_t port_status_mask_slave;
    uint32_t flow_removed_mask;
    uint32_t flow_removed_mask_slave;
  };

/// \relates Async_message_base
template<Message_type T>
  inline bool
  operator==(const Async_message_base<T>& a, const Async_message_base<T>& b);

/// \relates Async_message_base
template<Message_type T>
  inline bool
  operator!=(const Async_message_base<T>& a, const Async_message_base<T>& b);

/// \relates Async_message_base
template<Message_type T>
  constexpr std::size_t
  bytes(const Async_message_base<T>&);

/// \relates Async_message_base
template<Message_type T>
  inline Error_condition
  is_valid(const Async_message_base<T>& c);

/// \relates Async_message_base
template<Message_type T>
  inline Error_condition
  to_buffer(Buffer_view& b, const Async_message_base<T>& m);

/// \relates Async_message_base
template<Message_type T>
  inline Error_condition
  from_buffer(Buffer_view& b, Async_message_base<T>& m);

// -------------------------------------------------------------------------- //
// Get Async Response

/// Get_async_req, Get_async_res, Set_async is used by the controller to set
/// which asynchronous messages it should send, as well as to query the switch
/// for which asynchronous messages it will send. (see Async_message_base)
///
/// \remark Defined in [OpenFlow v1.0, p75-76](http:://...)
struct Get_async_res : Async_message_base<GET_ASYNC_RES> { };

/// Returns a formatted string representation of the value.
///
/// \relates Get_async_res
std::string to_string(const Get_async_res&, Formatter&);

// -------------------------------------------------------------------------- //
// Set Async

/// Get_async_req, Get_async_res, Set_async is used by the controller to set
/// which asynchronous messages it should send, as well as to query the switch
/// for which asynchronous messages it will send. (see Async_message_base)
///
/// \remark Defined in [OpenFlow v1.0, p75-76](http:://...)
struct Set_async : Async_message_base<SET_ASYNC> { };

/// Returns a formatted string representation of the value.
///
/// \relates Set_async
std::string to_string(const Set_async&, Formatter&);

// -------------------------------------------------------------------------- //
// Meter Mod

/// Meter_mod message is used by the controller to modify the meter.
///
/// \remark Defined in [OpenFlow v1.0, p58-60](http:://...)
struct Meter_mod : Payload_base<METER_MOD>
{
  /// Commands used by Meter_mod messages
  enum Command : uint16_t {
    ADD    = 0x0000, ///< Add a meter
    MODIFY = 0x0001, ///< Modify a meter
    DELETE = 0x0002  ///< Remove a meter
  };

  /// Configuration flags for Meter_mod messages
  enum Flags_type : uint16_t {
    KBPS  = 0x0001, ///< Report the rate in kilo-bits per second
    PKTPS = 0x0010, ///< Report the rate in packets per second
    BURST = 0x0100, ///< Report burst size
    STATS = 0x1000  ///< College statistics
  };

  enum Id_value : uint32_t {
    MAX        = 0xffff0000, ///< Maximum value for representing meters
    SLOW_PATH  = 0xfffffffd, ///< Represents a slow datapath
    CONTROLLER = 0xfffffffe, ///< Represents a controler connection
    ALL        = 0xffffffff  ///< Apply to all meters
  };

  Meter_mod() = default;
  Meter_mod(Command c, Flags_type f, Id_value mid, Sequence<Meter_band> mb)
    : command(c), flags(f), meter_id(mid), meter_bands(mb) { }

  Command command;
  Flags_type flags;
  Id_value meter_id;
  Sequence<Meter_band> meter_bands;
};

/// Returns true when the messages compare equal.
///
/// \relates Meter_mod
bool operator==(const Meter_mod& a, const Meter_mod& b);

/// Returns true when two messages do not compare equal.
///
/// \relates Meter_mod
bool operator!=(const Meter_mod& a, const Meter_mod& b);

/// Returns the number of bytes needed to represent a Meter_mod message.
///
/// \relates Meter_mod
std::size_t bytes(const Meter_mod& mm);

Error_condition is_valid(const Meter_mod::Command c);

Error_condition is_valid(const Meter_mod::Id_value i);

/// Validates the value of a Meter_mod message.
///
/// \relates Meter_mod
Error_condition is_valid(const Meter_mod mm);

/// Writes a Meter_mod value to a Buffer_view.
///
/// \relates Meter_mod
Error_condition to_buffer(Buffer_view&, const Meter_mod&);

/// Reads a Meter_mod value from a Buffer_view.
///
/// \relates Meter_mod
Error_condition from_buffer(Buffer_view&, Meter_mod&);

/// Returns a string representation of a Meter_mod::Command.
///
/// \relates Meter_mod
std::string to_string(Meter_mod::Command);

/// Returns a string representation of a Meter_mod::Flags_type.
///
/// \relates Meter_mod
std::string to_string(Meter_mod::Flags_type);

/// Returns a string representation of a Meter_mod::Id_value.
///
/// \relates Meter_mod
std::string to_string(Meter_mod::Id_value);

/// Returns a formatted string representation of a Meter_mod message.
///
/// \relates Meter_mod
std::string to_string(const Meter_mod&, Formatter&);

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
  Multipart_req        multipart_req;
  Multipart_res        multipart_res;
  Barrier_req          barrier_req;
  Barrier_res          barrier_res;
  Queue_get_config_req queue_get_config_req;
  Queue_get_config_res queue_get_config_res;
  Role_req             role_req;
  Role_res             role_res;
  Get_async_req        get_async_req;
  Get_async_res        get_async_res;
  Set_async            set_async;
  Meter_mod            meter_mod;
};

struct Payload
{
  using Data = Payload_data;

  Payload() : init(false) { }

  explicit operator bool() const { return init; }

  bool init;  // True when initialized
  Data data;  // The underlying data
};

/// \relates Payload
void construct(Payload&, Message_type);
/// \relates Payload
void construct(Payload&, Payload&&, Message_type);
/// \relates Payload
void construct(Payload&, const Payload&, Message_type);

/// Construct a payload with the given arguments. The Tag argument, t,
/// must be of the form M::Tag where M is a messaage class in this
/// implementation. The arguments args, must conform to a constructor
/// of the class M.
/// 
/// \relates Payload
template<typename Tag, typename... Args>
  void construct(Payload& p, Tag t, Args&&... args) = delete;

/// \relates Payload
Payload& assign(Payload&, Payload&&, Message_type);

/// \relates Payload
Payload& assign(Payload&, const Payload&, Message_type);

/// \relates Payload
void destroy(Payload&, Message_type);

/// \relates Payload
bool equal(const Payload&, const Payload&, Message_type, Message_type);

/// \relates Payload
std::size_t bytes(const Payload&, Message_type);

/// \relates Payload
Error_condition is_valid(const Payload&, Message_type);

/// \relates Payload
Error_condition to_buffer(Buffer_view&, const Payload&, Message_type);

/// \relates Payload
Error_condition from_buffer(Buffer_view&, Payload&, Message_type);

/// \relates Payload
std::string to_string(const Payload&, Formatter&, Message_type);

// -------------------------------------------------------------------------- //
// Header

/// Every OpenFlow message begins with a fixed-sized header. This header 
/// describes the OpenFlow protocol version, the type of message, the length
/// in bytes (inclusive of the header), and the transaction id (used to match
/// responses to requests).
///
/// \remark [OpenFlow Switch Specification Version 1.3 p34](http://...)
struct Header
{
  Header() = default;
  
  Header(Message_type t)
    : version(VERSION), type(t) { }
  
  Header(Message_type t, uint16_t l, uint32_t id)
    : version(VERSION), type(t), length(l), xid(id) { }
  Header(Version_type v, Message_type t, uint16_t l, uint32_t id)
    : version(v), type(t), length(l), xid(id) { }

  template<typename T>
    Header(const T& value, uint32_t id)
    : version(VERSION), type(T::kind), length(8 + bytes(value)), xid(id) { }

  Version_type version;
  Message_type type;
  uint16_t length;
  uint32_t xid;
};

/// \relates Header
bool operator==(const Header& a, const Header& b);

/// \relates Header
bool operator!=(const Header& a, const Header& b);

/// \relates Header
constexpr std::size_t bytes(const Header&);

/// \relates Header
Error_condition is_valid(const Header& h);

/// \relates Header
Error_condition to_buffer(Buffer_view& buf, const Header& h);

/// \relates Header
Error_condition from_buffer(Buffer_view& buf, Header& h);

/// \relates Header
std::string to_string(const Header& h, Formatter&);

// -------------------------------------------------------------------------- //
// Message

/// \brief Encapsulates an OpenFlow v1.3 message.
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

  static Factory factory(Xid_generator<uint32_t>& gen) { return Factory(gen); }

  Header  header;
  Payload payload;
};

/// \brief Returns true when the arguments compare equal.
/// \relates Message
bool operator==(const Message& a, const Message& b);

/// \brief Returns true when the arguments do not compare equal.
/// \relates Message
bool operator!=(const Message& a, const Message& b);

std::size_t bytes(const Message& m);

/// \brief Validates the representation of the object.
/// \relates Message
Error_condition is_valid(const Message& m);

/// \brief Writes the value into a buffer view.
/// \relates Message
Error_condition to_buffer(Buffer_view&, const Message&);

/// \brief Reads the value from a buffer view.
/// \relates Message
Error_condition from_buffer(Buffer_view&, Message&);

/// \brief Returns a formatted string representation of the value.
/// \relates Message
std::string to_string(const Message&, Formatter&);

} // namespace v1_3
} // namespace ofp
} // namespace flog

#include "message.ipp"

#endif
