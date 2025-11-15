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
  State(const GameGlobal& gameGlobal, std::string logFile);
  virtual void handleEvents(bool& gameIsRunning);
  virtual void update();
  virtual void render() const = 0;

protected:
  GameGlobal gameGlobal;
  const std::string logFile;
  std::unique_ptr<Logger> logger;

  std::shared_ptr<Container> rootElement;
  SDL_Surface* windowSurface = nullptr;
};

#endif
