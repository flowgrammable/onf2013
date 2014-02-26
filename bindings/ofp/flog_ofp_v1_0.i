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


%module flog_ofp_v1_0

%include "flog_ofp.i"

%{
#include <libflog/proto/ofp/v1_0/message.hpp>
%}

namespace flog {
namespace ofp {
namespace v1_0 {

// Error handling

enum Error_code;

struct Error_condition {
  Error_code code;

  %pythoncode %{
    def __nonzero__(self):
      return self.code == 0;
  %}
};

// Structures

struct Match {
  enum Wildcards {
    IN_PORT, DL_VLAN, DL_SRC, DL_DST, DL_TYPE, NW_PROTO, TP_SRC, TP_DST, 
    NW_SRC, NW_DST, DL_VLAN_PCP, NW_TOS, ALL
  };
  
  Wildcards     wildcards;
  uint16_t      in_port;
  Ethernet_addr dl_src;
  Ethernet_addr dl_dst;
  uint16_t      dl_vlan;
  uint8_t       dl_pcp;
  uint16_t      dl_type;
  uint8_t       nw_tos;
  uint8_t       nw_proto;
  Ipv4_addr     nw_src;
  Ipv4_addr     nw_dst;
  uint16_t      tp_src;
  uint16_t      tp_dst;
};

struct Port {
  enum Id {
    MAX, IN_PORT, TABLE, NORMAL, FLOOD, ALL, CONTROLLER, LOCAL, NONE 
  };

  enum Config {
    PORT_DOWN, NO_STP, NO_RECV, NO_RECV_STP, NO_FLOOD, NO_FWD, NO_PACKET_IN 
  };

  enum State {
    STP_LISTEN, LINK_DOWN, STP_LEARN, STP_FORWARD, STP_BLOCK, STP_MASK 
  };

  enum Features {
    TEN_MB_HD, TEN_MB_FD, HUNDRED_MB_HD, HUNDRED_MB_FD, ONE_GB_HD, ONE_GB_FD, 
    TEN_GB_FD, COPPER, FIBER, AUTO_NEG, PAUSE, PAUSE_ASYM 
  };

  Id            port_id;
  Ethernet_addr hw_addr;
  Stringbuf<16> name;
  Config        config;
  State         state;
  Features      current;
  Features      advertised;
  Features      supported;
  Features      peer;
};

struct Action_output { 
  uint16_t port;
  uint16_t max_len;
};

struct Action_set_vlan_vid { 
  uint16_t vlan_vid;
};

struct Action_set_vlan_pcp { 
  uint8_t value;
};

struct Action_strip_vlan { };

struct Action_set_dl_src { 
    Ethernet_addr dl_addr;
};

struct Action_set_dl_dst { 
    Ethernet_addr dl_addr;
};

struct Action_set_nw_src { 
    Ipv4_addr addr;
};

struct Action_set_nw_dst { 
    Ipv4_addr addr;
};

struct Action_set_nw_tos { 
  uint8_t value;
};

struct Action_set_tp_src { 
    uint16_t value;
};

struct Action_set_tp_dst { 
    uint16_t value;
};

struct Action_enqueue { 
  uint16_t port;
  uint32_t queue_id;
};

struct Action_vendor { 
  uint32_t vendor;
};

union Action_payload_data {
  Action_output       output;
  Action_set_vlan_vid vlan_vid;
  Action_set_vlan_pcp vlan_pcp;
  Action_strip_vlan   strip_vlan;
  Action_set_dl_src   dl_src;
  Action_set_dl_dst   dl_dst;
  Action_set_nw_src   nw_src;
  Action_set_nw_dst   nw_dst;
  Action_set_nw_tos   nw_tos;
  Action_set_tp_src   tp_src;
  Action_set_tp_dst   tp_dst;
  Action_enqueue      enqueue;
  Action_vendor       vendor;
};

struct Action_payload {
  typedef Action_payload_data Data;
  Data data;
};

enum Action_type;

struct Action_header { 
  Action_type type;
  uint16_t length;
};

struct Action {
  Action_header header;
  Action_payload payload;
};

struct Queue_property_none { };
struct Queue_property_min_rate { };

union Queue_property_payload_data {
  Queue_property_none     none;
  Queue_property_min_rate min_rate;
};

struct Queue_property_payload {
  typedef Queue_property_payload_data Data;
  bool init;
  Data data;
};

enum Queue_property_type;

struct Queue_property_header {
  Queue_property_type property;
  uint16_t length;
};

struct Queue_property {
  Queue_property_header header;
  Queue_property_payload payload;
};

struct Queue {
  uint32_t queue_id;
  uint16_t length;
  Sequence<Queue_property> properties;
};

// Messages

struct Hello {
  Greedy_buffer data;
};

struct Error {
  enum Type {
    HELLO_FAILED, BAD_REQUEST, BAD_ACTION, FLOW_MOD_FAILED, PORT_MOD_FAILED,
    QUEUE_OP_FAILED
  };

