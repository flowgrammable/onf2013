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


#ifndef FLOWGRAMMABLE_PROTO_OFP_V1_2_IPP
#define FLOWGRAMMABLE_PROTO_OFP_V1_2_IPP

namespace flog {
namespace ofp {
namespace v1_2 {

// A helper facility for mapping various enumeration values with availability
// error codes. Specializations can be found throughout this file.

//template<typename T, T K> struct available_error;

// ------------------------------------------------------------------------- //
// OXM entry class

inline Error_condition
is_valid(const OXM_entry_class& c) {
  return ok(c == NXM_0 
         or c == NXM_1 
         or c == OPEN_FLOW_BASIC
         or c == OXM_EXPERIMENTER, BAD_OXM_CLASS);
}

// ------------------------------------------------------------------------- //
// OXM entry field

inline Error_condition
is_valid(OXM_entry_field f)
{
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
      or f == OXM_EF_MPLS_LABEL or f == OXM_EF_MPLS_TC, BAD_OXM_FIELD);
}

// -------------------------------------------------------------------------- //
// OXM entry payload: 8 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_VLAN_PCP> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_VLAN_PCP;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IP_DSCP> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IP_DSCP;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IP_ECN> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IP_ECN;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IP_PROTO> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IP_PROTO;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV4_TYPE> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ICMPV4_TYPE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV4_CODE> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ICMPV4_CODE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV6_TYPE> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ICMPV6_TYPE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ICMPV6_CODE> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ICMPV6_CODE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_MPLS_TC> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_MPLS_TC;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b)
  {
    return a.value == b.value;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base8<K>& a, const OXM_entry_base8<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base8<K>&) { return 1; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_base8<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base8<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;
    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base8<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload: 16 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_VLAN_VID> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_VLAN_VID;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_TYPE> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ETH_TYPE;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_TCP_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_TCP_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_TCP_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_TCP_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_UDP_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_UDP_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_UDP_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_UDP_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_SCTP_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_SCTP_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_SCTP_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_SCTP_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_OP> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_OP;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base16<K>& a, const OXM_entry_base16<K>& b)
  {
    return a.value == b.value;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base16<K>& a, const OXM_entry_base16<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base16<K>&) { return 2; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_base16<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base16<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base16<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;
    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 16 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_VLAN_VID_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_VLAN_VID_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base16_mask<K>& a,
             const OXM_entry_base16_mask<K>& b)
  {
    return a.value == b.value and a.mask == b.mask;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base16_mask<K>& a,
             const OXM_entry_base16_mask<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base16_mask<K>&) { return 4; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_base16_mask<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base16_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base16_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }


// -------------------------------------------------------------------------- //
// OXM entry payload: 32 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_IN_PORT> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IN_PORT;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IN_PHY_PORT> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IN_PHY_PORT;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_MPLS_LABEL> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_MPLS_LABEL;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_FLABEL> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_FLABEL;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base32<K>& a, const OXM_entry_base32<K>& b)
  {
    return a.value == b.value;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base32<K>& a, const OXM_entry_base32<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base32<K>&) { return 4; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_base32<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base32<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base32<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    return SUCCESS;
  }


// -------------------------------------------------------------------------- //
// OXM entry payload : in port

inline Error_condition is_valid(const OXM_entry_in_port& p)
{
  return ok(p.value < 0xFF00, BAD_OXM_EF_IN_PORT);
}

// -------------------------------------------------------------------------- //
// OXM entry payload : in phy port

inline Error_condition is_valid(const OXM_entry_in_phy_port& p)
{
  return ok(p.value < 0xFF00, BAD_OXM_EF_IN_PHY_PORT);
}

// -------------------------------------------------------------------------- //
// OXM entry payload: IPv4

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV4_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV4_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SPA> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_SPA;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_TPA> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_TPA;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv4<K>& a, const OXM_entry_ipv4<K>& b)
  {
    return a.value == b.value;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv4<K>& a, const OXM_entry_ipv4<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv4<K>&) { return 4; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_ipv4<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv4<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv4<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: 32 bits

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_FLABEL_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_FLABEL_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_base32_mask<K>& a,
             const OXM_entry_base32_mask<K>& b)
  {
    return a.value == b.value and a.mask == b.mask;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_base32_mask<K>& a,
             const OXM_entry_base32_mask<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_base32_mask<K>&) { return 8; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_base32_mask<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_base32_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_base32_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: IP

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_SRC_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV4_SRC_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV4_DST_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV4_DST_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SPA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_SPA_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_TPA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_TPA_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv4_mask<K>& a,
             const OXM_entry_ipv4_mask<K>& b)
  {
    return a.value == b.value and a.mask == b.mask;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv4_mask<K>& a,
             const OXM_entry_ipv4_mask<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv4_mask<K>&) { return 8; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_ipv4_mask<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv4_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv4_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }


// -------------------------------------------------------------------------- //
// OXM entry payload: ethernet

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ETH_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ETH_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SHA> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_SHA;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_THA> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_THA;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_ND_SLL> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_ND_SLL;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_ND_TLL> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_ND_TLL;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b)
  {
    return a.value == b.value;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ethernet<K>& a, const OXM_entry_ethernet<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ethernet<K>&) { return 6; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_ethernet<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ethernet<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ethernet<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    return SUCCESS;
  }


// -------------------------------------------------------------------------- //
// OXM entry payload with mask: Ethernet

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_SRC_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ETH_SRC_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ETH_DST_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ETH_DST_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_SHA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_SHA_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_ARP_THA_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_ARP_THA_MASK;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ethernet_mask<K>& a,
             const OXM_entry_ethernet_mask<K>& b)
  {
    return a.value == b.value and a.mask == b.mask;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ethernet_mask<K>& a,
             const OXM_entry_ethernet_mask<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ethernet_mask<K>&) { return 12; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_ethernet_mask<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ethernet_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ethernet_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload : metadata

inline bool
operator==(const OXM_entry_metadata& a, const OXM_entry_metadata& b)
{
  return a.value == b.value;
}

inline bool
operator!=(const OXM_entry_metadata& a, const OXM_entry_metadata& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const OXM_entry_metadata&) { return 8; }

inline Error_condition
is_valid(const OXM_entry_metadata&) { return SUCCESS; }


// -------------------------------------------------------------------------- //
// OXM entry payload : metadata mask

inline bool
operator==(const OXM_entry_metadata_mask& a,
           const OXM_entry_metadata_mask& b)
{
  return a.value == b.value and a.mask == b.mask;
}

inline bool
operator!=(const OXM_entry_metadata_mask& a,
           const OXM_entry_metadata_mask& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const OXM_entry_metadata_mask&) { return 16; }

inline Error_condition
is_valid(const OXM_entry_metadata_mask&) { return SUCCESS; }


// -------------------------------------------------------------------------- //
// OXM entry payload: IPv6

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_SRC> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_SRC;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_DST> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_DST;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_ND_TARGET> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_ND_TARGET;
  };

template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv6<K>& a, const OXM_entry_ipv6<K>& b)
  {
    return a.value == b.value;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv6<K>& a, const OXM_entry_ipv6<K>& b)
  {
    return !(a == b);
  }

template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv6<K>&) { return 16; }

template<OXM_entry_field K>
  inline Error_condition
  is_valid(const OXM_entry_ipv6<K>&) { return SUCCESS; }

template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv6<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv6<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    return SUCCESS;
  }

