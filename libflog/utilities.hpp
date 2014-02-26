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

#ifndef FLOWGRAMMABLE_UTILITIES_H
#define FLOWGRAMMABLE_UTILITIES_H

#include <cassert>
#include <cstdint>
#include <cstring>
#include <numeric>
#include <random>
#include <iostream>
#include <sstream>
#include <type_traits>

// The program has a reached an invalid execution branch.
#define unreachable() \
  { __builtin_printf("error: unreachable\n"); assert (false); }

// The program has tried to use a variant in an invalid way.
#define variant_error(n) \
  { __builtin_printf("error: variant descriminator %d\n", n); assert(false); }


namespace flog {

struct Gen_error 
{
  // - Ctor
  Gen_error(const char* t, const char* r) 
    : type(t), reason(r) 
  {}

  // - Internalized info
  std::string type ;
  std::string reason ;
};

std::string 
str(const Gen_error&);

struct Sys_error 
{
  // - Ctor
  Sys_error(int e) 
    : error(e), reason(strerror(e)) 
  {}

  // - Internalized errno and string
  int error;
  std::string reason ;
};

std::string 
str(const Sys_error&);

struct Formatter
{
  Formatter() 
    : indent(0), mode(std::dec) 
  {}
  Formatter(int i, std::ios_base& (*f)(std::ios_base&) = std::dec) 
    : indent(i), mode(f)
  { }

  void push() { indent += 2; }
  void pop()  { indent -= 2; }

  int indent;
  std::ios_base& (*mode)(std::ios_base&);
};

template <typename T>
  inline std::ostream&
  nvp_to_string(std::ostream& out, const Formatter& f, const std::string& name,
                const T& value)
  {
    out << f.mode;
    out << std::string(f.indent, ' ');
    out << name << ": " << value;
    out << std::dec << "\n";
    return out;
  }

template <typename T>
  inline std::ostream&
  nvp_to_string(std::ostream& out, const Formatter& f, const std::string& name,
                const std::string& vname, const T& v)
  {
    out << f.mode;
    out << std::string(f.indent, ' ');
    out << name << ": " << vname << "(" << v << ")";
    out << std::dec << "\n";
    return out;
  }

inline std::ostream&
open_block(std::ostream& out, Formatter& f, const std::string& name)
{
  out << std::string(f.indent, ' ') << name << " { \n";
  f.push();
  return out;
}

inline std::ostream&
close_block(std::ostream& out, Formatter& f, const std::string& name)
{
  f.pop();
  out << std::string(f.indent, ' ') << "} //" << name << "\n";
  return out;
}

template<typename T>
  std::string
  cond_to_string(bool p, const std::string& f, const T& s)
  {
    std::stringstream ss;
    if (p)
      ss << f;
    else
      ss << s;
    return ss.str();
  }

// -------------------------------------------------------------------------- //
// Foreign Byte Order

/// The Foreign_byte_order class provides facilities for reordering the bytes
/// in unsigned integral values so that the most or least significant bit
/// appears first in the byte sequence.
///
/// \todo Clang will not compile this class with constexpr byte-ordering
/// functions as it is written. The reason is that the test against value
/// is not the active member of the union. Fixing this should rely on 
/// config-time information, and then write this as constexprs. For now, they 
/// are made non-constexpr.
struct Foreign_byte_order 
{
  // Union and initial value to test underlying architecture
  union Test { uint8_t a[4]; uint32_t value ; };
  static constexpr Test test = {{ 1, 2, 3, 4 }};
  
  // Test values to read underlying architecture behavior.
  static constexpr uint32_t MSBF = 0x01020304;
  static constexpr uint32_t LSBF = 0x04030201;
  
  // Convert the foreign representation to most-significant-byte-first.
  static uint8_t msbf(uint8_t v) {
    return v;
  }

  static uint16_t msbf(uint16_t v) {
     return test.value == MSBF ? v : __builtin_bswap16(v);
  }
  
  static uint32_t msbf(uint32_t v) {
     return test.value == MSBF ? v : __builtin_bswap32(v);
  }
  
  static uint64_t msbf(uint64_t v) {
     return test.value == MSBF ? v : __builtin_bswap64(v);
  }

  template<typename T>
    static T msbf(T v) {
      return (T)msbf(typename std::underlying_type<T>::type(v));
    }
  

  // Convert the foreign representation to least-significant-byte-first.
  static uint8_t lsbf(uint8_t v) {
    return v;
  }

  static uint16_t lsbf(uint16_t v) {
     return test.value == LSBF ? v : __builtin_bswap16(v);
  }
  
  static uint32_t lsbf(uint32_t v) {
     return test.value == LSBF ? v : __builtin_bswap32(v);
  }
  
  static uint64_t lsbf(uint64_t v) {
     return test.value == LSBF ? v : __builtin_bswap64(v);
  }

  template<typename T>
    static T lsbf(T v) {
      return lsbf(typename std::underlying_type<T>::type(v));
    }
};


template <typename T>
  class Generator_random {
    public:
      Generator_random() : dist(0,std::numeric_limits<T>::max()) {}
      T operator()() {
        return dist(generator);
      }
    private:
      T val;
      std::default_random_engine generator ;
    std::uniform_int_distribution<> dist ;
  };

template <typename T>
  class Generator_monotone {
    public:
      Generator_monotone() : val() {}
      T operator()() {
        return val++;
      }
    private:
      T val;
  };

  // TODO: Find a better place for these things.

  // Set x to its default state, and return its previous value as
  // an rvalue.
  template<typename T>
    inline T reset(T& x) {
      using std::swap;
      T y;
      swap(x, y);
      return y;
    }

  // Move the elements from c2 into c2. The elements are inserted at
  // the end of c2.
  template<typename C1, typename C2>
    inline void append(C1& c1, C2&& c2) {
      auto first = std::make_move_iterator(c2.begin());
      auto last = std::make_move_iterator(c2.end());
      c1.insert(c1.end(), first, last);
      c2.clear();
    }

} // namespace flog

#endif
