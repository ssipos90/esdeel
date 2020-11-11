#include <stdlib.h>
#include "./Food.hpp"
#include "./config.hpp"
#include "./types.hpp"

Position Food::getPosition() {
  return Position {
    pos.x, pos.y
  };
}

void Food::move(const Position *p) {
  pos.x = p->x;
  pos.y = p->y;
}