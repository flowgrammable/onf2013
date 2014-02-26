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

#ifndef APP1_HPP
#define APP1_HPP

#include <iostream>

#include <libflog/proto/ofp/v1_0/application.hpp>

struct App1 : flog::ofp::v1_0::Application
{
  App1() 
    : Application() 
  { }

  void init(const flog::Time& t) {
    std::cout << "init" << std::endl;
  }
  void fini(const flog::Time& t) {
    std::cout << "fini" << std::endl;
  }

};

EXPORT_INTERFACE(App1)

#endif
