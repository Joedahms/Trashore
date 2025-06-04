#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>

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

  std::shared_ptr<Text> title = std::make_shared<Text>(
      this->gameGlobal, this->logFile, SDL_Rect{0, 100, 0, 0},
      GameGlobal::futuramFontPath, "TRASHORE", 24, SDL_Color{0, 255, 0, 0});
  title->setCenteredHorizontal();
  rootElement->addElement(std::move(title));

  // Start Scan
  SDL_Rect newScanButtonRectangle       = {200, 150, 200, 50};
  std::shared_ptr<Button> newScanButton = std::make_shared<Button>(
      this->gameGlobal, this->logFile, newScanButtonRectangle, "Start Game",
      SDL_Point{10, 10}, [this]() { this->currentState = EngineState::GAMEPLAY; });
  newScanButton->setCenteredHorizontal();
  rootElement->addElement(std::move(newScanButton));

  this->logger->log("Main menu state constructed");
}

void MainMenu::render() const {
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 0, 0, 0, 255); // Black background
  SDL_RenderClear(this->gameGlobal.renderer);
  this->rootElement->render();
  SDL_RenderPresent(this->gameGlobal.renderer);
}

void MainMenu::exit() {}
