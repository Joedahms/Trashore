#ifndef ELEMENT_H
#define ELEMENT_H

#include <SDL3/SDL.h>
#include <memory>

#include "../GameGlobal.h"
#include "../Logger.h"

#include <vector>

struct Velocity {
  float x;
  float y;
};

struct Acceleration {
  float x;
  float y;
};

/**
 * Defines the interface for an SDL element. This is any basic shape or texture to be
 * rendered to the screen.
 */
class Element : public std::enable_shared_from_this<Element> {
public:
  Element(const GameGlobal& gameGlobal, std::string logFile, SDL_FRect boundaryRectangle);
  virtual ~Element() = default;
  virtual void addElement(const std::shared_ptr<Element> element) {}
  virtual void update();
  virtual void render() const;
  virtual void handleEvent(const SDL_Event& event) = 0;
  virtual void addBoundaryRectangle(std::vector<SDL_FRect>& boundaryRectangles) const;

  virtual std::string getContent() const;
  virtual void setContent(const std::string& content) {}

  void setParent(Element* newParent);

  SDL_FPoint getPositionRelativeToParent() const;
  void setPositionRelativeToParent(const SDL_FPoint& relativePosition);

  SDL_FRect getBoundaryRectangle() const;
  void setBoundaryRectangle(SDL_FRect newBoundaryRectangle);

  void setCentered();

  void setCenteredVertical();
  bool checkCenterVertical() const;

  void setCenteredHorizontal();
  bool checkCenterHorizontal() const;

  bool checkMouseHovered() const;

  void addBorder(const int& newBorderThickness);
  void renderBorder() const;

  Velocity getVelocity() const;
  void setVelocity(Velocity newVelocity);
  Acceleration getAcceleration() const;
  void setAcceleration(Acceleration newAcceleration);

  int getBorderThickness() const;
  bool getScreenBoundX() const;
  bool getScreenBoundY() const;

private:
  void centerVertical();
  void centerHorizontal();

protected:
  GameGlobal gameGlobal;
  const std::string logFile;
  std::unique_ptr<Logger> logger;
  std::string debugName = "no debug name";

  std::chrono::steady_clock::time_point previousUpdate;
  std::chrono::steady_clock::time_point currentUpdate;

  SDL_FRect boundaryRectangle         = {0, 0, 0, 0};
  SDL_FPoint positionRelativeToParent = {0, 0};
  Element* parent                     = nullptr;

  bool centerWithinParent           = false;
  bool centerVerticalWithinParent   = false;
  bool centerHorizontalWithinParent = false;

  bool hasBorder      = false;
  int borderThickness = 1;

  bool screenBoundX = true;
  bool screenBoundY = true;

  Velocity velocity         = {0, 0};
  Acceleration acceleration = {0, 0};

  void setupPosition(const SDL_FRect& newBoundaryRectangle);
  void hasParentUpdate();
  void updatePosition();
};

#endif
