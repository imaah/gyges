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
include CMakeFiles/gyges.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gyges.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gyges.dir/flags.make

CMakeFiles/gyges.dir/main.c.o: CMakeFiles/gyges.dir/flags.make
CMakeFiles/gyges.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gyges.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gyges.dir/main.c.o   -c /home/esteban/gyges/phase-3/src/main.c

CMakeFiles/gyges.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gyges.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/esteban/gyges/phase-3/src/main.c > CMakeFiles/gyges.dir/main.c.i

CMakeFiles/gyges.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gyges.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/esteban/gyges/phase-3/src/main.c -o CMakeFiles/gyges.dir/main.c.s

CMakeFiles/gyges.dir/window.c.o: CMakeFiles/gyges.dir/flags.make
CMakeFiles/gyges.dir/window.c.o: window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gyges.dir/window.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gyges.dir/window.c.o   -c /home/esteban/gyges/phase-3/src/window.c

CMakeFiles/gyges.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gyges.dir/window.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/esteban/gyges/phase-3/src/window.c > CMakeFiles/gyges.dir/window.c.i

CMakeFiles/gyges.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gyges.dir/window.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/esteban/gyges/phase-3/src/window.c -o CMakeFiles/gyges.dir/window.c.s

CMakeFiles/gyges.dir/board.c.o: CMakeFiles/gyges.dir/flags.make
CMakeFiles/gyges.dir/board.c.o: board.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/gyges.dir/board.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gyges.dir/board.c.o   -c /home/esteban/gyges/phase-3/src/board.c

CMakeFiles/gyges.dir/board.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gyges.dir/board.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/esteban/gyges/phase-3/src/board.c > CMakeFiles/gyges.dir/board.c.i

CMakeFiles/gyges.dir/board.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gyges.dir/board.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/esteban/gyges/phase-3/src/board.c -o CMakeFiles/gyges.dir/board.c.s

CMakeFiles/gyges.dir/game.c.o: CMakeFiles/gyges.dir/flags.make
CMakeFiles/gyges.dir/game.c.o: game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/gyges.dir/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gyges.dir/game.c.o   -c /home/esteban/gyges/phase-3/src/game.c

CMakeFiles/gyges.dir/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gyges.dir/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/esteban/gyges/phase-3/src/game.c > CMakeFiles/gyges.dir/game.c.i

CMakeFiles/gyges.dir/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gyges.dir/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/esteban/gyges/phase-3/src/game.c -o CMakeFiles/gyges.dir/game.c.s

CMakeFiles/gyges.dir/input_output.c.o: CMakeFiles/gyges.dir/flags.make
CMakeFiles/gyges.dir/input_output.c.o: input_output.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/gyges.dir/input_output.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gyges.dir/input_output.c.o   -c /home/esteban/gyges/phase-3/src/input_output.c

CMakeFiles/gyges.dir/input_output.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gyges.dir/input_output.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/esteban/gyges/phase-3/src/input_output.c > CMakeFiles/gyges.dir/input_output.c.i

CMakeFiles/gyges.dir/input_output.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gyges.dir/input_output.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/esteban/gyges/phase-3/src/input_output.c -o CMakeFiles/gyges.dir/input_output.c.s

# Object files for target gyges
gyges_OBJECTS = \
"CMakeFiles/gyges.dir/main.c.o" \
"CMakeFiles/gyges.dir/window.c.o" \
"CMakeFiles/gyges.dir/board.c.o" \
"CMakeFiles/gyges.dir/game.c.o" \
"CMakeFiles/gyges.dir/input_output.c.o"

# External object files for target gyges
gyges_EXTERNAL_OBJECTS =

gyges: CMakeFiles/gyges.dir/main.c.o
gyges: CMakeFiles/gyges.dir/window.c.o
gyges: CMakeFiles/gyges.dir/board.c.o
gyges: CMakeFiles/gyges.dir/game.c.o
gyges: CMakeFiles/gyges.dir/input_output.c.o
gyges: CMakeFiles/gyges.dir/build.make
gyges: /usr/lib/x86_64-linux-gnu/libSDL2main.a
gyges: /usr/lib/x86_64-linux-gnu/libSDL2.so
gyges: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
gyges: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
gyges: CMakeFiles/gyges.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/esteban/gyges/phase-3/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable gyges"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gyges.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gyges.dir/build: gyges

.PHONY : CMakeFiles/gyges.dir/build

CMakeFiles/gyges.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gyges.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gyges.dir/clean

CMakeFiles/gyges.dir/depend:
	cd /home/esteban/gyges/phase-3/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src /home/esteban/gyges/phase-3/src/CMakeFiles/gyges.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gyges.dir/depend