  enum Hello_failed {
    HF_INCOMPATIBLE, HF_EPERM
  };

  enum Bad_request {
    BR_BAD_VERSION, BR_BAD_TYPE, BR_BAD_STAT, BR_BAD_VENDOR, BR_BAD_SUBTYPE, 
    BR_EPERM, BR_BAD_LEN, BR_BUFFER_EMPTY, BR_BUFFER_UNKNOWN
  };
  
  enum Bad_action {
    BA_BAD_TYPE, BA_BAD_LEN, BA_BAD_VENDOR, BA_BAD_VENDOR_TYPE, BA_BAD_OUT_PORT,
    BA_BAD_ARGUMENT, BA_EPERM, BA_TOO_MANY, BA_BAD_QUEUE
  };
  
  enum Flow_mod_failed {
    FMF_ALL_TABLES_FULL, FMF_OVERLAP, FMF_EPERM, FMF_BAD_EMERG_TIMEOUT, 
    FMF_BAD_COMMAND, FMF_UNSUPPORTED
  };
  
  enum Port_mod_failed {
    PMF_BAD_PORT, PMF_BAD_HW_ADDR
  };
  
  enum Queue_op_failed {
    QOF_BAD_PORT, QOF_BAD_QUEUE, QOF_EPERM
  };

  union Code;

  Type type;
  Code code;
};

struct Echo_req {
  Greedy_buffer data;
};

struct Echo_res { 
  Greedy_buffer data;
};

struct Vendor { 
  uint32_t      vendor_id;
  Greedy_buffer data;
};

struct Feature_req { };

struct Feature_res { 
  enum Capability {
    FLOW_STATS, TABLE_STATS, PORT_STATS, STP, RESERVED, IP_REASM, QUEUE_STATS,
    ARP_MATCH_IP 
  };
  
  enum Action {
    OUTPUT, SET_VLAN_VID, SET_VLAN_PCP, STRIP_VLAN, SET_DL_SRC, SET_DL_DST,
    SET_NW_SRC, SET_NW_DST, SET_NW_TOS, SET_TP_SRC, SET_TP_DST, ENQUEUE
  };

  uint64_t       datapath_id;
  uint32_t       n_buffers;
  uint8_t        n_tbls;
  Capability     capabilities;
  Action         feature_actions; 
  Sequence<Port> ports;
};

struct Get_config_req { };

struct Get_config_res { 
  enum Flags { FRAG_NORMAL, FRAG_DROP, FRAG_REASM, FRAG_MASK };

  Flags flags;
  uint16_t miss_send_len;
};

struct Set_config { 
  enum Flags {
    FRAG_NORMAL, FRAG_DROP, FRAG_REASM, FRAG_MASK
  };

  Flags flags;
  uint16_t miss_send_len;
};

struct Packet_in { 
  enum Reason { NO_MATCH, ACTION };

  uint32_t buffer_id;
  uint16_t total_len;
  uint16_t in_port; 
  Reason   reason;
  Buffer   data;
};

struct Packet_out { 
  uint32_t buffer_id;
  uint16_t in_port;
  uint16_t actions_len;
  Sequence<Action> actions;
  Greedy_buffer data;
};

struct Flow_mod { 
  enum Command { ADD, MODIFY, MODIFY_STRICT, DELETE, DELETE_STRICT };
  enum Flags { SEND_FLOW_REM, CHECK_OVERLAP, EMERG };

