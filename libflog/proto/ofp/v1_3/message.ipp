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


#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_3_IPP
#define FLOWGRAMMABLE_PROTO_OFP_V1_3_IPP

namespace flog {
namespace ofp {
namespace v1_3 {

// A helper facility for mapping various enumeration values with availability
// error codes. Specializations can be found throughout this file.
template<typename T, T K> struct available_error;

// Another helper facility for doing the same with status features.
template<Message_type M, Multipart_type S> struct multipart_available_error;

// -------------------------------------------------------------------------- //
// OXM entry class

inline Error_condition
is_valid(const OXM_entry_class& c) {
  return ok(c <= NXM_1
      or c == OPEN_FLOW_BASIC
      or c == OXM_EXPERIMENTER, BAD_OXM_CLASS);
}

// -------------------------------------------------------------------------- //
// OXM entry field

inline Error_condition
is_valid(const OXM_entry_field f) {
  return ok(f == OXM_EF_IN_PORT or f == OXM_EF_IN_PHY_PORT
      or (OXM_EF_METADATA <= f and f <= OXM_EF_ETH_TYPE)
      or (OXM_EF_VLAN_VID <= f and f <= OXM_EF_VLAN_PCP)
      or f == OXM_EF_IP_DSCP or f == OXM_EF_IP_ECN
      or f == OXM_EF_IP_PROTO
      or (OXM_EF_IPV4_SRC <= f and f <= OXM_EF_TCP_SRC)
      or f == OXM_EF_TCP_DST or f == OXM_EF_UDP_SRC
      or f == OXM_EF_UDP_DST or f == OXM_EF_SCTP_SRC
      or f == OXM_EF_SCTP_DST or f == OXM_EF_ICMPV4_TYPE
      or f == OXM_EF_ICMPV4_CODE or f == OXM_EF_ARP_OP
      or (OXM_EF_ARP_SPA <= f and f <= OXM_EF_ICMPV6_TYPE)
      or f == OXM_EF_ICMPV6_CODE or f == OXM_EF_IPV6_ND_TARGET
      or f == OXM_EF_IPV6_ND_SLL or f == OXM_EF_IPV6_ND_TLL
      or f == OXM_EF_MPLS_LABEL or f == OXM_EF_MPLS_TC
      or f == OXM_EF_MPLS_BOS
      or (OXM_EF_PBB_ISID <= f and f <= OXM_EF_IPV6_EXTHDR_MASK),
         BAD_OXM_FIELD);
}

// -------------------------------------------------------------------------- //
// OXM entry payload: 8 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_VLAN_PCP> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_VLAN_PCP;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IP_DSCP> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IP_DSCP;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IP_ECN> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IP_ECN;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IP_PROTO> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IP_PROTO;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV4_TYPE> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ICMPV4_TYPE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV4_CODE> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ICMPV4_CODE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV6_TYPE> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ICMPV6_TYPE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV6_CODE> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ICMPV6_CODE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_MPLS_TC> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_MPLS_TC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_MPLS_BOS> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_MPLS_BOS;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b)
  { return a.value == b.value; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base8<K>&) { return 1; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base8<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base8<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload: 16 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_VLAN_VID> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_VLAN_VID;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_TYPE> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ETH_TYPE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_TCP_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_TCP_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_TCP_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_TCP_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_UDP_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_UDP_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_UDP_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_UDP_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_SCTP_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_SCTP_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_SCTP_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_SCTP_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_OP> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_OP;
  };
  
template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base16<K>& a, const OXM_entry_base16<K>& b)
  { return a.value == b.value; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base16<K>& a, const OXM_entry_base16<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base16<K>&) { return 2; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base16<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base16<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 16 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_VLAN_VID_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_VLAN_VID_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base16_mask<K>& a,
             const OXM_entry_base16_mask<K>& b)
  { return a.value == b.value and a.mask == b.mask; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base16_mask<K>& a,
             const OXM_entry_base16_mask<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base16_mask<K>&) { return 4; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base16_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base16_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload: 32 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_IN_PORT> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IN_PORT;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IN_PHY_PORT> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IN_PHY_PORT;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_MPLS_LABEL> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_MPLS_LABEL;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_FLABEL> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_FLABEL;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base32<K>& a, const OXM_entry_base32<K>& b)
  { return a.value == b.value; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base32<K>& a, const OXM_entry_base32<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base32<K>&) { return 4; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base32<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base32<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload : PBB I-SID

inline bool
operator==(const OXM_entry_pbb_isid& a, const OXM_entry_pbb_isid& b) {
  return a.value == b.value;
}

inline bool
operator!=(const OXM_entry_pbb_isid& a, const OXM_entry_pbb_isid& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const OXM_entry_pbb_isid&) { return 3; }

constexpr Error_condition
is_valid(const OXM_entry_pbb_isid&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 32 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_FLABEL_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_FLABEL_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base32_mask<K>& a,
             const OXM_entry_base32_mask<K>& b)
  { return a.value == b.value and a.mask == b.mask; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base32_mask<K>& a,
             const OXM_entry_base32_mask<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base32_mask<K>&) { return 8; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base32_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base32_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload : PBB I-SID mask

inline bool
operator==(const OXM_entry_pbb_isid_mask& a, const OXM_entry_pbb_isid_mask& b) {
  return a.value == b.value and a.mask == b.mask;
}

inline bool
operator!=(const OXM_entry_pbb_isid_mask& a, const OXM_entry_pbb_isid_mask& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const OXM_entry_pbb_isid_mask&) { return 6; }

constexpr Error_condition
is_valid(const OXM_entry_pbb_isid_mask&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// OXM entry payload: IPv4

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV4_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV4_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SPA> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_SPA;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_TPA> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_TPA;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv4<K>& a, const OXM_entry_ipv4<K>& b)
  { return a.value == b.value; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv4<K>& a, const OXM_entry_ipv4<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv4<K>&) { return 4; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv4<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv4<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: IP

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_SRC_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV4_SRC_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_DST_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV4_DST_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SPA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_SPA_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_TPA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_TPA_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv4_mask<K>& a,
             const OXM_entry_ipv4_mask<K>& b)
  { return a.value == b.value and a.mask == b.mask; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv4_mask<K>& a,
             const OXM_entry_ipv4_mask<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv4_mask<K>&) { return 8; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv4_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv4_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload: ethernet

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ETH_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ETH_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SHA> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_SHA;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_THA> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_THA;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_ND_SLL> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_ND_SLL;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_ND_TLL> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_ND_TLL;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b)
  { return a.value == b.value; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ethernet<K>&) { return 6; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ethernet<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ethernet<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: Ethernet

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_DST_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ETH_DST_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_SRC_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ETH_SRC_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SHA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_SHA_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_THA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_ARP_THA_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ethernet_mask<K>& a,
             const OXM_entry_ethernet_mask<K>& b)
  { return a.value == b.value and a.mask == b.mask; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ethernet_mask<K>& a,
             const OXM_entry_ethernet_mask<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ethernet_mask<K>&) { return 12; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ethernet_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ethernet_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload: 64 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_METADATA> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_METADATA;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_TUNNEL_ID> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_TUNNEL_ID;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base64<K>& a, const OXM_entry_base64<K>& b)
  { return a.value == b.value; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base64<K>& a, const OXM_entry_base64<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base64<K>&) { return 8; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base64<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base64<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 64 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_METADATA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_METADATA_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_TUNNEL_ID_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_TUNNEL_ID_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base64_mask<K>& a,
             const OXM_entry_base64_mask<K>& b)
  { return a.value == b.value and a.mask == b.mask; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base64_mask<K>& a,
             const OXM_entry_base64_mask<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base64_mask<K>&) { return 16; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base64_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base64_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload: IPv6

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_ND_TARGET> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_ND_TARGET;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv6<K>& a, const OXM_entry_ipv6<K>& b)
  { return a.value == b.value; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv6<K>& a, const OXM_entry_ipv6<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv6<K>&) { return 16; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv6<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv6<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: IPv6

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_SRC_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_SRC_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_DST_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_ENTRY_IPV6_DST_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv6_mask<K>& a,
             const OXM_entry_ipv6_mask<K>& b)
  { return a.value == b.value and a.mask == b.mask; }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv6_mask<K>& a,
             const OXM_entry_ipv6_mask<K>& b)
  { return !(a == b); }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv6_mask<K>&) { return 32; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv6_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv6_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field,K>::value;
    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload : Ipv6 ext header

inline bool
operator==(const OXM_entry_ipv6_exthdr& a, const OXM_entry_ipv6_exthdr& b) {
  return a.flag == b.flag;
}

inline bool
operator!=(const OXM_entry_ipv6_exthdr& a, const OXM_entry_ipv6_exthdr& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const OXM_entry_ipv6_exthdr&) { return 2; }

// -------------------------------------------------------------------------- //
// OXM entry payload : Ipv6 ext header mask

inline bool
operator==(const OXM_entry_ipv6_exthdr_mask& a,
           const OXM_entry_ipv6_exthdr_mask& b) {
  return a.flag == b.flag and a.mask == b.mask;
}

inline bool
operator!=(const OXM_entry_ipv6_exthdr_mask& a,
           const OXM_entry_ipv6_exthdr_mask& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const OXM_entry_ipv6_exthdr_mask&) { return 4; }

// -------------------------------------------------------------------------- //
// OXM Experimenter

inline bool
operator==(const OXM_experimenter& a, const OXM_experimenter& b) {
  return a.experimenter == b.experimenter;
}

inline bool
operator!=(const OXM_experimenter& a, const OXM_experimenter& b) {
  return !(a == b);
}

constexpr std::size_t bytes(const OXM_experimenter&) { return 4; }

// -------------------------------------------------------------------------- //
// OXM entry: Header

inline bool
operator==(const OXM_entry_header& a, const OXM_entry_header& b) {
  return a.oxm_class == b.oxm_class and a.field == b.field and
         a.length == b.length;
}

inline bool
operator!=(const OXM_entry_header& a, const OXM_entry_header& b) {
  return !(a == b);
}

inline Error_condition
is_valid(const OXM_entry_header& e) {
  if(Error_decl err = is_valid(e.oxm_class))
    return err;
  return is_valid(e.field);
}

inline std::size_t
bytes(const OXM_entry_header& h) { return 4; }

// -------------------------------------------------------------------------- //
// OXM

inline
OXM_entry::~OXM_entry() {
  if (header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    destroy(payload, header.field);
}

inline
OXM_entry::OXM_entry(OXM_entry&& x)
  : header(std::move(x.header)) {
  if (header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    construct(payload, std::move(x.payload), header.field);
  else
    payload = std::move(x.payload);
}

inline OXM_entry&
OXM_entry::operator=(OXM_entry&& x) {
  header = std::move(x.header);
  if (header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    assign(payload, std::move(x.payload), header.field);
  else
    payload = std::move(x.payload);
  return *this;
}

inline
OXM_entry::OXM_entry(const OXM_entry& x)
  : header(x.header) {
  if (x.header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    construct(payload, x.payload, header.field);
  else
    payload = x.payload;
}

inline OXM_entry&
OXM_entry::operator=(const OXM_entry& x) {
  header = x.header;
  if (x.header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    assign(payload, x.payload, header.field);
  else
    payload = x.payload;
  return *this;
}

inline bool
operator==(const OXM_entry& a, const OXM_entry& b) {
  return a.header == b.header
     and ((a.header.oxm_class == OXM_entry_class::OXM_EXPERIMENTER
     and a.experimenter == b.experimenter)
      or equal(a.payload, b.payload, a.header.field, b.header.field));
}

inline bool
operator!=(const OXM_entry& a, const OXM_entry& b) { return !(a == b); }

inline std::size_t
bytes(const OXM_entry& a) {
  if (a.header.oxm_class == OXM_entry_class::OXM_EXPERIMENTER)
    return 4 + bytes(a.experimenter);
  else
    return 4 + bytes(a.payload, a.header.field);
}

inline Error_condition
is_valid(const OXM_entry& e) {
  if(Error_decl err = is_valid(e.header))
    return err;
  return is_valid(e.payload, e.header.field);
}

inline uint64_t
OXM_entry_field_flag(const OXM_entry_field& f) {
  return 0x0000000000000001 << (f >> 1);
}

inline Error_condition
is_valid(const Sequence<OXM_entry> r) {
  for (auto iter = r.begin(); iter != r.end(); iter++) {
    if(Error_decl err = is_valid(*iter))
      return err;
  }

  // Prerequisite and conflict constraints
  uint64_t flag = 0x000000400000007D;

  for (auto iter = r.begin(); iter != r.end(); iter++) {
    OXM_entry_field type = (*iter).header.field;
    if ((flag & OXM_entry_field_flag(type)) == 0)
      return FAILURE;

    switch (type) {
    case OXM_EF_IN_PORT:
      flag &= OXM_entry_field_flag(OXM_EF_IN_PHY_PORT);
      break;

    case OXM_EF_ETH_TYPE:
      switch ((*iter).payload.data.eth_type.value) {
      case 0x0800:
        flag |= ( OXM_entry_field_flag(OXM_EF_IP_DSCP)
                | OXM_entry_field_flag(OXM_EF_IP_ECN)
                | OXM_entry_field_flag(OXM_EF_IP_PROTO)
                | OXM_entry_field_flag(OXM_EF_IPV4_DST)
                | OXM_entry_field_flag(OXM_EF_IPV4_SRC));
        break;
      case 0x86dd:
        flag |= ( OXM_entry_field_flag(OXM_EF_IP_DSCP)
                | OXM_entry_field_flag(OXM_EF_IP_ECN)
                | OXM_entry_field_flag(OXM_EF_IP_PROTO)
                | OXM_entry_field_flag(OXM_EF_IPV6_SRC)
                | OXM_entry_field_flag(OXM_EF_IPV6_DST)
                | OXM_entry_field_flag(OXM_EF_IPV6_FLABEL)
                | OXM_entry_field_flag(OXM_EF_IPV6_EXTHDR) );

        break;
      case 0x0806:
        flag |= ( OXM_entry_field_flag(OXM_EF_ARP_OP)
                | OXM_entry_field_flag(OXM_EF_ARP_SPA)
                | OXM_entry_field_flag(OXM_EF_ARP_TPA)
                | OXM_entry_field_flag(OXM_EF_ARP_SHA)
                | OXM_entry_field_flag(OXM_EF_ARP_THA));
        break;
      case 0x8847:
      case 0x8848:
        flag |= ( OXM_entry_field_flag(OXM_EF_MPLS_LABEL)
                | OXM_entry_field_flag(OXM_EF_MPLS_TC)
                | OXM_entry_field_flag(OXM_EF_MPLS_BOS) );
        break;
      case 0x88E7:
        flag |= ( OXM_entry_field_flag(OXM_EF_PBB_ISID) );
        break;
      default:
        break;
      }
      break;

    case OXM_EF_VLAN_VID:
    case OXM_EF_VLAN_VID_MASK:
      switch ((*iter).payload.data.vlan_vid.value) {
      case 0x0000:
        break;
      default:
        flag |= OXM_entry_field_flag(OXM_EF_VLAN_PCP);
      }
      break;

    case OXM_EF_IP_PROTO:
      switch ((*iter).payload.data.ip_proto.value) {
      case 6:
        flag |= ( OXM_entry_field_flag(OXM_EF_TCP_SRC)
                | OXM_entry_field_flag(OXM_EF_TCP_DST) );
        break;
      case 17:
        flag |= ( OXM_entry_field_flag(OXM_EF_UDP_SRC)
                | OXM_entry_field_flag(OXM_EF_UDP_DST) );
        break;
      case 132:
        flag |= ( OXM_entry_field_flag(OXM_EF_SCTP_SRC)
                | OXM_entry_field_flag(OXM_EF_SCTP_DST) );
        break;
      case 1:
        flag |= ( OXM_entry_field_flag(OXM_EF_ICMPV4_TYPE)
                | OXM_entry_field_flag(OXM_EF_ICMPV4_CODE) );
        break;
      case 58:
        flag |= ( OXM_entry_field_flag(OXM_EF_ICMPV6_TYPE)
                | OXM_entry_field_flag(OXM_EF_ICMPV6_CODE) );
        break;
      default:
        break;
      }
      break;

    case OXM_EF_ICMPV6_TYPE:
      switch ((*iter).payload.data.icmpv6_type.value) {
      case 135:
        flag |= ( OXM_entry_field_flag(OXM_EF_IPV6_ND_SLL)
                | OXM_entry_field_flag(OXM_EF_IPV6_ND_TARGET) );
        break;
      case 136:
        flag |= ( OXM_entry_field_flag(OXM_EF_IPV6_ND_TLL)
                | OXM_entry_field_flag(OXM_EF_IPV6_ND_TARGET) );
        break;
      default:
        break;
      }
      break;

    default:
      break;
    }

    // Each field can only appear once
    flag &= (~OXM_entry_field_flag(type));
  }

  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Match

inline bool
operator==(const Match& a, const Match& b) {
  return a.type == b.type
     and a.length == b.length
     and a.rules == b.rules;
}

inline bool
operator!=(const Match& a, const Match& b) { return !(a == b); }

inline std::size_t
bytes(const Match& m) {
  std::size_t before_pad = bytes(m.rules) + 4;
  uint8_t padding = before_pad % 8;

  if (padding != 0)
    padding = 8 - padding;

  return before_pad + padding;
}

inline Error_condition
is_valid(const Match::Type t){
  return ok(t==Match::MT_OXM,BAD_MATCH_TYPE);
}

inline Error_condition
is_valid(const Match& m) {
  if(Error_decl err = is_valid(m.type))
    return err;
  return is_valid(m.rules);
}

// -------------------------------------------------------------------------- //
// Action type

inline Error_condition
is_valid(const Action_type at) {
  return ok(at == ACTION_OUTPUT
      or at == ACTION_COPY_TTL_OUT or at == ACTION_COPY_TTL_IN
      or (ACTION_SET_MPLS_TTL <= at and at <= ACTION_POP_PBB)
      or at == ACTION_EXPERIMENTER, BAD_ACTION);
}

// -------------------------------------------------------------------------- //
// Action: Output

inline bool
operator==(const Action_output& a, const Action_output& b) {
  return a.port == b.port and b.max_len == b.max_len;
}

inline bool
operator!=(const Action_output& a, const Action_output& b) {
  return !(a == b);
}

constexpr std::size_t bytes(const Action_output&) { return 12; }

constexpr Error_condition is_valid(const Action_output&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Copy ttl out

constexpr std::size_t bytes(const Action_copy_ttl_out&) { return 4; }

constexpr Error_condition
is_valid(const Action_copy_ttl_out&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Copy ttl in

constexpr std::size_t bytes(const Action_copy_ttl_in&) { return 4; }

constexpr Error_condition is_valid(const Action_copy_ttl_in&) { return SUCCESS;}

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

template<>
  struct available_error<Action_type, ACTION_PUSH_PBB> {
    static constexpr Error_condition value = AVAILABLE_ACTION_PUSH_PBB;
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
// Action: Set Field

inline bool
operator==(const Action_set_field& a, const Action_set_field& b) {
  return a.oxm == b.oxm;
}

inline bool
operator!=(const Action_set_field& a, const Action_set_field& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Action_set_field& asf) {
  std::size_t before_pad = bytes(asf.oxm) + 4;
  uint8_t padding = before_pad % 8;

  if (padding != 0)
    padding = 8 - padding;

  return before_pad - 4 + padding;
}

constexpr Error_condition is_valid(const Action_set_field&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Pop pbb

constexpr std::size_t bytes(const Action_pop_pbb&) { return 4; }

constexpr Error_condition is_valid(const Action_pop_pbb&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action_payload

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_output::Tag, Args&&... args) {
    new (&p.data.output) Action_output(std::forward<Args>(args)...);
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
  construct(Action_payload& p, Action_set_field::Tag, Args&&... args) {
    new (&p.data.set_field) Action_set_field(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Action_experimenter(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_push_pbb::Tag, Args&&... args) {
    new (&p.data.push_pbb) Action_push_pbb(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void 
  construct(Action_payload& p, Action_pop_pbb::Tag, Args&&... args) {
    new (&p.data.pop_pbb) Action_pop_pbb(std::forward<Args>(args)...);
  }

// -------------------------------------------------------------------------- //
// Action Header

template<typename T>
  inline
  Action_header::Action_header(const T& value)
    : type(T::kind) {
    if (type != ACTION_EXPERIMENTER)
    {
      length = 4 + bytes(value);
    }
    else
    {
      length = 8;
      experimenter = value.experimenter;
    }
  }

inline bool
operator==(const Action_header& a, const Action_header& b) {
  if (a.type == ACTION_EXPERIMENTER and
      a.experimenter != b.experimenter)
    return false;

  return a.type == b.type
     and a.length == b.length;
}

inline bool
operator!=(const Action_header& a, const Action_header& b) { return !(a == b); }

inline std::size_t
bytes(const Action_header& h) {
  if (h.type != ACTION_EXPERIMENTER)
    return 4;
  else
    return 8;
}

inline Error_condition
is_valid(const Action_header& h) {
  return SUCCESS;
}

// -------------------------------------------------------------------------- //
// Action

inline Action&
Action::operator=(const Action& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
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
  return ok((INSTRUCTION_GOTO_TABLE <= it and it <= INSTRUCTION_METER)
      or it == INSTRUCTION_EXPERIMENTER, BAD_INSTRUCTION);
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
// Instruction: Meter

inline bool
operator==(const Instruction_meter& a, const Instruction_meter& b) {
  return a.meter_id == b.meter_id;
}

inline bool
operator!=(const Instruction_meter& a, const Instruction_meter& b) {
  return !(a == b);
}

constexpr std::size_t bytes(const Instruction_meter&) { return 4; }

constexpr Error_condition is_valid(const Instruction_meter&) { return SUCCESS; }

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

template<typename T>
  inline
  Instruction_header::Instruction_header(const T& value)
    : type(T::kind) {
    if (type != INSTRUCTION_EXPERIMENTER)
    {
      length = 4 + bytes(value);
    }
    else
    {
      length = 8;
      experimenter_id = value.experimenter_id;
    }
  }

inline bool
operator==(const Instruction_header& a, const Instruction_header& b) {
  if (a.type == INSTRUCTION_EXPERIMENTER and
      a.experimenter_id != b.experimenter_id)
    return false;

  return a.type == b.type
     and a.length == b.length;
}

inline bool
operator!=(const Instruction_header& a, const Instruction_header& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Instruction_header& h) {
  if (h.type == INSTRUCTION_EXPERIMENTER)
    return 8;
  else
    return 4;
}

inline Error_condition
is_valid(const Instruction_header& h) { return h.length >= bytes(h); }

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
      if ((flag & 0x80) != 0)
        return FAILURE;
      flag |= 0x80;
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
     and a.curr == b.curr
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
is_valid(const Port::Id_value id) {
  return ok(id <= 0xffffff00 or id >= 0xfffffff8, BAD_PORT_ID);
}

inline Error_condition
is_valid(const Port::Config_value) { return SUCCESS; }

inline Error_condition
is_valid(const Port::State_value) { return SUCCESS; }

inline Error_condition
is_valid(const Port::Features_value) { return SUCCESS; }

inline Error_condition
is_valid(const Port& p) {
  if (Error_decl err = is_valid(p.port_id))
    return err;
  if (Error_decl err = is_valid(p.config))
    return err;
  if (Error_decl err = is_valid(p.state))
    return err;
  if (Error_decl err = is_valid(p.curr))
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
  return ok((QUEUE_PROPERTY_MIN_RATE <= t and t <= QUEUE_PROPERTY_MAX_RATE)
      or t == QUEUE_PROPERTY_EXPERIMENTER, BAD_QUEUE_PROPERTY);
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
// Queue property: Max rate

inline bool
operator==(const Queue_property_max_rate& a, const Queue_property_max_rate& b) {
  return a.rate == b.rate;
}

inline bool
operator!=(const Queue_property_max_rate& a, const Queue_property_max_rate& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Queue_property_max_rate&) { return 8; }

constexpr Error_condition
is_valid(const Queue_property_max_rate&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Queue property: Experimenter

inline bool
operator==(const Queue_property_experimenter& a,
           const Queue_property_experimenter& b) {
  return a.experimenter == b.experimenter and a.data == b.data;
}

inline bool
operator!=(const Queue_property_experimenter& a,
           const Queue_property_experimenter& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Queue_property_experimenter& e) { return 8 + bytes(e.data); }

constexpr Error_condition
is_valid(const Queue_property_experimenter& e) { return SUCCESS; }

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
     and a.port == b.port
     and a.length == b.length
     and a.properties == b.properties;
}

inline bool
operator!=(const Queue& a, const Queue& b) { return !(a == b); }

inline std::size_t
bytes(const Queue& q) { return 16 + bytes(q.properties); }

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
  return ok(t <= METER_MOD, BAD_MESSAGE);
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
     and a.code == b.code
     and (a.type != Error::EXPERIMENTER
      or a.experimenter_id == b.experimenter_id)
     and a.data == b.data;
}

inline bool
operator!=(const Error& a, const Error& b) { return !(a == b); }

inline std::size_t
bytes(const Error& e) {
  if (e.type == Error::EXPERIMENTER)
    return 8 + bytes(e.data);
  else
    return 4 + bytes(e.data);
}

inline Error_condition
is_valid(const Error::Type t) {
  return ok((Error::HELLO_FAILED <= t
     and t <= Error::TABLE_FEATURES_FAILED)
      or t == Error::EXPERIMENTER, BAD_ERROR_TYPE);
}

inline Error_condition
is_valid(const Error::Hello_failed c) {
  return ok(c == Error::HF_INCOMPATIBLE || c == Error::HF_EPERM,
            BAD_HELLO_FAILED);
}

inline Error_condition
is_valid(const Error::Bad_request c) {
  return ok(Error::BR_BAD_VERSION <= c
     and c <= Error::BR_MULTIPART_BUFFER_OVERFLOW, BAD_BAD_REQUEST);
}

inline Error_condition
is_valid(const Error::Bad_action c) {
  return ok(Error::BA_BAD_TYPE <= c and c <= Error::BA_BAD_SET_ARGUMENT,
            BAD_BAD_ACTION); 
}

inline Error_condition
is_valid(const Error::Bad_instruction c) {
  return ok(Error::BI_UNKNOWN_INST <= c and c <= Error::BI_EPERM,
            BAD_BAD_INSTRUCTION);
}

inline Error_condition
is_valid(const Error::Bad_match c) {
  return ok(Error::BM_BAD_TYPE <= c and c <= Error::BM_EPERM, BAD_BAD_MATCH);
}

inline Error_condition
is_valid(const Error::Flow_mod_failed c) {
  return ok(Error::FMF_UNKNOWN <= c and c <= Error::FMF_BAD_FLAGS,
            BAD_FLOW_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Group_mod_failed c) {
  return ok(Error::GMF_GROUP_EXISTS <= c and c <= Error::GMF_EPERM,
            BAD_GROUP_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Port_mod_failed c) {
  return ok(Error::PMF_BAD_PORT <= c and c <= Error::PMF_EPERM,
            BAD_PORT_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Table_mod_failed c) {
  return ok(Error::TMF_BAD_TABLE <= c and c <= Error::TMF_EPERM,
            BAD_TABLE_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Queue_op_failed c) {
  return ok(Error::QOF_BAD_PORT <= c and c <= Error::QOF_EPERM,
            BAD_QUEUE_OP_FAILED);
}

inline Error_condition
is_valid(const Error::Switch_config_failed c) {
  return ok(Error::SCF_BAD_FLAGS <= c and c <= Error::SCF_EPERM,
            BAD_SWITCH_CONFIG_FAILED);
}

inline Error_condition
is_valid(const Error::Role_request_failed c) {
  return ok(Error::RRF_STALE <= c and c <= Error::RRF_BAD_ROLE,
            BAD_ROLE_REQUEST_FAILED);
}

inline Error_condition
is_valid(const Error::Meter_mod_failed c) {
  return ok(Error::MMF_UNKNOWN <= c and c <= Error::MMF_OUT_OF_BANDS,
            BAD_METER_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Table_features_failed c) {
  return ok(Error::TFF_BAD_TABLE <= c and c <= Error::TFF_PERMISSIONS_ERROR,
            BAD_TABLE_FEATURES_FAILED);
}

inline Error_condition
is_valid(const Error::Type t, Error::Code c) {
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
  case Error::ROLE_REQUEST_FAILED: return is_valid(c.rrf);
  case Error::METER_MOD_FAILED: return is_valid(c.mmf);
  case Error::TABLE_FEATURES_FAILED: return is_valid(c.tff);
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
  return a.experimenter_id == b.experimenter_id
     and a.experimenter_type == b.experimenter_type
     and a.data == b.data;
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
     and a.aux_id == b.aux_id
     and a.capabilities == b.capabilities
     and a.reserved == b.reserved;
}

inline bool
operator!=(const Feature_res& a, const Feature_res& b) { return !(a == b); }

constexpr std::size_t
bytes(const Feature_res&) { return 24; }

inline Error_condition
is_valid(const Feature_res::Capability_type& c) { return SUCCESS; }

inline Error_condition
is_valid(const Feature_res& fr) { return is_valid(fr.capabilities); }

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
feature_res_capabilities_port_blocked(uint32_t c) {
  return c & Feature_res::PORT_BLOCKED;
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
    return ok(c.flags <= 0x0003,BAD_CONFIG_FLAGS);
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
  config_frag_mask(typename Config_message_base<T>::Flags ft)
  { return ft & Config_message_base<T>::FRAG_MASK; }

// -------------------------------------------------------------------------- //
// Packet In

inline bool
operator==(const Packet_in& a, const Packet_in& b) {
  return a.buffer_id == b.buffer_id
     and a.total_len == b.total_len
     and a.reason == b.reason
     and a.tbl_id == b.tbl_id
     and a.cookie == b.cookie
     and a.match == b.match
     and a.data == b.data;
}

inline bool
operator!=(const Packet_in& a, const Packet_in& b) { return !(a == b); }

inline std::size_t
bytes(const Packet_in& pi) { return 18 + bytes(pi.match) + bytes(pi.data); }

inline Error_condition
is_valid(const Packet_in::Reason_type r) {
  return ok(r <= Packet_in::INVALID_TTL, BAD_PACKET_IN_REASON);
}

inline Error_condition
is_valid(const Packet_in& p) {
  if (Error_decl err = is_valid(p.reason))
    return err;
  return is_valid(p.match);
}

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
     and a.hard_timeout == b.hard_timeout
     and a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.match == b.match;
}

inline bool
operator!=(const Flow_removed& a, const Flow_removed& b) { return !(a == b); }

inline std::size_t
bytes(const Flow_removed& fr) { return bytes(fr.match) + 40; }

inline Error_condition
is_valid(const Flow_removed::Reason_type r) {
  return ok(r <= Flow_removed::GROUP_DELETE, BAD_FLOW_REMOVED_REASON);
}

inline Error_condition
is_valid(const Flow_removed& f) {
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
is_valid(const Port_status::Reason_type r) {
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
operator!=(const Flow_mod& a, const Flow_mod& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Flow_mod& fm) {
  return 40 + bytes(fm.match) + bytes(fm.instructions);
}

inline Error_condition
is_valid(const Flow_mod::Command t) {
  return ok(t <= Flow_mod::DELETE_STRICT, BAD_FLOW_MOD_COMMAND); ;
}

inline Error_condition 
is_valid(const Flow_mod::Command c, const uint8_t table_id) {

  if( table_id == 0xFF and c < Flow_mod::DELETE)
    return BAD_FLOW_MOD_COMMAND;
  else
    return SUCCESS;
}

inline Error_condition
is_valid(const Flow_mod::Flags t) { return SUCCESS; }

inline Error_condition
is_valid(const Flow_mod& f) {
  if (Error_decl err = is_valid(f.command))
    return err;
  if (Error_decl err = is_valid(f.command, f.table_id))
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
  return f & Port_mod::FORTY_GB_FD;
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
is_valid(const Table_mod::Config_type c) {
  return ok(c <= Table_mod::MISS_MASK, BAD_TABLE_MOD_CONFIG);
}

inline Error_condition
is_valid(const Table_mod tm) { return is_valid(tm.config); }



// -------------------------------------------------------------------------- //
// Multipart type

constexpr Error_condition
is_valid(const Multipart_type t) {
  return ok(t <= MULTIPART_PORT_DESC or t == MULTIPART_EXPERIMENTER,
            BAD_MULTIPART);
}

// -------------------------------------------------------------------------- //
// Multipart Request Flow Base

template<>
  struct multipart_available_error<MULTIPART_REQ, MULTIPART_FLOW> {
    static constexpr Error_code value = AVAILABLE_MULTIPART_REQ_FLOW;
  };

template<>
  struct multipart_available_error<MULTIPART_REQ, MULTIPART_AGGREGATE> {
    static constexpr Error_code value = AVAILABLE_MULTIPART_REQ_FLOW;
  };

template<Multipart_type K>
  inline bool
  operator==(const Multipart_req_flow_base<K>& a, const Multipart_req_flow_base<K>& b)
  {
    return a.table_id == b.table_id
       and a.out_port == b.out_port
       and a.out_group == b.out_group
       and a.cookie == b.cookie
       and a.cookie_mask == b.cookie_mask
       and a.match == b.match;
  }

template<Multipart_type K>
  inline bool
  operator!=(const Multipart_req_flow_base<K>& a, const Multipart_req_flow_base<K>& b)
  { return !(a == b); }

template<Multipart_type K>
  inline std::size_t
  bytes(const Multipart_req_flow_base<K>& f)
  { return 32 + bytes(f.match); }

template<Multipart_type K>
  inline Error_condition
  is_valid(const Multipart_req_flow_base<K>& f) { return is_valid(f.match); }

template<Multipart_type K>
  inline Error_condition
  to_buffer(Buffer_view& v, const Multipart_req_flow_base<K>& f)
  {
    if (not available(v, bytes(f)))
      return multipart_available_error<MULTIPART_REQ, K>::value;

    to_buffer(v, f.table_id);
    pad(v, 3);
    to_buffer(v, f.out_port);
    to_buffer(v, f.out_group);
    pad(v, 4);
    to_buffer(v, f.cookie);
    to_buffer(v, f.cookie_mask);

    return to_buffer(v, f.match);
  }

template<Multipart_type K>
  inline Error_condition
  from_buffer(Buffer_view& v, Multipart_req_flow_base<K>& f)
  {
    if (not available(v, bytes(f)))
      return multipart_available_error<MULTIPART_REQ, K>::value;

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
// Multipart Request: Port

inline bool
operator==(const Multipart_req_port& a, const Multipart_req_port& b) {
  return a.port_no == b.port_no;
}

inline bool
operator!=(const Multipart_req_port& a, const Multipart_req_port& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_req_port&) { return 8; }

constexpr Error_condition
is_valid(const Multipart_req_port&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Request: Queue

inline bool
operator==(const Multipart_req_queue& a, const Multipart_req_queue& b) {
  return a.port_no == b.port_no and a.queue_id == b.queue_id;
}

inline bool
operator!=(const Multipart_req_queue& a, const Multipart_req_queue& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_req_queue& q) { return 8; }

constexpr Error_condition
is_valid(const Multipart_req_queue& q) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Request: Group

inline bool
operator==(const Multipart_req_group& a, const Multipart_req_group& b) {
  return a.group_id == b.group_id;
}

inline bool
operator!=(const Multipart_req_group& a, const Multipart_req_group& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_req_group&) { return 8; }

constexpr Error_condition
is_valid(const Multipart_req_group&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Request: Meter base

template<>
  struct multipart_available_error<MULTIPART_REQ, MULTIPART_METER> {
    static constexpr Error_code value = AVAILABLE_MULTIPART_REQ_METER;
  };

template<>
  struct multipart_available_error<MULTIPART_REQ, MULTIPART_METER_CONFIG> {
    static constexpr Error_code value = AVAILABLE_MULTIPART_REQ_METER_CONFIG;
  };

template <Multipart_type K>
  inline bool
  operator==(const Multipart_req_meter_base<K>& a,
             const Multipart_req_meter_base<K>& b)
  { return a.meter_id == b.meter_id; }

template <Multipart_type K>
  inline bool
  operator!=(const Multipart_req_meter_base<K>& a,
             const Multipart_req_meter_base<K>& b)
  { return !(a == b); }

template <Multipart_type K>
  constexpr std::size_t
  bytes(const Multipart_req_meter_base<K>&) { return 8; }

template <Multipart_type K>
  constexpr Error_condition
  is_valid(const Multipart_req_meter_base<K>&) { return SUCCESS; }

template <Multipart_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Multipart_req_meter_base<K>& mb)
  {
    if (not available(v, bytes(mb)))
      return multipart_available_error<MULTIPART_REQ, K>::value;
    to_buffer(v, mb.meter_id);
    pad(v, 4);
    return SUCCESS;
  }

template <Multipart_type K>
  Error_condition
  from_buffer(Buffer_view& v, Multipart_req_meter_base<K>& mb)
  {
    if (not available(v, bytes(mb)))
      return multipart_available_error<MULTIPART_REQ, K>::value;
    from_buffer(v, mb.meter_id);
    pad(v, 4);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Multipart Request: Table feature property type

inline Error_condition
is_valid(const Table_feature_property_type tfpt)
{
  return ok((tfpt <= TABLE_FEATURE_PROPERTY_MATCH)
      or tfpt == TABLE_FEATURE_PROPERTY_WILDCARDS
      or (TABLE_FEATURE_PROPERTY_WRITE_SETFIELD <= tfpt
     and tfpt <= TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS)
      or tfpt == TABLE_FEATURE_PROPERTY_EXPERIMENTER
      or tfpt == TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS, BAD_TABLE_FEATURE_PROPERTY);
}

// -------------------------------------------------------------------------- //
// Table feature property: instructions base

template<>
  struct available_error<Table_feature_property_type,
                         TABLE_FEATURE_PROPERTY_INSTRUCTIONS> {
    static constexpr Error_code value =
                                  AVAILABLE_TABLE_FEATURE_PROPERTY_INSTRUCTIONS;
  };

template<>
  struct available_error<Table_feature_property_type,
                         TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS> {
    static constexpr Error_code value =
                             AVAILABLE_TABLE_FEATURE_PROPERTY_INSTRUCTIONS_MISS;
  };

template<Table_feature_property_type K>
  inline bool
  operator==(const Table_feature_property_instructions_base<K>& a,
             const Table_feature_property_instructions_base<K>& b)  {
    return a.instructions == b.instructions;
  }

template<Table_feature_property_type K>
  inline bool
  operator!=(const Table_feature_property_instructions_base<K>& a,
             const Table_feature_property_instructions_base<K>& b) {
    return !(a == b);
  }

template<Table_feature_property_type K>
  inline std::size_t
  bytes(const Table_feature_property_instructions_base<K>& ib) {
    return bytes(ib.instructions);
  }

template<Table_feature_property_type K>
  inline Error_condition
  is_valid(const Table_feature_property_instructions_base<K>& ib) {
    return is_valid(ib.instructions);
  }

template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_instructions_base<K>& ib) {
    if (not available(v, bytes(ib)))
      return available_error<Table_feature_property_type,K>::value;
    return to_buffer(v, ib.instructions);
  }

template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_instructions_base<K>& ib) {
    if (not available(v, bytes(ib)))
      return available_error<Table_feature_property_type,K>::value;
    return from_buffer(v, ib.instructions);
  }

// -------------------------------------------------------------------------- //
// Table id

inline bool
operator==(const Table_id& a, const Table_id& b) { return a.table == b.table; }

inline bool
operator!=(const Table_id& a, const Table_id& b) { return !(a == b); }

constexpr std::size_t
bytes(const Table_id&) { return 1; }

constexpr Error_condition
is_valid(const Table_id&) { return SUCCESS; }

inline Error_condition
to_buffer(Buffer_view& v, const Table_id& ti)
{
  if (not available(v, bytes(ti)))
    return AVAILABLE_TABLE_ID;
  to_buffer(v, ti.table);
  return SUCCESS;
}

inline Error_condition
from_buffer(Buffer_view& v, Table_id& ti)
{
  if (not available(v, bytes(ti)))
    return AVAILABLE_TABLE_ID;
  from_buffer(v, ti.table);
  return SUCCESS;
}

inline std::string
to_string(const Table_id& ti, Formatter& f) {
  std::stringstream ss;
  open_block(ss, f, "Table ID");

  nvp_to_string(ss, f, "Table ID", int(ti.table));

  close_block(ss, f, "Table ID");
  return ss.str();
}

// -------------------------------------------------------------------------- //
// Table feature property: instructions base

template<>
  struct available_error<Table_feature_property_type,
                         TABLE_FEATURE_PROPERTY_NEXT_TABLES> {
    static constexpr Error_condition value =
                                   AVAILABLE_TABLE_FEATURE_PROPERTY_NEXT_TABLES;
  };

template<>
  struct available_error<Table_feature_property_type,
                         TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS> {
    static constexpr Error_condition value =
                              AVAILABLE_TABLE_FEATURE_PROPERTY_NEXT_TABLES_MISS;
  };

template<Table_feature_property_type K>
  inline bool
  operator==(const Table_feature_property_next_tables_base<K>& a,
             const Table_feature_property_next_tables_base<K>& b)
  { return a.next_table_ids == b.next_table_ids; }

template<Table_feature_property_type K>
  inline bool
  operator!=(const Table_feature_property_next_tables_base<K>& a,
             const Table_feature_property_next_tables_base<K>& b)
  { return !(a == b); }

template<Table_feature_property_type K>
  inline std::size_t
  bytes(const Table_feature_property_next_tables_base<K>& ntb)
  { return bytes(ntb.next_table_ids); }

template<Table_feature_property_type K>
  inline Error_condition
  is_valid(const Table_feature_property_next_tables_base<K>& ntb)
  { return is_valid(ntb.next_table_ids); }

template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_next_tables_base<K>& ntb) {
    if (not available(v, bytes(ntb)))
      return available_error<Table_feature_property_type, K>::value;
    return to_buffer(v, ntb.next_table_ids);
  }

template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_next_tables_base<K>& ntb) {
    if (not available(v, bytes(ntb)))
      return available_error<Table_feature_property_type, K>::value;
    return from_buffer(v, ntb.next_table_ids);
  }

// -------------------------------------------------------------------------- //
// Table feature property: actions base

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_WRITE_ACTIONS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_ACTIONS;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_ACTIONS_MISS;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_APPLY_ACTIONS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_ACTIONS;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_ACTIONS_MISS;
  };

template<Table_feature_property_type K>
  inline bool
  operator==(const Table_feature_property_actions_base<K>& a,
             const Table_feature_property_actions_base<K>& b)
  { return a.actions == b.actions; }

template<Table_feature_property_type K>
  inline bool
  operator!=(const Table_feature_property_actions_base<K>& a,
             const Table_feature_property_actions_base<K>& b)
  { return !(a == b); }

template<Table_feature_property_type K>
  inline std::size_t
  bytes(const Table_feature_property_actions_base<K>& ab)
  { return bytes(ab.actions); }

template<Table_feature_property_type K>
  inline Error_condition
  is_valid(const Table_feature_property_actions_base<K>& ab)
  { return is_valid(ab.actions); }

template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_actions_base<K>& ab) {
    if (not available(v, bytes(ab)))
      return available_error<Table_feature_property_type, K>::value;
    return to_buffer(v, ab.actions);
  }

template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_actions_base<K>& ab) {
    if (not available(v, bytes(ab)))
      return available_error<Table_feature_property_type, K>::value;
    return from_buffer(v, ab.actions);
  }

// -------------------------------------------------------------------------- //
// Table feature property: oxm base

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_MATCH> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_MATCH;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_WILDCARDS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_WILDCARDS;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_WRITE_SETFIELD> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_SETFIELD;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_WRITE_SETFIELD_MISS;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_APPLY_SETFIELD> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_SETFIELD;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_APPLY_SETFIELD_MISS;
  };

template<Table_feature_property_type K>
  inline bool
  operator==(const Table_feature_property_oxm_base<K>& a,
             const Table_feature_property_oxm_base<K>& b) {
    return a.oxms == b.oxms;
  }

template<Table_feature_property_type K>
  inline bool
  operator!=(const Table_feature_property_oxm_base<K>& a,
             const Table_feature_property_oxm_base<K>& b) { return !(a == b); }

template<Table_feature_property_type K>
  inline std::size_t
  bytes(const Table_feature_property_oxm_base<K>& ob) { return bytes(ob.oxms); }

template<Table_feature_property_type K>
  inline Error_condition
  is_valid(const Table_feature_property_oxm_base<K>& ob) { return SUCCESS; }

template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_oxm_base<K>& ob) {
    if (not available(v, bytes(ob)))
      return available_error<Table_feature_property_type, K>::value;
    return to_buffer(v, ob.oxms);
  }

template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_oxm_base<K>& ob) {
    if (not available(v, bytes(ob)))
      return available_error<Table_feature_property_type, K>::value;
    return from_buffer(v, ob.oxms);
  }

// -------------------------------------------------------------------------- //
// Table feature property: experimenter base

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_EXPERIMENTER> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_EXPERIMENTER;
  };

template<>
  struct available_error<Table_feature_property_type, TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS> {
    static constexpr Error_condition value = AVAILABLE_TABLE_FEATURE_PROPERTY_EXPERIMENTER_MISS;
  };

template<Table_feature_property_type K>
  inline bool
  operator==(const Table_feature_property_experimenter_base<K>& a,
             const Table_feature_property_experimenter_base<K>& b)
  { return a.data == b.data; }

template<Table_feature_property_type K>
  inline bool
  operator!=(const Table_feature_property_experimenter_base<K>& a,
             const Table_feature_property_experimenter_base<K>& b)
  { return !(a == b); }

template<Table_feature_property_type K>
  inline std::size_t
  bytes(const Table_feature_property_experimenter_base<K>& eb)
  { return bytes(eb.data); }

template<Table_feature_property_type K>
  inline Error_condition
  is_valid(const Table_feature_property_experimenter_base<K>& eb)
  { return SUCCESS; }

template<Table_feature_property_type K>
  Error_condition to_buffer(Buffer_view& v,
                 const Table_feature_property_experimenter_base<K>& eb) {
    if (not available(v, bytes(eb)))
      return available_error<Table_feature_property_type, K>::value;
    return to_buffer(v, eb.data);
  }

template<Table_feature_property_type K>
  Error_condition from_buffer(Buffer_view& v,
                   Table_feature_property_experimenter_base<K>& eb) {
    if (not available(v, bytes(eb)))
      return available_error<Table_feature_property_type, K>::value;
    return from_buffer(v, eb.data);
  }

// -------------------------------------------------------------------------- //
// Table feature property header

inline bool
operator==(const Table_feature_property_header& a,
           const Table_feature_property_header& b) {
  return a.type == b.type and a.length == b.length;
}

inline bool
operator!=(const Table_feature_property_header& a,
           const Table_feature_property_header& b) { return !(a == b); }

constexpr std::size_t
bytes(const Table_feature_property_header&) { return 4; }

inline Error_condition
is_valid(const Table_feature_property_header& h) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Table feature property

inline
Table_feature_property::~Table_feature_property() {
  destroy(payload, header.type);
}

inline
Table_feature_property::Table_feature_property(Table_feature_property&& x)
  : header(std::move(x.header)) {
  construct(payload, std::move(x.payload), header.type);
}

inline Table_feature_property&
Table_feature_property::operator=(Table_feature_property&& x) {
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Table_feature_property::Table_feature_property(const Table_feature_property& x)
  : header(x.header) {
  construct(payload, x.payload, header.type);
}

inline Table_feature_property&
Table_feature_property::operator=(const Table_feature_property& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

inline bool
operator==(const Table_feature_property& a, const Table_feature_property& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Table_feature_property& a, const Table_feature_property& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Table_feature_property& tfp) {
  return bytes(tfp.header) + bytes(tfp.payload, tfp.header.type);
}

inline Error_condition
is_valid(const Table_feature_property& tfp) {
  if(Error_decl err = is_valid(tfp.header))
    return err;
  return is_valid(tfp.payload, tfp.header.type);
}

// -------------------------------------------------------------------------- //
// Multipart Request: Table feature

inline bool
operator==(const Multipart_req_table_feature& a,
           const Multipart_req_table_feature& b) {
  return a.length == b.length
     and a.table_id == b.table_id
     and a.name == b.name
     and a.metadata_match == b.metadata_match
     and a.metadata_write == b.metadata_write
     and a.config == b.config
     and a.max_entries == b.max_entries
     and a.properties == b.properties;
}

inline bool
operator!=(const Multipart_req_table_feature& a,
           const Multipart_req_table_feature& b) { return !(a == b); }

inline std::size_t
bytes(const Multipart_req_table_feature& tf) {
  std::size_t size = 64 + bytes(tf.properties);

  if (size % 8 != 0)
    size += (8 - size % 8);

  return size;
}

inline Error_condition
is_valid(const Multipart_req_table_feature& tf) {
  return is_valid(tf.properties);
}

// -------------------------------------------------------------------------- //
// Multipart Request: Table features

inline bool
operator==(const Multipart_req_table_features& a,
           const Multipart_req_table_features& b) {
  return a.table_features == b.table_features;
}

inline bool
operator!=(const Multipart_req_table_features& a,
           const Multipart_req_table_features& b) { return !(a == b); }

inline std::size_t
bytes(const Multipart_req_table_features& tf) {
  return bytes(tf.table_features);
}

inline Error_condition
is_valid(const Multipart_req_table_features& tf) {
  return is_valid(tf.table_features);
}

// -------------------------------------------------------------------------- //
// Multipart Request: Experimenter

inline bool
operator==(const Multipart_req_experimenter& a, const Multipart_req_experimenter& b) {
  return a.experimenter_id == b.experimenter_id
     and a.exp_type == b.exp_type
     and a.data == b.data;
}

inline bool
operator!=(const Multipart_req_experimenter& a, const Multipart_req_experimenter& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_req_experimenter& e) {
  return 8 + bytes(e.data);
}

constexpr Error_condition
is_valid(const Multipart_req_experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart_req_payload

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_desc::Tag, Args&&... args) {
    new (&p.data.desc) Multipart_req_desc(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_flow::Tag, Args&&... args) {
    new (&p.data.flow) Multipart_req_flow(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_aggregate::Tag, Args&&... args) {
    new (&p.data.aggregate) Multipart_req_aggregate(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_table::Tag, Args&&... args) {
    new (&p.data.table) Multipart_req_table(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_port::Tag, Args&&... args) {
    new (&p.data.port) Multipart_req_port(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_queue::Tag, Args&&... args) {
    new (&p.data.queue) Multipart_req_queue(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_group::Tag, Args&&... args) {
    new (&p.data.group) Multipart_req_group(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_group_desc::Tag, Args&&... args) {
    new (&p.data.group_desc) Multipart_req_group_desc(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_group_features::Tag, Args&&... args) {
    new (&p.data.group_features) Multipart_req_group_features(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_meter::Tag, Args&&... args) {
    new (&p.data.meter) Multipart_req_meter(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_meter_config::Tag, Args&&... args) {
    new (&p.data.meter_config) Multipart_req_meter_config(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_meter_features::Tag, Args&&... args) {
    new (&p.data.meter_features) Multipart_req_meter_features(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_table_features::Tag, Args&&... args) {
    new (&p.data.table_features) Multipart_req_table_features(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_port_desc::Tag, Args&&... args) {
    new (&p.data.port_desc) Multipart_req_port_desc(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Multipart_req_payload& p, Multipart_req_experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Multipart_req_experimenter(std::forward<Args>(args)...); 
  }

// -------------------------------------------------------------------------- //
// Multipart Header

inline bool
operator==(const Multipart_header& a, const Multipart_header& b) {
  return a.type == b.type and a.flags == b.flags;
}

inline bool
operator!=(const Multipart_header& a, const Multipart_header& b) { return !(a == b); }

constexpr std::size_t
bytes(const Multipart_header& h) { return 8; }

constexpr Error_condition
is_valid(const Multipart_header::Flags f) { return SUCCESS; }

inline Error_condition
is_valid(const Multipart_header& h) {
  return is_valid(h.type);
}

// -------------------------------------------------------------------------- //
// Multipart Request

inline
Multipart_req::~Multipart_req() {
  destroy(payload, header.type);
}

inline
Multipart_req::Multipart_req(Multipart_req&& x)
  : header(std::move(x.header)) {
  construct(payload, std::move(x.payload), header.type);
}

inline Multipart_req&
Multipart_req::operator=(Multipart_req&& x) {
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Multipart_req::Multipart_req(const Multipart_req& x)
  : header(x.header) {
  construct(payload, x.payload, header.type);
}

inline Multipart_req&
Multipart_req::operator=(const Multipart_req& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

inline bool
operator==(const Multipart_req& a, const Multipart_req& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Multipart_req& a, const Multipart_req& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_req& r) {
  return bytes(r.header) + bytes(r.payload, r.header.type);
}

inline Error_condition
is_valid(const Multipart_req& r) {
  if (Error_decl err = is_valid(r.header))
    return err;  
  return is_valid(r.payload, r.header.type);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Desc

inline bool
operator==(const Multipart_res_desc& a, const Multipart_res_desc& b) {
  return a.mfr_desc == b.mfr_desc
     and a.hw_desc == b.hw_desc
     and a.sw_desc == b.sw_desc
     and a.serial_num == b.serial_num
     and a.dp_desc == b.dp_desc;
}

inline bool
operator!=(const Multipart_res_desc& a, const Multipart_res_desc& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_desc& d) {
  return 4 * Multipart_res_desc::DESC_STR_LEN + Multipart_res_desc::SERIAL_NUM_LEN;
}

constexpr Error_condition
is_valid(const Multipart_res_desc& d) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response: Flow

inline bool
operator==(const Multipart_res_flow& a, const Multipart_res_flow& b) {
  return a.length == b.length
     and a.table_id == b.table_id
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec
     and a.priority == b.priority
     and a.idle_timeout == b.idle_timeout
     and a.hard_timeout == b.hard_timeout
     and a.flags == b.flags
     and a.cookie == b.cookie
     and a.packet_count == b.packet_count
     and a.match == b.match
     and a.instructions == b.instructions;
}

inline bool
operator!=(const Multipart_res_flow& a, const Multipart_res_flow& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_flow& f) {
  return 48 + bytes(f.match) + bytes(f.instructions);
}

inline Error_condition
is_valid(const Multipart_res_flow& f) {
  if (Error_decl err = is_valid(f.match))
    return err;
  return is_valid(f.instructions);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Flows

inline bool
operator==(const Multipart_res_flows& a, const Multipart_res_flows& b) {
  return a.flows == b.flows;
}

inline bool
operator!=(const Multipart_res_flows& a, const Multipart_res_flows& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_flows& f) { return bytes(f.flows); }

inline Error_condition
is_valid(const Multipart_res_flows& f) { return is_valid(f.flows); }

// -------------------------------------------------------------------------- //
// Multipart Response: Aggregate

inline bool
operator==(const Multipart_res_aggregate& a, const Multipart_res_aggregate& b) {
  return a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.flow_count == b.flow_count;
}

inline bool
operator!=(const Multipart_res_aggregate& a, const Multipart_res_aggregate& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_res_aggregate&) { return 24; }

constexpr Error_condition
is_valid(const Multipart_res_aggregate& a) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response: Port

inline bool
operator==(const Multipart_res_port& a, const Multipart_res_port& b) {
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
     and a.collisions == b.collisions
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec;
}

inline bool
operator!=(const Multipart_res_port& a, const Multipart_res_port& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_res_port&) { return 112; }

constexpr Error_condition
is_valid(const Multipart_res_port&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response: Ports

inline bool
operator==(const Multipart_res_ports& a, const Multipart_res_ports& b) {
  return a.ports == b.ports;
}

inline bool
operator!=(const Multipart_res_ports& a, const Multipart_res_ports& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_ports& p) { return bytes(p.ports); }

inline Error_condition
is_valid(const Multipart_res_ports& p) { return is_valid(p.ports); }

// -------------------------------------------------------------------------- //
// Multipart Response: Queue

inline bool
operator==(const Multipart_res_queue& a, const Multipart_res_queue& b) {
  return a.port_no == b.port_no
     and a.queue_id == b.queue_id
     and a.tx_bytes == b.tx_bytes
     and a.tx_packets == b.tx_packets
     and a.tx_errors == b.tx_errors
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec;
}

inline bool
operator!=(const Multipart_res_queue& a, const Multipart_res_queue& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_res_queue&) { return 40; }

inline Error_condition
is_valid(const Multipart_res_queue&) { return SUCCESS; }

Error_condition to_buffer(Buffer_view& v, const Multipart_res_queue& q);

Error_condition from_buffer(Buffer_view& v, Multipart_res_queue& q);

std::string to_string(const Multipart_res_queue&, Formatter&);

// -------------------------------------------------------------------------- //
// Multipart Response: Queues

inline bool
operator==(const Multipart_res_queues& a, const Multipart_res_queues& b) {
  return a.queues == b.queues;
}

inline bool
operator!=(const Multipart_res_queues& a, const Multipart_res_queues& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_queues& q) { return bytes(q.queues); }

inline Error_condition
is_valid(const Multipart_res_queues& q) { return is_valid(q.queues); }

// -------------------------------------------------------------------------- //
// Multipart Response: Table

inline bool
operator==(const Multipart_res_table& a, const Multipart_res_table& b) {
  return a.table_id == b.table_id
     and a.active_count == b.active_count
     and a.lookup_count == b.lookup_count
     and a.matched_count == b.matched_count;
}

inline bool
operator!=(const Multipart_res_table& a, const Multipart_res_table& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_res_table&) { return 24; }

inline Error_condition
is_valid(const Multipart_res_table&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response: Tables

inline bool
operator==(const Multipart_res_tables& a, const Multipart_res_tables& b) {
  return a.tables == b.tables;
}

inline bool
operator!=(const Multipart_res_tables& a, const Multipart_res_tables& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_tables& t) { return bytes(t.tables); }

inline Error_condition
is_valid(const Multipart_res_tables& t) {
  int table_id = -1;

  auto iter = t.tables.begin();
  auto end = t.tables.end();
  while (iter != end)
  {
    int tid = iter->table_id;
    if (tid <= table_id)
      return FAILURE;
    table_id = tid;
    iter++;
  }
  return ok(iter == end, FAILURE);
}

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
// Multipart Response: Group

inline bool
operator==(const Multipart_res_group& a, const Multipart_res_group& b) {
  return a.length == b.length
     and a.group_id == b.group_id
     and a.ref_count == b.ref_count
     and a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec
     and a.bucket_multipart == b.bucket_multipart;
}

inline bool
operator!=(const Multipart_res_group& a, const Multipart_res_group& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_group& g) { return 40 + bytes(g.bucket_multipart); }

inline Error_condition
is_valid(const Multipart_res_group& g) { return is_valid(g.bucket_multipart); }

// -------------------------------------------------------------------------- //
// Multipart Response: Groups

inline bool
operator==(const Multipart_res_groups& a, const Multipart_res_groups& b) {
  return a.groups == b.groups;
}

inline bool
operator!=(const Multipart_res_groups& a, const Multipart_res_groups& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_groups& gd) { return bytes(gd.groups); }

inline Error_condition
is_valid(const Multipart_res_groups& g) { return is_valid(g.groups); }

// -------------------------------------------------------------------------- //
// Multipart Response: Group desc

inline bool
operator==(const Multipart_res_group_desc& a,
           const Multipart_res_group_desc& b) {
  return a.length == b.length
     and a.type == b.type
     and a.group_id == b.group_id
     and a.buckets == b.buckets;
}

inline bool
operator!=(const Multipart_res_group_desc& a,
           const Multipart_res_group_desc& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_group_desc& gd) { return 8 + bytes(gd.buckets); }

inline Error_condition
is_valid(const Multipart_res_group_desc& gd) { return is_valid(gd.buckets); }

// -------------------------------------------------------------------------- //
// Multipart Response: Group descs

inline bool
operator==(const Multipart_res_group_descs& a,
           const Multipart_res_group_descs& b) {
  return a.group_descs == b.group_descs;
}

inline bool
operator!=(const Multipart_res_group_descs& a,
           const Multipart_res_group_descs& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_group_descs& gd) { return bytes(gd.group_descs); }

inline Error_condition
is_valid(const Multipart_res_group_descs& gd) {
  return is_valid(gd.group_descs);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Group features

inline bool
operator==(const Multipart_res_group_features& a,
           const Multipart_res_group_features& b) {
  return a.types == b.types
     and a.capabilities == b.capabilities
     and a.max_groups_all
     and a.max_groups_select
     and a.max_groups_indirect
     and a.max_groups_ff
     and a.actions_all
     and a.actions_select
     and a.actions_indirect
     and a.actions_ff;
}

inline bool
operator!=(const Multipart_res_group_features& a,
           const Multipart_res_group_features& b) { return !(a == b); }

constexpr std::size_t
bytes(const Multipart_res_group_features&) { return 40; }

constexpr Error_condition
is_valid(const Multipart_res_group_features&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response: Meter band stats

inline bool
operator==(const Meter_band_stats& a, const Meter_band_stats& b) {
  return a.packet_band_count == b.packet_band_count
     and a.byte_band_count == b.byte_band_count;
}

inline bool
operator!=(const Meter_band_stats& a, const Meter_band_stats& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Meter_band_stats&) { return 16; }

constexpr Error_condition
is_valid(const Meter_band_stats&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response: Meter

inline bool
operator==(const Multipart_res_meter& a, const Multipart_res_meter& b) {
  return a.meter_id == b.meter_id
     and a.len == b.len
     and a.flow_count == b.flow_count
     and a.packet_in_count == b.packet_in_count
     and a.byte_in_count == b.byte_in_count
     and a.duration_sec == b.duration_sec
     and a.duration_nsec == b.duration_nsec
     and a.meter_band_stats == b.meter_band_stats;
}

inline bool
operator!=(const Multipart_res_meter& a, const Multipart_res_meter& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_meter& m) { return 40 + bytes(m.meter_band_stats); }

inline Error_condition
is_valid(const Multipart_res_meter& m) { return is_valid(m.meter_band_stats); }

// -------------------------------------------------------------------------- //
// Multipart Response: Meters

inline bool
operator==(const Multipart_res_meters& a, const Multipart_res_meters& b) {
  return a.meters == b.meters;
}

inline bool
operator!=(const Multipart_res_meters& a, const Multipart_res_meters& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_meters& m) { return bytes(m.meters); }

inline Error_condition
is_valid(const Multipart_res_meters& m) { return is_valid(m.meters); }

// -------------------------------------------------------------------------- //
// Meter band type

inline Error_condition
is_valid(const Meter_band_type mbt)
{
  return ok((METER_BAND_DROP <= mbt and mbt <= METER_BAND_DSCP_REMARK)
      or mbt == METER_BAND_EXPERIMENTER, BAD_METER_BAND);
}

// -------------------------------------------------------------------------- //
// Meter band: drop

constexpr std::size_t
bytes(const Meter_band_drop&) { return 4; }

constexpr Error_condition
is_valid(const Meter_band_drop&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Meter band: dscp remark

inline bool
operator==(const Meter_band_dscp_remark& a, const Meter_band_dscp_remark& b) {
  return a.prec_level == b.prec_level;
}

inline bool
operator!=(const Meter_band_dscp_remark& a, const Meter_band_dscp_remark& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Meter_band_dscp_remark&) { return 4; }

constexpr Error_condition
is_valid(const Meter_band_dscp_remark&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Meter band: experimenter

inline bool
operator==(const Meter_band_experimenter& a, const Meter_band_experimenter& b) {
  return a.experimenter_id == b.experimenter_id;
}

inline bool
operator!=(const Meter_band_experimenter& a, const Meter_band_experimenter& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Meter_band_experimenter&) { return 4; }

constexpr Error_condition
is_valid(const Meter_band_experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Meter band header

inline bool
operator==(const Meter_band_header& a, const Meter_band_header& b) {
  return a.type == b.type
     and a.len == b.len
     and a.rate == b.rate
     and a.burst_size == b.burst_size;
}

inline bool
operator!=(const Meter_band_header& a, const Meter_band_header& b) {
  return !(a == b);
}

constexpr std::size_t
bytes(const Meter_band_header&) { return 12; }

inline Error_condition
is_valid(const Meter_band_header& h) {
  return SUCCESS;//h.len >= bytes(h);
}

// -------------------------------------------------------------------------- //
// Meter band

inline
Meter_band::Meter_band(const Meter_band& x)
  : header(x.header) { construct(payload, x.payload, header.type); }

inline Meter_band&
Meter_band::operator=(const Meter_band& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

inline bool
operator==(const Meter_band& a, const Meter_band& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Meter_band& a, const Meter_band& b) { return !(a == b); }

inline std::size_t
bytes(const Meter_band& mb) {
  return bytes(mb.header) + bytes(mb.payload, mb.header.type);
}

inline Error_condition
is_valid(const Meter_band& mb)
{
  if(Error_decl err = is_valid(mb.header))
    return err;
  return is_valid(mb.payload, mb.header.type);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Meter config

inline bool
operator==(const Multipart_res_meter_config& a,
           const Multipart_res_meter_config& b) {
  return a.len == b.len
     and a.flags == b.flags
     and a.meter_id == b.meter_id
     and a.meter_bands == b.meter_bands;
}

inline bool
operator!=(const Multipart_res_meter_config& a,
           const Multipart_res_meter_config& b) { return !(a == b); }

inline std::size_t
bytes(const Multipart_res_meter_config& mc) { return 8 + bytes(mc.meter_bands);}

inline Error_condition
is_valid(const Multipart_res_meter_config& mc) {
  return is_valid(mc.meter_bands);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Meter configs

inline bool
operator==(const Multipart_res_meter_configs& a,
           const Multipart_res_meter_configs& b) {
  return a.meter_configs == b.meter_configs;
}

inline bool
operator!=(const Multipart_res_meter_configs& a,
           const Multipart_res_meter_configs& b) { return !(a == b); }

inline std::size_t
bytes(const Multipart_res_meter_configs& mc) { return bytes(mc.meter_configs); }

inline Error_condition
is_valid(const Multipart_res_meter_configs& mc) {
  return is_valid(mc.meter_configs);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Meter features

inline bool
operator==(const Multipart_res_meter_features& a,
           const Multipart_res_meter_features& b)
{
  return a.max_meter == b.max_meter
     and a.band_type == b.band_type
     and a.capabilities == b.capabilities
     and a.max_bands == b.max_bands
     and a.max_color == b.max_color;
}

inline bool
operator!=(const Multipart_res_meter_features& a,
           const Multipart_res_meter_features& b)
{
  return !(a == b);
}

constexpr std::size_t
bytes(const Multipart_res_meter_features&) { return 16; }

constexpr Error_condition
is_valid(const Multipart_res_meter_features&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response: Table feature

inline bool
operator==(const Multipart_res_table_feature& a,
           const Multipart_res_table_feature& b) {
  return a.length == b.length
     and a.table_id == b.table_id
     and a.name == b.name
     and a.metadata_match == b.metadata_match
     and a.metadata_write == b.metadata_write
     and a.config == b.config
     and a.max_entries == b.max_entries
     and a.properties == b.properties;
}

inline bool
operator!=(const Multipart_res_table_feature& a,
           const Multipart_res_table_feature& b) { return !(a == b); }

inline std::size_t
bytes(const Multipart_res_table_feature& tf) {
  std::size_t size = 64 + bytes(tf.properties);

  if (size % 8 != 0)
    size += (8 - size % 8);

  return size;
 // return 64 + bytes(tf.properties);
}

inline Error_condition
is_valid(const Multipart_res_table_feature& tf) {
  return is_valid(tf.properties);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Table features

inline bool
operator==(const Multipart_res_table_features& a,
           const Multipart_res_table_features& b) {
  return a.table_features == b.table_features;
}

inline bool
operator!=(const Multipart_res_table_features& a,
           const Multipart_res_table_features& b) { return !(a == b); }

inline std::size_t
bytes(const Multipart_res_table_features& tf) {
  return bytes(tf.table_features);
}

inline Error_condition
is_valid(const Multipart_res_table_features& tf) {
  return is_valid(tf.table_features);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Port desc

inline bool
operator==(const Multipart_res_port_desc& a, const Multipart_res_port_desc& b)
{
  return a.ports == b.ports;
}

inline bool
operator!=(const Multipart_res_port_desc& a, const Multipart_res_port_desc& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_port_desc& pd)
{
  return bytes(pd.ports);
}

inline Error_condition
is_valid(const Multipart_res_port_desc& pd)
{
  return is_valid(pd.ports);
}

// -------------------------------------------------------------------------- //
// Multipart Response: Experimenter

inline bool
operator==(const Multipart_res_experimenter& a,
           const Multipart_res_experimenter& b) {
  return a.experimenter_id == b.experimenter_id
     and a.exp_type == b.exp_type
     and a.data == b.data;
}

inline bool
operator!=(const Multipart_res_experimenter& a,
           const Multipart_res_experimenter& b) {
  return !(a == b);
}

inline std::size_t
bytes(const Multipart_res_experimenter& e) { return 8 + bytes(e.data); }

inline Error_condition
is_valid(const Multipart_res_experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Multipart Response

inline
Multipart_res::~Multipart_res() { destroy(payload, header.type); }

inline
Multipart_res::Multipart_res(Multipart_res&& x)
  : header(std::move(x.header)) {
  construct(payload, std::move(x.payload), header.type);
}

inline Multipart_res&
Multipart_res::operator=(Multipart_res&& x) {
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Multipart_res::Multipart_res(const Multipart_res& x)
  : header(x.header) {
  construct(payload, x.payload, header.type);
}

inline Multipart_res&
Multipart_res::operator=(const Multipart_res& x) {
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

inline bool
operator==(const Multipart_res& a, const Multipart_res& b) {
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Multipart_res& a, const Multipart_res& b) { return !(a == b); }

inline std::size_t
bytes(const Multipart_res& r) {
  return bytes(r.header) + bytes(r.payload, r.header.type);
}

inline Error_condition
is_valid(const Multipart_res& r) {
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
// Role enum

constexpr Error_condition
is_valid(const Role r) { return ok(r <= Role::R_SLAVE, BAD_ROLE); }

// -------------------------------------------------------------------------- //
// Role Base

template<>
  struct available_error<Message_type, ROLE_REQ> {
    static constexpr Error_code value = AVAILABLE_ROLE_REQ;
  };

template<>
  struct available_error<Message_type, ROLE_RES> {
    static constexpr Error_code value = AVAILABLE_ROLE_RES;
  };

template <Message_type K>
  inline bool
  operator==(const Role_base<K>& a, const Role_base<K>& b) {
    return a.role == b.role and a.generation_id == b.generation_id;
  }

template <Message_type K>
  inline bool
  operator!=(const Role_base<K>& a, const Role_base<K>& b) { return !(a == b); }

template <Message_type K>
  constexpr std::size_t bytes(const Role_base<K>&) { return 16; }

template <Message_type K>
  constexpr Error_condition is_valid(const Role_base<K>& rb) {
    return is_valid(rb.role);
  }

template <Message_type K>
  Error_condition to_buffer(Buffer_view& v, const Role_base<K>& rb) {
    if (not available(v, bytes(rb)))
      return available_error<Message_type,K>::value;
    to_buffer(v, rb.role);
    pad(v, 4);
    to_buffer(v, rb.generation_id);
    return SUCCESS;
  }

template <Message_type K>
  Error_condition from_buffer(Buffer_view& v, Role_base<K>& rb) {
    if (not available(v, bytes(rb)))
      return available_error<Message_type,K>::value;
    from_buffer(v, rb.role);
    pad(v, 4);
    from_buffer(v, rb.generation_id);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Async base

template<>
  struct available_error<Message_type, GET_ASYNC_RES> {
    static constexpr Error_code value = AVAILABLE_GET_ASYNC_RES;
  };

template<>
  struct available_error<Message_type, SET_ASYNC> {
    static constexpr Error_code value = AVAILABLE_SET_ASYNC;
  };

template<Message_type T>
  inline bool
  operator==(const Async_message_base<T>& a, const Async_message_base<T>& b) {
    return a.packet_in_mask == b.packet_in_mask
       and a.packet_in_mask_slave == b.packet_in_mask_slave
       and a.port_status_mask == b.port_status_mask
       and a.port_status_mask_slave == b.port_status_mask_slave
       and a.flow_removed_mask == b.flow_removed_mask
       and a.flow_removed_mask_slave == b.flow_removed_mask_slave;
  }

template<Message_type T>
  inline bool
  operator!=(const Async_message_base<T>& a, const Async_message_base<T>& b)
  { return !(a == b); }

template<Message_type T>
  constexpr std::size_t
  bytes(const Async_message_base<T>&) { return 24; }

template<Message_type T>
  inline Error_condition
  is_valid(const Async_message_base<T>& c) { return SUCCESS; }

template<Message_type T>
  inline Error_condition
  to_buffer(Buffer_view& b, const Async_message_base<T>& m) {
    if (not available(b, bytes(m)))
      return available_error<Message_type, T>::value;
    to_buffer(b, m.packet_in_mask);
    to_buffer(b, m.packet_in_mask_slave);
    to_buffer(b, m.port_status_mask);
    to_buffer(b, m.port_status_mask_slave);
    to_buffer(b, m.flow_removed_mask);
    to_buffer(b, m.flow_removed_mask_slave);
    return SUCCESS;
  }

template<Message_type T>
  inline Error_condition
  from_buffer(Buffer_view& b, Async_message_base<T>& m) {
    if (not available(b, bytes(m)))
      return available_error<Message_type, T>::value;
    from_buffer(b, m.packet_in_mask);
    from_buffer(b, m.packet_in_mask_slave);
    from_buffer(b, m.port_status_mask);
    from_buffer(b, m.port_status_mask_slave);
    from_buffer(b, m.flow_removed_mask);
    from_buffer(b, m.flow_removed_mask_slave);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// Meter Mod

inline bool
operator==(const Meter_mod& a, const Meter_mod& b) {
  return a.command == b.command
     and a.flags == b.flags
     and a.meter_id == b.meter_id
     and a.meter_bands == b.meter_bands;
}

inline bool
operator!=(const Meter_mod& a, const Meter_mod& b) { return !(a == b); }

inline std::size_t
bytes(const Meter_mod& mm) { return 8 + bytes(mm.meter_bands); }

inline Error_condition
is_valid(const Meter_mod::Command c) {
  return ok(c <= Meter_mod::DELETE, BAD_METER_MOD_COMMAND);
}

inline Error_condition
is_valid(const Meter_mod::Id_value i) {
  return ok(i == Meter_mod::MAX
      or i >= Meter_mod::SLOW_PATH, BAD_METER_MOD_ID);
}

inline Error_condition
is_valid(const Meter_mod mm)
{
  if (Error_decl err = is_valid(mm.command))
    return err;
  if (Error_decl err = is_valid(mm.meter_id))
    return err;
  return is_valid(mm.meter_bands);
}

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
  construct(Payload& p, Port_mod::Tag, Args&&... args) {
    new (&p.data.port_mod) Port_mod(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Multipart_req::Tag, Args&&... args) {
    new (&p.data.multipart_req) Multipart_req(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Multipart_res::Tag, Args&&... args) {
    new (&p.data.multipart_res) Multipart_res(std::forward<Args>(args)...);
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

template<typename... Args>
  inline void
  construct(Payload& p, Role_req::Tag, Args&&... args) {
    new (&p.data.role_req) Role_req(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Role_res::Tag, Args&&... args) {
    new (&p.data.role_res) Role_res(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Meter_mod::Tag, Args&&... args) {
    new (&p.data.meter_mod) Meter_mod(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Get_async_req::Tag, Args&&... args) {
    new (&p.data.get_async_req) Get_async_req(std::forward<Args>(args)...);
  }

/*
template<typename... Args>
  inline void
  construct(Payload& p, Get_async_res::Tag, Args&&... args) {
    new (&p.data.get_async_res) Get_async_res(std::forward<Args>(args)...);
  }

template<typename... Args>
  inline void
  construct(Payload& p, Set_async::Tag, Args&&... args) {
    new (&p.data.set_async) Set_async(std::forward<Args>(args)...);
  }
*/

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

} // namespace v1_3
} // namespace ofp
} // namespace flog

#endif
