#pragma once

#include <SDL2/SDL_events.h>
#include <memory>
#include <vector>
#include <functional>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include "./VideoLayer.hpp"
#include "./types.hpp"

class MenuLayer: public VideoLayer {
public:
  MenuLayer(const App &);
  ~MenuLayer();
  void draw(uint32_t deltatime) override;
  bool handleEvent(const SDL_Event &event) override;

private:
  struct MenuItem {
    std::string label;
    SDL_Texture *texture;
    SDL_Rect* rect;
  };
  uint32_t pTop = 30;
  std::vector<MenuItem> menu;
  SDL_Color fg{0xCC, 0x00, 0x00, 0x0};

  SDL_Texture *renderMenuItem(std::string text);
  void addMenuItem(std::string text);
};
