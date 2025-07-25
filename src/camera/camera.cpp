#include <iomanip>
#include <iostream>

#include "camera.h"

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

  int xPosition = 0;
  int yPosition = 0;

  this->destinationRect.resize(mapSizeTiles.x);
  for (int x = 0; x < mapSizeTiles.x; x++) {
    for (int y = 0; y < mapSizeTiles.y; y++) {
      this->destinationRect[x].emplace_back(
          SDL_Rect{xPosition, yPosition, initialTileSize, initialTileSize});
      yPosition += initialTileSize;
    }
    yPosition = 0;
    xPosition += initialTileSize;
  }
}

/**
 * Move the camera position for zoom in.
 *
 * @param tileSize Size of the tiles in the tilemap
 * @return None
 */
void Camera::zoomIn() {
  // Max zoom
  if (this->zoomLevel == 100) {
    return;
  }

  this->zoomLevel++;
  SDL_Point shiftAmount = {0, 0};
  for (auto& column : destinationRect) {
    for (auto& rectangle : column) {
      rectangle.x += shiftAmount.x;
      rectangle.y += shiftAmount.y;
      rectangle.w++;
      rectangle.h++;

      shiftAmount.y++;
    }
    shiftAmount.y = 0;
    shiftAmount.x++;
  }

  /*
  shift(SDL_Point{this->initialVisibleTiles.x / 2, this->initialVisibleTiles.y / 2},
        );
  */
  shift(SDL_Point{this->initialVisibleTiles.x / 2 + this->truePosition.x / 16,
                  this->initialVisibleTiles.y / 2 + this->truePosition.y / 16},
        true);
}

/**
 * Move the camera position for zoom out.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomOut() {
  this->zoomLevel--;
  SDL_Point shiftAmount = {0, 0};
  for (auto& column : destinationRect) {
    for (auto& rectangle : column) {
      rectangle.x -= shiftAmount.x;
      rectangle.y -= shiftAmount.y;
      rectangle.w--;
      rectangle.h--;

      shiftAmount.y++;
    }
    shiftAmount.y = 0;
    shiftAmount.x++;
  }

  //  shift(SDL_Point{-this->initialVisibleTiles.x / 2, -this->initialVisibleTiles.y /
  //  2});
  shift(SDL_Point{-(this->initialVisibleTiles.x / 2 + this->truePosition.x / 16),
                  -(this->initialVisibleTiles.y / 2 + this->truePosition.y / 16)},
        true);
}

/**
 * Ensure that the camera is within the boundries of the tilemap. Checks at the left,
 * right, top, and bottom. Corrects the camera's position and the destination rectangles.
 *
 * @return None
 */
void Camera::checkBoundries() {
  // Left
  if (this->zoomedPosition.x < 0) {
    shift(SDL_Point{1, 0}, false);
  }

  // Right
  if (this->zoomedPosition.x + this->screenSizePixels.x > this->mapSizePixels.x) {
    shift(SDL_Point{-1, 0}, false);
  }

  // Top
  if (this->zoomedPosition.y < 0) {
    shift(SDL_Point{0, 1}, false);
  }

  // Bottom
  if (this->zoomedPosition.y + this->screenSizePixels.y > this->mapSizePixels.y) {
    shift(SDL_Point{0, -1}, false);
  }
}

/**
 * Update camera postion based on velocity. Ensure that the camera stays within the bounds
 * of the tile map.
 *
 * @return None
 */
void Camera::update() {
  // Make time stuff into function
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
        shift(SDL_Point{1, 0}, false);
      }
      else {
        shift(SDL_Point{-1, 0}, false);
      }
    }
  }

  if (this->velocity.y != 0) {
    float inverseVelocity  = 1.0 / this->velocity.y;
    float deltaTimeSeconds = totalDeltaTime / 1000.0;
    if (deltaTimeSeconds >= fabsf(inverseVelocity)) {
      this->totalDeltaTime = 0;
      if (inverseVelocity > 0) {
        shift(SDL_Point{0, 1}, false);
      }
      else {
        shift(SDL_Point{0, -1}, false);
      }
    }
  }

  checkBoundries();
}

void Camera::setYVelocity(int yVelocity) { this->velocity.y = yVelocity; }
void Camera::setXVelocity(int xVelocity) { this->velocity.x = xVelocity; }

SDL_Point Camera::getPosition() { return this->zoomedPosition; }

void Camera::shift(const SDL_Point shift, bool zoomShift) {
  if (zoomShift) {
    this->zoomedPosition.x += shift.x;
    this->zoomedPosition.y += shift.y;
  }
  else {
    this->truePosition.x += shift.x;
    this->truePosition.y += shift.y;

    this->zoomedPosition.x += shift.x;
    this->zoomedPosition.y += shift.y;
  }
  for (auto& column : this->destinationRect) {
    for (auto& rectangle : column) {
      rectangle.x -= shift.x;
      rectangle.y -= shift.y;
    }
  }
}
