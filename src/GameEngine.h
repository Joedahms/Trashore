#ifndef DISPLAY_ENGINE_H
#define DISPLAY_ENGINE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Logger.h"

#include "states/Gameplay.h"
#include "states/MainMenu.h"

#include "EngineState.h"
#include "GameGlobal.h"

class GameEngine {
public:
  GameEngine(const char* windowTitle,
             int windowXPosition,
             int windowYPosition,
             int screenWidth,
             int screenHeight,
             bool fullscreen);
  void start();

private:
  Logger logger;
  GameGlobal gameGlobal{};
  State* engineState       = nullptr;
  EngineState currentState = EngineState::MAIN_MENU;
  bool gameIsRunning       = false;

  std::unique_ptr<MainMenu> mainMenu;
  std::unique_ptr<Gameplay> gameplay;

  SDL_Window* setupWindow(const char* windowTitle,
                          int windowXPosition,
                          int windowYPosition,
                          int screenWidth,
                          int screenHeight,
                          bool fullscreen) const;
  void initializeEngine(SDL_Window* window);

  void handleStateChange();
  void handleEvents();
  void update() const;
  void renderState() const;
  void clean() const;
};

#endif
