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

#include <iostream>

#include <libflog/system/plugin.hpp>
#include <libflog/proto/ofp/v1_0/application.hpp>

int main(int argc, char** argv)
{
  if(argc != 2) {
    std::cerr << "usage syntax: " << argv[0] << " <plugin name>" << std::endl;
    std::exit(-1);
  }

  flog::plugin::Plugin plugin(argv[1]);
  if(not plugin) {
    std::cerr << plugin.error << std::endl;
    std::exit(-1);
  }

  auto result = plugin.get<flog::ofp::v1_0::Application>();
  if(result.first){
    result.first->init(flog::Time());
    result.first->fini(flog::Time());
  } else {
    std::cerr << result.second << std::endl;
    std::exit(-1);
  }

  return 0;
}
