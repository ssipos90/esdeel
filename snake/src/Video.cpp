#include <SDL2/SDL_render.h>
#include "./Video.hpp"
#include "./VideoLayer.hpp"
#include "./MainMenuLayer.hpp"

Video::Video(SDL_Renderer *renderer) : renderer(renderer) {
  MainMenuLayer mainMenu;
  layers.push_back(mainMenu);
};

void Video::progress(uint32_t deltatime) {
  for(auto &layer: layers) {
    layer.draw();
  }
};