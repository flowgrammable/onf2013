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

# Binding dependencies
find_package(SWIG 2.0)

# Check that we have the right SWIG version.
if(SWIG_FOUND)
  include(${SWIG_USE_FILE})
else()
  message(STATUS "SWIG not found: Disabling language bindings")
  set(FLOG_BUILD_BINDINGS OFF CACHE BOOL "Build language bindings" FORCE)
endif()

# If we're actually building bindings, then optionally search for
# the languages that are supported on the host system.
if(FLOG_BUILD_BINDINGS)
  
  # Check Python support.
  find_package(PythonLibs)
  if(PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_PATH})
    set(FLOG_BUILD_PYTHON_BINDINGS TRUE)
  else()
    message(STATUS "Python library not found: Disabling Python bindings")
    set(FLOG_BUILD_PYTHON_BINDINGS FALSE)
  endif()

  # Check for Ruby support
  find_package(Ruby)
  if(RUBY_FOUND)
    include_directories(${RUBY_INCLUDE_PATH})
    set(FLOG_BUILD_RUBY_BINDINGS TRUE)
  else()
    message(STATUS "Ruby library not found: Disabling Ruby bindings")
    set(FLOG_BUILD_RUBY_BINDINGS TRUE)
  endif()

  # Check for JNI support.
  find_package(JNI)
  if(JNI_FOUND)
    include_directories(${JAVA_INCLUDE_PATH})
    set(FLOG_BUILD_JAVA_BINDINGS TRUE)
  else()
    message(STATUS "JNI libray not found: Disabling Java bindings")
    set(FLOG_BUILD_JAVA_BINDINGS FALSE)
  endif()
endif()


# Python-specific build tools.
if (FLOG_BUILD_PYTHON_BINDINGS)
  # Add a Python module to the build with the given name.
  macro(add_python_module iface)
    get_filename_component(name ${iface} NAME_WE)

    # Configure properties for the iface file.
    set_source_files_properties(
      ${iface} 
      PROPERTIES CPLUSPLUS ON 
                 SWIG_FLAGS "-includeall")
    
    swig_add_module(${name} python ${iface})

    # Disable all warnings when compiling generated code.
    set_source_files_properties(
      ${swig_generated_file_fullname}
      PROPERTIES COMPILE_FLAGS "-w")

    swig_link_libraries(${name} ${PYTHON_LIBRARIES} ${FLOG_LIBRARIES})
  endmacro()
endif()

