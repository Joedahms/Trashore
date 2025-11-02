#ifndef DIRT_TILE_H
#define DIRT_TILE_H

#include "Tile.h"

class DirtTile final : public Tile {
public:
  explicit DirtTile(const GameGlobal& gameGlobal);
  void print() override;
};

#endif
