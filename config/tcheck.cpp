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


#include "tcheck.hpp"

namespace cfg {
/*
Things TODO
do we care what the name of things are in the config?
  or just the type?
I'm not really using scope properly except for staging...
add specific realm, auth, etc types, for metadata purposes
fullly check realm/connector vs authentication
*/
Built_In::Built_In(Built_In::Built_Type t)
: type(t)
{}

Stage::Stage(State_Point a, State_Point b)
: t1(a), t2(b)
{}

List_Type::List_Type(const Base_Type* t)
: type(t)
{}

Record_Type::Record_Type(Record_Type::Record_Name n)
: name(n)
{}

void
Print_type::visit(const Built_In& t)
{
  switch(t.type) 
  {
    case Built_In::Void:
      ss<<"void";break;
    case Built_In::Int:
      ss<<"int";break;
    case Built_In::Hex:
      ss<<"hex";break;
    case Built_In::Str:
      ss<<"str";break;
    case Built_In::Version:
      ss<<"version";break;
    case Built_In::Ip4:
      ss<<"ip4";break;
    case Built_In::Ip6:
      ss<<"ip6";break;
    case Built_In::Network:
      ss<<"network";break;
    case Built_In::Millisec:
      ss<<"millisec";break;
    case Built_In::Connection:
      ss<<"connection";break;
    case Built_In::Address:
      ss<<"address";break;
    default:
      ss<<"err";
  }
}

void
Print_type::visit(const Stage& t)
{
  ss<< "stage";
}

void
Print_type::visit(const List_Type& t)
{
  t.type->accept(*this);
  ss<<" list";
}

void
Print_type::visit(const Record_Type& t)
{ 
  switch(t.name) 
  {
    case Record_Type::Realm:
      ss<<"realm";break;
    case Record_Type::Authen:
      ss<<"authen";break;
    case Record_Type::Author:
      ss<<"author";break;
    case Record_Type::Init:
      ss<<"init";break;
    case Record_Type::OFP:
      ss<<"ofp";break;
    case Record_Type::Connector:
      ss<<"connector";break;
    default:
      ss<<"err";
  }
}

Expr::Expr(const Base_Type* type)
: t(type)
{}

template<typename T>
Expr_Impl<T>::Expr_Impl(const Base_Type* type = nullptr)
: Expr(type)
{}

List_expr::List_expr(std::vector<const Expr*> l, const Base_Type* type)
: Expr_Impl(type), list(l)
{}

Record_expr::Record_expr(std::vector<const Expr*> l, const Base_Type* type)
: Expr_Impl(type), record(l)
{}

Sym_expr::Sym_expr(const std::string& s, const Base_Type* type)
: Expr_Impl(type), name(s)
{}

Bind_expr::Bind_expr(const Sym_expr* s, const Expr* e, const Base_Type* type)
: Expr_Impl(type), lhs(s), rhs(e)
{}

Arrow_expr::Arrow_expr(const Expr* s, const Expr* e, const Base_Type* type)
: Expr_Impl(type), lhs(s), rhs(e)
{}

Int_expr::Int_expr(uint32_t i, const Base_Type* type)
: Expr_Impl(type), val(i)
{}

Hex_expr::Hex_expr(uint16_t i, const Base_Type* type)
: Expr_Impl(type), val(i)
{}

Str_expr::Str_expr(const std::string& s, const Base_Type* type)
: Expr_Impl(type), val(s)
{}

Ver_expr::Ver_expr(const std::string& v, const Base_Type* type)
: Expr_Impl(type), val(v)
{}

Listener_expr::Listener_expr(Proto pro, const Expr* i1, const Int_expr* p1, 
                             const Expr* i2, const Int_expr* p2, 
                             const Base_Type* type)
: Expr_Impl(type), p(pro), ip1(i1), port1(p1), ip2(i2), port2(p2)
{}

Ipv4_expr::Ipv4_expr(const Int_expr* a, const Int_expr* b, const Int_expr* c,
                   const Int_expr* d, const Base_Type* type)
: Expr_Impl(type), g1(a), g2(b), g3(c), g4(d)
{}

Ipv6_expr::Ipv6_expr(std::vector<const Hex_expr*> g, const Base_Type* type)
: Expr_Impl(type), groups(g)
{}

Net_expr::Net_expr(const Expr* i, const Int_expr* m, const Base_Type* type)
: Expr_Impl(type), ip(i), mask(m)
{}

Elab_Error::Elab_Error(const std::string& s)
: errmsg(s)
{}

Convert_Error::Convert_Error(const std::string& v, const std::string& e)
: val(v), errmsg(e)
{}

void 
Print_expr::print_tabs()
{
  for( int x = 0; x<tabs; x++)
    ss<<"  ";
}
//the printer for the elab tree needs to show the expr and the type
void 
Print_expr::do_print(const std::string& val, const Base_Type* type)
{//gotta take into account tabs here
  //takes the val, and the type and prints it
  //uses the print visitor for the type
  Print_type pt;
  type->accept(pt);
  print_tabs();
  ss<<"Value: "<<val<<" Type: "<<pt.ss.str()<<'\n';
}

void 
Print_expr::visit(const List_expr& l)
{
  tabs++;
  for(const Expr* e:l.list)
    e->accept(*this);
  tabs--;
}

void
Print_expr::visit(const Record_expr& r)
{
  tabs++;
  for(const Expr* e:r.record)
    e->accept(*this);
  tabs--;
}

void 
Print_expr::visit(const Bind_expr& b)
{
  print_tabs();
  ss<<"Bind: \n";
  tabs++;
  b.lhs->accept(*this);
  b.rhs->accept(*this);
  tabs--;

}

void 
Print_expr::visit(const Arrow_expr& a)
{
  print_tabs();
  ss<<"Arrow: \n";
  tabs++;
  a.lhs->accept(*this);
  a.rhs->accept(*this);
  tabs--;
}

void 
Print_expr::visit(const Sym_expr& s)
{
  do_print(s.name, s.t);
}

void 
Print_expr::visit(const Listener_expr& l)
{
  //if we had the type here, or could compare types, this would be different
  print_tabs();
  Print_type pt;
  l.t->accept(pt);
  ss<<pt.ss.str()<<" proto: ";
  if(l.p == Listener_expr::tcp)
    ss<<"tcp\n";
  else
    ss<<"tls\n";
  tabs++;
  l.ip1->accept(*this);
  if(l.port1!=nullptr)
    l.port1->accept(*this);
  if(l.ip2!=nullptr)
    l.ip2->accept(*this);
  if(l.port2!=nullptr)
    l.port2->accept(*this);
  tabs--;
}

void 
Print_expr::visit(const Ver_expr& v)
{
  do_print(v.val, v.t);
}

void 
Print_expr::visit(const Int_expr& l)
{//could be a time though
  do_print(std::to_string(l.val), l.t);
}

void 
Print_expr::visit(const Hex_expr& l)
{
  do_print(std::to_string(l.val), l.t);
}

void 
Print_expr::visit(const Str_expr& l)
{
  do_print(l.val, l.t);
}

void 
Print_expr::visit(const Ipv4_expr& l)
{
  print_tabs();
  ss<<"ipv4:\n";
  tabs++;
  l.g1->accept(*this);
  l.g2->accept(*this);
  l.g3->accept(*this);
  l.g4->accept(*this);
  tabs--;
}

void 
Print_expr::visit(const Ipv6_expr& l)
{
  print_tabs();
  ss<<"ipv6:\n";
  tabs++;
  for(const Hex_expr* h:l.groups)
    h->accept(*this);
  tabs--;
}

void 
Print_expr::visit(const Net_expr& l)
{
  print_tabs();
  ss<<"network:\n";
  tabs++;
  l.ip->accept(*this);
  l.mask->accept(*this);
  tabs--;

}

TypeFactory::TypeFactory()
:voidptr(Built_In(Built_In::Void)), intptr(Built_In(Built_In::Int)),
 hexptr(Built_In(Built_In::Hex)), strptr(Built_In(Built_In::Str)),
 verptr(Built_In(Built_In::Version)), msptr(Built_In(Built_In::Millisec)),
 ip4ptr(Built_In(Built_In::Ip4)), ip6ptr(Built_In(Built_In::Ip6)),
 netptr(Built_In(Built_In::Network)), connptr(Built_In(Built_In::Connection)),
 addrptr(Built_In(Built_In::Address)),
 aclptr(List_Type(&netptr)), x509ptr(List_Type(&strptr)),
 advertptr(List_Type(&verptr)), addrlistptr(List_Type(&addrptr)),
 connectionptr(List_Type(&connptr)),
 realmptr(Record_Type(Record_Type::Realm)), 
 authorptr(Record_Type(Record_Type::Author)),
 authenptr(Record_Type(Record_Type::Authen)), 
 initptr(Record_Type(Record_Type::Init)),
 ofpptr(Record_Type(Record_Type::OFP)),
 connectorptr(Record_Type(Record_Type::Connector))
{
  //nothing here yet, might add soon?
}

Elaborator::Elaborator()
: isTypeError(false), env(Scope_Stack())
{}

bool
check_for_tls(Elaborator* ctx, const Expr* e)
{
  bool returnval = false;
  const List_expr* list_to_check = dynamic_cast<const List_expr*>(e);
  //should check if the list_to_check is ok...
  for(const Expr* item: list_to_check->list)//the list contains only listeners
  {//if the listener is protocol tls....
    if(dynamic_cast<const Listener_expr*>(item)->p == Listener_expr::tls)
      {returnval = true; break;}
  }
  return returnval;
}

const Expr*
elab_realm(Elaborator* ctx, std::vector<const Expr*> elist)
{ //TODO get need_private_key value to authen, so I can type check that
  bool need_private_key = false;
  bool found_addresses = false;
  bool found_private_key = false;
  for(const Expr* e: elist)//this is a list of bindings
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);//force
    if(b->rhs->t == &(ctx->addrlistptr) && b->lhs->name.compare("address")==0)
    {//is a type addresses, and named address 
      found_addresses = true;//right type, successful search
      if(check_for_tls(ctx, b->rhs))
        need_private_key = true;
      continue;
    }
    if(b->rhs->t == &(ctx->strptr) && b->lhs->name.compare("private_key") ==0)
    {//is type string, and is named private key...
      found_private_key = true;
      continue;
    }//if it's not supposed be in a realm, this line will catch that
    throw Convert_Error(b->lhs->name,"Invalid member of realm: ");
  }    
  if(need_private_key && !found_private_key)
      throw Elab_Error("private_key in realm not found");
  if((!need_private_key && found_addresses) ||//no private key, just addresses
     (found_addresses && found_private_key))//both private key and addresses
    return ctx->make_record(elist, ctx->make_realm_type());
  else
    throw Elab_Error("Missing member of Realm");
}

