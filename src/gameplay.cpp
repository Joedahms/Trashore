#include <SDL2/SDL.h>
#include <assert.h>
#include <iostream>
#include <string>

#include "camera/camera.h"
#include "game_global.h"
#include "gameplay.h"
#include "logger.h"
#include "tile/tile_map.h"

/**
 * @param gameGlobal - Global variables.
 */
Gameplay::Gameplay(struct GameGlobal gameGlobal) { this->gameGlobal = gameGlobal; }

/**
 * Handle all events in the SDL event queue.
 *
 * @param gameIsRunning - Whether or not the game is running.
 * @return - The current state of the game after updating gameplay.
 */
int Gameplay::handleEvents(bool* gameIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) { // While events in the queue
    switch (event.type) {
    case SDL_QUIT: // Quit event
      *gameIsRunning = false;
      break;

    case SDL_MOUSEWHEEL:                          // Mousewheel event
      if (event.wheel.y > 0) {                    // Scroll up -> zoom in
        if (this->tileMap->getTileSize() == 16) { // If not already zoomed in
          this->zoomedIn  = true;
          this->zoomedOut = false;

          this->tileMap->setTileSize(32);
          this->camera->zoomIn(32, this->tileMap->getTotalXTiles(),
                               this->tileMap->getTotalYTiles());
          break;
        }
      }
      else if (event.wheel.y < 0) {               // Scroll down -> zoom out
        if (this->tileMap->getTileSize() == 32) { // If not already zoomed out
          this->zoomedIn  = false;
          this->zoomedOut = true;

          this->tileMap->setTileSize(16);
          this->camera->zoomOut(16, this->tileMap->getTotalXTiles(),
                                this->tileMap->getTotalYTiles());
          break;
        }
      }

    default:
      break;
    }
  }

  // Still in gameplay state
  return 1;
}

/**
 * Perform the appropriate action depending on which keyboard key has been pressed.
 *
 * @param - None
 * @return - The state the game is in after checking if any keys have been pressed.
 */
int Gameplay::checkKeystates() {
  const Uint8* keystates = SDL_GetKeyboardState(NULL);

  // Camera movement (arrow keys)
  if (keystates[SDL_SCANCODE_UP]) {
    this->camera->setYVelocity(-1);
    return 1;
  }
  else if (keystates[SDL_SCANCODE_DOWN]) {
    this->camera->setYVelocity(1);
    return 1;
  }
  else if (keystates[SDL_SCANCODE_RIGHT]) {
    this->camera->setXVelocity(1);
    return 1;
  }
  else if (keystates[SDL_SCANCODE_LEFT]) {
    this->camera->setXVelocity(-1);
    return 1;
  }
  else { // No arrow key pressed
    this->camera->setXVelocity(0);
    this->camera->setYVelocity(0);
  }

  // Pause menu
  if (keystates[SDL_SCANCODE_ESCAPE]) {
    return 2;
  }

  return 1;
}

/**
 * Determines where the mouse is and sets the tile it is over to selected.
 *
 * @param - None
 * @return - None
 */
void Gameplay::setSelectedTile() {
  int X;
  int Y;
  Uint32 mouse = SDL_GetMouseState(&X, &Y);

  int cameraXPosition = this->camera->getXPosition();
  int cameraYPosition = this->camera->getYPosition();

  int selectedXCoordinate = floor(X / this->tileMap->getTileSize()) + cameraXPosition;
  int selectedYCoordinate = floor(Y / this->tileMap->getTileSize()) + cameraYPosition;

  // Unselect all tiles
  for (int x = 0; x < this->camera->getVisibleXTiles() + cameraXPosition; x++) {
    for (int y = 0; y < this->camera->getVisibleYTiles() + cameraYPosition; y++) {
      this->tileMap->unselectTile(x, y);
    }
  }

  this->tileMap->selectTile(selectedXCoordinate, selectedYCoordinate);
}

