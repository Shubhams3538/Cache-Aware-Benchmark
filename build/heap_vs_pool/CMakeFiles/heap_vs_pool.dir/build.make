# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/murphy/Downloads/cache-aware-benchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/murphy/Downloads/cache-aware-benchmark/build

# Include any dependencies generated for this target.
include heap_vs_pool/CMakeFiles/heap_vs_pool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include heap_vs_pool/CMakeFiles/heap_vs_pool.dir/compiler_depend.make

# Include the progress variables for this target.
include heap_vs_pool/CMakeFiles/heap_vs_pool.dir/progress.make

# Include the compile flags for this target's objects.
include heap_vs_pool/CMakeFiles/heap_vs_pool.dir/flags.make

heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o: heap_vs_pool/CMakeFiles/heap_vs_pool.dir/flags.make
heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o: /home/murphy/Downloads/cache-aware-benchmark/heap_vs_pool/heap_vs_pool.cpp
heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o: heap_vs_pool/CMakeFiles/heap_vs_pool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/murphy/Downloads/cache-aware-benchmark/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o"
	cd /home/murphy/Downloads/cache-aware-benchmark/build/heap_vs_pool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o -MF CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o.d -o CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o -c /home/murphy/Downloads/cache-aware-benchmark/heap_vs_pool/heap_vs_pool.cpp

heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.i"
	cd /home/murphy/Downloads/cache-aware-benchmark/build/heap_vs_pool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/murphy/Downloads/cache-aware-benchmark/heap_vs_pool/heap_vs_pool.cpp > CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.i

heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.s"
	cd /home/murphy/Downloads/cache-aware-benchmark/build/heap_vs_pool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/murphy/Downloads/cache-aware-benchmark/heap_vs_pool/heap_vs_pool.cpp -o CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.s

# Object files for target heap_vs_pool
heap_vs_pool_OBJECTS = \
"CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o"

# External object files for target heap_vs_pool
heap_vs_pool_EXTERNAL_OBJECTS =

heap_vs_pool/heap_vs_pool: heap_vs_pool/CMakeFiles/heap_vs_pool.dir/heap_vs_pool.cpp.o
heap_vs_pool/heap_vs_pool: heap_vs_pool/CMakeFiles/heap_vs_pool.dir/build.make
heap_vs_pool/heap_vs_pool: heap_vs_pool/CMakeFiles/heap_vs_pool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/murphy/Downloads/cache-aware-benchmark/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable heap_vs_pool"
	cd /home/murphy/Downloads/cache-aware-benchmark/build/heap_vs_pool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/heap_vs_pool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
heap_vs_pool/CMakeFiles/heap_vs_pool.dir/build: heap_vs_pool/heap_vs_pool
.PHONY : heap_vs_pool/CMakeFiles/heap_vs_pool.dir/build

heap_vs_pool/CMakeFiles/heap_vs_pool.dir/clean:
	cd /home/murphy/Downloads/cache-aware-benchmark/build/heap_vs_pool && $(CMAKE_COMMAND) -P CMakeFiles/heap_vs_pool.dir/cmake_clean.cmake
.PHONY : heap_vs_pool/CMakeFiles/heap_vs_pool.dir/clean

heap_vs_pool/CMakeFiles/heap_vs_pool.dir/depend:
	cd /home/murphy/Downloads/cache-aware-benchmark/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/murphy/Downloads/cache-aware-benchmark /home/murphy/Downloads/cache-aware-benchmark/heap_vs_pool /home/murphy/Downloads/cache-aware-benchmark/build /home/murphy/Downloads/cache-aware-benchmark/build/heap_vs_pool /home/murphy/Downloads/cache-aware-benchmark/build/heap_vs_pool/CMakeFiles/heap_vs_pool.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : heap_vs_pool/CMakeFiles/heap_vs_pool.dir/depend

