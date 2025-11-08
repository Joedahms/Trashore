#ifndef GAME_GLOBAL_H
#define GAME_GLOBAL_H

#include <SDL3/SDL.h>
#include <string>

struct GameGlobal {
  SDL_Renderer* renderer;
  SDL_Window* window;
  static const std::string futuramFontPath;
  static const std::string logger;
};

#endif
