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

#include <sstream>
#include "buffer.hpp"

namespace flog {

Buffer
buffer_from_file(const std::string& file)
{
  Buffer buf;
  std::fstream input(file, std::ios::in | std::ios::binary);
  if (not input) {
    buf.bad();
  } else {
    input.seekg(0, std::ios::end);
    buf.resize(input.tellg());
    input.seekg(0, std::ios::beg);
    input.read((char*)buf.data(), buf.size());
    input.close();
  }
  return buf;
}

void 
buffer_to_file(const std::string& file, Buffer& buf)
{
  std::fstream output(file, std::ios::out | std::ios::binary);
  output.write((char*)buf.data(), buf.size());
  output.close();
}

Error_condition
to_buffer(Buffer_view& v, const Buffer& b)
{
  if (not available(v, b.size()))
    return AVAILABLE_BUFFER;
  put(v, b.data(), b.size());
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Buffer& b)
{
  if (not available(v, b.size()))
    return AVAILABLE_BUFFER;
  get(v, b.data(), b.size());
  return SUCCESS;
}

Error_condition
from_buffer(Buffer_view& v, Greedy_buffer& b)
{
  if (not remaining(v))
    return SUCCESS;
  b = Greedy_buffer(v.first, v.last);
  v.first = v.last;
  return SUCCESS;
}

std::string
to_string(const Buffer& b, Formatter& f)
{
  std::stringstream ss;
  open_block(ss, f, "Buffer");
  nvp_to_string(ss, f, "Bytes", b.size());
  close_block(ss, f, "Buffer");
  return ss.str();
}



} // namespace flog
