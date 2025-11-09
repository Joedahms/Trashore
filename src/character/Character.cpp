#include <SDL3/SDL.h>

#include "Character.h"

void Character::updatePosition() {
  this->rectangle.x = this->rectangle.x += this->xVelocity;
  this->rectangle.y = this->rectangle.y += this->yVelocity;
}

int Character::getYPosition() const { return this->yPosition; }
int Character::getXPosition() const { return this->yPosition; }

void Character::setYVelocity(int newYVelocity) { this->yVelocity = newYVelocity; }
void Character::setXVelocity(int newXVelocity) { this->xVelocity = newXVelocity; }

SDL_Texture* Character::getTexture() const { return this->texture; }
SDL_FRect Character::getRectangle() const { return this->rectangle; }

void Character::render() const {
  SDL_RenderTexture(this->gameGlobal.renderer, this->texture, nullptr, &this->rectangle);
}
