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

#ifndef FLOWGRAMMABLE_PIPE_H
#define FLOWGRAMMABLE_PIPE_H

extern "C" {
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
}

#include <string>

namespace flog {

struct Pipe
{
  Pipe(const std::string& n, int f);
  ~Pipe();

  std::string name;
  int fd;
};

struct Read_pipe : Pipe
{
  Read_pipe(const std::string& n);
};

template<typename T>
  int read(Read_pipe& ch, T& m);

struct Write_pipe : Pipe
{
  Write_pipe(const std::string& n);
};

template<typename T>
  int 
  write(Write_pipe& ch, const T& m);

template<typename T>
  inline int
  read(Read_pipe& ch, T& m);

template<typename T>
  inline int
  write(Write_pipe& ch, T& m);

} // namespace flog

#include "pipe.ipp"

#endif
