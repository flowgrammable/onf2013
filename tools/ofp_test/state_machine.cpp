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


#include <set>

#include <libflog/proto/ofp/fsm_negotiation.hpp>

using namespace flog;
using namespace flog::ofp;

void 
test1()
{
  std::cout << "test1" << std::endl;

  Timer_config tc;
  Time t(2);
  tc.hello_wait = t;

  FSM_config c(FSM_config::v1_0, FSM_config::a1_0, tc);

  Negotiation<v1_0::Message> a(c);
  if (a.state != Negotiation<v1_0::Message>::IDLE)
    std::cout << "a idle" << std::endl;

  Negotiation<v1_0::Message> b(c);
  if (b.state != Negotiation<v1_0::Message>::IDLE)
    std::cout << "b idle" << std::endl;

  Time t2(0);

  v1_0::Message* m1 = v1_0::Message::mk_hello(to_stack_version(a.config.supported));
  v1_0::Message* m2 = v1_0::Message::mk_hello(to_stack_version(b.config.supported));
  //std::pair<bool, std::vector<v1_0::Message*> > = idle_init(a, t2); 
  
  Result<v1_0::Message> r1 = idle_init(a, t2); 
  if (not r1.first 
      or *(r1.second[0]) != *m1 
      or a.state != Negotiation<v1_0::Message>::WAIT)
    std::cout << "a idle-wait" << std::endl;
  
  Result<v1_0::Message> r2 = idle_init(b, t2); 
  if (not r2.first 
      or *(r2.second[0]) != *m2 
      or b.state != Negotiation<v1_0::Message>::WAIT)
    std::cout << "b idle-wait" << std::endl;

  Time t3(0);
  
  Result<v1_0::Message> r3 = recv(a, t3, *m2);
  if (r3.first 
      or not r3.second.empty()
      or a.state != Negotiation<v1_0::Message>::SUCCESS)
    std::cout << "a wait-success" << std::endl;
    
  //std::cout << to_string(a) << std::endl;

  Result<v1_0::Message> r4 = recv(b, t3, *m1);
  if (r4.first 
      or not r4.second.empty()
      or b.state != Negotiation<v1_0::Message>::SUCCESS)
    std::cout << "b wait-success" << std::endl;
}


//void test(FSM_config c1, FSM_config c2, int idle_wait_time, int wait_recv_time)
std::vector<FSM_config> 
get_set()
{
  //std::set<FSM_config> s;
  std::vector<FSM_config> s;
  Timer_config tc;
  //Time t(0);
  
  FSM_config c(FSM_config::v1_0, FSM_config::a1_0, tc);
  
  c.supported = FSM_config::Supported(1);
  s.push_back(c);

  c.version = FSM_config::v1_1;
  for (int i = 2; i <= 3; i++)
  {
    c.supported = FSM_config::Supported(i);
    s.push_back(c);
  }

  c.version = FSM_config::v1_2;
  for (int i = 4; i <= 7; i++)
  {
    c.supported = FSM_config::Supported(i);
    s.push_back(c);
  }

  c.version = FSM_config::v1_3;
  for (int i = 8; i <= 15; i++)
  {
    c.supported = FSM_config::Supported(i);
    s.push_back(c);
  }

  c.version = FSM_config::v1_3_1;
  for (int i = 8; i <= 15; i++)
  {
    c.supported = FSM_config::Supported(i);
    s.push_back(c);
  }
  
  //std::cout << s.size() << std::endl;
  //for (auto x : set)
  //  std::cout << to_string(x) << std::endl;

  return s;
}

template<typename T1, typename T2>
  bool
  execute(FSM_config c1, FSM_config c2)
  {
    Time t(0);

    Negotiation<T1> n1(c1);
    Negotiation<T2> n2(c2);

    idle_init(n1, t);
    idle_init(n2, t);

    T1* m1 = T1::mk_hello(n1.config.supported);
    T2* m2 = T2::mk_hello(n2.config.supported);

    recv(n1, t, *m2); 
    recv(n2, t, *m1); 

    return n1.state == Negotiation<T1>::SUCCESS
       and n2.state == Negotiation<T2>::SUCCESS;
  }

/*
bool
execute_special(FSM_config c1, FSM_config c2)
{
  if (c1.version == FSM_config::v1_3 and c2.version == FSM_config::v1_3_1)
  {
    Time t(0);

    Negotiation<v1_3::Message> n1(c1);
    Negotiation<v1_3_1::Message> n2(c2);

    idle_init(n1, t);
    idle_init(n2, t);

    v1_3::Message* m1 
      = v1_3::Message::mk_hello(to_stack_version(n1.config.supported));
    v1_3_1::Message* m2 
      = v1_3_1::Message::mk_hello(to_stack_version(n2.config.supported));

    //Buffer_view v;
    //v1_3::to_buffer(v, 

    recv(n1, t, *m2); 
    recv(n2, t, *m1); 

    return n1.state == Negotiation<v1_3::Message>::SUCCESS
       and n2.state == Negotiation<v1_3_1::Message>::SUCCESS;

  }
  else if (c1.version == FSM_config::v1_3_1 and c2.version == FSM_config::v1_3)
  {
    Time t(0);

    Negotiation<v1_3_1::Message> n1(c1);
    Negotiation<v1_3::Message> n2(c2);

    idle_init(n1, t);
    idle_init(n2, t);

    v1_3_1::Message* m1 
      = v1_3_1::Message::mk_hello(to_stack_version(n1.config.supported));
    v1_3::Message* m2 
      = v1_3::Message::mk_hello(to_stack_version(n2.config.supported));

    recv(n1, t, *m2); 
    recv(n2, t, *m1); 

    return n1.state == Negotiation<v1_3_1::Message>::SUCCESS
       and n2.state == Negotiation<v1_3::Message>::SUCCESS;


  }
  else
    return false;
}
*/

