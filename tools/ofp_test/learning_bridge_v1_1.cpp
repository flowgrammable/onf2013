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

#include "applications/learning_bridge/v1_1/bridge.cpp"

using namespace flog::ofp::v1_1;
using namespace flog::ofp;
using namespace flog;

bool test_init(const Bridge& b)
{
  return b.timeout == 100 and b.none_priority == 0 and b.src_priority == 1
     and b.dst_priority == 2 and b.full_priority == 3;
}

bool test()
{
  Time t(0);
  Bridge b;

  if (not test_init(b))
  {
    std::cout << "incorrect init" << std::endl;
    return false;
  }
  
  Packet_in pi;
  pi.in_port = 2;
  pi.data = Buffer(12);
  for (int i = 0; i <= 11; i++)
    pi.data[i] = i;

  b.packet_in(pi, t);

  if (b.table.size() != 1)
  {
    std::cout << "incorrect table size" << std::endl;
    return false;
  }

  Ethernet_addr addr;
  for (int i = 0; i <= 5; i++)
    addr[i] = i;

  using Record = std::pair<uint16_t, Time>;
  using Iterator = std::unordered_map<Ethernet_addr, Record>::iterator;

  Iterator iter = b.table.find(addr);
  if (iter->second.first != 2)
  {
    std::cout << "incorrect record content" << std::endl;
    return false;
  }

  //send the same packet_in, this should not change learning table
  Packet_in pi2 = pi;
  b.packet_in(pi2, t);

  if (b.table.size() != 1)
  {
    std::cout << "incorrect table size" << std::endl;
    return false;
  }

  if (iter->second.first != 2 and iter->second.second != Time(100))
  {
    std::cout << "incorrect record content" << std::endl;
    return false;
  }

  Time t2(200);
  b.packet_in(pi2, t2);

  if (b.table.size() != 1)
  {
    std::cout << "incorrect table size" << std::endl;
    return false;
  }

  if (iter->second.first != 2 and iter->second.second != Time(300))
  {
    std::cout << "incorrect record content" << std::endl;
    return false;
  }

  //send a new packet_in
  Packet_in pi3;
  pi.in_port = 3;
  pi.data = Buffer(12);
  for (int i = 0; i <= 11; i++)
    pi.data[i] = i + 1;
  b.packet_in(pi, t2);

  Ethernet_addr addr2;
  for (int i = 0; i <= 5; i++)
    addr2[i] = i + 1;

  if (b.table.size() != 2)
  {
    std::cout << "incorrect table size" << std::endl;
    return false;
  }

  iter = b.table.find(addr2);
  if (iter->second.first != 3 and iter->second.second != Time(300))
  {
    std::cout << "incorrect record content" << std::endl;
    return false;
  }

  return true;
}

int main()
{
  return test() ? 0 : -1;
}
