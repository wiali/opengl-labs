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
CMAKE_SOURCE_DIR = /home/roman/dev/opengl-labs/qt5-shadow-maps

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default

# Include any dependencies generated for this target.
include sources/CMakeFiles/shadowmaps.dir/depend.make

# Include the progress variables for this target.
include sources/CMakeFiles/shadowmaps.dir/progress.make

# Include the compile flags for this target's objects.
include sources/CMakeFiles/shadowmaps.dir/flags.make

sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o: sources/CMakeFiles/shadowmaps.dir/flags.make
sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o: /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/maingui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadowmaps.dir/maingui.cpp.o -c /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/maingui.cpp

sources/CMakeFiles/shadowmaps.dir/maingui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadowmaps.dir/maingui.cpp.i"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/maingui.cpp > CMakeFiles/shadowmaps.dir/maingui.cpp.i

sources/CMakeFiles/shadowmaps.dir/maingui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadowmaps.dir/maingui.cpp.s"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/maingui.cpp -o CMakeFiles/shadowmaps.dir/maingui.cpp.s

sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.requires:

.PHONY : sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.requires

sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.provides: sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.requires
	$(MAKE) -f sources/CMakeFiles/shadowmaps.dir/build.make sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.provides.build
.PHONY : sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.provides

sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.provides.build: sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o


sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o: sources/CMakeFiles/shadowmaps.dir/flags.make
sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o: /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/openglviewer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadowmaps.dir/openglviewer.cpp.o -c /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/openglviewer.cpp

sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadowmaps.dir/openglviewer.cpp.i"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/openglviewer.cpp > CMakeFiles/shadowmaps.dir/openglviewer.cpp.i

sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadowmaps.dir/openglviewer.cpp.s"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/openglviewer.cpp -o CMakeFiles/shadowmaps.dir/openglviewer.cpp.s

sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.requires:

.PHONY : sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.requires

sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.provides: sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.requires
	$(MAKE) -f sources/CMakeFiles/shadowmaps.dir/build.make sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.provides.build
.PHONY : sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.provides

sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.provides.build: sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o


sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o: sources/CMakeFiles/shadowmaps.dir/flags.make
sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o: /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/appmain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadowmaps.dir/appmain.cpp.o -c /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/appmain.cpp

sources/CMakeFiles/shadowmaps.dir/appmain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadowmaps.dir/appmain.cpp.i"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/appmain.cpp > CMakeFiles/shadowmaps.dir/appmain.cpp.i

sources/CMakeFiles/shadowmaps.dir/appmain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadowmaps.dir/appmain.cpp.s"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/appmain.cpp -o CMakeFiles/shadowmaps.dir/appmain.cpp.s

sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.requires:

.PHONY : sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.requires

sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.provides: sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.requires
	$(MAKE) -f sources/CMakeFiles/shadowmaps.dir/build.make sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.provides.build
.PHONY : sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.provides

sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.provides.build: sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o


sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o: sources/CMakeFiles/shadowmaps.dir/flags.make
sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o: /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/tinyply.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadowmaps.dir/tinyply.cpp.o -c /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/tinyply.cpp

sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadowmaps.dir/tinyply.cpp.i"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/tinyply.cpp > CMakeFiles/shadowmaps.dir/tinyply.cpp.i

sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadowmaps.dir/tinyply.cpp.s"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/qt5-shadow-maps/sources/tinyply.cpp -o CMakeFiles/shadowmaps.dir/tinyply.cpp.s

sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.requires:

.PHONY : sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.requires

sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.provides: sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.requires
	$(MAKE) -f sources/CMakeFiles/shadowmaps.dir/build.make sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.provides.build
.PHONY : sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.provides

sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.provides.build: sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o


sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o: sources/CMakeFiles/shadowmaps.dir/flags.make
sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o: sources/shadowmaps_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o -c /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources/shadowmaps_automoc.cpp

sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.i"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources/shadowmaps_automoc.cpp > CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.i

sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.s"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources/shadowmaps_automoc.cpp -o CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.s

sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.requires:

.PHONY : sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.requires

sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.provides: sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.requires
	$(MAKE) -f sources/CMakeFiles/shadowmaps.dir/build.make sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.provides.build
.PHONY : sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.provides

sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.provides.build: sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o


# Object files for target shadowmaps
shadowmaps_OBJECTS = \
"CMakeFiles/shadowmaps.dir/maingui.cpp.o" \
"CMakeFiles/shadowmaps.dir/openglviewer.cpp.o" \
"CMakeFiles/shadowmaps.dir/appmain.cpp.o" \
"CMakeFiles/shadowmaps.dir/tinyply.cpp.o" \
"CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o"

# External object files for target shadowmaps
shadowmaps_EXTERNAL_OBJECTS =

/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: sources/CMakeFiles/shadowmaps.dir/build.make
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5OpenGL.so.5.7.1
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: /usr/lib/x86_64-linux-gnu/libGLU.so
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: /usr/lib/x86_64-linux-gnu/libGL.so
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5Widgets.so.5.7.1
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5Gui.so.5.7.1
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: /home/roman/IDEAs/Qt/5.7/gcc_64/lib/libQt5Core.so.5.7.1
/home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps: sources/CMakeFiles/shadowmaps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable /home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps"
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shadowmaps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sources/CMakeFiles/shadowmaps.dir/build: /home/roman/dev/opengl-labs/qt5-shadow-maps/build/bin/shadowmaps

.PHONY : sources/CMakeFiles/shadowmaps.dir/build

sources/CMakeFiles/shadowmaps.dir/requires: sources/CMakeFiles/shadowmaps.dir/maingui.cpp.o.requires
sources/CMakeFiles/shadowmaps.dir/requires: sources/CMakeFiles/shadowmaps.dir/openglviewer.cpp.o.requires
sources/CMakeFiles/shadowmaps.dir/requires: sources/CMakeFiles/shadowmaps.dir/appmain.cpp.o.requires
sources/CMakeFiles/shadowmaps.dir/requires: sources/CMakeFiles/shadowmaps.dir/tinyply.cpp.o.requires
sources/CMakeFiles/shadowmaps.dir/requires: sources/CMakeFiles/shadowmaps.dir/shadowmaps_automoc.cpp.o.requires

.PHONY : sources/CMakeFiles/shadowmaps.dir/requires

sources/CMakeFiles/shadowmaps.dir/clean:
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources && $(CMAKE_COMMAND) -P CMakeFiles/shadowmaps.dir/cmake_clean.cmake
.PHONY : sources/CMakeFiles/shadowmaps.dir/clean

sources/CMakeFiles/shadowmaps.dir/depend:
	cd /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roman/dev/opengl-labs/qt5-shadow-maps /home/roman/dev/opengl-labs/qt5-shadow-maps/sources /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources /home/roman/dev/opengl-labs/build-qt5-shadow-maps-Desktop_Qt_5_7_1_GCC_64bit-Default/sources/CMakeFiles/shadowmaps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sources/CMakeFiles/shadowmaps.dir/depend

