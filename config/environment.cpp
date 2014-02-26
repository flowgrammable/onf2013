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

#include "environment.hpp"

namespace cfg {

void
Scope::push_binding(const std::string& s, const Expr* e)
{
  bindings[s] = e;
}

const Expr*
Scope::lookup(const std::string& s)
{
  auto it = bindings.find(s);
  if(it == bindings.end())
    return nullptr;
  return it->second;
}

Scope_Stack::Scope_Stack()
{
  scopes.push_back(Scope());//this is the global scope
                            //it's added by default when creating a scope stack
}

void
Scope_Stack::push_binding(const std::string& s, const Expr* e)
{
  scopes.back().push_binding(s,e);
}

const Expr*
Scope_Stack::local_lookup(const std::string& s)
{//only in local scope, not entire environment
  return scopes.back().lookup(s);
}

const Expr*
Scope_Stack::lookup(const std::string& s)
{//global look up, starts from global scope and moves to local

  const Expr* e = nullptr;
  for(Scope scope : scopes)//for each scope in scopes
  {
    e = scope.lookup(s);
    if(e != nullptr)
      break;
  }
  return e;
}

Scope&
Scope_Stack::current_scope()
{
  return scopes.back();
}

void
Scope_Stack::push_scope()
{
  scopes.push_back(Scope());//creates a new scope and adds it
}

void
Scope_Stack::pop_scope()
{
  scopes.pop_back();//removes the last scope in the stack
}

Scope_Manager::Scope_Manager(Scope_Stack& x)
:ss(x)
{
  ss.push_scope();
}

Scope_Manager::~Scope_Manager()
{
  ss.pop_scope();
}

}//end namespace