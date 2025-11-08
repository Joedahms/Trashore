#ifndef BIRD_H
#define BIRD_H

#include "../Element.h"

class Bird : public Element {
public:
  Bird(const struct GameGlobal& gameGlobal,
       const std::string& logFile,
       const SDL_Rect boundaryRectangle);
  void handleEvent(const SDL_Event& event) override;
  void render() const override;

private:
  SDL_Texture* texture;
};

#endif
