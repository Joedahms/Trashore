#include "engine_state.h"

std::string engineStateToString(EngineState engineState) {
  switch (engineState) {
  case EngineState::MAIN_MENU:
    return "MAIN_MENU";
  case EngineState::GAMEPLAY:
    return "GAMEPLAY";
  default:
    return "UNKNOWN";
  }
}
