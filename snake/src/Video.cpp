#include <cstdio>
#include <memory>
#include <SDL2/SDL_render.h>
#include "./Video.hpp"
#include "./VideoLayer.hpp"
#include "./MainMenuLayer.hpp"
#include "./types.hpp"

Video::Video(const App &app):app(app) {
  layers.emplace_back(new MainMenuLayer(this->app));
};

void Video::progress(uint32_t deltatime) {
  SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(app.renderer);
  for(auto &layer: layers) {
    (*layer).draw(deltatime);
  }
};
