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

#include <sstream>

#include <libflog/proto/internet.hpp>

#include "command.hpp"

namespace flog {
namespace config {

static const std::string port = "p";

Acceptor
parse_v4_acceptor(const Arguments& args, int pos, net::Transport t)
{
  int sz = args.size();
  uint16_t p = 0;
  if(sz - pos == 3 and port.compare(args[pos+1]) == 0) {
    p = atoi(args[pos+2].c_str());
  }
  return Acceptor(net::make_address(t, net::IPv4, args[pos], p));
}

Acceptor
parse_v6_acceptor(const Arguments& args, int pos, net::Transport t)
{
  int sz = args.size();
  uint16_t p = 0;
  if(sz - pos == 3 and port.compare(args[pos+1]) == 0) {
    p = atoi(args[pos+2].c_str());
  } 
  return Acceptor(net::make_address(t, net::IPv6, args[pos], p));
}

Connection
parse_v4_connection(const Arguments& args, int pos, net::Transport t)
{
  int sz = args.size();
  uint16_t p = 0;
  if(sz - pos >= 3 and port.compare(args[pos+1]) == 0) {
    p = atoi(args[pos+2].c_str());
    pos += 3;
  }
  net::Address peer = net::make_address(t, net::IPv4, args[pos-3], p);
  p = 0;
  if(sz - pos >= 3 and port.compare(args[pos+1]) == 0) {
    p = atoi(args[pos+2].c_str());
    pos += 3;
  }
  net::Address local;
  if(pos < sz)
    local = net::make_address(t, net::IPv4, args[pos-3], p);
  return Connection(peer, local);
}

Connection
parse_v6_connection(const Arguments& args, int pos, net::Transport t)
{
  int sz = args.size();
  uint16_t p = 0;
  if(sz - pos >= 3 and port.compare(args[pos+1]) == 0) {
    p = atoi(args[pos+2].c_str());
    pos += 3;
  }
  net::Address peer = net::make_address(t, net::IPv6, args[pos-3], p);
  p = 0;
  if(sz - pos >= 3 and port.compare(args[pos+1]) == 0) {
    p = atoi(args[pos+2].c_str());
    pos += 3;
  }
  net::Address local;
  if(pos < sz)
    local = net::make_address(t, net::IPv6, args[pos-3], p);
  return Connection(peer, local);
}

std::string
to_string(const Acceptor& a)
{
  std::stringstream ss;
  ss << to_string(a.acceptor.transport) << " ";
  ss << to_string(a.acceptor.network) << " ";
  switch(a.acceptor.network) {
    case net::IPv4: 
      ss << to_string(a.acceptor.v4) ;
      break;
    case net::IPv6:
      ss << to_string(a.acceptor.v6) ;
      break;
    default:
      break;
  }
  if(a.acceptor.port != 0)
    ss << "|" << a.acceptor.port;
  return ss.str();
}

std::string
to_string(const Connection& c)
{
  std::stringstream ss;
  ss << to_string(c.peer.transport) << " ";
  ss << to_string(c.peer.network) << " ";
  switch(c.peer.network) {
    case net::IPv4: 
      ss << to_string(c.peer.v4) ;
      break;
    case net::IPv6:
      ss << to_string(c.peer.v6) ;
      break;
    default:
      break;
  }
  if(c.peer.port != 0)
    ss << "|" << c.peer.port;
  if(c.local) {
    switch(c.local.network) {
      case net::IPv4: 
        ss << to_string(c.local.v4) ;
        break;
      case net::IPv6:
        ss << to_string(c.local.v6) ;
        break;
      default:
        break;
    }
    if(c.local.port != 0)
      ss << "|" << c.local.port;
  }
  return ss.str();
}

const std::string Command::s_add         = "add";
const std::string Command::s_del         = "del";
const std::string Command::s_start       = "start";
const std::string Command::s_stop        = "stop";
const std::string Command::s_acceptor    = "acceptor";
const std::string Command::s_connection  = "connection";
const std::string Command::s_public_key  = "public_key";
const std::string Command::s_private_key = "private_key";
const std::string Command::s_openflow    = "openflow";
const std::string Command::s_application = "application";
const std::string Command::s_realm       = "realm";

const std::string Command::s_v1_0 = "1.0";
const std::string Command::s_v1_1 = "1.1";
const std::string Command::s_v1_2 = "1.2";
const std::string Command::s_v1_3 = "1.3";
const std::string Command::s_v1_3_1 = "1.3.1";

const std::string parse_head::ipv4 = "ipv4";
const std::string parse_head::ipv6 = "ipv6";
const std::string parse_head::tcp  = "tcp";
const std::string parse_head::tls  = "tls";

bool 
parse_head::operator()(const std::string& t, const std::string& n)
{
  if(tls.compare(t) == 0) {
    transport = net::TLS;
  } else if(tcp.compare(t) == 0) {
    transport = net::TCP;
  } else {
    status = false;
    error = ("bad transport: " + t);
    return *this;
  }
  if(ipv4.compare(n) == 0) {
    network = net::IPv4;
  } else if(ipv6.compare(n) == 0) {
    network = net::IPv6;
  } else {
    status = false;
    error = ("bad network: " + n);
  }
  return *this;
}

void
Command::parse_acceptor(const Arguments& args)
{
  auto sz = args.size();
  if(sz != 3 and sz != 5) {
    status = false;
    error = "wrong number of arguments";
  } else if (ph(args[0], args[1])) {
    Acceptor a;
    switch(ph.network) {
      case net::IPv4:
        if(not (a = parse_v4_acceptor(args, 2, ph.transport))) {
          std::cout << "parse fail" << std::endl;
          status = false;
          error = acceptor.error;
        }
        break;
      case net::IPv6:
        if(not (a = parse_v6_acceptor(args, 2, ph.transport))) {
          std::cout << "parse fail" << std::endl;
          status = false;
          error = acceptor.error;
        }
        break;
      default:
        break;
    }
    new (&acceptor) Acceptor(a);
  } else {
    status = ph.status;
    error = ph.error;
  }
}

void
Command::parse_connection(const Arguments& args)
{
  auto sz = args.size();
  if(sz < 3 or sz == 6 or sz > 8) {
    status = false;
    error = "wrong number arguments";
  } else if (ph(args[0], args[1])) {
    Connection c;
    switch(ph.network) {
      case net::IPv4:
        if(not (c = parse_v4_connection(args, 2, ph.transport))) {
          status = false;
          error = connection.error;
        }
        break;
      case net::IPv6:
        if(not (c = parse_v6_connection(args, 2, ph.transport))) {
          status = false;
          error = connection.error;
        }
        break;
      default:
        break;
    }
    new (&connection) Connection(c);
  } else {
    status = ph.status;
    error = ph.error;
  }
}

std::string
to_string(Version v)
{
  switch(v) {
    case Version::v1_0: return "1.0";
    case Version::v1_1: return "1.1";
    case Version::v1_2: return "1.2";
    case Version::v1_3: return "1.3";
    case Version::v1_3_1: return "1.3.1";
    default: return "Unkonwn";
  }
}

void
Command::parse_key(const Arguments& args)
{
  auto sz = args.size();
  if (sz == 0) {
    status = false;
    error = "too few arguments";
  } else if (sz > 1) {
    status = false;
    error = "too many arguments";
  } else
    new (&key) std::string(args[0]);
}

void
Command::parse_openflow(const Arguments& args)
{
   auto sz = args.size();
   if(sz == 0) {
     status = false;
     error = "too few arguments";
   } else if(sz > 1) {
     status = false;
     error = "too many arguments";
   } else {
    if (s_v1_0.compare(args[0]) == 0) {
      version = Version::v1_0;
    } else if (s_v1_1.compare(args[0]) == 0) {
      version = Version::v1_1;
    } else if (s_v1_2.compare(args[0]) == 0) {
      version = Version::v1_2;
    } else if (s_v1_3.compare(args[0]) == 0) {
      version = Version::v1_3;
    } else if (s_v1_3_1.compare(args[0]) == 0) {
      version = Version::v1_3_1;
    }
   }
}

void
Command::parse_application(const Arguments& args)
{
   auto sz = args.size();
   if(sz == 0) {
     status = false;
     error = "too few arguments";
   } else if(sz > 1) {
     status = false;
     error = "too many arguments";
   } else {
     new (&application) std::string(args[0]);
   }
}

Command::Command(const std::string& a, const std::string& n, 
                 const std::string& r, const Arguments& args)
  : realm(r)
{
  // parse the action
  if (s_add.compare(a)==0)
    action = ADD;
  else if (s_del.compare(a)==0)
    action = DEL;
  else if (s_start.compare(a)==0)
    action = START;
  else if (s_stop.compare(a) == 0)
    action = STOP;
  else {
    status = false;
    error = ("Bad Action: " + a);
    return;
  }

  // parse the name
  if (s_acceptor.compare(n) == 0)
    name = ACCEPTOR;
  else if (s_connection.compare(n)==0)
    name = CONNECTION;
  else if (s_public_key.compare(n) == 0)
    name = PUBLIC_KEY;
  else if (s_private_key.compare(n) == 0)
    name = PRIVATE_KEY;
  else if (s_openflow.compare(n) == 0)
    name = OPENFLOW;
  else if (s_application.compare(n) == 0)
    name = APPLICATION;
  else if (s_realm.compare(n) == 0)
    name = REALM;
  else {
    status = false;
    error = ("Bad Name: " + n);
    return;
  }

  // dispatch the appropriate component
  switch(name) {
    case ACCEPTOR:
      parse_acceptor(args);
      break;
    case CONNECTION:
      parse_connection(args);
      break;
    case PUBLIC_KEY:
    case PRIVATE_KEY:
      parse_key(args);
      break;
    case OPENFLOW:
      parse_openflow(args);
      break;
    case APPLICATION:
      parse_application(args);
      break;
    default:
      break;
  }
}

std::string
to_string(Command::Action a)
{
  switch(a) {
    case Command::ADD: return "add";
    case Command::DEL: return "del";
    case Command::START: return "start";
    case Command::STOP: return "stop";
    default: return "unknown";
  }
}

std::string
to_string(Command::Name a)
{
  switch(a) {
    case Command::ACCEPTOR: return "acceptor";
    case Command::CONNECTION: return "connection";
    case Command::PUBLIC_KEY: return "public_key";
    case Command::PRIVATE_KEY: return "private_key";
    case Command::OPENFLOW: return "openflow";
    case Command::APPLICATION: return "application";
    case Command::REALM: return "realm";
    default: return "unknown";
  }
}

std::string 
to_string(const Command& c)
{
  std::stringstream ss;

  ss << to_string(c.action) << " " << to_string(c.name) << " ";
  ss << c.realm << " ";
  switch(c.name) {
    case Command::ACCEPTOR:
      ss << to_string(c.acceptor);
      break;
    case Command::CONNECTION:
      ss << to_string(c.connection);
      break;
    case Command::PUBLIC_KEY:
      ss << c.key;
      break;
    case Command::PRIVATE_KEY:
      ss << c.key;
      break;
    case Command::APPLICATION:
      ss << c.application;
      break;
    case Command::OPENFLOW:
      ss << to_string(c.version);
      break;
    default:
      break;
  }
  return ss.str();
}

} // namespace config
} // namespace flog
