#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>

#include "character.h"

class CharacterFactory {
public:
  virtual std::unique_ptr<Character> create(characterId id);
};

#endif
