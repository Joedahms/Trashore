#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>

#include "../game_global.h"
#include "character.h"

class CharacterFactory final {
public:
  explicit CharacterFactory(GameGlobal);
  ~CharacterFactory() = default;
  std::unique_ptr<Character> create(characterId id);

private:
  GameGlobal gameGlobal{};
};

#endif
