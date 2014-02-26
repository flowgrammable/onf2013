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

#ifndef FLOWGRAMMABLE_REACTOR_H
#define FLOWGRAMMABLE_REACTOR_H

#include <map>

#include <libflog/proto/internet.hpp>

#include "time.hpp"
#include "logger.hpp"
#include "selector.hpp"

namespace flog {

struct Reactor;

// TODO: Make this hashable.
struct Subscriber
{
  Subscriber(Reactor& r);
  virtual ~Subscriber(){}

  virtual void read(const Time& ct)  = 0;
  virtual void write(const Time& ct) = 0;
  virtual void time(const Time& ct) = 0;
  virtual bool local_addr(const net::Address& addr) = 0;

  bool operator<(const Subscriber& s) const;
  inline operator bool() const { return status; }

  Reactor& reactor;
  Time current_time;
  int fd;

  bool status;
  std::string error;
};

// TODO: Use hash tables.
using Sub_entry = std::pair<int,Subscriber*>;
using Subscribers = std::map<int,Subscriber*>;

struct Reactor {
  Reactor(Logger& lgr, const Time& t = Time());

  Logger& logger;
  bool done;
  Selector selector;
  Time timeout;

  Subscribers readers;
  Subscribers writers;
};

void run(Reactor& r);
void process(Reactor& r);
void stop(Reactor& r);

Subscriber* find_reader(Reactor& r, const net::Address& addr);
Subscriber* find_writer(Reactor& r, const net::Address& addr);
void subscribe_read(Reactor& r, Subscriber* s);
void subscribe_write(Reactor& r, Subscriber* s);
void unsubscribe_read(Reactor& r, Subscriber* s);
void unsubscribe_write(Reactor& r, Subscriber* s);

inline
Subscriber::Subscriber(Reactor& r)
  : reactor(r), current_time(), fd(-1), status(true)
{ }

inline bool
Subscriber::operator<(const Subscriber& s) const
{
  return fd < s.fd;
}

inline
Reactor::Reactor(Logger& lgr, const Time& t)
  : logger(lgr), done(false), selector(), timeout(t), readers(), writers()
{ }

inline void
stop(Reactor& r)
{
  r.done = true;
}

} // namespace flog

#endif
