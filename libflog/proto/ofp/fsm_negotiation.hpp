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

#ifndef FLOWGRAMMABLE_FSM_NEGOTIATION_HPP
#define FLOWGRAMMABLE_FSM_NEGOTIATION_HPP

#include <vector>

#include <libflog/proto/ofp/fsm_config.hpp>
#include <libflog/proto/ofp/result_type.hpp>
#include <libflog/proto/ofp/xid_gen.hpp>
#include <libflog/proto/ofp/message.hpp>

namespace flog {
namespace ofp {

inline Stack_version 
to_stack_version(FSM_config::Supported a);

template <typename T>
  struct Negotiation {
    enum State { IDLE, WAIT, SUCCESS, FAILURE };

    Negotiation(const FSM_config& fc, Xid_generator<uint32_t>& g);
    Negotiation& operator=(const Negotiation& n);

    State                       state;
    FSM_config                  config;
    uint32_t                    negotiated_version;
    Time                        hello_timer;
    Xid_generator<uint32_t>&    gen;
  };

template<typename T>
  std::string
  to_string(typename Negotiation<T>::State s);

template<typename T>
  std::string 
  to_string(const Negotiation<T>& n);

/// state(init) ----> transition(init)
template<typename T>
  inline State_result
  idle_init(Negotiation<T>& n, const Time& t);

/// state(init) ----> transition(all but init)
template<typename T>
  inline State_result
  idle_fail(Negotiation<T>& n, const Time& t);

/// state(wait) ----> transition(fail)
template<typename T>
  inline State_result
  wait_fail(Negotiation<T>& n, const Time& t);

template<typename T>
  inline State_result
  wait_timer(Negotiation<T>& n, const Time& t);

template<typename T>
  inline State_result
  idle_timer(Negotiation<T>& n, const Time& t);

inline FSM_config::Version
negotiate_version(const FSM_config& c, FSM_config::Version remote);

inline FSM_config::Version
negotiate_version_bitmap(const FSM_config& c, FSM_config::Supported remote);

template<typename T>
  inline State_result
  wait_v1_0_hello(Negotiation<T>& n, const Time& t, const v1_0::Message& m);

template<typename T>
  inline State_result
  wait_v1_1_hello(Negotiation<T>& n, const Time& t, const v1_1::Message& m);

template<typename T>
  inline State_result
  wait_v1_2_hello(Negotiation<T>& n, const Time& t, const v1_2::Message& m);

template<typename T>
  inline State_result
  wait_v1_3_hello(Negotiation<T>& n, const Time& t, const v1_3::Message& m);

template<typename T>
  inline State_result
  wait_v1_3_1_hello(Negotiation<T>& n, const Time& t, const v1_3_1::Message& m);

/// state(init): pick the transition
template<typename T>
  State_result
  init(Negotiation<T>& n, const Time& t);

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_0::Message& m);

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_1::Message& m);

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_2::Message& m);

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_3::Message& m);

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_3_1::Message& m);

template<typename T>
  State_result
  time(Negotiation<T>& n, const Time& t);

template<typename T>
  void
  fini(Negotiation<T>& n, const Time& t);

} // namespace ofp
} // namespace libopenflow

#include "fsm_negotiation.ipp"

#endif
