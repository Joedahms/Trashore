#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player final : public Character {
public:
  Player();
  ~Player() override;
  void print() override;
};

#endif
