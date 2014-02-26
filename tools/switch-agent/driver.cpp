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

#include "libflog/system/manager.hpp"
#include "libflog/system/reactor.hpp"

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "usage error: " << argv[0] << " <manager pipe>" << std::endl;
    std::exit(-1);
  }

  using namespace flog;

  Logger logger("switch-agent.log");
  Reactor reactor(logger);
  Manager manager(reactor, argv[1]);
  subscribe_read(reactor, &manager);
  run(reactor);

  return 0;
}
