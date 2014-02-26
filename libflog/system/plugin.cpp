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

#include "plugin.hpp"

namespace flog {
namespace plugin {

Plugin::Plugin(const std::string& n)
  : name(n), module(::dlopen(n.c_str(), RTLD_LAZY)), status(true)
{ 
  if(not module) {
    status = false;
    if(char* err = ::dlerror())
      error = ("Failed module load: " + n + "\n\t" + err);
    else
      error = ("Failed module load: " + n);
  }

  auto beg = n.find("lib");
  beg = beg == std::string::npos ? 0 : beg + 3;
  auto end = n.find('.', beg);
  end = end == std::string::npos ? n.size() - beg : end;

  type_name = n.substr(beg, end-beg);
}

} // namespace plugin
} // namespace flog
