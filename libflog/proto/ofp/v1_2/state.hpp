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

#ifndef FLOWGRAMMABLE_FSM_V1_2_H
#define FLOWGRAMMABLE_FSM_V1_2_H

#include <cassert>
#include <map>
#include <utility>

#include <libflog/proto/ofp/fsm_config.hpp>
#include <libflog/proto/ofp/xid_gen.hpp>
#include <libflog/proto/ofp/message.hpp>

#include "message.hpp"
#include "application.hpp"
#include "agent.hpp"

namespace flog {
namespace ofp {
namespace v1_2 {

using Timer_id = std::pair<uint32_t, Message_type>;

struct FSM_switch 
{
  enum State { IDLE, FEATURE_WAIT, ESTABLISHED, FAIL };

  FSM_switch(const FSM_config& c, 
             Xid_generator<uint32_t>& g,
             Agent& a)
    : state(IDLE), role(R_EQUAL), config(c), gen(g), agent(a) { }

  State                       state;
  Role                        role;
  const FSM_config&           config;
  std::map<Timer_id, Time>    timer;
  Time                        feature_timer;
  Time                        echo_timer;
  Xid_generator<uint32_t>&    gen;
  Agent&                      agent;
};

/*
inline
FSM_switch::FSM_switch(const FSM_config& c)
  : config(c) {}
*/

std::string to_string(FSM_switch::State s);
std::string to_string(const FSM_switch& fs);

State_result init(FSM_switch& s, const Time& t);
State_result fini(FSM_switch& s, const Time& t);
State_result recv(FSM_switch& s, const Time& t, const Message& m);
State_result time(FSM_switch& s, const Time& t);

struct FSM_controller 
{
  enum State { IDLE, FEATURE_WAIT, ESTABLISHED, FAIL };

  FSM_controller(const FSM_config& c, Xid_generator<uint32_t>& g, Application& a)
    : state(IDLE), config(c), gen(g), app(a) { }

  State                       state;
  const FSM_config&           config;
  std::map<Timer_id, Time>    timer;
  Time                        feature_timer;
  Time                        echo_timer;
  Xid_generator<uint32_t>&    gen;
  Application&                app;
};

/*
inline
FSM_controller::FSM_controller(const FSM_config& c)
  : config(c) {}
*/

std::string to_string(FSM_controller::State s);
std::string to_string(const FSM_controller& fc);

State_result init(FSM_controller& c, const Time& t);
State_result fini(FSM_controller& c, const Time& t);
State_result recv(FSM_controller& c, const Time& t, const Message& m);
State_result time(FSM_controller& c, const Time& t);

} // namespace v1_2
} // namespace ofp
} // namespace flog

#endif
