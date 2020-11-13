#include "./Game.hpp"
#include "./types.hpp"
#include <vector>

Game::Game() {
  std::vector<Position> pieces = snake.getPieces();
  moveFood(&pieces);
}

void Game::handleEvent(const SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      direction = Direction::UP;
      break;
    case SDLK_DOWN:
      direction = Direction::DOWN;
      break;
    case SDLK_LEFT:
      direction = Direction::LEFT;
      break;
    case SDLK_RIGHT:
      direction = Direction::RIGHT;
      break;
    }
  }
}

bool Game::isOver() { return over; };

void Game::progress(uint32_t deltatime) {
  if (over) {
    return;
  }

  uint32_t vel = snake.getVel();
  dt += deltatime;
  if (dt < snake.t / vel) {
    return;
  }

  int steps = ceil(dt / (snake.t / vel));
  dt = 0;
  for (int i = 0; i < steps; ++i) {
    if (!snake.move(direction)) {
      over = true;
      return;
    }

    std::vector<Position> pieces = snake.getPieces();
    auto foodPosition = food.getPosition();
    bool respawnFood = false;
    for (auto &piece : pieces) {
      if (piece.x == foodPosition.x && piece.y == foodPosition.y) {
        snake.eat();
        respawnFood = true;
      }
    }
    if (respawnFood) {
      moveFood(&pieces);
    }
  }
}

std::vector<Position> Game::getSnakePieces() { return snake.getPieces(); }

Position Game::getFoodPosition() { return food.getPosition(); }

void Game::moveFood(const std::vector<Position> *occupied) {
  Position p;
  do {
    p.x = rand() % GRID_X;
    p.y = rand() % GRID_Y;
  } while (isColliding(occupied, &p));
  food.move(&p);
}

bool Game::isColliding(const std::vector<Position> *occupied, Position *p) {
  for (const auto &piece : *occupied) {
    if (piece.x == p->x && piece.y == p->y) {
      return true;
    }
  }
  return false;
}