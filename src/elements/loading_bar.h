#ifndef LOADING_BAR_H
#define LOADING_BAR_H

#include <SDL2/SDL.h>

#include "element.h"

class LoadingBar : public Element {
public:
  LoadingBar(const struct DisplayGlobal& displayGlobal,
             const std::string& logFile,
             const SDL_Rect boundaryRectangle,
             const int& borderThickness,
             const float& totalTimeSeconds,
             const float& updatePeriodMs);

  void update() override;
  void handleEvent(const SDL_Event& event) override;
  void render() const override;

private:
  SDL_Rect barRectangle;
  SDL_Color barColor;
  float totalTimeSeconds;
  float updatePeriodMs;
  int pixelsPerUpdate;

  SDL_Point previousMotion = {0, 0};

  void handleMouseDown();
  void handleMouseMotion(const SDL_Event& event);
  void handleMouseUp();
};

#endif
