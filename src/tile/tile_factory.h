#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include <memory>

#include "tile.h"

class TileFactory {
public:
  explicit TileFactory(const GameGlobal& gameGlobal);
  std::unique_ptr<Tile> create(tileId id);

private:
  GameGlobal gameGlobal;
};

#endif
