# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/adminpc/Dokumente/projects/game-of-life

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adminpc/Dokumente/projects/game-of-life

# Include any dependencies generated for this target.
include CMakeFiles/executeTests2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/executeTests2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/executeTests2.dir/flags.make

CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.o: CMakeFiles/executeTests2.dir/flags.make
CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.o: opencl/gol-test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adminpc/Dokumente/projects/game-of-life/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.o -c /home/adminpc/Dokumente/projects/game-of-life/opencl/gol-test.cpp

CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adminpc/Dokumente/projects/game-of-life/opencl/gol-test.cpp > CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.i

CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adminpc/Dokumente/projects/game-of-life/opencl/gol-test.cpp -o CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.s

# Object files for target executeTests2
executeTests2_OBJECTS = \
"CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.o"

# External object files for target executeTests2
executeTests2_EXTERNAL_OBJECTS =

executeTests2: CMakeFiles/executeTests2.dir/opencl/gol-test.cpp.o
executeTests2: CMakeFiles/executeTests2.dir/build.make
executeTests2: /usr/lib/x86_64-linux-gnu/libgtest.a
executeTests2: CMakeFiles/executeTests2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adminpc/Dokumente/projects/game-of-life/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable executeTests2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/executeTests2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/executeTests2.dir/build: executeTests2

.PHONY : CMakeFiles/executeTests2.dir/build

CMakeFiles/executeTests2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/executeTests2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/executeTests2.dir/clean

CMakeFiles/executeTests2.dir/depend:
	cd /home/adminpc/Dokumente/projects/game-of-life && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adminpc/Dokumente/projects/game-of-life /home/adminpc/Dokumente/projects/game-of-life /home/adminpc/Dokumente/projects/game-of-life /home/adminpc/Dokumente/projects/game-of-life /home/adminpc/Dokumente/projects/game-of-life/CMakeFiles/executeTests2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/executeTests2.dir/depend
