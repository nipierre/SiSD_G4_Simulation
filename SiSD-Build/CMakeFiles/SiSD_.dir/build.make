# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nico/CodeSoft/G4/G4/SiSD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nico/CodeSoft/G4/G4/SiSD-Build

# Utility rule file for SiSD_.

# Include the progress variables for this target.
include CMakeFiles/SiSD_.dir/progress.make

CMakeFiles/SiSD_: SiSD

SiSD_: CMakeFiles/SiSD_
SiSD_: CMakeFiles/SiSD_.dir/build.make
.PHONY : SiSD_

# Rule to build all files generated by this target.
CMakeFiles/SiSD_.dir/build: SiSD_
.PHONY : CMakeFiles/SiSD_.dir/build

CMakeFiles/SiSD_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SiSD_.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SiSD_.dir/clean

CMakeFiles/SiSD_.dir/depend:
	cd /Users/nico/CodeSoft/G4/G4/SiSD-Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nico/CodeSoft/G4/G4/SiSD /Users/nico/CodeSoft/G4/G4/SiSD /Users/nico/CodeSoft/G4/G4/SiSD-Build /Users/nico/CodeSoft/G4/G4/SiSD-Build /Users/nico/CodeSoft/G4/G4/SiSD-Build/CMakeFiles/SiSD_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SiSD_.dir/depend
