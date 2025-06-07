#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL_image.h>

#include "../game_global.h"

enum tileId { WATER_TILE, DIRT_TILE };

class Tile {
public:
  Tile(const GameGlobal& gameGlobal, const std::string& spritePath);

  virtual void print() = 0;
  void setSelected();
  void unsetSelected();
  bool getSelected();
  SDL_Texture* getTileTexture();

protected:
  GameGlobal gameGlobal;

  const std::string spritePath;

  SDL_Rect rectangle   = {0, 0, 0, 0};
  SDL_Texture* texture = nullptr;
  bool selected        = false;
};

#endif
