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

%module flog

%include <stdint.i>
%include <std_string.i>

%{
#include <libflog/buffer.hpp>
#include <libflog/sequence.hpp>
#include <libflog/string.hpp>
%}

namespace flog {

// Buffer facilities

typedef uint8_t Byte;

struct Buffer {
  Buffer();
  Buffer(int n);

  size_t size() const;

  %extend {
    size_t __len__() const { return $self->size(); }
    Byte __getitem__(size_t n) const { return $self->operator[](n); }
  }
};

struct Greedy_buffer : Buffer { };

Buffer buffer_from_file(const std::string&);
void   buffer_to_file(const std::string&, Buffer&);

struct Buffer_view { 
  Buffer_view(Buffer&);
};


// Data types

template<typename T>
  struct Sequence { };

template<std::size_t N>
  struct Stringbuf { };

struct Formatter { };

} // namespace flog

