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

#include <sstream>

#include <libflog/proto/ofp/xid_gen.hpp>
#include <libflog/system/time.hpp>

#include "state.hpp"

namespace flog {
namespace ofp {
namespace v1_0 {

template<typename T>
inline State_result
estb_echo_interval(T& sm, const Time& t) {
  const Message *m = Message::factory(sm.gen).make_echo_req();
  State_result rlt(true);
  
  rlt.second.push_back(m);

  add_timer(sm, ECHO_REQ, 0, t + sm.config.timers.echo_res_wait);
  sm.echo_timer = t + sm.config.timers.echo_req_interval;

  return reset(rlt);
}

template<typename T>
inline State_result
estb_time(T& sm, const Time& t) {
  State_result rlt;

  // Check echo timer
  if (t >= sm.echo_timer) {
    append(rlt.second, std::move(estb_echo_interval(sm, t).second));
  }

  // Check other timers
  auto it = sm.timer.begin();
  while (it != sm.timer.end()) {
    if (t >= (*it).second) {
      State_result r;
      switch ((*it).first.second) {
        case ECHO_REQ:
          r = estb_echo_timeout(sm, t);
          break;
        default:
          r = estb_default_timeout(sm, t);
      }
      // Notice that `it' may have been invalid here due to 
      // clear() of timer in the timeout handler. Only use
      // `it' if timeout handler returns true.
      append(rlt.second, std::move(r.second));
      if (r.first == false) {
        rlt.first = false;
        return std::move(rlt);
      }
      else {
        it = sm.timer.erase(it);
      }
    }
    else {
      ++it;
    }
  }
  rlt.first = true;

  return reset(rlt);
}

template<typename T>
State_result time_impl(T& sm, const Time& t) {
  switch (sm.state) {
    case FSM_controller::FEATURE_WAIT:
      if (t >= sm.feature_timer)
        return wait_timeout(sm, t);
      else
        return true;
    case FSM_controller::ESTABLISHED: 
      return estb_time(sm, t);
    default:
      return false;
  }
}

std::string 
to_string(FSM_switch::State s)
{
  switch(s) {
    case FSM_switch::IDLE: return "IDLE";
    case FSM_switch::FEATURE_WAIT: return "FEATURE_REQ_WAIT";
    case FSM_switch::ESTABLISHED: return "ESTABLISHED";
    case FSM_switch::FAIL: return "FAIL";
    default: return "unkonwn";
  }
}

std::string 
to_string(const FSM_switch& fs)
{
  std::stringstream ss;
  ss << to_string(fs.config);
  ss << "State: " << to_string(fs.state) << "\n";
  return ss.str();
}

inline void
state_machine_fail(FSM_switch& s, const Time& t) 
{
  s.state = FSM_switch::FAIL;
  s.timer.clear();
}

inline void
add_timer(FSM_switch& s, Message_type t, uint32_t xid, const Time& to) 
{
  s.timer.insert({{xid, t}, to});
}

inline void
remove_timer(FSM_switch& s, uint32_t xid, Message_type t) 
{
  s.timer.erase({xid, t});
}

inline State_result
idle_init(FSM_switch& s, const Time& t) 
{
  s.state = FSM_switch::FEATURE_WAIT;
  s.feature_timer = t + s.config.timers.feature_req_wait;
  s.agent.init(t);

  return true;
}

inline State_result
default_init(FSM_switch& s, const Time& t) 
{
  state_machine_fail(s, t);

  return false;
}

inline State_result
wait_feature_req(FSM_switch& s, const Time& t, const Message& m)
{
  s.state = FSM_switch::ESTABLISHED;
  s.echo_timer = t + s.config.timers.echo_req_interval;

  Factory factory(s.gen);
  
  Sequence<Port> ports;

  for (auto& port : s.config.ports) {
    ports.push_back({Port::Id(port.port_no), 
                     {},
                     {},
                     Port::Config(port.config),
                     Port::State(port.state),
                     Port::Features(port.curr),
                     Port::Features(port.advertised),
                     Port::Features(port.supported),
                     Port::Features(port.peer)});

    memcpy(ports.back().hw_addr.data, port.hw_addr, 6);
    ports.back().name = port.name;
  }

  Message_vector v {
    factory.make_feature_res(s.config.feature.datapath_id,
                             s.config.feature.n_buffers, 
                             s.config.feature.n_tables, 
                             s.config.feature.capabilities, 
                             s.config.feature.actions,
                             ports)
  };
  return std::move(v);
}

inline State_result
wait_default_message(FSM_switch& s, const Time& t, const Message& m)
{
  state_machine_fail(s, t);

  return false;
}

inline State_result
wait_timeout(FSM_switch& s, const Time& t) 
{
  state_machine_fail(s, t);

  return false;
}

inline State_result
estb_echo_req(FSM_switch& s, const Time& t, const Message& m) {
  Factory fact (s.gen);
  Message_vector v {
    fact.make_echo_res()
  };
  return std::move(v);

}

inline State_result
estb_echo_res(FSM_switch& s, const Time& t, const Message& m) {
  remove_timer(s, m.header.xid, ECHO_REQ);

  return true;
}

inline State_result
estb_vendor(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.vendor(m.payload.data.vendor, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_feature_req(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.feature_request(m.payload.data.feature_req, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_get_config_req(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.get_config_request(m.payload.data.get_config_req, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_set_config(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.set_config(m.payload.data.set_config, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_packet_out(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.packet_out(m.payload.data.packet_out, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_flow_mod(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.flow_mod(m.payload.data.flow_mod, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_port_mod(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.port_mod(m.payload.data.port_mod, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_stats_req(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.stats_request(m.payload.data.stats_req, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_barrier_req(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.barrier_request(m.payload.data.barrier_req, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_queue_get_config_req(FSM_switch& s, const Time& t, const Message& m) {
  s.agent.queue_get_config_request(m.payload.data.queue_get_config_req, t);

  return reset(s.agent.tx_queue);
}

inline State_result
estb_default_message(FSM_switch& s, const Time& t, const Message& m) {
  return true;
}

inline State_result
estb_echo_timeout(FSM_switch& s, const Time& t) {
  state_machine_fail(s, t);

  return false;
}

inline State_result
estb_default_timeout(FSM_switch& s, const Time& t) {
  Message_vector v;
  return std::move(v);
}

State_result 
init(FSM_switch& s, const Time& t)
{
  switch (s.state) {
  case FSM_switch::IDLE:
    return idle_init(s, t);
  default:
    return default_init(s, t);
  }
}

State_result 
fini(FSM_switch& s, const Time& t)
{
  s.state = FSM_switch::IDLE;
  s.timer.clear();
  s.agent.fini(t);
  return false;
}

State_result 
recv(FSM_switch& s, const Time& t, const Message& m)
{
  switch (s.state) {
  case FSM_switch::FEATURE_WAIT:
    switch (m.header.type) {
    case FEATURE_REQ:
      return wait_feature_req(s, t, m) ;
    default: 
      return wait_default_message(s, t, m);
    }
  case FSM_switch::ESTABLISHED:
    switch (m.header.type) {
    case ECHO_REQ:
      return estb_echo_req(s, t, m);
    case ECHO_RES:
      return estb_echo_res(s, t, m);
    case VENDOR:
      return estb_vendor(s, t, m);
    case FEATURE_REQ:
      return estb_feature_req(s, t, m);
    case GET_CONFIG_REQ:
      return estb_get_config_req(s, t, m);
    case SET_CONFIG:
      return estb_set_config(s, t, m);
    case PACKET_OUT:
      return estb_packet_out(s, t, m);
    case FLOW_MOD:
      return estb_flow_mod(s, t, m);
    case PORT_MOD:
      return estb_port_mod(s, t, m);
    case STATS_REQ:
      return estb_stats_req(s, t, m);
    case BARRIER_REQ:
      return estb_barrier_req(s, t, m);
    case QUEUE_GET_CONFIG_REQ:
      return estb_queue_get_config_req(s, t, m);
    default:
      return estb_default_message(s, t, m);
    }
  default:
    state_machine_fail(s, t);
    return false;
  }
}

State_result 
time(FSM_switch& s, const Time& t)
{
  return time_impl(s, t);
}

std::string 
to_string(FSM_controller::State s)
{
  switch(s) {
    case FSM_controller::IDLE: return "IDLE";
    case FSM_controller::FEATURE_WAIT: return "FEATURE_RES_WAIT";
    case FSM_controller::ESTABLISHED: return "ESTABLISHED";
    default: return "unkonwn";
  }
}

std::string to_string(const FSM_controller& fc)
{
  std::stringstream ss;
  ss << to_string(fc.config);
  ss << "State: " << to_string(fc.state) << "\n";
  return ss.str();
}

inline void
state_machine_fail(FSM_controller& c, const Time& t) {
  c.state = FSM_controller::FAIL;
  c.timer.clear();
}

inline void 
add_timer(FSM_controller& c, Message_type t, uint32_t xid, const Time& to) {
  c.timer.insert({{xid, t}, to});
}

inline void
remove_timer(FSM_controller& c, uint32_t xid, Message_type t) {
  c.timer.erase({xid, t});
}

inline State_result
idle_init(FSM_controller& c, const Time& t) {
  c.state = FSM_controller::FEATURE_WAIT;
  c.feature_timer = t + c.config.timers.feature_res_wait;
  c.app.init(t);

  return std::move(Message::factory(c.gen).make_feature_req());
}

inline State_result
default_init(FSM_controller& c, const Time& t) {
  state_machine_fail(c, t);

  return false;
}

inline State_result
wait_recv_feature_res(FSM_controller& c, const Time& t, const Message& m)
{
  c.state = FSM_controller::ESTABLISHED;
  c.echo_timer = t + c.config.timers.echo_req_interval;

  c.app.feature_response(m.payload.data.feature_res, t);

  return reset(c.app.tx_queue);
}

inline State_result
wait_default_message(FSM_controller& c, const Time& t, const Message& m)
{
  state_machine_fail(c, t);

  return false;
}

inline State_result
wait_timeout(FSM_controller& c, const Time& t) {
  state_machine_fail(c, t);

  return false;
}

inline State_result
estb_echo_req(FSM_controller& c, const Time& t, const Message& m) {
  // FIXME: Don't use the factory this way.
  const Message *r = Message::factory(c.gen).make_echo_res();
  Message_vector v {r};
  
  return std::move(v);
}

inline State_result
estb_echo_res(FSM_controller& c, const Time& t, const Message& m) {
  remove_timer(c, m.header.xid, ECHO_REQ);
  return true;
}

inline State_result
estb_error(FSM_controller& c, const Time& t, const Message& m) {
  c.app.error(m.payload.data.error, t);
  return reset(c.app.tx_queue);
}

inline State_result
estb_vendor(FSM_controller& c, const Time& t, const Message& m) {
  c.app.vendor(m.payload.data.vendor, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_feature_res(FSM_controller& c, const Time& t, const Message& m) {
  c.app.feature_response(m.payload.data.feature_res, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_get_config_res(FSM_controller& c, const Time& t, const Message& m) {
  c.app.get_config_response(m.payload.data.get_config_res, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_packet_in(FSM_controller& c, const Time& t, const Message& m) {
  c.app.packet_in(m.payload.data.packet_in, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_flow_removed(FSM_controller& c, const Time& t, const Message& m) {
  c.app.flow_removed(m.payload.data.flow_removed, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_port_status(FSM_controller& c, const Time& t, const Message& m) {
  c.app.port_status(m.payload.data.port_status, t);
  return reset(c.app.tx_queue);
}

inline State_result
estb_stats_res(FSM_controller& c, const Time& t, const Message& m) {
  c.app.stats_response(m.payload.data.stats_res, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_barrier_res(FSM_controller& c, const Time& t, const Message& m) {
  c.app.barrier_response(m.payload.data.barrier_res, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_queue_get_config_res(FSM_controller& c, const Time& t, const Message& m) {
  c.app.queue_get_config_response(m.payload.data.queue_get_config_res, t);

  return reset(c.app.tx_queue);
}

inline State_result
estb_default_message(FSM_controller& c, const Time& t, const Message& m) {
  return true;
}

inline State_result
estb_echo_timeout(FSM_controller& c, const Time& t) {
  state_machine_fail(c, t);

  return false;
}

inline State_result
estb_default_timeout(FSM_controller& c, const Time& t) {
  return true;
}

State_result 
init(FSM_controller& c, const Time& t)
{
  switch (c.state) {
  case FSM_controller::IDLE:
    return idle_init(c, t);
  default:
    return default_init(c, t);
  }
}

State_result 
fini(FSM_controller& c, const Time& t)
{
  c.state = FSM_controller::IDLE;
  c.timer.clear();
  c.app.fini(t);
  
  return false;
}

State_result 
recv(FSM_controller& c, const Time& t, const Message& m)
{
  switch (c.state) {
  case FSM_controller::FEATURE_WAIT:
    switch (m.header.type) {
    case FEATURE_RES:
      return wait_recv_feature_res(c, t, m) ;
    default: 
      return wait_default_message(c, t, m);
    }
  case FSM_controller::ESTABLISHED:
    switch (m.header.type) {
    case ERROR:
      return estb_error(c, t, m);
    case VENDOR:
      return estb_vendor(c, t, m);
    case FEATURE_RES:
      return estb_feature_res(c, t, m);
    case GET_CONFIG_RES:
      return estb_get_config_res(c, t, m);
    case PACKET_IN:
      return estb_packet_in(c, t, m);
    case FLOW_REMOVED:
      return estb_flow_removed(c, t, m);
    case PORT_STATUS:
      return estb_port_status(c, t, m);
    case STATS_RES:
      return estb_stats_res(c, t, m);
    case BARRIER_RES:
      return estb_barrier_res(c, t, m);
    case QUEUE_GET_CONFIG_RES:
      return estb_queue_get_config_res(c, t, m);
    default:
      return estb_default_message(c, t, m);
    }
  default:
    state_machine_fail(c, t);
    return false;
  }
}

State_result 
time(FSM_controller& c, const Time& t)
{
  return time_impl(c, t);
}
} // namespace v1_0
} // anmespace ofp 
} // namespace flog
