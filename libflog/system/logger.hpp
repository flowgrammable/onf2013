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

#ifndef FLOWGRAMMABLE_LOGGER_H
#define FLOWGRAMMABLE_LOGGER_H

#include <fstream>

#include "time.hpp"

namespace flog {

struct Log
{
  enum Level { Info, Warning, Error };

  Log(const Time& t, Level l, const std::string& md, const std::string& ms);

  Time time;
  Level level;
  std::string module;
  std::string msg;
};

std::string to_string(Log::Level ll);

struct Logger
{
  Logger(const std::string& f);
  std::string filename;
  std::fstream output;
};

void log(Logger& lr, const Log& lg);

inline
Log::Log(const Time& t, Level l, const std::string& md, const std::string& ms)
  : time(t), level(l), module(md), msg(ms)
{ }

inline
Logger::Logger(const std::string& f)
  : filename(f), output(filename, std::ios::out)
{ }

inline void
log(Logger& lr, const Log& lg)
{
  lr.output << to_string(lg.time);
  lr.output << " " << to_string(lg.level);
  lr.output << " " << lg.module;
  lr.output << " " << lg.msg;
  lr.output << "\n";
}

template<typename T>
  void
  slog(T& t, Log::Level ll, const std::string& msg)
  {
    log(t.reactor.logger, Log(t.current_time, ll, t.module_name, msg));
  }

} // namespace flog

#endif