const Expr*
elab_authen(Elaborator* ctx, std::vector<const Expr*> elist)
{ //at this point, it is valid with or without public keys
  //acl is always optional
  //in staging we can determine if this is valid or not based on the 
  //staged realm before it
  for(const Expr* e: elist)
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);//force
    if(b->rhs->t == &(ctx->x509ptr) && b->lhs->name.compare("public_keys")==0)
      continue;
    if(b->rhs->t == &(ctx->aclptr) && b->lhs->name.compare("acl")==0)
      continue;
    throw Convert_Error(b->lhs->name,"Invalid member of Authentication: ");
  }
  //all members are optional or conditional... so make anyway
  return ctx->make_record(elist, ctx->make_authen_type());
}

const Expr*
elab_author(Elaborator* ctx, std::vector<const Expr*> elist)
{//all potential members are optional TODO make empty lists possible
  for(const Expr* e: elist)
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);//force
    if(b->rhs->t == &(ctx->intptr) && b->lhs->name.compare("tcp_max")==0)
      continue;
    if(b->rhs->t == &(ctx->intptr) && b->lhs->name.compare("tls_max")==0)
      continue;
    throw Convert_Error(b->lhs->name,"Invalid member of Authorization: ");
  }
  return ctx->make_record(elist,ctx->make_author_type());
}

