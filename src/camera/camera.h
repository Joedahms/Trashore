#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <vector>

#include "../game_global.h"

/**
 * The camera defines how the game is displayed to the user. It dictates what is
 * visible at any one given time.
 */
class Camera {
public:
  Camera(const GameGlobal& gameGlobal,
         const SDL_Point mapSizeTiles,
         const int initialTileSize);

  void zoomIn(const int tileSize);
  void zoomOut(const int tileSize);
  void zoomChange(int tileSize);

  void checkBoundries();

  void update(int tileSize);

  void shiftDestinationRectVertical(int tileSize);
  void shiftDestinationRectHorizontal(int tileSize);
  SDL_Rect& getDestinationRect(int xCoordinate, int yCoordinate);

  // Needs to be dependent on screen size
  std::vector<std::vector<SDL_Rect>> destinationRect;

  int getVisibleXTiles();
  int getVisibleYTiles();

  void setYVelocity(int yVelocity);
  void setXVelocity(int xVelocity);

  SDL_Point getPosition();

private:
  GameGlobal gameGlobal;

  SDL_Point screenSizePixels = {0, 0};

  const SDL_Point MAP_SIZE_TILES;
  SDL_Point mapSizePixels = {0, 0};

  SDL_Point position = {0, 0};
  SDL_Point velocity = {0, 0};

  SDL_Point visibleTiles = {0, 0};

  int deltaTime        = 0;
  int totalDeltaTime   = 0;
  Uint64 currentTicks  = 0;
  Uint64 previousTicks = 0;
};

#endif
