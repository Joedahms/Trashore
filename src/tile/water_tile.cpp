#include <assert.h>
#include <iostream>

#include "tile.h"
#include "water_tile.h"

WaterTile::WaterTile(SDL_Renderer* renderer) {
  SDL_Surface* temporarySurface = IMG_Load("../sprites/water_tile.png");

  tileTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);

  SDL_FreeSurface(temporarySurface);
}

void WaterTile::print() { std::cout << "water tile" << std::endl; }
