#include <vector>
#include "./Snake.hpp"
#include "./config.hpp"

Snake::Snake() {
  Piece *prev = nullptr;
  Piece *current = nullptr;
  for(int i = 0; i < initialLength; ++i) {
    current = new Piece;
    current->position.x = i;
    current->position.y = 0;
    current->prev = prev;
    if (prev != nullptr) {
      current->prev->next = current;
    }
    prev = current;
  }
  head = current;
};

Snake::~Snake() {
  Piece *next;
  while (head->next != nullptr) {
    next = head->next;
    delete head;
  }
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

void Snake::move(uint32_t deltatime) {
  dt += deltatime;
  if (dt < t / vel) {
    return;
  }
  dt = 0;
  direction = tempDirection;

  Piece *next = new Piece();
  next->position.x = head->position.x;
  next->position.y = head->position.y;
  next->prev = head;
  head->next = next;

  switch (direction) {
  case Direction::UP:
    next->position.y = next->position.y - 1 < 0 ? GRID_Y - 1 : head->position.y - 1;
    break;
  case Direction::DOWN:
    next->position.y = next->position.y + 1 >= GRID_Y ? 0 : next->position.y + 1;
    break;
  case Direction::LEFT:
    next->position.x = next->position.x <= 0 ? GRID_X - 1 : next->position.x - 1;
    break;
  case Direction::RIGHT:
    next->position.x = next->position.x + 1 >= GRID_X ? 0 : next->position.x + 1;
    break;
  }

  Piece *last = head;
  while(last->prev != nullptr) {
    last = last->prev;
  }

  head = next;
  if (last->grow) {
    last->grow = false;
  } else {
    last->next->prev = nullptr;
    delete last;
  }
};

void Snake::eat() {
  head->grow = true;
}

std::vector<Position> Snake::getPieces() {
  std::vector<Position> pieces;

  Piece *current = head;
  while(current != nullptr) {
    pieces.push_back(current->position);
    current = current->prev;
  }

  return pieces;
};

Position Snake::getHead() {
  return head->position;
};
