# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pjawahar/flecs-rpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pjawahar/flecs-rpc/build

# Utility rule file for gen_rpc_interface.

interface/CMakeFiles/gen_rpc_interface: interface/flecs.h
interface/CMakeFiles/gen_rpc_interface: interface/flecs.cpp

interface/flecs.h: ../interface/flecs.ice
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pjawahar/flecs-rpc/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating flecs.h, flecs.cpp"
	cd /home/pjawahar/flecs-rpc/build/interface && slice2cpp /home/pjawahar/flecs-rpc/interface/flecs.ice

interface/flecs.cpp: interface/flecs.h

gen_rpc_interface: interface/CMakeFiles/gen_rpc_interface
gen_rpc_interface: interface/flecs.h
gen_rpc_interface: interface/flecs.cpp
gen_rpc_interface: interface/CMakeFiles/gen_rpc_interface.dir/build.make
.PHONY : gen_rpc_interface

# Rule to build all files generated by this target.
interface/CMakeFiles/gen_rpc_interface.dir/build: gen_rpc_interface
.PHONY : interface/CMakeFiles/gen_rpc_interface.dir/build

interface/CMakeFiles/gen_rpc_interface.dir/clean:
	cd /home/pjawahar/flecs-rpc/build/interface && $(CMAKE_COMMAND) -P CMakeFiles/gen_rpc_interface.dir/cmake_clean.cmake
.PHONY : interface/CMakeFiles/gen_rpc_interface.dir/clean

interface/CMakeFiles/gen_rpc_interface.dir/depend:
	cd /home/pjawahar/flecs-rpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pjawahar/flecs-rpc /home/pjawahar/flecs-rpc/interface /home/pjawahar/flecs-rpc/build /home/pjawahar/flecs-rpc/build/interface /home/pjawahar/flecs-rpc/build/interface/CMakeFiles/gen_rpc_interface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : interface/CMakeFiles/gen_rpc_interface.dir/depend

