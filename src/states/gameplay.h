#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../camera/camera.h"
#include "../character/character_factory.h"
#include "../elements/gui_box.h"
#include "../tile/tile_map.h"
#include "state.h"

class Gameplay : public State {
public:
  Gameplay(const GameGlobal& gameGlobal, const EngineState& state);
  void handleEvents(bool& gameIsRunning) override;
  void checkKeystates();
  void setSelectedTile();
  void update() override;
  void render() const override;
  void exit() override;

private:
  const SDL_Point MAP_SIZE_TILES = {200, 200};
  const int INITIAL_TILE_SIZE    = 16;

  std::unique_ptr<CharacterFactory> characterFactory;
  std::unique_ptr<Camera> camera;
  std::unique_ptr<TileMap> tileMap;
  std::vector<std::unique_ptr<Character>> npcVector;

  SDL_Texture* selectedTexture;
};

#endif
