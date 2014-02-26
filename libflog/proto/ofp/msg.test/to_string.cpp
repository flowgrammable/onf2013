#include <iostream>

#include <libopenflow/msg_v1_0.hpp>
#include <libopenflow/msg_v1_1.hpp>
#include <libopenflow/msg_v1_2.hpp>
#include <libopenflow/msg_v1_3.hpp>
#include <libopenflow/msg_v1_3_1.hpp>

// Report the success or failure of a specific test.
bool 
report (const std::string& name, bool result)
{
  std::cout << "Test " << name << ": "
            << (result ? "PASSED" : "FAILED")
            << '\n';
  return result;
}

template<typename P>
  bool 
  run_version(ofp::buffer& buf)
  {
    using Message = ofp::message<P>;

  // Read the message from the buffer.  
    Message msg;
    if (not ofp::from_buffer(buf, msg)) {

    std::cout << to_string(msg) << std::endl ;
      return report("from-buffer", false);
    }

    std::cout << to_string(msg) << std::endl ;

    return true;
  }

bool 
wrap_version(ofp::buffer& buf)
{
  using namespace ofp;
  switch(*buf.current()) {
    case v1_0::version::value:
      return run_version<v1_0::payload>(buf);
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
      std::cout << "Bad version: " << int(*buf.current()) << std::endl;
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
