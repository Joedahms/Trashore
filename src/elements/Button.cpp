#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <utility>

#include "../GameGlobal.h"
#include "Button.h"
#include "Element.h"
#include "Text.h"

/**
 * @param gameGlobal Global display variables
 * @param logFile Name of log file
 * @param boundaryRectangle Rectangle to describe the position relative to parent element
 * as well as the width and height. The x and y parameters of the rectangle are used as
 * the position relative to the parent.
 * @param textContent The text to print in the middle of the button
 * @param textPadding How offset the text should be from parent
 * @param onClick The callback function to execute when the button is clicked
 */
Button::Button(const GameGlobal& gameGlobal,
               const std::string& logFile,
               const SDL_Rect boundaryRectangle,
               std::string textContent,
               const SDL_Point textPadding,
               std::function<void()> onClick)
    : CompositeElement(gameGlobal, logFile, boundaryRectangle),
      textContent(std::move(textContent)), textPadding(textPadding),
      onClick(std::move(onClick)) {
  this->logger->log("Constructing " + this->textContent + " button");

  this->backgroundColor = {255, 0, 0, 255}; // Red
  this->hoveredColor    = {0, 255, 0, 255}; // Green
  this->defaultColor    = {255, 0, 0, 255}; // Red

  SDL_Color textColor = {255, 255, 0, 255}; // Yellow
  SDL_Rect textRect   = {textPadding.x, textPadding.y, 0, 0};
  auto text           = std::make_shared<Text>(this->gameGlobal, this->logFile, textRect,
                                               GameGlobal::futuramFontPath,
                                               this->textContent.c_str(), 24, textColor);
  text->setCentered();

  if (this->boundaryRectangle.w == 0 && this->boundaryRectangle.h == 0) {
    const SDL_Rect textBoundaryRectangle = text->getBoundaryRectangle();
    this->boundaryRectangle.w            = textBoundaryRectangle.w + textPadding.x;
    this->boundaryRectangle.h            = textBoundaryRectangle.h + textPadding.y;
  }

  CompositeElement::addElement(std::move(text));
  this->logger->log(this->textContent + " button constructed");
}

/**
 * Change color if the cursor is hovered over the button.
 */
void Button::updateSelf() {
  if (parent) {
    hasParentUpdate();
  }

  updateColor();
}

/**
 * Render the background color
 */
void Button::renderSelf() const {
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, backgroundColor.r, backgroundColor.g,
                         backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(this->gameGlobal.renderer, &this->boundaryRectangle);
}

/**
 * If the user is hovered over the button when a click event occurs, call the callback
 * function.
 *
 * @param event An SDL event that has occured.
 */
void Button::handleEventSelf(const SDL_Event& event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (checkMouseHovered()) {
      this->logger->log(this->textContent + " button clicked");
      onClick();
      this->logger->log(this->textContent + " button click callback successful");
    }
  }
}

/**
 * Choose background color based on mouse position.
 */
void Button::updateColor() {
  if (checkMouseHovered()) {
    this->logger->log(this->textContent + " button hovered");
    this->backgroundColor = this->hoveredColor;
  }
  else {
    this->backgroundColor = this->defaultColor;
  }
}
