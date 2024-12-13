#include <memory>

#include "character.h"
#include "character_factory.h"
#include "npc.h"
#include "player.h"

std::unique_ptr<Character> CharacterFactory::create(characterId id) {
  if (characterId::PLAYER == id) {
    return std::make_unique<Player>();
  }
  if (characterId::NPC == id) {
    return std::make_unique<Npc>();
  }
  return nullptr;
}
