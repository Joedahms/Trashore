#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <iostream>

#include "../GameGlobal.h"
#include "Character.h"
#include "Npc.h"

Npc::Npc(const GameGlobal gameGlobal) {
  this->gameGlobal = gameGlobal;

  SDL_Surface* npcSurface = IMG_Load("../sprites/NPC.png");
  assert(npcSurface != nullptr);

  this->texture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, npcSurface);
  assert(this->texture != nullptr);

  this->rectangle = {0, 0, 16, 16};

  SDL_FreeSurface(npcSurface);
}

void Npc::print() { std::cout << "npc" << std::endl; }
