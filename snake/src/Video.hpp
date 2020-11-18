#pragma once
#ifndef VIDEO_H_
#define VIDEO_H_

#include <vector>
#include <SDL2/SDL_render.h>
#include "./VideoLayer.hpp"

class Video {
public:
  Video(SDL_Renderer *renderer);

  void progress(uint32_t deltatime);

private:
  SDL_Renderer *renderer;
  std::vector<VideoLayer> layers;
};

#endif // VIDEO
