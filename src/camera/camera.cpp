#include <iomanip>
#include <iostream>

#include "camera.h"

Camera::Camera(const GameGlobal& gameGlobal,
               const SDL_Point mapSizeTiles,
               const int initialTileSize)
    : gameGlobal(gameGlobal), MAP_SIZE_TILES(mapSizeTiles),
      mapSizePixels(mapSizeTiles.x * initialTileSize, mapSizeTiles.y * initialTileSize) {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);
  this->screenSizePixels.x   = windowSurface->w;
  this->screenSizePixels.y   = windowSurface->h;

  zoomChange(initialTileSize);
}

/**
 * Move the camera position for zoom in.
 *
 * @param tileSize Size of the tiles in the tilemap
 * @return None
 */
void Camera::zoomIn(const int tileSize) {
  this->position.x += this->visibleTiles.x / 4;
  this->position.y += this->visibleTiles.y / 4;
  zoomChange(tileSize);
}

/**
 * Move the camera position for zoom out.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomOut(const int tileSize) {
  this->position.x -= this->visibleTiles.x / 2;
  this->position.y -= this->visibleTiles.y / 2;
  zoomChange(tileSize);
}

/**
 * Ensure that the camera is within the boundries of the tilemap. Checks at the left,
 * right, top, and bottom. Corrects the camera's position and the destination rectangles.
 *
 * @param totalXTiles - The total tiles on the x axis of the tile map.
 * @param totalYTiles - The total tiles on the y axis of the tile map.
 *
 * @return None
 */
void Camera::checkBoundries() {
  // Left
  if (this->position.x < 0) {
    this->position.x = 0;

    for (int y = 0; y < this->visibleTiles.y + 1; y++) {
      for (int x = 0; x < this->visibleTiles.x + 1; x++) {
        this->destinationRect[x][y].x--;
      }
      this->destinationRect[this->visibleTiles.x + 1][y].x--;
    }
  }

  // Right
  if (this->position.x + this->screenSizePixels.x > this->mapSizePixels.x) {
    for (int y = 0; y < this->visibleTiles.y + 1; y++) {
      for (int x = 0; x < this->visibleTiles.x + 1; x++) {
        this->destinationRect[x][y].x++;
      }
      this->destinationRect[this->visibleTiles.x + 1][y].x++;
    }
    this->position.x = this->MAP_SIZE_TILES.x - this->visibleTiles.x;
  }

  // Top
  if (this->position.y < 0) {
    this->position.y = 0;

    for (int x = 0; x < this->visibleTiles.x + 1; x++) {
      for (int y = 0; y < this->visibleTiles.y + 1; y++) {
        this->destinationRect[x][y].y--;
      }
      this->destinationRect[x][this->visibleTiles.y + 1].y--;
    }
  }

  // Bottom
  if (this->position.y + this->screenSizePixels.y > this->mapSizePixels.y) {
    this->position.y = this->MAP_SIZE_TILES.y - this->visibleTiles.y;

    for (int x = 0; x < this->visibleTiles.x + 1; x++) {
      for (int y = 0; y < this->visibleTiles.y + 1; y++) {
        this->destinationRect[x][y].y++;
      }
      this->destinationRect[x][this->visibleTiles.y + 1].y++;
    }
  }
}

/**
 * Handle the changing of zoom level.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomChange(int tileSize) {
  this->destinationRect.resize(
      this->screenSizePixels.x / tileSize + 2,
      std::vector<SDL_Rect>(this->screenSizePixels.y / tileSize + 2));

  this->visibleTiles.x = this->screenSizePixels.x / tileSize;
  this->visibleTiles.y = this->screenSizePixels.y / tileSize;

  checkBoundries();

  // Set up rectangles for rendering
  for (int x = 0; x < this->visibleTiles.x + 2; x++) {
    for (int y = 0; y < this->visibleTiles.y + 2; y++) {
      this->destinationRect[x][y].x = x * tileSize;
      this->destinationRect[x][y].y = y * tileSize;
      this->destinationRect[x][y].w = tileSize;
      this->destinationRect[x][y].h = tileSize;
    }
  }
}

/**
 * Update camera postion based on velocity. Ensure that the camera stays within the bounds
 * of the tile map.
 *
 * @param totalXTiles - Total amount of tiles on the x axis of the tile map.
 * @param totalYTiles - Total amount of tiles on the y axis of the tile map.
 * @return None
 */
