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


#include <iostream>

namespace flog {

inline
Pipe::Pipe(const std::string& n, int f)
  : name(n), fd(f)
{ 
  if(fd<0) {
    std::cout << std::string(strerror(errno)) << "\n";
    throw 1;
  }
}

inline
Pipe::~Pipe()
{
  if(fd > -1)
    ::close(fd);
}

inline
Read_pipe::Read_pipe(const std::string& n)
  : Pipe(n, ::open(n.c_str(), O_RDONLY | O_NONBLOCK))
{ }

inline
Write_pipe::Write_pipe(const std::string& n)
  : Pipe(n, ::open(n.c_str(), O_WRONLY | O_NONBLOCK))
{ }

template<typename T>
  inline int
  read(Read_pipe& ch, T& m)
  {
    return ::read(ch.fd, &m, sizeof(T));
  }

template<typename T>
  inline int
  write(Write_pipe& ch, T& m)
  {
    return ::write(ch.fd, &m, sizeof(T));
  }

} // namespace flog

