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
namespace v1_0 {

std::string
to_string(Version_type t) {
  if (t == 1) 
    return "1.0";
  else
    return "Unknown";
}

std::string 
to_string(Message_type t) {
  switch(t) {
  case HELLO: return "Hello";
  case ERROR: return "Error";
  case ECHO_REQ: return "EchoReq";
  case ECHO_RES: return "EchoRes";
  case VENDOR: return "Vendor";
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
  case PORT_MOD: return "PortMod";
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
to_buffer(Buffer_view& v, const Hello& h) {
  if (not available(v, bytes(h)))
    return AVAILABLE_HELLO;
  to_buffer(v, h.data);
  return SUCCESS;
}

Error_condition 
from_buffer(Buffer_view& v, Hello& h) {
  if (not available(v, bytes(h)))
    return AVAILABLE_HELLO;
  from_buffer(v, h.data);
  return SUCCESS;
}

std::string 
to_string(const Hello& h, Formatter& f) {
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
to_string(Error::Type t)
{
  switch(t) {
  case Error::HELLO_FAILED: return "Hello Failed";
  case Error::BAD_REQUEST: return "Bad Request";
  case Error::BAD_ACTION: return "Bad Action";
  case Error::FLOW_MOD_FAILED: return "FlowMod Failed";
  case Error::PORT_MOD_FAILED: return "PortMod Failed";
  case Error::QUEUE_OP_FAILED: return "Queue Op Failed";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Hello_failed c)
{
  switch(c) {
  case Error::HF_INCOMPATIBLE: return "Incompatible";
  case Error::HF_EPERM: return "EPerm";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Bad_request c)
{
  switch(c) {
  case Error::BR_BAD_VERSION: return "Bad Version";
  case Error::BR_BAD_TYPE: return "Bad Type";
  case Error::BR_BAD_STAT: return "Bad Stat";
  case Error::BR_BAD_VENDOR: return "Bad Vendor";
  case Error::BR_BAD_SUBTYPE: return "Bad Subtype";
  case Error::BR_EPERM: return "EPerm";
  case Error::BR_BAD_LEN: return "Bad Length";
  case Error::BR_BUFFER_EMPTY: return "Buffer Empty";
  case Error::BR_BUFFER_UNKNOWN: return "Buffer Unknown";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Bad_action c)
{
  switch(c) {
  case Error::BA_BAD_TYPE: return "Bad Type";
  case Error::BA_BAD_LEN: return "Bad Length";
  case Error::BA_BAD_VENDOR: return "Bad Vendor";
  case Error::BA_BAD_VENDOR_TYPE: return "Bad Vendor Type";
  case Error::BA_BAD_OUT_PORT: return "Bad Output Port";
  case Error::BA_BAD_ARGUMENT: return "Bad Argument";
  case Error::BA_EPERM: return "EPerm";
  case Error::BA_TOO_MANY: return "Too Many";
  case Error::BA_BAD_QUEUE: return "Bad Queue";
  default: return "Unknown"; 
  }
}

std::string
to_string(Error::Flow_mod_failed c)
{
  switch(c) {
  case Error::FMF_ALL_TABLES_FULL: return "All Tables Full";
  case Error::FMF_OVERLAP: return "Overlap";
  case Error::FMF_EPERM: return "EPerm";
  case Error::FMF_BAD_EMERG_TIMEOUT: return "Bad Emerg Timeout";
  case Error::FMF_BAD_COMMAND: return "Bad Command";
  case Error::FMF_UNSUPPORTED: return "Unsupported";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Port_mod_failed c)
{
  switch(c) {
  case Error::PMF_BAD_PORT: return "Bad Port";
  case Error::PMF_BAD_HW_ADDR: return "Bad HW Addr";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Queue_op_failed c)
{
  switch(c) {
  case Error::QOF_BAD_PORT: return "Bad Port";
  case Error::QOF_BAD_QUEUE: return "Bad Queue";
  case Error::QOF_EPERM: return "EPerm";
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
  case Error::FLOW_MOD_FAILED: return to_string(c.fmf);
  case Error::PORT_MOD_FAILED: return to_string(c.pmf);
  case Error::QUEUE_OP_FAILED: return to_string(c.qof);
  default: return "Unknown";
  }
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

// -------------------------------------------------------------------------- //
// Echo req

std::string
to_string(const Echo_req& er, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "EchoReq");
  nvp_to_string(ss, f, "Data bytes", bytes(er.data));
  close_block(ss, f, "EchoReq");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Echo req

std::string
to_string(const Echo_res& er, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "EchoRes");
  nvp_to_string(ss, f, "Data bytes", bytes(er.data));
  close_block(ss, f, "EchoRes");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Vendor

std::string 
to_string(const Vendor& m, Formatter& f) 
{
  std::stringstream ss;
  open_block(ss, f, "Vendor");
  nvp_to_string(ss, f, "Vendor ID", m.vendor_id);
  nvp_to_string(ss, f, "Data bytes", bytes(m.data));
  close_block(ss, f, "Vendor");
  return ss.str();
}
  
Error_condition
to_buffer(Buffer_view& v, const Vendor& m)
{
  if (not available(v, bytes(m)))
    return AVAILABLE_VENDOR;
  to_buffer(v, m.vendor_id);
  to_buffer(v, m.data);
  return SUCCESS;
}
  
Error_condition
from_buffer(Buffer_view& v, Vendor& m) 
{
  if (not available(v, bytes(m)))
    return AVAILABLE_VENDOR;
  from_buffer(v, m.vendor_id);
  from_buffer(v, m.data);
  return SUCCESS;
}


// -------------------------------------------------------------------------- //
// Match

std::string 
to_string(const Match& m, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Match");

  nvp_to_string(ss, f, "Port", 
                cond_to_string(wildcard_in_port(m.wildcards), "all", m.in_port),
                m.in_port);

  nvp_to_string(ss, f, "Src MAC", 
                cond_to_string(wildcard_dl_src(m.wildcards),
                               to_string(ethernet::broadcast),
                               ethernet::to_string(m.dl_src)),
                to_string(m.dl_src));
  
  nvp_to_string(ss, f, "Dst MAC", 
                cond_to_string(wildcard_dl_dst(m.wildcards), 
                               to_string(ethernet::broadcast), 
                               to_string(m.dl_dst)),
                to_string(m.dl_dst));

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

  std::stringstream tsrc;
  tsrc << to_string(m.nw_src) << " / " <<  wildcard_nw_src(m.wildcards);
  nvp_to_string(ss, f, "IPv4 Src", tsrc.str());
  
  std::stringstream tdst;
  tdst << to_string(m.nw_dst) << " / " <<  wildcard_nw_dst(m.wildcards);
  nvp_to_string(ss, f, "IPv4 Dst", tdst.str());

  nvp_to_string(ss, f, "L4 Src",
                cond_to_string(wildcard_tp_src(m.wildcards), "all", m.tp_src),
                m.tp_src);
  
  nvp_to_string(ss, f, "L4 Dst",
                cond_to_string(wildcard_tp_dst(m.wildcards), "all", m.tp_dst),
                m.tp_dst);
  
  close_block(ss, f, "Match");
  return ss.str(); 
} 

Error_condition 
to_buffer(Buffer_view& v, const Match& m) {
  to_buffer(v, m.wildcards);
  to_buffer(v, m.in_port);
  to_buffer(v, m.dl_src);
  to_buffer(v, m.dl_dst);
  to_buffer(v, m.dl_vlan);
  to_buffer(v, m.dl_pcp);
  pad(v, 1);
  to_buffer(v, m.dl_type);
  to_buffer(v, m.nw_tos);
  to_buffer(v, m.nw_proto);
  pad(v, 2);
  to_buffer(v, m.nw_src);
  to_buffer(v, m.nw_dst);
  to_buffer(v, m.tp_src);
  to_buffer(v, m.tp_dst);
  return SUCCESS;
}

Error_condition 
from_buffer(Buffer_view& v, Match& m) {
  from_buffer(v, m.wildcards);
  from_buffer(v, m.in_port);
  from_buffer(v, m.dl_src);
  from_buffer(v, m.dl_dst);
  from_buffer(v, m.dl_vlan);
  from_buffer(v, m.dl_pcp);
  pad(v, 1);
  from_buffer(v, m.dl_type);
  from_buffer(v, m.nw_tos);
  from_buffer(v, m.nw_proto);
  pad(v, 2);
  from_buffer(v, m.nw_src);
  from_buffer(v, m.nw_dst);
  from_buffer(v, m.tp_src);
  from_buffer(v, m.tp_dst);
  return SUCCESS;
}


// -------------------------------------------------------------------------- //
// Action type

std::string
to_string(Action_type t)
{
  switch(t) {
  case ACTION_OUTPUT: return "OUTPUT";
  case ACTION_SET_VLAN_VID: return "SET_VLAN_ID";
  case ACTION_SET_VLAN_PCP: return "SET_VLAN_PCP";
  case ACTION_STRIP_VLAN: return "STRIP_VLAN";
  case ACTION_SET_DL_SRC: return "SET_DL_SRC";
  case ACTION_SET_DL_DST: return "SET_DL_DST";
  case ACTION_SET_NW_SRC: return "SET_NW_SRC";
  case ACTION_SET_NW_DST: return "SET_NW_DST";
  case ACTION_SET_NW_TOS: return "SET_NW_TOS";
  case ACTION_SET_TP_SRC: return "SET_TP_SRC";
  case ACTION_SET_TP_DST: return "SET_TP_DST";
  case ACTION_ENQUEUE: return "ENQUEUE";
  case ACTION_VENDOR: return "VENDOR";
  default: return "UNKNOWN";
  }
}

// -------------------------------------------------------------------------- //
// Action_output

Error_condition
to_buffer(Buffer_view& v, const Action_output& a) {
  if(not available(v, bytes(a)))
    return AVAILABLE_ACTION_OUTPUT;
  to_buffer(v, a.port);
  to_buffer(v, a.max_len);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_output& a) {
  if(not available(v, bytes(a)))
    return AVAILABLE_ACTION_OUTPUT;
  from_buffer(v, a.port);
  from_buffer(v, a.max_len);
  return SUCCESS;
}

std::string 
to_string(const Action_output& ao, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Action Output");
  nvp_to_string(ss, f, "Port", ao.port);
  nvp_to_string(ss, f, "Max Len", ao.max_len);
  close_block(ss, f, "Action Output");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Action_set_vlan_vid

std::string 
to_string(const Action_set_vlan_vid& a, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action VLAN VID");
  nvp_to_string(ss, f, "VLAN ID", a.vlan_vid);
  close_block(ss, f, "Action VLAN VID");
  return ss.str();
}

Error_condition 
to_buffer(Buffer_view& v, const Action_set_vlan_vid& a) {
  if (not available(v, bytes(a)))
    return AVAILABLE_ACTION_SET_VLAN_VID;
  to_buffer(v, a.vlan_vid);
  pad(v, 2);
  return SUCCESS;
}

Error_condition 
from_buffer(Buffer_view& v, Action_set_vlan_vid& a) {
  if (not available(v, bytes(a)))
    return AVAILABLE_ACTION_SET_VLAN_VID;
  from_buffer(v, a.vlan_vid);
  pad(v, 2);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action_set_vlan_pcp

Error_condition 
to_buffer(Buffer_view& v, const Action_set_vlan_pcp& avp) {
  if (not available(v, bytes(avp)))
    return AVAILABLE_ACTION_SET_VLAN_PCP;
  to_buffer(v, avp.value);
  pad(v, 3);
  return SUCCESS;
}

Error_condition 
from_buffer(Buffer_view& v, Action_set_vlan_pcp& avp) {
  if (not available(v, bytes(avp)))
    return AVAILABLE_ACTION_SET_VLAN_PCP;
  from_buffer(v, avp.value);
  pad(v, 3);
  return SUCCESS;
}

std::string 
to_string(const Action_set_vlan_pcp& avp, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Action VLAN PCP");
  nvp_to_string(ss, f, "VLAN PCP", avp.value);
  close_block(ss, f, "Action VLAN PCP");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action_strip_vlan

Error_condition
to_buffer(Buffer_view& v, const Action_strip_vlan& a) {
  if (not available(v, bytes(a)))
    return AVAILABLE_ACTION_STRIP_VLAN;
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_strip_vlan& a) {
  if (not available(v, bytes(a)))
    return AVAILABLE_ACTION_STRIP_VLAN;
  pad(v, 4);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action_set_nw_tos

std::string 
to_string(const Action_set_nw_tos& a, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Action NW ToS");
  nvp_to_string(ss, f, "IPv4 ToS", int(a.value));
  close_block(ss, f, "Action NW ToS");
  return ss.str();
}

Error_condition
to_buffer(Buffer_view& v, const Action_set_nw_tos& a) {
  if (not available(v, bytes(a)))
    return AVAILABLE_ACTION_SET_NW_TOS;
  to_buffer(v, a.value);
  pad(v, 3);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_nw_tos& a) {
  if(not available(v, bytes(a)))
    return AVAILABLE_ACTION_SET_NW_TOS;
  from_buffer(v, a.value);
  pad(v, 3);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action_enqueue

std::string 
to_string(const Action_enqueue& a, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Action Enqueue");
  nvp_to_string(ss, f, "Port", a.port);
  nvp_to_string(ss, f, "Queue ID", a.queue_id);
  close_block(ss, f, "Action Enqueue");
  return ss.str();
}

Error_condition
to_buffer(Buffer_view& v, const Action_enqueue& a) {
  if (not available(v, bytes(a)))
    return AVAILABLE_ACTION_ENQUEUE;
  to_buffer(v, a.port);
  pad(v, 6);
  to_buffer(v, a.queue_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_enqueue& a)
{
  if(not available(v, bytes(a)))
    return AVAILABLE_ACTION_ENQUEUE;
  from_buffer(v, a.port);
  pad(v, 6);
  from_buffer(v, a.queue_id);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action_vendor

std::string 
to_string(const Action_vendor& a, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Action Vendor");
  nvp_to_string(ss, f, "Vendor", a.vendor);
  close_block(ss, f, "Action Vendor");
  return ss.str();
}

Error_condition 
to_buffer(Buffer_view& v, const Action_vendor& a) {
  if (not available(v, bytes(a)))
    return AVAILABLE_ACTION_VENDOR;
  to_buffer(v, a.vendor);
  return SUCCESS;
}

Error_condition 
from_buffer(Buffer_view& v, Action_vendor& a) {
  if(not available(v, bytes(a)))
    return AVAILABLE_ACTION_VENDOR;
  from_buffer(v, a.vendor);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action Payload

void
construct(Action_payload& p, Action_type t) {
  p.init = true;
  switch (t) {
  case ACTION_OUTPUT: new (&p.data.output) Action_output(); break;
  case ACTION_SET_VLAN_VID: new (&p.data.vlan_vid) Action_set_vlan_vid(); break;
  case ACTION_SET_VLAN_PCP: new (&p.data.vlan_pcp) Action_set_vlan_pcp(); break;
  case ACTION_STRIP_VLAN: new (&p.data.strip_vlan) Action_strip_vlan(); break;
  case ACTION_SET_DL_SRC: new (&p.data.dl_src) Action_set_dl_src(); break;
  case ACTION_SET_DL_DST: new (&p.data.dl_dst) Action_set_dl_dst(); break;
  case ACTION_SET_NW_SRC: new (&p.data.nw_src) Action_set_nw_src(); break;
  case ACTION_SET_NW_DST: new (&p.data.nw_dst) Action_set_nw_dst(); break;
  case ACTION_SET_NW_TOS: new (&p.data.nw_tos) Action_set_nw_tos(); break;
  case ACTION_SET_TP_SRC: new (&p.data.tp_src) Action_set_tp_src(); break;
  case ACTION_SET_TP_DST: new (&p.data.tp_dst) Action_set_tp_dst(); break;
  case ACTION_ENQUEUE: new (&p.data.enqueue) Action_enqueue(); break;
  case ACTION_VENDOR: new (&p.data.vendor) Action_vendor(); break;
  default: variant_error(t);
  }
}
void 
construct(Action_payload& p, const Action_payload& x, Action_type t) {
  p.init = x.init;
  if (not p)
    return;
  switch (t) {
  case ACTION_OUTPUT: 
    new (&p.data.output) Action_output(x.data.output); break;
  case ACTION_SET_VLAN_VID: 
    new (&p.data.vlan_vid) Action_set_vlan_vid(x.data.vlan_vid); break;
  case ACTION_SET_VLAN_PCP:
    new (&p.data.vlan_pcp) Action_set_vlan_pcp(x.data.vlan_pcp); break;
  case ACTION_STRIP_VLAN:
    new (&p.data.strip_vlan) Action_strip_vlan(x.data.strip_vlan); break;
  case ACTION_SET_DL_SRC:
    new (&p.data.dl_src) Action_set_dl_src(x.data.dl_src); break;
  case ACTION_SET_DL_DST:
    new (&p.data.dl_dst) Action_set_dl_dst(x.data.dl_dst); break;
  case ACTION_SET_NW_SRC:
    new (&p.data.nw_src) Action_set_nw_src(x.data.nw_src); break;
  case ACTION_SET_NW_DST:
    new (&p.data.nw_dst) Action_set_nw_dst(x.data.nw_dst); break;
  case ACTION_SET_NW_TOS: 
    new (&p.data.nw_tos) Action_set_nw_tos(x.data.nw_tos); break;
  case ACTION_SET_TP_SRC: 
    new (&p.data.tp_src) Action_set_tp_src(x.data.tp_src); break;
  case ACTION_SET_TP_DST:
    new (&p.data.tp_dst) Action_set_tp_dst(x.data.tp_dst); break;
  case ACTION_ENQUEUE: 
    new (&p.data.enqueue) Action_enqueue(x.data.enqueue); break;
  case ACTION_VENDOR: 
    new (&p.data.vendor) Action_vendor(x.data.vendor); break;
  default: variant_error(t);
  }
}

Action_payload& 
assign(Action_payload& a, const Action_payload& b, Action_type t) {
  if (&a == &b)
    return a;
  
  a.init = b.init;
  if (not a)
    return a;
  
  switch (t) {
  case ACTION_OUTPUT: a.data.output = b.data.output; break;
  case ACTION_SET_VLAN_VID: a.data.vlan_vid = b.data.vlan_vid; break;
  case ACTION_SET_VLAN_PCP: a.data.vlan_pcp = b.data.vlan_pcp; break;
  case ACTION_STRIP_VLAN: a.data.strip_vlan = b.data.strip_vlan; break;
  case ACTION_SET_DL_SRC: a.data.dl_src = b.data.dl_src; break;
  case ACTION_SET_DL_DST: a.data.dl_dst = b.data.dl_dst; break;
  case ACTION_SET_NW_SRC: a.data.nw_src = b.data.nw_src; break;
  case ACTION_SET_NW_DST: a.data.nw_dst = b.data.nw_dst; break;
  case ACTION_SET_NW_TOS: a.data.nw_tos = b.data.nw_tos; break;
  case ACTION_SET_TP_SRC: a.data.tp_src = b.data.tp_src; break;
  case ACTION_SET_TP_DST: a.data.tp_dst = b.data.tp_dst; break;
  case ACTION_ENQUEUE: a.data.enqueue = b.data.enqueue; break;
  case ACTION_VENDOR: a.data.vendor = b.data.vendor; break;
  default: variant_error(t);
  }
  return a;
}

bool 
equal(const Action_payload& a, const Action_payload& b, Action_type t1, Action_type t2) {
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case ACTION_OUTPUT: return a.data.output == b.data.output;
  case ACTION_SET_VLAN_VID: return a.data.vlan_vid == b.data.vlan_vid;
  case ACTION_SET_VLAN_PCP: return a.data.vlan_pcp == b.data.vlan_pcp;
  case ACTION_STRIP_VLAN: return a.data.strip_vlan == b.data.strip_vlan;
  case ACTION_SET_DL_SRC: return a.data.dl_src == b.data.dl_src;
  case ACTION_SET_DL_DST: return a.data.dl_dst == b.data.dl_dst;
  case ACTION_SET_NW_SRC: return a.data.nw_src == b.data.nw_src;
  case ACTION_SET_NW_DST: return a.data.nw_dst == b.data.nw_dst;
  case ACTION_SET_NW_TOS: return a.data.nw_tos == b.data.nw_tos;
  case ACTION_SET_TP_SRC: return a.data.tp_src == b.data.tp_src;
  case ACTION_SET_TP_DST: return a.data.tp_dst == b.data.tp_dst;
  case ACTION_ENQUEUE: return a.data.enqueue == b.data.enqueue;
  case ACTION_VENDOR: return a.data.vendor == b.data.vendor;
  default: variant_error(t1);
  }
  return false;
}

std::size_t 
bytes(const Action_payload& p, Action_type t) {
  if (not p)
    return 0;
  switch (t) {
  case ACTION_OUTPUT: return bytes(p.data.output);
  case ACTION_SET_VLAN_VID: return bytes(p.data.vlan_vid);
  case ACTION_SET_VLAN_PCP: return bytes(p.data.vlan_pcp);
  case ACTION_STRIP_VLAN: return bytes(p.data.strip_vlan);
  case ACTION_SET_DL_SRC: return bytes(p.data.dl_src);
  case ACTION_SET_DL_DST: return bytes(p.data.dl_dst);
  case ACTION_SET_NW_SRC: return bytes(p.data.nw_src);
  case ACTION_SET_NW_DST: return bytes(p.data.nw_dst);
  case ACTION_SET_NW_TOS: return bytes(p.data.nw_tos);
  case ACTION_SET_TP_SRC: return bytes(p.data.tp_src);
  case ACTION_SET_TP_DST: return bytes(p.data.tp_dst);
  case ACTION_ENQUEUE: return bytes(p.data.enqueue);
  case ACTION_VENDOR: return bytes(p.data.vendor);
  default: variant_error(t);
  }
  return 0;
}

Error_condition 
is_valid(const Action_payload& p, Action_type t) {
  if (not p)
    return BAD_ACTION_INIT;
  switch (t) {
  case ACTION_OUTPUT: return is_valid(p.data.output);
  case ACTION_SET_VLAN_VID: return is_valid(p.data.vlan_vid);
  case ACTION_SET_VLAN_PCP: return is_valid(p.data.vlan_pcp);
  case ACTION_STRIP_VLAN: return is_valid(p.data.strip_vlan);
  case ACTION_SET_DL_SRC: return is_valid(p.data.dl_src);
  case ACTION_SET_DL_DST: return is_valid(p.data.dl_dst);
  case ACTION_SET_NW_SRC: return is_valid(p.data.nw_src);
  case ACTION_SET_NW_DST: return is_valid(p.data.nw_dst);
  case ACTION_SET_NW_TOS: return is_valid(p.data.nw_tos);
  case ACTION_SET_TP_SRC: return is_valid(p.data.tp_src);
  case ACTION_SET_TP_DST: return is_valid(p.data.tp_dst);
  case ACTION_ENQUEUE: return is_valid(p.data.enqueue);
  case ACTION_VENDOR: return is_valid(p.data.vendor);
  default: variant_error(t);
  }
  return BAD_ACTION;
}

Error_condition
to_buffer(Buffer_view& v, const Action_payload& p, Action_type t) {switch (t) {
  case ACTION_OUTPUT: return to_buffer(v, p.data.output);
  case ACTION_SET_VLAN_VID: return to_buffer(v, p.data.vlan_vid);
  case ACTION_SET_VLAN_PCP: return to_buffer(v, p.data.vlan_pcp);
  case ACTION_STRIP_VLAN: return to_buffer(v, p.data.strip_vlan);
  case ACTION_SET_DL_SRC: return to_buffer(v, p.data.dl_src);
  case ACTION_SET_DL_DST: return to_buffer(v, p.data.dl_dst);
  case ACTION_SET_NW_SRC: return to_buffer(v, p.data.nw_src);
  case ACTION_SET_NW_DST: return to_buffer(v, p.data.nw_dst);
  case ACTION_SET_NW_TOS: return to_buffer(v, p.data.nw_tos);
  case ACTION_SET_TP_SRC: return to_buffer(v, p.data.tp_src);
  case ACTION_SET_TP_DST: return to_buffer(v, p.data.tp_dst);
  case ACTION_ENQUEUE: return to_buffer(v, p.data.enqueue);
  case ACTION_VENDOR: return to_buffer(v, p.data.vendor);
  default: variant_error(t);
  }
  return BAD_ACTION;
}

Error_condition
from_buffer(Buffer_view& v, Action_payload& p, Action_type t) {
  switch (t) {
  case ACTION_OUTPUT: return from_buffer(v, p.data.output);
  case ACTION_SET_VLAN_VID: return from_buffer(v, p.data.vlan_vid);
  case ACTION_SET_VLAN_PCP: return from_buffer(v, p.data.vlan_pcp);
  case ACTION_STRIP_VLAN: return from_buffer(v, p.data.strip_vlan);
  case ACTION_SET_DL_SRC: return from_buffer(v, p.data.dl_src);
  case ACTION_SET_DL_DST: return from_buffer(v, p.data.dl_dst);
  case ACTION_SET_NW_SRC: return from_buffer(v, p.data.nw_src);
  case ACTION_SET_NW_DST: return from_buffer(v, p.data.nw_dst);
  case ACTION_SET_NW_TOS: return from_buffer(v, p.data.nw_tos);
  case ACTION_SET_TP_SRC: return from_buffer(v, p.data.tp_src);
  case ACTION_SET_TP_DST: return from_buffer(v, p.data.tp_dst);
  case ACTION_ENQUEUE: return from_buffer(v, p.data.enqueue);
  case ACTION_VENDOR: return from_buffer(v, p.data.vendor);
  default: variant_error(t);
  }
  return BAD_ACTION;
}

std::string
to_string(const Action_payload& p, Formatter& fmt, Action_type t) {
  assert(p);
  switch (t) {
  case ACTION_OUTPUT: return to_string(p.data.output, fmt);
  case ACTION_SET_VLAN_VID: return to_string(p.data.vlan_vid, fmt);
  case ACTION_SET_VLAN_PCP: return to_string(p.data.vlan_pcp, fmt);
  case ACTION_STRIP_VLAN: return to_string(p.data.strip_vlan, fmt);
  case ACTION_SET_DL_SRC: return to_string(p.data.dl_src, fmt);
  case ACTION_SET_DL_DST: return to_string(p.data.dl_dst, fmt);
  case ACTION_SET_NW_SRC: return to_string(p.data.nw_src, fmt);
  case ACTION_SET_NW_DST: return to_string(p.data.nw_dst, fmt);
  case ACTION_SET_NW_TOS: return to_string(p.data.nw_tos, fmt);
  case ACTION_SET_TP_SRC: return to_string(p.data.tp_src, fmt);
  case ACTION_SET_TP_DST: return to_string(p.data.tp_dst, fmt);
  case ACTION_ENQUEUE: return to_string(p.data.enqueue, fmt);
  case ACTION_VENDOR: return to_string(p.data.vendor, fmt);
  default: variant_error(t)
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Action header

Error_condition
to_buffer(Buffer_view& v, const Action_header& h) {
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_header& h) {
  from_buffer(v, h.type);
  from_buffer(v, h.length);
  return SUCCESS;
}

std::string
to_string(const Action_header& h, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Hdr");
  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);
  close_block(ss, f, "Hdr");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action

Error_condition 
to_buffer(Buffer_view& v, const Action& a) {  
  if (not available(v, bytes(a.header)))
    return AVAILABLE_ACTION_HEADER;
  to_buffer(v, a.header);
  
  // TODO: Do w need to check this? I don't think so.
  if (Error_decl err = is_valid(a.header))
    return err;

  // TODO: Constrain views for this also?
  return to_buffer(v, a.payload, a.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Action& a) {
  // Check the availability and read the header,
  if (not available(v, bytes(a.header)))
    return AVAILABLE_ACTION_HEADER;
  from_buffer(v, a.header);

  // Check that the header length is sane.
  if (a.header.length < bytes(a.header))
    return BAD_ACTION_LENGTH;

  // Validate the header and initialize the payload
  if (Error_decl err = is_valid(a.header.type))
    return err;

  // a.payload = Action::Payload() with a.header.type 
  Action::Payload p;
  construct(p, a.header.type);
  assign(a.payload, std::move(p), a.header.type);

  // Ensure that we can constrain the view.
  std::size_t n = a.header.length - bytes(a.header);
  if (remaining(v) < n)
    return AVAILABLE_ACTION_PAYLOAD;

  // Try reading the payload, updating the view on success.
  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, a.payload, a.header.type))
    return err;
  
  // Check that we didn't underflow buffer.
  if (not update(v, c))
    return EXCESS_ACTION;

  return SUCCESS;
}

std::string
to_string(const Action& a, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Action");
  ss << to_string(a.header, f);
  if (is_valid(a.header))
    ss << to_string(a.payload, f, a.header.type);
  close_block(ss, f, "Action");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Port

Error_condition 
to_buffer(Buffer_view& v, const Port& p) {
  if (not available(v, bytes(p)))
    return AVAILABLE_PORT;
  to_buffer(v, p.port_id);
  to_buffer(v, p.hw_addr);
  to_buffer(v, p.name);
  to_buffer(v, p.config);
  to_buffer(v, p.state);
  to_buffer(v, p.current);
  to_buffer(v, p.advertised);
  to_buffer(v, p.supported);
  to_buffer(v, p.peer);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Port& p) {
  if (not available(v, bytes(p)))
    return AVAILABLE_PORT;
  from_buffer(v, p.port_id);
  from_buffer(v, p.hw_addr);
  from_buffer(v, p.name);
  from_buffer(v, p.config);
  from_buffer(v, p.state);
  from_buffer(v, p.current);
  from_buffer(v, p.advertised);
  from_buffer(v, p.supported);
  from_buffer(v, p.peer);
  return SUCCESS;
}

std::string
to_string(const Port& p, Formatter& f) {
  std::stringstream ss;
  ss << std::string(20,'=') << "Port" << std::string(20,'=') << std::endl;

  ss << "Port: " << to_string(p.port_id) << '\n';
  ss << "Ethernet Addr: " << to_string(p.hw_addr) << std::endl;
  ss << "Name: " << p.name.str() << std::endl ;

  ss << "Port Status: ";

  if (port_config_port_down(p.config))
    ss << "down ";
  else
    ss << "up ";
  
  if (port_config_no_stp(p.config))
    ss << "down ";
  else
    ss << "up ";

  ss << std::endl;

  ss << std::string(40,'=') << std::endl;
  return ss.str();
}

std::string
to_string(Port::Id id) {
  switch(id) {
  case Port::MAX: return "Max";
  case Port::IN_PORT: return "Input Port";
  case Port::TABLE: return "Table";
  case Port::NORMAL: return "Normal";
  case Port::FLOOD: return "Flood";
  case Port::ALL: return "All";
  case Port::CONTROLLER: return "Controller";
  case Port::LOCAL: return "Local";
  case Port::NONE: return "None";
  default: return "Unknown";
  }
}

std::string
to_string(Port::Config c) {
  switch(c) {
  case Port::PORT_DOWN: return "Port Down";
  case Port::NO_STP: return "No STP";
  case Port::NO_RECV: return "No Recv";
  case Port::NO_RECV_STP: return "No Recv STP";
  case Port::NO_FLOOD: return "No Flood";
  case Port::NO_FWD: return "No Fwd";
  case Port::NO_PACKET_IN: return "No PacketIn";
  default: return "Unknown";
  }
}

std::string
to_string(Port::State s) {
  switch(s) {
  case Port::STP_LISTEN: return "STP Listen";
  case Port::LINK_DOWN: return "Link Down";
  case Port::STP_LEARN: return "STP Learn";
  case Port::STP_FORWARD: return "STP Forward";
  case Port::STP_BLOCK: return "STP Block";
  case Port::STP_MASK: return "STP Mask";
  default: return "Unknown";
  }
}


std::string
to_string(Port::Features f) {
  switch(f) {
  case Port::TEN_MB_HD: return "10MB HD"; 
  case Port::TEN_MB_FD: return "10MB FD"; 
  case Port::HUNDRED_MB_HD: return "100MB HD";  
  case Port::HUNDRED_MB_FD: return "100MB FD";  
  case Port::ONE_GB_HD: return "1GB HD";  
  case Port::ONE_GB_FD: return "1GB FD";  
  case Port::TEN_GB_FD: return "10GB FD";
  case Port::COPPER: return "Copper";
  case Port::FIBER: return "Fiber";
  case Port::AUTO_NEG: return "AutoNeg";
  case Port::PAUSE: return "Pause"; 
  case Port::PAUSE_ASYM: return "PauseAsym";
  default: return "Unknown";
  }
}


// -------------------------------------------------------------------------- //
// Flow_mod

Error_condition 
to_buffer(Buffer_view& v, const Flow_mod& fm) {
  if (not available(v, bytes(fm)))
    return AVAILABLE_FLOW_MOD;
  to_buffer(v, fm.match);
  to_buffer(v, fm.cookie);
  to_buffer(v, fm.command);
  to_buffer(v, fm.idle_timeout);
  to_buffer(v, fm.hard_timeout);
  to_buffer(v, fm.priority);
  to_buffer(v, fm.buffer_id);
  to_buffer(v, fm.out_port);
  to_buffer(v, fm.flags);
  return to_buffer(v, fm.actions);
}

Error_condition
from_buffer(Buffer_view& v, Flow_mod& fm) {
  if (not available(v, bytes(fm)))
    return AVAILABLE_FLOW_MOD;
  from_buffer(v, fm.match);
  from_buffer(v, fm.cookie);
  from_buffer(v, fm.command);
  from_buffer(v, fm.idle_timeout);
  from_buffer(v, fm.hard_timeout);
  from_buffer(v, fm.priority);
  from_buffer(v, fm.buffer_id);
  from_buffer(v, fm.out_port);
  from_buffer(v, fm.flags);
  return from_buffer(v, fm.actions);
}

std::string
to_string(Flow_mod::Command c) {
  switch(c){
    case Flow_mod::ADD: return "ADD";
    case Flow_mod::MODIFY: return "MODIFY";
    case Flow_mod::MODIFY_STRICT: return "MODIFY_STRICT";
    case Flow_mod::DELETE: return "DELETE";
    case Flow_mod::DELETE_STRICT: return "DELETE_STRICT";
    default: return "UNKNWON";
  }
}

// FIXME: Need to test this field as a bitset.
std::string
to_string(Flow_mod::Flags f) {
  switch(f) {
    case Flow_mod::SEND_FLOW_REM: return "SEND_FLOW_REM";
    case Flow_mod::CHECK_OVERLAP: return "CHECK_OVERLAP";
    case Flow_mod::EMERG: return "EMERG";
    default: return "UNKNOWN";
  }
}

std::string 
to_string(const Flow_mod& fm, Formatter& f) 
{
  std::stringstream ss;
  open_block(ss, f, "FlowMod");

  ss << to_string(fm.match, f);

  nvp_to_string(ss, f, "Cookie", fm.cookie);
  nvp_to_string(ss, f, "Command ", to_string(fm.command), (int)fm.command);
  nvp_to_string(ss, f, "Idle Timeout", fm.idle_timeout);
  nvp_to_string(ss, f, "Hard Timeout", fm.hard_timeout);
  nvp_to_string(ss, f, "Priority", fm.priority); 
  nvp_to_string(ss, f, "Buffer ID", fm.buffer_id);
  nvp_to_string(ss, f, "Output Port", fm.out_port);
  nvp_to_string(ss, f, "Flags", to_string(fm.flags), (int)fm.flags);

  ss << to_string(fm.actions, f);

  close_block(ss, f, "FlowMod");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Feature Response

Error_condition 
to_buffer(Buffer_view& v, const Feature_res& m) {
  if (not available(v, bytes(m)))
    return AVAILABLE_FEATURE_RES;
  to_buffer(v, m.datapath_id);
  to_buffer(v, m.n_buffers);
  to_buffer(v, m.n_tbls);
  pad(v, 3);
  to_buffer(v, m.capabilities);
  to_buffer(v, m.feature_actions);
  return to_buffer(v, m.ports);
}

Error_condition
from_buffer(Buffer_view& v, Feature_res& m) {
  if (not available(v, bytes(m)))
    return AVAILABLE_FEATURE_RES;
  from_buffer(v, m.datapath_id);
  from_buffer(v, m.n_buffers);
  from_buffer(v, m.n_tbls);
  pad(v, 3);
  from_buffer(v, m.capabilities);
  from_buffer(v, m.feature_actions);
  return from_buffer(v, m.ports);
}

std::string 
to_string(const Feature_res& fr, Formatter& fmt) {
  std::stringstream ss;
  open_block(ss, fmt, "Feature_res");
  nvp_to_string(ss, fmt, "Datapath", fr.datapath_id);
  nvp_to_string(ss, fmt, "No. Buffers", fr.n_buffers);
  nvp_to_string(ss, fmt, "No. Tables", fr.n_tbls);
  nvp_to_string(ss, fmt, "Capabilities", fr.capabilities);
  nvp_to_string(ss, fmt, "Actions", fr.feature_actions);
  ss << to_string(fr.ports, fmt) << '\n';
  close_block(ss, fmt, "Feature_res");
  return ss.str();
}

std::string
to_string(Feature_res::Capability c) {
  switch(c) {
  case Feature_res::FLOW_STATS: return "Flow Stats";
  case Feature_res::TABLE_STATS: return "Table Stats";
  case Feature_res::PORT_STATS: return "Port Stats";
  case Feature_res::STP: return "STP";
  case Feature_res::RESERVED: return "Reserved";
  case Feature_res::IP_REASM: return "IP Reasm";
  case Feature_res::QUEUE_STATS: return "Queue Stats";
  case Feature_res::ARP_MATCH_IP: return "ARP Match IP"; 
  default: return "Unknown";
  }
}

std::string
to_string(Feature_res::Action a) {
  switch(a) {
  case Feature_res::OUTPUT: return "Output";
  case Feature_res::SET_VLAN_VID: return "Set VLAN VID";
  case Feature_res::SET_VLAN_PCP: return "Set VLAN PCP";
  case Feature_res::STRIP_VLAN: return "Strip VLAN";
  case Feature_res::SET_DL_SRC: return "Set DL Src";
  case Feature_res::SET_DL_DST: return "Set DL Dst";
  case Feature_res::SET_NW_SRC: return "Set NW Src";
  case Feature_res::SET_NW_DST: return "Set NW Dst";
  case Feature_res::SET_NW_TOS: return "Set NW Tos";
  case Feature_res::SET_TP_SRC: return "Set TP Src";
  case Feature_res::SET_TP_DST: return "Set TP Dst";
  case Feature_res::ENQUEUE: return "Enqueue";
  default: return "Unknown";
  }
}


// -------------------------------------------------------------------------- //
// Get Config Res

std::string
to_string(const Get_config_res& gcr, Formatter& f) 
{
  std::stringstream ss;
  open_block(ss, f, "GetConfigRes");
  //nvp_to_string(ss, f, "Flag", to_string(gcr.flags), int(gcr.flags));
  nvp_to_string(ss, f, "Flag", int(gcr.flags));
  nvp_to_string(ss, f, "Miss Send Length", gcr.miss_send_len);
  close_block(ss, f, "GetConfigRes");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Set Config 

std::string
to_string(const Set_config& sc, Formatter& f) 
{
  std::stringstream ss;
  open_block(ss, f, "SetConfig");
  //nvp_to_string(ss, f, "Flag", to_string(sc.flags), int(sc.flags));
  nvp_to_string(ss, f, "Flag", int(sc.flags));
  nvp_to_string(ss, f, "Miss Send Length", sc.miss_send_len);
  close_block(ss, f, "SetConfigRes");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Packet In


Error_condition 
to_buffer(Buffer_view& v, const Packet_in& pi) {
  if (not available(v, bytes(pi)))
    return AVAILABLE_PACKET_IN;
  to_buffer(v, pi.buffer_id);
  to_buffer(v, pi.total_len);
  to_buffer(v, pi.in_port);
  to_buffer(v, pi.reason);
  pad(v, 1);
  to_buffer(v, pi.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Packet_in& pi) {
  if (not available(v, bytes(pi)))
    return AVAILABLE_PACKET_IN;
  from_buffer(v, pi.buffer_id);
  from_buffer(v, pi.total_len);
  from_buffer(v, pi.in_port);
  from_buffer(v, pi.reason);
  pad(v, 1);

  // Allocating the buffer depends on whether the length is non-zero.
  if (pi.total_len == 0)
    return SUCCESS;
  pi.data = Buffer(pi.total_len);

  // Availability is checked in this call.
  if (not from_buffer(v, pi.data))
    return AVAILABLE_PACKET_IN;
  return SUCCESS; 
}


std::string
to_string(Packet_in::Reason r)
{
  switch(r) {
  case Packet_in::NO_MATCH: return "NoMatch";
  case Packet_in::ACTION: return "Action";
  default: return "Unknown";
  }
} 

std::string 
to_string(const Packet_in& pi, Formatter& f) 
{
  std::stringstream ss;
  open_block(ss, f, "PacketIn");
  nvp_to_string(ss, f, "Buffer ID", pi.buffer_id);
  nvp_to_string(ss, f, "Total Len", pi.total_len);
  nvp_to_string(ss, f, "Ingress Port", pi.in_port);
  nvp_to_string(ss, f, "Reason", to_string(pi.reason), int(pi.reason));
  nvp_to_string(ss, f, "Data bytes", bytes(pi.data));
  close_block(ss, f, "PacketIn");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Flow Removed

Error_condition 
to_buffer(Buffer_view& v, const Flow_removed& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FLOW_REMOVED;
  to_buffer(v, fr.match);
  to_buffer(v, fr.cookie);
  to_buffer(v, fr.priority);
  to_buffer(v, fr.reason);
  pad(v, 1);
  to_buffer(v, fr.duration_sec);
  to_buffer(v, fr.duration_nsec);
  to_buffer(v, fr.idle_timeout);
  pad(v, 2);
  to_buffer(v, fr.packet_count);
  to_buffer(v, fr.byte_count);
  return SUCCESS;
}

Error_condition 
from_buffer(Buffer_view& v, Flow_removed& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FLOW_REMOVED;
  from_buffer(v, fr.match);
  from_buffer(v, fr.cookie);
  from_buffer(v, fr.priority);
  from_buffer(v, fr.reason);
  pad(v, 1);
  from_buffer(v, fr.duration_sec);
  from_buffer(v, fr.duration_nsec);
  from_buffer(v, fr.idle_timeout);
  pad(v, 2);
  from_buffer(v, fr.packet_count);
  from_buffer(v, fr.byte_count);
  return SUCCESS;
}

std::string 
to_string(const Flow_removed& fr, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "FlowRemoved");
  
  ss << to_string(fr.match, f);

  nvp_to_string(ss, f, "Cookie", fr.cookie);
  nvp_to_string(ss, f, "Priority", fr.priority);
  nvp_to_string(ss, f, "Reason", to_string(fr.reason), int(fr.reason));
  nvp_to_string(ss, f, "Duration in Seconds", fr.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoseconds", fr.duration_nsec);
  nvp_to_string(ss, f, "Idle Timeout", fr.idle_timeout);
  nvp_to_string(ss, f, "Packet Count", fr.packet_count);
  nvp_to_string(ss, f, "Byte Count", fr.byte_count);
  
  close_block(ss, f, "FlowRemoved");
  return ss.str();
}

std::string
to_string(Flow_removed::Reason r) {
  switch(r) {
  case Flow_removed::IDLE_TIMEOUT: return "IdleTimeout";
  case Flow_removed::HARD_TIMEOUT: return "HardTimeout";
  case Flow_removed::DELETE: return "Delete";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Port Status

Error_condition
to_buffer(Buffer_view& v, const Port_status& ps) {
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
to_string(Port_status::Reason r)
{
  switch(r) {
  case Port_status::Reason::ADD: return "Add";
  case Port_status::Reason::DELETE: return "Delete";
  case Port_status::Reason::MODIFY: return "Modify";
  default: return "Unknown";
  }
} 

// -------------------------------------------------------------------------- //
// Packet Out

Error_condition 
to_buffer(Buffer_view& v, const Packet_out& po)
{
  if (not available(v, bytes(po)))
    return AVAILABLE_PACKET_OUT;
  to_buffer(v, po.buffer_id);
  to_buffer(v, po.in_port);
  to_buffer(v, po.actions_len);

  // FIXME: Constrain this view?
  if (Error_decl err = to_buffer(v, po.actions))
    return err;

  to_buffer(v, po.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Packet_out& po) {
  // Check and read the static portion.
  if (not available(v, bytes(po)))
    return AVAILABLE_PACKET_OUT;
  from_buffer(v, po.buffer_id);
  from_buffer(v, po.in_port);
  from_buffer(v, po.actions_len);

  // Ensure that sufficient bytes exist to constrain.
  if (remaining (v) < po.actions_len)
    return BAD_PACKET_OUT_LENGTH;

  // Read the sequence of actions from the constrained view
  // and update the current view.
  Buffer_view c = constrain(v, po.actions_len);
  if (Error_decl err = from_buffer(c, po.actions))
    return err;

  // Check for excess data.
  if (not update(v, c))
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
  nvp_to_string(ss, f, "Action Length", po.actions_len);
  
  ss << to_string(po.actions, f);
  ss << to_string(po.data, f);
  
  close_block(ss, f, "PacketOut");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Port Mod

std::string 
to_string(const Port_mod& pm, Formatter& f) 
{
  std::stringstream ss;
  open_block(ss, f, "PortMod");
  
  nvp_to_string(ss, f, "Port", pm.port);
  nvp_to_string(ss, f, "Hardware Address", ethernet::to_string(pm.hw_addr),
                to_string(pm.hw_addr));
  nvp_to_string(ss, f, "Config", to_string(pm.config), int(pm.config));
  nvp_to_string(ss, f, "Mask", to_string(pm.mask), int(pm.mask));
  nvp_to_string(ss, f, "Advertise", to_string(pm.advertise), 
                int(pm.advertise));
  
  open_block(ss, f, "PortMod");
  return ss.str();
}

std::string
to_string(Port_mod::Config c)
{
  switch(c) {
  case Port_mod::PORT_DOWN: return "PortDown";
  case Port_mod::NO_STP: return "No STP";
  case Port_mod::NO_RECV: return "No Recv";
  case Port_mod::NO_RECV_STP: return "No Recv STP";
  case Port_mod::NO_FLOOD: return "No Flood";
  case Port_mod::NO_FWD: return "No Fwd";
  case Port_mod::NO_PACKET_IN: return "No PacketIn";
  default: return "Unknown";
  }
}

std::string
to_string(Port_mod::Features f)
{
  switch(f) {
  case Port_mod::Features::TEN_MB_HD: return "10MB HD";
  case Port_mod::Features::TEN_MB_FD: return "10MB FD";
  case Port_mod::Features::HUNDRED_MB_HD: return "100MB HD";
  case Port_mod::Features::HUNDRED_MB_FD: return "100MB FD";
  case Port_mod::Features::ONE_GB_HD: return "1GB HD";
  case Port_mod::Features::ONE_GB_FD: return "1GB FD";
  case Port_mod::Features::TEN_GB_FD: return "10GB FD";
  case Port_mod::Features::COPPER: return "Copper";
  case Port_mod::Features::FIBER: return "Fiber";
  case Port_mod::Features::AUTO_NEG: return "Auto Neg";
  case Port_mod::Features::PAUSE: return "Pause";
  case Port_mod::Features::PAUSE_ASYM: return "Pause Asym";
  default: return "Unknown";
  }
}

Error_condition 
to_buffer(Buffer_view& v, const Port_mod& pm)
{
  if (not available(v, bytes(pm)))
    return AVAILABLE_PORT_MOD;
  to_buffer(v, pm.port);
  to_buffer(v, pm.hw_addr);
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
  from_buffer(v, pm.hw_addr);
  from_buffer(v, pm.config);
  from_buffer(v, pm.mask);
  from_buffer(v, pm.advertise);
  pad(v, 4);
  return SUCCESS;
}


// -------------------------------------------------------------------------- //
// Stats Type

std::string
to_string(Stats_type t)
{
  switch (t) {
  case STATS_DESC: return "Desc";
  case STATS_FLOW: return "Flow";
  case STATS_TABLE: return "Table";
  case STATS_PORT: return "Port";
  case STATS_QUEUE: return "Queue";
  case STATS_VENDOR: return "Vendor";
  default: return "Unknown";
  }
}


// -------------------------------------------------------------------------- //
// Stats Header

Error_condition
to_buffer(Buffer_view& v, const Stats_header& h) {
  to_buffer(v, h.type);
  to_buffer(v, h.flags);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_header& h) {
  from_buffer(v, h.type);
  from_buffer(v, h.flags);
  return SUCCESS;
}

std::string
to_string(const Stats_header& h, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Hdr");
  nvp_to_string(ss, f, "Type", to_string(h.type), (int)h.type);
  nvp_to_string(ss, f, "Flags", to_string(h.flags), (int)h.flags);
  close_block(ss, f, "Hdr");
  return ss.str();
}

std::string
to_string(Stats_header::Flags f) {
  std::stringstream ss;
  if (f & Stats_header::MORE)
    ss << "More";
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats_req_flow

std::string 
to_string(const Stats_req_flow& srf, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "StatsReq Flow");
  ss << to_string(srf.match, f);
  nvp_to_string(ss, f, "Table ID", srf.table_id);
  nvp_to_string(ss, f, "Out Port", srf.out_port);
  close_block(ss, f, "StatsReq Flow");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats_req_aggregate

std::string 
to_string(const Stats_req_aggregate& sra, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "StatsReq Aggregate");
  ss << to_string(sra.match, f);
  nvp_to_string(ss, f, "Table ID", sra.table_id);
  nvp_to_string(ss, f, "Out Port", sra.out_port);
  close_block(ss, f, "StatsReq Aggregate");
  return ss.str();
}
// -------------------------------------------------------------------------- //
// Stats_req_port

Error_condition
to_buffer(Buffer_view& v, const Stats_req_port& p) {
  if (not available(v, bytes(p)))
    return AVAILABLE_STATS_REQ_PORT;
  to_buffer(v, p.port_no);
  pad(v, 6);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_port& p) {
  if (not available(v, bytes(p)))
    return AVAILABLE_STATS_REQ_PORT;
  from_buffer(v, p.port_no);
  pad(v, 6);
  return SUCCESS;
}

std::string
to_string(const Stats_req_port& p, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Port");
  nvp_to_string(ss, f, "Port ID", p.port_no);
  close_block(ss, f, "StatsReq Port");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Stats_req_queue

Error_condition
to_buffer(Buffer_view& v, const Stats_req_queue& q) {
  if (not available(v, bytes(q)))
    return AVAILABLE_STATS_REQ_QUEUE;
  to_buffer(v, q.port_no);
  pad(v, 2);
  to_buffer(v, q.queue_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_queue& q) {
  if (not available(v, bytes(q)))
    return AVAILABLE_STATS_REQ_QUEUE;
  from_buffer(v, q.port_no);
  pad(v, 2);
  from_buffer(v, q.queue_id);
  return SUCCESS;
}

std::string
to_string(const Stats_req_queue& q, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "StatsReq Queue");
  nvp_to_string(ss, f, "Port ID", q.port_no);
  nvp_to_string(ss, f, "Queue ID", q.queue_id);
  close_block(ss, f, "StatsReq Queue");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats Request: Vendor

Error_condition
to_buffer(Buffer_view& v, const Stats_req_vendor& srv)
{
  if (not available(v, bytes(srv)))
    return AVAILABLE_STATS_REQ_VENDOR;
  to_buffer(v, srv.vendor_id);
  return to_buffer(v, srv.data);
}

Error_condition
from_buffer(Buffer_view& v, Stats_req_vendor& srv)
{
  if (not available(v, bytes(srv)))
    return AVAILABLE_STATS_REQ_VENDOR;
  from_buffer(v, srv.vendor_id);
  return from_buffer(v, srv.data);
}

std::string
to_string(const Stats_req_vendor& srv, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq Vendor");
  nvp_to_string(ss, f, "Vendor ID", srv.vendor_id);
  nvp_to_string(ss, f, "Data Bytes", bytes(srv.data));
  close_block(ss, f, "StatsReq Vendor");
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
  case STATS_AGGREGATE: new (&p.data.aggr) Stats_req_aggregate(); break;
  case STATS_TABLE: new (&p.data.table) Stats_req_table(); break;
  case STATS_PORT: new (&p.data.port) Stats_req_port(); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_req_queue(); break;
  case STATS_VENDOR: new (&p.data.vendor) Stats_req_vendor(); break;
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
  case STATS_DESC: new (&p.data.desc) Stats_req_desc(std::move(x.data.desc)); 
    break;
  case STATS_FLOW: new (&p.data.flow) Stats_req_flow(std::move(x.data.flow)); 
    break;
  case STATS_AGGREGATE: 
    new (&p.data.aggr) Stats_req_aggregate(std::move(x.data.aggr)); break;
  case STATS_TABLE: 
    new (&p.data.table) Stats_req_table(std::move(x.data.table)); break;
  case STATS_PORT: new (&p.data.port) Stats_req_port(std::move(x.data.port)); 
    break;
  case STATS_QUEUE: 
    new (&p.data.queue) Stats_req_queue(std::move(x.data.queue)); break;
  case STATS_VENDOR: 
    new (&p.data.vendor) Stats_req_vendor(std::move(x.data.vendor)); break;
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
  case STATS_AGGREGATE: new (&p.data.aggr) Stats_req_aggregate(x.data.aggr); 
    break;
  case STATS_TABLE: new (&p.data.table) Stats_req_table(x.data.table); break;
  case STATS_PORT: new (&p.data.port) Stats_req_port(x.data.port); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_req_queue(x.data.queue); break;
  case STATS_VENDOR: new (&p.data.vendor) Stats_req_vendor(x.data.vendor); 
    break;
  default: variant_error(t);
  }
}

void 
destroy(Stats_req_payload& p, Stats_type t)
{
  switch(t) {
  case STATS_DESC: p.data.desc.~Stats_req_desc(); break;
  case STATS_FLOW: p.data.flow.~Stats_req_flow(); break;
  case STATS_AGGREGATE: p.data.aggr.~Stats_req_aggregate(); break;
  case STATS_TABLE: p.data.table.~Stats_req_table(); break;
  case STATS_PORT: p.data.port.~Stats_req_port(); break;
  case STATS_QUEUE: p.data.queue.~Stats_req_queue(); break;
  case STATS_VENDOR: p.data.vendor.~Stats_req_vendor(); break;
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
  case STATS_AGGREGATE: p.data.aggr = std::move(x.data.aggr); break;
  case STATS_TABLE: p.data.table = std::move(x.data.table); break;
  case STATS_PORT: p.data.port = std::move(x.data.port); break;
  case STATS_QUEUE: p.data.queue = std::move(x.data.queue); break;
  case STATS_VENDOR: p.data.vendor = std::move(x.data.vendor); break;
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
  case STATS_AGGREGATE: p.data.aggr = x.data.aggr; break;
  case STATS_TABLE: p.data.table = x.data.table; break;
  case STATS_PORT: p.data.port = x.data.port; break;
  case STATS_QUEUE: p.data.queue = x.data.queue; break;
  case STATS_VENDOR: p.data.vendor = x.data.vendor; break;
  default: variant_error(t);
  }
  return p;
}

bool 
equal(const Stats_req_payload& a, const Stats_req_payload& b, Stats_type t1, 
      Stats_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case STATS_DESC: return a.data.desc == b.data.desc;
  case STATS_FLOW: return a.data.flow == b.data.flow;
  case STATS_AGGREGATE: return a.data.aggr == b.data.aggr;
  case STATS_TABLE: return a.data.table == b.data.table;
  case STATS_PORT: return a.data.port == b.data.port;
  case STATS_QUEUE: return a.data.queue == b.data.queue;
  case STATS_VENDOR: return a.data.vendor == b.data.vendor;
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
  case STATS_AGGREGATE: return bytes(p.data.aggr);
  case STATS_TABLE: return bytes(p.data.table);
  case STATS_PORT: return bytes(p.data.port);
  case STATS_QUEUE: return bytes(p.data.queue);
  case STATS_VENDOR: return bytes(p.data.vendor);
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
  case STATS_AGGREGATE: return is_valid(p.data.aggr);
  case STATS_TABLE: return is_valid(p.data.table);
  case STATS_PORT: return is_valid(p.data.port);
  case STATS_QUEUE: return is_valid(p.data.queue);
  case STATS_VENDOR: return is_valid(p.data.vendor);
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
  case STATS_AGGREGATE: return to_buffer(v, p.data.aggr);
  case STATS_TABLE: return to_buffer(v, p.data.table);
  case STATS_PORT: return to_buffer(v, p.data.port);
  case STATS_QUEUE: return to_buffer(v, p.data.queue);
  case STATS_VENDOR: return to_buffer(v, p.data.vendor);
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
  case STATS_AGGREGATE: return from_buffer(v, p.data.aggr);
  case STATS_TABLE: return from_buffer(v, p.data.table);
  case STATS_PORT: return from_buffer(v, p.data.port);
  case STATS_QUEUE: return from_buffer(v, p.data.queue);
  case STATS_VENDOR: return from_buffer(v, p.data.vendor);
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
  case STATS_AGGREGATE: return to_string(p.data.aggr, fmt);
  case STATS_TABLE: return to_string(p.data.table, fmt);
  case STATS_PORT: return to_string(p.data.port, fmt);
  case STATS_QUEUE: return to_string(p.data.queue, fmt);
  case STATS_VENDOR: return to_string(p.data.vendor, fmt);
  default: variant_error(t);
  }
}


// -------------------------------------------------------------------------- //
// Stats_req

Error_condition
to_buffer(Buffer_view& v, const Stats_req& r)
{
  if (not available(v, bytes(r.header)))
    return AVAILABLE_STATS_REQ;
  to_buffer(v, r.header);
  return to_buffer(v, r.payload, r.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Stats_req& r)
{
  if (not available(v, bytes(r.header)))
    return AVAILABLE_STATS_REQ;
  from_buffer(v, r.header);

  if (not is_valid(r.header.type))
    return BAD_STATS;

  Stats_req::Payload p;
  construct(p, r.header.type);
  assign(r.payload, std::move(p), r.header.type);

  return from_buffer(v, r.payload, r.header.type);
}

std::string
to_string(const Stats_req& r, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsReq");

  ss << to_string(r.header, f) << "\n";
  if (is_valid(r.header.type))
    ss << to_string(r.payload, f,r.header.type) << "\n";
  else
    ss << "Malformed payload\n";

  close_block(ss, f, "StatsReq");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats_res_desc

Error_condition
to_buffer(Buffer_view& v, const Stats_res_desc& d) {
  if (!available(v, bytes(d)))
    return AVAILABLE_STATS_RES_DESC;
  to_buffer(v, d.mfr_desc);
  to_buffer(v, d.hw_desc);
  to_buffer(v, d.sw_desc);
  to_buffer(v, d.serial_num);
  to_buffer(v, d.dp_desc);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_desc& d) {
  if (!available (v, bytes(d)))
    return AVAILABLE_STATS_RES_DESC;
  from_buffer(v, d.mfr_desc);
  from_buffer(v, d.hw_desc);
  from_buffer(v, d.sw_desc);
  from_buffer(v, d.serial_num);
  from_buffer(v, d.dp_desc);
  return SUCCESS;
}

std::string to_string(const Stats_res_desc& d, Formatter& f) {
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
to_buffer(Buffer_view& v, const Stats_res_flow& f) {
  if (not available (v, bytes(f)))
    return AVAILABLE_STATS_RES_FLOW;

  to_buffer(v, f.length);
  to_buffer(v, f.table_id);
  pad(v, 1);

  if (Error_decl err = to_buffer(v, f.match))
    return err;

  to_buffer(v, f.duration_sec);
  to_buffer(v, f.duration_nsec);
  to_buffer(v, f.priority);
  to_buffer(v, f.idle_timeout);
  to_buffer(v, f.hard_timeout);
  pad(v, 6);
  to_buffer(v, f.cookie);
  to_buffer(v, f.packet_count);
  to_buffer(v, f.byte_count);

  return to_buffer(v, f.actions);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_flow& f) {
  if (not available (v, bytes(f)))
    return AVAILABLE_STATS_RES_FLOW;

  from_buffer(v, f.length);
  from_buffer(v, f.table_id);
  pad(v, 1);
  
  if (Error_decl err = from_buffer(v, f.match))
    return err;

  from_buffer(v, f.duration_sec);
  from_buffer(v, f.duration_nsec);
  from_buffer(v, f.priority);
  from_buffer(v, f.idle_timeout);
  from_buffer(v, f.hard_timeout);
  pad(v, 6);
  from_buffer(v, f.cookie);
  from_buffer(v, f.packet_count);
  from_buffer(v, f.byte_count);

  return from_buffer(v, f.actions);
}

std::string
to_string(const Stats_res_flow& f, Formatter& fmt) {
  std::stringstream ss;
  open_block(ss, fmt, "StatsRes Flow");
  
  nvp_to_string(ss, fmt, "Length", f.length);
  nvp_to_string(ss, fmt, "Table ID", f.table_id);
  
  ss << to_string(f.match, fmt);
  
  nvp_to_string(ss, fmt, "Duration in Seconds", f.duration_sec);
  nvp_to_string(ss, fmt, "Duration in Nanoeconds", f.duration_nsec);
  nvp_to_string(ss, fmt, "Priority", f.priority);
  nvp_to_string(ss, fmt, "Idle Timeout", f.idle_timeout);
  nvp_to_string(ss, fmt, "Hard Timeout", f.hard_timeout);
  nvp_to_string(ss, fmt, "Cookie", f.cookie);
  nvp_to_string(ss, fmt, "Packet Count", f.packet_count);
  nvp_to_string(ss, fmt, "Byte Count", f.byte_count);
  
  ss << to_string(f.actions, fmt);

  close_block(ss, fmt, "StatsRes Flow");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats Response Flows

Error_condition
to_buffer(Buffer_view& v, const Stats_res_flows& s) {
  if (not available (v, bytes(s)))
    return AVAILABLE_STATS_RES_FLOWS;
  return to_buffer(v, s.flows);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_flows& s)
{
  if (not available (v, bytes(s)))
    return AVAILABLE_STATS_RES_FLOWS;
  return from_buffer(v, s.flows);
}


std::string
to_string(const Stats_res_flows& srf, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "StatsRes Flows");

  ss << to_string(srf.flows, f);

  close_block(ss, f, "StatsRes Flows");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats Response Aggregate

Error_condition
to_buffer(Buffer_view& v, const Stats_res_aggregate& a) {
  if (!available (v, bytes(a)))
    return AVAILABLE_STATS_RES_AGGREGATE;
  to_buffer(v, a.packet_count);
  to_buffer(v, a.byte_count);
  to_buffer(v, a.flow_count);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_aggregate& a) {
  if (!available (v, bytes(a)))
    return AVAILABLE_STATS_RES_AGGREGATE;
  from_buffer(v, a.packet_count);
  from_buffer(v, a.byte_count);
  from_buffer(v, a.flow_count);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Stats_res_aggregate& a, Formatter& fmt)
{
  std::stringstream ss;
  open_block(ss, fmt, "StatsRes Aggregate");
  nvp_to_string(ss, fmt, "Packet count", a.packet_count);
  nvp_to_string(ss, fmt, "Byte count", a.byte_count);
  nvp_to_string(ss, fmt, "Flow count", a.flow_count);
  close_block(ss, fmt, "StatsRes Aggregate");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats Response Port

Error_condition
to_buffer(Buffer_view& v, const Stats_res_port& p) {
  if (!available(v, bytes(p)))
    return AVAILABLE_STATS_RES_PORT;
  to_buffer(v, p.port_no);
  pad(v, 6);
  to_buffer(v, p.rx_packets);
  to_buffer(v, p.tx_packets);
  to_buffer(v, p.rx_bytes);
  to_buffer(v, p.tx_bytes);
  to_buffer(v, p.rx_dropped);
  to_buffer(v, p.tx_dropped);
  to_buffer(v, p.rx_errors);
  to_buffer(v, p.tx_errors);
  to_buffer(v, p.rx_frame_err);
  to_buffer(v, p.rx_over_err);
  to_buffer(v, p.rx_crc_err);
  to_buffer(v, p.collisions);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_port& p) {
  if (!available(v, bytes(p)))
    return AVAILABLE_STATS_RES_PORT;
  from_buffer(v, p.port_no);
  pad(v, 6);
  from_buffer(v, p.rx_packets);
  from_buffer(v, p.tx_packets);
  from_buffer(v, p.rx_bytes);
  from_buffer(v, p.tx_bytes);
  from_buffer(v, p.rx_dropped);
  from_buffer(v, p.tx_dropped);
  from_buffer(v, p.rx_errors);
  from_buffer(v, p.tx_errors);
  from_buffer(v, p.rx_frame_err);
  from_buffer(v, p.rx_over_err);
  from_buffer(v, p.rx_crc_err);
  from_buffer(v, p.collisions);
  return SUCCESS;
}

std::string
to_string(const Stats_res_port& p, Formatter& fmt)
{
  std::stringstream ss;
  open_block(ss, fmt, "StatsRes Port");
  nvp_to_string(ss, fmt, "Port Number", p.port_no);

  ss << std::string(fmt.indent, ' ');
  ss << "Packets (rx/tx): " << p.rx_packets << '/' << p.tx_packets << '\n';

  ss << std::string(fmt.indent, ' ');
  ss << "Bytes (rx/tx): " << p.rx_bytes << '/' << p.tx_bytes << '\n';

  ss << std::string(fmt.indent, ' ');
  ss << "Dropped (rx/tx): " << p.rx_dropped << '/' << p.tx_dropped << '\n';

  ss << std::string(fmt.indent, ' ');
  ss << "Error (rx/tx): " << p.rx_errors << '/' << p.tx_errors << '\n';

  nvp_to_string(ss, fmt, "Rx Frame Errors", p.rx_frame_err);
  nvp_to_string(ss, fmt, "Rx Overrun Errors", p.rx_over_err);
  nvp_to_string(ss, fmt, "Rx CRC Errors", p.rx_crc_err);
  nvp_to_string(ss, fmt, "Collisions", p.collisions);
  close_block(ss, fmt, "StatsRes Port");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats Response Ports

Error_condition
to_buffer(Buffer_view& v, const Stats_res_ports& srp) {
  if (not available(v, bytes(srp)))
    return AVAILABLE_STATS_RES_PORTS;
  return to_buffer(v, srp.ports);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_ports& srp) {
  if (not available(v, bytes(srp)))
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
// Stats_res_queue

Error_condition
to_buffer(Buffer_view& v, const Stats_res_queue& q) {
  if (!available(v, bytes(q)))
    return AVAILABLE_STATS_RES_QUEUE;
  to_buffer(v, q.port_no);
  pad(v, 2);
  to_buffer(v, q.queue_id);
  to_buffer(v, q.tx_packets);
  to_buffer(v, q.tx_bytes);
  to_buffer(v, q.tx_errors);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_queue& q) {
  if (!available(v, bytes(q)))
    return AVAILABLE_STATS_RES_QUEUE;
  from_buffer(v, q.port_no);
  pad(v, 2);
  from_buffer(v, q.queue_id);
  from_buffer(v, q.tx_packets);
  from_buffer(v, q.tx_bytes);
  from_buffer(v, q.tx_errors);
  return SUCCESS;
}

std::string
to_string(const Stats_res_queue& q, Formatter& fmt) {
  std::stringstream ss;
  open_block(ss, fmt, "StatsRes Queue");
  nvp_to_string(ss, fmt, "Port No", q.port_no);
  nvp_to_string(ss, fmt, "Queue Id", q.queue_id);
  nvp_to_string(ss, fmt, "Tx Packets", q.tx_packets);
  nvp_to_string(ss, fmt, "Tx Bytes", q.tx_bytes);
  nvp_to_string(ss, fmt, "Tx Errors", q.tx_errors);
  close_block(ss, fmt, "StatsRes Queue");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats Response Queues

Error_condition
to_buffer(Buffer_view& v, const Stats_res_queues& srq) {
  if (not available (v, bytes(srq)))
    return AVAILABLE_STATS_RES_QUEUES;
  return to_buffer(v, srq.queues);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_queues& srq) {
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
// Stats_res_table

Error_condition
to_buffer(Buffer_view& v, const Stats_res_table& t) {
  if (!available(v, bytes(t)))
    return AVAILABLE_STATS_RES_TABLE;
  to_buffer(v, t.table_id);
  pad(v, 3);
  to_buffer(v, t.name);
  to_buffer(v, t.wildcards);
  to_buffer(v, t.max_entries);
  to_buffer(v, t.active_count);
  to_buffer(v, t.lookup_count);
  to_buffer(v, t.matched_count);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_table& t) {
  if (!available(v, bytes(t)))
    return AVAILABLE_STATS_RES_TABLE;
  from_buffer(v, t.table_id);
  pad(v, 3);
  from_buffer(v, t.name);
  from_buffer(v, t.wildcards);
  from_buffer(v, t.max_entries);
  from_buffer(v, t.active_count);
  from_buffer(v, t.lookup_count);
  from_buffer(v, t.matched_count);
  return SUCCESS;
}

std::string
to_string(const Stats_res_table& t, Formatter& fmt)
{
  std::stringstream ss;
  open_block(ss, fmt, "StatsRes Table");
  nvp_to_string(ss, fmt, "Table Id", t.table_id);

  // FIXME: Doesn't work?
  // nvp_to_string(ss, fmt, "Table Name", t.name);

  // FIXME: The wildcards are actually a Match::Wildcard_type. I think
  // we need to lift those values out of the class definition.
  nvp_to_string(ss, fmt, "Wildcards", t.wildcards);
  
  nvp_to_string(ss, fmt, "Max Entries", t.max_entries);
  nvp_to_string(ss, fmt, "Tx Active Count", t.active_count);
  nvp_to_string(ss, fmt, "Tx Lookup Count", t.lookup_count);
  nvp_to_string(ss, fmt, "Tx Matched Count", t.matched_count);
  close_block(ss, fmt, "StatsRes Queue");
  
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats_res_tables

Error_condition
to_buffer(Buffer_view& v, const Stats_res_tables& s) {
  if (not available (v, bytes(s)))
    return AVAILABLE_STATS_RES_TABLES;
  return to_buffer(v, s.tables);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_tables& s) {
  if (not available (v, bytes(s)))
    return AVAILABLE_STATS_RES_TABLES;
  return from_buffer(v, s.tables);
}

std::string
to_string(const Stats_res_tables& s, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Tables");

  ss << to_string(s.tables, f);

  close_block(ss, f, "StatsRes Tables");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats_res_vendor

Error_condition
to_buffer(Buffer_view& v, const Stats_res_vendor& r)
{
  if (not available(v, bytes(r)))
    return AVAILABLE_STATS_RES_VENDOR;
  to_buffer(v, r.vendor_id);
  return to_buffer(v, r.data);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res_vendor& r)
{
  if (not available(v, bytes(r)))
    return AVAILABLE_STATS_RES_VENDOR;
  from_buffer(v, r.vendor_id);
  return from_buffer(v, r.data);
}

std::string
to_string(const Stats_res_vendor& v, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes Vendor");
  nvp_to_string(ss, f, "Vendor ID", v.vendor_id);
  nvp_to_string(ss, f, "Data bytes", bytes(v.data));
  close_block(ss, f, "StatsRes Vendor");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Stats_res_payload

void 
construct(Stats_res_payload& p, Stats_type t)
{
  p.init = true;
  switch(t) {
  case STATS_DESC: new (&p.data.desc) Stats_res_desc(); break;
  case STATS_FLOW: new (&p.data.flow) Stats_res_flows(); break;
  case STATS_AGGREGATE: new (&p.data.aggr) Stats_res_aggregate(); break;
  case STATS_TABLE: new (&p.data.table) Stats_res_tables(); break;
  case STATS_PORT: new (&p.data.port) Stats_res_ports(); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_res_queues(); break;
  case STATS_VENDOR: new (&p.data.vendor) Stats_res_vendor(); break;
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
  case STATS_DESC: new (&p.data.desc) Stats_res_desc(std::move(x.data.desc)); 
    break;
  case STATS_FLOW: new (&p.data.flow) Stats_res_flows(std::move(x.data.flow)); 
    break;
  case STATS_AGGREGATE: 
    new (&p.data.aggr) Stats_res_aggregate(std::move(x.data.aggr)); break;
  case STATS_TABLE: 
    new (&p.data.table) Stats_res_tables(std::move(x.data.table)); break;
  case STATS_PORT: new (&p.data.port) Stats_res_ports(std::move(x.data.port)); 
    break;
  case STATS_QUEUE: 
    new (&p.data.queue) Stats_res_queues(std::move(x.data.queue)); break;
  case STATS_VENDOR: 
    new (&p.data.vendor) Stats_res_vendor(std::move(x.data.vendor)); break;
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
  case STATS_AGGREGATE: new (&p.data.aggr) Stats_res_aggregate(x.data.aggr); 
    break;
  case STATS_TABLE: new (&p.data.table) Stats_res_tables(x.data.table); break;
  case STATS_PORT: new (&p.data.port) Stats_res_ports(x.data.port); break;
  case STATS_QUEUE: new (&p.data.queue) Stats_res_queues(x.data.queue); break;
  case STATS_VENDOR: new (&p.data.vendor) Stats_res_vendor(x.data.vendor); 
    break;
  default: variant_error(t);
  }
}

void 
destroy(Stats_res_payload& p, Stats_type t)
{
  switch(t) {
  case STATS_DESC: p.data.desc.~Stats_res_desc(); break;
  case STATS_FLOW: p.data.flow.~Stats_res_flows(); break;
  case STATS_AGGREGATE: p.data.aggr.~Stats_res_aggregate(); break;
  case STATS_TABLE: p.data.table.~Stats_res_tables(); break;
  case STATS_PORT: p.data.port.~Stats_res_ports(); break;
  case STATS_QUEUE: p.data.queue.~Stats_res_queues(); break;
  case STATS_VENDOR: p.data.vendor.~Stats_res_vendor(); break;
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
  case STATS_AGGREGATE: p.data.aggr = std::move(x.data.aggr); break;
  case STATS_TABLE: p.data.table = std::move(x.data.table); break;
  case STATS_PORT: p.data.port = std::move(x.data.port); break;
  case STATS_QUEUE: p.data.queue = std::move(x.data.queue); break;
  case STATS_VENDOR: p.data.vendor = std::move(x.data.vendor); break;
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
  case STATS_AGGREGATE: p.data.aggr = x.data.aggr; break;
  case STATS_TABLE: p.data.table = x.data.table; break;
  case STATS_PORT: p.data.port = x.data.port; break;
  case STATS_QUEUE: p.data.queue = x.data.queue; break;
  case STATS_VENDOR: p.data.vendor = x.data.vendor; break;
  default: variant_error(t);
  }
  return p;
}

bool 
equal(const Stats_res_payload& a, const Stats_res_payload& b, Stats_type t1, 
      Stats_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case STATS_DESC: return a.data.desc == b.data.desc;
  case STATS_FLOW: return a.data.flow == b.data.flow;
  case STATS_AGGREGATE: return a.data.aggr == b.data.aggr;
  case STATS_TABLE: return a.data.table == b.data.table;
  case STATS_PORT: return a.data.port == b.data.port;
  case STATS_QUEUE: return a.data.queue == b.data.queue;
  case STATS_VENDOR: return a.data.vendor == b.data.vendor;
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
  case STATS_AGGREGATE: return bytes(p.data.aggr);
  case STATS_TABLE: return bytes(p.data.table);
  case STATS_PORT: return bytes(p.data.port);
  case STATS_QUEUE: return bytes(p.data.queue);
  case STATS_VENDOR: return bytes(p.data.vendor);
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
  case STATS_AGGREGATE: return is_valid(p.data.aggr);
  case STATS_TABLE: return is_valid(p.data.table);
  case STATS_PORT: return is_valid(p.data.port);
  case STATS_QUEUE: return is_valid(p.data.queue);
  case STATS_VENDOR: return is_valid(p.data.vendor);
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
  case STATS_AGGREGATE: return to_buffer(v, p.data.aggr);
  case STATS_TABLE: return to_buffer(v, p.data.table);
  case STATS_PORT: return to_buffer(v, p.data.port);
  case STATS_QUEUE: return to_buffer(v, p.data.queue);
  case STATS_VENDOR: return to_buffer(v, p.data.vendor);
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
  case STATS_AGGREGATE: return from_buffer(v, p.data.aggr);
  case STATS_TABLE: return from_buffer(v, p.data.table);
  case STATS_PORT: return from_buffer(v, p.data.port);
  case STATS_QUEUE: return from_buffer(v, p.data.queue);
  case STATS_VENDOR: return from_buffer(v, p.data.vendor);
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
  case STATS_AGGREGATE: return to_string(p.data.aggr, fmt);
  case STATS_TABLE: return to_string(p.data.table, fmt);
  case STATS_PORT: return to_string(p.data.port, fmt);
  case STATS_QUEUE: return to_string(p.data.queue, fmt);
  case STATS_VENDOR: return to_string(p.data.vendor, fmt);
  default: variant_error(t);
  }
}


// -------------------------------------------------------------------------- //
// Stats_res

Error_condition
to_buffer(Buffer_view& v, const Stats_res& r) {
  if (not available(v, bytes(r)))
    return AVAILABLE_STATS_RES;
  to_buffer(v, r.header);
  return to_buffer(v, r.payload, r.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Stats_res& r) {
  if (not available(v, bytes(r)))
    return AVAILABLE_STATS_RES;
  from_buffer(v, r.header);

  // Check that the payload is valid.
  if (not is_valid(r.header.type))
    return BAD_STATS;

  // r.payload = Stats_res::Payload() with r.header.type
  Stats_res::Payload p;
  construct(p, r.header.type);
  assign(r.payload, std::move(p), r.header.type);

  // Construct the payload.
  return from_buffer(v, r.payload, r.header.type);
}

std::string 
to_string(const Stats_res& r, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "StatsRes");

  ss << to_string(r.header, f) << "\n";
  if (is_valid(r.header.type))
    ss << to_string(r.payload, f,r.header.type) << "\n";
  else
    ss << "Malformed payload\n";

  close_block(ss, f, "StatsRes");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Queue_get_config_req

Error_condition 
to_buffer(Buffer_view& v, const Queue_get_config_req& r) {
  if (not available(v, bytes(r)))
    return AVAILABLE_QUEUE_GET_CONFIG_REQ;
  to_buffer(v, r.port);
  pad(v, 2);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Queue_get_config_req& r) {
  if (not available(v, bytes(r)))
    return AVAILABLE_QUEUE_GET_CONFIG_REQ;
  from_buffer(v, r.port);
  pad(v, 2);
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
// Queue_property_type

std::string 
to_string(Queue_property_type t)
{
  switch (t) {
  case QUEUE_PROPERTY_NONE:
    return "None";
  case QUEUE_PROPERTY_MIN_RATE:
    return "Min Rate";
  default:
    unreachable();
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Queue_property_min_rate

Error_condition
to_buffer(Buffer_view& v, const Queue_property_min_rate& p) {
  if (not available(v, bytes(p)))
    return AVAILABLE_QUEUE_PROPERTY_MIN_RATE;
  to_buffer(v, p.rate);
  pad(v, 6);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_min_rate& p) {
  if (not available(v, bytes(p)))
    return AVAILABLE_QUEUE_PROPERTY_MIN_RATE;
  from_buffer(v, p.rate);
  pad(v, 6);
  return SUCCESS;
}

std::string
to_string(const Queue_property_min_rate& p, Formatter& fmt)
{
  std::stringstream ss;
  open_block(ss, fmt, "QueuePropertyMinRate");
  nvp_to_string(ss, fmt, "Rate", p.rate);
  close_block(ss, fmt, "QueuePropertyMinRate");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Queue Property Header

Error_condition
to_buffer(Buffer_view& v, const Queue_property_header& h) {
  to_buffer(v, h.property);
  to_buffer(v, h.length);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_header& h) {
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
// Queue Property Payload

void
construct(Queue_property_payload& a, Queue_property_type t)
{
  a.init = true;
  switch (t) {
  case QUEUE_PROPERTY_NONE:
    new (&a.data.none) Queue_property_none();
    break;
  case QUEUE_PROPERTY_MIN_RATE:
    new (&a.data.min_rate) Queue_property_min_rate();
    break;
  default:
    variant_error(t);
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
    new (&a.data.none) Queue_property_none(b.data.none);
    break;
  case QUEUE_PROPERTY_MIN_RATE:
    new (&a.data.min_rate) Queue_property_min_rate(b.data.min_rate);
    break;
  default:
    unreachable();
  }
}

Queue_property::Payload&
assign(Queue_property_payload& a, const Queue_property_payload& b, 
       Queue_property_type t)
{
  if (&a == &b)
    return a;
  
  a.init = b.init;
  if (not a.init)
    return a;

  switch (t) {
  case QUEUE_PROPERTY_NONE: a.data.none = b.data.none; break;
  case QUEUE_PROPERTY_MIN_RATE: a.data.min_rate = b.data.min_rate; break;
  default:
    variant_error(t);
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
to_string(const Queue_property_payload& p, Formatter& fmt, 
          Queue_property_type t)
{
  assert(p);
  switch (t) {
  case QUEUE_PROPERTY_NONE:
    return to_string(p.data.none, fmt);
  case QUEUE_PROPERTY_MIN_RATE:
    return to_string(p.data.min_rate, fmt);
  default: variant_error(t); 
  }
  return "";
}


// -------------------------------------------------------------------------- //
// Queue_property

Error_condition 
to_buffer(Buffer_view& v, const Queue_property& q)
{
  if (not available(v, bytes(q.header)))
    return AVAILABLE_QUEUE_PROPERTY_HEADER;
  to_buffer(v, q.header);
  return to_buffer(v, q.payload, q.header.property);
}

Error_condition 
from_buffer(Buffer_view& v, Queue_property& q)
{
  if (not available(v, bytes(q.header)))
    return AVAILABLE_QUEUE_PROPERTY_HEADER;  
  from_buffer(v, q.header);

  // Length sanity check.
  if (q.header.length < bytes(q.header))
    return BAD_QUEUE_PROPERTY_LENGTH;

  // Validate the type code.
  if (not is_valid(q.header.property))
    return BAD_QUEUE_PROPERTY;

  // q.payload = Queue_property::Payload() with q.header.property
  Queue_property::Payload p;
  construct(p, q.header.property);
  assign(q.payload, std::move(p), q.header.property);
  
  // Ensure that we can constrain the view.
  std::size_t n = q.header.length - bytes(q.header);
  if (remaining(v) < n)
    return AVAILABLE_QUEUE_PROPERTY_PAYLOAD;

  // Try reading the payload, updating the view on success.
  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, q.payload, q.header.property))
    return err;
  
  if (not update(v, c))
    return EXCESS_QUEUE_PROPERTY;

  return SUCCESS;
}

std::string
to_string(const Queue_property& q, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Queue Property");

  ss << to_string(q.header, f) << "\n";
  if (is_valid(q.header.property))
    ss << to_string(q.payload, f,q.header.property) << "\n";
  else
    ss << "Malformed payload\n";

  close_block(ss, f, "Queue Property");
  return ss.str();
}


// -------------------------------------------------------------------------- //
// Queue

Error_condition
to_buffer(Buffer_view& v, const Queue& q) {
  if(not available(v,bytes(q)))
    return AVAILABLE_QUEUE;
  to_buffer(v, q.queue_id);
  to_buffer(v, q.length);
  pad(v, 2);
  return to_buffer(v, q.properties);
}

Error_condition
from_buffer(Buffer_view& v, Queue& q) {
  if(not available(v,bytes(q)))
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
// Queue_get_config_response

Error_condition 
to_buffer(Buffer_view& v, const Queue_get_config_res& qgcr) {
  if (not available(v, bytes(qgcr)))
    return AVAILABLE_QUEUE_GET_CONFIG_RES;
  to_buffer(v, qgcr.port);
  pad(v, 6);
  return to_buffer(v, qgcr.queues);
}

Error_condition 
from_buffer(Buffer_view& v, Queue_get_config_res& r) {
  if (not available(v, bytes(r)))
    return AVAILABLE_QUEUE_GET_CONFIG_RES;
  from_buffer(v, r.port);
  pad(v, 6);
  return from_buffer(v, r.queues);
}

std::string 
to_string(const Queue_get_config_res& qgcr, Formatter& f) 
{
  std::stringstream ss;
  open_block(ss, f, "QueueGetConfigRes");
  nvp_to_string(ss, f, "Port", qgcr.port);
  ss << to_string(qgcr.queues, f);
  close_block(ss, f, "QueueGetConfigReq");
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
  case VENDOR: new (&p.data.vendor) Vendor(); break;
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
  case PORT_MOD: new (&p.data.port_mod) Port_mod(); break;
  case STATS_REQ: new (&p.data.stats_req) Stats_req(); break;
  case STATS_RES: new (&p.data.stats_res) Stats_res(); break;
  case BARRIER_REQ: new (&p.data.barrier_req) Barrier_req(); break;
  case BARRIER_RES: new (&p.data.barrier_res) Barrier_res(); break;
  case QUEUE_GET_CONFIG_REQ: new (&p.data.queue_get_config_req) Queue_get_config_req(); break;
  case QUEUE_GET_CONFIG_RES: new (&p.data.queue_get_config_res) Queue_get_config_res(); break;
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
  case ECHO_REQ: new (&p.data.echo_req) Echo_req(std::move(x.data.echo_req)); 
    break;
  case ECHO_RES: new (&p.data.echo_res) Echo_res(std::move(x.data.echo_res)); 
    break;
  case VENDOR: new (&p.data.vendor) Vendor(std::move(x.data.vendor)); break;
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
  case PORT_MOD: 
    new (&p.data.port_mod) Port_mod(std::move(x.data.port_mod)); break;
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
  case VENDOR: new (&p.data.vendor) Vendor(x.data.vendor); break;
  case FEATURE_REQ: new (&p.data.feature_req) Feature_req(x.data.feature_req); 
    break;
  case FEATURE_RES: new (&p.data.feature_res) Feature_res(x.data.feature_res); 
    break;
  case GET_CONFIG_REQ: 
    new (&p.data.get_config_req) Get_config_req(x.data.get_config_req); break;
  case GET_CONFIG_RES: 
    new (&p.data.get_config_res) Get_config_res(x.data.get_config_res); break;
  case SET_CONFIG: new (&p.data.set_config) Set_config(x.data.set_config); 
    break;
  case PACKET_IN: new (&p.data.packet_in) Packet_in(x.data.packet_in); break;
  case FLOW_REMOVED: 
    new (&p.data.flow_removed) Flow_removed(x.data.flow_removed); break;
  case PORT_STATUS: new (&p.data.port_status) Port_status(x.data.port_status); 
    break;
  case PACKET_OUT: new (&p.data.packet_out) Packet_out(x.data.packet_out); 
    break;
  case FLOW_MOD: new (&p.data.flow_mod) Flow_mod(x.data.flow_mod); break;
  case PORT_MOD: new (&p.data.port_mod) Port_mod(x.data.port_mod); break;
  case STATS_REQ: new (&p.data.stats_req) Stats_req(x.data.stats_req); break;
  case STATS_RES: new (&p.data.stats_res) Stats_res(x.data.stats_res); break;
  case BARRIER_REQ: new (&p.data.barrier_req) Barrier_req(x.data.barrier_req); 
    break;
  case BARRIER_RES: new (&p.data.barrier_res) Barrier_res(x.data.barrier_res); 
    break;
  case QUEUE_GET_CONFIG_REQ: 
    new (&p.data.queue_get_config_req) 
        Queue_get_config_req(x.data.queue_get_config_req); break;
  case QUEUE_GET_CONFIG_RES: 
    new (&p.data.queue_get_config_res) 
        Queue_get_config_res(x.data.queue_get_config_res); break;
  default: variant_error(t);
  }
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
  case VENDOR: p.data.vendor = std::move(x.data.vendor); break;
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
  case PORT_MOD: p.data.port_mod = std::move(x.data.port_mod); break;
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
  case VENDOR: p.data.vendor = x.data.vendor; break;
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
  case PORT_MOD: p.data.port_mod = x.data.port_mod; break;
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
  case VENDOR: p.data.vendor.~Vendor(); break;
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
  case PORT_MOD: p.data.port_mod.~Port_mod(); break;
  case STATS_REQ: p.data.stats_req.~Stats_req(); break;
  case STATS_RES: p.data.stats_res.~Stats_res(); break;
  case BARRIER_REQ: p.data.barrier_req.~Barrier_req(); break;
  case BARRIER_RES: p.data.barrier_res.~Barrier_res(); break;
  case QUEUE_GET_CONFIG_REQ: p.data.queue_get_config_req.~Queue_get_config_req(); break;
  case QUEUE_GET_CONFIG_RES: p.data.queue_get_config_res.~Queue_get_config_res(); break;
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
  case VENDOR: return a.data.vendor == b.data.vendor;
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
  case PORT_MOD: return a.data.port_mod == b.data.port_mod;
  case STATS_REQ: return a.data.stats_req == b.data.stats_req;
  case STATS_RES: return a.data.stats_res == b.data.stats_res;
  case BARRIER_REQ: return a.data.barrier_req == b.data.barrier_req;
  case BARRIER_RES: return a.data.barrier_res == b.data.barrier_res;
  case QUEUE_GET_CONFIG_REQ: return a.data.queue_get_config_req == b.data.queue_get_config_req;
  case QUEUE_GET_CONFIG_RES: return a.data.queue_get_config_res == b.data.queue_get_config_res;
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
  case VENDOR: return bytes(p.data.vendor);
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
  case PORT_MOD: return bytes(p.data.port_mod);
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
  case VENDOR: return is_valid(p.data.vendor);
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
  case PORT_MOD: return is_valid(p.data.port_mod);
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
  case VENDOR: return to_buffer(v, p.data.vendor);
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
  case PORT_MOD: return to_buffer(v, p.data.port_mod);
  case STATS_REQ: return to_buffer(v, p.data.stats_req);
  case STATS_RES: return to_buffer(v, p.data.stats_res);
  case BARRIER_REQ: return to_buffer(v, p.data.barrier_req);
  case BARRIER_RES: return to_buffer(v, p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ: return to_buffer(v, p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES: return to_buffer(v, p.data.queue_get_config_res);
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
  case VENDOR: return from_buffer(v, p.data.vendor);
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
  case PORT_MOD: return from_buffer(v, p.data.port_mod);
  case STATS_REQ: return from_buffer(v, p.data.stats_req);
  case STATS_RES: return from_buffer(v, p.data.stats_res);
  case BARRIER_REQ: return from_buffer(v, p.data.barrier_req);
  case BARRIER_RES: return from_buffer(v, p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ: return from_buffer(v, p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES: return from_buffer(v, p.data.queue_get_config_res);
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
  case VENDOR: return to_string(p.data.vendor, fmt);
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
  case PORT_MOD: return to_string(p.data.port_mod, fmt);
  case STATS_REQ: return to_string(p.data.stats_req, fmt);
  case STATS_RES: return to_string(p.data.stats_res, fmt);
  case BARRIER_REQ: return to_string(p.data.barrier_req, fmt);
  case BARRIER_RES: return to_string(p.data.barrier_res, fmt);
  case QUEUE_GET_CONFIG_REQ: return to_string(p.data.queue_get_config_req, fmt);
  case QUEUE_GET_CONFIG_RES: return to_string(p.data.queue_get_config_res, fmt);
  default: variant_error(t);
  }
}


// -------------------------------------------------------------------------- //
// Header

Error_condition
to_buffer(Buffer_view& v, const Header& h) {
  to_buffer(v, h.version);
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  to_buffer(v, h.xid);
  return SUCCESS;
}

Error_condition 
from_buffer(Buffer_view& v, Header& h) {
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

  // Length sanity check.
  if (m.header.length < bytes(m.header))
    return BAD_MESSAGE_LENGTH;

  // Check that the message type is valid.
  if (Error_decl err = is_valid(m.header.type))
    return err;

  // m.payload = Payload() with m.header.type
  Payload p;
  construct(p, m.header.type);
  assign(m.payload, std::move(p), m.header.type);

  // Ensure that sufficient bytes to constrain the view.
  std::size_t n = m.header.length - bytes(m.header);
  if (not available(v, n))
    return AVAILABLE_PAYLOAD;

  // Read the payload and update the view.
  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, m.payload, m.header.type))
    return err;
  
  // Check that we don't have excess bytes after reading
  // the constrained view.
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

} // namespace v1_0
} // namesapce ofp
} // namespace flog
