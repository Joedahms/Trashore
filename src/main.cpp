#include <SDL3/SDL.h>

#include "GameEngine.h"
#include "Logger.h"

/**
 * WINDOW_WIDTH and WINDOW_HEIGHT are ignored if FULLSCREEN is set to true
 */
int main() {
  constexpr int WINDOW_WIDTH  = 1024;
  constexpr int WINDOW_HEIGHT = 640;
  constexpr bool FULLSCREEN   = true;

  const auto gameEngine = std::make_unique<GameEngine>("game_engine", WINDOW_WIDTH,
                                                       WINDOW_HEIGHT, FULLSCREEN);

  gameEngine->start();
  return 0;
}
