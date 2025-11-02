#include <cassert>
#include <iostream>

#include "tile.h"
#include "water_tile.h"

WaterTile::WaterTile(const GameGlobal& gameGlobal)
    : Tile(gameGlobal, "../sprites/water_tile.png") {
  SDL_Surface* temporarySurface = IMG_Load(this->spritePath.c_str());
  assert(temporarySurface != nullptr);

  this->texture =
      SDL_CreateTextureFromSurface(this->gameGlobal.renderer, temporarySurface);
  assert(this->texture != nullptr);

  SDL_FreeSurface(temporarySurface);
}

void WaterTile::print() { std::cout << "water tile" << std::endl; }
