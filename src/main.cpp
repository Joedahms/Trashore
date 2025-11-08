#include <SDL3/SDL.h>

#include "GameEngine.h"
#include "Logger.h"

int main(int argc, const char* argv[]) {
  constexpr int WINDOW_WIDTH  = 1024;
  constexpr int WINDOW_HEIGHT = 640;
  constexpr bool FULLSCREEN   = false;

  const auto gameEngine = std::make_unique<GameEngine>(
      "game_engine", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1),
      WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN);

  gameEngine->start();
  return 0;
}
