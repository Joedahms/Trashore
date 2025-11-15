#ifndef DISPLAY_ENGINE_H
#define DISPLAY_ENGINE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Logger.h"

#include "states/gameplay/Gameplay.h"
#include "states/main_menu/MainMenu.h"

#include "EngineState.h"
#include "GameGlobal.h"
#include "RmlUi_Platform_SDL.h"
#include "RmlUi_Renderer_SDL.h"

class GameEngine {
public:
  GameEngine(const char* windowTitle, int screenWidth, int screenHeight, bool fullscreen);
  void start();

  static void setCurrentState(EngineState newEngineState);

  static inline bool gameIsRunning = false;

private:
  Logger logger;
  GameGlobal gameGlobal{};
  State* engineState = nullptr;
  static EngineState currentState;

  std::unique_ptr<SystemInterface_SDL> systemInterface;
  std::unique_ptr<RenderInterface_SDL> renderInterface;

  std::unique_ptr<MainMenu> mainMenu;
  std::unique_ptr<Gameplay> gameplay;

  void initializeEngine(const char* windowTitle,
                        int screenWidth,
                        int screenHeight,
                        bool fullscreen);

  void handleStateChange();
  void handleEvents();
  void update() const;
  void renderState() const;
  void clean() const;
};

#endif
