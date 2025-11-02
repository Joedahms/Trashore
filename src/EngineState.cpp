#include "EngineState.h"

#include <string>

std::string engineStateToString(const EngineState engineState) {
  switch (engineState) {
  case EngineState::MAIN_MENU:
    return "MAIN_MENU";
  case EngineState::GAMEPLAY:
    return "GAMEPLAY";
  default:
    return "UNKNOWN";
  }
}
