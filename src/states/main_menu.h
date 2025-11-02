#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../game_global.h"
#include "state.h"

class MainMenu final : public State {
public:
  MainMenu(const GameGlobal& gameGlobal, const EngineState& state);
  void render() const override;
  void exit() override;
};

#endif
