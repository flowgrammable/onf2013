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


#ifndef FLOWGRAMMABLE_ERROR_HPP
#define FLOWGRAMMABLE_ERROR_HPP

#include <iosfwd> // FIXME: Get rid of me.

namespace flog {

template<typename C> struct Condition;
template<typename C> struct Condition_decl;

/// The Condition template represents the results of reading, writing, or
/// validating a message. The condition can be evaluated in an if
/// statement to determine if the operation succeeded. For example, we
/// can validate a message like this:
///
///   Message m = ...;
///   if (is_valid(m))
///     cout << "success\n";
///
/// If an operation fails, the Condition's code member is set to one of
/// the values of the nested Code enumeration. There is an enumeration
/// value for every possible failure in this message. The interpretation
/// of those codes is left to the user. An example would be to respond with
/// an Error message:
///
///   if (m.code == BAD_HEADER_LENGTH)
///     return error_bad_length(m);
///
/// The specific codes representing failures are specified by the type
/// parameter C. This is required to be an enumeration type (an error code)
/// where the value 0 indicates success.
///
/// \todo Describe the naming conventions used to define values of the
/// error code argument.
///
/// Note the name "condition" comes from the std::error_condition
/// facility in the C++ standard library. This represents a testable
/// condition resulting from the invocation of a procedure.
template<typename C>
  struct Condition {
    using Code = C;
    static constexpr Code SUCCESS = Code(0);
    static constexpr Code FAILURE = Code(-1);

    /// \brief Default construct a condition.
    ///
    /// Initialize the message with the SUCCESS code.
    constexpr Condition() : code(SUCCESS) { }

    /// \brief Construct the condition.
    ///
    /// Intitialize the message result with the result code c.
    constexpr Condition(Code c) : code(c) { }

    /// Constructs a Condition from some other type of error code. Initialize
    /// the condition with a reinterpreted value of some other error condition
    /// T. This effectively embeds an error code in a different category until
    /// it can be reinterpreted later.
    ///
    /// Note that the success/failure property is still preserved as long
    /// as T is a valid error code.
    ///
    /// This is used to return error codes through Sequence.
    template<typename T>
      explicit Condition(T t) : code((Code)(int)t) { }

    /// Constructs a Condition from some other Condition type.
    template<typename T>
      Condition(Condition<T> c) : Condition(c.code) { }

    /// Allow implicit construction from bool.
    ///
    /// \todo Remove this constructor when adoption is complete.
    constexpr Condition(bool b) : code(b ? SUCCESS : FAILURE) { }


    /// Allows implicit conversion to bool. Returns true iff code == SUCCESS 
    /// and false otherwise.
    ///
    /// \todo We allow implicit conversion to prevent breakage while we
    /// upgrade to the error_condition facility. Make this an explicit 
    /// conversion to bool once its use has been broadly adopted.
    ///
    /// \todo At some point in the future, make the test code != SUCCESS
    /// because it lets us write this `if (auto err = to_buffer(...))`
    /// when we want to react to errors.
    operator bool() const { return code == SUCCESS; }

    Code code;
  };

/// Returns an error condition based on a predicate.
///
/// If the condition b is true, the resulting error condition will evaluate
/// to SUCCESS. Otherwise, the condition will evaluate to the code c.
template<typename C>
  constexpr Condition<C> ok(bool b, C c) {
    return b ? Condition<C>() : Condition<C>(c);
  }

/// Used to capture the test of an Error_condition in an `if` statement.
/// The Condition_decl class is identical to the Condition class except that
/// it inverts its conversion-to-bool test. The Condition_decl evaluates to
/// true when an error is present. This allows the following use pattern:
///
///    if (Condition_decl<C> err = ...)
///      return err;
///
/// This greatly simplifies the interface.
///
/// \todo The long-term plan is to phase out this class after Error_condition
/// is universally adopted and then change the condition above.
template<typename C>
  struct Condition_decl : Condition<C> 
  {
    using Condition<C>::Condition;

    /// Constructs a Condition_decl from any other Condition type.
    template<typename T>
      Condition_decl(Condition<T> c) : Condition<C>(c) { }

    /// Converts the Condition_decl to bool.
    explicit operator bool() const { return this->code != this->SUCCESS; }
  };


/// \brief Error codes for basic facilities.
///
/// The error codes in the Basic_error_code class describe failures that
/// can occur in general facilities such as buffers and strings.
///
/// Note that all other error codes must essentially include...
enum Error_code {
  FAILIURE = -1,    ///< General failure
  SUCCESS  = 0,     ///< Success

  AVAILABLE_BUFFER, ///< Not enough bytes to read a buffer
  AVAILABLE_STRING, ///< Not enough bytes to read a string

  EXCESS_SEQUENCE   ///< Excess data in a sequence
};

using Error_condition = Condition<Error_code>;
using Error_decl = Condition_decl<Error_code>;



} // namespace flog

#endif
