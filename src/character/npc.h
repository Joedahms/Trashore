#ifndef NPC_H
#define NPC_H

#include "../game_global.h"
#include "character.h"

class Npc final : public Character {
public:
  explicit Npc(GameGlobal);
  void print() override;
};

#endif
