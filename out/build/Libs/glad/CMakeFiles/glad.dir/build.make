# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/alan/DevS/Cpp/OpenGl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alan/DevS/Cpp/OpenGl/out/build

# Include any dependencies generated for this target.
include Libs/glad/CMakeFiles/glad.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Libs/glad/CMakeFiles/glad.dir/compiler_depend.make

# Include the progress variables for this target.
include Libs/glad/CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include Libs/glad/CMakeFiles/glad.dir/flags.make

Libs/glad/CMakeFiles/glad.dir/glad.c.o: Libs/glad/CMakeFiles/glad.dir/flags.make
Libs/glad/CMakeFiles/glad.dir/glad.c.o: ../../Libs/glad/glad.c
Libs/glad/CMakeFiles/glad.dir/glad.c.o: Libs/glad/CMakeFiles/glad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alan/DevS/Cpp/OpenGl/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Libs/glad/CMakeFiles/glad.dir/glad.c.o"
	cd /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libs/glad/CMakeFiles/glad.dir/glad.c.o -MF CMakeFiles/glad.dir/glad.c.o.d -o CMakeFiles/glad.dir/glad.c.o -c /home/alan/DevS/Cpp/OpenGl/Libs/glad/glad.c

Libs/glad/CMakeFiles/glad.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/glad.c.i"
	cd /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alan/DevS/Cpp/OpenGl/Libs/glad/glad.c > CMakeFiles/glad.dir/glad.c.i

Libs/glad/CMakeFiles/glad.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/glad.c.s"
	cd /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alan/DevS/Cpp/OpenGl/Libs/glad/glad.c -o CMakeFiles/glad.dir/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

Libs/glad/libglad.a: Libs/glad/CMakeFiles/glad.dir/glad.c.o
Libs/glad/libglad.a: Libs/glad/CMakeFiles/glad.dir/build.make
Libs/glad/libglad.a: Libs/glad/CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alan/DevS/Cpp/OpenGl/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	cd /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	cd /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Libs/glad/CMakeFiles/glad.dir/build: Libs/glad/libglad.a
.PHONY : Libs/glad/CMakeFiles/glad.dir/build

Libs/glad/CMakeFiles/glad.dir/clean:
	cd /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : Libs/glad/CMakeFiles/glad.dir/clean

Libs/glad/CMakeFiles/glad.dir/depend:
	cd /home/alan/DevS/Cpp/OpenGl/out/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alan/DevS/Cpp/OpenGl /home/alan/DevS/Cpp/OpenGl/Libs/glad /home/alan/DevS/Cpp/OpenGl/out/build /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad /home/alan/DevS/Cpp/OpenGl/out/build/Libs/glad/CMakeFiles/glad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Libs/glad/CMakeFiles/glad.dir/depend

