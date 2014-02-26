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

#include <libflog/buffer.hpp>
#include <libflog/proto/ofp/v1_0/message.hpp>
#include <libflog/proto/ofp/v1_1/message.hpp>
#include <libflog/proto/ofp/v1_2/message.hpp>
#include <libflog/proto/ofp/v1_3/message.hpp>
#include <libflog/proto/ofp/v1_3_1/message.hpp>

using namespace flog;


// Report the success or failure of a specific test.
bool 
report(const std::string& name, bool result)
{
  std::cout << "Test " << name << ": "<< (result ? "Passed" : "Failed") << '\n';
  return result;
}

template<typename Message>
  bool 
  check_message(Buffer& buf, const std::string& filename)
  {
    bool result = true;

    Message msg;
    Buffer_view v1 = buf;
    if (not from_buffer(v1, msg))
      return report("from-buffer", false);
    
//    Formatter f;
//    std::cout << to_string(msg, f) << std::endl;
 
    if (not is_valid(msg))
      result &= report("is-valid", false);

    return result;
  }

bool 
check_message(Buffer& buf, const std::string& filename)
{
  switch(buf[0]) {
  case ofp::v1_0::VERSION:
    return check_message<ofp::v1_0::Message>(buf, filename);

  case ofp::v1_1::VERSION:
    return check_message<ofp::v1_1::Message>(buf, filename);

  case ofp::v1_2::VERSION:
    return check_message<ofp::v1_2::Message>(buf, filename);

  case ofp::v1_3::VERSION:
    return check_message<ofp::v1_3::Message>(buf, filename);
  /*
  case ofp::v1_3_1::VERSION:
    return check_message<ofp::v1_3_1::Message>(buf, filename);
  */
  default:
    std::cout << "Unsupported protocol '" << int(buf[0]) << "'\n";
    return false;
  }
}

int
check_buffer(Buffer& buf, const std::string& file)
{
  // Print buffer diags
  Formatter f;
  std::cout << to_string(buf, f) << std::endl;

  // Check messages in the file.  
  return check_message(buf, file) ? 0 : -1;
}

int 
main(int argc, char *argv[])
{
  if (argc != 3) {
    std::cerr << "usage error: " << argv[0] << " <input> <output>" << std::endl;
    return -1;
  }
  
  if (Buffer buf = buffer_from_file(argv[1])) {
    return check_buffer(buf, argv[2]);
  } else {
    std::cerr << "failed creating buffer from: " << argv[1] << std::endl;
    return -1;
  }
}
