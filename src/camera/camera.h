#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <vector>

/**
 * The camera defines how the game is displayed to the user. It dictates what is
 * visible at any one given time.
 */
class Camera {
public:
  Camera(int, int, int, int, int);

  void setXVelocity(int);
  void setYVelocity(int);

  int getXPosition();
  int getYPosition();

  int getScreenHeight();
  int getScreenWidth();

  void zoomIn(int, int, int);
  void zoomOut(int, int, int);

  void checkBoundries(int, int);

  void update(int, int);

  void zoomChange(int, int, int);

  void shiftDestinationRectVertical();
  void shiftDestinationRectHorizontal();
  SDL_Rect& getDestinationRect(int, int);

  // Needs to be dependent on screen size
  std::vector<std::vector<SDL_Rect>> destinationRect;

  int getVisibleXTiles();
  int getVisibleYTiles();

private:
  int screenHeight;
  int screenWidth;

  int xPosition;
  int yPosition;

  int xVelocity;
  int yVelocity;

  int visibleXTiles;
  int visibleYTiles;
};

#endif
