#pragma once
#ifndef VIDEO_H_
#define VIDEO_H_

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
  std::vector<std::shared_ptr<VideoLayer>> layers;
};

#endif // VIDEO
