#pragma once

#include <SDL2/SDL_stdinc.h>
#include "./config.hpp"
#include "./enums.hpp"

typedef struct Piece {
  unsigned x;
  unsigned y;
  Piece *prev = nullptr;
  Piece *next = nullptr;
} Piece;

class Snake {
  static const int acc = 1;

public:
  Snake();

  void go(Direction dir);

  void move(const Uint32 deltatime);

  unsigned **getPieces();

private:
  Direction direction;
  Direction tempDirection = Direction::RIGHT;
  int velStep = 10;
  int vel = 100;
  int clen = 1;
  int dt = 0;
  Piece *head;
  Piece tail[GRID_SIZE];
};
