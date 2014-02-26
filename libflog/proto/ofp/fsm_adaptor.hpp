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

#ifndef FLOWGRAMMABLE_ADAPTOR_H
#define FLOWGRAMMABLE_ADAPTOR_H

#include "fsm_negotiation.hpp"

#include <libflog/proto/ofp/v1_0/state.hpp>
#include <libflog/proto/ofp/v1_1/state.hpp>
#include <libflog/proto/ofp/v1_2/state.hpp>
#include <libflog/proto/ofp/v1_3/state.hpp>
#include <libflog/proto/ofp/v1_3_1/state.hpp>

namespace flog {
namespace ofp {

  struct FSM_switch_agent {
    FSM_switch_agent(const FSM_config& fc, Xid_generator<uint32_t>& g);

    union {
      Negotiation<v1_0::Message> neg_v1_0;
      Negotiation<v1_1::Message> neg_v1_1;
      Negotiation<v1_2::Message> neg_v1_2;
      Negotiation<v1_3::Message> neg_v1_3;
      Negotiation<v1_3_1::Message> neg_v1_3_1;
    };

    union {
      v1_0::FSM_switch sa_v1_0;
      v1_1::FSM_switch sa_v1_1;
      v1_2::FSM_switch sa_v1_2;
      v1_3::FSM_switch sa_v1_3;
      v1_3_1::FSM_switch sa_v1_3_1;
    };

    FSM_config config;
    bool established;
  };

std::string 
to_string(const FSM_switch_agent& fsa);

inline bool
is_established(const FSM_switch_agent& fsa);

template<typename T>
  Result<T> 
  init(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  void 
  fini(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  Result<T> 
  recv(FSM_switch_agent& fsa, const Time& t, const T& m);

template<typename T>
  Result<T> 
  time(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  Result<T>
  init_negotiating(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  Result<T>
  init_established(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  Result<T>
  fini_negotiating(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  Result<T>
  fini_established(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  Result<T>
  recv_negotiating(FSM_switch_agent& fsa, const Time& t, const T& m);

template<typename T>
  Result<T>
  recv_established(FSM_switch_agent& fsa, const Time& t, const T& m);

template<typename T>
  Result<T>
  time_negotiating(FSM_switch_agent& fsa, const Time& t);

template<typename T>
  Result<T>
  time_established(FSM_switch_agent& fsa, const Time& t);

} // namespace ofp
} // namespace flog

#include "fsm_adaptor.ipp"

#endif
