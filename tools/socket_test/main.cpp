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

#include "libflog/system/socket2.hpp"

int main(int argc, char** argv)
{
  using namespace flog;
  if(argc != 3 and argc != 4) {
    std::cerr << "usage error: " << argv[0] << " ipv4|ipv6 <addr> [port]" << std::endl;
    std::exit(-1);
  }

  std::string ipv4("ipv4");
  std::string ipv6("ipv6");

  uint16_t port = 0;
  if(argc == 4)
    port = atoi(argv[3]);

  using namespace socket;
  if(ipv4.compare(argv[1]) == 0) {
    IPv4 addr(argv[2], port);
    if(not addr)
      std::cerr << addr.error << std::endl;
    else
      std::cout << addr.to_string() << std::endl;
  } else if(ipv6.compare(argv[1]) == 0) {
    IPv6 addr(argv[2], port);
    if(not addr)
      std::cerr << addr.error << std::endl;
    else
      std::cout << addr.to_string() << std::endl;
  } else {
    std::cerr << "invalid transport: " << argv[1] << std::endl;
    std::exit(-1);
  }

  return 0;
}
