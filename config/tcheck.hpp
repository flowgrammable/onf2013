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


#ifndef CFG_TCHECKER_H
#define CFG_TCHECKER_H

#include "parser.hpp"
#include "environment.hpp"

namespace cfg {

//TYPES

struct Base_Type 
{
  struct Typevisitor;
  virtual ~Base_Type() {}
  virtual void accept(Typevisitor&) const =0;
};

template<typename T>
struct Base_Type_Impl : Base_Type
{
  virtual ~Base_Type_Impl() {}
  void accept(Typevisitor&) const;
};

struct Built_In : Base_Type_Impl<Built_In>
{
  enum Built_Type { Void, Int, Hex, Str, Version, Ip4, Ip6, Network, Millisec,
                    Connection, Address};
  Built_In(Built_Type);
  Built_Type type;
};

struct Stage : Base_Type_Impl<Stage>
{ 
  enum State_Point { Realm, Authen, Author, Init, Connector};
  Stage(State_Point, State_Point);
  State_Point t1;
  State_Point t2;
};

struct List_Type: Base_Type_Impl<List_Type>
{
  List_Type(const Base_Type*);
  const Base_Type* type;
};

struct Record_Type : Base_Type_Impl<Record_Type>
{
  enum Record_Name { Realm, Authen, Author, Init, OFP, Connector};
  Record_Type(Record_Name);
  Record_Name name;
};

struct Base_Type::Typevisitor
{
  virtual void visit(const Built_In& x){};
  virtual void visit(const Stage& x){};
  virtual void visit(const List_Type& x){};
  virtual void visit(const Record_Type& x){};
};

struct Print_type : Base_Type::Typevisitor
{ 
  void visit(const Built_In&);
  void visit(const Stage&);
  void visit(const List_Type&);
  void visit(const Record_Type&);
  std::stringstream ss;
};
//accept is defined here, for all types
template <typename T>
void Base_Type_Impl<T>::accept(Typevisitor& v) const
{
  v.visit(static_cast<const T&>(*this));
}

//EXPRESSIONS

struct Expr
{
  Expr(const Base_Type*);
  virtual ~Expr() {}
  struct Evisitor;
  virtual void accept(Evisitor&) const = 0;
  const Base_Type* t;
};

template <typename T>
struct Expr_Impl : Expr
{
  virtual ~Expr_Impl(){}
  Expr_Impl(const Base_Type*);
  void accept(Evisitor& v) const;
};

//struct block, comes from parser changes
//represents the contents of a parser::list
//block is a list of exprs
//block needs to be type void TODO a later time and date

struct List_expr : Expr_Impl<List_expr>
{ //the type here is what is in all elements of the list if list
  List_expr(std::vector<const Expr*>, const Base_Type*);
  std::vector<const Expr*> list;
};

struct Record_expr :Expr_Impl<Record_expr>
{//the record type describes how to_string properly read this list
  //used for more organized lists, like realm and stuff
  Record_expr(std::vector<const Expr*>, const Base_Type*);
  std::vector<const Expr*> record;
};

struct Sym_expr : Expr_Impl<Sym_expr>
{
  Sym_expr(const std::string&, const Base_Type*);
  std::string name;
};

struct Bind_expr : Expr_Impl<Bind_expr>
{//type void
  Bind_expr(const Sym_expr*, const Expr*, const Base_Type*);
  const Sym_expr* lhs;
  const Expr* rhs;
};

struct Arrow_expr : Expr_Impl<Arrow_expr>
{
  Arrow_expr(const Expr*, const Expr*, const Base_Type*);
  const Expr* lhs;//this needs to be an expression, not a symbol
  const Expr* rhs;
};

struct Int_expr : Expr_Impl<Int_expr>
{//this is an int or a time
  //time is only in ms now, so if the type is time, we interperet differently
  Int_expr(uint32_t, const Base_Type*);
  uint32_t val;//could be a long long???
};

struct Hex_expr : Expr_Impl<Hex_expr>
{
  Hex_expr(uint16_t, const Base_Type*);
  uint16_t val;
};

struct Str_expr : Expr_Impl<Str_expr>
{
  Str_expr(const std::string&, const Base_Type*);
  std::string val;
};

struct Ver_expr : Expr_Impl<Ver_expr>
{
  Ver_expr(const std::string&, const Base_Type*);
  std::string val;
};

struct Listener_expr : Expr_Impl<Listener_expr>
{//these could be the address listener or connection listener
  enum Proto {tcp, tls};
  Listener_expr(Proto, const Expr*, const Int_expr*, const Expr*, const Int_expr*, 
                const Base_Type*);
  Proto p;
  const Expr* ip1;
  const Int_expr* port1;
  const Expr* ip2;
  const Int_expr* port2;
};

struct Ipv4_expr : Expr_Impl<Ipv4_expr>
{
  Ipv4_expr(const Int_expr*, const Int_expr*, const Int_expr*, const Int_expr*,
            const Base_Type*);
  const Int_expr* g1;
  const Int_expr* g2;
  const Int_expr* g3;
  const Int_expr* g4;
};

struct Ipv6_expr : Expr_Impl<Ipv6_expr>
{
  Ipv6_expr(std::vector<const Hex_expr*>, const Base_Type*);
  std::vector<const Hex_expr*> groups;
};

struct Net_expr : Expr_Impl<Net_expr>
{//not sure if I should store as lit_int or uint32_t or something
  Net_expr(const Expr*, const Int_expr*, const Base_Type*);
  const Expr* ip;
  const Int_expr* mask;
};

struct Elab_Tree : std::vector<const Expr*>
{};

//Vistors
struct Expr::Evisitor
{
  virtual void visit(const List_expr& x){};
  virtual void visit(const Record_expr& x){};
  virtual void visit(const Bind_expr& x){};
  virtual void visit(const Arrow_expr& x){};
  virtual void visit(const Sym_expr& x){};
  virtual void visit(const Listener_expr& x){};
  virtual void visit(const Ver_expr& x){};
  virtual void visit(const Int_expr& x){};
  virtual void visit(const Hex_expr& x){};
  virtual void visit(const Str_expr& x){};
  virtual void visit(const Ipv4_expr& x){};
  virtual void visit(const Ipv6_expr& x){};
  virtual void visit(const Net_expr& x){};
};

struct Print_expr : Expr::Evisitor
{
  Print_expr():tabs(0){}
  void do_print(const std::string&, const Base_Type*);
  void print_tabs();
  void visit(const List_expr&);
  void visit(const Record_expr&);
  void visit(const Bind_expr&);
  void visit(const Arrow_expr&);
  void visit(const Sym_expr&);
  void visit(const Listener_expr&);
  void visit(const Ver_expr&);
  void visit(const Int_expr&);
  void visit(const Hex_expr&);
  void visit(const Str_expr&);
  void visit(const Ipv4_expr&);
  void visit(const Ipv6_expr&);
  void visit(const Net_expr&);
  std::stringstream ss;
  int tabs;
};

//the generic factory is found in parser.hpp
struct TypeFactory
{
public:
  //one for each type here
  TypeFactory();
  //call a function to return the correct builtin record type in the
  //constructor here
  //make functions
  const Built_In* make_void_type()
    { return &voidptr; }
  const Built_In* make_int_type()
    { return &intptr; }
  const Built_In* make_hex_type()
    { return &hexptr; }
  const Built_In* make_str_type()
    { return &strptr; }
  const Built_In* make_ver_type()
    { return &verptr; }
  const Built_In* make_ms_type()
    { return &msptr; }
  const Built_In* make_ip4_type()
    { return &ip4ptr; }
  const Built_In* make_ip6_type()
    { return &ip6ptr; }
  const Built_In* make_conn_type()
    { return &connptr; }
  const Built_In* make_addr_type()
    { return &addrptr; }
  const Built_In* make_network_type()
    { return &netptr; }
  const List_Type* make_acl_type()
    { return &aclptr; }
  const List_Type* make_x509_type()
    { return &x509ptr; }
  const List_Type* make_advert_type()
    { return &advertptr; }
  const List_Type* make_connection_type()
    { return &connectionptr; }
  const Record_Type* make_realm_type()
    { return &realmptr; }
  const Record_Type* make_author_type()
    { return &authorptr; }
  const Record_Type* make_authen_type()
    { return &authenptr; }
  const Record_Type* make_init_type()
    { return &initptr; }
  const Record_Type* make_ofp_type()
    { return &ofpptr; }
  const Record_Type* make_connector_type()
    { return &connectorptr; }
  const Stage* make_stage_type(Stage::State_Point a, Stage::State_Point b)
    { return stage.make(a,b); }
  const List_Type* make_list_type(const Base_Type* t)
    { return listtype.make(t); }//I am not sure if I really need this
  //factories

