# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/faculty/asutton/Code/onf/onfc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/faculty/asutton/Code/onf/onfc/build

# Include any dependencies generated for this target.
include applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/depend.make

# Include the progress variables for this target.
include applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/progress.make

# Include the compile flags for this target's objects.
include applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/flags.make

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o: applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/flags.make
applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o: ../applications/learning_bridge/v1_0/bridge.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/faculty/asutton/Code/onf/onfc/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o"
	cd /home/faculty/asutton/Code/onf/onfc/build/applications/learning_bridge && /usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o -c /home/faculty/asutton/Code/onf/onfc/applications/learning_bridge/v1_0/bridge.cpp

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.i"
	cd /home/faculty/asutton/Code/onf/onfc/build/applications/learning_bridge && /usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/faculty/asutton/Code/onf/onfc/applications/learning_bridge/v1_0/bridge.cpp > CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.i

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.s"
	cd /home/faculty/asutton/Code/onf/onfc/build/applications/learning_bridge && /usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/faculty/asutton/Code/onf/onfc/applications/learning_bridge/v1_0/bridge.cpp -o CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.s

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.requires:
.PHONY : applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.requires

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.provides: applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.requires
	$(MAKE) -f applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/build.make applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.provides.build
.PHONY : applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.provides

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.provides.build: applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o

# Object files for target bridge_v1_0
bridge_v1_0_OBJECTS = \
"CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o"

# External object files for target bridge_v1_0
bridge_v1_0_EXTERNAL_OBJECTS =

applications/learning_bridge/libbridge_v1_0.so: applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o
applications/learning_bridge/libbridge_v1_0.so: /usr/lib/i386-linux-gnu/libssl.so
applications/learning_bridge/libbridge_v1_0.so: /usr/lib/i386-linux-gnu/libcrypto.so
applications/learning_bridge/libbridge_v1_0.so: libflog/libflog.a
applications/learning_bridge/libbridge_v1_0.so: applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/build.make
applications/learning_bridge/libbridge_v1_0.so: applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libbridge_v1_0.so"
	cd /home/faculty/asutton/Code/onf/onfc/build/applications/learning_bridge && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bridge_v1_0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/build: applications/learning_bridge/libbridge_v1_0.so
.PHONY : applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/build

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/requires: applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/v1_0/bridge.cpp.o.requires
.PHONY : applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/requires

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/clean:
	cd /home/faculty/asutton/Code/onf/onfc/build/applications/learning_bridge && $(CMAKE_COMMAND) -P CMakeFiles/bridge_v1_0.dir/cmake_clean.cmake
.PHONY : applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/clean

applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/depend:
	cd /home/faculty/asutton/Code/onf/onfc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/faculty/asutton/Code/onf/onfc /home/faculty/asutton/Code/onf/onfc/applications/learning_bridge /home/faculty/asutton/Code/onf/onfc/build /home/faculty/asutton/Code/onf/onfc/build/applications/learning_bridge /home/faculty/asutton/Code/onf/onfc/build/applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : applications/learning_bridge/CMakeFiles/bridge_v1_0.dir/depend

