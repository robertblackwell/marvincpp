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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/robertblackwell/Projects/marvin++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/robertblackwell/Projects/marvin++/cmake-build

# Include any dependencies generated for this target.
include tests/test_buffers/CMakeFiles/test_buffers.dir/depend.make

# Include the progress variables for this target.
include tests/test_buffers/CMakeFiles/test_buffers.dir/progress.make

# Include the compile flags for this target's objects.
include tests/test_buffers/CMakeFiles/test_buffers.dir/flags.make

tests/test_buffers/CMakeFiles/test_buffers.dir/test_buffer_main.cpp.o: tests/test_buffers/CMakeFiles/test_buffers.dir/flags.make
tests/test_buffers/CMakeFiles/test_buffers.dir/test_buffer_main.cpp.o: ../tests/test_buffers/test_buffer_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/robertblackwell/Projects/marvin++/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/test_buffers/CMakeFiles/test_buffers.dir/test_buffer_main.cpp.o"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_buffers.dir/test_buffer_main.cpp.o -c /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_buffer_main.cpp

tests/test_buffers/CMakeFiles/test_buffers.dir/test_buffer_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_buffers.dir/test_buffer_main.cpp.i"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_buffer_main.cpp > CMakeFiles/test_buffers.dir/test_buffer_main.cpp.i

tests/test_buffers/CMakeFiles/test_buffers.dir/test_buffer_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_buffers.dir/test_buffer_main.cpp.s"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_buffer_main.cpp -o CMakeFiles/test_buffers.dir/test_buffer_main.cpp.s

tests/test_buffers/CMakeFiles/test_buffers.dir/test_fbuffer.cpp.o: tests/test_buffers/CMakeFiles/test_buffers.dir/flags.make
tests/test_buffers/CMakeFiles/test_buffers.dir/test_fbuffer.cpp.o: ../tests/test_buffers/test_fbuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/robertblackwell/Projects/marvin++/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/test_buffers/CMakeFiles/test_buffers.dir/test_fbuffer.cpp.o"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_buffers.dir/test_fbuffer.cpp.o -c /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_fbuffer.cpp

tests/test_buffers/CMakeFiles/test_buffers.dir/test_fbuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_buffers.dir/test_fbuffer.cpp.i"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_fbuffer.cpp > CMakeFiles/test_buffers.dir/test_fbuffer.cpp.i

tests/test_buffers/CMakeFiles/test_buffers.dir/test_fbuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_buffers.dir/test_fbuffer.cpp.s"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_fbuffer.cpp -o CMakeFiles/test_buffers.dir/test_fbuffer.cpp.s

tests/test_buffers/CMakeFiles/test_buffers.dir/test_mbuffer.cpp.o: tests/test_buffers/CMakeFiles/test_buffers.dir/flags.make
tests/test_buffers/CMakeFiles/test_buffers.dir/test_mbuffer.cpp.o: ../tests/test_buffers/test_mbuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/robertblackwell/Projects/marvin++/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/test_buffers/CMakeFiles/test_buffers.dir/test_mbuffer.cpp.o"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_buffers.dir/test_mbuffer.cpp.o -c /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_mbuffer.cpp

tests/test_buffers/CMakeFiles/test_buffers.dir/test_mbuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_buffers.dir/test_mbuffer.cpp.i"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_mbuffer.cpp > CMakeFiles/test_buffers.dir/test_mbuffer.cpp.i

tests/test_buffers/CMakeFiles/test_buffers.dir/test_mbuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_buffers.dir/test_mbuffer.cpp.s"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/robertblackwell/Projects/marvin++/tests/test_buffers/test_mbuffer.cpp -o CMakeFiles/test_buffers.dir/test_mbuffer.cpp.s

# Object files for target test_buffers
test_buffers_OBJECTS = \
"CMakeFiles/test_buffers.dir/test_buffer_main.cpp.o" \
"CMakeFiles/test_buffers.dir/test_fbuffer.cpp.o" \
"CMakeFiles/test_buffers.dir/test_mbuffer.cpp.o"

# External object files for target test_buffers
test_buffers_EXTERNAL_OBJECTS =

tests/test_buffers/test_buffers: tests/test_buffers/CMakeFiles/test_buffers.dir/test_buffer_main.cpp.o
tests/test_buffers/test_buffers: tests/test_buffers/CMakeFiles/test_buffers.dir/test_fbuffer.cpp.o
tests/test_buffers/test_buffers: tests/test_buffers/CMakeFiles/test_buffers.dir/test_mbuffer.cpp.o
tests/test_buffers/test_buffers: tests/test_buffers/CMakeFiles/test_buffers.dir/build.make
tests/test_buffers/test_buffers: marvin/libmarvin_library.a
tests/test_buffers/test_buffers: marvin/libmarvin_library.a
tests/test_buffers/test_buffers: ../vendor/lib/libcrypto.a
tests/test_buffers/test_buffers: ../vendor/lib/libssl.a
tests/test_buffers/test_buffers: ../vendor/lib/libboost_filesystem.a
tests/test_buffers/test_buffers: ../vendor/lib/libboost_system.a
tests/test_buffers/test_buffers: tests/test_buffers/CMakeFiles/test_buffers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/robertblackwell/Projects/marvin++/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test_buffers"
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_buffers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/test_buffers/CMakeFiles/test_buffers.dir/build: tests/test_buffers/test_buffers

.PHONY : tests/test_buffers/CMakeFiles/test_buffers.dir/build

tests/test_buffers/CMakeFiles/test_buffers.dir/clean:
	cd /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers && $(CMAKE_COMMAND) -P CMakeFiles/test_buffers.dir/cmake_clean.cmake
.PHONY : tests/test_buffers/CMakeFiles/test_buffers.dir/clean

tests/test_buffers/CMakeFiles/test_buffers.dir/depend:
	cd /Users/robertblackwell/Projects/marvin++/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/robertblackwell/Projects/marvin++ /Users/robertblackwell/Projects/marvin++/tests/test_buffers /Users/robertblackwell/Projects/marvin++/cmake-build /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers /Users/robertblackwell/Projects/marvin++/cmake-build/tests/test_buffers/CMakeFiles/test_buffers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/test_buffers/CMakeFiles/test_buffers.dir/depend
