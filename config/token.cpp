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

#include "token.hpp"

namespace cfg {
Location::Location()
:col(1),line(1)
{}
Location::Location(int c, int l)
:col(c),line(l)
{}
//
// Token
//
Token::Token()
:tkind(Tkind::invalid), tval(""), locate(Location()), file("")
{}

Token::Token(Location l)
:tkind(Tkind::eof), tval(""), locate(l), file("")
{}

Token::Token(Tkind kind, const std::string& val, Location l, 
             const std::string& filename)
:tkind(kind), tval(val), locate(l), file(filename)
{}
Token&
Token::operator=(const Token& rhs)
{
  this->tkind = rhs.tkind;
  this->tval = rhs.tval;
  this->locate = rhs.locate;
  this->file = rhs.file;
  return *this;
}
//
// Tokenizer
//
Tokenizer::Tokenizer(const std::string& filen)
: locate(Location(1,1)),loc(std::locale()),input(filen),filename(filen),
  table(make_table())
{
  lex_next_token();
}
std::map<std::string, Token::Tkind> 
Tokenizer::make_table()
{
  std::map<std::string, Token::Tkind> map;
  map = { 
          {".",Token::sym_dot},
          {"=",Token::sym_bind},
          {"{",Token::sym_lcurly},
          {"}",Token::sym_rcurly},
          {",",Token::sym_comma},
          {":",Token::sym_colon},
          {"::",Token::sym_2colon},
          {"|",Token::sym_bar},
          {"/",Token::sym_slash},
          {"->",Token::sym_arrow},
          {"Realm",Token::key_realm},
          {"Addresses",Token::key_addr},//this may need a better name
          {"Authentication",Token::key_authen},
          {"Authorization",Token::key_author},
          {"Initialization",Token::key_init},
          {"ACL",Token::key_acl},
          {"x509",Token::key_x509},
          {"OFP",Token::key_ofp},
          {"Advertise",Token::key_ad},
          {"Apps",Token::key_app},
          {"Connector",Token::key_connector},
          {"Connections",Token::key_connection},
          {"tcp", Token::key_tcp},
          {"tls", Token::key_tls},
          {"s",Token::unit_s},
          {"ms",Token::unit_ms}//could add tcp and tls as keywords
        };
  return map;
}
void
Tokenizer::move_and_set(std::string& val)
{//This function is called everywhere, so pulled it out, does as said
  if(!input.eof())
  {
    char c = input.get();
    val += c;
    locate.col++;
  }
}
void
Tokenizer::eof()
{
  current.push_back(Token(Token::Tkind::eof, "eof",locate,filename));
}
void
Tokenizer::trim()
{//removes whitespace, I am not sure if it works properly
  using namespace std;
  while(isspace(char(input.peek())) && input.good())//and a, isspace
  {
    if(input.peek() == '\n')
    {
      input.get();
      locate.col = 1;
      locate.line++;
    }
    else
    {
      //char c = input.peek();//debugging
      input.get();
      locate.col++;
    }
  }
}
bool
Tokenizer::is_comment()
{
  bool is_comm = false;
  if (char(input.peek()) == '/')
  {
    input.get();
    if(char(input.peek())=='/')
      is_comm = true;
    input.unget();
  }
  return is_comm;
}
void
Tokenizer::tok_comment()
{//removes all comments, should be in while loop for multi line comments
  std::string val = "";
  while(is_comment())
  {
    while(input.good() && (input.peek()!='\n'))
      move_and_set(val);
    trim();//remove newlines and tabs after comments
  }
}
Token
Tokenizer::tok_string()
{//given a string in ' " ' chars, grab the string literal
  std::string val = "";
  input.ignore(1);
  locate.col++;
  while(input.peek() != '"' && input.good())
    move_and_set(val);//if no ending ", will eat all chars
  input.ignore(1);
  locate.col++;//this must be a " char, or eof
  return Token(Token::string, val,locate, filename);
}
Token
Tokenizer::tok_digit()
{ //grabs integer or parts of a version, also grabs hex
  std::string val = "";
  move_and_set(val);
  while(isxdigit(char(input.peek()),loc))
    move_and_set(val);
  return Token(Token::digit, val,locate, filename);
}
Token
Tokenizer::tok_identifier()
{ //anything starting with a char, and ending with char or num or _ is grabbed
  std::string val = "";
  move_and_set(val);
  while((isalnum(char(input.peek()),loc)|| input.peek() == '_'))
    move_and_set(val);//second to rest can be alpha or num
  auto it = table.find(val);
  if(it == table.end())
    return Token(Token::identifier, val, locate, filename);
  return Token(it->second, val, locate, filename);
}
Token
Tokenizer::tok_symbol()
{ //should grab symbols
  std::string val = "";
  move_and_set(val);
  char c = input.peek();//{ and } don't combine with other symbols
  if (0!=val.compare("{") && 0!=val.compare("}"))
  {
    while(ispunct(c, loc) && !isalnum(c,loc))
    {
      if(is_comment())//got one symbol, if next is comment "//"
        {tok_comment(); break;}//just clear it out here, return what was found
      move_and_set(val);
      c = input.peek();
    }
  }
  auto it = table.find(val);
  if(it == table.end())
    return Token(Token::invalid, "val", locate, filename);
  return Token(it->second, val, locate, filename);
}
void
Tokenizer::lex_next_token()
{//peeks at next token, saves to current if called more than once
  Token tok = Token(locate);
  if(input.eof())
    eof();
  else
  {
    trim();
    tok_comment();
    char c = input.peek();
    if(isalpha(c,loc))
      tok = tok_identifier();
    else if(isxdigit(c,loc))
      tok = tok_digit();
    else if(c == '"')
      tok = tok_string();
    else if(ispunct(c, loc))
      tok = tok_symbol();//label as id anyway
    if(tok.tkind == Token::invalid)
    {
      std::cout<<"Invalid Token, Line: "<<tok.locate.line;
      std::cout<<" Column: "<<tok.locate.col - tok.tval.length()<<'\n';
      std::cout<<"Val: "<<tok.tval<<"\n";
    }
  current.push_back(tok);
  }
}

const Token&
Tokenizer::peek()
{
  return current[0];
}

Token::Tkind
Tokenizer::peek_tkind_n(unsigned int n)
{
  //if current already has enough elements, this loop won't run
  //otherwise, it will run till there are enough elements
  unsigned int highest_index = current.size()-1;
  if(n > highest_index)//not sure what to do with bad input
    for(unsigned int x = highest_index+1; x <= n ; x++)
      lex_next_token();
  return current[n].tkind;
}

Token::Tkind
Tokenizer::peek_tkind()
{
  return current[0].tkind;
}

Token
Tokenizer::consume()
{//returns the closest token peeked at, then clears first elem of current
  Token t = current[0];
  current.erase(current.begin(), current.begin()+1);
  if(current.size() == 0)//if empty, lex next token
    lex_next_token();
  return t;
}
std::string
to_string(std::vector<Token>& tokenstream)
{
  std::stringstream ss;
  for(Token t: tokenstream)
    ss<<"Kind: "<<t.tkind<<" Val: "<<t.tval<<'\n';
  return ss.str();
}

void
test_tokenizer(Tokenizer& T)
{
  std::vector<Token> ts;
  Token t;
  while(1)
  {
    t = T.consume();
    if(t.tkind == Token::eof || t.tkind == Token::invalid)
      break;
    ts.push_back(t);
  }
  std::cout<<to_string(ts)<<'\n';
}

}//end namespace