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

#ifndef FLOWGRAMMABLE_SEQUENCE_H
#define FLOWGRAMMABLE_SEQUENCE_H

#include <vector>
#include <sstream>
#include <numeric>

#include "buffer.hpp"

namespace flog {

template<typename T>
  struct Sequence : public std::vector<T> 
  {
    using std::vector<T>::vector;
  };

// Bytes
template<typename T>
  inline std::size_t 
  bytes(const Sequence<T>& s) 
  {
    std::size_t result = 0;
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
      result += bytes(*itr);
    }
    return result;
  }

// To/from buffer
template<typename T>
  Error_condition
  to_buffer(Buffer_view& v, const Sequence<T>& s) 
  {
    auto iter = s.begin();
    auto end = s.end();
    while (iter != end and available(v, bytes(*iter))) {
      if (Error_decl err = to_buffer(v, *iter))
        return err;
      iter++;
    }
    return iter == end ? SUCCESS : EXCESS_SEQUENCE;
  }

template<typename T>
  Error_condition
  from_buffer(Buffer_view& v, Sequence<T>& s) 
  {
    // Continue reading until no more T objects can be constructed. 
    // Note that availability is necessary to construct a T object,
    // but it is not sufficient. If T contains a variant whose total
    // size is determined during from_buffer, then we may not be able 
    // to fully read a T object. Hence the nested check on from_buffer.
    while (remaining(v)) {
      T t;
      if (Error_decl err = from_buffer(v, t))
        return err;
      s.push_back(std::move(t));
    }
    return SUCCESS;
  }

// Is valid
template<typename T>
  Error_condition
  is_valid(const Sequence<T>& s)
  {
    for (const auto& x : s) {
      if (auto err = is_valid(x))
        return err;
    }
    return SUCCESS;
  }

// To string
template<typename T>
  inline std::string 
  to_string(const Sequence<T>& s, Formatter& f) 
  {
    std::stringstream ss;
    for (auto itr = s.begin(); itr != s.end(); ++itr) {
      ss << to_string(*itr, f);
    }
    return ss.str();
  }

} // namespace flog

#endif
