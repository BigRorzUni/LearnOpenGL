# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bigrorz/GLFW-CMake-starter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bigrorz/GLFW-CMake-starter/build

# Include any dependencies generated for this target.
include CMakeFiles/GLFW-CMake-starter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GLFW-CMake-starter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GLFW-CMake-starter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GLFW-CMake-starter.dir/flags.make

CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o: CMakeFiles/GLFW-CMake-starter.dir/flags.make
CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o: /Users/bigrorz/GLFW-CMake-starter/main.cpp
CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o: CMakeFiles/GLFW-CMake-starter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/bigrorz/GLFW-CMake-starter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o -MF CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o.d -o CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o -c /Users/bigrorz/GLFW-CMake-starter/main.cpp

CMakeFiles/GLFW-CMake-starter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLFW-CMake-starter.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bigrorz/GLFW-CMake-starter/main.cpp > CMakeFiles/GLFW-CMake-starter.dir/main.cpp.i

CMakeFiles/GLFW-CMake-starter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLFW-CMake-starter.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bigrorz/GLFW-CMake-starter/main.cpp -o CMakeFiles/GLFW-CMake-starter.dir/main.cpp.s

CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o: CMakeFiles/GLFW-CMake-starter.dir/flags.make
CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o: /Users/bigrorz/GLFW-CMake-starter/glad/src/glad.c
CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o: CMakeFiles/GLFW-CMake-starter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/bigrorz/GLFW-CMake-starter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o -MF CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o.d -o CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o -c /Users/bigrorz/GLFW-CMake-starter/glad/src/glad.c

CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/bigrorz/GLFW-CMake-starter/glad/src/glad.c > CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.i

CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/bigrorz/GLFW-CMake-starter/glad/src/glad.c -o CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.s

# Object files for target GLFW-CMake-starter
GLFW__CMake__starter_OBJECTS = \
"CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o" \
"CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o"

# External object files for target GLFW-CMake-starter
GLFW__CMake__starter_EXTERNAL_OBJECTS =

GLFW-CMake-starter: CMakeFiles/GLFW-CMake-starter.dir/main.cpp.o
GLFW-CMake-starter: CMakeFiles/GLFW-CMake-starter.dir/glad/src/glad.c.o
GLFW-CMake-starter: CMakeFiles/GLFW-CMake-starter.dir/build.make
GLFW-CMake-starter: glfw/src/libglfw3.a
GLFW-CMake-starter: CMakeFiles/GLFW-CMake-starter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/bigrorz/GLFW-CMake-starter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable GLFW-CMake-starter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GLFW-CMake-starter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GLFW-CMake-starter.dir/build: GLFW-CMake-starter
.PHONY : CMakeFiles/GLFW-CMake-starter.dir/build

CMakeFiles/GLFW-CMake-starter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GLFW-CMake-starter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GLFW-CMake-starter.dir/clean

CMakeFiles/GLFW-CMake-starter.dir/depend:
	cd /Users/bigrorz/GLFW-CMake-starter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bigrorz/GLFW-CMake-starter /Users/bigrorz/GLFW-CMake-starter /Users/bigrorz/GLFW-CMake-starter/build /Users/bigrorz/GLFW-CMake-starter/build /Users/bigrorz/GLFW-CMake-starter/build/CMakeFiles/GLFW-CMake-starter.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GLFW-CMake-starter.dir/depend

