#ifndef ELEMENT_H
#define ELEMENT_H

#include <SDL2/SDL.h>
#include <memory>

#include "../../../logger.h"
#include "../display_global.h"
#include "element_mediator.h"

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
  Element(const struct DisplayGlobal& displayGlobal,
          const std::string& logFile,
          const SDL_Rect boundaryRectangle);
  virtual ~Element() = default;
  virtual void addElement(std::shared_ptr<Element> element) {}
  virtual void update();
  virtual void render() const;
  virtual void handleEvent(const SDL_Event& event) = 0;
  virtual void addBoundaryRectangle(std::vector<SDL_Rect>& boundaryRectangles) const;
  virtual void checkCollision(std::vector<SDL_Rect>& boundaryRectangles);

  virtual std::string getContent() const;
  virtual void setContent(const std::string& content) {}

  void setMediator(std::shared_ptr<Mediator> mediator);
  void setParent(Element* parent);

  SDL_Point getPositionRelativeToParent();
  void setPositionRelativeToParent(const SDL_Point& relativePosition);

  SDL_Rect getBoundaryRectangle();
  void setBoundaryRectangle(SDL_Rect boundaryRectangle);

  void setCentered();

  void setCenteredVertical();
  bool checkCenterVertical();

  void setCenteredHorizontal();
  bool checkCenterHorizontal();

  bool checkMouseHovered();

  void addBorder(const int& borderThickness);
  void renderBorder() const;

  Velocity getVelocity();
  void setVelocity(Velocity velocity);
  Acceleration getAcceleration();
  void setAcceleration(Acceleration acceleration);

  int getBorderThickness();
  bool getFixed();
  bool getScreenBoundX();
  bool getScreenBoundY();
  bool getHasCollided();
  void setFixed(bool fixed);
  void setCanCollide(bool canCollide);
  void setCollisionFixed(bool collisionFixed);
  void setGravityAffected(bool gravityAffected);
  void setHasCollided(bool collided);

private:
  void centerVertical();
  void centerHorizontal();

protected:
  struct DisplayGlobal displayGlobal;
  const std::string logFile;
  std::unique_ptr<Logger> logger;
  std::string debugName = "no debug name";

  std::chrono::steady_clock::time_point previousUpdate;
  std::chrono::steady_clock::time_point currentUpdate;

  SDL_Rect boundaryRectangle         = {0, 0, 0, 0};
  SDL_Point positionRelativeToParent = {0, 0};
  Element* parent                    = nullptr;

  bool centerWithinParent           = false;
  bool centerVerticalWithinParent   = false;
  bool centerHorizontalWithinParent = false;

  bool hasBorder      = false;
  int borderThickness = 1;

  bool gravityAffected = false;
  bool fixed           = true;
  bool held            = false;
  bool screenBoundX    = true;
  bool screenBoundY    = true;
  bool canCollide      = false;
  bool collisionFixed  = true;
  bool hasCollided     = false;

  Velocity velocity         = {0, 0};
  Acceleration acceleration = {0, 0};

  std::weak_ptr<Mediator> mediator;

  void setupPosition(const SDL_Rect& boundaryRectangle);
  void hasParentUpdate();
  void updatePosition();
  void checkCollisionImpl(std::vector<SDL_Rect>& boundaryRectangles);
  SDL_Point calculateOverlap(const SDL_Rect boundaryRectangle) const;
  void fixCollision(const SDL_Point overlap, const SDL_Rect boundaryRectangle);
};

#endif
