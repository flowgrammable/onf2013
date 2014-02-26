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
namespace v1_3_1 {

std::string
to_string(Version_type t)
{
  if (t == 4)
    return "1.3.1";
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

  case MULTIPART_REQ: return "MultipartReq";
  case MULTIPART_RES: return "MultipartRes";
  case BARRIER_REQ: return "BarrierReq";
  case BARRIER_RES: return "BarrierRes";

  case QUEUE_GET_CONFIG_REQ: return "QueueGetConfigReq";
  case QUEUE_GET_CONFIG_RES: return "QueueGetConfigRes";

  case ROLE_REQ: return "RoleReq";
  case ROLE_RES: return "RoleRes";

  case GET_ASYNC_REQ: return "GetAsyncReq";
  case GET_ASYNC_RES: return "GetAsyncRes";
  case SET_ASYNC: return "SetAsync";

  case METER_MOD: return "MeterMod";

  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Hello element type

std::string
to_string(Hello_element_type t)
{
  switch(t) {
  case VERSIONBITMAP: return "VERSIONBITMAP";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Hello element version bitmap

std::string
to_string(const Hello_element_version_bitmap& hevb, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Hello Element Version Bitmap");

  ss << to_string(hevb.bitmaps, f);

  close_block(ss, f, "Hello Element Version Bitmap");
  return ss.str();
}

Error_condition
to_buffer(Buffer_view& v, const Hello_element_version_bitmap& hevb)
{
  if (not available(v, bytes(hevb)))
    return AVAILABLE_HELLO_ELEMENT_VERSION_BITMAP;
  return to_buffer(v, hevb.bitmaps);
}

Error_condition
from_buffer(Buffer_view& v, Hello_element_version_bitmap& hevb)
{
  if (not available(v, bytes(hevb)))
    return AVAILABLE_HELLO_ELEMENT_VERSION_BITMAP;
  return from_buffer(v, hevb.bitmaps);
}

// -------------------------------------------------------------------------- //
// Hello element payload

void
construct(Hello_element_payload& p, Hello_element_type t)
{
  p.init = true;
  switch (t) {
  case VERSIONBITMAP:
    new (&p.data.version_bitmap) Hello_element_version_bitmap(); break;
  default: variant_error(t);
  }
}

void
construct(Hello_element_payload& p, const Hello_element_payload&& x,
          Hello_element_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch (t) {
  case VERSIONBITMAP:
    new (&p.data.version_bitmap)
        Hello_element_version_bitmap(std::move(x.data.version_bitmap)); break;
  default: variant_error(t);
  }
}

void
construct(Hello_element_payload& p, const Hello_element_payload& x,
          Hello_element_type t)
{
  p.init = x.init;
  if (not p.init)
    return;
  switch (t) {
  case VERSIONBITMAP:
    new (&p.data.version_bitmap)
        Hello_element_version_bitmap(x.data.version_bitmap); break;
  default: variant_error(t);
  }
}

void
destroy(Hello_element_payload& p, Hello_element_type t)
{
  switch (t) {
  case VERSIONBITMAP: p.data.version_bitmap.~Hello_element_version_bitmap(); break;
  default: return;
  }
}

Hello_element_payload&
assign(Hello_element_payload& a, const Hello_element_payload&& b,
       Hello_element_type t)
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
  
  switch (t) {
    case VERSIONBITMAP:
      a.data.version_bitmap = std::move(b.data.version_bitmap); break;
  default: variant_error(t);
  }
  return a;
}

Hello_element_payload&
assign(Hello_element_payload& a, const Hello_element_payload& b,
       Hello_element_type t)
{
  if (&a == &b)
    return a;
  
  if (not a) {
      construct(a,b,t);
      return a;
  }
  
  a.init = b.init;
  if (not a) {
    destroy(a, t);
    return a;
  }
  
  switch (t) {
  case VERSIONBITMAP: a.data.version_bitmap = b.data.version_bitmap; break;
  default: variant_error(t);
  }
  return a;
}

bool
equal(const Hello_element_payload& a, const Hello_element_payload& b,
      Hello_element_type t1, Hello_element_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case VERSIONBITMAP: return a.data.version_bitmap == b.data.version_bitmap;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Hello_element_payload& p, Hello_element_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case VERSIONBITMAP: return bytes(p.data.version_bitmap);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Hello_element_payload& p, const Hello_element_type t)
{
  if (not p)
    return BAD_HELLO_ELEMENT_INIT;
  switch (t) {
  case VERSIONBITMAP: return is_valid(p.data.version_bitmap);
  default: variant_error(t);
  }
  return BAD_HELLO_ELEMENT;
}

Error_condition
to_buffer(Buffer_view& v, const Hello_element_payload& p, const Hello_element_type t)
{
  assert(p);
  switch (t) {
  case VERSIONBITMAP: return to_buffer(v, p.data.version_bitmap);
  default: variant_error(t);
  }
  return BAD_HELLO_ELEMENT;
}

Error_condition
from_buffer(Buffer_view& v, Hello_element_payload& p, Hello_element_type t)
{
  assert(p);
  switch (t) {
  case VERSIONBITMAP: return from_buffer(v, p.data.version_bitmap);
  default: variant_error(t);
  }
  return BAD_HELLO_ELEMENT;
}

std::string
to_string(const Hello_element_payload& p, Formatter& fmt, Hello_element_type t)
{
  assert(p);
  switch (t) {
  case VERSIONBITMAP: return to_string(p.data.version_bitmap, fmt);
  default: variant_error(t);
  }
  return "";
}

void construct(Hello_element_payload& p, 
               const Hello_element_version_bitmap& bm) {
  new (&p.data.version_bitmap) Hello_element_version_bitmap{bm};
}
// -------------------------------------------------------------------------- //
// Hello element header

std::string
to_string(const Hello_element_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Hello Element Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);

  close_block(ss, f, "Hello_element Hdr");
  return ss.str();
}

Error_condition
to_buffer(Buffer_view& v, const Hello_element_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Hello_element_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.length);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Hello element

Error_condition
to_buffer(Buffer_view& v, const Hello_element& he)
{
  if (not available(v, bytes(he.header)))
    return AVAILABLE_HELLO_ELEMENT_HEADER;
  to_buffer(v, he.header);
  return to_buffer(v, he.payload, he.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Hello_element& he)
{
  if (not available(v, bytes(he.header)))
    return AVAILABLE_HELLO_ELEMENT_HEADER;
  from_buffer(v, he.header);

  if (he.header.length < bytes(he.header))
    return BAD_HELLO_ELEMENT_LENGTH;

  if (Error_decl err = is_valid(he.header.type))
    return err;

  Hello_element::Payload p;
  construct(p, he.header.type);
  assign(he.payload, std::move(p), he.header.type);

  std::size_t n = he.header.length - bytes(he.header);
  if (remaining(v) < n)
    return AVAILABLE_HELLO_ELEMENT_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, he.payload, he.header.type))
    return err;
  
  if (not update(v, c))
    return EXCESS_HELLO_ELEMENT;
  
  return SUCCESS;
}

std::string
to_string(const Hello_element& he, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Hello Element");

  ss << to_string(he.header, f);
  if (is_valid(he.header))
    ss << to_string(he.payload, f, he.header.type);

  close_block(ss, f, "Hello Element");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Hello

Error_condition
to_buffer(Buffer_view& v, const Hello& h)
{
  if (not available(v, bytes(h)))
    return AVAILABLE_HELLO;

  return to_buffer(v, h.elements);
}

Error_condition
from_buffer(Buffer_view& v, Hello& h)
{
  if (not available(v, bytes(h)))
    return AVAILABLE_HELLO;

  return from_buffer(v, h.elements);
}

std::string
to_string(const Hello& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Hello");

  ss << to_string(h.elements, f);

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
  to_buffer(v, e.code);

  if (e.type == Error::EXPERIMENTER) {
    to_buffer(v, e.experimenter_id);
  }

  to_buffer(v, e.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Error& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_ERROR;
  from_buffer(v, e.type);
  from_buffer(v, e.code);

  if (e.type == Error::EXPERIMENTER) {
    from_buffer(v, e.experimenter_id);
  }

  from_buffer(v, e.data);
  return SUCCESS;
}

std::string
to_string(const Error& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Error");
  nvp_to_string(ss, f, "Type", to_string(e.type), int(e.type));
  if (e.type != Error::EXPERIMENTER) {
    nvp_to_string(ss, f, "Type", to_string(e.type, e.code), int(e.code));
  }
  else {
    nvp_to_string(ss, f, "Experimenter Type", e.code);
    nvp_to_string(ss, f, "Experimenter ID", e.experimenter_id);
  }
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
  case Error::ROLE_REQUEST_FAILED: return "RoleRequest Failed";
  case Error::METER_MOD_FAILED: return "MeterMod Failed";
  case Error::TABLE_FEATURES_FAILED: return "TableFeatures Failed";
  case Error::EXPERIMENTER: return "Experimenter";
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
  case Error::BR_BAD_EXP_TYPE: return "Bad Subtype";
  case Error::BR_EPERM: return "EPerm";
  case Error::BR_BAD_LEN: return "Bad Length";
  case Error::BR_BUFFER_EMPTY: return "Buffer Empty";
  case Error::BR_BUFFER_UNKNOWN: return "Buffer Unknown";
  case Error::BR_BAD_TABLE_ID: return "Bad Table ID";
  case Error::BR_IS_SLAVE: return "Controller in slave mode";
  case Error::BR_BAD_PORT: return "Bad Port";
  case Error::BR_BAD_PACKET: return "Bad Packet";
  case Error::BR_MULTIPART_BUFFER_OVERFLOW:
    return "Multipart buffer overflow";
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
  case Error::BA_BAD_SET_TYPE: return "Bad SetType";
  case Error::BA_BAD_SET_LEN: return "Bad SetLen";
  case Error::BA_BAD_SET_ARGUMENT: return "Bad SetArgument";
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
  case Error::BI_BAD_EXPERIMENTER: return "Bad Experimenter";
  case Error::BI_BAD_EXP_TYPE: return "Bad Experimenter Type";
  case Error::BI_BAD_LEN: return "Bad Len";
  case Error::BI_EPERM: return "EPerm";
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
  case Error::BM_BAD_MASK: return "Bad Mask";
  case Error::BM_BAD_PREREQ: return "Bad Prerequisite";
  case Error::BM_DUP_FIELD: return "Duplicated Field";
  case Error::BM_EPERM: return "EPerm";
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
  case Error::FMF_BAD_FLAGS: return "Bad Flags";
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
  case Error::GMF_CHAINED_GROUP: return "Chained Group";
  case Error::GMF_BAD_TYPE: return "Bad Type";
  case Error::GMF_BAD_COMMAND: return "Bad Command";
  case Error::GMF_BAD_BUCKET: return "Bad Bucket";
  case Error::GMF_BAD_WATCH: return "Bad Watch";
  case Error::GMF_EPERM: return "EPerm";
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
  case Error::PMF_EPERM: return "EPerm";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Table_mod_failed tmf)
{
  switch(tmf) {
  case Error::TMF_BAD_TABLE: return "Bad Table";
  case Error::TMF_BAD_CONFIG: return "Bad Config";
  case Error::TMF_EPERM: return "EPerm";
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
  case Error::SCF_EPERM: return "EPerm";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Role_request_failed rrf)
{
  switch(rrf) {
  case Error::RRF_STALE: return "Stale";
  case Error::RRF_UNSUP: return "Unsupported";
  case Error::RRF_BAD_ROLE: return "Bad Role";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Meter_mod_failed mmf)
{
  switch(mmf) {
  case Error::MMF_UNKNOWN: return "Unknown";
  case Error::MMF_METER_EXISTS: return "Meter Exists";
  case Error::MMF_INVALID_METER: return "Invalid Meter";
  case Error::MMF_UNKNOWN_METER: return "Unknown Meter";
  case Error::MMF_BAD_COMMAND: return "Bad Command";
  case Error::MMF_BAD_FLAGS: return "Bad Flags";
  case Error::MMF_BAD_RATE: return "Bad Rate";
  case Error::MMF_BAD_BURST: return "Bad Burst";
  case Error::MMF_BAD_BAND: return "Bad Band";
  case Error::MMF_BAD_BAND_VALUE: return "Bad Band Value";
  case Error::MMF_OUT_OF_METERS: return "Out of Meters";
  case Error::MMF_OUT_OF_BANDS: return "out of Bands";
  default: return "Unknown";
  }
}

std::string
to_string(Error::Table_features_failed tff)
{
  switch(tff) {
  case Error::TFF_BAD_TABLE: return "Bad Table";
  case Error::TFF_BAD_METADATA: return "Bad Metadata";
  case Error::TFF_BAD_TYPE: return "Bad Type";
  case Error::TFF_BAD_LENGTH: return "Bad Length";
  case Error::TFF_BAD_ARGUMENT: return "Bad Argument";
  case Error::TFF_PERMISSIONS_ERROR: return "Permissions Error";
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
  case Error::ROLE_REQUEST_FAILED: return to_string(c.rrf);
  case Error::METER_MOD_FAILED: return to_string(c.mmf);
  case Error::TABLE_FEATURES_FAILED: return to_string(c.tff);
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
  to_buffer(v, e.experimenter_type);
  to_buffer(v, e.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Experimenter& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_EXPERIMENTER;
  from_buffer(v, e.experimenter_id);
  from_buffer(v, e.experimenter_type);
  from_buffer(v, e.data);
  return SUCCESS;
}

std::string
to_string(const Experimenter& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Experimenter");

  nvp_to_string(ss, f, "Experimenter ID", e.experimenter_id);
  nvp_to_string(ss, f, "Experimenter Type", e.experimenter_type);
  nvp_to_string(ss, f, "Data bytes", bytes(e.data));

  close_block(ss, f, "Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM_entry_field

std::string
to_string(const OXM_entry_field oef)
{
  switch(oef) {
  case OXM_entry_field::OXM_EF_IN_PORT: return "Ingress Port";
  case OXM_entry_field::OXM_EF_IN_PHY_PORT: return "Physical Ingress Port";
  case OXM_entry_field::OXM_EF_METADATA: return "Metadata";
  case OXM_entry_field::OXM_EF_METADATA_MASK: return "Metadata Mask";
  case OXM_entry_field::OXM_EF_ETH_DST: return "Ethernet Dst";
  case OXM_entry_field::OXM_EF_ETH_DST_MASK: return "Ethernet Dst Mask";
  case OXM_entry_field::OXM_EF_ETH_SRC: return "Ethernet Src";
  case OXM_entry_field::OXM_EF_ETH_SRC_MASK: return "Ethernet Src Mask";
  case OXM_entry_field::OXM_EF_ETH_TYPE: return "Ethernet Type";
  case OXM_entry_field::OXM_EF_VLAN_VID: return "VLAN ID";
  case OXM_entry_field::OXM_EF_VLAN_VID_MASK: return "VLAN ID Mask";
  case OXM_entry_field::OXM_EF_VLAN_PCP: return "VLAN priority";
  case OXM_entry_field::OXM_EF_IP_DSCP: return "IP DSCP";
  case OXM_entry_field::OXM_EF_IP_ECN: return "IP ECN";
  case OXM_entry_field::OXM_EF_IP_PROTO: return "IP Protocol";
  case OXM_entry_field::OXM_EF_IPV4_SRC: return "IPV4 Src";
  case OXM_entry_field::OXM_EF_IPV4_SRC_MASK: return "IPV4 Src Mask";
  case OXM_entry_field::OXM_EF_IPV4_DST: return "IPV4 Dst";
  case OXM_entry_field::OXM_EF_IPV4_DST_MASK: return "IPV4 Dst Mask";
  case OXM_entry_field::OXM_EF_TCP_SRC: return "TCP Src";
  case OXM_entry_field::OXM_EF_TCP_DST: return "TCP Dst";
  case OXM_entry_field::OXM_EF_UDP_SRC: return "UDP Src";
  case OXM_entry_field::OXM_EF_UDP_DST: return "UDP Dst";
  case OXM_entry_field::OXM_EF_SCTP_SRC: return "SCTP Src";
  case OXM_entry_field::OXM_EF_SCTP_DST: return "SCTP Dst";
  case OXM_entry_field::OXM_EF_ICMPV4_TYPE: return "ICMPv4 Type";
  case OXM_entry_field::OXM_EF_ICMPV4_CODE: return "ICMPv4 Code";
  case OXM_entry_field::OXM_EF_ARP_OP: return "ARP Opcode";
  case OXM_entry_field::OXM_EF_ARP_SPA: return "ARP Src IPv4";
  case OXM_entry_field::OXM_EF_ARP_SPA_MASK: return "ARP Src IPv4 Mask";
  case OXM_entry_field::OXM_EF_ARP_TPA: return "ARP Target IPv4";
  case OXM_entry_field::OXM_EF_ARP_TPA_MASK: return "ARP Target IPv4 Mask";
  case OXM_entry_field::OXM_EF_ARP_SHA: return "ARP Src Hw Addr";
  case OXM_entry_field::OXM_EF_ARP_SHA_MASK: return "ARP Src Hw Addr Mask";
  case OXM_entry_field::OXM_EF_ARP_THA: return "ARP Target Hw Addr";
  case OXM_entry_field::OXM_EF_ARP_THA_MASK: return "ARP Target Hw Addr Mask";
  case OXM_entry_field::OXM_EF_IPV6_SRC: return "IPv6 Src";
  case OXM_entry_field::OXM_EF_IPV6_SRC_MASK: return "IPv6 Src Mask";
  case OXM_entry_field::OXM_EF_IPV6_DST: return "IPv6 Dst";
  case OXM_entry_field::OXM_EF_IPV6_DST_MASK: return "IPv6 Dst Mask";
  case OXM_entry_field::OXM_EF_IPV6_FLABEL: return "IPv6 Flow Label";
  case OXM_entry_field::OXM_EF_IPV6_FLABEL_MASK:
    return "IPv6 Flow Label MASK";
  case OXM_entry_field::OXM_EF_ICMPV6_TYPE: return "ICMPv6 Type";
  case OXM_entry_field::OXM_EF_ICMPV6_CODE: return "ICMPv6 Code";
  case OXM_entry_field::OXM_EF_IPV6_ND_TARGET: return "IPv6 ND Target";
  case OXM_entry_field::OXM_EF_IPV6_ND_SLL: return "IPv6 ND LL Src";
  case OXM_entry_field::OXM_EF_IPV6_ND_TLL: return "IPv6 ND LL Target";
  case OXM_entry_field::OXM_EF_MPLS_LABEL: return "MPLS Label";
  case OXM_entry_field::OXM_EF_MPLS_TC: return "MPLS TC";
  case OXM_entry_field::OXM_EF_MPLS_BOS: return "MPLS BoS";
  case OXM_entry_field::OXM_EF_PBB_ISID: return "PBB I-SID";
  case OXM_entry_field::OXM_EF_PBB_ISID_MASK: return "PBB I-SID Mask";
  case OXM_entry_field::OXM_EF_TUNNEL_ID: return "Tunnel ID";
  case OXM_entry_field::OXM_EF_TUNNEL_ID_MASK: return "Tunnel ID Mask";
  case OXM_entry_field::OXM_EF_IPV6_EXTHDR: return "Ipv6 Extension Header";
  case OXM_entry_field::OXM_EF_IPV6_EXTHDR_MASK:
    return "Ipv6 Extension Header Mask";
  default: return "UNKNOWN";
  }
}

// -------------------------------------------------------------------------- //
// OXM entry: Header

Error_condition
to_buffer(Buffer_view& v, const OXM_entry_header& h)
{
  if (not available(v, bytes(h)))
    return AVAILABLE_OXM_ENTRY_HEADER;
  to_buffer(v, h.oxm_class);
  to_buffer(v, h.field);
  //to_buffer(v, uint8_t((h.field << 1) | uint8_t(h.has_mask)));
  to_buffer(v, h.length);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, OXM_entry_header& h)
{
  if (not available(v, bytes(h)))
    return AVAILABLE_OXM_ENTRY_HEADER;
  from_buffer(v, h.oxm_class);
  //uint8_t temp_byte;
  //from_buffer(v, temp_byte);
  //h.field = OXM_entry_field(temp_byte >> 1);
  //h.has_mask = bool(temp_byte & 0x01);
  from_buffer(v, h.field);
  from_buffer(v, h.length);
  return SUCCESS;
}

std::string to_string(const OXM_entry_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM Hdr");
  nvp_to_string(ss, f, "Class", to_string(h.oxm_class), int(h.oxm_class));
  nvp_to_string(ss, f, "Field", to_string(h.field), int(h.field));
  //nvp_to_string(ss, f, "Has Mask", h.has_mask);
  nvp_to_string(ss, f, "Length", int(h.length));
  close_block(ss, f, "OXM Hdr");

  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IN_PORT

std::string
to_string(const OXM_entry_in_port& ip, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload in_port");

  nvp_to_string(ss, f, "Ingress Port", ip.value);

  close_block(ss, f, "OXM payload in_port");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IN_PHY_PORT

std::string
to_string(const OXM_entry_in_phy_port& ipp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload in_phy_port");

  nvp_to_string(ss, f, "Ingress Physical Port", ipp.value);

  close_block(ss, f, "OXM payload in_phy_port");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Metadata

std::string
to_string(const OXM_entry_metadata& m, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload metadata");

  nvp_to_string(ss, f, "Metadata", m.value);

  close_block(ss, f, "OXM payload metadata");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Metadata mask

std::string
to_string(const OXM_entry_metadata_mask& mm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload metadata mask");

  nvp_to_string(ss, f, "Metadata", mm.value);
  nvp_to_string(ss, f, "Metadata mask", mm.mask);

  close_block(ss, f, "OXM payload metadata mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Eth Dst

std::string
to_string(const OXM_entry_eth_dst& ed, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload eth_dst");

  nvp_to_string(ss, f, "Ethernet Dst", ethernet::to_string(ed.value));

  close_block(ss, f, "OXM payload eth_dst");
  return ss.str();
}

std::string
to_string(const OXM_entry_eth_dst_mask& edm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload eth_dst mask");

  nvp_to_string(ss, f, "Ethernet Dst", ethernet::to_string(edm.value));
  nvp_to_string(ss, f, "Ethernet Dst Mask", ethernet::to_string(edm.mask));

  close_block(ss, f, "OXM payload eth_dst mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ETH_SRC

std::string
to_string(const OXM_entry_eth_src& es, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload eth_src");

  nvp_to_string(ss, f, "Ethernet Src", ethernet::to_string(es.value));

  close_block(ss, f, "OXM payload eth_src");
  return ss.str();
}

std::string
to_string(const OXM_entry_eth_src_mask& esm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload eth_src mask");

  nvp_to_string(ss, f, "Ethernet Src", ethernet::to_string(esm.value));
  nvp_to_string(ss, f, "Ethernet Src Mask", ethernet::to_string(esm.mask));

  close_block(ss, f, "OXM payload eth_src mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ETH_TYPE

std::string
to_string(const OXM_entry_eth_type& et, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload eth_type");

  nvp_to_string(ss, f, "Ethernet Type", et.value);

  close_block(ss, f, "OXM payload eth_type");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: VLAN_VID

std::string
to_string(const OXM_entry_vlan_vid& vv, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload vlan_vid");

  nvp_to_string(ss, f, "VLAN VID", int(vv.value));

  close_block(ss, f, "OXM payload vlan_vid");
  return ss.str();
}

std::string
to_string(const OXM_entry_vlan_vid_mask& vvm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload vlan_vid mask");

  nvp_to_string(ss, f, "VLAN VID", int(vvm.value));
  nvp_to_string(ss, f, "VLAN VID mask", int(vvm.mask));

  close_block(ss, f, "OXM payload vlan_vid mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: VLAN_PCP

std::string
to_string(const OXM_entry_vlan_pcp& vp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload vlan_pcp");

  nvp_to_string(ss, f, "VLAN PCP", int(vp.value));

  close_block(ss, f, "OXM payload vlan_pcp");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IP_DSCP

std::string
to_string(const OXM_entry_ip_dscp& id, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ip_dscp");

  nvp_to_string(ss, f, "IP DSCP", int(id.value));

  close_block(ss, f, "OXM payload ip_dscp");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IP_ECN

std::string
to_string(const OXM_entry_ip_ecn& ie, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ip_ecn");

  nvp_to_string(ss, f, "IP ECN", int(ie.value));

  close_block(ss, f, "OXM payload ip_ecn");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IP_PROTO

std::string
to_string(const OXM_entry_ip_proto& ip, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ip_proto");

  nvp_to_string(ss, f, "IP PROTO", int(ip.value));

  close_block(ss, f, "OXM payload ip_proto");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV4_SRC

std::string
to_string(const OXM_entry_ipv4_src& is, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv4_src");

  nvp_to_string(ss, f, "IPv4 Src", ipv4::to_string(is.value));

  close_block(ss, f, "OXM payload ipv4_src");
  return ss.str();
}

std::string
to_string(const OXM_entry_ipv4_src_mask& ism, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv4_src mask");

  nvp_to_string(ss, f, "IPv4 Src", ipv4::to_string(ism.value));
  nvp_to_string(ss, f, "IPv4 Src Mask", ipv4::to_string(ism.mask));

  close_block(ss, f, "OXM payload ipv4_src mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV4_DST

std::string
to_string(const OXM_entry_ipv4_dst& id, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv4_dst");

  nvp_to_string(ss, f, "IPv4 Dst", ipv4::to_string(id.value));

  close_block(ss, f, "OXM payload ipv4_dst");
  return ss.str();
}

std::string
to_string(const OXM_entry_ipv4_dst_mask& idm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv4_dst mask");

  nvp_to_string(ss, f, "IPv4 Dst", ipv4::to_string(idm.value));
  nvp_to_string(ss, f, "IPv4 Dst Mask", ipv4::to_string(idm.mask));

  close_block(ss, f, "OXM payload ipv4_dst mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: TCP_SRC

std::string
to_string(const OXM_entry_tcp_src& ts, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload tcp_src");

  nvp_to_string(ss, f, "TCP Src", ts.value);

  close_block(ss, f, "OXM payload tcp_src");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: TCP_DST

std::string
to_string(const OXM_entry_tcp_dst& td, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload tcp_dst");

  nvp_to_string(ss, f, "TCP_DST", td.value);

  close_block(ss, f, "OXM payload tcp_dst");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: UDP_SRC

std::string
to_string(const OXM_entry_udp_src& us, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload udp_src");

  nvp_to_string(ss, f, "UDP Src", us.value);

  close_block(ss, f, "OXM payload udp_src");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: UDP_DST

std::string
to_string(const OXM_entry_udp_dst& ud, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload udp_dst");

  nvp_to_string(ss, f, "UDP Dst", ud.value);

  close_block(ss, f, "OXM payload udp_dst");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: SCTP_SRC

std::string
to_string(const OXM_entry_sctp_src& s, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload sctp_src");

  nvp_to_string(ss, f, "SCTP Src", s.value);

  close_block(ss, f, "OXM payload sctp_src");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: SCTP_DST

std::string
to_string(const OXM_entry_sctp_dst& sd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload sctp_dst");

  nvp_to_string(ss, f, "SCTP Dst", sd.value);

  close_block(ss, f, "OXM payload sctp_dst");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ICMPV4_TYPE

std::string
to_string(const OXM_entry_icmpv4_type& it, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload icmpv4_type");

  nvp_to_string(ss, f, "ICMPv4 Type", int(it.value));

  close_block(ss, f, "OXM payload icmpv4_type");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ICMPV4_CODE
std::string
to_string(const OXM_entry_icmpv4_code& ic, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload icmpv4_code");

  nvp_to_string(ss, f, "ICMPv4 Code", int(ic.value));

  close_block(ss, f, "OXM payload icmpv4_code");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ARP_OP

std::string
to_string(const OXM_entry_arp_op& ao, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_op");

  nvp_to_string(ss, f, "ARP Op", ao.value);

  close_block(ss, f, "OXM payload arp_op");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ARP_SPA

std::string
to_string(const OXM_entry_arp_spa& as, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_spa");

  nvp_to_string(ss, f, "ARP SPA", ipv4::to_string(as.value));

  close_block(ss, f, "OXM payload arp_spa");
  return ss.str();
}

std::string
to_string(const OXM_entry_arp_spa_mask& as, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_spa mask");

  nvp_to_string(ss, f, "ARP SPA", ipv4::to_string(as.value));
  nvp_to_string(ss, f, "ARP SPA Mask", ipv4::to_string(as.mask));

  close_block(ss, f, "OXM payload arp_spa mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ARP_TPA

std::string
to_string(const OXM_entry_arp_tpa& at, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_tpa");

  nvp_to_string(ss, f, "ARP TPA", ipv4::to_string(at.value));

  close_block(ss, f, "OXM payload arp_tpa");
  return ss.str();
}

std::string
to_string(const OXM_entry_arp_tpa_mask& atm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_tpa mask");

  nvp_to_string(ss, f, "ARP TPA", ipv4::to_string(atm.value));
  nvp_to_string(ss, f, "ARP TPA Mask", ipv4::to_string(atm.mask));

  close_block(ss, f, "OXM payload arp_tpa mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ARP_SHA

std::string
to_string(const OXM_entry_arp_sha& as, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_sha");

  nvp_to_string(ss, f, "ARP SHA", ethernet::to_string(as.value));

  close_block(ss, f, "OXM payload arp_sha");
  return ss.str();
}

std::string
to_string(const OXM_entry_arp_sha_mask& as, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_sha mask");

  nvp_to_string(ss, f, "ARP SHA", ethernet::to_string(as.value));
  nvp_to_string(ss, f, "ARP SHA Mask", ethernet::to_string(as.mask));

  close_block(ss, f, "OXM payload arp_sha mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ARP_THA

std::string
to_string(const OXM_entry_arp_tha& at, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_tha");

  nvp_to_string(ss, f, "ARP THA", ethernet::to_string(at.value));

  close_block(ss, f, "OXM payload arp_tha");
  return ss.str();
}

std::string
to_string(const OXM_entry_arp_tha_mask& atm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload arp_tha mask");

  nvp_to_string(ss, f, "ARP THA", ethernet::to_string(atm.value));
  nvp_to_string(ss, f, "ARP THA Mask", ethernet::to_string(atm.mask));

  close_block(ss, f, "OXM payload arp_tha mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV6_SRC

std::string
to_string(const OXM_entry_ipv6_src& is, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_src");

  nvp_to_string(ss, f, "IPv6 Src", ipv6::to_string(is.value));

  close_block(ss, f, "OXM payload ipv6_src");
  return ss.str();
}

std::string
to_string(const OXM_entry_ipv6_src_mask& ism, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_src mask");

  nvp_to_string(ss, f, "IPv6 Src", ipv6::to_string(ism.value));
  nvp_to_string(ss, f, "IPv6 Src Mask", ipv6::to_string(ism.mask));

  close_block(ss, f, "OXM payload ipv6_src mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV6_DST

std::string
to_string(const OXM_entry_ipv6_dst& id, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_dst");

  nvp_to_string(ss, f, "IPv6 Dst", ipv6::to_string(id.value));

  close_block(ss, f, "OXM payload ipv6_dst");
  return ss.str();
}

std::string
to_string(const OXM_entry_ipv6_dst_mask& idm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_dst mask");

  nvp_to_string(ss, f, "IPv6 Dst", ipv6::to_string(idm.value));
  nvp_to_string(ss, f, "IPv6 Dst", ipv6::to_string(idm.mask));

  close_block(ss, f, "OXM payload ipv6_dst mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV6_FLABEL

std::string
to_string(const OXM_entry_ipv6_flabel& i, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_flabel");

  nvp_to_string(ss, f, "IPv6 Flabel", i.value);

  close_block(ss, f, "OXM payload ipv6_flabel");
  return ss.str();
}

std::string
to_string(const OXM_entry_ipv6_flabel_mask& ifm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_flabel mask");

  nvp_to_string(ss, f, "IPv6 Flabel", ifm.value);
  nvp_to_string(ss, f, "IPv6 Flabel Mask", ifm.mask);

  close_block(ss, f, "OXM payload ipv6_flabel mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ICMPv6 type

std::string
to_string(const OXM_entry_icmpv6_type& it, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload icmpv6_type");

  nvp_to_string(ss, f, "ICMPv6 Type", int(it.value));

  close_block(ss, f, "OXM payload icmpv6_type");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: ICMPv6 code

std::string
to_string(const OXM_entry_icmpv6_code& ic, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload icmpv6_code");

  nvp_to_string(ss, f, "ICMPv6 Code", int(ic.value));

  close_block(ss, f, "OXM payload icmpv6_code");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV6_ND_TARGET

std::string
to_string(const OXM_entry_ipv6_nd_target& nt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_nd_target");

  nvp_to_string(ss, f, "IPv6 ND Target", ipv6::to_string(nt.value));

  close_block(ss, f, "OXM payload ipv6_nd_target");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV6_ND_SLL

std::string
to_string(const OXM_entry_ipv6_nd_sll& ins, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_nd_sll");

  nvp_to_string(ss, f, "IPv6 ND SLL", ethernet::to_string(ins.value));

  close_block(ss, f, "OXM payload ipv6_nd_sll");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPV6_ND_TLL

std::string
to_string(const OXM_entry_ipv6_nd_tll& nt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_nd_tll");

  nvp_to_string(ss, f, "IPv6 ND TLL", ethernet::to_string(nt.value));

  close_block(ss, f, "OXM payload ipv6_nd_tll");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: MPLS_LABEL

std::string
to_string(const OXM_entry_mpls_label& ml, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload mpls_label");

  nvp_to_string(ss, f, "MPLS Label", ml.value);

  close_block(ss, f, "OXM payload mpls_label");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: MPLS_TC

std::string
to_string(const OXM_entry_mpls_tc& mt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload mpls_tc");

  nvp_to_string(ss, f, "MPLS TC", int(mt.value));

  close_block(ss, f, "OXM payload mpls_tc");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: MPLS_BoS

std::string
to_string(const OXM_entry_mpls_bos& mb, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload mpls_bos");

  nvp_to_string(ss, f, "MPLS Bos", int(mb.value));

  close_block(ss, f, "OXM payload mpls_bos");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: PBB_ISID

Error_condition
to_buffer(Buffer_view& v, const OXM_entry_pbb_isid& pi)
{
  if (not available(v, bytes(pi)))
    return AVAILABLE_OXM_ENTRY_PBB_ISID;
  to_buffer(v, (uint8_t)(pi.value >> 16));
  to_buffer(v, (uint8_t)(pi.value >> 8));
  to_buffer(v, (uint8_t)pi.value);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, OXM_entry_pbb_isid& pi)
{
  if (not available(v, bytes(pi)))
    return AVAILABLE_OXM_ENTRY_PBB_ISID;
  uint8_t temp[3];
  get(v, temp, 3);
  pi.value = (temp[0] << 16) | (temp[1] << 8) | (temp[2]);
  return SUCCESS;
}

std::string
to_string(const OXM_entry_pbb_isid& pi, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload pbb_isid");

  nvp_to_string(ss, f, "PBB I-SID", int(pi.value));

  close_block(ss, f, "OXM payload pbb_isid");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: PBB_ISID mask

Error_condition
to_buffer(Buffer_view& v, const OXM_entry_pbb_isid_mask& pim)
{
  if (not available(v, bytes(pim)))
    return AVAILABLE_OXM_ENTRY_PBB_ISID_MASK;
  to_buffer(v, (uint8_t)(pim.value >> 16));
  to_buffer(v, (uint8_t)(pim.value >> 8));
  to_buffer(v, (uint8_t)pim.value);
  to_buffer(v, (uint8_t)(pim.mask >> 16));
  to_buffer(v, (uint8_t)(pim.mask >> 8));
  to_buffer(v, (uint8_t)pim.mask);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, OXM_entry_pbb_isid_mask& pim)
{
  if (not available(v, bytes(pim)))
    return AVAILABLE_OXM_ENTRY_PBB_ISID_MASK;
  uint8_t temp[3];
  get(v, temp, 3);
  pim.value = (temp[0] << 16) | (temp[1] << 8) | (temp[2]);
  get(v, temp, 3);
  pim.mask = (temp[0] << 16) | (temp[1] << 8) | (temp[2]);
  return SUCCESS;
}

std::string
to_string(const OXM_entry_pbb_isid_mask& pim, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload pbb_isid mask");

  nvp_to_string(ss, f, "PBB I-SID", int(pim.value));
  nvp_to_string(ss, f, "PBB I-SID Mask", int(pim.mask));

  close_block(ss, f, "OXM payload pbb_isid mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Tunnel ID

std::string
to_string(const OXM_entry_tunnel_id& ti, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload tunnel_id");

  nvp_to_string(ss, f, "Tunnel ID", int(ti.value));

  close_block(ss, f, "OXM payload tunnel_id");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Tunnel ID mask

std::string
to_string(const OXM_entry_tunnel_id_mask& tim, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload tunnel_id mask");

  nvp_to_string(ss, f, "Tunnel ID", int(tim.value));
  nvp_to_string(ss, f, "Tunnel ID Mask", int(tim.mask));

  close_block(ss, f, "OXM payload tunnel_id mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Ipv6 Extension header flags

std::string
to_string(Ipv6_exthdr_flags f)
{
  switch(f) {
  case NONEXT: return "NONEXT";
  case ESP: return "ESP";
  case AUTH: return "AUTH";
  case DEST: return "DEST";
  case FRAG: return "FRAG";
  case ROUTER: return "ROUTER";
  case HOP: return "HOP";
  case UNREP: return "UNREP";
  case UNSEQ: return "UNSEQ";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Ipv6 Extension header

Error_condition
to_buffer(Buffer_view& v, const OXM_entry_ipv6_exthdr& ie)
{
  if (not available(v, bytes(ie)))
    return AVAILABLE_OXM_ENTRY_IPV6_EXTHDR;
  to_buffer(v, ie.flag);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, OXM_entry_ipv6_exthdr& ie)
{
  if (not available(v, bytes(ie)))
    return AVAILABLE_OXM_ENTRY_IPV6_EXTHDR;
  from_buffer(v, ie.flag);
  return SUCCESS;
}

std::string
to_string(const OXM_entry_ipv6_exthdr& ie, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_exthdr");

  nvp_to_string(ss, f, "Flag", to_string(ie.flag), int(ie.flag));

  close_block(ss, f, "OXM payload ipv6_exthdr");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload: Ipv6 Extension header mask

Error_condition
to_buffer(Buffer_view& v, const OXM_entry_ipv6_exthdr_mask& iem)
{
  if (not available(v, bytes(iem)))
    return AVAILABLE_OXM_ENTRY_IPV6_EXTHDR_MASK;
  to_buffer(v, iem.flag);
  to_buffer(v, iem.mask);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, OXM_entry_ipv6_exthdr_mask& iem)
{
  if (not available(v, bytes(iem)))
    return AVAILABLE_OXM_ENTRY_IPV6_EXTHDR_MASK;
  from_buffer(v, iem.flag);
  from_buffer(v, iem.mask);
  return SUCCESS;
}

std::string
to_string(const OXM_entry_ipv6_exthdr_mask& iem, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM payload ipv6_exthdr mask");

  nvp_to_string(ss, f, "Flag", to_string(iem.flag), int(iem.flag));
  nvp_to_string(ss, f, "Mask", iem.mask);

  close_block(ss, f, "OXM payload ipv6_exthdr mask");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM entry payload

void
construct(OXM_entry_payload& a, OXM_entry_field f)
{
  a.init = true;
  switch (f) {
  case OXM_EF_IN_PORT: new (&a.data.in_port) OXM_entry_in_port(); break;
  case OXM_EF_IN_PHY_PORT:
    new (&a.data.in_phy_port) OXM_entry_in_phy_port(); break;
  case OXM_EF_METADATA: new (&a.data.metadata) OXM_entry_metadata(); break;
  case OXM_EF_METADATA_MASK:
    new (&a.data.metadata_mask) OXM_entry_metadata_mask(); break;
  case OXM_EF_ETH_DST: new (&a.data.eth_dst) OXM_entry_eth_dst(); break;
  case OXM_EF_ETH_DST_MASK:
    new (&a.data.eth_dst_mask) OXM_entry_eth_dst_mask(); break;
  case OXM_EF_ETH_SRC: new (&a.data.eth_src) OXM_entry_eth_src(); break;
  case OXM_EF_ETH_SRC_MASK:
    new (&a.data.eth_src_mask) OXM_entry_eth_src_mask(); break;
  case OXM_EF_ETH_TYPE: new (&a.data.eth_type) OXM_entry_eth_type(); break;
  case OXM_EF_VLAN_VID: new (&a.data.vlan_vid) OXM_entry_vlan_vid(); break;
  case OXM_EF_VLAN_VID_MASK:
    new (&a.data.vlan_vid_mask) OXM_entry_vlan_vid_mask(); break;
  case OXM_EF_VLAN_PCP: new (&a.data.vlan_pcp) OXM_entry_vlan_pcp(); break;
  case OXM_EF_IP_DSCP: new (&a.data.ip_dscp) OXM_entry_ip_dscp(); break;
  case OXM_EF_IP_ECN: new (&a.data.ip_ecn) OXM_entry_ip_ecn(); break;
  case OXM_EF_IP_PROTO: new (&a.data.ip_proto) OXM_entry_ip_proto(); break;
  case OXM_EF_IPV4_SRC: new (&a.data.ipv4_src) OXM_entry_ipv4_src(); break;
  case OXM_EF_IPV4_SRC_MASK:
    new (&a.data.ipv4_src_mask) OXM_entry_ipv4_src_mask(); break;
  case OXM_EF_IPV4_DST: new (&a.data.ipv4_dst) OXM_entry_ipv4_dst(); break;
  case OXM_EF_IPV4_DST_MASK:
    new (&a.data.ipv4_dst_mask) OXM_entry_ipv4_dst_mask(); break;
  case OXM_EF_TCP_SRC: new (&a.data.tcp_src) OXM_entry_tcp_src(); break;
  case OXM_EF_TCP_DST: new (&a.data.tcp_dst) OXM_entry_tcp_dst(); break;
  case OXM_EF_UDP_SRC: new (&a.data.udp_src) OXM_entry_udp_src(); break;
  case OXM_EF_UDP_DST: new (&a.data.udp_dst) OXM_entry_udp_dst(); break;
  case OXM_EF_SCTP_SRC: new (&a.data.sctp_src) OXM_entry_sctp_src(); break;
  case OXM_EF_SCTP_DST: new (&a.data.sctp_dst) OXM_entry_sctp_dst(); break;
  case OXM_EF_ICMPV4_TYPE:
    new (&a.data.icmpv4_type) OXM_entry_icmpv4_type(); break;
  case OXM_EF_ICMPV4_CODE:
    new (&a.data.icmpv4_code) OXM_entry_icmpv4_code(); break;
  case OXM_EF_ARP_OP: new (&a.data.arp_op) OXM_entry_arp_op(); break;
  case OXM_EF_ARP_SPA: new (&a.data.arp_spa) OXM_entry_arp_spa(); break;
  case OXM_EF_ARP_SPA_MASK:
    new (&a.data.arp_spa_mask) OXM_entry_arp_spa_mask(); break;
  case OXM_EF_ARP_TPA: new (&a.data.arp_tpa) OXM_entry_arp_tpa(); break;
  case OXM_EF_ARP_TPA_MASK:
    new (&a.data.arp_tpa_mask) OXM_entry_arp_tpa_mask(); break;
  case OXM_EF_ARP_SHA: new (&a.data.arp_sha) OXM_entry_arp_sha(); break;
  case OXM_EF_ARP_SHA_MASK:
    new (&a.data.arp_sha_mask) OXM_entry_arp_sha_mask(); break;
  case OXM_EF_ARP_THA: new (&a.data.arp_tha) OXM_entry_arp_tha(); break;
  case OXM_EF_ARP_THA_MASK:
    new (&a.data.arp_tha_mask) OXM_entry_arp_tha_mask(); break;
  case OXM_EF_IPV6_SRC: new (&a.data.ipv6_src) OXM_entry_ipv6_src(); break;
  case OXM_EF_IPV6_SRC_MASK:
    new (&a.data.ipv6_src_mask) OXM_entry_ipv6_src_mask(); break;
  case OXM_EF_IPV6_DST: new (&a.data.ipv6_dst) OXM_entry_ipv6_dst(); break;
  case OXM_EF_IPV6_DST_MASK:
    new (&a.data.ipv6_dst_mask) OXM_entry_ipv6_dst_mask(); break;
  case OXM_EF_IPV6_FLABEL:
    new (&a.data.ipv6_flabel) OXM_entry_ipv6_flabel(); break;
  case OXM_EF_IPV6_FLABEL_MASK:
    new (&a.data.ipv6_flabel_mask) OXM_entry_ipv6_flabel_mask(); break;
  case OXM_EF_ICMPV6_TYPE:
    new (&a.data.icmpv6_type) OXM_entry_icmpv6_type(); break;
  case OXM_EF_ICMPV6_CODE:
    new (&a.data.icmpv6_code) OXM_entry_icmpv6_code(); break;
  case OXM_EF_IPV6_ND_TARGET:
    new (&a.data.ipv6_nd_target) OXM_entry_ipv6_nd_target(); break;
  case OXM_EF_IPV6_ND_SLL:
    new (&a.data.ipv6_nd_sll) OXM_entry_ipv6_nd_sll(); break;
  case OXM_EF_IPV6_ND_TLL:
    new (&a.data.ipv6_nd_tll) OXM_entry_ipv6_nd_tll(); break;
  case OXM_EF_MPLS_LABEL:
    new (&a.data.mpls_label) OXM_entry_mpls_label(); break;
  case OXM_EF_MPLS_TC: new (&a.data.mpls_tc) OXM_entry_mpls_tc(); break;
  case OXM_EF_MPLS_BOS: new (&a.data.mpls_bos) OXM_entry_mpls_bos(); break;
  case OXM_EF_PBB_ISID: new (&a.data.pbb_isid) OXM_entry_pbb_isid(); break;
  case OXM_EF_PBB_ISID_MASK:
    new (&a.data.pbb_isid_mask) OXM_entry_pbb_isid_mask(); break;
  case OXM_EF_TUNNEL_ID: new (&a.data.tunnel_id) OXM_entry_tunnel_id(); break;
  case OXM_EF_TUNNEL_ID_MASK:
    new (&a.data.tunnel_id_mask) OXM_entry_tunnel_id_mask(); break;
  case OXM_EF_IPV6_EXTHDR:
    new (&a.data.ipv6_exthdr) OXM_entry_ipv6_exthdr(); break;
  case OXM_EF_IPV6_EXTHDR_MASK:
    new (&a.data.ipv6_exthdr_mask) OXM_entry_ipv6_exthdr_mask(); break;
  default: variant_error(f);
  }
}

void
construct(OXM_entry_payload& a, OXM_entry_payload&& b, OXM_entry_field f)
{
  a.init = b.init;
  if(not a)
    return;
  switch (f) {
  case OXM_EF_IN_PORT:
    new (&a.data.in_port) OXM_entry_in_port(std::move(b.data.in_port)); break;
  case OXM_EF_IN_PHY_PORT:
    new (&a.data.in_phy_port)
        OXM_entry_in_phy_port(std::move(b.data.in_phy_port)); break;
  case OXM_EF_METADATA:
    new (&a.data.metadata) OXM_entry_metadata(std::move(b.data.metadata));
    break;
  case OXM_EF_METADATA_MASK:
    new (&a.data.metadata_mask)
        OXM_entry_metadata_mask(std::move(b.data.metadata_mask)); break;
  case OXM_EF_ETH_DST:
    new (&a.data.eth_dst) OXM_entry_eth_dst(std::move(b.data.eth_dst)); break;
  case OXM_EF_ETH_DST_MASK:
    new (&a.data.eth_dst_mask)
        OXM_entry_eth_dst_mask(std::move(b.data.eth_dst_mask)); break;
  case OXM_EF_ETH_SRC:
    new (&a.data.eth_src) OXM_entry_eth_src(std::move(b.data.eth_src)); break;
  case OXM_EF_ETH_SRC_MASK:
    new (&a.data.eth_src_mask)
        OXM_entry_eth_src_mask(std::move(b.data.eth_src_mask)); break;
  case OXM_EF_ETH_TYPE:
    new (&a.data.eth_type) OXM_entry_eth_type(std::move(b.data.eth_type));
    break;
  case OXM_EF_VLAN_VID:
    new (&a.data.vlan_vid) OXM_entry_vlan_vid(std::move(b.data.vlan_vid));
    break;
  case OXM_EF_VLAN_VID_MASK:
    new (&a.data.vlan_vid_mask)
        OXM_entry_vlan_vid_mask(std::move(b.data.vlan_vid_mask)); break;
  case OXM_EF_VLAN_PCP:
    new (&a.data.vlan_pcp) OXM_entry_vlan_pcp(std::move(b.data.vlan_pcp));
    break;
  case OXM_EF_IP_DSCP:
    new (&a.data.ip_dscp) OXM_entry_ip_dscp(std::move(b.data.ip_dscp)); break;
  case OXM_EF_IP_ECN:
    new (&a.data.ip_ecn) OXM_entry_ip_ecn(std::move(b.data.ip_ecn)); break;
  case OXM_EF_IP_PROTO:
    new (&a.data.ip_proto) OXM_entry_ip_proto(std::move(b.data.ip_proto));
    break;
  case OXM_EF_IPV4_SRC:
    new (&a.data.ipv4_src) OXM_entry_ipv4_src(std::move(b.data.ipv4_src));
    break;
  case OXM_EF_IPV4_SRC_MASK:
    new (&a.data.ipv4_src_mask)
        OXM_entry_ipv4_src_mask(std::move(b.data.ipv4_src_mask)); break;
  case OXM_EF_IPV4_DST:
    new (&a.data.ipv4_dst) OXM_entry_ipv4_dst(std::move(b.data.ipv4_dst));
    break;
  case OXM_EF_IPV4_DST_MASK:
    new (&a.data.ipv4_dst_mask)
        OXM_entry_ipv4_dst_mask(std::move(b.data.ipv4_dst_mask)); break;
  case OXM_EF_TCP_SRC:
    new (&a.data.tcp_src) OXM_entry_tcp_src(std::move(b.data.tcp_src)); break;
  case OXM_EF_TCP_DST:
    new (&a.data.tcp_dst) OXM_entry_tcp_dst(std::move(b.data.tcp_dst)); break;
  case OXM_EF_UDP_SRC:
    new (&a.data.udp_src) OXM_entry_udp_src(std::move(b.data.udp_src)); break;
  case OXM_EF_UDP_DST:
    new (&a.data.udp_dst) OXM_entry_udp_dst(std::move(b.data.udp_dst)); break;
  case OXM_EF_SCTP_SRC:
    new (&a.data.sctp_src) OXM_entry_sctp_src(std::move(b.data.sctp_src));
    break;
  case OXM_EF_SCTP_DST:
    new (&a.data.sctp_dst) OXM_entry_sctp_dst(std::move(b.data.sctp_dst));
    break;
  case OXM_EF_ICMPV4_TYPE:
    new (&a.data.icmpv4_type)
        OXM_entry_icmpv4_type(std::move(b.data.icmpv4_type)); break;
  case OXM_EF_ICMPV4_CODE:
    new (&a.data.icmpv4_code)
        OXM_entry_icmpv4_code(std::move(b.data.icmpv4_code)); break;
  case OXM_EF_ARP_OP:
    new (&a.data.arp_op) OXM_entry_arp_op(std::move(b.data.arp_op)); break;
  case OXM_EF_ARP_SPA:
    new (&a.data.arp_spa) OXM_entry_arp_spa(std::move(b.data.arp_spa)); break;
  case OXM_EF_ARP_SPA_MASK:
    new (&a.data.arp_spa_mask)
        OXM_entry_arp_spa_mask(std::move(b.data.arp_spa_mask)); break;
  case OXM_EF_ARP_TPA:
    new (&a.data.arp_tpa) OXM_entry_arp_tpa(std::move(b.data.arp_tpa)); break;
  case OXM_EF_ARP_TPA_MASK:
    new (&a.data.arp_tpa_mask)
        OXM_entry_arp_tpa_mask(std::move(b.data.arp_tpa_mask)); break;
  case OXM_EF_ARP_SHA:
    new (&a.data.arp_sha) OXM_entry_arp_sha(std::move(b.data.arp_sha)); break;
  case OXM_EF_ARP_SHA_MASK:
    new (&a.data.arp_sha_mask)
        OXM_entry_arp_sha_mask(std::move(b.data.arp_sha_mask)); break;
  case OXM_EF_ARP_THA:
    new (&a.data.arp_tha) OXM_entry_arp_tha(std::move(b.data.arp_tha)); break;
  case OXM_EF_ARP_THA_MASK:
    new (&a.data.arp_tha_mask)
        OXM_entry_arp_tha_mask(std::move(b.data.arp_tha_mask)); break;
  case OXM_EF_IPV6_SRC:
    new (&a.data.ipv6_src) OXM_entry_ipv6_src(std::move(b.data.ipv6_src));
    break;
  case OXM_EF_IPV6_SRC_MASK:
    new (&a.data.ipv6_src_mask)
        OXM_entry_ipv6_src_mask(std::move(b.data.ipv6_src_mask)); break;
  case OXM_EF_IPV6_DST:
    new (&a.data.ipv6_dst) OXM_entry_ipv6_dst(std::move(b.data.ipv6_dst));
    break;
  case OXM_EF_IPV6_DST_MASK:
    new (&a.data.ipv6_dst_mask)
        OXM_entry_ipv6_dst_mask(std::move(b.data.ipv6_dst_mask)); break;
  case OXM_EF_IPV6_FLABEL:
    new (&a.data.ipv6_flabel)
        OXM_entry_ipv6_flabel(std::move(b.data.ipv6_flabel)); break;
  case OXM_EF_IPV6_FLABEL_MASK:
    new (&a.data.ipv6_flabel_mask)
         OXM_entry_ipv6_flabel_mask(std::move(b.data.ipv6_flabel_mask)); break;
  case OXM_EF_ICMPV6_TYPE:
    new (&a.data.icmpv6_type)
        OXM_entry_icmpv6_type(std::move(b.data.icmpv6_type)); break;
  case OXM_EF_ICMPV6_CODE:
    new (&a.data.icmpv6_code)
        OXM_entry_icmpv6_code(std::move(b.data.icmpv6_code)); break;
  case OXM_EF_IPV6_ND_TARGET:
    new (&a.data.ipv6_nd_target)
         OXM_entry_ipv6_nd_target(std::move(b.data.ipv6_nd_target)); break;
  case OXM_EF_IPV6_ND_SLL:
    new (&a.data.ipv6_nd_sll)
        OXM_entry_ipv6_nd_sll(std::move(b.data.ipv6_nd_sll)); break;
  case OXM_EF_IPV6_ND_TLL:
    new (&a.data.ipv6_nd_tll)
        OXM_entry_ipv6_nd_tll(std::move(b.data.ipv6_nd_tll)); break;
  case OXM_EF_MPLS_LABEL:
    new (&a.data.mpls_label)
        OXM_entry_mpls_label(std::move(b.data.mpls_label)); break;
  case OXM_EF_MPLS_TC:
    new (&a.data.mpls_tc) OXM_entry_mpls_tc(std::move(b.data.mpls_tc)); break;
  case OXM_EF_MPLS_BOS:
    new (&a.data.mpls_bos) OXM_entry_mpls_bos(std::move(b.data.mpls_bos));
    break;
  case OXM_EF_PBB_ISID:
    new (&a.data.pbb_isid) OXM_entry_pbb_isid(std::move(b.data.pbb_isid));
    break;
  case OXM_EF_PBB_ISID_MASK:
    new (&a.data.pbb_isid_mask)
        OXM_entry_pbb_isid_mask(std::move(b.data.pbb_isid_mask)); break;
  case OXM_EF_TUNNEL_ID:
    new (&a.data.tunnel_id) OXM_entry_tunnel_id(std::move(b.data.tunnel_id));
    break;
  case OXM_EF_TUNNEL_ID_MASK:
    new (&a.data.tunnel_id_mask)
        OXM_entry_tunnel_id_mask(std::move(b.data.tunnel_id_mask)); break;
  case OXM_EF_IPV6_EXTHDR:
    new (&a.data.ipv6_exthdr)
        OXM_entry_ipv6_exthdr(std::move(b.data.ipv6_exthdr));
    break;
  case OXM_EF_IPV6_EXTHDR_MASK:
    new (&a.data.ipv6_exthdr_mask)
        OXM_entry_ipv6_exthdr_mask(std::move(b.data.ipv6_exthdr_mask)); break;
  default: variant_error(f);
  }
}

void
construct(OXM_entry_payload& a, const OXM_entry_payload& b,
                  OXM_entry_field f)
{
  a.init = b.init;
  if(not a)
    return;
  switch (f) {
  case OXM_EF_IN_PORT:
    new (&a.data.in_port) OXM_entry_in_port(b.data.in_port); break;
  case OXM_EF_IN_PHY_PORT:
    new (&a.data.in_phy_port) OXM_entry_in_phy_port(b.data.in_phy_port); break;
  case OXM_EF_METADATA:
    new (&a.data.metadata) OXM_entry_metadata(b.data.metadata); break;
  case OXM_EF_METADATA_MASK:
    new (&a.data.metadata_mask) OXM_entry_metadata_mask(b.data.metadata_mask);
    break;
  case OXM_EF_ETH_DST:
    new (&a.data.eth_dst) OXM_entry_eth_dst(b.data.eth_dst); break;
  case OXM_EF_ETH_DST_MASK:
    new (&a.data.eth_dst_mask) OXM_entry_eth_dst_mask(b.data.eth_dst_mask);
    break;
  case OXM_EF_ETH_SRC:
    new (&a.data.eth_src) OXM_entry_eth_src(b.data.eth_src); break;
  case OXM_EF_ETH_SRC_MASK:
    new (&a.data.eth_src_mask) OXM_entry_eth_src_mask(b.data.eth_src_mask);
    break;
  case OXM_EF_ETH_TYPE:
    new (&a.data.eth_type) OXM_entry_eth_type(b.data.eth_type); break;
  case OXM_EF_VLAN_VID:
    new (&a.data.vlan_vid) OXM_entry_vlan_vid(b.data.vlan_vid); break;
  case OXM_EF_VLAN_VID_MASK:
    new (&a.data.vlan_vid_mask) OXM_entry_vlan_vid_mask(b.data.vlan_vid_mask);
    break;
  case OXM_EF_VLAN_PCP:
    new (&a.data.vlan_pcp) OXM_entry_vlan_pcp(b.data.vlan_pcp); break;
  case OXM_EF_IP_DSCP:
    new (&a.data.ip_dscp) OXM_entry_ip_dscp(b.data.ip_dscp); break;
  case OXM_EF_IP_ECN:
    new (&a.data.ip_ecn) OXM_entry_ip_ecn(b.data.ip_ecn); break;
  case OXM_EF_IP_PROTO:
    new (&a.data.ip_proto) OXM_entry_ip_proto(b.data.ip_proto); break;
  case OXM_EF_IPV4_SRC:
    new (&a.data.ipv4_src) OXM_entry_ipv4_src(b.data.ipv4_src); break;
  case OXM_EF_IPV4_SRC_MASK:
    new (&a.data.ipv4_src_mask) OXM_entry_ipv4_src_mask(b.data.ipv4_src_mask);
    break;
  case OXM_EF_IPV4_DST:
    new (&a.data.ipv4_dst) OXM_entry_ipv4_dst(b.data.ipv4_dst); break;
  case OXM_EF_IPV4_DST_MASK:
    new (&a.data.ipv4_dst_mask) OXM_entry_ipv4_dst_mask(b.data.ipv4_dst_mask);
    break;
  case OXM_EF_TCP_SRC:
    new (&a.data.tcp_src) OXM_entry_tcp_src(b.data.tcp_src); break;
  case OXM_EF_TCP_DST:
    new (&a.data.tcp_dst) OXM_entry_tcp_dst(b.data.tcp_dst); break;
  case OXM_EF_UDP_SRC:
    new (&a.data.udp_src) OXM_entry_udp_src(b.data.udp_src); break;
  case OXM_EF_UDP_DST:
    new (&a.data.udp_dst) OXM_entry_udp_dst(b.data.udp_dst); break;
  case OXM_EF_SCTP_SRC:
    new (&a.data.sctp_src) OXM_entry_sctp_src(b.data.sctp_src); break;
  case OXM_EF_SCTP_DST:
    new (&a.data.sctp_dst) OXM_entry_sctp_dst(b.data.sctp_dst); break;
  case OXM_EF_ICMPV4_TYPE:
    new (&a.data.icmpv4_type) OXM_entry_icmpv4_type(b.data.icmpv4_type); break;
  case OXM_EF_ICMPV4_CODE:
    new (&a.data.icmpv4_code) OXM_entry_icmpv4_code(b.data.icmpv4_code); break;
  case OXM_EF_ARP_OP:
    new (&a.data.arp_op) OXM_entry_arp_op(b.data.arp_op); break;
  case OXM_EF_ARP_SPA:
    new (&a.data.arp_spa) OXM_entry_arp_spa(b.data.arp_spa); break;
  case OXM_EF_ARP_SPA_MASK:
    new (&a.data.arp_spa_mask) OXM_entry_arp_spa_mask(b.data.arp_spa_mask);
    break;
  case OXM_EF_ARP_TPA:
    new (&a.data.arp_tpa) OXM_entry_arp_tpa(b.data.arp_tpa); break;
  case OXM_EF_ARP_TPA_MASK:
    new (&a.data.arp_tpa_mask) OXM_entry_arp_tpa_mask(b.data.arp_tpa_mask);
    break;
  case OXM_EF_ARP_SHA:
    new (&a.data.arp_sha) OXM_entry_arp_sha(b.data.arp_sha); break;
  case OXM_EF_ARP_SHA_MASK:
    new (&a.data.arp_sha_mask) OXM_entry_arp_sha_mask(b.data.arp_sha_mask);
    break;
  case OXM_EF_ARP_THA:
    new (&a.data.arp_tha) OXM_entry_arp_tha(b.data.arp_tha); break;
  case OXM_EF_ARP_THA_MASK:
    new (&a.data.arp_tha_mask) OXM_entry_arp_tha_mask(b.data.arp_tha_mask);
    break;
  case OXM_EF_IPV6_SRC:
    new (&a.data.ipv6_src) OXM_entry_ipv6_src(b.data.ipv6_src); break;
  case OXM_EF_IPV6_SRC_MASK:
    new (&a.data.ipv6_src_mask) OXM_entry_ipv6_src_mask(b.data.ipv6_src_mask);
    break;
  case OXM_EF_IPV6_DST:
    new (&a.data.ipv6_dst) OXM_entry_ipv6_dst(b.data.ipv6_dst); break;
  case OXM_EF_IPV6_DST_MASK:
    new (&a.data.ipv6_dst_mask) OXM_entry_ipv6_dst_mask(b.data.ipv6_dst_mask);
    break;
  case OXM_EF_IPV6_FLABEL:
    new (&a.data.ipv6_flabel) OXM_entry_ipv6_flabel(b.data.ipv6_flabel); break;
  case OXM_EF_IPV6_FLABEL_MASK:
    new (&a.data.ipv6_flabel_mask)
         OXM_entry_ipv6_flabel_mask(b.data.ipv6_flabel_mask); break;
  case OXM_EF_ICMPV6_TYPE:
    new (&a.data.icmpv6_type) OXM_entry_icmpv6_type(b.data.icmpv6_type); break;
  case OXM_EF_ICMPV6_CODE:
    new (&a.data.icmpv6_code) OXM_entry_icmpv6_code(b.data.icmpv6_code); break;
  case OXM_EF_IPV6_ND_TARGET:
    new (&a.data.ipv6_nd_target)
         OXM_entry_ipv6_nd_target(b.data.ipv6_nd_target); break;
  case OXM_EF_IPV6_ND_SLL:
    new (&a.data.ipv6_nd_sll) OXM_entry_ipv6_nd_sll(b.data.ipv6_nd_sll); break;
  case OXM_EF_IPV6_ND_TLL:
    new (&a.data.ipv6_nd_tll) OXM_entry_ipv6_nd_tll(b.data.ipv6_nd_tll); break;
  case OXM_EF_MPLS_LABEL:
    new (&a.data.mpls_label) OXM_entry_mpls_label(b.data.mpls_label); break;
  case OXM_EF_MPLS_TC:
    new (&a.data.mpls_tc) OXM_entry_mpls_tc(b.data.mpls_tc); break;
  case OXM_EF_MPLS_BOS:
    new (&a.data.mpls_bos) OXM_entry_mpls_bos(b.data.mpls_bos); break;
  case OXM_EF_PBB_ISID:
    new (&a.data.pbb_isid) OXM_entry_pbb_isid(b.data.pbb_isid); break;
  case OXM_EF_PBB_ISID_MASK:
    new (&a.data.pbb_isid_mask) OXM_entry_pbb_isid_mask(b.data.pbb_isid_mask);
    break;
  case OXM_EF_TUNNEL_ID:
    new (&a.data.tunnel_id) OXM_entry_tunnel_id(b.data.tunnel_id); break;
  case OXM_EF_TUNNEL_ID_MASK:
    new (&a.data.tunnel_id_mask)
        OXM_entry_tunnel_id_mask(b.data.tunnel_id_mask); break;
  case OXM_EF_IPV6_EXTHDR:
    new (&a.data.ipv6_exthdr) OXM_entry_ipv6_exthdr(b.data.ipv6_exthdr);
    break;
  case OXM_EF_IPV6_EXTHDR_MASK:
    new (&a.data.ipv6_exthdr_mask)
        OXM_entry_ipv6_exthdr_mask(b.data.ipv6_exthdr_mask); break;
  default: variant_error(f);
  }
}

void
destroy(OXM_entry_payload& p, OXM_entry_field f)
{
  switch (f) {
  case OXM_EF_IN_PORT: p.data.in_port.~OXM_entry_in_port(); break;
  case OXM_EF_IN_PHY_PORT: p.data.in_phy_port.~OXM_entry_in_phy_port(); break;
  case OXM_EF_METADATA: p.data.metadata.~OXM_entry_metadata(); break;
  case OXM_EF_METADATA_MASK: p.data.metadata_mask.~OXM_entry_metadata_mask();
    break;
  case OXM_EF_ETH_DST: p.data.eth_dst.~OXM_entry_eth_dst(); break;
  case OXM_EF_ETH_DST_MASK: p.data.eth_dst_mask.~OXM_entry_eth_dst_mask();
    break;
  case OXM_EF_ETH_SRC: p.data.eth_src.~OXM_entry_eth_src(); break;
  case OXM_EF_ETH_SRC_MASK: p.data.eth_src_mask.~OXM_entry_eth_src_mask();
    break;
  case OXM_EF_ETH_TYPE: p.data.eth_type.~OXM_entry_eth_type(); break;
  case OXM_EF_VLAN_VID: p.data.vlan_vid.~OXM_entry_vlan_vid(); break;
  case OXM_EF_VLAN_VID_MASK: p.data.vlan_vid_mask.~OXM_entry_vlan_vid_mask();
    break;
  case OXM_EF_VLAN_PCP: p.data.vlan_pcp.~OXM_entry_vlan_pcp(); break;
  case OXM_EF_IP_DSCP: p.data.ip_dscp.~OXM_entry_ip_dscp(); break;
  case OXM_EF_IP_ECN: p.data.ip_ecn.~OXM_entry_ip_ecn(); break;
  case OXM_EF_IP_PROTO: p.data.ip_proto.~OXM_entry_ip_proto(); break;
  case OXM_EF_IPV4_SRC: p.data.ipv4_src.~OXM_entry_ipv4_src(); break;
  case OXM_EF_IPV4_SRC_MASK: p.data.ipv4_src_mask.~OXM_entry_ipv4_src_mask();
    break;
  case OXM_EF_IPV4_DST: p.data.ipv4_dst.~OXM_entry_ipv4_dst(); break;
  case OXM_EF_IPV4_DST_MASK: p.data.ipv4_dst_mask.~OXM_entry_ipv4_dst_mask();
    break;
  case OXM_EF_TCP_SRC: p.data.tcp_src.~OXM_entry_tcp_src(); break;
  case OXM_EF_TCP_DST: p.data.tcp_dst.~OXM_entry_tcp_dst(); break;
  case OXM_EF_UDP_SRC: p.data.udp_src.~OXM_entry_udp_src(); break;
  case OXM_EF_UDP_DST: p.data.udp_dst.~OXM_entry_udp_dst(); break;
  case OXM_EF_SCTP_SRC: p.data.sctp_src.~OXM_entry_sctp_src(); break;
  case OXM_EF_SCTP_DST: p.data.sctp_dst.~OXM_entry_sctp_dst(); break;
  case OXM_EF_ICMPV4_TYPE: p.data.icmpv4_type.~OXM_entry_icmpv4_type(); break;
  case OXM_EF_ICMPV4_CODE: p.data.icmpv4_code.~OXM_entry_icmpv4_code(); break;
  case OXM_EF_ARP_OP: p.data.arp_op.~OXM_entry_arp_op(); break;
  case OXM_EF_ARP_SPA: p.data.arp_spa.~OXM_entry_arp_spa(); break;
  case OXM_EF_ARP_SPA_MASK: p.data.arp_spa_mask.~OXM_entry_arp_spa_mask();
    break;
  case OXM_EF_ARP_TPA: p.data.arp_tpa.~OXM_entry_arp_tpa(); break;
  case OXM_EF_ARP_TPA_MASK: p.data.arp_tpa_mask.~OXM_entry_arp_tpa_mask();
    break;
  case OXM_EF_ARP_SHA: p.data.arp_sha.~OXM_entry_arp_sha(); break;
  case OXM_EF_ARP_SHA_MASK: p.data.arp_sha_mask.~OXM_entry_arp_sha_mask();
    break;
  case OXM_EF_ARP_THA: p.data.arp_tha.~OXM_entry_arp_tha(); break;
  case OXM_EF_ARP_THA_MASK: p.data.arp_tha_mask.~OXM_entry_arp_tha_mask();
    break;
  case OXM_EF_IPV6_SRC: p.data.ipv6_src.~OXM_entry_ipv6_src(); break;
  case OXM_EF_IPV6_SRC_MASK: p.data.ipv6_src_mask.~OXM_entry_ipv6_src_mask();
    break;
  case OXM_EF_IPV6_DST: p.data.ipv6_dst.~OXM_entry_ipv6_dst(); break;
  case OXM_EF_IPV6_DST_MASK: p.data.ipv6_dst_mask.~OXM_entry_ipv6_dst_mask();
    break;
  case OXM_EF_IPV6_FLABEL: p.data.ipv6_flabel.~OXM_entry_ipv6_flabel(); break;
  case OXM_EF_IPV6_FLABEL_MASK:
    p.data.ipv6_flabel_mask.~OXM_entry_ipv6_flabel_mask(); break;
  case OXM_EF_ICMPV6_TYPE: p.data.icmpv6_type.~OXM_entry_icmpv6_type(); break;
  case OXM_EF_ICMPV6_CODE: p.data.icmpv6_code.~OXM_entry_icmpv6_code(); break;
  case OXM_EF_IPV6_ND_TARGET:
    p.data.ipv6_nd_target.~OXM_entry_ipv6_nd_target(); break;
  case OXM_EF_IPV6_ND_SLL: p.data.ipv6_nd_sll.~OXM_entry_ipv6_nd_sll(); break;
  case OXM_EF_IPV6_ND_TLL: p.data.ipv6_nd_tll.~OXM_entry_ipv6_nd_tll(); break;
  case OXM_EF_MPLS_LABEL: p.data.mpls_label.~OXM_entry_mpls_label(); break;
  case OXM_EF_MPLS_TC: p.data.mpls_tc.~OXM_entry_mpls_tc(); break;
  case OXM_EF_MPLS_BOS: p.data.mpls_bos.~OXM_entry_mpls_bos(); break;
  case OXM_EF_PBB_ISID: p.data.pbb_isid.~OXM_entry_pbb_isid(); break;
  case OXM_EF_PBB_ISID_MASK: p.data.pbb_isid_mask.~OXM_entry_pbb_isid_mask();
    break;
  case OXM_EF_TUNNEL_ID: p.data.tunnel_id.~OXM_entry_tunnel_id(); break;
  case OXM_EF_TUNNEL_ID_MASK:
    p.data.tunnel_id_mask.~OXM_entry_tunnel_id_mask(); break;
  case OXM_EF_IPV6_EXTHDR: p.data.ipv6_exthdr.~OXM_entry_ipv6_exthdr(); break;
  case OXM_EF_IPV6_EXTHDR_MASK:
    p.data.ipv6_exthdr_mask.~OXM_entry_ipv6_exthdr_mask(); break;
  default: return;
  }
}

OXM_entry_payload&
assign(OXM_entry_payload& a, OXM_entry_payload&& b, OXM_entry_field f)
{
  if (&a == &b)
    return a;

  if (not a) {
    construct(a, std::move(b), f);
    return a;
  }

  a.init = b.init;
  if (not a) {
    destroy(a, f);
    return a;
  }

  switch (f) {
  case OXM_EF_IN_PORT: a.data.in_port = std::move(b.data.in_port); break;
  case OXM_EF_IN_PHY_PORT: a.data.in_phy_port = std::move(b.data.in_phy_port);
    break;
  case OXM_EF_METADATA: a.data.metadata = std::move(b.data.metadata); break;
  case OXM_EF_METADATA_MASK:
    a.data.metadata_mask = std::move(b.data.metadata_mask); break;
  case OXM_EF_ETH_DST: a.data.eth_dst = std::move(b.data.eth_dst); break;
  case OXM_EF_ETH_DST_MASK:
    a.data.eth_dst_mask = std::move(b.data.eth_dst_mask); break;
  case OXM_EF_ETH_SRC: a.data.eth_src = std::move(b.data.eth_src); break;
  case OXM_EF_ETH_SRC_MASK:
    a.data.eth_src_mask = std::move(b.data.eth_src_mask); break;
  case OXM_EF_ETH_TYPE: a.data.eth_type = std::move(b.data.eth_type); break;
  case OXM_EF_VLAN_VID: a.data.vlan_vid = std::move(b.data.vlan_vid); break;
  case OXM_EF_VLAN_VID_MASK:
    a.data.vlan_vid_mask = std::move(b.data.vlan_vid_mask); break;
  case OXM_EF_VLAN_PCP: a.data.vlan_pcp = std::move(b.data.vlan_pcp); break;
  case OXM_EF_IP_DSCP: a.data.ip_dscp = std::move(b.data.ip_dscp); break;
  case OXM_EF_IP_ECN: a.data.ip_ecn = std::move(b.data.ip_ecn); break;
  case OXM_EF_IP_PROTO: a.data.ip_proto = std::move(b.data.ip_proto); break;
  case OXM_EF_IPV4_SRC: a.data.ipv4_src = std::move(b.data.ipv4_src); break;
  case OXM_EF_IPV4_SRC_MASK:
    a.data.ipv4_src_mask = std::move(b.data.ipv4_src_mask); break;
  case OXM_EF_IPV4_DST: a.data.ipv4_dst = std::move(b.data.ipv4_dst); break;
  case OXM_EF_IPV4_DST_MASK:
    a.data.ipv4_dst_mask = std::move(b.data.ipv4_dst_mask); break;
  case OXM_EF_TCP_SRC: a.data.tcp_src = std::move(b.data.tcp_src); break;
  case OXM_EF_TCP_DST: a.data.tcp_dst = std::move(b.data.tcp_dst); break;
  case OXM_EF_UDP_SRC: a.data.udp_src = std::move(b.data.udp_src); break;
  case OXM_EF_UDP_DST: a.data.udp_dst = std::move(b.data.udp_dst); break;
  case OXM_EF_SCTP_SRC: a.data.sctp_src = std::move(b.data.sctp_src); break;
  case OXM_EF_SCTP_DST: a.data.sctp_dst = std::move(b.data.sctp_dst); break;
  case OXM_EF_ICMPV4_TYPE: a.data.icmpv4_type = std::move(b.data.icmpv4_type);
    break;
  case OXM_EF_ICMPV4_CODE: a.data.icmpv4_code = std::move(b.data.icmpv4_code);
    break;
  case OXM_EF_ARP_OP: a.data.arp_op = std::move(b.data.arp_op); break;
  case OXM_EF_ARP_SPA: a.data.arp_spa = std::move(b.data.arp_spa); break;
  case OXM_EF_ARP_SPA_MASK:
    a.data.arp_spa_mask = std::move(b.data.arp_spa_mask); break;
  case OXM_EF_ARP_TPA: a.data.arp_tpa = std::move(b.data.arp_tpa); break;
  case OXM_EF_ARP_TPA_MASK:
    a.data.arp_tpa_mask = std::move(b.data.arp_tpa_mask); break;
  case OXM_EF_ARP_SHA: a.data.arp_sha = std::move(b.data.arp_sha); break;
  case OXM_EF_ARP_SHA_MASK:
    a.data.arp_sha_mask = std::move(b.data.arp_sha_mask); break;
  case OXM_EF_ARP_THA: a.data.arp_tha = std::move(b.data.arp_tha); break;
  case OXM_EF_ARP_THA_MASK:
    a.data.arp_tha_mask = std::move(b.data.arp_tha_mask); break;
  case OXM_EF_IPV6_SRC: a.data.ipv6_src = std::move(b.data.ipv6_src); break;
  case OXM_EF_IPV6_SRC_MASK:
    a.data.ipv6_src_mask = std::move(b.data.ipv6_src_mask); break;
  case OXM_EF_IPV6_DST: a.data.ipv6_dst = std::move(b.data.ipv6_dst); break;
  case OXM_EF_IPV6_DST_MASK:
    a.data.ipv6_dst_mask = std::move(b.data.ipv6_dst_mask); break;
  case OXM_EF_IPV6_FLABEL: a.data.ipv6_flabel = std::move(b.data.ipv6_flabel);
    break;
  case OXM_EF_IPV6_FLABEL_MASK:
    a.data.ipv6_flabel_mask = std::move(b.data.ipv6_flabel_mask); break;
  case OXM_EF_ICMPV6_TYPE: a.data.icmpv6_type = std::move(b.data.icmpv6_type);
    break;
  case OXM_EF_ICMPV6_CODE: a.data.icmpv6_code = std::move(b.data.icmpv6_code);
    break;
  case OXM_EF_IPV6_ND_TARGET:
    a.data.ipv6_nd_target = std::move(b.data.ipv6_nd_target); break;
  case OXM_EF_IPV6_ND_SLL: a.data.ipv6_nd_sll = std::move(b.data.ipv6_nd_sll);
    break;
  case OXM_EF_IPV6_ND_TLL: a.data.ipv6_nd_tll = std::move(b.data.ipv6_nd_tll);
    break;
  case OXM_EF_MPLS_LABEL: a.data.mpls_label = std::move(b.data.mpls_label);
    break;
  case OXM_EF_MPLS_TC: a.data.mpls_tc = std::move(b.data.mpls_tc); break;
  case OXM_EF_MPLS_BOS: a.data.mpls_bos = std::move(b.data.mpls_bos); break;
  case OXM_EF_PBB_ISID: a.data.pbb_isid = std::move(b.data.pbb_isid); break;
  case OXM_EF_PBB_ISID_MASK:
    a.data.pbb_isid_mask = std::move(b.data.pbb_isid_mask); break;
  case OXM_EF_TUNNEL_ID: a.data.tunnel_id = std::move(b.data.tunnel_id); break;
  case OXM_EF_TUNNEL_ID_MASK:
    a.data.tunnel_id_mask = std::move(b.data.tunnel_id_mask); break;
  case OXM_EF_IPV6_EXTHDR: a.data.ipv6_exthdr = std::move(b.data.ipv6_exthdr);
    break;
  case OXM_EF_IPV6_EXTHDR_MASK:
    a.data.ipv6_exthdr_mask = std::move(b.data.ipv6_exthdr_mask); break;
  default: variant_error(f);
  }
  return a;
}

OXM_entry_payload&
assign(OXM_entry_payload& a, const OXM_entry_payload& b,
               OXM_entry_field f)
{
  if (&a == &b)
    return a;

  if (not a) {
    construct(a, b, f);
    return a;
  }

  a.init = b.init;
  if (not a) {
    destroy(a, f);
    return a;
  }

  switch (f) {
  case OXM_EF_IN_PORT: a.data.in_port = b.data.in_port; break;
  case OXM_EF_IN_PHY_PORT: a.data.in_phy_port = b.data.in_phy_port; break;
  case OXM_EF_METADATA: a.data.metadata = b.data.metadata; break;
  case OXM_EF_METADATA_MASK: a.data.metadata_mask = b.data.metadata_mask; break;
  case OXM_EF_ETH_DST: a.data.eth_dst = b.data.eth_dst; break;
  case OXM_EF_ETH_DST_MASK: a.data.eth_dst_mask = b.data.eth_dst_mask; break;
  case OXM_EF_ETH_SRC: a.data.eth_src = b.data.eth_src; break;
  case OXM_EF_ETH_SRC_MASK: a.data.eth_src_mask = b.data.eth_src_mask; break;
  case OXM_EF_ETH_TYPE: a.data.eth_type = b.data.eth_type; break;
  case OXM_EF_VLAN_VID: a.data.vlan_vid = b.data.vlan_vid; break;
  case OXM_EF_VLAN_VID_MASK: a.data.vlan_vid_mask = b.data.vlan_vid_mask; break;
  case OXM_EF_VLAN_PCP: a.data.vlan_pcp = b.data.vlan_pcp; break;
  case OXM_EF_IP_DSCP: a.data.ip_dscp = b.data.ip_dscp; break;
  case OXM_EF_IP_ECN: a.data.ip_ecn = b.data.ip_ecn; break;
  case OXM_EF_IP_PROTO: a.data.ip_proto = b.data.ip_proto; break;
  case OXM_EF_IPV4_SRC: a.data.ipv4_src = b.data.ipv4_src; break;
  case OXM_EF_IPV4_SRC_MASK: a.data.ipv4_src_mask = b.data.ipv4_src_mask; break;
  case OXM_EF_IPV4_DST: a.data.ipv4_dst = b.data.ipv4_dst; break;
  case OXM_EF_IPV4_DST_MASK: a.data.ipv4_dst_mask = b.data.ipv4_dst_mask; break;
  case OXM_EF_TCP_SRC: a.data.tcp_src = b.data.tcp_src; break;
  case OXM_EF_TCP_DST: a.data.tcp_dst = b.data.tcp_dst; break;
  case OXM_EF_UDP_SRC: a.data.udp_src = b.data.udp_src; break;
  case OXM_EF_UDP_DST: a.data.udp_dst = b.data.udp_dst; break;
  case OXM_EF_SCTP_SRC: a.data.sctp_src = b.data.sctp_src; break;
  case OXM_EF_SCTP_DST: a.data.sctp_dst = b.data.sctp_dst; break;
  case OXM_EF_ICMPV4_TYPE: a.data.icmpv4_type = b.data.icmpv4_type; break;
  case OXM_EF_ICMPV4_CODE: a.data.icmpv4_code = b.data.icmpv4_code; break;
  case OXM_EF_ARP_OP: a.data.arp_op = b.data.arp_op; break;
  case OXM_EF_ARP_SPA: a.data.arp_spa = b.data.arp_spa; break;
  case OXM_EF_ARP_SPA_MASK: a.data.arp_spa_mask = b.data.arp_spa_mask; break;
  case OXM_EF_ARP_TPA: a.data.arp_tpa = b.data.arp_tpa; break;
  case OXM_EF_ARP_TPA_MASK: a.data.arp_tpa_mask = b.data.arp_tpa_mask; break;
  case OXM_EF_ARP_SHA: a.data.arp_sha = b.data.arp_sha; break;
  case OXM_EF_ARP_SHA_MASK: a.data.arp_sha_mask = b.data.arp_sha_mask; break;
  case OXM_EF_ARP_THA: a.data.arp_tha = b.data.arp_tha; break;
  case OXM_EF_ARP_THA_MASK: a.data.arp_tha_mask = b.data.arp_tha_mask; break;
  case OXM_EF_IPV6_SRC: a.data.ipv6_src = b.data.ipv6_src; break;
  case OXM_EF_IPV6_SRC_MASK: a.data.ipv6_src_mask = b.data.ipv6_src_mask; break;
  case OXM_EF_IPV6_DST: a.data.ipv6_dst = b.data.ipv6_dst; break;
  case OXM_EF_IPV6_DST_MASK: a.data.ipv6_dst_mask = b.data.ipv6_dst_mask; break;
  case OXM_EF_IPV6_FLABEL: a.data.ipv6_flabel = b.data.ipv6_flabel; break;
  case OXM_EF_IPV6_FLABEL_MASK:
    a.data.ipv6_flabel_mask = b.data.ipv6_flabel_mask; break;
  case OXM_EF_ICMPV6_TYPE: a.data.icmpv6_type = b.data.icmpv6_type; break;
  case OXM_EF_ICMPV6_CODE: a.data.icmpv6_code = b.data.icmpv6_code; break;
  case OXM_EF_IPV6_ND_TARGET:
    a.data.ipv6_nd_target = b.data.ipv6_nd_target; break;
  case OXM_EF_IPV6_ND_SLL: a.data.ipv6_nd_sll = b.data.ipv6_nd_sll; break;
  case OXM_EF_IPV6_ND_TLL: a.data.ipv6_nd_tll = b.data.ipv6_nd_tll; break;
  case OXM_EF_MPLS_LABEL: a.data.mpls_label = b.data.mpls_label; break;
  case OXM_EF_MPLS_TC: a.data.mpls_tc = b.data.mpls_tc; break;
  case OXM_EF_MPLS_BOS: a.data.mpls_bos = b.data.mpls_bos; break;
  case OXM_EF_PBB_ISID: a.data.pbb_isid = b.data.pbb_isid; break;
  case OXM_EF_PBB_ISID_MASK: a.data.pbb_isid_mask = b.data.pbb_isid_mask;
    break;
  case OXM_EF_TUNNEL_ID: a.data.tunnel_id = b.data.tunnel_id; break;
  case OXM_EF_TUNNEL_ID_MASK: a.data.tunnel_id_mask = b.data.tunnel_id_mask;
    break;
  case OXM_EF_IPV6_EXTHDR: a.data.ipv6_exthdr = b.data.ipv6_exthdr; break;
  case OXM_EF_IPV6_EXTHDR_MASK:
    a.data.ipv6_exthdr_mask = b.data.ipv6_exthdr_mask; break;
  default: variant_error(f);
  }
  return a;
}

bool
equal(const OXM_entry_payload& a, const OXM_entry_payload& b,
              OXM_entry_field f1, OXM_entry_field f2)
{
  assert(f1 == f2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (f1) {
  case OXM_EF_IN_PORT: return a.data.in_port == b.data.in_port;
  case OXM_EF_IN_PHY_PORT: return a.data.in_phy_port == b.data.in_phy_port;
  case OXM_EF_METADATA: return a.data.metadata == b.data.metadata;
  case OXM_EF_METADATA_MASK:
    return a.data.metadata_mask == b.data.metadata_mask;
  case OXM_EF_ETH_DST: return a.data.eth_dst == b.data.eth_dst;
  case OXM_EF_ETH_DST_MASK: return a.data.eth_dst_mask == b.data.eth_dst_mask;
  case OXM_EF_ETH_SRC: return a.data.eth_src == b.data.eth_src;
  case OXM_EF_ETH_SRC_MASK: return a.data.eth_src_mask == b.data.eth_src_mask;
  case OXM_EF_ETH_TYPE: return a.data.eth_type == b.data.eth_type;
  case OXM_EF_VLAN_VID: return a.data.vlan_vid == b.data.vlan_vid;
  case OXM_EF_VLAN_VID_MASK:
    return a.data.vlan_vid_mask == b.data.vlan_vid_mask;
  case OXM_EF_VLAN_PCP: return a.data.vlan_pcp == b.data.vlan_pcp;
  case OXM_EF_IP_DSCP: return a.data.ip_dscp == b.data.ip_dscp;
  case OXM_EF_IP_ECN: return a.data.ip_ecn == b.data.ip_ecn;
  case OXM_EF_IP_PROTO: return a.data.ip_proto == b.data.ip_proto;
  case OXM_EF_IPV4_SRC: return a.data.ipv4_src == b.data.ipv4_src;
  case OXM_EF_IPV4_SRC_MASK:
    return a.data.ipv4_src_mask == b.data.ipv4_src_mask;
  case OXM_EF_IPV4_DST: return a.data.ipv4_dst == b.data.ipv4_dst;
  case OXM_EF_IPV4_DST_MASK:
    return a.data.ipv4_dst_mask == b.data.ipv4_dst_mask;
  case OXM_EF_TCP_SRC: return a.data.tcp_src == b.data.tcp_src;
  case OXM_EF_TCP_DST: return a.data.tcp_dst == b.data.tcp_dst;
  case OXM_EF_UDP_SRC: return a.data.udp_src == b.data.udp_src;
  case OXM_EF_UDP_DST: return a.data.udp_dst == b.data.udp_dst;
  case OXM_EF_SCTP_SRC: return a.data.sctp_src == b.data.sctp_src;
  case OXM_EF_SCTP_DST: return a.data.sctp_dst == b.data.sctp_dst;
  case OXM_EF_ICMPV4_TYPE: return a.data.icmpv4_type == b.data.icmpv4_type;
  case OXM_EF_ICMPV4_CODE: return a.data.icmpv4_code == b.data.icmpv4_code;
  case OXM_EF_ARP_OP: return a.data.arp_op == b.data.arp_op;
  case OXM_EF_ARP_SPA: return a.data.arp_spa == b.data.arp_spa;
  case OXM_EF_ARP_SPA_MASK: return a.data.arp_spa_mask == b.data.arp_spa_mask;
  case OXM_EF_ARP_TPA: return a.data.arp_tpa == b.data.arp_tpa;
  case OXM_EF_ARP_TPA_MASK: return a.data.arp_tpa_mask == b.data.arp_tpa_mask;
  case OXM_EF_ARP_SHA: return a.data.arp_sha == b.data.arp_sha;
  case OXM_EF_ARP_SHA_MASK: return a.data.arp_sha_mask == b.data.arp_sha_mask;
  case OXM_EF_ARP_THA: return a.data.arp_tha == b.data.arp_tha;
  case OXM_EF_ARP_THA_MASK: return a.data.arp_tha_mask == b.data.arp_tha_mask;
  case OXM_EF_IPV6_SRC: return a.data.ipv6_src == b.data.ipv6_src;
  case OXM_EF_IPV6_SRC_MASK:
    return a.data.ipv6_src_mask == b.data.ipv6_src_mask;
  case OXM_EF_IPV6_DST: return a.data.ipv6_dst == b.data.ipv6_dst;
  case OXM_EF_IPV6_DST_MASK:
    return a.data.ipv6_dst_mask == b.data.ipv6_dst_mask;
  case OXM_EF_IPV6_FLABEL: return a.data.ipv6_flabel == b.data.ipv6_flabel;
  case OXM_EF_IPV6_FLABEL_MASK:
    return a.data.ipv6_flabel_mask == b.data.ipv6_flabel_mask;
  case OXM_EF_ICMPV6_TYPE: return a.data.icmpv6_type == b.data.icmpv6_type;
  case OXM_EF_ICMPV6_CODE: return a.data.icmpv6_code == b.data.icmpv6_code;
  case OXM_EF_IPV6_ND_TARGET:
    return a.data.ipv6_nd_target == b.data.ipv6_nd_target;
  case OXM_EF_IPV6_ND_SLL: return a.data.ipv6_nd_sll == b.data.ipv6_nd_sll;
  case OXM_EF_IPV6_ND_TLL: return a.data.ipv6_nd_tll == b.data.ipv6_nd_tll;
  case OXM_EF_MPLS_LABEL: return a.data.mpls_label == b.data.mpls_label;
  case OXM_EF_MPLS_TC: return a.data.mpls_tc == b.data.mpls_tc;
  case OXM_EF_MPLS_BOS: return a.data.mpls_bos == b.data.mpls_bos;
  case OXM_EF_PBB_ISID: return a.data.pbb_isid == b.data.pbb_isid;
  case OXM_EF_PBB_ISID_MASK:
    return a.data.pbb_isid_mask == b.data.pbb_isid_mask;
  case OXM_EF_TUNNEL_ID: return a.data.tunnel_id == b.data.tunnel_id;
  case OXM_EF_TUNNEL_ID_MASK:
    return a.data.tunnel_id_mask == b.data.tunnel_id_mask;
  case OXM_EF_IPV6_EXTHDR: return a.data.ipv6_exthdr == b.data.ipv6_exthdr;
  case OXM_EF_IPV6_EXTHDR_MASK:
    return a.data.ipv6_exthdr_mask == b.data.ipv6_exthdr_mask;
  default: variant_error(f1);
  }
  return false;
}

// Is_valid

Error_condition
is_valid(const OXM_entry_payload& p, OXM_entry_field f)
{
  if (not p)
    return BAD_OXM_INIT;
  switch (f) {
  case OXM_EF_IN_PORT: return is_valid(p.data.in_port);
  case OXM_EF_IN_PHY_PORT: return is_valid(p.data.in_phy_port);
  case OXM_EF_METADATA: return is_valid(p.data.metadata);
  case OXM_EF_METADATA_MASK: return is_valid(p.data.metadata_mask);
  case OXM_EF_ETH_DST: return is_valid(p.data.eth_dst);
  case OXM_EF_ETH_DST_MASK: return is_valid(p.data.eth_dst_mask);
  case OXM_EF_ETH_SRC: return is_valid(p.data.eth_src);
  case OXM_EF_ETH_SRC_MASK: return is_valid(p.data.eth_src_mask);
  case OXM_EF_ETH_TYPE: return is_valid(p.data.eth_type);
  case OXM_EF_VLAN_VID: return is_valid(p.data.vlan_vid);
  case OXM_EF_VLAN_VID_MASK: return is_valid(p.data.vlan_vid_mask);
  case OXM_EF_VLAN_PCP: return is_valid(p.data.vlan_pcp);
  case OXM_EF_IP_DSCP: return is_valid(p.data.ip_dscp);
  case OXM_EF_IP_ECN: return is_valid(p.data.ip_ecn);
  case OXM_EF_IP_PROTO: return is_valid(p.data.ip_proto);
  case OXM_EF_IPV4_SRC: return is_valid(p.data.ipv4_src);
  case OXM_EF_IPV4_SRC_MASK: return is_valid(p.data.ipv4_src_mask);
  case OXM_EF_IPV4_DST: return is_valid(p.data.ipv4_dst);
  case OXM_EF_IPV4_DST_MASK: return is_valid(p.data.ipv4_dst_mask);
  case OXM_EF_TCP_SRC: return is_valid(p.data.tcp_src);
  case OXM_EF_TCP_DST: return is_valid(p.data.tcp_dst);
  case OXM_EF_UDP_SRC: return is_valid(p.data.udp_src);
  case OXM_EF_UDP_DST: return is_valid(p.data.udp_dst);
  case OXM_EF_SCTP_SRC: return is_valid(p.data.sctp_src);
  case OXM_EF_SCTP_DST: return is_valid(p.data.sctp_dst);
  case OXM_EF_ICMPV4_TYPE: return is_valid(p.data.icmpv4_type);
  case OXM_EF_ICMPV4_CODE: return is_valid(p.data.icmpv4_code);
  case OXM_EF_ARP_OP: return is_valid(p.data.arp_op);
  case OXM_EF_ARP_SPA: return is_valid(p.data.arp_spa);
  case OXM_EF_ARP_SPA_MASK: return is_valid(p.data.arp_spa_mask);
  case OXM_EF_ARP_TPA: return is_valid(p.data.arp_tpa);
  case OXM_EF_ARP_TPA_MASK: return is_valid(p.data.arp_tpa_mask);
  case OXM_EF_ARP_SHA: return is_valid(p.data.arp_sha);
  case OXM_EF_ARP_SHA_MASK: return is_valid(p.data.arp_sha_mask);
  case OXM_EF_ARP_THA: return is_valid(p.data.arp_tha);
  case OXM_EF_ARP_THA_MASK: return is_valid(p.data.arp_tha_mask);
  case OXM_EF_IPV6_SRC: return is_valid(p.data.ipv6_src);
  case OXM_EF_IPV6_SRC_MASK: return is_valid(p.data.ipv6_src_mask);
  case OXM_EF_IPV6_DST: return is_valid(p.data.ipv6_dst);
  case OXM_EF_IPV6_DST_MASK: return is_valid(p.data.ipv6_dst_mask);
  case OXM_EF_IPV6_FLABEL: return is_valid(p.data.ipv6_flabel);
  case OXM_EF_IPV6_FLABEL_MASK: return is_valid(p.data.ipv6_flabel_mask);
  case OXM_EF_ICMPV6_TYPE: return is_valid(p.data.icmpv6_type);
  case OXM_EF_ICMPV6_CODE: return is_valid(p.data.icmpv6_code);
  case OXM_EF_IPV6_ND_TARGET: return is_valid(p.data.ipv6_nd_target);
  case OXM_EF_IPV6_ND_SLL: return is_valid(p.data.ipv6_nd_sll);
  case OXM_EF_IPV6_ND_TLL: return is_valid(p.data.ipv6_nd_tll);
  case OXM_EF_MPLS_LABEL: return is_valid(p.data.mpls_label);
  case OXM_EF_MPLS_TC: return is_valid(p.data.mpls_tc);
  case OXM_EF_MPLS_BOS: return is_valid(p.data.mpls_bos);
  case OXM_EF_PBB_ISID: return is_valid(p.data.pbb_isid);
  case OXM_EF_PBB_ISID_MASK: return is_valid(p.data.pbb_isid_mask);
  case OXM_EF_TUNNEL_ID: return is_valid(p.data.tunnel_id);
  case OXM_EF_TUNNEL_ID_MASK: return is_valid(p.data.tunnel_id_mask);
  case OXM_EF_IPV6_EXTHDR: return is_valid(p.data.ipv6_exthdr);
  case OXM_EF_IPV6_EXTHDR_MASK: return is_valid(p.data.ipv6_exthdr_mask);
  default: variant_error(f);
  }
  return BAD_OXM_FIELD;
}

// Bytes
inline std::size_t
bytes(const OXM_entry_payload& p, OXM_entry_field f)
{
  if (not p)
    return 0;
  switch (f) {
  case OXM_EF_IN_PORT: return bytes(p.data.in_port);
  case OXM_EF_IN_PHY_PORT: return bytes(p.data.in_phy_port);
  case OXM_EF_METADATA: return bytes(p.data.metadata);
  case OXM_EF_METADATA_MASK: return bytes(p.data.metadata_mask);
  case OXM_EF_ETH_DST: return bytes(p.data.eth_dst);
  case OXM_EF_ETH_DST_MASK: return bytes(p.data.eth_dst_mask);
  case OXM_EF_ETH_SRC: return bytes(p.data.eth_src);
  case OXM_EF_ETH_SRC_MASK: return bytes(p.data.eth_src_mask);
  case OXM_EF_ETH_TYPE: return bytes(p.data.eth_type);
  case OXM_EF_VLAN_VID: return bytes(p.data.vlan_vid);
  case OXM_EF_VLAN_VID_MASK: return bytes(p.data.vlan_vid_mask);
  case OXM_EF_VLAN_PCP: return bytes(p.data.vlan_pcp);
  case OXM_EF_IP_DSCP: return bytes(p.data.ip_dscp);
  case OXM_EF_IP_ECN: return bytes(p.data.ip_ecn);
  case OXM_EF_IP_PROTO: return bytes(p.data.ip_proto);
  case OXM_EF_IPV4_SRC: return bytes(p.data.ipv4_src);
  case OXM_EF_IPV4_SRC_MASK: return bytes(p.data.ipv4_src_mask);
  case OXM_EF_IPV4_DST: return bytes(p.data.ipv4_dst);
  case OXM_EF_IPV4_DST_MASK: return bytes(p.data.ipv4_dst_mask);
  case OXM_EF_TCP_SRC: return bytes(p.data.tcp_src);
  case OXM_EF_TCP_DST: return bytes(p.data.tcp_dst);
  case OXM_EF_UDP_SRC: return bytes(p.data.udp_src);
  case OXM_EF_UDP_DST: return bytes(p.data.udp_dst);
  case OXM_EF_SCTP_SRC: return bytes(p.data.sctp_src);
  case OXM_EF_SCTP_DST: return bytes(p.data.sctp_dst);
  case OXM_EF_ICMPV4_TYPE: return bytes(p.data.icmpv4_type);
  case OXM_EF_ICMPV4_CODE: return bytes(p.data.icmpv4_code);
  case OXM_EF_ARP_OP: return bytes(p.data.arp_op);
  case OXM_EF_ARP_SPA: return bytes(p.data.arp_spa);
  case OXM_EF_ARP_SPA_MASK: return bytes(p.data.arp_spa_mask);
  case OXM_EF_ARP_TPA: return bytes(p.data.arp_tpa);
  case OXM_EF_ARP_TPA_MASK: return bytes(p.data.arp_tpa_mask);
  case OXM_EF_ARP_SHA: return bytes(p.data.arp_sha);
  case OXM_EF_ARP_SHA_MASK: return bytes(p.data.arp_sha_mask);
  case OXM_EF_ARP_THA: return bytes(p.data.arp_tha);
  case OXM_EF_ARP_THA_MASK: return bytes(p.data.arp_tha_mask);
  case OXM_EF_IPV6_SRC: return bytes(p.data.ipv6_src);
  case OXM_EF_IPV6_SRC_MASK: return bytes(p.data.ipv6_src_mask);
  case OXM_EF_IPV6_DST: return bytes(p.data.ipv6_dst);
  case OXM_EF_IPV6_DST_MASK: return bytes(p.data.ipv6_dst_mask);
  case OXM_EF_IPV6_FLABEL: return bytes(p.data.ipv6_flabel);
  case OXM_EF_IPV6_FLABEL_MASK: return bytes(p.data.ipv6_flabel_mask);
  case OXM_EF_ICMPV6_TYPE: return bytes(p.data.icmpv6_type);
  case OXM_EF_ICMPV6_CODE: return bytes(p.data.icmpv6_code);
  case OXM_EF_IPV6_ND_TARGET: return bytes(p.data.ipv6_nd_target);
  case OXM_EF_IPV6_ND_SLL: return bytes(p.data.ipv6_nd_sll);
  case OXM_EF_IPV6_ND_TLL: return bytes(p.data.ipv6_nd_tll);
  case OXM_EF_MPLS_LABEL: return bytes(p.data.mpls_label);
  case OXM_EF_MPLS_TC: return bytes(p.data.mpls_tc);
  case OXM_EF_MPLS_BOS: return bytes(p.data.mpls_bos);
  case OXM_EF_PBB_ISID: return bytes(p.data.pbb_isid);
  case OXM_EF_PBB_ISID_MASK: return bytes(p.data.pbb_isid_mask);
  case OXM_EF_TUNNEL_ID: return bytes(p.data.tunnel_id);
  case OXM_EF_TUNNEL_ID_MASK: return bytes(p.data.tunnel_id_mask);
  case OXM_EF_IPV6_EXTHDR: return bytes(p.data.ipv6_exthdr);
  case OXM_EF_IPV6_EXTHDR_MASK: return bytes(p.data.ipv6_exthdr_mask);
  default: variant_error(f);
  }
  return 0;
}

// To/from buffer
Error_condition
to_buffer(Buffer_view& v, const OXM_entry_payload& p,
                  OXM_entry_field f)
{
  assert(p);
  switch (f) {
  case OXM_EF_IN_PORT: return to_buffer(v, p.data.in_port);
  case OXM_EF_IN_PHY_PORT: return to_buffer(v, p.data.in_phy_port);
  case OXM_EF_METADATA: return to_buffer(v, p.data.metadata);
  case OXM_EF_METADATA_MASK: return to_buffer(v, p.data.metadata_mask);
  case OXM_EF_ETH_DST: return to_buffer(v, p.data.eth_dst);
  case OXM_EF_ETH_DST_MASK: return to_buffer(v, p.data.eth_dst_mask);
  case OXM_EF_ETH_SRC: return to_buffer(v, p.data.eth_src);
  case OXM_EF_ETH_SRC_MASK: return to_buffer(v, p.data.eth_src_mask);
  case OXM_EF_ETH_TYPE: return to_buffer(v, p.data.eth_type);
  case OXM_EF_VLAN_VID: return to_buffer(v, p.data.vlan_vid);
  case OXM_EF_VLAN_VID_MASK: return to_buffer(v, p.data.vlan_vid_mask);
  case OXM_EF_VLAN_PCP: return to_buffer(v, p.data.vlan_pcp);
  case OXM_EF_IP_DSCP: return to_buffer(v, p.data.ip_dscp);
  case OXM_EF_IP_ECN: return to_buffer(v, p.data.ip_ecn);
  case OXM_EF_IP_PROTO: return to_buffer(v, p.data.ip_proto);
  case OXM_EF_IPV4_SRC: return to_buffer(v, p.data.ipv4_src);
  case OXM_EF_IPV4_SRC_MASK: return to_buffer(v, p.data.ipv4_src_mask);
  case OXM_EF_IPV4_DST: return to_buffer(v, p.data.ipv4_dst);
  case OXM_EF_IPV4_DST_MASK: return to_buffer(v, p.data.ipv4_dst_mask);
  case OXM_EF_TCP_SRC: return to_buffer(v, p.data.tcp_src);
  case OXM_EF_TCP_DST: return to_buffer(v, p.data.tcp_dst);
  case OXM_EF_UDP_SRC: return to_buffer(v, p.data.udp_src);
  case OXM_EF_UDP_DST: return to_buffer(v, p.data.udp_dst);
  case OXM_EF_SCTP_SRC: return to_buffer(v, p.data.sctp_src);
  case OXM_EF_SCTP_DST: return to_buffer(v, p.data.sctp_dst);
  case OXM_EF_ICMPV4_TYPE: return to_buffer(v, p.data.icmpv4_type);
  case OXM_EF_ICMPV4_CODE: return to_buffer(v, p.data.icmpv4_code);
  case OXM_EF_ARP_OP: return to_buffer(v, p.data.arp_op);
  case OXM_EF_ARP_SPA: return to_buffer(v, p.data.arp_spa);
  case OXM_EF_ARP_SPA_MASK: return to_buffer(v, p.data.arp_spa_mask);
  case OXM_EF_ARP_TPA: return to_buffer(v, p.data.arp_tpa);
  case OXM_EF_ARP_TPA_MASK: return to_buffer(v, p.data.arp_tpa_mask);
  case OXM_EF_ARP_SHA: return to_buffer(v, p.data.arp_sha);
  case OXM_EF_ARP_SHA_MASK: return to_buffer(v, p.data.arp_sha_mask);
  case OXM_EF_ARP_THA: return to_buffer(v, p.data.arp_tha);
  case OXM_EF_ARP_THA_MASK: return to_buffer(v, p.data.arp_tha_mask);
  case OXM_EF_IPV6_SRC: return to_buffer(v, p.data.ipv6_src);
  case OXM_EF_IPV6_SRC_MASK: return to_buffer(v, p.data.ipv6_src_mask);
  case OXM_EF_IPV6_DST: return to_buffer(v, p.data.ipv6_dst);
  case OXM_EF_IPV6_DST_MASK: return to_buffer(v, p.data.ipv6_dst_mask);
  case OXM_EF_IPV6_FLABEL: return to_buffer(v, p.data.ipv6_flabel);
  case OXM_EF_IPV6_FLABEL_MASK: return to_buffer(v, p.data.ipv6_flabel_mask);
  case OXM_EF_ICMPV6_TYPE: return to_buffer(v, p.data.icmpv6_type);
  case OXM_EF_ICMPV6_CODE: return to_buffer(v, p.data.icmpv6_code);
  case OXM_EF_IPV6_ND_TARGET: return to_buffer(v, p.data.ipv6_nd_target);
  case OXM_EF_IPV6_ND_SLL: return to_buffer(v, p.data.ipv6_nd_sll);
  case OXM_EF_IPV6_ND_TLL: return to_buffer(v, p.data.ipv6_nd_tll);
  case OXM_EF_MPLS_LABEL: return to_buffer(v, p.data.mpls_label);
  case OXM_EF_MPLS_TC: return to_buffer(v, p.data.mpls_tc);
  case OXM_EF_MPLS_BOS: return to_buffer(v, p.data.mpls_bos);
  case OXM_EF_PBB_ISID: return to_buffer(v, p.data.pbb_isid);
  case OXM_EF_PBB_ISID_MASK: return to_buffer(v, p.data.pbb_isid_mask);
  case OXM_EF_TUNNEL_ID: return to_buffer(v, p.data.tunnel_id);
  case OXM_EF_TUNNEL_ID_MASK: return to_buffer(v, p.data.tunnel_id_mask);
  case OXM_EF_IPV6_EXTHDR: return to_buffer(v, p.data.ipv6_exthdr);
  case OXM_EF_IPV6_EXTHDR_MASK: return to_buffer(v, p.data.ipv6_exthdr_mask);
  default: variant_error(f);
  }
  return BAD_OXM_FIELD;
}

Error_condition
from_buffer(Buffer_view& v, OXM_entry_payload& p, OXM_entry_field f)
{
  assert(p);
  switch (f) {
  case OXM_EF_IN_PORT: return from_buffer(v, p.data.in_port);
  case OXM_EF_IN_PHY_PORT: return from_buffer(v, p.data.in_phy_port);
  case OXM_EF_METADATA: return from_buffer(v, p.data.metadata);
  case OXM_EF_METADATA_MASK: return from_buffer(v, p.data.metadata_mask);
  case OXM_EF_ETH_DST: return from_buffer(v, p.data.eth_dst);
  case OXM_EF_ETH_DST_MASK: return from_buffer(v, p.data.eth_dst_mask);
  case OXM_EF_ETH_SRC: return from_buffer(v, p.data.eth_src);
  case OXM_EF_ETH_SRC_MASK: return from_buffer(v, p.data.eth_src_mask);
  case OXM_EF_ETH_TYPE: return from_buffer(v, p.data.eth_type);
  case OXM_EF_VLAN_VID: return from_buffer(v, p.data.vlan_vid);
  case OXM_EF_VLAN_VID_MASK: return from_buffer(v, p.data.vlan_vid_mask);
  case OXM_EF_VLAN_PCP: return from_buffer(v, p.data.vlan_pcp);
  case OXM_EF_IP_DSCP: return from_buffer(v, p.data.ip_dscp);
  case OXM_EF_IP_ECN: return from_buffer(v, p.data.ip_ecn);
  case OXM_EF_IP_PROTO: return from_buffer(v, p.data.ip_proto);
  case OXM_EF_IPV4_SRC: return from_buffer(v, p.data.ipv4_src);
  case OXM_EF_IPV4_SRC_MASK: return from_buffer(v, p.data.ipv4_src_mask);
  case OXM_EF_IPV4_DST: return from_buffer(v, p.data.ipv4_dst);
  case OXM_EF_IPV4_DST_MASK: return from_buffer(v, p.data.ipv4_dst_mask);
  case OXM_EF_TCP_SRC: return from_buffer(v, p.data.tcp_src);
  case OXM_EF_TCP_DST: return from_buffer(v, p.data.tcp_dst);
  case OXM_EF_UDP_SRC: return from_buffer(v, p.data.udp_src);
  case OXM_EF_UDP_DST: return from_buffer(v, p.data.udp_dst);
  case OXM_EF_SCTP_SRC: return from_buffer(v, p.data.sctp_src);
  case OXM_EF_SCTP_DST: return from_buffer(v, p.data.sctp_dst);
  case OXM_EF_ICMPV4_TYPE: return from_buffer(v, p.data.icmpv4_type);
  case OXM_EF_ICMPV4_CODE: return from_buffer(v, p.data.icmpv4_code);
  case OXM_EF_ARP_OP: return from_buffer(v, p.data.arp_op);
  case OXM_EF_ARP_SPA: return from_buffer(v, p.data.arp_spa);
  case OXM_EF_ARP_SPA_MASK: return from_buffer(v, p.data.arp_spa_mask);
  case OXM_EF_ARP_TPA: return from_buffer(v, p.data.arp_tpa);
  case OXM_EF_ARP_TPA_MASK: return from_buffer(v, p.data.arp_tpa_mask);
  case OXM_EF_ARP_SHA: return from_buffer(v, p.data.arp_sha);
  case OXM_EF_ARP_SHA_MASK: return from_buffer(v, p.data.arp_sha_mask);
  case OXM_EF_ARP_THA: return from_buffer(v, p.data.arp_tha);
  case OXM_EF_ARP_THA_MASK: return from_buffer(v, p.data.arp_tha_mask);
  case OXM_EF_IPV6_SRC: return from_buffer(v, p.data.ipv6_src);
  case OXM_EF_IPV6_SRC_MASK: return from_buffer(v, p.data.ipv6_src_mask);
  case OXM_EF_IPV6_DST: return from_buffer(v, p.data.ipv6_dst);
  case OXM_EF_IPV6_DST_MASK: return from_buffer(v, p.data.ipv6_dst_mask);
  case OXM_EF_IPV6_FLABEL: return from_buffer(v, p.data.ipv6_flabel);
  case OXM_EF_IPV6_FLABEL_MASK: return from_buffer(v, p.data.ipv6_flabel_mask);
  case OXM_EF_ICMPV6_TYPE: return from_buffer(v, p.data.icmpv6_type);
  case OXM_EF_ICMPV6_CODE: return from_buffer(v, p.data.icmpv6_code);
  case OXM_EF_IPV6_ND_TARGET: return from_buffer(v, p.data.ipv6_nd_target);
  case OXM_EF_IPV6_ND_SLL: return from_buffer(v, p.data.ipv6_nd_sll);
  case OXM_EF_IPV6_ND_TLL: return from_buffer(v, p.data.ipv6_nd_tll);
  case OXM_EF_MPLS_LABEL: return from_buffer(v, p.data.mpls_label);
  case OXM_EF_MPLS_TC: return from_buffer(v, p.data.mpls_tc);
  case OXM_EF_MPLS_BOS: return from_buffer(v, p.data.mpls_bos);
  case OXM_EF_PBB_ISID: return from_buffer(v, p.data.pbb_isid);
  case OXM_EF_PBB_ISID_MASK: return from_buffer(v, p.data.pbb_isid_mask);
  case OXM_EF_TUNNEL_ID: return from_buffer(v, p.data.tunnel_id);
  case OXM_EF_TUNNEL_ID_MASK: return from_buffer(v, p.data.tunnel_id_mask);
  case OXM_EF_IPV6_EXTHDR: return from_buffer(v, p.data.ipv6_exthdr);
  case OXM_EF_IPV6_EXTHDR_MASK: return from_buffer(v, p.data.ipv6_exthdr_mask);
  default: variant_error(f);
  }
  return BAD_OXM_FIELD;
}

std::string
to_string(const OXM_entry_payload& p, Formatter& fmt,
                  OXM_entry_field f)
{
  assert(p);
  switch (f) {
  case OXM_EF_IN_PORT: return to_string(p.data.in_port, fmt);
  case OXM_EF_IN_PHY_PORT: return to_string(p.data.in_phy_port, fmt);
  case OXM_EF_METADATA: return to_string(p.data.metadata, fmt);
  case OXM_EF_METADATA_MASK: return to_string(p.data.metadata_mask, fmt);
  case OXM_EF_ETH_DST: return to_string(p.data.eth_dst, fmt);
  case OXM_EF_ETH_DST_MASK: return to_string(p.data.eth_dst_mask, fmt);
  case OXM_EF_ETH_SRC: return to_string(p.data.eth_src, fmt);
  case OXM_EF_ETH_SRC_MASK: return to_string(p.data.eth_src_mask, fmt);
  case OXM_EF_ETH_TYPE: return to_string(p.data.eth_type, fmt);
  case OXM_EF_VLAN_VID: return to_string(p.data.vlan_vid, fmt);
  case OXM_EF_VLAN_VID_MASK: return to_string(p.data.vlan_vid_mask, fmt);
  case OXM_EF_VLAN_PCP: return to_string(p.data.vlan_pcp, fmt);
  case OXM_EF_IP_DSCP: return to_string(p.data.ip_dscp, fmt);
  case OXM_EF_IP_ECN: return to_string(p.data.ip_ecn, fmt);
  case OXM_EF_IP_PROTO: return to_string(p.data.ip_proto, fmt);
  case OXM_EF_IPV4_SRC: return to_string(p.data.ipv4_src, fmt);
  case OXM_EF_IPV4_SRC_MASK: return to_string(p.data.ipv4_src_mask, fmt);
  case OXM_EF_IPV4_DST: return to_string(p.data.ipv4_dst, fmt);
  case OXM_EF_IPV4_DST_MASK: return to_string(p.data.ipv4_dst_mask, fmt);
  case OXM_EF_TCP_SRC: return to_string(p.data.tcp_src, fmt);
  case OXM_EF_TCP_DST: return to_string(p.data.tcp_dst, fmt);
  case OXM_EF_UDP_SRC: return to_string(p.data.udp_src, fmt);
  case OXM_EF_UDP_DST: return to_string(p.data.udp_dst, fmt);
  case OXM_EF_SCTP_SRC: return to_string(p.data.sctp_src, fmt);
  case OXM_EF_SCTP_DST: return to_string(p.data.sctp_dst, fmt);
  case OXM_EF_ICMPV4_TYPE: return to_string(p.data.icmpv4_type, fmt);
  case OXM_EF_ICMPV4_CODE: return to_string(p.data.icmpv4_code, fmt);
  case OXM_EF_ARP_OP: return to_string(p.data.arp_op, fmt);
  case OXM_EF_ARP_SPA: return to_string(p.data.arp_spa, fmt);
  case OXM_EF_ARP_SPA_MASK: return to_string(p.data.arp_spa_mask, fmt);
  case OXM_EF_ARP_TPA: return to_string(p.data.arp_tpa, fmt);
  case OXM_EF_ARP_TPA_MASK: return to_string(p.data.arp_tpa_mask, fmt);
  case OXM_EF_ARP_SHA: return to_string(p.data.arp_sha, fmt);
  case OXM_EF_ARP_SHA_MASK: return to_string(p.data.arp_sha_mask, fmt);
  case OXM_EF_ARP_THA: return to_string(p.data.arp_tha, fmt);
  case OXM_EF_ARP_THA_MASK: return to_string(p.data.arp_tha_mask, fmt);
  case OXM_EF_IPV6_SRC: return to_string(p.data.ipv6_src, fmt);
  case OXM_EF_IPV6_SRC_MASK: return to_string(p.data.ipv6_src_mask, fmt);
  case OXM_EF_IPV6_DST: return to_string(p.data.ipv6_dst, fmt);
  case OXM_EF_IPV6_DST_MASK: return to_string(p.data.ipv6_dst_mask, fmt);
  case OXM_EF_IPV6_FLABEL: return to_string(p.data.ipv6_flabel, fmt);
  case OXM_EF_IPV6_FLABEL_MASK: return to_string(p.data.ipv6_flabel_mask, fmt);
  case OXM_EF_ICMPV6_TYPE: return to_string(p.data.icmpv6_type, fmt);
  case OXM_EF_ICMPV6_CODE: return to_string(p.data.icmpv6_code, fmt);
  case OXM_EF_IPV6_ND_TARGET: return to_string(p.data.ipv6_nd_target, fmt);
  case OXM_EF_IPV6_ND_SLL: return to_string(p.data.ipv6_nd_sll, fmt);
  case OXM_EF_IPV6_ND_TLL: return to_string(p.data.ipv6_nd_tll, fmt);
  case OXM_EF_MPLS_LABEL: return to_string(p.data.mpls_label, fmt);
  case OXM_EF_MPLS_TC: return to_string(p.data.mpls_tc, fmt);
  case OXM_EF_MPLS_BOS: return to_string(p.data.mpls_bos, fmt);
  case OXM_EF_PBB_ISID: return to_string(p.data.pbb_isid, fmt);
  case OXM_EF_PBB_ISID_MASK: return to_string(p.data.pbb_isid_mask, fmt);
  case OXM_EF_TUNNEL_ID: return to_string(p.data.tunnel_id, fmt);
  case OXM_EF_TUNNEL_ID_MASK: return to_string(p.data.tunnel_id_mask, fmt);
  case OXM_EF_IPV6_EXTHDR: return to_string(p.data.ipv6_exthdr, fmt);
  case OXM_EF_IPV6_EXTHDR_MASK: return to_string(p.data.ipv6_exthdr_mask, fmt);
  default: variant_error(f);
  }
}

// -------------------------------------------------------------------------- //
// OXM experimenter

Error_condition
to_buffer(Buffer_view& v, const OXM_experimenter& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_OXM_EXPERIMENTER;
  to_buffer(v, e.experimenter);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, OXM_experimenter& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_OXM_EXPERIMENTER;
  from_buffer(v, e.experimenter);
  return SUCCESS;
}

std::string
to_string(const OXM_experimenter& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM experimenter");

  nvp_to_string(ss, f, "Experimenter", e.experimenter);

  close_block(ss, f, "OXM experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// OXM

std::string
to_string(const OXM_entry_class c)
{
  switch(c) {
  case OXM_entry_class::NXM_0: return "NXM 0";
  case OXM_entry_class::NXM_1: return "NXM 1";
  case OXM_entry_class::OPEN_FLOW_BASIC: return "OpenFlow Basic";
  case OXM_entry_class::OXM_EXPERIMENTER: return "Experimenter";
  default: return "Unknown";
  }
}

Error_condition
to_buffer(Buffer_view& v, const OXM_entry& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_OXM_ENTRY_HEADER;

  to_buffer(v, e.header);

  if (e.header.oxm_class == OXM_entry_class::OXM_EXPERIMENTER)
    return to_buffer(v, e.experimenter);
  else
    return to_buffer(v, e.payload, e.header.field);
}

Error_condition
from_buffer(Buffer_view& v, OXM_entry& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_OXM_ENTRY_HEADER;

  if (Error_decl err = from_buffer(v, e.header))
    return err;

  if (e.header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER) {
    OXM_entry::Payload p;
    construct(p, e.header.field);
    assign(e.payload, std::move(p), e.header.field);
  }
  //else
  //  e.experimenter = OXM_experimenter;

  //if (not is_valid(e.header))
  //  return false;

  std::size_t n = e.header.length;
  if (remaining(v) < n)
    return AVAILABLE_OXM_ENTRY_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (e.header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
  {
    if (Error_decl err = from_buffer(c, e.payload, e.header.field))
      return err;
  }
  else
  {
    if (Error_decl err = from_buffer(c, e.experimenter))
      return err;
  }

  if(not update(v, c))
    return EXCESS_OXM;

  return SUCCESS;
}

//TODO
std::string
to_string(const OXM_entry& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "OXM entry");

/*
  nvp_to_string(ss, f, "Class", to_string(e.oxm_class), int(e.oxm_class));

  if (e.oxm_class != OXM_class::OXM_EXPERIMENTER)
    nvp_to_string(ss, f, "Field", to_string(e.field), int(e.field));

  nvp_to_string(ss, f, "Length", int(e.length));

  if (e.oxm_class == OXM_class::OXM_EXPERIMENTER)
    ss << to_string(e.experimenter, f);
  else
    ss << to_string(e.payload, f, e.field);
*/

  close_block(ss, f, "OXM entry");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Match

Error_condition
to_buffer(Buffer_view& v, const Match& m)
{
  if (not available(v, bytes(m)))
    return AVAILABLE_MATCH;

  to_buffer(v, m.type);
  to_buffer(v, m.length);
  //pad(v,4);
//  return to_buffer(v, m.rules);
  if (Error_decl err = to_buffer(v, m.rules))
    return err;

  uint8_t padding = 8 - (m.length % 8);
  if (padding == 8)
    return SUCCESS;
  if (not available(v, padding))
    return AVAILABLE_MATCH_PADDING;

  pad(v, padding);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Match& m)
{
  if (not available(v, bytes(m)))
    return AVAILABLE_MATCH;

  from_buffer(v, m.type);
  from_buffer(v, m.length);
//  pad(v,4); //in wiki but not in spec

  std::size_t n = m.length - 4;
  if (n == 0) {
    pad(v,4);
    return SUCCESS;
  }
  if (remaining(v) < n)
    return BAD_MATCH_LENGTH;
  Buffer_view c = constrain(v, n);

  if (Error_decl err = from_buffer(c, m.rules))
    return err;
//  return update(v, c);
  if (not update(v, c))
    return EXCESS_MATCH;

  uint8_t padding = 8 - (m.length % 8);
  if (padding == 8)
    return SUCCESS;
  if (not available(v, padding))
    return AVAILABLE_MATCH_PADDING;
  pad(v, padding);
  return SUCCESS;
}

std::string
to_string(const Match& m, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Match");
  nvp_to_string(ss, f, "Type", int(m.type));
  nvp_to_string(ss, f, "Length", m.length);
  ss << to_string(m.rules, f);
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
    case ACTION_COPY_TTL_OUT: return "COPY_TTL_OUT";
    case ACTION_COPY_TTL_IN: return "COPY_TTL_IN";
    case ACTION_SET_MPLS_TTL: return "SET_MPLS_TTL";
    case ACTION_DEC_MPLS_TTL: return "DEC_MPLS_TTL";
    case ACTION_PUSH_VLAN: return "PUSH_VLAN";
    case ACTION_POP_VLAN: return "POP_VLAN";
    case ACTION_PUSH_MPLS: return "PUSH_MPLS";
    case ACTION_SET_QUEUE: return "SET_QUEUE";
    case ACTION_GROUP: return "GROUP";
    case ACTION_SET_NW_TTL: return "SET_NW_TTL";
    case ACTION_DEC_NW_TTL: return "DEC_NW_TTL";
    case ACTION_SET_FIELD: return "SET_FIELD";
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
// Action: Set mpls ttl

std::string
to_string(const Action_set_mpls_ttl& asmt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set MPLS TTL");
  nvp_to_string(ss, f, "Set MPLS TTL", asmt.mpls_ttl);
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
  nvp_to_string(ss, f, "Dec MPLS TTL", admt.mpls_ttl);
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

std::string
to_string(const Action_set_queue& asq, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set Queue");
  nvp_to_string(ss, f, "Queue ID", asq.queue_id);
  close_block(ss, f, "Action Set Queue");
  return ss.str();
}

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
// Action: Set Field

Error_condition
to_buffer(Buffer_view& v, const Action_set_field& sf)
{
  if (not available(v, bytes(sf)))
    return AVAILABLE_ACTION_SET_FIELD;

  if(Error_decl err = to_buffer(v, sf.oxm))
    return err;

  uint8_t padding = 8-((bytes(sf.oxm)+4) % 8);
  if(padding==8)
  return SUCCESS;
  if (not available(v, padding))
    return AVAILABLE_ACTION_SET_FIELD_PADDING;
  pad(v,padding);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_set_field& sf)
{
  if (not available(v, bytes(sf)))
    return AVAILABLE_ACTION_SET_FIELD;

  if(Error_decl err = from_buffer(v, sf.oxm))
    return err;

  uint8_t padding = 8-((bytes(sf.oxm)+4) % 8);
  if(padding==8)
    return SUCCESS;
  if (not available(v, padding))
    return AVAILABLE_ACTION_SET_FIELD_PADDING;
  pad(v,padding);
  return SUCCESS;
}

std::string
to_string(const Action_set_field& sf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Set Field");
  ss << to_string(sf.oxm,f);
  close_block(ss, f, "Action Set Field");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Push PBB

std::string
to_string(const Action_push_pbb& app, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Push PBB");

  nvp_to_string(ss, f, "Ethernet Type", app.ether_type);

  close_block(ss, f, "Action Push PBB");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Action: Pop PBB

Error_condition
to_buffer(Buffer_view& v, const Action_pop_pbb& app)
{
  if (not available(v, bytes(app)))
    return AVAILABLE_ACTION_POP_PBB;
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_pop_pbb& app)
{
  if (not available(v, bytes(app)))
    return AVAILABLE_ACTION_POP_PBB;
  pad(v, 4);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action: Experimenter

/*
std::string
to_string(const Action_experimenter& ae, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Experimenter");
  nvp_to_string(ss, f, "Experimenter", ae.experimenter);
  close_block(ss, f, "Action Experimenter");
  return ss.str();
}

Error_condition
to_buffer(Buffer_view& v, const Action_experimenter& ae)
{
  if (not available(v, bytes(ae)))
    return false;

  to_buffer(v, ae.experimenter);

  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_experimenter& ae)
{
  if (not available(v, bytes(ae)))
    return false;

  from_buffer(v, ae.experimenter);

  return SUCCESS;
}
*/

// -------------------------------------------------------------------------- //
// Action Payload

void
construct(Action_payload& p, Action_type t)
{
  p.init = true;
  switch (t) {
  case ACTION_OUTPUT:
    new (&p.data.output) Action_output(); break;
  case ACTION_COPY_TTL_OUT:
    new (&p.data.copy_ttl_out) Action_copy_ttl_out(); break;
  case ACTION_COPY_TTL_IN:
    new (&p.data.copy_ttl_in) Action_copy_ttl_in(); break;
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
  case ACTION_SET_FIELD:
    new (&p.data.set_field) Action_set_field(); break;
  case ACTION_PUSH_PBB:
    new (&p.data.push_pbb) Action_push_pbb(); break;
  case ACTION_POP_PBB:
    new (&p.data.pop_pbb) Action_pop_pbb(); break;
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
  case ACTION_COPY_TTL_OUT:
    new (&p.data.copy_ttl_out) Action_copy_ttl_out(x.data.copy_ttl_out); break;
  case ACTION_COPY_TTL_IN:
    new (&p.data.copy_ttl_in) Action_copy_ttl_in(x.data.copy_ttl_in); break;
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
  case ACTION_SET_FIELD:
    new (&p.data.set_field) Action_set_field(x.data.set_field); break;
  case ACTION_PUSH_PBB:
    new (&p.data.push_pbb) Action_push_pbb(x.data.push_pbb); break;
  case ACTION_POP_PBB:
    new (&p.data.pop_pbb) Action_pop_pbb(x.data.pop_pbb); break;
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

  if (not a) {
    construct(a, b, t);
    return a;
  }

  a.init = b.init;
  if (not a)
    return a;

  switch (t) {
  case ACTION_OUTPUT: a.data.output = b.data.output; break;
  case ACTION_COPY_TTL_OUT: a.data.copy_ttl_out = b.data.copy_ttl_out; break;
  case ACTION_COPY_TTL_IN: a.data.copy_ttl_in = b.data.copy_ttl_in; break;
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
  case ACTION_SET_FIELD: a.data.set_field = b.data.set_field; break;
  case ACTION_PUSH_PBB: a.data.push_pbb = b.data.push_pbb; break;
  case ACTION_POP_PBB: a.data.pop_pbb = b.data.pop_pbb; break;
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
  case ACTION_COPY_TTL_OUT: return a.data.copy_ttl_out == b.data.copy_ttl_out;
  case ACTION_COPY_TTL_IN: return a.data.copy_ttl_in == b.data.copy_ttl_in;
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
  case ACTION_SET_FIELD: return a.data.set_field == b.data.set_field;
  case ACTION_PUSH_PBB: return a.data.push_pbb == b.data.push_pbb;
  case ACTION_POP_PBB: return a.data.pop_pbb == b.data.pop_pbb;
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
  case ACTION_COPY_TTL_OUT: return bytes(p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return bytes(p.data.copy_ttl_in);
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
  case ACTION_SET_FIELD: return bytes(p.data.set_field);
  case ACTION_PUSH_PBB: return bytes(p.data.push_pbb);
  case ACTION_POP_PBB: return bytes(p.data.pop_pbb);
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
  case ACTION_COPY_TTL_OUT: return is_valid(p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return is_valid(p.data.copy_ttl_in);
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
  case ACTION_SET_FIELD: return is_valid(p.data.set_field);
  case ACTION_PUSH_PBB: return is_valid(p.data.push_pbb);
  case ACTION_POP_PBB: return is_valid(p.data.pop_pbb);
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
  case ACTION_COPY_TTL_OUT: return to_buffer(v, p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return to_buffer(v, p.data.copy_ttl_in);
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
  case ACTION_SET_FIELD: return to_buffer(v, p.data.set_field);
  case ACTION_PUSH_PBB: return to_buffer(v, p.data.push_pbb);
  case ACTION_POP_PBB: return to_buffer(v, p.data.pop_pbb);
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
  case ACTION_COPY_TTL_OUT: return from_buffer(v, p.data.copy_ttl_out);
  case ACTION_COPY_TTL_IN: return from_buffer(v, p.data.copy_ttl_in);
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
  case ACTION_SET_FIELD: return from_buffer(v, p.data.set_field);
  case ACTION_PUSH_PBB: return from_buffer(v, p.data.push_pbb);
  case ACTION_POP_PBB: return from_buffer(v, p.data.pop_pbb);
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
  case ACTION_COPY_TTL_OUT: return to_string(p.data.copy_ttl_out, fmt);
  case ACTION_COPY_TTL_IN: return to_string(p.data.copy_ttl_in, fmt);
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
  case ACTION_SET_FIELD: return to_string(p.data.set_field, fmt);
  case ACTION_PUSH_PBB: return to_string(p.data.push_pbb, fmt);
  case ACTION_POP_PBB: return to_string(p.data.pop_pbb, fmt);
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

  if (h.type == ACTION_EXPERIMENTER)
    to_buffer(v, h.experimenter);

  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Action_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.length);

  if (h.type == ACTION_EXPERIMENTER)
    from_buffer(v, h.experimenter);

  return SUCCESS;
}

std::string
to_string(const Action_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Action Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);

  if (h.type == ACTION_EXPERIMENTER)
    nvp_to_string(ss, f, "Experimenter", h.experimenter);

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
  if (is_valid(a.header))
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
  nvp_to_string(ss, f, "Table ID", igt.table_id);
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
// Instruction: Meter

Error_condition
to_buffer(Buffer_view& v, const Instruction_meter& im)
{
  if (not available(v, bytes(im)))
    return AVAILABLE_INSTRUCTION_METER;
  to_buffer(v, im.meter_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_meter& im)
{
  if (not available(v, bytes(im)))
    return AVAILABLE_INSTRUCTION_METER;
  from_buffer(v, im.meter_id);
  return SUCCESS;
}

std::string
to_string(const Instruction_meter& im, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Meter");

  nvp_to_string(ss, f, "Meter ID", im.meter_id);

  close_block(ss, f, "Instruction Meter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Instruction: Experimenter

/*
Error_condition
to_buffer(Buffer_view& v, const Instruction_experimenter& ie)
{
  if (not available(v, bytes(ie)))
    return false;

  to_buffer(v, ie.experimenter_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_experimenter& ie)
{
  if (not available(v, bytes(ie)))
    return false;

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
*/

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
  case INSTRUCTION_METER: new (&p.data.meter) Instruction_meter(); break;
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
  case INSTRUCTION_METER:
    new (&p.data.meter) Instruction_meter(std::move(x.data.meter)); break;
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
  case INSTRUCTION_METER:
    new (&p.data.meter) Instruction_meter(x.data.meter); break;
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
  case INSTRUCTION_GOTO_TABLE: p.data.goto_table.~Instruction_goto_table();
    break;
  case INSTRUCTION_WRITE_METADATA:
    p.data.write_metadata.~Instruction_write_metadata(); break;
  case INSTRUCTION_WRITE_ACTIONS:
    p.data.write_actions.~Instruction_write_actions(); break;
  case INSTRUCTION_APPLY_ACTIONS:
    p.data.apply_actions.~Instruction_apply_actions(); break;
  case INSTRUCTION_CLEAR_ACTIONS:
    p.data.clear_actions.~Instruction_clear_actions(); break;
  case INSTRUCTION_METER: p.data.meter.~Instruction_meter(); break;
  case INSTRUCTION_EXPERIMENTER:
    p.data.experimenter.~Instruction_experimenter(); break;
  default: return;
  }
}

Instruction_payload&
assign(Instruction_payload& a, Instruction_payload&& b,
       Instruction_type t)
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
  case INSTRUCTION_METER: a.data.meter = std::move(b.data.meter); break;
  case INSTRUCTION_EXPERIMENTER:
    a.data.experimenter = std::move(b.data.experimenter); break;
  default: variant_error(t);
  }
  return a;
}

Instruction_payload&
assign(Instruction_payload& a, const Instruction_payload& b,
       Instruction_type t)
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
  case INSTRUCTION_WRITE_METADATA:
    a.data.write_metadata = b.data.write_metadata; break;
  case INSTRUCTION_WRITE_ACTIONS:
    a.data.write_actions = b.data.write_actions; break;
  case INSTRUCTION_APPLY_ACTIONS:
    a.data.apply_actions = b.data.apply_actions; break;
  case INSTRUCTION_CLEAR_ACTIONS:
    a.data.clear_actions = b.data.clear_actions; break;
  case INSTRUCTION_METER: a.data.meter = b.data.meter; break;
  case INSTRUCTION_EXPERIMENTER:
    a.data.experimenter = b.data.experimenter; break;
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
  case INSTRUCTION_METER: return a.data.meter == b.data.meter;
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
  case INSTRUCTION_METER: return bytes(p.data.meter);
  case INSTRUCTION_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Instruction_payload& p, Instruction_type t)
{
  assert(p);
  switch(t) {
  case INSTRUCTION_GOTO_TABLE: return is_valid(p.data.goto_table);
  case INSTRUCTION_WRITE_METADATA: return is_valid(p.data.write_metadata);
  case INSTRUCTION_WRITE_ACTIONS: return is_valid(p.data.write_actions);
  case INSTRUCTION_APPLY_ACTIONS: return is_valid(p.data.apply_actions);
  case INSTRUCTION_CLEAR_ACTIONS: return is_valid(p.data.clear_actions);
  case INSTRUCTION_METER: return is_valid(p.data.meter);
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
  case INSTRUCTION_METER: return to_buffer(v, p.data.meter);
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
  case INSTRUCTION_METER: return from_buffer(v, p.data.meter);
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
  case INSTRUCTION_METER: return to_string(p.data.meter, fmt);
  case INSTRUCTION_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Instruction header

//inline bool
//check_header(const Buffer_view& v, const Instruction_header& h)
//{
//  return is_valid(h) and available(v, h.length - bytes(h));
//}

Error_condition
to_buffer(Buffer_view& v, const Instruction_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.length);

  if (h.type == INSTRUCTION_EXPERIMENTER)
    to_buffer(v, h.experimenter_id);

  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Instruction_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.length);

  if (h.type == INSTRUCTION_EXPERIMENTER)
    from_buffer(v, h.experimenter_id);

  return SUCCESS;
}

std::string
to_string(const Instruction_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Instruction Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);

  if (h.type == INSTRUCTION_EXPERIMENTER)
    nvp_to_string(ss, f, "Experimenter ID", h.experimenter_id);

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

  if (Error_decl err = is_valid(i.header.type))
    return err;

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
  //if (check_header(i.header))
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
  to_buffer(v, p.curr);
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
  from_buffer(v, p.curr);
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
  nvp_to_string(ss, f, "Curr", to_string(p.curr), int(p.curr));
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
to_string(Port::Config_value cv)
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
to_string(Port::State_value sv)
{
  switch(sv) {
    case Port::LINK_DOWN: return "Link Down";
    case Port::BLOCKED: return "Blocked";
    case Port::LIVE: return "Live";
    default: return "Unknown";
  }
}

std::string
to_string(Port::Id_value iv)
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
    default:
      std::stringstream ss;
      ss << int32_t(iv);
      return ss.str();
  }
}

std::string
to_string(Port::Features_value fv)
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
// Feature response

Error_condition
to_buffer(Buffer_view& v, const Feature_res& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FEATURE_RES;
  to_buffer(v, fr.datapath_id);
  to_buffer(v, fr.n_buffers);
  to_buffer(v, fr.n_tbls);
  to_buffer(v, fr.aux_id);
  pad(v, 2);
  to_buffer(v, fr.capabilities);
  to_buffer(v, fr.reserved);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Feature_res& fr)
{
  if (not available(v, bytes(fr)))
    return AVAILABLE_FEATURE_RES;
  from_buffer(v, fr.datapath_id);
  from_buffer(v, fr.n_buffers);
  from_buffer(v, fr.n_tbls);
  from_buffer(v, fr.aux_id);
  pad(v, 2);
  from_buffer(v, fr.capabilities);
  from_buffer(v, fr.reserved);
  return SUCCESS;
}

std::string
to_string(const Feature_res& fr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "FeatureRes");

  nvp_to_string(ss, f, "Datapath ID", fr.datapath_id);
  nvp_to_string(ss, f, "Buffer Numbers", fr.n_buffers);
  nvp_to_string(ss, f, "Table Numbers", fr.n_tbls);
  nvp_to_string(ss, f, "Aux ID", fr.aux_id);
  nvp_to_string(ss, f, "Feature Capabilities", to_string(fr.capabilities),
                int(fr.capabilities));
  nvp_to_string(ss, f, "Reserved", fr.reserved);

  close_block(ss, f, "FeatureRes");
  return ss.str();
}

std::string
to_string(const Feature_res::Capability_type ct)
{
  switch(ct) {
  case Feature_res::Capability_type::FLOW_STATS: return "Flow Stats";
  case Feature_res::Capability_type::TABLE_STATS: return "Table Stats";
  case Feature_res::Capability_type::PORT_STATS: return "Port Stats";
  case Feature_res::Capability_type::GROUP_STATS: return "Group Stats";
  case Feature_res::Capability_type::IP_REASM: return "IP Reasm";
  case Feature_res::Capability_type::QUEUE_STATS: return "Queue Stats";
  case Feature_res::Capability_type::PORT_BLOCKED: return "Port Blocked";
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

  //nvp_to_string(ss, f, "Flags", to_string(gcr.flags), gcr.flags);
  nvp_to_string(ss, f, "Miss Send Length", gcr.miss_send_len);

  close_block(ss, f, "GetConfigRes");
  return ss.str();
}

/*
std::string
to_string(Get_config_res::Flags ft)
{
  switch(ft) {
    case Get_config_res::FRAG_NORMAL: return "FRAG_NORMAL";
    case Get_config_res::FRAG_DROP: return "FRAG_DROP";
    case Get_config_res::FRAG_REASM: return "FRAG_REASM";
    case Get_config_res::FRAG_MASK: return "FRAG_MASK";
    default: return "Unknown";
  }
}
*/

// -------------------------------------------------------------------------- //
// Set config

std::string
to_string(const Set_config& sc, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "SetConfig");

  //nvp_to_string(ss, f, "Flags", to_string(sc.flags), sc.flags);
  nvp_to_string(ss, f, "Miss Send Length", sc.miss_send_len);

  close_block(ss, f, "SetConfig");
  return ss.str();
}

/*
std::string
to_string(Set_config::Flags ft)
{
  switch(ft) {
    case Set_config::FRAG_NORMAL: return "FRAG_NORMAL";
    case Set_config::FRAG_DROP: return "FRAG_DROP";
    case Set_config::FRAG_REASM: return "FRAG_REASM";
    case Set_config::FRAG_MASK: return "FRAG_MASK";
    default: return "Unknown";
  }
}
*/

// -------------------------------------------------------------------------- //
// Packet in

Error_condition
to_buffer(Buffer_view& v, const Packet_in& pi)
{
  if (not available(v, bytes(pi)))
    return AVAILABLE_PACKET_IN;
  to_buffer(v, pi.buffer_id);
  to_buffer(v, pi.total_len);
  to_buffer(v, pi.reason);
  to_buffer(v, pi.tbl_id);
  to_buffer(v, pi.cookie);

  if (Error_decl err = to_buffer(v, pi.match))
    return err;

  pad(v, 2);
  to_buffer(v, pi.data);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Packet_in& pi)
{
  if (not available(v, bytes(pi)))
    return AVAILABLE_PACKET_IN;
  from_buffer(v, pi.buffer_id);
  from_buffer(v, pi.total_len);
  from_buffer(v, pi.reason);
  from_buffer(v, pi.tbl_id);
  from_buffer(v, pi.cookie);

  if (Error_decl err = from_buffer(v, pi.match))
    return err;

  if (remaining(v) < 2)
    return AVAILABLE_PACKET_IN_PADDING;

  pad(v, 2);

  if (pi.total_len == 0)
    return SUCCESS;

  pi.data = Buffer(pi.total_len);
  from_buffer(v, pi.data);
  return SUCCESS;
}

std::string
to_string(const Packet_in& pi, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "PacketIn");

  nvp_to_string(ss, f, "Buffer ID", pi.buffer_id);
  nvp_to_string(ss, f, "Total Len", pi.total_len);
  nvp_to_string(ss, f, "Reason", to_string(pi.reason), int(pi.reason));
  nvp_to_string(ss, f, "Table ID", int(pi.tbl_id));
  nvp_to_string(ss, f, "Cookie", pi.cookie);

  ss << to_string(pi.match, f);

  nvp_to_string(ss, f, "Data bytes", bytes(pi.data));

  close_block(ss, f, "PacketIn");
  return ss.str();
}

std::string
to_string(Packet_in::Reason_type rt)
{
  switch(rt) {
  case Packet_in::Reason_type::NO_MATCH: return "NoMatch";
  case Packet_in::Reason_type::ACTION: return "Action";
  case Packet_in::Reason_type::INVALID_TTL: return "InvalidTTL";
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
  to_buffer(v, fr.hard_timeout);
  to_buffer(v, fr.packet_count);
  to_buffer(v, fr.byte_count);
  return to_buffer(v, fr.match);
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
  from_buffer(v, fr.hard_timeout);
  from_buffer(v, fr.packet_count);
  from_buffer(v, fr.byte_count);
  return from_buffer(v, fr.match);
}

std::string
to_string(const Flow_removed& fr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "FlowRemoved");

  nvp_to_string(ss, f, "Cookie", fr.cookie);
  nvp_to_string(ss, f, "Priority", fr.priority);
  nvp_to_string(ss, f, "Reason", to_string(fr.reason), int(fr.reason));
  nvp_to_string(ss, f, "Table ID", fr.table_id);
  nvp_to_string(ss, f, "Duration in Seconds", fr.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoseconds", fr.duration_nsec);
  nvp_to_string(ss, f, "Idle Timeout", fr.idle_timeout);
  nvp_to_string(ss, f, "Hard Timeout", fr.hard_timeout);
  nvp_to_string(ss, f, "Packet Count", fr.packet_count);
  nvp_to_string(ss, f, "Byte Count", fr.byte_count);

  ss << to_string(fr.match, f);

  close_block(ss, f, "FlowRemoved");
  return ss.str();
}

std::string
to_string(Flow_removed::Reason_type rt)
{
  switch(rt) {
  case Flow_removed::Reason_type::IDLE_TIMEOUT: return "IdleTimeout";
  case Flow_removed::Reason_type::HARD_TIMEOUT: return "HardTimeout";
  case Flow_removed::Reason_type::DELETE: return "Delete";
  case Flow_removed::Reason_type::GROUP_DELETE: return "GroupDelete";
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
to_string(Port_status::Reason_type rt)
{
  switch(rt) {
  case Port_status::Reason_type::ADD: return "Add";
  case Port_status::Reason_type::DELETE: return "Delete";
  case Port_status::Reason_type::MODIFY: return "Modify";
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

  if (Error_decl err = to_buffer(v, fm.match))
    return err;

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

  if (Error_decl err = from_buffer(v, fm.match))
    return err;

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
    case Flow_mod::RESET_COUNTS: return "RESET_COUNTS";
    case Flow_mod::NO_PACKET_COUNTS: return "NO_PACKET_COUNTS";
    case Flow_mod::NO_BYTE_COUNTS: return "NO_BYTE_COUNTS";
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

std::string
to_string(Group_mod::Id_value iv)
{
  switch(iv) {
  case Group_mod::Id_value::ID_MAX: return "MAX";
  case Group_mod::Id_value::ID_ALL: return "ALL";
  case Group_mod::Id_value::ID_ANY: return "ANY";
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
to_string(Port_mod::Config_type ct)
{
  switch(ct) {
  case Port_mod::Config_type::PORT_DOWN: return "PortDown";
  case Port_mod::Config_type::NO_RECV: return "No Recv";
  case Port_mod::Config_type::NO_FWD: return "No Fwd";
  case Port_mod::Config_type::NO_PACKET_IN: return "No PacketIn";
  default: return "Unknown";
  }
}

std::string
to_string(Port_mod::Features_type ft)
{
  switch(ft) {
  case Port_mod::Features_type::TEN_MB_HD: return "10MB HD";
  case Port_mod::Features_type::TEN_MB_FD: return "10MB FD";
  case Port_mod::Features_type::HUNDRED_MB_HD: return "100MB HD";
  case Port_mod::Features_type::HUNDRED_MB_FD: return "100MB FD";
  case Port_mod::Features_type::ONE_GB_HD: return "1GB HD";
  case Port_mod::Features_type::ONE_GB_FD: return "1GB FD";
  case Port_mod::Features_type::TEN_GB_FD: return "10GB FD";
  case Port_mod::Features_type::FORTY_GB_FD: return "40GB FD";
  case Port_mod::Features_type::HUNDRED_GB_FD: return "100GB FD";
  case Port_mod::Features_type::ONE_TB_FD: return "1TB FD";
  case Port_mod::Features_type::OTHER: return "Other";
  case Port_mod::Features_type::COPPER: return "Copper";
  case Port_mod::Features_type::FIBER: return "Fiber";
  case Port_mod::Features_type::AUTO_NEG: return "AutoNeg";
  case Port_mod::Features_type::PAUSE: return "Pause";
  case Port_mod::Features_type::PAUSE_ASYM: return "PauseAsym";
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

  nvp_to_string(ss, f, "Table ID", tm.table_id);
  nvp_to_string(ss, f, "Config", to_string(tm.config), int(tm.config));

  close_block(ss, f, "TableMod");
  return ss.str();
}

std::string
to_string(Table_mod::Config_type ct)
{
  switch(ct) {
  case Table_mod::Config_type::DEPRECATED_MASK: return "Deprecated Mask";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Multipart type

std::string
to_string(Multipart_type t)
{
  switch (t) {
  case MULTIPART_DESC: return "Desc";
  case MULTIPART_FLOW: return "Flow";
  case MULTIPART_AGGREGATE: return "Aggregate";
  case MULTIPART_TABLE: return "Table";
  case MULTIPART_PORT: return "Port";
  case MULTIPART_QUEUE: return "Queue";
  case MULTIPART_GROUP: return "Group";
  case MULTIPART_GROUP_DESC: return "Group Desc";
  case MULTIPART_GROUP_FEATURES: return "Group Features";
  case MULTIPART_METER: return "Meter";
  case MULTIPART_METER_CONFIG: return "Meter Config";
  case MULTIPART_METER_FEATURES: return "Meter Features";
  case MULTIPART_TABLE_FEATURES: return "Table Features";
  case MULTIPART_PORT_DESC: return "Port Description";
  case MULTIPART_EXPERIMENTER: return "Experimenter";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Multipart Request: Flow

std::string
to_string(const Multipart_req_flow& srf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Flow");

  nvp_to_string(ss, f, "Table ID", srf.table_id);
  nvp_to_string(ss, f, "Out Port", srf.out_port);
  nvp_to_string(ss, f, "Out Group", srf.out_group);
  nvp_to_string(ss, f, "Cookie", srf.cookie);
  nvp_to_string(ss, f, "Cookie Mask", srf.cookie_mask);

  ss << to_string(srf.match, f);

  close_block(ss, f, "MultipartReq Flow");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Aggregate

std::string
to_string(const Multipart_req_aggregate& sra, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Aggregate");

  nvp_to_string(ss, f, "Table ID", sra.table_id);
  nvp_to_string(ss, f, "Out Port", sra.out_port);
  nvp_to_string(ss, f, "Out Group", sra.out_group);
  nvp_to_string(ss, f, "Cookie", sra.cookie);
  nvp_to_string(ss, f, "Cookie Mask", sra.cookie_mask);

  ss << to_string(sra.match, f);

  close_block(ss, f, "MultipartReq Aggregate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Port

Error_condition
to_buffer(Buffer_view& v, const Multipart_req_port& srp)
{
  if (not available(v, bytes(srp)))
    return AVAILABLE_MULTIPART_REQ_PORT;
  to_buffer(v, srp.port_no);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req_port& srp)
{
  if (not available(v, bytes(srp)))
    return AVAILABLE_MULTIPART_REQ_PORT;
  from_buffer(v, srp.port_no);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Multipart_req_port& srp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Port");

  nvp_to_string(ss, f, "Port No", srp.port_no);

  close_block(ss, f, "MultipartReq Aggregate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Queue

Error_condition
to_buffer(Buffer_view& v, const Multipart_req_queue& srq)
{
  if (not available(v, bytes(srq)))
    return AVAILABLE_MULTIPART_REQ_QUEUE;
  to_buffer(v, srq.port_no);
  to_buffer(v, srq.queue_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req_queue& srq)
{
  if (not available(v, bytes(srq)))
    return AVAILABLE_MULTIPART_REQ_QUEUE;
  from_buffer(v, srq.port_no);
  from_buffer(v, srq.queue_id);
  return SUCCESS;
}

std::string
to_string(const Multipart_req_queue& srq, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Queue");

  nvp_to_string(ss, f, "Port No", srq.port_no);
  nvp_to_string(ss, f, "Queue ID", srq.queue_id);

  close_block(ss, f, "MultipartReq Queue");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Group

Error_condition
to_buffer(Buffer_view& v, const Multipart_req_group& srg)
{
  if (not available(v, bytes(srg)))
    return AVAILABLE_MULTIPART_REQ_GROUP;
  to_buffer(v, srg.group_id);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req_group& srg)
{
  if (not available(v, bytes(srg)))
    return AVAILABLE_MULTIPART_REQ_GROUP;
  from_buffer(v, srg.group_id);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Multipart_req_group& srg, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Group");

  nvp_to_string(ss, f, "Group ID", srg.group_id);

  close_block(ss, f, "MultipartReq Group");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Meter

std::string
to_string(const Multipart_req_meter& srm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Meter");

  nvp_to_string(ss, f, "Meter ID", srm.meter_id);

  close_block(ss, f, "MultipartReq Meter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Meter config

std::string
to_string(const Multipart_req_meter_config& srmc, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Meter Config");

  nvp_to_string(ss, f, "Meter ID", srmc.meter_id);

  close_block(ss, f, "MultipartReq Meter Config");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property type

std::string
to_string(Table_feature_property_type t)
{
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS: return "INSTRUCTIONS";
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS: return "INSTRUCTIONS_MISS";
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES: return "NEXT_TABLES";
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS: return "NEXT_TABLES_MISS";
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS: return "WRITE_ACTIONS";
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS: return "WRITE_ACTIONS_MISS";
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS: return "APPLY_ACTIONS";
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS: return "APPLY_ACTIONS_MISS";
  case TABLE_FEATURE_PROPERTY_MATCH: return "MATCH";
  case TABLE_FEATURE_PROPERTY_WILDCARDS: return "WILDCARDS";
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD: return "WRITE_SETFIELD";
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    return "WRITE_SETFIELD_MISS";
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD: return "APPLY_SETFIELD";
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    return "APPLY_SETFIELD_MISS";
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER: return "EXPERIMENTER";
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS: return "EXPERIMENTER_MISS";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Table feature property: Instructinos

std::string
to_string(const Table_feature_property_instructions& tfpi, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Instructions");

  ss << to_string(tfpi.instructions, f);

  close_block(ss, f, "Table Feature Property Instructions");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Instructinos miss

std::string
to_string(const Table_feature_property_instructions_miss& tfpim, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Instructions Miss");

  ss << to_string(tfpim.instructions, f);

  close_block(ss, f, "Table Feature Property Instructions Miss");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Next tables

std::string
to_string(const Table_feature_property_next_tables& tfpnt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Next Tables");

  ss << to_string(tfpnt.next_table_ids, f);

  close_block(ss, f, "Table Feature Property Next Tables");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Next tables miss

std::string
to_string(const Table_feature_property_next_tables_miss& tfpntm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Next Tables Miss");

  ss << to_string(tfpntm.next_table_ids, f);

  close_block(ss, f, "Table Feature Property Next Tables Miss");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Write actions

std::string
to_string(const Table_feature_property_write_actions& tfpwa, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Write Actions");

  ss << to_string(tfpwa.actions, f);

  close_block(ss, f, "Table Feature Property Write Actions");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Write actions miss

std::string
to_string(const Table_feature_property_write_actions_miss& tfpwam,
          Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Write Actions Miss");

  ss << to_string(tfpwam.actions, f);

  close_block(ss, f, "Table Feature Property Write Actions Miss");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Apply actions

std::string
to_string(const Table_feature_property_apply_actions& tfpaa, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Apply Actions");

  ss << to_string(tfpaa.actions, f);

  close_block(ss, f, "Table Feature Property Apply Actions");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Apply actions miss

std::string
to_string(const Table_feature_property_apply_actions_miss& tfpaam,
          Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Apply Actions Miss");

  ss << to_string(tfpaam.actions, f);

  close_block(ss, f, "Table Feature Property Apply Actions Miss");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Match

std::string
to_string(const Table_feature_property_match& tfpm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Match");

  ss << to_string(tfpm.oxms, f);

  close_block(ss, f, "Table Feature Property Match");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Wildcards

std::string
to_string(const Table_feature_property_wildcards& tfpw, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Wildcards");

  ss << to_string(tfpw.oxms, f);

  close_block(ss, f, "Table Feature Property Wildcards");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Write setfield

std::string
to_string(const Table_feature_property_write_setfield& tfpws, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Write Setfield");

  ss << to_string(tfpws.oxms, f);

  close_block(ss, f, "Table Feature Property Write Setfield");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Write setfield miss

std::string
to_string(const Table_feature_property_write_setfield_miss& tfpwsm,
          Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Write Setfield Miss");

  ss << to_string(tfpwsm.oxms, f);

  close_block(ss, f, "Table Feature Property Write Setfield Miss");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Apply setfield

std::string
to_string(const Table_feature_property_apply_setfield& tfpas, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Apply Setfield");

  ss << to_string(tfpas.oxms, f);

  close_block(ss, f, "Table Feature Property Apply Setfield");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: Apply setfield miss

std::string
to_string(const Table_feature_property_apply_setfield_miss& tfpasm,
          Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Apply Setfield Miss");

  ss << to_string(tfpasm.oxms, f);

  close_block(ss, f, "Table Feature Property Apply Setfield Miss");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: experimenter miss

std::string
to_string(const Table_feature_property_experimenter& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Experimenter");

  nvp_to_string(ss, f, "Data bytes", bytes(e.data));

  close_block(ss, f, "Table Feature Property Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: experimenter miss

std::string
to_string(const Table_feature_property_experimenter_miss& em, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Experimenter Miss");

  nvp_to_string(ss, f, "Data bytes", bytes(em.data));

  close_block(ss, f, "Table Feature Property Experimenter Miss");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property payload

void
construct(Table_feature_property_payload& p, Table_feature_property_type t)
{
  p.init = true;
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    new (&p.data.instructions) Table_feature_property_instructions(); break;
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    new (&p.data.instructions_miss) Table_feature_property_instructions_miss();
    break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    new (&p.data.next_tables) Table_feature_property_next_tables(); break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    new (&p.data.next_tables_miss) Table_feature_property_next_tables_miss();
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    new (&p.data.write_actions) Table_feature_property_write_actions(); break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    new (&p.data.write_actions_miss)
        Table_feature_property_write_actions_miss(); break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    new (&p.data.apply_actions) Table_feature_property_apply_actions(); break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    new (&p.data.apply_actions_miss)
        Table_feature_property_apply_actions_miss(); break;
  case TABLE_FEATURE_PROPERTY_MATCH:
    new (&p.data.match) Table_feature_property_match(); break;
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    new (&p.data.wildcards) Table_feature_property_wildcards(); break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    new (&p.data.write_setfield) Table_feature_property_write_setfield();
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    new (&p.data.write_setfield_miss)
        Table_feature_property_write_setfield_miss(); break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    new (&p.data.apply_setfield) Table_feature_property_apply_setfield();
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    new (&p.data.apply_setfield_miss)
        Table_feature_property_apply_setfield_miss(); break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    new (&p.data.experimenter) Table_feature_property_experimenter();
    break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    new (&p.data.experimenter_miss) Table_feature_property_experimenter_miss();
    break;
  default: variant_error(t);
  }
}

void
construct(Table_feature_property_payload& p,
          Table_feature_property_payload&& x, Table_feature_property_type t)
{
  p.init = x.init;
  if (not p.init)
    return;
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    new (&p.data.instructions)
        Table_feature_property_instructions(std::move(x.data.instructions));
    break;
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    new (&p.data.instructions_miss)
        Table_feature_property_instructions_miss
          (std::move(x.data.instructions_miss));
    break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    new (&p.data.next_tables)
        Table_feature_property_next_tables(std::move(x.data.next_tables));
    break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    new (&p.data.next_tables_miss)
        Table_feature_property_next_tables_miss
          (std::move(x.data.next_tables_miss));
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    new (&p.data.write_actions)
        Table_feature_property_write_actions(std::move(x.data.write_actions));
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    new (&p.data.write_actions_miss)
        Table_feature_property_write_actions_miss
          (std::move(x.data.write_actions_miss));
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    new (&p.data.apply_actions)
        Table_feature_property_apply_actions(std::move(x.data.apply_actions));
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    new (&p.data.apply_actions_miss)
        Table_feature_property_apply_actions_miss
          (std::move(x.data.apply_actions_miss));
    break;
  case TABLE_FEATURE_PROPERTY_MATCH:
    new (&p.data.match) Table_feature_property_match(std::move(x.data.match));
    break;
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    new (&p.data.wildcards)
        Table_feature_property_wildcards(std::move(x.data.wildcards)); break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    new (&p.data.write_setfield)
        Table_feature_property_write_setfield(std::move(x.data.write_setfield));
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    new (&p.data.write_setfield_miss)
        Table_feature_property_write_setfield_miss
          (std::move(x.data.write_setfield_miss)); break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    new (&p.data.apply_setfield)
        Table_feature_property_apply_setfield(std::move(x.data.apply_setfield));
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    new (&p.data.apply_setfield_miss)
        Table_feature_property_apply_setfield_miss
          (std::move(x.data.apply_setfield_miss));
    break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    new (&p.data.experimenter)
        Table_feature_property_experimenter(std::move(x.data.experimenter));
    break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    new (&p.data.experimenter_miss)
        Table_feature_property_experimenter_miss
          (std::move(x.data.experimenter_miss));
    break;
  default: variant_error(t);
  }
}

void
construct(Table_feature_property_payload& p,
          const Table_feature_property_payload& x,
          Table_feature_property_type t)
{
  p.init = x.init;
  if (not p.init)
    return;
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    new (&p.data.instructions)
        Table_feature_property_instructions(x.data.instructions); break;
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    new (&p.data.instructions_miss)
        Table_feature_property_instructions_miss(x.data.instructions_miss);
    break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    new (&p.data.next_tables)
        Table_feature_property_next_tables(x.data.next_tables); break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    new (&p.data.next_tables_miss)
        Table_feature_property_next_tables_miss(x.data.next_tables_miss);
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    new (&p.data.write_actions)
        Table_feature_property_write_actions(x.data.write_actions); break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    new (&p.data.write_actions_miss)
        Table_feature_property_write_actions_miss(x.data.write_actions_miss);
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    new (&p.data.apply_actions)
        Table_feature_property_apply_actions(x.data.apply_actions); break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    new (&p.data.apply_actions_miss)
        Table_feature_property_apply_actions_miss(x.data.apply_actions_miss);
    break;
  case TABLE_FEATURE_PROPERTY_MATCH:
    new (&p.data.match) Table_feature_property_match(x.data.match); break;
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    new (&p.data.wildcards) Table_feature_property_wildcards(x.data.wildcards);
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    new (&p.data.write_setfield)
        Table_feature_property_write_setfield(x.data.write_setfield); break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    new (&p.data.write_setfield_miss)
        Table_feature_property_write_setfield_miss(x.data.write_setfield_miss);
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    new (&p.data.apply_setfield)
        Table_feature_property_apply_setfield(x.data.apply_setfield); break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    new (&p.data.apply_setfield_miss)
        Table_feature_property_apply_setfield_miss(x.data.apply_setfield_miss);
    break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    new (&p.data.experimenter)
        Table_feature_property_experimenter(x.data.experimenter); break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    new (&p.data.experimenter_miss)
        Table_feature_property_experimenter_miss(x.data.experimenter_miss);
    break;
  default: variant_error(t);
  }
}

void
destroy(Table_feature_property_payload& p, Table_feature_property_type t)
{
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    p.data.instructions.~Table_feature_property_instructions(); break;
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    p.data.instructions_miss.~Table_feature_property_instructions_miss();
    break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    p.data.next_tables.~Table_feature_property_next_tables(); break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    p.data.next_tables_miss.~Table_feature_property_next_tables_miss();
    break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    p.data.write_actions.~Table_feature_property_write_actions(); break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    p.data.write_actions_miss.~Table_feature_property_write_actions_miss();
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    p.data.apply_actions.~Table_feature_property_apply_actions(); break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    p.data.apply_actions_miss.~Table_feature_property_apply_actions_miss();
    break;
  case TABLE_FEATURE_PROPERTY_MATCH:
    p.data.match.~Table_feature_property_match(); break;
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    p.data.wildcards.~Table_feature_property_wildcards(); break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    p.data.write_setfield.~Table_feature_property_write_setfield(); break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    p.data.write_setfield_miss.~Table_feature_property_write_setfield_miss();
    break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    p.data.apply_setfield.~Table_feature_property_apply_setfield(); break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    p.data.apply_setfield_miss.~Table_feature_property_apply_setfield_miss();
    break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    p.data.experimenter.~Table_feature_property_experimenter(); break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    p.data.experimenter_miss.~Table_feature_property_experimenter_miss();
    break;
  default: return;
  }
}

Table_feature_property_payload&
assign(Table_feature_property_payload& a,
       Table_feature_property_payload&& b, Table_feature_property_type t)
{
  if (&a == &b)
    return a;

  if (not a) {
    construct(a, std::move(b), t);
    return a;
  }

  a.init = b.init;
  if (not a.init) {
    destroy(a, t);
    return a;
  }

  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    a.data.instructions = std::move(b.data.instructions); break;
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    a.data.instructions_miss = std::move(b.data.instructions_miss); break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    a.data.next_tables = std::move(b.data.next_tables); break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    a.data.next_tables_miss = std::move(b.data.next_tables_miss); break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    a.data.write_actions = std::move(b.data.write_actions); break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    a.data.write_actions_miss = std::move(b.data.write_actions_miss); break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    a.data.apply_actions = std::move(b.data.apply_actions); break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    a.data.apply_actions_miss = std::move(b.data.apply_actions_miss); break;
  case TABLE_FEATURE_PROPERTY_MATCH:
    a.data.match = std::move(b.data.match); break;
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    a.data.wildcards = std::move(b.data.wildcards); break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    a.data.write_setfield = std::move(b.data.write_setfield); break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    a.data.write_setfield_miss = std::move(b.data.write_setfield_miss); break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    a.data.apply_setfield = std::move(b.data.apply_setfield); break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    a.data.apply_setfield_miss = std::move(b.data.apply_setfield_miss); break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    a.data.experimenter = std::move(b.data.experimenter); break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    a.data.experimenter_miss = std::move(b.data.experimenter_miss); break;
  default: variant_error(t);
  }
  return a;
}

Table_feature_property_payload&
assign(Table_feature_property_payload& a,
       const Table_feature_property_payload& b, Table_feature_property_type t)
{
  if (&a == &b)
    return a;

  if (not a) {
    construct(a, b, t);
    return a;
  }

  a.init = b.init;
  if (not a.init) {
    destroy(a, t);
    return a;
  }

  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    a.data.instructions = b.data.instructions; break;
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    a.data.instructions_miss = b.data.instructions_miss; break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    a.data.next_tables = b.data.next_tables; break;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    a.data.next_tables_miss = b.data.next_tables_miss; break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    a.data.write_actions = b.data.write_actions; break;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    a.data.write_actions_miss = b.data.write_actions_miss; break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    a.data.apply_actions = b.data.apply_actions; break;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    a.data.apply_actions_miss = b.data.apply_actions_miss; break;
  case TABLE_FEATURE_PROPERTY_MATCH:
    a.data.match = b.data.match; break;
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    a.data.wildcards = b.data.wildcards; break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    a.data.write_setfield = b.data.write_setfield; break;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    a.data.write_setfield_miss = b.data.write_setfield_miss; break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    a.data.apply_setfield = b.data.apply_setfield; break;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    a.data.apply_setfield_miss = b.data.apply_setfield_miss; break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    a.data.experimenter = b.data.experimenter; break;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    a.data.experimenter_miss = b.data.experimenter_miss; break;
  default: variant_error(t);
  }
  return a;
}

bool
equal(const Table_feature_property_payload& a,
      const Table_feature_property_payload& b,
      Table_feature_property_type t1, Table_feature_property_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    return a.data.instructions == b.data.instructions;
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    return a.data.instructions_miss == b.data.instructions_miss;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    return a.data.next_tables == b.data.next_tables;
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    return a.data.next_tables_miss == b.data.next_tables_miss;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    return a.data.write_actions == b.data.write_actions;
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    return a.data.write_actions_miss == b.data.write_actions_miss;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    return a.data.apply_actions == b.data.apply_actions;
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    return a.data.apply_actions_miss == b.data.apply_actions_miss;
  case TABLE_FEATURE_PROPERTY_MATCH: return a.data.match == b.data.match;
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    return a.data.wildcards == b.data.wildcards;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    return a.data.write_setfield == b.data.write_setfield;
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    return a.data.write_setfield_miss == b.data.write_setfield_miss;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    return a.data.apply_setfield == b.data.apply_setfield;
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    return a.data.apply_setfield_miss == b.data.apply_setfield_miss;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    return a.data.experimenter == b.data.experimenter;
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    return a.data.experimenter_miss == b.data.experimenter_miss;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Table_feature_property_payload& p, Table_feature_property_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS: return bytes(p.data.instructions);
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    return bytes(p.data.instructions_miss);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES: return bytes(p.data.next_tables);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    return bytes(p.data.next_tables_miss);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    return bytes(p.data.write_actions);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    return bytes(p.data.write_actions_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    return bytes(p.data.apply_actions);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    return bytes(p.data.apply_actions_miss);
  case TABLE_FEATURE_PROPERTY_MATCH: return bytes(p.data.match);
  case TABLE_FEATURE_PROPERTY_WILDCARDS: return bytes(p.data.wildcards);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    return bytes(p.data.write_setfield);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    return bytes(p.data.write_setfield_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    return bytes(p.data.apply_setfield);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    return bytes(p.data.apply_setfield_miss);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    return bytes(p.data.experimenter);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    return bytes(p.data.experimenter_miss);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Table_feature_property_payload& p, Table_feature_property_type t)
{
  if (not p)
    return BAD_TABLE_FEATURE_PROPERTY_INIT;
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    return is_valid(p.data.instructions);
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    return is_valid(p.data.instructions_miss);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES: return is_valid(p.data.next_tables);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    return is_valid(p.data.next_tables_miss);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    return is_valid(p.data.write_actions);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    return is_valid(p.data.write_actions_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    return is_valid(p.data.apply_actions);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    return is_valid(p.data.apply_actions_miss);
  case TABLE_FEATURE_PROPERTY_MATCH: return is_valid(p.data.match);
  case TABLE_FEATURE_PROPERTY_WILDCARDS: return is_valid(p.data.wildcards);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    return is_valid(p.data.write_setfield);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    return is_valid(p.data.write_setfield_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    return is_valid(p.data.apply_setfield);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    return is_valid(p.data.apply_setfield_miss);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    return is_valid(p.data.experimenter);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    return is_valid(p.data.experimenter_miss);
  default: variant_error(t);
  }
  return BAD_TABLE_FEATURE_PROPERTY;
}

Error_condition
to_buffer(Buffer_view& v, const Table_feature_property_payload& p,
          Table_feature_property_type t)
{
  assert(p);
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    return to_buffer(v, p.data.instructions);
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    return to_buffer(v, p.data.instructions_miss);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    return to_buffer(v, p.data.next_tables);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    return to_buffer(v, p.data.next_tables_miss);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    return to_buffer(v, p.data.write_actions);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    return to_buffer(v, p.data.write_actions_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    return to_buffer(v, p.data.apply_actions);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    return to_buffer(v, p.data.apply_actions_miss);
  case TABLE_FEATURE_PROPERTY_MATCH: return to_buffer(v, p.data.match);
  case TABLE_FEATURE_PROPERTY_WILDCARDS: return to_buffer(v, p.data.wildcards);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    return to_buffer(v, p.data.write_setfield);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    return to_buffer(v, p.data.write_setfield_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    return to_buffer(v, p.data.apply_setfield);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    return to_buffer(v, p.data.apply_setfield_miss);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    return to_buffer(v, p.data.experimenter);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    return to_buffer(v, p.data.experimenter_miss);
  default: variant_error(t);
  }
  return BAD_TABLE_FEATURE_PROPERTY;
}

Error_condition
from_buffer(Buffer_view& v, Table_feature_property_payload& p,
            Table_feature_property_type t)
{
  assert(p);
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    return from_buffer(v, p.data.instructions);
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    return from_buffer(v, p.data.instructions_miss);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    return from_buffer(v, p.data.next_tables);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    return from_buffer(v, p.data.next_tables_miss);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    return from_buffer(v, p.data.write_actions);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    return from_buffer(v, p.data.write_actions_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    return from_buffer(v, p.data.apply_actions);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    return from_buffer(v, p.data.apply_actions_miss);
  case TABLE_FEATURE_PROPERTY_MATCH: return from_buffer(v, p.data.match);
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    return from_buffer(v, p.data.wildcards);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    return from_buffer(v, p.data.write_setfield);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    return from_buffer(v, p.data.write_setfield_miss);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    return from_buffer(v, p.data.apply_setfield);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    return from_buffer(v, p.data.apply_setfield_miss);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    return from_buffer(v, p.data.experimenter);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    return from_buffer(v, p.data.experimenter_miss);
  default: variant_error(t);
  }
  return BAD_TABLE_FEATURE_PROPERTY;
}

std::string
to_string(const Table_feature_property_payload& p, Formatter& fmt,
          Table_feature_property_type t)
{
  assert(p);
  switch (t) {
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS:
    return to_string(p.data.instructions, fmt);
  case TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS:
    return to_string(p.data.instructions_miss, fmt);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES:
    return to_string(p.data.next_tables, fmt);
  case TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS:
    return to_string(p.data.next_tables_miss, fmt);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS:
    return to_string(p.data.write_actions, fmt);
  case TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS:
    return to_string(p.data.write_actions_miss, fmt);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS:
    return to_string(p.data.apply_actions, fmt);
  case TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS:
    return to_string(p.data.apply_actions_miss, fmt);
  case TABLE_FEATURE_PROPERTY_MATCH: return to_string(p.data.match, fmt);
  case TABLE_FEATURE_PROPERTY_WILDCARDS:
    return to_string(p.data.wildcards, fmt);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD:
    return to_string(p.data.write_setfield, fmt);
  case TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS:
    return to_string(p.data.write_setfield_miss, fmt);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD:
    return to_string(p.data.apply_setfield, fmt);
  case TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS:
    return to_string(p.data.apply_setfield_miss, fmt);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER:
    return to_string(p.data.experimenter, fmt);
  case TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS:
    return to_string(p.data.experimenter_miss, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Table feature property header

//inline bool
//check_header(const Buffer_view& v, const Table_feature_property_header& h)
//{
//  return is_valid(h) and available(v, h.length - bytes(h));
//}

std::string
to_string(const Table_feature_property_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.length);

  close_block(ss, f, "Table Feature Property Hdr");
  return ss.str();
}

Error_condition
to_buffer(Buffer_view& v, const Table_feature_property_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Table_feature_property_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.length);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Table feature property

Error_condition
to_buffer(Buffer_view& v, const Table_feature_property& tfp)
{
  if (not available(v, bytes(tfp.header)))
    return AVAILABLE_TABLE_FEATURE_PROPERTY;

  to_buffer(v, tfp.header);
  //if (not check_header(v, tfp.header))
    //return false;

  return to_buffer(v, tfp.payload, tfp.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Table_feature_property& tfp)
{
  if (not available(v, bytes(tfp.header)))
    return AVAILABLE_TABLE_FEATURE_PROPERTY;
  from_buffer(v, tfp.header);

  if (Error_decl err = is_valid(tfp.header.type))
    return err;

  Table_feature_property::Payload p;
  construct(p, tfp.header.type);
  assign(tfp.payload, std::move(p), tfp.header.type);

  if (Error_decl err = is_valid(tfp.header))
    return err;

  std::size_t n = tfp.header.length - bytes(tfp.header);
  if (remaining(v) < n)
    return AVAILABLE_TABLE_FEATURE_PROPERTY_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, tfp.payload, tfp.header.type))
    return err;

  if (not update(v, c))
    return EXCESS_TABLE_FEATURE_PROPERTY;

  return SUCCESS;
}

std::string
to_string(const Table_feature_property& tfp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Table Feature Property");

  ss << to_string(tfp.header, f);
  if (is_valid(tfp.header))
    ss << to_string(tfp.payload, f, tfp.header.type);

  close_block(ss, f, "Table Feature Property");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Table feature

Error_condition
to_buffer(Buffer_view& v, const Multipart_req_table_feature& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_REQ_TABLE_FEATURE;

  to_buffer(v, mrtf.length);
  to_buffer(v, mrtf.table_id);
  pad(v, 5);
  to_buffer(v, mrtf.name);
  to_buffer(v, mrtf.metadata_match);
  to_buffer(v, mrtf.metadata_write);
  to_buffer(v, mrtf.config);
  to_buffer(v, mrtf.max_entries);

  if (Error_decl err = to_buffer(v, mrtf.properties))
    return err;

  uint8_t padding = 8 - (mrtf.length % 8);
  if (padding == 8)
    return SUCCESS;

  if (not available(v, padding))
    return AVAILABLE_MULTIPART_REQ_TABLE_FEATURE_PADDING;

  pad(v, padding);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req_table_feature& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_REQ_TABLE_FEATURE;

  from_buffer(v, mrtf.length);
  from_buffer(v, mrtf.table_id);
  pad(v, 5);
  from_buffer(v, mrtf.name);
  from_buffer(v, mrtf.metadata_match);
  from_buffer(v, mrtf.metadata_write);
  from_buffer(v, mrtf.config);
  from_buffer(v, mrtf.max_entries);

  std::size_t n = mrtf.length - 64;

  if (remaining(v) < n)
    return AVAILABLE_TABLE_FEATURE_PROPERTY;
  Buffer_view c = constrain(v, n);

  if (Error_decl err = from_buffer(c, mrtf.properties))
    return err;

  if (not update(v, c))
    return EXCESS_MULTIPART_REQ_TABLE_FEATURE;

  uint8_t padding = 8 - (mrtf.length % 8);
  if (padding == 8)
    return SUCCESS;

  if (not available(v, padding))
    return AVAILABLE_MULTIPART_REQ_TABLE_FEATURE_PADDING;

  pad(v, padding);
  return SUCCESS;
}

std::string
to_string(const Multipart_req_table_feature& mrtf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq TableFeature");

  nvp_to_string(ss, f, "Length", mrtf.length);
  nvp_to_string(ss, f, "Table ID", mrtf.table_id);
  nvp_to_string(ss, f, "Name", mrtf.name.str());
  nvp_to_string(ss, f, "Metadata Match", mrtf.metadata_match);
  nvp_to_string(ss, f, "Metadata Write", mrtf.metadata_write);
  nvp_to_string(ss, f, "Config", mrtf.config);
  nvp_to_string(ss, f, "Max Entries", mrtf.max_entries);

  ss << to_string(mrtf.properties, f);

  close_block(ss, f, "MultipartReq TableFeature");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response: Table features

Error_condition
to_buffer(Buffer_view& v, const Multipart_req_table_features& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURES;
  return to_buffer(v, mrtf.table_features);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req_table_features& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURES;
  return from_buffer(v, mrtf.table_features);
}

std::string
to_string(const Multipart_req_table_features& mrtf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq TableFeatures");

  ss << to_string(mrtf.table_features, f);

  close_block(ss, f, "MultipartReq TableFeatures");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request: Experimenter

Error_condition
to_buffer(Buffer_view& v, const Multipart_req_experimenter& mre)
{
  if (not available(v, bytes(mre)))
    return AVAILABLE_MULTIPART_RES_EXPERIMENTER;
  to_buffer(v, mre.experimenter_id);
  to_buffer(v, mre.exp_type);
  return to_buffer(v, mre.data);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req_experimenter& mre)
{
  if (not available(v, bytes(mre)))
    return AVAILABLE_MULTIPART_RES_EXPERIMENTER;
  from_buffer(v, mre.experimenter_id);
  from_buffer(v, mre.exp_type);
  return from_buffer(v, mre.data);
}

std::string
to_string(const Multipart_req_experimenter& sre, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq Experimenter");

  nvp_to_string(ss, f, "Experimenter ID", sre.experimenter_id);
  nvp_to_string(ss, f, "Experimenter ID", sre.exp_type);
  nvp_to_string(ss, f, "Data bytes", bytes(sre.data));

  close_block(ss, f, "MultipartReq Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request Payload

void
construct(Multipart_req_payload& p, Multipart_type t)
{
  p.init = true;
  switch(t) {
  case MULTIPART_DESC: new (&p.data.desc) Multipart_req_desc(); break;
  case MULTIPART_FLOW: new (&p.data.flow) Multipart_req_flow(); break;
  case MULTIPART_AGGREGATE: new (&p.data.aggregate) Multipart_req_aggregate();
    break;
  case MULTIPART_TABLE: new (&p.data.table) Multipart_req_table(); break;
  case MULTIPART_PORT: new (&p.data.port) Multipart_req_port(); break;
  case MULTIPART_QUEUE: new (&p.data.queue) Multipart_req_queue(); break;
  case MULTIPART_GROUP: new (&p.data.group) Multipart_req_group(); break;
  case MULTIPART_GROUP_DESC:
    new (&p.data.group_desc) Multipart_req_group_desc(); break;
  case MULTIPART_GROUP_FEATURES:
    new (&p.data.group_features) Multipart_req_group_features(); break;
  case MULTIPART_METER: new (&p.data.meter) Multipart_req_meter(); break;
  case MULTIPART_METER_CONFIG:
    new (&p.data.meter_config) Multipart_req_meter_config(); break;
  case MULTIPART_METER_FEATURES:
    new (&p.data.meter_features) Multipart_req_meter_features(); break;
  case MULTIPART_TABLE_FEATURES:
    new (&p.data.table_features) Multipart_req_table_features(); break;
  case MULTIPART_PORT_DESC: new (&p.data.port_desc) Multipart_req_port_desc();
    break;
  case MULTIPART_EXPERIMENTER:
    new (&p.data.experimenter) Multipart_req_experimenter(); break;
  default: variant_error(t);
  }
}

void
construct(Multipart_req_payload& p, Multipart_req_payload&& x,
          Multipart_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case MULTIPART_DESC:
    new (&p.data.desc) Multipart_req_desc(std::move(x.data.desc)); break;
  case MULTIPART_FLOW:
    new (&p.data.flow) Multipart_req_flow(std::move(x.data.flow)); break;
  case MULTIPART_AGGREGATE:
    new (&p.data.aggregate)
        Multipart_req_aggregate(std::move(x.data.aggregate)); break;
  case MULTIPART_TABLE:
    new (&p.data.table) Multipart_req_table(std::move(x.data.table)); break;
  case MULTIPART_PORT:
    new (&p.data.port) Multipart_req_port(std::move(x.data.port)); break;
  case MULTIPART_QUEUE:
    new (&p.data.queue) Multipart_req_queue(std::move(x.data.queue)); break;
  case MULTIPART_GROUP:
    new (&p.data.group) Multipart_req_group(std::move(x.data.group)); break;
  case MULTIPART_GROUP_DESC:
    new (&p.data.group_desc)
        Multipart_req_group_desc(std::move(x.data.group_desc)); break;
  case MULTIPART_GROUP_FEATURES:
    new (&p.data.group_features)
        Multipart_req_group_features(std::move(x.data.group_features)); break;
  case MULTIPART_METER:
    new (&p.data.meter) Multipart_req_meter(std::move(x.data.meter)); break;
  case MULTIPART_METER_CONFIG:
    new (&p.data.meter_config)
         Multipart_req_meter_config(std::move(x.data.meter_config)); break;
  case MULTIPART_METER_FEATURES:
    new (&p.data.meter_features)
         Multipart_req_meter_features(std::move(x.data.meter_features)); break;
  case MULTIPART_TABLE_FEATURES:
    new (&p.data.table_features)
         Multipart_req_table_features(std::move(x.data.table_features)); break;
  case MULTIPART_PORT_DESC:
    new (&p.data.port_desc)
        Multipart_req_port_desc(std::move(x.data.port_desc)); break;
  case MULTIPART_EXPERIMENTER:
    new (&p.data.experimenter)
        Multipart_req_experimenter(std::move(x.data.experimenter)); break;
  default: variant_error(t);
  }
}

void
construct(Multipart_req_payload& p, const Multipart_req_payload& x,
          Multipart_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case MULTIPART_DESC: new (&p.data.desc) Multipart_req_desc(x.data.desc);
    break;
  case MULTIPART_FLOW: new (&p.data.flow) Multipart_req_flow(x.data.flow);
    break;
  case MULTIPART_AGGREGATE:
    new (&p.data.aggregate) Multipart_req_aggregate(x.data.aggregate); break;
  case MULTIPART_TABLE: new (&p.data.table) Multipart_req_table(x.data.table);
    break;
  case MULTIPART_PORT: new (&p.data.port) Multipart_req_port(x.data.port);
    break;
  case MULTIPART_QUEUE: new (&p.data.queue) Multipart_req_queue(x.data.queue);
    break;
  case MULTIPART_GROUP: new (&p.data.group) Multipart_req_group(x.data.group);
    break;
  case MULTIPART_GROUP_DESC:
    new (&p.data.group_desc) Multipart_req_group_desc(x.data.group_desc);
    break;
  case MULTIPART_GROUP_FEATURES:
    new (&p.data.group_features)
        Multipart_req_group_features(x.data.group_features); break;
  case MULTIPART_METER: new (&p.data.meter) Multipart_req_meter(x.data.meter);
    break;
  case MULTIPART_METER_CONFIG:
    new (&p.data.meter_config)
         Multipart_req_meter_config(x.data.meter_config); break;
  case MULTIPART_METER_FEATURES:
    new (&p.data.meter_features)
         Multipart_req_meter_features(x.data.meter_features); break;
  case MULTIPART_TABLE_FEATURES:
    new (&p.data.table_features)
         Multipart_req_table_features(x.data.table_features); break;
  case MULTIPART_PORT_DESC:
    new (&p.data.port_desc) Multipart_req_port_desc(x.data.port_desc); break;
  case MULTIPART_EXPERIMENTER:
    new (&p.data.experimenter) Multipart_req_experimenter(x.data.experimenter);
    break;
  default: variant_error(t);
  }
}

void
destroy(Multipart_req_payload& p, Multipart_type t)
{
  switch(t) {
  case MULTIPART_DESC: p.data.desc.~Multipart_req_desc(); break;
  case MULTIPART_FLOW: p.data.flow.~Multipart_req_flow(); break;
  case MULTIPART_AGGREGATE: p.data.aggregate.~Multipart_req_aggregate();
    break;
  case MULTIPART_TABLE: p.data.table.~Multipart_req_table(); break;
  case MULTIPART_PORT: p.data.port.~Multipart_req_port(); break;
  case MULTIPART_QUEUE: p.data.queue.~Multipart_req_queue(); break;
  case MULTIPART_GROUP: p.data.group.~Multipart_req_group(); break;
  case MULTIPART_GROUP_DESC: p.data.group_desc.~Multipart_req_group_desc();
    break;
  case MULTIPART_GROUP_FEATURES:
    p.data.group_features.~Multipart_req_group_features(); break;
  case MULTIPART_METER: p.data.meter.~Multipart_req_meter(); break;
  case MULTIPART_METER_CONFIG:
    p.data.meter_config.~Multipart_req_meter_config(); break;
  case MULTIPART_METER_FEATURES:
    p.data.meter_features.~Multipart_req_meter_features(); break;
  case MULTIPART_TABLE_FEATURES:
    p.data.table_features.~Multipart_req_table_features(); break;
  case MULTIPART_PORT_DESC: p.data.port_desc.~Multipart_req_port_desc(); break;
  case MULTIPART_EXPERIMENTER:
    p.data.experimenter.~Multipart_req_experimenter(); break;
  default: return;
  }
}

Multipart_req_payload&
assign(Multipart_req_payload& p, Multipart_req_payload&& x, Multipart_type t)
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
  case MULTIPART_DESC: p.data.desc = std::move(x.data.desc); break;
  case MULTIPART_FLOW: p.data.flow = std::move(x.data.flow); break;
  case MULTIPART_AGGREGATE: p.data.aggregate = std::move(x.data.aggregate);
    break;
  case MULTIPART_TABLE: p.data.table = std::move(x.data.table); break;
  case MULTIPART_PORT: p.data.port = std::move(x.data.port); break;
  case MULTIPART_QUEUE: p.data.queue = std::move(x.data.queue); break;
  case MULTIPART_GROUP: p.data.group = std::move(x.data.group); break;
  case MULTIPART_GROUP_DESC: p.data.group_desc = std::move(x.data.group_desc);
    break;
  case MULTIPART_GROUP_FEATURES:
    p.data.group_features = std::move(x.data.group_features); break;
  case MULTIPART_METER: p.data.meter = std::move(x.data.meter); break;
  case MULTIPART_METER_CONFIG:
    p.data.meter_config = std::move(x.data.meter_config); break;
  case MULTIPART_METER_FEATURES:
    p.data.meter_features = std::move(x.data.meter_features); break;
  case MULTIPART_TABLE_FEATURES:
    p.data.table_features = std::move(x.data.table_features); break;
  case MULTIPART_PORT_DESC: p.data.port_desc = std::move(x.data.port_desc);
    break;
  case MULTIPART_EXPERIMENTER:
    p.data.experimenter = std::move(x.data.experimenter); break;
  default: variant_error(t);
  }
  return p;
}

Multipart_req_payload&
assign(Multipart_req_payload& p, const Multipart_req_payload& x,
       Multipart_type t)
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
  case MULTIPART_DESC: p.data.desc = x.data.desc; break;
  case MULTIPART_FLOW: p.data.flow = x.data.flow; break;
  case MULTIPART_AGGREGATE: p.data.aggregate = x.data.aggregate; break;
  case MULTIPART_TABLE: p.data.table = x.data.table; break;
  case MULTIPART_PORT: p.data.port = x.data.port; break;
  case MULTIPART_QUEUE: p.data.queue = x.data.queue; break;
  case MULTIPART_GROUP: p.data.group = x.data.group; break;
  case MULTIPART_GROUP_DESC: p.data.group_desc = x.data.group_desc; break;
  case MULTIPART_GROUP_FEATURES: p.data.group_features = x.data.group_features;
    break;
  case MULTIPART_METER: p.data.meter = x.data.meter; break;
  case MULTIPART_METER_CONFIG: p.data.meter_config = x.data.meter_config;
    break;
  case MULTIPART_METER_FEATURES: p.data.meter_features = x.data.meter_features;
    break;
  case MULTIPART_TABLE_FEATURES: p.data.table_features = x.data.table_features;
    break;
  case MULTIPART_PORT_DESC: p.data.port_desc = x.data.port_desc; break;
  case MULTIPART_EXPERIMENTER: p.data.experimenter = x.data.experimenter;
    break;
  default: variant_error(t);
  }
  return p;
}

bool
equal(const Multipart_req_payload& a, const Multipart_req_payload& b,
      Multipart_type t1, Multipart_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case MULTIPART_DESC: return a.data.desc == b.data.desc;
  case MULTIPART_FLOW: return a.data.flow == b.data.flow;
  case MULTIPART_AGGREGATE: return a.data.aggregate == b.data.aggregate;
  case MULTIPART_TABLE: return a.data.table == b.data.table;
  case MULTIPART_PORT: return a.data.port == b.data.port;
  case MULTIPART_QUEUE: return a.data.queue == b.data.queue;
  case MULTIPART_GROUP: return a.data.group == b.data.group;
  case MULTIPART_GROUP_DESC: return a.data.group_desc == b.data.group_desc;
  case MULTIPART_GROUP_FEATURES:
    return a.data.group_features == b.data.group_features;
  case MULTIPART_METER: return a.data.meter == b.data.meter;
  case MULTIPART_METER_CONFIG:
    return a.data.meter_config == b.data.meter_config;
  case MULTIPART_METER_FEATURES:
    return a.data.meter_features == b.data.meter_features;
  case MULTIPART_TABLE_FEATURES:
    return a.data.table_features == b.data.table_features;
  case MULTIPART_PORT_DESC: return a.data.port_desc == b.data.port_desc;
  case MULTIPART_EXPERIMENTER:
    return a.data.experimenter == b.data.experimenter;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Multipart_req_payload& p, Multipart_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case MULTIPART_DESC: return bytes(p.data.desc);
  case MULTIPART_FLOW: return bytes(p.data.flow);
  case MULTIPART_AGGREGATE: return bytes(p.data.aggregate);
  case MULTIPART_TABLE: return bytes(p.data.table);
  case MULTIPART_PORT: return bytes(p.data.port);
  case MULTIPART_QUEUE: return bytes(p.data.queue);
  case MULTIPART_GROUP: return bytes(p.data.group);
  case MULTIPART_GROUP_DESC: return bytes(p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return bytes(p.data.group_features);
  case MULTIPART_METER: return bytes(p.data.meter);
  case MULTIPART_METER_CONFIG: return bytes(p.data.meter_config);
  case MULTIPART_METER_FEATURES: return bytes(p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return bytes(p.data.table_features);
  case MULTIPART_PORT_DESC: return bytes(p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Multipart_req_payload& p, Multipart_type t)
{
  if (not p)
    return BAD_MULTIPART_INIT;
  switch (t) {
  case MULTIPART_DESC: return is_valid(p.data.desc);
  case MULTIPART_FLOW: return is_valid(p.data.flow);
  case MULTIPART_AGGREGATE: return is_valid(p.data.aggregate);
  case MULTIPART_TABLE: return is_valid(p.data.table);
  case MULTIPART_PORT: return is_valid(p.data.port);
  case MULTIPART_QUEUE: return is_valid(p.data.queue);
  case MULTIPART_GROUP: return is_valid(p.data.group);
  case MULTIPART_GROUP_DESC: return is_valid(p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return is_valid(p.data.group_features);
  case MULTIPART_METER: return is_valid(p.data.meter);
  case MULTIPART_METER_CONFIG: return is_valid(p.data.meter_config);
  case MULTIPART_METER_FEATURES: return is_valid(p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return is_valid(p.data.table_features);
  case MULTIPART_PORT_DESC: return is_valid(p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return is_valid(p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_MULTIPART;
}

Error_condition
to_buffer(Buffer_view& v, const Multipart_req_payload& p, Multipart_type t)
{
  assert(p);
  switch (t) {
  case MULTIPART_DESC: return to_buffer(v, p.data.desc);
  case MULTIPART_FLOW: return to_buffer(v, p.data.flow);
  case MULTIPART_AGGREGATE: return to_buffer(v, p.data.aggregate);
  case MULTIPART_TABLE: return to_buffer(v, p.data.table);
  case MULTIPART_PORT: return to_buffer(v, p.data.port);
  case MULTIPART_QUEUE: return to_buffer(v, p.data.queue);
  case MULTIPART_GROUP: return to_buffer(v, p.data.group);
  case MULTIPART_GROUP_DESC: return to_buffer(v, p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return to_buffer(v, p.data.group_features);
  case MULTIPART_METER: return to_buffer(v, p.data.meter);
  case MULTIPART_METER_CONFIG: return to_buffer(v, p.data.meter_config);
  case MULTIPART_METER_FEATURES: return to_buffer(v, p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return to_buffer(v, p.data.table_features);
  case MULTIPART_PORT_DESC: return to_buffer(v, p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_MULTIPART;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req_payload& p, Multipart_type t)
{
  assert(p);
  switch (t) {
  case MULTIPART_DESC: return from_buffer(v, p.data.desc);
  case MULTIPART_FLOW: return from_buffer(v, p.data.flow);
  case MULTIPART_AGGREGATE: return from_buffer(v, p.data.aggregate);
  case MULTIPART_TABLE: return from_buffer(v, p.data.table);
  case MULTIPART_PORT: return from_buffer(v, p.data.port);
  case MULTIPART_QUEUE: return from_buffer(v, p.data.queue);
  case MULTIPART_GROUP: return from_buffer(v, p.data.group);
  case MULTIPART_GROUP_DESC: return from_buffer(v, p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return from_buffer(v, p.data.group_features);
  case MULTIPART_METER: return from_buffer(v, p.data.meter);
  case MULTIPART_METER_CONFIG: return from_buffer(v, p.data.meter_config);
  case MULTIPART_METER_FEATURES: return from_buffer(v, p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return from_buffer(v, p.data.table_features);
  case MULTIPART_PORT_DESC: return from_buffer(v, p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_MULTIPART;
}

std::string
to_string(const Multipart_req_payload& p, Formatter& fmt, Multipart_type t)
{
  assert(p);
  switch (t) {
  case MULTIPART_DESC: return to_string(p.data.desc, fmt);
  case MULTIPART_FLOW: return to_string(p.data.flow, fmt);
  case MULTIPART_AGGREGATE: return to_string(p.data.aggregate, fmt);
  case MULTIPART_TABLE: return to_string(p.data.table, fmt);
  case MULTIPART_PORT: return to_string(p.data.port, fmt);
  case MULTIPART_QUEUE: return to_string(p.data.queue, fmt);
  case MULTIPART_GROUP: return to_string(p.data.group, fmt);
  case MULTIPART_GROUP_DESC: return to_string(p.data.group_desc, fmt);
  case MULTIPART_GROUP_FEATURES: return to_string(p.data.group_features, fmt);
  case MULTIPART_METER: return to_string(p.data.meter, fmt);
  case MULTIPART_METER_CONFIG: return to_string(p.data.meter_config, fmt);
  case MULTIPART_METER_FEATURES: return to_string(p.data.meter_features, fmt);
  case MULTIPART_TABLE_FEATURES: return to_string(p.data.table_features, fmt);
  case MULTIPART_PORT_DESC: return to_string(p.data.port_desc, fmt);
  case MULTIPART_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Multipart: Header

/*
inline bool
check_header(const Multipart_header& h)
{
  return is_valid(h.type);
}
*/

Error_condition
to_buffer(Buffer_view& v, const Multipart_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.flags);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.flags);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Multipart_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Multipart Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Flags", to_string(h.flags));

  close_block(ss, f, "Multipart Hdr");
  return ss.str();
}

std::string
to_string(Multipart_header::Flags f)
{
  std::stringstream ss;
  if (f & Multipart_header::MORE)
    ss << "More";
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Request

Error_condition
to_buffer(Buffer_view& v, const Multipart_req& r)
{
  if (not available(v, bytes(r.header)))
    return AVAILABLE_MULTIPART_HEADER;
  to_buffer(v, r.header);
  return to_buffer(v, r.payload, r.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_req& r)
{
  if (not available(v, bytes(r.header)))
    return AVAILABLE_MULTIPART_HEADER;
  from_buffer(v, r.header);

  if (Error_decl err = is_valid(r.header.type))
    return err;

  Multipart_req::Payload p;
  construct(p, r.header.type);
  assign(r.payload, std::move(p), r.header.type);

  return from_buffer(v, r.payload, r.header.type);
}

std::string
to_string(const Multipart_req& r, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartReq");

  ss << to_string(r.header, f);
  if (is_valid(r.header.type))
    ss << to_string(r.payload, f,r.header.type);
  else
    ss << "Malformed payload";

  close_block(ss, f, "MultipartReq");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Description

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_desc& d)
{
  if (not available(v, bytes(d)))
    return AVAILABLE_MULTIPART_RES_DESC;
  to_buffer(v, d.mfr_desc);
  to_buffer(v, d.hw_desc);
  to_buffer(v, d.sw_desc);
  to_buffer(v, d.serial_num);
  to_buffer(v, d.dp_desc);

  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_desc& d)
{
  if (not available (v, bytes(d)))
    return AVAILABLE_MULTIPART_RES_DESC;
  from_buffer(v, d.mfr_desc);
  from_buffer(v, d.hw_desc);
  from_buffer(v, d.sw_desc);
  from_buffer(v, d.serial_num);
  from_buffer(v, d.dp_desc);

  return SUCCESS;
}

std::string to_string(const Multipart_res_desc& d, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Description");

  nvp_to_string(ss, f, "Manufacturer Description", d.mfr_desc.str());
  nvp_to_string(ss, f, "Hardware Description", d.hw_desc.str());
  nvp_to_string(ss, f, "Softwrae Description", d.sw_desc.str());
  nvp_to_string(ss, f, "Datapath Description", d.dp_desc.str());
  nvp_to_string(ss, f, "Serial Number", d.serial_num.str());

  close_block(ss, f, "MultipartRes Description");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Flow

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_flow& f)
{
  if (not available (v, bytes(f)))
    return AVAILABLE_MULTIPART_RES_FLOW;

  to_buffer(v, f.length);
  to_buffer(v, f.table_id);
  pad(v, 1);
  to_buffer(v, f.duration_sec);
  to_buffer(v, f.duration_nsec);
  to_buffer(v, f.priority);
  to_buffer(v, f.idle_timeout);
  to_buffer(v, f.hard_timeout);
  to_buffer(v, f.flags);
  pad(v, 4);
  to_buffer(v, f.cookie);
  to_buffer(v, f.packet_count);
  to_buffer(v, f.byte_count);

  if (Error_decl err = to_buffer(v, f.match))
    return err;

  return to_buffer(v, f.instructions);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_flow& f)
{
  if (not available (v, bytes(f)))
    return AVAILABLE_MULTIPART_RES_FLOW;

  from_buffer(v, f.length);
  from_buffer(v, f.table_id);
  pad(v, 1);
  from_buffer(v, f.duration_sec);
  from_buffer(v, f.duration_nsec);
  from_buffer(v, f.priority);
  from_buffer(v, f.idle_timeout);
  from_buffer(v, f.hard_timeout);
  from_buffer(v, f.flags);
  pad(v, 4);
  from_buffer(v, f.cookie);
  from_buffer(v, f.packet_count);
  from_buffer(v, f.byte_count);

  std::size_t n = f.length - 48;

  if (remaining(v) < n)
    return AVAILABLE_MATCH;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, f.match))
    return err;

  if (Error_decl err = from_buffer(c, f.instructions))
    return err;
  if (not update(v, c))
    return EXCESS_MULTIPART_RES_FLOW;
  return SUCCESS;
}

std::string
to_string(const Multipart_res_flow& srf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Flow");

  nvp_to_string(ss, f, "Length", srf.length);
  nvp_to_string(ss, f, "Table ID", srf.table_id);
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

  close_block(ss, f, "MultipartRes Flow");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Flows

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_flows& mrf)
{
  if (not available (v, bytes(mrf)))
    return AVAILABLE_MULTIPART_RES_FLOWS;
  return to_buffer(v, mrf.flows);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_flows& mrf)
{
  if (not available (v, bytes(mrf)))
    return AVAILABLE_MULTIPART_RES_FLOWS;
  return from_buffer(v, mrf.flows);
}

std::string
to_string(const Multipart_res_flows& mrf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Flows");

  ss << to_string(mrf.flows, f);

  close_block(ss, f, "MultipartRes Flows");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Aggregate

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_aggregate& a)
{
  if (not available (v, bytes(a)))
    return AVAILABLE_MULTIPART_RES_AGGREGATE;
  to_buffer(v, a.packet_count);
  to_buffer(v, a.byte_count);
  to_buffer(v, a.flow_count);
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_aggregate& a)
{
  if (not available (v, bytes(a)))
    return AVAILABLE_MULTIPART_RES_AGGREGATE;
  from_buffer(v, a.packet_count);
  from_buffer(v, a.byte_count);
  from_buffer(v, a.flow_count);
  pad(v, 4);
  return SUCCESS;
}

std::string
to_string(const Multipart_res_aggregate& a, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Aggregate");

  nvp_to_string(ss, f, "Packet Count", a.packet_count);
  nvp_to_string(ss, f, "Byte Count", a.byte_count);
  nvp_to_string(ss, f, "Flow Count", a.flow_count);

  close_block(ss, f, "MultipartRes Aggregate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Port

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_port& p)
{
  if (not available (v, bytes(p)))
    return AVAILABLE_MULTIPART_RES_PORT;
  to_buffer(v, p.port_no);
  pad(v, 4);
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
  to_buffer(v, p.duration_sec);
  to_buffer(v, p.duration_nsec);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_port& p)
{
  if (not available (v, bytes(p)))
    return AVAILABLE_MULTIPART_RES_PORT;
  from_buffer(v, p.port_no);
  pad(v, 4);
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
  from_buffer(v, p.duration_sec);
  from_buffer(v, p.duration_nsec);
  return SUCCESS;
}

std::string
to_string(const Multipart_res_port& p, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Port");

  nvp_to_string(ss, f, "Port No", p.port_no);
  nvp_to_string(ss, f, "Rx Packets", p.rx_packets);
  nvp_to_string(ss, f, "Tx Packets", p.tx_packets);
  nvp_to_string(ss, f, "Rx Bytes", p.rx_bytes);
  nvp_to_string(ss, f, "Tx Bytes", p.tx_bytes);
  nvp_to_string(ss, f, "Rx Dropped", p.rx_dropped);
  nvp_to_string(ss, f, "Tx Dropped", p.tx_dropped);
  nvp_to_string(ss, f, "Rx Errors", p.rx_errors);
  nvp_to_string(ss, f, "Tx Errors", p.tx_errors);
  nvp_to_string(ss, f, "Rx Frame Error", p.rx_frame_err);
  nvp_to_string(ss, f, "Rx Over Error", p.rx_over_err);
  nvp_to_string(ss, f, "Rx CRC Error", p.rx_crc_err);
  nvp_to_string(ss, f, "Collisions", p.collisions);
  nvp_to_string(ss, f, "Duration in Seconds", p.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoseconds", p.duration_nsec);

  close_block(ss, f, "MultipartRes Port");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Ports

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_ports& mrp)
{
  if (not available(v, bytes(mrp)))
    return AVAILABLE_MULTIPART_RES_PORTS;
  return to_buffer(v, mrp.ports);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_ports& mrp)
{
  if (not available(v, bytes(mrp)))
    return AVAILABLE_MULTIPART_RES_PORTS;
  return from_buffer(v, mrp.ports);
}

std::string
to_string(const Multipart_res_ports& mrp, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Ports");

  ss << to_string(mrp.ports, f);

  close_block(ss, f, "MultipartRes Ports");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Queue

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_queue& q)
{
  if (not available(v, bytes(q)))
    return AVAILABLE_MULTIPART_RES_QUEUE;
  to_buffer(v, q.port_no);
  to_buffer(v, q.queue_id);
  to_buffer(v, q.tx_bytes);
  to_buffer(v, q.tx_packets);
  to_buffer(v, q.tx_errors);
  to_buffer(v, q.duration_sec);
  to_buffer(v, q.duration_nsec);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_queue& q)
{
  if (not available(v, bytes(q)))
    return AVAILABLE_MULTIPART_RES_QUEUE;
  from_buffer(v, q.port_no);
  from_buffer(v, q.queue_id);
  from_buffer(v, q.tx_bytes);
  from_buffer(v, q.tx_packets);
  from_buffer(v, q.tx_errors);
  from_buffer(v, q.duration_sec);
  from_buffer(v, q.duration_nsec);
  return SUCCESS;
}

std::string
to_string(const Multipart_res_queue& q, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Queue");

  nvp_to_string(ss, f, "Port No", q.port_no);
  nvp_to_string(ss, f, "Queue ID", q.queue_id);
  nvp_to_string(ss, f, "Tx Bytes", q.tx_bytes);
  nvp_to_string(ss, f, "Tx Packets", q.tx_packets);
  nvp_to_string(ss, f, "Tx Errors", q.tx_errors);
  nvp_to_string(ss, f, "Duration in Seconds", q.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoseconds", q.duration_nsec);

  close_block(ss, f, "MultipartRes Queue");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Queues

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_queues& mrq)
{
  if (not available(v, bytes(mrq)))
    return AVAILABLE_MULTIPART_RES_QUEUES;
  return to_buffer(v, mrq.queues);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_queues& mrq)
{
  if (not available(v, bytes(mrq)))
    return AVAILABLE_MULTIPART_RES_QUEUES;
  return from_buffer(v, mrq.queues);
}

std::string
to_string(const Multipart_res_queues& mrq, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Queues");

  ss << to_string(mrq.queues, f);

  close_block(ss, f, "MultipartRes Queues");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Table

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_table& t)
{
  if (not available(v, bytes(t)))
    return AVAILABLE_MULTIPART_RES_TABLE;
  to_buffer(v, t.table_id);
  pad(v, 3);
  to_buffer(v, t.active_count);
  to_buffer(v, t.lookup_count);
  to_buffer(v, t.matched_count);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_table& t)
{
  if (not available(v, bytes(t)))
    return AVAILABLE_MULTIPART_RES_TABLE;
  from_buffer(v, t.table_id);
  pad(v, 3);
  from_buffer(v, t.active_count);
  from_buffer(v, t.lookup_count);
  from_buffer(v, t.matched_count);
  return SUCCESS;
}

std::string
to_string(const Multipart_res_table& t, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Table");

  nvp_to_string(ss, f, "Table ID", t.table_id);
  nvp_to_string(ss, f, "Active Count", t.active_count);
  nvp_to_string(ss, f, "Lookup Count", t.lookup_count);
  nvp_to_string(ss, f, "Matched Count", t.matched_count);

  close_block(ss, f, "MultipartRes Table");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Tables

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_tables& mrt)
{
  if (not available (v, bytes(mrt)))
    return AVAILABLE_MULTIPART_RES_TABLES;
  return to_buffer(v, mrt.tables);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_tables& mrt)
{
  if (not available (v, bytes(mrt)))
    return AVAILABLE_MULTIPART_RES_TABLES;
  return from_buffer(v, mrt.tables);
}

std::string
to_string(const Multipart_res_tables& mrt, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Tables");

  ss << to_string(mrt.tables, f);

  close_block(ss, f, "MultipartRes Tables");
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
// Multipart Response Group

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_group& g)
{
  if (not available (v, bytes(g)))
    return AVAILABLE_MULTIPART_RES_GROUP;
  to_buffer(v, g.length);
  pad(v, 2);
  to_buffer(v, g.group_id);
  to_buffer(v, g.ref_count);
  pad(v, 4);
  to_buffer(v, g.packet_count);
  to_buffer(v, g.byte_count);
  to_buffer(v, g.duration_sec);
  to_buffer(v, g.duration_nsec);
  return to_buffer(v, g.bucket_multipart);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_group& g)
{
  if (not available (v, bytes(g)))
    return AVAILABLE_MULTIPART_RES_GROUP;

  from_buffer(v, g.length);
  pad(v, 2);
  from_buffer(v, g.group_id);
  from_buffer(v, g.ref_count);
  pad(v, 4);
  from_buffer(v, g.packet_count);
  from_buffer(v, g.byte_count);
  from_buffer(v, g.duration_sec);
  from_buffer(v, g.duration_nsec);

  std::size_t n = g.length - 40;
  if (remaining(v) < n)
    return AVAILABLE_BUCKET;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, g.bucket_multipart))
    return err;
  if (not update(v, c))
    return EXCESS_MULTIPART_RES_GROUP;

  return SUCCESS;
}

std::string
to_string(const Multipart_res_group& g, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Group");

  nvp_to_string(ss, f, "Length", g.length);
  nvp_to_string(ss, f, "Group ID", g.group_id);
  nvp_to_string(ss, f, "Ref Count", g.ref_count);
  nvp_to_string(ss, f, "Packet Count", g.packet_count);
  nvp_to_string(ss, f, "Byte Count", g.byte_count);
  nvp_to_string(ss, f, "Duration in Seconds", g.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoeconds", g.duration_nsec);

  ss << to_string(g.bucket_multipart, f);

  close_block(ss, f, "MultipartRes Group");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Groups

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_groups& mrg)
{
  if (not available (v, bytes(mrg)))
    return AVAILABLE_MULTIPART_RES_GROUPS;
  return to_buffer(v, mrg.groups);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_groups& mrg)
{
  if (not available (v, bytes(mrg)))
    return AVAILABLE_MULTIPART_RES_GROUPS;
  return from_buffer(v, mrg.groups);
}

std::string
to_string(const Multipart_res_groups& mrg, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Groups");

  ss << to_string(mrg.groups, f);

  close_block(ss, f, "MultipartRes Groups");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Group Desc

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_group_desc& gd)
{
  if (not available (v, bytes(gd)))
    return AVAILABLE_MULTIPART_RES_GROUP_DESC;
  to_buffer(v, gd.length);
  to_buffer(v, gd.type);
  pad(v, 1);
  to_buffer(v, gd.group_id);
  return to_buffer(v, gd.buckets);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_group_desc& gd)
{
  if (not available (v, bytes(gd)))
    return AVAILABLE_MULTIPART_RES_GROUP_DESC;
  from_buffer(v, gd.length);
  from_buffer(v, gd.type);
  pad(v, 1);
  from_buffer(v, gd.group_id);

  std::size_t n = gd.length - 8;
  if (remaining(v) < n)
    return AVAILABLE_BUCKET;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, gd.buckets))
    return err;
  if (not update(v, c))
    return EXCESS_MULTIPART_RES_GROUP_DESC;
  return SUCCESS;
}

std::string
to_string(const Multipart_res_group_desc& gd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes GroupDesc");

  nvp_to_string(ss, f, "Length", gd.length);
  nvp_to_string(ss, f, "Type", gd.type);
  nvp_to_string(ss, f, "Group ID", gd.group_id);

  ss << to_string(gd.buckets, f);

  close_block(ss, f, "MultipartRes GroupDesc");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Group descs

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_group_descs& mrgd)
{
  if (not available (v, bytes(mrgd)))
    return AVAILABLE_MULTIPART_RES_GROUP_DESCS;
  return to_buffer(v, mrgd.group_descs);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_group_descs& mrgd)
{
  if (not available (v, bytes(mrgd)))
    return AVAILABLE_MULTIPART_RES_GROUP_DESCS;
  return from_buffer(v, mrgd.group_descs);
}

std::string
to_string(const Multipart_res_group_descs& mrgd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Group Descs");

  ss << to_string(mrgd.group_descs, f);

  close_block(ss, f, "MultipartRes Group Descs");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Group Features

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_group_features& gf)
{
  if (not available (v, bytes(gf)))
    return AVAILABLE_MULTIPART_RES_GROUP_FEATURES;
  to_buffer(v, gf.types);
  to_buffer(v, gf.capabilities);
  to_buffer(v, gf.max_groups_all);
  to_buffer(v, gf.max_groups_select);
  to_buffer(v, gf.max_groups_indirect);
  to_buffer(v, gf.max_groups_ff);
  to_buffer(v, gf.actions_all);
  to_buffer(v, gf.actions_select);
  to_buffer(v, gf.actions_indirect);
  to_buffer(v, gf.actions_ff);

  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_group_features& gf)
{
  if (not available (v, bytes(gf)))
    return AVAILABLE_MULTIPART_RES_GROUP_FEATURES;
  from_buffer(v, gf.types);
  from_buffer(v, gf.capabilities);
  from_buffer(v, gf.max_groups_all);
  from_buffer(v, gf.max_groups_select);
  from_buffer(v, gf.max_groups_indirect);
  from_buffer(v, gf.max_groups_ff);
  from_buffer(v, gf.actions_all);
  from_buffer(v, gf.actions_select);
  from_buffer(v, gf.actions_indirect);
  from_buffer(v, gf.actions_ff);

  return SUCCESS;
}

std::string
to_string(Multipart_res_group_features::Capability_type t)
{
  switch (t) {
  case Multipart_res_group_features::SELECT_WEIGHT: return "SELECT_WEIGHT";
  case Multipart_res_group_features::SELECT_LIVENESS: return "SELECT_LIVENESS";
  case Multipart_res_group_features::CHAINING: return "CHAINING";
  case Multipart_res_group_features::CHAINING_CHECKS: return "CHAINING_CHECKS";
  default: return "Unknown";
  }
}

std::string
to_string(const Multipart_res_group_features& gf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes GroupFeatures");

  nvp_to_string(ss, f, "Types", gf.types);
  nvp_to_string(ss, f, "Capabilities", to_string(gf.capabilities),
                int(gf.capabilities));
  nvp_to_string(ss, f, "Max Groups All", gf.max_groups_all);
  nvp_to_string(ss, f, "Max Groups Select", gf.max_groups_select);
  nvp_to_string(ss, f, "Max Groups Indirect", gf.max_groups_indirect);
  nvp_to_string(ss, f, "Max Groups FF", gf.max_groups_ff);
  nvp_to_string(ss, f, "Actions All", gf.actions_all);
  nvp_to_string(ss, f, "Actions Select", gf.actions_select);
  nvp_to_string(ss, f, "Actions Indirect", gf.actions_indirect);
  nvp_to_string(ss, f, "Actions FF", gf.actions_ff);

  close_block(ss, f, "MultipartRes GroupFeatures");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Meter band stats

Error_condition
to_buffer(Buffer_view& v, const Meter_band_stats& mbs)
{
  if (not available(v, bytes(mbs)))
    return AVAILABLE_METER_BAND_STATS;
  to_buffer(v, mbs.packet_band_count);
  to_buffer(v, mbs.byte_band_count);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Meter_band_stats& mbs)
{
  if (not available(v, bytes(mbs)))
    return AVAILABLE_METER_BAND_STATS;
  from_buffer(v, mbs.packet_band_count);
  from_buffer(v, mbs.byte_band_count);
  return SUCCESS;
}

std::string
to_string(const Meter_band_stats& mbs, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MeterBand Stats");

  nvp_to_string(ss, f, "Packet Band Count", mbs.packet_band_count);
  nvp_to_string(ss, f, "Byte Band Count", mbs.byte_band_count);

  close_block(ss, f, "MeterBand Stats");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart response: Meter

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_meter& mrm)
{
  if (not available(v, bytes(mrm)))
    return AVAILABLE_MULTIPART_RES_METER;
  to_buffer(v, mrm.meter_id);
  to_buffer(v, mrm.len);
  pad(v, 6);
  to_buffer(v, mrm.flow_count);
  to_buffer(v, mrm.packet_in_count);
  to_buffer(v, mrm.byte_in_count);
  to_buffer(v, mrm.duration_sec);
  to_buffer(v, mrm.duration_nsec);

  return to_buffer(v, mrm.meter_band_stats);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_meter& mrm)
{
  if (not available(v, bytes(mrm)))
    return AVAILABLE_MULTIPART_RES_METER;
  from_buffer(v, mrm.meter_id);
  from_buffer(v, mrm.len);
  pad(v, 6);
  from_buffer(v, mrm.flow_count);
  from_buffer(v, mrm.packet_in_count);
  from_buffer(v, mrm.byte_in_count);
  from_buffer(v, mrm.duration_sec);
  from_buffer(v, mrm.duration_nsec);

  std::size_t n = mrm.len - 40;
  if (remaining(v) < n)
    return AVAILABLE_METER_BAND;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, mrm.meter_band_stats))
    return err;
  if(not update(v, c))
    return EXCESS_MULTIPART_RES_METER;
  return SUCCESS;
}

std::string
to_string(const Multipart_res_meter& mrm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Meter");

  nvp_to_string(ss, f, "Meter ID", mrm.meter_id);
  nvp_to_string(ss, f, "Length", mrm.len);
  nvp_to_string(ss, f, "Flow Count", mrm.flow_count);
  nvp_to_string(ss, f, "Packet In Count", mrm.packet_in_count);
  nvp_to_string(ss, f, "Byte In Count", mrm.byte_in_count);
  nvp_to_string(ss, f, "Duration in Seconds", mrm.duration_sec);
  nvp_to_string(ss, f, "Duration in Nanoseconds", mrm.duration_nsec);

  ss << to_string(mrm.meter_band_stats, f);

  close_block(ss, f, "MultipartRes Meter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Meters

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_meters& mrm)
{
  if (not available (v, bytes(mrm)))
    return AVAILABLE_MULTIPART_RES_METERS;
  return to_buffer(v, mrm.meters);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_meters& mrm)
{
  if (not available (v, bytes(mrm)))
    return AVAILABLE_MULTIPART_RES_METERS;
  return from_buffer(v, mrm.meters);
}

std::string
to_string(const Multipart_res_meters& mrm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Meters");

  ss << to_string(mrm.meters, f);

  close_block(ss, f, "MultipartRes Meters");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Meter band type

std::string
to_string(Meter_band_type t)
{
  switch(t) {
  case METER_BAND_DROP: return "DROP";
  case METER_BAND_DSCP_REMARK: return "DSCP_REMARK";
  case METER_BAND_EXPERIMENTER: return "EXPERIMENTER";
  default: return "UNKNOWN";
  }
}

// -------------------------------------------------------------------------- //
// Meter band: drop

Error_condition
to_buffer(Buffer_view& v, const Meter_band_drop& mbd)
{
  if (not available(v, bytes(mbd)))
    return AVAILABLE_METER_BAND_DROP;
  pad(v, 4);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Meter_band_drop& mbd)
{
  if (not available(v, bytes(mbd)))
    return AVAILABLE_METER_BAND_DROP;
  pad(v, 4);
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Meter band: dscp remark

Error_condition
to_buffer(Buffer_view& v, const Meter_band_dscp_remark& mbdr)
{
  if (not available(v, bytes(mbdr)))
    return AVAILABLE_METER_BAND_DSCP_REMARK;
  to_buffer(v, mbdr.prec_level);
  pad(v, 3);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Meter_band_dscp_remark& mbdr)
{
  if (not available(v, bytes(mbdr)))
    return AVAILABLE_METER_BAND_DSCP_REMARK;
  from_buffer(v, mbdr.prec_level);
  pad(v, 3);
  return SUCCESS;
}

std::string
to_string(const Meter_band_dscp_remark& mbdr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MeterBand DSCP Remark");
  nvp_to_string(ss, f, "Prec Level", mbdr.prec_level);
  close_block(ss, f, "MeterBand DSCP Remark");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Meter band: experimenter

Error_condition
to_buffer(Buffer_view& v, const Meter_band_experimenter& mbe)
{
  if (not available(v, bytes(mbe)))
    return AVAILABLE_METER_BAND_EXPERIMENTER;
  to_buffer(v, mbe.experimenter_id);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Meter_band_experimenter& mbe)
{
  if (not available(v, bytes(mbe)))
    return AVAILABLE_METER_BAND_EXPERIMENTER;
  from_buffer(v, mbe.experimenter_id);
  return SUCCESS;
}

std::string
to_string(const Meter_band_experimenter& mbe, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MeterBand Experimenter");
  nvp_to_string(ss, f, "Experimenter ID", mbe.experimenter_id);
  close_block(ss, f, "MeterBand Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Meter band payload

void
construct(Meter_band_payload& p, Meter_band_type t)
{
  p.init = true;
  switch(t) {
  case METER_BAND_DROP: new (&p.data.drop) Meter_band_drop(); break;
  case METER_BAND_DSCP_REMARK:
    new (&p.data.dscp_remark) Meter_band_dscp_remark(); break;
  case METER_BAND_EXPERIMENTER:
    new (&p.data.experimenter) Meter_band_experimenter(); break;
  default: variant_error(t);
  }
}

void
construct(Meter_band_payload& p, const Meter_band_payload& x,
          Meter_band_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch (t) {
  case METER_BAND_DROP: new (&p.data.drop) Meter_band_drop(x.data.drop);
    break;
  case METER_BAND_DSCP_REMARK:
    new (&p.data.dscp_remark) Meter_band_dscp_remark(x.data.dscp_remark);
    break;
  case METER_BAND_EXPERIMENTER:
    new (&p.data.experimenter) Meter_band_experimenter(x.data.experimenter);
    break;
  default: variant_error(t);
  }
}

Meter_band_payload&
assign(Meter_band_payload& a, const Meter_band_payload& b, Meter_band_type t)
{
  if (&a == &b)
    return a;
  a.init = b.init;
  if (not a)
    return a;
  switch (t) {
  case METER_BAND_DROP:
    a.data.drop = b.data.drop;
    break;
  case METER_BAND_DSCP_REMARK:
    a.data.dscp_remark = b.data.dscp_remark;
    break;
  case METER_BAND_EXPERIMENTER:
    a.data.experimenter = b.data.experimenter;
    break;
  default: variant_error(t);
  }
  return a;
}

bool
equal(const Meter_band_payload& a, const Meter_band_payload& b,
      Meter_band_type t1, Meter_band_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch(t1) {
  case METER_BAND_DROP: return a.data.drop == b.data.drop;
  case METER_BAND_DSCP_REMARK:
    return a.data.dscp_remark == b.data.dscp_remark;
  case METER_BAND_EXPERIMENTER:
    return a.data.experimenter == b.data.experimenter;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Meter_band_payload& p, Meter_band_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case METER_BAND_DROP: return bytes(p.data.drop);
  case METER_BAND_DSCP_REMARK: return bytes(p.data.dscp_remark);
  case METER_BAND_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Meter_band_payload& p, Meter_band_type t)
{
  if (not p)
    return BAD_METER_BAND_INIT;
  switch (t) {
  case METER_BAND_DROP: return is_valid(p.data.drop);
  case METER_BAND_DSCP_REMARK: return is_valid(p.data.dscp_remark);
  case METER_BAND_EXPERIMENTER: return is_valid(p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_METER_BAND;
}

Error_condition
to_buffer(Buffer_view& v, const Meter_band_payload& p, Meter_band_type t)
{
  assert(p);
  switch (t) {
  case METER_BAND_DROP: return to_buffer(v, p.data.drop);
  case METER_BAND_DSCP_REMARK: return to_buffer(v, p.data.dscp_remark);
  case METER_BAND_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_METER_BAND;
}

Error_condition
from_buffer(Buffer_view& v, Meter_band_payload& p, Meter_band_type t)
{
  assert(p);
  switch (t) {
  case METER_BAND_DROP: return from_buffer(v, p.data.drop);
  case METER_BAND_DSCP_REMARK: return from_buffer(v, p.data.dscp_remark);
  case METER_BAND_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_METER_BAND;
}

std::string
to_string(const Meter_band_payload& p, Formatter& fmt, Meter_band_type t)
{
  assert(p);
  switch (t) {
  case METER_BAND_DROP: return to_string(p.data.drop, fmt);
  case METER_BAND_DSCP_REMARK: return to_string(p.data.dscp_remark, fmt);
  case METER_BAND_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Meter band header

//inline bool
//check_header(const Buffer_view& v, const Meter_band_header& h)
//{
//  return is_valid(h) and available(v, h.len - bytes(h));
//}

Error_condition
to_buffer(Buffer_view& v, const Meter_band_header& h)
{
  to_buffer(v, h.type);
  to_buffer(v, h.len);
  to_buffer(v, h.rate);
  to_buffer(v, h.burst_size);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Meter_band_header& h)
{
  from_buffer(v, h.type);
  from_buffer(v, h.len);
  from_buffer(v, h.rate);
  from_buffer(v, h.burst_size);
  return SUCCESS;
}

std::string
to_string(const Meter_band_header& h, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Hdr");

  nvp_to_string(ss, f, "Type", to_string(h.type), int(h.type));
  nvp_to_string(ss, f, "Length", h.len);
  nvp_to_string(ss, f, "Rate", h.rate);
  nvp_to_string(ss, f, "Burst Size", h.burst_size);

  close_block(ss, f, "Hdr");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Meter band

Error_condition
to_buffer(Buffer_view& v, const Meter_band& mb)
{
  if (not available(v, bytes(mb.header)))
    return AVAILABLE_METER_BAND_HEADER;

  to_buffer(v, mb.header);
//  if (not check_header(v, mb.header))
//    return false;

  return to_buffer(v, mb.payload, mb.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Meter_band& mb)
{
  if (not available(v, bytes(mb.header)))
    return AVAILABLE_METER_BAND_HEADER;
  from_buffer(v, mb.header);

  if (Error_decl err = is_valid(mb.header.type))
   return err;

  Meter_band::Payload p;
  construct(p, mb.header.type);
  assign(mb.payload, std::move(p), mb.header.type);

  if (Error_decl err = is_valid(mb.header))
    return err;

  std::size_t n = mb.header.len - bytes(mb.header);
  if (remaining(v) < n)
    return AVAILABLE_METER_BAND_PAYLOAD;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, mb.payload, mb.header.type))
    return err;

  if(not update(v, c))
    return EXCESS_METER_BAND;

  return SUCCESS;
}

std::string
to_string(const Meter_band& mb, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MeterBand");
  ss << to_string(mb.header, f);
  if (is_valid(mb.header))
    ss << to_string(mb.payload, f, mb.header.type);
  close_block(ss, f, "MeterBand");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response: Meter config

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_meter_config& mrmc)
{
  if (not available(v, bytes(mrmc)))
    return AVAILABLE_MULTIPART_RES_METER_CONFIG;
  to_buffer(v, mrmc.len);
  to_buffer(v, mrmc.flags);
  to_buffer(v, mrmc.meter_id);
  return to_buffer(v, mrmc.meter_bands);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_meter_config& mrmc)
{
  if (not available(v, bytes(mrmc)))
    return AVAILABLE_MULTIPART_RES_METER_CONFIG;
  from_buffer(v, mrmc.len);
  from_buffer(v, mrmc.flags);
  from_buffer(v, mrmc.meter_id);

  std::size_t n = mrmc.len - 8;
  if (remaining(v) < n)
    return AVAILABLE_METER_BAND;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, mrmc.meter_bands))
    return err;

  if(not update(v, c))
    return EXCESS_MULTIPART_RES_METER_CONFIG;

  return SUCCESS;
}

std::string
to_string(const Multipart_res_meter_config& mrmc, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes MeterConfig");

  nvp_to_string(ss, f, "Length", mrmc.len);
  nvp_to_string(ss, f, "Flags", mrmc.flags);
  nvp_to_string(ss, f, "Meter ID", mrmc.meter_id);

  ss << to_string(mrmc.meter_bands, f);

  close_block(ss, f, "MultipartRes MeterConfig");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Meter configs

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_meter_configs& mrmc)
{
  if (not available (v, bytes(mrmc)))
    return AVAILABLE_MULTIPART_RES_METER_CONFIGS;
  return to_buffer(v, mrmc.meter_configs);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_meter_configs& mrmc)
{
  if (not available (v, bytes(mrmc)))
    return AVAILABLE_MULTIPART_RES_METER_CONFIGS;
  return from_buffer(v, mrmc.meter_configs);
}

std::string
to_string(const Multipart_res_meter_configs& mrmc, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Meter Configs");

  ss << to_string(mrmc.meter_configs, f);

  close_block(ss, f, "MultipartRes Meter Configs");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response: Meter features

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_meter_features& mrmf)
{
  if (not available(v, bytes(mrmf)))
    return AVAILABLE_MULTIPART_RES_METER_FEATURES;
  to_buffer(v, mrmf.max_meter);
  to_buffer(v, mrmf.band_type);
  to_buffer(v, mrmf.capabilities);
  to_buffer(v, mrmf.max_bands);
  to_buffer(v, mrmf.max_color);
  pad(v, 2);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_meter_features& mrmf)
{
  if (not available(v, bytes(mrmf)))
    return AVAILABLE_MULTIPART_RES_METER_FEATURES;
  from_buffer(v, mrmf.max_meter);
  from_buffer(v, mrmf.band_type);
  from_buffer(v, mrmf.capabilities);
  from_buffer(v, mrmf.max_bands);
  from_buffer(v, mrmf.max_color);
  pad(v, 2);
  return SUCCESS;
}

std::string
to_string(const Multipart_res_meter_features& mrmf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes MeterFeatures");

  nvp_to_string(ss, f, "Max Meter", mrmf.max_meter);
  nvp_to_string(ss, f, "Band Type", mrmf.band_type);
  nvp_to_string(ss, f, "Capabilities", mrmf.capabilities);
  nvp_to_string(ss, f, "Max Bands", mrmf.max_bands);
  nvp_to_string(ss, f, "Max Color", mrmf.max_color);

  close_block(ss, f, "MultipartRes MeterConfig");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response: Table feature

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_table_feature& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURE;

  to_buffer(v, mrtf.length);
  to_buffer(v, mrtf.table_id);
  pad(v, 5);
  to_buffer(v, mrtf.name);
  to_buffer(v, mrtf.metadata_match);
  to_buffer(v, mrtf.metadata_write);
  to_buffer(v, mrtf.config);
  to_buffer(v, mrtf.max_entries);

  //return to_buffer(v, mrtf.properties);
  if (Error_decl err = to_buffer(v, mrtf.properties))
    return err;

  uint8_t padding = 8 - (mrtf.length % 8);
  if (padding == 8)
    return SUCCESS;

  if (not available(v, padding))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURE_PADDING;

  pad(v, padding);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_table_feature& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURE;

  from_buffer(v, mrtf.length);
  from_buffer(v, mrtf.table_id);
  pad(v, 5);
  from_buffer(v, mrtf.name);
  from_buffer(v, mrtf.metadata_match);
  from_buffer(v, mrtf.metadata_write);
  from_buffer(v, mrtf.config);
  from_buffer(v, mrtf.max_entries);

  //return from_buffer(v, mrtf.properties);

  std::size_t n = mrtf.length - 64;

  if (remaining(v) < n)
    return AVAILABLE_TABLE_FEATURE_PROPERTY;
  Buffer_view c = constrain(v, n);

  if (Error_decl err = from_buffer(c, mrtf.properties))
    return err;

  if (not update(v, c))
    return EXCESS_MULTIPART_RES_TABLE_FEATURE;

  uint8_t padding = 8 - (mrtf.length % 8);
  if (padding == 8)
    return SUCCESS;

  if (not available(v, padding))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURE_PADDING;

  pad(v, padding);
  return SUCCESS;
}

std::string
to_string(const Multipart_res_table_feature& mrtf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes TableFeature");

  nvp_to_string(ss, f, "Length", mrtf.length);
  nvp_to_string(ss, f, "Table ID", mrtf.table_id);
  nvp_to_string(ss, f, "Name", mrtf.name.str());
  nvp_to_string(ss, f, "Metadata Match", mrtf.metadata_match);
  nvp_to_string(ss, f, "Metadata Write", mrtf.metadata_write);
  nvp_to_string(ss, f, "Config", mrtf.config);
  nvp_to_string(ss, f, "Max Entries", mrtf.max_entries);

  ss << to_string(mrtf.properties, f);

  close_block(ss, f, "MultipartRes TableFeature");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response: Table features

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_table_features& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURES;
  return to_buffer(v, mrtf.table_features);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_table_features& mrtf)
{
  if (not available(v, bytes(mrtf)))
    return AVAILABLE_MULTIPART_RES_TABLE_FEATURES;
  return from_buffer(v, mrtf.table_features);
}

std::string
to_string(const Multipart_res_table_features& mrtf, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes TableFeatures");

  ss << to_string(mrtf.table_features, f);

  close_block(ss, f, "MultipartRes TableFeatures");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response: Port desc

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_port_desc& mrpd)
{
  if (not available(v, bytes(mrpd)))
    return AVAILABLE_MULTIPART_RES_PORT_DESC;
  return to_buffer(v, mrpd.ports);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_port_desc& mrpd)
{
  if (not available(v, bytes(mrpd)))
    return AVAILABLE_MULTIPART_RES_PORT_DESC;
  return from_buffer(v, mrpd.ports);
}

std::string
to_string(const Multipart_res_port_desc& mrpd, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes PortDesc");

  ss << to_string(mrpd.ports, f);

  close_block(ss, f, "MultipartRes PortDesc");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response: Experimenter

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_experimenter& mre)
{
  if (not available(v, bytes(mre)))
    return AVAILABLE_MULTIPART_RES_EXPERIMENTER;
  to_buffer(v, mre.experimenter_id);
  to_buffer(v, mre.exp_type);
  return to_buffer(v, mre.data);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_experimenter& mre)
{
  if (not available(v, bytes(mre)))
    return AVAILABLE_MULTIPART_RES_EXPERIMENTER;
  from_buffer(v, mre.experimenter_id);
  from_buffer(v, mre.exp_type);
  return from_buffer(v, mre.data);
}

std::string
to_string(const Multipart_res_experimenter& mre, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes Experimenter");

  nvp_to_string(ss, f, "Experimenter ID", mre.experimenter_id);
  nvp_to_string(ss, f, "Exp Type", mre.exp_type);
  nvp_to_string(ss, f, "Data Bytes", bytes(mre.data));

  close_block(ss, f, "MultipartRes Experimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Multipart Response Payload

void
construct(Multipart_res_payload& p, Multipart_type t)
{
  p.init = true;
  switch(t) {
  case MULTIPART_DESC: new (&p.data.desc) Multipart_res_desc(); break;
  case MULTIPART_FLOW: new (&p.data.flow) Multipart_res_flows(); break;
  case MULTIPART_AGGREGATE: new (&p.data.aggregate) Multipart_res_aggregate();
    break;
  case MULTIPART_TABLE: new (&p.data.table) Multipart_res_tables(); break;
  case MULTIPART_PORT: new (&p.data.port) Multipart_res_ports(); break;
  case MULTIPART_QUEUE: new (&p.data.queue) Multipart_res_queues(); break;
  case MULTIPART_GROUP: new (&p.data.group) Multipart_res_groups(); break;
  case MULTIPART_GROUP_DESC:
    new (&p.data.group_desc) Multipart_res_group_descs(); break;
  case MULTIPART_GROUP_FEATURES:
    new (&p.data.group_features) Multipart_res_group_features(); break;
  case MULTIPART_METER: new (&p.data.meter) Multipart_res_meters(); break;
  case MULTIPART_METER_CONFIG:
    new (&p.data.meter_config) Multipart_res_meter_configs(); break;
  case MULTIPART_METER_FEATURES:
    new (&p.data.meter_features) Multipart_res_meter_features(); break;
  case MULTIPART_TABLE_FEATURES:
    new (&p.data.table_features) Multipart_res_table_features(); break;
  case MULTIPART_PORT_DESC: new (&p.data.port_desc) Multipart_res_port_desc();
    break;
  case MULTIPART_EXPERIMENTER:
    new (&p.data.experimenter) Multipart_res_experimenter(); break;
  default: variant_error(t);
  }
}

void
construct(Multipart_res_payload& p, Multipart_res_payload&& x,
          Multipart_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case MULTIPART_DESC:
    new (&p.data.desc) Multipart_res_desc(std::move(x.data.desc)); break;
  case MULTIPART_FLOW:
    new (&p.data.flow) Multipart_res_flows(std::move(x.data.flow)); break;
  case MULTIPART_AGGREGATE:
    new (&p.data.aggregate)
        Multipart_res_aggregate(std::move(x.data.aggregate)); break;
  case MULTIPART_TABLE:
    new (&p.data.table) Multipart_res_tables(std::move(x.data.table)); break;
  case MULTIPART_PORT:
    new (&p.data.port) Multipart_res_ports(std::move(x.data.port)); break;
  case MULTIPART_QUEUE:
    new (&p.data.queue) Multipart_res_queues(std::move(x.data.queue)); break;
  case MULTIPART_GROUP:
    new (&p.data.group) Multipart_res_groups(std::move(x.data.group)); break;
  case MULTIPART_GROUP_DESC:
    new (&p.data.group_desc)
         Multipart_res_group_descs(std::move(x.data.group_desc)); break;
  case MULTIPART_GROUP_FEATURES:
    new (&p.data.group_features)
         Multipart_res_group_features(std::move(x.data.group_features)); break;
  case MULTIPART_METER:
    new (&p.data.meter) Multipart_res_meters(std::move(x.data.meter)); break;
  case MULTIPART_METER_CONFIG:
    new (&p.data.meter_config)
         Multipart_res_meter_configs(std::move(x.data.meter_config)); break;
  case MULTIPART_METER_FEATURES:
    new (&p.data.meter_features)
         Multipart_res_meter_features(std::move(x.data.meter_features)); break;
  case MULTIPART_TABLE_FEATURES:
    new (&p.data.table_features)
         Multipart_res_table_features(std::move(x.data.table_features)); break;
  case MULTIPART_PORT_DESC:
    new (&p.data.port_desc)
        Multipart_res_port_desc(std::move(x.data.port_desc)); break;
  case MULTIPART_EXPERIMENTER:
    new (&p.data.experimenter)
        Multipart_res_experimenter(std::move(x.data.experimenter)); break;
  default: variant_error(t);
  }
}

void
construct(Multipart_res_payload& p, const Multipart_res_payload& x,
          Multipart_type t)
{
  p.init = x.init;
  if (not p)
    return;
  switch(t) {
  case MULTIPART_DESC: new (&p.data.desc) Multipart_res_desc(x.data.desc);
    break;
  case MULTIPART_FLOW: new (&p.data.flow) Multipart_res_flows(x.data.flow);
    break;
  case MULTIPART_AGGREGATE:
    new (&p.data.aggregate) Multipart_res_aggregate(x.data.aggregate); break;
  case MULTIPART_TABLE: new (&p.data.table) Multipart_res_tables(x.data.table);
    break;
  case MULTIPART_PORT: new (&p.data.port) Multipart_res_ports(x.data.port);
    break;
  case MULTIPART_QUEUE: new (&p.data.queue) Multipart_res_queues(x.data.queue);
    break;
  case MULTIPART_GROUP: new (&p.data.group) Multipart_res_groups(x.data.group);
    break;
  case MULTIPART_GROUP_DESC:
    new (&p.data.group_desc) Multipart_res_group_descs(x.data.group_desc);
    break;
  case MULTIPART_GROUP_FEATURES:
    new (&p.data.group_features)
        Multipart_res_group_features(x.data.group_features); break;
  case MULTIPART_METER: new (&p.data.meter) Multipart_res_meters(x.data.meter);
    break;
  case MULTIPART_METER_CONFIG:
    new (&p.data.meter_config)
         Multipart_res_meter_configs(x.data.meter_config);
    break;
  case MULTIPART_METER_FEATURES:
    new (&p.data.meter_features)
        Multipart_res_meter_features(x.data.meter_features); break;
  case MULTIPART_TABLE_FEATURES:
    new (&p.data.table_features)
         Multipart_res_table_features(x.data.table_features); break;
  case MULTIPART_PORT_DESC:
    new (&p.data.port_desc) Multipart_res_port_desc(x.data.port_desc); break;
  case MULTIPART_EXPERIMENTER:
    new (&p.data.experimenter)
        Multipart_res_experimenter(x.data.experimenter); break;
  default: variant_error(t);
  }
}

void
destroy(Multipart_res_payload& p, Multipart_type t)
{
  switch(t) {
  case MULTIPART_DESC: p.data.desc.~Multipart_res_desc(); break;
  case MULTIPART_FLOW: p.data.flow.~Multipart_res_flows(); break;
  case MULTIPART_AGGREGATE: p.data.aggregate.~Multipart_res_aggregate();
    break;
  case MULTIPART_TABLE: p.data.table.~Multipart_res_tables(); break;
  case MULTIPART_PORT: p.data.port.~Multipart_res_ports(); break;
  case MULTIPART_QUEUE: p.data.queue.~Multipart_res_queues(); break;
  case MULTIPART_GROUP: p.data.group.~Multipart_res_groups(); break;
  case MULTIPART_GROUP_DESC: p.data.group_desc.~Multipart_res_group_descs();
    break;
  case MULTIPART_GROUP_FEATURES:
    p.data.group_features.~Multipart_res_group_features(); break;
  case MULTIPART_METER: p.data.meter.~Multipart_res_meters(); break;
  case MULTIPART_METER_CONFIG:
    p.data.meter_config.~Multipart_res_meter_configs(); break;
  case MULTIPART_METER_FEATURES:
    p.data.meter_features.~Multipart_res_meter_features(); break;
  case MULTIPART_TABLE_FEATURES:
    p.data.table_features.~Multipart_res_table_features(); break;
  case MULTIPART_PORT_DESC: p.data.port_desc.~Multipart_res_port_desc(); break;
  case MULTIPART_EXPERIMENTER:
    p.data.experimenter.~Multipart_res_experimenter(); break;
  default: return;
  }
}

Multipart_res_payload&
assign(Multipart_res_payload& p, Multipart_res_payload&& x, Multipart_type t)
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
  case MULTIPART_DESC: p.data.desc = std::move(x.data.desc); break;
  case MULTIPART_FLOW: p.data.flow = std::move(x.data.flow); break;
  case MULTIPART_AGGREGATE: p.data.aggregate = std::move(x.data.aggregate);
    break;
  case MULTIPART_TABLE: p.data.table = std::move(x.data.table); break;
  case MULTIPART_PORT: p.data.port = std::move(x.data.port); break;
  case MULTIPART_QUEUE: p.data.queue = std::move(x.data.queue); break;
  case MULTIPART_GROUP: p.data.group = std::move(x.data.group); break;
  case MULTIPART_GROUP_DESC:
    p.data.group_desc = std::move(x.data.group_desc); break;
  case MULTIPART_GROUP_FEATURES:
    p.data.group_features = std::move(x.data.group_features); break;
  case MULTIPART_METER: p.data.meter = std::move(x.data.meter); break;
  case MULTIPART_METER_CONFIG:
    p.data.meter_config = std::move(x.data.meter_config); break;
  case MULTIPART_METER_FEATURES:
    p.data.meter_features = std::move(x.data.meter_features); break;
  case MULTIPART_TABLE_FEATURES:
    p.data.table_features = std::move(x.data.table_features); break;
  case MULTIPART_PORT_DESC: p.data.port_desc = std::move(x.data.port_desc);
    break;
  case MULTIPART_EXPERIMENTER:
    p.data.experimenter = std::move(x.data.experimenter); break;
  default: variant_error(t);
  }
  return p;
}

Multipart_res_payload&
assign(Multipart_res_payload& p, const Multipart_res_payload& x,
       Multipart_type t)
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
  case MULTIPART_DESC: p.data.desc = x.data.desc; break;
  case MULTIPART_FLOW: p.data.flow = x.data.flow; break;
  case MULTIPART_AGGREGATE: p.data.aggregate = x.data.aggregate; break;
  case MULTIPART_TABLE: p.data.table = x.data.table; break;
  case MULTIPART_PORT: p.data.port = x.data.port; break;
  case MULTIPART_QUEUE: p.data.queue = x.data.queue; break;
  case MULTIPART_GROUP: p.data.group = x.data.group; break;
  case MULTIPART_GROUP_DESC: p.data.group_desc = x.data.group_desc; break;
  case MULTIPART_GROUP_FEATURES: p.data.group_features = x.data.group_features;
    break;
  case MULTIPART_METER: p.data.meter = x.data.meter; break;
  case MULTIPART_METER_CONFIG: p.data.meter_config = x.data.meter_config;
    break;
  case MULTIPART_METER_FEATURES:
    p.data.meter_features = x.data.meter_features; break;
  case MULTIPART_TABLE_FEATURES: p.data.table_features = x.data.table_features;
    break;
  case MULTIPART_PORT_DESC: p.data.port_desc = x.data.port_desc; break;
  case MULTIPART_EXPERIMENTER: p.data.experimenter = x.data.experimenter;
    break;
  default: variant_error(t);
  }
  return p;
}

bool
equal(const Multipart_res_payload& a, const Multipart_res_payload& b,
      Multipart_type t1, Multipart_type t2)
{
  assert(t1 == t2);
  if (not a)
    return not b;
  if (not b)
    return false;
  switch (t1) {
  case MULTIPART_DESC: return a.data.desc == b.data.desc;
  case MULTIPART_FLOW: return a.data.flow == b.data.flow;
  case MULTIPART_AGGREGATE: return a.data.aggregate == b.data.aggregate;
  case MULTIPART_TABLE: return a.data.table == b.data.table;
  case MULTIPART_PORT: return a.data.port == b.data.port;
  case MULTIPART_QUEUE: return a.data.queue == b.data.queue;
  case MULTIPART_GROUP: return a.data.group == b.data.group;
  case MULTIPART_GROUP_DESC: return a.data.group_desc == b.data.group_desc;
  case MULTIPART_GROUP_FEATURES:
    return a.data.group_features == b.data.group_features;
  case MULTIPART_METER: return a.data.meter == b.data.meter;
  case MULTIPART_METER_CONFIG:
    return a.data.meter_config == b.data.meter_config;
  case MULTIPART_METER_FEATURES:
    return a.data.meter_features == b.data.meter_features;
  case MULTIPART_TABLE_FEATURES:
    return a.data.table_features == b.data.table_features;
  case MULTIPART_PORT_DESC: return a.data.port_desc == b.data.port_desc;
  case MULTIPART_EXPERIMENTER:
    return a.data.experimenter == b.data.experimenter;
  default: variant_error(t1);
  }
  return false;
}

std::size_t
bytes(const Multipart_res_payload& p, Multipart_type t)
{
  if (not p)
    return 0;
  switch (t) {
  case MULTIPART_DESC: return bytes(p.data.desc);
  case MULTIPART_FLOW: return bytes(p.data.flow);
  case MULTIPART_AGGREGATE: return bytes(p.data.aggregate);
  case MULTIPART_TABLE: return bytes(p.data.table);
  case MULTIPART_PORT: return bytes(p.data.port);
  case MULTIPART_QUEUE: return bytes(p.data.queue);
  case MULTIPART_GROUP: return bytes(p.data.group);
  case MULTIPART_GROUP_DESC: return bytes(p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return bytes(p.data.group_features);
  case MULTIPART_METER: return bytes(p.data.meter);
  case MULTIPART_METER_CONFIG: return bytes(p.data.meter_config);
  case MULTIPART_METER_FEATURES: return bytes(p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return bytes(p.data.table_features);
  case MULTIPART_PORT_DESC: return bytes(p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return bytes(p.data.experimenter);
  default: variant_error(t);
  }
  return 0;
}

Error_condition
is_valid(const Multipart_res_payload& p, Multipart_type t)
{
  if (not p)
    return BAD_MULTIPART_INIT;
  switch (t) {
  case MULTIPART_DESC: return is_valid(p.data.desc);
  case MULTIPART_FLOW: return is_valid(p.data.flow);
  case MULTIPART_AGGREGATE: return is_valid(p.data.aggregate);
  case MULTIPART_TABLE: return is_valid(p.data.table);
  case MULTIPART_PORT: return is_valid(p.data.port);
  case MULTIPART_QUEUE: return is_valid(p.data.queue);
  case MULTIPART_GROUP: return is_valid(p.data.group);
  case MULTIPART_GROUP_DESC: return is_valid(p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return is_valid(p.data.group_features);
  case MULTIPART_METER: return is_valid(p.data.meter);
  case MULTIPART_METER_CONFIG: return is_valid(p.data.meter_config);
  case MULTIPART_METER_FEATURES: return is_valid(p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return is_valid(p.data.table_features);
  case MULTIPART_PORT_DESC: return is_valid(p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return is_valid(p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_MULTIPART;
}

Error_condition
to_buffer(Buffer_view& v, const Multipart_res_payload& p, Multipart_type t)
{
  assert(p);
  switch (t) {
  case MULTIPART_DESC: return to_buffer(v, p.data.desc);
  case MULTIPART_FLOW: return to_buffer(v, p.data.flow);
  case MULTIPART_AGGREGATE: return to_buffer(v, p.data.aggregate);
  case MULTIPART_TABLE: return to_buffer(v, p.data.table);
  case MULTIPART_PORT: return to_buffer(v, p.data.port);
  case MULTIPART_QUEUE: return to_buffer(v, p.data.queue);
  case MULTIPART_GROUP: return to_buffer(v, p.data.group);
  case MULTIPART_GROUP_DESC: return to_buffer(v, p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return to_buffer(v, p.data.group_features);
  case MULTIPART_METER: return to_buffer(v, p.data.meter);
  case MULTIPART_METER_CONFIG: return to_buffer(v, p.data.meter_config);
  case MULTIPART_METER_FEATURES: return to_buffer(v, p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return to_buffer(v, p.data.table_features);
  case MULTIPART_PORT_DESC: return to_buffer(v, p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_MULTIPART;
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res_payload& p, Multipart_type t)
{
  assert(p);
  switch (t) {
  case MULTIPART_DESC: return from_buffer(v, p.data.desc);
  case MULTIPART_FLOW: return from_buffer(v, p.data.flow);
  case MULTIPART_AGGREGATE: return from_buffer(v, p.data.aggregate);
  case MULTIPART_TABLE: return from_buffer(v, p.data.table);
  case MULTIPART_PORT: return from_buffer(v, p.data.port);
  case MULTIPART_QUEUE: return from_buffer(v, p.data.queue);
  case MULTIPART_GROUP: return from_buffer(v, p.data.group);
  case MULTIPART_GROUP_DESC: return from_buffer(v, p.data.group_desc);
  case MULTIPART_GROUP_FEATURES: return from_buffer(v, p.data.group_features);
  case MULTIPART_METER: return from_buffer(v, p.data.meter);
  case MULTIPART_METER_CONFIG: return from_buffer(v, p.data.meter_config);
  case MULTIPART_METER_FEATURES: return from_buffer(v, p.data.meter_features);
  case MULTIPART_TABLE_FEATURES: return from_buffer(v, p.data.table_features);
  case MULTIPART_PORT_DESC: return from_buffer(v, p.data.port_desc);
  case MULTIPART_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
  default: variant_error(t);
  }
  return BAD_MULTIPART;
}

std::string
to_string(const Multipart_res_payload& p, Formatter& fmt, Multipart_type t)
{
  assert(p);
  switch (t) {
  case MULTIPART_DESC: return to_string(p.data.desc, fmt);
  case MULTIPART_FLOW: return to_string(p.data.flow, fmt);
  case MULTIPART_AGGREGATE: return to_string(p.data.aggregate, fmt);
  case MULTIPART_TABLE: return to_string(p.data.table, fmt);
  case MULTIPART_PORT: return to_string(p.data.port, fmt);
  case MULTIPART_QUEUE: return to_string(p.data.queue, fmt);
  case MULTIPART_GROUP: return to_string(p.data.group, fmt);
  case MULTIPART_GROUP_DESC: return to_string(p.data.group_desc, fmt);
  case MULTIPART_GROUP_FEATURES: return to_string(p.data.group_features, fmt);
  case MULTIPART_METER: return to_string(p.data.meter, fmt);
  case MULTIPART_METER_CONFIG: return to_string(p.data.meter_config, fmt);
  case MULTIPART_METER_FEATURES: return to_string(p.data.meter_features, fmt);
  case MULTIPART_TABLE_FEATURES: return to_string(p.data.table_features, fmt);
  case MULTIPART_PORT_DESC: return to_string(p.data.port_desc, fmt);
  case MULTIPART_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
  default: variant_error(t);
  }
  return "";
}

// -------------------------------------------------------------------------- //
// Multipart Response

Error_condition
to_buffer(Buffer_view& v, const Multipart_res& r)
{
  if (not available(v, bytes(r)))
    return AVAILABLE_MULTIPART_HEADER;
  to_buffer(v, r.header);
  return to_buffer(v, r.payload, r.header.type);
}

Error_condition
from_buffer(Buffer_view& v, Multipart_res& r)
{
  if (not available(v, bytes(r)))
    return AVAILABLE_MULTIPART_HEADER;
  from_buffer(v, r.header);

  // Check that the payload is valid.
  if (Error_decl err = is_valid(r.header.type))
    return err;

  Multipart_res::Payload p;
  construct(p, r.header.type);
  assign(r.payload, std::move(p), r.header.type);

  // Construct the payload.
  return from_buffer(v, r.payload, r.header.type);
}

std::string
to_string(const Multipart_res& sr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MultipartRes");

  ss << to_string(sr.header, f);
  //if (check_header(sr.header))
    ss << to_string(sr.payload, f, sr.header.type);

  close_block(ss, f, "MultipartRes");
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
// Queue property type

std::string
to_string(Queue_property_type t)
{
  switch(t) {
  case QUEUE_PROPERTY_MIN_RATE: return "MIN_RATE";
  case QUEUE_PROPERTY_MAX_RATE: return "MAX_RATE";
  case QUEUE_PROPERTY_EXPERIMENTER: return "EXPERIMENTER";
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
// Queue property: max rate

Error_condition
to_buffer(Buffer_view& v, const Queue_property_max_rate& mr)
{
  if (not available(v, bytes(mr)))
    return AVAILABLE_QUEUE_PROPERTY_MAX_RATE;
  to_buffer(v, mr.rate);
  pad(v, 6);
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_max_rate& mr)
{
  if (not available(v, bytes(mr)))
    return AVAILABLE_QUEUE_PROPERTY_MAX_RATE;
  from_buffer(v, mr.rate);
  pad(v, 6);
  return SUCCESS;
}

std::string
to_string(const Queue_property_max_rate& mr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "QueuePropertyMaxRate");

  nvp_to_string(ss, f, "Rate", mr.rate);

  close_block(ss, f, "QueuePropertyMaxRate");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Queue property: Experimenter

Error_condition
to_buffer(Buffer_view& v, const Queue_property_experimenter& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_QUEUE_PROPERTY_EXPERIMENTER;
  to_buffer(v, e.experimenter);
  pad(v, 4);
  return to_buffer(v, e.data);
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_experimenter& e)
{
  if (not available(v, bytes(e)))
    return AVAILABLE_QUEUE_PROPERTY_EXPERIMENTER;
  from_buffer(v, e.experimenter);
  pad(v, 4);
  return from_buffer(v, e.data);
}

std::string
to_string(const Queue_property_experimenter& e, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "QueuePropertyExperimenter");

  nvp_to_string(ss, f, "Experimenter", e.experimenter);

  close_block(ss, f, "QueuePropertyExperimenter");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Queue Property Payload

void
construct(Queue_property_payload& a, Queue_property_type t)
{
  a.init = true;
  switch (t) {
  case QUEUE_PROPERTY_MIN_RATE:
    new (&a.data.min_rate) Queue_property_min_rate(); break;
  case QUEUE_PROPERTY_MAX_RATE:
    new (&a.data.max_rate) Queue_property_max_rate(); break;
  case QUEUE_PROPERTY_EXPERIMENTER:
    new (&a.data.experimenter) Queue_property_experimenter(); break;
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
  case QUEUE_PROPERTY_MIN_RATE:
    new (&a.data.min_rate) Queue_property_min_rate(b.data.min_rate); break;
  case QUEUE_PROPERTY_MAX_RATE:
    new (&a.data.max_rate) Queue_property_max_rate(b.data.max_rate); break;
  case QUEUE_PROPERTY_EXPERIMENTER: new (&a.data.experimenter)
    Queue_property_experimenter(b.data.experimenter); break;
  default: variant_error(t);
  }
}

Queue_property::Payload&
assign(Queue_property_payload& a, const Queue_property_payload& b,
       Queue_property_type t)
{
  if (&a == &b)
    return a;

  if (not a) {
    construct(a, b, t);
    return a;
  }

  a.init = b.init;
  if (not a)
    return a;

  switch (t) {
  case QUEUE_PROPERTY_MIN_RATE: a.data.min_rate = b.data.min_rate; break;
  case QUEUE_PROPERTY_MAX_RATE: a.data.max_rate = b.data.max_rate; break;
  case QUEUE_PROPERTY_EXPERIMENTER: a.data.experimenter = b.data.experimenter;
    break;
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
  case QUEUE_PROPERTY_MIN_RATE: return a.data.min_rate == b.data.min_rate;
  case QUEUE_PROPERTY_MAX_RATE: return a.data.max_rate == b.data.max_rate;
  case QUEUE_PROPERTY_EXPERIMENTER:
    return a.data.experimenter == b.data.experimenter;
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
  case QUEUE_PROPERTY_MIN_RATE: return bytes(p.data.min_rate);
  case QUEUE_PROPERTY_MAX_RATE: return bytes(p.data.max_rate);
  case QUEUE_PROPERTY_EXPERIMENTER: return bytes(p.data.experimenter);
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
  case QUEUE_PROPERTY_MIN_RATE: return is_valid(p.data.min_rate);
  case QUEUE_PROPERTY_MAX_RATE: return is_valid(p.data.max_rate);
  case QUEUE_PROPERTY_EXPERIMENTER: return is_valid(p.data.experimenter);
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
  case QUEUE_PROPERTY_MIN_RATE: return to_buffer(v, p.data.min_rate);
  case QUEUE_PROPERTY_MAX_RATE: return to_buffer(v, p.data.max_rate);
  case QUEUE_PROPERTY_EXPERIMENTER: return to_buffer(v, p.data.experimenter);
  default: variant_error(t)
  }
  return BAD_QUEUE_PROPERTY;
}

Error_condition
from_buffer(Buffer_view& v, Queue_property_payload& p, Queue_property_type t)
{
  assert(p);
  switch (t) {
  case QUEUE_PROPERTY_MIN_RATE: return from_buffer(v, p.data.min_rate);
  case QUEUE_PROPERTY_MAX_RATE: return from_buffer(v, p.data.max_rate);
  case QUEUE_PROPERTY_EXPERIMENTER: return from_buffer(v, p.data.experimenter);
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
  case QUEUE_PROPERTY_MIN_RATE: return to_string(p.data.min_rate, fmt);
  case QUEUE_PROPERTY_MAX_RATE: return to_string(p.data.max_rate, fmt);
  case QUEUE_PROPERTY_EXPERIMENTER: return to_string(p.data.experimenter, fmt);
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
  if (Error_decl err = is_valid(qp.header))
    return err;

  Queue_property::Payload p;
  construct(p, qp.header.property);
  assign(qp.payload, std::move(p), qp.header.property);
  //construct(qp.payload, qp.header.property);

  // Ensure that we can constrain the view.
  std::size_t n = qp.header.length - bytes(qp.header);
  if (remaining(v) < n)
    return AVAILABLE_QUEUE_PROPERTY_PAYLOAD;

  // Try reading the payload, updating the view on success.
  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, qp.payload, qp.header.property))
    return err;

  if(not update(v, c))
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
  to_buffer(v, q.port);
  to_buffer(v, q.length);
  pad(v, 6);
  return to_buffer(v, q.properties);
}

Error_condition
from_buffer(Buffer_view& v, Queue& q)
{
  if (not available(v, bytes(q)))
    return AVAILABLE_QUEUE;
  from_buffer(v, q.queue_id);
  from_buffer(v, q.port);
  from_buffer(v, q.length);
  pad(v, 6);

  std::size_t n = q.length - bytes(q);
  if (remaining(v) < n)
    return AVAILABLE_QUEUE_PROPERTIES;

  Buffer_view c = constrain(v, n);
  if (Error_decl err = from_buffer(c, q.properties))
    return err;

  if(not update(v, c))
    return EXCESS_QUEUE;

  return SUCCESS;
}

std::string
to_string(const Queue& q, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Queue");

  nvp_to_string(ss, f, "Queue ID", q.queue_id);
  nvp_to_string(ss, f, "Port", q.port);
  nvp_to_string(ss, f, "Length", q.length);

  ss << to_string(q.properties, f);

  close_block(ss, f, "Queue");
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
// Role enum

std::string
to_string(const Role r)
{
  switch(r) {
  case Role::R_NO_CHANGE: return "No Change";
  case Role::R_EQUAL: return "Equal";
  case Role::R_MASTER: return "Master";
  case Role::R_SLAVE: return "Slave";
  default: return "Unknown";
  }
}

// -------------------------------------------------------------------------- //
// Role Request

std::string
to_string(const Role_req& rr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "RoleReq");

  nvp_to_string(ss, f, "Role", to_string(rr.role), int(rr.role));
  nvp_to_string(ss, f, "Generation ID", rr.generation_id);

  close_block(ss, f, "RoleReq");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Role Response

std::string
to_string(const Role_res& rr, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "RoleRes");

  nvp_to_string(ss, f, "Role", to_string(rr.role), int(rr.role));
  nvp_to_string(ss, f, "Generation ID", rr.generation_id);

  close_block(ss, f, "RoleRes");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Get Asnyc Response

std::string
to_string(const Get_async_res& gar, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "GetAsyncRes");

  nvp_to_string(ss, f, "PacketIn Mask", gar.packet_in_mask);
  nvp_to_string(ss, f, "PacketIn Mask Slave", gar.packet_in_mask_slave);
  nvp_to_string(ss, f, "PortStatus Mask", gar.port_status_mask);
  nvp_to_string(ss, f, "PortStatus Mask Slave", gar.port_status_mask_slave);
  nvp_to_string(ss, f, "FlowRemoved Mask", gar.flow_removed_mask);
  nvp_to_string(ss, f, "FlowRemoved Mask Slave", gar.flow_removed_mask_slave);

  close_block(ss, f, "GetAsyncRes");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Set Asnyc

std::string
to_string(const Set_async& sa, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "SetAsync");

  nvp_to_string(ss, f, "PacketIn Mask", sa.packet_in_mask);
  nvp_to_string(ss, f, "PacketIn Mask Slave", sa.packet_in_mask_slave);
  nvp_to_string(ss, f, "PortStatus Mask", sa.port_status_mask);
  nvp_to_string(ss, f, "PortStatus Mask Slave", sa.port_status_mask_slave);
  nvp_to_string(ss, f, "FlowRemoved Mask", sa.flow_removed_mask);
  nvp_to_string(ss, f, "FlowRemoved Mask Slave", sa.flow_removed_mask_slave);

  close_block(ss, f, "SetAsync");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Meter mod

Error_condition
to_buffer(Buffer_view& v, const Meter_mod& mm)
{
  if (not available(v, bytes(mm)))
    return AVAILABLE_METER_MOD;
  to_buffer(v, mm.command);
  to_buffer(v, mm.flags);
  to_buffer(v, mm.meter_id);
  return to_buffer(v, mm.meter_bands);
}

Error_condition
from_buffer(Buffer_view& v, Meter_mod& mm)
{
  if (not available(v, bytes(mm)))
    return AVAILABLE_METER_MOD;
  from_buffer(v, mm.command);
  from_buffer(v, mm.flags);
  from_buffer(v, mm.meter_id);
  return from_buffer(v, mm.meter_bands);
}

std::string
to_string(Meter_mod::Command t)
{
  switch(t) {
  case Meter_mod::ADD: return "ADD";
  case Meter_mod::MODIFY: return "MODIFY";
  case Meter_mod::DELETE: return "DELETE";
  default: return "Unknown";
  }
}

std::string
to_string(Meter_mod::Flags_type t)
{
  switch(t) {
  case Meter_mod::KBPS: return "KBPS";
  case Meter_mod::PKTPS: return "PKTPS";
  case Meter_mod::BURST: return "BURST";
  case Meter_mod::STATS: return "STATS";
  default: return "Unknown";
  }
}

std::string
to_string(Meter_mod::Id_value t)
{
  switch(t) {
  case Meter_mod::MAX: return "MAX";
  case Meter_mod::SLOW_PATH: return "SLOW_PATH";
  case Meter_mod::CONTROLLER: return "CONTROLLER";
  case Meter_mod::ALL: return "ALL";
  default: return "Unknown";
  }
}

std::string
to_string(const Meter_mod& mm, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "MeterMod");

  nvp_to_string(ss, f, "Command", to_string(mm.command), int(mm.command));
  nvp_to_string(ss, f, "Flag", to_string(mm.flags), int(mm.flags));
  nvp_to_string(ss, f, "Meter ID", to_string(mm.meter_id), int(mm.meter_id));

  ss << to_string(mm.meter_bands, f);

  close_block(ss, f, "MeterMod");
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
  case MULTIPART_REQ: new (&p.data.multipart_req) Multipart_req(); break;
  case MULTIPART_RES: new (&p.data.multipart_res) Multipart_res(); break;
  case BARRIER_REQ: new (&p.data.barrier_req) Barrier_req(); break;
  case BARRIER_RES: new (&p.data.barrier_res) Barrier_res(); break;
  case QUEUE_GET_CONFIG_REQ:
    new (&p.data.queue_get_config_req) Queue_get_config_req(); break;
  case QUEUE_GET_CONFIG_RES:
    new (&p.data.queue_get_config_res) Queue_get_config_res(); break;
  case ROLE_REQ: new (&p.data.role_req) Role_req(); break;
  case ROLE_RES: new (&p.data.role_res) Role_res(); break;
  case GET_ASYNC_REQ: new (&p.data.get_async_req) Get_async_req(); break;
  case GET_ASYNC_RES: new (&p.data.get_async_res) Get_async_res(); break;
  case SET_ASYNC: new (&p.data.set_async) Set_async(); break;
  case METER_MOD: new (&p.data.meter_mod) Meter_mod(); break;
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
  case MULTIPART_REQ:
    new (&p.data.multipart_req) Multipart_req(std::move(x.data.multipart_req)); break;
  case MULTIPART_RES:
    new (&p.data.multipart_res) Multipart_res(std::move(x.data.multipart_res)); break;
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
  case ROLE_REQ: new (&p.data.role_req) Role_req(std::move(x.data.role_req));
    break;
  case ROLE_RES: new (&p.data.role_res) Role_res(std::move(x.data.role_res));
    break;
  case GET_ASYNC_REQ:
    new (&p.data.get_async_req) Get_async_req(std::move(x.data.get_async_req));
    break;
  case GET_ASYNC_RES:
    new (&p.data.get_async_res) Get_async_res(std::move(x.data.get_async_res));
    break;
  case SET_ASYNC:
    new (&p.data.set_async) Set_async(std::move(x.data.set_async)); break;
  case METER_MOD:
    new (&p.data.meter_mod) Meter_mod(std::move(x.data.meter_mod)); break;
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
  case MULTIPART_REQ:
    new (&p.data.multipart_req) Multipart_req(x.data.multipart_req); break;
  case MULTIPART_RES:
    new (&p.data.multipart_res) Multipart_res(x.data.multipart_res); break;
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
  case ROLE_REQ: new (&p.data.role_req) Role_req(x.data.role_req); break;
  case ROLE_RES: new (&p.data.role_res) Role_res(x.data.role_res); break;
  case GET_ASYNC_REQ:
    new (&p.data.get_async_req) Get_async_req(x.data.get_async_req); break;
  case GET_ASYNC_RES:
    new (&p.data.get_async_res) Get_async_res(x.data.get_async_res); break;
  case SET_ASYNC: new (&p.data.set_async) Set_async(x.data.set_async); break;
  case METER_MOD:
    new (&p.data.meter_mod) Meter_mod(x.data.meter_mod); break;
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
  case EXPERIMENTER: p.data.experimenter = std::move(x.data.experimenter);
    break;
  case FEATURE_REQ: p.data.feature_req = std::move(x.data.feature_req); break;
  case FEATURE_RES: p.data.feature_res = std::move(x.data.feature_res); break;
  case GET_CONFIG_REQ:
    p.data.get_config_req = std::move(x.data.get_config_req); break;
  case GET_CONFIG_RES:
    p.data.get_config_res = std::move(x.data.get_config_res); break;
  case SET_CONFIG: p.data.set_config = std::move(x.data.set_config); break;
  case PACKET_IN: p.data.packet_in = std::move(x.data.packet_in); break;
  case FLOW_REMOVED:
    p.data.flow_removed = std::move(x.data.flow_removed); break;
  case PORT_STATUS: p.data.port_status = std::move(x.data.port_status); break;
  case PACKET_OUT: p.data.packet_out = std::move(x.data.packet_out); break;
  case FLOW_MOD: p.data.flow_mod = std::move(x.data.flow_mod); break;
  case GROUP_MOD: p.data.group_mod = std::move(x.data.group_mod); break;
  case PORT_MOD: p.data.port_mod = std::move(x.data.port_mod); break;
  case TABLE_MOD: p.data.table_mod = std::move(x.data.table_mod); break;
  case MULTIPART_REQ: p.data.multipart_req = std::move(x.data.multipart_req);
    break;
  case MULTIPART_RES: p.data.multipart_res = std::move(x.data.multipart_res);
    break;
  case BARRIER_REQ: p.data.barrier_req = std::move(x.data.barrier_req); break;
  case BARRIER_RES: p.data.barrier_res = std::move(x.data.barrier_res); break;
  case QUEUE_GET_CONFIG_REQ:
    p.data.queue_get_config_req = std::move(x.data.queue_get_config_req);
    break;
  case QUEUE_GET_CONFIG_RES:
    p.data.queue_get_config_res = std::move(x.data.queue_get_config_res);
    break;
  case ROLE_REQ: p.data.role_req = std::move(x.data.role_req); break;
  case ROLE_RES: p.data.role_res = std::move(x.data.role_res); break;
  case GET_ASYNC_REQ: p.data.get_async_req = std::move(x.data.get_async_req);
    break;
  case GET_ASYNC_RES: p.data.get_async_res = std::move(x.data.get_async_res);
    break;
  case SET_ASYNC: p.data.set_async = std::move(x.data.set_async); break;
  case METER_MOD: p.data.meter_mod = std::move(x.data.meter_mod); break;
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
  case MULTIPART_REQ: p.data.multipart_req = x.data.multipart_req; break;
  case MULTIPART_RES: p.data.multipart_res = x.data.multipart_res; break;
  case BARRIER_REQ: p.data.barrier_req = x.data.barrier_req; break;
  case BARRIER_RES: p.data.barrier_res = x.data.barrier_res; break;
  case QUEUE_GET_CONFIG_REQ:
    p.data.queue_get_config_req = x.data.queue_get_config_req; break;
  case QUEUE_GET_CONFIG_RES:
    p.data.queue_get_config_res = x.data.queue_get_config_res; break;
  case ROLE_REQ: p.data.role_req = x.data.role_req; break;
  case ROLE_RES: p.data.role_res = x.data.role_res; break;
  case GET_ASYNC_REQ: p.data.get_async_req = x.data.get_async_req; break;
  case GET_ASYNC_RES: p.data.get_async_res = x.data.get_async_res; break;
  case SET_ASYNC: p.data.set_async = x.data.set_async; break;
  case METER_MOD: p.data.meter_mod = x.data.meter_mod; break;
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
  case MULTIPART_REQ: p.data.multipart_req.~Multipart_req(); break;
  case MULTIPART_RES: p.data.multipart_res.~Multipart_res(); break;
  case BARRIER_REQ: p.data.barrier_req.~Barrier_req(); break;
  case BARRIER_RES: p.data.barrier_res.~Barrier_res(); break;
  case QUEUE_GET_CONFIG_REQ:
    p.data.queue_get_config_req.~Queue_get_config_req(); break;
  case QUEUE_GET_CONFIG_RES:
    p.data.queue_get_config_res.~Queue_get_config_res(); break;
  case ROLE_REQ: p.data.role_req.~Role_req(); break;
  case ROLE_RES: p.data.role_res.~Role_res(); break;
  case GET_ASYNC_REQ: p.data.get_async_req.~Get_async_req(); break;
  case GET_ASYNC_RES: p.data.get_async_res.~Get_async_res(); break;
  case SET_ASYNC: p.data.set_async.~Set_async(); break;
  case METER_MOD: p.data.meter_mod.~Meter_mod(); break;
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
  case MULTIPART_REQ: return a.data.multipart_req == b.data.multipart_req;
  case MULTIPART_RES: return a.data.multipart_res == b.data.multipart_res;
  case BARRIER_REQ: return a.data.barrier_req == b.data.barrier_req;
  case BARRIER_RES: return a.data.barrier_res == b.data.barrier_res;
  case QUEUE_GET_CONFIG_REQ:
    return a.data.queue_get_config_req == b.data.queue_get_config_req;
  case QUEUE_GET_CONFIG_RES:
    return a.data.queue_get_config_res == b.data.queue_get_config_res;
  case ROLE_REQ: return a.data.role_req == b.data.role_req;
  case ROLE_RES: return a.data.role_res == b.data.role_res;
  case GET_ASYNC_REQ: return a.data.get_async_req == b.data.get_async_req;
  case GET_ASYNC_RES: return a.data.get_async_res == b.data.get_async_res;
  case SET_ASYNC: return a.data.set_async == b.data.set_async;
  case METER_MOD: return a.data.meter_mod == b.data.meter_mod;
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
  case MULTIPART_REQ: return bytes(p.data.multipart_req);
  case MULTIPART_RES: return bytes(p.data.multipart_res);
  case BARRIER_REQ: return bytes(p.data.barrier_req);
  case BARRIER_RES: return bytes(p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ: return bytes(p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES: return bytes(p.data.queue_get_config_res);
  case ROLE_REQ: return bytes(p.data.role_req);
  case ROLE_RES: return bytes(p.data.role_res);
  case GET_ASYNC_REQ: return bytes(p.data.get_async_req);
  case GET_ASYNC_RES: return bytes(p.data.get_async_res);
  case SET_ASYNC: return bytes(p.data.set_async);
  case METER_MOD: return bytes(p.data.meter_mod);
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
  case MULTIPART_REQ: return is_valid(p.data.multipart_req);
  case MULTIPART_RES: return is_valid(p.data.multipart_res);
  case BARRIER_REQ: return is_valid(p.data.barrier_req);
  case BARRIER_RES: return is_valid(p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ: return is_valid(p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES: return is_valid(p.data.queue_get_config_res);
  case ROLE_REQ: return is_valid(p.data.role_req);
  case ROLE_RES: return is_valid(p.data.role_res);
  case GET_ASYNC_REQ: return is_valid(p.data.get_async_req);
  case GET_ASYNC_RES: return is_valid(p.data.get_async_res);
  case SET_ASYNC: return is_valid(p.data.set_async);
  case METER_MOD: return is_valid(p.data.meter_mod);
  default: return BAD_MESSAGE;
  }
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
  case MULTIPART_REQ: return to_buffer(v, p.data.multipart_req);
  case MULTIPART_RES: return to_buffer(v, p.data.multipart_res);
  case BARRIER_REQ: return to_buffer(v, p.data.barrier_req);
  case BARRIER_RES: return to_buffer(v, p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ:
    return to_buffer(v, p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES:
    return to_buffer(v, p.data.queue_get_config_res);
  case ROLE_REQ: return to_buffer(v, p.data.role_req);
  case ROLE_RES: return to_buffer(v, p.data.role_res);
  case GET_ASYNC_REQ: return to_buffer(v, p.data.get_async_req);
  case GET_ASYNC_RES: return to_buffer(v, p.data.get_async_res);
  case SET_ASYNC: return to_buffer(v, p.data.set_async);
  case METER_MOD: return to_buffer(v, p.data.meter_mod);
  default: variant_error(t);
  }
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
  case MULTIPART_REQ: return from_buffer(v, p.data.multipart_req);
  case MULTIPART_RES: return from_buffer(v, p.data.multipart_res);
  case BARRIER_REQ: return from_buffer(v, p.data.barrier_req);
  case BARRIER_RES: return from_buffer(v, p.data.barrier_res);
  case QUEUE_GET_CONFIG_REQ:
    return from_buffer(v, p.data.queue_get_config_req);
  case QUEUE_GET_CONFIG_RES:
    return from_buffer(v, p.data.queue_get_config_res);
  case ROLE_REQ: return from_buffer(v, p.data.role_req);
  case ROLE_RES: return from_buffer(v, p.data.role_res);
  case GET_ASYNC_REQ: return from_buffer(v, p.data.get_async_req);
  case GET_ASYNC_RES: return from_buffer(v, p.data.get_async_res);
  case SET_ASYNC: return from_buffer(v, p.data.set_async);
  case METER_MOD: return from_buffer(v, p.data.meter_mod);
  default: variant_error(t);
  }
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
  case MULTIPART_REQ: return to_string(p.data.multipart_req, fmt);
  case MULTIPART_RES: return to_string(p.data.multipart_res, fmt);
  case BARRIER_REQ: return to_string(p.data.barrier_req, fmt);
  case BARRIER_RES: return to_string(p.data.barrier_res, fmt);
  case QUEUE_GET_CONFIG_REQ:
    return to_string(p.data.queue_get_config_req, fmt);
  case QUEUE_GET_CONFIG_RES:
    return to_string(p.data.queue_get_config_res, fmt);
  case ROLE_REQ: return to_string(p.data.role_req, fmt);
  case ROLE_RES: return to_string(p.data.role_res, fmt);
  case GET_ASYNC_REQ: return to_string(p.data.get_async_req, fmt);
  case GET_ASYNC_RES: return to_string(p.data.get_async_res, fmt);
  case SET_ASYNC: return to_string(p.data.set_async, fmt);
  case METER_MOD: return to_string(p.data.meter_mod, fmt);
  default: variant_error(t);
  }
}

// -------------------------------------------------------------------------- //
// Header

//inline bool
//check_header(const Buffer_view& v, const Header& h)
//{
//  return is_valid(h) and available(v, h.length - bytes(h));
//}

Error_condition
to_buffer(Buffer_view& v, const Header& h)
{
  to_buffer(v, h.version);
  to_buffer(v, h.type);
  to_buffer(v, h.length);
  to_buffer(v, h.xid);
  return SUCCESS;//check_header(v, h);
}

Error_condition
from_buffer(Buffer_view& v, Header& h)
{
  from_buffer(v, h.version);
  from_buffer(v, h.type);
  from_buffer(v, h.length);
  from_buffer(v, h.xid);
  return SUCCESS;//check_header(v, h);
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

} // namespace v1_3_1
} // namesapce ofp
} // namespace flog
