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

extern "C" {
#include <netinet/in.h>
#include <arpa/inet.h>
}

#include <sstream>
#include "internet.hpp"

namespace flog {
namespace net {

static const std::string ipv4 = "ipv4";
static const std::string ipv6 = "ipv6";

std::string
to_string(Network n)
{
  switch(n) {
    case IPv4: return "ipv4";
    case IPv6: return "ipv6";
    default: return "unknown";
  }
}

Network
network_from_string(const std::string& s)
{
  if (ipv4.compare(s) == 0)
    return IPv4;
  else if (ipv6.compare(s) == 0)
    return IPv6;
  else
    return Unknown_network;
}

static const std::string tcp = "tcp";
static const std::string udp = "udp";
static const std::string sctp = "sctp";
static const std::string tls = "tls";

std::string
to_string(Transport t)
{
  switch(t) {
    case TCP: return "tcp";
    case UDP: return "udp";
    case SCTP: return "sctp";
    case TLS: return "tls";
    default: return "unknown";
  }
}

Transport
transport_from_string(const std::string& s)
{
  if (tcp.compare(s) == 0)
    return TCP;
  else if (udp.compare(s) == 0)
    return UDP;
  else if (sctp.compare(s) == 0)
    return SCTP;
  else if (tls.compare(s) == 0)
    return TLS;
  else
    return Unknown_transport;
}

Address
make_ipv4(const std::string& ip)
{
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  auto result = inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
  if (result == 0) {
    return Address(("Malformed IPv4: " + ip));
  } else if (result < 0) {
    return Address(strerror(errno));
  }
  return Address(ipv4::Address(ntohl(addr.sin_addr.s_addr)), TCP, 0);
}

Address
make_ipv6(const std::string& ip)
{
  sockaddr_in6 addr;
  addr.sin6_family = AF_INET6;
  auto result = inet_pton(AF_INET6, ip.c_str(), &addr.sin6_addr);
  if (result == 0) {
    return Address(("Malformed IPv6: " + ip));
  } else if (result < 0) {
    return Address(strerror(errno));
  }
  return Address(ipv6::Address(addr.sin6_addr.s6_addr), TCP, 0);
}

Address 
make_address(Transport t, Network n, const std::string& ip, uint32_t p)
{
  if(n == Unknown_network or t == Unknown_transport)
    return Address();

  switch(n) {
    case IPv4: return Address(make_ipv4(ip), t, p);
    case IPv6: return Address(make_ipv6(ip), t, p);
    default: return Address();
  }
}


Address 
make_address(const std::string& trpt, const std::string& nwk, 
             const std::string& ip, uint32_t p)
{
  Network n = network_from_string(nwk);
  Transport t = transport_from_string(trpt);
  return make_address(t, n, ip, p);
}

std::string
to_string(const Address& a)
{
  std::stringstream ss;
  if(a) {
  ss << to_string(a.transport) << " ";
  ss << to_string(a.network) << " " ;
  if(a.network == net::IPv4)
    ss << to_string(a.v4);
  else
    ss << to_string(a.v6);
  if(a.port != 0)
    ss << "|" << a.port;
  }
  return ss.str();
}

} // namespace net
} // namespace flogrammable
