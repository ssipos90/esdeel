#pragma once

#include <SDL2/SDL_render.h>
#include "./assets.hpp"
#include "./types.hpp"

class VideoLayer {
public:
  VideoLayer(const App &app);
  virtual ~VideoLayer() {}
  virtual void draw(uint32_t deltatime) = 0;
  virtual bool handleEvent(const SDL_Event &event) = 0;
  virtual bool isOpaque();
  bool closeRequested();

protected:
  const App &app;
  bool close = false;
};
