#ifndef FLOWGRAMMABLE_SOCKET_H
#define FLOWGRAMMABLE_SOCKET_H

extern "C" {
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
}

#include <string>

#include <libflog/proto/internet.hpp>

#include "ssl_wrapper.hpp"

namespace flog {
namespace socket {

struct Address {
  Address(socklen_t s) 
    : size(s), status(true) 
  { }
  Address(const Address& a)
    : size(a.size), status(a.status), error(a.error)
  { }
  virtual ~Address() {}

  virtual const sockaddr* generic_address() const = 0;
  virtual sockaddr* generic_address() = 0;
  socklen_t* generic_address_size();
  virtual int type() const = 0;
  virtual bool match(const net::Address& rhs) const = 0;

  virtual Address* defcons() const = 0;
  virtual Address* copy() const = 0;
  virtual std::string to_string() const = 0;

  operator bool() const { return status; }

  socklen_t size;
  bool status;
  std::string error;
};

struct IPv4 : Address {
  IPv4();
  IPv4(const ipv4::Address& a, uint16_t p);
  IPv4(const std::string& ip, uint16_t p);
  IPv4(const IPv4& ip);

  const sockaddr* generic_address() const;
  sockaddr* generic_address();
  socklen_t* generic_address_size();
  int type() const;
  bool match(const net::Address& rhs) const;

  IPv4* defcons() const;
  IPv4* copy() const;
  std::string to_string() const;

  sockaddr_in addr;
};

struct IPv6 : Address {
  IPv6();
  IPv6(const ipv6::Address& a, uint16_t p);
  IPv6(const std::string& ip, uint16_t p);
  IPv6(const IPv6& ip);

  const sockaddr* generic_address() const;
  sockaddr* generic_address();
  socklen_t* generic_address_size();
  int type() const;
  bool match(const net::Address& rhs) const;

  IPv6* defcons() const;
  IPv6* copy() const;
  std::string to_string() const;

  sockaddr_in6 addr;
};

Address* make_address(const net::Address& a);

struct Socket {
  Socket(const net::Address& a);
  Socket(net::Transport t, const Address& l);
  Socket(net::Transport t, Address* l);
  Socket(net::Transport t, Address* l, Address* p, int f);
  Socket(Socket&& s);
  ~Socket();

  Socket& bind();
  Socket& listen();
  Socket& connect(const net::Address& p);
  Socket& connect(const Address& p);
  Socket accept();

  bool match(const net::Address& addr) const;

  net::Transport transport;
  Address* local;
  Address* peer;
  int fd;
  
  operator bool() const { return status; }

