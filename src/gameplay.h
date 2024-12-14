#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "camera/camera.h"
#include "character/character_factory.h"
#include "game_global.h"
#include "tile/tile_map.h"

/**
 * Gameplay state. State entered when user presses start button in main menu.
 */
class Gameplay {
public:
  Gameplay(struct GameGlobal);
  int handleEvents(bool*);
  int checkKeystates();
  void setSelectedTile();
  void update();
  void render();
  void enterGameplay();
  void initializeTextures();
  bool getStateEntered(); // Check if the state has already been entered

private:
  struct GameGlobal gameGlobal;
  bool stateEntered = false; // Has the state been entered before

  std::unique_ptr<CharacterFactory> characterFactory;

  std::unique_ptr<Camera> camera;
  std::unique_ptr<TileMap> tileMap;
  std::vector<std::unique_ptr<Character>> npcVector;

  // Zoom flags. Game starts zoomed out.
  bool zoomedIn  = false;
  bool zoomedOut = true;

  SDL_Texture* selectedTexture;
};

#endif