  Match            match;
  uint64_t         cookie;
  Command          command;
  uint16_t         idle_timeout;
  uint16_t         hard_timeout;
  uint16_t         priority;
  uint32_t         buffer_id;
  uint16_t         out_port;
  Flags            flags;
  Sequence<Action> actions;
};

struct Flow_removed { 
  enum Reason { IDLE_TIMEOUT, HARD_TIMEOUT, DELETE };

  Match    match;
  uint64_t cookie;
  uint16_t priority;
  Reason   reason;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  uint16_t idle_timeout;
  uint64_t packet_count;
  uint64_t byte_count;
};

struct Port_mod { 
  enum Config {
    PORT_DOWN, NO_STP, NO_RECV, NO_RECV_STP, NO_FLOOD, NO_FWD, NO_PACKET_IN 
  };

  enum Features { 
    TEN_MB_HD, TEN_MB_FD, HUNDRED_MB_HD, HUNDRED_MB_FD, ONE_GB_HD, ONE_GB_FD, 
    TEN_GB_FD, COPPER, FIBER, AUTO_NEG, PAUSE, PAUSE_ASYM
  };

  uint16_t      port;
  Ethernet_addr hw_addr; 
  Config        config;
  Config        mask;
  Features      advertise;
};

struct Port_status { 
  enum Reason { ADD, DELETE, MODIFY };

  Reason reason;
  Port   port;
};

enum Stats_type;

struct Stats_header
{
  enum Flags { MORE };

