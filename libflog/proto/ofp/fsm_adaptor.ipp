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

inline bool
is_established(const FSM_switch_agent& fsa)
{
  return fsa.established;
}

template<typename T>
  Result<T>
  init_negotiating(FSM_switch_agent& fsa, const Time& t)
  {
    switch(fsa.config.version) {
      case FSM_config::v1_0:
        return init(fsa.neg_v1_0, t);
        break;
      case FSM_config::v1_1:
        return init(fsa.neg_v1_1, t);
        break;
      case FSM_config::v1_2:
        return init(fsa.neg_v1_2, t);
        break;
      case FSM_config::v1_3:
        return init(fsa.neg_v1_3, t);
        break;
      case FSM_config::v1_3_1:
        return init(fsa.neg_v1_3_1, t);
        break;
      default:
        return Result<T>();
        break;
    }
  }

template<typename T>
  Result<T>
  fini_negotiating(FSM_switch_agent& fsa, const Time& t)
  {
    return Result<T>();
  }

template<typename T>
  Result<T>
  fini_established(FSM_switch_agent& fsa, const Time& t)
  {
    return Result<T>();
  }

template<typename T>
  Result<T>
  recv_negotiating(FSM_switch_agent& fsa, const Time& t, const T& m)
  {
    return Result<T>();
  }

template<typename T>
  Result<T>
  recv_established(FSM_switch_agent& fsa, const Time& t, const T& m)
  {
    return Result<T>();
  }

template<typename T>
  Result<T>
  time_negotiating(FSM_switch_agent& fsa, const Time& t)
  {
    switch(fsa.config.version) {
      case FSM_config::v1_0:
        return time(fsa.neg_v1_0, t);
        break;
      case FSM_config::v1_1:
        return time(fsa.neg_v1_1, t);
        break;
      case FSM_config::v1_2:
        return time(fsa.neg_v1_2, t);
        break;
      case FSM_config::v1_3:
        return time(fsa.neg_v1_3, t);
        break;
      case FSM_config::v1_3_1:
        return time(fsa.neg_v1_3_1, t);
        break;
      default:
        return Result<T>();
        break;
    }
  }

template<typename T>
  Result<T>
  time_established(FSM_switch_agent& fsa, const Time& t)
  {
    return Result<T>();
  }

template<typename T>
  Result<T>
  init(FSM_switch_agent& fsa, const Time& t)
  {
    if(not is_established(fsa))
      return init_negotiating<T>(fsa, t);
    else
      return init_established<T>(fsa, t);
  }
   
  
template<typename T>
  void
  fini(FSM_switch_agent& fsa, const Time& t)
  {
    if(not is_established(fsa))
      return fini_negotiating<T>(fsa, t);
    else
      return fini_established<T>(fsa, t);
  }
    
template<typename T>
  Result<T> 
  recv(FSM_switch_agent& fsa, const Time& t, const T& m)
  {
    if(not is_established(fsa))
      return recv_negotiating<T>(fsa, t, m);
    else
      return recv_established<T>(fsa, t, m);
  }
  
template<typename T>
  Result<T> 
  time(FSM_switch_agent& fsa, const Time& t)
  {
    if(not is_established(fsa))
      return time_negotiating<T>(fsa, t);
    else
      return time_established<T>(fsa, t);
  }

} // namespace ofp 
} // namespace flog
