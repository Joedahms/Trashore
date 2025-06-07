#include <iostream>
#include <memory>
#include <vector>

#include "tile.h"
#include "tile_map.h"

// Pass tile size
TileMap::TileMap(const GameGlobal& gameGlobal,
                 const SDL_Point mapSizeTiles,
                 const int initialTileSize)
    : MAP_SIZE_TILES(mapSizeTiles), tileSize(initialTileSize) {
  this->tileFactory = std::make_unique<TileFactory>(gameGlobal);
  tileVector.resize(this->MAP_SIZE_TILES.x);
  int randomNum = 0;

  std::unique_ptr<Tile> waterTile;
  std::unique_ptr<Tile> dirtTile;

  for (int x = 0; x < this->MAP_SIZE_TILES.x; x++) {
    for (int y = 0; y < this->MAP_SIZE_TILES.y; y++) {
      randomNum = rand() % 2 + 1; // random tile (either one or two)

      switch (randomNum) { // Which type of tile to add to the array
      case 1:              // Water tile
        {
          std::unique_ptr<Tile> waterTile = this->tileFactory->create(tileId::WATER_TILE);
          this->tileVector[x].emplace_back(std::move(waterTile));
          break;
        }

      case 2: // Dirt tile
        {
          std::unique_ptr<Tile> dirtTile = this->tileFactory->create(tileId::DIRT_TILE);
          this->tileVector[x].emplace_back(std::move(dirtTile));
          break;
        }

      default:
        break;
      }
    }
  }
}

void TileMap::setTileSize(const int newTileSize) { this->tileSize = newTileSize; }
int TileMap::getTileSize() { return this->tileSize; }

void TileMap::selectTile(const int xCoordinate, const int yCoordinate) {
  this->tileVector[xCoordinate][yCoordinate]->setSelected();
}

void TileMap::unselectTile(const int xCoordinate, const int yCoordinate) {
  this->tileVector[xCoordinate][yCoordinate]->unsetSelected();
}

SDL_Texture* TileMap::getTileTexture(const int xCoordinate, const int yCoordinate) {
  return this->tileVector[xCoordinate][yCoordinate]->getTileTexture();
}

bool TileMap::getSelected(const int xCoordinate, const int yCoordinate) {
  return this->tileVector[xCoordinate][yCoordinate]->getSelected();
}
