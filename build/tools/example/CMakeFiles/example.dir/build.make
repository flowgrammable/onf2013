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
include tools/example/CMakeFiles/example.dir/depend.make

# Include the progress variables for this target.
include tools/example/CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include tools/example/CMakeFiles/example.dir/flags.make

tools/example/CMakeFiles/example.dir/example.cpp.o: tools/example/CMakeFiles/example.dir/flags.make
tools/example/CMakeFiles/example.dir/example.cpp.o: ../tools/example/example.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/faculty/asutton/Code/onf/onfc/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tools/example/CMakeFiles/example.dir/example.cpp.o"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/example && /usr/bin/g++-4.8   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/example.dir/example.cpp.o -c /home/faculty/asutton/Code/onf/onfc/tools/example/example.cpp

tools/example/CMakeFiles/example.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/example.cpp.i"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/example && /usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/faculty/asutton/Code/onf/onfc/tools/example/example.cpp > CMakeFiles/example.dir/example.cpp.i

tools/example/CMakeFiles/example.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/example.cpp.s"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/example && /usr/bin/g++-4.8  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/faculty/asutton/Code/onf/onfc/tools/example/example.cpp -o CMakeFiles/example.dir/example.cpp.s

tools/example/CMakeFiles/example.dir/example.cpp.o.requires:
.PHONY : tools/example/CMakeFiles/example.dir/example.cpp.o.requires

tools/example/CMakeFiles/example.dir/example.cpp.o.provides: tools/example/CMakeFiles/example.dir/example.cpp.o.requires
	$(MAKE) -f tools/example/CMakeFiles/example.dir/build.make tools/example/CMakeFiles/example.dir/example.cpp.o.provides.build
.PHONY : tools/example/CMakeFiles/example.dir/example.cpp.o.provides

tools/example/CMakeFiles/example.dir/example.cpp.o.provides.build: tools/example/CMakeFiles/example.dir/example.cpp.o

# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/example.cpp.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

tools/example/example: tools/example/CMakeFiles/example.dir/example.cpp.o
tools/example/example: /usr/lib/i386-linux-gnu/libssl.so
tools/example/example: /usr/lib/i386-linux-gnu/libcrypto.so
tools/example/example: libflog/libflog.a
tools/example/example: tools/example/CMakeFiles/example.dir/build.make
tools/example/example: tools/example/CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable example"
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/example/CMakeFiles/example.dir/build: tools/example/example
.PHONY : tools/example/CMakeFiles/example.dir/build

tools/example/CMakeFiles/example.dir/requires: tools/example/CMakeFiles/example.dir/example.cpp.o.requires
.PHONY : tools/example/CMakeFiles/example.dir/requires

tools/example/CMakeFiles/example.dir/clean:
	cd /home/faculty/asutton/Code/onf/onfc/build/tools/example && $(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : tools/example/CMakeFiles/example.dir/clean

tools/example/CMakeFiles/example.dir/depend:
	cd /home/faculty/asutton/Code/onf/onfc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/faculty/asutton/Code/onf/onfc /home/faculty/asutton/Code/onf/onfc/tools/example /home/faculty/asutton/Code/onf/onfc/build /home/faculty/asutton/Code/onf/onfc/build/tools/example /home/faculty/asutton/Code/onf/onfc/build/tools/example/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/example/CMakeFiles/example.dir/depend
