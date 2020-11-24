#pragma once
#include <vector>

#include "./types.hpp"

class Food {
public:
  Position getPosition();
  void move(const Position *p);

private:
  Position pos;
};
