#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>

enum characterId { PLAYER, NPC };

/**
 * @class Character
 *
 * Represent playable and non playable character entities
 */
class Character {
public:
  virtual void print() = 0;
  virtual ~Character() = default;

  void updateYPosition();
  void updateXPosition();

  int getYPosition();
  int getXPosition();

  void setYVelocity(int);
  void setXVelocity(int);

  SDL_Texture* getTexture();

private:
  SDL_Texture* texture;

  int yPosition;
  int xPosition;

  int yVelocity;
  int xVelocity;
};

#endif
