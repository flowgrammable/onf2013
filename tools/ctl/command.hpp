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

#ifndef FLOWGRAMMABLE_COMMAND_H
#define FLOWGRAMMABLE_COMMAND_H

#include "libflog/proto/internet.hpp"

namespace flog {
namespace config {

/////--------------------------------------

using Arguments = std::vector<std::string>;

struct Error_base {
  Error_base(const std::string e = std::string())
    : status(e.size()==0), error(e)
  { }

  operator bool() const { return status; }

  bool status;
  std::string error;
};

/////--------------------------------------

struct parse_head : Error_base
{
  static const std::string ipv4;
  static const std::string ipv6;
  static const std::string tcp;
  static const std::string tls;
                        
  parse_head()
    { } 
                       
  bool operator()(const std::string& t, const std::string& n);
                             
  net::Transport transport;
  net::Network   network;
};

struct Acceptor : Error_base {
  Acceptor() = default;

  Acceptor(const net::Address& a)
    : acceptor(a)
  { 
    if(not (status = acceptor))
      error = acceptor.error;
  }

  net::Address acceptor;
};

std::string to_string(const Acceptor& a);
Acceptor parse_v4_acceptor(const Arguments& args, int pos);
Acceptor parse_v6_acceptor(const Arguments& args, int pos);

struct Connection : Error_base {
  Connection() = default;
  Connection(const net::Address& p, const net::Address& l)
    : peer(p), local(l)
  { 
    if(not (status = peer)) {
      error = peer.error;
    } else if(not (status = local)) {
      error = local.error;
    }
  }

  net::Address peer;
  net::Address local;
};

std::string to_string(const Connection& c);
Connection parse_v4_connection(const Arguments& args, int pos);
Connection parse_v6_connection(const Arguments& args, int pos);

enum class Version { v1_0, v1_1, v1_2, v1_3, v1_3_1 };
std::string to_string(Version v);

using Arguments = std::vector<std::string>;

struct Command : Error_base {

  void parse_acceptor(const Arguments& args);
  void parse_connection(const Arguments& args);
  void parse_key(const Arguments& args);
  void parse_openflow(const Arguments& args);
  void parse_application(const Arguments& args);

  enum Action { ADD, DEL, START, STOP };
  enum Name { 
    ACCEPTOR, CONNECTION, PUBLIC_KEY, PRIVATE_KEY, OPENFLOW, APPLICATION, REALM
  };

  Command(const std::string& a, const std::string& n, const std::string& r, 
          const Arguments& args);
  ~Command(){}

  static const std::string s_add;
  static const std::string s_del;
  static const std::string s_start;
  static const std::string s_stop;
  static const std::string s_acceptor;
  static const std::string s_connection;
  static const std::string s_public_key;
  static const std::string s_private_key;
  static const std::string s_openflow;
  static const std::string s_application;
  static const std::string s_realm;

  static const std::string s_v1_0;
  static const std::string s_v1_1;
  static const std::string s_v1_2;
  static const std::string s_v1_3;
  static const std::string s_v1_3_1;

  Action action;
  Name name;
  std::string realm;

  union {
    Acceptor    acceptor;
    Connection  connection;
    std::string key;
    Version     version;
    std::string application;
  };

  parse_head          ph;
};

std::string to_string(Command::Action a);
std::string to_string(Command::Name n);
std::string to_string(const Command& c);


} // namespace config
} // namespace flog

#endif
