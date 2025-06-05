#include <cassert>

#include "gameplay.h"

Gameplay::Gameplay(const GameGlobal& gameGlobal, const EngineState& state)
    : State(gameGlobal, LogFiles::GAMEPLAY, state) {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(this->gameGlobal.window);

  // Initialize the tile map
  this->logger->log("Initializing tile map...");
  this->tileMap = std::make_unique<TileMap>(16, 200, 200, this->gameGlobal.renderer);
  this->logger->log("Tile map initialized");

  // Initialize the camera
  this->logger->log("Initializing camera");
  this->camera = std::make_unique<Camera>(windowSurface->h, windowSurface->w,
                                          this->tileMap->getTotalXTiles(),
                                          this->tileMap->getTotalYTiles(), 16);
  assert(this->camera->getScreenHeight() == windowSurface->h);
  assert(this->camera->getScreenWidth() == windowSurface->w);
  this->logger->log("Camera initialized");

  this->characterFactory = std::make_unique<CharacterFactory>(this->gameGlobal);

  // Initialize NPC
  this->logger->log("Initializing NPC...");
  std::unique_ptr<Character> npc = this->characterFactory->create(characterId::NPC);
  this->npcVector.emplace_back(std::move(npc));
  this->npcVector[0]->setXVelocity(1);
  this->npcVector[0]->setYVelocity(1);
  this->logger->log("NPC initialized");

  this->logger->log("Initializing textures...");
  SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
  selectedTexture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, tmp_surface);
  SDL_FreeSurface(tmp_surface);
  this->logger->log("Textures initialized");
}

void Gameplay::handleEvents(bool& gameIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) { // While events in the queue
    switch (event.type) {
    case SDL_QUIT: // Quit event
      gameIsRunning = false;
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
  checkKeystates();
}

void Gameplay::checkKeystates() {
  const Uint8* keystates = SDL_GetKeyboardState(NULL);

  // Camera movement (arrow keys)
  if (keystates[SDL_SCANCODE_UP]) {
    this->camera->setYVelocity(-128);
  }
  else if (keystates[SDL_SCANCODE_DOWN]) {
    this->camera->setYVelocity(128);
  }
  else if (keystates[SDL_SCANCODE_RIGHT]) {
    this->camera->setXVelocity(128);
  }
  else if (keystates[SDL_SCANCODE_LEFT]) {
    this->camera->setXVelocity(-128);
  }
  else { // No arrow key pressed
    this->camera->setXVelocity(0);
    this->camera->setYVelocity(0);
  }

  // Pause menu
  if (keystates[SDL_SCANCODE_ESCAPE]) {
    // pause
  }
}

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

void Gameplay::update() {
  this->rootElement->update();

  this->logger->log("updating in gameplay");
  this->camera->update(this->tileMap->getTileSize(), this->tileMap->getTotalXTiles(),
                       this->tileMap->getTotalYTiles()); // update camera
  // setSelectedTile();

  this->npcVector[0]->updatePosition();
}

void Gameplay::render() const {
  SDL_RenderClear(this->gameGlobal.renderer);

  int cameraXPosition = this->camera->getXPosition();
  int cameraYPosition = this->camera->getYPosition();
  // std::cout << cameraXPosition << std::endl;

  // Loop through all visible x tiles
  for (int x = 0; x < this->camera->getVisibleXTiles() + 1; x++) {
    // Loop through all visible y tiles
    for (int y = 0; y < this->camera->getVisibleYTiles() + 1; y++) {
      int currentXPosition = x + floor(cameraXPosition / 16);
      int currentYPosition = y + floor(cameraYPosition / 16);

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

void Gameplay::exit() {}
