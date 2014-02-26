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


%module flog_ofp_v1_1

%include "flog_ofp.i"

%{
#include <libflog/proto/ofp/v1_1/message.hpp>
%}

namespace flog {
namespace ofp {
namespace v1_1 {

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
    IN_PORT, DL_VLAN, DL_PCP, DL_TYPE, NW_TOS, NW_PROTO, TP_SRC, TP_DST, 
    MPLS_LABEL, MPLS_TC, ALL
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
  uint32_t      mpls_label;
  uint8_t       mpls_tc;
  uint64_t      metadata;
  uint64_t      metadata_mask;
};

struct Port {
  enum Id {
    MAX, IN_PORT, TABLE, NORMAL, FLOOD, ALL, CONTROLLER, LOCAL, ANY 
  };

  enum Config {
    PORT_DOWN, NO_RECV, NO_FWD, NO_PACKET_IN 
  };

  enum State {
    LINK_DOWN, BLOCKED, LIVE 
  };

  enum Features {
    TEN_MB_HD, TEN_MB_FD, HUNDRED_MB_HD, HUNDRED_MB_FD, ONE_GB_HD, ONE_GB_FD, 
    TEN_GB_FD, FORTY_GB_FD, HUNDRED_GB_FD, ONE_TB_FD, OTHER, COPPER, FIBER, 
    AUTO_NEG, PAUSE, PAUSE_ASYM 
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
  uint32_t      curr_speed;
  uint32_t      max_speed;
};

struct Action_output { 
  uint16_t port;
  uint16_t max_len;
};

struct Action_set_vlan_vid { 
  uint16_t vlan_vid;
};

struct Action_set_vlan_pcp { 
  uint8_t vlan_pcp;
};

struct Action_set_dl_src { 
    Ethernet_addr dl_addr;
};

struct Action_set_dl_dst { 
    Ethernet_addr dl_addr;
};

struct Action_set_nw_src { 
    Ipv4_addr nw_addr;
};

struct Action_set_nw_dst { 
    Ipv4_addr nw_addr;
};

struct Action_set_nw_tos { 
  uint8_t nw_tos;
};

struct Action_set_nw_ecn {
  uint8_t nw_ecn;
};

struct Action_set_tp_src { 
    uint16_t tp_port;
};

struct Action_set_tp_dst { 
    uint16_t tp_port;
};

struct Action_copy_ttl_out { };

struct Action_copy_ttl_in { };

struct Action_set_mpls_label {
  uint32_t mpls_label;
};

struct Action_set_mpls_tc {
  uint8_t mpls_tc;
};

struct Action_set_mpls_ttl {
  uint8_t mpls_ttl;
};

struct Action_dec_mpls_ttl {
  uint8_t mpls_ttl;
};

struct Action_push_vlan {
  uint16_t ether_type;
};

struct Action_pop_vlan {
  uint16_t ether_type;
};

struct Action_push_mpls {
  uint16_t ether_type;
};

struct Action_pop_mpls {
  uint16_t ether_type;
};

struct Action_set_queue {
  uint32_t queue_id;
};

struct Action_group {
  uint32_t group_id;
};

struct Action_set_nw_ttl {
  uint8_t nw_ttl;
};

struct Action_dec_nw_ttl {
  uint8_t nw_ttl;
};

struct Action_experimenter {
  uint32_t experimenter;
};

union Action_payload_data {
  Action_output         output;
  Action_set_vlan_vid   set_vlan_vid;
  Action_set_vlan_pcp   set_vlan_pcp;
  Action_set_dl_src     set_dl_src;
  Action_set_dl_dst     set_dl_dst;
  Action_set_nw_src     set_nw_src;
  Action_set_nw_dst     set_nw_dst;
  Action_set_nw_tos     set_nw_tos;
  Action_set_tp_src     set_tp_src;
  Action_set_tp_dst     set_tp_dst;
  Action_copy_ttl_out   copy_ttl_out;
  Action_copy_ttl_in    copy_ttl_in;
  Action_set_mpls_label set_mpls_label;
  Action_set_mpls_tc    set_mpls_tc;
  Action_set_mpls_ttl   set_mpls_ttl;
  Action_dec_mpls_ttl   dec_mpls_ttl;
  Action_push_vlan      push_vlan;
  Action_pop_vlan       pop_vlan;
  Action_push_mpls      push_mpls;
  Action_pop_mpls       pop_mpls;
  Action_set_queue      set_queue;
  Action_group          group;
  Action_set_nw_ttl     set_nw_ttl;
  Action_dec_nw_ttl;    dec_nw_ttl;
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


struct Instruction_goto_table {
  uint8_t table_id;
};

struct Instruction_write_metadata {
  uint64_t metadata;
  uint64_t metadata_mask;
};

struct Instruction_write_actions {
  Sequence<Action> actions;
};

struct Instruction_apply_actions {
  Sequence<Action> actions;
};

struct Instruction_clear_actions {
  Sequence<Action> actions;
};

struct Instruction_experimenter {
  uint32_t experimenter_id;
};

union Instruction_payload_data {
private:
  Instruction_payload_data& operator=(const Instruction_payload_data&);
public:
  Instruction_goto_table      goto_table;
  Instruction_write_metadata  write_metadata;
  Instruction_write_actions   write_actions;
  Instruction_apply_actions   apply_actions;
  Instruction_clear_actions   clear_actions;
  Instruction_experimenter    experimenter;
};

struct Instruction_payload {
private:
  Instruction_payload& operator=(const Instruction_payload&);
public:
  typedef Instruction_payload_data Data;
  Data data;
};

enum Instruction_type;

struct Instruction_header {
  Instruction_type type;
  uint16_t         length;
};

struct Instruction {
  Instruction_header  header;
  Instruction_payload payload;
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

struct Bucket {
  uint16_t len;
  uint16_t weight;
  uint32_t watch_port;
  uint32_t watch_group;
  Sequence<Action> actions;
};

struct Bucket_counter {
  uint64_t packet_count;
  uint64_t byte_count;
};

// Messages

struct Hello {
  Greedy_buffer data;
};

struct Error {
  enum Type {
    HELLO_FAILED, BAD_REQUEST, BAD_ACTION, BAD_INSTRUCTION, BAD_MATCH,
    FLOW_MOD_FAILED, GROUP_MOD_FAILED, PORT_MOD_FAILED, TABLE_MOD_FAILED,
    QUEUE_OP_FAILED, SWITCH_CONFIG_FAILED
  };

