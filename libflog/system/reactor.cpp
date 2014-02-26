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

#include <string.h>

#include "reactor.hpp"

namespace flog {

void
run(Reactor& r)
{
  while(not r.done) {
    process(r);
  }
}

void
process(Reactor& r)
{
  log(r.logger, Log(Time(), Log::Info, "Reactor", to_string(r.selector)));
  // block on select
  auto result = select(r.selector);
  Time current_time;

  if (result < 0) {
    log(r.logger, Log(current_time, Log::Error, "Reactor", std::string(strerror(errno))));
  } else if (result == 0) {
    log(r.logger, Log(current_time, Log::Info, "Reactor", "timeout"));
  } else
    log(r.logger, Log(current_time, Log::Info, "Reactor", to_string(r.selector)));

  // go through read set
  for(auto entry : r.readers) {
    if(isset_read(r.selector, entry.first)) {
      entry.second->read(current_time);
    }
  }
  // go through write set
  for(auto entry : r.writers) {
    if(isset_write(r.selector, entry.first)) {
      entry.second->write(current_time);
    }
  }
}

Subscriber*
find_reader(Reactor& r, const net::Address& addr)
{
  auto itr = r.readers.begin();
  while(itr != r.readers.end()) {
    if(itr->second->local_addr(addr))
      return itr->second;
    ++itr;
  }
  return nullptr;
}

Subscriber*
find_writer(Reactor& r)
{
  return nullptr;
}

void 
subscribe_read(Reactor& r, Subscriber* s)
{
  set_read(r.selector, s->fd);
  r.readers.insert(Sub_entry(s->fd, s));
}

void 
subscribe_write(Reactor& r, Subscriber* s)
{
  set_write(r.selector, s->fd);
  r.writers.insert(Sub_entry(s->fd, s));
}

void 
unsubscribe_read(Reactor& r, Subscriber* s)
{
  clear_read(r.selector, s->fd);
  r.readers.erase(s->fd);
}

void 
unsubscribe_write(Reactor& r, Subscriber* s)
{
  clear_write(r.selector, s->fd);
  r.writers.erase(s->fd);
}

} // namespace flog
