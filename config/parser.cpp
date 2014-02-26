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

#include "parser.hpp"

namespace cfg {

List::List(Token t, std::vector<const Node*> v)
: name(t), vec(v)
{}

Identifier::Identifier(Token t)
:val(t)
{}

Bind::Bind(const Identifier* l, const Node* r)
:lhs(l), rhs(r)
{}

Arrow::Arrow(const Identifier* l, const Node* r)
:lhs(l), rhs(r)
{}

Address::Address(Token pro, const Node* a1, const Lit_int* p1,
                 const Node* a2, const Lit_int* p2)
:proto(pro), addr1(a1), port1(p1), addr2(a2), port2(p2)
{}

Version::Version(const std::string& s)
:version(s)
{}

Lit_str::Lit_str(Token t)
:val(t)
{}

Lit_int::Lit_int(Token t, Token u)
:val(t), unit(u)
{}

Lit_ipv4::Lit_ipv4(const Lit_int* g1, const Lit_int* g2, const Lit_int* g3,
                   const Lit_int* g4)
:grp1(g1), grp2(g2), grp3(g3), grp4(g4)
{}

Lit_ipv6::Lit_ipv6(std::vector<std::string> v, int z)
: zero_point(z)
{ //TODO check this
  if(zero_point != -1)//there is a :: token
  {//calculate num of zero groups
    std::vector<std::string> fixed;
    int zgroups = 8 - v.size();
    int s = v.size();
    bool zeroes_added = false;
    for(int x = 0; x<s; x++)
    {
      if((x<z && !zeroes_added) || zeroes_added)
        fixed.push_back(v[x]);
      else if(!zeroes_added)
      {
        for(int y = 0; y<zgroups; y++)
          {fixed.push_back("0000");}
        zeroes_added = true;
        fixed.push_back(v[x]);
      }
    }
    groups = fixed;
  }
  else
    groups = v;
}

Lit_network::Lit_network(const Node* i, const Lit_int* n)
:ip(i), netmask(n)
{}
//why doesn't this work?
// Print::Print()
// :tabs(0)
// {}

void
Print::visit(const List& l)
{
  ss<<l.name.tval<<" {\n";
  tabs++;
  for(unsigned int x = 0; x < l.vec.size(); x++)
  {
    for(auto x = 0; x<tabs; x++)
      ss<<"  ";
    const Node* n = l.vec[x];
    n->accept(*this);
    if(x!=l.vec.size()-1)
      ss<<",\n";
    else
      ss<<"\n";
  }
  tabs--;
  for(auto x = 0; x<tabs; x++)
    ss<<"  ";
  ss<<"}";
}

// void
// Print::visit(const Block& b)
// {
//         for(unsigned int x = 0; x < l.vec.size(); x++)
//     {
//       for(auto x = 0; x<tabs; x++)
//         ss<<"  ";
//       const Node* n = l.vec[x];
//       n->accept(*this);
//       if(x!=l.vec.size()-1)
//         ss<<",\n";
//       else
//         ss<<"\n";
//     }
// // }

void
Print::visit(const Bind& b)
{
  b.lhs->accept(*this);
  ss<<" = ";
  b.rhs->accept(*this);
}

void
Print::visit(const Arrow& a)
{
  a.lhs->accept(*this);
  ss<<" -> ";
  a.rhs->accept(*this);
}

void
Print::visit(const Identifier& i)
{
  ss<<i.val.tval; 
}

void
Print::visit(const Address& a)
{//need to check if nullptr, try to print all that aren't nullptr
  ss<<a.proto.tval;
  ss<<" ";
  a.addr1->accept(*this);
  if(a.port1 != nullptr)
    {ss<<"|";a.port1->accept(*this); }
  if(a.addr2 != nullptr)
    {ss<<" ";a.addr2->accept(*this); }
  if(a.port2 != nullptr)
    {ss<<"|";a.port2->accept(*this);}
}

void
Print::visit(const Version& v)
{
  ss<<v.version;
}

void
Print::visit(const Lit_int& l)
{
  ss<<l.val.tval;
  if(l.unit.tkind != Token::invalid)
    ss<<l.unit.tval;
}

void
Print::visit(const Lit_str& l)
{
  ss<<'"'<<l.val.tval<<'"';
}

void
Print::visit(const Lit_ipv4& l)
{
  l.grp1->accept(*this);
  ss<<".";
  l.grp2->accept(*this);
  ss<<".";
  l.grp3->accept(*this);
  ss<<".";
  l.grp4->accept(*this);
}

void
Print::visit(const Lit_ipv6& l)
{//for now, no :: notation printed
  for(unsigned int x=0;x<l.groups.size();x++)
  {
    ss<<l.groups[x];
    if(x!=l.groups.size()-1)
      ss<<':';
  }
}

void
Print::visit(const Lit_network& l)
{
  l.ip->accept(*this);
  ss<<'/';
  l.netmask->accept(*this);
}

// template <typename T>
// Factory<T>::~Factory()
// {
//   for(T* t: store)
//     delete t;//this is giving me a lot of trouble
//   //so i defined ~Node(); and ~Node_Impl<T>(), and now having
//   //more trouble....???
// }

Parse_Error::Parse_Error(Token tok, const std::string& s)
:t(tok), errmsg(s)
{}

Parser::Parser(Tokenizer& t)
:tokenizer(t), isParseError(false), list_names(make_list_name_vec())
{}

std::vector<Token::Tkind>
Parser::make_list_name_vec()
{
  std::vector<Token::Tkind> list;
  list = {Token::key_realm, Token::key_addr, Token::key_authen, Token::key_x509,
          Token::key_acl, Token::key_author, Token::key_init, Token::key_ofp, 
          Token::key_ad, Token::key_app, Token::key_connector, 
          Token::key_connection};
  return list;
}

bool
Parser::is_list_name(const Token& t)
{
  std::vector<Token::Tkind>::iterator it = find(list_names.begin(),
                                                list_names.end(), t.tkind);
  if(it == list_names.end())
    return false;
  return true;
}

const Lit_str*
Parser::parse_str()
{
  if(tokenizer.peek_tkind() == Token::string)
    return make_str(tokenizer.consume());
  return nullptr;
}

const Lit_int*
Parser::parse_int()
{//will take care of optional suffix here
  if(tokenizer.peek_tkind() == Token::digit)
  {
    Token val = tokenizer.consume();
    if(tokenizer.peek_tkind() == Token::unit_s ||
       tokenizer.peek_tkind() == Token::unit_ms)
    {
      Token unit = tokenizer.consume();
      return make_int(val, unit);
    }
    return make_int(val,Token());
  }
  return nullptr;
}

const Node*
Parser::parse_ipv4()
{//some easier way to check?
  if(tokenizer.peek_tkind() == Token::digit &&
     tokenizer.peek_tkind_n(1) == Token::sym_dot &&
     tokenizer.peek_tkind_n(2) == Token::digit &&
     tokenizer.peek_tkind_n(3) == Token::sym_dot &&
     tokenizer.peek_tkind_n(4) == Token::digit &&
     tokenizer.peek_tkind_n(5) == Token::sym_dot &&
     tokenizer.peek_tkind_n(6) == Token::digit)
  {
    const Lit_int* g1 = parse_int();
    tokenizer.consume();
    const Lit_int* g2 = parse_int();
    tokenizer.consume();
    const Lit_int* g3 = parse_int();
    tokenizer.consume();
    const Lit_int* g4 = parse_int();
    return make_ipv4(g1,g2,g3,g4);
  }
  return nullptr;
}

const Node*
Parser::parse_ipv6()//TODO make the check conditions for ipv4 and ipv6 functions
{ //if it starts with ::, or starts with digit or id followed by : or ::, ipv6
  //TODO check for special case ::
  if(tokenizer.peek_tkind() == Token::sym_2colon ||
    ((tokenizer.peek_tkind() ==  Token::digit || 
    tokenizer.peek_tkind() == Token::identifier) &&
    (tokenizer.peek_tkind_n(1) == Token::sym_colon ||
    tokenizer.peek_tkind_n(1) == Token::sym_2colon)))
  {//assume ipv6 now, if error, we throw
    int temp = 0;
    int zero_loc = 0;
    std::vector<std::string> ip;
    bool dblcolon_found = false;
    if(tokenizer.peek_tkind() == Token::sym_2colon)
    {//take care of leading :: here
      dblcolon_found = true;
      tokenizer.consume();//consume ::
    }
    while(1)//break if there isn't a :: or : to parse
    {//take care of leading 
      const Lit_int* x = parse_int();//if this succeeds, below will fail
      const Identifier* y = parse_identifier();//this is ok
      if(x != nullptr)
        ip.push_back(x->val.tval);
      else if(y != nullptr)
        ip.push_back(y->val.tval);
      if(x == nullptr && y == nullptr)
        throw Parse_Error(tokenizer.peek(), "failed to parse ipv6");
      temp++;
      //check for : or ::
      if(tokenizer.peek_tkind() == Token::sym_colon)
        tokenizer.consume();
      else if(tokenizer.peek_tkind() == Token::sym_2colon)
      {
        if(dblcolon_found)
          throw Parse_Error(tokenizer.peek(), "Can't have two :: tokens in ipv6");
        dblcolon_found = true;
        tokenizer.consume();
        if(tokenizer.peek_tkind() == Token::sym_comma ||//is comma
           tokenizer.peek_tkind() == Token::sym_rcurly ||//is }
           tokenizer.peek_tkind() == Token::sym_bar ||
           (tokenizer.peek_tkind() == Token::digit && // 
            tokenizer.peek_tkind_n(1) == Token::sym_dot)) // if ipv4
          break; //lol
        zero_loc = temp;
      }//TODO fix if it ends with ::, going with special case token(':: ')
      else
        break;//break if we don't see a : or ::
    }
    if(dblcolon_found)
      return make_ipv6(ip, zero_loc);
    return make_ipv6(ip, -1);
  }
  return nullptr;
}

const Node*
Parser::parse_ip()
{
  const Node* ret = parse_ipv4();
  if(ret == nullptr)
    ret = parse_ipv6();
  return ret;
}

const Node*
Parser::parse_ip_or_network()
{
  const Node* ip = parse_ip();
  if(ip == nullptr)
    return nullptr;
  if(tokenizer.peek_tkind() == Token::sym_slash)
  {
    tokenizer.consume();
    const Lit_int* mask = parse_int();
    if(mask==nullptr)
      throw Parse_Error(tokenizer.peek(), "expected int for network mask");
    return make_net(ip, mask);
  }
  else
    return ip;//just an ip address
  return nullptr;
}

const Node*
Parser::parse_version()
{
  if(tokenizer.peek_tkind() == Token::digit &&
     tokenizer.peek_tkind_n(1) == Token::sym_dot &&
     tokenizer.peek_tkind_n(2) == Token::digit)
  {
    std::string s;
    const Lit_int* d1 = parse_int();
    tokenizer.consume();
    const Lit_int* d2 = parse_int();
    if(tokenizer.peek_tkind() == Token::sym_dot &&
       tokenizer.peek_tkind_n(1) == Token::digit)
    {
      tokenizer.consume();
      const Lit_int* d3 = parse_int();
      s = d1->val.tval +"."+d2->val.tval+"."+d3->val.tval;
    }
    else
      s = d1->val.tval + "." + d2->val.tval;
    return make_ver(s);
  }
  return nullptr;
}

const Node*
Parser::parse_literal()
{//most likely this function will result in permanent failure
  const Node* lit = parse_str();
  if(lit == nullptr)
    lit = parse_ip_or_network();
  if(lit == nullptr)
    lit = parse_version();
  if(lit == nullptr)
    lit = parse_int();
  return lit;//either nullptr, or a real val
}

const Identifier*
Parser::parse_identifier()//done?
{//return nullptr if not id, or consume if it is
  if(tokenizer.peek_tkind() != Token::identifier)
    return nullptr;
  return make_id(tokenizer.consume());
}

const Node*
Parser::parse_list_item()
{ //either binding or assignee, followed by a ','
  //at this point, the list name, and the { char are not there
  //NEED TO FIX THIS FUNCTION, TODO because of ipv6
  const Identifier* i = parse_identifier();
  if(i == nullptr)
  {//then it's an assignee, and token is not consumed
    const Node* n = parse_assignee();
    if(n==nullptr)
      throw Parse_Error(tokenizer.peek(), "looked for assignee, didn't work");
    return n;
  }
  else if(tokenizer.peek_tkind() == Token::sym_comma ||
          tokenizer.peek_tkind() == Token::sym_rcurly)
  {//we had a single identifier in a list, followed by a comma or }, that's ok
    return i;
  }
  else
  {
    const Node* n = parse_bind(i);
    if(n == nullptr)
      throw Parse_Error(tokenizer.peek(), "Not sure what happened (pli)"); 
      //not sure what above error would mean
    return n;//return a bind
  }
  return nullptr;
}

const Node* 
Parser::parse_list()//done?
{ //check what the name of the list is
  const Node* returnval = nullptr;
  if(is_list_name(tokenizer.peek()))
  {//assume if true, this is a point of no return, must throw on error
    Token name = tokenizer.consume();
    if(tokenizer.peek_tkind() != Token::sym_lcurly)
      throw Parse_Error(tokenizer.peek(), "Lists must start with '{' character"); //no { token
    tokenizer.consume();//the { token
    std::vector<const Node*> list;
    while(tokenizer.peek_tkind() != Token::sym_rcurly)
    {
      const Node* item = parse_list_item();
      if(item == nullptr)
        throw Parse_Error(tokenizer.peek(), "invalid list item...");
      list.push_back(item);
      if(tokenizer.peek_tkind() == Token::sym_comma)
        tokenizer.consume();
      else if(tokenizer.peek_tkind() != Token::sym_rcurly)
        throw Parse_Error(tokenizer.peek(), "Commas must be used between list items");
    }
    tokenizer.consume();//assume this is a } token
    returnval = make_list(name, list);    
  }//not a list, return nullptr
  return returnval;
}

const Node*
Parser::parse_address()
{ //this won't check for tls and no port, that will happen at type checking
  if(tokenizer.peek_tkind() != Token::key_tcp && 
     tokenizer.peek_tkind() != Token::key_tls)
    return nullptr;
  Token connection_type = tokenizer.consume(); 
  //MUST THROW AFTER THIS POINT
  const Node* addr1 = parse_ip();
  if(addr1 == nullptr)
    Parse_Error(tokenizer.peek(), "invalid ip address");
  const Lit_int* port1 = nullptr;
  if(tokenizer.peek_tkind() == Token::sym_bar)//if a port is there
  {
    tokenizer.consume();//the | token
    port1 = parse_int();//the port
  }
  if(tokenizer.peek_tkind() == Token::sym_comma || 
     tokenizer.peek_tkind() == Token::sym_rcurly)
    return make_addr(connection_type, addr1, port1, nullptr, nullptr);
  else//has form proto dest source
  {
    const Node* addr2 = parse_ip();
    if(addr2 == nullptr)
      Parse_Error(tokenizer.peek(), "invalid ip address");
    if(tokenizer.peek_tkind() != Token::sym_bar)
      Parse_Error(tokenizer.peek(), "must have port specified for source ip");
    tokenizer.consume();//the | token
    const Lit_int* port2 = parse_int();
    if(port2 == nullptr)
      Parse_Error(tokenizer.peek(), "must have port specified for source ip");
    return make_addr(connection_type, addr1, port1, addr2, port2);
  }
  return nullptr;
}

const Node*
Parser::parse_assignee()//potential problem here with ipv6 representation
{
  const Node* node1 = parse_identifier();
  if(node1 == nullptr)
    node1 = parse_list();
  if(node1 == nullptr)
    node1 = parse_literal(); 
  if(node1 == nullptr)
    node1 = parse_address();
  if(node1 == nullptr)
    throw Parse_Error(tokenizer.peek(), "No valid arg for assignee");
  return node1;
}

const Node*
Parser::parse_arrow(const Identifier* lhs)//done?
{
  if(lhs == nullptr)//if nullptr passed in, there was an error above this
    return nullptr;
  tokenizer.consume();//CONSUME ->
  const Node* rhs = parse_identifier();//this may be changed at some point
                                       //if arrow gets more complicated
  if(rhs != nullptr)
    return make_arrow(lhs,rhs);
  return nullptr;//at least always returns nullptr;
}

const Node*
Parser::parse_bind(const Identifier* lhs )//done?
{
  if(lhs == nullptr)
    return nullptr;
  tokenizer.consume();//CONSUME =
  const Node* rhs = parse_assignee();
  if(rhs != nullptr)
    return make_bind(lhs,rhs);
  return nullptr;
}

bool
Parser::error()
{
  return isParseError;
}

Parse_Tree
Parser::parse()
{
  try {
  //maybe need to check for nullptr, potentially
    while(tokenizer.peek_tkind() != Token::eof)
    {
      const Node* n;
      const Identifier* i = parse_identifier();
      if(tokenizer.peek_tkind() == Token::sym_bind)
        n = parse_bind(i);
      else if(tokenizer.peek_tkind() == Token::sym_arrow)
        n = parse_arrow(i);
      else
        throw Parse_Error(tokenizer.peek(), "Not valid top level");
      //check that bind or arrow's return val is good
      if(n == nullptr)
        throw Parse_Error(tokenizer.peek(), "Invalid token at this position");
      //add to top level
      pt.push_back(n);
    }
    return pt;
  }
  catch(const Parse_Error& e)
  {
    isParseError = true;
    std::cout<<"Error, val: "<<e.t.tval<<'\n';
    std::cout<<"token kind: "<<e.t.tkind<<'\n';
    std::cout<<"token line: "<<e.t.locate.line<<" c: "<<e.t.locate.col<<'\n';
    std::cout<<"error: "<<e.errmsg<<'\n';
    return pt;
  }

}

std::string
to_string(Parse_Tree& pt)
{
  Print p;
  for(const Node* n: pt)
  {
    n->accept(p);
    p.ss<<'\n'; 
  }
  return p.ss.str();
}

}//end namespace