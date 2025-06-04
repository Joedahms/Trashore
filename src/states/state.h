#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

#include "../elements/container.h"
#include "../engine_state.h"
#include "../game_global.h"
#include "../log_files.h"

class State {
public:
  State(const GameGlobal& gameGlobal,
        const std::string& logFile,
        const EngineState& state);
  virtual void handleEvents(bool* displayIsRunning);
  virtual void update();
  virtual void render() const = 0;
  virtual void enter();
  virtual void exit() = 0;

  EngineState getCurrentState();
  void setCurrentState(EngineState currentState);

  bool checkStateChange();

protected:
  struct GameGlobal gameGlobal;
  const std::string logFile;
  std::unique_ptr<Logger> logger;

  const EngineState defaultState;
  EngineState currentState;

  std::shared_ptr<Container> rootElement;
  SDL_Surface* windowSurface = nullptr;
};

#endif