const Expr*
elab_init(Elaborator* ctx, std::vector<const Expr*> elist)
{//for now only ofp, maybe more things later
  for(const Expr* e: elist)
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);
    if(b->rhs->t == &(ctx->ofpptr) && b->lhs->name.compare("opf")==0)
      continue;
    throw Convert_Error(b->lhs->name,"Invalid member of Initialization: ");
  }
  return ctx->make_record(elist,ctx->make_init_type());
}

const Expr*
elab_ofp(Elaborator* ctx, std::vector<const Expr*> elist)
{//what if advertise is first on list? what happens?
  bool found_version = false;
  bool need_advertise = false;
  bool found_advertise = false;
  for(const Expr* e: elist)
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);
    if(b->rhs->t == &(ctx->verptr) && b->lhs->name.compare("version")==0)
    {
      found_version = true;
      const Ver_expr* v = dynamic_cast<const Ver_expr*>(b->rhs);
      if(v->val.compare("1.3.1")==0)
        need_advertise = true;
      continue;
    }
    if(b->rhs->t == &(ctx->advertptr) && b->lhs->name.compare("advertise")==0)
    {
      found_advertise = true;
      continue;
    }
    if(b->rhs->t == &(ctx->msptr) && b->lhs->name.compare("echo_interval")==0)
      continue;
    if(b->rhs->t == &(ctx->intptr) && b->lhs->name.compare("echo_miss")==0)
      continue;
    if(b->rhs->t == &(ctx->msptr) && b->lhs->name.compare("hello_timeout")==0)
      continue;
    if(b->rhs->t == &(ctx->strptr) && b->lhs->name.compare("app")==0)
      continue;
    throw Convert_Error(b->lhs->name,"Invalid member of OFP: ");
  }
  if((found_version && !need_advertise) ||
     (found_version && need_advertise && found_advertise))
    return ctx->make_record(elist,ctx->make_ofp_type());
  else
    throw Elab_Error("Missing member of OFP");
}

