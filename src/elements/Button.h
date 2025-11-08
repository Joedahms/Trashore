#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <functional>
#include <string>

#include "../GameGlobal.h"
#include "CompositeElement.h"
#include "Element.h"

/**
 * Clickable button containing centered text. Can be set to perform an action upon click.
 */
class Button final : public CompositeElement {
public:
  Button(const GameGlobal& gameGlobal,
         const std::string& logFile,
         SDL_FRect boundaryRectangle,
         std::string textContent,
         SDL_FPoint textPadding,
         std::function<void()> onClick);

  Button(const GameGlobal& gameGlobal,
         const std::string& logFile,
         SDL_FRect boundaryRectangle,
         std::string textContent,
         SDL_FPoint textPadding,
         std::string notifyMessage);

  void updateSelf() override;
  void renderSelf() const override;
  void handleEventSelf(const SDL_Event& event) override;

private:
  std::string textContent;
  SDL_FPoint textPadding = {0, 0};
  std::function<void()> onClick;
  std::string notifyMessage;

  SDL_Color backgroundColor{};
  SDL_Color defaultColor{};
  SDL_Color hoveredColor{};

  void updateColor();
};

#endif
