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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test

# Include any dependencies generated for this target.
include CMakeFiles/test_shapes.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_shapes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_shapes.dir/flags.make

CMakeFiles/test_shapes.dir/test_shapes.c.o: CMakeFiles/test_shapes.dir/flags.make
CMakeFiles/test_shapes.dir/test_shapes.c.o: test_shapes.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_shapes.dir/test_shapes.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_shapes.dir/test_shapes.c.o   -c /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/test_shapes.c

CMakeFiles/test_shapes.dir/test_shapes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_shapes.dir/test_shapes.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/test_shapes.c > CMakeFiles/test_shapes.dir/test_shapes.c.i

CMakeFiles/test_shapes.dir/test_shapes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_shapes.dir/test_shapes.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/test_shapes.c -o CMakeFiles/test_shapes.dir/test_shapes.c.s

CMakeFiles/test_shapes.dir/test_shapes.c.o.requires:
.PHONY : CMakeFiles/test_shapes.dir/test_shapes.c.o.requires

CMakeFiles/test_shapes.dir/test_shapes.c.o.provides: CMakeFiles/test_shapes.dir/test_shapes.c.o.requires
	$(MAKE) -f CMakeFiles/test_shapes.dir/build.make CMakeFiles/test_shapes.dir/test_shapes.c.o.provides.build
.PHONY : CMakeFiles/test_shapes.dir/test_shapes.c.o.provides

CMakeFiles/test_shapes.dir/test_shapes.c.o.provides.build: CMakeFiles/test_shapes.dir/test_shapes.c.o

CMakeFiles/test_shapes.dir/console-colors.c.o: CMakeFiles/test_shapes.dir/flags.make
CMakeFiles/test_shapes.dir/console-colors.c.o: console-colors.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_shapes.dir/console-colors.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_shapes.dir/console-colors.c.o   -c /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/console-colors.c

CMakeFiles/test_shapes.dir/console-colors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_shapes.dir/console-colors.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/console-colors.c > CMakeFiles/test_shapes.dir/console-colors.c.i

CMakeFiles/test_shapes.dir/console-colors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_shapes.dir/console-colors.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/console-colors.c -o CMakeFiles/test_shapes.dir/console-colors.c.s

CMakeFiles/test_shapes.dir/console-colors.c.o.requires:
.PHONY : CMakeFiles/test_shapes.dir/console-colors.c.o.requires

CMakeFiles/test_shapes.dir/console-colors.c.o.provides: CMakeFiles/test_shapes.dir/console-colors.c.o.requires
	$(MAKE) -f CMakeFiles/test_shapes.dir/build.make CMakeFiles/test_shapes.dir/console-colors.c.o.provides.build
.PHONY : CMakeFiles/test_shapes.dir/console-colors.c.o.provides

CMakeFiles/test_shapes.dir/console-colors.c.o.provides.build: CMakeFiles/test_shapes.dir/console-colors.c.o

# Object files for target test_shapes
test_shapes_OBJECTS = \
"CMakeFiles/test_shapes.dir/test_shapes.c.o" \
"CMakeFiles/test_shapes.dir/console-colors.c.o"

# External object files for target test_shapes
test_shapes_EXTERNAL_OBJECTS =

test_shapes: CMakeFiles/test_shapes.dir/test_shapes.c.o
test_shapes: CMakeFiles/test_shapes.dir/console-colors.c.o
test_shapes: CMakeFiles/test_shapes.dir/build.make
test_shapes: CMakeFiles/test_shapes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable test_shapes"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_shapes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_shapes.dir/build: test_shapes
.PHONY : CMakeFiles/test_shapes.dir/build

CMakeFiles/test_shapes.dir/requires: CMakeFiles/test_shapes.dir/test_shapes.c.o.requires
CMakeFiles/test_shapes.dir/requires: CMakeFiles/test_shapes.dir/console-colors.c.o.requires
.PHONY : CMakeFiles/test_shapes.dir/requires

CMakeFiles/test_shapes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_shapes.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_shapes.dir/clean

CMakeFiles/test_shapes.dir/depend:
	cd /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles/test_shapes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_shapes.dir/depend
