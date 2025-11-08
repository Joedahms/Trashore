#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../GameGlobal.h"
#include "State.h"

class MainMenu final : public State {
public:
  MainMenu(const GameGlobal& gameGlobal, const EngineState& state);
  void render() const override;
};

#endif
