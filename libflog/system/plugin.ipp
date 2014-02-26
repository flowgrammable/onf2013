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

#ifndef FLOWGRAMMABLE_LOADER_IPP
#define FLOWGRAMMABLE_LOADER_IPP

#include "exporter.hpp"

namespace flog {
namespace plugin {

inline
Plugin::~Plugin()
{
  for(auto f : destructors)
    f();
  if(module)
    ::dlclose(module);
}

inline
Plugin::operator bool() const
{
  return status;
}

template<typename T>
  Symbol<T>
  Plugin::get()
  {
    char const * cons_e = "";
    char const * dest_e = "";

    std::string cons_s = std::string("flog_plugin_cons_") + type_name;
    std::string dest_s = std::string("flog_plugin_dest_") + type_name;

    void* cons = ::dlsym(module, cons_s.c_str());
    if(not cons)
      cons_e = ::dlerror();
    void* dest = ::dlsym(module, dest_s.c_str());
    if(not dest)
      dest_e = ::dlerror();

    Cons_if<T> cons_t = reinterpret_cast<Cons_if<T>>(cons);
    Dest_if    dest_t = reinterpret_cast<Dest_if>(dest);

    if(cons_t and dest_t) {
      destructors.push_back(dest_t);
      return Symbol<T>(cons_t(), "");
    } else if(cons_t) {
      std::string msg_e("Failed symbol load: " + type_name + "\n\t" +
                        dest_e);
      return Symbol<T>(cons_t(),msg_e);
    } else {
      std::string msg_e("Failed symbol load: " + type_name + 
                        "\n\t" + cons_e + "\n" + 
                        "Failed symbol load: " + type_name + 
                        "\n\t" + dest_e);
      return Symbol<T>(nullptr,msg_e);
    }
  }

} // namespace plugin
} // namespace flog

#endif
