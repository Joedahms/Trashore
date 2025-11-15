//
// Created by joe on 11/9/25.
//

#include "MainMenuRmlEventHandler.h"

#include "../../GameEngine.h"

#include <RmlUi/Core/Element.h>

void MainMenuRmlEventHandler::handleEvent(Rml::Event& event) {
  if (event.GetId() == Rml::EventId::Click) {
    Rml::String buttonId = event.GetCurrentElement()->GetId();

    Rml::Log::Message(Rml::Log::LT_WARNING, buttonId.c_str());

    if (buttonId == "start_game") {
      GameEngine::setCurrentState(EngineState::GAMEPLAY);
    }
    else if (buttonId == "quit") {
      GameEngine::gameIsRunning = false;
    }
  }
}
