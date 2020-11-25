#include <cstdio>
#include <memory>
#include "./Video.hpp"
#include "./MainMenuLayer.hpp"
#include "./VideoLayer.hpp"
#include "./config.hpp"
#include "./types.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

Video::Video(const App &app) : app(app) {
  layers.emplace_back(new MainMenuLayer(this->app));
};

void Video::loop() {
  while (!exit) {
    starttime = SDL_GetTicks();

    // time spent since last renderer present
    deltatime = starttime - endtime;
    handleEvent();

    // draw game state
    progress();

    SDL_RenderPresent(app.renderer);

    endtime = SDL_GetTicks();
    deltatime = endtime - starttime;
    if (deltatime <= (1000 / FPS)) {
      SDL_Delay((1000 / FPS) - deltatime);
    }
  }
}

void Video::handleEvent() {
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      exit = true;
      break;
    } else {
    }
  }
}

void Video::progress() {
  SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(app.renderer);

  for (auto &layer : layers) {
    (*layer).draw(deltatime);
  }
};
