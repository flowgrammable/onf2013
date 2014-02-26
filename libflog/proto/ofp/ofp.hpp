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


#ifndef FLOWGRAMMABLE_PROTO_OFP_OFP_HPP
#define FLOWGRAMMABLE_PROTO_OFP_OFP_HPP

#include <cstring>
#include <algorithm>

#include <libflog/utilities.hpp>
#include <libflog/buffer.hpp>
#include <libflog/string.hpp>
#include <libflog/proto/ethernet/ethernet.hpp>
#include <libflog/proto/ipv4/ipv4.hpp>
#include <libflog/proto/ipv6/ipv6.hpp>
#include <libflog/proto/mpls/mpls.hpp>

namespace flog {
namespace ofp {

// Aliases for address types
using Ethernet_addr = ethernet::Address;
using Ipv4_addr = ipv4::Address;
using Ipv6_addr = ipv6::Address;

enum Stack_version : uint32_t{
  sv_1_0 = 0x01,
  sv_1_1 = 0x02,
  sv_1_2 = 0x04,
  sv_1_3 = 0x08,
  sv_1_3_1 = 0x10 
};

// To buffer primitives

inline bool
to_buffer(Buffer_view& v, uint8_t n)
{
  put(v, n);
  return true;
}

inline bool
to_buffer(Buffer_view& v, uint16_t n)
{
  put(v, Foreign_byte_order::msbf(n));
  return true;
}

inline bool
to_buffer(Buffer_view& v, uint32_t n)
{
  put(v, Foreign_byte_order::msbf(n));
  return true;
}

inline bool
to_buffer(Buffer_view& v, uint64_t n)
{
  put(v, Foreign_byte_order::msbf(n));
  return true;
}

// To buffer for enumeration types.
template<typename T, 
         typename = typename std::enable_if<std::is_enum<T>::value>::type>
  inline bool
  to_buffer(Buffer_view& v, T value)
  {
    using U = typename std::underlying_type<T>::type;
    put(v, Foreign_byte_order::msbf(U(value)));
    return true;
  }

// To buffer for stringbufs
template<std::size_t N>
  inline bool
  to_buffer(Buffer_view& v, const Stringbuf<N>& str)
  {
    put(v, str.data(), N);
    return true;
  }

// To buffer for Ethernet addresses.
inline bool
to_buffer(Buffer_view& v, const Ethernet_addr& addr)
{
  put(v, addr.data, 6);
  return true;
}

// To buffer for IPv4 addresses.
inline bool
to_buffer(Buffer_view& v, const Ipv4_addr& addr)
{
  return to_buffer(v, addr.addr);
}

// To buffer IPv4 Differential Services Code Point
inline bool
to_buffer(Buffer_view& v, const ipv4::DSCP& a)
{
  return to_buffer(v, a.DSCP);
}

// To buffer IPv4 Explicit Congestion Notification
inline bool
to_buffer(Buffer_view& v, const ipv4::ECN& a)
{
  return to_buffer(v, a.ECN);
}

// To buffer for IPv6 addresses.
inline bool
to_buffer(Buffer_view& v, const Ipv6_addr& addr)
{
  put(v, addr.addr, 16);
  return true;
}

// To buffer for IPv6 flow labels.
inline bool
to_buffer(Buffer_view& v, const ipv6::Flow_label& fl)
{
  put(v, fl.data, 3);
  return true;
}

// To buffer for MPLS flow labels.
inline bool
to_buffer(Buffer_view& v, const mpls::Flow_label& fl)
{
  put(v, fl.data, 3);
  return true;
}


// From buffer primitives.

inline bool
from_buffer(Buffer_view& v, uint8_t& n)
{
  get(v, n);
  return true;
}

inline bool
from_buffer(Buffer_view& v, uint16_t& n)
{
  n = Foreign_byte_order::msbf(get<uint16_t>(v));
  return true;
}

inline bool
from_buffer(Buffer_view& v, uint32_t& n)
{
  n = Foreign_byte_order::msbf(get<uint32_t>(v));
  return true;
}

inline bool
from_buffer(Buffer_view& v, uint64_t& n)
{
  n = Foreign_byte_order::msbf(get<uint64_t>(v));
  return true;
}

// From buffer for enumeration types.
template<typename T, 
         typename = typename std::enable_if<std::is_enum<T>::value>::type>
  inline bool
  from_buffer(Buffer_view& v, T& x)
  {
    using U = typename std::underlying_type<T>::type;
    x = T(Foreign_byte_order::msbf(get<U>(v)));
    return true;
  }

// From buffer for Stringbuf types
template<std::size_t N>
  inline bool
  from_buffer(Buffer_view& v, Stringbuf<N>& str)
  {
    get(v, str.data(), N);
    return true;
  }

// From buffer for Ethernet addresses.
inline bool
from_buffer(Buffer_view& v, Ethernet_addr& addr)
{
  get(v, addr.data, 6);
  return true;
}

// From buffer for IPv4 addresses.
inline bool
from_buffer(Buffer_view& v, Ipv4_addr& addr)
{
  return from_buffer(v, addr.addr);
}

// From buffer IPv4 Differential Services Code Point
inline bool
from_buffer(Buffer_view& v, ipv4::DSCP& a)
{
  return from_buffer(v, a.DSCP);
}

// From buffer IPv4 Explicit Congestion Notification
inline bool
from_buffer(Buffer_view& v, ipv4::ECN& a)
{
  return from_buffer(v, a.ECN);
}

// From buffer for IPv6 addresses.
inline bool
from_buffer(Buffer_view& v, Ipv6_addr& addr)
{
  get(v, addr.addr, 16);
  return true;
}

// From buffer for IPv6 flow labels.
inline bool
from_buffer(Buffer_view& v, ipv6::Flow_label& fl)
{
  get(v, fl.data, 3);
  return true;
}

// From buffer for MPLS flow labels.
inline bool
from_buffer(Buffer_view& v, mpls::Flow_label& fl)
{
  get(v, fl.data, 3);
  return true;
}

} // namespace ofp
} // namespace flog
#endif
