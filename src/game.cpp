#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <iostream>

#include "camera/camera.h"
#include "character/character.h"
#include "character/character_factory.h"
#include "character/npc.h"
#include "game.h"
#include "game_global.h"
#include "logger.h"

/**
 * @function: Game
 *
 * Construct the game object and set up relevant components
 *
 * @param windowTitle - Title of the game window
 * @param windowXPosition - X position of the game window
 * @param windowYPostition - Y position of the game window
 * @param screenWidth - Width of the game window
 * @param screenHeight - Height of the game window
 * @param fullscreen - Whether or not the game window should be fullscreen
 * @param gameGlobal - Global game variables
 *
 * @output none
 */
Game::Game(const char* windowTitle,
           int windowXPosition,
           int windowYPosition,
           int screenWidth,
           int screenHeight,
           bool fullscreen,
           struct GameGlobal gameGlobal) {
  writeToLogFile(gameGlobal.logFile, "Constructing game...");

  this->gameGlobal = gameGlobal;
  this->gameGlobal.window =
      setupWindow(windowTitle, windowXPosition, windowYPosition, screenWidth,
                  screenHeight, fullscreen); // Setup the SDL game window

  initializeSdl(this->gameGlobal.window);

  // Create NPC
  std::unique_ptr<Character> npc = characterFactory->create(characterId::NPC);
  npcVector.emplace_back(std::move(npc));

  // Initialize states
  this->mainMenu  = std::make_unique<MainMenu>(this->gameGlobal);
  this->gameplay  = std::make_unique<Gameplay>(this->gameGlobal);
  this->pauseMenu = std::make_unique<PauseMenu>(this->gameGlobal);

  this->previousTicks = SDL_GetTicks(); // First physics tick count
  gameIsRunning       = true;
  writeToLogFile(this->gameGlobal.logFile, "Game constructed");
}

/**
 * @function: setupWindow
 * Purpose: Setup the SDL game window
 * Input:
 * - The name of the window
 * - The X position of the window on the user's screen
 * - The Y position of the window on the user's screen
 * - The width of the screen in pixels
 * - The height of the screen in pixels
 * - Whether or not the game window should be fullscreen
 * Output:
 * - Pointer to the game window
 */
SDL_Window* Game::setupWindow(const char* windowTitle,
                              int windowXPosition,
                              int windowYPosition,
                              int screenWidth,
                              int screenHeight,
                              bool fullscreen) {
  writeToLogFile(this->gameGlobal.logFile, "Creating SDL game window...");

  // Check for fullscreen
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  // Create the SDL window
  try {
    return SDL_CreateWindow(windowTitle, windowXPosition, windowYPosition, screenWidth,
                            screenHeight, flags);
  } catch (...) {
    writeToLogFile(this->gameGlobal.logFile, "Error setting up SDL game window");
    exit(1);
  }
  writeToLogFile(this->gameGlobal.logFile, "SDL game window created");
}

/**
 * @function: initializeSdl
 * Purpose: Setup SDL, the renderer, and TTF
 * Input:
 * - The game window
 * Output: None
 */
void Game::initializeSdl(SDL_Window* window) {
  // Initialize SDL
  writeToLogFile(this->gameGlobal.logFile, "Initializing SDL...");
  try {
    int sdlInitReturn = SDL_Init(SDL_INIT_EVERYTHING);
    if (sdlInitReturn != 0) {
      throw;
    }
  } catch (...) {
    writeToLogFile(this->gameGlobal.logFile, "Failed to initialize SDL");
    exit(1);
  }
  writeToLogFile(this->gameGlobal.logFile, "SDL initialized");

  // Create renderer
  writeToLogFile(this->gameGlobal.logFile, "Creating renderer");
  try {
    this->gameGlobal.renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->gameGlobal.renderer) {
      throw;
    }
    SDL_SetRenderDrawColor(this->gameGlobal.renderer, 255, 255, 255, 255);
  } catch (...) {
    writeToLogFile(this->gameGlobal.logFile, "Error creating renderer");
    exit(1);
  }
  writeToLogFile(this->gameGlobal.logFile, "Renderer created");

  // Initialize TTF
  writeToLogFile(this->gameGlobal.logFile, "Initializing TTF...");
  try {
    int ttfInitReturn = TTF_Init();
    if (ttfInitReturn == -1) {
      throw;
    }
  } catch (...) {
    writeToLogFile(this->gameGlobal.logFile, "Failed to initialize TTF");
    exit(1);
  }
  writeToLogFile(this->gameGlobal.logFile, "TTF initialized");
}

