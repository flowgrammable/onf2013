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

#include "message.hpp"

namespace flog {
namespace ofp {
namespace v1_1 {

std::string
to_string(Version_type t)
{
  if (t == 2)
    return "1.1";
  else
    return "Unknown";
}

std::string
to_string(Message_type t)
{
  switch(t) {
  case HELLO: return "Hello";
  case ERROR: return "Error";
  case ECHO_REQ: return "EchoReq";
  case ECHO_RES: return "EchoRes";
  case EXPERIMENTER: return "Experimenter";
  case FEATURE_REQ: return "FeatureReq";
  case FEATURE_RES: return "FeatureRes";
  case GET_CONFIG_RES: return "GetConfigReq";
  case GET_CONFIG_REQ: return "GetConfigRes";
  case SET_CONFIG: return "SetConfig";
  case PACKET_IN: return "PacketIn";
  case FLOW_REMOVED: return "FlowRemoved";
  case PORT_STATUS: return "PortStatus";
  case PACKET_OUT: return "PacketOut";
  case FLOW_MOD: return "FlowMod";
  case GROUP_MOD: return "GroupMod";
  case PORT_MOD: return "PortMod";
  case TABLE_MOD: return "TableMod";
  case STATS_REQ: return "StatsReq";
  case STATS_RES: return "StatsRes";
  case BARRIER_REQ: return "BarrierReq";
  case BARRIER_RES: return "BarrierRes";
  case QUEUE_GET_CONFIG_REQ: return "QueueGetConfigReq";
  case QUEUE_GET_CONFIG_RES: return "QueueGetConfigRes";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Hello

Error_condition
to_buffer(Buffer_view& v, const Hello& h)
{
  if (not available(v, bytes(h)))
    return AVAILABLE_HELLO;
  to_buffer(v, h.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Hello& h)
{
  if (not available(v, bytes(h)))
    return AVAILABLE_HELLO;
  from_buffer(v, h.data);
  return SUCCESS;
}

std::string
to_string(const Hello& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Hello");
  nvp_to_string(ss, f, "Data bytes", bytes(h.data));
  close_block(ss, f, "Hello");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Error

Error_condition
to_buffer(Buffer_view& v, const Error& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_ERROR;
  to_buffer(v, e.type);
  to_buffer(v, e.code.value);
  to_buffer(v, e.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Error& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_ERROR;
  from_buffer(v, e.type);
  from_buffer(v, e.code.value);
  from_buffer(v, e.data);
  return SUCCESS;
}

std::string
to_string(const Error& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Error");
  nvp_to_string(ss, f, "Type", to_string(e.type), (int)e.type);
  nvp_to_string(ss, f, "Type", to_string(e.type, e.code), (int)e.code.value);
  nvp_to_string(ss, f, "Data bytes", bytes(e.data));
  close_block(ss, f, "Error");
  return ss.str();
}

std::string
to_string(Error::Type t)
{
  switch(t) {
  case Error::HELLO_FAILED: return "Hello Failed";
  case Error::BAD_REQUEST: return "Bad Request";
  case Error::BAD_ACTION: return "Bad Action";
  case Error::BAD_INSTRUCTION: return "Bad Instruction";
  case Error::BAD_MATCH: return "Bad Match";
  case Error::FLOW_MOD_FAILED: return "FlowMod Failed";
  case Error::GROUP_MOD_FAILED: return "GroupMod Failed";
  case Error::PORT_MOD_FAILED: return "PortMod Failed";
  case Error::TABLE_MOD_FAILED: return "TableMod Failed";
  case Error::QUEUE_OP_FAILED: return "Queue Op Failed";
  case Error::SWITCH_CONFIG_FAILED: return "SwitchConfigFailed";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Hello_failed hf)
{
  switch(hf) {
  case Error::HF_INCOMPATIBLE: return "Incompatible";
  case Error::HF_EPERM: return "EPerm";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Bad_request br)
{
  switch(br) {
  case Error::BR_BAD_VERSION: return "Bad Version";
  case Error::BR_BAD_TYPE: return "Bad Type";
  case Error::BR_BAD_STAT: return "Bad Stat";
  case Error::BR_BAD_EXPERIMENTER: return "Bad Experimenter";
  case Error::BR_BAD_SUBTYPE: return "Bad Subtype";
  case Error::BR_EPERM: return "EPerm";
  case Error::BR_BAD_LEN: return "Bad Length";
  case Error::BR_BUFFER_EMPTY: return "Buffer Empty";
  case Error::BR_BUFFER_UNKNOWN: return "Buffer Unknown";
  case Error::BR_BAD_TABLE_ID: return "Bad Table ID";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Bad_action ba)
{
  switch(ba) {
  case Error::BA_BAD_TYPE: return "Bad Type";
  case Error::BA_BAD_LEN: return "Bad Length";
  case Error::BA_BAD_EXPERIMENTER: return "Bad Experimenter";
  case Error::BA_BAD_EXPERIMENTER_TYPE: return "Bad Experimenter Type";
  case Error::BA_BAD_OUT_PORT: return "Bad Output Port";
  case Error::BA_BAD_ARGUMENT: return "Bad Argument";
  case Error::BA_EPERM: return "EPerm";
  case Error::BA_TOO_MANY: return "Too Many";
  case Error::BA_BAD_QUEUE: return "Bad Queue";
  case Error::BA_BAD_OUT_GROUP: return "Bad Output Groups";
  case Error::BA_MATCH_INCONSISTENT: return "Match Inconsistent";
  case Error::BA_UNSUPPORTED_ORDER: return "Unsupported Order";
  case Error::BA_BAD_TAG: return "Bad Tag";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Bad_instruction bi)
{
  switch(bi) {
  case Error::BI_UNKNOWN_INST: return "Unknown Inst";
  case Error::BI_UNSUP_INST: return "Unsup Inst";
  case Error::BI_BAD_TABLE_ID: return "Bad Table ID";
  case Error::BI_UNSUP_METADATA: return "Unsup Metadata";
  case Error::BI_UNSUP_METADATA_MASK: return "Unsup Metadata Mask";
  case Error::BI_UNSUP_EXP_LIST: return "Unsuo Exp List";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Bad_match bm)
{
  switch(bm) {
  case Error::BM_BAD_TYPE: return "Bad Type";
  case Error::BM_BAD_LEN: return "Bad Length";
  case Error::BM_BAD_TAG: return "Bad Tag";
  case Error::BM_BAD_DL_ADDR_MASK: return "Bad DL Addr Mask";
  case Error::BM_BAD_HW_ADDR_MASK: return "Bad HW Addr Mask";
  case Error::BM_BAD_WILDCARDS: return "Bad Wildcards";
  case Error::BM_BAD_FIELD: return "Bad Field";
  case Error::BM_BAD_VALUE: return "Bad Value";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Flow_mod_failed fmf)
{
  switch(fmf) {
  case Error::FMF_UNKNOWN: return "Unknown";
  case Error::FMF_TABLE_FULL: return "Table Full";
  case Error::FMF_BAD_TABLE_ID: return "Bad Table ID";
  case Error::FMF_OVERLAP: return "Overlap";
  case Error::FMF_EPERM: return "EPerm";
  case Error::FMF_BAD_TIMEOUT: return "Bad Timeout";
  case Error::FMF_BAD_COMMAND: return "Bad Command";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Group_mod_failed gmf)
{
  switch(gmf) {
  case Error::GMF_GROUP_EXISTS: return "Group Exists";
  case Error::GMF_INVALID_GROUP: return "Invalid Group";
  case Error::GMF_WEIGHT_UNSUPPORTED: return "Weight Unsupported";
  case Error::GMF_OUT_OF_GROUPS: return "Out of Groups";
  case Error::GMF_OUT_OF_BUCKETS: return "Out of Buckets";
  case Error::GMF_CHAINING_UNSUPPORTED: return "Chaining Unsupported";
  case Error::GMF_WATCH_UNSUPPORTED: return "Watch Unsupported";
  case Error::GMF_LOOP: return "Loop";
  case Error::GMF_UNKNOWN_GROUP: return "Unknown Group";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Port_mod_failed pmf)
{
  switch(pmf) {
  case Error::PMF_BAD_PORT: return "Bad Port";
  case Error::PMF_BAD_HW_ADDR: return "Bad HW Addr";
  case Error::PMF_BAD_CONFIG: return "Bad Config";
  case Error::PMF_BAD_ADVERTISE: return "Bad Advertise";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Table_mod_failed tmf)
{
  switch(tmf) {
  case Error::TMF_BAD_TABLE: return "Bad Table";
  case Error::TMF_BAD_CONFIG: return "Bad Config";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Queue_op_failed qof)
{
  switch(qof) {
  case Error::QOF_BAD_PORT: return "Bad Port";
  case Error::QOF_BAD_QUEUE: return "Bad Queue";
  case Error::QOF_EPERM: return "EPerm";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Switch_config_failed scf)
{
  switch(scf) {
  case Error::SCF_BAD_FLAGS: return "Bad Flags";
  case Error::SCF_BAD_LEN: return "Bad Length";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Type t, Error::Code c)
{
  switch(t) {
  case Error::HELLO_FAILED: return to_string(c.hf);
  case Error::BAD_REQUEST: return to_string(c.br);
  case Error::BAD_ACTION: return to_string(c.ba);
  case Error::BAD_INSTRUCTION: return to_string(c.bi);
  case Error::BAD_MATCH: return to_string(c.bm);
  case Error::FLOW_MOD_FAILED: return to_string(c.fmf);
  case Error::GROUP_MOD_FAILED: return to_string(c.gmf);
  case Error::PORT_MOD_FAILED: return to_string(c.pmf);
  case Error::TABLE_MOD_FAILED: return to_string(c.tmf);
  case Error::QUEUE_OP_FAILED: return to_string(c.qof);
  case Error::SWITCH_CONFIG_FAILED: return to_string(c.scf);
  default: return "UNKNOWN";
  }
}

// -------------------------------------------------------------------------- //
// Experimenter

Error_condition
to_buffer(Buffer_view& v, const Experimenter& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_EXPERIMENTER;
  to_buffer(v, e.experimenter_id);
  pad(v, 4);
  to_buffer(v, e.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Experimenter& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_EXPERIMENTER;
  from_buffer(v, e.experimenter_id);
  pad(v, 4);
  from_buffer(v, e.data);
  return SUCCESS;
}

std::string
to_string(const Experimenter& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Experimenter");

  nvp_to_string(ss, f, "Experimenter ID", e.experimenter_id);
  nvp_to_string(ss, f, "Data bytes", bytes(e.data));

  close_block(ss, f, "Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Match

Error_condition
to_buffer(Buffer_view& v, const Match& m)
{
  to_buffer(v, m.type);
  to_buffer(v, m.length);
  to_buffer(v, m.in_port);
  to_buffer(v, m.wildcards);
  to_buffer(v, m.dl_src);
  to_buffer(v, m.dl_src_mask);
  to_buffer(v, m.dl_dst);
  to_buffer(v, m.dl_dst_mask);
  to_buffer(v, m.dl_vlan);
  to_buffer(v, m.dl_pcp);
  pad(v, 1);
  to_buffer(v, m.dl_type);
  to_buffer(v, m.nw_tos);
  to_buffer(v, m.nw_proto);
  to_buffer(v, m.nw_src);
  to_buffer(v, m.nw_src_mask);
  to_buffer(v, m.nw_dst);
  to_buffer(v, m.nw_dst_mask);
  to_buffer(v, m.tp_src);
  to_buffer(v, m.tp_dst);
  to_buffer(v, m.mpls_label);
  to_buffer(v, m.mpls_tc);
  pad(v, 3);
  to_buffer(v, m.metadata);
  to_buffer(v, m.metadata_mask);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Match& m)
{
  from_buffer(v, m.type);
  from_buffer(v, m.length);
  from_buffer(v, m.in_port);
  from_buffer(v, m.wildcards);
  from_buffer(v, m.dl_src);
  from_buffer(v, m.dl_src_mask);
  from_buffer(v, m.dl_dst);
  from_buffer(v, m.dl_dst_mask);
  from_buffer(v, m.dl_vlan);
  from_buffer(v, m.dl_pcp);
  pad(v, 1);
  from_buffer(v, m.dl_type);
  from_buffer(v, m.nw_tos);
  from_buffer(v, m.nw_proto);
  from_buffer(v, m.nw_src);
  from_buffer(v, m.nw_src_mask);
  from_buffer(v, m.nw_dst);
  from_buffer(v, m.nw_dst_mask);
  from_buffer(v, m.tp_src);
  from_buffer(v, m.tp_dst);
  from_buffer(v, m.mpls_label);
  from_buffer(v, m.mpls_tc);
  pad(v, 3);
  from_buffer(v, m.metadata);
  from_buffer(v, m.metadata_mask);
  return SUCCESS;
}

std::string
to_string(const Match& m, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Match");

  nvp_to_string(ss, f, "Length", m.length);

  nvp_to_string(ss, f, "Port",
                cond_to_string(wildcard_in_port(m.wildcards), "all", m.in_port),
                m.in_port);

  nvp_to_string(ss, f, "Wildcards", int(m.wildcards));

  nvp_to_string(ss, f, "Src MAC", ethernet::to_string(m.dl_src));
  nvp_to_string(ss, f, "Src MAC Mask", ethernet::to_string(m.dl_src_mask));
  nvp_to_string(ss, f, "Dst MAC", ethernet::to_string(m.dl_dst));
  nvp_to_string(ss, f, "Dst MAC Mask", ethernet::to_string(m.dl_dst_mask));

  nvp_to_string(ss, f, "VLAN ID",
                cond_to_string(wildcard_dl_vlan(m.wildcards), "all", m.dl_vlan),
                m.dl_vlan);

  nvp_to_string(ss, f, "VLAN Priority",
                cond_to_string(wildcard_dl_pcp(m.wildcards), "all",
                                int(m.dl_pcp)),
                int(m.dl_pcp));

  nvp_to_string(ss, f, "Eth TypLen",
                cond_to_string(wildcard_dl_type(m.wildcards), "all", m.dl_type),
                m.dl_type);

  nvp_to_string(ss, f, "IPv4 ToS",
                cond_to_string(wildcard_nw_tos(m.wildcards), "all",
                                int(m.nw_tos)),
                int(m.nw_tos));

  nvp_to_string(ss, f, "IPv4 Proto",
                cond_to_string(wildcard_nw_proto(m.wildcards), "all",
                                int(m.nw_proto)),
                int(m.nw_proto));

  nvp_to_string(ss, f, "IPv4 Src", ipv4::to_string(m.nw_src));
  nvp_to_string(ss, f, "IPv4 Src Mask", ipv4::to_string(m.nw_src_mask));
  nvp_to_string(ss, f, "IPv4 Dst", ipv4::to_string(m.nw_dst));
  nvp_to_string(ss, f, "IPv4 Dst Mask", ipv4::to_string(m.nw_dst_mask));

  nvp_to_string(ss, f, "L4 Src",
                cond_to_string(wildcard_tp_src(m.wildcards), "all", m.tp_src),
                m.tp_src);

  nvp_to_string(ss, f, "L4 Dst",
                cond_to_string(wildcard_tp_dst(m.wildcards), "all", m.tp_dst),
                m.tp_dst);

  nvp_to_string(ss, f, "MPLS Label", m.mpls_label);
  nvp_to_string(ss, f, "MPLS TC", int(m.mpls_tc));
  nvp_to_string(ss, f, "Metadata", m.metadata);
  nvp_to_string(ss, f, "Metadata Mask", m.metadata_mask);

  close_block(ss, f, "Match");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action type

std::string
to_string(Action_type t)
{
  switch(t){
    case ACTION_OUTPUT: return "OUTPUT";
    case ACTION_SET_VLAN_VID: return "SET_VLAN_VID";
    case ACTION_SET_VLAN_PCP: return "SET_VLAN_PCP";
    case ACTION_SET_DL_SRC: return "SET_DL_SRC";
    case ACTION_SET_DL_DST: return "SET_DL_DST";
    case ACTION_SET_NW_SRC: return "SET_NW_SRC";
    case ACTION_SET_NW_DST: return "SET_NW_DST";
    case ACTION_SET_NW_TOS: return "SET_NW_TOS";
    case ACTION_SET_NW_ECN: return "SET_NW_ECN";
    case ACTION_SET_TP_SRC: return "SET_TP_SRC";
    case ACTION_SET_TP_DST: return "SET_TP_DST";
    case ACTION_COPY_TTL_OUT: return "COPY_TTL_OUT";
    case ACTION_COPY_TTL_IN: return "COPY_TTL_IN";
    case ACTION_SET_MPLS_LABEL: return "SET_MPLS_LABEL";
    case ACTION_SET_MPLS_TC: return "SET_MPLS_TC";
    case ACTION_SET_MPLS_TTL: return "SET_MPLS_TTL";
    case ACTION_DEC_MPLS_TTL: return "DEC_MPLS_TTL";
    case ACTION_PUSH_VLAN: return "PUSH_VLAN";
    case ACTION_POP_VLAN: return "POP_VLAN";
    case ACTION_PUSH_MPLS: return "PUSH_MPLS";
    case ACTION_SET_QUEUE: return "SET_QUEUE";
    case ACTION_GROUP: return "GROUP";
    case ACTION_SET_NW_TTL: return "SET_NW_TTL";
    case ACTION_DEC_NW_TTL: return "DEC_NW_TTL";
    case ACTION_EXPERIMENTER: return "EXPERIMENTER";
    default: return "UNKNOWN";
  }
}

// -------------------------------------------------------------------------- //
// Action: Output

Error_condition
to_buffer(Buffer_view& v, const Action_output& ao)
{
  if (not available(v, bytes(ao)))
    return AVAILABLE_ACTION_OUTPUT;
  to_buffer(v, ao.port);
  to_buffer(v, ao.max_len);
  pad(v, 6);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_output& ao)
{
  if (not available(v, bytes(ao)))
    return AVAILABLE_ACTION_OUTPUT;
  from_buffer(v, ao.port);
  from_buffer(v, ao.max_len);
  pad(v, 6);
  return SUCCESS;
}

std::string
to_string(const Action_output& ao, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Output");
  nvp_to_string(ss, f, "Port", ao.port);
  nvp_to_string(ss, f, "Max Len", ao.max_len);
  close_block(ss, f, "Action Output");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: VLAN VID

Error_condition
to_buffer(Buffer_view& v, const Action_set_vlan_vid& asvv)
{
  if (not available(v, bytes(asvv)))
    return AVAILABLE_ACTION_SET_VLAN_VID;
  to_buffer(v, asvv.vlan_vid);
  pad(v, 2);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_vlan_vid& asvv)
{
  if (not available(v, bytes(asvv)))
    return AVAILABLE_ACTION_SET_VLAN_VID;
  from_buffer(v, asvv.vlan_vid);
  pad(v, 2);
  return SUCCESS;
}

std::string
to_string(const Action_set_vlan_vid& asvv, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set VLAN VID");
  nvp_to_string(ss, f, "VLAN ID", asvv.vlan_vid);
  close_block(ss, f, "Action Set VLAN VID");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: VLAN_PCP

Error_condition
to_buffer(Buffer_view& v, const Action_set_vlan_pcp& asvp)
{
  if (not available(v, bytes(asvp)))
    return AVAILABLE_ACTION_SET_VLAN_PCP;
  to_buffer(v, asvp.vlan_pcp);
  pad(v, 3);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_vlan_pcp& asvp)
{
  if (not available(v, bytes(asvp)))
    return AVAILABLE_ACTION_SET_VLAN_PCP;
  from_buffer(v, asvp.vlan_pcp);
  pad(v, 3);
  return SUCCESS;
}

std::string
to_string(const Action_set_vlan_pcp& asvp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set VLAN PCP");
  nvp_to_string(ss, f, "VLAN PCP", int(asvp.vlan_pcp));
  close_block(ss, f, "Action Set VLAN PCP");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set dl src

std::string
to_string(const Action_set_dl_src& asds, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set DL Src");
  nvp_to_string(ss, f, "Ethernet Src", ethernet::to_string(asds.dl_addr));
  close_block(ss, f, "Action Set DL Src");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set dl dst

std::string
to_string(const Action_set_dl_dst& asdd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set DL Dst");
  nvp_to_string(ss, f, "Ethernet Dst", ethernet::to_string(asdd.dl_addr));
  close_block(ss, f, "Action Set DL Dst");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set nw src

std::string
to_string(const Action_set_nw_src& asns, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set NW Src");
  nvp_to_string(ss, f, "IPv4 Src", ipv4::to_string(asns.nw_addr));
  close_block(ss, f, "Action Set NW Src");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set nw dst

std::string
to_string(const Action_set_nw_dst& asnd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set NW Dst");
  nvp_to_string(ss, f, "IPv4 Dst", ipv4::to_string(asnd.nw_addr));
  close_block(ss, f, "Action Set NW Dst");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: NW ToS

Error_condition
to_buffer(Buffer_view& v, const Action_set_nw_tos& asnt)
{
  if (not available(v, bytes(asnt)))
    return AVAILABLE_ACTION_SET_NW_TOS;
  to_buffer(v, asnt.nw_tos);
  pad(v, 3);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_nw_tos& asnt)
{
  if (not available(v, bytes(asnt)))
    return AVAILABLE_ACTION_SET_NW_TOS;
  from_buffer(v, asnt.nw_tos);
  pad(v, 3);
  return SUCCESS;
}

std::string
to_string(const Action_set_nw_tos& asnt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set NW ToS");
  nvp_to_string(ss, f, "IPv4 ToS", int(asnt.nw_tos));
  close_block(ss, f, "Action Set NW ToS");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: NW ECN

Error_condition
to_buffer(Buffer_view& v, const Action_set_nw_ecn& asne)
{
  if (not available(v, bytes(asne)))
    return AVAILABLE_ACTION_SET_NW_ECN;
  to_buffer(v, asne.nw_ecn);
  pad(v, 3);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_nw_ecn& asne)
{
  if (not available(v, bytes(asne)))
    return AVAILABLE_ACTION_SET_NW_ECN;
  from_buffer(v, asne.nw_ecn);
  pad(v, 3);
  return SUCCESS;
}

std::string
to_string(const Action_set_nw_ecn& asne, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set NW ECN");
  nvp_to_string(ss, f, "IPv4 ECN", int(asne.nw_ecn));
  close_block(ss, f, "Action Set NW ECN");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set tp src

std::string
to_string(const Action_set_tp_src& asts, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set TP Src");
  nvp_to_string(ss, f, "TP Src", asts.tp_port);
  close_block(ss, f, "Action Set TP Src");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set tp dst

std::string
to_string(const Action_set_tp_dst& astd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set TP Dst");
  nvp_to_string(ss, f, "TP Dst", astd.tp_port);
  close_block(ss, f, "Action Set TP Dst");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Copy ttl out

Error_condition
to_buffer(Buffer_view& v, const Action_copy_ttl_out& acto)
{
  if (not available(v, bytes(acto)))
    return AVAILABLE_ACTION_COPY_TTL_OUT;
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_copy_ttl_out& acto)
{
  if (not available(v, bytes(acto)))
    return AVAILABLE_ACTION_COPY_TTL_OUT;
  pad(v, 4);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action: Copy ttl in

Error_condition
to_buffer(Buffer_view& v, const Action_copy_ttl_in& acti)
{
  if (not available(v, bytes(acti)))
    return AVAILABLE_ACTION_COPY_TTL_IN;
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_copy_ttl_in& acti)
{
  if (not available(v, bytes(acti)))
    return AVAILABLE_ACTION_COPY_TTL_IN;
  pad(v, 4);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action: Set mpls label

Error_condition
to_buffer(Buffer_view& v, const Action_set_mpls_label& asml)
{
  if (not available(v, bytes(asml)))
    return AVAILABLE_ACTION_SET_MPLS_LABEL;
  to_buffer(v, asml.mpls_label);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_mpls_label& asml)
{
  if (not available(v, bytes(asml)))
    return AVAILABLE_ACTION_SET_MPLS_LABEL;
  from_buffer(v, asml.mpls_label);
  return SUCCESS;
}

std::string
to_string(const Action_set_mpls_label& asml, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set MPLS Label");
  nvp_to_string(ss, f, "MPLS Label", asml.mpls_label);
  close_block(ss, f, "Action Set MPLS Label");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set mpls tc

Error_condition
to_buffer(Buffer_view& v, const Action_set_mpls_tc& asmt)
{
  if (not available(v, bytes(asmt)))
    return AVAILABLE_ACTION_SET_MPLS_TC;
  to_buffer(v, asmt.mpls_tc);
  pad(v, 3);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_mpls_tc& asmt)
{
  if (not available(v, bytes(asmt)))
    return AVAILABLE_ACTION_SET_MPLS_TC;
  from_buffer(v, asmt.mpls_tc);
  pad(v, 3);
  return SUCCESS;
}

std::string
to_string(const Action_set_mpls_tc& asmt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set MPLS TC");
  nvp_to_string(ss, f, "MPLS TC", int(asmt.mpls_tc));
  close_block(ss, f, "Action Set MPLS TC");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set mpls ttl

std::string
to_string(const Action_set_mpls_ttl& asmt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set MPLS TTL");
  nvp_to_string(ss, f, "Set MPLS TTL", int(asmt.mpls_ttl));
  close_block(ss, f, "Action Set MPLS TTL");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Dec mpls ttl

std::string
to_string(const Action_dec_mpls_ttl& admt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Dec MPLS TTL");
  nvp_to_string(ss, f, "Dec MPLS TTL", int(admt.mpls_ttl));
  close_block(ss, f, "Action Dec MPLS TTL");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Push vlan

std::string
to_string(const Action_push_vlan& apv, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Push VLAN");
  nvp_to_string(ss, f, "Push VLAN", apv.ether_type);
  close_block(ss, f, "Action Push VLAN");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Pop vlan

std::string
to_string(const Action_pop_vlan& apv, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Pop VLAN");
  nvp_to_string(ss, f, "Pop VLAN", apv.ether_type);
  close_block(ss, f, "Action Pop VLAN");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Push mpls

std::string
to_string(const Action_push_mpls& apm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Push MPLS");
  nvp_to_string(ss, f, "Push MPLS", apm.ether_type);
  close_block(ss, f, "Action Push MPLS");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Pop mpls

std::string
to_string(const Action_pop_mpls& apm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Pop MPLS");
  nvp_to_string(ss, f, "Pop MPLS", apm.ether_type);
  close_block(ss, f, "Action Pop MPLS");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set queue

Error_condition
to_buffer(Buffer_view& v, const Action_set_queue& asq)
{
  if (not available(v, bytes(asq)))
    return AVAILABLE_ACTION_SET_QUEUE;
  to_buffer(v, asq.queue_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_queue& asq)
{
  if (not available(v, bytes(asq)))
    return AVAILABLE_ACTION_SET_QUEUE;
  from_buffer(v, asq.queue_id);
  return SUCCESS;
}

std::string
to_string(const Action_set_queue& asq, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set Queue");
  nvp_to_string(ss, f, "Queue ID", asq.queue_id);
  close_block(ss, f, "Action Set Queue");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Group

Error_condition
to_buffer(Buffer_view& v, const Action_group& ag)
{
  if (not available(v, bytes(ag)))
    return AVAILABLE_ACTION_GROUP;
  to_buffer(v, ag.group_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_group& ag)
{
  if (not available(v, bytes(ag)))
    return AVAILABLE_ACTION_GROUP;
  from_buffer(v, ag.group_id);
  return SUCCESS;
}

std::string
to_string(const Action_group& ag, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Group");
  nvp_to_string(ss, f, "Group ID", ag.group_id);
  close_block(ss, f, "Action Group");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Set nw ttl

std::string
to_string(const Action_set_nw_ttl& asnt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set NW TTL");
  nvp_to_string(ss, f, "Set IPv4 TTL", int(asnt.nw_ttl));
  close_block(ss, f, "Action Set NW TTL");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Dec nw ttl

std::string
to_string(const Action_dec_nw_ttl& adnt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Dec NW TTL");
  nvp_to_string(ss, f, "Dec IPv4 TTL", int(adnt.nw_ttl));
  open_block(ss, f, "Action Dec NW TTL");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Experimenter

Error_condition
to_buffer(Buffer_view& v, const Action_experimenter& ae)
{
  if (not available(v, bytes(ae)))
    return AVAILABLE_ACTION_EXPERIMENTER;
  to_buffer(v, ae.experimenter);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_experimenter& ae)
{
  if (not available(v, bytes(ae)))
    return AVAILABLE_ACTION_EXPERIMENTER;
  from_buffer(v, ae.experimenter);
  return SUCCESS;
}

std::string
to_string(const Action_experimenter& ae, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Experimenter");
  nvp_to_string(ss, f, "Experimenter", ae.experimenter);
  close_block(ss, f, "Action Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action Payload

void
construct(Action_payload& p, Action_type t)
{
  p.init = true;
  switch (t) {
  case ACTION_OUTPUT:
    new (&p.data.output) Action_output(); break;
  case ACTION_SET_VLAN_VID:
    new (&p.data.set_vlan_vid) Action_set_vlan_vid(); break;
  case ACTION_SET_VLAN_PCP:
    new (&p.data.set_vlan_pcp) Action_set_vlan_pcp(); break;
  case ACTION_SET_DL_SRC:
    new (&p.data.set_dl_src) Action_set_dl_src(); break;
  case ACTION_SET_DL_DST:
    new (&p.data.set_dl_dst) Action_set_dl_dst(); break;
  case ACTION_SET_NW_SRC:
    new (&p.data.set_nw_src) Action_set_nw_src(); break;
  case ACTION_SET_NW_DST:
    new (&p.data.set_nw_dst) Action_set_nw_dst(); break;
  case ACTION_SET_NW_TOS:
    new (&p.data.set_nw_tos) Action_set_nw_tos(); break;
  case ACTION_SET_NW_ECN:
    new (&p.data.set_nw_ecn) Action_set_nw_ecn(); break;
  case ACTION_SET_TP_SRC:
    new (&p.data.set_tp_src) Action_set_tp_src(); break;
  case ACTION_SET_TP_DST:
    new (&p.data.set_tp_dst) Action_set_tp_dst(); break;
  case ACTION_COPY_TTL_OUT:
    new (&p.data.copy_ttl_out) Action_copy_ttl_out(); break;
  case ACTION_COPY_TTL_IN:
    new (&p.data.copy_ttl_in) Action_copy_ttl_in(); break;
  case ACTION_SET_MPLS_LABEL:
    new (&p.data.set_mpls_label) Action_set_mpls_label(); break;
  case ACTION_SET_MPLS_TC:
    new (&p.data.set_mpls_tc) Action_set_mpls_tc(); break;
  case ACTION_SET_MPLS_TTL:
    new (&p.data.set_mpls_ttl) Action_set_mpls_ttl(); break;
  case ACTION_DEC_MPLS_TTL:
    new (&p.data.dec_mpls_ttl) Action_dec_mpls_ttl(); break;
  case ACTION_PUSH_VLAN:
    new (&p.data.push_vlan) Action_push_vlan(); break;
  case ACTION_POP_VLAN:
    new (&p.data.pop_vlan) Action_pop_vlan(); break;
  case ACTION_PUSH_MPLS:
    new (&p.data.push_mpls) Action_push_mpls(); break;
  case ACTION_POP_MPLS:
    new (&p.data.pop_mpls) Action_pop_mpls(); break;
  case ACTION_SET_QUEUE:
    new (&p.data.set_queue) Action_set_queue(); break;
  case ACTION_GROUP:
    new (&p.data.group) Action_group(); break;
  case ACTION_SET_NW_TTL:
    new (&p.data.set_nw_ttl) Action_set_nw_ttl(); break;
  case ACTION_DEC_NW_TTL:
    new (&p.data.dec_nw_ttl) Action_dec_nw_ttl(); break;
  case ACTION_EXPERIMENTER:
    new (&p.data.experimenter) Action_experimenter(); break;
  default: variant_error(t);
  }
}

void
construct(Action_payload& p, const Action_payload& x, Action_type t)
{
  p.init = x.init;
  if (not p.init)
    return;
  switch (t) {
  case ACTION_OUTPUT:
    new (&p.data.output) Action_output(x.data.output); break;
  case ACTION_SET_VLAN_VID:
    new (&p.data.set_vlan_vid) Action_set_vlan_vid(x.data.set_vlan_vid); break;
  case ACTION_SET_VLAN_PCP:
    new (&p.data.set_vlan_pcp) Action_set_vlan_pcp(x.data.set_vlan_pcp); break;
  case ACTION_SET_DL_SRC:
    new (&p.data.set_dl_src) Action_set_dl_src(x.data.set_dl_src); break;
  case ACTION_SET_DL_DST:
    new (&p.data.set_dl_dst) Action_set_dl_dst(x.data.set_dl_dst); break;
  case ACTION_SET_NW_SRC:
    new (&p.data.set_nw_src) Action_set_nw_src(x.data.set_nw_src); break;
  case ACTION_SET_NW_DST:
    new (&p.data.set_nw_dst) Action_set_nw_dst(x.data.set_nw_dst); break;
  case ACTION_SET_NW_TOS:
    new (&p.data.set_nw_tos) Action_set_nw_tos(x.data.set_nw_tos); break;
  case ACTION_SET_NW_ECN:
    new (&p.data.set_nw_ecn) Action_set_nw_ecn(x.data.set_nw_ecn); break;
  case ACTION_SET_TP_SRC:
    new (&p.data.set_tp_src) Action_set_tp_src(x.data.set_tp_src); break;
  case ACTION_SET_TP_DST:
    new (&p.data.set_tp_dst) Action_set_tp_dst(x.data.set_tp_dst); break;
  case ACTION_COPY_TTL_OUT:
    new (&p.data.copy_ttl_out) Action_copy_ttl_out(x.data.copy_ttl_out); break;
  case ACTION_COPY_TTL_IN:
    new (&p.data.copy_ttl_in) Action_copy_ttl_in(x.data.copy_ttl_in); break;
  case ACTION_SET_MPLS_LABEL:
    new (&p.data.set_mpls_label) Action_set_mpls_label(x.data.set_mpls_label);
    break;
  case ACTION_SET_MPLS_TC:
    new (&p.data.set_mpls_tc) Action_set_mpls_tc(x.data.set_mpls_tc); break;
  case ACTION_SET_MPLS_TTL:
    new (&p.data.set_mpls_ttl) Action_set_mpls_ttl(x.data.set_mpls_ttl); break;
  case ACTION_DEC_MPLS_TTL:
    new (&p.data.dec_mpls_ttl) Action_dec_mpls_ttl(x.data.dec_mpls_ttl); break;
  case ACTION_PUSH_VLAN:
    new (&p.data.push_vlan) Action_push_vlan(x.data.push_vlan); break;
  case ACTION_POP_VLAN:
    new (&p.data.pop_vlan) Action_pop_vlan(x.data.pop_vlan); break;
  case ACTION_PUSH_MPLS:
    new (&p.data.push_mpls) Action_push_mpls(x.data.push_mpls); break;
  case ACTION_POP_MPLS:
    new (&p.data.pop_mpls) Action_pop_mpls(x.data.pop_mpls); break;
  case ACTION_SET_QUEUE:
    new (&p.data.set_queue) Action_set_queue(x.data.set_queue); break;
  case ACTION_GROUP:
    new (&p.data.group) Action_group(x.data.group); break;
  case ACTION_SET_NW_TTL:
    new (&p.data.set_nw_ttl) Action_set_nw_ttl(x.data.set_nw_ttl); break;
  case ACTION_DEC_NW_TTL:
    new (&p.data.dec_nw_ttl) Action_dec_nw_ttl(x.data.dec_nw_ttl); break;
  case ACTION_EXPERIMENTER:
    new (&p.data.experimenter) Action_experimenter(x.data.experimenter); break;
  default: variant_error(t);
  }
}

Action_payload&
assign(Action_payload& a, const Action_payload& b, Action_type t)
{
  if (&a == &b)
    return a;

  a.init = b.init;
  if (not a.init)
    return a;
  
  switch (t) {
  case ACTION_OUTPUT: a.data.output = b.data.output; break;
  case ACTION_SET_VLAN_VID: a.data.set_vlan_vid = b.data.set_vlan_vid; break;
  case ACTION_SET_VLAN_PCP: a.data.set_vlan_pcp = b.data.set_vlan_pcp; break;
  case ACTION_SET_DL_SRC: a.data.set_dl_src = b.data.set_dl_src; break;
  case ACTION_SET_DL_DST: a.data.set_dl_dst = b.data.set_dl_dst; break;
  case ACTION_SET_NW_SRC: a.data.set_nw_src = b.data.set_nw_src; break;
  case ACTION_SET_NW_DST: a.data.set_nw_dst = b.data.set_nw_dst; break;
  case ACTION_SET_NW_TOS: a.data.set_nw_tos = b.data.set_nw_tos; break;
  case ACTION_SET_NW_ECN: a.data.set_nw_ecn = b.data.set_nw_ecn; break;
  case ACTION_SET_TP_SRC: a.data.set_tp_src = b.data.set_tp_src; break;
  case ACTION_SET_TP_DST: a.data.set_tp_dst = b.data.set_tp_dst; break;
  case ACTION_COPY_TTL_OUT: a.data.copy_ttl_out = b.data.copy_ttl_out; break;
  case ACTION_COPY_TTL_IN: a.data.copy_ttl_in = b.data.copy_ttl_in; break;
  case ACTION_SET_MPLS_LABEL:
    a.data.set_mpls_label = b.data.set_mpls_label; break;
  case ACTION_SET_MPLS_TC: a.data.set_mpls_tc = b.data.set_mpls_tc; break;
  case ACTION_SET_MPLS_TTL: a.data.set_mpls_ttl = b.data.set_mpls_ttl; break;
  case ACTION_DEC_MPLS_TTL: a.data.dec_mpls_ttl = b.data.dec_mpls_ttl; break;
  case ACTION_PUSH_VLAN: a.data.push_vlan = b.data.push_vlan; break;
  case ACTION_POP_VLAN: a.data.pop_vlan = b.data.pop_vlan; break;
  case ACTION_PUSH_MPLS: a.data.push_mpls = b.data.push_mpls; break;
  case ACTION_POP_MPLS: a.data.pop_mpls = b.data.pop_mpls; break;
  case ACTION_SET_QUEUE: a.data.set_queue = b.data.set_queue; break;
  case ACTION_GROUP: a.data.group = b.data.group; break;
  case ACTION_SET_NW_TTL: a.data.set_nw_ttl = b.data.set_nw_ttl; break;
  case ACTION_DEC_NW_TTL: a.data.dec_nw_ttl = b.data.dec_nw_ttl; break;
  case ACTION_EXPERIMENTER: a.data.experimenter = b.data.experimenter; break;
  default: variant_error(t);
  }
  return a;
}

bool
equal(const Action_payload& a, const Action_payload& b,
              Action_type t1, Action_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case ACTION_OUTPUT: return a.data.output == b.data.output;
  case ACTION_SET_VLAN_VID: return a.data.set_vlan_vid == b.data.set_vlan_vid;
  case ACTION_SET_VLAN_PCP: return a.data.set_vlan_pcp == b.data.set_vlan_pcp;
  case ACTION_SET_DL_SRC: return a.data.set_dl_src == b.data.set_dl_src;
  case ACTION_SET_DL_DST: return a.data.set_dl_dst == b.data.set_dl_dst;
  case ACTION_SET_NW_SRC: return a.data.set_nw_src == b.data.set_nw_src;
  case ACTION_SET_NW_DST: return a.data.set_nw_dst == b.data.set_nw_dst;
  case ACTION_SET_NW_TOS: return a.data.set_nw_tos == b.data.set_nw_tos;
  case ACTION_SET_NW_ECN: return a.data.set_nw_ecn == b.data.set_nw_ecn;
  case ACTION_SET_TP_SRC: return a.data.set_tp_src == b.data.set_tp_src;
  case ACTION_SET_TP_DST: return a.data.set_tp_dst == b.data.set_tp_dst;
  case ACTION_COPY_TTL_OUT: return a.data.copy_ttl_out == b.data.copy_ttl_out;
  case ACTION_COPY_TTL_IN: return a.data.copy_ttl_in == b.data.copy_ttl_in;
  case ACTION_SET_MPLS_LABEL:
    return a.data.set_mpls_label == b.data.set_mpls_label;
  case ACTION_SET_MPLS_TC: return a.data.set_mpls_tc == b.data.set_mpls_tc;
  case ACTION_SET_MPLS_TTL: return a.data.set_mpls_ttl == b.data.set_mpls_ttl;
  case ACTION_DEC_MPLS_TTL: return a.data.dec_mpls_ttl == b.data.dec_mpls_ttl;
  case ACTION_PUSH_VLAN: return a.data.push_vlan == b.data.push_vlan;
  case ACTION_POP_VLAN: return a.data.pop_vlan == b.data.pop_vlan;
  case ACTION_PUSH_MPLS: return a.data.push_mpls == b.data.push_mpls;
  case ACTION_POP_MPLS: return a.data.pop_mpls == b.data.pop_mpls;
  case ACTION_SET_QUEUE: return a.data.set_queue == b.data.set_queue;
  case ACTION_GROUP: return a.data.group == b.data.group;
  case ACTION_SET_NW_TTL: return a.data.set_nw_ttl == b.data.set_nw_ttl;
  case ACTION_DEC_NW_TTL: return a.data.dec_nw_ttl == b.data.dec_nw_ttl;
  case ACTION_EXPERIMENTER: return a.data.experimenter == b.data.experimenter;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Action_payload& p, Action_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case ACTION_OUTPUT: return bytes(p.data.output);
  case ACTION_SET_VLAN_VID: return bytes(p.data.set_vlan_vid);
  case ACTION_SET_VLAN_PCP: return bytes(p.data.set_vlan_pcp);
  case ACTION_SET_DL_SRC: return bytes(p.data.set_dl_src);
  case ACTION_SET_DL_DST: return bytes(p.data.set_dl_dst);
  case ACTION_SET_NW_SRC: return bytes(p.data.set_nw_src);
  case ACTION_SET_NW_DST: return bytes(p.data.set_nw_dst);
  case ACTION_SET_NW_TOS: return bytes(p.data.set_nw_tos);
  case ACTION_SET_NW_ECN: return bytes(p.data.set_nw_ecn);
  case ACTION_SET_TP_SRC: return bytes(p.data.set_tp_src);
  case ACTION_SET_TP_DST: return bytes(p.data.set_tp_dst);
  case ACTION_COPY_TTL_OUT: return bytes(p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return bytes(p.data.copy_ttl_in);
  case ACTION_SET_MPLS_LABEL: return bytes(p.data.set_mpls_label);
  case ACTION_SET_MPLS_TC: return bytes(p.data.set_mpls_tc);
  case ACTION_SET_MPLS_TTL: return bytes(p.data.set_mpls_ttl);
  case ACTION_DEC_MPLS_TTL: return bytes(p.data.dec_mpls_ttl);
  case ACTION_PUSH_VLAN: return bytes(p.data.push_vlan);
  case ACTION_POP_VLAN: return bytes(p.data.pop_vlan);
  case ACTION_PUSH_MPLS: return bytes(p.data.push_mpls);
  case ACTION_POP_MPLS: return bytes(p.data.pop_mpls);
  case ACTION_SET_QUEUE: return bytes(p.data.set_queue);
  case ACTION_GROUP: return bytes(p.data.group);
  case ACTION_SET_NW_TTL: return bytes(p.data.set_nw_ttl);
  case ACTION_DEC_NW_TTL: return bytes(p.data.dec_nw_ttl);
  case ACTION_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}


Error_condition
is_valid(const Action_payload& p, Action_type t)
{
  if (not p)
    return BAD_ACTION_INIT;
  switch (t) {
  case ACTION_OUTPUT: return is_valid(p.data.output);
  case ACTION_SET_VLAN_VID: return is_valid(p.data.set_vlan_vid);
  case ACTION_SET_VLAN_PCP: return is_valid(p.data.set_vlan_pcp);
  case ACTION_SET_DL_SRC: return is_valid(p.data.set_dl_src);
  case ACTION_SET_DL_DST: return is_valid(p.data.set_dl_dst);
  case ACTION_SET_NW_SRC: return is_valid(p.data.set_nw_src);
  case ACTION_SET_NW_DST: return is_valid(p.data.set_nw_dst);
  case ACTION_SET_NW_TOS: return is_valid(p.data.set_nw_tos);
  case ACTION_SET_NW_ECN: return is_valid(p.data.set_nw_ecn);
  case ACTION_SET_TP_SRC: return is_valid(p.data.set_tp_src);
  case ACTION_SET_TP_DST: return is_valid(p.data.set_tp_dst);
  case ACTION_COPY_TTL_OUT: return is_valid(p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return is_valid(p.data.copy_ttl_in);
  case ACTION_SET_MPLS_LABEL: return is_valid(p.data.set_mpls_label);
  case ACTION_SET_MPLS_TC: return is_valid(p.data.set_mpls_tc);
  case ACTION_SET_MPLS_TTL: return is_valid(p.data.set_mpls_ttl);
  case ACTION_DEC_MPLS_TTL: return is_valid(p.data.dec_mpls_ttl);
  case ACTION_PUSH_VLAN: return is_valid(p.data.push_vlan);
  case ACTION_POP_VLAN: return is_valid(p.data.pop_vlan);
  case ACTION_PUSH_MPLS: return is_valid(p.data.push_mpls);
  case ACTION_POP_MPLS: return is_valid(p.data.pop_mpls);
  case ACTION_SET_QUEUE: return is_valid(p.data.set_queue);
  case ACTION_GROUP: return is_valid(p.data.group);
  case ACTION_SET_NW_TTL: return is_valid(p.data.set_nw_ttl);
  case ACTION_DEC_NW_TTL: return is_valid(p.data.dec_nw_ttl);
  case ACTION_EXPERIMENTER: return is_valid(p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_ACTION;
}


Error_condition
to_buffer(Buffer_view& v, const Action_payload& p, Action_type t)
{
  assert(p);
  switch (t) {
  case ACTION_OUTPUT: return to_buffer(v, p.data.output);
  case ACTION_SET_VLAN_VID: return to_buffer(v, p.data.set_vlan_vid);
  case ACTION_SET_VLAN_PCP: return to_buffer(v, p.data.set_vlan_pcp);
  case ACTION_SET_DL_SRC: return to_buffer(v, p.data.set_dl_src);
  case ACTION_SET_DL_DST: return to_buffer(v, p.data.set_dl_dst);
  case ACTION_SET_NW_SRC: return to_buffer(v, p.data.set_nw_src);
  case ACTION_SET_NW_DST: return to_buffer(v, p.data.set_nw_dst);
  case ACTION_SET_NW_TOS: return to_buffer(v, p.data.set_nw_tos);
  case ACTION_SET_NW_ECN: return to_buffer(v, p.data.set_nw_ecn);
  case ACTION_SET_TP_SRC: return to_buffer(v, p.data.set_tp_src);
  case ACTION_SET_TP_DST: return to_buffer(v, p.data.set_tp_dst);
  case ACTION_COPY_TTL_OUT: return to_buffer(v, p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return to_buffer(v, p.data.copy_ttl_in);
  case ACTION_SET_MPLS_LABEL: return to_buffer(v, p.data.set_mpls_label);
  case ACTION_SET_MPLS_TC: return to_buffer(v, p.data.set_mpls_tc);
  case ACTION_SET_MPLS_TTL: return to_buffer(v, p.data.set_mpls_ttl);
  case ACTION_DEC_MPLS_TTL: return to_buffer(v, p.data.dec_mpls_ttl);
  case ACTION_PUSH_VLAN: return to_buffer(v, p.data.push_vlan);
  case ACTION_POP_VLAN: return to_buffer(v, p.data.pop_vlan);
  case ACTION_PUSH_MPLS: return to_buffer(v, p.data.push_mpls);
  case ACTION_POP_MPLS: return to_buffer(v, p.data.pop_mpls);
  case ACTION_SET_QUEUE: return to_buffer(v, p.data.set_queue);
  case ACTION_GROUP: return to_buffer(v, p.data.group);
  case ACTION_SET_NW_TTL: return to_buffer(v, p.data.set_nw_ttl);
  case ACTION_DEC_NW_TTL: return to_buffer(v, p.data.dec_nw_ttl);
  case ACTION_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t)
  }
  return BAD_ACTION;
}

Error_condition
from_buffer(Buffer_view& v, Action_payload& p, Action_type t)
{
  assert(p);
  switch (t) {
  case ACTION_OUTPUT: return from_buffer(v, p.data.output);
  case ACTION_SET_VLAN_VID: return from_buffer(v, p.data.set_vlan_vid);
  case ACTION_SET_VLAN_PCP: return from_buffer(v, p.data.set_vlan_pcp);
  case ACTION_SET_DL_SRC: return from_buffer(v, p.data.set_dl_src);
  case ACTION_SET_DL_DST: return from_buffer(v, p.data.set_dl_dst);
  case ACTION_SET_NW_SRC: return from_buffer(v, p.data.set_nw_src);
  case ACTION_SET_NW_DST: return from_buffer(v, p.data.set_nw_dst);
  case ACTION_SET_NW_TOS: return from_buffer(v, p.data.set_nw_tos);
  case ACTION_SET_NW_ECN: return from_buffer(v, p.data.set_nw_ecn);
  case ACTION_SET_TP_SRC: return from_buffer(v, p.data.set_tp_src);
  case ACTION_SET_TP_DST: return from_buffer(v, p.data.set_tp_dst);
  case ACTION_COPY_TTL_OUT: return from_buffer(v, p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return from_buffer(v, p.data.copy_ttl_in);
  case ACTION_SET_MPLS_LABEL: return from_buffer(v, p.data.set_mpls_label);
  case ACTION_SET_MPLS_TC: return from_buffer(v, p.data.set_mpls_tc);
  case ACTION_SET_MPLS_TTL: return from_buffer(v, p.data.set_mpls_ttl);
  case ACTION_DEC_MPLS_TTL: return from_buffer(v, p.data.dec_mpls_ttl);
  case ACTION_PUSH_VLAN: return from_buffer(v, p.data.push_vlan);
  case ACTION_POP_VLAN: return from_buffer(v, p.data.pop_vlan);
  case ACTION_PUSH_MPLS: return from_buffer(v, p.data.push_mpls);
  case ACTION_POP_MPLS: return from_buffer(v, p.data.pop_mpls);
  case ACTION_SET_QUEUE: return from_buffer(v, p.data.set_queue);
  case ACTION_GROUP: return from_buffer(v, p.data.group);
  case ACTION_SET_NW_TTL: return from_buffer(v, p.data.set_nw_ttl);
  case ACTION_DEC_NW_TTL: return from_buffer(v, p.data.dec_nw_ttl);
  case ACTION_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  default: variant_error(t)
  }
  return BAD_ACTION;
}

std::string
to_string(const Action_payload& p, Formatter& fmt, Action_type t)
{
  assert(p);
  switch (t) {
  case ACTION_OUTPUT: return to_string(p.data.output, fmt);
  case ACTION_SET_VLAN_VID: return to_string(p.data.set_vlan_vid, fmt);
  case ACTION_SET_VLAN_PCP: return to_string(p.data.set_vlan_pcp, fmt);
  case ACTION_SET_DL_SRC: return to_string(p.data.set_dl_src, fmt);
  case ACTION_SET_DL_DST: return to_string(p.data.set_dl_dst, fmt);
  case ACTION_SET_NW_SRC: return to_string(p.data.set_nw_src, fmt);
  case ACTION_SET_NW_DST: return to_string(p.data.set_nw_dst, fmt);
  case ACTION_SET_NW_TOS: return to_string(p.data.set_nw_tos, fmt);
  case ACTION_SET_NW_ECN: return to_string(p.data.set_nw_tos, fmt);
  case ACTION_SET_TP_SRC: return to_string(p.data.set_tp_src, fmt);
  case ACTION_SET_TP_DST: return to_string(p.data.set_tp_dst, fmt);
  case ACTION_COPY_TTL_OUT: return to_string(p.data.copy_ttl_out, fmt);
  case ACTION_COPY_TTL_IN: return to_string(p.data.copy_ttl_in, fmt);
  case ACTION_SET_MPLS_LABEL: return to_string(p.data.set_mpls_label, fmt);
  case ACTION_SET_MPLS_TC: return to_string(p.data.set_mpls_tc, fmt);
  case ACTION_SET_MPLS_TTL: return to_string(p.data.set_mpls_ttl, fmt);
  case ACTION_DEC_MPLS_TTL: return to_string(p.data.dec_mpls_ttl, fmt);
  case ACTION_PUSH_VLAN: return to_string(p.data.push_vlan, fmt);
  case ACTION_POP_VLAN: return to_string(p.data.pop_vlan, fmt);
  case ACTION_PUSH_MPLS: return to_string(p.data.push_mpls, fmt);
  case ACTION_POP_MPLS: return to_string(p.data.pop_mpls, fmt);
  case ACTION_SET_QUEUE: return to_string(p.data.set_queue, fmt);
  case ACTION_GROUP: return to_string(p.data.group, fmt);
  case ACTION_SET_NW_TTL: return to_string(p.data.set_nw_ttl, fmt);
  case ACTION_DEC_NW_TTL: return to_string(p.data.dec_nw_ttl, fmt);
  case ACTION_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t)
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Action header

Error_condition
to_buffer(Buffer_view& v, const Action_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.length);
  return SUCCESS;
}

std::string
to_string(const Action_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);

  close_block(ss, f, "Action Hdr");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action

Error_condition
to_buffer(Buffer_view& v, const Action& a)
{
  if (not available(v, bytes(a.header)))
    return AVAILABLE_ACTION_HEADER;
  to_buffer(v, a.header);

  if (Error_decl err = is_valid(a.header.type))
    return err;

  return to_buffer(v, a.payload, a.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Action& a)
{
  if (not available(v, bytes(a.header)))
    return AVAILABLE_ACTION_HEADER;
  from_buffer(v, a.header);

  if (a.header.length < bytes(a.header))
    return BAD_ACTION_LENGTH;

  if (Error_decl err = is_valid(a.header.type))
    return err;
  
  Action::Payload p;
  construct(p, a.header.type);
  assign(a.payload, std::move(p), a.header.type);

  std::size_t n = a.header.length - bytes(a.header);
  if (remaining(v) < n)
    return AVAILABLE_ACTION_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, a.payload, a.header.type))
    return err;
  
  if(not update(v, c))
    return EXCESS_ACTION;
  
  return SUCCESS;
}

std::string
to_string(const Action& a, Formatter& f)
{
  std::stringstream ss;

  open_block(ss, f, "Action");
  ss << to_string(a.header, f);
  if (not is_valid(a.header))
    ss << to_string(a.payload, f, a.header.type);
  close_block(ss, f, "Action");

  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction type

std::string
to_string(Instruction_type t)
{
  switch(t) {
    case INSTRUCTION_GOTO_TABLE: return "INSTRUCTION_GOTO_TABLE";
    case INSTRUCTION_WRITE_METADATA: return "INSTRUCTION_WRITE_METADATA";
    case INSTRUCTION_WRITE_ACTIONS: return "INSTRUCTION_WRITE_ACTIONS";
    case INSTRUCTION_APPLY_ACTIONS: return "INSTRUCTION_APPLY_ACTIONS";
    case INSTRUCTION_CLEAR_ACTIONS: return "INSTRUCTION_CLEAR_ACTIONS";
    case INSTRUCTION_EXPERIMENTER: return "INSTRUCTION_EXPERIMENTER";
    default: return "UNKNOWN";
  }
}

// -------------------------------------------------------------------------- //
// Instruction: Goto table

Error_condition
to_buffer(Buffer_view& v, const Instruction_goto_table& igt)
{
  if (not available(v, bytes(igt)))
    return AVAILABLE_INSTRUCTION_GOTO_TABLE;
  to_buffer(v, igt.table_id);
  pad(v, 3);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_goto_table& igt)
{
  if (not available(v, bytes(igt)))
    return AVAILABLE_INSTRUCTION_GOTO_TABLE;
  from_buffer(v, igt.table_id);
  pad(v, 3);
  return SUCCESS;
}

std::string
to_string(const Instruction_goto_table& igt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Goto Table");
  nvp_to_string(ss, f, "Table ID", int(igt.table_id));
  close_block(ss, f, "Instruction Goto Table");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction: Write metadata

Error_condition
to_buffer(Buffer_view& v, const Instruction_write_metadata& iwm)
{
  if (not available(v, bytes(iwm)))
    return AVAILABLE_INSTRUCTION_WRITE_METADATA;
  pad(v, 4);
  to_buffer(v, iwm.metadata);
  to_buffer(v, iwm.metadata_mask);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_write_metadata& iwm)
{
  if (not available(v, bytes(iwm)))
    return AVAILABLE_INSTRUCTION_WRITE_METADATA;
  pad(v, 4);
  from_buffer(v, iwm.metadata);
  from_buffer(v, iwm.metadata_mask);
  return SUCCESS;
}

std::string
to_string(const Instruction_write_metadata& iwm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Write Metadata");
  nvp_to_string(ss, f, "Metadata", iwm.metadata);
  nvp_to_string(ss, f, "Metadata Mask",  iwm.metadata_mask);
  close_block(ss, f, "Instruction Write Metadata");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction: Write Actions

std::string
to_string(const Instruction_write_actions& iwa, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Write Actions");
  ss << to_string(iwa.actions, f);
  close_block(ss, f, "Instruction Write Actions");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction: Apply Actions

std::string
to_string(const Instruction_apply_actions& iaa, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Apply Actions");
  ss << to_string(iaa.actions, f);
  close_block(ss, f, "Instruction Apply Actions");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction: Clear Actions

std::string
to_string(const Instruction_clear_actions& ica, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Clear Actions");
  ss << to_string(ica.actions, f);
  close_block(ss, f, "Instruction Clear Actions");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction: Experimenter

Error_condition
to_buffer(Buffer_view& v, const Instruction_experimenter& ie)
{
  if (not available(v, bytes(ie)))
    return AVAILABLE_INSTRUCTION_EXPERIMENTER;
  to_buffer(v, ie.experimenter_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_experimenter& ie)
{
  if (not available(v, bytes(ie)))
    return AVAILABLE_INSTRUCTION_EXPERIMENTER;
  from_buffer(v, ie.experimenter_id);
  return SUCCESS;
}

std::string
to_string(const Instruction_experimenter& ie, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Experimenter");
  nvp_to_string(ss, f, "Experimenter ID", ie.experimenter_id);
  close_block(ss, f, "Instruction Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction payload

void
construct(Instruction_payload& p, Instruction_type t)
{
  p.init = true;
  switch(t) {
  case INSTRUCTION_GOTO_TABLE:
    new (&p.data.goto_table) Instruction_goto_table(); break;
  case INSTRUCTION_WRITE_METADATA:
    new (&p.data.write_metadata) Instruction_write_metadata(); break;
  case INSTRUCTION_WRITE_ACTIONS:
    new (&p.data.write_actions) Instruction_write_actions(); break;
  case INSTRUCTION_APPLY_ACTIONS:
    new (&p.data.apply_actions) Instruction_apply_actions(); break;
  case INSTRUCTION_CLEAR_ACTIONS:
    new (&p.data.clear_actions) Instruction_clear_actions(); break;
  case INSTRUCTION_EXPERIMENTER:
    new (&p.data.experimenter) Instruction_experimenter(); break;
  default: variant_error(t);
  }
}

void
construct(Instruction_payload& p, Instruction_payload&& x,
          Instruction_type t)
{
  p.init = x.init;
  if (not p.init)
    return;
  switch(t) {
  case INSTRUCTION_GOTO_TABLE:
    new (&p.data.goto_table)
        Instruction_goto_table(std::move(x.data.goto_table)); break;
  case INSTRUCTION_WRITE_METADATA:
    new (&p.data.write_metadata)
        Instruction_write_metadata(std::move(x.data.write_metadata)); break;
  case INSTRUCTION_WRITE_ACTIONS:
    new (&p.data.write_actions)
        Instruction_write_actions(std::move(x.data.write_actions)); break;
  case INSTRUCTION_APPLY_ACTIONS:
    new (&p.data.apply_actions)
        Instruction_apply_actions(std::move(x.data.apply_actions)); break;
  case INSTRUCTION_CLEAR_ACTIONS:
    new (&p.data.clear_actions)
        Instruction_clear_actions(std::move(x.data.clear_actions)); break;
  case INSTRUCTION_EXPERIMENTER:
    new (&p.data.experimenter)
        Instruction_experimenter(std::move(x.data.experimenter)); break;
  default: variant_error(t);
  }
}

void
construct(Instruction_payload& p, const Instruction_payload& x,
          Instruction_type t)
{
  p.init = x.init;
  if (not p.init)
    return;
  switch(t) {
  case INSTRUCTION_GOTO_TABLE:
    new (&p.data.goto_table) Instruction_goto_table(x.data.goto_table); break;
  case INSTRUCTION_WRITE_METADATA:
    new (&p.data.write_metadata)
    Instruction_write_metadata(x.data.write_metadata); break;
  case INSTRUCTION_WRITE_ACTIONS:
    new (&p.data.write_actions)
    Instruction_write_actions(x.data.write_actions); break;
  case INSTRUCTION_APPLY_ACTIONS:
    new (&p.data.apply_actions)
    Instruction_apply_actions(x.data.apply_actions); break;
  case INSTRUCTION_CLEAR_ACTIONS:
    new (&p.data.clear_actions)
    Instruction_clear_actions(x.data.clear_actions); break;
  case INSTRUCTION_EXPERIMENTER:
    new (&p.data.experimenter) Instruction_experimenter(x.data.experimenter);
    break;
  default: variant_error(t);
  }
}

void
destroy(Instruction_payload& p, Instruction_type t)
{
  switch(t) {
  case INSTRUCTION_GOTO_TABLE: p.data.goto_table.~Instruction_goto_table(); break;
  case INSTRUCTION_WRITE_METADATA: p.data.write_metadata.~Instruction_write_metadata(); break;
  case INSTRUCTION_WRITE_ACTIONS: p.data.write_actions.~Instruction_write_actions(); break;
  case INSTRUCTION_APPLY_ACTIONS: p.data.apply_actions.~Instruction_apply_actions(); break;
  case INSTRUCTION_CLEAR_ACTIONS: p.data.clear_actions.~Instruction_clear_actions(); break;
  case INSTRUCTION_EXPERIMENTER: p.data.experimenter.~Instruction_experimenter(); break;
  default: return;
  }
}

Instruction_payload&
assign(Instruction_payload& a, Instruction_payload&& b, Instruction_type t)
{
  if (&a == &b)
    return a;

  if (not a) {
    construct(a, std::move(b), t);
    return a;
  }

  a.init = b.init;
  if (not a) {
    destroy(a, t);
    return a;
  }
  
  switch(t) {
  case INSTRUCTION_GOTO_TABLE:
    a.data.goto_table = std::move(b.data.goto_table); break;
  case INSTRUCTION_WRITE_METADATA:
    a.data.write_metadata = std::move(b.data.write_metadata); break;
  case INSTRUCTION_WRITE_ACTIONS:
    a.data.write_actions = std::move(b.data.write_actions); break;
  case INSTRUCTION_APPLY_ACTIONS:
    a.data.apply_actions = std::move(b.data.apply_actions); break;
  case INSTRUCTION_CLEAR_ACTIONS:
    a.data.clear_actions = std::move(b.data.clear_actions); break;
  case INSTRUCTION_EXPERIMENTER:
    a.data.experimenter = std::move(b.data.experimenter); break;
  default: variant_error(t);
  }
  return a;
}

Instruction_payload&
assign(Instruction_payload& a, const Instruction_payload& b, Instruction_type t)
{
  if (&a == &b)
    return a;

  if (not a) {
    construct(a, b, t);
    return a;
  }

  a.init = b.init;
  if (not a) {
    destroy(a, t);
    return a;
  }

  switch(t) {
  case INSTRUCTION_GOTO_TABLE: a.data.goto_table = b.data.goto_table; break;
  case INSTRUCTION_WRITE_METADATA: a.data.write_metadata = b.data.write_metadata; break;
  case INSTRUCTION_WRITE_ACTIONS: a.data.write_actions = b.data.write_actions; break;
  case INSTRUCTION_APPLY_ACTIONS: a.data.apply_actions = b.data.apply_actions; break;
  case INSTRUCTION_CLEAR_ACTIONS: a.data.clear_actions = b.data.clear_actions; break;
  case INSTRUCTION_EXPERIMENTER: a.data.experimenter = b.data.experimenter; break;
  default: variant_error(t);
  }
  return a;
}

bool
equal(const Instruction_payload& a, const Instruction_payload& b,
      Instruction_type t1, Instruction_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch(t1) {
  case INSTRUCTION_GOTO_TABLE: return a.data.goto_table == b.data.goto_table;
  case INSTRUCTION_WRITE_METADATA:
    return a.data.write_metadata == b.data.write_metadata;
  case INSTRUCTION_WRITE_ACTIONS:
    return a.data.write_actions == b.data.write_actions;
  case INSTRUCTION_APPLY_ACTIONS:
    return a.data.apply_actions == b.data.apply_actions;
  case INSTRUCTION_CLEAR_ACTIONS:
    return a.data.clear_actions == b.data.clear_actions;
  case INSTRUCTION_EXPERIMENTER:
    return a.data.experimenter == b.data.experimenter;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Instruction_payload& p, Instruction_type t)
{
  if (not p)
    return 0;
  switch(t) {
  case INSTRUCTION_GOTO_TABLE: return bytes(p.data.goto_table);
  case INSTRUCTION_WRITE_METADATA: return bytes(p.data.write_metadata);
  case INSTRUCTION_WRITE_ACTIONS: return bytes(p.data.write_actions);
  case INSTRUCTION_APPLY_ACTIONS: return bytes(p.data.apply_actions);
  case INSTRUCTION_CLEAR_ACTIONS: return bytes(p.data.clear_actions);
  case INSTRUCTION_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Instruction_payload& p, Instruction_type t)
{
  if (not p)
    return BAD_INSTRUCTION_INIT;
  switch (t) {
  case INSTRUCTION_GOTO_TABLE: return is_valid(p.data.goto_table);
  case INSTRUCTION_WRITE_METADATA: return is_valid(p.data.write_metadata);
  case INSTRUCTION_WRITE_ACTIONS: return is_valid(p.data.write_actions);
  case INSTRUCTION_APPLY_ACTIONS: return is_valid(p.data.apply_actions);
  case INSTRUCTION_CLEAR_ACTIONS: return is_valid(p.data.clear_actions);
  case INSTRUCTION_EXPERIMENTER: return is_valid(p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_INSTRUCTION;
}

Error_condition
to_buffer(Buffer_view& v, const Instruction_payload& p, Instruction_type t)
{
  assert(p);
  switch(t) {
  case INSTRUCTION_GOTO_TABLE: return to_buffer(v, p.data.goto_table);
  case INSTRUCTION_WRITE_METADATA: return to_buffer(v, p.data.write_metadata);
  case INSTRUCTION_WRITE_ACTIONS: return to_buffer(v, p.data.write_actions);
  case INSTRUCTION_APPLY_ACTIONS: return to_buffer(v, p.data.apply_actions);
  case INSTRUCTION_CLEAR_ACTIONS: return to_buffer(v, p.data.clear_actions);
  case INSTRUCTION_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_INSTRUCTION;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_payload& p, Instruction_type t)
{
  assert(p);
  switch(t) {
  case INSTRUCTION_GOTO_TABLE: return from_buffer(v, p.data.goto_table);
  case INSTRUCTION_WRITE_METADATA: return from_buffer(v, p.data.write_metadata);
  case INSTRUCTION_WRITE_ACTIONS: return from_buffer(v, p.data.write_actions);
  case INSTRUCTION_APPLY_ACTIONS: return from_buffer(v, p.data.apply_actions);
  case INSTRUCTION_CLEAR_ACTIONS: return from_buffer(v, p.data.clear_actions);
  case INSTRUCTION_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_INSTRUCTION;
}

std::string
to_string(const Instruction_payload& p, Formatter& fmt, Instruction_type t)
{
  assert(p);
  switch(t) {
  case INSTRUCTION_GOTO_TABLE: return to_string(p.data.goto_table, fmt);
  case INSTRUCTION_WRITE_METADATA:
    return to_string(p.data.write_metadata, fmt);
  case INSTRUCTION_WRITE_ACTIONS: return to_string(p.data.write_actions, fmt);
  case INSTRUCTION_APPLY_ACTIONS: return to_string(p.data.apply_actions, fmt);
  case INSTRUCTION_CLEAR_ACTIONS: return to_string(p.data.clear_actions, fmt);
  case INSTRUCTION_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Instruction header

Error_condition
to_buffer(Buffer_view& v, const Instruction_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.length);
  return SUCCESS;
}

std::string
to_string(const Instruction_header& h, Formatter& f)
{
  std::stringstream ss;

  open_block(ss, f, "Instruction Hdr");
  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);
  close_block(ss, f, "Instruction Hdr");

  return ss.str();
}


// -------------------------------------------------------------------------- //
// Instruction

Error_condition
to_buffer(Buffer_view& v, const Instruction& i)
{
  if (not available(v, bytes(i.header)))
    return AVAILABLE_INSTRUCTION_HEADER;
  to_buffer(v, i.header);
  
  if (Error_decl err = is_valid(i.header))
    return err;

  return to_buffer(v, i.payload, i.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Instruction& i)
{
  if (not available(v, bytes(i.header)))
    return AVAILABLE_INSTRUCTION_HEADER;
  from_buffer(v, i.header);
  
  if (i.header.length < bytes(i.header))
    return BAD_INSTRUCTION_LENGTH;
  
  if (Error_decl err = is_valid(i.header))
    return err;
  
  Instruction::Payload p;
  construct(p, i.header.type);
  assign(i.payload, std::move(p), i.header.type);

  std::size_t n = i.header.length - bytes(i.header);
  if (remaining(v) < n)
    return AVAILABLE_INSTRUCTION_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, i.payload, i.header.type))
    return err;
  
  if(not update(v, c))
    return EXCESS_INSTRUCTION;
  
  return SUCCESS;
}

std::string
to_string(const Instruction& i, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction");
  ss << to_string(i.header, f);
  if (is_valid(i.header))
    ss << to_string(i.payload, f, i.header.type);
  close_block(ss, f, "Instruction");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Port

Error_condition
to_buffer(Buffer_view& v, const Port& p)
{
  if (not available(v, bytes(p)))
    return AVAILABLE_PORT;
  to_buffer(v, p.port_id);
  pad(v, 4);
  to_buffer(v, p.hw_addr);
  pad(v, 2);
  to_buffer(v, p.name);
  to_buffer(v, p.config);
  to_buffer(v, p.state);
  to_buffer(v, p.current);
  to_buffer(v, p.advertised);
  to_buffer(v, p.supported);
  to_buffer(v, p.peer);
  to_buffer(v, p.curr_speed);
  to_buffer(v, p.max_speed);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Port& p)
{
  if (not available(v, bytes(p)))
    return AVAILABLE_PORT;
  from_buffer(v, p.port_id);
  pad(v, 4);
  from_buffer(v, p.hw_addr);
  pad(v, 2);
  from_buffer(v, p.name);
  from_buffer(v, p.config);
  from_buffer(v, p.state);
  from_buffer(v, p.current);
  from_buffer(v, p.advertised);
  from_buffer(v, p.supported);
  from_buffer(v, p.peer);
  from_buffer(v, p.curr_speed);
  from_buffer(v, p.max_speed);
  return SUCCESS;
}

std::string
to_string(const Port& p, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Port");

  nvp_to_string(ss, f, "Port ID", to_string(p.port_id), int(p.port_id));
  nvp_to_string(ss, f, "Hw Addr", ethernet::to_string(p.hw_addr));
  nvp_to_string(ss, f, "Name", p.name.str());
  nvp_to_string(ss, f, "Config", to_string(p.config), int(p.config));
  nvp_to_string(ss, f, "State", to_string(p.state), int(p.state));
  nvp_to_string(ss, f, "Current", to_string(p.current), int(p.current));
  nvp_to_string(ss, f, "Advertised", to_string(p.advertised),
                int(p.advertised));
  nvp_to_string(ss, f, "Supported", to_string(p.supported), int(p.supported));
  nvp_to_string(ss, f, "Peer", to_string(p.peer), int(p.peer));
  nvp_to_string(ss, f, "Current Speed", p.curr_speed);
  nvp_to_string(ss, f, "Max Speed", p.max_speed);

  close_block(ss, f, "Port");
  return ss.str();
}

std::string
to_string(Port::Config cv)
{
  switch(cv) {
    case Port::PORT_DOWN: return "Port Down";
    case Port::NO_RECV: return "No Recv";
    case Port::NO_FWD: return "No Fwd";
    case Port::NO_PACKET_IN: return "No PacketIn";
    default: return "Unknown";
  }
}

std::string
to_string(Port::State sv)
{
  switch(sv) {
    case Port::LINK_DOWN: return "Link Down";
    case Port::BLOCKED: return "Blocked";
    case Port::LIVE: return "Live";
    default: return "Unknown";
  }
}

std::string
to_string(Port::Id iv)
{
  switch(iv) {
    case Port::MAX: return "Max";
    case Port::IN_PORT: return "Input Port";
    case Port::TABLE: return "Table";
    case Port::NORMAL: return "Normal";
    case Port::FLOOD: return "Flood";
    case Port::ALL: return "All";
    case Port::CONTROLLER: return "Controller";
    case Port::LOCAL: return "Local";
    case Port::ANY: return "Any";
    default: return "Unknown";
  }
}

std::string
to_string(Port::Features fv)
{
  switch(fv) {
    case Port::TEN_MB_HD: return "10MB HD";
    case Port::TEN_MB_FD: return "10MB FD";
    case Port::HUNDRED_MB_HD: return "100MB HD";
    case Port::HUNDRED_MB_FD: return "100MB FD";
    case Port::ONE_GB_HD: return "1GB HD";
    case Port::ONE_GB_FD: return "1GB FD";
    case Port::TEN_GB_FD: return "10GB FD";
    case Port::FORTY_GB_FD: return "40GB FD";
    case Port::HUNDRED_GB_FD: return "100GB FD";
    case Port::ONE_TB_FD: return "1TB FD";
    case Port::OTHER: return "Other";
    case Port::COPPER: return "Copper";
    case Port::FIBER: return "Fiber";
    case Port::AUTO_NEG: return "AutoNeg";
    case Port::PAUSE: return "Pause";
    case Port::PAUSE_ASYM: return "PauseAsym";
    default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Queue property type

std::string
to_string(Queue_property_type t)
{
  switch(t) {
    case QUEUE_PROPERTY_NONE: return "NONE";
    case QUEUE_PROPERTY_MIN_RATE: return "MIN_RATE";
    default: unreachable();
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Queue property header

Error_condition
to_buffer(Buffer_view& v, const Queue_property_header& h)
{
  to_buffer(v, h.property);
  to_buffer(v, h.length);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_header& h)
{
  from_buffer(v, h.property);
  from_buffer(v, h.length);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Queue_property_header& h, Formatter& f)
{
  std::stringstream ss;

  open_block(ss, f, "Queue Property Hdr");
  nvp_to_string(ss, f, "Property", to_string(h.property), int(h.property));
  nvp_to_string(ss, f, "Length", h.length);
  close_block(ss, f, "Queue Property Hdr");

  return ss.str();
}

// -------------------------------------------------------------------------- //
// Queue property min rate

Error_condition
to_buffer(Buffer_view& v, const Queue_property_min_rate& mr)
{
  if (not available(v, bytes(mr)))
    return AVAILABLE_QUEUE_PROPERTY_MIN_RATE;
  to_buffer(v, mr.rate);
  pad(v, 6);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_min_rate& mr)
{
  if (not available(v, bytes(mr)))
    return AVAILABLE_QUEUE_PROPERTY_MIN_RATE;
  from_buffer(v, mr.rate);
  pad(v, 6);
  return SUCCESS;
}

std::string
to_string(const Queue_property_min_rate& mr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "QueuePropertyMinRate");

  nvp_to_string(ss, f, "Rate", mr.rate);

  close_block(ss, f, "QueuePropertyMinRate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Queue Property Payload

void
construct(Queue_property_payload& a, Queue_property_type t)
{
  a.init = true;
  switch (t) {
  case QUEUE_PROPERTY_NONE: new (&a.data.none) Queue_property_none(); break;
  case QUEUE_PROPERTY_MIN_RATE:
    new (&a.data.min_rate) Queue_property_min_rate(); break;
  default: variant_error(t);
  }
}

void
construct(Queue_property_payload& a, const Queue_property_payload& b,
          Queue_property_type t)
{
  a.init = b.init;
  if (not b)
    return;
  switch (t) {
  case QUEUE_PROPERTY_NONE:
    new (&a.data.none) Queue_property_none(b.data.none); break;
  case QUEUE_PROPERTY_MIN_RATE:
    new (&a.data.min_rate) Queue_property_min_rate(b.data.min_rate); break;
  default: variant_error(t);
  }
}

Queue_property::Payload&
assign(Queue_property_payload& a, const Queue_property_payload& b, Queue_property_type t)
{
  if (&a == &b)
    return a;

  a.init = b.init;
  if (not a.init)
    return a;

  switch (t) {
  case QUEUE_PROPERTY_NONE: a.data.none = b.data.none; break;
  case QUEUE_PROPERTY_MIN_RATE: a.data.min_rate = b.data.min_rate; break;
  default: variant_error(t);
  }
  return a;
}

bool
equal(const Queue_property_payload& a, const Queue_property_payload& b,
      Queue_property_type t1, Queue_property_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case QUEUE_PROPERTY_NONE: return a.data.none == b.data.none;
  case QUEUE_PROPERTY_MIN_RATE: return a.data.min_rate == b.data.min_rate;
  default: variant_error(t1);
  }
  return false;
}

// Bytes
inline std::size_t
bytes(const Queue_property_payload& p, Queue_property_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case QUEUE_PROPERTY_NONE: return bytes(p.data.none);
  case QUEUE_PROPERTY_MIN_RATE: return bytes(p.data.min_rate);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Queue_property_payload& p, Queue_property_type t)
{
  if (not p)
    return BAD_QUEUE_PROPERTY_INIT;
  switch (t) {
  case QUEUE_PROPERTY_NONE: return is_valid(p.data.none);
  case QUEUE_PROPERTY_MIN_RATE: return is_valid(p.data.min_rate);
  default: variant_error(t);
  }
  return BAD_QUEUE_PROPERTY;
}

// To/from buffer
Error_condition
to_buffer(Buffer_view& v, const Queue_property_payload& p,
          Queue_property_type t)
{
  assert(p);
  switch (t) {
  case QUEUE_PROPERTY_NONE: return to_buffer(v, p.data.none);
  case QUEUE_PROPERTY_MIN_RATE: return to_buffer(v, p.data.min_rate);
  default: variant_error(t);
  }
  return BAD_QUEUE_PROPERTY;
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_payload& p, Queue_property_type t)
{
  assert(p);
  switch (t) {
  case QUEUE_PROPERTY_NONE: return from_buffer(v, p.data.none);
  case QUEUE_PROPERTY_MIN_RATE: return from_buffer(v, p.data.min_rate);
  default: variant_error(t);
  }
  return BAD_QUEUE_PROPERTY;
}

std::string
to_string(const Queue_property_payload& p, Formatter& fmt, Queue_property_type t)
{
  assert(p);
  switch (t) {
  case QUEUE_PROPERTY_NONE: return to_string(p.data.none, fmt);
  case QUEUE_PROPERTY_MIN_RATE: return to_string(p.data.min_rate, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Queue property

Error_condition
to_buffer(Buffer_view& v, const Queue_property& qp)
{
  if (not available(v, bytes(qp.header)))
    return AVAILABLE_QUEUE_PROPERTY_HEADER;  
  to_buffer(v, qp.header);
  return to_buffer(v, qp.payload, qp.header.property);
}

Error_condition
from_buffer(Buffer_view& v, Queue_property& qp)
{
  if (not available(v, bytes(qp.header)))
    return AVAILABLE_QUEUE_PROPERTY_HEADER;  
  from_buffer(v, qp.header);
  
  if (qp.header.length < bytes(qp.header))
    return BAD_QUEUE_PROPERTY_LENGTH;
  
  if (not is_valid(qp.header))
    return BAD_QUEUE_PROPERTY;
  
  Queue_property::Payload p;
  construct(p, qp.header.property);
  assign(qp.payload, std::move(p), qp.header.property);

  std::size_t n = qp.header.length - bytes(qp.header);
  if (remaining(v) < n)
    return AVAILABLE_QUEUE_PROPERTY_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, qp.payload, qp.header.property))
    return err;
  
  if (not update(v, c))
    return EXCESS_QUEUE_PROPERTY;

  return SUCCESS;
}

std::string
to_string(const Queue_property& qp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "QueueProperty");

  ss << to_string(qp.header, f);

  if (is_valid(qp.header))
    ss << to_string(qp.payload, f, qp.header.property);

  close_block(ss, f, "QueueProperty");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Queue

Error_condition
to_buffer(Buffer_view& v, const Queue& q)
{
  if (not available(v, bytes(q)))
    return AVAILABLE_QUEUE;
  to_buffer(v, q.queue_id);
  to_buffer(v, q.length);
  pad(v, 2);
  
  return to_buffer(v, q.properties);
}

Error_condition
from_buffer(Buffer_view& v, Queue& q)
{
  if (not available(v, bytes(q)))
    return AVAILABLE_QUEUE;
  from_buffer(v, q.queue_id);
  from_buffer(v, q.length);
  pad(v, 2);
  
  std::size_t n = q.length - bytes(q);
  if (remaining(v) < n)
    return AVAILABLE_QUEUE_PROPERTIES;
  
  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, q.properties))
    return err;
  
  if (not update(v, c))
    return EXCESS_QUEUE;
  return SUCCESS;
}

std::string
to_string(const Queue& q, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Queue");

  nvp_to_string(ss, f, "Queue ID", q.queue_id);
  nvp_to_string(ss, f, "Length", q.length);

  ss << to_string(q.properties, f);

  close_block(ss, f, "Queue");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Feature response

Error_condition
to_buffer(Buffer_view& v, const Feature_res& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FEATURE_RES;
  to_buffer(v, fr.datapath_id);
  to_buffer(v, fr.n_buffers);
  to_buffer(v, fr.n_tbls);
  pad(v, 3);
  to_buffer(v, fr.capabilities);
  to_buffer(v, fr.reserved);
  return to_buffer(v, fr.ports);
}

Error_condition
from_buffer(Buffer_view& v, Feature_res& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FEATURE_RES;
  from_buffer(v, fr.datapath_id);
  from_buffer(v, fr.n_buffers);
  from_buffer(v, fr.n_tbls);
  pad(v, 3);
  from_buffer(v, fr.capabilities);
  from_buffer(v, fr.reserved);
  return from_buffer(v, fr.ports);
}

std::string
to_string(const Feature_res& fr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "FeatureRes");

  nvp_to_string(ss, f, "Datapath ID", fr.datapath_id);
  nvp_to_string(ss, f, "Buffer Numbers", fr.n_buffers);
  nvp_to_string(ss, f, " Table Numbers", int(fr.n_tbls));
  nvp_to_string(ss, f, "Feature Capabilities", to_string(fr.capabilities),
                int(fr.capabilities));
  nvp_to_string(ss, f, "Reserved", fr.reserved);

  ss << to_string(fr.ports, f);

  close_block(ss, f, "FeatureRes");
  return ss.str();
}

std::string
to_string(Feature_res::Capability ct)
{
  switch(ct) {
  case Feature_res::FLOW_STATS: return "Flow Stats";
  case Feature_res::TABLE_STATS: return "Table Stats";
  case Feature_res::PORT_STATS: return "Port Stats";
  case Feature_res::GROUP_STATS: return "Group Stats";
  case Feature_res::IP_REASM: return "IP Reasm";
  case Feature_res::QUEUE_STATS: return "Queue Stats";
  case Feature_res::ARP_MATCH_IP: return "ARP Match IP";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Get config response

std::string
to_string(const Get_config_res& gcr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "GetConfigRes");

  nvp_to_string(ss, f, "Flags", int(gcr.flags));
  nvp_to_string(ss, f, "Miss Send Length", gcr.miss_send_len);

  close_block(ss, f, "GetConfigRes");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Set config

std::string
to_string(const Set_config& sc, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "SetConfig");

  nvp_to_string(ss, f, "Flags", int(sc.flags));
  nvp_to_string(ss, f, "Miss Send Length", sc.miss_send_len);

  close_block(ss, f, "SetConfig");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Packet in

Error_condition
to_buffer(Buffer_view& v, const Packet_in& pi)
{
  if (not available(v, bytes(pi)))
    return AVAILABLE_PACKET_IN;
  to_buffer(v, pi.buffer_id);
  to_buffer(v, pi.in_port);
  to_buffer(v, pi.in_phy_port);
  to_buffer(v, pi.total_len);
  to_buffer(v, pi.reason);
  to_buffer(v, pi.tbl_id);
  to_buffer(v, pi.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Packet_in& pi)
{
  if (not available(v, bytes(pi)))
    return AVAILABLE_PACKET_IN;
  from_buffer(v, pi.buffer_id);
  from_buffer(v, pi.in_port);
  from_buffer(v, pi.in_phy_port);
  from_buffer(v, pi.total_len);
  from_buffer(v, pi.reason);
  from_buffer(v, pi.tbl_id);
  
  if (pi.total_len == 0)
    return SUCCESS;
  pi.data = Buffer(pi.total_len);
  
  if (not from_buffer(v, pi.data))
    return AVAILABLE_PACKET_IN;
  return SUCCESS;
}

std::string
to_string(const Packet_in& pi, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "PacketIn");

  nvp_to_string(ss, f, "Buffer ID", pi.buffer_id);
  nvp_to_string(ss, f, "Total Len", pi.total_len);
  nvp_to_string(ss, f, "Ingress Port", pi.in_port);
  nvp_to_string(ss, f, "Ingress Physical Port", pi.in_phy_port);
  nvp_to_string(ss, f, "Reason", to_string(pi.reason), int(pi.reason));
  nvp_to_string(ss, f, "Table ID", int(pi.tbl_id));
  nvp_to_string(ss, f, "Data bytes", bytes(pi.data));

  close_block(ss, f, "PacketIn");
  return ss.str();
}

std::string
to_string(Packet_in::Reason rt)
{
  switch(rt) {
  case Packet_in::Reason::NO_MATCH: return "NoMatch";
  case Packet_in::Reason::ACTION: return "Action";
  default: return "Unknown";
  }
}


// -------------------------------------------------------------------------- //
// Flow removed

Error_condition
to_buffer(Buffer_view& v, const Flow_removed& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FLOW_REMOVED;
  to_buffer(v, fr.cookie);
  to_buffer(v, fr.priority);
  to_buffer(v, fr.reason);
  to_buffer(v, fr.table_id);
  to_buffer(v, fr.duration_sec);
  to_buffer(v, fr.duration_nsec);
  to_buffer(v, fr.idle_timeout);
  pad(v, 2);
  to_buffer(v, fr.packet_count);
  to_buffer(v, fr.byte_count);
  to_buffer(v, fr.match);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Flow_removed& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FLOW_REMOVED;
  from_buffer(v, fr.cookie);
  from_buffer(v, fr.priority);
  from_buffer(v, fr.reason);
  from_buffer(v, fr.table_id);
  from_buffer(v, fr.duration_sec);
  from_buffer(v, fr.duration_nsec);
  from_buffer(v, fr.idle_timeout);
  pad(v, 2);
  from_buffer(v, fr.packet_count);
  from_buffer(v, fr.byte_count);
  from_buffer(v, fr.match);
  return SUCCESS;
}

std::string
to_string(const Flow_removed& fr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "FlowRemoved");

  nvp_to_string(ss, f, "Cookie", fr.cookie);
  nvp_to_string(ss, f, "Priority", fr.priority);
  nvp_to_string(ss, f, "Reason", to_string(fr.reason), int(fr.reason));
  nvp_to_string(ss, f, "Table ID", int(fr.table_id));
  nvp_to_string(ss, f, "Duration in Seconds", fr.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoseconds", fr.duration_nsec);
  nvp_to_string(ss, f, "Idle Timeout", fr.idle_timeout);
  nvp_to_string(ss, f, "Packet Count", fr.packet_count);
  nvp_to_string(ss, f, "Byte Count", fr.byte_count);

  ss << to_string(fr.match, f);

  close_block(ss, f, "FlowRemoved");
  return ss.str();
}

std::string
to_string(Flow_removed::Reason rt)
{
  switch(rt) {
  case Flow_removed::Reason::IDLE_TIMEOUT: return "IdleTimeout";
  case Flow_removed::Reason::HARD_TIMEOUT: return "HardTimeout";
  case Flow_removed::Reason::DELETE: return "Delete";
  case Flow_removed::Reason::GROUP_DELETE: return "GroupDelete";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Port status

Error_condition
to_buffer(Buffer_view& v, const Port_status& ps)
{
  if (not available(v, bytes(ps)))
    return AVAILABLE_PORT_STATUS;
  to_buffer(v, ps.reason);
  pad(v, 7);
  return to_buffer(v, ps.port);
}

Error_condition
from_buffer(Buffer_view& v, Port_status& ps)
{
  if (not available(v, bytes(ps)))
    return AVAILABLE_PORT_STATUS;
  from_buffer(v, ps.reason);
  pad(v, 7);
  return from_buffer(v, ps.port);
}

std::string
to_string(const Port_status& ps, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "PortStatus");

  nvp_to_string(ss, f, "Reason", to_string(ps.reason), int(ps.reason));

  ss << to_string(ps.port, f);

  close_block(ss, f, "PortStatus");
  return ss.str();
}

std::string
to_string(Port_status::Reason rt)
{
  switch(rt) {
  case Port_status::Reason::ADD: return "Add";
  case Port_status::Reason::DELETE: return "Delete";
  case Port_status::Reason::MODIFY: return "Modify";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Packet out

Error_condition
to_buffer(Buffer_view& v, const Packet_out& po)
{
  if (not available(v, bytes(po)))
    return AVAILABLE_PACKET_OUT;
  to_buffer(v, po.buffer_id);
  to_buffer(v, po.in_port);
  to_buffer(v, po.actions_len);
  pad(v, 6);
  
  if (Error_decl err = to_buffer(v, po.actions))
    return err;

  to_buffer(v, po.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Packet_out& po)
{
  if (not available(v, bytes(po)))
    return AVAILABLE_PACKET_OUT;
  from_buffer(v, po.buffer_id);
  from_buffer(v, po.in_port);
  from_buffer(v, po.actions_len);
  pad(v, 6);

  if (remaining(v) < po.actions_len)
    return BAD_PACKET_OUT_LENGTH;
  
  Buffer_view c = constrain(v, po.actions_len);
  if (Error_decl err = from_buffer(c, po.actions))
    return err;
  
  if(not update(v,c))
    return EXCESS_PACKET_OUT;

  if (not from_buffer(v, po.data))
    return AVAILABLE_PACKET_OUT;

  return SUCCESS;
}

std::string
to_string(const Packet_out& po, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "PacketOut");

  nvp_to_string(ss, f, "Buffer ID", po.buffer_id);
  nvp_to_string(ss, f, "Ingress Port", po.in_port);
  nvp_to_string(ss, f, "Actions Length", po.actions_len);

  ss << to_string(po.actions, f);

  close_block(ss, f, "PacketOut");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Flow_mod

Error_condition
to_buffer(Buffer_view& v, const Flow_mod& fm)
{
  if (not available(v, bytes(fm)))
    return AVAILABLE_FLOW_MOD;
  to_buffer(v, fm.cookie);
  to_buffer(v, fm.cookie_mask);
  to_buffer(v, fm.table_id);
  to_buffer(v, fm.command);
  to_buffer(v, fm.idle_timeout);
  to_buffer(v, fm.hard_timeout);
  to_buffer(v, fm.priority);
  to_buffer(v, fm.buffer_id);
  to_buffer(v, fm.out_port);
  to_buffer(v, fm.out_group);
  to_buffer(v, fm.flags);
  pad(v, 2);
  to_buffer(v, fm.match);
  return to_buffer(v, fm.instructions);
}

Error_condition
from_buffer(Buffer_view& v, Flow_mod& fm)
{
  if (not available(v, bytes(fm)))
    return AVAILABLE_FLOW_MOD;
  from_buffer(v, fm.cookie);
  from_buffer(v, fm.cookie_mask);
  from_buffer(v, fm.table_id);
  from_buffer(v, fm.command);
  from_buffer(v, fm.idle_timeout);
  from_buffer(v, fm.hard_timeout);
  from_buffer(v, fm.priority);
  from_buffer(v, fm.buffer_id);
  from_buffer(v, fm.out_port);
  from_buffer(v, fm.out_group);
  from_buffer(v, fm.flags);
  pad(v, 2);
  from_buffer(v, fm.match);
  return from_buffer(v, fm.instructions);
}

std::string
to_string(Flow_mod::Command ct)
{
  switch(ct){
    case Flow_mod::ADD: return "ADD";
    case Flow_mod::MODIFY: return "MODIFY";
    case Flow_mod::MODIFY_STRICT: return "MODIFY_STRICT";
    case Flow_mod::DELETE: return "DELETE";
    case Flow_mod::DELETE_STRICT: return "DELETE_STRICT";
    default: return "UNKNWON";
  }
}

std::string
to_string(Flow_mod::Flags ft)
{
  switch(ft) {
    case Flow_mod::SEND_FLOW_REM: return "SEND_FLOW_REM";
    case Flow_mod::CHECK_OVERLAP: return "CHECK_OVERLAP";
    default: return "UNKNOWN";
  }
}

std::string
to_string(const Flow_mod& fm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "FlowMod");

  nvp_to_string(ss, f, "Cookie", fm.cookie);
  nvp_to_string(ss, f, "Cookie Mask", fm.cookie_mask);
  nvp_to_string(ss, f, "Table ID", int(fm.table_id));
  nvp_to_string(ss, f, "Command ",
                to_string(Flow_mod::Command(fm.command)),
                int(fm.command));
  nvp_to_string(ss, f, "Idle Timeout", fm.idle_timeout);
  nvp_to_string(ss, f, "Hard Timeout", fm.hard_timeout);
  nvp_to_string(ss, f, "Priority", fm.priority);
  nvp_to_string(ss, f, "Buffer ID", fm.buffer_id);
  nvp_to_string(ss, f, "Output Port", fm.out_port);
  nvp_to_string(ss, f, "Output Group", fm.out_group);
  nvp_to_string(ss, f, "Flags", to_string(Flow_mod::Flags(fm.flags)),
                int(fm.flags));

  ss << to_string(fm.match, f);
  ss << to_string(fm.instructions, f);

  close_block(ss, f, "FlowMod");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Bucket

Error_condition
to_buffer(Buffer_view& v, const Bucket& b)
{
  if (not available(v, bytes(b)))
    return AVAILABLE_BUCKET;
  to_buffer(v, b.len);
  to_buffer(v, b.weight);
  to_buffer(v, b.watch_port);
  to_buffer(v, b.watch_group);
  pad(v, 4);
  return to_buffer(v, b.actions);
}

Error_condition
from_buffer(Buffer_view& v, Bucket& b)
{
  if (not available(v, bytes(b)))
    return AVAILABLE_BUCKET;
  from_buffer(v, b.len);
  from_buffer(v, b.weight);
  from_buffer(v, b.watch_port);
  from_buffer(v, b.watch_group);
  pad(v, 4);

  std::size_t n = b.len - bytes(b) + bytes(b.actions);
  if (remaining(v) < n)
    return BAD_BUCKET_LENGTH;
  
  Buffer_view c = constrain(v, n);
  if(Error_decl err = from_buffer(c, b.actions))
    return err;
  
  if (not update(v, c))
    return EXCESS_BUCKET;
  
  return SUCCESS;
}

std::string
to_string(const Bucket& b, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Bucket");

  nvp_to_string(ss, f, "Length", b.len);
  nvp_to_string(ss, f, "Weight", b.weight);
  nvp_to_string(ss, f, "Watch Port", b.watch_port);
  nvp_to_string(ss, f, "Watch Group", b.watch_group);

  ss << to_string(b.actions, f);

  close_block(ss, f, "Bucket");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Group mod

Error_condition
to_buffer(Buffer_view& v, const Group_mod& gm)
{
  if (not available(v, bytes(gm)))
    return AVAILABLE_GROUP_MOD;
  to_buffer(v, gm.command);
  to_buffer(v, gm.type);
  pad(v, 1);
  to_buffer(v, gm.group_id);

  return to_buffer(v, gm.buckets);
}

Error_condition
from_buffer(Buffer_view& v, Group_mod& gm)
{
  if (not available(v, bytes(gm)))
    return AVAILABLE_GROUP_MOD;

  from_buffer(v, gm.command);
  from_buffer(v, gm.type);
  pad(v, 1);
  from_buffer(v, gm.group_id);

  return from_buffer(v, gm.buckets);
}

std::string
to_string(const Group_mod& gm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "GroupMod");

  nvp_to_string(ss, f, "Command", to_string(gm.command), int(gm.command));
  nvp_to_string(ss, f, "Type", to_string(gm.type), int(gm.type));
  nvp_to_string(ss, f, "Group ID", gm.group_id);

  close_block(ss, f, "GroupMod");
  return ss.str();
}

std::string
to_string(Group_mod::Command ct)
{
  switch(ct) {
  case Group_mod::Command::ADD: return "ADD";
  case Group_mod::Command::MODIFY: return "MODIFY";
  case Group_mod::Command::DELETE: return "DELETE";
  default: return "Unknown";
  }
}

std::string
to_string(Group_mod::Type tv)
{
  switch(tv) {
  case Group_mod::Type::ALL: return "ALL";
  case Group_mod::Type::SELECT: return "SELECT";
  case Group_mod::Type::INDIRECT: return "INDIRECT";
  case Group_mod::Type::FF: return "FAST FAILOVER";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Port mod

Error_condition
to_buffer(Buffer_view& v, const Port_mod& pm)
{
  if (not available(v, bytes(pm)))
    return AVAILABLE_PORT_MOD;
  to_buffer(v, pm.port);
  pad(v, 4);
  to_buffer(v, pm.hw_addr);
  pad(v, 2);
  to_buffer(v, pm.config);
  to_buffer(v, pm.mask);
  to_buffer(v, pm.advertise);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Port_mod& pm)
{
  if (not available(v, bytes(pm)))
    return AVAILABLE_PORT_MOD;
  from_buffer(v, pm.port);
  pad(v, 4);
  from_buffer(v, pm.hw_addr);
  pad(v, 2);
  from_buffer(v, pm.config);
  from_buffer(v, pm.mask);
  from_buffer(v, pm.advertise);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Port_mod& pm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "PortMod");

  nvp_to_string(ss, f, "Port", pm.port);
  nvp_to_string(ss, f, "HW Addr", ethernet::to_string(pm.hw_addr));
  nvp_to_string(ss, f, "Config", to_string(pm.config), int(pm.config));
  nvp_to_string(ss, f, "Mask", pm.mask);
  nvp_to_string(ss, f, "Advertise", to_string(pm.advertise),
                int(pm.advertise));

  close_block(ss, f, "PortMod");
  return ss.str();
}

std::string
to_string(Port_mod::Config ct)
{
  switch(ct) {
  case Port_mod::Config::PORT_DOWN: return "PortDown";
  case Port_mod::Config::NO_RECV: return "No Recv";
  case Port_mod::Config::NO_FWD: return "No Fwd";
  case Port_mod::Config::NO_PACKET_IN: return "No PacketIn";
  default: return "Unknown";
  }
}

std::string
to_string(Port_mod::Features ft)
{
  switch(ft) {
  case Port_mod::TEN_MB_HD: return "10MB HD";
  case Port_mod::TEN_MB_FD: return "10MB FD";
  case Port_mod::HUNDRED_MB_HD: return "100MB HD";
  case Port_mod::HUNDRED_MB_FD: return "100MB FD";
  case Port_mod::ONE_GB_HD: return "1GB HD";
  case Port_mod::ONE_GB_FD: return "1GB FD";
  case Port_mod::TEN_GB_FD: return "10GB FD";
  case Port_mod::FOURTY_GB_FD: return "40GB FD";
  case Port_mod::HUNDRED_GB_FD: return "100GB FD";
  case Port_mod::ONE_TB_FD: return "1TB FD";
  case Port_mod::OTHER: return "Other";
  case Port_mod::COPPER: return "Copper";
  case Port_mod::FIBER: return "Fiber";
  case Port_mod::AUTO_NEG: return "AutoNeg";
  case Port_mod::PAUSE: return "Pause";
  case Port_mod::PAUSE_ASYM: return "PauseAsym";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Table mod

Error_condition
to_buffer(Buffer_view& v, const Table_mod& tm)
{
  if (not available(v, bytes(tm)))
    return AVAILABLE_TABLE_MOD;
  to_buffer(v, tm.table_id);
  pad(v, 3);
  to_buffer(v, tm.config);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Table_mod& tm)
{
  if (not available(v, bytes(tm)))
    return AVAILABLE_TABLE_MOD;
  from_buffer(v, tm.table_id);
  pad(v, 3);
  from_buffer(v, tm.config);
  return SUCCESS;
}

std::string
to_string(const Table_mod& tm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "TableMod");

  nvp_to_string(ss, f, "Table ID", int(tm.table_id));
  nvp_to_string(ss, f, "Config", to_string(tm.config), int(tm.config));

  close_block(ss, f, "TableMod");
  return ss.str();
}

std::string
to_string(Table_mod::Config ct)
{
  switch(ct) {
  case Table_mod::Config::MISS_CONTROLLER: return "Miss Controller";
  case Table_mod::Config::MISS_CONTINUE: return "Miss Continue";
  case Table_mod::Config::MISS_DROP: return "Miss Drop";
  case Table_mod::Config::MISS_MASK: return "Miss Mask";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Stats type

std::string
to_string(Stats_type t)
{
  switch (t) {
  case STATS_DESC: return "Desc";
  case STATS_FLOW: return "Flow";
  case STATS_AGGREGATE: return "Aggregate";
  case STATS_TABLE: return "Table";
  case STATS_PORT: return "Port";
  case STATS_QUEUE: return "Queue";
  case STATS_GROUP: return "Group";
  case STATS_GROUP_DESC: return "Group Desc";
  case STATS_EXPERIMENTER: return "Experimenter";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Stats Request: Flow

std::string
to_string(const Stats_req_flow& srf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Flow");

  nvp_to_string(ss, f, "Table ID", int(srf.table_id));
  nvp_to_string(ss, f, "Out Port", srf.out_port);
  nvp_to_string(ss, f, "Out Group", srf.out_group);
  nvp_to_string(ss, f, "Cookie", srf.cookie);
  nvp_to_string(ss, f, "Cookie Mask", srf.cookie_mask);

  ss << to_string(srf.match, f);

  close_block(ss, f, "StatsReq Flow");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Request: Aggregate

std::string
to_string(const Stats_req_aggregate& sra, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Aggregate");

  nvp_to_string(ss, f, "Table ID", int(sra.table_id));
  nvp_to_string(ss, f, "Out Port", sra.out_port);
  nvp_to_string(ss, f, "Out Group", sra.out_group);
  nvp_to_string(ss, f, "Cookie", sra.cookie);
  nvp_to_string(ss, f, "Cookie Mask", sra.cookie_mask);

  ss << to_string(sra.match, f);

  close_block(ss, f, "StatsReq Aggregate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Request: Port

Error_condition
to_buffer(Buffer_view& v, const Stats_req_port& srp)
{
  if (not available(v, bytes(srp)))
    return AVAILABLE_STATS_REQ_PORT;
  to_buffer(v, srp.port_no);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_port& srp)
{
  if (not available(v, bytes(srp)))
    return AVAILABLE_STATS_REQ_PORT;
  from_buffer(v, srp.port_no);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Stats_req_port& srp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Port");

  nvp_to_string(ss, f, "Port No", srp.port_no);

  close_block(ss, f, "StatsReq Aggregate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Request: Queue

Error_condition
to_buffer(Buffer_view& v, const Stats_req_queue& srq)
{
  if (not available(v, bytes(srq)))
    return AVAILABLE_STATS_REQ_QUEUE;
  to_buffer(v, srq.port_no);
  to_buffer(v, srq.queue_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_queue& srq)
{
  if (not available(v, bytes(srq)))
    return AVAILABLE_STATS_REQ_QUEUE;
  from_buffer(v, srq.port_no);
  from_buffer(v, srq.queue_id);
  return SUCCESS;
}

std::string
to_string(const Stats_req_queue& srq, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Queue");

  nvp_to_string(ss, f, "Port No", srq.port_no);
  nvp_to_string(ss, f, "Queue ID", srq.queue_id);

  close_block(ss, f, "StatsReq Queue");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Request: Group

Error_condition
to_buffer(Buffer_view& v, const Stats_req_group& srg)
{
  if (not available(v, bytes(srg)))
    return AVAILABLE_STATS_REQ_GROUP;
  to_buffer(v, srg.group_id);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_group& srg)
{
  if (not available(v, bytes(srg)))
    return AVAILABLE_STATS_REQ_GROUP;
  from_buffer(v, srg.group_id);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Stats_req_group& srg, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Group");

  nvp_to_string(ss, f, "Group ID", srg.group_id);

  close_block(ss, f, "StatsReq Group");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Request: Experimenter

Error_condition
to_buffer(Buffer_view& v, const Stats_req_experimenter& sre)
{
  if (not available(v, bytes(sre)))
    return AVAILABLE_STATS_REQ_EXPERIMENTER;
  to_buffer(v, sre.experimenter_id);
  return to_buffer(v, sre.data);
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_experimenter& sre)
{
  if (not available(v, bytes(sre)))
    return AVAILABLE_STATS_REQ_EXPERIMENTER;
  from_buffer(v, sre.experimenter_id);
  return from_buffer(v, sre.data);
}

std::string
to_string(const Stats_req_experimenter& sre, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Experimenter");

  nvp_to_string(ss, f, "Experimenter ID", sre.experimenter_id);
  nvp_to_string(ss, f, "Data bytes", bytes(sre.data));

  close_block(ss, f, "StatsReq Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Request Payload

void
construct(Stats_req_payload& p, Stats_type t)
{
  p.init = true;
  switch(t) {
  case STATS_DESC: new (&p.data.desc) Stats_req_desc(); break;
  case STATS_FLOW: new (&p.data.flow) Stats_req_flow(); break;
  case STATS_AGGREGATE: new (&p.data.aggregate) Stats_req_aggregate(); break;
  case STATS_TABLE: new (&p.data.table) Stats_req_table(); break;
  case STATS_PORT: new (&p.data.port) Stats_req_port(); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_req_queue(); break;
  case STATS_GROUP: new (&p.data.group) Stats_req_group(); break;
  case STATS_GROUP_DESC: new (&p.data.group_desc) Stats_req_group_desc();
    break;
  case STATS_EXPERIMENTER:
    new (&p.data.experimenter) Stats_req_experimenter(); break;
  default: variant_error(t);
  }
}

void
construct(Stats_req_payload& p, Stats_req_payload&& x, Stats_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case STATS_DESC:
    new (&p.data.desc) Stats_req_desc(std::move(x.data.desc)); break;
  case STATS_FLOW:
    new (&p.data.flow) Stats_req_flow(std::move(x.data.flow)); break;
  case STATS_AGGREGATE:
    new (&p.data.aggregate) Stats_req_aggregate(std::move(x.data.aggregate));
    break;
  case STATS_TABLE:
    new (&p.data.table) Stats_req_table(std::move(x.data.table)); break;
  case STATS_PORT:
    new (&p.data.port) Stats_req_port(std::move(x.data.port)); break;
  case STATS_QUEUE:
    new (&p.data.queue) Stats_req_queue(std::move(x.data.queue)); break;
  case STATS_GROUP:
    new (&p.data.group) Stats_req_group(std::move(x.data.group)); break;
  case STATS_GROUP_DESC:
    new (&p.data.group_desc)
    Stats_req_group_desc(std::move(x.data.group_desc)); break;
  case STATS_EXPERIMENTER:
    new (&p.data.experimenter)
    Stats_req_experimenter(std::move(x.data.experimenter)); break;
  default: variant_error(t);
  }
}

void
construct(Stats_req_payload& p, const Stats_req_payload& x, Stats_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case STATS_DESC: new (&p.data.desc) Stats_req_desc(x.data.desc); break;
  case STATS_FLOW: new (&p.data.flow) Stats_req_flow(x.data.flow); break;
  case STATS_AGGREGATE:
    new (&p.data.aggregate) Stats_req_aggregate(x.data.aggregate); break;
  case STATS_TABLE: new (&p.data.table) Stats_req_table(x.data.table); break;
  case STATS_PORT: new (&p.data.port) Stats_req_port(x.data.port); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_req_queue(x.data.queue); break;
  case STATS_GROUP: new (&p.data.group) Stats_req_group(x.data.group); break;
  case STATS_GROUP_DESC:
    new (&p.data.group_desc) Stats_req_group_desc(x.data.group_desc); break;
  case STATS_EXPERIMENTER:
    new (&p.data.experimenter)
    Stats_req_experimenter(x.data.experimenter); break;
  default: variant_error(t);
  }
}

void
destroy(Stats_req_payload& p, Stats_type t)
{
  switch(t) {
  case STATS_DESC: p.data.desc.~Stats_req_desc(); break;
  case STATS_FLOW: p.data.flow.~Stats_req_flow(); break;
  case STATS_AGGREGATE: p.data.aggregate.~Stats_req_aggregate(); break;
  case STATS_TABLE: p.data.table.~Stats_req_table(); break;
  case STATS_PORT: p.data.port.~Stats_req_port(); break;
  case STATS_QUEUE: p.data.queue.~Stats_req_queue(); break;
  case STATS_GROUP: p.data.group.~Stats_req_group(); break;
  case STATS_GROUP_DESC: p.data.group_desc.~Stats_req_group_desc(); break;
  case STATS_EXPERIMENTER:
    p.data.experimenter.~Stats_req_experimenter(); break;
  default: return;
  }
}

Stats_req_payload&
assign(Stats_req_payload& p, Stats_req_payload&& x, Stats_type t)
{
  if (&p == &x)
    return p;

  if (not p) {
    construct(p, std::move(x), t);
    return p;
  }

  p.init = x.init;
  if (not p) {
    destroy(p, t);
    return p;
  }
  
  switch(t) {
  case STATS_DESC: p.data.desc = std::move(x.data.desc); break;
  case STATS_FLOW: p.data.flow = std::move(x.data.flow); break;
  case STATS_AGGREGATE: p.data.aggregate = std::move(x.data.aggregate); break;
  case STATS_TABLE: p.data.table = std::move(x.data.table); break;
  case STATS_PORT: p.data.port = std::move(x.data.port); break;
  case STATS_QUEUE: p.data.queue = std::move(x.data.queue); break;
  case STATS_GROUP: p.data.group = std::move(x.data.group); break;
  case STATS_GROUP_DESC: p.data.group_desc = std::move(x.data.group_desc); break;
  case STATS_EXPERIMENTER: p.data.experimenter = std::move(x.data.experimenter); break;
  default: variant_error(t);
  }
  return p;
}

Stats_req_payload&
assign(Stats_req_payload& p, const Stats_req_payload& x, Stats_type t)
{
  if (&p == &x)
    return p;

  if (not p) {
    construct (p, x, t);
    return p;
  }

  p.init = x.init;
  if (not p) {
    destroy(p, t);
    return p;
  }
  
  switch(t) {
  case STATS_DESC: p.data.desc = x.data.desc; break;
  case STATS_FLOW: p.data.flow = x.data.flow; break;
  case STATS_AGGREGATE: p.data.aggregate = x.data.aggregate; break;
  case STATS_TABLE: p.data.table = x.data.table; break;
  case STATS_PORT: p.data.port = x.data.port; break;
  case STATS_QUEUE: p.data.queue = x.data.queue; break;
  case STATS_GROUP: p.data.group = x.data.group; break;
  case STATS_GROUP_DESC: p.data.group_desc = x.data.group_desc; break;
  case STATS_EXPERIMENTER: p.data.experimenter = x.data.experimenter; break;
  default: variant_error(t);
  }
  return p;
}

bool
equal(const Stats_req_payload& a, const Stats_req_payload& b,
      Stats_type t1, Stats_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case STATS_DESC: return a.data.desc == b.data.desc;
  case STATS_FLOW: return a.data.flow == b.data.flow;
  case STATS_AGGREGATE: return a.data.aggregate == b.data.aggregate;
  case STATS_TABLE: return a.data.table == b.data.table;
  case STATS_PORT: return a.data.port == b.data.port;
  case STATS_QUEUE: return a.data.queue == b.data.queue;
  case STATS_GROUP: return a.data.group == b.data.group;
  case STATS_GROUP_DESC: return a.data.group_desc == b.data.group_desc;
  case STATS_EXPERIMENTER: return a.data.experimenter == b.data.experimenter;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Stats_req_payload& p, Stats_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case STATS_DESC: return bytes(p.data.desc);
  case STATS_FLOW: return bytes(p.data.flow);
  case STATS_AGGREGATE: return bytes(p.data.aggregate);
  case STATS_TABLE: return bytes(p.data.table);
  case STATS_PORT: return bytes(p.data.port);
  case STATS_QUEUE: return bytes(p.data.queue);
  case STATS_GROUP: return bytes(p.data.group);
  case STATS_GROUP_DESC: return bytes(p.data.group_desc);
  case STATS_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Stats_req_payload& p, Stats_type t)
{
  if (not p)
    return BAD_STATS_INIT;
  switch (t) {
  case STATS_DESC: return is_valid(p.data.desc);
  case STATS_FLOW: return is_valid(p.data.flow);
  case STATS_AGGREGATE: return is_valid(p.data.aggregate);
  case STATS_TABLE: return is_valid(p.data.table);
  case STATS_PORT: return is_valid(p.data.port);
  case STATS_QUEUE: return is_valid(p.data.queue);
  case STATS_GROUP: return is_valid(p.data.group);
  case STATS_GROUP_DESC: return is_valid(p.data.group_desc);
  case STATS_EXPERIMENTER: return is_valid(p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_STATS;
}

Error_condition
to_buffer(Buffer_view& v, const Stats_req_payload& p, Stats_type t)
{
  assert(p);
  switch (t) {
  case STATS_DESC: return to_buffer(v, p.data.desc);
  case STATS_FLOW: return to_buffer(v, p.data.flow);
  case STATS_AGGREGATE: return to_buffer(v, p.data.aggregate);
  case STATS_TABLE: return to_buffer(v, p.data.table);
  case STATS_PORT: return to_buffer(v, p.data.port);
  case STATS_QUEUE: return to_buffer(v, p.data.queue);
  case STATS_GROUP: return to_buffer(v, p.data.group);
  case STATS_GROUP_DESC: return to_buffer(v, p.data.group_desc);
  case STATS_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_STATS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_payload& p, Stats_type t)
{
  assert(p);
  switch (t) {
  case STATS_DESC: return from_buffer(v, p.data.desc);
  case STATS_FLOW: return from_buffer(v, p.data.flow);
  case STATS_AGGREGATE: return from_buffer(v, p.data.aggregate);
  case STATS_TABLE: return from_buffer(v, p.data.table);
  case STATS_PORT: return from_buffer(v, p.data.port);
  case STATS_QUEUE: return from_buffer(v, p.data.queue);
  case STATS_GROUP: return from_buffer(v, p.data.group);
  case STATS_GROUP_DESC: return from_buffer(v, p.data.group_desc);
  case STATS_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_STATS;
}

std::string
to_string(const Stats_req_payload& p, Formatter& fmt, Stats_type t)
{
  assert(p);
  switch (t) {
  case STATS_DESC: return to_string(p.data.desc, fmt);
  case STATS_FLOW: return to_string(p.data.flow, fmt);
  case STATS_AGGREGATE: return to_string(p.data.aggregate, fmt);
  case STATS_TABLE: return to_string(p.data.table, fmt);
  case STATS_PORT: return to_string(p.data.port, fmt);
  case STATS_QUEUE: return to_string(p.data.queue, fmt);
  case STATS_GROUP: return to_string(p.data.group, fmt);
  case STATS_GROUP_DESC: return to_string(p.data.group_desc, fmt);
  case STATS_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Stats Request: Header

Error_condition
to_buffer(Buffer_view& v, const Stats_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.flags);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.flags);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Stats_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Stats Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Flags", to_string(h.flags));

  close_block(ss, f, "Stats Hdr");
  return ss.str();
}

std::string
to_string(Stats_header::Flags f)
{
  std::stringstream ss;
  if (f & Stats_header::MORE)
    ss << "More";
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Request

Error_condition
to_buffer(Buffer_view& v, const Stats_req& sr)
{
  if (not available(v, bytes(sr.header)))
    return AVAILABLE_STATS_REQ;
  to_buffer(v, sr.header);
  return to_buffer(v, sr.payload, sr.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Stats_req& sr)
{
  if (not available(v, bytes(sr.header)))
    return AVAILABLE_STATS_REQ;
  from_buffer(v, sr.header);

  if (not is_valid(sr.header.type))
    return BAD_STATS;
  
  Stats_req::Payload p;
  construct(p, sr.header.type);
  assign(sr.payload, std::move(p), sr.header.type);

  return from_buffer(v, sr.payload, sr.header.type);
}

std::string
to_string(const Stats_req& sr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq");

  ss << to_string(sr.header, f);
  if (is_valid(sr.header))
    ss << to_string(sr.payload, f, sr.header.type);

  close_block(ss, f, "StatsReq");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Description

Error_condition
to_buffer(Buffer_view& v, const Stats_res_desc& d)
{
  if (not available(v, bytes(d)))
    return AVAILABLE_STATS_RES_DESC;
  to_buffer(v, d.mfr_desc);
  to_buffer(v, d.hw_desc);
  to_buffer(v, d.sw_desc);
  to_buffer(v, d.serial_num);
  to_buffer(v, d.dp_desc);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_desc& d)
{
  if (not available (v, bytes(d)))
    return AVAILABLE_STATS_RES_DESC;
  from_buffer(v, d.mfr_desc);
  from_buffer(v, d.hw_desc);
  from_buffer(v, d.sw_desc);
  from_buffer(v, d.serial_num);
  from_buffer(v, d.dp_desc);
  return SUCCESS;
}

std::string to_string(const Stats_res_desc& d, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Description");

  nvp_to_string(ss, f, "Manufacturer Description", d.mfr_desc.str());
  nvp_to_string(ss, f, "Hardware Description", d.hw_desc.str());
  nvp_to_string(ss, f, "Softwrae Description", d.sw_desc.str());
  nvp_to_string(ss, f, "Datapath Description", d.dp_desc.str());
  nvp_to_string(ss, f, "Serial Number", d.serial_num.str());

  close_block(ss, f, "StatsRes Description");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Flow

Error_condition
to_buffer(Buffer_view& v, const Stats_res_flow& f)
{
  if (not available (v, bytes(f)))
    return AVAILABLE_STATS_RES_FLOW;

  to_buffer(v, f.length);
  to_buffer(v, f.table_id);
  pad(v, 1);
  to_buffer(v, f.duration_sec);
  to_buffer(v, f.duration_nsec);
  to_buffer(v, f.priority);
  to_buffer(v, f.idle_timeout);
  to_buffer(v, f.hard_timeout);
  pad(v, 6);
  to_buffer(v, f.cookie);
  to_buffer(v, f.packet_count);
  to_buffer(v, f.byte_count);

  if (Error_decl err = to_buffer(v, f.match))
    return err;
  return to_buffer(v, f.instructions);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_flow& f)
{
  if (not available (v, bytes(f)))
    return AVAILABLE_STATS_RES_FLOW;

  from_buffer(v, f.length);
  from_buffer(v, f.table_id);
  pad(v, 1);
  from_buffer(v, f.duration_sec);
  from_buffer(v, f.duration_nsec);
  from_buffer(v, f.priority);
  from_buffer(v, f.idle_timeout);
  from_buffer(v, f.hard_timeout);
  pad(v, 6);
  from_buffer(v, f.cookie);
  from_buffer(v, f.packet_count);
  from_buffer(v, f.byte_count);
  from_buffer(v, f.match);

  std::size_t n = f.length - bytes(f);
  if (remaining(v) < n)
    return AVAILABLE_INSTRUCTION;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, f.instructions))
    return err;
  
  if (not update(v, c))
    return EXCESS_STATS_RES_FLOW;
  
  return SUCCESS;
}

std::string
to_string(const Stats_res_flow& srf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Flow");

  nvp_to_string(ss, f, "Length", srf.length);
  nvp_to_string(ss, f, "Table ID", int(srf.table_id));
  nvp_to_string(ss, f, "Duration in Seconds", srf.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoseconds", srf.duration_nsec);
  nvp_to_string(ss, f, "Priority", srf.priority);
  nvp_to_string(ss, f, "Idle Timeout", srf.idle_timeout);
  nvp_to_string(ss, f, "Hard Timeout", srf.hard_timeout);
  nvp_to_string(ss, f, "Cookie", srf.cookie);
  nvp_to_string(ss, f, "Packet Count", srf.packet_count);
  nvp_to_string(ss, f, "Byte Count", srf.byte_count);

  ss << to_string(srf.match, f);
  ss << to_string(srf.instructions, f);

  close_block(ss, f, "StatsRes Flow");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Flows

Error_condition
to_buffer(Buffer_view& v, const Stats_res_flows& srf)
{
  if (not available (v, bytes(srf)))
    return AVAILABLE_STATS_RES_FLOWS;
  return to_buffer(v, srf.flows);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_flows& srf)
{
  if (not available (v, bytes(srf)))
    return AVAILABLE_STATS_RES_FLOWS;
  return from_buffer(v, srf.flows);
}

std::string
to_string(const Stats_res_flows& srf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Flows");

  ss << to_string(srf.flows, f);

  close_block(ss, f, "StatsRes Flows");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Aggregate

Error_condition
to_buffer(Buffer_view& v, const Stats_res_aggregate& a)
{
  if (not available (v, bytes(a)))
    return AVAILABLE_STATS_RES_AGGREGATE;
  to_buffer(v, a.packet_count);
  to_buffer(v, a.byte_count);
  to_buffer(v, a.flow_count);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_aggregate& a)
{
  if (not available (v, bytes(a)))
    return AVAILABLE_STATS_RES_AGGREGATE;
  from_buffer(v, a.packet_count);
  from_buffer(v, a.byte_count);
  from_buffer(v, a.flow_count);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Stats_res_aggregate& a, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Aggregate");

  nvp_to_string(ss, f, "Packet Count", a.packet_count);
  nvp_to_string(ss, f, "Byte Count", a.byte_count);
  nvp_to_string(ss, f, "Flow Count", a.flow_count);

  close_block(ss, f, "StatsRes Aggregate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Port

Error_condition
to_buffer(Buffer_view& v, const Stats_res_port& srp)
{
  if (not available (v, bytes(srp)))
    return AVAILABLE_STATS_RES_PORT;
  to_buffer(v, srp.port_no);
  pad(v, 4);
  to_buffer(v, srp.rx_packets);
  to_buffer(v, srp.tx_packets);
  to_buffer(v, srp.rx_bytes);
  to_buffer(v, srp.tx_bytes);
  to_buffer(v, srp.rx_dropped);
  to_buffer(v, srp.tx_dropped);
  to_buffer(v, srp.rx_errors);
  to_buffer(v, srp.tx_errors);
  to_buffer(v, srp.rx_frame_err);
  to_buffer(v, srp.rx_over_err);
  to_buffer(v, srp.rx_crc_err);
  to_buffer(v, srp.collisions);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_port& srp)
{
  if (not available (v, bytes(srp)))
    return AVAILABLE_STATS_RES_PORT;
  from_buffer(v, srp.port_no);
  pad(v, 4);
  from_buffer(v, srp.rx_packets);
  from_buffer(v, srp.tx_packets);
  from_buffer(v, srp.rx_bytes);
  from_buffer(v, srp.tx_bytes);
  from_buffer(v, srp.rx_dropped);
  from_buffer(v, srp.tx_dropped);
  from_buffer(v, srp.rx_errors);
  from_buffer(v, srp.tx_errors);
  from_buffer(v, srp.rx_frame_err);
  from_buffer(v, srp.rx_over_err);
  from_buffer(v, srp.rx_crc_err);
  from_buffer(v, srp.collisions);
  return SUCCESS;
}

std::string
to_string(const Stats_res_port& srp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Port");

  nvp_to_string(ss, f, "Port No", srp.port_no);
  nvp_to_string(ss, f, "Rx Packets", srp.rx_packets);
  nvp_to_string(ss, f, "Tx Packets", srp.tx_packets);
  nvp_to_string(ss, f, "Rx Bytes", srp.rx_bytes);
  nvp_to_string(ss, f, "Tx Bytes", srp.tx_bytes);
  nvp_to_string(ss, f, "Rx Dropped", srp.rx_dropped);
  nvp_to_string(ss, f, "Tx Dropped", srp.tx_dropped);
  nvp_to_string(ss, f, "Rx Errors", srp.rx_errors);
  nvp_to_string(ss, f, "Tx Errors", srp.tx_errors);
  nvp_to_string(ss, f, "Rx Frame Error", srp.rx_frame_err);
  nvp_to_string(ss, f, "Rx Over Error", srp.rx_over_err);
  nvp_to_string(ss, f, "Rx CRC Error", srp.rx_crc_err);
  nvp_to_string(ss, f, "Collisions", srp.collisions);

  close_block(ss, f, "StatsRes Port");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Ports

Error_condition
to_buffer(Buffer_view& v, const Stats_res_ports& srp)
{
  if (not available (v, bytes(srp)))
    return AVAILABLE_STATS_RES_PORTS;
  return to_buffer(v, srp.ports);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_ports& srp)
{
  if (not available (v, bytes(srp)))
    return AVAILABLE_STATS_RES_PORTS;
  return from_buffer(v, srp.ports);
}

std::string
to_string(const Stats_res_ports& srp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Ports");

  ss << to_string(srp.ports, f);

  close_block(ss, f, "StatsRes Ports");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Queue

Error_condition
to_buffer(Buffer_view& v, const Stats_res_queue& srq)
{
  if (not available (v, bytes(srq)))
    return AVAILABLE_STATS_RES_QUEUE;
  to_buffer(v, srq.port_no);
  to_buffer(v, srq.queue_id);
  to_buffer(v, srq.tx_bytes);
  to_buffer(v, srq.tx_packets);
  to_buffer(v, srq.tx_errors);

  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_queue& srq)
{
  if (not available (v, bytes(srq)))
    return AVAILABLE_STATS_RES_QUEUE;
  from_buffer(v, srq.port_no);
  from_buffer(v, srq.queue_id);
  from_buffer(v, srq.tx_bytes);
  from_buffer(v, srq.tx_packets);
  from_buffer(v, srq.tx_errors);

  return SUCCESS;
}

std::string
to_string(const Stats_res_queue& srq, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Queue");

  nvp_to_string(ss, f, "Port No", srq.port_no);
  nvp_to_string(ss, f, "Queue ID", srq.queue_id);
  nvp_to_string(ss, f, "Tx Bytes", srq.tx_bytes);
  nvp_to_string(ss, f, "Tx Packets", srq.tx_packets);
  nvp_to_string(ss, f, "Tx Errors", srq.tx_errors);

  close_block(ss, f, "StatsRes Queue");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Queues

Error_condition
to_buffer(Buffer_view& v, const Stats_res_queues& srq)
{
  if (not available (v, bytes(srq)))
    return AVAILABLE_STATS_RES_QUEUES;
  return to_buffer(v, srq.queues);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_queues& srq)
{
  if (not available (v, bytes(srq)))
    return AVAILABLE_STATS_RES_QUEUES;
  return from_buffer(v, srq.queues);
}

std::string
to_string(const Stats_res_queues& srq, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Queues");

  ss << to_string(srq.queues, f);

  close_block(ss, f, "StatsRes Queues");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Table

Error_condition
to_buffer(Buffer_view& v, const Stats_res_table& t)
{
  if (not available (v, bytes(t)))
    return AVAILABLE_STATS_RES_TABLE;
  to_buffer(v, t.table_id);
  pad(v, 7);
  to_buffer(v, t.name);
  to_buffer(v, t.wildcards);
  to_buffer(v, t.match);
  to_buffer(v, t.instructions);
  to_buffer(v, t.write_actions);
  to_buffer(v, t.apply_actions);
  to_buffer(v, t.config);
  to_buffer(v, t.max_entries);
  to_buffer(v, t.active_count);
  to_buffer(v, t.lookup_count);
  to_buffer(v, t.matched_count);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_table& t)
{
  if (not available (v, bytes(t)))
    return AVAILABLE_STATS_RES_TABLE;
  from_buffer(v, t.table_id);
  pad(v, 7);
  from_buffer(v, t.name);
  from_buffer(v, t.wildcards);
  from_buffer(v, t.match);
  from_buffer(v, t.instructions);
  from_buffer(v, t.write_actions);
  from_buffer(v, t.apply_actions);
  from_buffer(v, t.config);
  from_buffer(v, t.max_entries);
  from_buffer(v, t.active_count);
  from_buffer(v, t.lookup_count);
  from_buffer(v, t.matched_count);
  return SUCCESS;
}

std::string
to_string(const Stats_res_table& t, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Table");

  nvp_to_string(ss, f, "Table ID", int(t.table_id));
  nvp_to_string(ss, f, "Name", t.name.str());
  nvp_to_string(ss, f, "Wildcards", t.wildcards);
  nvp_to_string(ss, f, "Match", t.match);
  nvp_to_string(ss, f, "Instructions", t.instructions);
  nvp_to_string(ss, f, "Write Actions", t.write_actions);
  nvp_to_string(ss, f, "Apply Actions", t.apply_actions);
  nvp_to_string(ss, f, "Config", t.config);
  nvp_to_string(ss, f, "Max Entries", t.max_entries);
  nvp_to_string(ss, f, "Active Count", t.active_count);
  nvp_to_string(ss, f, "Lookup Count", t.lookup_count);
  nvp_to_string(ss, f, "Matched Count", t.matched_count);

  close_block(ss, f, "StatsRes Table");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Tables

Error_condition
to_buffer(Buffer_view& v, const Stats_res_tables& srt)
{
  if (not available (v, bytes(srt)))
    return AVAILABLE_STATS_RES_TABLES;
  return to_buffer(v, srt.tables);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_tables& srt)
{
  if (not available (v, bytes(srt)))
    return AVAILABLE_STATS_RES_TABLES;
  return from_buffer(v, srt.tables);
}

std::string
to_string(const Stats_res_tables& srt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Tables");

  ss << to_string(srt.tables, f);

  close_block(ss, f, "StatsRes Tables");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Bucket counter

Error_condition
to_buffer(Buffer_view& v, const Bucket_counter& bc)
{
  if (not available(v, bytes(bc)))
    return AVAILABLE_BUCKET_COUNTER;
  to_buffer(v, bc.packet_count);
  to_buffer(v, bc.byte_count);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Bucket_counter& bc)
{
  if (not available(v, bytes(bc)))
    return AVAILABLE_BUCKET_COUNTER;
  from_buffer(v, bc.packet_count);
  from_buffer(v, bc.byte_count);
  return SUCCESS;
}

std::string
to_string(const Bucket_counter& bc, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Bucket Counter");

  nvp_to_string(ss, f, "Packet Count", bc.packet_count);
  nvp_to_string(ss, f, "Byte Count", bc.byte_count);

  close_block(ss, f, "Bucket Counter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Group

Error_condition
to_buffer(Buffer_view& v, const Stats_res_group& g)
{
  if (not available (v, bytes(g)))
    return AVAILABLE_STATS_RES_GROUP;

  to_buffer(v, g.length);
  pad(v, 2);
  to_buffer(v, g.group_id);
  to_buffer(v, g.ref_count);
  pad(v, 4);
  to_buffer(v, g.packet_count);
  to_buffer(v, g.byte_count);

  return to_buffer(v, g.bucket_stats);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_group& g)
{
  if (not available (v, bytes(g)))
    return AVAILABLE_STATS_RES_GROUP;

  from_buffer(v, g.length);
  pad(v, 2);
  from_buffer(v, g.group_id);
  from_buffer(v, g.ref_count);
  pad(v, 4);
  from_buffer(v, g.packet_count);
  from_buffer(v, g.byte_count);

  if (g.length < bytes(g))
    return BAD_STATS_RES_GROUP_LENGTH;

  std::size_t n = g.length - 32;
  if (remaining(v) < n)
    return AVAILABLE_BUCKET_COUNTER;
  
  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, g.bucket_stats))
    return err;
  
  if (not update(v, c))
    return EXCESS_STATS_RES_GROUP;

  return SUCCESS;
}

std::string
to_string(const Stats_res_group& g, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Group");

  nvp_to_string(ss, f, "Length", g.length);
  nvp_to_string(ss, f, "Group ID", g.group_id);
  nvp_to_string(ss, f, "Ref Count", g.ref_count);
  nvp_to_string(ss, f, "Packet Count", g.packet_count);
  nvp_to_string(ss, f, "Byte Count", g.byte_count);

  ss << to_string(g.bucket_stats, f);

  close_block(ss, f, "StatsRes Group");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Groups

Error_condition
to_buffer(Buffer_view& v, const Stats_res_groups& srg)
{
  if (not available (v, bytes(srg)))
    return AVAILABLE_STATS_RES_GROUPS;
  return to_buffer(v, srg.groups);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_groups& srg)
{
  if (not available (v, bytes(srg)))
    return AVAILABLE_STATS_RES_GROUPS;
  return from_buffer(v, srg.groups);
}

std::string
to_string(const Stats_res_groups& srg, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Groups");

  ss << to_string(srg.groups, f);

  close_block(ss, f, "StatsRes Groups");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Group Desc

Error_condition
to_buffer(Buffer_view& v, const Stats_res_group_desc& gd)
{
  if (not available (v, bytes(gd)))
    return AVAILABLE_STATS_RES_GROUP_DESC;

  to_buffer(v, gd.length);
  to_buffer(v, gd.type);
  pad(v, 1);
  to_buffer(v, gd.group_id);

  return to_buffer(v, gd.buckets);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_group_desc& gd)
{
  if (not available (v, bytes(gd)))
    return AVAILABLE_STATS_RES_GROUP_DESC;

  from_buffer(v, gd.length);
  from_buffer(v, gd.type);
  pad(v, 1);
  from_buffer(v, gd.group_id);

  if (gd.length < bytes(gd))
    return BAD_STATS_RES_GROUP_DESC_LENGTH;

  std::size_t n = gd.length - 8;
  if (remaining(v) < n)
    return AVAILABLE_BUCKET;
  
  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, gd.buckets))
    return err;
  
  if (not update(v, c))
    return EXCESS_STATS_RES_GROUP_DESC;
  
  return SUCCESS;
}

std::string
to_string(const Stats_res_group_desc& gd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes GroupDesc");

  nvp_to_string(ss, f, "Length", gd.length);
  nvp_to_string(ss, f, "Type", int(gd.type));
  nvp_to_string(ss, f, "Group ID", gd.group_id);

  ss << to_string(gd.buckets, f);

  close_block(ss, f, "StatsRes GroupDesc");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Group Descs

Error_condition
to_buffer(Buffer_view& v, const Stats_res_group_descs& srgd)
{
  if (not available (v, bytes(srgd)))
    return AVAILABLE_STATS_RES_GROUP_DESCS;
  return to_buffer(v, srgd.group_descs);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_group_descs& srgd)
{
  if (not available (v, bytes(srgd)))
    return AVAILABLE_STATS_RES_GROUP_DESCS;
  return from_buffer(v, srgd.group_descs);
}

std::string
to_string(const Stats_res_group_descs& srgd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes GroupDescs");

  ss << to_string(srgd.group_descs, f);

  close_block(ss, f, "StatsRes GroupDescs");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response: Experimenter

Error_condition
to_buffer(Buffer_view& v, const Stats_res_experimenter& sre)
{
  if (not available(v, bytes(sre)))
    return AVAILABLE_STATS_RES_EXPERIMENTER;
  to_buffer(v, sre.experimenter_id);
  return to_buffer(v, sre.data);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_experimenter& sre)
{
  if (not available(v, bytes(sre)))
    return AVAILABLE_STATS_RES_EXPERIMENTER;
  from_buffer(v, sre.experimenter_id);
  return from_buffer(v, sre.data);
}

std::string
to_string(const Stats_res_experimenter& sre, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Experimenter");

  nvp_to_string(ss, f, "Experimenter ID", sre.experimenter_id);
  nvp_to_string(ss, f, "Data bytes", bytes(sre.data));

  close_block(ss, f, "StatsRes Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats Response Payload

void
construct(Stats_res_payload& p, Stats_type t)
{
  p.init = true;
  switch(t) {
  case STATS_DESC: new (&p.data.desc) Stats_res_desc(); break;
  case STATS_FLOW: new (&p.data.flow) Stats_res_flows(); break;
  case STATS_AGGREGATE: new (&p.data.aggregate) Stats_res_aggregate(); break;
  case STATS_TABLE: new (&p.data.table) Stats_res_tables(); break;
  case STATS_PORT: new (&p.data.port) Stats_res_ports(); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_res_queues(); break;
  case STATS_GROUP: new (&p.data.group) Stats_res_groups(); break;
  case STATS_GROUP_DESC: new (&p.data.group_desc) Stats_res_group_descs();
    break;
  case STATS_EXPERIMENTER:
    new (&p.data.experimenter) Stats_res_experimenter(); break;
  default: variant_error(t);
  }
}

void
construct(Stats_res_payload& p, Stats_res_payload&& x, Stats_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case STATS_DESC:
    new (&p.data.desc) Stats_res_desc(std::move(x.data.desc)); break;
  case STATS_FLOW:
    new (&p.data.flow) Stats_res_flows(std::move(x.data.flow)); break;
  case STATS_AGGREGATE:
    new (&p.data.aggregate)
    Stats_res_aggregate(std::move(x.data.aggregate)); break;
  case STATS_TABLE:
    new (&p.data.table) Stats_res_tables(std::move(x.data.table)); break;
  case STATS_PORT:
    new (&p.data.port) Stats_res_ports(std::move(x.data.port)); break;
  case STATS_QUEUE:
    new (&p.data.queue) Stats_res_queues(std::move(x.data.queue)); break;
  case STATS_GROUP:
    new (&p.data.group) Stats_res_groups(std::move(x.data.group)); break;
  case STATS_GROUP_DESC:
    new (&p.data.group_desc)
    Stats_res_group_descs(std::move(x.data.group_desc)); break;
  case STATS_EXPERIMENTER:
    new (&p.data.experimenter)
    Stats_res_experimenter(std::move(x.data.experimenter)); break;
  default: variant_error(t);
  }
}

void
construct(Stats_res_payload& p, const Stats_res_payload& x, Stats_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case STATS_DESC: new (&p.data.desc) Stats_res_desc(x.data.desc); break;
  case STATS_FLOW: new (&p.data.flow) Stats_res_flows(x.data.flow); break;
  case STATS_AGGREGATE:
    new (&p.data.aggregate) Stats_res_aggregate(x.data.aggregate); break;
  case STATS_TABLE: new (&p.data.table) Stats_res_tables(x.data.table); break;
  case STATS_PORT: new (&p.data.port) Stats_res_ports(x.data.port); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_res_queues(x.data.queue); break;
  case STATS_GROUP: new (&p.data.group) Stats_res_groups(x.data.group); break;
  case STATS_GROUP_DESC:
    new (&p.data.group_desc) Stats_res_group_descs(x.data.group_desc); break;
  case STATS_EXPERIMENTER:
    new (&p.data.experimenter)
    Stats_res_experimenter(x.data.experimenter); break;
  default: variant_error(t);
  }
}

void
destroy(Stats_res_payload& p, Stats_type t)
{
  switch(t) {
  case STATS_DESC: p.data.desc.~Stats_res_desc(); break;
  case STATS_FLOW: p.data.flow.~Stats_res_flows(); break;
  case STATS_AGGREGATE: p.data.aggregate.~Stats_res_aggregate(); break;
  case STATS_TABLE: p.data.table.~Stats_res_tables(); break;
  case STATS_PORT: p.data.port.~Stats_res_ports(); break;
  case STATS_QUEUE: p.data.queue.~Stats_res_queues(); break;
  case STATS_GROUP: p.data.group.~Stats_res_groups(); break;
  case STATS_GROUP_DESC: p.data.group_desc.~Stats_res_group_descs(); break;
  case STATS_EXPERIMENTER:
    p.data.experimenter.~Stats_res_experimenter(); break;
  default: return;
  }
}

Stats_res_payload&
assign(Stats_res_payload& p, Stats_res_payload&& x, Stats_type t)
{
  if (&p == &x)
    return p;

  if (not p) {
    construct(p, std::move(x), t);
    return p;
  }

  p.init = x.init;
  if (not p) {
    destroy(p, t);
    return p;
  }
  
  switch(t) {
  case STATS_DESC: p.data.desc = std::move(x.data.desc); break;
  case STATS_FLOW: p.data.flow = std::move(x.data.flow); break;
  case STATS_AGGREGATE: p.data.aggregate = std::move(x.data.aggregate); break;
  case STATS_TABLE: p.data.table = std::move(x.data.table); break;
  case STATS_PORT: p.data.port = std::move(x.data.port); break;
  case STATS_QUEUE: p.data.queue = std::move(x.data.queue); break;
  case STATS_GROUP: p.data.group = std::move(x.data.group); break;
  case STATS_GROUP_DESC: p.data.group_desc = std::move(x.data.group_desc); break;
  case STATS_EXPERIMENTER: p.data.experimenter = std::move(x.data.experimenter); break;
  default: variant_error(t);
  }
  return p;
}

Stats_res_payload&
assign(Stats_res_payload& p, const Stats_res_payload& x, Stats_type t)
{
  if (&p == &x)
    return p;

  if (not p) {
    construct(p, x, t);
    return p;
  }

  p.init = x.init;
  if (not p) {
    destroy(p, t);
    return p;
  }

  switch(t) {
  case STATS_DESC: p.data.desc = x.data.desc; break;
  case STATS_FLOW: p.data.flow = x.data.flow; break;
  case STATS_AGGREGATE: p.data.aggregate = x.data.aggregate; break;
  case STATS_TABLE: p.data.table = x.data.table; break;
  case STATS_PORT: p.data.port = x.data.port; break;
  case STATS_QUEUE: p.data.queue = x.data.queue; break;
  case STATS_GROUP: p.data.group = x.data.group; break;
  case STATS_GROUP_DESC: p.data.group_desc = x.data.group_desc; break;
  case STATS_EXPERIMENTER: p.data.experimenter = x.data.experimenter; break;
  default: variant_error(t);
  }
  return p;
}

bool
equal(const Stats_res_payload& a, const Stats_res_payload& b,
      Stats_type t1, Stats_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case STATS_DESC: return a.data.desc == b.data.desc;
  case STATS_FLOW: return a.data.flow == b.data.flow;
  case STATS_AGGREGATE: return a.data.aggregate == b.data.aggregate;
  case STATS_TABLE: return a.data.table == b.data.table;
  case STATS_PORT: return a.data.port == b.data.port;
  case STATS_QUEUE: return a.data.queue == b.data.queue;
  case STATS_GROUP: return a.data.group == b.data.group;
  case STATS_GROUP_DESC: return a.data.group_desc == b.data.group_desc;
  case STATS_EXPERIMENTER: return a.data.experimenter == b.data.experimenter;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Stats_res_payload& p, Stats_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case STATS_DESC: return bytes(p.data.desc);
  case STATS_FLOW: return bytes(p.data.flow);
  case STATS_AGGREGATE: return bytes(p.data.aggregate);
  case STATS_TABLE: return bytes(p.data.table);
  case STATS_PORT: return bytes(p.data.port);
  case STATS_QUEUE: return bytes(p.data.queue);
  case STATS_GROUP: return bytes(p.data.group);
  case STATS_GROUP_DESC: return bytes(p.data.group_desc);
  case STATS_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Stats_res_payload& p, Stats_type t)
{
  if (not p)
    return BAD_STATS_INIT;
  switch (t) {
  case STATS_DESC: return is_valid(p.data.desc);
  case STATS_FLOW: return is_valid(p.data.flow);
  case STATS_AGGREGATE: return is_valid(p.data.aggregate);
  case STATS_TABLE: return is_valid(p.data.table);
  case STATS_PORT: return is_valid(p.data.port);
  case STATS_QUEUE: return is_valid(p.data.queue);
  case STATS_GROUP: return is_valid(p.data.group);
  case STATS_GROUP_DESC: return is_valid(p.data.group_desc);
  case STATS_EXPERIMENTER: return is_valid(p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_STATS;
}

Error_condition
to_buffer(Buffer_view& v, const Stats_res_payload& p, Stats_type t)
{
  assert(p);
  switch (t) {
  case STATS_DESC: return to_buffer(v, p.data.desc);
  case STATS_FLOW: return to_buffer(v, p.data.flow);
  case STATS_AGGREGATE: return to_buffer(v, p.data.aggregate);
  case STATS_TABLE: return to_buffer(v, p.data.table);
  case STATS_PORT: return to_buffer(v, p.data.port);
  case STATS_QUEUE: return to_buffer(v, p.data.queue);
  case STATS_GROUP: return to_buffer(v, p.data.group);
  case STATS_GROUP_DESC: return to_buffer(v, p.data.group_desc);
  case STATS_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_STATS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_payload& p, Stats_type t)
{
  assert(p);
  switch (t) {
  case STATS_DESC: return from_buffer(v, p.data.desc);
  case STATS_FLOW: return from_buffer(v, p.data.flow);
  case STATS_AGGREGATE: return from_buffer(v, p.data.aggregate);
  case STATS_TABLE: return from_buffer(v, p.data.table);
  case STATS_PORT: return from_buffer(v, p.data.port);
  case STATS_QUEUE: return from_buffer(v, p.data.queue);
  case STATS_GROUP: return from_buffer(v, p.data.group);
  case STATS_GROUP_DESC: return from_buffer(v, p.data.group_desc);
  case STATS_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_STATS;
}

std::string
to_string(const Stats_res_payload& p, Formatter& fmt, Stats_type t)
{
  assert(p);
  switch (t) {
  case STATS_DESC: return to_string(p.data.desc, fmt);
  case STATS_FLOW: return to_string(p.data.flow, fmt);
  case STATS_AGGREGATE: return to_string(p.data.aggregate, fmt);
  case STATS_TABLE: return to_string(p.data.table, fmt);
  case STATS_PORT: return to_string(p.data.port, fmt);
  case STATS_QUEUE: return to_string(p.data.queue, fmt);
  case STATS_GROUP: return to_string(p.data.group, fmt);
  case STATS_GROUP_DESC: return to_string(p.data.group_desc, fmt);
  case STATS_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Stats Response

Error_condition
to_buffer(Buffer_view& v, const Stats_res& sr)
{
  if (not available(v, bytes(sr.header)))
    return AVAILABLE_STATS_RES;
  to_buffer(v, sr.header);
  return to_buffer(v, sr.payload, sr.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res& sr)
{
  if (not available(v, bytes(sr.header)))
    return AVAILABLE_STATS_RES;
  from_buffer(v, sr.header);

  if (not is_valid(sr.header.type))
    return BAD_STATS;
  
  Stats_res::Payload p;
  construct(p, sr.header.type);
  assign(sr.payload, std::move(p), sr.header.type);

  return from_buffer(v, sr.payload, sr.header.type);
}

std::string
to_string(const Stats_res& sr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes");

  ss << to_string(sr.header, f);
  if (is_valid(sr.header))
    ss << to_string(sr.payload, f, sr.header.type);

  close_block(ss, f, "StatsRes");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Queue Get Config Request

Error_condition
to_buffer(Buffer_view& v, const Queue_get_config_req& qgcr)
{
  if (not available(v, bytes(qgcr)))
    return AVAILABLE_QUEUE_GET_CONFIG_REQ;
  to_buffer(v, qgcr.port);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Queue_get_config_req& qgcr)
{
  if (not available(v, bytes(qgcr)))
    return AVAILABLE_QUEUE_GET_CONFIG_REQ;
  from_buffer(v, qgcr.port);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Queue_get_config_req& qgcr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "QueueGetConfigReq");

  nvp_to_string(ss, f, "Port", qgcr.port);

  close_block(ss, f, "QueueGetConfigReq");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Queue get config response

Error_condition
to_buffer(Buffer_view& v, const Queue_get_config_res& qgcr)
{
  if (not available(v, bytes(qgcr)))
    return AVAILABLE_QUEUE_GET_CONFIG_RES;
  to_buffer(v, qgcr.port);
  pad(v, 4);
  return to_buffer(v, qgcr.queues);
}

Error_condition
from_buffer(Buffer_view& v, Queue_get_config_res& qgcr)
{
  if (not available(v, bytes(qgcr)))
    return AVAILABLE_QUEUE_GET_CONFIG_RES;
  from_buffer(v, qgcr.port);
  pad(v, 4);
  return from_buffer(v, qgcr.queues);
}

std::string
to_string(const Queue_get_config_res& qgcr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "QueueGetConfigRes");

  nvp_to_string(ss, f, "Port", qgcr.port);

  ss << to_string(qgcr.queues, f);

  close_block(ss, f, "QueueGetConfigRes");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Payload

void
construct(Payload& p, Message_type t)
{
  p.init = true;
  switch (t) {
  case HELLO: new (&p.data.hello) Hello(); break;
  case ERROR: new (&p.data.error) Error(); break;
  case ECHO_REQ: new (&p.data.echo_req) Echo_req(); break;
  case ECHO_RES: new (&p.data.echo_res) Echo_res(); break;
  case EXPERIMENTER: new (&p.data.experimenter) Experimenter(); break;
  case FEATURE_REQ: new (&p.data.feature_req) Feature_req(); break;
  case FEATURE_RES: new (&p.data.feature_res) Feature_res(); break;
  case GET_CONFIG_REQ: new (&p.data.get_config_req) Get_config_req(); break;
  case GET_CONFIG_RES: new (&p.data.get_config_res) Get_config_res(); break;
  case SET_CONFIG: new (&p.data.set_config) Set_config(); break;
  case PACKET_IN: new (&p.data.packet_in) Packet_in(); break;
  case FLOW_REMOVED: new (&p.data.flow_removed) Flow_removed(); break;
  case PORT_STATUS: new (&p.data.port_status) Port_status(); break;
  case PACKET_OUT: new (&p.data.packet_out) Packet_out(); break;
  case FLOW_MOD: new (&p.data.flow_mod) Flow_mod(); break;
  case GROUP_MOD: new (&p.data.group_mod) Group_mod(); break;
  case PORT_MOD: new (&p.data.port_mod) Port_mod(); break;
  case TABLE_MOD: new (&p.data.table_mod) Table_mod(); break;
  case STATS_REQ: new (&p.data.stats_req) Stats_req(); break;
  case STATS_RES: new (&p.data.stats_res) Stats_res(); break;
  case BARRIER_REQ: new (&p.data.barrier_req) Barrier_req(); break;
  case BARRIER_RES: new (&p.data.barrier_res) Barrier_res(); break;
  case QUEUE_GET_CONFIG_REQ:
    new (&p.data.queue_get_config_req) Queue_get_config_req(); break;
  case QUEUE_GET_CONFIG_RES:
    new (&p.data.queue_get_config_res) Queue_get_config_res(); break;
  default: variant_error(t);
  }
}

void
construct(Payload& p, Payload&& x, Message_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch (t) {
  case HELLO: new (&p.data.hello) Hello(std::move(x.data.hello)); break;
  case ERROR: new (&p.data.error) Error(std::move(x.data.error)); break;
  case ECHO_REQ:
    new (&p.data.echo_req) Echo_req(std::move(x.data.echo_req)); break;
  case ECHO_RES:
    new (&p.data.echo_res) Echo_res(std::move(x.data.echo_res)); break;
  case EXPERIMENTER:
    new (&p.data.experimenter) Experimenter(std::move(x.data.experimenter));
    break;
  case FEATURE_REQ:
    new (&p.data.feature_req) Feature_req(std::move(x.data.feature_req));
    break;
  case FEATURE_RES:
    new (&p.data.feature_res) Feature_res(std::move(x.data.feature_res));
    break;
  case GET_CONFIG_REQ:
    new (&p.data.get_config_req)
        Get_config_req(std::move(x.data.get_config_req)); break;
  case GET_CONFIG_RES:
    new (&p.data.get_config_res)
        Get_config_res(std::move(x.data.get_config_res)); break;
  case SET_CONFIG:
    new (&p.data.set_config) Set_config(std::move(x.data.set_config)); break;
  case PACKET_IN:
    new (&p.data.packet_in) Packet_in(std::move(x.data.packet_in)); break;
  case FLOW_REMOVED:
    new (&p.data.flow_removed) Flow_removed(std::move(x.data.flow_removed));
    break;
  case PORT_STATUS:
    new (&p.data.port_status) Port_status(std::move(x.data.port_status));
    break;
  case PACKET_OUT:
    new (&p.data.packet_out) Packet_out(std::move(x.data.packet_out)); break;
  case FLOW_MOD:
    new (&p.data.flow_mod) Flow_mod(std::move(x.data.flow_mod)); break;
  case GROUP_MOD:
    new (&p.data.group_mod) Group_mod(std::move(x.data.group_mod)); break;
  case PORT_MOD:
    new (&p.data.port_mod) Port_mod(std::move(x.data.port_mod)); break;
  case TABLE_MOD:
    new (&p.data.table_mod) Table_mod(std::move(x.data.table_mod)); break;
  case STATS_REQ:
    new (&p.data.stats_req) Stats_req(std::move(x.data.stats_req)); break;
  case STATS_RES:
    new (&p.data.stats_res) Stats_res(std::move(x.data.stats_res)); break;
  case BARRIER_REQ:
    new (&p.data.barrier_req) Barrier_req(std::move(x.data.barrier_req));
    break;
  case BARRIER_RES:
    new (&p.data.barrier_res) Barrier_res(std::move(x.data.barrier_res));
    break;
  case QUEUE_GET_CONFIG_REQ:
    new (&p.data.queue_get_config_req)
        Queue_get_config_req(std::move(x.data.queue_get_config_req)); break;
  case QUEUE_GET_CONFIG_RES:
    new (&p.data.queue_get_config_res)
        Queue_get_config_res(std::move(x.data.queue_get_config_res)); break;
  default: variant_error(t);
  }
}

void
construct(Payload& p, const Payload& x, Message_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch (t) {
  case HELLO: new (&p.data.hello) Hello(x.data.hello); break;
  case ERROR: new (&p.data.error) Error(x.data.error); break;
  case ECHO_REQ: new (&p.data.echo_req) Echo_req(x.data.echo_req); break;
  case ECHO_RES: new (&p.data.echo_res) Echo_res(x.data.echo_res); break;
  case EXPERIMENTER:
    new (&p.data.experimenter) Experimenter(x.data.experimenter); break;
  case FEATURE_REQ:
    new (&p.data.feature_req) Feature_req(x.data.feature_req); break;
  case FEATURE_RES: new (&p.data.feature_res) Feature_res(x.data.feature_res);
    break;
  case GET_CONFIG_REQ:
    new (&p.data.get_config_req) Get_config_req(x.data.get_config_req); break;
  case GET_CONFIG_RES:
    new (&p.data.get_config_res) Get_config_res(x.data.get_config_res); break;
  case SET_CONFIG:
    new (&p.data.set_config) Set_config(x.data.set_config); break;
  case PACKET_IN:
    new (&p.data.packet_in) Packet_in(x.data.packet_in); break;
  case FLOW_REMOVED:
    new (&p.data.flow_removed) Flow_removed(x.data.flow_removed); break;
  case PORT_STATUS:
    new (&p.data.port_status) Port_status(x.data.port_status); break;
  case PACKET_OUT:
    new (&p.data.packet_out) Packet_out(x.data.packet_out); break;
  case FLOW_MOD:
    new (&p.data.flow_mod) Flow_mod(x.data.flow_mod); break;
  case GROUP_MOD:
    new (&p.data.group_mod) Group_mod(x.data.group_mod); break;
  case PORT_MOD:
    new (&p.data.port_mod) Port_mod(x.data.port_mod); break;
  case TABLE_MOD:
    new (&p.data.table_mod) Table_mod(x.data.table_mod); break;
  case STATS_REQ:
    new (&p.data.stats_req) Stats_req(x.data.stats_req); break;
  case STATS_RES:
    new (&p.data.stats_res) Stats_res(x.data.stats_res); break;
  case BARRIER_REQ:
    new (&p.data.barrier_req) Barrier_req(x.data.barrier_req); break;
  case BARRIER_RES:
    new (&p.data.barrier_res) Barrier_res(x.data.barrier_res); break;
  case QUEUE_GET_CONFIG_REQ:
    new (&p.data.queue_get_config_req)
        Queue_get_config_req(x.data.queue_get_config_req); break;
  case QUEUE_GET_CONFIG_RES:
    new (&p.data.queue_get_config_res)
       Queue_get_config_res(x.data.queue_get_config_res); break;
  default: variant_error(t);
  }
}

void
construct(Payload& p, Hello&& x) { 
  p.init = true; new (&p.data.hello) Hello(std::move(x)); 
}

void
construct(Payload& p, Error&& x) { 
  p.init = true; new (&p.data.error) Error(std::move(x)); 
}

void
construct(Payload& p, Echo_req&& x) { 
  p.init = true; new (&p.data.echo_req) Echo_req(std::move(x)); 
}

void
construct(Payload& p, Echo_res&& x) { 
  p.init = true; new (&p.data.echo_res) Echo_res(std::move(x)); 
}

void
construct(Payload& p, Experimenter&& x) { 
  p.init = true; new (&p.data.experimenter) Experimenter(std::move(x)); 
}

void
construct(Payload& p, Feature_req&& x) { 
  p.init = true; new (&p.data.feature_req) Feature_req(std::move(x)); 
}

void
construct(Payload& p, Feature_res&& x) { 
  p.init = true; new (&p.data.feature_res) Feature_res(std::move(x)); 
}

void
construct(Payload& p, Get_config_req&& x) { 
  p.init = true; new (&p.data.get_config_req) Get_config_req(std::move(x)); 
}

void
construct(Payload& p, Get_config_res&& x) { 
  p.init = true; new (&p.data.get_config_res) Get_config_res(std::move(x)); 
}

void
construct(Payload& p, Set_config&& x) { 
  p.init = true; new (&p.data.set_config) Set_config(std::move(x)); 
}

void
construct(Payload& p, Packet_in&& x) { 
  p.init = true; new (&p.data.packet_in) Packet_in(std::move(x)); 
}

void
construct(Payload& p, Packet_out&& x) { 
  p.init = true; new (&p.data.packet_out) Packet_out(std::move(x)); 
}

void
construct(Payload& p, Flow_mod&& x) { 
  p.init = true; new (&p.data.flow_mod) Flow_mod(std::move(x)); 
}

void
construct(Payload& p, Group_mod&& x) { 
  p.init = true; new (&p.data.group_mod) Group_mod(std::move(x)); 
}

void
construct(Payload& p, Port_mod&& x) { 
  p.init = true; new (&p.data.port_mod) Port_mod(std::move(x)); 
}

void
construct(Payload& p, Table_mod&& x) { 
  p.init = true; new (&p.data.table_mod) Table_mod(std::move(x)); 
}

void
construct(Payload& p, Stats_req&& x) { 
  p.init = true; new (&p.data.stats_req) Stats_req(std::move(x)); 
}

void
construct(Payload& p, Stats_res&& x) { 
  p.init = true; new (&p.data.stats_res) Stats_res(std::move(x)); 
}

void
construct(Payload& p, Barrier_req&& x) { 
  p.init = true; new (&p.data.barrier_req) Barrier_req(std::move(x)); 
}

void
construct(Payload& p, Barrier_res&& x) { 
  p.init = true; new (&p.data.barrier_res) Barrier_res(std::move(x)); 
}

void
construct(Payload& p, Queue_get_config_req&& x) { 
  p.init = true; new (&p.data.queue_get_config_req) Queue_get_config_req(std::move(x)); 
}

void
construct(Payload& p, Queue_get_config_res&& x) { 
  p.init = true; new (&p.data.queue_get_config_res) Queue_get_config_res(std::move(x)); 
}

void
construct(Payload& p, const Hello& x) { 
  p.init = true; new (&p.data.hello) Hello(x); 
}

void
construct(Payload& p, const Error& x) { 
  p.init = true; new (&p.data.error) Error(x); 
}

void
construct(Payload& p, const Echo_req& x) { 
  p.init = true; new (&p.data.echo_req) Echo_req(x); 
}

void
construct(Payload& p, const Echo_res& x) { 
  p.init = true; new (&p.data.echo_res) Echo_res(x); 
}

void
construct(Payload& p, const Experimenter& x) { 
  p.init = true; new (&p.data.experimenter) Experimenter(x); 
}

void
construct(Payload& p, const Feature_req& x) { 
  p.init = true; new (&p.data.feature_req) Feature_req(x); 
}

void
construct(Payload& p, const Feature_res& x) { 
  p.init = true; new (&p.data.feature_res) Feature_res(x); 
}

void
construct(Payload& p, const Get_config_req& x) { 
  p.init = true; new (&p.data.get_config_req) Get_config_req(x); 
}

void
construct(Payload& p, const Get_config_res& x) { 
  p.init = true; new (&p.data.get_config_res) Get_config_res(x); 
}

void
construct(Payload& p, const Set_config& x) { 
  p.init = true; new (&p.data.set_config) Set_config(x); 
}

void
construct(Payload& p, const Packet_in& x) { 
  p.init = true; new (&p.data.packet_in) Packet_in(x); 
}

void
construct(Payload& p, const Packet_out& x) { 
  p.init = true; new (&p.data.packet_out) Packet_out(x); 
}

void
construct(Payload& p, const Flow_mod& x) { 
  p.init = true; new (&p.data.flow_mod) Flow_mod(x); 
}

void
construct(Payload& p, const Group_mod& x) { 
  p.init = true; new (&p.data.group_mod) Group_mod(x); 
}

void
construct(Payload& p, const Port_mod& x) { 
  p.init = true; new (&p.data.port_mod) Port_mod(x); 
}

void
construct(Payload& p, const Table_mod& x) { 
  p.init = true; new (&p.data.table_mod) Table_mod(x); 
}

void
construct(Payload& p, const Stats_req& x) { 
  p.init = true; new (&p.data.stats_req) Stats_req(x); 
}

void
construct(Payload& p, const Stats_res& x) { 
  p.init = true; new (&p.data.stats_res) Stats_res(x); 
}

void
construct(Payload& p, const Barrier_req& x) { 
  p.init = true; new (&p.data.barrier_req) Barrier_req(x); 
}

void
construct(Payload& p, const Barrier_res& x) { 
  p.init = true; new (&p.data.barrier_res) Barrier_res(x); 
}

void
construct(Payload& p, const Queue_get_config_req& x) { 
  p.init = true; new (&p.data.queue_get_config_req) Queue_get_config_req(x); 
}

void
construct(Payload& p, const Queue_get_config_res& x) { 
  p.init = true; new (&p.data.queue_get_config_res) Queue_get_config_res(x); 
}

Payload&
assign(Payload& p, Payload&& x, Message_type t)
{
  if (&p == &x)
    return p;

  if (not p) {
    construct(p, std::move(x), t);
    return p;
  }

  p.init = x.init;
  if (not p) {
    destroy(p, t);
    return p;
  }
  
  switch (t) {
  case HELLO: p.data.hello = std::move(x.data.hello); break;
  case ERROR: p.data.error = std::move(x.data.error); break;
  case ECHO_REQ: p.data.echo_req = std::move(x.data.echo_req); break;
  case ECHO_RES: p.data.echo_res = std::move(x.data.echo_res); break;
  case EXPERIMENTER: p.data.experimenter = std::move(x.data.experimenter); break;
  case FEATURE_REQ: p.data.feature_req = std::move(x.data.feature_req); break;
  case FEATURE_RES: p.data.feature_res = std::move(x.data.feature_res); break;
  case GET_CONFIG_REQ: p.data.get_config_req = std::move(x.data.get_config_req); break;
  case GET_CONFIG_RES: p.data.get_config_res = std::move(x.data.get_config_res); break;
  case SET_CONFIG: p.data.set_config = std::move(x.data.set_config); break;
  case PACKET_IN: p.data.packet_in = std::move(x.data.packet_in); break;
  case FLOW_REMOVED: p.data.flow_removed = std::move(x.data.flow_removed); break;
  case PORT_STATUS: p.data.port_status = std::move(x.data.port_status); break;
  case PACKET_OUT: p.data.packet_out = std::move(x.data.packet_out); break;
  case FLOW_MOD: p.data.flow_mod = std::move(x.data.flow_mod); break;
  case GROUP_MOD: p.data.group_mod = std::move(x.data.group_mod); break;
  case PORT_MOD: p.data.port_mod = std::move(x.data.port_mod); break;
  case TABLE_MOD: p.data.table_mod = std::move(x.data.table_mod); break;
  case STATS_REQ: p.data.stats_req = std::move(x.data.stats_req); break;
  case STATS_RES: p.data.stats_res = std::move(x.data.stats_res); break;
  case BARRIER_REQ: p.data.barrier_req = std::move(x.data.barrier_req); break;
  case BARRIER_RES: p.data.barrier_res = std::move(x.data.barrier_res); break;
  case QUEUE_GET_CONFIG_REQ: p.data.queue_get_config_req = std::move(x.data.queue_get_config_req); break;
  case QUEUE_GET_CONFIG_RES: p.data.queue_get_config_res = std::move(x.data.queue_get_config_res); break;
  default: variant_error(t);
  }
  return p;
}

Payload&
assign(Payload& p, const Payload& x, Message_type t)
{
  if (&p == &x)
    return p;

  if (not p) {
    construct(p, x, t);
    return p;
  }

  p.init = x.init;
  if (not p) {
    destroy(p, t);
    return p;
  }
  
  switch (t) {
  case HELLO: p.data.hello = x.data.hello; break;
  case ERROR: p.data.error = x.data.error; break;
  case ECHO_REQ: p.data.echo_req = x.data.echo_req; break;
  case ECHO_RES: p.data.echo_res = x.data.echo_res; break;
  case EXPERIMENTER: p.data.experimenter = x.data.experimenter; break;
  case FEATURE_REQ: p.data.feature_req = x.data.feature_req; break;
  case FEATURE_RES: p.data.feature_res = x.data.feature_res; break;
  case GET_CONFIG_REQ: p.data.get_config_req = x.data.get_config_req; break;
  case GET_CONFIG_RES: p.data.get_config_res = x.data.get_config_res; break;
  case SET_CONFIG: p.data.set_config = x.data.set_config; break;
  case PACKET_IN: p.data.packet_in = x.data.packet_in; break;
  case FLOW_REMOVED: p.data.flow_removed = x.data.flow_removed; break;
  case PORT_STATUS: p.data.port_status = x.data.port_status; break;
  case PACKET_OUT: p.data.packet_out = x.data.packet_out; break;
  case FLOW_MOD: p.data.flow_mod = x.data.flow_mod; break;
  case GROUP_MOD: p.data.group_mod = x.data.group_mod; break;
  case PORT_MOD: p.data.port_mod = x.data.port_mod; break;
  case TABLE_MOD: p.data.table_mod = x.data.table_mod; break;
  case STATS_REQ: p.data.stats_req = x.data.stats_req; break;
  case STATS_RES: p.data.stats_res = x.data.stats_res; break;
  case BARRIER_REQ: p.data.barrier_req = x.data.barrier_req; break;
  case BARRIER_RES: p.data.barrier_res = x.data.barrier_res; break;
  case QUEUE_GET_CONFIG_REQ: p.data.queue_get_config_req = x.data.queue_get_config_req; break;
  case QUEUE_GET_CONFIG_RES: p.data.queue_get_config_res = x.data.queue_get_config_res; break;
  default: variant_error(t);
  }
  return p;
}

void
destroy(Payload& p, Message_type t)
{
  if (not p)
    return;
  switch (t) {
  case HELLO: p.data.hello.~Hello(); break;
  case ERROR: p.data.error.~Error(); break;
  case ECHO_REQ: p.data.echo_req.~Echo_req(); break;
  case ECHO_RES: p.data.echo_res.~Echo_res(); break;
  case EXPERIMENTER: p.data.experimenter.~Experimenter(); break;
  case FEATURE_REQ: p.data.feature_req.~Feature_req(); break;
  case FEATURE_RES: p.data.feature_res.~Feature_res(); break;
  case GET_CONFIG_REQ: p.data.get_config_req.~Get_config_req(); break;
  case GET_CONFIG_RES: p.data.get_config_res.~Get_config_res(); break;
  case SET_CONFIG: p.data.set_config.~Set_config(); break;
  case PACKET_IN: p.data.packet_in.~Packet_in(); break;
  case FLOW_REMOVED: p.data.flow_removed.~Flow_removed(); break;
  case PORT_STATUS: p.data.port_status.~Port_status(); break;
  case PACKET_OUT: p.data.packet_out.~Packet_out(); break;
  case FLOW_MOD: p.data.flow_mod.~Flow_mod(); break;
  case GROUP_MOD: p.data.group_mod.~Group_mod(); break;
  case PORT_MOD: p.data.port_mod.~Port_mod(); break;
  case TABLE_MOD: p.data.table_mod.~Table_mod(); break;
  case STATS_REQ: p.data.stats_req.~Stats_req(); break;
  case STATS_RES: p.data.stats_res.~Stats_res(); break;
  case BARRIER_REQ: p.data.barrier_req.~Barrier_req(); break;
  case BARRIER_RES: p.data.barrier_res.~Barrier_res(); break;
  case QUEUE_GET_CONFIG_REQ:
    p.data.queue_get_config_req.~Queue_get_config_req(); break;
  case QUEUE_GET_CONFIG_RES:
    p.data.queue_get_config_res.~Queue_get_config_res(); break;
  default: return;
  }
}

bool
equal(const Payload& a, const Payload& b, Message_type t1, Message_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case HELLO: return a.data.hello == b.data.hello;
  case ERROR: return a.data.error == b.data.error;
  case ECHO_REQ: return a.data.echo_req == b.data.echo_req;
  case ECHO_RES: return a.data.echo_res == b.data.echo_res;
  case EXPERIMENTER: return a.data.experimenter == b.data.experimenter;
  case FEATURE_REQ: return a.data.feature_req == b.data.feature_req;
  case FEATURE_RES: return a.data.feature_res == b.data.feature_res;
  case GET_CONFIG_REQ: return a.data.get_config_req == b.data.get_config_req;
  case GET_CONFIG_RES: return a.data.get_config_res == b.data.get_config_res;
  case SET_CONFIG: return a.data.set_config == b.data.set_config;
  case PACKET_IN: return a.data.packet_in == b.data.packet_in;
  case FLOW_REMOVED: return a.data.flow_removed == b.data.flow_removed;
  case PORT_STATUS: return a.data.port_status == b.data.port_status;
  case PACKET_OUT: return a.data.packet_out == b.data.packet_out;
  case FLOW_MOD: return a.data.flow_mod == b.data.flow_mod;
  case GROUP_MOD: return a.data.group_mod == b.data.group_mod;
  case PORT_MOD: return a.data.port_mod == b.data.port_mod;
  case TABLE_MOD: return a.data.table_mod == b.data.table_mod;
  case STATS_REQ: return a.data.stats_req == b.data.stats_req;
  case STATS_RES: return a.data.stats_res == b.data.stats_res;
  case BARRIER_REQ: return a.data.barrier_req == b.data.barrier_req;
  case BARRIER_RES: return a.data.barrier_res == b.data.barrier_res;
  case QUEUE_GET_CONFIG_REQ:
    return a.data.queue_get_config_req == b.data.queue_get_config_req;
  case QUEUE_GET_CONFIG_RES:
    return a.data.queue_get_config_res == b.data.queue_get_config_res;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Payload& p, Message_type t)
{
  if (not p)

    return 0;
  switch (t) {
  case HELLO: return bytes(p.data.hello);
  case ERROR: return bytes(p.data.error);
  case ECHO_REQ: return bytes(p.data.echo_req);
  case ECHO_RES: return bytes(p.data.echo_res);
  case EXPERIMENTER: return bytes(p.data.experimenter);
  case FEATURE_REQ: return bytes(p.data.feature_req);
  case FEATURE_RES: return bytes(p.data.feature_res);
  case GET_CONFIG_REQ: return bytes(p.data.get_config_req);
  case GET_CONFIG_RES: return bytes(p.data.get_config_res);
  case SET_CONFIG: return bytes(p.data.set_config);
  case PACKET_IN: return bytes(p.data.packet_in);
  case FLOW_REMOVED: return bytes(p.data.flow_removed);
  case PORT_STATUS: return bytes(p.data.port_status);
  case PACKET_OUT: return bytes(p.data.packet_out);
  case FLOW_MOD: return bytes(p.data.flow_mod);
  case GROUP_MOD: return bytes(p.data.group_mod);
  case PORT_MOD: return bytes(p.data.port_mod);
  case TABLE_MOD: return bytes(p.data.table_mod);
  case STATS_REQ: return bytes(p.data.stats_req);
  case STATS_RES: return bytes(p.data.stats_res);
  case BARRIER_REQ: return bytes(p.data.barrier_req);
  case BARRIER_RES: return bytes(p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ: return bytes(p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES: return bytes(p.data.queue_get_config_res);
  default: variant_error(t);
  }
}

Error_condition
is_valid(const Payload& p, Message_type t)
{
  if (not p)
    return BAD_MESSAGE_INIT;
  switch (t) {
  case HELLO: return is_valid(p.data.hello);
  case ERROR: return is_valid(p.data.error);
  case ECHO_REQ: return is_valid(p.data.echo_req);
  case ECHO_RES: return is_valid(p.data.echo_res);
  case EXPERIMENTER: return is_valid(p.data.experimenter);
  case FEATURE_REQ: return is_valid(p.data.feature_req);
  case FEATURE_RES: return is_valid(p.data.feature_res);
  case GET_CONFIG_REQ: return is_valid(p.data.get_config_req);
  case GET_CONFIG_RES: return is_valid(p.data.get_config_res);
  case SET_CONFIG: return is_valid(p.data.set_config);
  case PACKET_IN: return is_valid(p.data.packet_in);
  case FLOW_REMOVED: return is_valid(p.data.flow_removed);
  case PORT_STATUS: return is_valid(p.data.port_status);
  case PACKET_OUT: return is_valid(p.data.packet_out);
  case FLOW_MOD: return is_valid(p.data.flow_mod);
  case GROUP_MOD: return is_valid(p.data.group_mod);
  case PORT_MOD: return is_valid(p.data.port_mod);
  case TABLE_MOD: return is_valid(p.data.table_mod);
  case STATS_REQ: return is_valid(p.data.stats_req);
  case STATS_RES: return is_valid(p.data.stats_res);
  case BARRIER_REQ: return is_valid(p.data.barrier_req);
  case BARRIER_RES: return is_valid(p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ: return is_valid(p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES: return is_valid(p.data.queue_get_config_res);
  default: variant_error(t);
  }
  return BAD_MESSAGE;
}


Error_condition
to_buffer(Buffer_view& v, const Payload& p, Message_type t)
{
  assert(p);
  switch (t) {
  case HELLO: return to_buffer(v, p.data.hello);
  case ERROR: return to_buffer(v, p.data.error);
  case ECHO_REQ: return to_buffer(v, p.data.echo_req);
  case ECHO_RES: return to_buffer(v, p.data.echo_res);
  case EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  case FEATURE_REQ: return to_buffer(v, p.data.feature_req);
  case FEATURE_RES: return to_buffer(v, p.data.feature_res);
  case GET_CONFIG_REQ: return to_buffer(v, p.data.get_config_req);
  case GET_CONFIG_RES: return to_buffer(v, p.data.get_config_res);
  case SET_CONFIG: return to_buffer(v, p.data.set_config);
  case PACKET_IN: return to_buffer(v, p.data.packet_in);
  case FLOW_REMOVED: return to_buffer(v, p.data.flow_removed);
  case PORT_STATUS: return to_buffer(v, p.data.port_status);
  case PACKET_OUT: return to_buffer(v, p.data.packet_out);
  case FLOW_MOD: return to_buffer(v, p.data.flow_mod);
  case GROUP_MOD: return to_buffer(v, p.data.group_mod);
  case PORT_MOD: return to_buffer(v, p.data.port_mod);
  case TABLE_MOD: return to_buffer(v, p.data.table_mod);
  case STATS_REQ: return to_buffer(v, p.data.stats_req);
  case STATS_RES: return to_buffer(v, p.data.stats_res);
  case BARRIER_REQ: return to_buffer(v, p.data.barrier_req);
  case BARRIER_RES: return to_buffer(v, p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ:
    return to_buffer(v, p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES:
    return to_buffer(v, p.data.queue_get_config_res);
  default: variant_error(t);
  }
  return BAD_MESSAGE;
}

Error_condition
from_buffer(Buffer_view& v, Payload& p, Message_type t)
{
  assert(p);
  switch (t) {
  case HELLO: return from_buffer(v, p.data.hello);
  case ERROR: return from_buffer(v, p.data.error);
  case ECHO_REQ: return from_buffer(v, p.data.echo_req);
  case ECHO_RES: return from_buffer(v, p.data.echo_res);
  case EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  case FEATURE_REQ: return from_buffer(v, p.data.feature_req);
  case FEATURE_RES: return from_buffer(v, p.data.feature_res);
  case GET_CONFIG_REQ: return from_buffer(v, p.data.get_config_req);
  case GET_CONFIG_RES: return from_buffer(v, p.data.get_config_res);
  case SET_CONFIG: return from_buffer(v, p.data.set_config);
  case PACKET_IN: return from_buffer(v, p.data.packet_in);
  case FLOW_REMOVED: return from_buffer(v, p.data.flow_removed);
  case PORT_STATUS: return from_buffer(v, p.data.port_status);
  case PACKET_OUT: return from_buffer(v, p.data.packet_out);
  case FLOW_MOD: return from_buffer(v, p.data.flow_mod);
  case GROUP_MOD: return from_buffer(v, p.data.group_mod);
  case PORT_MOD: return from_buffer(v, p.data.port_mod);
  case TABLE_MOD: return from_buffer(v, p.data.table_mod);
  case STATS_REQ: return from_buffer(v, p.data.stats_req);
  case STATS_RES: return from_buffer(v, p.data.stats_res);
  case BARRIER_REQ: return from_buffer(v, p.data.barrier_req);
  case BARRIER_RES: return from_buffer(v, p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ:
    return from_buffer(v, p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES:
    return from_buffer(v, p.data.queue_get_config_res);
  default: variant_error(t);
  }
  return BAD_MESSAGE;
}

std::string
to_string(const Payload& p, Formatter& fmt, Message_type t)
{
  assert(p);
  switch (t) {
  case HELLO: return to_string(p.data.hello, fmt);
  case ERROR: return to_string(p.data.error, fmt);
  case ECHO_REQ: return to_string(p.data.echo_req, fmt);
  case ECHO_RES: return to_string(p.data.echo_res, fmt);
  case EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  case FEATURE_REQ: return to_string(p.data.feature_req, fmt);
  case FEATURE_RES: return to_string(p.data.feature_res, fmt);
  case GET_CONFIG_REQ: return to_string(p.data.get_config_req, fmt);
  case GET_CONFIG_RES: return to_string(p.data.get_config_res, fmt);
  case SET_CONFIG: return to_string(p.data.set_config, fmt);
  case PACKET_IN: return to_string(p.data.packet_in, fmt);
  case FLOW_REMOVED: return to_string(p.data.flow_removed, fmt);
  case PORT_STATUS: return to_string(p.data.port_status, fmt);
  case PACKET_OUT: return to_string(p.data.packet_out, fmt);
  case FLOW_MOD: return to_string(p.data.flow_mod, fmt);
  case GROUP_MOD: return to_string(p.data.group_mod, fmt);
  case PORT_MOD: return to_string(p.data.port_mod, fmt);
  case TABLE_MOD: return to_string(p.data.table_mod, fmt);
  case STATS_REQ: return to_string(p.data.stats_req, fmt);
  case STATS_RES: return to_string(p.data.stats_res, fmt);
  case BARRIER_REQ: return to_string(p.data.barrier_req, fmt);
  case BARRIER_RES: return to_string(p.data.barrier_res, fmt);
  case QUEUE_GET_CONFIG_REQ:
    return to_string(p.data.queue_get_config_req, fmt);
  case QUEUE_GET_CONFIG_RES:
    return to_string(p.data.queue_get_config_res, fmt);
  default: variant_error(t);
  }
}

// -------------------------------------------------------------------------- //
// Header

Error_condition
to_buffer(Buffer_view& v, const Header& h)
{
  to_buffer(v, h.version);
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  to_buffer(v, h.xid);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Header& h)
{
  from_buffer(v, h.version);
  from_buffer(v, h.type);
  from_buffer(v, h.length);
  from_buffer(v, h.xid);
  return SUCCESS;
}

std::string
to_string(const Header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Hdr");

  nvp_to_string(ss, f, "Version", to_string(h.version), int(h.version));
  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);
  nvp_to_string(ss, f, "X-ID", h.xid);

  close_block(ss, f, "Hdr");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Message

Error_condition
to_buffer(Buffer_view& v, const Message& m)
{
  if (not available(v, bytes(m.header)))
    return AVAILABLE_HEADER;
  to_buffer(v, m.header);
  return to_buffer(v, m.payload, m.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Message& m)
{
  if (not available(v, bytes(m.header)))
    return AVAILABLE_HEADER;
  from_buffer(v, m.header);
  
  if (m.header.length < bytes(m.header))
    return BAD_MESSAGE_LENGTH;
  
  if (Error_decl err = is_valid(m.header.type))
    return err;
  
  Payload p;
  construct(p, m.header.type);
  assign(m.payload, std::move(p), m.header.type);

  std::size_t n = m.header.length - bytes(m.header);
  if (not available(v, n))
    return AVAILABLE_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, m.payload, m.header.type))
    return err;
  
  if (not update(v, c))
    return EXCESS_PAYLOAD;

  return SUCCESS;
}

std::string
to_string(const Message& m, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Msg");

  ss << to_string(m.header, f);
  if (is_valid(m.header))
    ss << to_string(m.payload, f, m.header.type);

  close_block(ss, f, "Msg");
  return ss.str();
}

} // namespace v1_1
} // namesapce ofp
} // namespace flog
