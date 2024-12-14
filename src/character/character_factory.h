#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>

#include "../game_global.h"
#include "character.h"

class CharacterFactory {
public:
  CharacterFactory(GameGlobal);
  virtual std::unique_ptr<Character> create(characterId id);

private:
  GameGlobal gameGlobal;
};

#endif