/**
 * @function: checkState
 * Purpose: Check which state the game is in. If there was a state switch and the current
 * state has not been entered before, run its enter method. Input:
 * - None
 * Output: None
 */
void Game::checkState() {
  std::cout << this->state << std::endl;
  switch (this->state) {
  case 0: // Main menu
    break;

  case 1: // Gameplay
    if (!this->gameplay->getStateEntered()) {
      this->gameplay->enterGameplay();
    }
    break;

  case 2: // Pause menu
    break;

  default:
    break;
  }
}

/**
 * @function: handleEvents
 * Purpose: Check the current state, and call that state's handle events method
 * Input:
 * - None
 * Output: None
 */
void Game::handleEvents() {
  switch (this->state) {
  case 0: // Main menu
    this->state = this->mainMenu->handleEvents(&this->gameIsRunning);
    break;

  case 1: // Gameplay
    this->state = this->gameplay->handleEvents(&this->gameIsRunning);
    break;

  case 2: // Pause menu
    this->state = this->pauseMenu->handleEvents(&this->gameIsRunning);
    break;

  default:
    break;
  }
}

/**
 * @function: checkKeystates
 * Purpose: Check the current state of the game and call that state's method to check the
 * key states Input:
 * - None
 * Output: None
 */
void Game::checkKeystates() {
  switch (this->state) {
  case 0: // Main menu
    break;

  case 1: // Gameplay
    this->state = this->gameplay->checkKeystates();
    break;

  case 2: // Pause menu
    break;

  default:
    break;
  }
}

/**
 * @function: update
 * Purpose: First check if it's time to update. If it is, reset the time since last
 * update. Then check the current state and call that state's function to update Input:
 * - None
 * Output: None
 */
void Game::update() {
  // Calculate values used to check if it's time to update

  // Ticks at this very moment
  this->currentTicks = SDL_GetTicks();

  // Time since this funnction was last executed
  this->deltaTime = this->currentTicks - this->previousTicks;

  // Add the time since the function was last executed to the time the game was last
  // updated
  this->totalDeltaTime += this->deltaTime;

  this->previousTicks = this->currentTicks;

  if (this->totalDeltaTime >= 128) { // Check if it is time to update
    this->totalDeltaTime = 0;        // Reset time since last update
    switch (this->state) {           // Check current state
    case 0:                          // Main menu
      break;

    case 1: // Gameplay
      this->gameplay->update();
      break;

    case 2: // Pause menu
      break;

    default:
      break;
    }
  }
}

/**
 * @function: renderState
 * Purpose: Check current state and call that state's function to render
 * Input:
 * - None
 * Output: None
 */
void Game::renderState() {
  switch (this->state) {
  case 0: // Main menu
    this->mainMenu->render();
    break;

  case 1: // Gameplay
    this->gameplay->render();
    break;

  case 2: // Pause menu
    this->pauseMenu->render();
    break;

  default:
    break;
  }
}

/**
 * @function: clean
 * Purpose: Frees SDL resources and quits
 * Input:
 * - None
 * Output: None
 */
void Game::clean() {
  SDL_DestroyWindow(this->gameGlobal.window);
  SDL_DestroyRenderer(this->gameGlobal.renderer);
  SDL_Quit();
  writeToLogFile(this->gameGlobal.logFile, "Game cleaned");
}
