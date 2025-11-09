#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>

#include "../GameGlobal.h"
#include "TileFactory.h"

class TileMap {
public:
  TileMap(const GameGlobal& gameGlobal, SDL_Point mapSizeTiles, int initialTileSize);
  void setTileSize(int newTileSize);
  [[nodiscard]] int getTileSize() const;

  void selectTile(int xCoordinate, int yCoordinate) const;
  void unselectTile(int xCoordinate, int yCoordinate) const;

  [[nodiscard]] SDL_Texture* getTileTexture(int xCoordinate, int yCoordinate) const;

  [[nodiscard]] bool getSelected(int xCoordinate, int yCoordinate) const;

  [[nodiscard]] SDL_Rect getTileRectangle(SDL_Point tileCoordinate) const;

private:
  GameGlobal gameGlobal;

  std::vector<std::vector<std::unique_ptr<Tile>>> tileVector;
  std::unique_ptr<TileFactory> tileFactory;

  const SDL_Point MAP_SIZE_TILES;
  int tileSize = 0;
};

#endif
