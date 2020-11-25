#pragma once
#include <vector>
#include <memory>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "./MainMenuLayer.hpp"
#include "./VideoLayer.hpp"
#include "./types.hpp"

class Video {
public:
  Video(const App &app);
  virtual ~Video() = default; // to silence -Wall warnings

  void loop();

private:
  const App &app;
  bool exit = false;
  uint32_t starttime;
  uint32_t endtime = 0;
  uint32_t deltatime;
  SDL_Event event;

  std::vector<std::unique_ptr<VideoLayer>> layers;

  void progress();
  void handleEvent();
};
