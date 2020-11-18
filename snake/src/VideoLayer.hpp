#pragma once
#ifndef VIDEO_LAYER_H_
#define VIDEO_LAYER_H_

#include <SDL2/SDL_render.h>
#include "./assets.hpp"

class VideoLayer {
public:
  VideoLayer(SDL_Renderer *renderer, const FontAssets &fonts);
  virtual void draw();

protected:
  const FontAssets &fonts;
};

#endif // VIDEO_LAYER