const Expr*
elab_connector(Elaborator* ctx, std::vector<const Expr*> elist)
{//same as realm really, but can't make it generic enough to use for both
  bool need_private_key = false;
  bool found_addresses = false;
  bool found_private_key = false;
  for(const Expr* e: elist)//this is a list of bindings
  {
    const Bind_expr* b = dynamic_cast<const Bind_expr*>(e);//force
    if(b->rhs->t == &(ctx->connectionptr) && b->lhs->name.compare("connections")==0)
    {//is a type addresses, and named address 
      found_addresses = true;//right type, successful search
      if(check_for_tls(ctx, b->rhs))
        need_private_key = true;
      continue;
    }
    if(b->rhs->t == &(ctx->strptr) && b->lhs->name.compare("private_key") ==0)
    {//is type string, and is named private key...
      found_private_key = true;
      continue;
    }//if it's not supposed be in a realm, this line will catch that
    throw Convert_Error(b->lhs->name,"Invalid member of Connector: ");
  }    
  if(need_private_key && !found_private_key)
      throw Elab_Error("private_key in connector not found");
  if((!need_private_key && found_addresses) ||//no private key, just addresses
     (found_addresses && found_private_key))//both private key and addresses
    return ctx->make_record(elist, ctx->make_connector_type());
  else
    throw Elab_Error("Missing member of Connector");
}

const Expr*
elab_record(Elaborator* ctx, const std::string& name, 
            std::vector<const Expr*> elist)
{//this function takes a record, and will match it to the correct elab function
  const Expr* returnval;
  if(name.compare("Realm") ==0 )
    returnval = elab_realm(ctx, elist);
  if(name.compare("Authentication") ==0 )
    returnval = elab_authen(ctx, elist);
  if(name.compare("Authorization")==0 )
    returnval = elab_author(ctx, elist);
  if(name.compare("Initialization") ==0 )
    returnval = elab_init(ctx, elist);
  if(name.compare("OFP")==0)
    returnval = elab_ofp(ctx, elist);
  if(name.compare("Connector")==0)
    returnval = elab_connector(ctx, elist);
  return returnval;
}

