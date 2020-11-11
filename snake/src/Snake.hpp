#pragma once

#include <bits/stdint-uintn.h>
#include <vector>
#include <SDL2/SDL_stdinc.h>
#include "./config.hpp"
#include "./types.hpp"

typedef struct Piece {
  int x;
  int y;
  Piece *prev = nullptr;
  Piece *next = nullptr;
} Piece;

class Snake {
  static const int acc = 1;

public:
  Snake();

  void go(Direction dir);

  void move(uint32_t deltatime);
  std::vector<Position> getPieces();
  void eat();
  Position *getHead();

private:
  const static uint32_t t = 100000;
  Direction direction;
  Direction tempDirection = Direction::RIGHT;
  int clen = 1;
  uint32_t velStep = 10;
  uint32_t vel = 100;
  uint32_t dt = 1;
  Piece *head;
  Piece tail[GRID_SIZE];
};
