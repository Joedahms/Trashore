cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-14")

project(sdlGameEngine DESCRIPTION "Game engine in SDL2" LANGUAGES CXX)

# Set build type and C++ standard
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags (only compiler flags, not linker flags)
set(CXXFLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

# Find required packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Include directories for all libraries
include_directories(
  ${SDL2_INCLUDE_DIRS} 
  ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Add executable with all source files
add_executable(sdlGameEngine
  src/main.cpp
  src/logger.cpp

  src/log_files.cpp
  src/engine_state.cpp
  src/game_engine.cpp
  src/sdl_debug.cpp
  src/game_global.cpp

  src/elements/container.cpp
  src/elements/element.cpp
  src/elements/composite_element.cpp
  src/elements/button.cpp
  src/elements/text.cpp
  src/elements/loading_bar.cpp

  src/elements/flappy_food/flappy_food.cpp
  src/elements/flappy_food/bird.cpp
  src/elements/flappy_food/obstacle.cpp
  src/elements/flappy_food/obstacle_pair.cpp

  src/states/state.cpp
  src/states/main_menu.cpp
  src/states/gameplay.cpp

  src/camera/camera.cpp

  src/character/character.cpp 
  src/character/character_factory.cpp 
  src/character/npc.cpp 
  src/character/player.cpp 

  src/tile/dirt_tile.cpp
  src/tile/tile.cpp
  src/tile/tile_factory.cpp
  src/tile/tile_map.cpp
  src/tile/water_tile.cpp
)

# Link all libraries
target_link_libraries(sdlGameEngine
  ${SDL2_LIBRARIES}
  SDL2_image
  SDL2_ttf
)
