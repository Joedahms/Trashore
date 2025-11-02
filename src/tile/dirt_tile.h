#ifndef DIRT_TILE_H
#define DIRT_TILE_H

#include "tile.h"

class DirtTile final : public Tile {
public:
  explicit DirtTile(const GameGlobal& gameGlobal);
  void print() override;
};

#endif
