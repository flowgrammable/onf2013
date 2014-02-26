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

#ifndef FLOWGRAMMABLE_IPV4_H
#define FLOWGRAMMABLE_IPV4_H

#include <cstdint>

#include <libflog/buffer.hpp>

namespace flog {
namespace ipv4 {


// -------------------------------------------------------------------------- //
// Address

/// An IPv4 address is a 32-bit value...
struct Address
{
  Address() = default;
  constexpr Address(uint32_t a) : addr(a) { }
  
  uint32_t addr;
};

// Equality comparison
inline bool
operator==(Address a, Address b)
{ 
  return a.addr == b.addr;
}

inline bool
operator!=(Address a, Address b) 
{
  return !(a == b);
}

// Bytes
inline std::size_t 
bytes(const ipv4::Address& a)
{
    return 4;
}

// To string
std::string to_string(Address);

// To network
Address to_network(Address, int);

// Well-known addresses
constexpr Address broadcast { 0xffffffff };
constexpr Address localhost { 0x80000001 };


/// TODO: Document me
template<typename T>
  inline T
  prefix_1s(size_t ones) 
  {
    std::size_t bits = sizeof(T) * 8;
    if (bits < ones)
      return ~T(0);
    ones = bits - ones;
    T result = T(0);
    while(ones--) { result <<= 1; result |= T(1); }
    return ~result;
  }
         
/// TODO: Document me  
template<typename T>
  inline T 
  prefix_0s(size_t zeros) 
  {
    return ~prefix_1s<T>(zeros);
  }
           
/// TODO: Document me
template<typename T>
  inline bool 
  valid_mask(T t) 
  {
    bool zero = true;
    size_t bits = 8 * sizeof(T);
    while (bits--) {
      if (0x01 & t) 
        zero = false;
      else if (!zero) 
        return false;
      t >>= 1;
    }
    return true;
   }

/// TODO: Document me
template<typename T>
  size_t 
  mask_to_vlsm(T t)
  {
    size_t count = 0;
    size_t bits = 8 * sizeof(T);
    while (bits--) {
      if (0x01 & t)
        return 32 - count;
      count++;
      t >>= 1;
    }
    return 32;
  }

// -------------------------------------------------------------------------- //
// Differential Services Code Point

struct DSCP
{
  uint8_t DSCP; //6 bits in ToS field
};

// Equality comparison
inline bool
operator==(DSCP a, DSCP b)
{ 
  return (a.DSCP & 0x3f) == (b.DSCP & 0x3f);
}

inline bool
operator!=(DSCP a, DSCP b) 
{
  return !(a == b);
}

// Bytes
inline std::size_t 
bytes(const ipv4::DSCP& a)
{
    return 1;
}

// To/from
std::string to_string(const ipv4::DSCP& a);


// -------------------------------------------------------------------------- //
// Explicit Congestion Notification

struct ECN
{
  uint8_t ECN; //2 bits in ToS field
};

// Equality comparison
inline bool
operator==(ECN a, ECN b)
{ 
  return (a.ECN & 0x03) == (b.ECN & 0x03);
}

inline bool
operator!=(ECN a, ECN b) 
{
  return !(a == b);
}

// Bytes
inline std::size_t 
bytes(const ipv4::ECN& a)
{
    return 1;
}

// To/from
std::string to_string(const ipv4::ECN& a);


} // namespace ipv4
} // namespace flog

#endif
