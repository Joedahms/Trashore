#include <assert.h>
#include <iostream>

#include "dirt_tile.h"
#include "tile.h"

DirtTile::DirtTile(SDL_Renderer* renderer) {
  SDL_Surface* temporarySurface = IMG_Load("../sprites/dirt_tile.png");
  assert(temporarySurface != 0);

  tileTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
  assert(tileTexture != 0);

  SDL_FreeSurface(temporarySurface);
}

void DirtTile::print() { std::cout << "dirt tile" << std::endl; }
