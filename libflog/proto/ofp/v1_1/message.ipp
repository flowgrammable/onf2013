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


#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_1_IPP
#define FLOWGRAMMABLE_PROTO_OFP_V1_1_IPP

namespace flog {
namespace ofp {
namespace v1_1 {

// A helper facility for mapping various enumeration values with availability
// error codes. Specializations can be found throughout this file.
template<typename T, T K> struct available_error;

// Another helper facility for doing the same with status features.
template<Message_type M, Stats_type S> struct stats_available_error;

// -------------------------------------------------------------------------- //
// Match

inline bool
operator==(const Match& a, const Match& b) {
  return a.type == b.type
     and a.length == b.length
     and a.in_port == b.in_port
     and a.wildcards == b.wildcards
     and a.dl_src == b.dl_src
     and a.dl_src_mask == b.dl_src_mask
     and a.dl_dst == b.dl_dst
     and a.dl_dst_mask == b.dl_dst_mask
     and a.dl_vlan == b.dl_vlan
     and a.dl_pcp == b.dl_pcp
     and a.dl_type == b.dl_type
     and a.nw_tos == b.nw_tos
     and a.nw_proto == b.nw_proto
     and a.nw_src == b.nw_src
     and a.nw_src_mask == b.nw_src_mask
     and a.nw_dst == b.nw_dst
     and a.nw_dst_mask == b.nw_dst_mask
     and a.tp_src == b.tp_src
     and a.tp_dst == b.tp_dst
     and a.mpls_label == b.mpls_label
     and a.mpls_tc == b.mpls_tc
     and a.metadata == b.metadata
     and a.metadata_mask == b.metadata_mask;
}

inline bool
operator!=(const Match& a, const Match& b) { return !(a == b); }

constexpr std::size_t
bytes(const Match&) { return 88; }

inline Error_condition
is_valid(const Match::Wildcards w) { return SUCCESS; }

inline Error_condition
is_valid(const Match& m) { return is_valid(m.wildcards); }

constexpr bool
wildcard_in_port(Match::Wildcards wt) { return wt & Match::IN_PORT; }

constexpr bool
wildcard_dl_vlan(Match::Wildcards wt) { return wt & Match::DL_VLAN; }

constexpr bool
wildcard_dl_pcp(Match::Wildcards wt) { return wt & Match::DL_PCP; }

constexpr bool
wildcard_dl_type(Match::Wildcards wt) { return wt & Match::DL_TYPE; }

constexpr bool
wildcard_nw_tos(Match::Wildcards wt) { return wt & Match::NW_TOS; }

constexpr bool
wildcard_nw_proto(Match::Wildcards wt) { return wt & Match::NW_PROTO; }

constexpr bool
wildcard_tp_src(Match::Wildcards wt) { return wt & Match::TP_SRC; }

constexpr bool
wildcard_tp_dst(Match::Wildcards wt) { return wt & Match::TP_DST; }

constexpr bool
wildcard_mpls_label(Match::Wildcards wt) { return wt & Match::MPLS_LABEL; }

constexpr bool
wildcard_mpls_tc(Match::Wildcards wt) { return wt & Match::MPLS_TC; }

// -------------------------------------------------------------------------- //
// Action Type

inline Error_condition
is_valid(const Action_type at) {
  return ok((ACTION_OUTPUT <= at and at <= ACTION_DEC_NW_TTL)
      or at == ACTION_EXPERIMENTER, BAD_ACTION);
}

// -------------------------------------------------------------------------- //
// Action: Output

inline bool
operator==(const Action_output& a, const Action_output& b) {
  return a.port == b.port and b.max_len == b.max_len;
}

inline bool
operator!=(const Action_output& a, const Action_output& b) { return !(a == b); }

constexpr std::size_t
bytes(const Action_output&) { return 12; }

constexpr Error_condition
is_valid(const Action_output&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Vlan VID

inline bool
operator==(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b) {
  return a.vlan_vid == b.vlan_vid;
}

inline bool
operator!=(const Action_set_vlan_vid& a, const Action_set_vlan_vid& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_set_vlan_vid&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_vlan_vid&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Vlan PCP

inline bool
operator==(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b) {
  return a.vlan_pcp == b.vlan_pcp;
}

inline bool
operator!=(const Action_set_vlan_pcp& a, const Action_set_vlan_pcp& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_set_vlan_pcp&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_vlan_pcp&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Dl Addr

template<>
  struct available_error<Action_type, ACTION_SET_DL_SRC> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_DL_SRC;
  };

template<>
  struct available_error<Action_type, ACTION_SET_DL_DST> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_DL_DST;
  };

template<Action_type K>
  inline bool
  operator==(const Action_dl_addr<K>& a, const Action_dl_addr<K>& b) {
    return a.dl_addr == b.dl_addr;
  }

template<Action_type K>
  inline bool
  operator!=(const Action_dl_addr<K>& a, const Action_dl_addr<K>& b) {
    return !(a == b);
  }

template<Action_type K>
  constexpr std::size_t
  bytes(const Action_dl_addr<K>&) { return 12; }

template<Action_type K>
  constexpr Error_condition
  is_valid(const Action_dl_addr<K>&) { return SUCCESS; }

template<Action_type K>
  Error_condition to_buffer(Buffer_view& v, const Action_dl_addr<K>& da)
  {
    if (not available(v, bytes(da)))
      return available_error<Action_type, K>::value;

    to_buffer(v, da.dl_addr);
    pad(v, 6);
    return SUCCESS;
  }

template<Action_type K>
  Error_condition from_buffer(Buffer_view& v, Action_dl_addr<K>& da)
  {
    if (not available(v, bytes(da)))
      return available_error<Action_type, K>::value;

    from_buffer(v, da.dl_addr);
    pad(v, 6);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Action: Nw Addr

template<>
  struct available_error<Action_type, ACTION_SET_NW_SRC> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_NW_SRC;
  };

template<>
  struct available_error<Action_type, ACTION_SET_NW_DST> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_NW_DST;
  };

template <Action_type K>
  inline bool
  operator==(const Action_nw_addr<K>& a, const Action_nw_addr<K>& b) {
    return a.nw_addr == b.nw_addr;
  }

template <Action_type K>
  inline bool
  operator!=(const Action_nw_addr<K>& a, const Action_nw_addr<K>& b) {
    return !(a == b);
  }

template <Action_type K>
  constexpr std::size_t
  bytes(const Action_nw_addr<K>&) { return 4; }

template<Action_type K>
  constexpr Error_condition
  is_valid(const Action_nw_addr<K>&) { return SUCCESS; }

template <Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_nw_addr<K>& na)
  {
    if (not available(v, bytes(na)))
      return available_error<Action_type, K>::value;

    to_buffer(v, na.nw_addr);
    return SUCCESS;
  }

template <Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_nw_addr<K>& na)
  {
    if (not available(v, bytes(na)))
      return available_error<Action_type, K>::value;

    from_buffer(v, na.nw_addr);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Action: NW Tos

inline bool
operator==(const Action_set_nw_tos& a, const Action_set_nw_tos& b) {
  return a.nw_tos == b.nw_tos;
}

inline bool
operator!=(const Action_set_nw_tos& a, const Action_set_nw_tos& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_set_nw_tos&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_nw_tos&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: NW Ecn

inline bool
operator==(const Action_set_nw_ecn& a, const Action_set_nw_ecn& b) {
  return a.nw_ecn == b.nw_ecn;
}

inline bool
operator!=(const Action_set_nw_ecn& a, const Action_set_nw_ecn& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_set_nw_ecn&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_nw_ecn&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: TP Addr

template<>
  struct available_error<Action_type, ACTION_SET_TP_SRC> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_TP_SRC;
  };

template<>
  struct available_error<Action_type, ACTION_SET_TP_DST> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_TP_DST;
  };

template <Action_type K>
  inline bool
  operator==(const Action_tp_addr<K>& a, const Action_tp_addr<K>& b) {
    return a.tp_port == b.tp_port;
  }

template <Action_type K>
  inline bool
  operator!=(const Action_tp_addr<K>& a, const Action_tp_addr<K>& b) {
    return !(a == b);
  }

template <Action_type K>
  constexpr std::size_t
  bytes(const Action_tp_addr<K>&) { return 4; }

template<Action_type K>
  constexpr Error_condition
  is_valid(const Action_tp_addr<K>&) { return SUCCESS; }

template <Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_tp_addr<K>& ta)
  {
    if (not available(v, bytes(ta)))
      return available_error<Action_type, K>::value;

    to_buffer(v, ta.tp_port);
    pad(v, 2);
    return SUCCESS;
  }

template <Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_tp_addr<K>& ta)
  {
    if (not available(v, bytes(ta)))
      return available_error<Action_type, K>::value;

    from_buffer(v, ta.tp_port);
    pad(v, 2);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Action: Copy ttl out

constexpr std::size_t
bytes(const Action_copy_ttl_out&) { return 4; }

constexpr Error_condition
is_valid(const Action_copy_ttl_out&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Copy ttl in

constexpr std::size_t
bytes(const Action_copy_ttl_in&) { return 4; }

constexpr Error_condition
is_valid(const Action_copy_ttl_in&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Set MPLS Label

inline bool
operator==(const Action_set_mpls_label& a, const Action_set_mpls_label& b) {
  return a.mpls_label == b.mpls_label;
}

inline bool
operator!=(const Action_set_mpls_label& a, const Action_set_mpls_label& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_set_mpls_label&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_mpls_label&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Set MPLS TC

inline bool
operator==(const Action_set_mpls_tc& a, const Action_set_mpls_tc& b) {
  return a.mpls_tc == b.mpls_tc;
}

inline bool
operator!=(const Action_set_mpls_tc& a, const Action_set_mpls_tc& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_set_mpls_tc&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_mpls_tc&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: MPLS TTL

template<>
  struct available_error<Action_type, ACTION_SET_MPLS_TTL> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_MPLS_TTL;
  };

template<>
  struct available_error<Action_type, ACTION_DEC_MPLS_TTL> {
    static constexpr Error_condition value = AVAILABLE_ACTION_DEC_MPLS_TTL;
  };

template <Action_type K>
  inline bool
  operator==(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b) {
    return a.mpls_ttl == b.mpls_ttl;
  }

template <Action_type K>
  inline bool
  operator!=(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b) {
    return !(a == b);
  }

template <Action_type K>
  constexpr std::size_t
  bytes(const Action_mpls_ttl<K>&) { return 4; }

template<Action_type K>
  constexpr Error_condition
  is_valid(const Action_mpls_ttl<K>&) { return SUCCESS; }

template <Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_mpls_ttl<K>& mt) {
    if (not available(v, bytes(mt)))
      return available_error<Action_type, K>::value;

    to_buffer(v, mt.mpls_ttl);
    pad(v, 3);

    return SUCCESS;
  }

template <Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_mpls_ttl<K>& mt) {
    if (not available(v, bytes(mt)))
      return available_error<Action_type, K>::value;

    from_buffer(v, mt.mpls_ttl);
    pad(v, 3);

    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Action: Push Pop

template<>
  struct available_error<Action_type, ACTION_PUSH_VLAN> {
    static constexpr Error_condition value = AVAILABLE_ACTION_PUSH_VLAN;
  };

template<>
  struct available_error<Action_type, ACTION_POP_VLAN> {
    static constexpr Error_condition value = AVAILABLE_ACTION_POP_VLAN;
  };

template<>
  struct available_error<Action_type, ACTION_PUSH_MPLS> {
    static constexpr Error_condition value = AVAILABLE_ACTION_PUSH_MPLS;
  };

template<>
  struct available_error<Action_type, ACTION_POP_MPLS> {
    static constexpr Error_condition value = AVAILABLE_ACTION_POP_MPLS;
  };

template <Action_type K>
  inline bool
  operator==(const Action_push_pop<K>& a, const Action_push_pop<K>& b) {
    return a.ether_type == b.ether_type;
  }

template <Action_type K>
  inline bool
  operator!=(const Action_push_pop<K>& a, const Action_push_pop<K>& b) {
    return !(a == b);
  }

template <Action_type K>
  constexpr std::size_t
  bytes(const Action_push_pop<K>&) { return 4; }

template<Action_type K>
  inline Error_condition
  is_valid(const Action_push_pop<K>&) { return SUCCESS; }

template <Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_push_pop<K>& pp)
  {
    if (not available(v, bytes(pp)))
      return available_error<Action_type, K>::value;

    to_buffer(v, pp.ether_type);
    pad(v, 2);
    return SUCCESS;
  }

template <Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_push_pop<K>& pp)
  {
    if (not available(v, bytes(pp)))
      return available_error<Action_type, K>::value;

    from_buffer(v, pp.ether_type);
    pad(v, 2);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Action: SetQueue

inline bool
operator==(const Action_set_queue& a, const Action_set_queue& b) {
  return a.queue_id == b.queue_id;
}

inline bool
operator!=(const Action_set_queue& a, const Action_set_queue& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_set_queue&) { return 4; }

constexpr Error_condition
is_valid(const Action_set_queue&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Group

inline bool
operator==(const Action_group& a, const Action_group& b) {
  return a.group_id == b.group_id;
}

inline bool
operator!=(const Action_group& a, const Action_group& b) { return !(a == b); }

constexpr std::size_t
bytes(const Action_group&) { return 4; }

constexpr Error_condition
is_valid(const Action_group&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: NW TTL

template<>
  struct available_error<Action_type, ACTION_SET_NW_TTL> {
    static constexpr Error_condition value = AVAILABLE_ACTION_SET_NW_TTL;
  };

template<>
  struct available_error<Action_type, ACTION_DEC_NW_TTL> {
    static constexpr Error_condition value = AVAILABLE_ACTION_DEC_NW_TTL;
  };

template <Action_type K>
  inline bool
  operator==(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b) {
    return a.nw_ttl == b.nw_ttl;
  }

template <Action_type K>
  inline bool
  operator!=(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b) {
    return !(a == b);
  }

template <Action_type K>
  constexpr std::size_t
  bytes(const Action_nw_ttl<K>& nt) { return 4; }

template<Action_type K>
  constexpr Error_condition
  is_valid(const Action_nw_ttl<K>&) { return SUCCESS; }

template <Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_nw_ttl<K>& nt)
  {
    if (not available(v, bytes(nt)))
      return available_error<Action_type, K>::value;

    to_buffer(v, nt.nw_ttl);
    pad(v, 3);

    return SUCCESS;
  }

template <Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_nw_ttl<K>& nt)
  {
    if (not available(v, bytes(nt)))
      return available_error<Action_type, K>::value;

    from_buffer(v, nt.nw_ttl);
    pad(v, 3);

    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Action: Experimenter

inline bool
operator==(const Action_experimenter& a, const Action_experimenter& b) {
  return a.experimenter == b.experimenter;
}

inline bool
operator!=(const Action_experimenter& a, const Action_experimenter& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Action_experimenter&) { return 4; }

constexpr Error_condition
is_valid(const Action_experimenter&) { return SUCCESS; }

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
    new (&p.data.set_vlan_vid) Action_set_vlan_vid(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_vlan_pcp::Tag, Args&&... args) {
    new (&p.data.set_vlan_pcp) Action_set_vlan_pcp(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_dl_src::Tag, Args&&... args) {
    new (&p.data.set_dl_src) Action_set_dl_src(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_dl_dst::Tag, Args&&... args) {
    new (&p.data.set_dl_dst) Action_set_dl_dst(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_src::Tag, Args&&... args) {
    new (&p.data.set_nw_src) Action_set_nw_src(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_dst::Tag, Args&&... args) {
    new (&p.data.set_nw_dst) Action_set_nw_dst(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_tos::Tag, Args&&... args) {
    new (&p.data.set_nw_tos) Action_set_nw_tos(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_ecn::Tag, Args&&... args) {
    new (&p.data.set_nw_ecn) Action_set_nw_ecn(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_tp_src::Tag, Args&&... args) {
    new (&p.data.set_tp_src) Action_set_tp_src(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_tp_dst::Tag, Args&&... args) {
    new (&p.data.set_tp_dst) Action_set_tp_dst(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_copy_ttl_out::Tag, Args&&... args) {
    new (&p.data.copy_ttl_out) Action_copy_ttl_out(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_copy_ttl_in::Tag, Args&&... args) {
    new (&p.data.copy_ttl_in) Action_copy_ttl_in(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_mpls_label::Tag, Args&&... args) {
    new (&p.data.set_mpls_label) Action_set_mpls_label(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_mpls_tc::Tag, Args&&... args) {
    new (&p.data.set_mpls_tc) Action_set_mpls_tc(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_mpls_ttl::Tag, Args&&... args) {
    new (&p.data.set_mpls_ttl) Action_set_mpls_ttl(std::forward<Args>(args)...);
  }

/*
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_dec_mpls_ttl::Tag, Args&&... args) {
    new (&p.data.dec_mpls_ttl) Action_dec_mpls_ttl(std::forward<Args>(args)...);
  }
*/

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_push_vlan::Tag, Args&&... args) {
    new (&p.data.push_vlan) Action_push_vlan(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_pop_vlan::Tag, Args&&... args) {
    new (&p.data.pop_vlan) Action_pop_vlan(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_push_mpls::Tag, Args&&... args) {
    new (&p.data.push_mpls) Action_push_mpls(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_pop_mpls::Tag, Args&&... args) {
    new (&p.data.pop_mpls) Action_pop_mpls(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_queue::Tag, Args&&... args) {
    new (&p.data.set_queue) Action_set_queue(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_group::Tag, Args&&... args) {
    new (&p.data.group) Action_group(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_set_nw_ttl::Tag, Args&&... args) {
    new (&p.data.set_nw_ttl) Action_set_nw_ttl(std::forward<Args>(args)...);
  }
/*
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_dec_nw_ttl::Tag, Args&&... args) {
    new (&p.data.dec_nw_ttl) Action_dec_nw_ttl(std::forward<Args>(args)...);
  }
*/
template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Action_experimenter(std::forward<Args>(args)...);
  }


// -------------------------------------------------------------------------- //
// Action_header

inline bool
operator==(const Action_header& a, const Action_header& b) {
  return a.type == b.type and a.length == b.length;
}

inline bool
operator!=(const Action_header& a, const Action_header& b) { return !(a == b); }

constexpr std::size_t
bytes(const Action_header&) { return 4; }

inline Error_condition
is_valid(const Action_header& h) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action

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
// Instruction type

inline Error_condition
is_valid(const Instruction_type it) {
  return ok(it <= INSTRUCTION_CLEAR_ACTIONS or it == INSTRUCTION_EXPERIMENTER,
            BAD_INSTRUCTION);
}

// -------------------------------------------------------------------------- //
// Instruction: Goto table

inline bool
operator==(const Instruction_goto_table& a, const Instruction_goto_table& b) {
  return a.table_id == b.table_id;
}

inline bool
operator!=(const Instruction_goto_table& a, const Instruction_goto_table& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Instruction_goto_table&) { return 4; }

inline Error_condition
is_valid(const Instruction_goto_table&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Instruction: Goto write metadata

inline bool
operator==(const Instruction_write_metadata& a,
           const Instruction_write_metadata& b) {
  return a.metadata == b.metadata and a.metadata_mask == b.metadata_mask;
}

inline bool
operator!=(const Instruction_write_metadata& a,
           const Instruction_write_metadata& b) { return !(a == b); }

constexpr std::size_t
bytes(const Instruction_write_metadata&) { return 20; }

inline Error_condition
is_valid(const Instruction_write_metadata&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Instruction: Action

template<>
  struct available_error<Instruction_type, INSTRUCTION_WRITE_ACTIONS> {
    static constexpr Error_condition value = AVAILABLE_INSTRUCTION_WRITE_ACTIONS;
  };

template<>
  struct available_error<Instruction_type, INSTRUCTION_APPLY_ACTIONS> {
    static constexpr Error_condition value = AVAILABLE_INSTRUCTION_APPLY_ACTIONS;
  };

template<>
  struct available_error<Instruction_type, INSTRUCTION_CLEAR_ACTIONS> {
    static constexpr Error_condition value = AVAILABLE_INSTRUCTION_CLEAR_ACTIONS;
  };

template <Instruction_type K>
  inline bool
  operator==(const Instruction_action<K>& a, const Instruction_action<K>& b) {
    return a.actions == b.actions;
  }

template <Instruction_type K>
  inline bool
  operator!=(const Instruction_action<K>& a, const Instruction_action<K>& b) {
    return !(a == b);
  }

template <Instruction_type K>
  std::size_t bytes(const Instruction_action<K>& ia) {
    return 4 + bytes(ia.actions);
  }

template<Instruction_type K>
  constexpr Error_condition
  is_valid(const Instruction_action<K>&) { return SUCCESS; }

template <Instruction_type K>
  Error_condition to_buffer(Buffer_view& v, const Instruction_action<K>& ia)
  {
    if (not available(v, bytes(ia)))
      return available_error<Instruction_type, K>::value;

    pad(v, 4);
    return to_buffer(v, ia.actions);
  }

template <Instruction_type K>
  Error_condition from_buffer(Buffer_view& v, Instruction_action<K>& ia)
  {
    if (not available(v, bytes(ia)))
      return available_error<Instruction_type, K>::value;

    pad(v, 4);
    return from_buffer(v, ia.actions);
  }

// -------------------------------------------------------------------------- //
// Instruction: Experimenter

inline bool
operator==(const Instruction_experimenter& a,
           const Instruction_experimenter& b) {
  return a.experimenter_id == b.experimenter_id;
}

inline bool
operator!=(const Instruction_experimenter& a,
           const Instruction_experimenter& b) { return !(a == b); }

constexpr std::size_t
bytes(const Instruction_experimenter&) { return 4; }

inline Error_condition
is_valid(const Instruction_experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Instruction payload

template<typename... Args>
  inline void 
  construct(Instruction_payload& p, Instruction_goto_table::Tag, Args&&... args) {
    new (&p.data.goto_table) Instruction_goto_table(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Instruction_payload& p, Instruction_write_metadata::Tag, Args&&... args) {
    new (&p.data.write_metadata) Instruction_write_metadata(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Instruction_payload& p, Instruction_write_actions::Tag, Args&&... args) {
    new (&p.data.write_actions) Instruction_write_actions(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Instruction_payload& p, Instruction_apply_actions::Tag, Args&&... args) {
    new (&p.data.apply_actions) Instruction_apply_actions(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Instruction_payload& p, Instruction_clear_actions::Tag, Args&&... args) {
    new (&p.data.clear_actions) Instruction_clear_actions(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Instruction_payload& p, Instruction_experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Instruction_experimenter(std::forward<Args>(args)...);
  }


// -------------------------------------------------------------------------- //
// Instruction header

inline bool
operator==(const Instruction_header& a, const Instruction_header& b) {
  return a.type == b.type and a.length == b.length;
}

inline bool
operator!=(const Instruction_header& a, const Instruction_header& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Instruction_header&) { return 4; }

inline Error_condition
is_valid(const Instruction_header& h) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Instruction

inline
Instruction::~Instruction() {
  destroy(payload, header.type);
}

inline
Instruction::Instruction(Instruction&& x)
  : header(std::move(x.header)) {
  construct(payload, std::move(x.payload), header.type);
}

inline Instruction&
Instruction::operator=(Instruction&& x) {
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Instruction::Instruction(const Instruction& x)
  : header(x.header) {
  construct(payload, x.payload, header.type);
}

inline Instruction&
Instruction::operator=(const Instruction& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

template<typename T, typename Tag>
  Instruction::Instruction(T&& x) 
    : header(x) { construct(payload, Tag(), std::forward<T>(x)); }

template<typename Tag, typename... Args>
  inline
  Instruction::Instruction(Tag t, Args&&... args)
  : header(t.value) { 
    construct(payload, t, std::forward<Args>(args)...);
    header.length = bytes(*this);
  }

inline bool
operator==(const Instruction& a, const Instruction& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Instruction& a, const Instruction& b) { return !(a == b); }

inline std::size_t
bytes(const Instruction& a) {
  return bytes(a.header) + bytes(a.payload, a.header.type);
}

inline Error_condition
is_valid(const Instruction& a) { return is_valid(a.payload, a.header.type); }

inline Error_condition
is_valid(const Sequence<Instruction> i) {
  for (auto iter = i.begin(); iter != i.end(); iter++)
  {
    if(Error_decl err = is_valid(*iter))
      return err;
  }

  uint8_t flag = 0;
 
  for (auto iter = i.begin(); iter != i.end(); iter++)
  {
    Instruction_type t = iter->header.type;
    if (t != Instruction_type::INSTRUCTION_EXPERIMENTER)
    {
      if ((flag & (1 << t)) != 0)
        return FAILURE;
      flag |= (1 << t);
    }
    else
    {
      if ((flag & 0x40) != 0)
        return FAILURE;
      flag |= 0x40;
    }
  }
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Port

inline bool
operator==(const Port& a, const Port& b) {
  return a.port_id == b.port_id
     and a.hw_addr == b.hw_addr
     and a.name == b.name
     and a.config == b.config
     and a.state == b.state
     and a.current == b.current
     and a.advertised == b.advertised
     and a.supported == b.supported
     and a.peer == b.peer
     and a.curr_speed == b.curr_speed
     and a.max_speed == b.max_speed;
}

inline bool
operator!=(const Port& a, const Port& b) { return !(a == b); }

constexpr std::size_t
bytes(const Port&) { return 64; }

inline Error_condition
is_valid(const Port::Id id) {
  return ok(id <= 0xffffff00 or id >= 0xfffffff8, BAD_PORT_ID);
}

inline Error_condition
is_valid(const Port::Config) { return SUCCESS; }

inline Error_condition
is_valid(const Port::State) { return SUCCESS; }

inline Error_condition
is_valid(const Port::Features) { return SUCCESS; }

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
  return is_valid(p.peer);
}

constexpr bool
port_config_port_down(uint32_t c) { return c & Port::PORT_DOWN; }

constexpr bool
port_config_no_recv(uint32_t c) { return c & Port::NO_RECV; }

constexpr bool
port_config_no_fwd(uint32_t c) { return c & Port::NO_FWD; }

constexpr bool
port_config_no_packet_in(uint32_t c) { return c & Port::NO_PACKET_IN; }

constexpr bool
port_state_blocked(uint32_t s) { return s & Port::BLOCKED; }

constexpr bool
port_state_live(uint32_t s) { return s & Port::LIVE; }

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
port_any(uint16_t p) { return p & Port::ANY; }

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
port_feature_40gb_fd(uint32_t p) { return p & Port::FORTY_GB_FD; }

constexpr bool
port_feature_100gb_fd(uint32_t p) { return p & Port::HUNDRED_GB_FD; }

constexpr bool
port_feature_1tb_fd(uint32_t p) { return p & Port::ONE_TB_FD; }

constexpr bool
port_feature_other(uint32_t p) { return p & Port::OTHER; }

constexpr bool
port_feature_copper(uint32_t p) { return p & Port::COPPER; }

constexpr bool
port_feature_fiber(uint32_t p) { return p & Port::FIBER; }

constexpr bool
port_feature_auto_neg(uint32_t p) { return p & Port::AUTO_NEG; }

constexpr bool
port_feature_pause(uint32_t p) { return p & Port::PAUSE; }

// -------------------------------------------------------------------------- //
// Queue property type

constexpr Error_condition
is_valid(const Queue_property_type t) {
  return ok(t == QUEUE_PROPERTY_NONE
      or t == QUEUE_PROPERTY_MIN_RATE,BAD_QUEUE_PROPERTY);
}

// -------------------------------------------------------------------------- //
// Queue property: Min rate

inline bool
operator==(const Queue_property_min_rate& a, const Queue_property_min_rate& b) {
  return a.rate == b.rate;
}

inline bool
operator!=(const Queue_property_min_rate& a, const Queue_property_min_rate& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Queue_property_min_rate&) { return 8; }

constexpr Error_condition
is_valid(const Queue_property_min_rate&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Queue property header

template<typename T>
  inline
  Queue_property_header::Queue_property_header(const T& value)
    : property(T::kind), length(8 + bytes(value)) { }

inline bool
operator==(const Queue_property_header& a, const Queue_property_header& b) {
  return a.property == b.property and a.length == b.length;
}

inline bool
operator!=(const Queue_property_header& a, const Queue_property_header& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Queue_property_header&) { return 8; }

inline Error_condition
is_valid(const Queue_property_header& h) {
  if (Error_decl err = is_valid(h.property))
    return err;
  return ok(bytes(h) <= h.length,BAD_QUEUE_PROPERTY_LENGTH);
}

// -------------------------------------------------------------------------- //
// Queue property

inline
Queue_property::Queue_property(const Queue_property& x)
  : header(x.header) {
  construct(payload, x.payload, header.property);
}

inline Queue_property&
Queue_property::operator=(const Queue_property& x) {
  header = x.header;
  assign(payload, x.payload, x.header.property);
  return *this;
}

inline bool
operator==(const Queue_property& a, const Queue_property& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.property, b.header.property);
}

inline bool
operator!=(const Queue_property& a, const Queue_property& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Queue_property& p) {
  return bytes(p.header) + bytes(p.payload, p.header.property);
}

inline Error_condition
is_valid(const Queue_property& p) {
  if (Error_decl err = is_valid(p.header))
    return err;
  return is_valid(p.payload, p.header.property);
}

// -------------------------------------------------------------------------- //
// Queue

inline bool
operator==(const Queue& a, const Queue& b) {
  return a.queue_id == b.queue_id
     and a.length == b.length
     and a.properties == b.properties;
}

inline bool
operator!=(const Queue& a, const Queue& b) { return !(a == b); }

inline std::size_t
bytes(const Queue& q) { return 8 + bytes(q.properties); }

inline Error_condition
is_valid(const Queue& q) { return is_valid(q.properties); }

// -------------------------------------------------------------------------- //
// Bucket

inline bool
operator==(const Bucket& a, const Bucket& b) {
  return a.len == b.len
     and a.weight == b.weight
     and a.watch_port == b.watch_port
     and a.watch_group == b.watch_group
     and a.actions == b.actions;
}

inline bool
operator!=(const Bucket& a, const Bucket& b) { return !(a == b); }

inline std::size_t
bytes(const Bucket& b) { return 16 + bytes(b.actions); }

inline Error_condition
is_valid(const Bucket& b) { return is_valid(b.actions); }

// -------------------------------------------------------------------------- //
// Version Type

inline Error_condition
is_valid(const Version_type v) { return ok(v == VERSION, BAD_VERSION); }

// -------------------------------------------------------------------------- //
// Message Type

inline Error_condition
is_valid(const Message_type t) {
  return ok(t <= QUEUE_GET_CONFIG_RES, BAD_MESSAGE);
}

// -------------------------------------------------------------------------- //
// Hello

inline bool
operator==(const Hello& a, const Hello& b) {
  return a.data == b.data;
}

inline bool
operator!=(const Hello& a, const Hello& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Hello& h) { return bytes(h.data); }

constexpr Error_condition
is_valid(const Hello& h) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Error

inline bool
operator==(const Error& a, const Error& b) {
  return a.type == b.type
     and a.code.value == b.code.value
     and a.data == b.data;
}

inline bool
operator!=(const Error& a, const Error& b) { return !(a == b); }

inline std::size_t
bytes(const Error& e) { return 4 + bytes(e.data); }

inline Error_condition
is_valid(const Error::Type t) {
  return ok(t <= Error::SWITCH_CONFIG_FAILED, BAD_ERROR_TYPE);
}

inline Error_condition
is_valid(const Error::Hello_failed c) {
  return ok(c <= Error::HF_EPERM, BAD_HELLO_FAILED);
}

inline Error_condition
is_valid(const Error::Bad_request c) {
  return ok(c <= Error::BR_BAD_TABLE_ID, BAD_BAD_REQUEST);
}

inline Error_condition
is_valid(const Error::Bad_action c) {
  return ok(c <= Error::BA_BAD_TAG, BAD_BAD_ACTION); 
}

inline Error_condition
is_valid(const Error::Bad_instruction c) {
  return ok(c <= Error::BI_UNSUP_EXP_LIST, BAD_BAD_INSTRUCTION);
}

inline Error_condition
is_valid(const Error::Bad_match c) {
  return ok(c <= Error::BM_BAD_VALUE, BAD_BAD_MATCH);
}

inline Error_condition
is_valid(const Error::Flow_mod_failed c) {
  return ok(c <= Error::FMF_BAD_COMMAND, BAD_FLOW_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Group_mod_failed c) {
  return ok(c <= Error::GMF_UNKNOWN_GROUP, BAD_GROUP_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Port_mod_failed c) {
  return ok(c <= Error::PMF_BAD_ADVERTISE, BAD_PORT_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Table_mod_failed c) {
  return ok(c <= Error::TMF_BAD_CONFIG, BAD_TABLE_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Queue_op_failed c) {
  return ok(c <= Error::QOF_EPERM, BAD_QUEUE_OP_FAILED);
}

inline Error_condition
is_valid(const Error::Switch_config_failed c) {
  return ok(c <= Error::SCF_BAD_LEN, BAD_SWITCH_CONFIG_FAILED);
}

inline Error_condition
is_valid(const Error::Type t, const Error::Code c) {
  switch(t) {
  case Error::HELLO_FAILED: return is_valid(c.hf);
  case Error::BAD_REQUEST: return is_valid(c.br);
  case Error::BAD_ACTION: return is_valid(c.ba);
  case Error::BAD_INSTRUCTION: return is_valid(c.bi);
  case Error::BAD_MATCH: return is_valid(c.bm);
  case Error::FLOW_MOD_FAILED: return is_valid(c.fmf);
  case Error::GROUP_MOD_FAILED: return is_valid(c.gmf);
  case Error::PORT_MOD_FAILED: return is_valid(c.pmf);
  case Error::TABLE_MOD_FAILED: return is_valid(c.tmf);
  case Error::QUEUE_OP_FAILED: return is_valid(c.qof);
  case Error::SWITCH_CONFIG_FAILED: return is_valid(c.scf);
  default: return BAD_ERROR_TYPE;
  };
}

inline Error_condition
is_valid(const Error& e) { return is_valid(e.type, e.code); }

// -------------------------------------------------------------------------- //
// Echo Base

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
    return to_buffer(v, e.data);
  }

template<Message_type K>
  inline Error_condition
  from_buffer(Buffer_view& v, Echo_base<K>& e) {
    return from_buffer(v, e.data);
  }

template<Message_type K>
  inline std::string
  to_string(const Echo_base<K>& e, Formatter& f) {
    return to_string(e.data, f);
  }

// -------------------------------------------------------------------------- //
// Experimenter

inline bool
operator==(const Experimenter& a, const Experimenter& b) {
  return a.experimenter_id == b.experimenter_id and a.data == b.data;
}

inline bool
operator!=(const Experimenter& a, const Experimenter& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Experimenter& e) { return 8 + bytes(e.data); }

constexpr Error_condition
is_valid(const Experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Feature Response

inline bool
operator==(const Feature_res& a, const Feature_res& b) {
  return a.datapath_id == b.datapath_id
     and a.n_buffers == b.n_buffers
     and a.n_tbls == b.n_tbls
     and a.capabilities == b.capabilities
     and a.reserved == b.reserved
     and a.ports == b.ports;
}

inline bool
operator!=(const Feature_res& a, const Feature_res& b) { return !(a == b); }

inline std::size_t
bytes(const Feature_res& fr) { return 24 + bytes(fr.ports); }

inline Error_condition
is_valid(const Feature_res::Capability& c) {
  return SUCCESS;
  //return 0x00000000 == (c & 0x00000010);
}

inline Error_condition
is_valid(const Feature_res& fr) {
  if (Error_decl err = is_valid(fr.capabilities))
    return err;
  return is_valid(fr.ports);
}

inline bool
feature_res_capabilities_flow_stats(uint32_t c) {
  return c & Feature_res::FLOW_STATS;
}

inline bool
feature_res_capabilities_table_stats(uint32_t c) {
  return c & Feature_res::TABLE_STATS;
}

inline bool
feature_res_capabilities_port_stats(uint32_t c) {
  return c & Feature_res::PORT_STATS;
}

inline bool
feature_res_capabilities_group_stats(uint32_t c) {
  return c & Feature_res::GROUP_STATS;
}

inline bool
feature_res_capabilities_ip_reasm(uint32_t c) {
  return c & Feature_res::IP_REASM;
}

inline bool
feature_res_capabilities_queue_stats(uint32_t c) {
  return c & Feature_res::QUEUE_STATS;
}

inline bool
feature_res_capabilities_arp_match_ip(uint32_t c) {
  return c & Feature_res::ARP_MATCH_IP;
}

// -------------------------------------------------------------------------- //
// Config Message Base

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
  operator==(const Config_message_base<T>& a, const Config_message_base<T>& b)
  { return a.flags == b.flags and a.miss_send_len == b.miss_send_len; }

template<Message_type T>
  inline bool
  operator!=(const Config_message_base<T>& a, const Config_message_base<T>& b)
  { return !(a == b); }

// Bytes
template<Message_type T>
  constexpr std::size_t
  bytes(const Config_message_base<T>&) { return 4; }

template<Message_type T>
  inline Error_condition
  is_valid(const Config_message_base<T>& c) {
    return ok(c.flags <= 0x0004,BAD_CONFIG_FLAGS);
  }

template<Message_type T>
  inline Error_condition
  to_buffer(Buffer_view& v, const Config_message_base<T>& m)
  {
    if (not available(v, bytes(m)))
      return available_error<Message_type, T>::value;

    to_buffer(v, m.flags);
    to_buffer(v, m.miss_send_len);

    return SUCCESS;
  }

template<Message_type T>
  inline Error_condition
  from_buffer(Buffer_view& v, Config_message_base<T>& m)
  {
    if (not available(v, bytes(m)))
      return available_error<Message_type, T>::value;

    from_buffer(v, m.flags);
    from_buffer(v, m.miss_send_len);

    return SUCCESS;
  }

template<Message_type T>
  inline bool
  config_frag_normal(typename Config_message_base<T>::Flags ft)
  { return ft & Config_message_base<T>::FRAG_NORMAL; }

template<Message_type T>
  inline bool
  config_frag_drop(typename Config_message_base<T>::Flags ft)
  { return ft & Config_message_base<T>::FRAG_DROP; }

template<Message_type T>
  inline bool
  config_frag_reasm(typename Config_message_base<T>::Flags ft)
  { return ft & Config_message_base<T>::FRAG_REASM; }

template<Message_type T>
  inline bool
  config_invalid_ttl_to_controller(typename Config_message_base<T>::Flags
                                            ft)
  { return ft & Config_message_base<T>::INVALID_TTL_TO_CONTROLLER; }

// -------------------------------------------------------------------------- //
// Packet In

inline bool
operator==(const Packet_in& a, const Packet_in& b) {
  return a.buffer_id == b.buffer_id
     and a.in_port == b.in_port
     and a.in_phy_port == b.in_phy_port
     and a.total_len == b.total_len
     and a.reason == b.reason
     and a.tbl_id == b.tbl_id
     and a.data == b.data;
}

inline bool
operator!=(const Packet_in& a, const Packet_in& b) { return !(a == b); }

inline std::size_t
bytes(const Packet_in& pi) { return 16 + bytes(pi.data); }

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
  return a.cookie == b.cookie
     and a.priority == b.priority
     and a.reason == b.reason
     and a.table_id == b.table_id
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec
     and a.idle_timeout == b.idle_timeout
     and a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.match == b.match;
}

inline bool
operator!=(const Flow_removed& a, const Flow_removed& b) { return !(a == b); }

inline std::size_t
bytes(const Flow_removed& fr) { return bytes(fr.match) + 40; }

inline Error_condition
is_valid(const Flow_removed::Reason r) {
  return ok(r <= Flow_removed::GROUP_DELETE, BAD_FLOW_REMOVED_REASON);
}

inline Error_condition
is_valid(const Flow_removed& f)  {
  if (Error_decl err = is_valid(f.reason))
    return err;
  return is_valid(f.match);
}

// -------------------------------------------------------------------------- //
// Port Status

inline bool
operator==(const Port_status& a, const Port_status& b) {
  return a.reason == b.reason and a.port == b.port;
}

inline bool
operator!=(const Port_status& a, const Port_status& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Port_status& ps) { return 8 + bytes(ps.port); }

inline Error_condition
is_valid(const Port_status::Reason r) {
  return ok(r <= Port_status::MODIFY, BAD_PORT_STATUS_REASON);
}

inline Error_condition
is_valid(const Port_status& p) {
  if (Error_decl err = is_valid(p.reason))
    return err;
  return is_valid(p.port);
}

// -------------------------------------------------------------------------- //
// Packet Out

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
bytes(const Packet_out& po) {
  return 16 + bytes(po.actions) + bytes(po.data);
}

inline Error_condition
is_valid(const Packet_out& p) { return is_valid(p.actions); }

// -------------------------------------------------------------------------- //
// Flow_mod

inline bool
operator==(const Flow_mod& a, const Flow_mod& b) {
  return a.cookie == b.cookie
     and a.cookie_mask == b.cookie_mask
     and a.table_id == b.table_id
     and a.command == b.command
     and a.idle_timeout == b.idle_timeout
     and a.hard_timeout == b.hard_timeout
     and a.priority == b.priority
     and a.buffer_id == b.buffer_id
     and a.out_port == b.out_port
     and a.out_group == b.out_group
     and a.flags == b.flags
     and a.match == b.match
     and a.instructions == b.instructions;
}

inline bool
operator!=(const Flow_mod& a, const Flow_mod& b) { return !(a == b); }

inline std::size_t
bytes(const Flow_mod& fm) {
  return 40 + bytes(fm.match) + bytes(fm.instructions);
}

inline Error_condition
is_valid(const Flow_mod::Command t) {
  return ok(t <= Flow_mod::DELETE_STRICT, BAD_FLOW_MOD_COMMAND); 
}

inline Error_condition
is_valid(const Flow_mod::Flags t) {
  return ok(t <= (Flow_mod::SEND_FLOW_REM | Flow_mod::CHECK_OVERLAP),
            BAD_FLOW_MOD_FLAGS);
}

inline Error_condition
is_valid(const Flow_mod& f) {
  if (Error_decl err = is_valid(f.command))
    return err;
  if (Error_decl err = is_valid(f.flags))
    return err;
  if (Error_decl err = is_valid(f.match))
    return err;
  return is_valid(f.instructions);
}

// -------------------------------------------------------------------------- //
// Group Mod

inline bool
operator==(const Group_mod& a, const Group_mod& b) {
  return a.command == b.command
     and a.type == b.type
     and a.group_id == b.group_id
     and a.buckets == b.buckets;
}

inline bool
operator!=(const Group_mod& a, const Group_mod& b) { return !(a == b); }

inline std::size_t
bytes(const Group_mod& gm) { return 8 + bytes(gm.buckets); }

inline Error_condition
is_valid(const Group_mod::Command c) {
  return ok(c <= Group_mod::DELETE, BAD_GROUP_MOD_COMMAND);
}

inline Error_condition
is_valid(const Group_mod::Type v) {
  return ok(v <= Group_mod::FF, BAD_GROUP_MOD_TYPE);
}

inline Error_condition
is_valid(const Group_mod& gm) {
  if (Error_decl err = is_valid(gm.command))
    return err;
  if (Error_decl err = is_valid(gm.type))
    return err;
  return is_valid(gm.buckets);
}

// -------------------------------------------------------------------------- //
// Port Mod

inline bool
operator==(const Port_mod& a, const Port_mod& b) {
  return a.port == b.port
     and a.hw_addr == b.hw_addr
     and a.config == b.config
     and a.mask == b.mask
     and a.advertise == b.advertise;
}

inline bool
operator!=(const Port_mod& a, const Port_mod& b) {
  return a != b;
}

constexpr std::size_t
bytes(const Port_mod&) { return 32; }

constexpr Error_condition
is_valid(const Port_mod& p) { return SUCCESS; }

inline bool
port_mod_config_port_down(uint32_t c) {
  return c & Port_mod::PORT_DOWN;
}

inline bool
port_mod_config_no_recv(uint32_t c) {
  return c & Port_mod::NO_RECV;
}

inline bool
port_mod_config_no_fwd(uint32_t c) {
  return c & Port_mod::NO_FWD;
}

inline bool
port_mod_config_no_packet_in(uint32_t c) {
  return c & Port_mod::NO_PACKET_IN;
}

inline bool
port_mod_features_10mb_hd(uint32_t f) {
  return f & Port_mod::TEN_MB_HD;
}

inline bool
port_mod_features_10mb_fd(uint32_t f) {
  return f & Port_mod::TEN_MB_FD;
}

inline bool
port_mod_features_100mb_hd(uint32_t f) {
  return f & Port_mod::HUNDRED_MB_HD;
}

inline bool
port_mod_features_100mb_fd(uint32_t f) {
  return f & Port_mod::HUNDRED_MB_FD;
}

inline bool
port_mod_features_1gb_hd(uint32_t f) {
  return f & Port_mod::ONE_GB_HD;
}

inline bool
port_mod_features_1gb_fd(uint32_t f) {
  return f & Port_mod::ONE_GB_FD;
}

inline bool
port_mod_features_10gb_fd(uint32_t f) {
  return f & Port_mod::TEN_GB_FD;
}

inline bool
port_mod_features_40gb_fd(uint32_t f) {
  return f & Port_mod::FOURTY_GB_FD;
}

inline bool
port_mod_features_100gb_fd(uint32_t f) {
  return f & Port_mod::HUNDRED_GB_FD;
}

inline bool
port_mod_features_1tb_fd(uint32_t f) {
  return f & Port_mod::ONE_TB_FD;
}

inline bool
port_mod_features_other(uint32_t f) {
  return f & Port_mod::OTHER;
}

inline bool
port_mod_features_copper(uint32_t f) {
  return f & Port_mod::COPPER;
}

inline bool
port_mod_features_fiber(uint32_t f) {
  return f & Port_mod::FIBER;
}

inline bool
port_mod_features_auto_neg(uint32_t f) {
  return f & Port_mod::AUTO_NEG;
}

inline bool
port_mod_features_pause(uint32_t f) {
  return f & Port_mod::PAUSE;
}

inline bool
port_mod_features_pause_asym(uint32_t f) {
  return f & Port_mod::PAUSE_ASYM;
}

// -------------------------------------------------------------------------- //
// Table Mod

inline bool
operator==(const Table_mod& a, const Table_mod& b) {
  return a.table_id == b.table_id
     and a.config == b.config;
}

inline bool
operator!=(const Table_mod& a, const Table_mod& b) {
  return a != b;
}

constexpr std::size_t
bytes(const Table_mod&) { return 8; }

inline Error_condition
is_valid(const Table_mod::Config c) {
  return ok(c <= Table_mod::MISS_MASK, BAD_TABLE_MOD_CONFIG);
}

inline Error_condition
is_valid(const Table_mod tm) { return is_valid(tm.config); }

// -------------------------------------------------------------------------- //
// Stats type

constexpr Error_condition
is_valid(const Stats_type t) {
  return ok(t <= STATS_GROUP_DESC or t == STATS_EXPERIMENTER, BAD_STATS);
}

// -------------------------------------------------------------------------- //
// Stats Request Flow Base

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
  operator==(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b)
  {
    return a.table_id == b.table_id
       and a.out_port == b.out_port
       and a.out_group == b.out_group
       and a.cookie == b.cookie
       and a.cookie_mask == b.cookie_mask
       and a.match == b.match;
  }

template<Stats_type K>
  inline bool
  operator!=(const Stats_req_flow_base<K>& a, const Stats_req_flow_base<K>& b)
  { return !(a == b); }

template<Stats_type K>
  inline std::size_t
  bytes(const Stats_req_flow_base<K>& f)
  { return 32 + bytes(f.match); }

template<Stats_type K>
  inline Error_condition
  is_valid(const Stats_req_flow_base<K>& f) { return is_valid(f.match); }

template<Stats_type K>
  inline Error_condition
  to_buffer(Buffer_view& v, const Stats_req_flow_base<K>& f)
  {
    if (not available(v, bytes(f)))
      return stats_available_error<STATS_REQ, K>::value;

    to_buffer(v, f.table_id);
    pad(v, 3);
    to_buffer(v, f.out_port);
    to_buffer(v, f.out_group);
    pad(v, 4);
    to_buffer(v, f.cookie);
    to_buffer(v, f.cookie_mask);

    return to_buffer(v, f.match);
  }

template<Stats_type K>
  inline Error_condition
  from_buffer(Buffer_view& v, Stats_req_flow_base<K>& f)
  {
    if (not available(v, bytes(f)))
      return stats_available_error<STATS_REQ, K>::value;

    from_buffer(v, f.table_id);
    pad(v, 3);
    from_buffer(v, f.out_port);
    from_buffer(v, f.out_group);
    pad(v, 4);
    from_buffer(v, f.cookie);
    from_buffer(v, f.cookie_mask);

    return from_buffer(v, f.match);
  }

// -------------------------------------------------------------------------- //
// Stats Request: Port

inline bool
operator==(const Stats_req_port& a, const Stats_req_port& b) {
  return a.port_no == b.port_no;
}

inline bool
operator!=(const Stats_req_port& a, const Stats_req_port& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Stats_req_port&) { return 8; }

constexpr Error_condition
is_valid(const Stats_req_port&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Request: Queue

inline bool
operator==(const Stats_req_queue& a, const Stats_req_queue& b) {
  return a.port_no == b.port_no and a.queue_id == b.queue_id;
}

inline bool
operator!=(const Stats_req_queue& a, const Stats_req_queue& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Stats_req_queue& q) { return 8; }

constexpr Error_condition
is_valid(const Stats_req_queue& q) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Request: Group

inline bool
operator==(const Stats_req_group& a, const Stats_req_group& b) {
  return a.group_id == b.group_id;
}

inline bool
operator!=(const Stats_req_group& a, const Stats_req_group& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Stats_req_group&) { return 8; }

constexpr Error_condition
is_valid(const Stats_req_group&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Request: Experimenter

inline bool
operator==(const Stats_req_experimenter& a, const Stats_req_experimenter& b) {
  return a.experimenter_id == b.experimenter_id
     and a.data == b.data;
}

inline bool
operator!=(const Stats_req_experimenter& a, const Stats_req_experimenter& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_req_experimenter& e) {
  return 4 + bytes(e.data);
}

constexpr Error_condition
is_valid(const Stats_req_experimenter&) { return SUCCESS; }

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
    new (&p.data.aggregate) Stats_req_aggregate(std::forward<Args>(args)...); 
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
  construct(Stats_req_payload& p, Stats_req_group::Tag, Args&&... args) {
    new (&p.data.group) Stats_req_group(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_group_desc::Tag, Args&&... args) {
    new (&p.data.group_desc) Stats_req_group_desc(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Stats_req_experimenter(std::forward<Args>(args)...); 
  }

// -------------------------------------------------------------------------- //
// Stats Header

inline bool
operator==(const Stats_header& a, const Stats_header& b) {
  return a.type == b.type and a.flags == b.flags;
}

inline bool
operator!=(const Stats_header& a, const Stats_header& b) { return !(a == b); }

constexpr std::size_t
bytes(const Stats_header& h) { return 8; }

constexpr Error_condition
is_valid(const Stats_header::Flags f) { return SUCCESS; }

inline Error_condition
is_valid(const Stats_header& h) {
  if (Error_decl err = is_valid(h.type))
    return err;
  return is_valid(h.flags);
}

// -------------------------------------------------------------------------- //
// Stats Request

inline
Stats_req::~Stats_req() {
  destroy(payload, header.type);
}

inline
Stats_req::Stats_req(Stats_req&& x)
  : header(std::move(x.header)) {
  construct(payload, std::move(x.payload), header.type);
}

inline Stats_req&
Stats_req::operator=(Stats_req&& x) {
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Stats_req::Stats_req(const Stats_req& x)
  : header(x.header) {
  construct(payload, x.payload, header.type);
}

inline Stats_req&
Stats_req::operator=(const Stats_req& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

inline bool
operator==(const Stats_req& a, const Stats_req& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Stats_req& a, const Stats_req& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_req& r) {
  return bytes(r.header) + bytes(r.payload, r.header.type);
}

inline Error_condition
is_valid(const Stats_req& r) {
  if (Error_decl err = is_valid(r.header))
    return err;  
  return is_valid(r.payload, r.header.type);
}

// -------------------------------------------------------------------------- //
// Stats Response: Desc

inline bool
operator==(const Stats_res_desc& a, const Stats_res_desc& b) {
  return a.mfr_desc == b.mfr_desc
     and a.hw_desc == b.hw_desc
     and a.sw_desc == b.sw_desc
     and a.serial_num == b.serial_num
     and a.dp_desc == b.dp_desc;
}

inline bool
operator!=(const Stats_res_desc& a, const Stats_res_desc& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_desc& d) {
  return 4 * Stats_res_desc::DESC_STR_LEN + Stats_res_desc::SERIAL_NUM_LEN;
}

constexpr Error_condition
is_valid(const Stats_res_desc& d) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response: Flow

inline bool
operator==(const Stats_res_flow& a, const Stats_res_flow& b) {
  return a.length == b.length
     and a.table_id == b.table_id
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec
     and a.priority == b.priority
     and a.idle_timeout == b.idle_timeout
     and a.hard_timeout == b.hard_timeout
     and a.cookie == b.cookie
     and a.packet_count == b.packet_count
     and a.match == b.match
     and a.instructions == b.instructions;
}

inline bool
operator!=(const Stats_res_flow& a, const Stats_res_flow& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_flow& f) {
  return 48 + bytes(f.match) + bytes(f.instructions);
}

inline Error_condition
is_valid(const Stats_res_flow& f) {
  if (Error_decl err = is_valid(f.match))
    return err;
  return is_valid(f.instructions);
}

// -------------------------------------------------------------------------- //
// Stats Response: Flows

inline bool
operator==(const Stats_res_flows& a, const Stats_res_flows& b) {
  return a.flows == b.flows;
}

inline bool
operator!=(const Stats_res_flows& a, const Stats_res_flows& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_flows& f) { return bytes(f.flows); }

inline Error_condition
is_valid(const Stats_res_flows& f) { return is_valid(f.flows); }

// -------------------------------------------------------------------------- //
// Stats Response: Aggregate

inline bool
operator==(const Stats_res_aggregate& a, const Stats_res_aggregate& b) {
  return a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.flow_count == b.flow_count;
}

inline bool
operator!=(const Stats_res_aggregate& a, const Stats_res_aggregate& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Stats_res_aggregate&) { return 24; }

constexpr Error_condition
is_valid(const Stats_res_aggregate& a) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response: Port

inline bool
operator==(const Stats_res_port& a, const Stats_res_port& b) {
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

inline bool
operator!=(const Stats_res_port& a, const Stats_res_port& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Stats_res_port&) { return 104; }

constexpr Error_condition
is_valid(const Stats_res_port&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response: Ports

inline bool
operator==(const Stats_res_ports& a, const Stats_res_ports& b) {
  return a.ports == b.ports;
}

inline bool
operator!=(const Stats_res_ports& a, const Stats_res_ports& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_ports& p) { return bytes(p.ports); }

inline Error_condition
is_valid(const Stats_res_ports& p) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response: Queue

inline bool
operator==(const Stats_res_queue& a, const Stats_res_queue& b) {
  return a.port_no == b.port_no
     and a.queue_id == b.queue_id
     and a.tx_bytes == b.tx_bytes
     and a.tx_packets == b.tx_packets
     and a.tx_errors == b.tx_errors;
}

inline bool
operator!=(const Stats_res_queue& a, const Stats_res_queue& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Stats_res_queue&) { return 32; }

inline Error_condition
is_valid(const Stats_res_queue&) { return SUCCESS; }

Error_condition to_buffer(Buffer_view& v, const Stats_res_queue& q);

Error_condition from_buffer(Buffer_view& v, Stats_res_queue& q);

std::string to_string(const Stats_res_queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Stats Response: Queues

inline bool
operator==(const Stats_res_queues& a, const Stats_res_queues& b) {
  return a.queues == b.queues;
}

inline bool
operator!=(const Stats_res_queues& a, const Stats_res_queues& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_queues& q) { return bytes(q.queues); }

inline Error_condition
is_valid(const Stats_res_queues& q) { return is_valid(q.queues); }

// -------------------------------------------------------------------------- //
// Stats Response: Table

inline bool
operator==(const Stats_res_table& a, const Stats_res_table& b) {
  return a.table_id == b.table_id
     and a.name == b.name
     and a.wildcards == b.wildcards
     and a.match == b.match
     and a.instructions == b.instructions
     and a.write_actions == b.write_actions
     and a.apply_actions == b.apply_actions
     and a.config == b.config
     and a.max_entries == b.max_entries
     and a.active_count == b.active_count
     and a.lookup_count == b.lookup_count
     and a.matched_count == b.matched_count;
}

inline bool
operator!=(const Stats_res_table& a, const Stats_res_table& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Stats_res_table&) { return 88; }

inline Error_condition
is_valid(const Stats_res_table&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response: Tables

inline bool
operator==(const Stats_res_tables& a, const Stats_res_tables& b) {
  return a.tables == b.tables;
}

inline bool
operator!=(const Stats_res_tables& a, const Stats_res_tables& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_tables& t) { return bytes(t.tables); }

inline Error_condition
is_valid(const Stats_res_tables& t) { return is_valid(t.tables); }

// -------------------------------------------------------------------------- //
// Bucket Counter

inline bool
operator==(const Bucket_counter& a, const Bucket_counter& b) {
  return a.packet_count == b.packet_count
     and a.byte_count == b.byte_count;
}

inline bool
operator!=(const Bucket_counter& a, const Bucket_counter& b) {
  return !(a == b);
}

constexpr std::size_t bytes(const Bucket_counter&) { return 16; }

constexpr Error_condition
is_valid(const Bucket_counter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response: Group

inline bool
operator==(const Stats_res_group& a, const Stats_res_group& b) {
  return a.length == b.length
     and a.group_id == b.group_id
     and a.ref_count == b.ref_count
     and a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.bucket_stats == b.bucket_stats;
}

inline bool
operator!=(const Stats_res_group& a, const Stats_res_group& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_group& g) { return 32 + bytes(g.bucket_stats); }

inline Error_condition
is_valid(const Stats_res_group& g) { return is_valid(g.bucket_stats); }

// -------------------------------------------------------------------------- //
// Stats Response: Groups

inline bool
operator==(const Stats_res_groups& a, const Stats_res_groups& b) {
  return a.groups == b.groups;
}

inline bool
operator!=(const Stats_res_groups& a, const Stats_res_groups& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_groups& gd) { return bytes(gd.groups); }

// -------------------------------------------------------------------------- //
// Stats Response: Group desc

inline bool
operator==(const Stats_res_group_desc& a, const Stats_res_group_desc& b) {
  return a.length == b.length
     and a.type == b.type
     and a.group_id == b.group_id
     and a.buckets == b.buckets;
}

inline bool
operator!=(const Stats_res_group_desc& a, const Stats_res_group_desc& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_group_desc& gd) { return 8 + bytes(gd.buckets); }

inline Error_condition
is_valid(const Stats_res_group_desc& gd) { return is_valid(gd.buckets); }

// -------------------------------------------------------------------------- //
// Stats Response: Group descs

inline bool
operator==(const Stats_res_group_descs& a, const Stats_res_group_descs& b) {
  return a.group_descs == b.group_descs;
}

inline bool
operator!=(const Stats_res_group_descs& a, const Stats_res_group_descs& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_group_descs& gd) { return bytes(gd.group_descs); }

// -------------------------------------------------------------------------- //
// Stats Response: Experimenter

inline bool
operator==(const Stats_res_experimenter& a, const Stats_res_experimenter& b) {
  return a.experimenter_id == b.experimenter_id
     and a.data == b.data;
}

inline bool
operator!=(const Stats_res_experimenter& a, const Stats_res_experimenter& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_experimenter& e) { return 4 + bytes(e.data); }

inline Error_condition
is_valid(const Stats_res_experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats_res_payload
/*
template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_desc::Tag, Args&&... args) {
    new (&p.data.desc) Stats_res_desc(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_flow::Tag, Args&&... args) {
    new (&p.data.flow) Stats_res_flow(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_aggregate::Tag, Args&&... args) {
    new (&p.data.aggregate) Stats_res_aggregate(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_table::Tag, Args&&... args) {
    new (&p.data.table) Stats_res_table(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_port::Tag, Args&&... args) {
    new (&p.data.port) Stats_res_port(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_queue::Tag, Args&&... args) {
    new (&p.data.queue) Stats_res_queue(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_group::Tag, Args&&... args) {
    new (&p.data.group) Stats_res_group(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_group_desc::Tag, Args&&... args) {
    new (&p.data.group_desc) Stats_res_group_desc(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_res_payload& p, Stats_res_experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Stats_res_experimenter(std::forward<Args>(args)...); 
  }
*/
// -------------------------------------------------------------------------- //
// Stats Response

inline
Stats_res::~Stats_res() { destroy(payload, header.type); }

inline
Stats_res::Stats_res(Stats_res&& x)
  : header(std::move(x.header)) {
  construct(payload, std::move(x.payload), header.type);
}

inline Stats_res&
Stats_res::operator=(Stats_res&& x) {
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Stats_res::Stats_res(const Stats_res& x)
  : header(x.header) {
  construct(payload, x.payload, header.type);
}

inline Stats_res&
Stats_res::operator=(const Stats_res& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

inline bool
operator==(const Stats_res& a, const Stats_res& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Stats_res& a, const Stats_res& b) { return !(a == b); }

inline std::size_t
bytes(const Stats_res& r) {
  return bytes(r.header) + bytes(r.payload, r.header.type);
}

inline Error_condition
is_valid(const Stats_res& r) {
  if (Error_decl err = is_valid(r.header))
    return err;
  return is_valid(r.payload, r.header.type);
}

// -------------------------------------------------------------------------- //
// Queue Get Config Request

inline bool
operator==(const Queue_get_config_req& a, const Queue_get_config_req& b) {
  return a.port == b.port;
}

inline bool
operator!=(const Queue_get_config_req& a, const Queue_get_config_req& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Queue_get_config_req&) { return 8; }

inline Error_condition
is_valid(const Queue_get_config_req& q) {
  return ok(q.port < 0xffffff00, BAD_QUEUE_CONFIG_PORT);
}

// -------------------------------------------------------------------------- //
// Queue Get Config Repsonse

inline bool
operator==(const Queue_get_config_res& a, const Queue_get_config_res& b) {
  return a.port == b.port
     and a.queues == b.queues;
}

inline bool
operator!=(const Queue_get_config_res& a, const Queue_get_config_res& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Queue_get_config_res& qgcr) { return 8 + bytes(qgcr.queues); }

inline Error_condition
is_valid(const Queue_get_config_res& qgcr) { return is_valid(qgcr.queues); }

// -------------------------------------------------------------------------- //
// Payload

template<typename... Args>
  inline void
  construct(Payload& p, Hello::Tag, Args&&... args) {
    new (&p.data.hello) Hello(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Error::Tag, Args&&... args) {
    new (&p.data.error) Error(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Echo_req::Tag, Args&&... args) {
    new (&p.data.echo_req) Echo_req(std::forward<Args>(args)...);
  }

/*
template<typename... Args>
  inline void
  construct(Payload& p, Echo_res::Tag, Args&&... args) {
    new (&p.data.echo_res) Echo_res(std::forward<Args>(args)...);
  }
*/

template<typename... Args>
  inline void
  construct(Payload& p, Experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Experimenter(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Feature_req::Tag, Args&&... args) {
    new (&p.data.feature_req) Feature_req(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Feature_res::Tag, Args&&... args) {
    new (&p.data.feature_res) Feature_res(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Get_config_req::Tag, Args&&... args) {
    new (&p.data.get_config_req) Get_config_req(std::forward<Args>(args)...);
  }
/*
template<typename... Args>
  inline void
  construct(Payload& p, Get_config_res::Tag, Args&&... args) {
    new (&p.data.get_config_res) Get_config_res(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Set_config::Tag, Args&&... args) {
    new (&p.data.set_config) Set_config(std::forward<Args>(args)...);
  }
*/
template<typename... Args>
  inline void
  construct(Payload& p, Packet_in::Tag, Args&&... args) {
    new (&p.data.packet_in) Packet_in(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Flow_removed::Tag, Args&&... args) {
    new (&p.data.flow_removed) Flow_removed(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Port_status::Tag, Args&&... args) {
    new (&p.data.port_status) Port_status(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Packet_out::Tag, Args&&... args) {
    new (&p.data.packet_out) Packet_out(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Flow_mod::Tag, Args&&... args) {
    new (&p.data.flow_mod) Flow_mod(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Group_mod::Tag, Args&&... args) {
    new (&p.data.group_mod) Group_mod(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Port_mod::Tag, Args&&... args) {
    new (&p.data.port_mod) Port_mod(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Table_mod::Tag, Args&&... args) {
    new (&p.data.table_mod) Table_mod(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Stats_req::Tag, Args&&... args) {
    new (&p.data.stats_req) Stats_req(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Stats_res::Tag, Args&&... args) {
    new (&p.data.stats_res) Stats_res(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Barrier_req::Tag, Args&&... args) {
    new (&p.data.barrier_req) Barrier_req(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Barrier_res::Tag, Args&&... args) {
    new (&p.data.barrier_res) Barrier_res(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Queue_get_config_req::Tag, Args&&... args) {
    new (&p.data.queue_get_config_req) Queue_get_config_req(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Queue_get_config_res::Tag, Args&&... args) {
    new (&p.data.queue_get_config_res) Queue_get_config_res(std::forward<Args>(args)...);
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
operator!=(const Header& a, const Header& b) { return !(a == b); }

constexpr std::size_t
bytes(const Header&) { return 8; }

inline Error_condition
is_valid(const Header& h) { return h.length >= bytes(h); }

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

template<typename T, typename>
  Message::Message(T&& p)
    : header(std::forward<T>(p)) {
    construct(payload, std::forward<T>(p));
  }

template<typename T, typename>
  Message::Message(T&& p, uint32_t id)
    : header(std::forward<T>(p), id) { 
      construct(payload, std::forward<T>(p)); 
    }

template<typename Tag, typename... Args>
  Message::Message(uint32_t id, Tag t, Args&&... args)
    : header(t.value) {
      construct(payload, t, std::forward<Args>(args)...);
      header.xid = id;
    }

inline
Message::~Message() { destroy(payload, header.type); }

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

} // namespace v1_1
} // namespace ofp
} // namespace flog

#endif
