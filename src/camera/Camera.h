#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>

#include "../GameGlobal.h"

class Camera {
public:
  Camera(const GameGlobal& gameGlobal, SDL_Point mapSizeTiles, int initialTileSize);

  void checkBoundaries();
  void checkLeftBoundary();
  void checkRightBoundary();
  void checkBottomBoundary();
  void checkTopBoundary();

  void update();

  void setYVelocity(int yVelocity);
  void setXVelocity(int xVelocity);

  [[nodiscard]] SDL_FPoint getPosition() const;
  SDL_FPoint position   = {0, 0};
  SDL_FRect destination = {0, 0, 1024, 640};

private:
  GameGlobal gameGlobal;

  SDL_Point screenSizePixels    = {0, 0};
  SDL_Point mapSizePixels       = {0, 0};
  SDL_Point initialVisibleTiles = {0, 0};

  SDL_Point velocity = {0, 0};

  int deltaTimeMs      = 0;
  int totalDeltaTimeMs = 0;
  Uint64 currentTicks  = 0;
  Uint64 previousTicks = 0;
};

#endif
