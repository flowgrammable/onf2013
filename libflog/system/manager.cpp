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

#include "manager.hpp"
#include "acceptor.hpp"
#include "connection.hpp"

namespace flog {

const std::string Manager::module_name = "Manager";

void
add_remote(Manager& m, const std::string& s)
{
  slog<Manager>(m, Log::Info, ("add remote " + s));
}

void
add_local(Manager& m, const std::string& s)
{
  slog<Manager>(m, Log::Info, ("add local " + s));
}

void
add_app(Manager& m, const std::string& n, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("add app " + n + " -> " + t));
}

void
add_x509(Manager& m, const std::string& n, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("add x509 " + n + " -> " + t));
}

void
add_acl(Manager& m, const config::Acl& a, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("add acl " + to_string(a) + " -> " + t));
}

void
add_server(Manager& m, const config::Server& s, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("add server " + to_string(s) + " -> " + t));
  subscribe_read(m.reactor, new Acceptor(m.reactor, s.local));
}
  
void
add_client(Manager& m, const config::Client& c, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("add client " + to_string(c) + " -> " + t));
  Connection *conn = new Connection(m.reactor, c.remote, c.local);

  subscribe_read(m.reactor, conn);
  subscribe_write(m.reactor, conn);
}

void
del_remote(Manager& m, const std::string& s)
{
  slog<Manager>(m, Log::Info, ("del remote " + s));
}

void
del_local(Manager& m, const std::string& s)
{
  slog<Manager>(m, Log::Info, ("del local " + s));
}

void
del_app(Manager& m, const std::string& n, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("del app " + n + " -> " + t));
}

void
del_x509(Manager& m, const std::string& n, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("del x509 " + n + " -> " + t));
}

void
del_acl(Manager& m, const config::Acl& a, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("del acl " + to_string(a) + " -> " + t));
}

void
del_server(Manager& m, const config::Server& s, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("del server " + to_string(s) + " -> " + t));
  if(Subscriber* acceptor = find_reader(m.reactor, s.local)) {
    unsubscribe_read(m.reactor, acceptor);
    slog<Manager>(m, Log::Info, ("Deleted: " + to_string(s)));
    delete acceptor;
  } else {
    slog<Manager>(m, Log::Info, ("Delete failed: " + to_string(s)));
  }
  // del a listener
}
  
void
del_client(Manager& m, const config::Client& c, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("del client " + to_string(c) + " -> " + t));
  // del a client
}

void
set_ofp_version(Manager& m, unsigned int v, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("set ofp version " + to_string(config::Ofp_version(v)) + " -> " + t));
}
void
set_ofp_echo_interval(Manager& m, const Time& tm, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("set ofp echo interval " + to_string(tm) + " -> " + t));
}
void
set_ofp_echo_timeout(Manager& m, const Time& tm, const std::string& t)
{
  slog<Manager>(m, Log::Info, ("set ofp echo timeout " + to_string(tm) + " -> " + t));
}
void
set_ofp_echo_miss(Manager& m, unsigned int v, const std::string& t)
{
  //slog<Manager>(m, Log::Info, ("set ofp echo miss" + v + " -> " + t));
}

void 
add(Manager& m, const config::Command& cmd)
{
  switch(cmd.name) {
    case config::Command::REMOTE:
      add_remote(m, std::string(cmd.target));
      break;
    case config::Command::LOCAL:
      add_local(m, std::string(cmd.target));
      break;
    case config::Command::APP:
      add_app(m, std::string(cmd.get_filename()), std::string(cmd.target));
      break;
    case config::Command::X509:
      add_x509(m, std::string(cmd.get_filename()), std::string(cmd.target));
      break;
    case config::Command::ACL:
      add_acl(m, cmd.get_acl(), std::string(cmd.target));
      break;
    case config::Command::SERVER:
      add_server(m, cmd.get_server(), std::string(cmd.target));
      break;
    case config::Command::CLIENT:
      add_client(m, cmd.get_client(), std::string(cmd.target));
      break;
    default:
      slog<Manager>(m, Log::Warning, "unknown name");
      break;
  }
}

void 
del(Manager& m, const config::Command& cmd)
{
  switch(cmd.name) {
    case config::Command::REMOTE:
      add_remote(m, std::string(cmd.target));
      break;
    case config::Command::LOCAL:
      add_local(m, std::string(cmd.target));
      break;
    case config::Command::APP:
      add_app(m, std::string(cmd.get_filename()), std::string(cmd.target));
      break;
    case config::Command::X509:
      add_x509(m, std::string(cmd.get_filename()), std::string(cmd.target));
      break;
    case config::Command::ACL:
      add_acl(m, cmd.get_acl(), std::string(cmd.target));
      break;
    case config::Command::SERVER:
      add_server(m, cmd.get_server(), std::string(cmd.target));
      break;
    case config::Command::CLIENT:
      add_client(m, cmd.get_client(), std::string(cmd.target));
      break;
    default:
      slog<Manager>(m, Log::Warning, "unknown name");
      break;
  }
}

void 
set(Manager& m, const config::Command& cmd)
{
  if(cmd.name == config::Command::OFP) {
    switch(cmd.get_ofp().type) {
      case config::Ofp::Version:
        set_ofp_version(m, cmd.get_ofp().value, std::string(cmd.target));
        break;
      case config::Ofp::Echo_interval:
        set_ofp_echo_interval(m, cmd.get_ofp().time, std::string(cmd.target));
        break;
      case config::Ofp::Echo_timeout:
        set_ofp_echo_timeout(m, cmd.get_ofp().time, std::string(cmd.target));
        break;
      case config::Ofp::Echo_miss:
        set_ofp_echo_miss(m, cmd.get_ofp().value, std::string(cmd.target));
        break;
      default:
        slog<Manager>(m, Log::Warning, "unknown name");
        break;
    }
  }
}

void
stop(Manager& m)
{
  slog<Manager>(m, Log::Info, "stopping");
  stop(m.reactor);
}

void
Manager::read(const Time& ct)
{
  config::Command cmd;
  auto result = config::read(channel, cmd);
  slog<Manager>(*this, Log::Info, "read event");

  if(result < 0) {
    slog<Manager>(*this, Log::Error, strerror(errno));
  } else if(result == 0) {
    slog<Manager>(*this, Log::Info, "writer closed");
  } else if(result != sizeof(config::Command)) {
    std::stringstream ss;
    ss << "malformed command, bytes rx: " << result << ", ";
    ss << "expected: " << sizeof(config::Command);
    slog<Manager>(*this, Log::Error, ss.str());
  } else {
    switch(cmd.action) {
      case config::Command::Add:
        add(*this, cmd);
        break;
      case config::Command::Del:
        del(*this, cmd);
        break;
      case config::Command::Set:
        set(*this, cmd);
        break;
      case config::Command::Stop:
        stop(*this);
        break;
      default:
        slog<Manager>(*this, Log::Warning, "unknown action");
        break;
    }
  }

}

} // namespace flog
