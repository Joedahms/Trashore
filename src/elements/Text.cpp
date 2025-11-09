#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include <utility>

#include "Element.h"
#include "Text.h"

Text::Text(const GameGlobal& gameGlobal,
           const std::string& logFile,
           const SDL_FRect boundaryRectangle,
           const std::string& fontPath,
           std::string content,
           const int fontSize,
           const SDL_Color color)
    : Element(gameGlobal, logFile, boundaryRectangle), content(std::move(content)),
      fontSize(fontSize), color(color) {
  this->font = TTF_OpenFont(fontPath.c_str(), this->fontSize);
  if (this->font == nullptr) {
    std::cerr << "Text failed to open font " << SDL_GetError();
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

  SDL_Surface* textSurface = TTF_RenderText_Solid(
      this->font, this->content.c_str(), sizeof(this->content.c_str()), this->color);
  this->texture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, textSurface);
  SDL_DestroySurface(textSurface);
}

void Text::render() const {
  SDL_RenderTexture(this->gameGlobal.renderer, this->texture, NULL,
                    &this->boundaryRectangle);
}

void Text::handleEvent(const SDL_Event& event) {}

// TODO: Figure out how to set width and height
void Text::setWidthAndHeight() {
  // Query texture is no longer available in SDL3. I could try to find a way to replicate
  // this behavior with something in SDL3 but since I plan on switching to SDL_GPU, this
  // might not even matter.
  /*
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->boundaryRectangle.w,
                   &this->boundaryRectangle.h);
                   */
}

void Text::setTexture() {
  SDL_Surface* textSurface = TTF_RenderText_Solid(
      this->font, this->content.c_str(), sizeof(this->content.c_str()), this->color);
  this->texture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, textSurface);
  SDL_DestroySurface(textSurface);
}
