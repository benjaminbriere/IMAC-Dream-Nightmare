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
CMAKE_SOURCE_DIR = /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build

# Include any dependencies generated for this target.
include src/CMakeFiles/src_main.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src_main.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src_main.dir/flags.make

src/CMakeFiles/src_main.dir/main.cpp.o: src/CMakeFiles/src_main.dir/flags.make
src/CMakeFiles/src_main.dir/main.cpp.o: /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/GLImac-Template/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src_main.dir/main.cpp.o"
	cd /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src_main.dir/main.cpp.o -c /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/GLImac-Template/src/main.cpp

src/CMakeFiles/src_main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src_main.dir/main.cpp.i"
	cd /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/GLImac-Template/src/main.cpp > CMakeFiles/src_main.dir/main.cpp.i

src/CMakeFiles/src_main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src_main.dir/main.cpp.s"
	cd /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/GLImac-Template/src/main.cpp -o CMakeFiles/src_main.dir/main.cpp.s

# Object files for target src_main
src_main_OBJECTS = \
"CMakeFiles/src_main.dir/main.cpp.o"

# External object files for target src_main
src_main_EXTERNAL_OBJECTS =

src/src_main: src/CMakeFiles/src_main.dir/main.cpp.o
src/src_main: src/CMakeFiles/src_main.dir/build.make
src/src_main: glimac/libglimac.a
src/src_main: game/libgame.a
src/src_main: /usr/lib/x86_64-linux-gnu/libSDLmain.a
src/src_main: /usr/lib/x86_64-linux-gnu/libSDL.so
src/src_main: /usr/lib/x86_64-linux-gnu/libSDL_mixer.so
src/src_main: /usr/lib/x86_64-linux-gnu/libGL.so
src/src_main: /usr/lib/x86_64-linux-gnu/libGLU.so
src/src_main: /usr/lib/x86_64-linux-gnu/libGLEW.so
src/src_main: /usr/lib/x86_64-linux-gnu/libassimp.so
src/src_main: glimac/libglimac.a
src/src_main: /usr/lib/x86_64-linux-gnu/libSDLmain.a
src/src_main: /usr/lib/x86_64-linux-gnu/libSDL.so
src/src_main: src/CMakeFiles/src_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable src_main"
	cd /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src_main.dir/build: src/src_main

.PHONY : src/CMakeFiles/src_main.dir/build

src/CMakeFiles/src_main.dir/clean:
	cd /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src_main.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src_main.dir/clean

src/CMakeFiles/src_main.dir/depend:
	cd /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/GLImac-Template /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/GLImac-Template/src /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/src /home/benjamin/Documents/openGL/S3/GITProjet/IMAC-Dream-Nightmare/BASE_Propre/build/src/CMakeFiles/src_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/src_main.dir/depend
