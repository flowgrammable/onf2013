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

#ifndef FLOWGRAMMABLE_OFP_APPLICATION_HPP
#define FLOWGRAMMABLE_OFP_APPLICATION_HPP

#include <vector>

#include <libflog/system/time.hpp>
#include <libflog/system/exporter.hpp>
#include <libflog/proto/ofp/message.hpp>

namespace flog {
namespace ofp {

/// The base class for application and switch agent interface.
struct Application {

  Application() { }
  
  virtual ~Application() { }

  /// Transmit a message.
  void send(Common_message m) { tx_queue.push_back(m); }

  /// Interface init is invoked by Flowgrammable state machine when
  /// the lower layer (TCP/TLS) connection is established with the
  /// other end of OpenFlow device.
  virtual void init(const Time& t) = 0;

  /// Interface fini is invoked by Flowgrammable state machine when
  /// connection with the other end of OpenFlow device is
  /// terminated.
  virtual void fini(const Time& t) { };

  /// The queue of messages to be sent.
  Message_vector tx_queue;
};

} // namespace ofp
} // namespace flog

#endif
