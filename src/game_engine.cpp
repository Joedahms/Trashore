#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <iostream>
#include <thread>

#include "game_engine.h"
#include "game_global.h"
#include "states/state.h"

GameEngine::GameEngine(const char* windowTitle,
                       const int windowXPosition,
                       const int windowYPosition,
                       const int screenWidth,
                       const int screenHeight,
                       const bool fullscreen)
    : logger("game_engine.txt") {
  this->logger.log("Constructing game engine");

  this->gameGlobal.window = setupWindow(windowTitle, windowXPosition, windowYPosition,
                                        screenWidth, screenHeight, fullscreen);

  initializeEngine(this->gameGlobal.window);

  this->mainMenu = std::make_unique<MainMenu>(this->gameGlobal, EngineState::MAIN_MENU);
  this->gameplay = std::make_unique<Gameplay>(this->gameGlobal, EngineState::GAMEPLAY);

  this->engineState = this->mainMenu.get();

  this->gameIsRunning = true;
  this->logger.log("Engine is constructed and now running");
}

void GameEngine::start() {
  std::chrono::milliseconds msPerFrame = std::chrono::milliseconds(16);

  while (this->gameIsRunning) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    handleEvents();
    handleStateChange();
    update();
    renderState();

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::milliseconds sleepDuration =
        std::chrono::duration_cast<std::chrono::milliseconds>(start + msPerFrame - now);
    std::this_thread::sleep_for(sleepDuration);
  }

  clean();
}

SDL_Window* GameEngine::setupWindow(const char* windowTitle,
                                    int windowXPosition,
                                    int windowYPosition,
                                    int screenWidth,
                                    int screenHeight,
                                    bool fullscreen) {
  this->logger.log("Creating SDL game window");

  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  try {
    return SDL_CreateWindow(windowTitle, windowXPosition, windowYPosition, screenWidth,
                            screenHeight, flags);
  } catch (...) {
    std::cerr << "Error setting up SDL game window";
    exit(1);
  }

  this->logger.log("SDL game window created");
}

void GameEngine::initializeEngine(SDL_Window* window) {
  this->logger.log("Initializing engine");
  int sdlInitReturn = SDL_Init(SDL_INIT_EVERYTHING);
  if (sdlInitReturn != 0) {
    std::cerr << "Failed to initialize engine";
    exit(1);
  }

  // Create renderer
  this->gameGlobal.renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!this->gameGlobal.renderer) {
    std::cerr << "Error creating renderer";
    exit(1);
  }

  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 255, 255, 255, 255);

  // Initialize TTF
  int ttfInitReturn = TTF_Init();
  if (ttfInitReturn == -1) {
    std::cerr << "Failed to initialize TTF";
    exit(1);
  }

  this->logger.log("Engine initialized");
}

void GameEngine::handleStateChange() {
  if (this->engineState->checkStateChange()) {
    this->engineState->exit();
    EngineState currentState = this->engineState->getCurrentState();

    switch (currentState) {
    case EngineState::MAIN_MENU:
      this->engineState = this->mainMenu.get();
      break;

    case EngineState::GAMEPLAY:
      this->engineState = this->gameplay.get();
      break;

    default:
      break;
    }
    this->engineState->enter();
  }
}

void GameEngine::handleEvents() { this->engineState->handleEvents(this->gameIsRunning); }

void GameEngine::update() { this->engineState->update(); }

void GameEngine::renderState() { this->engineState->render(); }

void GameEngine::clean() {
  SDL_DestroyWindow(this->gameGlobal.window);
  SDL_DestroyRenderer(this->gameGlobal.renderer);
  SDL_Quit();
  this->logger.log("GameEngine cleaned");
}
