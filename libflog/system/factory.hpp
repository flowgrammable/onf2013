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

#ifndef FLOWGRAMMABLE_FACTORY_H
#define FLOWGRAMMABLE_FACTORY_H

namespace flog {

template<typename T>
  struct Factory 
  {
    Factory();

    template<typename P>
      T* 
      make(const P& p) 
      {
        return &*store.insert(T(p)).first;
      }

    template<typename P, typename R>
      T* 
      make(const P& p, const R& r)
      {
        return &*store.insert(T(p, r)).first;
      }
    template<typename P, typename R, typename S>
      T* 
      make(const P& p, const R& r, const S& s)
      {
        return &*store.insert(T(p, r, s)).first;
      }

    std::set<T> store;
  };

} // namespace flog

#endif
