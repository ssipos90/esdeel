#pragma once

#include <SDL2/SDL_render.h>
#include "./assets.hpp"
#include "./types.hpp"

class VideoLayer {
public:
  VideoLayer(const App &app);
  virtual ~VideoLayer() {}
  virtual void draw([[maybe_unused]] uint32_t deltatime) {};

protected:
  const App &app;
};
