#include <iostream>

#include "camera.h"

/**
 * @param screenHeight - Height of the screen in pixels.
 * @param screenWidth - Width of the screen in pixels.
 * @param initialTileSize - Tiles are squares so side length of a tile in pixels.
 */
Camera::Camera(int screenHeight,
               int screenWidth,
               int totalXTiles,
               int totalYTiles,
               int initialTileSize) {
  std::cout << "here" << std::endl;

  this->screenHeight = screenHeight;
  this->screenWidth  = screenWidth;

  this->xPosition = 0;
  this->yPosition = 0;

  this->xVelocity = 0;
  this->yVelocity = 0;

  this->visibleXTiles = 0;
  this->visibleYTiles = 0;

  zoomChange(initialTileSize, totalXTiles, totalYTiles);
}

void Camera::setXVelocity(int xVelocity) { this->xVelocity = xVelocity; }
void Camera::setYVelocity(int yVelocity) { this->yVelocity = yVelocity; }

int Camera::getXPosition() { return this->xPosition; }
int Camera::getYPosition() { return this->yPosition; }

int Camera::getScreenHeight() { return this->screenHeight; }
int Camera::getScreenWidth() { return this->screenWidth; }

/**
 * Move the camera position for zoom in.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomIn(int tileSize, int totalXTiles, int totalYTiles) {
  this->xPosition += this->visibleXTiles / 4;
  this->yPosition += this->visibleYTiles / 4;
  zoomChange(tileSize, totalXTiles, totalYTiles);
}

/**
 * Move the camera position for zoom out.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomOut(int tileSize, int totalXTiles, int totalYTiles) {
  this->xPosition -= this->visibleXTiles / 2;
  this->yPosition -= this->visibleYTiles / 2;
  zoomChange(tileSize, totalXTiles, totalYTiles);
}

void Camera::checkBoundries(int totalXTiles, int totalYTiles) {
  if (this->xPosition < 0) {
    this->xPosition = 0;
  }
  if (this->xPosition + this->visibleXTiles > totalXTiles) {
    this->xPosition = totalXTiles - this->visibleXTiles;
  }

  if (this->yPosition < 0) {
    this->yPosition = 0;
  }
  if (this->yPosition + this->visibleYTiles > totalYTiles) {
    this->yPosition = totalYTiles - this->visibleYTiles;
  }
}

/**
 * Handle the changing of zoom level.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomChange(int tileSize, int totalXTiles, int totalYTiles) {
  this->destinationRect.resize(this->screenWidth / tileSize + 2,
                               std::vector<SDL_Rect>(this->screenHeight / tileSize));

  this->visibleXTiles = this->screenWidth / tileSize;
  this->visibleYTiles = this->screenHeight / tileSize;

  checkBoundries(totalXTiles, totalYTiles);

  // Set up rectangles for rendering
  for (int x = 0; x < this->visibleXTiles + 2; x++) {
    for (int y = 0; y < this->visibleYTiles; y++) {
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
void Camera::update(int totalXTiles, int totalYTiles) {
  this->xPosition += this->xVelocity;
  //  this->yPosition += this->yVelocity;

  if (this->xVelocity != 0) {
    if (this->xVelocity > 0) {
      if (this->xPosition % 16 == 0) {
        for (int y = 0; y < this->visibleYTiles; y++) {
          for (int x = 0; x < this->visibleXTiles + 1; x++) {
            this->destinationRect[x][y].x = this->destinationRect[x + 1][y].x;
          }
          this->destinationRect[this->visibleXTiles + 1][y].x += 16;
        }
      }
    }

    for (int x = 0; x < this->visibleXTiles + 2; x++) {
      for (int y = 0; y < this->visibleYTiles; y++) {
        this->destinationRect[x][y].x -= this->xVelocity;
      }
    }

    if (this->xVelocity < 0) {
      if (this->xPosition % 16 == 15) {
        for (int y = 0; y < this->visibleYTiles; y++) {
          for (int x = this->visibleXTiles + 1; x > 0; x--) {
            this->destinationRect[x][y].x = this->destinationRect[x - 1][y].x;
          }
          this->destinationRect[0][y].x -= 16;
        }
      }
    }
  }

  checkBoundries(totalXTiles, totalYTiles);
}

SDL_Rect& Camera::getDestinationRect(int xCoordinate, int yCoordinate) {
  return destinationRect[xCoordinate][yCoordinate];
}

int Camera::getVisibleXTiles() { return visibleXTiles; }
int Camera::getVisibleYTiles() { return visibleYTiles; }
