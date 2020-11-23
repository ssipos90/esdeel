#pragma once
#ifndef VIDEO_LAYER_H_
#define VIDEO_LAYER_H_

#include <SDL2/SDL_render.h>
#include "./assets.hpp"
#include "./types.hpp"

class VideoLayer {
public:
  VideoLayer(const App &app);
  virtual void draw(uint32_t deltatime);

protected:
  const App &app;
};

#endif // VIDEO_LAYER
