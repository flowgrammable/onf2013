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

#ifndef FLOWGRAMMABLE_CONFIG_H
#define FLOWGRAMMABLE_CONFIG_H

extern "C" {
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
}

#include <libflog/proto/internet.hpp>

#include "time.hpp"

namespace flog {
namespace config {

struct Acl
{
  Acl(){};
  Acl(const flog::ipv4::Address& a, int v);
  Acl(const flog::ipv6::Address& a, int v);

  net::Network nw;
  union {
    flog::ipv4::Address v4;
    flog::ipv6::Address v6;
  };
  int vlsm;
};

std::string to_string(const Acl& n);

enum Ofp_version : uint8_t
{
  v10 = 1, v11 = 2, v12 = 3, v13 = 4
};

std::string to_string(Ofp_version v);

struct Ofp
{
  enum Type { Version, Echo_interval, Echo_timeout, Echo_miss };

  Ofp(const Ofp& o);
  Ofp(Type t, int v);
  Ofp(Type t, const Time& tm);

  Type type;
  union {
    unsigned int value;
    Time time;
  };
};

std::string to_string(Ofp::Type t);
std::string to_string(const Ofp& o);

struct Server
{
  Server(const net::Address& a);
  net::Address local;
};

std::string to_string(const Server& s);

struct Client
{
  Client(const net::Address& l, const net::Address& r);

  net::Address local;
  net::Address remote;
};

std::string to_string(const Client& c);

struct Command
{
  enum Action { Add, Del, Set, Stop, NoOp };
  enum Name { REMOTE, LOCAL, APP, X509, ACL, OFP, SERVER, CLIENT };

  Command(Action a = NoOp);
  Command(const Command& c);
  Command(Action a, Name n, const std::string& t);
  Command(Action a, Name n, const std::string& app, const std::string& t);
  Command(Action a, const Acl& ac, const std::string& t);
  Command(Action a, const Ofp& o, const std::string& t);
  Command(Action a, const Server& s, const std::string& t);
  Command(Action a, const Client& c, const std::string& t);
  ~Command(){}

  char* get_filename() { return payload.filename; }
  const char* get_filename() const { return payload.filename; }
  const Acl& get_acl() const { return payload.acl; }
  const Ofp& get_ofp() const { return payload.ofp; }
  const Server& get_server() const { return payload.server; }
  const Client& get_client() const { return payload.client; }

  Action action;
  Name name;

  union Payload {
    Payload(){}
    Payload(const Payload& p) {
      ::memcpy(this, &p, sizeof(Payload));
    }
    Payload(const Acl& a)
      : acl(a)
    { }
    Payload(const Ofp& o)
      : ofp(o)
    { }
    Payload(const Server& s)
      : server(s)
    { }
    Payload(const Client& c)
      : client(c)
    { }
    ~Payload(){}

    char filename[32];
    Acl acl;
    Ofp ofp;
    Server server;
    Client client;
  } payload;

  char target[32];
};

inline
Acl::Acl(const flog::ipv4::Address& a, int v)
  : nw(net::IPv4), v4(a), vlsm(v)
{ }

inline
Acl::Acl(const flog::ipv6::Address& a, int v)
  : nw(net::IPv6), v6(a), vlsm(v)
{ }

inline
Ofp::Ofp(const Ofp& o)
  : type(o.type)
{
  switch(type) {
    case Version:
    case Echo_miss:
      value = o.value;
      break;
    case Echo_interval:
    case Echo_timeout:
      time = o.time;
      break;
  }
}

inline
Ofp::Ofp(Type t, int v)
  : type(t), value(v)
{ }

inline
Ofp::Ofp(Type t, const Time& tm)
  : type(t), time(tm)
{ }

inline
Server::Server(const net::Address& a)
  : local(a)
{ }

inline
Client::Client(const net::Address& l, const net::Address& r)
  : local(l), remote(r)
{ }

inline
Command::Command(Action a)
  : action(a), payload()
{ }

inline
Command::Command(const Command& c)
  : action(c.action), name(c.name), payload(c.payload)
{
  std::copy(c.target, c.target+32, target);
}

inline
Command::Command(Action a, Name n, const std::string& t)
  : action(a), name(n)
{ 
  auto sz = t.length() < 32 ? t.length() : 31;
  std::fill(target, target+32, 0);
  std::copy(t.c_str(), t.c_str()+sz, target);
}

inline
Command::Command(Action a, Name n, const std::string& app, const std::string& t)
  : action(a), name(n)
{
  auto sz_f = app.length() < 32 ? app.length() : 31;
  std::fill(get_filename(), get_filename() + 32, 0);
  std::copy(app.c_str(), app.c_str()+sz_f, get_filename());

  auto sz = t.length() < 32 ? t.length() : 31;
  std::fill(target, target+32, 0);
  std::copy(t.c_str(), t.c_str()+sz, target);
}
  
inline
Command::Command(Action a, const Acl& ac, const std::string& t)
  : action(a), name(ACL), payload(ac)
{ 
  auto sz = t.length() < 32 ? t.length() : 31;
  std::fill(target, target+32, 0);
  std::copy(t.c_str(), t.c_str()+sz, target);
}
  
inline 
Command::Command(Action a, const Ofp& o, const std::string& t)
  : action(a), name(OFP), payload(o)
{ 
  auto sz = t.length() < 32 ? t.length() : 31;
  std::fill(target, target+32, 0);
  std::copy(t.c_str(), t.c_str()+sz, target);
}
  
inline 
Command::Command(Action a, const Server& s, const std::string& t)
  : action(a), name(SERVER), payload(s)
{ 
  auto sz = t.length() < 32 ? t.length() : 31;
  std::fill(target, target+32, 0);
  std::copy(t.c_str(), t.c_str()+sz, target);
}

inline
Command::Command(Action a, const Client& c, const std::string& t)
  : action(a), name(CLIENT), payload(c)
{ 
  auto sz = t.length() < 32 ? t.length() : 31;
  std::fill(target, target+32, 0);
  std::copy(t.c_str(), t.c_str()+sz, target);
}

std::string to_string(Command::Action a);
std::string to_string(Command::Name n);
std::string to_string(const Command& c);

struct Channel
{
  Channel(const std::string& n, int f);
  ~Channel();

  std::string name;
  int fd;
};

inline
Channel::Channel(const std::string& n, int f)
  : name(n), fd(f)
{ 
  if(fd<0) throw fd;
}

inline
Channel::~Channel()
{
  if(fd > -1)
    ::close(fd);
}

struct Read_channel : Channel
{
  Read_channel(const std::string& n);
};

int read(Read_channel& ch, Command& cmd);

inline
Read_channel::Read_channel(const std::string& n)
  : Channel(n, ::open(n.c_str(), O_RDONLY | O_NONBLOCK))
{ }

struct Write_channel : Channel
{
  Write_channel(const std::string& n);
};

int write(Write_channel& ch, const Command& cmd);

inline
Write_channel::Write_channel(const std::string& n)
  : Channel(n, ::open(n.c_str(), O_WRONLY | O_NONBLOCK))
{ }

inline int
read(Read_channel& ch, Command& cmd)
{
  return ::read(ch.fd, &cmd, sizeof(Command));
}

inline int
write(Write_channel& ch, Command& cmd)
{
  return ::write(ch.fd, &cmd, sizeof(Command));
}

} // namespace config
} // namespace flog

#endif
