#include <SDL3/SDL_locale.h>
#include <SDL3/SDL_render.h>
#include <cassert>

#include "Gameplay.h"

#include <SDL3_image/SDL_image.h>

Gameplay::Gameplay(const GameGlobal& gameGlobal) : State(gameGlobal, LogFiles::GAMEPLAY) {
  this->tileMap = std::make_unique<TileMap>(gameGlobal, this->MAP_SIZE_TILES,
                                            this->INITIAL_TILE_SIZE);

  this->camera =
      std::make_unique<Camera>(gameGlobal, this->MAP_SIZE_TILES, this->INITIAL_TILE_SIZE);

  this->characterFactory = std::make_unique<CharacterFactory>(this->gameGlobal);

  std::unique_ptr<Character> npc = this->characterFactory->create(NPC);
  this->npcVector.emplace_back(std::move(npc));
  this->npcVector[0]->setXVelocity(0);
  this->npcVector[0]->setYVelocity(0);

  SDL_Surface* tmp_surface = IMG_Load("sprites/selected.png");
  selectedTexture = SDL_CreateTextureFromSurface(this->gameGlobal.renderer, tmp_surface);
  SDL_DestroySurface(tmp_surface);

  SDL_Point screenSizePixels;
  SDL_GetWindowSize(this->gameGlobal.window, &screenSizePixels.x, &screenSizePixels.y);

  this->texture =
      SDL_CreateTexture(this->gameGlobal.renderer,
                        SDL_PIXELFORMAT_RGBA8888, // Pixel format
                        SDL_TEXTUREACCESS_TARGET, // This makes it a render target
                        screenSizePixels.x, screenSizePixels.y);
}

void Gameplay::handleEvents(bool& gameIsRunning) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
    case SDL_EVENT_QUIT: // Quit event
      gameIsRunning = false;
      break;

    case SDL_EVENT_MOUSE_WHEEL:
      if (event.wheel.y > 0) { // Scroll up -> zoom in
        this->camera->destination.x *= 1.01;
        this->camera->destination.y *= 1.01;
        this->camera->destination.x -= 512 * 0.01;
        this->camera->destination.y -= 320 * 0.01;
        this->camera->destination.w *= 1.01;
        this->camera->destination.h *= 1.01;
      }
      else if (event.wheel.y < 0) { // Scroll down -> zoom out
        this->camera->destination.x *= 0.9;
        this->camera->destination.y *= 0.9;
        this->camera->destination.x += 512 * 0.1;
        this->camera->destination.y += 320 * 0.1;

        this->camera->destination.w *= 0.9;
        this->camera->destination.h *= 0.9;
      }

    default:
      break;
    }
  }
  checkKeyStates();
}

void Gameplay::checkKeyStates() const {
  const bool* keyStates = SDL_GetKeyboardState(nullptr);

  // Camera movement (arrow keys)
  if (keyStates[SDL_SCANCODE_UP]) {
    this->camera->setYVelocity(-128);
  }
  else if (keyStates[SDL_SCANCODE_DOWN]) {
    this->camera->setYVelocity(128);
  }
  else if (keyStates[SDL_SCANCODE_RIGHT]) {
    this->camera->setXVelocity(128);
  }
  else if (keyStates[SDL_SCANCODE_LEFT]) {
    this->camera->setXVelocity(-128);
  }
  else { // No arrow key pressed
    this->camera->setXVelocity(0);
    this->camera->setYVelocity(0);
  }

  // Pause menu
  if (keyStates[SDL_SCANCODE_ESCAPE]) {
    // pause
  }
}

void Gameplay::update() {
  this->logger->log("updating in gameplay");
  this->rootElement->update();

  this->camera->update();

  this->npcVector[0]->updatePosition();
}

void Gameplay::render() const {
  SDL_SetRenderTarget(this->gameGlobal.renderer, this->texture);
  SDL_RenderClear(this->gameGlobal.renderer);

  for (int x = 0; x < this->MAP_SIZE_TILES.x; x++) {
    for (int y = 0; y < this->MAP_SIZE_TILES.y; y++) {
      SDL_FRect tileRectangle = this->tileMap->getTileRectangle(SDL_Point{x, y});
      const auto tilePosition = SDL_FPoint{tileRectangle.x, tileRectangle.y};

      auto [tilePositionWithinCameraX, tilePositionWithinCameraY] =
          subtractFPoints(tilePosition, this->camera->getPosition());

      tileRectangle.x = tilePositionWithinCameraX;
      tileRectangle.y = tilePositionWithinCameraY;

      // TODO: Check if within camera viewport
      SDL_RenderTexture(this->gameGlobal.renderer, this->tileMap->getTileTexture(x, y),
                        nullptr, &tileRectangle);
    }
  }
  SDL_SetRenderTarget(this->gameGlobal.renderer, nullptr);
  SDL_RenderTexture(this->gameGlobal.renderer, this->texture, nullptr,
                    &this->camera->destination);

  this->npcVector[0]->render();

  SDL_RenderPresent(this->gameGlobal.renderer);
}

SDL_FPoint Gameplay::subtractFPoints(const SDL_FPoint pointA, const SDL_FPoint pointB) {
  const float x = pointA.x - pointB.x;
  const float y = pointA.y - pointB.y;
  return SDL_FPoint{x, y};
}
