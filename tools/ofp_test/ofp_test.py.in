#!/usr/bin/env python2.7

# Copyright (c) 2013 Flowgrammable, LLC.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an "AS IS"
# BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
# or implied. See the License for the specific language governing
# permissions and limitations under the License.

import sys
import flog

def get_ofp_version(ver):
  """Returns the OFP module that implements the given version."""
  if ver == 1:
    import flog_ofp_v1_0
    return flog_ofp_v1_0
  elif ver == 2:
    import flog_ofp_v1_1
    return flog_ofp_v1_1
  else:
    raise "Unsupported protocol version"

# Read a message from the buffer
b = flog.buffer_from_file(sys.argv[1])
ofp = get_ofp_version(b[0])

v = ofp.Buffer_view(b)
m = ofp.Message()

# Try reading the message
err = ofp.from_buffer(v, m)
if not err:
  print "Could not read the message from the buffer"
  sys.exit(err.code)

# Try validating the messaage
err = ofp.is_valid(m)
if not err:
  print "Could not validate the mesasge"
  sys.exit(err.code)

# Rewrite the message into new buffer
b = flog.Buffer(ofp.bytes(m))
v = ofp.Buffer_view(b)
err = ofp.to_buffer(v, m)
if not err:
  "Could not write the messatge to the buffer"
  sys.exit(err.code)

# Write the buffer back out.
ofp.buffer_to_file(sys.argv[2], b)
