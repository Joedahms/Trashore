#ifndef ELEMENT_H
#define ELEMENT_H

#include <SDL2/SDL.h>
#include <memory>

#include "../GameGlobal.h"
#include "../Logger.h"

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
  Element(const GameGlobal& gameGlobal, std::string logFile, SDL_Rect boundaryRectangle);
  virtual ~Element() = default;
  virtual void addElement(std::shared_ptr<Element> element) {}
  virtual void update();
  virtual void render() const;
  virtual void handleEvent(const SDL_Event& event) = 0;
  virtual void addBoundaryRectangle(std::vector<SDL_Rect>& boundaryRectangles) const;
  virtual void checkCollision(std::vector<SDL_Rect>& boundaryRectangles);

  virtual std::string getContent() const;
  virtual void setContent(const std::string& content) {}

  void setParent(Element* newParent);

  SDL_Point getPositionRelativeToParent() const;
  void setPositionRelativeToParent(const SDL_Point& relativePosition);

  SDL_Rect getBoundaryRectangle() const;
  void setBoundaryRectangle(SDL_Rect newBoundaryRectangle);

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
  bool getFixed() const;
  bool getScreenBoundX() const;
  bool getScreenBoundY() const;
  bool getHasCollided() const;
  void setFixed(bool newFixed);
  void setCanCollide(bool newCanCollide);
  void setCollisionFixed(bool newCollisionFixed);
  void setGravityAffected(bool newGravityAffected);
  void setHasCollided(bool collided);

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
  bool screenBoundX    = true;
  bool screenBoundY    = true;
  bool canCollide      = false;
  bool collisionFixed  = true;
  bool hasCollided     = false;

  Velocity velocity         = {0, 0};
  Acceleration acceleration = {0, 0};

  void setupPosition(const SDL_Rect& newBoundaryRectangle);
  void hasParentUpdate();
  void updatePosition();
  void checkCollisionImpl(const std::vector<SDL_Rect>& boundaryRectangles);
  SDL_Point calculateOverlap(SDL_Rect overlappingWithBoundaryRectangle) const;
  void fixCollision(SDL_Point overlap, SDL_Rect collidedWithBoundaryRectangle);
};

#endif
