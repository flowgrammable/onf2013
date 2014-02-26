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

#ifndef FLOWGRAMMABLE_INTERNET_H
#define FLOWGRAMMABLE_INTERNET_H

#include <libflog/proto/ipv4/ipv4.hpp>
#include <libflog/proto/ipv6/ipv6.hpp>

namespace flog {
namespace net {

enum Network
{
  IPv4, IPv6,
  Unknown_network
};

std::string to_string(Network n);
Network network_from_string(const std::string& s);

enum Transport
{
  TCP, UDP, SCTP, TLS,
  Unknown_transport
};

std::string to_string(Transport t);
Transport transport_from_string(const std::string& s);

struct Address
{
  Address(const std::string& s = std::string())
    : status(false), error(s)
  { }
  Address(const Address& a);
  Address(const Address& a, Transport t, uint16_t p)
    : Address(a)
  {
    transport = t;
    port = p;
  }

  Address(const ipv4::Address& a, Transport t, uint16_t p);
  Address(const ipv6::Address& a, Transport t, uint16_t p);

  Network network;
  union {
    ipv4::Address v4;
    ipv6::Address v6;
  };

  operator bool() const { return status; }

  Transport transport;
  uint16_t port;
  bool status;
  std::string error;
};

Address make_address(const std::string& trpt, const std::string& nwk, 
                     const std::string& ip, uint32_t p = 0);

Address make_address(Transport t, Network n, const std::string& ip, 
                     uint32_t p = 0);

std::string to_string(const Address& a);

inline
Address::Address(const Address& a)
  : network(a.network), transport(a.transport), port(a.port), status(a.status)
{
  if(network == IPv4)
    v4 = a.v4;
  if(network == IPv6)
    v6 = a.v6;
}

inline
Address::Address(const ipv4::Address& a, Transport t, uint16_t p)
  : network(IPv4), v4(a), transport(t), port(p), status(true)
{ }

inline
Address::Address(const ipv6::Address& a, Transport t, uint16_t p)
  : network(IPv6), v6(a), transport(t), port(p), status(true)
{ }

} // namespace net
} // namespace flog

#endif
