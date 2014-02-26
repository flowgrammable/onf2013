#include <iostream>
#include <sstream>

#include <libopenflow/msg_v1_0.hpp>
#include <libopenflow/msg_v1_1.hpp>

template<typename T>
  bool
  runner(uint8_t v, const std::string& type, uint8_t (*tt)(const std::string&))
  {
    using namespace ofp;
    message<v1_0::payload> msg(v, tt(type), 8, 1, v1_0::payload(v1_0::hello()));
    std::cout << ofp::to_string(msg) << std::endl;
    return true;
  }

bool
synth(uint8_t version, const std::string& type)
{
  using namespace ofp;

  switch(version) {
    case v1_0::version::value:
      return runner<v1_0::payload>(version, type, v1_0::to_type);
      break;
      /*
    case v1_1::version::value:
      return runner<v1_1::payload>(version, type, v1_1::to_type);
      break;
    case v1_2::version::value:
      return runner<v1_2::payload>(version, type, v1_1::to_type);
      break;
    case v1_3::version::value:
      return runner<v1_3::payload>(version, type, v1_1::to_type);
      break;
      */
    default:
      return false;
      break;
  }

  return true;
}

int
main(int argc, char** argv)
{
  if (argc != 3) {
    std::cout << "usage error: " << argv[0] << " <version> <type>" << std::endl;
    std::exit(-1);
  }

  std::stringstream ss;
  uint8_t version;
  ss << argv[1];
  ss >> version ;

  if (not synth(version, argv[2])) {
    std::cout << "msg synt failed" << std::endl;
    std::exit(-1);
  }

  return 0;
}
