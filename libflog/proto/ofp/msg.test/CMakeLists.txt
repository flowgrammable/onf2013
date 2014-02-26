

# Add a simple unit test.
add_run_test(msg_message message.cpp)

# Build the msg_test program, which will be used to evaluate
# data files in the test directory. Note that this is not, itself
# a unit test.
add_executable(msg_rep_test representation_layer.cpp)
target_link_libraries(msg_rep_test openflow)

add_executable(msg_rep_fb rep_from_buffer.cpp)
target_link_libraries(msg_rep_fb openflow)

add_executable(msg_abs_test abstraction_layer.cpp)
target_link_libraries(msg_abs_test openflow)

add_executable(msg_custom custom.cpp)
target_link_libraries(msg_custom openflow)

add_executable(msg_to_string to_string.cpp)
target_link_libraries(msg_to_string openflow)

# For each data/*.pass file, create a test target that
# executes the msg_test tool.
file(GLOB_RECURSE pass data/*.pass)
foreach(file ${pass})
  # Extract the name of the file to generate a unique
  # test target name.
  get_filename_component(name ${file} NAME_WE)

  # Generate an output path for the file.
  set(out ${CMAKE_CURRENT_BINARY_DIR}/name.out)

  # Set test names.
  set(rep_test test_rep_${name}_pass)
  set(diff_test test_rep_${name}_diff)
  set(abs_test test_abs_${name}_fail)

  # Create unit tests
  add_test(${rep_test} msg_rep_test ${file} ${out})
  add_test(${abs_test} msg_abs_test ${file})
  add_test(NAME ${diff_test} COMMAND diff ${file} ${out})
endforeach()

# For each data/*.fail file, create a test target that
# executes the msg_test tool.
file(GLOB_RECURSE fail data/rep*.fail)
foreach(file ${fail})
  get_filename_component(name ${file} NAME_WE)
  set(out ${CMAKE_CURRENT_BINARY_DIR}/name.out)
  set(test test_${name}_fail)

  # Add a representation test for the *.fail.
  # We expect each of these to fail.
  add_test(${test} msg_rep_test ${file} ${out})
  set_tests_properties(${test} PROPERTIES WILL_FAIL TRUE)
endforeach()

