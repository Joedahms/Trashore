#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>

#include "../GameGlobal.h"

enum characterId { PLAYER, NPC };

class Character {
public:
  virtual void print() = 0;
  virtual ~Character() = default;

  void updatePosition();

  [[nodiscard]] int getYPosition() const;
  [[nodiscard]] int getXPosition() const;

  void setYVelocity(int);
  void setXVelocity(int);

  [[nodiscard]] SDL_Texture* getTexture() const;
  [[nodiscard]] SDL_Rect getRectangle() const;

  void render() const;

protected:
  GameGlobal gameGlobal{};

  SDL_Texture* texture{};
  SDL_Rect rectangle{};

  int yPosition{};
  int xPosition{};

  int yVelocity{};
  int xVelocity{};
};

#endif
