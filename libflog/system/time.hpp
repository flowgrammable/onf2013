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

#ifndef FLOWGRAMMABLE_TIME_H
#define FLOWGRAMMABLE_TIME_H

extern "C" {
#include <sys/time.h>
}

#include <string>

namespace flog {

///
/// @brief Time type with micro-second precision
///
///
/// Time is a micro-second precision time type. This type's invariant
/// assures that there are never more than 999,999 micro-seconds in
/// the micro-second field. Times can be: constructed from c-style timeval, copy
/// constructed, copy assigned, compared, ordered, added, and subtracted.
/// 

struct Time
{
  /// Provides the upper bound for micro-seconds
  static const int Radix = 1000000;

  /// Constructs in invalid time object
  Time();

  /// Constructs a valid time object
  /// @param[in] s is seconds
  /// @param[in] us is micro-seconds
  Time(int s, int us=0);

  /// Constructs a valid time object
  /// @param[in] timeval is a c-style timeval structure
  Time(const timeval& tv);

  /// Copy constructor
  Time(const Time& t);
  /// Copy assignment
  Time& operator=(const Time& t);

  /// Return the state of this object
  /// @return Indicates whether the object is valid or invalid
  operator bool() const;

  ///
  /// Represents wether the time object is well-formed, for example, a negative
  /// time or a time with more than 999,999 micro-seconds would be ill-formed.
  ///
  
  bool good;
  int sec;

  ///
  /// The value range for micro-seconds is [0,Radix)
  ///
  
  int usec;
};

bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Time& lhs, const Time& rhs);
bool operator<(const Time& lhs, const Time& rhs);
bool operator<=(const Time& lhs, const Time& rhs);
bool operator>(const Time& lhs, const Time& rhs);
bool operator>=(const Time& lhs, const Time& rhs);

///
/// Produce a new time that is the summation of lhs and rhs.
///

Time operator+(const Time& lhs, const Time& rhs);

///
/// Produce a new time that is the difference of lhs and rhs, return
/// an invalid time if the result would be negative.
///

Time operator-(const Time& lhs, const Time& rhs);

timeval c_timeval(const Time& t);

std::string to_string(const Time& t);

inline
Time::Time()
  : good(false), sec(0), usec(0)
{ }

inline
Time::Time(int s, int us)
  : good(true), sec(s), usec(us)
{
  while(usec>=Radix) {
    usec -= Radix;
    ++sec;
  }
}

inline
Time::Time(const timeval& tv)
  : good(true), sec(tv.tv_sec), usec(tv.tv_usec)
{ }

inline
Time::Time(const Time& t)
  : good(t.good), sec(t.sec), usec(t.usec)
{ }

inline Time& 
Time::operator=(const Time& t)
{
  good = t.good;
  sec = t.sec;
  usec = t.usec;
  return *this;
}

inline timeval
c_timeval(const Time& t)
{
  return timeval{t.sec,t.usec};
}

inline bool
operator==(const Time& lhs, const Time& rhs)
{
  return lhs.good == rhs.good and lhs.sec == rhs.sec and lhs.usec == rhs.usec;
}

inline bool
operator!=(const Time& lhs, const Time& rhs)
{
  return !(lhs == rhs);
}

inline bool
operator<(const Time& lhs, const Time& rhs)
{
  if(lhs.sec < rhs.sec) return true;
  if(rhs.sec < lhs.sec) return false;
  if(lhs.usec < rhs.usec) return true;
  return false;
}

inline bool
operator<=(const Time& lhs, const Time& rhs)
{
  return lhs < rhs or lhs == rhs;
}

inline bool operator>(const Time& lhs, const Time& rhs)
{
  return not(lhs <= rhs);
}

inline bool operator>=(const Time& lhs, const Time& rhs)
{
  return not(lhs < rhs);
}

inline Time
operator+(const Time& lhs, const Time& rhs)
{
  return Time(lhs.sec+rhs.sec, lhs.usec+rhs.usec);
}

inline Time
operator-(Time lhs, const Time& rhs)
{
  if(rhs.sec < lhs.sec or (lhs.sec == rhs.sec and rhs.usec > lhs.usec)) 
    return Time();
  if(lhs.usec < rhs.usec) {
    --lhs.sec;
    lhs.usec += Time::Radix;
  }
  return Time(lhs.sec-rhs.sec, lhs.usec-rhs.usec);
}

} // namespace

#endif
