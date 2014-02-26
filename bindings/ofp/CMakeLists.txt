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

# TODO: Can we actually make this a single-source multi-language
# binding implementation? Note that we're going to end up with
# a lot of language customization stuff inside the .i files.
# Also, the targets are going to need separate names.

if (FLOG_BUILD_PYTHON_BINDINGS)
  # Configure extra dependencies for these modules.
  set(SWIG_MODULE_flog_ofp_v1_0_EXTRA_DEPS flog.i flog_ofp.i)
  set(SWIG_MODULE_flog_ofp_v1_1_EXTRA_DEPS flog.i flog_ofp.i)

  add_python_module(flog.i)
  add_python_module(flog_ofp_v1_0.i)
  add_python_module(flog_ofp_v1_1.i)
endif()

# Build Ruby bindings 
# swig_add_module(v1_0_ruby ruby v1_0.i)
# swig_link_libraries(v1_0_ruby ${RUBY_LIBRARY} openflow)

# Build Java bindings
# swig_add_module(v1_0_java java v1_0.i)
# swig_link_libraries(v1_0_java ${JNI_LIBRARIES} openflow)
