#include "../elements/button.h"
#include "gui_box.h"

GuiBox::GuiBox(const GameGlobal& gameGlobal,
               const std::string& logFile,
               const SDL_Rect boundaryRectangle)
    : CompositeElement(gameGlobal, logFile, boundaryRectangle) {
  std::shared_ptr<Button> buildWall = std::make_shared<Button>(
      gameGlobal, logFile, SDL_Rect{5, 5, 0, 0}, "wall", SDL_Point{5, 5}, "hi");
  addElement(std::move(buildWall));
}

void GuiBox::handleEventSelf(const SDL_Event& event) {}

void GuiBox::renderSelf() const {
  // Set draw color and fill the button
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 128, 128, 128, 255);
  SDL_RenderFillRect(this->gameGlobal.renderer, &this->boundaryRectangle);
}
