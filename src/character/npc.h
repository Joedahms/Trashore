#ifndef NPC_H
#define NPC_H

#include "../game_global.h"
#include "character.h"

class Npc : public Character {
public:
  Npc(GameGlobal);
  void print();
};

#endif
