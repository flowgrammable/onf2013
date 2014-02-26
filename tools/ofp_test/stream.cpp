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
//#include <sstream>

#include <libflog/proto/ofp/v1_0/message.hpp>

using namespace flog;

// Report the success or failure of a specific test.
bool 
report(const std::string& name, bool result)
{
  std::cout << "Test " << name << ": "
            << (result ? "Passed" : "Failed")
            << '\n';
  return result;
}

template<typename Message>
  bool 
  run_version(Buffer_view& v)
  {
    // Read the message from the buffer.  
    Message msg;
    Formatter f;
    if (not from_buffer(v, msg)) {
      std::cout << to_string(msg, f) << std::endl ;
      return report("from-buffer", false);
    }
    std::cout << to_string(msg, f) << std::endl ;
    return true;
  }

bool
wrap_version(Buffer_view& v)
{
  switch(*v.first) {
  case ofp::v1_0::VERSION:
    return run_version<ofp::v1_0::Message>(v);
    break;
    
    /*
  case v1_1::version::value:
    return run_version<v1_1::payload>(buf);
    break;
  case v1_2::version::value:
    return run_version<v1_2::payload>(buf);
    break;
  case v1_3::version::value:
    return run_version<v1_3::payload>(buf);
    break;
  case v1_3_1::version::value:
    return run_version<v1_3_1::payload>(buf);
    break;
    */
  default:
    std::cout << "Bad version: " << int(*v.first) << std::endl;
    return false;
  }
}

Buffer 
read_stdin()
{
  using namespace ofp;

  Buffer buf(8);
  std::cin.read((char*)buf.data(), 8);
  std::size_t sz = std::cin.gcount();
  if (sz < 8) {
    std::cerr << "Hdr Bytes Missing:" << (8 - sz) << std::endl;
    buf.bad();
    return buf;
  }

  uint16_t len = *reinterpret_cast<uint16_t*>(buf.data() + 2);
  len = Foreign_byte_order::msbf(len);

  // Resize so we can read the entire buffer.
  if (std::size_t(len) - 8 > buf.size())
    buf.resize(len - 8);

  std::cin.read((char*)buf.data() + 8, len - 8);
  
  // Resize so that we hold exactly the entire buffer.
  sz = std::cin.gcount();
  if (sz < len)
    buf.resize(sz + 8);
  
  return buf;
}

int main(int argc, char** argv)
{
  if (argc != 1) {
    std::cerr << "usage error: " << argv[0] << std::endl;
    return -1;
  }

  std::size_t cnt = 0;
  while (Buffer buf = read_stdin()) {
    Buffer_view v = buf;
    std::cout << "remaining: " << remaining(v) << std::endl;
    if (not wrap_version(v)) {
      std::cout << "remaining: " << remaining(v) << std::endl;
      std::stringstream ss;
      ss << "fail_file_" << cnt;
      buffer_to_file(ss.str(), buf);
      std::cerr << "fail:" << remaining(v) << std::endl;
    }
  }
  
  return 0;
}
