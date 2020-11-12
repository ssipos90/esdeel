#pragma once
#include <SDL2/SDL_events.h>
#include <vector>
#ifndef GAME_H_
#define GAME_H_

#include "./Snake.hpp"
#include "./Food.hpp"

class Game {
  public:
  Game();
  void progress(uint32_t deltatime);
  void handleEvent(const SDL_Event *event);

  std::vector<Position> getSnakePieces();
  Position getFoodPosition();

  private:
  Snake snake;
  Food food;

  void moveFood(const std::vector<Position> *occupied);
  bool isColliding(const std::vector<Position> *occupied, Position *p);
};

#endif // GAME
