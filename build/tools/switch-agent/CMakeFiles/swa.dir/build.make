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
include tools/switch-agent/CMakeFiles/swa.dir/depend.make

# Include the progress variables for this target.
include tools/switch-agent/CMakeFiles/swa.dir/progress.make

# Include the compile flags for this target's objects.
include tools/switch-agent/CMakeFiles/swa.dir/flags.make

tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o: tools/switch-agent/CMakeFiles/swa.dir/flags.make
tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o: ../tools/switch-agent/driver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/faculty/asutton/Code/onf/onfc/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/switch-agent && /usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/swa.dir/driver.cpp.o -c /home/faculty/asutton/Code/onf/onfc/tools/switch-agent/driver.cpp

tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/swa.dir/driver.cpp.i"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/switch-agent && /usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/faculty/asutton/Code/onf/onfc/tools/switch-agent/driver.cpp > CMakeFiles/swa.dir/driver.cpp.i

tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/swa.dir/driver.cpp.s"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/switch-agent && /usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/faculty/asutton/Code/onf/onfc/tools/switch-agent/driver.cpp -o CMakeFiles/swa.dir/driver.cpp.s

tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.requires:
.PHONY : tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.requires

tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.provides: tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.requires
	$(MAKE) -f tools/switch-agent/CMakeFiles/swa.dir/build.make tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.provides.build
.PHONY : tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.provides

tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.provides.build: tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o

# Object files for target swa
swa_OBJECTS = \
"CMakeFiles/swa.dir/driver.cpp.o"

# External object files for target swa
swa_EXTERNAL_OBJECTS =

tools/switch-agent/swa: tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o
tools/switch-agent/swa: /usr/lib/i386-linux-gnu/libssl.so
tools/switch-agent/swa: /usr/lib/i386-linux-gnu/libcrypto.so
tools/switch-agent/swa: libflog/libflog.a
tools/switch-agent/swa: tools/switch-agent/CMakeFiles/swa.dir/build.make
tools/switch-agent/swa: tools/switch-agent/CMakeFiles/swa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable swa"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/switch-agent && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/swa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/switch-agent/CMakeFiles/swa.dir/build: tools/switch-agent/swa
.PHONY : tools/switch-agent/CMakeFiles/swa.dir/build

tools/switch-agent/CMakeFiles/swa.dir/requires: tools/switch-agent/CMakeFiles/swa.dir/driver.cpp.o.requires
.PHONY : tools/switch-agent/CMakeFiles/swa.dir/requires

tools/switch-agent/CMakeFiles/swa.dir/clean:
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/switch-agent && $(CMAKE_COMMAND) -P CMakeFiles/swa.dir/cmake_clean.cmake
.PHONY : tools/switch-agent/CMakeFiles/swa.dir/clean

tools/switch-agent/CMakeFiles/swa.dir/depend:
	cd /home/faculty/asutton/Code/onf/onfc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/faculty/asutton/Code/onf/onfc /home/faculty/asutton/Code/onf/onfc/tools/switch-agent /home/faculty/asutton/Code/onf/onfc/build /home/faculty/asutton/Code/onf/onfc/build/tools/switch-agent /home/faculty/asutton/Code/onf/onfc/build/tools/switch-agent/CMakeFiles/swa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/switch-agent/CMakeFiles/swa.dir/depend

