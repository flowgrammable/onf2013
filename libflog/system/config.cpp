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

#include <sstream>
#include "config.hpp"

namespace flog {
namespace config {

std::string
to_string(const Acl& a)
{
  std::stringstream ss;
  ss << to_string(a.nw) << "/" << a.vlsm;
  return ss.str();
}

std::string
to_string(Ofp_version v)
{
  switch(v) {
    case v10: return "1.0";
    case v11: return "1.1";
    case v12: return "1.2";
    case v13: return "1.3";
    default: return "Unknown";
  }
}

std::string
to_string(const Ofp& o) 
{
  std::stringstream ss;
  switch(o.type) {
    case Ofp::Version:
      ss << "OPF Version " << to_string(Ofp_version(o.value));
      break;
    case Ofp::Echo_interval:
      ss << "Echo Interval " << to_string(o.time);
      break;
    case Ofp::Echo_timeout:
      ss << "Echo Timeout " << to_string(o.time);
      break;
    case Ofp::Echo_miss:
      ss << "Echo Miss " << o.value;
      break;
    default:
      ss << "Uknown Ofp attribute";
      break;
  }
  return ss.str();
}

std::string
to_string(const Server& s)
{
  return to_string(s.local);
}

std::string
to_string(const Client& c)
{
  std::stringstream ss;
  ss << to_string(c.local) << " -> ";
  ss << to_string(c.remote);
  return ss.str();
}

std::string
to_string(Command::Action a)
{
  switch(a) {
    case Command::Add: return "Add";
    case Command::Del: return "Del";
    case Command::Set: return "Set";
    case Command::Stop: return "Stop";
    case Command::NoOp: return "NoOp";
    default: return "Uknown";
  }
}

std::string
to_string(Command::Name n)
{
  switch(n) {
    case Command::REMOTE: return "Remote";
    case Command::LOCAL: return "Local";
    case Command::APP: return "App";
    case Command::X509: return "x509";
    case Command::ACL: return "Acl";
    case Command::OFP: return "Ofp";
    case Command::SERVER: return "Server";
    case Command::CLIENT: return "Client";
    default: return "Unknown";
  }
}

std::string
to_string(const Command& c)
{
  std::stringstream ss;
  ss << to_string(c.action);

  switch(c.name) {
    case Command::REMOTE:
    case Command::LOCAL:
      ss << " " << to_string(c.name) << " ";
      ss << c.target;
      break;
    case Command::APP:
    case Command::X509: 
      ss << " " << to_string(c.name) << " ";
      ss << c.payload.filename << " ";
      ss << c.target;
      break;
    case Command::ACL: 
      ss << " " << to_string(c.name) << " ";
      ss << to_string(c.payload.acl) << " ";
      ss << c.target;
      break;
    case Command::OFP: 
      ss << " " << to_string(c.name) << " ";
      ss << to_string(c.payload.ofp) << " ";
      ss << c.target;
      break;
    case Command::SERVER: 
      ss << " " << to_string(c.name) << " ";
      ss << to_string(c.payload.server) << " ";
      ss << c.target;
      break;
    case Command::CLIENT: 
      ss << " " << to_string(c.name) << " ";
      ss << to_string(c.payload.client) << " ";
      ss << c.target;
      break;
    default:
      break;
  }

  return ss.str();
}

} // namespace config
} // namespace flog
