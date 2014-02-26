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

#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_0_IPP
#define FLOWGRAMMABLE_PROTO_OFP_V1_0_IPP

namespace flog {
namespace ofp {
namespace v1_0 {

// A helper facility for mapping various enumeration values with availability
// error codes. Specializations can be found throughout this file.
template<typename T, T K> struct available_error;

// Another helper facility for doing the same with status features.
template<Message_type M, Stats_type S> struct stats_available_error;

// -------------------------------------------------------------------------- //
// Match

inline bool 
operator==(const Match& a, const Match& b) {
  return a.wildcards == b.wildcards 
     and a.in_port == b.in_port 
     and a.dl_src == b.dl_src
     and a.dl_dst == b.dl_dst
     and a.dl_vlan == b.dl_vlan 
     and a.dl_pcp == b.dl_pcp 
     and a.dl_type == b.dl_type 
     and a.nw_tos == b.nw_tos 
     and a.nw_proto == b.nw_proto 
     and a.nw_src == b.nw_src 
     and a.nw_dst == b.nw_dst 
     and a.tp_src == b.tp_src;
}

inline bool
operator!=(const Match& a, const Match& b) {
  return !(a == b);
}

constexpr std::size_t 
bytes(const Match&) { return 40; }

inline Error_condition
is_valid(const Match& m) { return SUCCESS; }

constexpr bool
wildcard_in_port(Match::Wildcards w) { return w & Match::IN_PORT; }

constexpr bool
wildcard_dl_src(Match::Wildcards w) { return w & Match::DL_SRC; }

constexpr bool
wildcard_dl_dst(Match::Wildcards w) { return w & Match::DL_DST; }

constexpr bool
wildcard_dl_vlan(Match::Wildcards w) { return w & Match::DL_VLAN; }

constexpr bool
wildcard_dl_pcp(Match::Wildcards w) { return w & Match::DL_VLAN_PCP; }

constexpr bool
wildcard_dl_type(Match::Wildcards w) { return w & Match::DL_TYPE; }

constexpr bool
wildcard_nw_tos(Match::Wildcards w) { return w & Match::NW_TOS; }

constexpr bool
wildcard_nw_proto(Match::Wildcards w) { return w & Match::NW_PROTO; }

inline std::size_t
wildcard_nw_src(Match::Wildcards w) {
  std::size_t mask = (w >> 8) & 0x3f;
  return mask >= 32 ? 0 : 32 - mask;
}

inline std::size_t
wildcard_nw_dst(Match::Wildcards w) {
  std::size_t mask = (w >> 14) & 0x3f;
  return mask >= 32 ? 0 : 32 - mask;
}

constexpr bool
wildcard_tp_src(Match::Wildcards w) { return w & Match::TP_SRC; }

constexpr bool
wildcard_tp_dst(Match::Wildcards w) { return w & Match::TP_DST; }

// -------------------------------------------------------------------------- //
// Action_type

inline Error_condition
is_valid(Action_type t) {
  return ok(t <= ACTION_ENQUEUE or t == ACTION_VENDOR, BAD_ACTION);
}

// -------------------------------------------------------------------------- //
// Action_output

inline bool
operator==(const Action_output& a, const Action_output& b) {
  return a.port == b.port and b.max_len == b.max_len;
}

inline bool
operator!=(const Action_output& a, const Action_output& b) {
  return !(a == b);
}

constexpr Error_condition
is_valid(const Action_output&) { return SUCCESS; }

constexpr std::size_t 
bytes(const Action_output&) { return 4; }

// -------------------------------------------------------------------------- //
// Action_set_vlan_vid

inline bool
operator==(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b) {
  return a.vlan_vid == b.vlan_vid;
}

inline bool
operator!=(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b) {
  return !(a == b);
}

constexpr Error_condition
is_valid(const Action_set_vlan_vid& a) { return SUCCESS; }

constexpr std::size_t 
bytes(const Action_set_vlan_vid&) { return 4; }

// -------------------------------------------------------------------------- //
// Action_set_vlan_pcp

inline bool
operator==(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b) {
  return a.value == b.value;
}

inline bool
operator!=(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b) {
  return !(a == b);
}

constexpr Error_condition
is_valid(const Action_set_vlan_pcp&) { return SUCCESS; }

constexpr std::size_t 
bytes(const Action_set_vlan_pcp&) { return 4; }

// -------------------------------------------------------------------------- //
// Action_strip_vlan

constexpr std::size_t 
bytes(const Action_strip_vlan&) { return 4; }

constexpr Error_condition
is_valid(const Action_strip_vlan& a) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action_dl_addr

template<> 
  struct available_error<Action_type, ACTION_SET_DL_SRC> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_DL_SRC;
  };

template<> 
  struct available_error<Action_type, ACTION_SET_DL_DST> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_DL_DST;
  };

template<Action_type K>
  constexpr std::size_t 
  bytes(const Action_dl_addr<K>& a) { return 12; }

template<Action_type K>
  constexpr Error_condition
  is_valid(const Action_dl_addr<K>& a) { return SUCCESS; }

template<Action_type K>
  Error_condition 
  to_buffer(Buffer_view& v, const Action_dl_addr<K>& a)
  {
    if (not available (v, bytes(a)))
      return available_error<Action_type, K>::value;
    to_buffer(v, a.dl_addr);
    pad(v, 6);
    return SUCCESS;
  }

template<Action_type K>
  Error_condition 
  from_buffer(Buffer_view& v, Action_dl_addr<K>& a)
  {
    if (not available (v, bytes(a)))
      return available_error<Action_type, K>::value;
    from_buffer(v, a.dl_addr);
    pad(v, 6);
    return SUCCESS;
  }

template<Action_type K>
  inline std::string 
  to_string(const Action_dl_addr<K>& a,  Formatter& f)
  {
    std::stringstream ss;
    nvp_to_string(ss, f, "Address", to_string(a.dl_addr));
    return ss.str();
  }

// -------------------------------------------------------------------------- //
// Action_set_nw_addr

template<> 
  struct available_error<Action_type, ACTION_SET_NW_SRC> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_NW_SRC;
  };

