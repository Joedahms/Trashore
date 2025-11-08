#include "Container.h"

Container::Container(const GameGlobal& gameGlobal,
                     const std::string& logFile,
                     const SDL_FRect boundaryRectangle)
    : CompositeElement(gameGlobal, logFile, boundaryRectangle) {}

void Container::update() {
  updateSelf();

  for (const auto& element : this->children) {
    element->update();
    if (element->getScreenBoundX()) {
      checkElementPositionX(element);
    }
    if (element->getScreenBoundY()) {
      checkElementPositionY(element);
    }
  }
}

void Container::checkElementPositionX(std::shared_ptr<Element> element) const {
  Velocity elementVelocity                   = element->getVelocity();
  const int elementBorderThickness           = element->getBorderThickness();
  SDL_FPoint elementPositionRelativeToParent = element->getPositionRelativeToParent();
  const SDL_FRect elementBoundaryRectangle   = element->getBoundaryRectangle();

  // Left
  if (elementPositionRelativeToParent.x - elementBorderThickness < 0) {
    elementVelocity.x = 0;
    element->setVelocity(elementVelocity);

    elementPositionRelativeToParent.x = elementBorderThickness;
    element->setPositionRelativeToParent(elementPositionRelativeToParent);
  }

  // Right
  const float elementRightEdge = elementPositionRelativeToParent.x +
                                 elementBoundaryRectangle.w + elementBorderThickness;
  if (elementRightEdge > this->boundaryRectangle.x + this->boundaryRectangle.w) {
    elementVelocity.x = 0;
    element->setVelocity(elementVelocity);

    elementPositionRelativeToParent.x =
        this->boundaryRectangle.x + this->boundaryRectangle.w -
        elementBoundaryRectangle.w - elementBorderThickness;
    element->setPositionRelativeToParent(elementPositionRelativeToParent);
  }
}

void Container::checkElementPositionY(const std::shared_ptr<Element>& element) const {
  Velocity elementVelocity                   = element->getVelocity();
  const int elementBorderThickness           = element->getBorderThickness();
  SDL_FPoint elementPositionRelativeToParent = element->getPositionRelativeToParent();
  const SDL_FRect elementBoundaryRectangle   = element->getBoundaryRectangle();

  // Top
  if (elementPositionRelativeToParent.y - elementBorderThickness < 0) {
    elementVelocity.y = 0;
    element->setVelocity(elementVelocity);

    elementPositionRelativeToParent.y = elementBorderThickness;
    element->setPositionRelativeToParent(elementPositionRelativeToParent);
  }

  // Bottom
  const int elementBottomEdge = elementPositionRelativeToParent.y +
                                elementBoundaryRectangle.h + elementBorderThickness;
  if (elementBottomEdge > this->boundaryRectangle.y + this->boundaryRectangle.h) {
    elementVelocity.y = 0;
    element->setVelocity(elementVelocity);

    elementPositionRelativeToParent.y =
        this->boundaryRectangle.y + this->boundaryRectangle.h -
        elementBoundaryRectangle.h - elementBorderThickness;
    element->setPositionRelativeToParent(elementPositionRelativeToParent);
  }
}

void Container::handleEventSelf(const SDL_Event& event) {}
