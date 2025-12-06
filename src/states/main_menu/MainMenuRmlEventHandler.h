#ifndef SDLGAMEENGINE_MAINMENURMLEVENTHANDLER_H
#define SDLGAMEENGINE_MAINMENURMLEVENTHANDLER_H

#include <RmlUi/Core/Event.h>

class MainMenuRmlEventHandler {
public:
  MainMenuRmlEventHandler();
  static void handleEvent(Rml::Event& event);
};

#endif
