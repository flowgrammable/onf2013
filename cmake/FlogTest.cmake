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

enable_testing()

# Allow the use of valgrind for unit tests, and control its usage
# through the FLOG_USE_VALGRIND option.
find_program(VALGRIND_EXECUTABLE valgrind)

if(NOT VALGRIND_EXECUTABLE)
  message(STATUS "Valgrind not found: Disabling valgrind tests")
  set(FLOG_ENABLE_VALGRIND OFF CACHE BOOL "Enable testing with valgrind" FORCE)
endif()


# The following tools are built during compilation and then used
# to execute unit tests.
set(FLOG_OFP_TEST_EXECUTABLE ${CMAKE_BINARY_DIR}/tools/ofp_test/ofp_test)
set(FLOG_OFP_ABS_EXECUTABLE ${CMAKE_BINARY_DIR}/tools/ofp_test/ofp_abs)


# Build a test target for cross-compiled binaries that executes with
# a specified emulator or launcher. The target is the name of the build
# target, and the command is taken as the remaining arguments.
macro(add_cross_test target)
  add_test(test_${target} ${CTEST_EXE_PREFIX} ${ARGN})
endmacro()

# Build a test target for the host environment. If Valgrind testing
# is enabled, also build a test target for the memcheck version
# of that test. The target is the name of the build target, and the command is 
# taken as the remaining arguments.
macro(add_host_test target)
  add_test(test_${target} ${ARGN})
  if (FLOG_ENABLE_VALGRIND)
    add_test(memtest_${target} ${VALGRIND_EXECUTABLE} ${ARGN})
  endif()
endmacro()

# Add a unit test.
macro(add_unit_test target)
  if (CTEST_EXE_PREFIX)
    add_cross_test(${target} ${ARGN})
  else()
    add_host_test(${target} ${ARGN})
  endif()
endmacro()

# A macro that simplifies the registration of unit tests to be 
# compiled and run.
#
#    target -- the name of the Makefile target
#    file   -- the name of the source file
#
macro(add_run_test target file)
  add_executable(${target} ${file})
  add_unit_test(${target} ${target})
endmacro()

# Like add_unit_test but expects failure and does not register a
# memcheck test.
macro(add_fail_test target)
  if (CTEST_EXE_PREFIX)
    add_test(test_${target} ${CTEST_EXE_PREFIX} ${ARGN})
  else()
    add_test(test_${target} ${ARGN})
  endif()
  set_tests_properties(test_${target} PROPERTIES WILL_FAIL TRUE)
endmacro()

# Decode various parts of a file name. This exports
#   name -- the name of the test
#   ext --  the extension of the file
#   version -- the protocol versoin
macro(decode_filename file)
  get_filename_component(name ${in} NAME_WE)
  get_filename_component(ext ${in} EXT)
  string(SUBSTRING ${ext} 1 -1 ext)
  string(REGEX MATCH "v[0-9](_[0-9])+" version ${in})
endmacro()

# Add a set of unit tests from the given list of arguments. The value of 
# pass must be either PASS or FAIL indicating the expected result of the
# test. If FLOG_ENABLE_VALGRIND is on, then we create VALGRIND test
# for each PASS and FAIL test.
macro(add_rep_tests pass)
  foreach(in ${ARGN})
    decode_filename(${in})
    string(REPLACE "_" "." ver ${version})
    string(SUBSTRING ${ver} 1 -1 ver)
    set(out ${CMAKE_CURRENT_BINARY_DIR}/${name}.${ext}.out)
    
    if (${pass} STREQUAL PASS)
      # Build the exec test
      set(rep_test ${version}_rep_${name}_pass)
      add_unit_test(${rep_test} ${FLOG_OFP_TEST_EXECUTABLE} ${in} ${out} ${ver})
      
      # Build the diff test
      set(diff_test ${version}_rep_${name}_diff)
      add_test(NAME ${diff_test} COMMAND diff ${in} ${out})
    elseif(${pass} STREQUAL FAIL)
      # build the fail test
      set(fail_test ${version}_${name}_fail)
      add_fail_test(${fail_test} ${FLOG_OFP_TEST_EXECUTABLE} ${in} ${out} ${ver})
    else()
      message(SEND_ERROR "Test is neither PASS nor FAIL")
    endif()
  endforeach()
endmacro()

# Add a set of unit tests from the given list of arguments. The value of 
# pass must be either PASS or FAIL indicating the expected result of the
# test. If FLOG_ENABLE_VALGRIND is on, then we create VALGRIND test
# for each PASS and FAIL test.
macro(add_abs_tests pass)
  foreach(in ${ARGN})
    decode_filename(${in})
    set(out ${CMAKE_CURRENT_BINARY_DIR}/${name}.${ext}.out)

    if (${pass} STREQUAL PASS)
      set(abs_test ${version}_abs_${name}_pass)
      add_unit_test(${abs_test} ${FLOG_OFP_ABS_EXECUTABLE} ${in} ${out})      
    elseif(${pass} STREQUAL FAIL)
      set(fail_test ${version}_${name}_fail)
      add_fail_test(${fail_test} ${FLOG_OFP_ABS_EXECUTABLE} ${in} ${out})
    else()
      message(SEND_ERROR "Test is neither PASS nor FAIL")
    endif()
  endforeach()
endmacro()

# Add a set of abs files to be tested with the ofp testing tool.
if(FLOG_BUILD_PYTHON_BINDINGS)
  set(FLOG_PY_EXECUTABLE ${CMAKE_BINARY_DIR}/tools/ofp_test/ofp_test.sh)

  macro(add_py_test pass)
    foreach(in ${ARGN})
      decode_filename(${in})
      set(out ${CMAKE_CURRENT_BINARY_DIR}/py_${name}.${ext}.out)

      if (${pass} STREQUAL PASS)
        set(py_test py_${version}_${name}_pass)
        add_test(${py_test} ${FLOG_PY_EXECUTABLE} ${in} ${out})      
      elseif(${pass} STREQUAL FAIL)
        set(py_test py_${version}_${name}_fail)
        add_test(${py_test} ${FLOG_PY_EXECUTABLE} ${in} ${out})
        set_tests_properties(${py_test} PROPERTIES WILL_FAIL TRUE)
      else()
        message(SEND_ERROR "Test is neither PASS nor FAIL")
      endif()
    endforeach()
  endmacro()
endif()