  enum Hello_failed {
    HF_INCOMPATIBLE, HF_EPERM
  };

  enum Bad_request {
    BR_BAD_VERSION, BR_BAD_TYPE, BR_BAD_STAT, BR_BAD_EXPERIMENTER, 
    BR_BAD_SUBTYPE, BR_EPERM, BR_BAD_LEN, BR_BUFFER_EMPTY, BR_BUFFER_UNKNOWN,
    BR_BAD_TABLE_ID
  };
  
  enum Bad_action {
    BA_BAD_TYPE, BA_BAD_LEN, BA_BAD_EXPERIMENTER, BA_BAD_EXPERIMENTER_TYPE, 
    BA_BAD_OUT_PORT, BA_BAD_ARGUMENT, BA_EPERM, BA_TOO_MANY, BA_BAD_QUEUE,
    BA_BAD_OUT_GROUP, BA_MATCH_INCONSISTENT, BA_UNSUPPORTED_ORDER, BA_BAD_TAG
  };

  enum Bad_instruction {
    BI_UNKNOWN_INST, BI_UNSUP_INST, BI_BAD_TABLE_ID, BI_UNSUP_METADATA,
    BI_UNSUP_METADATA_MASK, BI_UNSUP_EXP_LIST
  };

  enum Bad_match {
    BM_BAD_TYPE, BM_BAD_LEN, BM_BAD_TAG, BM_BAD_DL_ADDR_MASK, 
    BM_BAD_HW_ADDR_MASK, BM_BAD_WILDCARDS, BM_BAD_FIELD, BM_BAD_VALUE
  };
  
  enum Flow_mod_failed {
    FMF_UNKNOWN, FMF_TABLE_FULL, FMF_OVERLAP, FMF_EPERM, FMF_BAD_TIMEOUT, 
    FMF_BAD_COMMAND
  };
  
  enum Port_mod_failed {
    PMF_BAD_PORT, PMF_BAD_HW_ADDR, PMF_BAD_CONFIG, PMF_BAD_ADVERTISE
  };

  enum Table_mod_failed {
    TMF_BAD_TABLE, TMF_BAD_CONFIG
  };
  
