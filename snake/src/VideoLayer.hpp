#pragma once
#ifndef VIDEO_LAYER_H_
#define VIDEO_LAYER_H_

abstract class VideoLayer {
  constructor(SDL_Renderer * renderer);
  abstract void draw();
};

#endif // VIDEO_LAYER
