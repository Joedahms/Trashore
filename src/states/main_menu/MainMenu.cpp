#include <memory>

#include "../../GameGlobal.h"
#include "../../LogFiles.h"
#include "../../elements/Button.h"
#include "MainMenu.h"

#include <RmlUi/Core/Element.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/ID.h>
#include <iostream>

/**
 * @param gameGlobal Global display variables.
 */
MainMenu::MainMenu(const GameGlobal& gameGlobal)
    : State(gameGlobal, LogFiles::MAIN_MENU) {
  this->logger->log("Constructing main menu state");

  this->document = this->gameGlobal.rmlContext->LoadDocument("../rml/menu.html");

  if (this->document) {
    this->document->Show();
  }
  else {
    std::cerr << "Failed to load document";
  }

  this->eventListener = std::make_unique<MainMenuRmlEventListener>();

  this->startButton = this->document->GetElementById("start_game");
  if (this->startButton) {
    this->startButton->AddEventListener(Rml::EventId::Click, this->eventListener.get(),
                                        true);
  }
  else {
    Rml::Log::Message(Rml::Log::LT_WARNING, "No");
  }

  this->quitButton = this->document->GetElementById("quit");
  if (this->quitButton) {
    this->quitButton->AddEventListener(Rml::EventId::Click, this->eventListener.get(),
                                       true);
  }
  else {
    Rml::Log::Message(Rml::Log::LT_WARNING, "No");
  }

  this->logger->log("Main menu state constructed");
}

void MainMenu::update() { this->gameGlobal.rmlContext->Update(); }

void MainMenu::render() const {
  SDL_SetRenderDrawColor(this->gameGlobal.renderer, 0, 0, 0, 255); // Black background
  SDL_RenderClear(this->gameGlobal.renderer);
  this->rootElement->render();
  this->gameGlobal.rmlContext->Render();
  SDL_RenderPresent(this->gameGlobal.renderer);
}