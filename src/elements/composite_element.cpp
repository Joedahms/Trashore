#include "composite_element.h"
#include "element.h"

CompositeElement::CompositeElement(const struct DisplayGlobal& displayGlobal,
                                   const std::string& logFile,
                                   const SDL_Rect boundaryRectangle)
    : Element(displayGlobal, logFile, boundaryRectangle) {}

/**
 * Update this element then update all of its children.
 *
 * @param None
 * @return None
 */
void CompositeElement::update() {
  updateSelf();
  for (const auto& element : this->children) {
    element->update();
  }
}

/**
 * Default updateSelf for a composite element. If a child of another composite element,
 * perform updates relating to being a child.
 *
 * @param None
 * @return None
 */
void CompositeElement::updateSelf() {
  if (parent) {
    hasParentUpdate();
  }
}

/**
 * Add an element to the composite and ensure that the new element's parent is set to
 * this.
 *
 * @param element The new element to be added to the composite
 * @return None
 */
void CompositeElement::addElement(std::shared_ptr<Element> element) {
  SDL_Rect elementRect = element->getBoundaryRectangle();
  if (elementRect.w == 0) {
    elementRect.w = this->boundaryRectangle.w;
    element->setBoundaryRectangle(elementRect);
  }

  Element* childPointer = element.get();
  childPointer->setParent(this);

  this->children.push_back(std::move(element));
}

/**
 * Render this element then render all of its children.
 *
 * @param None
 * @return None
 */
void CompositeElement::render() const {
  renderSelf();
  for (const auto& element : this->children) {
    element->render();
  }
}

void CompositeElement::renderSelf() const {
  if (this->hasBorder) {
    renderBorder();
  }
}

/**
 * Handle the event then ask all children to handle the event.
 *
 * @param event The SDL event that occured.
 * @return None
 */
void CompositeElement::handleEvent(const SDL_Event& event) {
  handleEventSelf(event);
  for (const auto& element : this->children) {
    element->handleEvent(event);
  }
}

void CompositeElement::addBoundaryRectangle(
    std::vector<SDL_Rect>& boundaryRectangles) const {
  if (this->canCollide) {
    addBoundaryRectangleSelf(boundaryRectangles);
  }
  for (const auto& element : this->children) {
    element->addBoundaryRectangle(boundaryRectangles);
  }
}

void CompositeElement::addBoundaryRectangleSelf(
    std::vector<SDL_Rect>& boundaryRectangles) const {
  boundaryRectangles.push_back(this->boundaryRectangle);
}

void CompositeElement::checkCollision(std::vector<SDL_Rect>& boundaryRectangles) {
  if (this->canCollide) {
    checkCollisionImpl(boundaryRectangles);
  }
  for (auto& element : this->children) {
    element->checkCollision(boundaryRectangles);
  }
}

/**
 * Remove all child elements from this composite element.
 * This will destroy elements if this composite holds the last reference.
 *
 * @param None
 * @return None
 */
void CompositeElement::removeAllChildren() {
  for (auto& child : this->children) {
    if (child) {
      child->setParent(nullptr);
    }
  }

  this->children.clear();
}

void CompositeElement::containChildren() {
  for (auto& child : this->children) {
    SDL_Rect childRect              = child->getBoundaryRectangle();
    SDL_Point childRelativePosition = child->getPositionRelativeToParent();
    Velocity childVelocity          = child->getVelocity();

    if (childRect.y + childRect.h >
        this->boundaryRectangle.y + this->boundaryRectangle.h) {
      childRelativePosition.y--;
      childVelocity.y = 0;
    }

    child->setBoundaryRectangle(childRect);
    child->setPositionRelativeToParent(childRelativePosition);
    child->setVelocity(childVelocity);
  }
}
