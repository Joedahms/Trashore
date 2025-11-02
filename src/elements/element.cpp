#include <SDL2/SDL.h>
#include <iostream>
#include <utility>

#include "element.h"

Element::Element(const GameGlobal& gameGlobal,
                 std::string logFile,
                 const SDL_Rect boundaryRectangle)
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
  const SDL_Rect parentBoundaryRectangle = parent->getBoundaryRectangle();
  this->boundaryRectangle.x =
      parentBoundaryRectangle.x + this->positionRelativeToParent.x;
  this->boundaryRectangle.y =
      parentBoundaryRectangle.y + this->positionRelativeToParent.y;
}

std::string Element::getContent() const { return "no content"; }

void Element::setParent(Element* newParent) { this->parent = newParent; }

void Element::setPositionRelativeToParent(const SDL_Point& relativePosition) {
  this->positionRelativeToParent = relativePosition;
}

SDL_Point Element::getPositionRelativeToParent() const {
  return this->positionRelativeToParent;
}

SDL_Rect Element::getBoundaryRectangle() const { return this->boundaryRectangle; }

void Element::setBoundaryRectangle(SDL_Rect newBoundaryRectangle) {
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
  SDL_Point mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  if (SDL_PointInRect(&mousePosition, &this->boundaryRectangle)) {
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
    SDL_RenderDrawLine(this->gameGlobal.renderer,
                       this->positionRelativeToParent.x - i, // Start X
                       this->positionRelativeToParent.y - i, // Start Y
                       this->positionRelativeToParent.x + this->boundaryRectangle.w +
                           i,                                 // End X
                       this->positionRelativeToParent.y - i); // End Y
  }

  // Draw the bottom border
  for (int i = 0; i < borderThickness; i++) {
    SDL_RenderDrawLine(
        this->gameGlobal.renderer,
        this->positionRelativeToParent.x - i,                              // Start X
        this->positionRelativeToParent.y + this->boundaryRectangle.h + i,  // Start Y
        this->positionRelativeToParent.x + this->boundaryRectangle.w + i,  // End X
        this->positionRelativeToParent.y + this->boundaryRectangle.h + i); // End Y
  }

  // Draw the left border
  for (int i = 0; i < borderThickness; i++) {
    SDL_RenderDrawLine(this->gameGlobal.renderer,
                       this->positionRelativeToParent.x - i, // Start X
                       this->positionRelativeToParent.y - i, // Start Y
                       this->positionRelativeToParent.x - i, // End X
                       this->positionRelativeToParent.y + this->boundaryRectangle.h +
                           i); // End Y
  }

  // Draw the right border
  for (int i = 0; i < borderThickness; i++) {
    SDL_RenderDrawLine(
        this->gameGlobal.renderer,
        this->positionRelativeToParent.x + this->boundaryRectangle.w + i,  // Start X
        this->positionRelativeToParent.y - i,                              // Start Y
        this->positionRelativeToParent.x + this->boundaryRectangle.w + i,  // End X
        this->positionRelativeToParent.y + this->boundaryRectangle.h + i); // End Y
  }
}