const List_Type*
return_type(Elaborator* ctx, const std::string& name)
{
  const List_Type* ret = nullptr;
  if(name.compare("ACL")==0)
    ret = &(ctx->aclptr);//aclptr
  if(name.compare("x509")==0)
    ret = &(ctx->x509ptr);//x509ptr
  if(name.compare("Advertise")==0)
    ret = &(ctx->advertptr);//advertptr
  if(name.compare("Addresses")==0)
    ret = &(ctx->addrlistptr);//connectorptr
  if(name.compare("Connections")==0)
    ret = &(ctx->connectionptr);
  return ret;
}

bool
is_list_valid(Elaborator* ctx, std::vector<const Expr*>& elist,
              const std::string& type)
{ //given a list and a type, check if all elements on list match the type
  //will rewrite addresses as connections
  const List_Type* lt = return_type(ctx, type);
  bool coerce_type = false;
  if(lt->type == &(ctx->connptr))
    coerce_type =true;//means if you see address type, coerce to connection
  for(unsigned int x = 0; x<elist.size();x++)
  {
    auto e = elist[x];
    if(coerce_type)//only for connptr now
    {
      if(e->t == &(ctx->addrptr))
        {
          const Listener_expr* l = dynamic_cast<const Listener_expr*>(e);
          //rewrite the pointer
          elist[x] = ctx->make_listen(l->p,l->ip1,l->port1,l->ip2,l->port2,ctx->make_conn_type());
          continue;
        }
    }
    if(e->t != lt->type)//lt contains the type of its list, predefined
      return false;
  }
  return true;
}

bool
is_record(const std::string& name)
{
  if(name.compare("Realm") ==0 || name.compare("Authentication") ==0 ||
     name.compare("Authorization")==0 || name.compare("Initialization") ==0 ||
     name.compare("OFP")==0 || name.compare("Connector") ==0)
    return true;
  return false;
}

const Expr*
elab_list(Elaborator* ctx, const List* l)
{//all groups of things are lists in the parser, need to reorganize
  Scope_Manager(ctx->env);
  std::vector<const Expr*> expr_list;
  for(const Node* n: l->vec)
    expr_list.push_back(ctx->elab(n));
  //At this point we know the contents are valid, but do they belong
  //to this list/record?
  const Expr* returnval = nullptr;
  if(is_record(l->name.tval))
    returnval = elab_record(ctx, l->name.tval, expr_list);//make_record called
  else
  { //it's a list, check if all members of correct type
    if( !is_list_valid(ctx, expr_list, l->name.tval))
       throw Elab_Error("Bad element in list, list type: "+ l->name.tval);
       //i guess make_list takes the item type?
    returnval = ctx->make_list(expr_list, return_type(ctx, l->name.tval));
  } 
  return returnval;
}

const Expr* 
elab_bind(Elaborator* ctx, const Bind* b)
{
  std::string name = b->lhs->val.tval;
  const Expr* e = ctx->elab(b->rhs);
  if(ctx->env.lookup(name) != nullptr)//if name already defined
    throw Elab_Error("redefining identifier "+name);
  ctx->env.push_binding(name, e);
  const Sym_expr* sym = dynamic_cast<const Sym_expr*>(ctx->elab(b->lhs));
  return ctx->make_bind(sym, e);
}

const Stage*
Elaborator::coerce_type(const Base_Type* in)
{
  const Record_Type* rt = dynamic_cast<const Record_Type*>(in);
  const Stage* returnval = nullptr;
  if(rt==nullptr)
    throw Elab_Error("Couldn't coerce type in staging");
  if(rt->name == Record_Type::Realm)
    returnval = make_stage_type(Stage::Realm, Stage::Realm);
  if(rt->name == Record_Type::Connector)
    returnval = make_stage_type(Stage::Connector, Stage::Connector);
  if(rt->name == Record_Type::Authen)
    returnval = make_stage_type(Stage::Authen, Stage::Authen);
  if(rt->name == Record_Type::Author)
    returnval = make_stage_type(Stage::Author, Stage::Author);
  if(rt->name == Record_Type::Init)
    returnval = make_stage_type(Stage::Init, Stage::Init);
  return returnval;
}

