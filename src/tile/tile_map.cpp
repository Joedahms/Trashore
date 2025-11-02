#include <iostream>
#include <memory>
#include <vector>

#include "tile.h"
#include "tile_map.h"

TileMap::TileMap(const GameGlobal& gameGlobal,
                 const SDL_Point mapSizeTiles,
                 const int initialTileSize)
    : gameGlobal(gameGlobal), MAP_SIZE_TILES(mapSizeTiles), tileSize(initialTileSize) {
  this->tileFactory = std::make_unique<TileFactory>(gameGlobal);
  tileVector.resize(this->MAP_SIZE_TILES.x);
  int randomNum = 0;

  SDL_Point tilePosition = {0, 0};
  for (int x = 0; x < this->MAP_SIZE_TILES.x; x++) {
    for (int y = 0; y < this->MAP_SIZE_TILES.y; y++) {
      randomNum = rand() % 2 + 1; // random tile (either one or two)

      switch (randomNum) { // Which type of tile to add to the array
      case 1:              // Water tile
        {
          std::unique_ptr<Tile> waterTile = this->tileFactory->create(WATER_TILE);
          waterTile->setTileRectangle(
              SDL_Rect{tilePosition.x, tilePosition.y, this->tileSize, this->tileSize});
          this->tileVector[x].emplace_back(std::move(waterTile));
          break;
        }

      case 2: // Dirt tile
        {
          std::unique_ptr<Tile> dirtTile = this->tileFactory->create(DIRT_TILE);
          // TODO: I think this rectangle might be set somewhere else but idk
          dirtTile->setTileRectangle(
              SDL_Rect{tilePosition.x, tilePosition.y, this->tileSize, this->tileSize});
          this->tileVector[x].emplace_back(std::move(dirtTile));
          break;
        }

      default:
        break;
      }
      tilePosition.y += tileSize;
    }
    tilePosition.y = 0;
    tilePosition.x += tileSize;
  }
}

void TileMap::setTileSize(const int newTileSize) { this->tileSize = newTileSize; }
int TileMap::getTileSize() const { return this->tileSize; }

void TileMap::selectTile(const int xCoordinate, const int yCoordinate) const {
  this->tileVector[xCoordinate][yCoordinate]->setSelected();
}

void TileMap::unselectTile(const int xCoordinate, const int yCoordinate) const {
  this->tileVector[xCoordinate][yCoordinate]->unsetSelected();
}

SDL_Texture* TileMap::getTileTexture(const int xCoordinate, const int yCoordinate) const {
  return this->tileVector[xCoordinate][yCoordinate]->getTileTexture();
}

bool TileMap::getSelected(const int xCoordinate, const int yCoordinate) const {
  return this->tileVector[xCoordinate][yCoordinate]->getSelected();
}

SDL_Rect TileMap::getTileRectangle(const SDL_Point tileCoordinate) const {
  return this->tileVector[tileCoordinate.x][tileCoordinate.y]->getTileRectangle();
}
