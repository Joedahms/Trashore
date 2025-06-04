#include "loading_bar.h"

LoadingBar::LoadingBar(const struct DisplayGlobal& displayGlobal,
                       const std::string& logFile,
                       const SDL_Rect boundaryRectangle,
                       const int& borderThickness,
                       const float& totalTimeSeconds,
                       const float& updatePeriodMs)
    : Element(displayGlobal, logFile, boundaryRectangle),
      totalTimeSeconds(totalTimeSeconds), updatePeriodMs(updatePeriodMs) {
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
 *
 * @param None
 * @return None
 */
void LoadingBar::update() {
  if (parent) {
    hasParentUpdate();
  }

  float pixelsPerMs =
      static_cast<float>(this->boundaryRectangle.w) / (this->totalTimeSeconds * 1000);
  this->pixelsPerUpdate = pixelsPerMs * this->updatePeriodMs;

  // Get time since last update
  this->currentUpdate = std::chrono::steady_clock::now();
  std::chrono::milliseconds updateDifference;
  updateDifference = std::chrono::duration_cast<std::chrono::milliseconds>(
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

/**
 * If the mouse is clicked over the loading bar, it is held and no longer centered in any
 * way.
 *
 * @param None
 * @return None
 */
void LoadingBar::handleMouseDown() {
  if (checkMouseHovered()) {
    this->held = true;

    this->centerWithinParent           = false;
    this->centerVerticalWithinParent   = false;
    this->centerHorizontalWithinParent = false;
  }
  else {
    if (!fixed) {
      this->velocity.y = -5;
    }
  }
}

/**
 * If the mouse is moved while the loading bar is held, the loading bar should follow the
 * mouse. The loading bar is drug by the mouse.
 *
 * @param event The SDL_MOUSEMOTION event to handle
 * @return None
 */
void LoadingBar::handleMouseMotion(const SDL_Event& event) {
  if (this->held) {
    this->fixed = false;

    this->velocity.x += event.motion.x - this->previousMotion.x;
    this->velocity.y += event.motion.y - this->previousMotion.y;
    this->previousMotion.x = event.motion.x;
    this->previousMotion.y = event.motion.y;
  }
  this->previousMotion.x = event.motion.x;
  this->previousMotion.y = event.motion.y;
}

void LoadingBar::handleMouseUp() { this->held = false; }

void LoadingBar::render() const {
  // Border
  if (this->hasBorder) {
    renderBorder();
  }

  // Bar
  SDL_SetRenderDrawColor(this->displayGlobal.renderer, barColor.r, barColor.g, barColor.b,
                         barColor.a);
  SDL_RenderFillRect(this->displayGlobal.renderer, &this->barRectangle);
}
