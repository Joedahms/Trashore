#include <SDL2/SDL.h>

#include "character.h"

void Character::updatePosition() {
  this->rectangle.x = this->rectangle.x += this->xVelocity;
  this->rectangle.y = this->rectangle.y += this->yVelocity;
}

int Character::getYPosition() { return this->yPosition; }
int Character::getXPosition() { return this->yPosition; }

void Character::setYVelocity(int newYVelocity) { this->yVelocity = newYVelocity; }
void Character::setXVelocity(int newXVelocity) { this->xVelocity = newXVelocity; }

SDL_Texture* Character::getTexture() { return this->texture; }
SDL_Rect Character::getRectangle() { return this->rectangle; }

void Character::render() {
  SDL_RenderCopy(this->gameGlobal.renderer, this->texture, NULL, &this->rectangle);
}