// -------------------------------------------------------------------------- //
// OXM entry payload with mask: IPv6

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_SRC_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_SRC_MASK;
  };

template<>
  struct available_error<OXM_entry_field, OXM_EF_IPV6_DST_MASK> {
    static constexpr Error_condition value = AVAILABLE_OXM_EF_IPV6_DST_MASK;
  };

// Equality comparison
template<OXM_entry_field K>
  inline bool
  operator==(const OXM_entry_ipv6_mask<K>& a,
             const OXM_entry_ipv6_mask<K>& b)
  {
    return a.value == b.value and a.mask == b.mask;
  }

template<OXM_entry_field K>
  inline bool
  operator!=(const OXM_entry_ipv6_mask<K>& a,
             const OXM_entry_ipv6_mask<K>& b)
  {
    return !(a == b);
  }

// Bytes
template<OXM_entry_field K>
  inline std::size_t
  bytes(const OXM_entry_ipv6_mask<K>&) { return 32; }

// To/from buffer
template<OXM_entry_field K>
  inline Error_condition
  to_buffer(Buffer_view& v, const OXM_entry_ipv6_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    to_buffer(v, b.value);
    to_buffer(v, b.mask);
    return SUCCESS;
  }

template<OXM_entry_field K>
  inline Error_condition
  from_buffer(Buffer_view& v, OXM_entry_ipv6_mask<K>& b)
  {
    if (not available(v, bytes(b)))
      return available_error<OXM_entry_field, K>::value;

    from_buffer(v, b.value);
    from_buffer(v, b.mask);
    return SUCCESS;
  }


// -------------------------------------------------------------------------- //
// OXM Experimenter

// Equality comparison
inline bool
operator==(const OXM_experimenter& a, const OXM_experimenter& b)
{
  return a.experimenter == b.experimenter;
}

inline bool
operator!=(const OXM_experimenter& a, const OXM_experimenter& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const OXM_experimenter&) { return 4; }


// -------------------------------------------------------------------------- //
// OXM entry: Header

inline bool
operator==(const OXM_entry_header& a, const OXM_entry_header& b)
{
  return a.oxm_class == b.oxm_class and a.field == b.field and
         a.length == b.length;
}

inline bool
operator!=(const OXM_entry_header& a, const OXM_entry_header& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const OXM_entry_header& h) { return 4; }

inline Error_condition
is_valid(const OXM_entry_header& e)
{
  if(Error_decl err =  is_valid(e.oxm_class))
    return err;
  return is_valid(e.field);
}

// ----------------------------------------------------------------------- //
// OXM

