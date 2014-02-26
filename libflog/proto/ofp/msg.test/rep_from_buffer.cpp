#include <iostream>

#include <libopenflow/msg_v1_0.hpp>
/*
#include <libopenflow/msg_v1_1.hpp>
#include <msg_v1_2.hpp>
#include <msg_v1_3.hpp>
#include <msg_v1_3_1.hpp>
*/

// Report the success or failure of a specific test.
bool 
report (const std::string& name, bool result)
{
  std::cout << "Test " << name << ": "
            << (result ? "PASSED" : "FAILED")
            << '\n';
  return result;
}

template<typename T>
  bool
  check_rewrite(ofp::buffer& buf, const T& msg)
  {
    // Write the message into a new buffer.
    ofp::buffer b(buf.bytes());
    if (not ofp::to_buffer(b, msg))
      return false;
    b.reset();

    // Read it back and make sure that it compares
    // equal to the original.
    T m;
    if (not ofp::from_buffer(b, m))
      return false;
    return report("rewrite", m == msg);
  }

template<typename P>
  bool 
  run_version(ofp::buffer& buf)
  {
    using Message = ofp::message<P>;

  // Read the message from the buffer.  
    Message msg;
    if (not ofp::from_buffer(buf, msg))
      return report("from-buffer", false);

    std::cout << to_string(msg) << std::endl ;

    return true;
  }

bool 
wrap_version(ofp::buffer& buf)
{
  switch(*buf.current()) {
    case ofp::v1_0::version::value:
      return run_version<ofp::v1_0::payload>(buf);
      break;
      /*
    case v1_1::version::value:
      return run_version<ofp::v1_1::payload>(buf, filename);
      break;
    case v1_2::version::value:
      return run_version<ofp::v1_2::payload>(buf, filename);
      break;
    case v1_3::version::value:
      return run_version<ofp::v1_3::payload>(buf, filename);
      break;
      */
    default:
      return false;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "usage error: " << argv[0] << " <input>" << std::endl;
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

  return wrap_version(*buf);

  std::exit(-1);
}
