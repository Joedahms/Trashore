#include <memory>

#include "dirt_tile.h"
#include "tile.h"
#include "tile_factory.h"
#include "water_tile.h"

TileFactory::TileFactory(const GameGlobal& gameGlobal) : gameGlobal(gameGlobal) {}

std::unique_ptr<Tile> TileFactory::create(tileId id) {
  if (tileId::WATER_TILE == id) {
    return std::make_unique<WaterTile>(gameGlobal);
  }
  if (tileId::DIRT_TILE == id) {
    return std::make_unique<DirtTile>(gameGlobal);
  }
  return nullptr;
}
