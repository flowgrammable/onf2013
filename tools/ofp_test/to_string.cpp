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

#include <libflog/proto/ofp/v1_0/message.hpp>
#include <libflog/proto/ofp/v1_1/message.hpp>
#include <libflog/proto/ofp/v1_2/message.hpp>
#include <libflog/proto/ofp/v1_3/message.hpp>

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
  run_version(Buffer& buf)
  {
    // Read the message from the buffer.  
    Message msg;
    Formatter f;
    Buffer_view v = buf;
    if (not from_buffer(v, msg)) {
      std::cout << to_string(msg, f) << std::endl ;
      return report("from-buffer", false);
    }
    std::cout << to_string(msg, f) << std::endl ;
    return true;
  }

bool
wrap_version(Buffer& buf)
{
  switch(buf[0]) {
  case ofp::v1_0::VERSION:
    return run_version<ofp::v1_0::Message>(buf);
    break;    
  case ofp::v1_1::VERSION:
    return run_version<ofp::v1_1::Message>(buf);
    break;
  case ofp::v1_2::VERSION:
    return run_version<ofp::v1_2::Message>(buf);
    break;
  case ofp::v1_3::VERSION:
    return run_version<ofp::v1_3::Message>(buf);
    break;
    /*
  case v1_3_1::version::value:
    return run_version<v1_3_1::payload>(buf);
    break;
    */
  default:
    std::cout << "Bad version: " << int(buf[0]) << std::endl;
    return false;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "usage error: " << argv[0] << " <input>" << std::endl;
    return -1;
  }
  
  if (Buffer buf = buffer_from_file(argv[1])) {
    Formatter f;
    std::cout << to_string(buf, f) << std::endl;
    return wrap_version(buf);
  } else {
    std::cerr << "failed creating buffer from: " << argv[1] << std::endl;
    return -1;    
  }
  return 0;
}
