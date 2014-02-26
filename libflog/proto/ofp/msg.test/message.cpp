
#include <libopenflow/msg.hpp>
#include <libopenflow/msg_v1_0.hpp>
#include <libopenflow/msg_v1_1.hpp>
#include <libopenflow/msg_v1_2.hpp>
#include <libopenflow/msg_v1_3.hpp>
#include <libopenflow/msg_v1_3_1.hpp>

void
v1_0()
{
  using namespace ofp::v1_0;
  
  hello h;
  error e;
  echo_req erq;
  echo_res ers;
  vendor v;
  feature_req frq;
  feature_res frs;
  get_config_req gcrq;
  get_config_res gcrs;
  set_config sc;
  packet_in pi;
  flow_removed fr;
  port_status ps;
  packet_out po;
  flow_mod fm;
  port_mod pm;
  // Uncomment once stats are present
  //stats_req srq;
  //stats_res srs;
  barrier_req brq;
  barrier_res brs;
  queue_get_config_req qgcrq;
  queue_get_config_res qgcrs;
}

void v1_1() 
{
  using namespace ofp::v1_1;
  
	hello h;
  error e;
  echo_req erq;
  echo_res ers;
  experimenter ex;
  feature_req frq;
  feature_res frs;
  get_config_req gcrq;
  get_config_res gcrs;
  set_config sc;
  packet_in pi;
  flow_removed fr;
  port_status ps;
  packet_out po;
  flow_mod fm;
	//group_mod gm;
  port_mod pm;
	table_mod tm;
  //stats_req srq;
  //stats_res srs;
  barrier_req brq;
  barrier_res brs;
  queue_get_config_req qgcrq;
  queue_get_config_res qgcrs;
}

void v1_2() {
  using namespace ofp::v1_2;
	
	hello h;
  error e;
  echo_req erq;
  echo_res ers;
  experimenter ex;
  feature_req frq;
  feature_res frs;
  get_config_req gcrq;
  get_config_res gcrs;
  set_config sc;
  packet_in pi;
  flow_removed fr;
  port_status ps;
  packet_out po;
  flow_mod fm;
	//group_mod gm;
  port_mod pm;
	table_mod tm;
  //stats_req srq;
  //stats_res srs;
  barrier_req brq;
  barrier_res brs;
  queue_get_config_req qgcrq;
  queue_get_config_res qgcrs;
	role_req rrq;
	role_res rrs;
}


void v1_3() {
  using namespace ofp::v1_3;
	
	hello h;
  error e;
  echo_req erq;
  echo_res ers;
  experimenter ex;
  feature_req frq;
  feature_res frs;
  get_config_req gcrq;
  get_config_res gcrs;
  set_config sc;
  packet_in pi;
  flow_removed fr;
  port_status ps;
  packet_out po;
  flow_mod fm;
	//group_mod gm;
  port_mod pm;
	table_mod tm;
  //stats_req srq;
  //stats_res srs;
  barrier_req brq;
  barrier_res brs;
  queue_get_config_req qgcrq;
  queue_get_config_res qgcrs;
	role_req rrq;
	role_res rrs;
	get_async_req garq;
	get_async_res gars;
	set_async sa;
	//meter_mod mm;
}

void v1_3_1() {
  using namespace ofp::v1_3_1;
	
	//hello h;
  error e;
  echo_req erq;
  echo_res ers;
  experimenter ex;
  feature_req frq;
  feature_res frs;
  get_config_req gcrq;
  get_config_res gcrs;
  set_config sc;
  packet_in pi;
  flow_removed fr;
  port_status ps;
  packet_out po;
  flow_mod fm;
	//group_mod gm;
  port_mod pm;
	table_mod tm;
  //stats_req srq;
  //stats_res srs;
  barrier_req brq;
  barrier_res brs;
  queue_get_config_req qgcrq;
  queue_get_config_res qgcrs;
	role_req rrq;
	role_res rrs;
	get_async_req garq;
	get_async_res gars;
	set_async sa;
	//meter_mod mm;
}

int main()
{
  ofp::v1_0::message m;
}
