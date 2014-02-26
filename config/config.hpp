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

#ifndef CFG_CONFIG_H
#define CFG_CONFIG_H
//I think this file is old and can be deleted...
//Eric

//should all of these be here....
#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <vector>

namespace cfg {

//structs or classes go here for token
/*Ipaddress*/
uint32_t string_to_int(const std::string&);
struct Ipaddress
{
  Ipaddress();
  Ipaddress(std::string);
  //add one for int inputs if needed
  uint32_t address;
  bool isValid;
};
std::string to_string(const Ipaddress&);
bool operator==(const Ipaddress&, const Ipaddress&);
//add a to int if needed

/*Listener*/
struct Listener
{
  enum Transport {invalid, tls, tcp};
  Listener(){};
  Listener(Ipaddress, Transport, uint16_t portin = 6633);
  
  //is this the best way of doing this?
  //or should listener automatically set it to 6633 with a specific
  //constructor?
  Ipaddress ip;
  Transport trans;
  uint16_t port;
};
std::string to_string(const Listener::Transport&);
std::string to_string(const Listener&);
Listener::Transport string_to_trans(const std::string&);
bool operator==(const Listener&, const Listener&);

/*Listeners*/
//TODO should this have a better and easier to see name?
struct Listeners
{
  Listeners();
  Listeners(std::vector<Listener>, std::string);

  std::vector<Listener> listeners;
  std::string name;
}; 
std::string to_string(const Listeners&);
bool operator==(const Listeners&, const Listeners&);

/*Server*/
struct Server
{
  Server();//why is this needed for the config constructor?
  Server(Listeners,std::string);
  //as new things are added to the server, add them here
  Listeners listeners;
  std::string name;
};
std::string to_string(const Server&);
bool operator==(const Server&, const Server&);

/*Config*/
struct Config
{
  Config();
  Config(Server, std::string);
  //as new things are added to the config, add them here
  Server server;
  std::string name;//do configs have names? if so what?
};
std::string to_string(const Config&);

}

#endif