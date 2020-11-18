#pragma once
#ifndef MAIN_MENU_LAYER_H_
#define MAIN_MENU_LAYER_H_

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include "./VideoLayer.hpp"

class MainMenuLayer: VideoLayer {
public:
  using VideoLayer::VideoLayer;
  void draw() override;

private:
  SDL_Color* fg;
  SDL_Color* bg;
};

#endif // MAIN_MENU_LAYER
