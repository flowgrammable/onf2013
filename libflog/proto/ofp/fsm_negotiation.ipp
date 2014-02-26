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

namespace flog {
namespace ofp {

template<typename T>
  Negotiation<T>& 
  Negotiation<T>::operator=(const Negotiation<T>& n)
  {
    state = n.state;
    config = n.config;
    negotiated_version = n.negotiated_version;
    hello_timer = n.hello_timer;
    gen = n.gen;
    return *this;
  }

inline Stack_version 
to_stack_version(FSM_config::Supported a)
{
  switch(a) {
    case FSM_config::a1_0: return sv_1_0;
    case FSM_config::a1_1: return sv_1_1;
    case FSM_config::a1_2: return sv_1_2;
    case FSM_config::a1_3: return sv_1_3;
    default: return sv_1_0;
  }
}

template<typename T>
  std::string
  to_string(typename Negotiation<T>::State s)
  {
    switch(s) {
      case Negotiation<T>::IDLE: return "IDLE";
      case Negotiation<T>::WAIT: return "WAIT";
      case Negotiation<T>::SUCCESS: return "SUCCESS";
      case Negotiation<T>::FAILURE: return "FAILURE";
      default: return "unknown";
    }
  }

template<typename T>
  std::string 
  to_string(const Negotiation<T>& n)
  {
    std::stringstream ss;
    ss << to_string(n.config);
    ss << "State: " << to_string<T>(n.state) << "\n";
    return ss.str();
  }

template<typename T>
  inline
  Negotiation<T>::Negotiation(const FSM_config& fc, 
                              Xid_generator<uint32_t>& g)
    : state(IDLE), config(fc), gen(g)
  { }

/// state(init) ----> transition(init)
template<typename T>
  inline State_result
  idle_init(Negotiation<T>& n, const Time& t)
  {
    n.state = Negotiation<T>::WAIT;
    n.hello_timer = t + n.config.timers.hello_wait;

    return {true, {T::factory(n.gen).make_hello(n.config.supported)}};
  }

/// state(init) ----> transition(all but init)
template<typename T>
  inline State_result
  idle_fail(Negotiation<T>& n, const Time& t)
  {
    n.state = Negotiation<T>::FAILURE;
    return {false, {}};
  }

/// state(wait) ----> transition(fail)
template<typename T>
  inline State_result
  wait_fail(Negotiation<T>& n, const Time& t)
  {
    n.state = Negotiation<T>::FAILURE;
    return {false, {}};
  }

template<typename T>
  inline State_result
  wait_timer(Negotiation<T>& n, const Time& t) {
    if (t >= n.hello_timer) {
      n.state = Negotiation<T>::FAILURE;

      return {false, {}};
    }
    else {
      return {true, {}};
    }
  }

template<typename T>
  inline State_result
  idle_timer(Negotiation<T>& n, const Time& t) {
    return {false, {}};
  }

inline FSM_config::Version
negotiate_version(const FSM_config& c, FSM_config::Version remote) {

  FSM_config::Version ver = c.version <= remote ? c.version : remote;

  if (((1 << (ver - 1)) & c.supported) != 0)
    return ver;
  else
    return FSM_config::Unsup;
}

inline FSM_config::Version
negotiate_version_bitmap(const FSM_config& c, FSM_config::Supported remote) {
  FSM_config::Supported local = c.supported;

  for (uint32_t ver = 4; ver > 0; ver--) {
    if ((local & (1 << (ver - 1))) != 0 and (remote & (1 << (ver - 1))) != 0) {
      if (ver == 4)
        ver = 5;
      return FSM_config::Version(ver);
    }
  }

  return FSM_config::Unsup;
}

template<typename T>
  inline State_result
  wait_v1_0_hello(Negotiation<T>& n, const Time& t, const v1_0::Message& m)
  {
    if (FSM_config::Unsup != (n.negotiated_version = 
        negotiate_version(n.config, FSM_config::v1_0))) {
      n.state = Negotiation<T>::SUCCESS;
      return {false, {}};
    }
    else {
      std::cout << FSM_config::Unsup << std::endl;
      std::cout << negotiate_version(n.config, FSM_config::v1_0) << std::endl;

      n.state = Negotiation<T>::FAILURE;
      return {false, {T::factory(n.gen).make_hello_failed()}};
    }
  }

template<typename T>
  inline State_result
  wait_v1_1_hello(Negotiation<T>& n, const Time& t, const v1_1::Message& m)
  {
    if (FSM_config::Unsup != (n.negotiated_version = 
        negotiate_version(n.config, FSM_config::v1_1))) {
      n.state = Negotiation<T>::SUCCESS;
      return {false, {}};
    }
    else {
      n.state = Negotiation<T>::FAILURE;
      return {false, {T::factory(n.gen).make_hello_failed()}};
    }
  }

template<typename T>
  inline State_result
  wait_v1_2_hello(Negotiation<T>& n, const Time& t, const v1_2::Message& m)
  {
    if (FSM_config::Unsup != (n.negotiated_version = 
        negotiate_version(n.config, FSM_config::v1_2))) {
      n.state = Negotiation<T>::SUCCESS;
      return {false, {}};
    }
    else {
      n.state = Negotiation<T>::FAILURE;
      return {false, {T::factory(n.gen).make_hello_failed()}};
    }
  }

template<typename T>
  inline State_result
  wait_v1_3_hello(Negotiation<T>& n, const Time& t, const v1_3::Message& m)
  {
    if (FSM_config::Unsup != (n.negotiated_version = 
        negotiate_version(n.config, FSM_config::v1_3))) {
      n.state = Negotiation<T>::SUCCESS;
      return {false, {}};
    }
    else {
      n.state = Negotiation<T>::FAILURE;
      return {false, {T::factory(n.gen).make_hello_failed()}};
    }
  }

template<typename T>
  inline State_result
  wait_v1_3_1_hello(Negotiation<T>& n, const Time& t, const v1_3_1::Message& m)
  {
    if (m.payload.data.hello.elements.size() == 0
        or  std::all_of(m.payload.data.hello.elements.begin(),
                        m.payload.data.hello.elements.end(),
                        [](v1_3_1::Hello_element he)
                        { return he.header.type != v1_3_1::VERSIONBITMAP; })) {
      if (FSM_config::Unsup != (n.negotiated_version = 
          negotiate_version(n.config, FSM_config::v1_3))) {
        n.state = Negotiation<T>::SUCCESS;
        return {false, {}};
      }
      else {
        n.state = Negotiation<T>::FAILURE;
        return {false, {T::factory(n.gen).make_hello_failed()}};
      }
    }
    else {
      auto it = m.payload.data.hello.elements.begin();
      while ((*it).header.type != v1_3_1::VERSIONBITMAP)  it++;

      int num = (*it).payload.data.version_bitmap.bitmaps[0].bitmap >> 1;
        
      if (FSM_config::Unsup != (n.negotiated_version = 
          negotiate_version_bitmap(n.config, 
          FSM_config::Supported(num)))) {
        n.state = Negotiation<T>::SUCCESS;
        return {false, {}};
      }
      else {
        n.state = Negotiation<T>::FAILURE;
        return {false, {T::factory(n.gen).make_hello_failed()}};
      }
    }  
  }

/// state(init): pick the transition
template<typename T>
  State_result
  init(Negotiation<T>& n, const Time& t) {
    switch (n.state) {
      case Negotiation<T>::IDLE: return idle_init(n, t);
      default: return idle_fail(n, t);
    }
  }

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_0::Message& m) {
    switch (n.state) {
      case Negotiation<T>::WAIT:
        switch(m.header.type) {
          case v1_0::HELLO: return wait_v1_0_hello(n, t, m);
          default: return wait_fail(n, t);
        }
      default: return idle_fail(n, t);
    }
  }

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_1::Message& m) {
    switch (n.state) {
      case Negotiation<T>::WAIT:
        switch (m.header.type) {
          case v1_1::HELLO: 
            return wait_v1_1_hello(n, t, m);
          default:
            return wait_fail(n, t);
        }
      default:
        return idle_fail(n, t);
    }
  }

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_2::Message& m) {
    switch (n.state) {
      case Negotiation<T>::WAIT:
        switch (m.header.type) {
          case v1_2::HELLO: 
            return wait_v1_2_hello(n, t, m);
          default:
            return wait_fail(n, t);
        }
      default:
        return idle_fail(n, t);
    }
 }

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_3::Message& m) {
    switch (n.state) {
      case Negotiation<T>::WAIT:
        switch (m.header.type) {
          case v1_3::HELLO: 
            return wait_v1_3_hello(n, t, m);
          default:
            return wait_fail(n, t);
        }
      default:
        return idle_fail(n, t);
    }
  }

template<typename T>
  State_result
  recv(Negotiation<T>& n, const Time& t, const v1_3_1::Message& m) {
    switch (n.state) {
      case Negotiation<T>::WAIT:
        switch (m.header.type) {
          case v1_3_1::HELLO: 
            return wait_v1_3_1_hello(n, t, m);
          default:
            return wait_fail(n, t);
        }
      default:
        return idle_fail(n, t);
    }
  }


template<typename T>
  State_result
  time(Negotiation<T>& n, const Time& t) {
    switch (n.state) {
      case Negotiation<T>::WAIT:
        return wait_timer(n, t);
      default:
        return idle_timer(n, t);
    }
  }

template<typename T>
  void
  fini(Negotiation<T>& n, const Time& t) {
    n.state = Negotiation<T>::IDLE;
    
    return;
  }

} // namespace ofp
} // namespace libopenflow