/**
 * Update the camera and set the selected tile.
 *
 * @param - None
 * @return - None
 */
void Gameplay::update() {
  writeToLogFile(this->gameGlobal.logFile, "updating in gameplay");
  this->camera->update(this->tileMap->getTotalXTiles(),
                       this->tileMap->getTotalYTiles()); // update camera
  setSelectedTile();

  this->npcVector[0]->updatePosition();
}

/**
 * Render all gameplay elements.
 *
 * @param - None
 * @return - None
 */
void Gameplay::render() {
  SDL_RenderClear(this->gameGlobal.renderer);

  int cameraXPosition = this->camera->getXPosition();
  int cameraYPosition = this->camera->getYPosition();

  // Loop through all visible x tiles
  for (int x = 0; x < this->camera->getVisibleXTiles(); x++) {
    // Loop through all visible y tiles
    for (int y = 0; y < this->camera->getVisibleYTiles(); y++) {
      int currentXPosition = x + cameraXPosition;
      int currentYPosition = y + cameraYPosition;

      // Render all visible tiles
      SDL_RenderCopy(this->gameGlobal.renderer,
                     this->tileMap->getTileTexture(currentXPosition, currentYPosition),
                     NULL, &(this->camera->destinationRect[x][y]));

      // If the current tile is selected
      if (this->tileMap->getSelected(currentXPosition, currentYPosition)) {
        // Render selected texture over it
        SDL_RenderCopy(this->gameGlobal.renderer, this->selectedTexture, NULL,
                       &(camera->destinationRect[x][y]));
      }
    }
  }

  this->npcVector[0]->render();

  SDL_RenderPresent(this->gameGlobal.renderer);
}

/**
 * Perform necessary actions when the gameplay state is entered for the first.
 *
 * @param - None
 * @return - None
 */
void Gameplay::enterGameplay() {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);

  // Initialize the tile map
  writeToLogFile(this->gameGlobal.logFile, "Initializing tile map...");
  this->tileMap = std::make_unique<TileMap>(16, 200, 200, this->gameGlobal.renderer);
  writeToLogFile(this->gameGlobal.logFile, "Tile map initialized");

  // Initialize the camera
  writeToLogFile(this->gameGlobal.logFile, "Initializing camera");
  this->camera = std::make_unique<Camera>(windowSurface->h, windowSurface->w,
                                          this->tileMap->getTotalXTiles(),
                                          this->tileMap->getTotalYTiles(), 16);
  assert(this->camera->getScreenHeight() == windowSurface->h);
  assert(this->camera->getScreenWidth() == windowSurface->w);
  writeToLogFile(this->gameGlobal.logFile, "Camera initialized");

  this->characterFactory = std::make_unique<CharacterFactory>(this->gameGlobal);

  // Initialize NPC
  writeToLogFile(this->gameGlobal.logFile, "Initializing NPC...");
  std::unique_ptr<Character> npc = this->characterFactory->create(characterId::NPC);
  this->npcVector.emplace_back(std::move(npc));
  this->npcVector[0]->setXVelocity(1);
  this->npcVector[0]->setYVelocity(1);
  writeToLogFile(this->gameGlobal.logFile, "NPC initialized");

  initializeTextures();

  // State has been entered once
  this->stateEntered = true;
}

/**
 * Initialize all textures in the gameplay state.
 *
 * @param - None
 * @return - None
 */
void Gameplay::initializeTextures() {
  writeToLogFile(this->gameGlobal.logFile, "Initializing textures...");
  SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
  selectedTexture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, tmp_surface);
  SDL_FreeSurface(tmp_surface);
  writeToLogFile(this->gameGlobal.logFile, "Textures initialized");
}

/**
 * Check if the gameplay state has been entered before.
 *
 * @param - None
 * @return - Whether the state has been entered before
 */
bool Gameplay::getStateEntered() { return this->stateEntered; }
