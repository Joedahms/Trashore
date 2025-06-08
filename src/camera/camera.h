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

  void zoomIn();
  void zoomOut();

  void checkBoundries();

  void update();

  std::vector<std::vector<SDL_Rect>> destinationRect;

  void setYVelocity(int yVelocity);
  void setXVelocity(int xVelocity);

  SDL_Point getPosition();

private:
  GameGlobal gameGlobal;

  SDL_Point screenSizePixels = {0, 0};
  SDL_Point mapSizePixels    = {0, 0};

  SDL_Point position = {0, 0};
  SDL_Point velocity = {0, 0};

  int deltaTime        = 0; // MS
  int totalDeltaTime   = 0;
  Uint64 currentTicks  = 0;
  Uint64 previousTicks = 0;

  void shift(const SDL_Point shift);
};

#endif
