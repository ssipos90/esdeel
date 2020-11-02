#include <SDL2/SDL.h>
#include <iostream>

#include "structs.hpp"
#include "config.hpp"
#include "Dot.hpp"

using namespace std;

Dot::Dot() {
  mPosX = 0;
  mPosY = 0;
  mVelX = 0;
  mVelY = 0;
}
void Dot::handleEvent(SDL_Event &e) {
  // If a key was pressed
  if (e.type == SDL_KEYDOWN) {
    int cacat = DOT_VEL * (e.key.repeat < 10 ? e.key.repeat +1 : 3);
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      mVelY -= cacat;
      break;
    case SDLK_DOWN:
      mVelY += cacat;
      break;
    case SDLK_LEFT:
      mVelX -= cacat;
      break;
    case SDLK_RIGHT:
      mVelX += cacat;
      break;
    }
  }
}

void Dot::move() {
  if (mPosX + mVelX < 0 || mPosX + DOT_WIDTH > SCREEN_WIDTH) {
    mVelX = -mVelX % SCREEN_WIDTH;
  }
  mPosX += mVelX;
  if (mVelX > 0) {
    --mVelX;
  } else if (mVelX < 0) {
    ++mVelX;
  }

  if (mPosY + mVelY < 0 || mPosY + DOT_WIDTH > SCREEN_HEIGHT) {
    mVelY = -mVelY % SCREEN_HEIGHT;
  }
  mPosY += mVelY;
  if (mVelY > 0) {
    --mVelY;
  } else if (mVelY < 0) {
    ++mVelY;
  }

}

void Dot::render(SDL_Renderer *renderer) {
  SDL_Rect rect = {
    mPosX,
    mPosY,
    DOT_HEIGHT,
    DOT_WIDTH,
  };

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
}

