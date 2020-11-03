#pragma once

#include "config.hpp"
#include "enums.hpp"
#include "structs.hpp"
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
  Snake ();

  void go(Direction dir);

  void move();
  
  unsigned** getPieces();

private:
  Direction direction = Direction::RIGHT;
  int vel = 10;
  int clen = 1;
  Piece *head;
  Piece tail[GRID_SIZE];

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
};

