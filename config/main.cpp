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

#include <fstream>

#include "parser.hpp"
#include "token.hpp"
#include "tcheck.hpp"
#include "eval.hpp"
void//TODO potentially make this better, return the buffer?
read_arg(const std::string& arg, std::string& buffer)
{
  std::ifstream file(arg);//for some reason, c_str() not needed in sfw
  if(file.is_open())
  {
    file.seekg(0,std::ios::end);
    buffer.resize(file.tellg());//from sfw, kinda smart
    file.seekg(0,std::ios::beg);
    file.read(&buffer[0],buffer.size());
    file.close();
  }
  else
    std::cout<<"\nUnable to open file\n";
}
int 
main(int argc, char* argv[])
{
  using namespace cfg;
  if(argc!=2)
  {
    std::cout<<"Proper usage is ./cfg <file_to_read>.cfg\n";
    std::exit(-1);
  }
  else
  {
    std::string file = argv[1];
    //std::cout<<"Reading "<<file<<"\n\n";
    Tokenizer T(file);
    /*to test tokenizer with*/
    //test_tokenizer(T);
    Parser p(T);
    Parse_Tree pt = p.parse();
    if(p.error())
      std::exit(-1);
    //std::cout<<to_string(pt)<<'\n';
    Elaborator e = Elaborator();
    e.elab(pt);
    if(!e.isTypeError)
    {
      //std::cout<<"Type check success!\n";
      //std::cout<<to_string(e.result)<<'\n';
    }
    else
    {
      std::cout<<"Type check failure\n";
      std::exit(-1);
    }
    Elab_Tree et = e.result;
    Evaluator eval(et);
    eval.evaluate();
    for(auto str:eval.commands)
      std::cout<<str<<'\n';
    //should be done here
  }

}