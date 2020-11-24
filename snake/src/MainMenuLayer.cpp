#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "./MainMenuLayer.hpp"
#include "./VideoLayer.hpp"
#include "./assets.hpp"

MainMenuLayer::MainMenuLayer(const App &app): VideoLayer(app) {
  SDL_Surface *surface = TTF_RenderUTF8_Blended(app.fonts.menu, "ceva", fg);

  if (surface == nullptr) {
    throw std::runtime_error("asd");
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, surface);
  SDL_FreeSurface(surface);
};

void MainMenuLayer::draw(uint32_t deltatime) {
  (void) deltatime;
  SDL_Rect dest{ 100, 100, 200, 100};
  SDL_RenderCopy(app.renderer, texture, nullptr, &dest);
};
