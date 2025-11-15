#include <cassert>
#include <utility>

#include "../GameGlobal.h"
#include "State.h"

State::State(const GameGlobal& gameGlobal, std::string logFile)
    : gameGlobal(gameGlobal), logFile(std::move(logFile)) {
  this->logger        = std::make_unique<Logger>(this->logFile);
  this->windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  assert(windowSurface != nullptr);
  SDL_FRect rootRectangle = {0, 0, static_cast<float>(windowSurface->w),
                             static_cast<float>(windowSurface->h)};
  this->rootElement =
      std::make_shared<Container>(this->gameGlobal, this->logFile, rootRectangle);
}

void State::handleEvents(bool& displayIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_EVENT_QUIT) {
      displayIsRunning = false;
      break;
    }
    this->rootElement->handleEvent(event);
  }
}

void State::update() { this->rootElement->update(); }