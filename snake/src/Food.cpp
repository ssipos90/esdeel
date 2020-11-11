#include <stdlib.h>
#include "./Food.hpp"
#include "./config.hpp"
#include "./types.hpp"

void Food::respawn(const std::vector<Position> *occupied) {
  do {
    x = rand() % GRID_X;
    y = random() % GRID_Y;
  } while (isColliding(occupied));
}

bool Food::isColliding(const std::vector<Position> *occupied) {
  for (const auto & piece : *occupied){
    if (piece.x == x && piece.y == y) {
      return true;
    }
  }
  return false;
}

Position Food::getPosition() {
  return Position {
    x, y
  };
}
