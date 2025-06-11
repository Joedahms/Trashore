#ifndef GUI_BOX_H
#define GUI_BOX_H

#include "composite_element.h"

class GuiBox : public CompositeElement {
public:
  GuiBox(const GameGlobal& gameGlobal,
         const std::string& logFile,
         const SDL_Rect boundaryRectangle);

private:
  void handleEventSelf(const SDL_Event& event) override;
  void renderSelf() const override;
};

#endif
