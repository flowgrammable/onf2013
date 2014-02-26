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

extern "C" {
#include <unistd.h>
}

namespace flog {

inline 
Connection::Connection(int fd)
  : file_ds(fd), begin(0), end(0), active(0), 
    buffers{ Buffer(MAX_SIZE), Buffer(MAX_SIZE) }
{ }

inline std::size_t
Connection::read()
{
  std::size_t amt = ::read(file_ds, &buffers[active][end], MAX_SIZE - end);
  end += amt;
  return amt;
}

inline std::size_t
Connection::available() const 
{
  return end - begin;
}

inline void
Connection::swap()
{
  int inactive = (active + 1) % 2;
  std::copy(&buffers[active][begin], &buffers[active][end], 
            &buffers[inactive][0]);
  end = end - begin;
  begin = 0;
  active = inactive;
}

inline Buffer_view
Connection::view(std::size_t s)
{
  std::size_t old_begin = begin;
  begin = end;
  return Buffer_view(buffers[active], &buffers[active][old_begin], 
                     &buffers[active][end]);
}

} // namespace flog
