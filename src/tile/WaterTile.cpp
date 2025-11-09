#include <SDL3_image/SDL_image.h>
#include <cassert>
#include <iostream>

#include "Tile.h"
#include "WaterTile.h"

WaterTile::WaterTile(const GameGlobal& gameGlobal)
    : Tile(gameGlobal, "../sprites/water_tile.png") {
  SDL_Surface* temporarySurface = IMG_Load(this->spritePath.c_str());
  assert(temporarySurface != nullptr);

  this->texture =
      SDL_CreateTextureFromSurface(this->gameGlobal.renderer, temporarySurface);
  assert(this->texture != nullptr);

  SDL_DestroySurface(temporarySurface);
}

void WaterTile::print() { std::cout << "water tile" << std::endl; }