template<> 
  struct available_error<Action_type, ACTION_SET_NW_DST> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_NW_DST;
  };

template<Action_type K>
  constexpr std::size_t 
  bytes(const Action_set_nw_addr<K>& a) { return 4; }

template<Action_type K>
  constexpr Error_condition
  is_valid(const Action_set_nw_addr<K>& a) { return SUCCESS; }

template<Action_type K>
  inline Error_condition 
  to_buffer(Buffer_view& v, const Action_set_nw_addr<K>& a)
  {
    if (not available(v, bytes(a)))
      return available_error<Action_type, K>::value;
    to_buffer(v, a.addr);
    return SUCCESS;
  }

template<Action_type K>
  inline Error_condition 
  from_buffer(Buffer_view& v, Action_set_nw_addr<K>& a)
  {
    if (not available(v, bytes(a)))
      return available_error<Action_type, K>::value;
    from_buffer(v, a.addr);
    return SUCCESS;
  }

template<Action_type K>
  inline std::string 
  to_string(const Action_set_nw_addr<K>& na,  Formatter& f)
  {
    std::stringstream ss;
    ss << "IPv4 Addr: " << to_string(na.addr) << std::endl;
    return ss.str();
  }

// -------------------------------------------------------------------------- //
// Action_set_nw_tos

inline bool
operator==(const Action_set_nw_tos& a, const Action_set_nw_tos& b) {
  return a.value == b.value;
}

inline bool
operator!=(const Action_set_nw_tos& a, const Action_set_nw_tos& b) {
  return !(a == b);
}

constexpr std::size_t 
bytes(const Action_set_nw_tos&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_nw_tos& a) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action_set_tp_port

template<> 
  struct available_error<Action_type, ACTION_SET_TP_SRC> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_TP_SRC;
  };

template<> 
  struct available_error<Action_type, ACTION_SET_TP_DST> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_TP_DST;
  };

template<Action_type K>
  inline bool
  operator==(const Action_set_tp_port<K>& a, const Action_set_tp_port<K>& b) {
    return a.value == b.value;
  }

template<Action_type K>
  inline bool
  operator!=(const Action_set_tp_port<K>& a, const Action_set_tp_port<K>& b) {
    return !(a == b);
  }

template<Action_type K>
  constexpr std::size_t
  bytes(const Action_set_tp_port<K>& a) { return 4; }

template<Action_type K>
  inline Error_condition
  is_valid(const Action_set_tp_port<K>& a) { return SUCCESS; }

template<Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_set_tp_port<K>& a) {
    if (not available(v, bytes(a)))
      return available_error<Action_type, K>::value;
    to_buffer(v, a.value);
    pad(v, 2);
    return SUCCESS;
  }

