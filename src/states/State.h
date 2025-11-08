#ifndef STATE_H
#define STATE_H

#include <memory>

#include "../EngineState.h"
#include "../GameGlobal.h"
#include "../LogFiles.h"
#include "../elements/Container.h"

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