  bool status;
  std::string error;
};

int to_domain(net::Transport t);

std::string to_string(const Socket& s);

inline socklen_t* 
Address::generic_address_size() 
{ 
  return &size; 
}

inline
IPv4::IPv4()
  : Address(sizeof(sockaddr_in))
{
  bzero(&addr, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
}

inline
IPv4::IPv4(const ipv4::Address& a, uint16_t p)
  : Address(sizeof(sockaddr_in))
{
  bzero(&addr, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(a.addr);
  addr.sin_port = htons(p);
}

inline
IPv4::IPv4(const IPv4& ip)
  : Address(ip), addr(ip.addr)
{ }
  
inline const sockaddr* 
IPv4::generic_address() const 
{ 
  return reinterpret_cast<const sockaddr*>(&addr); 
}

inline sockaddr* 
IPv4::generic_address() 
{ 
  return reinterpret_cast<sockaddr*>(&addr); 
}

inline int
IPv4::type() const
{
  return AF_INET;
}

inline bool
IPv4::match(const net::Address& rhs) const 
{
  return rhs.network == net::IPv4 and 
         rhs.v4.addr == addr.sin_addr.s_addr and 
         rhs.port == addr.sin_port;
}

inline IPv4*
IPv4::defcons() const
{
  return new IPv4();
}

inline IPv4*
IPv4::copy() const
{
  return new IPv4(*this);
}

inline
IPv6::IPv6()
  : Address(sizeof(sockaddr_in6))
{
  bzero(&addr, sizeof(sockaddr_in6));
  addr.sin6_family = AF_INET6;
  addr.sin6_addr = in6addr_any;
}

inline
IPv6::IPv6(const ipv6::Address& a, uint16_t p)
  : Address(sizeof(sockaddr_in6))
{
  bzero(&addr, sizeof(sockaddr_in6));
  addr.sin6_family = AF_INET6;
  std::copy(a.addr, a.addr+16, addr.sin6_addr.s6_addr);
  addr.sin6_port = htons(p);
}

inline
IPv6::IPv6(const IPv6& ip)
  : Address(ip), addr(ip.addr)
{ }
  
inline const sockaddr* 
IPv6::generic_address() const 
{ 
  return reinterpret_cast<const sockaddr*>(&addr); 
}

inline sockaddr* 
IPv6::generic_address() 
{ 
  return reinterpret_cast<sockaddr*>(&addr); 
}

inline int
IPv6::type() const
{
  return AF_INET6;
}

inline bool
IPv6::match(const net::Address& rhs) const 
{
  return rhs.network == net::IPv6 and
         std::equal(rhs.v6.addr, rhs.v6.addr+16, addr.sin6_addr.s6_addr) and
         rhs.port == addr.sin6_port;
}

inline IPv6*
IPv6::defcons() const
{
  return new IPv6();
}

inline IPv6*
IPv6::copy() const
{
  return new IPv6(*this);
}

inline
Socket::Socket(const net::Address& a)
  : transport(a.transport), local(make_address(a)), peer(nullptr),
    fd(::socket(local->type(), to_domain(a.transport), 0)), status(true)
{
  int flags;
  if (fd < 0) {
    status = false;
    error = strerror(errno);
  } else {
    flags = ::fcntl(fd, F_GETFD);
    if (flags < 0) {
      status = false;
      error = strerror(errno);
    } else {
      flags = ::fcntl(fd, F_SETFD, flags|O_NONBLOCK);
      if (flags < 0) {
        status = false;
        error = strerror(errno);
      } else 
        this->bind();
    }
  }
}

inline
Socket::Socket(net::Transport t, const Address& l)
  : transport(t), local(l.copy()), peer(nullptr), 
    fd(::socket(l.type(), to_domain(t), 0)), status(true)
{ 
  int flags;
  if (fd < 0) {
    status = false;
    error = strerror(errno);
  } else {
    flags = ::fcntl(fd, F_GETFD);
    if (flags < 0) {
      status = false;
      error = strerror(errno);
    } else {
      flags = ::fcntl(fd, F_SETFD, flags|O_NONBLOCK);
      if (flags < 0) {
        status = false;
        error = strerror(errno);
      } else 
        this->bind();
    }
  }
}

inline
Socket::Socket(net::Transport t, Address* l)
  : transport(t), local(l), peer(nullptr),
    fd(::socket(l->type(), to_domain(t), 0)), status(true)
{ 
  int flags;
  if (fd < 0) {
    status = false;
    error = strerror(errno);
  } else {
    flags = ::fcntl(fd, F_GETFD);
    if (flags < 0) {
      status = false;
      error = strerror(errno);
    } else {
      flags = ::fcntl(fd, F_SETFD, flags|O_NONBLOCK);
      if (flags < 0) {
        status = false;
        error = strerror(errno);
      } else 
        this->bind();
    }
  }
}

inline
Socket::Socket(net::Transport t, Address* l, Address* p, int f)
  : transport(t), local(l), peer(p), fd(f), status(true)
{ }

inline
Socket::Socket(Socket&& s)
  : transport(s.transport), local(s.local), peer(s.peer), 
    fd(s.fd), status(s.status), error(s.error)
{
  s.local = nullptr;
  s.peer = nullptr;
  s.fd = -1;
  s.status = false;
  s.error = "moved from";
}

inline
Socket::~Socket()
{
  if(fd > -1) ::close(fd);
  if(local) delete local;
  if(peer) delete peer;
}

inline bool
Socket::match(const net::Address& rhs) const {
  if(rhs.transport != transport)
    return false;
  return local->match(rhs);
}

inline int
to_domain(net::Transport t)
{
  switch(t) {
    case net::TLS:
    case net::TCP:
      return SOCK_STREAM;
    case net::UDP:
      return SOCK_DGRAM;
    default:
      return -1;
  }
}

inline Socket&
Socket::bind()
{
  auto r = ::bind(fd, local->generic_address(), *local->generic_address_size());
  if( r < 0) {
    status = false;
    error = strerror(errno);
  }
  return *this;
}

inline Socket&
Socket::listen()
{
  auto r = ::listen(fd, SOMAXCONN);
  if (r < 0) {
    status = false;
    error = strerror(errno);
  }
  return *this;
}

inline Socket&
Socket::connect(const net::Address& p)
{
  if(peer) delete peer;
  peer = make_address(p);

  // connect to the peer address
  auto r = ::connect(fd, peer->generic_address(), 
                     *peer->generic_address_size());
  if (r < 0) {
    status = false;
    error = strerror(errno);
  }

  return *this;
}

inline Socket&
Socket::connect(const Address& p)
{
  // copy the peer address
  if(peer) delete peer;
  peer = p.copy();

  // connect to the peer address
  auto r = ::connect(fd, peer->generic_address(), 
                     *peer->generic_address_size());
  if (r < 0) {
    status = false;
    error = strerror(errno);
  }
  return *this;
}

inline Socket
Socket::accept()
{
  Address* new_peer = local->defcons();
  auto r = ::accept(fd, new_peer->generic_address(), 
                    new_peer->generic_address_size());
  if (r < 0) {
    status = false;
    error = strerror(errno);
  }
  return Socket(transport, local->copy(), new_peer, r);
}

} // namespace socket
} // namespace flog

#endif
