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

#include <libflog/msg_v1_0.hpp>
// #include <libopenflow/msg_v1_1.hpp>
// #include <msg_v1_2.hpp>
// #include <msg_v1_3.hpp>
// #include <msg_v1_3_1.hpp>

// Report the success or failure of a specific test.
bool 
report (const std::string& name, bool result)
{
  std::cout << "Test " << name << ": "
            << (result ? "PASSED" : "FAILED")
            << '\n';
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
    return report("move-assign", m2 == m1);
  }

/// to/from_buffer test(s)
template<typename T>
  bool
  check_rewrite(ofp::buffer& buf, const T& msg)
  {
    // Write the message into a new buffer.
    ofp::buffer b(buf.bytes());
    if (not ofp::to_buffer(b, msg))
      return report("rewrite-write", false);
    b.reset();

    // Read it back and make sure that it compares
    // equal to the original.
    T m;
    if (not ofp::from_buffer(b, m))
      return false;
    return report("rewrite-compare", m == msg);
  }

template<typename P>
  bool 
  run_version(ofp::buffer& buf, const std::string& filename)
  {
    using Message = ofp::message<P>;

    // Read the message from the buffer.  
    Message msg;
    if (not ofp::from_buffer(buf, msg))
      return report("from-buffer", false);

    // Run a set of structural tests on the message.
    if (not check_copy_construct(msg))
      return false;

    if (not check_move_construct(msg))
      return false;

    if (not check_copy_assign(msg))
      return false;

    if (not check_move_assign(msg))
      return false;

    if (not check_rewrite(buf, msg))
      return false;
    
    // Write the message to a different buffer
    ofp::buffer b(bytes(msg));
    if (not ofp::to_buffer(b, msg))
      return report("to-buffer", false);

    // And save it to a file.
    ofp::buffer_factory::to_file(filename, b);
    return true;
  }

bool 
wrap_version(ofp::buffer& buf, const std::string& filename)
{
  switch(*buf.current()) {
    case ofp::v1_0::version::value:
      return run_version<ofp::v1_0::payload>(buf, filename);
    // case ofp::v1_1::version::value:
    //   // return run_version<ofp::v1_1::payload>(buf, filename);
    //   std::cout << "v1.1 unsupported\n";
    //   return false;
    // case v1_2::version::value:
    //   // return run_version<ofp::v1_2::payload>(buf, filename);
    //   std::cout << "v1.2 unsupported\n";
    //   return false;
    // case v1_3::version::value:
    //   // return run_version<ofp::v1_3::payload>(buf, filename);
    //   std::cout << "v1.3 unsupported\n";
    //   return false;
    default:
      std::cout << "Unsupported protocol '" << int(*buf.current()) << "'\n";
      return false;
  }
}

int main(int argc, char** argv)
{
  if (argc != 3) {
    std::cerr << "usage error: " << argv[0] << " <input> <output>" << std::endl;
    std::exit(-1);
  }
  
  using namespace ofp;
  
  buffer* buf;
  if ((buf = buffer_factory::from_file(argv[1])) == nullptr) {
    std::cerr << "failed creating buffer from: " << argv[1] << std::endl;
    std::exit(-1);
  }
       
  std::cout << "Filename: " << argv[1] << std::endl;
  std::cout << buf->to_string() << std::endl;
 
  // Run the test and exit with an appropriate message
  std::string file(argv[2]);
  if (not wrap_version(*buf, file))
    std::exit(-1);
  else
    std::exit(0);
}
