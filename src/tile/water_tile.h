#ifndef WATER_TILE_H
#define WATER_TILE_H

#include "tile.h"

class WaterTile final : public Tile {
public:
  explicit WaterTile(const GameGlobal& gameGlobal);
  void print() override;
};

#endif
