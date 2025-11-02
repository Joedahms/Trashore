#include "camera.h"
#include <iostream>

Camera::Camera(const GameGlobal& gameGlobal,
               const SDL_Point mapSizeTiles,
               const int initialTileSize)
    : gameGlobal(gameGlobal),
      mapSizePixels{mapSizeTiles.x * initialTileSize, mapSizeTiles.y * initialTileSize} {
  SDL_Surface const* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  this->screenSizePixels.x         = windowSurface->w;
  this->screenSizePixels.y         = windowSurface->h;

  this->initialVisibleTiles.x = this->screenSizePixels.x / initialTileSize;
  this->initialVisibleTiles.y = this->screenSizePixels.y / initialTileSize;
}

void Camera::checkBoundaries() {
  // Need to factor in the destination rectangle
  // Currently this only works if the destination rectangle is unmodified
  // If the destination rectangle x = -2 then left bound is camera x - 2
  // If the destination rectangle x = -4 then left bound is camera x - 4
  checkLeftBoundary();
  checkRightBoundary();
  checkTopBoundary();
  checkBottomBoundary();
}

void Camera::checkLeftBoundary() {
  if (this->position.x < destination.x) {
    this->position.x += 1;
    //    std::cout << "postion x: " << this->position.x << std::endl;
    //   std::cout << "destination x: " << this->destination.x << std::endl;
  }

  /*
  if (this->position.x < 0) {
    this->position.x += 1;
  }
  */
}

void Camera::checkRightBoundary() {
  if (this->position.x + this->screenSizePixels.x > this->mapSizePixels.x) {
    this->position.x -= 1;
  }
}

void Camera::checkTopBoundary() {
  if (this->position.y < 0) {
    this->position.y += 1;
  }
}

void Camera::checkBottomBoundary() {
  if (this->position.y + this->screenSizePixels.y > this->mapSizePixels.y) {
    this->position.y -= 1;
  }
}

void Camera::update() {
  // TODO: Make time stuff into function
  this->currentTicks = SDL_GetTicks64();
  this->deltaTimeMs  = this->currentTicks - this->previousTicks;
  this->totalDeltaTimeMs += this->deltaTimeMs;
  this->previousTicks = this->currentTicks;

  if (this->velocity.x != 0) {
    const float inverseVelocity = 1.0 / this->velocity.x;
    if (const float deltaTimeSeconds = totalDeltaTimeMs / 1000.0;
        deltaTimeSeconds >= fabsf(inverseVelocity)) {
      this->totalDeltaTimeMs = 0;
      if (inverseVelocity > 0) {
        this->position.x += 1;
      }
      else {
        this->position.x -= 1;
      }
    }
    std::cout << "position x: " << this->position.x << std::endl;
  }

  if (this->velocity.y != 0) {
    const float inverseVelocity = 1.0 / this->velocity.y;
    if (const float deltaTimeSeconds = totalDeltaTimeMs / 1000.0;
        deltaTimeSeconds >= fabsf(inverseVelocity)) {
      this->totalDeltaTimeMs = 0;
      if (inverseVelocity > 0) {
        this->position.y += 1;
      }
      else {
        this->position.y -= 1;
      }
    }
  }

  checkBoundaries();
}

void Camera::setYVelocity(const int yVelocity) { this->velocity.y = yVelocity; }
void Camera::setXVelocity(const int xVelocity) { this->velocity.x = xVelocity; }

SDL_Point Camera::getPosition() const { return this->position; }
