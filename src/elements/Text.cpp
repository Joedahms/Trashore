#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <utility>

#include "../SdlDebug.h"
#include "Element.h"
#include "Text.h"

Text::Text(const GameGlobal& gameGlobal,
           const std::string& logFile,
           const SDL_Rect boundaryRectangle,
           const std::string& fontPath,
           std::string content,
           const int fontSize,
           const SDL_Color color)
    : Element(gameGlobal, logFile, boundaryRectangle), content(std::move(content)),
      fontSize(fontSize), color(color) {
  this->font = TTF_OpenFont(fontPath.c_str(), this->fontSize);
  if (this->font == nullptr) {
    std::cerr << "Text failed to open font";
    exit(1);
  }

  setTexture();
  setWidthAndHeight();
}

Text::~Text() {
  SDL_DestroyTexture(this->texture);
  TTF_CloseFont(this->font);
}

void Text::setContent(const std::string& content) {
  this->content = content;

  if (this->texture) {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }

  SDL_Surface* textSurface =
      TTF_RenderText_Solid(this->font, this->content.c_str(), this->color);
  this->texture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, textSurface);
  SDL_FreeSurface(textSurface);
}

void Text::render() const {
  SDL_RenderCopy(this->gameGlobal.renderer, this->texture, NULL,
                 &this->boundaryRectangle);
}

void Text::handleEvent(const SDL_Event& event) {}

void Text::setWidthAndHeight() {
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->boundaryRectangle.w,
                   &this->boundaryRectangle.h);
}

void Text::setTexture() {
  SDL_Surface* textSurface =
      TTF_RenderText_Solid(this->font, this->content.c_str(), this->color);
  this->texture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, textSurface);
  SDL_FreeSurface(textSurface);
}
