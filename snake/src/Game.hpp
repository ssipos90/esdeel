#pragma once
#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <SDL2/SDL_events.h>
#include "./Snake.hpp"
#include "./Food.hpp"

class Game {
public:
  Game();
  void progress(uint32_t deltatime);
  void handleEvent(const SDL_Event *event);

  std::vector<Position> getSnakePieces();
  Position getFoodPosition();
  bool isOver();

private:
  bool over = false;
  Snake snake;
  Food food;
  Direction direction = Direction::RIGHT;
  uint32_t dt;

  void moveFood(const std::vector<Position> *occupied);
  bool isColliding(const std::vector<Position> *occupied, Position *p);
};

#endif // GAME
