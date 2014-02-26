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

#include <libflog/proto/ofp/v1_0/factory.hpp>
#include <libflog/proto/ofp/v1_0/state.hpp>
#include <libflog/proto/ofp/v1_0/application.hpp>

using namespace flog;
using namespace flog::ofp;
using namespace flog::ofp::v1_0;

struct Test_agent : v1_0::Agent {
  void init(const Time& t) { } 
};

int switch_test() {
  Time t(0);
  Timer_config tc;
  tc.hello_wait = Time(5);
  tc.echo_req_interval = Time(5);
  tc.echo_res_wait = Time(2);
  tc.feature_req_wait = Time(5);
  tc.feature_res_wait = Time(5);
  tc.barrier_res_wait = Time(5);
    
  Test_agent ta;
  Xid_generator<uint32_t> xid;
  FSM_config c(FSM_config::v1_0, FSM_config::a1_0, tc);
  FSM_switch fsm_sw(c, xid, ta);

  if (fsm_sw.state != FSM_switch::IDLE) {
   std::cout << "FAIL: switch did not reach IDLE state " << '\n';
   return -1;
  }

  init(fsm_sw, t);
  
  // Test 1: Verify fsm_sw is in FEATURE_WAIT state
  if (fsm_sw.state != FSM_switch::FEATURE_WAIT) {
   std::cout << "FAIL: switch did not reach FEATURE_WAIT state"<< '\n';
   return -1; 
  }

  // Test 2:  Verify fsm_sw is in ESTABLISHED STATE
  v1_0::Factory f = v1_0::Message::factory(xid);  
  recv(fsm_sw, Time(2), *(f.make_feature_req()));
  
  if (fsm_sw.state != FSM_switch::ESTABLISHED) {
   std::cout << "FAIL: switch did not reach ESTABLISHED state" << '\n';
   return -1;
   }

  // Test 5: Verify echo timeout triggers FAIL state
  time(fsm_sw, Time(7)); 
  time(fsm_sw, Time(9, 1));
  if (fsm_sw.state != FSM_switch::FAIL){
	  std::cout << "FAIL: switch did not reach FAIL state after echo timeout" << '\n';
	  return -1;
  }
  
  // Test 3: Verify fini puts fsm_sw into IDLE state
  fini(fsm_sw, t + Time(1));
  
  if (fsm_sw.state != FSM_switch::IDLE) {
   std::cout << "FAIL: fini did not set state back to IDLE" << '\n';
   return -1;
  } 


  // Test 4: Verify fsm_sw reaches fail state after feature_req timeout
  t = Time(0, 0);
  init(fsm_sw, t);
  t = Time(5, 1);

  time(fsm_sw, t);
  if (fsm_sw.state != FSM_switch::FAIL){
   std::cout << "FAIL: switch did not reach FAIL state after feature_req timeout " << '\n';
   return -1;
  }

  time(fsm_sw, t);
  return 0;
}

struct Test_app : v1_0::Application {
  void init(const Time& t) { } 
};

int controller_test() {
  Time t(0);
  Timer_config tc;
  tc.hello_wait = Time(5);
  tc.echo_req_interval = Time(5);
  tc.echo_res_wait = Time(2);
  tc.feature_req_wait = Time(5);
  tc.feature_res_wait = Time(5);
  tc.barrier_res_wait = Time(5);
  
  Test_app myapp;
  Xid_generator<uint32_t> xid; 
  FSM_config c(FSM_config::v1_0, FSM_config::a1_0, tc);
  FSM_controller fsm_ctl(c,xid, myapp);

  if (fsm_ctl.state != FSM_controller::IDLE) {
   std::cout << "FAIL: controller did not reach IDLE state " << '\n';
   return -1;
  }

  init(fsm_ctl, t);
  
  // Test 1: Verify fsm_ctl is in FEATURE_WAIT state
  if (fsm_ctl.state != FSM_controller::FEATURE_WAIT) {
   std::cout << "FAIL: controller did not reach FEATURE_WAIT state"<< '\n';
   return -1; 
  }

  // Test 2:  Verify fsm_ctl is in ESTABLISHED STATE
  v1_0::Factory f = v1_0::Message::factory(xid);  
  
  recv(fsm_ctl, Time(2), *(f.make_feature_res()));
  if (fsm_ctl.state != FSM_controller::ESTABLISHED) {
    std::cout << "FAIL: controller did not reach ESTABLISHED state" << '\n';
    return -1;
  }
  time(fsm_ctl, Time(7));
  time(fsm_ctl, Time(9, 1));
  // Test 5:  Verify controller is in fail state after echo timeout
  if (fsm_ctl.state != FSM_controller::FAIL) {
	  std::cout << "FAIL: controller did not reach FAIL state after echo to" << '\n';
    return -1;
  }

  // Test 3: Verify fini puts fsm_ctl into IDLE state
  fini(fsm_ctl, Time(10));
  
  if (fsm_ctl.state != FSM_controller::IDLE) {
    std::cout << "FAIL: fini did not set state back to IDLE" << '\n';
    return -1;
  } 


  // Test 4: Verify fsm_ctl reaches fail state after feature_req timeout
  init(fsm_ctl, t);
  t = Time(5,1);
  time(fsm_ctl, t);
  if (fsm_ctl.state != FSM_controller::FAIL) {
    std::cout << "FAIL: controller did not reach FAIL state after feature_req timeout " << '\n';
    return -1;
  }
  
  return 0;
}

int main() {
  if (switch_test())
    return -1;
  if (controller_test())
    return -1;
  return 0;
}