const Stage*
Elaborator::combine_stage_type(const Base_Type* a, const Base_Type* b)
{ //this function may need to coerse the record types to stage types....
  //valid combinations are realm author, author authen, authen init
  const Stage* in1 = dynamic_cast<const Stage*>(a);
  const Stage* in2 = dynamic_cast<const Stage*>(b);
  if(in1 == nullptr){in1 = coerce_type(a);}
  if(in2 == nullptr){in2 = coerce_type(b);}
  if(in1->t2 == Stage::Realm && in2->t1 == Stage::Authen)
    return make_stage_type(in1->t1, in2->t2);
  else if(in1->t2 == Stage::Connector && in2->t1 == Stage::Authen)
    return make_stage_type(in1->t1, in2->t2);
  else if(in1->t2 == Stage::Authen && in2->t1 == Stage::Author)
    return make_stage_type(in1->t1, in2->t2);
  else if(in1->t2 == Stage::Author && in2->t1 == Stage::Init)
    return make_stage_type(in1->t1, in2->t2);
  else
    throw Elab_Error("Couldn't combine staging types");
}

const Expr* //TODO
elab_arrow(Elaborator* ctx, const Arrow* a)
{ //going to try to not have a top_level distinction for arrow
  const Expr* lhs = ctx->elab(a->lhs);
  const Expr* rhs = ctx->elab(a->rhs);
  //not sure how to do below function
  const Stage* stage_t = ctx->combine_stage_type(lhs->t, rhs->t);
  bool has_tls = false;
  bool is_valid = false;
  auto lhs_sym = dynamic_cast<const Sym_expr*>(lhs);
  auto rhs_sym = dynamic_cast<const Sym_expr*>(rhs);
  auto lhs_check = dynamic_cast<const Record_expr*>(ctx->env.lookup(lhs_sym->name));
  auto rhs_check = dynamic_cast<const Record_expr*>(ctx->env.lookup(rhs_sym->name));
  //I am so sorry, this is so bad =(
  if(stage_t->t1 == Stage::Realm && stage_t->t2 == Stage::Authen)
  {//if true, we must check it for consistency
    for(auto e:lhs_check->record)
    {
      auto bind_e = dynamic_cast<const Bind_expr*>(e);
      if(bind_e->rhs->t == &(ctx->addrlistptr))
        has_tls = check_for_tls(ctx, bind_e->rhs);
    }
    if(has_tls)//check the rhs for public key
    {
      for(auto e:rhs_check->record)
      {
        auto bind_e = dynamic_cast<const Bind_expr*>(e);
        if(bind_e->rhs->t == &(ctx->x509ptr))
          is_valid = true;
      }
    }
    else
      is_valid = true;
    if(!is_valid)
      throw Elab_Error("If tls is used in a realm, the authentication staged must have a list of x509 keys");
  }
  if(stage_t->t1 == Stage::Connector && stage_t->t2 == Stage::Authen)
  {//if true, we must check it for consistency
    for(auto e:lhs_check->record)
    {
      auto bind_e = dynamic_cast<const Bind_expr*>(e);
      if(bind_e->rhs->t == &(ctx->connectionptr))
        has_tls = check_for_tls(ctx, bind_e->rhs);
    }
    if(has_tls)//check the rhs for public key
    {
      for(auto e:rhs_check->record)
      {
        auto bind_e = dynamic_cast<const Bind_expr*>(e);
        if(bind_e->rhs->t == &(ctx->x509ptr))
          is_valid = true;
      }
    }
    else
      is_valid = true;
    if(!is_valid)
      throw Elab_Error("If tls is used in a realm, the authentication staged must have a list of x509 keys");
  }
  return ctx->make_arrow(lhs,rhs,stage_t);
}

