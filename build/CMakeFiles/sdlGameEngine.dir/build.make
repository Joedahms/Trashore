# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/joe/Documents/coding_projects/sdl_tutorial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joe/Documents/coding_projects/sdl_tutorial/build

# Include any dependencies generated for this target.
include CMakeFiles/sdlGameEngine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sdlGameEngine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sdlGameEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sdlGameEngine.dir/flags.make

CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/camera/camera.cpp
CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/camera/camera.cpp

CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/camera/camera.cpp > CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.i

CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/camera/camera.cpp -o CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.s

CMakeFiles/sdlGameEngine.dir/src/character.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/character.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/character.cpp
CMakeFiles/sdlGameEngine.dir/src/character.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/character.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/character.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/character.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/character.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/character.cpp

CMakeFiles/sdlGameEngine.dir/src/character.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/character.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/character.cpp > CMakeFiles/sdlGameEngine.dir/src/character.cpp.i

CMakeFiles/sdlGameEngine.dir/src/character.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/character.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/character.cpp -o CMakeFiles/sdlGameEngine.dir/src/character.cpp.s

CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/character_factory.cpp
CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/character_factory.cpp

CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/character_factory.cpp > CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.i

CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/character_factory.cpp -o CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.s

CMakeFiles/sdlGameEngine.dir/src/game.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/game.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/game.cpp
CMakeFiles/sdlGameEngine.dir/src/game.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/game.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/game.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/game.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/game.cpp

CMakeFiles/sdlGameEngine.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/game.cpp > CMakeFiles/sdlGameEngine.dir/src/game.cpp.i

CMakeFiles/sdlGameEngine.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/game.cpp -o CMakeFiles/sdlGameEngine.dir/src/game.cpp.s

CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/logger.cpp
CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/logger.cpp

CMakeFiles/sdlGameEngine.dir/src/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/logger.cpp > CMakeFiles/sdlGameEngine.dir/src/logger.cpp.i

CMakeFiles/sdlGameEngine.dir/src/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/logger.cpp -o CMakeFiles/sdlGameEngine.dir/src/logger.cpp.s

CMakeFiles/sdlGameEngine.dir/src/main.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/main.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/main.cpp
CMakeFiles/sdlGameEngine.dir/src/main.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/main.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/main.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/main.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/main.cpp

CMakeFiles/sdlGameEngine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/main.cpp > CMakeFiles/sdlGameEngine.dir/src/main.cpp.i

CMakeFiles/sdlGameEngine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/main.cpp -o CMakeFiles/sdlGameEngine.dir/src/main.cpp.s

CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/main_menu.cpp
CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/main_menu.cpp

CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/main_menu.cpp > CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.i

CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/main_menu.cpp -o CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.s

CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/menu_background.cpp
CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/menu_background.cpp

CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/menu_background.cpp > CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.i

CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/menu/menu_background.cpp -o CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.s

CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/npc.cpp
CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/npc.cpp

CMakeFiles/sdlGameEngine.dir/src/npc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/npc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/npc.cpp > CMakeFiles/sdlGameEngine.dir/src/npc.cpp.i

CMakeFiles/sdlGameEngine.dir/src/npc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/npc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/npc.cpp -o CMakeFiles/sdlGameEngine.dir/src/npc.cpp.s

CMakeFiles/sdlGameEngine.dir/src/player.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/player.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/player.cpp
CMakeFiles/sdlGameEngine.dir/src/player.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/player.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/player.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/player.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/player.cpp

CMakeFiles/sdlGameEngine.dir/src/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/player.cpp > CMakeFiles/sdlGameEngine.dir/src/player.cpp.i

CMakeFiles/sdlGameEngine.dir/src/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/player.cpp -o CMakeFiles/sdlGameEngine.dir/src/player.cpp.s

CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/dirt_tile.cpp
CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/dirt_tile.cpp

CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/dirt_tile.cpp > CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.i

CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/dirt_tile.cpp -o CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.s

CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile.cpp
CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile.cpp

CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile.cpp > CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.i

CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile.cpp -o CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.s

CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile_factory.cpp
CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile_factory.cpp

CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile_factory.cpp > CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.i

CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/tile_factory.cpp -o CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.s

CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/water_tile.cpp
CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/water_tile.cpp

CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/water_tile.cpp > CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.i

CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/tile/water_tile.cpp -o CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.s

CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o: CMakeFiles/sdlGameEngine.dir/flags.make
CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o: /home/joe/Documents/coding_projects/sdl_tutorial/src/tile_map.cpp
CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o: CMakeFiles/sdlGameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o -MF CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o.d -o CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o -c /home/joe/Documents/coding_projects/sdl_tutorial/src/tile_map.cpp

CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joe/Documents/coding_projects/sdl_tutorial/src/tile_map.cpp > CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.i

CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joe/Documents/coding_projects/sdl_tutorial/src/tile_map.cpp -o CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.s

# Object files for target sdlGameEngine
sdlGameEngine_OBJECTS = \
"CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/character.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/game.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/main.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/player.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o" \
"CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o"

# External object files for target sdlGameEngine
sdlGameEngine_EXTERNAL_OBJECTS =

sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/camera/camera.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/character.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/character_factory.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/game.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/logger.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/main.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/menu/main_menu.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/menu/menu_background.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/npc.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/player.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/tile/dirt_tile.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/tile/tile.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/tile/tile_factory.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/tile/water_tile.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/src/tile_map.cpp.o
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/build.make
sdlGameEngine: CMakeFiles/sdlGameEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable sdlGameEngine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdlGameEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sdlGameEngine.dir/build: sdlGameEngine
.PHONY : CMakeFiles/sdlGameEngine.dir/build

CMakeFiles/sdlGameEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdlGameEngine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdlGameEngine.dir/clean

CMakeFiles/sdlGameEngine.dir/depend:
	cd /home/joe/Documents/coding_projects/sdl_tutorial/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joe/Documents/coding_projects/sdl_tutorial /home/joe/Documents/coding_projects/sdl_tutorial /home/joe/Documents/coding_projects/sdl_tutorial/build /home/joe/Documents/coding_projects/sdl_tutorial/build /home/joe/Documents/coding_projects/sdl_tutorial/build/CMakeFiles/sdlGameEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sdlGameEngine.dir/depend
