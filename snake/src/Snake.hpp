#pragma once

#include "config.hpp"
#include "enums.hpp"
#include "structs.hpp"
#include <SDL2/SDL_stdinc.h>
#include <iostream>

struct Piece {
  unsigned x;
  unsigned y;
  Piece *prev = nullptr;
  Piece *next = nullptr;
};

class Snake {
  static const int acc = 1;

public:
  Snake();

  void go(Direction dir);

  void move(const Uint32 deltatime);

  unsigned **getPieces();

private:
  Direction direction = Direction::RIGHT;
  const int max_speed = 1000;
  int vel = 100;
  int clen = 1;
  int dt = 0;
  Piece *head;
  Piece tail[GRID_SIZE];

  void moveUp(Piece *next);
  void moveDown(Piece *next);
  void moveLeft(Piece *next);
  void moveRight(Piece *next);
};