bool
compare(FSM_config c1, FSM_config c2)
{
  switch(c1.version) {
  case FSM_config::v1_0:
    switch(c2.version) {
    case FSM_config::v1_0:
    return execute<v1_0::Message, v1_0::Message>(c1, c2);
    case FSM_config::v1_1:
    return execute<v1_0::Message, v1_1::Message>(c1, c2);
    case FSM_config::v1_2:
    return execute<v1_0::Message, v1_2::Message>(c1, c2);
    case FSM_config::v1_3:
    return execute<v1_0::Message, v1_3::Message>(c1, c2);
    case FSM_config::v1_3_1:
    return execute<v1_0::Message, v1_3::Message>(c1, c2);
    default: return false;
    }
  case FSM_config::v1_1:
    switch(c2.version) {
    case FSM_config::v1_0:
    return execute<v1_1::Message, v1_0::Message>(c1, c2);
    case FSM_config::v1_1:
    return execute<v1_1::Message, v1_1::Message>(c1, c2);
    case FSM_config::v1_2:
    return execute<v1_1::Message, v1_2::Message>(c1, c2);
    case FSM_config::v1_3:
    return execute<v1_1::Message, v1_3::Message>(c1, c2);
    case FSM_config::v1_3_1:
    return execute<v1_1::Message, v1_3::Message>(c1, c2);
    default: return false;
    } 
  case FSM_config::v1_2:
    switch(c2.version) {
    case FSM_config::v1_0:
    return execute<v1_2::Message, v1_0::Message>(c1, c2);
    case FSM_config::v1_1:
    return execute<v1_2::Message, v1_1::Message>(c1, c2);
    case FSM_config::v1_2:
    return execute<v1_2::Message, v1_2::Message>(c1, c2);
    case FSM_config::v1_3:
    return execute<v1_2::Message, v1_3::Message>(c1, c2);
    case FSM_config::v1_3_1:
    return execute<v1_2::Message, v1_3::Message>(c1, c2);
    default: return false;
    } 
  case FSM_config::v1_3:
    switch(c2.version) {
    case FSM_config::v1_0:
    return execute<v1_3::Message, v1_0::Message>(c1, c2);
    case FSM_config::v1_1:
    return execute<v1_3::Message, v1_1::Message>(c1, c2);
    case FSM_config::v1_2:
    return execute<v1_3::Message, v1_2::Message>(c1, c2);
    case FSM_config::v1_3:
    return execute<v1_3::Message, v1_3::Message>(c1, c2);
    //case FSM_config::v1_3_1:
    //return execute<v1_3::Message, v1_3::Message>(c1, c2);
    //return execute_special(c1, c2);
    //return true;
    default: return false;
    } 
  case FSM_config::v1_3_1:
    switch(c2.version) {
    case FSM_config::v1_0:
    return execute<v1_3_1::Message, v1_0::Message>(c1, c2);
    case FSM_config::v1_1:
    return execute<v1_3_1::Message, v1_1::Message>(c1, c2);
    case FSM_config::v1_2:
    return execute<v1_3_1::Message, v1_2::Message>(c1, c2);
    //case FSM_config::v1_3:
    //return execute<v1_3_1::Message, v1_3_1::Message>(c1, c2);
    //return execute_special(c1, c2);
    case FSM_config::v1_3_1:
    return execute<v1_3_1::Message, v1_3_1::Message>(c1, c2);
    default: return false;
    } 
  default: return false;
  }
  return false;
}

int 
max_supported(int x)
{
  if (x & 8)
    return 8;
  else if (x & 4)
    return 4;
  else if (x & 2)
    return 2;
  else if (x & 1)
    return 1;
  else return 0;
}

bool
quick_compare(FSM_config c1, FSM_config c2)
{
  int x = max_supported(int(c1.supported));
  int y = max_supported(int(c2.supported));

  if (x == y)
    return true;
  else if (x > y)
    return y & int(c1.supported);
  else
    return x & int(c2.supported);
}

bool
test()
{
  std::vector<FSM_config> s1 = get_set(); 
  std::vector<FSM_config> s2 = get_set(); 

  int fail_count = 0;

  for (auto x : s1)
  {
    for (auto y : s2) 
    {
      if ((x.version == FSM_config::v1_3 
          and y.version == FSM_config::v1_3_1)
          or (x.version == FSM_config::v1_3_1 
          and y.version == FSM_config::v1_3))
        continue;

      bool qc = quick_compare(x, y);
      //std::cout << to_string(x) << std::endl;
    
      bool c = compare(x, y);
    
      if (c != qc)
      {
        std::cout << "quick algorithm : ";
        std::cout << qc << std::endl;
        std::cout << "state machine under test: ";
        std::cout << c << std::endl;
        std::cout << to_string(x) << std::endl;
        std::cout << to_string(y) << std::endl;
        fail_count++;
      }
    }
  }

  std::cout << "fail count: " << fail_count << std::endl;
  return fail_count == 0; 
}

int 
main()
{
  //test1();

  return test() ? 0 : -1;
}



