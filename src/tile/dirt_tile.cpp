#include <assert.h>
#include <iostream>

#include "dirt_tile.h"
#include "tile.h"

DirtTile::DirtTile(const GameGlobal& gameGlobal)
    : Tile(gameGlobal, "../sprites/dirt_tile.png") {
  SDL_Surface* temporarySurface = IMG_Load(this->spritePath.c_str());
  assert(temporarySurface != 0);

  this->texture =
      SDL_CreateTextureFromSurface(this->gameGlobal.renderer, temporarySurface);
  assert(this->texture != 0);

  SDL_FreeSurface(temporarySurface);
}

void DirtTile::print() { std::cout << "dirt tile" << std::endl; }
