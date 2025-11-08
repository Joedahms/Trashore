#include <memory>

#include "../GameGlobal.h"
#include "Character.h"
#include "CharacterFactory.h"
#include "Npc.h"
#include "Player.h"

CharacterFactory::CharacterFactory(GameGlobal gameGlobal) {
  this->gameGlobal = gameGlobal;
}

std::unique_ptr<Character> CharacterFactory::create(characterId id) {
  if (PLAYER == id) {
    return std::make_unique<Player>();
  }
  if (NPC == id) {
    return std::make_unique<Npc>(this->gameGlobal);
  }
  return nullptr;
}
