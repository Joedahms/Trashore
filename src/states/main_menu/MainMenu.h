#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../../GameGlobal.h"
#include "../State.h"
#include "MainMenuRmlEventHandler.h"
#include "MainMenuRmlEventListener.h"

class MainMenu final : public State {
public:
  MainMenu(const GameGlobal& gameGlobal);
  void update() override;
  void render() const override;

private:
  Rml::ElementDocument* document;
  Rml::Element* startButton = nullptr;
  std::unique_ptr<MainMenuRmlEventListener> eventListener;
  MainMenuRmlEventHandler* eventHandler = nullptr;
};

#endif
