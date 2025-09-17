#include "camera.h"
#include <iostream>

Camera::Camera(const GameGlobal& gameGlobal,
               const SDL_Point mapSizeTiles,
               const int initialTileSize)
    : gameGlobal(gameGlobal),
      mapSizePixels(mapSizeTiles.x * initialTileSize, mapSizeTiles.y * initialTileSize) {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  this->screenSizePixels.x   = windowSurface->w;
  this->screenSizePixels.y   = windowSurface->h;

  this->initialVisibleTiles.x = this->screenSizePixels.x / initialTileSize;
  this->initialVisibleTiles.y = this->screenSizePixels.y / initialTileSize;
}

void Camera::checkBoundries() {
  // Need to factor in the destination rectangle
  // Currently this only works if the destination rectangle is unmodified
  // If the destination rectangle x = -2 then left bound is camera x - 2
  // If the destination rectangle x = -4 then left bound is camera x - 4
  checkLeftBoundry();
  checkRightBoundry();
  checkTopBoundry();
  checkBottomBoundry();
}

void Camera::checkLeftBoundry() {
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

void Camera::checkRightBoundry() {
  if (this->position.x + this->screenSizePixels.x > this->mapSizePixels.x) {
    this->position.x -= 1;
  }
}

void Camera::checkTopBoundry() {
  if (this->position.y < 0) {
    this->position.y += 1;
  }
}

void Camera::checkBottomBoundry() {
  if (this->position.y + this->screenSizePixels.y > this->mapSizePixels.y) {
    this->position.y -= 1;
  }
}

void Camera::update() {
  // TODO: Make time stuff into function
  this->currentTicks = SDL_GetTicks64();
  this->deltaTime    = this->currentTicks - this->previousTicks;
  this->totalDeltaTime += this->deltaTime;
  this->previousTicks = this->currentTicks;

  if (this->velocity.x != 0) {
    float inverseVelocity  = 1.0 / this->velocity.x;
    float deltaTimeSeconds = totalDeltaTime / 1000.0;
    if (deltaTimeSeconds >= fabsf(inverseVelocity)) {
      this->totalDeltaTime = 0;
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
    float inverseVelocity  = 1.0 / this->velocity.y;
    float deltaTimeSeconds = totalDeltaTime / 1000.0;
    if (deltaTimeSeconds >= fabsf(inverseVelocity)) {
      this->totalDeltaTime = 0;
      if (inverseVelocity > 0) {
        this->position.y += 1;
      }
      else {
        this->position.y -= 1;
      }
    }
  }

  checkBoundries();
}

void Camera::setYVelocity(int yVelocity) { this->velocity.y = yVelocity; }
void Camera::setXVelocity(int xVelocity) { this->velocity.x = xVelocity; }

SDL_Point Camera::getPosition() { return this->position; }
