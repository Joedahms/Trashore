#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <chrono>

#include "../game_global.h"
#include "state.h"

class MainMenu : public State {
public:
  MainMenu(const GameGlobal& gameGlobal, const EngineState& state);
  void handleEvents(bool* displayIsRunning) override;
  void render() const override;
  void exit() override;
};

#endif
