#include <memory>

#include "DirtTile.h"
#include "Tile.h"
#include "TileFactory.h"
#include "WaterTile.h"

TileFactory::TileFactory(const GameGlobal& gameGlobal) : gameGlobal(gameGlobal) {}

std::unique_ptr<Tile> TileFactory::create(tileId id) {
  if (WATER_TILE == id) {
    return std::make_unique<WaterTile>(gameGlobal);
  }
  if (DIRT_TILE == id) {
    return std::make_unique<DirtTile>(gameGlobal);
  }
  return nullptr;
}
