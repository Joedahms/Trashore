#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <vector>

#include "../game_global.h"

class Camera {
public:
  Camera(const GameGlobal& gameGlobal,
         const SDL_Point mapSizeTiles,
         const int initialTileSize);

  void checkBoundries();
  void checkLeftBoundry();
  void checkRightBoundry();
  void checkBottomBoundry();
  void checkTopBoundry();

  void update();

  void setYVelocity(int yVelocity);
  void setXVelocity(int xVelocity);

  SDL_Point getPosition();

private:
  GameGlobal gameGlobal;

  SDL_Point screenSizePixels    = {0, 0};
  SDL_Point mapSizePixels       = {0, 0};
  SDL_Point initialVisibleTiles = {0, 0};

  SDL_Point position = {0, 0};
  SDL_Point velocity = {0, 0};

  int deltaTime        = 0; // MS
  int totalDeltaTime   = 0;
  Uint64 currentTicks  = 0;
  Uint64 previousTicks = 0;

  void shift(const SDL_Point shift);
  void shift(const SDL_Point shift, bool zoomShift);
  int zoomLevel = 32;
};

#endif
