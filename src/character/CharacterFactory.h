#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>

#include "../GameGlobal.h"
#include "Character.h"

class CharacterFactory final {
public:
  explicit CharacterFactory(GameGlobal);
  ~CharacterFactory() = default;
  std::unique_ptr<Character> create(characterId id);

private:
  GameGlobal gameGlobal{};
};

#endif
