# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


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
CMAKE_COMMAND = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gil.romano/WET2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gil.romano/WET2/build

# Include any dependencies generated for this target.
include CMakeFiles/hw2_wet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw2_wet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw2_wet.dir/flags.make

CMakeFiles/hw2_wet.dir/test_main.cpp.o: CMakeFiles/hw2_wet.dir/flags.make
CMakeFiles/hw2_wet.dir/test_main.cpp.o: ../test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gil.romano/WET2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw2_wet.dir/test_main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw2_wet.dir/test_main.cpp.o -c /home/gil.romano/WET2/test_main.cpp

CMakeFiles/hw2_wet.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2_wet.dir/test_main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gil.romano/WET2/test_main.cpp > CMakeFiles/hw2_wet.dir/test_main.cpp.i

CMakeFiles/hw2_wet.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2_wet.dir/test_main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gil.romano/WET2/test_main.cpp -o CMakeFiles/hw2_wet.dir/test_main.cpp.s

# Object files for target hw2_wet
hw2_wet_OBJECTS = \
"CMakeFiles/hw2_wet.dir/test_main.cpp.o"

# External object files for target hw2_wet
hw2_wet_EXTERNAL_OBJECTS =

hw2_wet: CMakeFiles/hw2_wet.dir/test_main.cpp.o
hw2_wet: CMakeFiles/hw2_wet.dir/build.make
hw2_wet: CMakeFiles/hw2_wet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gil.romano/WET2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw2_wet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw2_wet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw2_wet.dir/build: hw2_wet

.PHONY : CMakeFiles/hw2_wet.dir/build

CMakeFiles/hw2_wet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw2_wet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw2_wet.dir/clean

CMakeFiles/hw2_wet.dir/depend:
	cd /home/gil.romano/WET2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gil.romano/WET2 /home/gil.romano/WET2 /home/gil.romano/WET2/build /home/gil.romano/WET2/build /home/gil.romano/WET2/build/CMakeFiles/hw2_wet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw2_wet.dir/depend
