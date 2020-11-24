#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "./MainMenuLayer.hpp"
#include "./VideoLayer.hpp"
#include "./assets.hpp"
#include "config.hpp"

MainMenuLayer::MainMenuLayer(const App &app): VideoLayer(app) {
  menu.push_back(
    renderMenuItem(app.renderer, app.fonts.menu, "Ma-ta", &fg)
  );
  menu.push_back(
    renderMenuItem(app.renderer, app.fonts.menu, "pizda", &fg)
  );
};

void MainMenuLayer::draw(uint32_t deltatime) {
  (void) deltatime;
  SDL_Rect dest;
  int th = 30;
  SDL_SetRenderDrawColor(app.renderer, 0x20, 0x20, 0x20, 0x00);
  for(const auto &item: menu) {
    SDL_QueryTexture(item.texture, nullptr, nullptr, &dest.w, &dest.h);
    dest.x = SCREEN_WIDTH / 2 - dest.w / 2;
    dest.y = th - 1;
    th += dest.h - 1;
    SDL_RenderCopy(app.renderer, item.texture, nullptr, &dest);
    dest.x -= 10;
    dest.w += 20;
    SDL_RenderDrawRect(app.renderer, &dest);
  }
};

MenuItem MainMenuLayer::renderMenuItem(SDL_Renderer *renderer, TTF_Font *font, std::string text, SDL_Color *color) {
  SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), *color);

  if (surface == nullptr) {
    throw std::runtime_error("asd");
  }

  MenuItem item;
  item.label = text;
  item.texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  return item;
};