void Camera::update(int tileSize) {
  // Make time stuff into function
  this->currentTicks = SDL_GetTicks64();
  this->deltaTime    = this->currentTicks - this->previousTicks;
  this->totalDeltaTime += this->deltaTime;
  this->previousTicks = this->currentTicks;

  // Delta time is in milliseconds

  if (this->velocity.x != 0) {
    float inverseVelocity  = 1.0 / this->velocity.x;
    float deltaTimeSeconds = totalDeltaTime / 1000.0;

    if (deltaTimeSeconds >= fabsf(inverseVelocity)) {
      this->totalDeltaTime = 0;
      if (inverseVelocity > 0) {
        this->position.x++;
      }
      else {
        this->position.x--;
      }
      shiftDestinationRectHorizontal(tileSize);
    }
  }

  if (this->velocity.y != 0) {
    float inverseVelocity  = 1.0 / this->velocity.y;
    float deltaTimeSeconds = totalDeltaTime / 1000.0;

    if (deltaTimeSeconds >= fabsf(inverseVelocity)) {
      this->totalDeltaTime = 0;
      if (inverseVelocity > 0) {
        this->position.y++;
      }
      else {
        this->position.y--;
      }
      shiftDestinationRectVertical(tileSize);
    }
  }

  checkBoundries();
}

/**
 * When the camera moves up or down, move the destination rectangles accordingly. Handle
 * the case where a rectangle goes off the screen on one side and a new one appears on the
 * other.
 *
 * @param None
 * @return None
 */
void Camera::shiftDestinationRectVertical(int tileSize) {
  if (this->velocity.y > 0) {
    if (this->position.y % tileSize == 0) {
      for (int x = 0; x < this->visibleTiles.x + 1; x++) {
        for (int y = 0; y < this->visibleTiles.y + 1; y++) {
          this->destinationRect[x][y].y = this->destinationRect[x][y + 1].y;
        }
        this->destinationRect[x][this->visibleTiles.y + 1].y += tileSize;
      }
    }
  }

  for (int y = 0; y < this->visibleTiles.y + 2; y++) {
    for (int x = 0; x < this->visibleTiles.x + 2; x++) {
      if (this->velocity.y > 0) {
        this->destinationRect[x][y].y--;
      }
      else {
        this->destinationRect[x][y].y++;
      }
    }
  }

  if (this->velocity.y < 0) {
    if (this->position.y % tileSize == tileSize - 1) {
      for (int x = 0; x < this->visibleTiles.x + 1; x++) {
        for (int y = this->visibleTiles.y + 1; y > 0; y--) {
          this->destinationRect[x][y].y = this->destinationRect[x][y - 1].y;
        }
        this->destinationRect[x][0].y -= tileSize;
      }
    }
  }
}

/**
 * When the camera moves left or right, move the destination rectangles accordingly.
 * Handle the case where a rectangle goes off the screen on one side and a new one appears
 * on the other.
 *
 * @param None
 * @return None
 */
void Camera::shiftDestinationRectHorizontal(int tileSize) {
  if (this->velocity.x > 0) {
    // Shift all rectangles to the right
    if (this->position.x % tileSize == 0) {
      for (int y = 0; y < this->visibleTiles.y + 1; y++) {
        for (int x = 0; x < this->visibleTiles.x + 1; x++) {
          this->destinationRect[x][y].x = this->destinationRect[x + 1][y].x;
        }
        this->destinationRect[this->visibleTiles.x + 1][y].x += tileSize;
      }
    }
  }

  // Modify position by velocity
  for (int x = 0; x < this->visibleTiles.x + 2; x++) {
    for (int y = 0; y < this->visibleTiles.y + 2; y++) {
      if (this->velocity.x > 0) {
        this->destinationRect[x][y].x--;
      }
      else {
        this->destinationRect[x][y].x++;
      }
    }
  }

  if (this->velocity.x < 0) {
    // Shift all rectangles to the left
    if (this->position.x % tileSize == tileSize - 1) {
      for (int y = 0; y < this->visibleTiles.y + 1; y++) {
        for (int x = this->visibleTiles.x + 1; x > 0; x--) {
          this->destinationRect[x][y].x = this->destinationRect[x - 1][y].x;
        }
        this->destinationRect[0][y].x -= tileSize;
      }
    }
  }
}

SDL_Rect& Camera::getDestinationRect(int xCoordinate, int yCoordinate) {
  return destinationRect[xCoordinate][yCoordinate];
}

int Camera::getVisibleXTiles() { return this->visibleTiles.x; }
int Camera::getVisibleYTiles() { return this->visibleTiles.y; }

void Camera::setYVelocity(int yVelocity) { this->velocity.y = yVelocity; }
void Camera::setXVelocity(int xVelocity) { this->velocity.x = xVelocity; }

SDL_Point Camera::getPosition() { return this->position; }
