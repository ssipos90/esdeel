#include <SDL2/SDL_stdinc.h>
#include <vector>
#include "./Snake.hpp"
#include "./config.hpp"

Snake::Snake() {
  for (int i = 1; i < GRID_SIZE - 1; i++) {
    tail[i].prev = &tail[i - 1];
    tail[i].next = &tail[i + 1];
  }

  head = &tail[0];

  tail[0].x = 0;
  tail[0].y = 0;
  return;
  tail[0].prev = &tail[GRID_SIZE - 1];
  tail[0].next = &tail[1];

  tail[GRID_SIZE - 1].prev = &tail[GRID_SIZE - 2];
  tail[GRID_SIZE - 1].next = &tail[0];
};

void Snake::go(Direction dir) {
  if (dir == direction) {
    return;
  }

  if ((direction == Direction::UP && dir == Direction::DOWN) ||
      (direction == Direction::DOWN && dir == Direction::UP) ||
      (direction == Direction::RIGHT && dir == Direction::LEFT) ||
      (direction == Direction::LEFT && dir == Direction::RIGHT)) {
    return;
  }

  tempDirection = dir;
}

void Snake::move(const Uint32 deltatime) {
  dt += deltatime;
  if (dt < 100000 / vel) {
    return;
  }
  direction = tempDirection;

  dt = 0;
  vel = velStep * clen + 100;

  Piece *next = head;
  while (head->next != nullptr) {
    next = head->next;
  }

  switch (direction) {
  case Direction::UP:
    next->y = head->y - 1 < 0 ? GRID_Y - 1 : head->y - 1;
    break;
  case Direction::DOWN:
    next->y = head->y + 1 >= GRID_Y ? 0 : head->y + 1;
    break;
  case Direction::LEFT:
    next->x = head->x <= 0 ? GRID_X - 1 : head->x - 1;
    break;
  case Direction::RIGHT:
    next->x = head->x + 1 >= GRID_X ? 0 : head->x + 1;
    break;
  }

  fprintf(stdout, "pos: %3d %3d\n", next->x, next->y);

  if (head != next) {
    head = next;
  }
}

std::vector<Position> Snake::getPieces() {
  std::vector<Position> pieces;
  Piece *p = head;
  do {
    pieces.push_back(
      Position{p->x, p->y}
    );
    p = p->next;
  } while (p != nullptr);

  return pieces;
}
