#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>

#include "../game_global.h"
#include "tile_factory.h"

class TileMap {
public:
  TileMap(const GameGlobal& gameGlobal,
          const SDL_Point mapSizeTiles,
          const int initialTileSize);
  void setTileSize(const int newTileSize);
  int getTileSize();

  void selectTile(const int xCoordinate, const int yCoordinate);
  void unselectTile(const int xCoordinate, const int yCoordinate);

  SDL_Texture* getTileTexture(const int xCoordinate, const int yCoordinate);

  bool getSelected(const int xCoordinate, const int yCoordinate);

private:
  GameGlobal gameGlobal;

  std::vector<std::vector<std::unique_ptr<Tile>>> tileVector;
  std::unique_ptr<TileFactory> tileFactory;

  const SDL_Point MAP_SIZE_TILES;
  int tileSize = 0;
};

#endif
