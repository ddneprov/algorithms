# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "/Users/dneprovdanila/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/dneprovdanila/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dneprovdanila/Desktop/time_loop

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dneprovdanila/Desktop/time_loop/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/time_loop.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/time_loop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/time_loop.dir/flags.make

CMakeFiles/time_loop.dir/main.cpp.o: CMakeFiles/time_loop.dir/flags.make
CMakeFiles/time_loop.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dneprovdanila/Desktop/time_loop/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/time_loop.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/time_loop.dir/main.cpp.o -c /Users/dneprovdanila/Desktop/time_loop/main.cpp

CMakeFiles/time_loop.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/time_loop.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dneprovdanila/Desktop/time_loop/main.cpp > CMakeFiles/time_loop.dir/main.cpp.i

CMakeFiles/time_loop.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/time_loop.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dneprovdanila/Desktop/time_loop/main.cpp -o CMakeFiles/time_loop.dir/main.cpp.s

# Object files for target time_loop
time_loop_OBJECTS = \
"CMakeFiles/time_loop.dir/main.cpp.o"

# External object files for target time_loop
time_loop_EXTERNAL_OBJECTS =

time_loop: CMakeFiles/time_loop.dir/main.cpp.o
time_loop: CMakeFiles/time_loop.dir/build.make
time_loop: CMakeFiles/time_loop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dneprovdanila/Desktop/time_loop/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable time_loop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/time_loop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/time_loop.dir/build: time_loop

.PHONY : CMakeFiles/time_loop.dir/build

CMakeFiles/time_loop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/time_loop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/time_loop.dir/clean

CMakeFiles/time_loop.dir/depend:
	cd /Users/dneprovdanila/Desktop/time_loop/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dneprovdanila/Desktop/time_loop /Users/dneprovdanila/Desktop/time_loop /Users/dneprovdanila/Desktop/time_loop/cmake-build-debug /Users/dneprovdanila/Desktop/time_loop/cmake-build-debug /Users/dneprovdanila/Desktop/time_loop/cmake-build-debug/CMakeFiles/time_loop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/time_loop.dir/depend