const Expr* 
elab_id(Elaborator* ctx, const Identifier* i)
{//any identifier at this point is ASSUMED to be in the environment already
  //std::cout<<"elab id";
  std::string name = i->val.tval;
  //std::cout<<name<<'\n';
  const Expr* expr = ctx->env.lookup(name);
  if(expr == nullptr) throw Elab_Error("undefined identifier: "+name);
  return ctx->make_sym(name, expr->t);//name and type
}

const Expr*
elab_addr(Elaborator* ctx, const Address* a)
{//TODO check that ports are valid port numbers
  std::string proto = a->proto.tval;
  const Expr* addr1 = ctx->elab(a->addr1);
  const Int_expr* port1; Listener_expr::Proto p;
  //set these for defaults in case of address used as connection
  std::vector<const Hex_expr*> v = {ctx->make_hex(0)};
  const Expr* addr2 = ctx->make_ipv6(v);
  const Int_expr* port2 = ctx->make_int(0,ctx->make_int_type());
  if(proto.compare("tls") == 0)
  {//port can be empty, in which case it should be 6633
    p = Listener_expr::tls;
    if(a->port1 != nullptr)
      port1 = dynamic_cast<const Int_expr*>(ctx->elab(a->port1));
    else
      port1 = ctx->make_int(uint32_t(6633),&(ctx->intptr));//default tls
  }
  else
  {
    p = Listener_expr::tcp;
    if(a->port1 == nullptr)
      throw Elab_Error("Tcp address must have port specified");
    port1 = dynamic_cast<const Int_expr*>(ctx->elab(a->port1));
  }
  if(a->addr2 == nullptr && a->port2 == nullptr)//then it's an address
    return ctx->make_listen(p,addr1,port1,addr2,port2,ctx->make_addr_type());
  //at this point it must be a connection
  addr2 = ctx->elab(a->addr2);
  port2 = dynamic_cast<const Int_expr*>(ctx->elab(a->port2));
  return ctx->make_listen(p,addr1, port1, addr2, port2, ctx->make_conn_type());
}

const Expr* 
elab_ver(Elaborator* ctx, const Version* v)
{//not sure if this is the best way to do it
  std::string val = v->version;
  if(val.compare("1.0") == 0 ||
     val.compare("1.1") == 0 ||
     val.compare("1.2") == 0 ||
     val.compare("1.3") == 0 ||
     val.compare("1.3.1") == 0)
    return ctx->make_ver(val);
  else
    throw Elab_Error("Invalid version number");
}

uint32_t
to_int(const std::string& s)
{
  for(char c: s)
  {
    std::locale loc = std::locale();
    if(!isdigit(c,loc))
      throw Convert_Error(s, "This is not a valid int");
  }//what follows converts the int
  std::stringstream ss; uint32_t ret;
  ss<<s;//put string into string stream
  ss>>ret;//read it out as an int
  return ret;
}

const Expr* //return base_type can be either msptr or intptr
elab_int(Elaborator* ctx, const Lit_int* l)
{ 
  uint32_t val = to_int(l->val.tval);//extract int from token in node object
  if(l->unit.tkind == Token::unit_ms) //then its already in ms
    return ctx->make_int(val, &(ctx->msptr));
  else if(l->unit.tkind == Token::unit_s)//conver to ms
    return ctx->make_int(val*1000, &(ctx->msptr));
  return ctx->make_int(val, &(ctx->intptr));//otherwise return a normal int
}

const Expr*
elab_str(Elaborator* ctx, const Lit_str* l)//TODO
{ //these turn into filenames, to type check, try opening the file
  //TODO make this return file contents, or check that the file
  //can be opened, not the string
  std::string file = l->val.tval;
  return ctx->make_str(file);
}

