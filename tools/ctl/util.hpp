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

#ifndef FLOWGRAMMABLE_UTIL_H
#define FLOWGRAMMABLE_UTIL_H

#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>

#include <libflog/system/config.hpp>

using namespace flog::config;
struct Some_Error : std::exception{
  Some_Error(const std::string& s)
  :errmsg(s)
  {}
  std::string errmsg;
};
flog::ipv4::Address
to_ipv4(const std::string& s)
{
  //auto length1 = s.find('.');
  return flog::ipv4::Address();
}
flog::ipv6::Address
to_ipv6(const std::string& s)
{
  return flog::ipv6::Address();
}
flog::net::Network
which_ip(const std::string& s)
{
  auto found = s.find(':');
  if(found == std::string::npos)
    return flog::net::Network::IPv6;
  return flog::net::Network::IPv4;
}
uint32_t
to_int(const std::string& in)
{
  std::stringstream ss;
  uint32_t x;
  ss<<in;
  ss>>x;
  return x;
}
flog::net::Transport
to_transport(const std::string& in)
{  
  std::string s(in);
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  if(s.compare("TCP")==0)
    return flog::net::Transport::TCP;
  if(s.compare("UDP")==0)
    return flog::net::Transport::UDP;
  if(s.compare("SCTP")==0)
    return flog::net::Transport::SCTP;
  if(s.compare("TLS")==0)
    return flog::net::Transport::TLS;
  throw Some_Error("no conversion for transport, input: "+in+"\n");
}
Command::Action
to_action(const std::string& in)
{ 
  std::string s(in);
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  if(s.compare("ADD")==0)
    return Command::Add;
  if(s.compare("DEL")==0)
    return Command::Del;
  if(s.compare("SET")==0)
    return Command::Set;
  if(s.compare("STOP")==0)
    return Command::Stop;
  if(s.compare("NOOP")==0)
    return Command::NoOp;
  //if it's at this point, we need to throw
  throw Some_Error("no conversion for action, input: "+in+"\n");
}
Command::Name
to_name(const std::string& in)
{ 
  std::string s(in);
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  if(s.compare("REMOTE")==0)
    return Command::REMOTE;
  if(s.compare("LOCAL")==0)
    return Command::LOCAL;
  if(s.compare("APP")==0)
    return Command::APP;
  if(s.compare("X509")==0)
    return Command::X509;
  if(s.compare("ACL")==0)
    return Command::ACL;
  if(s.compare("OFP")==0)
    return Command::OFP;
  if(s.compare("SERVER")==0)
    return Command::SERVER;
  if(s.compare("CLIENT")==0)
    return Command::CLIENT;
  //if it's at this point, we need to throw
  throw Some_Error("no conversion for name, input: "+in+"\n");
}
//potentially put target parser here, could be conditionally called on action
//in case of Command::Stop
flog::net::Address
parse_address(const std::string& attr)
{//string is of for
  try{
  auto length1 = attr.find(':');
  auto length2 = attr.find(':', length1+1);
  if(length1 == std::string::npos || length2 == std::string::npos)
    throw Some_Error("format is <ip>:<transport>:<port>\n");
  std::string ip = attr.substr(0,length1);
  std::string transport = attr.substr(length1+1,length2);
  std::string port = attr.substr(length2+1,std::string::npos);
  //now that we have all the pieces, how do I convert and make?
  //check and make ip
  //flog::net::Network n = which_ip(ip);
  // if(n == flog::net::Network::IPv4)
  //   auto ipaddr = to_ipv4(ip);
  // else
  //   auto ipaddr = to_ipv6(ip);
  //flog::net::Transport trans = to_transport(transport);
  uint32_t p = to_int(port);
  if(p>65535){throw Some_Error("port invalid\n");}
  //everything should be good now
  //return 
  return flog::net::Address();
  }
  catch(const Some_Error& e)
  {
    throw e;
  }
}
Command
parse_ACL(Command::Action act,const std::string& attr,const std::string& target)
{
  //take something in format of ip/vlsm and create an Acl to
  //construct a command. if there are errors, throw back up
  //what format is the ip in?
  try{
    auto found = attr.find('/');
    if(found == std::string::npos)
      throw Some_Error("format for ACL attr is <ip>/<vlsm>\n");
    std::string ip = attr.substr(0,found);
    std::string vlsm = attr.substr(found,std::string::npos);
    //now check if things are correct
    Acl acl;
    flog::net::Network n = which_ip(ip);
    uint32_t bitmask = to_int(vlsm);
    if(n == flog::net::Network::IPv4 && bitmask > 32)
      throw Some_Error("bitmask too large\n");
    else if(bitmask >128)
      throw Some_Error("bitmask too large\n");
    if(n == flog::net::Network::IPv4)
    {
      auto ipaddr = to_ipv4(ip);
      acl = Acl(ipaddr, bitmask);
    }
    else
    {
      auto ipaddr = to_ipv6(ip);
      acl = Acl(ipaddr, bitmask);
    }
    //after this point, everything should be converted and correct
    return Command(act,acl,target);
  }//end try
  catch(const Some_Error& e)
  {
    throw e;
  }

}
Command
parse_OFP(Command::Action act,const std::vector<std::string>& arglist)
{
  //many options, will need to diambiguate
  //version, interval, timeout, miss
  //version doesn't have leading 'echo'
  //interval and timeout use a time format
  return Command();//TODO
}
Command
parse_SERVER(Command::Action act, const std::string& attr)
{
  //use attr to turn format of ip:proto:port to server
  //create a sub parser for that, to share with client
  return Command();//TODO
}
Command
parse_CLIENT(Command::Action act,const std::vector<std::string>& arglist)
{
  //could have 1 or 2 attrs
  //use sub parser for ip:proto:port once or twice depending
  return Command();//TODO
}
Command
construct_command(Command::Action act, Command::Name name,
                  const std::vector<std::string>& arglist)
{
  //could check arglist length before this is called
  //only syntax is checked before a command is constructed, since
  //I don't know what valid would be in many cases
  //validity requires context I think.
  try{
    switch(name){
      case Command::REMOTE://remote and local need to be here to compile
      case Command::LOCAL://but they shouldn't ever be in this function
      {//these don't require parsing
        if(arglist.size()>=4)//forces vec of 3 items
          throw Some_Error("too many args for "+to_string(name)+"\n");
        return Command(act, name, arglist[2]);//last must be target
      }
      case Command::APP:
      case Command::X509:
      {//also these don't require parsing
        if(arglist.size()>=5)//one attr, app or cert name
          throw Some_Error("too many args for "+to_string(name)+"\n");
        return Command(act,name, arglist[2], arglist[3]);
      }
      case Command::ACL:
      {
        if(arglist.size()>=5)
          throw Some_Error("too many args for acl\n");//2 spot is ip/vlsm 
        return parse_ACL(act,arglist[2],arglist[3]);//3 spot is target
      }     
      case Command::OFP://this will be more complicated
      {
        if(arglist.size()>=6)
          throw Some_Error("too many args for ofp\n");
        return parse_OFP(act,arglist);//need whole vector since 5 or 6 args
      }
      case Command::SERVER:
      {
        if(arglist.size()>=5)
          throw Some_Error("too many args for server\n");
        return parse_SERVER(act,arglist[2]);//only one attr, ip:proto:port
      }
      case Command::CLIENT:
      {
        if(arglist.size()>=6)
          throw Some_Error("too many args for client\n");
        return parse_CLIENT(act,arglist);//could have one or two attr, ip:proto:port
      }
      default: return Command();
    }//end switch
  }//end try
  catch(const Some_Error& e)
    {throw e;}//if I throw here, easiest way to report errors
}
Command
make_command(const std::vector<std::string>& arglist)
{
  try {
    Command::Action act = to_action(arglist[0]);
    if(act == Command::Stop)
      return Command(Command::Stop);//TODO make this better?
    if(arglist.size()<3)
      throw Some_Error("Too few arguments\n");
    Command::Name name = to_name(arglist[1]);
    return construct_command(act, name, arglist);
  }
  catch(const Some_Error& e)
  {//everything will throw to this point
    std::cerr<<e.errmsg;
    std::exit(-1);//TODO not do this, maybe
  }
}

#endif