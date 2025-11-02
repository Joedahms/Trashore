#include "LoadingBar.h"

LoadingBar::LoadingBar(const GameGlobal& gameGlobal,
                       const std::string& logFile,
                       const SDL_Rect boundaryRectangle,
                       const int& borderThickness,
                       const float& totalTimeSeconds,
                       const float& updatePeriodMs)
    : Element(gameGlobal, logFile, boundaryRectangle), totalTimeSeconds(totalTimeSeconds),
      updatePeriodMs(updatePeriodMs) {
  this->borderThickness = borderThickness;

  this->barRectangle = {this->boundaryRectangle.x + 1, this->boundaryRectangle.y, 0,
                        this->boundaryRectangle.h - 1};
  this->barColor     = {0, 255, 0, 255};

  this->previousUpdate = std::chrono::steady_clock::now();
  addBorder(this->borderThickness);

  this->canCollide = true;
}

/**
 * Loading bar slowly fills the border.
 */
void LoadingBar::update() {
  if (parent) {
    hasParentUpdate();
  }

  const float pixelsPerMs =
      static_cast<float>(this->boundaryRectangle.w) / (this->totalTimeSeconds * 1000);
  this->pixelsPerUpdate = pixelsPerMs * this->updatePeriodMs;

  // Get time since last update
  this->currentUpdate         = std::chrono::steady_clock::now();
  const auto updateDifference = std::chrono::duration_cast<std::chrono::milliseconds>(
      this->currentUpdate - this->previousUpdate);

  if (this->barRectangle.w <= this->boundaryRectangle.w) {
    if (updateDifference.count() > this->updatePeriodMs) {
      this->barRectangle.w += this->pixelsPerUpdate;
      this->previousUpdate = this->currentUpdate;
    }
  }
  else {
    this->barRectangle.w = 0;
  }

  this->barRectangle.x = this->boundaryRectangle.x + 1;
  this->barRectangle.y = this->boundaryRectangle.y + 1;
}

void LoadingBar::handleEvent(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      SDL_Quit();
    }
  }
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    handleMouseDown();
  }
  else if (event.type == SDL_MOUSEMOTION) {
    handleMouseMotion(event);
  }
  else if (event.type == SDL_MOUSEBUTTONUP) {
    handleMouseUp();
  }
}

void LoadingBar::render() const {
  if (this->hasBorder) {
    renderBorder();
  }

  SDL_SetRenderDrawColor(this->gameGlobal.renderer, barColor.r, barColor.g, barColor.b,
                         barColor.a);
  SDL_RenderFillRect(this->gameGlobal.renderer, &this->barRectangle);
}
