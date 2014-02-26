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

#include "bridge.hpp"

//Export your application's implementation
EXPORT_IMPLEMENTATION(Bridge)

Bridge::Bridge() 
{
  init(Time(0));
}

Bridge::~Bridge() 
{
  delete factory;
}

void
Bridge::init(const Time& t)
{
  ofp::Xid_generator<uint32_t> xid;
  factory = new Factory(xid);
  timeout = 100;
  none_priority = 0;
  src_priority = 1;
  dst_priority = 2;
  full_priority = 3;

  flow_mod_none(t);
}

void 
Bridge::packet_in(const Packet_in& pi, const Time& t)
{
  Ethernet_addr src;
  for (int i = 0; i <= 5; i++)
    src[i] = pi.data[i];
    
  if (is_unicast(src) and not alive(src, t))
    learn(src, pi.in_port, t);
 
  Ethernet_addr dst;
  for (int i = 6; i <= 11; i++)
    dst[i] = pi.data[i];
 
  if (alive(dst, t))
    flow_mod_full(src, dst, pi.in_port, t);
  else
    flow_mod_dst(src, pi.in_port, t);

  flow_mod_src(src, pi.in_port, t); 
}

void 
Bridge::flow_mod_none(const Time& t)
{
  Match m;

  Sequence<Action> actions;
  actions.push_back(Action_output(Port::CONTROLLER, -1));
  actions.push_back(Action_output(Port::FLOOD, -1));
  
  Message *msg = new Message(Flow_mod(m, 0, Flow_mod::ADD, 0, -1, 
                             none_priority, 0, Port::FLOOD, 
                             Flow_mod::SEND_FLOW_REM, actions));
 
  Formatter f;
  send(msg);
}

void 
Bridge::flow_mod_src(const Ethernet_addr& addr, uint16_t port, const Time& t)
{
  Match m;
  m.in_port = port;
  m.dl_src = addr;

  Sequence<Action> actions;
  actions.push_back(Action_output(Port::FLOOD, -1));

  uint16_t hard_timeout = c_timeval(t).tv_sec + timeout;
  Message *msg = new Message(Flow_mod(m, 0, Flow_mod::ADD, 0, hard_timeout, 
                             src_priority, 0, Port::FLOOD,
                             Flow_mod::SEND_FLOW_REM, actions));
  send(msg);
}

void 
Bridge::flow_mod_dst(const Ethernet_addr& addr, uint16_t port, const Time& t)
{
  Match m;
  m.dl_dst = addr;

  Sequence<Action> actions;
  actions.push_back(Action_output(Port::CONTROLLER, -1));
  actions.push_back(Action_output(port, -1));
  
  uint16_t hard_timeout = c_timeval(t).tv_sec + timeout;
  Message *msg = new Message(Flow_mod(m, 0, Flow_mod::ADD, 0, hard_timeout, 
                             dst_priority, 0, port,
                             Flow_mod::SEND_FLOW_REM, actions));
  send(msg);
}

void 
Bridge::flow_mod_full(const Ethernet_addr& src, const Ethernet_addr& dst, 
                      uint16_t port, const Time& t)
{
  Match m;
  m.in_port = port;
  m.dl_src = src;
  m.dl_dst = dst;

  Sequence<Action> actions;
  actions.push_back(Action_output(port, -1));
  
  uint16_t hard_timeout = c_timeval(t).tv_sec + timeout;
  Message *msg = new Message(Flow_mod(m, 0, Flow_mod::ADD, 0, hard_timeout, 
                             full_priority, 0, port,
                             Flow_mod::SEND_FLOW_REM, actions));
  send(msg);
}

bool
Bridge::alive(const Ethernet_addr& addr, const Time& t)
{
  Iterator iter = table.find(addr);
  return iter != table.end() and t < table[addr].second;
}

void 
Bridge::learn(const Ethernet_addr& addr, uint16_t port, const Time& t) 
{  
  Record r;
  r.first = port;
  r.second = Time(timeout) + t;
  table[addr] = r;  
}

bool 
Bridge::is_unicast(const Ethernet_addr& addr) 
{
  for (int i = 0; i <= 5; i++)
  {
    if (addr.data[i] != -1)
      return true;
  }
  return true;
}


