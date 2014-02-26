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

#ifndef FLOWGRAMMABLE_CONNECTION_HPP
#define FLOWGRAMMABLE_CONNECTION_HPP

#include "buffer.hpp"

namespace flog {

class Connection
{
  public:

    static const int MAX_SIZE = 2048;

    Connection(int fd);

    std::size_t read();
    std::size_t available() const;
    void swap();
    Buffer_view view(std::size_t s);

  private:

    int file_ds;

    std::size_t begin;
    std::size_t end;

    int active;
    Buffer buffers[2];
};

} // namespace flog

#include "connection.ipp"

#endif
