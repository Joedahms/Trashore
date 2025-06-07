#ifndef DIRT_TILE_H
#define DIRT_TILE_H

#include "tile.h"

class DirtTile : public Tile {
public:
  DirtTile(const GameGlobal& gameGlobal);
  void print();
};

#endif
