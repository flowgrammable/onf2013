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

#ifndef CFG_EVAL_H
#define CFG_EVAL_H
#include <iostream>
#include <libflog/system/config.hpp>

#include "tcheck.hpp"

namespace cfg {

struct Evaluator {
  
  Evaluator(Elab_Tree elabtree): et(elabtree),realm_name(""){}
  void evaluate();
  void eval_realm(const Record_expr*);
  void eval_connector(const Record_expr*);
  void eval_authentication(const Record_expr*);
  void eval_initialization(const Record_expr*);
  void write_to_pipe();
  Elab_Tree et;
  std::string realm_name;
  std::vector<std::string> commands;
};

} // namespace cfg

#endif
