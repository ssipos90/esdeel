#include "Snake.hpp"
#include "config.hpp"
#include <SDL2/SDL_stdinc.h>
#include <iostream>

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
    std::cerr << "cannot go in opposite direction" << std::endl;
    return;
  }

  std::cout << "Direction changed: " << std::endl;

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
    next->y = head->y <= 0 ? GRID_Y - 1 : head->y - 1;
    break;
  case Direction::DOWN:
    next->y = head->y + 1 >= GRID_Y ? 0 : head->y + 1;
    break;
  case Direction::LEFT:
    next->x = head->x <= 0 ? GRID_X : head->x - 1;
    break;
  case Direction::RIGHT:
    next->x = head->x + 1 >= GRID_X ? 0 : head->x + 1;
    break;
  }


  if (head != next) {
    head = next;
  }
}

unsigned **Snake::getPieces() {
  unsigned **pieces = new unsigned *[clen];
  int i = 0;
  Piece *p = head;
  do {
    pieces[i++] = new unsigned[2]{p->x, p->y};
    p = p->next;
  } while (p != nullptr);

  return pieces;
}