  enum Queue_op_failed {
    QOF_BAD_PORT, QOF_BAD_QUEUE, QOF_EPERM
  };

  enum Switch_config_failed {
    SCF_BAD_FLAGS, SCF_BAD_LEN
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

struct Experimenter { 
  uint32_t      experimenter_id;
  Greedy_buffer data;
};

struct Feature_req { };

struct Feature_res { 
  enum Capability {
    FLOW_STATS, TABLE_STATS, PORT_STATS, GROUP_STATS, IP_REASM, QUEUE_STATS,
    ARP_MATCH_IP 
  };

  uint64_t       datapath_id;
  uint32_t       n_buffers;
  uint8_t        n_tbls;
  Capability     capabilities;
  uint32_t       reserved;
  Sequence<Port> ports;
};

struct Get_config_req { };

struct Get_config_res { 
  enum Flags { 
    FRAG_NORMAL, FRAG_DROP, FRAG_REASM, FRAG_MASK, 
    INVALID_TTL_TO_CONTROLLER 
  };

  Flags flags;
  uint16_t miss_send_len;
};

struct Set_config { 
  enum Flags {
    FRAG_NORMAL, FRAG_DROP, FRAG_REASM, FRAG_MASK, 
    INVALID_TTL_TO_CONTROLLER 
  };

  Flags flags;
  uint16_t miss_send_len;
};

struct Packet_in { 
  enum Reason { NO_MATCH, ACTION };

  uint32_t buffer_id;
  uint32_t in_port; 
  uint32_t in_phy_port; 
  Reason   reason;
  uint8_t  tbl_id;
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
  enum Flags { SEND_FLOW_REM, CHECK_OVERLAP };

  uint64_t              cookie;
  uint64_t              cookie_mask;
  Command               command;
  uint16_t              idle_timeout;
  uint16_t              hard_timeout;
  uint16_t              priority;
  uint32_t              buffer_id;
  uint32_t              out_port;
  uint32_t              out_group;
  Flags                 flags;
  Match                 match;
  Sequence<Instruction> instructions;
};

struct Flow_removed { 
  enum Reason { IDLE_TIMEOUT, HARD_TIMEOUT, DELETE, GROUP_DELETE };

  uint64_t cookie;
  uint16_t priority;
  Reason   reason;
  uint8_t  table_id;
  uint32_t duration_sec;
  uint32_t duration_nsec;
  uint16_t idle_timeout;
  uint64_t packet_count;
  uint64_t byte_count;
  Match    match;
};

struct Group_mod {
  enum Command { ADD, MODIFY, DELETE };

  enum Type { ALL, SELECT, INDIRECT, FF };

  Command          command;
  Type             type;
  uint32_t         group_id;
  Sequence<Bucket> buckets;
};

struct Port_mod { 
  enum Config {
    PORT_DOWN, NO_RECV, NO_FWD, NO_PACKET_IN 
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

struct Table_mod {
  enum Config {
    MISS_CONTROLLER, MISS_CONTINUE, MISS_DROP, MISS_MASK
  };

