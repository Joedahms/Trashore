#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>

#include "../game_global.h"
#include "tile_factory.h"

class TileMap {
public:
  TileMap(const GameGlobal& gameGlobal, SDL_Point mapSizeTiles, int initialTileSize);
  void setTileSize(int newTileSize);
  int getTileSize() const;

  void selectTile(int xCoordinate, int yCoordinate) const;
  void unselectTile(int xCoordinate, int yCoordinate) const;

  SDL_Texture* getTileTexture(int xCoordinate, int yCoordinate) const;

  bool getSelected(int xCoordinate, int yCoordinate) const;

  SDL_Rect getTileRectangle(SDL_Point tileCoordinate) const;

private:
  GameGlobal gameGlobal;

  std::vector<std::vector<std::unique_ptr<Tile>>> tileVector;
  std::unique_ptr<TileFactory> tileFactory;

  const SDL_Point MAP_SIZE_TILES;
  int tileSize = 0;
};

#endif
