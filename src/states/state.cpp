#include <cassert>
#include <iostream>

#include "../game_global.h"
#include "state.h"

State::State(const GameGlobal& gameGlobal,
             const std::string& logFile,
             const EngineState& state)
    : gameGlobal(gameGlobal), logFile(logFile), defaultState(state), currentState(state) {
  this->logger        = std::make_unique<Logger>(this->logFile);
  this->windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  assert(windowSurface != NULL);
  SDL_Rect rootRectangle = {0, 0, windowSurface->w, windowSurface->h};
  this->rootElement =
      std::make_shared<Container>(this->gameGlobal, this->logFile, rootRectangle);
}

void State::handleEvents(bool& displayIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) { // While there are events in the queue
    if (event.type == SDL_QUIT) {
      displayIsRunning = false;
      break;
    }
    else {
      this->rootElement->handleEvent(event);
    }
  }
}

void State::update() { this->rootElement->update(); }

void State::enter() { this->currentState = this->defaultState; }

EngineState State::getCurrentState() { return this->currentState; }

void State::setCurrentState(EngineState currentState) {
  this->currentState = currentState;
}

bool State::checkStateChange() {
  if (this->currentState != this->defaultState) {
    return true;
  }
  return false;
}
