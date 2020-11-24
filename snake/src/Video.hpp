#pragma once
#include "MainMenuLayer.hpp"

#include <vector>
#include <memory>
#include <SDL2/SDL_render.h>
#include "./VideoLayer.hpp"
#include "./types.hpp"

class Video {
public:
  Video(const App &app);
  virtual ~Video() = default; // to silence -Wall warnings

  void progress(uint32_t deltatime);

private:
  const App &app;
  std::vector<std::unique_ptr<VideoLayer>> layers;
};
