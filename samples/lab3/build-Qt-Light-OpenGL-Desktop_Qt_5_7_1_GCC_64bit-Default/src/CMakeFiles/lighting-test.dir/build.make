# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default

# Include any dependencies generated for this target.
include src/CMakeFiles/lighting-test.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/lighting-test.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/lighting-test.dir/flags.make

src/moc_lighting.cpp: /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/lighting.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating moc_lighting.cpp"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /home/roman/IDEAs/Qt/5.7/gcc_64/bin/moc @/home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src/moc_lighting.cpp_parameters

src/CMakeFiles/lighting-test.dir/lighting.cpp.o: src/CMakeFiles/lighting-test.dir/flags.make
src/CMakeFiles/lighting-test.dir/lighting.cpp.o: /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/lighting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/lighting-test.dir/lighting.cpp.o"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lighting-test.dir/lighting.cpp.o -c /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/lighting.cpp

src/CMakeFiles/lighting-test.dir/lighting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lighting-test.dir/lighting.cpp.i"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/lighting.cpp > CMakeFiles/lighting-test.dir/lighting.cpp.i

src/CMakeFiles/lighting-test.dir/lighting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lighting-test.dir/lighting.cpp.s"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/lighting.cpp -o CMakeFiles/lighting-test.dir/lighting.cpp.s

src/CMakeFiles/lighting-test.dir/lighting.cpp.o.requires:

.PHONY : src/CMakeFiles/lighting-test.dir/lighting.cpp.o.requires

src/CMakeFiles/lighting-test.dir/lighting.cpp.o.provides: src/CMakeFiles/lighting-test.dir/lighting.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/lighting-test.dir/build.make src/CMakeFiles/lighting-test.dir/lighting.cpp.o.provides.build
.PHONY : src/CMakeFiles/lighting-test.dir/lighting.cpp.o.provides

src/CMakeFiles/lighting-test.dir/lighting.cpp.o.provides.build: src/CMakeFiles/lighting-test.dir/lighting.cpp.o


src/CMakeFiles/lighting-test.dir/main.cpp.o: src/CMakeFiles/lighting-test.dir/flags.make
src/CMakeFiles/lighting-test.dir/main.cpp.o: /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/lighting-test.dir/main.cpp.o"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lighting-test.dir/main.cpp.o -c /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/main.cpp

src/CMakeFiles/lighting-test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lighting-test.dir/main.cpp.i"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/main.cpp > CMakeFiles/lighting-test.dir/main.cpp.i

src/CMakeFiles/lighting-test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lighting-test.dir/main.cpp.s"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src/main.cpp -o CMakeFiles/lighting-test.dir/main.cpp.s

src/CMakeFiles/lighting-test.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/lighting-test.dir/main.cpp.o.requires

src/CMakeFiles/lighting-test.dir/main.cpp.o.provides: src/CMakeFiles/lighting-test.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/lighting-test.dir/build.make src/CMakeFiles/lighting-test.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/lighting-test.dir/main.cpp.o.provides

src/CMakeFiles/lighting-test.dir/main.cpp.o.provides.build: src/CMakeFiles/lighting-test.dir/main.cpp.o


src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o: src/CMakeFiles/lighting-test.dir/flags.make
src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o: src/moc_lighting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lighting-test.dir/moc_lighting.cpp.o -c /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src/moc_lighting.cpp

src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lighting-test.dir/moc_lighting.cpp.i"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src/moc_lighting.cpp > CMakeFiles/lighting-test.dir/moc_lighting.cpp.i

src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lighting-test.dir/moc_lighting.cpp.s"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src/moc_lighting.cpp -o CMakeFiles/lighting-test.dir/moc_lighting.cpp.s

src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.requires:

.PHONY : src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.requires

src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.provides: src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/lighting-test.dir/build.make src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.provides.build
.PHONY : src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.provides

src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.provides.build: src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o


# Object files for target lighting-test
lighting__test_OBJECTS = \
"CMakeFiles/lighting-test.dir/lighting.cpp.o" \
"CMakeFiles/lighting-test.dir/main.cpp.o" \
"CMakeFiles/lighting-test.dir/moc_lighting.cpp.o"

# External object files for target lighting-test
lighting__test_EXTERNAL_OBJECTS =

bin/lighting-test: src/CMakeFiles/lighting-test.dir/lighting.cpp.o
bin/lighting-test: src/CMakeFiles/lighting-test.dir/main.cpp.o
bin/lighting-test: src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o
bin/lighting-test: src/CMakeFiles/lighting-test.dir/build.make
bin/lighting-test: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5OpenGL.so.5.7.1
bin/lighting-test: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5Widgets.so.5.7.1
bin/lighting-test: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5Gui.so.5.7.1
bin/lighting-test: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5Core.so.5.7.1
bin/lighting-test: src/CMakeFiles/lighting-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../bin/lighting-test"
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lighting-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/lighting-test.dir/build: bin/lighting-test

.PHONY : src/CMakeFiles/lighting-test.dir/build

src/CMakeFiles/lighting-test.dir/requires: src/CMakeFiles/lighting-test.dir/lighting.cpp.o.requires
src/CMakeFiles/lighting-test.dir/requires: src/CMakeFiles/lighting-test.dir/main.cpp.o.requires
src/CMakeFiles/lighting-test.dir/requires: src/CMakeFiles/lighting-test.dir/moc_lighting.cpp.o.requires

.PHONY : src/CMakeFiles/lighting-test.dir/requires

src/CMakeFiles/lighting-test.dir/clean:
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src && $(CMAKE_COMMAND) -P CMakeFiles/lighting-test.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/lighting-test.dir/clean

src/CMakeFiles/lighting-test.dir/depend: src/moc_lighting.cpp
	cd /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL /home/roman/dev/opengl-labs/shadow-samples/Qt-Light-OpenGL/src /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src /home/roman/dev/opengl-labs/shadow-samples/build-Qt-Light-OpenGL-Desktop_Qt_5_7_1_GCC_64bit-Default/src/CMakeFiles/lighting-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/lighting-test.dir/depend
