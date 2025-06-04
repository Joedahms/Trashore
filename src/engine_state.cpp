#include "engine_state.h"

std::string engineStateToString(EngineState engineState) {
  switch (engineState) {
  case EngineState::MAIN_MENU:
    return "MAIN_MENU";
  default:
    return "UNKNOWN";
  }
}
