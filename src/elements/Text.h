#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "../GameGlobal.h"
#include "Element.h"

/**
 * Represents a string of characters that can be rendered.
 */
class Text final : public Element {
public:
  Text(const GameGlobal& gameGlobal,
       const std::string& logFile,
       SDL_FRect boundaryRectangle,
       const std::string& fontPath,
       std::string content,
       int fontSize,
       SDL_Color color);
  ~Text() override;

  void setContent(const std::string& content) override;
  std::string getContent() const override { return this->content; }

  void render() const override;
  void handleEvent(const SDL_Event& event) override;

private:
  TTF_Font* font;
  std::string content;
  int fontSize;
  SDL_Color color;
  SDL_Texture* texture{};

  void setWidthAndHeight();
  void setTexture();
};

#endif
