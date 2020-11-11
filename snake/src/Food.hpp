#pragma once
#include <vector>
#ifndef FOOD_H_
#define FOOD_H_

#include "./types.hpp"

class Food {
public:
  void respawn(const std::vector<Position> *occupied);
  Position getPosition();

private:
  int x;
  int y;
  bool isColliding(const std::vector<Position> *occupied);
};

#endif // FOOD
