#ifndef NPC_H
#define NPC_H

#include "../GameGlobal.h"
#include "Character.h"

class Npc final : public Character {
public:
  explicit Npc(GameGlobal);
  void print() override;
};

#endif
