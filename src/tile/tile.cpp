#include "tile.h"
#include <SDL2/SDL_rect.h>

Tile::Tile(const GameGlobal& gameGlobal, const std::string& spritePath)
    : gameGlobal(gameGlobal), spritePath(spritePath) {}

void Tile::setSelected() { this->selected = true; }
void Tile::unsetSelected() { this->selected = false; }
bool Tile::getSelected() { return this->selected; }

SDL_Texture* Tile::getTileTexture() { return this->texture; }
SDL_Rect Tile::getTileRectangle() { return this->rectangle; }

void Tile::setTileRectangle(const SDL_Rect rectangle) { this->rectangle = rectangle; }
