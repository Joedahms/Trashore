//
// Created by joe on 11/9/25.
//

#ifndef SDLGAMEENGINE_MAINMENURMLEVENTLISTENER_H
#define SDLGAMEENGINE_MAINMENURMLEVENTLISTENER_H

#include <RmlUi/Core/EventListener.h>

class MainMenuRmlEventListener final : public Rml::EventListener {
public:
  void ProcessEvent(Rml::Event& event) override;
};

#endif SDLGAMEENGINE_MAINMENURMLEVENTLISTENER_H
