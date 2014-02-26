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

#ifndef FLOWGRAMMABLE_STRING_H
#define FLOWGRAMMABLE_STRING_H

#include <cstdint>
#include <cstring>
#include <string>
#include <algorithm>

#include "error.hpp"

namespace flog {

namespace detail {

template<std::size_t N>
  inline std::size_t 
  strnlen(const char* s)
  {
    std::size_t n = 0;
    while (s && n < N && *s)
      ++n;
    return n;
  }

// Copy at most n characters from in into out. Zero-fill the remaining
// characters of the string.
template<std::size_t N>
  inline void
  zero_copy(const char* in, char* out)
  {
    std::fill(std::copy_n(in, strnlen<N>(in), out), out + N, 0);
  }
} // namespace detail


/// The Stringbuf class is a statically sized C-string whose contents are
/// zero-filled. Note that this class does not provide the features typical
/// of the usual string abstraction. This is effectively an array of
/// characters.
template<std::size_t N>
  class Stringbuf
  {
    static_assert(N > 0, "N must not be zero");
  public:

    Stringbuf() = default;

    // Value initialization
    explicit Stringbuf(const char* str);
    Stringbuf& operator=(const char* str);

    // Observers
    bool empty() const;
    std::size_t size() const;
    std::string str() const;

    // Returns a pointer to the underlying character data.    
    char*       data()       { return data_; }
    const char* data() const { return data_; }

  private:
    char data_[N];
  };

template<std::size_t N>
  inline 
  Stringbuf<N>::Stringbuf(const char* s) { detail::zero_copy<N>(s, data_); }

template<std::size_t N>
  inline Stringbuf<N>&
  Stringbuf<N>::operator=(const char* s)
  {
    detail::zero_copy<N>(s, data_);
    return *this;
  }

template<std::size_t N>
  inline bool
  Stringbuf<N>::empty() const { return !data_[0]; }

template<std::size_t N>
  inline std::size_t
  Stringbuf<N>::size() const { return detail::strnlen<N>(data_); }

template<std::size_t N>
  inline std::string
  Stringbuf<N>::str() const { return std::string(data_, data_ + size()); }

// Equality comparison
template<std::size_t N>
  inline bool
  operator==(const Stringbuf<N>& a, const Stringbuf<N>& b)
  {
    return !std::strncmp(a.data(), b.data(), N);
  }

template<std::size_t N>
  inline bool
  operator!=(const Stringbuf<N>& a, const Stringbuf<N>& b) 
  { 
    return !(a == b); 
  }

// Is valid
template<std::size_t N>
  constexpr Error_condition
  is_valid(const Stringbuf<N>& s) { return SUCCESS; }

// To string
template<std::size_t N>
  inline std::string
  to_string(const Stringbuf<N>& s) { return s.str(); }

} // namespace flog


#endif