const Expr*
elab_ipv4(Elaborator* ctx, const Lit_ipv4* l)
{ 
  const Int_expr* g1 = dynamic_cast<const Int_expr*>(ctx->elab(l->grp1));
  const Int_expr* g2 = dynamic_cast<const Int_expr*>(ctx->elab(l->grp2));
  const Int_expr* g3 = dynamic_cast<const Int_expr*>(ctx->elab(l->grp3));
  const Int_expr* g4 = dynamic_cast<const Int_expr*>(ctx->elab(l->grp4));
  if(g1->t != &(ctx->intptr) || g2->t != &(ctx->intptr) ||
     g3->t != &(ctx->intptr) || g4->t != &(ctx->intptr) )//correct int type
    throw Elab_Error("Error making ipv4");
  if(g1->val > 255  || g2->val > 255 || g3->val > 255 || g4->val > 255)
    throw Elab_Error("ipv4 value out of range");
  return ctx->make_ipv4(g1,g2,g3,g4);
}

uint16_t
to_hex(const std::string& s)
{
  std::string checked_str = "";
  for(char c: s)
  {
    std::locale loc = std::locale();
    if(!isxdigit(c,loc))
      throw Convert_Error(s, "This is not a valid hex number");
  }
  std::stringstream ss; uint16_t ret;
  ss<<s;//put string into string stream
  ss>>std::hex>>ret;//read it out as an int
  return ret;
}

const Expr*
elab_ipv6(Elaborator* ctx, const Lit_ipv6* l)
{//convert everything to hex
  std::vector<const Hex_expr*> ip;
  for(std::string s: l->groups)
  {//convert and make hex object
    const Hex_expr* hex = ctx->make_hex(to_hex(s));
    ip.push_back(hex);
  }//maybe check value of hex to check if in valid range?
  return ctx->make_ipv6(ip);
}

const Expr*
elab_net(Elaborator* ctx, const Lit_network* l)
{//has an ipv4 or ipv6, then an int less than 32 for 4, and 128 for 6
  const Expr* ret = nullptr;
  const Expr* ip_expr = ctx->elab(l->ip);
  const Int_expr* i = dynamic_cast<const Int_expr*>(ctx->elab(l->netmask));
  if(i->t != &(ctx->intptr) &&//if i isn't int, and ip_expr isn't ip address 
    (ip_expr->t != &(ctx->ip4ptr) || ip_expr->t != &(ctx->ip6ptr) ) )
   throw Elab_Error("Incorrect types for a network");
  //types correct, check 
  if(ip_expr->t == &(ctx->ip4ptr) && i->val <= 32)
    ret = ctx->make_net(ip_expr,i);
  else if(ip_expr->t == &(ctx->ip6ptr) && i->val <= 128)
    ret = ctx->make_net(ip_expr,i);
  else
    throw Elab_Error("Incorrect netmask value");
  return ret;
}

const Expr* 
Elaborator::elab (const Node* n)//DO NOT CALL THIS YOURSELF
{ //This is the top level rule, called by the parse_tree elab
  //Errors will be thrown, and are only handled in the other elab function
  Elabvis e(this);
  n->accept(e);
  if(e.result == nullptr)
    throw Elab_Error("nullptr returned from elaboration");
  return e.result;
}

void
Elaborator::elab (Parse_Tree& pt)
{ 
  try {
    Elab_Tree et;
    const Expr* e = nullptr;
    for(const Node* n : pt)
    {
      e = elab(n);
      if(e == nullptr || isTypeError)//if nullptr returned, or there was an error
        break;
      et.push_back(e);
    }
    result = et;//result of visiting all nodes in parse tree;
  }
  catch(const Elab_Error& e)
  {
    isTypeError = true;
    std::cout<<"error: "<<e.errmsg<<'\n';
  }
  catch(const Convert_Error& e)
  {
    isTypeError = true; //refers to whole typechecking phase
    std::cout<<"error: "<<e.errmsg<<'\n';
    std::cout<<"val: "<<e.val<<'\n';
  }
}

std::string 
to_string(Elab_Tree& et)
{//i can't actually do this without an elaboration object
  Print_expr p;
  for(const Expr* e: et)
  {
    e->accept(p);
    p.ss<<'\n';
  }
  return p.ss.str();
}

}//end namespace