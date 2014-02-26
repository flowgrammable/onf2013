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

#include "eval.hpp"
#include <errno.h>
namespace cfg {

flog::ipv4::Address
make_jasson_ipv4(const Ipv4_expr* i)
{
  uint32_t temp = 0;
  temp = temp & i->g1->val;
  temp = temp<<8;
  temp = temp & i->g2->val;
  temp = temp<<8;
  temp = temp & i->g3->val;
  temp = temp<<8;
  temp = temp & i->g4->val;
  temp = temp<<8;
  return flog::ipv4::Address(temp);
}

flog::ipv6::Address
make_jasson_ipv6(const Ipv6_expr* i)
{
  uint8_t a[16];
  int x = 0;
  for(auto h:i->groups)
  {//TODO find out if endianness hurts us here
    a[x] = h->val & 0xff; x++;
    a[x] = h->val >> 8;   x++;
  }
  return flog::ipv6::Address(a);
}
std::string
to_string(const Ipv4_expr* i)
{
  std::stringstream ss;
  ss<<i->g1->val<<'.'<<i->g2->val<<'.'<<i->g3->val<<'.'<<i->g4->val;
  return ss.str();
}
std::string
to_string(const Ipv6_expr* i)
{
  std::stringstream ss;
  std::string delimit = "";
  for(auto h:i->groups)
  {
    ss<<delimit<<std::hex<<h->val;
    delimit = ":";
  }
  return ss.str();
}
std::string
to_string(Listener_expr::Proto p)
{
  if(p == Listener_expr::tcp)
    return "tcp";
  return "tls";
}

std::string
to_string(uint32_t i)
{
  std::stringstream ss;
  ss<<i;
  return ss.str();
}

std::string
get_type(const Expr* e)
{
  Print_type pt;
  e->t->accept(pt);
  return pt.ss.str();
}

void 
Evaluator::eval_realm(const Record_expr* re)
{//TODO clean this up...
  for(auto e:re->record)
  {//either list of addr, or private key
    auto bind = dynamic_cast<const Bind_expr*>(e);
    if(get_type(bind->rhs).compare("address list")==0)
    {
      auto le = dynamic_cast<const List_expr*>(bind->rhs);
      //list of addresses, need to cast each one
      for(auto a:le->list)
      {
        auto addr = dynamic_cast<const Listener_expr*>(a);
        auto ip4 = dynamic_cast<const Ipv4_expr*>(addr->ip1);
        if(ip4!=nullptr)
        {
          std::string val = "./ctl add acceptor ";
          if(realm_name.compare("")!=0)
            val= val + realm_name + ' ';
          val = val + to_string(addr->p) + ' ' + to_string(ip4);
          val = val + ' ' + to_string(addr->port1->val);
          commands.push_back(val);
          continue;
        }
        else
        {
          auto ip6 = dynamic_cast<const Ipv6_expr*>(addr->ip1);
          std::string val = "./ctl add acceptor ";
          if(realm_name.compare("")!=0)
            val= val + realm_name + ' ';
          val = val + to_string(addr->p) + ' ' + to_string(ip6);
          val = val + ' ' + to_string(addr->port1->val);
          commands.push_back(val);
          continue;
        }
      }
    }
    else if(get_type(bind->rhs).compare("str")==0)
    {
      auto str = dynamic_cast<const Str_expr*>(bind->rhs);
      std::string val = "./ctl add private_key ";
      if(realm_name.compare("")!=0)
        val= val + realm_name + ' ';
      val= val +str->val;
      commands.push_back(val);
      continue;
    }
    else
      std::cout<<"error! realm\n";
  }
}

void
Evaluator::eval_connector(const Record_expr* re)
{//TODO clean this up...
  for(auto e:re->record)
  {//either list of addr, or private key
    auto bind = dynamic_cast<const Bind_expr*>(e);
    if(get_type(bind->rhs).compare("connection list")==0)
    {
      auto le = dynamic_cast<const List_expr*>(bind->rhs);
      //list of addresses, need to cast each one
      for(auto a:le->list)
      {
        auto addr = dynamic_cast<const Listener_expr*>(a);
        auto ip4_1 = dynamic_cast<const Ipv4_expr*>(addr->ip1);
        if(ip4_1!=nullptr)
        {//first ip is ipv4
          std::string val = "./ctl add connection ";
          val = val + to_string(addr->p) + ' ' + to_string(ip4_1);
          val = val + ' ' + to_string(addr->port1->val);
          auto ip4_2 = dynamic_cast<const Ipv4_expr*>(addr->ip2);
          if(ip4_2!=nullptr)
          {//second is ipv4
            val = val + ' ' + to_string(ip4_2) + ' ' +to_string(addr->port2->val);
            commands.push_back(val);
            continue;
          }
          else
          {//second is ipv6
            auto ip6_1 = dynamic_cast<const Ipv6_expr*>(addr->ip2);
            val = val + ' ' + to_string(ip6_1) + ' ' +to_string(addr->port2->val);
            commands.push_back(val);
            continue;
          }
        }
        else
        {//first is ipv4
          auto ip6_1 = dynamic_cast<const Ipv6_expr*>(addr->ip1);
          std::string val = "./ctl add connection ";
          val = val + to_string(addr->p) + ' ' + to_string(ip6_1);
          val = val + ' ' + to_string(addr->port1->val);
          auto ip4_2 = dynamic_cast<const Ipv4_expr*>(addr->ip2);
          if(ip4_2!=nullptr)
          {//second is ipv4
            val = val + ' ' + to_string(ip4_2) + ' ' +to_string(addr->port2->val);
            commands.push_back(val);
            continue;
          }
          else
          {//second is ipv6
            auto ip6_2 = dynamic_cast<const Ipv6_expr*>(addr->ip2);
            val = val + ' ' + to_string(ip6_2) + ' ' +to_string(addr->port2->val);
            commands.push_back(val);
            continue;
          }
        }
      }
    }
    else if(get_type(bind->rhs).compare("str")==0)
    {
      auto str = dynamic_cast<const Str_expr*>(bind->rhs);
      std::string val = "./ctl add private_key ";
      if(realm_name.compare("")!=0)
        val= val + realm_name + ' ';
      val= val +str->val;
      commands.push_back(val);
      continue;
    }
    else
      std::cout<<"error! connector\n";
  }
}

void 
Evaluator::eval_authentication(const Record_expr* re)
{//TODO clean this up...
  for(auto e:re->record)
  {//either list of x509, or acl
    auto bind = dynamic_cast<const Bind_expr*>(e);
    if(get_type(bind->rhs).compare("str list")==0)
    {
      auto le = dynamic_cast<const List_expr*>(bind->rhs);
      //list of strings, need to cast each one
      for(auto s:le->list)
      {
        auto str = dynamic_cast<const Str_expr*>(s);
        std::string val = "./ctl add public_key ";
        if(realm_name.compare("")!=0)
          val= val + realm_name + ' ';
        val= val +str->val;
        commands.push_back(val);
        continue;
      }
    }
    else if(get_type(bind->rhs).compare("network list")==0)
    {
      //put acl stuff here
    }
    else
      std::cout<<"error! authen\n";
  }
}

void 
Evaluator::eval_initialization(const Record_expr* re)
{//TODO clean this up...
  for(auto e:re->record)
  {//need to find only the important bits, version and app
    auto bind = dynamic_cast<const Bind_expr*>(e);
    auto ofp = dynamic_cast<const Record_expr*>(bind->rhs);//we know it's an ofp
    for(auto item:ofp->record)
    {
      auto bind_item = dynamic_cast<const Bind_expr*>(item);
      if(get_type(bind_item->rhs).compare("version")==0)//succesful cast
      {//found version, add it
        auto check_item = dynamic_cast<const Ver_expr*>(bind_item->rhs);
        std::string val = "./ctl add openflow ";
        if(realm_name.compare("")!=0)
          val= val + realm_name + ' ';
        val= val +check_item->val;
        commands.push_back(val);
        continue;
      }
      if(get_type(bind_item->rhs).compare("str")==0)
      {//found app, run it
        auto check_item= dynamic_cast<const Str_expr*>(bind_item->rhs);
        std::string val = "./ctl start application ";
        if(realm_name.compare("")!=0)
          val= val + realm_name + ' ';
        val= val +check_item->val;
        commands.push_back(val);
        continue;
      }
      //std::cout<<get_type(bind_item->rhs)<<'\n';
    }
  }
}

void
Evaluator::evaluate()
{
  //try{
    //flog::config::Write_channel wc;//("config_pipe");//I would make this a member, but it
    //doesn't work, I think it's because there is no default constructor
  for(auto e: et)//find the realm name
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);
    if(b==nullptr)//assume only records are important at the top level
      continue;
    const Record_expr* re = dynamic_cast<const Record_expr*>(b->rhs);
    const Record_Type* rt = dynamic_cast<const Record_Type*>(re->t);
    if(rt->name == Record_Type::Realm)
    {//grab realm name here
      realm_name = b->lhs->name;
      break;
    }
  }
  if (realm_name.compare("")!=0)
    commands.push_back("./ctl add realm "+realm_name);
  for(auto e: et)
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);
    if(b==nullptr)
      continue;
    const Record_expr* re = dynamic_cast<const Record_expr*>(b->rhs);
    const Record_Type* rt = dynamic_cast<const Record_Type*>(re->t);
    if(rt->name == Record_Type::Realm)
    {
      eval_realm(re);
      continue;
    }
    if(rt->name == Record_Type::Connector)
    {
      eval_connector(re);
      continue;
    }
    if(rt->name == Record_Type::Authen)
    {
      eval_authentication(re);
      continue;
    }
    if(rt->name == Record_Type::Init)
    {
      eval_initialization(re);
      continue;
    }
  }
  // }
  // catch(int x)
  // {
  //   std::cout<<"error writing, "<<strerror(errno)<<'\n';
  // }
}

}//end namespace