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

#include <libflog/system/config.hpp>

int 
main(int argc, char** argv) 
{
  if(argc != 2) {
    std::cerr << "usage error: " << argv[0] << " <pipe name>" << std::endl;
    std::exit(-1);
  }
  using namespace flog::config;

  Read_channel rc(argv[1]);

  while(true) {
    Command cmd;
    auto sz = read(rc, cmd);
    if(sz < 0) {
      std::cerr << "Read failed: " << strerror(errno) << std::endl;
      std::exit(-1);
    } else if(sz == 0) {
      std::cout << "writer closed pipe" << std::endl;
      std::exit(-1);
    } else if (sz != sizeof(Command)) {
      std::cerr << "Recieved malformed command" << std::endl;
      std::exit(-1);
    } else {
      std::cout << "Successfully read" << std::endl;
      std::cout << to_string(cmd) << std::endl;
    }
  }
}
