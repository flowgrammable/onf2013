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

#include <libflog/system/pipe.hpp>

#include "command.hpp"

void 
usage_error(char* name) 
{
  std::cerr << "usage error: " << name << " ";
  std::cerr << "Action Name Realm <attributes ...>" << std::endl;
  std::cerr << "Action: add|del|start|stop" << std::endl;
  std::cerr << "Name: acceptor|connection|public_key|private_key|openflow|application|realm" << std::endl;
  std::cerr << "Real: <realm name>" << std::endl;
  std::cerr << "Attributes:" << std::endl;
  std::cerr << "\tacceptor: tls|tcp ipv4|ipv6 <addr> [p <port>]" << std::endl;
  std::cerr << "\tconnection: tls|tcp ipv4|ipv6 <addr> [p <port>] [<addr> [p <port>]]" << std::endl;
  std::cerr << "\tpublic_key: <public key file>" << std::endl;
  std::cerr << "\tprivate_key: <private key file>" << std::endl;
  std::cerr << "\topenflow: ... ? ... ? ... " << std::endl;
  std::cerr << "\tapplication: <application module>" << std::endl;
  std::cerr << std::endl;
  std::exit(-1);
}

int main(int argc, char** argv) {
  using namespace flog;
  using namespace flog::config;

  if(argc < 4)
    usage_error(argv[0]);

  std::vector<std::string> args;
  for(int pos = 4; pos < argc; ++pos)
    args.push_back(argv[pos]);

  config::Command cmd(argv[1], argv[2], argv[3], args);

  if (not cmd) {
    std::cerr << cmd.error << std::endl;
    std::exit(-1);
  }

  std::cout << "Issuing Command" << std::endl;
  std::cout << to_string(cmd) << std::endl;

  flog::Write_pipe wp("controller.pipe");

  auto sz = write(wp, cmd);
      
  if(sz < 0) {
    std::cerr << "Write operation failed" << std::endl;
    std::cerr << strerror(errno) << std::endl;
    std::exit(-1);
  } else if(sz != sizeof(Command)) {
    std::cerr << "Write sent partial msg" << std::endl;
    std::exit(-1);
  } else {
    std::cout << "Successfully sent" << std::endl;
    std::cout << to_string(cmd) << std::endl;
  }

  return 0;
}
