#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <iostream>
#include <thread>

#include "game_engine.h"
#include "game_global.h"
#include "states/state.h"

/**
 * @param windowTitle Title of the game window
 * @param windowXPosition X position of the game window
 * @param windowYPostition Y position of the game window
 * @param screenWidth Width of the game window in pixels
 * @param screenHeight Height of the game window in pixels
 * @param fullscreen Whether or not the game window should be fullscreen
 * @param context The zeroMQ context with which to create sockets with
 */
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

/**
 * Setup the SDL game window.
 *
 * @param windowTitle The name of the window. Is what is gameed on the top bezel of
 * the window when the game is running.
 * @param windowXPosition The X position of the window on the user's screen.
 * @param windowYPosition The Y position of the window on the user's screen.
 * @param screenWidth The width of the screen in pixels.
 * @param screenHeight The height of the screen in pixels.
 * @param fullscreen Whether or not the game window should be fullscreen.
 * @return Pointer to the SDL game window.
 */
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

/**
 * Setup SDL, the renderer, and TTF. Renderer is part of the global game objects.
 *
 * @param window The SDL game window
 * @return None
 */
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

/**
 * Check the current state, and call that state's handle events method.
 *
 * @param engineToDisplay Pipe from the game engine to the game
 * @param displayToEngine Pipe from the display to the displayEngine
 * @return None
 */
void GameEngine::handleEvents() { this->engineState->handleEvents(this->gameIsRunning); }

/**
 * Not implemented but may want to add:
 * First check if it's time to update. If it is, reset the time since last
 * update.
 *
 * @param None
 * @return None
 */
void GameEngine::update() { this->engineState->update(); }

/**
 * Check current state and call that state's function to render.
 *
 * @param None
 * @return None
 */
void GameEngine::renderState() { this->engineState->render(); }

/**
 * Free SDL resources and quit.
 *
 * @param None
 * @return None
 */
void GameEngine::clean() {
  SDL_DestroyWindow(this->gameGlobal.window);
  SDL_DestroyRenderer(this->gameGlobal.renderer);
  SDL_Quit();
  this->logger.log("GameEngine cleaned");
}
