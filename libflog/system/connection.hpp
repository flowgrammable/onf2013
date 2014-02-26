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

#ifndef FLOWGRAMMABLE_CONNECTION_H
#define FLOWGRAMMABLE_CONNECTION_H

#include "reactor.hpp"
#include "socket.hpp"

#include <libflog/proto/internet.hpp>

namespace flog {

struct Connection : Subscriber
{
  static const std::string module_name;
  Connection(Reactor& r, socket::Socket&& s);
  Connection(Reactor& r, const net::Address& d, 
            const net::Address& s = net::Address());

  void read(const Time& t);
  void write(const Time& t);
  void time(const Time& t);
  bool local_addr(const net::Address& addr);

  socket::Socket skt;
};

inline
Connection::Connection(Reactor& r, socket::Socket&& s)
  : Subscriber(r), skt(std::move(s))
{ }

inline
Connection::Connection(Reactor& r, const net::Address& d, const net::Address& s)
  : Subscriber(r), skt(s)
{
  skt.connect(d);
}

inline void
Connection::read(const Time& t)
{ }

inline void
Connection::write(const Time& t)
{ }

inline void
Connection::time(const Time& t)
{ }

inline bool
Connection::local_addr(const net::Address& addr)
{
  if(addr.transport != skt.transport)
    return false;
  return skt.local->match(addr);
}

} // namespace flog

#endif
