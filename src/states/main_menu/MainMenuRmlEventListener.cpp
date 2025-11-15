#include "MainMenuRmlEventListener.h"

#include "MainMenuRmlEventHandler.h"

#include <RmlUi/Core/Element.h>

void MainMenuRmlEventListener::ProcessEvent(Rml::Event& event) {
  Rml::Log::Message(Rml::Log::LT_WARNING, "Test warning.");
  MainMenuRmlEventHandler::handleEvent(event);
}
