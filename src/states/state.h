#ifndef STATE_H
#define STATE_H

#include <memory>

#include "../elements/container.h"
#include "../engine_state.h"
#include "../game_global.h"
#include "../log_files.h"

class State {
public:
  virtual ~State() = default;
  State(const GameGlobal& gameGlobal,
        std::string logFile,
        const EngineState& currentState);
  virtual void handleEvents(bool& gameIsRunning);
  virtual void update();
  virtual void render() const = 0;
  virtual void enter();
  virtual void exit() = 0;

  EngineState getCurrentState() const;
  void setCurrentState(EngineState newCurrentState);

  bool checkStateChange() const;

protected:
  GameGlobal gameGlobal;
  const std::string logFile;
  std::unique_ptr<Logger> logger;

  const EngineState defaultState;
  EngineState currentState;

  std::shared_ptr<Container> rootElement;
  SDL_Surface* windowSurface = nullptr;
};

#endif
