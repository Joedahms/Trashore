#include <cassert>

#include "gameplay.h"

Gameplay::Gameplay(const GameGlobal& gameGlobal, const EngineState& state)
    : State(gameGlobal, LogFiles::GAMEPLAY, state) {
  this->logger->log("Initializing tile map...");
  this->tileMap = std::make_unique<TileMap>(gameGlobal, this->MAP_SIZE_TILES,
                                            this->INITIAL_TILE_SIZE);
  this->logger->log("Tile map initialized");

  this->logger->log("Initializing camera");
  this->camera =
      std::make_unique<Camera>(gameGlobal, this->MAP_SIZE_TILES, this->INITIAL_TILE_SIZE);
  this->logger->log("Camera initialized");

  this->characterFactory = std::make_unique<CharacterFactory>(this->gameGlobal);

  this->logger->log("Initializing NPC...");
  std::unique_ptr<Character> npc = this->characterFactory->create(characterId::NPC);
  this->npcVector.emplace_back(std::move(npc));
  this->npcVector[0]->setXVelocity(0);
  this->npcVector[0]->setYVelocity(0);
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

    case SDL_MOUSEWHEEL:       // Mousewheel event
      if (event.wheel.y > 0) { // Scroll up -> zoom in
        this->camera->zoomIn();
      }
      else if (event.wheel.y < 0) { // Scroll down -> zoom out
        this->camera->zoomOut();
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

  SDL_Point cameraPosition = this->camera->getPosition();

  int selectedXCoordinate = floor(X / this->tileMap->getTileSize()) + cameraPosition.x;
  int selectedYCoordinate = floor(Y / this->tileMap->getTileSize()) + cameraPosition.y;

  /*
  // Unselect all tiles
  for (int x = 0; x < this->camera->getVisibleXTiles() + cameraPosition.x; x++) {
    for (int y = 0; y < this->camera->getVisibleYTiles() + cameraPosition.y; y++) {
      this->tileMap->unselectTile(x, y);
    }
  }

  this->tileMap->selectTile(selectedXCoordinate, selectedYCoordinate);
  */
}

void Gameplay::update() {
  this->logger->log("updating in gameplay");
  this->rootElement->update();

  this->camera->update();

  this->npcVector[0]->updatePosition();
}

void Gameplay::render() const {
  SDL_RenderClear(this->gameGlobal.renderer);

  SDL_Point cameraPosition = this->camera->getPosition();

  for (int x = 0; x < this->MAP_SIZE_TILES.x; x++) {
    for (int y = 0; y < this->MAP_SIZE_TILES.y; y++) {
      SDL_RenderCopy(this->gameGlobal.renderer, this->tileMap->getTileTexture(x, y), NULL,
                     &(this->camera->destinationRect[x][y]));

      // If the current tile is selected
      /*
      if (this->tileMap->getSelected(currentXPosition, currentYPosition)) {
        // Render selected texture over it
        SDL_RenderCopy(this->gameGlobal.renderer, this->selectedTexture, NULL,
                       &(this->camera->destinationRect[x][y]));
      }
      */
    }
  }

  this->npcVector[0]->render();

  SDL_RenderPresent(this->gameGlobal.renderer);
}

void Gameplay::exit() {}
