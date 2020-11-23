#include <memory>
#include <SDL2/SDL_render.h>
#include "./Video.hpp"
#include "./VideoLayer.hpp"
#include "./MainMenuLayer.hpp"
#include "./types.hpp"

Video::Video(const App &app):app(app) {
  auto layer = std::make_shared<MainMenuLayer>(app); //new MainMenuLayer(app);
  layers.push_back(layer);
};

void Video::progress(uint32_t deltatime) {
  for(auto &layer: layers) {
    (*layer).draw(deltatime);
  }
};