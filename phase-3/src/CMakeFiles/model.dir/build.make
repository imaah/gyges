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
CMAKE_SOURCE_DIR = /home/esteban/gyges/phase-3/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/esteban/gyges/phase-3/src

# Include any dependencies generated for this target.
include CMakeFiles/model.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/model.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/model.dir/flags.make

CMakeFiles/model.dir/main.c.o: CMakeFiles/model.dir/flags.make
CMakeFiles/model.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/model.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/model.dir/main.c.o   -c /home/esteban/gyges/phase-3/src/main.c

CMakeFiles/model.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/model.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/esteban/gyges/phase-3/src/main.c > CMakeFiles/model.dir/main.c.i

CMakeFiles/model.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/model.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/esteban/gyges/phase-3/src/main.c -o CMakeFiles/model.dir/main.c.s

CMakeFiles/model.dir/window.c.o: CMakeFiles/model.dir/flags.make
CMakeFiles/model.dir/window.c.o: window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/model.dir/window.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/model.dir/window.c.o   -c /home/esteban/gyges/phase-3/src/window.c

CMakeFiles/model.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/model.dir/window.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/esteban/gyges/phase-3/src/window.c > CMakeFiles/model.dir/window.c.i

CMakeFiles/model.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/model.dir/window.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/esteban/gyges/phase-3/src/window.c -o CMakeFiles/model.dir/window.c.s

# Object files for target model
model_OBJECTS = \
"CMakeFiles/model.dir/main.c.o" \
"CMakeFiles/model.dir/window.c.o"

# External object files for target model
model_EXTERNAL_OBJECTS =

model: CMakeFiles/model.dir/main.c.o
model: CMakeFiles/model.dir/window.c.o
model: CMakeFiles/model.dir/build.make
model: /usr/lib/x86_64-linux-gnu/libSDL2main.a
model: /usr/lib/x86_64-linux-gnu/libSDL2.so
model: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
model: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
model: CMakeFiles/model.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable model"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/model.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/model.dir/build: model

.PHONY : CMakeFiles/model.dir/build

CMakeFiles/model.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/model.dir/cmake_clean.cmake
.PHONY : CMakeFiles/model.dir/clean

CMakeFiles/model.dir/depend:
	cd /home/esteban/gyges/phase-3/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src/CMakeFiles/model.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/model.dir/depend

