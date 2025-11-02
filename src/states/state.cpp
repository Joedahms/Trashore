#include <cassert>
#include <iostream>
#include <utility>

#include "../game_global.h"
#include "state.h"

State::State(const GameGlobal& gameGlobal,
             std::string logFile,
             const EngineState& currentState)
    : gameGlobal(gameGlobal), logFile(std::move(logFile)), defaultState(currentState),
      currentState(currentState) {
  this->logger        = std::make_unique<Logger>(this->logFile);
  this->windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  assert(windowSurface != nullptr);
  SDL_Rect rootRectangle = {0, 0, windowSurface->w, windowSurface->h};
  this->rootElement =
      std::make_shared<Container>(this->gameGlobal, this->logFile, rootRectangle);
}

void State::handleEvents(bool& displayIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      displayIsRunning = false;
      break;
    }
    this->rootElement->handleEvent(event);
  }
}

void State::update() { this->rootElement->update(); }

void State::enter() { this->currentState = this->defaultState; }

EngineState State::getCurrentState() const { return this->currentState; }

void State::setCurrentState(const EngineState newCurrentState) {
  this->currentState = newCurrentState;
}

bool State::checkStateChange() const {
  if (this->currentState != this->defaultState) {
    return true;
  }
  return false;
}
