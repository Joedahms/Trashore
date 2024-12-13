#include <iostream>

#include "character.h"
#include "npc.h"

Npc::Npc(GameGlobal gameGlobal) {
  SDL_Surface* npcSurface = IMG_LOAD("../src/sprites/NPC.png");
  assert(npcSurface != 0);

  this->texture = SDL_CreateTextureFromSurface(gameGlobal.renderer, npcSurface);
  assert(this->texture != 0);

  SDL_FreeSurface(npcSurface);
}

void Npc::print() { std::cout << "npc" << std::endl; }
