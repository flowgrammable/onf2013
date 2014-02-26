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

#ifndef FLOWGRAMMABLE_MANAGER_H
#define FLOWGRAMMABLE_MANAGER_H

#include "reactor.hpp"
#include "config.hpp"

namespace flog {

struct Manager : Subscriber
{
  static const std::string module_name;
  Manager(Reactor& r, const std::string& s);

  void read(const Time& ct);
  void write(const Time& ct) { }
  void time(const Time& t) {}
  bool local_addr(const net::Address& addr) { return false; }

  config::Read_channel channel;
};

inline
Manager::Manager(Reactor& r, const std::string& s)
  : Subscriber(r), channel(s)
{ 
  fd = channel.fd;
}

} // namespace flog

#endif
