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

#ifndef CFG_PARSER_H
#define CFG_PARSER_H

#include <exception>
#include <algorithm>
#include "config.hpp"
#include "token.hpp"

namespace cfg {

struct Node
{
  struct Pvisitor;
  virtual ~Node() {}
  virtual void accept(Pvisitor&) const  =0;

};

template <typename T>
struct Node_Impl : Node
{
  virtual ~Node_Impl(){}
  void accept(Pvisitor& v) const;

};

struct List : Node_Impl<List>
{
  List(Token, std::vector<const Node*>);
  Token name;
  std::vector<const Node*> vec;
};

struct Identifier : Node_Impl<Identifier>
{
  Identifier(Token);
  Token val;
};

struct Bind : Node_Impl<Bind>
{
  Bind(const Identifier*, const Node*);
  const Identifier* lhs;
  const Node* rhs;
};

struct Arrow : Node_Impl<Arrow>
{
  Arrow(const Identifier*, const Node*);
  const Identifier* lhs;
  const Node* rhs;
};

struct Lit_str : Node_Impl<Lit_str>
{
  Lit_str(Token);
  Token val;
};

struct Lit_int : Node_Impl<Lit_int>
{
  Lit_int(Token, Token);
  Token val;
  Token unit;
};

struct Version : Node_Impl<Version>
{
  Version(const std::string&);
  std::string version;
};
struct Address : Node_Impl<Address>//we may want to rename this...
{
  Address(Token, const Node*, const Lit_int*, const Node*, const Lit_int*);
  Token proto;
  //for Addresses, addr1 and port 1 are listening
  const Node* addr1; //ipv4|ipv6|str|id
  const Lit_int* port1; //optional
  //for Connections they are destation information, addr2/port2 are for source
  const Node* addr2;
  const Lit_int* port2;
};

struct Lit_ipv4 : Node_Impl<Lit_ipv4>
{//all 4 grps separated by 3 dots
  Lit_ipv4(const Lit_int*,const Lit_int*,const Lit_int*,const Lit_int*);
  const Lit_int* grp1;
  const Lit_int* grp2;
  const Lit_int* grp3;
  const Lit_int* grp4;
};

struct Lit_ipv6 : Node_Impl<Lit_ipv6>
{//stores hex strings as strings, and keeps track of where :: token is
  Lit_ipv6(std::vector<std::string>, int);
  std::vector<std::string> groups;
  int zero_point;
};

struct Lit_network : Node_Impl<Lit_network>
{//should only be literals in here
  Lit_network(const Node*, const Lit_int*);
  const Node* ip;//ipv4 or ipv6
  const Lit_int* netmask;//int
  //~Lit_network(){};
};

//Parse_Tree
struct Parse_Tree: std::vector<const Node*>
{};

//Visitors
struct Node::Pvisitor
{
  virtual void visit(const List& x){};
  virtual void visit(const Bind& x){};
  virtual void visit(const Arrow& x){};
  virtual void visit(const Identifier& x){};
  virtual void visit(const Address& x){};
  virtual void visit(const Version& x){};
  virtual void visit(const Lit_int& x){};
  virtual void visit(const Lit_str& x){};
  virtual void visit(const Lit_ipv4& x){};
  virtual void visit(const Lit_ipv6& x){};
  virtual void visit(const Lit_network& x){};
};

struct Print : Node::Pvisitor
{//for some reason this has to be here...
  Print():tabs(0){}
  void visit(const List&);
  void visit(const Bind&);
  void visit(const Arrow&);
  void visit(const Identifier&);
  void visit(const Address&);
  void visit(const Version&);
  void visit(const Lit_int&);
  void visit(const Lit_str&);
  void visit(const Lit_ipv4&);
  void visit(const Lit_ipv6&);
  void visit(const Lit_network&);
  std::stringstream ss;
  int tabs;
};

//Factories
template <typename T>
struct Factory
{
  //vector of pointers of things
  std::vector<T*> store;
  //T* make();//create object based on arguments
  template <typename... U>
  const T* make(const U&... args)//create object based on arguments
  {
    T* t = new T(args...);
    //store.emplace_back(args...);
    store.push_back(t);
    //return &store.back();
    return t;
  }
  ~Factory()
  { 
    for(auto t : store)
      delete t;
  }
};

struct ParserFactory
{
  const List* make_list(Token t, const std::vector<const Node*> v)
    { return list.make(t,v); }
  const Identifier* make_id(Token t)
    { return id.make(t); }
  const Bind* make_bind(const Identifier* i, const Node* n)
    { return bind.make(i,n); }
  const Arrow* make_arrow(const Identifier* i, const Node* n)
    { return arrow.make(i,n); }
  const Address* make_addr(Token pro, const Node* a1, 
                           const Lit_int* p1, const Node* a2, const Lit_int* p2)
    { return addr.make(pro,a1,p1,a2,p2); }
  const Version* make_ver(const std::string& s)
    { return ver.make(s); }
  const Lit_str* make_str(Token t)
    { return str.make(t); }
  const Lit_int* make_int(Token t, Token u)
    { return lint.make(t,u); }
  const Lit_ipv4* make_ipv4(const Lit_int* g1, const Lit_int* g2, 
                            const Lit_int* g3, const Lit_int* g4)
    { return ipv4.make(g1,g2,g3,g4); }
  const Lit_ipv6* make_ipv6(std::vector<std::string> v, int z)
    { return ipv6.make(v,z); }
  const Lit_network* make_net(const Node* i, const Lit_int* n)
    { return net.make(i,n); }
  private: 
  Factory<List> list;
  Factory<Identifier> id;
  Factory<Bind> bind;
  Factory<Arrow> arrow;
  Factory<Address> addr;
  Factory<Version> ver;
  Factory<Lit_str> str;
  Factory<Lit_int> lint;
  Factory<Lit_ipv4> ipv4;
  Factory<Lit_ipv6> ipv6;
  Factory<Lit_network> net;
};

//accept is defined here, for everything
template <typename T>
void Node_Impl<T>::accept(Pvisitor& v) const
{
  v.visit(static_cast<const T&>(*this));
}

struct Parse_Error: std::exception
{
  Parse_Error(Token, const std::string&);
  Token t;
  std::string errmsg;
};
//Parser
class Parser: ParserFactory
{
  public:
    Parser(Tokenizer&);
    Parse_Tree parse();
    bool error();
  private:
    std::vector<Token::Tkind> make_list_name_vec();
    bool is_list_name(const Token&);
    const Node* parse_bind(const Identifier*);
    const Node* parse_assignee();
    const Node* parse_literal();
    const Identifier* parse_identifier();
    const Node* parse_address();
    const Node* parse_version();
    const Node* parse_arrow(const Identifier*);
    const Node* parse_list();
    const Node* parse_list_item();
    //literal parsers
    const Node* parse_ipv4();
    const Node* parse_ipv6();
    const Node* parse_ip();
    const Lit_str* parse_str();
    const Lit_int* parse_int();
    const Node* parse_ip_or_network();
    Tokenizer& tokenizer;
    bool isParseError;
    Parse_Tree pt;
    std::vector<Token::Tkind> list_names;
};
std::string to_string(Parse_Tree&);

}

#endif
