#include <RmlUi/Core.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <thread>

#include "GameEngine.h"
#include "GameGlobal.h"
#include "RmlUi_Platform_SDL.h"
#include "RmlUi_Renderer_SDL.h"
#include "states/State.h"

EngineState GameEngine::currentState = EngineState::MAIN_MENU;

GameEngine::GameEngine(const char* windowTitle,
                       const int screenWidth,
                       const int screenHeight,
                       const bool fullscreen)
    : logger("game_engine.txt") {
  this->logger.log("Constructing game engine");

  initializeEngine(windowTitle, screenWidth, screenHeight, fullscreen);

  this->mainMenu = std::make_unique<MainMenu>(this->gameGlobal);
  this->gameplay = std::make_unique<Gameplay>(this->gameGlobal);

  this->engineState = this->mainMenu.get();

  gameIsRunning = true;
  this->logger.log("Engine is constructed and now running");
}

void GameEngine::start() {
  const auto msPerFrame = std::chrono::milliseconds(16);

  while (gameIsRunning) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    handleEvents();
    handleStateChange();
    update();
    renderState();

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    auto sleepDuration =
        std::chrono::duration_cast<std::chrono::milliseconds>(start + msPerFrame - now);
    std::this_thread::sleep_for(sleepDuration);
  }

  clean();
}

void GameEngine::setCurrentState(const EngineState newEngineState) {
  currentState = newEngineState;
}

void GameEngine::initializeEngine(const char* windowTitle,
                                  const int screenWidth,
                                  const int screenHeight,
                                  const bool fullscreen) {
  this->logger.log("Initializing engine");
  int windowFlags = 0;
  if (fullscreen) {
    windowFlags = SDL_WINDOW_FULLSCREEN;
  }

  try {
    SDL_CreateWindowAndRenderer(windowTitle, screenWidth, screenHeight, windowFlags,
                                &this->gameGlobal.window, &this->gameGlobal.renderer);
    this->logger.log("SDL game window and renderer created");
  } catch (...) {
    std::cerr << "Error setting up SDL game window and renderer";
    exit(1);
  }

  if (const bool sdlInitReturn = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
      !sdlInitReturn) {
    std::cerr << "Failed to initialize engine";
    exit(1);
  }

  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 255, 255, 255, 255);

  if (const int ttfInitReturn = TTF_Init(); ttfInitReturn == -1) {
    std::cerr << "Failed to initialize TTF";
    exit(1);
  }

  this->systemInterface = std::make_unique<SystemInterface_SDL>();
  this->renderInterface =
      std::make_unique<RenderInterface_SDL>(this->gameGlobal.renderer);

  Rml::SetSystemInterface(this->systemInterface.get());
  Rml::SetRenderInterface(this->renderInterface.get());
  Rml::Initialise();

  if (!Rml::LoadFontFace("../fonts/16020_FUTURAM.ttf")) {
    std::cerr << "Failed to load font";
  }

  int windowWidth;
  int windowHeight;
  SDL_GetWindowSize(this->gameGlobal.window, &windowWidth, &windowHeight);

  this->gameGlobal.rmlContext =
      Rml::CreateContext("default", Rml::Vector2i(windowWidth, windowHeight));
  if (!this->gameGlobal.rmlContext) {
    Rml::Shutdown();
    std::cerr << "Error creating rmlContext";
  }

  this->logger.log("Engine initialized");
}

void GameEngine::handleStateChange() {
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
}

void GameEngine::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      gameIsRunning = false;
    }

    // Pass events to RmlUi
    RmlSDL::InputEventHandler(this->gameGlobal.rmlContext, this->gameGlobal.window,
                              event);
  }
  engineState->handleEvents(gameIsRunning);
}

void GameEngine::update() const {
  this->gameGlobal.rmlContext->Update();
  this->engineState->update();
}

void GameEngine::renderState() const { this->engineState->render(); }

void GameEngine::clean() const {
  Rml::Shutdown();
  SDL_DestroyWindow(this->gameGlobal.window);
  SDL_DestroyRenderer(this->gameGlobal.renderer);
  SDL_Quit();
  this->logger.log("GameEngine cleaned");
}