  Stats_type type;
  Flags      flags;
};

struct Stats_req_desc { };

struct Stats_req_flow { 
  Match    match;
  uint8_t  table_id;
  uint16_t out_port;
};

struct Stats_req_aggregate { 
  Match    match;
  uint8_t  table_id;
  uint16_t out_port;
};

struct Stats_req_table { };

struct Stats_req_port { 
  uint16_t port_no;
};

struct Stats_req_queue { 
  uint16_t port_no;
  uint32_t queue_id;
};

struct Stats_req_vendor { 
  uint32_t      vendor_id;
  Greedy_buffer data;
};

union Stats_req_payload_data {
private:
  Stats_req_payload_data& operator=(const Stats_req_payload_data&);
public:
  Stats_req_desc      desc;
  Stats_req_flow      flow;
  Stats_req_aggregate aggr;
  Stats_req_table     table;
  Stats_req_port      port;
  Stats_req_queue     queue;
  Stats_req_vendor    vendor;
};

struct Stats_req_payload {
private:
  Stats_req_payload& operator=(const Stats_req_payload&);
public:
  typedef Stats_req_payload_data Data;
  bool init;
  Data data;
};

struct Stats_req {
  Stats_header header;
  Stats_req_payload payload;
};

struct Stats_res_desc { 
  Stringbuf<256> mfr_desc;
  Stringbuf<256> hw_desc;
  Stringbuf<256> sw_desc;
  Stringbuf<32>  serial_num;
  Stringbuf<256> dp_desc;
};

struct Stats_res_flow { 
  uint16_t         length;
  uint8_t          table_id;
  Match            match;
  uint32_t         duration_sec;
  uint32_t         duration_nsec;
  uint16_t         priority;
  uint16_t         idle_timeout;
  uint16_t         hard_timeout;
  uint64_t         cookie;
  uint64_t         packet_count;
  uint64_t         byte_count;
  Sequence<Action> actions;
};

struct Stats_res_aggregate { 
  uint64_t packet_count;
  uint64_t byte_count;
  uint32_t flow_count;
};

struct Stats_res_table { 
  uint8_t  table_id;
  Stringbuf<32> name;
  uint32_t wildcards;
  uint32_t max_entries;
  uint32_t active_count;
  uint64_t lookup_count;
  uint64_t matched_count;
};

struct Stats_res_port { 
  uint16_t port_no;
  uint64_t rx_packets;
  uint64_t tx_packets;
  uint64_t rx_bytes;
  uint64_t tx_bytes;
  uint64_t rx_dropped;
  uint64_t tx_dropped;
  uint64_t rx_errors;
  uint64_t tx_errors;
  uint64_t rx_frame_err;
  uint64_t rx_over_err;
  uint64_t rx_crc_err;
  uint64_t collisions;
};

struct Stats_res_queue { 
  uint16_t port_no;
  uint32_t queue_id;
  uint64_t tx_bytes;
  uint64_t tx_packets;
  uint64_t tx_errors;
};

struct Stats_res_vendor { 
  uint32_t      vendor_id;
  Greedy_buffer data;
};

struct Stats_res_flows {
  Sequence<Stats_res_flow> flows;
};

struct Stats_res_tables {
  Sequence<Stats_res_table> tables;
};

struct Stats_res_ports {
  Sequence<Stats_res_port> ports;
};

struct Stats_res_queues {
  Sequence<Stats_res_queue> queues;
};

union Stats_res_payload_data {
private:
  Stats_res_payload_data& operator=(const Stats_res_payload_data&);
public:
  Stats_res_desc      desc;
  Stats_res_flows     flow;
  Stats_res_aggregate aggr;
  Stats_res_tables    table;
  Stats_res_ports     port;
  Stats_res_queues    queue;
  Stats_res_vendor    vendor;
};

struct Stats_res_payload {
private:
  Stats_res_payload& operator=(const Stats_res_payload&);
public:
  typedef Stats_res_payload_data Data;
  bool init;
  Data data;
};

struct Stats_res {
  Stats_header header;
  Stats_res_payload payload;
};

struct Barrier_req { };

struct Barrier_res { };

struct Queue_get_config_req { 
  uint16_t port;
};

struct Queue_get_config_res { 
  uint16_t port;
  Sequence<Queue> queues;
};

enum Version_type;

enum Message_type {
  HELLO, ERROR, ECHO_REQ, ECHO_RES, VENDOR, FEATURE_REQ, FEATURE_RES, 
  GET_CONFIG_REQ, GET_CONFIG_RES, SET_CONFIG, PACKET_IN, FLOW_REMOVED, 
  PORT_STATUS, PACKET_OUT, FLOW_MOD, PORT_MOD, STATS_REQ, STATS_RES, 
  BARRIER_REQ, BARRIER_RES, QUEUE_GET_CONFIG_REQ, QUEUE_GET_CONFIG_RES
};

struct Header
{
  Version_type version;
  Message_type type;
  uint16_t length;
  uint32_t xid;
};

union Payload_data
{
private:
  Payload_data& operator=(const Payload_data&);
public:
  Hello                hello;
  Error                error;
  Echo_req             echo_req;
  Echo_res             echo_res;
  Vendor               vendor;
  Flow_mod             flow_mod;
  Feature_req          feature_req;
  Feature_res          feature_res;
  Get_config_req       get_config_req;
  Get_config_res       get_config_res;
  Set_config           set_config;
  Packet_in            packet_in;
  Flow_removed         flow_removed;
  Port_status          port_status;
  Packet_out           packet_out;
  Port_mod             port_mod;
  Stats_req            stats_req;
  Stats_res            stats_res;
  Barrier_req          barrier_req;
  Barrier_res          barrier_res;
  Queue_get_config_req queue_get_config_req;
  Queue_get_config_res queue_get_config_res;
};

struct Payload
{
  typedef Payload_data Data;
private:
  Payload& operator=(const Payload&);
public:
  bool init;
  Data data;
};

struct Message
{
  Header header;
  Payload payload;

  %pythoncode %{
    def __str__(self):
      f = Formatter()
      return to_string(self, f)
  %}
};

size_t bytes(const Message&);

Error_condition is_valid(const Message&);

Error_condition from_buffer(Buffer_view&, Message& m);
Error_condition to_buffer(Buffer_view&, const Message& m);

std::string to_string(const Message& m, Formatter f);

} // namespace v1_0
} // namespace ofp
} // namespace flog
