#include <iostream>
#include "Snake.hpp"

Snake::Snake () {
    for (int i = 1; i < GRID_SIZE - 1; i++) {
      tail[i].prev = &tail[i - 1];
      tail[i].next = &tail[i + 1 ];
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
    if(dir == direction) {
      return;
    }

    if ((direction == Direction::UP && dir == Direction::DOWN) ||
        (direction == Direction::DOWN && dir == Direction::UP) ||
        (direction == Direction::RIGHT && dir == Direction::LEFT) ||
        (direction == Direction::LEFT && dir == Direction::RIGHT)) {
      std::cerr << "cannot go in opposite direction" << std::endl;
      return;
    }

    direction = dir;
  }

void Snake::move() {
  switch (direction) {
  case Direction::UP:
    std::cout << "up" << std::endl;
    moveUp();
    break;
  case Direction::DOWN:
    std::cout << "down" << std::endl;
    moveDown();
    break;
  case Direction::LEFT:
    std::cout << "left" << std::endl;
    moveLeft();
    break;
  case Direction::RIGHT:
    std::cout << "right" << std::endl;
    moveRight();
    break;
  }
}

unsigned** Snake::getPieces() {
  unsigned **pieces = new unsigned *[clen];
  int i = 0;
  Piece *p = head;
  do {
    pieces[i++] = new unsigned[2]{p->x, p->y};
    p = p->next;
  } while (p != NULL);

  return pieces;
}

void Snake::moveUp() {}

void Snake::moveDown() {}

void Snake::moveLeft() {}

void Snake::moveRight() {
  Piece *last = head;
  while(head->prev != nullptr) {
    std::cout << "Loop" << std::endl;
    last = head->prev;
  }
  std::cout << "x: " << head->x << std::endl
            << "y: " << head->y << std::endl
            << head << std::endl
            << last << std::endl;

  last->x = head->x + 1;
  if (head!=last){
    head = last;
  }
};
