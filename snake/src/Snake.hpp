#pragma once

#include <vector>
#include <SDL2/SDL_stdinc.h>
#include "./config.hpp"
#include "./types.hpp"

typedef struct Piece {
  Position position;
  Piece *prev = nullptr;
  Piece *next = nullptr;
  bool grow = false;
} Piece;

class Snake {
public:
  static const int acc = 1;
  static const int initialLength = 4;
  Snake();
  ~Snake();

  void go(Direction dir);

  void move(uint32_t deltatime);
  std::vector<Position> getPieces();
  void eat();
  Position getHead();

private:
  const static uint32_t t = 100000;
  Direction direction;
  Direction tempDirection = Direction::RIGHT;
  uint32_t vel = 1000;
  uint32_t dt = 1;
  Piece *head;
};