inline
OXM_entry::OXM_entry(OXM_entry&& x)
  : header(std::move(x.header))
{
  if (header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    construct(payload, std::move(x.payload), header.field);
  else
    payload = std::move(x.payload);
}

inline OXM_entry&
OXM_entry::operator=(OXM_entry&& x)
{
  header = std::move(x.header);
  if (header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    assign(payload, std::move(x.payload), header.field);
  else
    payload = std::move(x.payload);
  return *this;
}

inline
OXM_entry::OXM_entry(const OXM_entry& x)
  : header(x.header)
{
  if (x.header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    construct(payload, x.payload, header.field);
  else
    payload = x.payload;
}

inline OXM_entry&
OXM_entry::operator=(const OXM_entry& x)
{
  header = x.header;
  if (x.header.oxm_class != OXM_entry_class::OXM_EXPERIMENTER)
    assign(payload, x.payload, header.field);
  else
    payload = x.payload;
  return *this;
}

// Equality comparison
inline bool
operator==(const OXM_entry& a, const OXM_entry& b)
{
  return a.header == b.header
     and ((a.header.oxm_class == OXM_entry_class::OXM_EXPERIMENTER
     and a.experimenter == b.experimenter)
      or equal(a.payload, b.payload, a.header.field, b.header.field));
}

inline bool
operator!=(const OXM_entry& a, const OXM_entry& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const OXM_entry& a)
{
  if (a.header.oxm_class == OXM_entry_class::OXM_EXPERIMENTER)
    return 4 + bytes(a.experimenter);
  else
    return 4 + bytes(a.payload, a.header.field);
}

// Is_valid
inline Error_condition
is_valid(const OXM_entry& e)
{
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
  uint64_t flag = 0x000000000000007D;

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
                | OXM_entry_field_flag(OXM_EF_IPV6_FLABEL));
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
                | OXM_entry_field_flag(OXM_EF_MPLS_TC) );
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

// To/from buffer
Error_condition to_buffer(Buffer_view&, const OXM_entry&);
Error_condition from_buffer(Buffer_view&, OXM_entry&);

// To string
std::string to_string(const OXM_entry&, Formatter&);

// -------------------------------------------------------------------------- //
// Match

// Equality comparison
inline bool
operator==(const Match& a, const Match& b)
{
  return a.type == b.type
     and a.length == b.length
     and a.rules == b.rules;
}

inline bool
operator!=(const Match& a, const Match& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Match& m)
{
  std::size_t before_pad = bytes(m.rules)+4;
  uint8_t padding = before_pad % 8;

  if (padding != 0)
    padding = 8 - padding;

  return before_pad+padding;
}

inline Error_condition
is_valid(const Match::Type_value t){
  return ok(t==Match::MT_OXM,BAD_MATCH_TYPE);
}

inline Error_condition
is_valid(const Match& m) {

  if (Error_decl err = is_valid(m.type))
    return err;
  return is_valid(m.rules);
}


// -------------------------------------------------------------------------- //
// Action type

inline Error_condition 
is_valid(const Action_type at)
{
  return ok(at == ACTION_OUTPUT
      or at == ACTION_COPY_TTL_OUT or at == ACTION_COPY_TTL_IN
      or (ACTION_SET_MPLS_TTL <= at and at <= ACTION_SET_FIELD)
      or at == ACTION_EXPERIMENTER, BAD_ACTION);
}

// -------------------------------------------------------------------------- //
// Action output

inline bool
operator==(const Action_output& a, const Action_output& b)
{
  return a.port == b.port and b.max_len == b.max_len;
}

inline bool
operator!=(const Action_output& a, const Action_output& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Action_output&) { return 12; }

inline Error_condition
is_valid(const Action_output& a) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Action: Copy ttl out

inline std::size_t
bytes(const Action_copy_ttl_out&) { return 4; }

// -------------------------------------------------------------------------- //
// Action: Copy ttl in

inline std::size_t
bytes(const Action_copy_ttl_in&) { return 4; }

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
  operator==(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b)
  {
  return a.mpls_ttl == b.mpls_ttl;
  }

template <Action_type K>
  inline bool
  operator!=(const Action_mpls_ttl<K>& a, const Action_mpls_ttl<K>& b)
  {
  return !(a == b);
  }

template <Action_type K>
  inline std::size_t
  bytes(const Action_mpls_ttl<K>&) { return 4; }

template<Action_type K>
  inline Error_condition
  is_valid(const Action_mpls_ttl<K>&) { return SUCCESS; }

template <Action_type K>
  Error_condition
  to_buffer(Buffer_view& v, const Action_mpls_ttl<K>& mt)
  {
    if (not available(v, bytes(mt)))
      return available_error<Action_type, K>::value;

    to_buffer(v, mt.mpls_ttl);
    pad(v, 3);

    return SUCCESS;
  }

template <Action_type K>
  Error_condition
  from_buffer(Buffer_view& v, Action_mpls_ttl<K>& mt)
  {
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
  operator==(const Action_push_pop<K>& a, const Action_push_pop<K>& b)
  {
    return a.ether_type == b.ether_type;
  }

template <Action_type K>
  inline bool
  operator!=(const Action_push_pop<K>& a, const Action_push_pop<K>& b)
  {
    return !(a == b);
  }

template <Action_type K>
  inline std::size_t
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
operator==(const Action_set_queue& a, const Action_set_queue& b)
{
  return a.queue_id == b.queue_id;
}

inline bool
operator!=(const Action_set_queue& a, const Action_set_queue& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Action_set_queue&) { return 4; }

inline Error_condition
is_valid(const Action_set_queue&) { return SUCCESS; }


// -------------------------------------------------------------------------- //
// Action: Group

inline bool
operator==(const Action_group& a, const Action_group& b)
{
  return a.group_id == b.group_id;
}

inline bool
operator!=(const Action_group& a, const Action_group& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Action_group&) { return 4; }

inline Error_condition
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
  operator==(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b)
{
  return a.nw_ttl == b.nw_ttl;
}

template <Action_type K>
inline bool
  operator!=(const Action_nw_ttl<K>& a, const Action_nw_ttl<K>& b)
{
  return !(a == b);
}

template <Action_type K>
  inline std::size_t
  bytes(const Action_nw_ttl<K>& nt) { return 4; }

template<Action_type K>
  inline Error_condition
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

// Equality comparison
inline bool
operator==(const Action_set_field& a, const Action_set_field& b)
{
  return a.oxm == b.oxm;
}

inline bool
operator!=(const Action_set_field& a, const Action_set_field& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Action_set_field& asf) {
  std::size_t before_pad = bytes(asf.oxm)+4;
  uint8_t padding = before_pad % 8;
  if(padding!=0) padding=8-padding;
  return before_pad-4+padding;
}

inline Error_condition
is_valid(const Action_set_field& asf) { return is_valid(asf.oxm); }

// -------------------------------------------------------------------------- //
// Action: Experimenter

// Equality comparison
inline bool
operator==(const Action_experimenter& a, const Action_experimenter& b)
{
  return a.experimenter == b.experimenter;
}

inline bool
operator!=(const Action_experimenter& a, const Action_experimenter& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Action_experimenter&) { return 4; }

inline Error_condition
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


// -------------------------------------------------------------------------- //
// Action header

// Equality comparison
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

// Bytes
inline std::size_t
bytes(const Action_header&) { return 4; }

inline Error_condition
is_valid(const Action_header& h)
{
  if ( h.length >= bytes(h))
    return SUCCESS;
  else
    return BAD_ACTION_LENGTH;

}

// -------------------------------------------------------------------------- //
// Action

inline
Action::Action(const Action& x)
  : header(x.header)
{
  construct(payload, x.payload, header.type);
}

inline Action&
Action::operator=(const Action& x)
{
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

// Equality comparison
inline bool
operator==(const Action& a, const Action& b)
{
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Action& a, const Action& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Action& a)
{
  return bytes(a.header) + bytes(a.payload, a.header.type);
}

inline Error_condition
is_valid(const Action& a)
{ return is_valid(a.payload, a.header.type); }

// -------------------------------------------------------------------------- //
// Instruction type

inline Error_condition
is_valid(const Instruction_type it)
{
  return ok((INSTRUCTION_GOTO_TABLE <= it and it <= INSTRUCTION_CLEAR_ACTIONS)
      or it == INSTRUCTION_EXPERIMENTER, BAD_INSTRUCTION);
}

// -------------------------------------------------------------------------- //
// Instruction: Goto table

// Equality comparison
inline bool
operator==(const Instruction_goto_table& a, const Instruction_goto_table& b)
{
  return a.table_id == b.table_id;
}

inline bool
operator!=(const Instruction_goto_table& a, const Instruction_goto_table& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Instruction_goto_table&) { return 4; }

inline Error_condition
is_valid(const Instruction_goto_table&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Instruction: Goto write metadata

// Equality comparison
inline bool
operator==(const Instruction_write_metadata& a,
           const Instruction_write_metadata& b)
{
  return a.metadata == b.metadata and a.metadata_mask == b.metadata_mask;
}

inline bool
operator!=(const Instruction_write_metadata& a,
           const Instruction_write_metadata& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Instruction_write_metadata&) { return 20; }

inline Error_condition
is_valid(const Instruction_write_metadata&) { return SUCCESS; }

Error_condition to_buffer(Buffer_view&, const Instruction_write_metadata&);
Error_condition from_buffer(Buffer_view&, Instruction_write_metadata&);

std::string to_string(const Instruction_write_metadata&, Formatter&);

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
  operator==(const Instruction_action<K>& a, const Instruction_action<K>& b)
  {
    return a.actions == b.actions;
  }

template <Instruction_type K>
  inline bool
  operator!=(const Instruction_action<K>& a, const Instruction_action<K>& b)
  {
    return !(a == b);
  }

template <Instruction_type K>
  std::size_t bytes(const Instruction_action<K>& ia)
  {
    return 4 + bytes(ia.actions);
  }

template<Instruction_type K>
  inline Error_condition
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

// Equality comparison
inline bool
operator==(const Instruction_experimenter& a,
           const Instruction_experimenter& b)
{
  return a.experimenter_id == b.experimenter_id;
}

inline bool
operator!=(const Instruction_experimenter& a,
           const Instruction_experimenter& b)
{
  return !(a == b);
}

inline std::size_t
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

// Equality comparison
inline bool
operator==(const Instruction_header& a, const Instruction_header& b)
{
  return a.type == b.type and a.length == b.length;
}

inline bool
operator!=(const Instruction_header& a, const Instruction_header& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Instruction_header&) { return 4; }

inline Error_condition
is_valid(const Instruction_header& h)
{
  if (h.length >= bytes(h))
    return SUCCESS;
  else
    return BAD_INSTRUCTION_LENGTH;
}

Error_condition to_buffer(Buffer_view&, const Instruction_header&);
Error_condition from_buffer(Buffer_view&, Instruction_header&);

std::string to_string(const Instruction_header&, Formatter&);


// -------------------------------------------------------------------------- //
// Instruction

inline
Instruction::~Instruction()
{
  destroy(payload, header.type);
}

inline
Instruction::Instruction(Instruction&& x)
  : header(std::move(x.header))
{
  construct(payload, std::move(x.payload), header.type);
}

inline
Instruction::Instruction(const Instruction& x)
  : header(x.header)
{
  construct(payload, x.payload, header.type);
}

inline Instruction&
Instruction::operator=(Instruction&& x)
{
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline Instruction&
Instruction::operator=(const Instruction& x)
{
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

// Equality comparison
inline bool
operator==(const Instruction& a, const Instruction& b)
{
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Instruction& a, const Instruction& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Instruction& a)
{
  return bytes(a.header) + bytes(a.payload, a.header.type);
}

inline Error_condition
is_valid(const Instruction& a) { return is_valid(a.payload, a.header.type); }

inline Error_condition
is_valid(const Sequence<Instruction> i)
{
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

// Equality comparison
inline bool
operator==(const Port& a, const Port& b)
{
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
operator!=(const Port& a, const Port& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Port&) { return 64; }

inline Error_condition
is_valid(const Port::Id_value id)
{
  return ok(id <= 0xffffff00 or id >= 0xfffffff8, BAD_PORT_ID);
}

inline Error_condition
is_valid(const Port::Config_value) { return SUCCESS; }

inline Error_condition
is_valid(const Port::State_value) { return SUCCESS; }

inline Error_condition
is_valid(const Port::Features_value) { return SUCCESS; }

inline Error_condition
is_valid(const Port& p)
{
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
port_feature_40gb_fd(uint32_t p) { return p & Port::FOURTY_GB_FD; }

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

inline Error_condition
is_valid(const Queue_property_type t)
{
  return ok((QUEUE_PROPERTY_MIN_RATE <= t and t <= QUEUE_PROPERTY_MAX_RATE)
      or t == QUEUE_PROPERTY_EXPERIMENTER, BAD_QUEUE_PROPERTY);
}

// -------------------------------------------------------------------------- //
// Queue property: Min rate

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

//Bytes
inline std::size_t
bytes(const Queue_property_min_rate&) { return 8; }

// Is valid
inline Error_condition
is_valid(const Queue_property_min_rate&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Queue property: Max rate

// Equality comparison
inline bool
operator==(const Queue_property_max_rate& a, const Queue_property_max_rate& b)
{
  return a.rate == b.rate;
}

inline bool
operator!=(const Queue_property_max_rate& a, const Queue_property_max_rate& b)
{
  return !(a == b);
}

//Bytes
inline std::size_t
bytes(const Queue_property_max_rate&) { return 8; }

// -------------------------------------------------------------------------- //
// Queue property: Experimenter

// Equality comparison
inline bool
operator==(const Queue_property_experimenter& a, const Queue_property_experimenter& b)
{
  return a.experimenter == b.experimenter and a.data == b.data;
}

inline bool
operator!=(const Queue_property_experimenter& a, const Queue_property_experimenter& b)
{
  return !(a == b);
}

//Bytes
inline std::size_t
bytes(const Queue_property_experimenter& e) { return 8 + bytes(e.data); }

inline Error_condition
is_valid(const Queue_property_experimenter& e) { return SUCCESS; }


// -------------------------------------------------------------------------- //
// Queue property header

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

//Bytes
inline std::size_t
bytes(const Queue_property_header&) { return 8; }

inline Error_condition
is_valid(const Queue_property_header& h)
{
  if (Error_decl err = is_valid(h.property))
    return err;
  return ok(bytes(h) <= h.length,BAD_QUEUE_PROPERTY_LENGTH);

}

// -------------------------------------------------------------------------- //
// Queue property

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

// Equality comparison
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
  return bytes(p.header) + bytes(p.payload, p.header.property);
}

// -------------------------------------------------------------------------- //
// Queue

// Equality comparison
inline bool
operator==(const Queue& a, const Queue& b)
{
  return a.queue_id == b.queue_id
     and a.port == b.port
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
bytes(const Queue& q)
{
  return 16 + bytes(q.properties);
}

// -------------------------------------------------------------------------- //
// Bucket

// Equality comparison
inline bool
operator==(const Bucket& a, const Bucket& b)
{
  return a.len == b.len
     and a.weight == b.weight
     and a.watch_port == b.watch_port
     and a.watch_group == b.watch_group
     and a.actions == b.actions;
}

inline bool
operator!=(const Bucket& a, const Bucket& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Bucket& b) { return 16 + bytes(b.actions); }

// Is valid
inline Error_condition
is_valid(const Bucket& b) { return is_valid(b.actions); }


// -------------------------------------------------------------------------- //
// Bucket Counter

// Equality comparison
inline bool
operator==(const Bucket_counter& a, const Bucket_counter& b)
{
  return a.packet_count == b.packet_count
     and a.byte_count == b.byte_count;
}

inline bool
operator!=(const Bucket_counter& a, const Bucket_counter& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Bucket_counter&) { return 16; }

// ------------------------------------------------------------------------- //
// Messages

// -------------------------------------------------------------------------- //
// Version Type

// Is valid
inline Error_condition
is_valid(const Version_type t) { return ok(t == VERSION, BAD_VERSION); }

// -------------------------------------------------------------------------- //
// Message Type

/// Returns true if n is a valid value of Message_type.
inline Error_condition
is_valid(const Message_type t)
{
  return ok(HELLO <= t and t <= ROLE_RES, BAD_MESSAGE);
}

// -------------------------------------------------------------------------- //
// Hello

// Equality comparison
inline bool
operator==(const Hello& a, const Hello& b)
{
  return a.data == b.data;
}

// Equality comparison
inline bool
operator!=(const Hello& a, const Hello& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Hello& h) { return bytes(h.data); }

// Is valid
inline Error_condition
is_valid(const Hello& h) { return SUCCESS; }

// ------------------------------------------------------------------------- //
// Error

// Equality comparison
inline bool
operator==(const Error& a, const Error& b)
{
  return a.type == b.type
     and a.code.value == b.code.value
     and (a.type != Error::EXPERIMENTER or
          a.experimenter_id == b.experimenter_id)
     and a.data == b.data;
}

inline bool
operator!=(const Error& a, const Error& b) { return !(a == b); }

// Bytes
inline std::size_t
bytes(const Error& e)
{
  if (e.type == Error::EXPERIMENTER)
    return 8 + bytes(e.data);
  else
    return 4 + bytes(e.data);
}

// Is valid
inline Error_condition
is_valid(const Error::Type t) 
{ 
  return ok((Error::HELLO_FAILED <= t and t <= Error::ROLE_REQUEST_FAILED)
      or t == Error::EXPERIMENTER, BAD_ERROR_TYPE);
}

inline Error_condition
is_valid(const Error::Hello_failed c) 
{ 
  return ok(c == Error::HF_INCOMPATIBLE || c == Error::HF_EPERM,
            BAD_HELLO_FAILED);
}

inline Error_condition
is_valid(const Error::Bad_request c) 
{ 
  return ok(Error::BR_BAD_VERSION <= c and c <= Error::BR_BAD_PACKET,
            BAD_BAD_REQUEST);
}

inline Error_condition
is_valid(const Error::Bad_action c) 
{ 
  return ok(Error::BA_BAD_TYPE <= c and c <= Error::BA_BAD_SET_ARGUMENT,
            BAD_BAD_ACTION);
}

inline Error_condition
is_valid(const Error::Bad_instruction c) 
{ 
  return ok(Error::BI_UNKNOWN_INST <= c and c <= Error::BI_EPERM,
            BAD_BAD_INSTRUCTION);
}

inline Error_condition
is_valid(const Error::Bad_match c) 
{ 
  return ok(Error::BM_BAD_TYPE <= c and c <= Error::BM_EPERM,
            BAD_BAD_MATCH);
}

inline Error_condition
is_valid(const Error::Flow_mod_failed c) 
{ 
  return ok(Error::FMF_UNKNOWN <= c and c <= Error::FMF_BAD_FLAGS,
            BAD_FLOW_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Group_mod_failed c) 
{ 
  return ok(Error::GMF_GROUP_EXISTS <= c and c <= Error::GMF_EPERM,
            BAD_GROUP_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Port_mod_failed c) 
{ 
  return ok(c == Error::PMF_BAD_PORT or c == Error::PMF_EPERM,
            BAD_PORT_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Table_mod_failed c) 
{ 
  return ok(c == Error::TMF_BAD_TABLE or c == Error::TMF_EPERM,
            BAD_TABLE_MOD_FAILED);
}

inline Error_condition
is_valid(const Error::Queue_op_failed c) 
{ 
  return ok(Error::QOF_BAD_PORT <= c and c <= Error::QOF_EPERM,
            BAD_QUEUE_OP_FAILED);
}

inline Error_condition
is_valid(const Error::Switch_config_failed c) 
{ 
  return ok(Error::SCF_BAD_FLAGS <= c and c <= Error::SCF_EPERM,
            BAD_SWITCH_CONFIG_FAILED);
}

inline Error_condition
is_valid(const Error::Role_request_failed c) 
{ 
  return ok(Error::RRF_STALE <= c and c <= Error::RRF_BAD_ROLE,
            BAD_ROLE_REQUEST_FAILED);
}

inline Error_condition
is_valid(const Error::Type t, Error::Code c)
{
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
  default: return BAD_ERROR_TYPE;
  };
}

inline Error_condition
is_valid(const Error& e) { return is_valid(e.type, e.code); }


// -------------------------------------------------------------------------- //
// Echo Base

// Equality comparable
template<Message_type K>
  inline bool
  operator==(const Echo_base<K>& a, const Echo_base<K>& b)
  {
    return a.data == b.data;
  }

template<Message_type K>
  inline bool
  operator!=(const Echo_base<K>& a, const Echo_base<K>& b)
  {
    return !(a == b);
  }

// Bytes
template<Message_type K>
  inline std::size_t
  bytes(const Echo_base<K>& e) { return e.data.size(); }

// Is valid
template<Message_type K>
  inline Error_condition
  is_valid(const Echo_base<K>&) { return SUCCESS; }

// To/from buffer
template<Message_type K>
  inline Error_condition
  to_buffer(Buffer_view& v, const Echo_base<K>& e)
  {
    return to_buffer(v, e.data);
  }

template<Message_type K>
  inline Error_condition
  from_buffer(Buffer_view& v, Echo_base<K>& e)
  {
    return from_buffer(v, e.data);
  }

// To string
template<Message_type K>
  inline std::string
  to_string(const Echo_base<K>& e, Formatter& f)
  {
    return to_string(e.data, f);
  }

// -------------------------------------------------------------------------- //
// Experimenter

// Equality comparison
inline bool
operator==(const Experimenter& a, const Experimenter& b)
{
  return a.experimenter_id == b.experimenter_id
     and a.experimenter_type == b.experimenter_type
     and a.data == b.data;
}

inline bool
operator!=(const Experimenter& a, const Experimenter& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Experimenter& e) { return 8 + bytes(e.data); }

inline Error_condition
is_valid(const Experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Feature Response

// Equality comparable

inline bool
operator==(const Feature_res& a, const Feature_res& b)
{
  return a.datapath_id == b.datapath_id
     and a.n_buffers == b.n_buffers
     and a.n_tbls == b.n_tbls
     and a.capabilities == b.capabilities
     and a.reserved == b.reserved
     and a.ports == b.ports;
}

inline bool
operator!=(const Feature_res& a, const Feature_res& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Feature_res& fr) { return 24 + bytes(fr.ports); }

// is_valid
inline Error_condition
is_valid(const Feature_res::Capability_type& c)
{
  return SUCCESS;
  //return 0x00000000 == (c & 0x00000010);
}

inline Error_condition
is_valid(const Feature_res& fr)
{
  if (Error_decl err = is_valid(fr.capabilities))
     return err;
  return is_valid(fr.ports);
}

inline bool
feature_res_capabilities_flow_stats(uint32_t c)
{
  return c & Feature_res::FLOW_STATS;
}

inline bool
feature_res_capabilities_table_stats(uint32_t c)
{
  return c & Feature_res::TABLE_STATS;
}

inline bool
feature_res_capabilities_port_stats(uint32_t c)
{
  return c & Feature_res::PORT_STATS;
}

inline bool
feature_res_capabilities_group_stats(uint32_t c)
{
  return c & Feature_res::GROUP_STATS;
}

inline bool
feature_res_capabilities_ip_reasm(uint32_t c)
{
  return c & Feature_res::IP_REASM;
}

inline bool
feature_res_capabilities_queue_stats(uint32_t c)
{
  return c & Feature_res::QUEUE_STATS;
}

inline bool
feature_res_capabilities_port_blocked(uint32_t c)
{
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

// Equality comparison
template<Message_type T>
  inline bool
  operator==(const Config_message_base<T>& a, const Config_message_base<T>& b)
  {
    return a.flags == b.flags and a.miss_send_len == b.miss_send_len;
  }

template<Message_type T>
  inline bool
  operator!=(const Config_message_base<T>& a, const Config_message_base<T>& b)
  {
    return !(a == b);
  }

// Bytes
template<Message_type T>
  inline std::size_t
  bytes(const Config_message_base<T>&) { return 4; }

template<Message_type T>
  inline Error_condition
  is_valid(const Config_message_base<T>& c)
  {
    return ok(c.flags <= 0x0004, BAD_CONFIG_FLAGS);
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
  config_frag_normal(typename Config_message_base<T>::Flag_type ft)
  { return ft & Config_message_base<T>::FRAG_NORMAL; }

template<Message_type T>
  inline bool
  config_frag_drop(typename Config_message_base<T>::Flag_type ft)
  { return ft & Config_message_base<T>::FRAG_DROP; }

template<Message_type T>
  inline bool
  config_frag_reasm(typename Config_message_base<T>::Flag_type ft)
  { return ft & Config_message_base<T>::FRAG_REASM; }

template<Message_type T>
  inline bool
  config_invalid_ttl_to_controller(typename Config_message_base<T>::Flag_type
                                            ft)
  { return ft & Config_message_base<T>::INVALID_TTL_TO_CONTROLLER; }


// -------------------------------------------------------------------------- //
// Packet In

// Equality comparison
inline bool
operator==(const Packet_in& a, const Packet_in& b)
{
  return a.buffer_id == b.buffer_id
     and a.total_len == b.total_len
     and a.reason == b.reason
     and a.tbl_id == b.tbl_id
     and a.match == b.match
     and a.data == b.data;
}

inline bool
operator!=(const Packet_in& a, const Packet_in& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Packet_in& pi) { return 10 + bytes(pi.match) + bytes(pi.data); }

// Is valid
inline Error_condition
is_valid(const Packet_in::Reason_type r)
{
  return ok(r <= Packet_in::INVALID_TTL, BAD_PACKET_IN_REASON);
}

inline Error_condition
is_valid(const Packet_in& p)
{
  if(Error_decl err = is_valid(p.reason))
    return err;
  return is_valid(p.match);
}

// -------------------------------------------------------------------------- //
// Flow Removed

// Equality Comparable
inline bool
operator==(const Flow_removed& a, const Flow_removed& b)
{
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
operator!=(const Flow_removed& a, const Flow_removed& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Flow_removed& fr) { return bytes(fr.match) + 40; }

// Is valid
inline Error_condition
is_valid(const Flow_removed::Reason_type r)
{
  return ok(r <= Flow_removed::GROUP_DELETE, BAD_FLOW_REMOVED_REASON);
}

inline Error_condition
is_valid(const Flow_removed& f)
{
  if(Error_decl err = is_valid(f.reason))
    return err;
  return is_valid(f.match);
}

// -------------------------------------------------------------------------- //
// Port Status

// Equality comparison
inline bool
operator==(const Port_status& a, const Port_status& b)
{
  return a.reason == b.reason and a.port == b.port;
}

inline bool
operator!=(const Port_status& a, const Port_status& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Port_status& ps) { return 8 + bytes(ps.port); }

// Is valid
inline Error_condition
is_valid(const Port_status::Reason_type r)
{
  return ok(r <= Port_status::MODIFY, BAD_PORT_STATUS_REASON);
}

inline Error_condition
is_valid(const Port_status& p)
{
  if(Error_decl err = is_valid(p.reason))
    return err;
  return is_valid(p.port);
}

// -------------------------------------------------------------------------- //
// Packet Out

// Equality comparison
inline bool
operator==(const Packet_out& a, const Packet_out& b)
{
  return a.buffer_id == b.buffer_id
     and a.in_port == b.in_port
     and a.actions_len == b.actions_len
     and a.actions == b.actions
     and a.data == b.data;
}

inline bool
operator!=(const Packet_out& a, const Packet_out& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Packet_out& po)
{
  return 16 + bytes(po.actions) + bytes(po.data);
}

// Is valid
inline Error_condition
is_valid(const Packet_out& p) { return is_valid(p.actions); }


// -------------------------------------------------------------------------- //
// Flow_mod

// Equality comparison
inline bool
operator==(const Flow_mod& a, const Flow_mod& b)
{
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
operator!=(const Flow_mod& a, const Flow_mod& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Flow_mod& fm)
{
  return 40 + bytes(fm.match) + bytes(fm.instructions);
}

// Is Valid
inline Error_condition
is_valid(const Flow_mod::Command_type t)
{
  return ok(t <= Flow_mod::DELETE_STRICT, BAD_FLOW_MOD_COMMAND);
}

inline Error_condition
is_valid(const Flow_mod::Command_type c, const uint8_t table_id) {

  if( table_id == 0xFF and c < Flow_mod::DELETE)
    return BAD_FLOW_MOD_COMMAND;
  else
    return SUCCESS;
}

inline Error_condition
is_valid(const Flow_mod::Flag_type t)
{
  return ok(t <= (Flow_mod::SEND_FLOW_REM | Flow_mod::CHECK_OVERLAP |
               Flow_mod::RESET_COUNTS), BAD_FLOW_MOD_FLAGS);
  return SUCCESS;
}

inline Error_condition
is_valid(const Flow_mod& f)
{
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

// Equality comparison
inline bool
operator==(const Group_mod& a, const Group_mod& b)
{
  return a.command == b.command
     and a.type == b.type
     and a.group_id == b.group_id
     and a.buckets == b.buckets;
}

inline bool
operator!=(const Group_mod& a, const Group_mod& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Group_mod& gm) { return 8 + bytes(gm.buckets); }

// Is valid
inline Error_condition
is_valid(const Group_mod::Command_type c)
{
  return ok(c <= Group_mod::DELETE, BAD_GROUP_MOD_COMMAND);
}

inline Error_condition
is_valid(const Group_mod::Type_value v)
{
  return ok(v <= Group_mod::FF, BAD_GROUP_MOD_TYPE);
}

inline Error_condition
is_valid(const Group_mod& gm)
{
  if (Error_decl err = is_valid(gm.command))
    return err;
  if (Error_decl err = is_valid(gm.type))
    return err;
  return is_valid(gm.buckets);

}

// -------------------------------------------------------------------------- //
// Port Mod

// Equality comparison
inline bool
operator==(const Port_mod& a, const Port_mod& b)
{
  return a.port == b.port
     and a.hw_addr == b.hw_addr
     and a.config == b.config
     and a.mask == b.mask
     and a.advertise == b.advertise;
}

inline bool
operator!=(const Port_mod& a, const Port_mod& b)
{
  return a != b;
}

// Bytes
inline std::size_t
bytes(const Port_mod&) { return 32; }

inline Error_condition
is_valid(const Port_mod& p) { return SUCCESS; }

inline bool
port_mod_config_port_down(uint32_t c)
{
  return c & Port_mod::PORT_DOWN;
}

inline bool
port_mod_config_no_recv(uint32_t c)
{
  return c & Port_mod::NO_RECV;
}

inline bool
port_mod_config_no_fwd(uint32_t c)
{
  return c & Port_mod::NO_FWD;
}

inline bool
port_mod_config_no_packet_in(uint32_t c)
{
  return c & Port_mod::NO_PACKET_IN;
}

inline bool
port_mod_features_10mb_hd(uint32_t f)
{
  return f & Port_mod::TEN_MB_HD;
}

inline bool
port_mod_features_10mb_fd(uint32_t f)
{
  return f & Port_mod::TEN_MB_FD;
}

inline bool
port_mod_features_100mb_hd(uint32_t f)
{
  return f & Port_mod::HUNDRED_MB_HD;
}

inline bool
port_mod_features_100mb_fd(uint32_t f)
{
  return f & Port_mod::HUNDRED_MB_FD;
}

inline bool
port_mod_features_1gb_hd(uint32_t f)
{
  return f & Port_mod::ONE_GB_HD;
}

inline bool
port_mod_features_1gb_fd(uint32_t f)
{
  return f & Port_mod::ONE_GB_FD;
}

inline bool
port_mod_features_10gb_fd(uint32_t f)
{
  return f & Port_mod::TEN_GB_FD;
}

inline bool
port_mod_features_40gb_fd(uint32_t f)
{
  return f & Port_mod::FOURTY_GB_FD;
}

inline bool
port_mod_features_100gb_fd(uint32_t f)
{
  return f & Port_mod::HUNDRED_GB_FD;
}

inline bool
port_mod_features_1tb_fd(uint32_t f)
{
  return f & Port_mod::ONE_TB_FD;
}

inline bool
port_mod_features_other(uint32_t f)
{
  return f & Port_mod::OTHER;
}

inline bool
port_mod_features_copper(uint32_t f)
{
  return f & Port_mod::COPPER;
}

inline bool
port_mod_features_fiber(uint32_t f)
{
  return f & Port_mod::FIBER;
}

inline bool
port_mod_features_auto_neg(uint32_t f)
{
  return f & Port_mod::AUTO_NEG;
}

inline bool
port_mod_features_pause(uint32_t f)
{
  return f & Port_mod::PAUSE;
}

inline bool
port_mod_features_pause_asym(uint32_t f)
{
  return f & Port_mod::PAUSE_ASYM;
}

// -------------------------------------------------------------------------- //
// Table Mod

// Equality comparison
inline bool
operator==(const Table_mod& a, const Table_mod& b)
{
  return a.table_id == b.table_id
     and a.config == b.config;
}

inline bool
operator!=(const Table_mod& a, const Table_mod& b)
{
  return a != b;
}

// Bytes
inline std::size_t
bytes(const Table_mod&) { return 8; }

inline Error_condition
is_valid(const Table_mod::Config_type c)
{
  return ok(c <= Table_mod::MISS_MASK, BAD_TABLE_MOD_CONFIG);
}

inline Error_condition
is_valid(const Table_mod tm) { return is_valid(tm.config); }

// -------------------------------------------------------------------------- //
// Stats type

// Returns true whe t is a valid stats request value.
inline Error_condition
is_valid(const Stats_type t)
{
  return ok((STATS_DESC <= t and t <= STATS_GROUP_FEATURES)
            or t == STATS_EXPERIMENTER, BAD_STATS_TYPE);
}

// -------------------------------------------------------------------------- //
// Stats Request Flow Base

template<>
  struct available_error<Stats_type, STATS_FLOW> {
    static constexpr Error_code value = AVAILABLE_STATS_REQ_FLOW;
  };

template<>
  struct available_error<Stats_type, STATS_AGGREGATE> {
    static constexpr Error_code value = AVAILABLE_STATS_REQ_AGGREGATE;
  };

// Equality comparison
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
  {
    return !(a == b);
  }

// Bytes
template<Stats_type K>
  inline std::size_t
  bytes(const Stats_req_flow_base<K>& f)
  {
    return 32 + bytes(f.match);
  }

template<Stats_type K>
  inline Error_condition
  is_valid(const Stats_req_flow_base<K>& f) { return is_valid(f.match); }

// To/from buffer
template<Stats_type K>
  inline Error_condition
  to_buffer(Buffer_view& v, const Stats_req_flow_base<K>& f)
  {
    if (not available(v, bytes(f)))
      return available_error<Stats_type, K>::value;

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
      return available_error<Stats_type, K>::value;

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
inline std::size_t
bytes(const Stats_req_port& p) { return 8; }


// -------------------------------------------------------------------------- //
// Stats Request: Queue

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
inline std::size_t
bytes(const Stats_req_queue& q) { return 8; }

// -------------------------------------------------------------------------- //
// Stats Request: Group

// Equality comparison
inline bool
operator==(const Stats_req_group& a, const Stats_req_group& b)
{
  return a.group_id == b.group_id;
}

inline bool
operator!=(const Stats_req_group& a, const Stats_req_group& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_req_group&) { return 8; }

// -------------------------------------------------------------------------- //
// Stats Request: Experimenter

// Equality comparison
inline bool
operator==(const Stats_req_experimenter& a, const Stats_req_experimenter& b)
{
  return a.experimenter_id == b.experimenter_id
     and a.exp_type == b.exp_type
     and a.data == b.data;
}

inline bool
operator!=(const Stats_req_experimenter& a, const Stats_req_experimenter& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_req_experimenter& e)
{
  return 8 + bytes(e.data);
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
  construct(Stats_req_payload& p, Stats_req_group_features::Tag, Args&&... args) {
    new (&p.data.group_features) Stats_req_group_features(std::forward<Args>(args)...); 
  }

template<typename... Args>
  inline void
  construct(Stats_req_payload& p, Stats_req_experimenter::Tag, Args&&... args) {
    new (&p.data.experimenter) Stats_req_experimenter(std::forward<Args>(args)...); 
  }


// -------------------------------------------------------------------------- //
// Stats Header

// Equality comparable
inline bool
operator==(const Stats_header& a, const Stats_header& b)
{
  return a.type == b.type and a.flags == b.flags;
}

inline bool
operator!=(const Stats_header& a, const Stats_header& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_header& h) { return 8; }

// Is valid
inline Error_condition
is_valid(const Stats_header& h) { return is_valid(h.type); }


// -------------------------------------------------------------------------- //
// Stats Request

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

// Equality comparison
inline bool
operator==(const Stats_req& a, const Stats_req& b)
{
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Stats_req& a, const Stats_req& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_req& r)
{
  return bytes(r.header) + bytes(r.payload, r.header.type);
}

// Is valid
inline Error_condition
is_valid(const Stats_req& r)
{
  if (Error_decl err = is_valid(r.header))
    return err;
  return is_valid(r.payload, r.header.type);
}

// -------------------------------------------------------------------------- //
// Stats Response: Desc

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
inline std::size_t
bytes(const Stats_res_desc& d)
{
  return 4 * Stats_res_desc::DESC_STR_LEN + Stats_res_desc::SERIAL_NUM_LEN;
}

// Is valid
inline Error_condition
is_valid(const Stats_res_desc& d) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response: Flow

// Equality comparison
inline bool
operator==(const Stats_res_flow& a, const Stats_res_flow& b)
{
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
operator!=(const Stats_res_flow& a, const Stats_res_flow& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_flow& f)
{
  return 48 + bytes(f.match) + bytes(f.instructions);
}

// Is valid
inline Error_condition
is_valid(const Stats_res_flow& f)
{
  if (Error_decl err = is_valid(f.match))
    return err;
  return is_valid(f.instructions);
}

// -------------------------------------------------------------------------- //
// Stats Response: Flows

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

// -------------------------------------------------------------------------- //
// Stats Response: Aggregate

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
inline std::size_t
bytes(const Stats_res_aggregate&) { return 24; }

// Is valid
inline Error_condition
is_valid(const Stats_res_aggregate& a) { return SUCCESS; }


// -------------------------------------------------------------------------- //
// Stats Response: Port

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

inline bool
operator!=(const Stats_res_port& a, const Stats_res_port& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_port&) { return 104; }

// -------------------------------------------------------------------------- //
// Stats Response: Ports

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

// -------------------------------------------------------------------------- //
// Stats Response: Queue

// Equality comparison
inline bool
operator==(const Stats_res_queue& a, const Stats_res_queue& b)
{
  return a.port_no == b.port_no
     and a.queue_id == b.queue_id
     and a.tx_bytes == b.tx_bytes
     and a.tx_packets == b.tx_packets
     and a.tx_errors == b.tx_errors;
}

inline bool
operator!=(const Stats_res_queue& a, const Stats_res_queue& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_queue&) { return 32; }

// is_valid
inline Error_condition
is_valid(const Stats_res_queue&) { return SUCCESS; }


// -------------------------------------------------------------------------- //
// Stats Response: Queues

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


// -------------------------------------------------------------------------- //
// Stats Response: Table

// Equality comparison
inline bool
operator==(const Stats_res_table& a, const Stats_res_table& b)
{
  return a.table_id == b.table_id
     and a.name == b.name
     and a.match == b.match
     and a.wildcards == b.wildcards
     and a.write_actions == b.write_actions
     and a.apply_actions == b.apply_actions
     and a.write_setfields == b.write_setfields
     and a.apply_setfields == b.apply_setfields
     and a.metadata_match == b.metadata_match
     and a.metadata_write == b.metadata_write
     and a.instructions == b.instructions
     and a.config == b.config
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
inline std::size_t
bytes(const Stats_res_table&) { return 128; }

// is_valid
inline Error_condition
is_valid(const Stats_res_table&) { return SUCCESS; }


// -------------------------------------------------------------------------- //
// Stats Response: Tables

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

// -------------------------------------------------------------------------- //
// Stats Response: Group

// Equality comparison
inline bool
operator==(const Stats_res_group& a, const Stats_res_group& b)
{
  return a.length == b.length
     and a.group_id == b.group_id
     and a.ref_count == b.ref_count
     and a.packet_count == b.packet_count
     and a.byte_count == b.byte_count
     and a.bucket_stats == b.bucket_stats;
}

inline bool
operator!=(const Stats_res_group& a, const Stats_res_group& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_group& g)
{
  return 32 + bytes(g.bucket_stats);
}

// -------------------------------------------------------------------------- //
// Stats Response: Groups

inline bool
operator==(const Stats_res_groups& a, const Stats_res_groups& b)
{
  return a.groups == b.groups;
}

inline bool
operator!=(const Stats_res_groups& a, const Stats_res_groups& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_groups& gd) { return bytes(gd.groups); }

// -------------------------------------------------------------------------- //
// Stats Response: Group desc

// Equality comparison
inline bool
operator==(const Stats_res_group_desc& a, const Stats_res_group_desc& b)
{
  return a.length == b.length
     and a.type == b.type
     and a.group_id == b.group_id
     and a.buckets == b.buckets;
}

inline bool
operator!=(const Stats_res_group_desc& a, const Stats_res_group_desc& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_group_desc& gd)
{
  return 8 + bytes(gd.buckets);
}

// -------------------------------------------------------------------------- //
// Stats Response: Group descs

inline bool
operator==(const Stats_res_group_descs& a, const Stats_res_group_descs& b)
{
  return a.group_descs == b.group_descs;
}

inline bool
operator!=(const Stats_res_group_descs& a, const Stats_res_group_descs& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_group_descs& gd) { return bytes(gd.group_descs); }


// -------------------------------------------------------------------------- //
// Stats Response: Group features

// Equality comparison
inline bool
operator==(const Stats_res_group_features& a,
           const Stats_res_group_features& b)
{
  return a.types == b.types
     and a.capabilities == b.capabilities
     and a.max_groups_all == b.max_groups_all
     and a.max_groups_select == b.max_groups_select
     and a.max_groups_indirect == b.max_groups_indirect
     and a.max_groups_ff == b.max_groups_ff
     and a.actions_all == b.actions_all
     and a.actions_select == b.actions_select
     and a.actions_indirect == b.actions_indirect
     and a.actions_ff == b.actions_ff;
}

inline bool
operator!=(const Stats_res_group_features& a,
           const Stats_res_group_features& b)
{
  return !(a == b);
}

inline std::size_t
bytes(const Stats_res_group_features)
{
  return 40;
}

inline bool
capabilities_select_weight(Stats_res_group_features::Capabilities_type ct)
{
  return ct & Stats_res_group_features::SELECT_WEIGHT;
}

inline bool
capabilities_select_liveness(Stats_res_group_features::Capabilities_type ct)
{
  return ct & Stats_res_group_features::SELECT_LIVENESS;
}

inline bool
capabilities_chaining(Stats_res_group_features::Capabilities_type ct)
{
  return ct & Stats_res_group_features::CHAINING;
}

inline bool
capabilities_chaining_checks(Stats_res_group_features::Capabilities_type ct)
{
  return ct & Stats_res_group_features::CHAINING_CHECKS;
}

// -------------------------------------------------------------------------- //
// Stats Response: Experimenter

// Equality comparison
inline bool
operator==(const Stats_res_experimenter& a, const Stats_res_experimenter& b)
{
  return a.experimenter_id == b.experimenter_id
     and a.exp_type == b.exp_type
     and a.data == b.data;
}

inline bool
operator!=(const Stats_res_experimenter& a, const Stats_res_experimenter& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Stats_res_experimenter& e)
{
  return 8 + bytes(e.data);
}

// is_valid
inline Error_condition
is_valid(const Stats_res_experimenter&) { return SUCCESS; }

// -------------------------------------------------------------------------- //
// Stats Response

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
is_valid(const Stats_res& r)
{
  if (Error_decl err = is_valid(r.header))
    return err;
  return is_valid(r.payload, r.header.type);
}


// -------------------------------------------------------------------------- //
// Queue Get Config Request

// Equality comparison
inline bool
operator==(const Queue_get_config_req& a, const Queue_get_config_req& b)
{
  return a.port == b.port;
}

inline bool
operator!=(const Queue_get_config_req& a, const Queue_get_config_req& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Queue_get_config_req&) { return 8; }

// Is valid
inline Error_condition
is_valid(const Queue_get_config_req& q)
{
  return ok(q.port < 0xffffff00, BAD_QUEUE_GET_CONFIG_REQ_PORT) ;
}

// -------------------------------------------------------------------------- //
// Queue Get Config Response

// Equality comparison
inline bool
operator==(const Queue_get_config_res& a, const Queue_get_config_res& b)
{
  return a.port == b.port
     and a.queues == b.queues;
}

inline bool
operator!=(const Queue_get_config_res& a, const Queue_get_config_res& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Queue_get_config_res& qgcr)
{
  return 8 + bytes(qgcr.queues);
}

// -------------------------------------------------------------------------- //
// Role enum

inline Error_condition
is_valid(const Role t)
{
  return ok(t <= R_SLAVE, BAD_ROLE);
}

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

// Equality comparison
template <Message_type K>
  inline bool
  operator==(const Role_base<K>& a, const Role_base<K>& b)
  {
    return a.role == b.role and a.generation_id == b.generation_id;
  }

template <Message_type K>
  inline bool
  operator!=(const Role_base<K>& a, const Role_base<K>& b)
  {
    return !(a == b);
  }

// Bytes
template <Message_type K>
  inline std::size_t
  bytes(const Role_base<K>&)
  {
    return 16;
  }
// Is valid
template <Message_type K>
  inline Error_condition
  is_valid(const Role_base<K>& rb)
  {
    return is_valid(rb.role);
  }

template <Message_type K>
  Error_condition to_buffer(Buffer_view& v, const Role_base<K>& rb)
  {
    if (not available(v, bytes(rb)))
      return available_error<Message_type, K>::value;

    to_buffer(v, rb.role);
    pad(v, 4);
    to_buffer(v, rb.generation_id);
    return SUCCESS;
  }

template <Message_type K>
  Error_condition from_buffer(Buffer_view& v, Role_base<K>& rb)
  {
    if (not available(v, bytes(rb)))
      return available_error<Message_type, K>::value;

    from_buffer(v, rb.role);
    pad(v, 4);
    from_buffer(v, rb.generation_id);
    return SUCCESS;
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

// -------------------------------------------------------------------------- //
// Header

inline bool
operator==(const Header& a, const Header& b)
{
  return a.xid == b.xid
     and a.version == b.version
     and a.type == b.type
     and a.length == b.length;
}

inline bool
operator!=(const Header& a, const Header& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Header&) { return 8; }

// Is valid
inline Error_condition
is_valid(const Header& h)
{
  return ok(h.length >= bytes(h), BAD_HEADER_LENGTH);
}


// ------------------------------------------------------------ //
// Message

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
Message::Message(Message&& x)
  : header(std::move(x.header))
{
  construct(payload, std::move(x.payload), header.type);
}

inline Message&
Message::operator=(Message&& x)
{
  header = std::move(x.header);
  assign(payload, std::move(x.payload), header.type);
  return *this;
}

inline
Message::Message(const Message& x)
  : header(x.header)
{
  construct(payload, x.payload, header.type);
}

inline Message&
Message::operator=(const Message& x)
{
  header = x.header;
  assign(payload, x.payload, header.type);
  return *this;
}

inline
Message::~Message()
{
  destroy(payload, header.type);
}

// Equality comparable
inline bool
operator==(const Message& a, const Message& b)
{
  return a.header == b.header
     and equal(a.payload, b.payload, a.header.type, b.header.type);
}

inline bool
operator!=(const Message& a, const Message& b)
{
  return !(a == b);
}

// Bytes
inline std::size_t
bytes(const Message& m)
{
  return bytes(m.header) + bytes(m.payload, m.header.type);
}

// Is valid
inline Error_condition
is_valid(const Message& m) { return is_valid(m.payload, m.header.type); }


} // namespace v1_2
} // namespace ofp
} // namespace flog

#endif
