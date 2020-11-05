#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include "Snake.hpp"
#include "config.hpp"

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

    std::cout  << "Direction changed: " << std::endl;

    direction = dir;
  }

void Snake::move(const Uint32 deltatime) {
  dt += deltatime;
  if (dt < 100000 / vel) {
    return;
  }

  vel+=10;

  dt = 0;
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
  } while (p != nullptr);

  return pieces;
}

void Snake::moveUp() {
  if (head->y <= 0) {
    return;
  }
  Piece *next = head;
  while(head->next != nullptr) {
    next = head->next;
  }

  next->y = head->y - 1;
  if (head != next){
    head = next;
  }

}

void Snake::moveDown() {
  if (head->y + 1 >= GRID_Y) {
    return;
  }
  Piece *next = head;
  while(head->next != nullptr) {
    next = head->next;
  }

  next->y = head->y + 1;
  if (head != next){
    head = next;
  }
}

void Snake::moveLeft() {
  if (head->x <= 0) {
    return;
  }
  Piece *next = head;
  while(head->next != nullptr) {
    next = head->next;
  }

  next->x = head->x - 1;
  if (head != next){
    head = next;
  }
}

void Snake::moveRight() {
  if (head->x + 1 >= GRID_X) {
    return;
  }
  Piece *next = head;
  while(head->next != nullptr) {
    next = head->next;
  }

  next->x = head->x + 1;
  if (head != next){
    head = next;
  }
};
