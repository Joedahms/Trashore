#include "gui_box.h"

GuiBox::GuiBox(const GameGlobal& gameGlobal,
               const std::string& logFile,
               const SDL_Rect boundaryRectangle)
    : CompositeElement(gameGlobal, logFile, boundaryRectangle) {}

void GuiBox::handleEventSelf(const SDL_Event& event) {}

void GuiBox::renderSelf() const {
  // Set draw color and fill the button
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(this->gameGlobal.renderer, &this->boundaryRectangle);
}
