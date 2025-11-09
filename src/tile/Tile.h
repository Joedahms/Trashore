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
  [[nodiscard]] bool getSelected() const;
  [[nodiscard]] SDL_Texture* getTileTexture() const;
  [[nodiscard]] SDL_FRect getTileRectangle() const;
  void setTileRectangle(SDL_FRect newRectangle);

protected:
  GameGlobal gameGlobal;

  const std::string spritePath;

  SDL_FRect rectangle  = {0, 0, 0, 0};
  SDL_Texture* texture = nullptr;
  bool selected        = false;
};

#endif
