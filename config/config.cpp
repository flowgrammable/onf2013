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

#include "config.hpp"
//I think this file is old and can be deleted...
//Eric
namespace cfg {
uint32_t
string_to_int(const std::string& to_convert)
{
  std::stringstream ss;
  uint32_t returnval;
  ss<<to_convert;
  ss>>returnval;
  return returnval;
}
//
// Ipaddress
//
Ipaddress::Ipaddress()
{
  //std::cout<<"default Ipaddress constructor called\n";
}
Ipaddress::Ipaddress(std::string input)
{
  //this constructor assumes the string is of the format ddd.ddd.ddd.ddd
  //where there are at most 3 digits in each group. parser will need to check
  //that groups aren't greater than 4 digits, and we will check for >255 here
  using namespace std;
  stringstream ss;
  uint32_t group1,group2,group3,group4;
  size_t length1,length2,length3;
  length1 = input.find('.');
  length2 = input.find('.',length1+1);
  length3 = input.find('.',length2+1);

  length1 = input.find('.');
  group1 = string_to_int(input.substr(0,length1));

  length2 = input.find('.',length1+1);
  group2 = string_to_int(input.substr(length1+1,length2-length1-1));

  length3 = input.find('.',length2+1);
  group3 = string_to_int(input.substr(length2+1,length3-length2-1));
  group4 = string_to_int(input.substr(length3+1,string::npos));
  address = (group1<<24) | (group2<<16) | (group3<<8) | group4;
  if(group1>255 || group2>255 || group3>255 || group4>255)
    isValid = false;//TODO better solution later
  else
    isValid = true;
  //surely there is a better way to do this, but oh well
} 
std::string
to_string(const Ipaddress& ip)
{
  std::stringstream ss;
  ss<<(ip.address >> 24)<<'.'<<((ip.address >> 16) & 0xff)<<'.';
  ss<<((ip.address >> 8) & 0xff)<<'.'<<(ip.address & 0xff);
  return ss.str();
}
bool
operator==( const Ipaddress& lhs, const Ipaddress& rhs)
{
  if(lhs.address == rhs.address)
    return true;
  else
    return false;
}

//
// Listener
//
Listener::Listener(Ipaddress ipin, Transport transin, uint16_t portin)
{
  //portin is default 6633, potentially check if transport is tls for that
  //to be ok?
  ip = ipin;
  //do i need to check if portin < (2^16 - 1)?
  port = portin;
  trans = transin;
}
std::string
to_string(const Listener::Transport& trans)
{
  if(trans == Listener::Transport::tls)
    return "tls";
  else
    return "tcp";
}
std::string
to_string(const Listener& listen)
{
  std::stringstream ss;
  ss<<to_string(listen.ip)<<' '<<to_string(listen.trans);
  //should I use tls_default here instead of 6633, magic constant
  if((listen.trans == Listener::Transport::tls) && (listen.port == 6633))
    return ss.str();//default for tls
  else
  {
    ss<<' '<<listen.port;
    return ss.str();
  }
}
Listener::Transport
string_to_trans(const std::string& input)
{
  if(input == "tls")
    return Listener::Transport::tls;
  if(input == "tcp")
    return Listener::Transport::tcp;
  return Listener::Transport::invalid;
}
bool
operator ==(const Listener& lhs, const Listener& rhs)
{
  if((lhs.ip == rhs.ip) &&
     (lhs.port == rhs.port) &&
     (lhs.trans == rhs.trans))
    return true;
  else
    return false;
}
//
// Listeners
//
Listeners::Listeners()
{
  //nothing here right now
}
Listeners::Listeners(std::vector<Listener> ls, std::string in_name)
{
  listeners = ls;
  name = in_name;
}
std::string
to_string(const Listeners& ls)
{//does output formatting
  std::stringstream ss;
  if(!ls.name.empty())
    ss<<"  "<<ls.name<<" = listen {\n";
  else
    ss<<"  listen {\n";
  for(unsigned int ndx = 0; ndx < ls.listeners.size(); ndx++)
  {
    ss<<"    "<<to_string(ls.listeners[ndx])<<'\n';
  }
  ss<<"  }\n";
  return ss.str();
}
bool
operator ==(const Listeners& lhs, const Listeners& rhs)
{
  if(lhs.listeners == rhs.listeners)
    return true;
  else
    return false;
}
//
// Server
//
Server::Server()
{
  //std::cout<<"default Server constructor called\n";
}
Server::Server(Listeners inlists, std::string inname)
{
  listeners = inlists;
  name = inname;
}
std::string
to_string(const Server& serv)
{
  std::stringstream ss;
  if(!serv.name.empty())
    ss<<serv.name<<" = server {\n";
  else
    ss<<"server {\n";
  ss<<to_string(serv.listeners);
  ss<<"}\n";
  return ss.str();
}
bool
operator == (const Server& lhs, const Server& rhs)
{
  if (lhs.listeners == rhs.listeners)//do names need to be the same?
    return true;
  else
    return false;
}

//
// Config
//
Config::Config()
{
  //nothing here right now
}
Config::Config(Server serv, std::string inname)
{
  server = serv;
  name = inname;
}
std::string
to_string(const Config& con)
{//currently same as server to string, may change though soon
  std::stringstream ss;
  ss<<to_string(con.server)<<'\n';
  return ss.str();
}


}//end namespace