#include <memory>

#include "../game_global.h"
#include "character.h"
#include "character_factory.h"
#include "npc.h"
#include "player.h"

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
