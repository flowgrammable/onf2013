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

#ifndef FLOWGRAMMABLE_BUFFER_H
#define FLOWGRAMMABLE_BUFFER_H

#include <cassert>
#include <cstdint>
#include <algorithm>
#include <fstream>

#include "utilities.hpp"
#include "error.hpp"

/// \file buffer.hpp
/// Resources for memory buffers.

namespace flog {

// Declarations
class Buffer;
class Buffer_view;

using Byte = uint8_t;

// -------------------------------------------------------------------------- //
// Buffer

/// \brief A block of memory containing message data.
///
/// The Buffer is block of memory that stores data read from or to be
/// written to a network device. Reading and writing is primarily done through
/// the Buffer_view class.
///
/// A buffer object is in one of two states: good, and bad. A buffer in a 
/// good state can be read to and written from, whereas reading or writing 
/// from a buffer in a bad state is undefined behavior. A buffer is put into
/// a bad state when a structural violation occurs. The buffer records the
/// number of bytes missing when a structional violation occurs. Testing
/// the state of the buffer can be done by contextually converting to bool.
/// For example:
///
///     Buffer b;
///     // read from or write to b.
///     if (b) {
///       std::cout << "success!\n";
///     }
class Buffer : public std::vector<Byte>
{
public:
  enum State { GOOD, MISSING, BAD };

  Buffer();

  // Move semantics
  Buffer(Buffer&& x);
  Buffer& operator=(Buffer&& x);

  // Copy semantics
  Buffer(const Buffer& x);
  Buffer& operator=(const Buffer& x);

  // Fill initialization
  Buffer(std::size_t n);

  // Range initialization
  Buffer(const Byte* first, const Byte* last);

  /// Returns true when the state is good.
  explicit operator bool() const { return state_ == GOOD; }

  /// Returns the number of missing bytes.
  std::size_t missing() const { return missing_; }

  /// Set the number of missing bytes to n, putting the buffer
  /// in a bad state..
  void missing(std::size_t n);

  /// Put the buffer into a bad state.
  void bad();

private:
  State state_;
  std::size_t missing_;
};

inline 
Buffer::Buffer()
  : std::vector<Byte>(), state_(GOOD), missing_(0) 
{ }

inline 
Buffer::Buffer(Buffer&& x)
  : std::vector<Byte>(std::move(x)), state_(x.state_), missing_(x.missing_) 
{ }

inline Buffer&
Buffer::operator=(Buffer&& x)
{
  std::vector<Byte>::operator=(std::move(x));
  state_ = x.state_;
  missing_ = x.missing_;
  return *this;
}

inline 
Buffer::Buffer(const Buffer& x)
  : std::vector<Byte>(x), state_(x.state_), missing_(x.missing_) 
{ }

inline Buffer&
Buffer::operator=(const Buffer& x)
{
  std::vector<Byte>::operator=(x);
  state_ = x.state_;
  missing_ = x.missing_;
  return *this;
}

inline
Buffer::Buffer(std::size_t n)
  : std::vector<Byte>(n), state_(GOOD), missing_(0)
{ }

inline
Buffer::Buffer(const Byte* first, const Byte* last)
  : std::vector<Byte>(first, last), state_(GOOD), missing_(0)
{ }

inline void
Buffer::missing(std::size_t n)
{
  state_ = MISSING;
  missing_ = n;
}

inline void
Buffer::bad() { state_ = BAD; }

// Bytes
inline std::size_t
bytes(const Buffer& b) { return b.size(); }

// Is valid
constexpr bool
is_valid(const Buffer&) { return true; }

// To/from file
void   buffer_to_file  (const std::string& file, Buffer& buf);
Buffer buffer_from_file(const std::string& file); 


/// \brief Writes the value of an object to a buffer view.
///
/// The bytes of the buffer b are copied into the view, v. If the view
/// does not have sufficient bytes available, ths returns
/// AVAILABLE_BUFFER.
///
/// \relates Buffer
Error_condition to_buffer(Buffer_view& v, const Buffer& b);

/// \brief Reads the value of an object from a buffer view.
///
/// The bytes of the buffer b are copied from the view, v. If the view
/// does not have sufficient bytes available, ths returns
/// AVAILABLE_BUFFER.
///
/// \relates Buffer
Error_condition from_buffer(Buffer_view&, Buffer&);

/// \brief Returns a formatted string representation of the value.
/// \relates Buffer
std::string to_string(const Buffer&, Formatter&);


// -------------------------------------------------------------------------- //
// Greedy buffer

/// \brief A Buffer whose data occupies the remainder of a view.
///
/// A greedy buffer is a buffer that, when read from a view, will
/// consume any remaining bytes in a view. Otherwise, this class
/// is identical Buffer.
struct Greedy_buffer : Buffer
{
  using Buffer::Buffer;

  Greedy_buffer() = default;

