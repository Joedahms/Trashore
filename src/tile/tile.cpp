#include <iostream>

#include "tile.h"

Tile::Tile(const GameGlobal& gameGlobal, const std::string& spritePath)
    : gameGlobal(gameGlobal), spritePath(spritePath) {}

void Tile::setSelected() { this->selected = true; }
void Tile::unsetSelected() { this->selected = false; }
bool Tile::getSelected() { return this->selected; }

SDL_Texture* Tile::getTileTexture() { return this->texture; }
