#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "../display_global.h"
#include "element.h"

/**
 * Represents a string of characters that can be rendered.
 */
class Text : public Element {
public:
  Text(const struct DisplayGlobal& displayGlobal,
       const std::string& logFile,
       const SDL_Rect boundaryRectangle,
       const std::string& fontPath,
       const std::string& content,
       const int fontSize,
       const SDL_Color color);
  ~Text();

  void setContent(const std::string& content) override;
  std::string getContent() const override { return this->content; }

  void render() const override;
  void handleEvent(const SDL_Event& event);

private:
  TTF_Font* font;
  std::string content;
  int fontSize;
  SDL_Color color;
  SDL_Texture* texture;
};

#endif