void Element::setupPosition(const SDL_Rect& newBoundaryRectangle) {
  this->boundaryRectangle          = newBoundaryRectangle;
  this->positionRelativeToParent.x = newBoundaryRectangle.x;
  this->positionRelativeToParent.y = newBoundaryRectangle.y;

  if (parent) {
    SDL_Rect parentRectangle  = this->parent->getBoundaryRectangle();
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
bool Element::getFixed() const { return this->fixed; }
bool Element::getScreenBoundX() const { return this->screenBoundX; }
bool Element::getScreenBoundY() const { return this->screenBoundY; }

void Element::addBoundaryRectangle(std::vector<SDL_Rect>& boundaryRectangles) const {
  if (this->canCollide) {
    boundaryRectangles.push_back(this->boundaryRectangle);
  }
}

/**
 * If the element's position is not fixed in the event of a collision, check if it
 * has collided with any other element that can be collided with.
 *
 * @param boundaryRectangles Boundary rectangles for all objects that can be collided
 * with.
 */
void Element::checkCollision(std::vector<SDL_Rect>& boundaryRectangles) {
  if (!this->canCollide || this->collisionFixed) {
    return;
  }
  checkCollisionImpl(boundaryRectangles);
}

/**
 * Implementation of collision checking. Check against all other objects that can be
 * collided with. If there is a collision, adjust position so that there is no collision.
 *
 * @param boundaryRectangles Boundary rectangles for all objects that can be collided
 * with.
 */
void Element::checkCollisionImpl(const std::vector<SDL_Rect>& boundaryRectangles) {
  for (auto& possibleCollisionBoundaryRectangle : boundaryRectangles) {
    if (SDL_RectEquals(&this->boundaryRectangle, &possibleCollisionBoundaryRectangle)) {
      continue;
    }

    if (!SDL_HasIntersection(&this->boundaryRectangle,
                             &possibleCollisionBoundaryRectangle)) {
      continue;
    }
    this->hasCollided = true;

    SDL_Point overlap = calculateOverlap(possibleCollisionBoundaryRectangle);
    fixCollision(overlap, possibleCollisionBoundaryRectangle);
  }
}

/**
 * Calculate the overlap resulting from a collision between two elements.
 *
 * @param overlappingWithBoundaryRectangle The boundary rectangle of the element that this
 * element is colliding with
 * @return An SDL_Point containing the x and y dimensions of the overlap
 */
SDL_Point Element::calculateOverlap(
    const SDL_Rect overlappingWithBoundaryRectangle) const {
  SDL_Point overlap = {0, 0};

  // Right edge
  if (this->boundaryRectangle.x < overlappingWithBoundaryRectangle.x) {
    overlap.x = (this->boundaryRectangle.x + this->boundaryRectangle.w) -
                overlappingWithBoundaryRectangle.x;
  }
  // Left edge
  else {
    overlap.x = this->boundaryRectangle.x -
                (overlappingWithBoundaryRectangle.x + overlappingWithBoundaryRectangle.w);
    overlap.x = -overlap.x;
  }
  // Bottom edge
  if (this->boundaryRectangle.y < overlappingWithBoundaryRectangle.y) {
    overlap.y = (this->boundaryRectangle.y + this->boundaryRectangle.h) -
                overlappingWithBoundaryRectangle.y;
  }
  // Top edge
  else {
    overlap.y = this->boundaryRectangle.y -
                (overlappingWithBoundaryRectangle.y + overlappingWithBoundaryRectangle.h);
    overlap.y = -overlap.y;
  }

  return overlap;
}

/**
 * Undo a collision between two elements by moving this element outside of the other
 * element.
 *
 * @param overlap An SDL_Point containing the x and y dimensions of the overlap
 * @param collidedWithBoundaryRectangle The boundary rectangle of the element that this
 * element is colliding with
 */
void Element::fixCollision(const SDL_Point overlap,
                           const SDL_Rect collidedWithBoundaryRectangle) {
  if (overlap.x > 0 && overlap.y > 0) {
    if (overlap.x < overlap.y) {
      // Right
      if (this->boundaryRectangle.x < collidedWithBoundaryRectangle.x) {
        this->positionRelativeToParent.x -= overlap.x;
      }
      // Left
      else {
        this->positionRelativeToParent.x += overlap.x;
      }
    }
    else {
      // Bottom
      if (this->boundaryRectangle.y < collidedWithBoundaryRectangle.y) {
        this->positionRelativeToParent.y -= overlap.y;
      }
      // Top
      else {
        this->positionRelativeToParent.y += overlap.y;
      }
    }
    updatePosition();
  }
}

bool Element::getHasCollided() const { return this->hasCollided; }
void Element::setHasCollided(const bool collided) { this->hasCollided = collided; }

void Element::setFixed(const bool newFixed) { this->fixed = newFixed; }

void Element::setCanCollide(const bool newCanCollide) {
  this->canCollide = newCanCollide;
}

void Element::setCollisionFixed(const bool newCollisionFixed) {
  this->collisionFixed = newCollisionFixed;
}

void Element::setGravityAffected(const bool newGravityAffected) {
  this->gravityAffected = newGravityAffected;
}
