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

/// copy cons test(s)
template<typename T>
  bool
  check_copy_construct(const T& msg) 
  {
    T m = msg;
    return report("copy-construct", m == msg);
  }

/// move cons test(s)
template<typename T>
  bool
  check_move_construct(const T& msg)
  {
    T m1 = msg;
    T m2 = std::move(msg);
    return report("move-construct", m2 == m1);
  }

/// move cons test(s)
template<typename T>
  bool
  check_copy_assign(const T& msg)
  {
    T m = msg;
    return report("copy-assign", m == msg);
  }

/// move cons test(s)
template<typename T>
  bool
  check_move_assign(const T& msg)
  {
    T m1 = msg;
    T m2 = std::move(m1);
    return report("move-assign", m2 == msg);
  }

/// to/from_buffer test(s)
template<typename T>
  bool
  check_rewrite(const T& msg)
  {
    // Write the message into a new buffer.
    Buffer b(bytes(msg));
    Buffer_view v1 = b;
   
    std::cout << "Msg size " << bytes(msg) << std::endl;
    std::cout << "Buffer view size " << remaining(v1) << std::endl;

    Formatter fmt;
    std::cout << to_string (msg, fmt) << '\n';

    if (not to_buffer(v1, msg)) 
    {
      std::cout << "rewrite to_buffer failed" << std::endl;
      return report("rewrite-write", false);
    }

    // Read it back and make sure that it compares equal to the original.
    T m;
    Buffer_view v2 = b;
    if (not from_buffer(v2, m))
      return false;
    // Formatter f;
    // std::cout << to_string (msg, f) << '\n';
    // std::cout << to_string (m, f) << '\n';
    return report("rewrite-compare", m == msg);
  }

template<typename Message>
  bool 
  check_message(Buffer& buf, const std::string& filename)
  {
    bool result = true;

    // Read the message from the buffer. If we don't read it,
    // then don't try to run any other tests.
    Message msg;
    Buffer_view v1 = buf;
    if (not from_buffer(v1, msg))
      return report("from-buffer", false);

    // Sanity check for overflow
    //if (remaining(v1) > bytes(msg))	
    if (remaining(v1) > 0)	
      result &= report("overflow", false);

    // Run a set of structural tests on the message, but don't
    // stop running tests just because one failed.
    result &= check_copy_construct(msg);
    result &= check_move_construct(msg);
    result &= check_copy_assign(msg);
    result &= check_move_assign(msg);
    result &= check_rewrite(msg);
    
    // Write the message to a different buffer
    Buffer b(bytes(msg));
    Buffer_view v2 = b;
    if (not to_buffer(v2, msg))
      result &= report("to-buffer", false);
    else
      buffer_to_file(filename, b);

    return result;
  }

bool 
check_message(Buffer& buf, const std::string& filename, const std::string& version)
{
  switch(buf[0]) {
  case ofp::v1_0::VERSION:
    return check_message<ofp::v1_0::Message>(buf, filename);

  case ofp::v1_1::VERSION:
    return check_message<ofp::v1_1::Message>(buf, filename);

  case ofp::v1_2::VERSION:
    return check_message<ofp::v1_2::Message>(buf, filename);

  case ofp::v1_3::VERSION:
    return (version=="1.3.1")?check_message<ofp::v1_3_1::Message>(buf, filename):check_message<ofp::v1_3::Message>(buf, filename);

  default:
    std::cout << "Unsupported protocol '" << int(buf[0]) << "'\n";
    return false;
  }
}

int
check_buffer(Buffer& buf, const std::string& file, const std::string& version)
{
  // Print buffer diags
  Formatter f;
  std::cout << to_string(buf, f) << std::endl;

  // Check messages in the file.  
  return check_message(buf, file, version) ? 0 : -1;
}

int 
main(int argc, char *argv[])
{
  if (argc != 3 && argc != 4) {
    std::cerr << "usage error: " << argv[0] << " <input> <output> [version]" << std::endl;
    return -1;
  }
  
  std::string version(argc==4?argv[3]:"");
  
  if (Buffer buf = buffer_from_file(argv[1])) {
    return check_buffer(buf, argv[2], version);
  } else {
    std::cerr << "failed creating buffer from: " << argv[1] << std::endl;
    return -1;
  }
}
