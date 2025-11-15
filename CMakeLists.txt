cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-14")

project(sdlGameEngine DESCRIPTION "Game engine in SDL3" LANGUAGES CXX)

# Set build type and C++ standard
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags (only compiler flags, not linker flags)
set(CXXFLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

set(RMLUI_BACKEND_PATH Backends)

add_library(rmlui_backend_SDL_SDLrenderer INTERFACE)

target_sources(rmlui_backend_SDL_SDLrenderer INTERFACE
        ${RMLUI_BACKEND_PATH}/RmlUi_Platform_SDL.cpp
        ${RMLUI_BACKEND_PATH}/RmlUi_Renderer_SDL.cpp
)

# Find required packages
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(RmlUi REQUIRED)

# Include directories for all libraries
include_directories(
        ${SDL3_INCLUDE_DIRS}
        ${SDL3_IMAGE_INCLUDE_DIRS}
)

target_include_directories(rmlui_backend_SDL_SDLrenderer INTERFACE ${RMLUI_BACKEND_PATH})
target_compile_definitions(rmlui_backend_SDL_SDLrenderer INTERFACE
        RMLUI_SDL_VERSION_MAJOR=3  # Or 2 for SDL2
)

# Add executable with all source files
add_executable(sdlGameEngine
        src/main.cpp
        src/Logger.cpp

        src/LogFiles.cpp
        src/EngineState.cpp
        src/GameEngine.cpp
        src/SdlDebug.cpp
        src/GameGlobal.cpp

        src/elements/Container.cpp
        src/elements/Element.cpp
        src/elements/CompositeElement.cpp
        src/elements/Button.cpp
        src/elements/Text.cpp
        src/elements/LoadingBar.cpp

        #src/elements/flappy_food/flappy_food.cpp
        #src/elements/flappy_food/bird.cpp
        #src/elements/flappy_food/obstacle.cpp
        #src/elements/flappy_food/obstacle_pair.cpp

        src/states/State.cpp
        src/states/main_menu/MainMenu.cpp
        src/states/gameplay/Gameplay.cpp

        src/camera/Camera.cpp

        src/character/Character.cpp
        src/character/CharacterFactory.cpp
        src/character/Npc.cpp
        src/character/Player.cpp

        src/tile/DirtTile.cpp
        src/tile/Tile.cpp
        src/tile/TileFactory.cpp
        src/tile/TileMap.cpp
        src/tile/WaterTile.cpp
        src/states/main_menu/MainMenuRmlEventListener.cpp
        src/states/main_menu/MainMenuRmlEventListener.h
        src/states/main_menu/MainMenuRmlEventHandler.cpp
        src/states/main_menu/MainMenuRmlEventHandler.h
)

# Link all libraries
target_link_libraries(sdlGameEngine
        ${SDL3_LIBRARIES}
        SDL3_image
        SDL3_ttf
        RmlUi::RmlUi
        rmlui_backend_SDL_SDLrenderer
)
