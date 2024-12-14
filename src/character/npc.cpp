#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <iostream>

#include "../game_global.h"
#include "character.h"
#include "npc.h"

Npc::Npc(GameGlobal gameGlobal) {
  this->gameGlobal = gameGlobal;

  SDL_Surface* npcSurface = IMG_Load("../src/sprites/NPC.png");
  assert(npcSurface != 0);

  this->texture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, npcSurface);
  assert(this->texture != 0);

  this->rectangle = {0, 0, 16, 16};

  SDL_FreeSurface(npcSurface);
}

void Npc::print() { std::cout << "npc" << std::endl; }
