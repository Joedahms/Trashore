//
// Created by joe on 11/9/25.
//

#ifndef SDLGAMEENGINE_MAINMENURMLEVENTHANDLER_H
#define SDLGAMEENGINE_MAINMENURMLEVENTHANDLER_H
#include "../../EngineState.h"

#include <RmlUi/Core/Event.h>

class MainMenuRmlEventHandler {
public:
  MainMenuRmlEventHandler();
  static void handleEvent(Rml::Event& event);
};

#endif // SDLGAMEENGINE_MAINMENURMLEVENTHANDLER_H
