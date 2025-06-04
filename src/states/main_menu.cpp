#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>

// #include "../elements/dropdown.h"
// #include "../elements/panel.h"
// #include "../elements/scroll_box.h"
#include "../elements/button.h"
#include "../elements/text.h"
#include "../game_global.h"
#include "../log_files.h"
#include "main_menu.h"

/**
 * @param gameGlobal Global display variables.
 */
MainMenu::MainMenu(const GameGlobal& gameGlobal, const EngineState& state)
    : State(gameGlobal, LogFiles::MAIN_MENU, state) {
  this->logger->log("Constructing main menu state");

  // Start Scan
  SDL_Rect newScanButtonRectangle       = {200, 150, 200, 50};
  std::shared_ptr<Button> newScanButton = std::make_shared<Button>(
      this->gameGlobal, this->logFile, newScanButtonRectangle, "Scan New Item",
      SDL_Point{10, 10}, [this]() { /*this->currentState =*/});
  newScanButton->setCenteredHorizontal();
  rootElement->addElement(std::move(newScanButton));

  /*
  // Scrollbox
  SDL_Rect scrollBoxRect = {0, 0, 400, 100};
  int windowWidth, windowHeight;
  SDL_GetWindowSize(this->gameGlobal.window, &windowWidth, &windowHeight);
  scrollBoxRect.h = windowHeight - 1;
  std::shared_ptr<ScrollBox> scrollBox =
      std::make_shared<ScrollBox>(this->gameGlobal, this->logFile, scrollBoxRect);

  scrollBox->setPanelHeight(30);
  scrollBox->addBorder(1);
  this->mediator->addScrollBox(scrollBox);
  this->rootElement->addElement(std::move(scrollBox));
  this->rootElement->update();
  */

  /*
  // Dropdown
  std::shared_ptr<Dropdown> sortBy = std::make_shared<Dropdown>(
      this->gameGlobal, this->logFile, SDL_Rect{450, 0, 0, 0}, "Sort by:");

  std::shared_ptr<Button> sortByExpirationLowToHigh = std::make_shared<Button>(
      this->gameGlobal, this->logFile, SDL_Rect{0, 0, 0, 0},
      "Expiration Date - Lowest to Highest", SDL_Point{0, 0}, "low to high");
  sortByExpirationLowToHigh->initialize();
  this->mediator->addButton(sortByExpirationLowToHigh);

  std::shared_ptr<Button> sortByExpirationHighToLow = std::make_shared<Button>(
      this->gameGlobal, this->logFile, SDL_Rect{0, 0, 0, 0},
      "Expiration Date - Highest to Lowest", SDL_Point{0, 0}, "high to low");
  sortByExpirationHighToLow->initialize();
  this->mediator->addButton(sortByExpirationHighToLow);

  sortBy->addOption(std::move(sortByExpirationLowToHigh));
  sortBy->update();
  sortBy->addOption(std::move(sortByExpirationHighToLow));
  this->rootElement->addElement(std::move(sortBy));
  */

  this->logger->log("Item list state constructed");
}

void MainMenu::handleEvents(bool* displayIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) { // While there are events in the queue
    if (event.type == SDL_QUIT) {
      *displayIsRunning = false;
      break;
    }
    else {
      this->rootElement->handleEvent(event);
    }
  }
  // this->displayMessenger.ignoreVision();
}

void MainMenu::render() const {
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 0, 0, 0, 255); // Black background
  SDL_RenderClear(this->gameGlobal.renderer);
  this->rootElement->render();
  SDL_RenderPresent(this->gameGlobal.renderer);
}

void MainMenu::exit() {}
