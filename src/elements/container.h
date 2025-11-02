#ifndef CONTAINER_H
#define CONTAINER_H

#include "composite_element.h"

/**
 * A simple composite element that just contains other elements without adding any of its
 * own functionality. Useful as a root element of an element hierarchy.
 */
class Container : public CompositeElement {
public:
  Container(const GameGlobal& gameGlobal,
            const std::string& logFile,
            SDL_Rect boundaryRectangle);
  void update() override;
  void handleEventSelf(const SDL_Event& event) override;

private:
  void checkElementPositionX(std::shared_ptr<Element> element) const;
  void checkElementPositionY(const std::shared_ptr<Element>& element) const;
};

#endif
