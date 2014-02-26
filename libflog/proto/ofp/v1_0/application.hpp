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

#ifndef FLOWGRAMMABLE_OFP_APPLICATION_v1_0_HPP
#define FLOWGRAMMABLE_OFP_APPLICATION_v1_0_HPP

#include <libflog/proto/ofp/application.hpp>

#include "message.hpp"

namespace flog {
namespace ofp {
namespace v1_0 {

/// \brief The interface for a controller application
///
/// An OpenFlow v1.0 control application is implemented by inheriting
/// Application class and implementing the virtual functions. The
/// virtual functions (including init() and fini() in the base class)
/// are invoked when a specific OpenFlow message is received (or when
/// connection is established for init() and when connection is
/// terminated for fini()). If any virtual function is not implemented
/// in the derived class, the default behavior is to do nothing when
/// corresponding message is received. Virtual function init() must be
/// implemented in the derived class.
struct Application : flog::ofp::Application
{
  virtual ~Application(){}

  /// Interface for receiving Error message
  virtual void error(const Error& e, const Time& t) { }
  /// Interface for receiving Vendor message
  virtual void vendor(const Vendor& v, const Time& t) { }
  /// Interface for receiving Features Reply message
  virtual void feature_response(const Feature_res& fr, const Time& t) { }
  /// Interface for receiving Get Config Reply message
  virtual void get_config_response(const Get_config_res& gcr, const Time& t) { }
  /// Interface for receiving Packet-In message
  virtual void packet_in(const Packet_in& pi, const Time& t) { }
  /// Interface for receiving Flow Removed message
  virtual void flow_removed(const Flow_removed& fr, const Time& t) { }
  /// Interface for receiving Port Status message
  virtual void port_status(const Port_status& ps, const Time& t) { }
  /// Interface for receiving Stats Reply message
  virtual void stats_response(const Stats_res& sr, const Time& t) { }
  /// Interface for receiving Barrier Reply message
  virtual void barrier_response(const Barrier_res& br, const Time& t) { }
  /// Interface for receiving Queue Get Config Reply message
  virtual void queue_get_config_response(const Queue_get_config_res& qr, const Time& t) { }
};

} // namespace v1_0
} // namespace ofp
} // namespace flog

#endif
