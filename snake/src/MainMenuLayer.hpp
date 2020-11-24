#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include "./VideoLayer.hpp"
#include "./types.hpp"

struct MenuItem {
  std::string label;
  SDL_Texture *texture;
};

class MainMenuLayer: public VideoLayer {
public:
  MainMenuLayer(const App &);
  void draw(uint32_t deltatime) override;

private:
  std::vector<MenuItem> menu;
  SDL_Color fg{0xCC, 0x00, 0x00, 0x0};

  static MenuItem renderMenuItem(SDL_Renderer *renderer, TTF_Font *font, std::string text, SDL_Color *color);

  //SDL_Color *bg;
};
