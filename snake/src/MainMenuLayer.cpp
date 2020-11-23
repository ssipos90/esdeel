#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "./MainMenuLayer.hpp"
#include "./VideoLayer.hpp"
#include "./assets.hpp"

void MainMenuLayer::draw() {
  TTF_RenderUTF8_Blended(app.fonts.menu, "ceva", *fg);
};
