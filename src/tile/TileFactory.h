#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include <memory>

#include "Tile.h"

class TileFactory {
public:
  explicit TileFactory(const GameGlobal& gameGlobal);
  std::unique_ptr<Tile> create(tileId id);

private:
  GameGlobal gameGlobal;
};

#endif
