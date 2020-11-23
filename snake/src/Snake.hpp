#pragma once
#ifndef SNAKE_H_
#define SNAKE_H_

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
  const static uint32_t t = 100000;
  static const int acc = 30;
  static const int initialLength = 4;
  Snake();
  ~Snake();

  bool move(Direction dir);
  void eat();

  std::vector<Position> getPieces();
  Position getHead();
  uint32_t getVel();

private:
  Direction direction = Direction::RIGHT;
  uint32_t vel = 1000;
  Piece *head;

  void go(Direction dir);
};

#endif // SNAKE
