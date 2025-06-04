#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "game_engine.h"
#include "game_global.h"
#include "logger.h"

int main(int argc, const char* argv[]) {
  const int WINDOW_WIDTH  = 1024;
  const int WINDOW_HEIGHT = 640;
  const bool FULLSCREEN   = false;

  // Initialize the game
  std::unique_ptr<GameEngine> gameEngine = std::make_unique<GameEngine>(
      "game_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
      WINDOW_HEIGHT, FULLSCREEN);

  gameEngine->start();
  return 0;
}
