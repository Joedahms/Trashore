cmake_minimum_required(VERSION 3.7)
project(sdlGameEngine VERSION 0.01 DESCRIPTION "Game engine in SDL" LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(sdlGameEngine
src/camera/camera.cpp
src/camera/camera.h

src/character/character.cpp
src/character/character_factory.cpp
src/character/character_factory.h
src/character/character.h
src/character/npc.cpp
src/character/npc.h
src/character/player.cpp
src/character/player.h

src/game.cpp
src/game.h

src/logger.cpp
src/logger.h

src/main.cpp

src/tile/dirt_tile.cpp
src/tile/dirt_tile.h
src/tile/tile.cpp
src/tile/tile_factory.cpp
src/tile/tile_factory.h
src/tile/tile.h
src/tile/water_tile.cpp
src/tile/water_tile.h
src/tile/tile_map.cpp
src/tile/tile_map.h

src/button.h
src/button.cpp

src/main_menu.h
src/main_menu.cpp

src/gameplay.h
src/gameplay.cpp

src/pause_menu.h
src/pause_menu.cpp

src/text.h
src/text.cpp

src/rectangle.h
src/rectangle.cpp

src/game_global.h
)


target_compile_features(sdlGameEngine PRIVATE cxx_std_20)

target_link_libraries(sdlGameEngine ${SDL2_LIBRARIES} SDL2_image)
target_link_libraries(sdlGameEngine SDL2_ttf)
