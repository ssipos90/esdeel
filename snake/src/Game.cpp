#include <vector>
#include "./Game.hpp"
#include "./types.hpp"

void Game::handleEvent(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      snake->go(Direction::UP);
      break;
    case SDLK_DOWN:
      snake->go(Direction::DOWN);
      break;
    case SDLK_LEFT:
      snake->go(Direction::LEFT);
      break;
    case SDLK_RIGHT:
      snake->go(Direction::RIGHT);
      break;
    }
  }
}

void Game::progress(int deltatime) {
    snake->move(deltatime);
    
    std::vector<Position> pieces = snake->getPieces();
    auto foodPosition = food->getPosition();
    bool respawnFood = false;
    for (auto &piece: pieces) {
        if (piece.x == foodPosition.x) {
          respawnFood = true;
        }
    }
    if (respawnFood) {
      food->respawn(&pieces);
    }
}
