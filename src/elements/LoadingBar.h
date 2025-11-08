#ifndef LOADING_BAR_H
#define LOADING_BAR_H

#include <SDL3/SDL.h>

#include "Element.h"

class LoadingBar final : public Element {
public:
  LoadingBar(const GameGlobal& gameGlobal,
             const std::string& logFile,
             SDL_FRect boundaryRectangle,
             const int& borderThickness,
             const float& totalTimeSeconds,
             const float& updatePeriodMs);

  void update() override;
  void handleEvent(const SDL_Event& event) override;
  void render() const override;

private:
  SDL_FRect barRectangle{};
  SDL_Color barColor{};
  float totalTimeSeconds;
  float updatePeriodMs;
  int pixelsPerUpdate{};
};

#endif
