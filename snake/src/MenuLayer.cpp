#include "./MenuLayer.hpp"
#include "./VideoLayer.hpp"
#include "./assets.hpp"
#include "./config.hpp"
#include "./sdl_helper.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <stdexcept>

MenuLayer::MenuLayer(const App &app) : VideoLayer(app) {
  addMenuItem("Ma-ta");
  addMenuItem("pizda");
};

MenuLayer::~MenuLayer() {
  for (const auto &item : menu) {
    SDL_DestroyTexture(item.texture);
    delete item.rect;
  }
}

void MenuLayer::draw(uint32_t deltatime) {
  (void)deltatime;
  SDL_SetRenderDrawColor(app.renderer, 0x20, 0x20, 0x20, 0x00);
  for (const auto &item : menu) {
    SDL_RenderCopy(app.renderer, item.texture, nullptr, item.rect);
  }
  // dest.x -= 10;
  // dest.w += 20;
  // SDL_RenderDrawRect(app.renderer, &dest);
};

bool MenuLayer::handleEvent(const SDL_Event &event) {
  if (event.type == SDL_QUIT) {
    close = true;
  } else {
  }
  return false;
};

SDL_Texture *MenuLayer::renderMenuItem(std::string text) {
  SDL_Surface *surface = (SDL_Surface *)scp(
      TTF_RenderUTF8_Blended(app.fonts.menu, text.c_str(), fg),
      "render UTF8 text");

  auto texture =
      (SDL_Texture *)scp(SDL_CreateTextureFromSurface(app.renderer, surface),
                         "convert text surface to texture");
  SDL_FreeSurface(surface);

  return texture;
};

void MenuLayer::addMenuItem(std::string label) {
  MenuItem item;
  item.label = label;
  item.texture = renderMenuItem(label);
  item.rect = new SDL_Rect;
  SDL_QueryTexture(item.texture, nullptr, nullptr, &item.rect->w,
                   &item.rect->h);
  item.rect->x = SCREEN_WIDTH / 2 - item.rect->w / 2;
  item.rect->y = pTop + item.rect->h * menu.size();


  menu.push_back(item);
}