  Factory<Stage> stage;
  Factory<List_Type> listtype;
  const Built_In voidptr;
  const Built_In intptr;
  const Built_In hexptr;
  const Built_In strptr;
  const Built_In verptr;
  const Built_In msptr;
  const Built_In ip4ptr;
  const Built_In ip6ptr;
  const Built_In netptr;
  const Built_In connptr;
  const Built_In addrptr;
  const List_Type aclptr;
  const List_Type x509ptr;
  const List_Type advertptr;
  const List_Type addrlistptr;
  const List_Type connectionptr;
  const Record_Type realmptr;
  const Record_Type authorptr;
  const Record_Type authenptr;
  const Record_Type initptr;
  const Record_Type ofpptr;
  const Record_Type connectorptr;
};

struct ExprFactory : TypeFactory
{
  const List_expr* make_list(std::vector<const Expr*> l, const Base_Type* t)
    { return list.make(l,t); }
  const Record_expr* make_record(std::vector<const Expr*> l, const Base_Type* t)
    { return record.make(l,t); }
  const Sym_expr* make_sym(const std::string& s, const Base_Type* t)
    { return id.make(s,t); }
  const Bind_expr* make_bind(const Sym_expr* s, const Expr* e)
    { return bind.make(s,e, make_void_type()); }
  const Arrow_expr* make_arrow(const Expr* s, const Expr* e, const Base_Type* t)
    { return arrow.make(s,e,t); }//The calling end must give the already constructed
                                 //stage type, cannot make at this point
  const Listener_expr* make_listen(Listener_expr::Proto pro, const Expr* i1, 
                              const Int_expr* p1, const Expr* i2, 
                              const Int_expr* p2, const Base_Type* t)
    { return addr.make(pro,i1,p1,i2,p2,t); }
  const Ver_expr* make_ver(const std::string& s)
    { return ver.make(s, make_ver_type()); }
  const Str_expr* make_str(const std::string& s)
    { return str.make(s, make_str_type()); }
  const Int_expr* make_int(uint32_t i, const Base_Type* t)
    { return lint.make(i, t); }
  const Hex_expr* make_hex(uint16_t i)
    { return lhex.make(i, make_hex_type()); }
  const Ipv4_expr* make_ipv4(const Int_expr* g1, const Int_expr* g2, 
                            const Int_expr* g3, const Int_expr* g4)
    { return ipv4.make(g1,g2,g3,g4, make_ip4_type()); }
  const Ipv6_expr* make_ipv6(std::vector<const Hex_expr*> v)
    { return ipv6.make(v, make_ip6_type()); }
  const Net_expr* make_net(const Expr* i, const Int_expr* n)
    { return net.make(i,n, make_network_type()); }
  private: 
  Factory<List_expr> list;
  Factory<Record_expr> record;
  Factory<Sym_expr> id;
  Factory<Bind_expr> bind;
  Factory<Arrow_expr> arrow;
  Factory<Listener_expr> addr;
  Factory<Ver_expr> ver;
  Factory<Str_expr> str;
  Factory<Int_expr> lint;
  Factory<Hex_expr> lhex;
  Factory<Ipv4_expr> ipv4;
  Factory<Ipv6_expr> ipv6;
  Factory<Net_expr> net;
};

//accept is defined here, for everything
template <typename T>
void Expr_Impl<T>::accept(Evisitor& v) const
{
  v.visit(static_cast<const T&>(*this));
}

struct Elab_Error: std::exception
{//this could contain the const Expr* and print it if wrong
  Elab_Error(const std::string&);//for now just a string
  std::string errmsg;
};

struct Convert_Error: std::exception
{
  Convert_Error(const std::string&, const std::string&);
  std::string val;
  std::string errmsg;
};

struct Elaborator : ExprFactory
{ 
  Elaborator();
  const Expr* elab(const Node*);
  void elab(Parse_Tree&);
  const Stage* combine_stage_type(const Base_Type*, const Base_Type*);
  const Stage* coerce_type(const Base_Type*);
  Elab_Tree result;
  bool isTypeError;
  Scope_Stack env;//was a scope stack
};

std::string to_string(Elab_Tree&);
  const Expr* elab_record(Elaborator*, const std::string&, std::vector<const Expr*>);
bool check_for_tls(Elaborator*, const Expr* e);
  const Expr* elab_realm(Elaborator*, std::vector<const Expr*>);
  const Expr* elab_authen(Elaborator*, std::vector<const Expr*>);
  const Expr* elab_author(Elaborator*, std::vector<const Expr*>);
  const Expr* elab_init(Elaborator*, std::vector<const Expr*>);
  const Expr* elab_ofp(Elaborator*, std::vector<const Expr*>);
  const Expr* elab_connector(Elaborator*, std::vector<const Expr*>);
  bool is_list_valid(Elaborator*, std::vector<const Expr*>&, const std::string&);
  const Base_Type* return_type(const std::string&);
  bool is_record(const std::string&);
const Expr* elab_list(Elaborator*, const List*);
const Expr* elab_bind(Elaborator*, const Bind*);
const Expr* elab_arrow(Elaborator*, const Arrow*);
const Expr* elab_id(Elaborator*, const Identifier*);
const Expr* elab_addr(Elaborator*, const Address*);
const Expr* elab_ver(Elaborator*, const Version*);
  uint32_t to_int(const std::string&);
const Expr* elab_int(Elaborator*, const Lit_int*);
const Expr* elab_str(Elaborator*, const Lit_str*);
const Expr* elab_ipv4(Elaborator*, const Lit_ipv4*);
  uint16_t to_hex(const std::string&);
const Expr* elab_ipv6(Elaborator*, const Lit_ipv6*);
const Expr* elab_net(Elaborator*, const Lit_network*);


struct Elabvis : Node::Pvisitor 
{
  Elabvis(Elaborator* e) : ctx(e), result(nullptr) {}
  Elaborator* ctx;//really just need this for the env member
  const Expr* result;
  void visit(const List& x)       { result = elab_list(ctx, &x); }
  void visit(const Bind& x)       { result = elab_bind(ctx, &x); }
  void visit(const Arrow& x)      { result = elab_arrow(ctx, &x); }
  void visit(const Identifier& x) { result = elab_id(ctx, &x); }
  void visit(const Address& x)    { result = elab_addr(ctx, &x); }
  void visit(const Version& x)    { result = elab_ver(ctx, &x); }
  void visit(const Lit_int& x)    { result = elab_int(ctx, &x); }
  void visit(const Lit_str& x)    { result = elab_str(ctx, &x); }
  void visit(const Lit_ipv4& x)   { result = elab_ipv4(ctx, &x); }
  void visit(const Lit_ipv6& x)   { result = elab_ipv6(ctx, &x); }
  void visit(const Lit_network& x){ result = elab_net(ctx, &x); }
};

}//end namespace
#endif