  uint8_t table_id;
  Config config;
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
  uint8_t  table_id;
  uint32_t out_port;
  uint32_t out_group;
  uint64_t cookie;
  uint64_t cookie_mask;
  Match    match;
};

struct Stats_req_aggregate { 
  uint8_t  table_id;
  uint32_t out_port;
  uint32_t out_group;
  uint64_t cookie;
  uint64_t cookie_mask;
  Match    match;
};

struct Stats_req_table { };

struct Stats_req_port { 
  uint32_t port_no;
};

struct Stats_req_queue { 
  uint32_t port_no;
  uint32_t queue_id;
};

struct Stats_req_group {
  uint32_t group_id;
};

struct Stats_req_group_desc { };

struct Stats_req_experimenter { 
  uint32_t      experimenter_id;
  Greedy_buffer data;
};

union Stats_req_payload_data {
private:
  Stats_req_payload_data& operator=(const Stats_req_payload_data&);
public:
  Stats_req_desc         desc;
  Stats_req_flow         flow;
  Stats_req_aggregate    aggregate;
  Stats_req_table        table;
  Stats_req_port         port;
  Stats_req_queue        queue;
  Stats_req_group        group;
  Stats_req_group_desc   group_desc;
  Stats_req_experimenter experimenter;
};

struct Stats_req_payload {
private:
  Stats_req_payload& operator=(const Stats_req_payload&);
public:
  typedef Stats_req_payload_data Data;
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
  uint16_t              length;
  uint8_t               table_id;
  uint32_t              duration_sec;
  uint32_t              duration_nsec;
  uint16_t              priority;
  uint16_t              idle_timeout;
  uint16_t              hard_timeout;
  uint64_t              cookie;
  uint64_t              packet_count;
  uint64_t              byte_count;
  Match                 match;
  Sequence<Instruction> instructions;
};

struct Stats_res_flows {
  Sequence<Stats_res_flow> flows;
};

struct Stats_res_aggregate { 
  uint64_t packet_count;
  uint64_t byte_count;
  uint32_t flow_count;
};

struct Stats_res_port { 
  uint32_t port_no;
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

struct Stats_res_ports {
  Sequence<Stats_res_port> ports;
};

struct Stats_res_queue { 
  uint32_t port_no;
  uint32_t queue_id;
  uint64_t tx_bytes;
  uint64_t tx_packets;
  uint64_t tx_errors;
};

struct Stats_res_queues {
  Sequence<Stats_res_queue> queues;
};

struct Stats_res_table { 
  uint8_t       table_id;
  Stringbuf<32> name;
  uint32_t      wildcards;
  uint32_t      match;
  uint32_t      instructions;
  uint32_t      write_actions;
  uint32_t      apply_actions;
  uint32_t      config;
  uint32_t      max_entries;
  uint32_t      active_count;
  uint64_t      lookup_count;
  uint64_t      matched_count;
};

struct Stats_res_tables {
  Sequence<Stats_res_table> tables;
};

struct Stats_res_group {
  uint16_t                 length;
  uint32_t                 group_id;
  uint32_t                 ref_count;
  uint64_t                 packet_count;
  uint64_t                 byte_count;
  Sequence<Bucket_counter> bucket_stats;
};

struct Stats_res_groups {
  Sequence<Stats_res_group> groups;
};

struct Stats_res_group_desc {
  uint16_t         length;
  uint8_t          type;
  uint32_t         group_id;
  Sequence<Bucket> buckets;
};

struct Stats_res_group_descs {
  Sequence<Stats_res_group_desc> group_descs;
};

struct Stats_res_experimenter { 
  uint32_t      experimenter_id;
  Greedy_buffer data;
};

union Stats_res_payload_data {
private:
  Stats_res_payload_data& operator=(const Stats_res_payload_data&);
public:
  Stats_res_desc         desc;
  Stats_res_flows        flow;
  Stats_res_aggregate    aggregate;
  Stats_res_ports        port;
  Stats_res_queues       queue;
  Stats_res_tables       table;
  Stats_res_groups       group;
  Stats_res_group_descs  group_desc;
  Stats_res_experimenter experimenter;
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
  uint32_t port;
};

struct Queue_get_config_res { 
  uint32_t port;
  Sequence<Queue> queues;
};

enum Version_type;

enum Message_type {
  HELLO, ERROR, ECHO_REQ, ECHO_RES, EXPERIMENTER, FEATURE_REQ, FEATURE_RES, 
  GET_CONFIG_REQ, GET_CONFIG_RES, SET_CONFIG, PACKET_IN, FLOW_REMOVED, 
  PORT_STATUS, PACKET_OUT, FLOW_MOD, GROUP_MOD, PORT_MOD, TABLE_MOD, 
  STATS_REQ, STATS_RES, BARRIER_REQ, BARRIER_RES, QUEUE_GET_CONFIG_REQ, 
  QUEUE_GET_CONFIG_RES
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
  Experimenter         experimenter;
  Feature_req          feature_req;
  Feature_res          feature_res;
  Get_config_req       get_config_req;
  Get_config_res       get_config_res;
  Set_config           set_config;
  Packet_in            packet_in;
  Flow_removed         flow_removed;
  Port_status          port_status;
  Packet_out           packet_out;
  Flow_mod             flow_mod;
  Group_mod            group_mod;
  Port_mod             port_mod;
  Table_mod            table_mod;
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
};

size_t bytes(const Message&);

Error_condition is_valid(const Message&);

Error_condition from_buffer(Buffer_view&, Message& m);
Error_condition to_buffer(Buffer_view&, Message& m);

std::string to_string(const Message& m, Formatter f);

} // namespace v1_1
} // namespace ofp
} // namespace flog