  /// Allow conversion from buffers.
  Greedy_buffer(const Buffer& b)
    : Buffer(b) { }
};

Error_condition from_buffer(Buffer_view&, Greedy_buffer&);


// -------------------------------------------------------------------------- //
// Buffer View

/// \brief The primary interface for reading from and writing to Buffers.
///
/// The Buffer_view class is a reference to a bounded segment of memory within
/// a buffer. Reading and writng of network messages is done through the
/// buffer using the get() and put() operations. Each successive read and
/// write operation advances the bounded range of memory. 
///
/// There are a number of operations associated with Buffer_views.
///   * The remaining() function indicates the number of bytes in the bounded
///     range that can be read or written. 
///   * The available() operation determines
///     if there are enough bytes remaining to complete such an operation. 
///   * The constrain() operation returns another view whose end occurs
///     before the original (i.e., has fewer bytes).
///
/// Note that it is undefined behavior to read from or write to a view when
/// there are not enough bytes to complete the operation.
class Buffer_view
{
public:
  Buffer_view(Buffer& b)
    : buf(b), first(b.data()), last(first + b.size())
  { }

  Buffer_view(Buffer& b, Byte* f, Byte* l)
    : buf(b), first(f), last(l)
  { }

  Buffer& buf;
  Byte* first;
  Byte* last;
};

/// \defgroup view_ops Buffer View Operations

/// \ingroup view_ops
/// Returns the number of bytes remaining in the view.
inline std::size_t
remaining(const Buffer_view& v) { return v.last - v.first; }

/// \ingroup view_ops
/// Check that the buffer contains enough data to initialize or serialize
/// an object of type T. If sufficient memory is not available, then the
/// underlying buffer is put into a bad state, indicating the number of
/// bytes required to complete the read or write.
inline bool
available(const Buffer_view& v, std::size_t n)
{
  if (remaining(v) < n) {
    v.buf.missing(n - remaining(v));
    return false;
  }
  return true;
}

/// \ingroup view_ops
/// Write an scalar value x into the view v. This operation is defined only 
/// for standard integral types (char, uint8_t, uint16_t, etc.). Behavior is 
/// undefined if v does not have enough available bytes to complete the 
/// operation.
template<typename T>
  void put(Buffer_view& v, const T& x) = delete;

/// \ingroup view_ops
/// Read a scalar value x into the view v. This operation is defined only 
/// for standard integral types (char, uint8_t, uint16_t, etc.). Behavior is 
/// undefined if v does not have enough available bytes to complete the 
/// operation.
template<typename T>
  void get(Buffer_view& v, T& x) = delete;

namespace detail {

template<typename T>
  inline void 
  put(Buffer_view& v, T n)
  {
    assert(v.first + sizeof(T) <= v.last);
    *(reinterpret_cast<T*>(v.first)) = n;
    v.first += sizeof(T);
  }

template<typename T>
  inline T 
  get(Buffer_view& v, T& n)
  {
    assert(v.first + sizeof(T) <= v.last);
    n = *reinterpret_cast<T*>(v.first);
    v.first += sizeof(T);
    return n;
  }

} // namespace detail

inline void
put(Buffer_view& v, char c) { detail::put(v, c); }

inline void
put(Buffer_view& v, uint8_t n) { detail::put(v, n); }

inline void
put(Buffer_view& v, uint16_t n) { detail::put(v, n); }

inline void
put(Buffer_view& v, uint32_t n) { detail::put(v, n); }

inline void
put(Buffer_view& v, uint64_t n) { detail::put(v, n); }

template<typename T>
  inline void
  put(Buffer_view& v, T* p, std::size_t n)
  {
    while (n) { 
      put(v, *p);
      ++p;
      --n;
    }
  }

inline void
get(Buffer_view& v, char& c) { detail::get(v, c); }

inline void
get(Buffer_view& v, uint8_t& n) { detail::get(v, n); }

inline void
get(Buffer_view& v, uint16_t& n) { detail::get(v, n); }

inline void
get(Buffer_view& v, uint32_t& n) { detail::get(v, n); }

inline void
get(Buffer_view& v, uint64_t& n) { detail::get(v, n); }

template<typename T>
  inline T
  get(Buffer_view& v)
  {
    T n;
    get(v, n);
    return n;
  }

template<typename T>
  inline void
  get(Buffer_view& v, T* p, std::size_t n)
  {
    while (n) {
      get(v, *p);
      ++p;
      --n;
    }
  }

inline void
pad(Buffer_view& v, std::size_t n)
{
  v.first += n;
}

/// \ingroup view_ops
/// \brief Return a constrained view.
///
/// Behavior is undefined if the the constructed view is not within
/// the view v.
inline Buffer_view
constrain(const Buffer_view& v, std::size_t n) 
{
  assert(v.last - v.first >= std::ptrdiff_t(n));
  return Buffer_view(v.buf, v.first, v.first + n);
}

// Update a view v to the furthest position of a constrained view c
// and returns true iff c is an empty view.
//
// Behavior is undefined if the view c is not within the view v.
inline bool
update(Buffer_view& v, const Buffer_view& c)
{
  // If we didn't fully advance through the constrained, view,
  // then we cannot update v.
  if (c.first != c.last)
    return false;

  // Advance to the new view.
  v.first = c.first;
  return true;
}


} // namespace flog

#endif
