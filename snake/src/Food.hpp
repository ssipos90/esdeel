#pragma once
#include <vector>
#ifndef FOOD_H_
#define FOOD_H_

#include "./types.hpp"

class Food {
public:
  Position getPosition();
  void move(const Position *p);

private:
  Position pos;
};

#endif // FOOD
