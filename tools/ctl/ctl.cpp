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

#include "util.hpp"

void 
usage_error(char* name) 
{
  std::cerr << "usage: " << name << " ";
  std::cerr << "Action Name <attributes ...> [Target]" << std::endl;
  std::cerr << "Action: add|del|set|stop" << std::endl;
  std::cerr << "Name: remote|local|app|x509|acl|ofp|server|client" << std::endl;
  std::cerr << "\tstop: no attributes" << std::endl;
  std::cerr << "\tremote: - no attributes" << std::endl;
  std::cerr << "\tlocal: - no attributes" << std::endl;
  std::cerr << "\tapp: <name> - application name to load or unload" << std::endl;
  std::cerr << "\tx509: <name> - certificate name to load or unload" << std::endl;
  std::cerr << "\tacl: <ip>/<vlsm> to restrict to" << std::endl;
  std::cerr << "\tofp: version 1.0|1.1|1.2|1.3 - to run" << std::endl; 
  std::cerr << "\tofp: echo interval <sec>.<usec> - time between requests" << std::endl; 
  std::cerr << "\tofp: echo timeout <sec>.<usec> - time till miss" << std::endl; 
  std::cerr << "\tofp: echo miss <count> - misses till failure" << std::endl; 
  std::cerr << "\tserver: <ip>:TCP|UDP|SCTP|TLS:<port> - to listen on" << std::endl;
  std::cerr << "\tclient: <ip>:TCP|UDP|SCTP|TLS:<port> <ip>:TCP|UDP|SCTP|TLS:<port> - to connect" << std::endl;
  std::cerr << "Target: <identifier> - to target" << std::endl;
  std::cerr << std::endl;
  std::exit(-1);
}

int main(int argc, char** argv) {
  using namespace flog::config;
  //if(argc < 4)//need to check for smaller commands with stop
  //  usage_error(argv[0]);
  std::vector<std::string> arglist;
  for(int x = 1; x<argc; x++)
    arglist.push_back(argv[x]);
  Command c1 = make_command(arglist);
  for(int x = 1; x<argc; x++)
    std::cout<<argv[x]<<' ';
  std::cout<<'\n';
  //Command::Add, Command::REMOTE, "switch-group"
  std::cout << to_string(c1) << std::endl;

  return 0;
}
