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

#ifndef FLOWGRAMMABLE_SSL_WRAPPER_H
#define FLOWGRAMMABLE_SSL_WRAPPER_H

extern "C" {
#include <openssl/rsa.h>       
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
}

namespace flog {
namespace socket {

struct Error_base {
  Error_base()
    : status(true)
  { }

  operator bool() const { return status; }

  bool status;
  std::string error;
};

struct OpenSSL {
  static bool init;
  static void initialize();
};

struct SSL_ctx : Error_base {
  enum Type { Client, Server };

  SSL_ctx(Type t, const std::string& cert, const std::string& key);
  ~SSL_ctx();

  Type type;
  const SSL_METHOD *method;
  SSL_CTX* ctx;
  SSL* ssl;
  X509* peer_cert;
};

inline void
OpenSSL::initialize()
{
  if(not init) {
    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();
    init = true;
  }
}

} // namespace socket
} // namespace flog

#endif