template<Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_set_tp_port<K>& a) {
    if (not available(v, bytes(a)))
      return available_error<Action_type, K>::value;
    from_buffer(v, a.value);
    pad(v, 2);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Action_enqueue

inline bool
operator==(const Action_enqueue& a, const Action_enqueue& b) {
  return a.port == b.port and a.queue_id == b.queue_id;
}

inline bool
operator!=(const Action_enqueue& a, const Action_enqueue& b) {
  return !(a == b);
}

constexpr std::size_t 
bytes(const Action_enqueue&) { return 12; }

inline Error_condition
is_valid(const Action_enqueue& a) {
  return ok(a.port < 0xFF00 or a.port == 0xFFF8, BAD_ACTION_ENQUEUE_PORT);
}

// -------------------------------------------------------------------------- //
// Action_vendor

inline bool
operator==(const Action_vendor& a, const Action_vendor& b) {
  return a.vendor == b.vendor;
}

inline bool
operator!=(const Action_vendor& a, const Action_vendor& b) {
  return !(a == b);
}

constexpr std::size_t 
bytes(const Action_vendor&) { return 4; }

constexpr Error_condition
is_valid(const Action_vendor& a) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action_payload

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_output::Tag, Args&&... args) {
    new (&p.data.output) Action_output(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_vlan_vid::Tag, Args&&... args) {
    new (&p.data.vlan_vid) Action_set_vlan_vid(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_vlan_pcp::Tag, Args&&... args) {
    new (&p.data.vlan_pcp) Action_set_vlan_pcp(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_strip_vlan::Tag, Args&&... args) {
    new (&p.data.strip_vlan) Action_strip_vlan(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_dl_src::Tag, Args&&... args) {
    new (&p.data.dl_src) Action_set_dl_src(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_dl_dst::Tag, Args&&... args) {
    new (&p.data.dl_dst) Action_set_dl_dst(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_src::Tag, Args&&... args) {
    new (&p.data.nw_src) Action_set_nw_src(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_dst::Tag, Args&&... args) {
    new (&p.data.nw_dst) Action_set_nw_dst(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_tos::Tag, Args&&... args) {
    new (&p.data.nw_tos) Action_set_nw_tos(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_tp_src::Tag, Args&&... args) {
    new (&p.data.tp_src) Action_set_tp_src(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_tp_dst::Tag, Args&&... args) {
    new (&p.data.tp_dst) Action_set_tp_dst(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_enqueue::Tag, Args&&... args) {
    new (&p.data.enqueue) Action_enqueue(std::forward<Args>(args)...);
  }
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_vendor::Tag, Args&&... args) {
    new (&p.data.vendor) Action_vendor(std::forward<Args>(args)...);
  }

// -------------------------------------------------------------------------- //
// Action_header

inline bool
operator==(const Action_header& a, const Action_header& b)
{
  return a.type == b.type and a.length == b.length;
}

inline bool
operator!=(const Action_header& a, const Action_header& b)
{
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_header&) { return 4; }

constexpr Error_condition
is_valid(const Action_header& h) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action

inline
Action::Action(const Action& x)
  : header(x.header) { construct(payload, x.payload, header.type); }

inline Action&
Action::operator=(const Action& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

template<typename T, typename Tag>
  Action::Action(T&& x) 
    : header(x) { construct(payload, Tag(), std::forward<T>(x)); }

template<typename Tag, typename... Args>
  inline
  Action::Action(Tag t, Args&&... args)
  : header(t.value) { 
    construct(payload, t, std::forward<Args>(args)...);
    header.length = bytes(*this);
  }

inline bool 
operator==(const Action& a, const Action& b) {
  return a.header == b.header 
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Action& a, const Action& b) { return !(a == b); }

inline std::size_t
bytes(const Action& a) {
  return bytes(a.header) + bytes(a.payload, a.header.type);
}

inline Error_condition
is_valid(const Action& a) { return is_valid(a.payload, a.header.type); }

// -------------------------------------------------------------------------- //
// Port

inline bool 
operator==(const Port& a, const Port& b)
{
  return a.port_id == b.port_id
     and a.hw_addr == b.hw_addr
     and a.name == b.name
     and a.config == b.config
     and a.state == b.state
     and a.current == b.current
     and a.advertised == b.advertised
     and a.supported == b.supported
     and a.peer == b.peer;
}

inline bool 
operator!=(const Port& a, const Port& b) { return !(a == b); }

constexpr std::size_t 
bytes(const Port&) { return 48; }

constexpr Error_condition
is_valid(Port::Id id) { return ok(id <= 0xFF00 or id >= 0xFFF8, BAD_PORT_ID); }

constexpr Error_condition
is_valid(Port::Config) { return SUCCESS; }

constexpr Error_condition
is_valid(Port::State) { return SUCCESS; }

constexpr Error_condition
is_valid(Port::Features) { return SUCCESS; }

inline Error_condition
is_valid(const Port& p) {
  if (Error_decl err = is_valid(p.port_id))
    return err;
  if (Error_decl err = is_valid(p.config))
    return err;
  if (Error_decl err = is_valid(p.state))
    return err;
  if (Error_decl err = is_valid(p.current))
    return err;
  if (Error_decl err = is_valid(p.advertised))
    return err;
  if (Error_decl err = is_valid(p.supported))
    return err;
  if (Error_decl err = is_valid(p.peer))
    return err;
  return SUCCESS;
}

constexpr bool
port_config_port_down(uint32_t c) { return c & Port::PORT_DOWN; }

constexpr bool
port_config_no_stp(uint32_t c) { return c & Port::NO_STP; }

constexpr bool
port_config_no_recv(uint32_t c) { return c & Port::NO_RECV; }

constexpr bool
port_config_no_recv_stp(uint32_t c) { return c & Port::NO_RECV_STP; }

constexpr bool
port_config_no_flood(uint32_t c) { return c & Port::NO_FLOOD; }

constexpr bool
port_config_no_fwd(uint32_t c) { return c & Port::NO_FWD; }

constexpr bool 
port_config_no_packet_in(uint32_t c) { return c & Port::NO_PACKET_IN; }

constexpr bool
port_state_stp_listen(uint32_t s) { return s & Port::STP_LISTEN; }

constexpr bool
port_state_link_down(uint32_t s) { return s & Port::LINK_DOWN; }

constexpr bool
port_state_stp_learn(uint32_t s) { return s & Port::STP_LEARN; }

constexpr bool
port_state_stp_forward(uint32_t s) { return s & Port::STP_FORWARD; }

constexpr bool
port_state_stp_block(uint32_t s) { return s & Port::STP_BLOCK; }

constexpr bool
port_state_stp_mask(uint32_t s) { return s & Port::STP_MASK; }

constexpr bool
port_max(uint16_t p) { return p & Port::MAX; }

constexpr bool
port_in_port(uint16_t p) { return p & Port::IN_PORT; }

constexpr bool
port_table(uint16_t p) { return p & Port::TABLE; }

constexpr bool
port_normal(uint16_t p) { return p & Port::NORMAL; }

constexpr bool
port_flood(uint16_t p) { return p & Port::FLOOD; }

constexpr bool
port_all(uint16_t p) { return p & Port::ALL; }

constexpr bool
port_controller(uint16_t p) { return p & Port::CONTROLLER; }

constexpr bool
port_local(uint16_t p) { return p & Port::LOCAL; }

constexpr bool
port_none(uint16_t p) { return p & Port::NONE; }

constexpr bool
port_feature_10mb_hd(uint32_t p) { return p & Port::TEN_MB_HD; }

constexpr bool
port_feature_10mb_fd(uint32_t p) { return p & Port::TEN_MB_FD; }

constexpr bool
port_feature_100mb_hd(uint32_t p) { return p & Port::HUNDRED_MB_HD; }

constexpr bool
port_feature_100mb_fd(uint32_t p) { return p & Port::HUNDRED_MB_FD; }

constexpr bool
port_feature_1gb_hd(uint32_t p) { return p & Port::ONE_GB_HD; }

constexpr bool
port_feature_1gb_fd(uint32_t p) { return p & Port::ONE_GB_FD; }

constexpr bool
port_feature_10gb_fd(uint32_t p) { return p & Port::TEN_GB_FD; }

constexpr bool
port_feature_copper(uint32_t p) { return p & Port::COPPER; }

constexpr bool
port_feature_fiber(uint32_t p) { return p & Port::FIBER; }

constexpr bool
port_feature_auto_neg(uint32_t p) { return p & Port::AUTO_NEG; }

constexpr bool
port_feature_pause(uint32_t p) { return p & Port::PAUSE; }

constexpr bool
port_feature_pause_asym(uint32_t p) { return p & Port::PAUSE_ASYM; }

// -------------------------------------------------------------------------- //
// Version Type

inline Error_condition
is_valid(Version_type v) { return ok(v == VERSION, BAD_VERSION); }

// -------------------------------------------------------------------------- //
// Message Type

inline Error_condition
is_valid(Message_type m) { return ok(m <= QUEUE_GET_CONFIG_RES, BAD_MESSAGE); }

// -------------------------------------------------------------------------- //
// Hello

inline bool 
operator==(const Hello& a, const Hello& b) { return a.data == b.data; }

inline bool 
operator!=(const Hello& a, const Hello& b) { return !(a == b); }

inline std::size_t 
bytes(const Hello& m) { return bytes(m.data); }

constexpr Error_condition
is_valid(const Hello& m0) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Error

inline bool 
operator==(const Error& a, const Error& b) {
  return a.type == b.type and a.code.value == b.code.value and a.data == b.data;
}

inline bool
operator!=(const Error& a, const Error& b) { return !(a == b); }

inline std::size_t 
bytes(const Error& e) { return 4 + bytes(e.data); }

inline Error_condition
is_valid(Error::Type t) { 
  return ok(t <= Error::QUEUE_OP_FAILED,  BAD_ERROR_TYPE);
}

inline Error_condition
is_valid(Error::Hello_failed c) { 
  return ok(c <= Error::HF_EPERM, BAD_HELLO_FAILED);
}

inline Error_condition
is_valid(Error::Bad_request c) { 
  return ok(c <= Error::BR_BUFFER_UNKNOWN, BAD_BAD_REQUEST);
}

inline Error_condition
is_valid(Error::Bad_action c) { 
  return ok(c <= Error::BA_BAD_QUEUE, BAD_BAD_ACTION); 
}

inline Error_condition
is_valid(Error::Flow_mod_failed c) { 
  return ok(c <= Error::FMF_UNSUPPORTED, BAD_FLOW_MOD_FAILED);
}

inline Error_condition
is_valid(Error::Port_mod_failed c) { 
  return ok(c <= Error::PMF_BAD_HW_ADDR, BAD_PORT_MOD_FAILED);
}

inline Error_condition
is_valid(Error::Queue_op_failed c) {
  return ok(c <= Error::QOF_EPERM, BAD_QUEUE_OP_FAILED);
}

inline Error_condition
is_valid(Error::Type t, Error::Code c) {
  switch(t) {
  case Error::HELLO_FAILED: return is_valid(c.hf);
  case Error::BAD_REQUEST: return is_valid(c.br); 
  case Error::BAD_ACTION: return is_valid(c.ba);
  case Error::FLOW_MOD_FAILED: return is_valid(c.fmf);
  case Error::PORT_MOD_FAILED: return is_valid(c.pmf);
  case Error::QUEUE_OP_FAILED: return is_valid(c.qof);
  default: return BAD_ERROR_TYPE;
  };
}

inline Error_condition
is_valid(Error::Type t, const Greedy_buffer& data)
{
  if ( t != Error::HELLO_FAILED)
  {

     if(data.size() < 64)
       return BAD_ERROR_DATA;
  }

  return SUCCESS;
}



inline Error_condition
is_valid(const Error& e) { return is_valid(e.type, e.code); }

// -------------------------------------------------------------------------- //
// Echo_base

template<> 
  struct available_error<Message_type, ECHO_REQ> {
    static constexpr Error_condition value = AVAILABLE_ECHO_REQ;
  };

template<> 
  struct available_error<Message_type, ECHO_RES> {
    static constexpr Error_condition value = AVAILABLE_ECHO_RES;
  };

template<Message_type K>
  inline bool
  operator==(const Echo_base<K>& a, const Echo_base<K>& b) {
    return a.data == b.data;
  }

template<Message_type K>
  inline bool
  operator!=(const Echo_base<K>& a, const Echo_base<K>& b) {
    return !(a == b);
  }

template<Message_type K>
  inline std::size_t
  bytes(const Echo_base<K>& e) { return e.data.size(); }

template<Message_type K>
  constexpr Error_condition
  is_valid(const Echo_base<K>&) { return SUCCESS; }

template<Message_type K>
  inline Error_condition
  to_buffer(Buffer_view& v, const Echo_base<K>& e) {
    if (not available(v, bytes(e)))
      return available_error<Message_type, K>::value;
    to_buffer(v, e.data); 
    return SUCCESS;
  }

template<Message_type K>
  inline Error_condition
  from_buffer(Buffer_view& v, Echo_base<K>& e) {
    if (not available(v, bytes(e)))
      return available_error<Message_type, K>::value;
    from_buffer(v, e.data); 
    return SUCCESS;
  }

// To string
template<Message_type K>
  inline std::string
  to_string(const Echo_base<K>& e, Formatter& f) {
    return to_string(e.data, f); 
  }

// -------------------------------------------------------------------------- //
// Vendor

// Equality comparison
inline bool 
operator==(const Vendor& a, const Vendor& b) {
  return a.vendor_id == b.vendor_id and a.data == b.data;
}

inline bool
operator!=(const Vendor& a, const Vendor& b) {
  return !(a == b);
}

inline std::size_t 
bytes(const Vendor& m) { return 4 + bytes(m.data); }

constexpr Error_condition
is_valid(const Vendor& m) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Feature_res

/// Initialize the Feature_response with a datapath id, the number of
/// supported buffers and tables, a bitfield indicating capabilities,
/// a bitfield describing supported actions, and a sequence of ports.
inline
Feature_res::Feature_res(uint64_t id, 
                         uint32_t nbufs, 
                         uint8_t ntbls, 
                         Capability c, 
                         Action a,
                         const Sequence<Port>& p)
  : datapath_id(id), n_buffers(nbufs), n_tbls(ntbls), capabilities(c)
  , feature_actions(a), ports(p) { }

inline
Feature_res::Feature_res(uint64_t id, 
                         uint32_t nbufs,
                         uint8_t ntbls,
                         Capability c, 
                         Action a,
                         std::initializer_list<Port> p)
  : datapath_id(id), n_buffers(nbufs), n_tbls(ntbls), capabilities(c)
  , feature_actions(a), ports(p) { }


inline bool 
operator==(const Feature_res& a, const Feature_res& b) {
  return a.datapath_id == b.datapath_id
     and a.n_buffers == b.n_buffers
     and a.n_tbls == b.n_tbls
     and a.capabilities == b.capabilities
     and a.feature_actions == b.feature_actions
     and a.ports == b.ports;
}

inline bool
operator!=(const Feature_res& a, const Feature_res& b) {
  return !(a == b);
}

inline std::size_t 
bytes(const Feature_res& fr) { return 24 + bytes(fr.ports); }

inline Error_condition
is_valid(const Feature_res::Capability& c) {
  return ok(!(c & 0x00000010), BAD_FEATURE_RES_CAPABILITY);
}
  
inline Error_condition
is_valid(const Feature_res& m) {
  if (Error_decl err = is_valid(m.capabilities))
    return err;
  if (Error_decl err = is_valid(m.capabilities))
    return err;
  if (Error_decl err = is_valid(m.ports))
    return err;
  return SUCCESS;
}

constexpr bool
feature_has_flow_stats(Feature_res::Capability c) { 
  return c & Feature_res::FLOW_STATS; 
}

constexpr bool
feature_has_table_stats(Feature_res::Capability c) { 
  return c & Feature_res::TABLE_STATS; 
}

constexpr bool
feature_has_port_stats(Feature_res::Capability c) { 
  return c & Feature_res::PORT_STATS; 
}

constexpr bool
feature_has_stp(Feature_res::Capability c) { 
  return c & Feature_res::STP; 
}

constexpr bool
feature_has_reserved(Feature_res::Capability c) { 
  return c & Feature_res::RESERVED; 
}

constexpr bool
feature_has_ip_reasm(Feature_res::Capability c) { 
  return c & Feature_res::IP_REASM; 
}

constexpr bool
feature_has_queue_stats(Feature_res::Capability c) { 
  return c & Feature_res::QUEUE_STATS; 
}

constexpr bool
feature_has_arp_match_ip(Feature_res::Capability c) { 
  return c & Feature_res::ARP_MATCH_IP; 
}

constexpr bool
feature_can_output(Feature_res::Action a) { 
  return a & Feature_res::OUTPUT; 
}

constexpr bool
feature_can_set_vlan_vid(Feature_res::Action a) { 
  return a & Feature_res::SET_VLAN_VID; 
}

constexpr bool
feature_can_set_vlan_pcp(Feature_res::Action a) { 
  return a & Feature_res::SET_VLAN_PCP; 
}

constexpr bool
feature_can_strip_vlan(Feature_res::Action a) { 
  return a & Feature_res::STRIP_VLAN; 
}

constexpr bool
feature_can_set_dl_src(Feature_res::Action a) { 
  return a & Feature_res::SET_DL_SRC; 
}

constexpr bool
feature_can_set_dl_dst(Feature_res::Action a) {
  return a & Feature_res::SET_DL_DST; 
}

constexpr bool
feature_can_set_nw_src(Feature_res::Action a) {
  return a & Feature_res::SET_NW_SRC; 
}

constexpr bool
feature_can_set_nw_dst(Feature_res::Action a) {
  return a & Feature_res::SET_NW_DST; 
}

constexpr bool
feature_can_set_nw_tos(Feature_res::Action a) {
  return a & Feature_res::SET_NW_TOS; 
}

constexpr bool
feature_can_set_tp_src(Feature_res::Action a) {
  return a & Feature_res::SET_TP_SRC; 
}

constexpr bool
feature_can_set_tp_dst(Feature_res::Action a) {
  return a & Feature_res::SET_TP_DST; 
}

constexpr bool
feature_can_enqueue(Feature_res::Action a) {
  return a & Feature_res::ENQUEUE; 
}

// -------------------------------------------------------------------------- //
// Config_message_base

template<>
  struct available_error<Message_type, GET_CONFIG_RES> {
    static constexpr Error_condition value = AVAILABLE_GET_CONFIG_RES;
  };

template<>
  struct available_error<Message_type, SET_CONFIG> {
    static constexpr Error_condition value = AVAILABLE_SET_CONFIG;
  };

template<Message_type T>
  inline bool 
  operator==(const Config_message_base<T>& a, const Config_message_base<T>& b) {
    return a.flags == b.flags and a.miss_send_len == b.miss_send_len;
  }

template<Message_type T>
  inline bool
  operator!=(const Config_message_base<T>& a, const Config_message_base<T>& b) {
    return !(a == b);
  }

template<Message_type T>
  inline std::size_t 
  bytes(const Config_message_base<T>&) { return 4; }

// FIXME: Are the flags expected to be mutally exclusive?
template<Message_type T>
  constexpr Error_condition
  is_valid(typename Config_message_base<T>::Flags f) 
  { 
    return ok(f <= Config_message_base<T>::FRAG_MASK, BAD_CONFIG); 
  }

template<Message_type T>
  constexpr Error_condition
  is_valid(const Config_message_base<T>& c) { return is_valid<T>(c.flags); }

template<Message_type T>
  inline Error_condition
  to_buffer(Buffer_view& b, const Config_message_base<T>& m)
  {
    if (not available(b, bytes(m)))
      return available_error<Message_type, T>::value;
    to_buffer(b, m.flags);
    to_buffer(b, m.miss_send_len);
    return SUCCESS;
  }

template<Message_type T>
  inline Error_condition
  from_buffer(Buffer_view& b, Config_message_base<T>& m)
  {
    if (not available(b, bytes(m)))
      return available_error<Message_type, T>::value;
    from_buffer(b, m.flags);
    from_buffer(b, m.miss_send_len);
    return SUCCESS;
  }

template<Message_type T>
  inline bool
  config_frag_normal(typename Config_message_base<T>::Flags f) { 
    return f & Config_message_base<T>::FRAG_NORMAL; 
  }

template<Message_type T>
  inline bool
  config_frag_drop(typename Config_message_base<T>::Flags f) { 
    return f & Config_message_base<T>::FRAG_DROP; 
  }

template<Message_type T>
  inline bool
  config_frag_reasm(typename Config_message_base<T>::Flags f) { 
    return f & Config_message_base<T>::FRAG_REASM; 
  }

template<Message_type T>
  inline bool
  config_frag_mask(typename Config_message_base<T>::Flags f) { 
    return f & Config_message_base<T>::FRAG_MASK; 
  }

// -------------------------------------------------------------------------- //
// Packet_in

inline bool
operator==(const Packet_in& a, const Packet_in& b) {
  return a.buffer_id == b.buffer_id
     and a.total_len == b.total_len
     and a.in_port == b.in_port
     and a.reason == b.reason
     and a.data == b.data;
}

inline bool
operator!=(const Packet_in& a, const Packet_in& b) { return !(a == b); }

inline std::size_t
bytes(const Packet_in& p) { return 10 + bytes(p.data); }

inline Error_condition
is_valid(const Packet_in::Reason r) { 
  return ok(r <= Packet_in::ACTION, BAD_PACKET_IN_REASON); 
}

inline Error_condition
is_valid(const Packet_in& p) { return is_valid(p.reason); }

// -------------------------------------------------------------------------- //
// Flow Removed

inline bool 
operator==(const Flow_removed& a, const Flow_removed& b) {
  return a.match == b.match
     and a.cookie == b.cookie
     and a.priority == b.priority
     and a.reason == b.reason
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec
     and a.idle_timeout == b.idle_timeout
     and a.packet_count == b.packet_count
     and a.byte_count == b.byte_count;
}

inline bool 
operator!=(const Flow_removed& a, const Flow_removed& b) {
  return !(a == b);
}

inline std::size_t 
bytes(const Flow_removed& fr) { return bytes(fr.match) + 40; }

inline Error_condition
is_valid(Flow_removed::Reason r) { 
  return ok(r <= Flow_removed::DELETE, BAD_FLOW_REMOVED_REASON);
}

inline Error_condition
is_valid(const Flow_removed& f) { 
  if (Error_decl err = is_valid(f.match))
    return err;
  if (Error_decl err = is_valid(f.reason))
    return err; 
  return SUCCESS;
}


// -------------------------------------------------------------------------- //
// Port Status

inline bool 
operator==(const Port_status& a, const Port_status& b) {
  return a.reason == b.reason and a.port == b.port;
}

inline bool
operator!=(const Port_status& a, const Port_status& b) { return !(a == b); }

inline std::size_t 
bytes(const Port_status& ps) { return 8 + bytes(ps.port); }

inline Error_condition
is_valid(Port_status::Reason r) { 
  return ok(r <= Port_status::MODIFY, BAD_PORT_STATUS_REASON); 
}

inline Error_condition
is_valid(const Port_status& p) { 
  if (Error_decl err = is_valid(p.reason))
    return err;
  if (Error_decl err = is_valid(p.port))
    return err;
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Packet Out

/// Initialize the Packet_out message with the buffer id of the packet
/// in the switch, the ingress port for flowtable lookup, and a sequence
/// of actions for the packet.
inline
Packet_out::Packet_out(uint32_t buf, 
                       Port::Id port, 
                       std::initializer_list<Action> list)
  : buffer_id(buf), in_port(port), actions(list)
{
  actions_len = bytes(actions);
}

/// Initialize the Packet_out message with packet data, the ingress port
/// for flowtable lookup, and a sequence of actions for the packet.
inline
Packet_out::Packet_out(Greedy_buffer pkt, 
                       Port::Id port, 
                       std::initializer_list<Action> list)
  : buffer_id(-1), in_port(port), actions(list), data(pkt)
{
  actions_len = bytes(actions);
}

inline bool 
operator==(const Packet_out& a, const Packet_out& b) {
  return a.buffer_id == b.buffer_id
     and a.in_port == b.in_port
     and a.actions_len == b.actions_len
     and a.actions == b.actions
     and a.data == b.data;
}

inline bool
operator!=(const Packet_out& a, const Packet_out& b) { return !(a == b); }

inline std::size_t 
bytes(const Packet_out& po) { return 8 + bytes(po.actions) + bytes(po.data); }

inline Error_condition
is_valid(const Packet_out& p) { return is_valid(p.actions); }

// -------------------------------------------------------------------------- //
// Flow_mod

inline bool 
operator==(const Flow_mod& a, const Flow_mod& b) {
  return a.match == b.match 
     and a.cookie == b.cookie 
     and a.command == b.command 
     and a.idle_timeout == b.idle_timeout 
     and a.hard_timeout == b.hard_timeout 
     and a.priority == b.priority 
     and a.buffer_id == b.buffer_id 
     and a.out_port == b.out_port 
     and a.flags == b.flags
     and a.actions == b.actions;
}

inline bool
operator!=(const Flow_mod& a, const Flow_mod& b) { return !(a == b); }

inline std::size_t 
bytes(const Flow_mod& fm) { 
  return bytes(fm.match) + 24 + bytes(fm.actions); 
}

inline Error_condition
is_valid(const Flow_mod::Command t) { 
  return ok(t <= Flow_mod::DELETE_STRICT, BAD_FLOW_MOD_COMMAND); 
}

constexpr Error_condition
is_valid(const Flow_mod::Flags t) { return SUCCESS; }

inline Error_condition
is_valid(const Flow_mod& fm)
{
  Error_condition err;
  if (not (err = is_valid(fm.match)))
    return err;
  if (not (err = is_valid(fm.command)))
    return err;
  if (not (err = is_valid(fm.flags)))
    return err;
  if (not (err = is_valid(fm.actions)))
    return err;
  return SUCCESS;
}



// -------------------------------------------------------------------------- //
// Stats_req_flow_base

template<>
  struct stats_available_error<STATS_REQ, STATS_FLOW> {
    static constexpr Error_code value = AVAILABLE_STATS_REQ_FLOW;
  };

template<>
  struct stats_available_error<STATS_REQ, STATS_AGGREGATE> {
    static constexpr Error_code value = AVAILABLE_STATS_REQ_FLOW;
  };

template<Stats_type K>
  inline bool
  operator==(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b) {
    return a.match == b.match 
       and a.table_id == b.table_id 
       and a.out_port == b.out_port;
  }

template<Stats_type K>
  inline bool
  operator!=(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b) {
    return !(a == b);
  }

template<Stats_type K>
  inline std::size_t
  bytes(const Stats_req_flow_base<K>& f) { return bytes(f.match) + 4; }

template<Stats_type K>
  inline Error_condition
  is_valid(const Stats_req_flow_base<K>& f) { return is_valid(f.match); }

template<Stats_type K>
  inline Error_condition 
  to_buffer(Buffer_view& v, const Stats_req_flow_base<K>& f) {
    if (not available(v, bytes(f)))
      return stats_available_error<STATS_REQ, K>::value;
    to_buffer(v, f.match);
    to_buffer(v, f.table_id);
    pad(v, 1);
    to_buffer(v, f.out_port);
    return SUCCESS;
  }

template<Stats_type K>
  inline Error_condition 
  from_buffer(Buffer_view& v, Stats_req_flow_base<K>& f) {
    if (not available(v, bytes(f)))
      return stats_available_error<STATS_REQ, K>::value;
    from_buffer(v, f.match);
    from_buffer(v, f.table_id);
    pad(v, 1);
    from_buffer(v, f.out_port);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Stats_req_payload

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_desc::Tag, Args&&... args) {
    new (&p.data.desc) Stats_req_desc(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_flow::Tag, Args&&... args) {
    new (&p.data.flow) Stats_req_flow(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_aggregate::Tag, Args&&... args) {
    new (&p.data.aggr) Stats_req_aggregate(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_table::Tag, Args&&... args) {
    new (&p.data.table) Stats_req_table(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_port::Tag, Args&&... args) {
    new (&p.data.port) Stats_req_port(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_queue::Tag, Args&&... args) {
    new (&p.data.queue) Stats_req_queue(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_vendor::Tag, Args&&... args) {
    new (&p.data.vendor) Stats_req_vendor(std::forward<Args>(args)...); 
  }



// -------------------------------------------------------------------------- //
// Payload

template<typename... Args>
  inline void
  construct(Payload& p, Hello::Tag, Args&&... args) {
    new (&p.data.hello) Hello(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Error::Tag, Args&&... args) {
    new (&p.data.error) Error(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Echo_req::Tag, Args&&... args) {
    new (&p.data.echo_req) Echo_req(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Echo_res::Tag, Args&&... args) {
    new (&p.data.echo_res) Echo_res(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Vendor::Tag, Args&&... args) {
    new (&p.data.vendor) Vendor(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Feature_req::Tag, Args&&... args) {
    new (&p.data.feature_req) Feature_req(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Feature_res::Tag, Args&&... args) {
    new (&p.data.feature_res) Feature_res(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Get_config_req::Tag, Args&&... args) {
    new (&p.data.get_config_req) Get_config_req(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Get_config_res::Tag, Args&&... args) {
    new (&p.data.get_config_res) Get_config_res(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Set_config::Tag, Args&&... args) {
    new (&p.data.set_config) Set_config(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Packet_in::Tag, Args&&... args) {
    new (&p.data.packet_in) Packet_in(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Flow_removed::Tag, Args&&... args) {
    new (&p.data.flow_removed) Flow_removed(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Port_status::Tag, Args&&... args) {
    new (&p.data.port_status) Port_status(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Packet_out::Tag, Args&&... args) {
    new (&p.data.packet_out) Packet_out(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Flow_mod::Tag, Args&&... args) {
    new (&p.data.flow_mod) Flow_mod(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Port_mod::Tag, Args&&... args) {
    new (&p.data.port_mod) Port_mod(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Stats_req::Tag, Args&&... args) {
    new (&p.data.stats_req) Stats_req(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Stats_res::Tag, Args&&... args) {
    new (&p.data.stats_res) Stats_res(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Barrier_req::Tag, Args&&... args) {
    new (&p.data.barrier_req) Barrier_req(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Barrier_res::Tag, Args&&... args) {
    new (&p.data.barrier_res) Barrier_res(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Queue_get_config_req::Tag, Args&&... args) {
    new (&p.data.queue_get_config_req) Queue_get_config_req(std::forward<Args>(args)...);
    p.init = true;
  }

template<typename... Args>
  inline void
  construct(Payload& p, Queue_get_config_res::Tag, Args&&... args) {
    new (&p.data.queue_get_config_res) Queue_get_config_res(std::forward<Args>(args)...);
    p.init = true;
  }

// -------------------------------------------------------------------------- //
// Header

inline bool
operator==(const Header& a, const Header& b) {
  return a.xid == b.xid
     and a.version == b.version
     and a.type == b.type
     and a.length == b.length;
}

inline bool
operator!=(const Header& a, const Header& b) {
  return !(a == b);
}

// Bytes
constexpr std::size_t
bytes(const Header&) { return 8; }

// is_valid
inline Error_condition
is_valid(const Header& h) { return is_valid(h.type); }

// -------------------------------------------------------------------------- //
// Message

inline
Message::Message(Message&& x) 
  : header(std::move(x.header)) {
  construct(payload, std::move(x.payload), header.type);
}

inline Message&
Message::operator=(Message&& x) {
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Message::Message(const Message& x)
  : header(x.header) {
  construct(payload, x.payload, header.type);
}

inline Message&
Message::operator=(const Message& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

template<typename T, typename Tag>
  Message::Message(T&& p)
    : header(std::forward<T>(p)) {
    construct(payload, Tag(), std::forward<T>(p));
  }

template<typename T, typename Tag>
  Message::Message(T&& p, uint32_t id)
    : header(std::forward<T>(p), id) { 
      construct(payload, Tag(), std::forward<T>(p)); 
    }

template<typename Tag, typename... Args>
  Message::Message(uint32_t id, Tag t, Args&&... args)
    : header(t.value) {
      construct(payload, t, std::forward<Args>(args)...);
      header.xid = id;
    }

inline
Message::~Message() {
  destroy(payload, header.type);
}

// Equality comparable
inline bool 
operator==(const Message& a, const Message& b) {
  return a.header == b.header 
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool 
operator!=(const Message& a, const Message& b) { return !(a == b); }

inline std::size_t
bytes(const Message& m) {
  return bytes(m.header) + bytes(m.payload, m.header.type);
}

inline Error_condition
is_valid(const Message& m) { return is_valid(m.payload, m.header.type); }

} // namespace v1_0
} // namespace ofp
} // namespace flog

#endif
