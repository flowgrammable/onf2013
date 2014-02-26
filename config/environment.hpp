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

#ifndef CFG_ENVIRON_H
#define CFG_ENVIRON_H

#include <map>
#include <vector>
#include <iostream>

namespace cfg {
  
struct Expr;//need this I think because of having tcheck.hpp include environment.hpp
//and environment.hpp needing to include tcheck.hpp
struct Scope
{
  void push_binding(const std::string&, const Expr*);
  const Expr* lookup(const std::string&);
  //MICHAEL, put const before std::string to see a bug maybe
  //with const there is a segfault
  std::map<std::string, const Expr*> bindings;
};

struct Scope_Stack 
{
  //will always create the first stack, which is the global stack
  Scope_Stack();

  void push_binding(const std::string&, const Expr*);//add a new name val pair
  const Expr* lookup(const std::string&);//lookup on all scopes in stack
  const Expr* local_lookup(const std::string&);//just local scope
  Scope& current_scope();//return current scope

  void push_scope();//adds a new scope to the stack
  void pop_scope();//removes a scope from the stack
  std::vector<Scope> scopes;

};

struct Scope_Manager
{
  Scope_Manager(Scope_Stack&);//pushes a new scope on the stack
  ~Scope_Manager();//pops an old scope off the stack
  Scope_Stack& ss;
};

}//end namespace
#endif