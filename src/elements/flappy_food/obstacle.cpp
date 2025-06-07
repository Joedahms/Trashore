#include "obstacle.h"

Obstacle::Obstacle(const GameGlobal& gameGlobal,
                   const std::string& logFile,
                   const SDL_Rect boundaryRectangle)
    : Element(gameGlobal, logFile, boundaryRectangle) {
  this->screenBoundX = false;
  this->canCollide   = true;
}

void Obstacle::handleEvent(const SDL_Event& event) {}

void Obstacle::render() const {
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(this->gameGlobal.renderer, &this->boundaryRectangle);
}
