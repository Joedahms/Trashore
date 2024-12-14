#include "camera.h"

/**
 * @param screenHeight - Height of the screen in pixels.
 * @param screenWidth - Width of the screen in pixels.
 * @param initialTileSize - Tiles are squares so side length of a tile in pixels.
 */
Camera::Camera(int screenHeight, int screenWidth, int initialTileSize) {
  this->screenHeight = screenHeight;
  this->screenWidth  = screenWidth;

  this->xPosition = 0;
  this->yPosition = 0;

  this->xVelocity = 0;
  this->yVelocity = 0;

  this->visibleXTiles = 0;
  this->visibleYTiles = 0;

  zoomChange(initialTileSize);
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
void Camera::zoomIn(int tileSize) {
  xPosition += visibleXTiles / 4;
  yPosition += visibleYTiles / 4;

  zoomChange(tileSize);
}

/**
 * Move the camera position for zoom out.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomOut(int tileSize) {
  xPosition -= visibleXTiles / 2;
  // Past left side of map
  if (xPosition < 0) {
    xPosition = 0;
  }

  yPosition -= visibleYTiles / 2;
  // Past top of map
  if (yPosition < 0) {
    yPosition = 0;
  }

  zoomChange(tileSize);
}

/**
 * Handle the changing of zoom level.
 *
 * @param tileSize - Size of the tiles in the tilemap.
 * @return None
 */
void Camera::zoomChange(int tileSize) {
  destinationRect.resize(screenWidth / tileSize,
                         std::vector<SDL_Rect>(screenHeight / tileSize));

  this->visibleXTiles = screenWidth / tileSize;
  this->visibleYTiles = screenHeight / tileSize;

  // Set up rectangles for rendering
  for (int x = 0; x < this->visibleXTiles; x++) {
    for (int y = 0; y < this->visibleYTiles; y++) {
      destinationRect[x][y].x = x * tileSize;
      destinationRect[x][y].y = y * tileSize;
      destinationRect[x][y].w = tileSize;
      destinationRect[x][y].h = tileSize;
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
  xPosition += xVelocity;
  if (xPosition < 0) {
    xPosition = 0;
  }
  if (xPosition + visibleXTiles > totalXTiles) {
    xPosition = totalXTiles - visibleXTiles;
  }

  yPosition += yVelocity;
  if (yPosition < 0) {
    yPosition = 0;
  }
  if (yPosition + visibleYTiles > totalYTiles) {
    yPosition = totalYTiles - visibleYTiles;
  }
}

SDL_Rect& Camera::getDestinationRect(int xCoordinate, int yCoordinate) {
  return destinationRect[xCoordinate][yCoordinate];
}

int Camera::getVisibleXTiles() { return visibleXTiles; }
int Camera::getVisibleYTiles() { return visibleYTiles; }
