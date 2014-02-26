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

#include "applications/learning_bridge/v1_0/bridge.cpp"

using namespace flog::ofp::v1_0;
using namespace flog::ofp;
using namespace flog;

int main(){
    Bridge b;
    std::cout << "tx_queue size: " << b.tx_queue.size() << std::endl;
    

    Match m;
    Sequence<Action> actions;
    
    Action a1;
    a1.header.type = ACTION_OUTPUT;
    Action_output p1;
    p1.port = Port::CONTROLLER;
    construct(a1.payload, Action_output::Tag(), int(p1.port), -1);
    actions.push_back(a1);
    
    Action a2;
    a2.header.type = ACTION_OUTPUT;
    Action_output p2;
    p2.port = Port::FLOOD;
    construct(a2.payload, Action_output::Tag(), int(p2.port), -1);
    actions.push_back(a2);
    
    uint16_t out_port = int(p2.port);
    uint16_t hard_timeout = -1;
    uint16_t priority = 0;

    Message* first_fm = new Message(0, Flow_mod::Tag(), m, 0, Flow_mod::ADD, 0, hard_timeout, priority, 0, out_port
    , Flow_mod::SEND_FLOW_REM, actions);
    
    // Test 1: Verify flow mod is in tx_queue on startup

    Common_message& mout = b.tx_queue[0];
     if(*first_fm != *mout.ptr.m1) {
        std::cout << "FAIL: incorrect flow_mod in tx_queue " << std::endl;
        return -1;
     }
   // std::cout << to_string(*msg) << std::endl;
    return 0;
}
