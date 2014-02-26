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

#ifndef FLOWGRAMMABLE_OFP_AGENT_v1_2_HPP
#define FLOWGRAMMABLE_OFP_AGENT_v1_2_HPP

#include <libflog/proto/ofp/application.hpp>

#include "message.hpp"

namespace flog {
namespace ofp {
namespace v1_2 {

/// \brief The v1.2 OpenFlow interface for a switch
///
/// When implementing an OpenFlow switch, the Agent class should be inherited and
/// all the virtual functions should be reimplemented. The actions to be taken by
/// the switch when receiving an OpenFlow message from the controller should be put
/// in the corresponding reimplemented virtual functions. The virtual functions
/// (including init() and fini() in the base class) are invoked when a specific
/// OpenFlow message is received (or when connection is established for init() and
/// when connection is terminated for fini()). 
/// 
/// If any virtual function is not reimplemented in the derived class, the default
/// behavior is to do nothing when corresponding message is received. Virtual
/// function init() must be implemented in the derived class.  
struct Agent : flog::ofp::Application
{
  virtual ~Agent() {}

  /// Interface for receiving Experimenter message
  virtual void experimenter(const Experimenter& v, const Time& t)           {}
  /// Interface for receiving Features Request message
  virtual void feature_request(const Feature_req& fr, const Time& t)        {}
  /// Interface for receiving Get Config Request message
  virtual void get_config_request(const Get_config_req& gcr, const Time& t) {}
  /// Interface for receiving Set Config message
  virtual void set_config(const Set_config& sc, const Time& t)              {}
  /// Interface for receiving Packet Out message
  virtual void packet_out(const Packet_out& po, const Time& t)              {}
  /// Interface for receiving Flow Mod message
  virtual void flow_mod(const Flow_mod& fm, const Time& t)                  {}
  /// Interface for receiving Group Mod message
  virtual void group_mod(const Group_mod& gm, const Time& t)                {}
  /// Interface for receiving Port Mod message
  virtual void port_mod(const Port_mod& pm, const Time& t)                  {}
  /// Interface for receiving Table Mod message
  virtual void table_mod(const Table_mod& tm, const Time& t)                {}
  /// Interface for receiving Stats Request message
  virtual void stats_request(const Stats_req& sr, const Time& t)            {}
  /// Interface for receiving Barrier Request message
  virtual void barrier_request(const Barrier_req& br, const Time& t)        {}
  /// Interface for receiving Queue Get Config Request message
  virtual void queue_get_config_request(const Queue_get_config_req& qgcr, 
                                        const Time& t)                      {}
  /// Interface for receiving Role Request message
  virtual void role_request(const Role_req& rr, const Time& t)              {}
};

} // namespace v1_2
} // namespace ofp 
} // namespace flog

#endif
