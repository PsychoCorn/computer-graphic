# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\cg\fewf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\cg\fewf\build

# Include any dependencies generated for this target.
include CMakeFiles/lab.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab.dir/flags.make

CMakeFiles/lab.dir/main.cpp.obj: CMakeFiles/lab.dir/flags.make
CMakeFiles/lab.dir/main.cpp.obj: C:/cg/fewf/main.cpp
CMakeFiles/lab.dir/main.cpp.obj: CMakeFiles/lab.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\cg\fewf\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab.dir/main.cpp.obj -MF CMakeFiles\lab.dir\main.cpp.obj.d -o CMakeFiles\lab.dir\main.cpp.obj -c C:\cg\fewf\main.cpp

CMakeFiles/lab.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\cg\fewf\main.cpp > CMakeFiles\lab.dir\main.cpp.i

CMakeFiles/lab.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\cg\fewf\main.cpp -o CMakeFiles\lab.dir\main.cpp.s

# Object files for target lab
lab_OBJECTS = \
"CMakeFiles/lab.dir/main.cpp.obj"

# External object files for target lab
lab_EXTERNAL_OBJECTS =

lab.exe: CMakeFiles/lab.dir/main.cpp.obj
lab.exe: CMakeFiles/lab.dir/build.make
lab.exe: libcamera.a
lab.exe: CMakeFiles/lab.dir/linkLibs.rsp
lab.exe: CMakeFiles/lab.dir/objects1.rsp
lab.exe: CMakeFiles/lab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\cg\fewf\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lab.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab.dir/build: lab.exe
.PHONY : CMakeFiles/lab.dir/build

CMakeFiles/lab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lab.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lab.dir/clean

CMakeFiles/lab.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\cg\fewf C:\cg\fewf C:\cg\fewf\build C:\cg\fewf\build C:\cg\fewf\build\CMakeFiles\lab.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lab.dir/depend

