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

#ifndef CFG_TOKEN_H
#define CFG_TOKEN_H

#include <locale>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include "config.hpp"

namespace cfg {
struct Location {
  Location();
  Location(int,int);
  int col;
  int line;
};

struct Token {  
  //each of the reserved keywords needs its own Tkind
  enum Tkind{ eof, invalid, comment, digit, string, identifier, sym_dot, 
              sym_bind, sym_lcurly, sym_rcurly, sym_comma, sym_colon, sym_bar,
              sym_2colon, sym_slash, sym_arrow, key_realm, key_addr, key_authen,
              key_author, key_init, key_acl, key_x509, key_ofp, key_ad, 
              key_app, key_connector, key_connection,key_tcp, key_tls, unit_s, unit_ms};
  Token();
  Token(Location);
  Token(Tkind, const std::string&, Location, const std::string&);
  Token& operator=(const Token&);
  Tkind tkind;
  std::string tval;
  Location locate;
  std::string file;
};

class Tokenizer {
  public:
    Tokenizer(const std::string&);
    const Token& peek();
    Token::Tkind peek_tkind_n(unsigned int);
    Token::Tkind peek_tkind();
    Token consume();
  private:
    void move_and_set(std::string&);
    std::map<std::string, Token::Tkind> make_table();
    void lex_next_token();
    void trim();
    void eof();
    bool is_comment();
    void tok_comment();
    Token tok_string();
    Token tok_digit();
    Token tok_symbol();
    Token tok_identifier();
    Location locate;
    std::locale loc;
    std::ifstream input;
    std::string filename;
    std::vector<Token> current;
    std::map<std::string, Token::Tkind> table;
};
std::string to_string(std::vector<Token>&);
void test_tokenizer(Tokenizer&);
}

#endif