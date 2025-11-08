#include <SDL3/SDL.h>
#include <utility>

#include "Element.h"

Element::Element(const GameGlobal& gameGlobal,
                 std::string logFile,
                 const SDL_FRect boundaryRectangle)
    : gameGlobal(gameGlobal), logFile(std::move(logFile)) {
  this->logger         = std::make_unique<Logger>(this->logFile);
  this->previousUpdate = std::chrono::steady_clock::now();
  setupPosition(boundaryRectangle);
}

void Element::render() const {
  if (this->hasBorder) {
    renderBorder();
  }
}

/**
 * Ensure that the positioning of the element is correct. Make sure that if need be, it is
 * centered with respect to its parent (if it has one) and that it is in the correct
 * position relative to its parent (if it has one).
 */
void Element::update() {
  if (parent) {
    hasParentUpdate();
  }
}

/**
 * Updates to perform if the element has a parent. Checks centering within parent and
 * ensures the position of the element is correct giving its current position relative to
 * parent.
 */
void Element::hasParentUpdate() {
  if (this->centerWithinParent) {
    if (checkCenterVertical() == false) {
      centerVertical();
    }
    if (checkCenterHorizontal() == false) {
      centerHorizontal();
    }
  }
  else if (this->centerVerticalWithinParent && checkCenterVertical() == false) {
    centerVertical();
  }
  else if (this->centerHorizontalWithinParent && checkCenterHorizontal() == false) {
    centerHorizontal();
  }
}

void Element::updatePosition() {
  const SDL_FRect parentBoundaryRectangle = parent->getBoundaryRectangle();
  this->boundaryRectangle.x =
      parentBoundaryRectangle.x + this->positionRelativeToParent.x;
  this->boundaryRectangle.y =
      parentBoundaryRectangle.y + this->positionRelativeToParent.y;
}

std::string Element::getContent() const { return "no content"; }

void Element::setParent(Element* newParent) { this->parent = newParent; }

void Element::setPositionRelativeToParent(const SDL_FPoint& relativePosition) {
  this->positionRelativeToParent = relativePosition;
}

SDL_FPoint Element::getPositionRelativeToParent() const {
  return this->positionRelativeToParent;
}

SDL_FRect Element::getBoundaryRectangle() const { return this->boundaryRectangle; }

void Element::setBoundaryRectangle(const SDL_FRect newBoundaryRectangle) {
  this->boundaryRectangle = newBoundaryRectangle;
};

void Element::setCentered() { this->centerWithinParent = true; }

/**
 * Centering vertically means centering on the y axis.
 */
void Element::setCenteredVertical() { this->centerVerticalWithinParent = true; }

bool Element::checkCenterVertical() const {
  bool centered = false;
  if (this->positionRelativeToParent.y ==
      (this->parent->boundaryRectangle.h / 2 - this->boundaryRectangle.h / 2)) {
    centered = true;
  }
  return centered;
}
void Element::centerVertical() {
  this->positionRelativeToParent.y =
      (this->parent->boundaryRectangle.h / 2 - this->boundaryRectangle.h / 2);
}

/**
 * Centering horizontally means centering on the x axis.
 */
void Element::setCenteredHorizontal() { this->centerHorizontalWithinParent = true; }
bool Element::checkCenterHorizontal() const {
  bool centered = false;
  if (this->positionRelativeToParent.x ==
      (this->parent->boundaryRectangle.w / 2 - this->boundaryRectangle.w / 2)) {
    centered = true;
  }
  return centered;
}
void Element::centerHorizontal() {
  this->positionRelativeToParent.x =
      ((this->parent->boundaryRectangle.w - this->boundaryRectangle.w) / 2);
}

/**
 * Check if the mouse is over the element.
 */
bool Element::checkMouseHovered() const {
  SDL_FPoint mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  if (SDL_PointInRectFloat(&mousePosition, &this->boundaryRectangle)) {
    return true;
  }
  return false;
}

/**
 * Add a border to an element.
 *
 * @param newBorderThickness How many pixels thick the border should be
 */
void Element::addBorder(const int& newBorderThickness) {
  this->hasBorder       = true;
  this->borderThickness = newBorderThickness;
}

/**
 * Render a border around an object. Draws 4 lines on each side of the element's
 * boundaryRectangle.
 */
void Element::renderBorder() const {
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 255, 255, 255, 255);
  // Draw the top border
  for (int i = 0; i < borderThickness; i++) {
    SDL_RenderLine(this->gameGlobal.renderer,
                   this->positionRelativeToParent.x - i, // Start X
                   this->positionRelativeToParent.y - i, // Start Y
                   this->positionRelativeToParent.x + this->boundaryRectangle.w +
                       i,                                 // End X
                   this->positionRelativeToParent.y - i); // End Y
  }

  // Draw the bottom border
  for (int i = 0; i < borderThickness; i++) {
    SDL_RenderLine(
        this->gameGlobal.renderer,
        this->positionRelativeToParent.x - i,                              // Start X
        this->positionRelativeToParent.y + this->boundaryRectangle.h + i,  // Start Y
        this->positionRelativeToParent.x + this->boundaryRectangle.w + i,  // End X
        this->positionRelativeToParent.y + this->boundaryRectangle.h + i); // End Y
  }

  // Draw the left border
  for (int i = 0; i < borderThickness; i++) {
    SDL_RenderLine(this->gameGlobal.renderer,
                   this->positionRelativeToParent.x - i, // Start X
                   this->positionRelativeToParent.y - i, // Start Y
                   this->positionRelativeToParent.x - i, // End X
                   this->positionRelativeToParent.y + this->boundaryRectangle.h +
                       i); // End Y
  }

  // Draw the right border
  for (int i = 0; i < borderThickness; i++) {
    SDL_RenderLine(
        this->gameGlobal.renderer,
        this->positionRelativeToParent.x + this->boundaryRectangle.w + i,  // Start X
        this->positionRelativeToParent.y - i,                              // Start Y
        this->positionRelativeToParent.x + this->boundaryRectangle.w + i,  // End X
        this->positionRelativeToParent.y + this->boundaryRectangle.h + i); // End Y
  }
}

void Element::setupPosition(const SDL_FRect& newBoundaryRectangle) {
  this->boundaryRectangle          = newBoundaryRectangle;
  this->positionRelativeToParent.x = newBoundaryRectangle.x;
  this->positionRelativeToParent.y = newBoundaryRectangle.y;

  if (parent) {
    SDL_FRect parentRectangle = this->parent->getBoundaryRectangle();
    this->boundaryRectangle.x = parentRectangle.x + this->positionRelativeToParent.x;
    this->boundaryRectangle.y = parentRectangle.y + this->positionRelativeToParent.y;
  }
}

Velocity Element::getVelocity() const { return this->velocity; }
void Element::setVelocity(const Velocity newVelocity) { this->velocity = newVelocity; }
Acceleration Element::getAcceleration() const { return this->acceleration; }
void Element::setAcceleration(Acceleration newAcceleration) {
  this->acceleration = newAcceleration;
}

int Element::getBorderThickness() const { return this->borderThickness; }
bool Element::getScreenBoundX() const { return this->screenBoundX; }
bool Element::getScreenBoundY() const { return this->screenBoundY; }

void Element::addBoundaryRectangle(std::vector<SDL_FRect>& boundaryRectangles) const {
  boundaryRectangles.push_back(this->boundaryRectangle);
}