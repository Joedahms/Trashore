#ifndef TILE_H
#define TILE_H

#include "../GameGlobal.h"

enum tileId { WATER_TILE, DIRT_TILE };

class Tile {
public:
  virtual ~Tile() = default;
  Tile(const GameGlobal& gameGlobal, std::string spritePath);

  virtual void print() = 0;
  void setSelected();
  void unsetSelected();
  bool getSelected() const;
  SDL_Texture* getTileTexture() const;
  SDL_Rect getTileRectangle() const;
  void setTileRectangle(SDL_Rect rectangle);

protected:
  GameGlobal gameGlobal;

  const std::string spritePath;

  SDL_Rect rectangle   = {0, 0, 0, 0};
  SDL_Texture* texture = nullptr;
  bool selected        = false;
};

#endif
