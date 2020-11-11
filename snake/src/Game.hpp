#pragma once
#include <SDL2/SDL_events.h>
#ifndef GAME_H_
#define GAME_H_

#include "./Snake.hpp"
#include "./Food.hpp"

class Game {
  public:
  void progress(int deltatime);
  void handleEvent(const SDL_Event &e);

  private:
  Snake *snake;
  Food *food;
};

#endif // GAME
