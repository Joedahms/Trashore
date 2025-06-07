#ifndef WATER_TILE_H
#define WATER_TILE_H

#include "tile.h"

class WaterTile : public Tile {
public:
  WaterTile(const GameGlobal& gameGlobal);
  void print();
};

#endif
