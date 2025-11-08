#include "Tile.h"
#include <SDL3/SDL_rect.h>

#include <utility>

Tile::Tile(const GameGlobal& gameGlobal, std::string spritePath)
    : gameGlobal(gameGlobal), spritePath(std::move(spritePath)) {}

void Tile::setSelected() { this->selected = true; }
void Tile::unsetSelected() { this->selected = false; }
bool Tile::getSelected() const { return this->selected; }

SDL_Texture* Tile::getTileTexture() const { return this->texture; }
SDL_Rect Tile::getTileRectangle() const { return this->rectangle; }

void Tile::setTileRectangle(const SDL_Rect rectangle) { this->rectangle = rectangle; }
