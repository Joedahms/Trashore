#include "character.h"

void Character::updateYPosition() {
  this->yPosition = this->yPosition += this->yVelocity;
}
void Character::updateXPosition() {
  this->xPosition = this->xPosition += this->xVelocity;
}

int Character::getYPosition() { return this->yPosition; }
int Character::getXPosition() { return this->yPosition; }

void Character::setYVelocity(int newYVelocity) { this->yVelocity = newYVelocity; }
void Character::setXVelocity(int newXVelocity) { this->xVelocity = newXVelocity; }

SDL_Texture* Character::getTexture() { return this->texture; }
