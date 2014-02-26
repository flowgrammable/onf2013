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

#ifndef FLOWGRAMMABLE_MSG_H
#define FLOWGRAMMABLE_MSG_H

#include <vector>
#include <memory>
#include <sstream>

#include "utilities.hpp"
#include "buffer.hpp"

namespace flog {

// -------------------------------------------------------------------------- //
// Payload Base

/// The basic payload base is a facility that provides default behaviors that
/// are common to most messges. In particular, the base class exports the
/// derived messages type and provides default overloads for equality, string 
/// rendering, and the read/write protocols.
template<typename T, T K>
  struct Basic_payload_base
  {
    /// The static kind member denotes the enumerated value of the message
    /// type. This is used internally for construction and dispatching.
    ///
    /// \todo Do we need this any more? See kind_of().
    static constexpr T kind = K;
    
    /// The Tag type is passed as a constructor argument for variant types.
    /// It enables the compiler to dispatc to the correct constructor. 
    struct Tag {
      static constexpr T value = K;
    };
  };

// Equality comparison
//
// By default, two messages of the same type always compare equal. Note
// that uninterpreted data is 
template<typename T, T K>
  inline bool 
  operator==(const Basic_payload_base<T, K>& a, 
             const Basic_payload_base<T, K>& b) { return true; }

template<typename T, T K>
  inline bool 
  operator!=(const Basic_payload_base<T, K>& a, 
             const Basic_payload_base<T, K>& b) { return false; }

/// Returns the kind of payload. This is the same as the nested
/// kind declaration in all derived classes.
template<typename T, T K>
  constexpr T 
  kind_of(const Basic_payload_base<T, K>&) { return K; }

// Bytes
//
// Returns 0 by default. No additional bytes are added to the total size
// of a message unless otherwise specified.
template<typename T, T K>
  constexpr std::size_t 
  bytes(const Basic_payload_base<T, K>&) { return 0; }

// To string
template<typename T, T K>
  inline std::string 
  to_string(const Basic_payload_base<T, K>&, Formatter&) { return std::string(); }

// To buffer
template<typename T, T K>
  inline bool 
  to_buffer(Buffer_view&, const Basic_payload_base<T, K>&) { return true; }

// From buffer
template<typename T, T K>
  inline bool 
  from_buffer(Buffer_view&, Basic_payload_base<T, K>&) { return true; }

/// \brief Returns true.
///
/// \todo Either make this go away, or make it return a Basic_error_condition.
template<typename T, T K>
  inline bool
  is_valid(const Basic_payload_base<T, K>&) { return true; }

// -------------------------------------------------------------------------- //
// State Result

// FIXME: This does not belong here...

/// The State_result class embodies the result of a state change in a
/// protoco state machine. It is a boolean value indicating whether or not
/// the state machine will continue operating and a sequence of messages
/// that will be sent to the remote peer.
///
/// The template parameter T denotes the type of message being sent. This
/// intended to be a pointer (or union of pointers) to protocol messages.
template<typename T, typename D = std::default_delete<T>>
  struct State_result {
    using Message_vector = std::vector<T>;

    // Default construct the result. This return
    State_result() : first(true) { }

    // Move semantics
    State_result(State_result&& x) 
      : first(x.first), second(std::move(x.second)) { }

    State_result& operator=(State_result&& x) {
      first = x.first;
      second = std::move(x.second);
      return *this;
    }

    // Disable dopy semantics
    State_result(const State_result& x) = delete;
    State_result& operator=(const State_result&) = delete;
    
    // Value initialization

    // Allow implicit conversion from bool. The message list is empty.
    State_result(bool b) : first(b) { }

    // Initialize the State_result by moving the vector v into the object.
    State_result(Message_vector&& v) 
      : first(true), second(std::move(v)) { }

    // Disable copy initialization from message vectors.
    State_result(const Message_vector& v) = delete;

    // Destroy the elements in the result vector by deleting them.
    ~State_result() {
      D dtor;
      for (auto x : second)
        dtor(x);
    }
    
    // FIXME: These need better names.
    bool first;
    Message_vector second;
  };



} // namespace flog

#endif
