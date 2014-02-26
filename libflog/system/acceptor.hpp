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

#ifndef FLOWGRAMMABLE_ACCEPTOR_H
#define FLOWGRAMMABLE_ACCEPTOR_H

#include "reactor.hpp"
#include "socket.hpp"
#include "connection.hpp"

#include <libflog/proto/internet.hpp>

namespace flog {

struct Acceptor : Subscriber
{
  static const std::string module_name;
  Acceptor(Reactor& r, const net::Address& a);
  void read(const Time& t);
  void write(const Time& t) {}
  void time(const Time& t) {}
  bool local_addr(const net::Address& addr);

  socket::Socket skt;
};

inline
Acceptor::Acceptor(Reactor& r, const net::Address& a)
  : Subscriber(r), skt(a)
{ 
  if (not skt.bind()) {
    status = false;
    error = skt.error;
  }
  else if (not skt.listen()) {
    status = false;
    error = skt.error;
  }
}

inline void
Acceptor::read(const Time& t)
{
  Connection* conn = new Connection(reactor, skt.accept());
  subscribe_read(reactor, conn);
  slog<Acceptor>(*this, Log::Info, ("Created connection: " + to_string(skt)));
}

inline bool
Acceptor::local_addr(const net::Address& addr)
{
  return skt.match(addr);
}

} // namespace flog

#endif
