#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>

#include "../game_global.h"

enum characterId { PLAYER, NPC };

class Character {
public:
  virtual void print() = 0;
  virtual ~Character() = default;

  void updatePosition();

  int getYPosition();
  int getXPosition();

  void setYVelocity(int);
  void setXVelocity(int);

  SDL_Texture* getTexture();
  SDL_Rect getRectangle();

  void render();

protected:
  GameGlobal gameGlobal;

  SDL_Texture* texture;
  SDL_Rect rectangle;

  int yPosition;
  int xPosition;

  int yVelocity;
  int xVelocity;
};

#endif
