#include <sstream>
#include "socket.hpp"

namespace flog {
namespace socket {

IPv4::IPv4(const std::string& ip, uint16_t p)
  : Address(sizeof(sockaddr_in))
{ 
  bzero(&addr, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  auto result = inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
  if (result == 0) {
    status = false;
    error = "Malformed IPv4: " + ip;
  } else if (result < 0) {
    status = false;
    error = strerror(errno);
  }
  addr.sin_port = htons(p);
}

std::string
IPv4::to_string() const
{
  std::stringstream ss;
  ss << "ipv4 ";
  char tmp[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &addr.sin_addr, tmp, INET_ADDRSTRLEN))
    ss << tmp;
  else
    ss << "unknown";
  ss << " ";
  ss << ntohs(addr.sin_port);
  return ss.str();
}

IPv6::IPv6(const std::string& ip, uint16_t p) 
  : Address(sizeof(sockaddr_in6))
{
  bzero(&addr, sizeof(sockaddr_in6));
  addr.sin6_family = AF_INET6;
  auto result = inet_pton(AF_INET6, ip.c_str(), &addr.sin6_addr);
  if (result == 0) {
    status = false;
    error = "Malformed IPv6: " + ip;
  } else if (result < 0) {
    status = false;
    error = strerror(errno);
  }
  addr.sin6_port = htons(p);
}

std::string
IPv6::to_string() const
{
  std::stringstream ss;
  ss << "ipv6 ";
  char tmp[INET6_ADDRSTRLEN];
  if (inet_ntop(AF_INET6, &addr.sin6_addr, tmp, INET6_ADDRSTRLEN))
    ss << tmp;
  else
    ss << "uknown";
  ss << " ";
  ss << ntohs(addr.sin6_port);
  return ss.str();
}

Address*
make_address(const net::Address& a)
{
  switch(a.network) {
    case net::IPv4:
        return new IPv4(a.v4, a.port);
      break;
    case net::IPv6:
        return new IPv6(a.v6, a.port);
      break;
    default: return nullptr;
  }
}

std::string
to_string(const Socket& s)
{
  std::stringstream ss;
  return ss.str();
}

} // namespace socket
} // namespace flog
