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
include CMakeFiles/test_bluenoise.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_bluenoise.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_bluenoise.dir/flags.make

CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o: CMakeFiles/test_bluenoise.dir/flags.make
CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o: test_bluenoise.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o   -c /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/test_bluenoise.c

CMakeFiles/test_bluenoise.dir/test_bluenoise.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_bluenoise.dir/test_bluenoise.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/test_bluenoise.c > CMakeFiles/test_bluenoise.dir/test_bluenoise.c.i

CMakeFiles/test_bluenoise.dir/test_bluenoise.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_bluenoise.dir/test_bluenoise.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/test_bluenoise.c -o CMakeFiles/test_bluenoise.dir/test_bluenoise.c.s

CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.requires:
.PHONY : CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.requires

CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.provides: CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.requires
	$(MAKE) -f CMakeFiles/test_bluenoise.dir/build.make CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.provides.build
.PHONY : CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.provides

CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.provides.build: CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o

CMakeFiles/test_bluenoise.dir/lz4.cpp.o: CMakeFiles/test_bluenoise.dir/flags.make
CMakeFiles/test_bluenoise.dir/lz4.cpp.o: lz4.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_bluenoise.dir/lz4.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_bluenoise.dir/lz4.cpp.o -c /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/lz4.cpp

CMakeFiles/test_bluenoise.dir/lz4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_bluenoise.dir/lz4.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/lz4.cpp > CMakeFiles/test_bluenoise.dir/lz4.cpp.i

CMakeFiles/test_bluenoise.dir/lz4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_bluenoise.dir/lz4.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/lz4.cpp -o CMakeFiles/test_bluenoise.dir/lz4.cpp.s

CMakeFiles/test_bluenoise.dir/lz4.cpp.o.requires:
.PHONY : CMakeFiles/test_bluenoise.dir/lz4.cpp.o.requires

CMakeFiles/test_bluenoise.dir/lz4.cpp.o.provides: CMakeFiles/test_bluenoise.dir/lz4.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_bluenoise.dir/build.make CMakeFiles/test_bluenoise.dir/lz4.cpp.o.provides.build
.PHONY : CMakeFiles/test_bluenoise.dir/lz4.cpp.o.provides

CMakeFiles/test_bluenoise.dir/lz4.cpp.o.provides.build: CMakeFiles/test_bluenoise.dir/lz4.cpp.o

CMakeFiles/test_bluenoise.dir/lodepng.c.o: CMakeFiles/test_bluenoise.dir/flags.make
CMakeFiles/test_bluenoise.dir/lodepng.c.o: lodepng.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_bluenoise.dir/lodepng.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_bluenoise.dir/lodepng.c.o   -c /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/lodepng.c

CMakeFiles/test_bluenoise.dir/lodepng.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_bluenoise.dir/lodepng.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/lodepng.c > CMakeFiles/test_bluenoise.dir/lodepng.c.i

CMakeFiles/test_bluenoise.dir/lodepng.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_bluenoise.dir/lodepng.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/lodepng.c -o CMakeFiles/test_bluenoise.dir/lodepng.c.s

CMakeFiles/test_bluenoise.dir/lodepng.c.o.requires:
.PHONY : CMakeFiles/test_bluenoise.dir/lodepng.c.o.requires

CMakeFiles/test_bluenoise.dir/lodepng.c.o.provides: CMakeFiles/test_bluenoise.dir/lodepng.c.o.requires
	$(MAKE) -f CMakeFiles/test_bluenoise.dir/build.make CMakeFiles/test_bluenoise.dir/lodepng.c.o.provides.build
.PHONY : CMakeFiles/test_bluenoise.dir/lodepng.c.o.provides

CMakeFiles/test_bluenoise.dir/lodepng.c.o.provides.build: CMakeFiles/test_bluenoise.dir/lodepng.c.o

CMakeFiles/test_bluenoise.dir/sds.c.o: CMakeFiles/test_bluenoise.dir/flags.make
CMakeFiles/test_bluenoise.dir/sds.c.o: sds.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_bluenoise.dir/sds.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_bluenoise.dir/sds.c.o   -c /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/sds.c

CMakeFiles/test_bluenoise.dir/sds.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_bluenoise.dir/sds.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/sds.c > CMakeFiles/test_bluenoise.dir/sds.c.i

CMakeFiles/test_bluenoise.dir/sds.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_bluenoise.dir/sds.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/sds.c -o CMakeFiles/test_bluenoise.dir/sds.c.s

