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

#ifndef FLOWGRAMMABLE_SELECTOR_H
#define FLOWGRAMMABLE_SELECTOR_H

extern "C" {
#include <sys/select.h>
}

#include "time.hpp"

namespace flog {

struct Selector
{
  Selector();

  int max;
  fd_set read_set;
  fd_set write_set;
};

int select(Selector& s, const Time* t = nullptr);
bool isset_read(Selector& s, int fd);
bool isset_write(Selector& s, int fd);
void set_read(Selector& s, int fd);
void set_write(Selector& s, int fd);
void clear_read(Selector& s, int fd);
void clear_write(Selector& s, int fd);

std::string to_string(const Selector& s);

inline
Selector::Selector()
  : max(-1)
{
  FD_ZERO(&read_set);
  FD_ZERO(&write_set);
}

inline int
select(Selector& s, const Time* tm)
{
  if(tm != nullptr) {
    timeval timeout = c_timeval(*tm);
    return ::select(s.max+1, &s.read_set, &s.write_set, nullptr, &timeout);
  } else
    return ::select(s.max+1, &s.read_set, &s.write_set, nullptr, nullptr);
}

inline bool 
isset_read(Selector& s, int fd)
{
  return FD_ISSET(fd, &s.read_set);
}

inline bool 
isset_write(Selector& s, int fd)
{
  return FD_ISSET(fd, &s.write_set);
}

inline void
set_read(Selector& s, int fd)
{
  FD_SET(fd, &s.read_set);
  s.max = fd > s.max ? fd : s.max;
}

inline void
set_write(Selector& s, int fd)
{
  FD_SET(fd, &s.write_set);
  s.max = fd > s.max ? fd : s.max;
}

inline int
find_max(Selector& s, int fd)
{
  for(;fd>=0;--fd) {
    if(isset_read(s, fd))
      return fd;
    if(isset_write(s, fd))
      return fd;
  }
  return -1;
}

inline void
clear_read(Selector& s, int fd)
{
  FD_CLR(fd, &s.read_set);
  s.max = find_max(s, fd);
}

inline void
clear_write(Selector& s, int fd)
{
  FD_CLR(fd, &s.write_set);
  s.max = find_max(s, fd);
}

} // namespace flog

#endif
