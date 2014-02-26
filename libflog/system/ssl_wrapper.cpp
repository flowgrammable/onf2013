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
#include "ssl_wrapper.hpp"

namespace flog {
namespace socket {

bool OpenSSL::init = false;

SSL_ctx::SSL_ctx(Type t, const std::string& cert, const std::string& key)
  : Error_base(), method(nullptr), ctx(nullptr), ssl(nullptr), 
    peer_cert(nullptr)
{
  if (type == Client)
    method = SSLv23_client_method();
  else
    method = SSLv23_server_method();
  if (not method) {
    status = false;
    error = "SSLv23_server_method failed";
    return;
  } 

  ctx = SSL_CTX_new(method);
  if (not ctx) {
    status = false;
    error = "SSL_CTX_new failed";
  } else if (SSL_CTX_use_certificate_file(ctx, cert.c_str(), 
                                          SSL_FILETYPE_PEM) < 1) {
    status = false;
    error = "";
  } else if (SSL_CTX_use_PrivateKey_file(ctx, key.c_str(), 
                                         SSL_FILETYPE_PEM) < 1 ) {
    status = false;
    error = "";
  } else if (not SSL_CTX_check_private_key(ctx)) {
    status = false;
    error = "";
  }
  ssl = SSL_new(ctx);
  if (not ssl) {
    status = false;
    error = "SSL_new failed";
  }
}

SSL_ctx::~SSL_ctx()
{
  if(peer_cert) 
    X509_free(peer_cert);
  if(ssl) 
    SSL_free(ssl);
  if(ctx)
    SSL_CTX_free(ctx);
  if(method)
    ;
}

} // namespace socket
} // namespace flog
