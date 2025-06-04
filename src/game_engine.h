#ifndef DISPLAY_ENGINE_H
#define DISPLAY_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include <vector>
#include <zmqpp/zmqpp.hpp>

#include "logger.h"

#include "states/gameplay.h"
#include "states/main_menu.h"

#include "engine_state.h"
#include "game_global.h"

class GameEngine {
public:
  GameEngine(const char* windowTitle,
             const int windowXPosition,
             const int windowYPosition,
             const int screenWidth,
             const int screenHeight,
             const bool fullscreen);
  void start();

private:
  Logger logger;
  GameGlobal gameGlobal;
  State* engineState       = nullptr;
  EngineState currentState = EngineState::MAIN_MENU;
  bool gameIsRunning       = false;

  // States
  std::unique_ptr<MainMenu> mainMenu;
  std::unique_ptr<Gameplay> gameplay;

  SDL_Window* setupWindow(const char* windowTitle,
                          int windowXPosition,
                          int windowYPosition,
                          int screenWidth,
                          int screenHeight,
                          bool fullscreen);
  void initializeEngine(SDL_Window* window);

  void handleStateChange();
  void handleEvents();
  void update();
  void renderState();
  void clean();
};

#endif