CMakeFiles/test_bluenoise.dir/sds.c.o.requires:
.PHONY : CMakeFiles/test_bluenoise.dir/sds.c.o.requires

CMakeFiles/test_bluenoise.dir/sds.c.o.provides: CMakeFiles/test_bluenoise.dir/sds.c.o.requires
	$(MAKE) -f CMakeFiles/test_bluenoise.dir/build.make CMakeFiles/test_bluenoise.dir/sds.c.o.provides.build
.PHONY : CMakeFiles/test_bluenoise.dir/sds.c.o.provides

CMakeFiles/test_bluenoise.dir/sds.c.o.provides.build: CMakeFiles/test_bluenoise.dir/sds.c.o

CMakeFiles/test_bluenoise.dir/whereami.c.o: CMakeFiles/test_bluenoise.dir/flags.make
CMakeFiles/test_bluenoise.dir/whereami.c.o: whereami.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_bluenoise.dir/whereami.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_bluenoise.dir/whereami.c.o   -c /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/whereami.c

CMakeFiles/test_bluenoise.dir/whereami.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_bluenoise.dir/whereami.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/whereami.c > CMakeFiles/test_bluenoise.dir/whereami.c.i

CMakeFiles/test_bluenoise.dir/whereami.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_bluenoise.dir/whereami.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/whereami.c -o CMakeFiles/test_bluenoise.dir/whereami.c.s

CMakeFiles/test_bluenoise.dir/whereami.c.o.requires:
.PHONY : CMakeFiles/test_bluenoise.dir/whereami.c.o.requires

CMakeFiles/test_bluenoise.dir/whereami.c.o.provides: CMakeFiles/test_bluenoise.dir/whereami.c.o.requires
	$(MAKE) -f CMakeFiles/test_bluenoise.dir/build.make CMakeFiles/test_bluenoise.dir/whereami.c.o.provides.build
.PHONY : CMakeFiles/test_bluenoise.dir/whereami.c.o.provides

CMakeFiles/test_bluenoise.dir/whereami.c.o.provides.build: CMakeFiles/test_bluenoise.dir/whereami.c.o

# Object files for target test_bluenoise
test_bluenoise_OBJECTS = \
"CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o" \
"CMakeFiles/test_bluenoise.dir/lz4.cpp.o" \
"CMakeFiles/test_bluenoise.dir/lodepng.c.o" \
"CMakeFiles/test_bluenoise.dir/sds.c.o" \
"CMakeFiles/test_bluenoise.dir/whereami.c.o"

# External object files for target test_bluenoise
test_bluenoise_EXTERNAL_OBJECTS =

test_bluenoise: CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o
test_bluenoise: CMakeFiles/test_bluenoise.dir/lz4.cpp.o
test_bluenoise: CMakeFiles/test_bluenoise.dir/lodepng.c.o
test_bluenoise: CMakeFiles/test_bluenoise.dir/sds.c.o
test_bluenoise: CMakeFiles/test_bluenoise.dir/whereami.c.o
test_bluenoise: CMakeFiles/test_bluenoise.dir/build.make
test_bluenoise: CMakeFiles/test_bluenoise.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test_bluenoise"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bluenoise.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_bluenoise.dir/build: test_bluenoise
.PHONY : CMakeFiles/test_bluenoise.dir/build

CMakeFiles/test_bluenoise.dir/requires: CMakeFiles/test_bluenoise.dir/test_bluenoise.c.o.requires
CMakeFiles/test_bluenoise.dir/requires: CMakeFiles/test_bluenoise.dir/lz4.cpp.o.requires
CMakeFiles/test_bluenoise.dir/requires: CMakeFiles/test_bluenoise.dir/lodepng.c.o.requires
CMakeFiles/test_bluenoise.dir/requires: CMakeFiles/test_bluenoise.dir/sds.c.o.requires
CMakeFiles/test_bluenoise.dir/requires: CMakeFiles/test_bluenoise.dir/whereami.c.o.requires
.PHONY : CMakeFiles/test_bluenoise.dir/requires

CMakeFiles/test_bluenoise.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_bluenoise.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_bluenoise.dir/clean

CMakeFiles/test_bluenoise.dir/depend:
	cd /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test /home/dahl/rd/projects/00_electronics/neural_network_robot/par/test/CMakeFiles/test_bluenoise.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_bluenoise.dir/depend

