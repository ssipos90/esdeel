#include <SDL2/SDL_image.h>
#include <cstring>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./sdl_helper.hpp"
#include "./Video.hpp"
#include "./Game.hpp"
#include "./assets.hpp"
#include "./config.hpp"
#include "./types.hpp"

App app;

// Starts up SDL and creates window
void init() {
  // Initialize SDL
  scc(SDL_Init(SDL_INIT_VIDEO), "initialize SDL");

  // Create window
  app.window = (SDL_Window *)scp(
      SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                       SDL_WINDOW_SHOWN),
      "create window");

  app.renderer = (SDL_Renderer *)scp(
      SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED),
      "create renderer");

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    fprintf(stderr, "IMG_GetError (initialize): %s\n", IMG_GetError());
    exit(1);
  }

  if (TTF_Init() < 0) {
    fprintf(stderr, "TTF_GetError (initialize): %s\n", TTF_GetError());
    exit(1);
  }

  app.screen =
      (SDL_Surface *)scp(SDL_GetWindowSurface(app.window), "create surface");
}

// Frees media and shuts down SDL
void close() {
  TTF_CloseFont(app.fonts.menu);
  TTF_CloseFont(app.fonts.score);
  TTF_CloseFont(app.fonts.game_over);

  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);

  app.renderer = NULL;
  app.window = NULL;

  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void loop() {
  srand(time(0));

  uint32_t starttime;
  uint32_t endtime = 0;
  uint32_t deltatime;
  Game game;
  Video video(app);
  while (!app.exit) {
    starttime = SDL_GetTicks();
    while (SDL_PollEvent(&app.event) != 0) {
      if (app.event.type == SDL_QUIT) {
        app.exit = true;
        break;
      } else {
        game.handleEvent(&app.event);
      }
    }

    // time spent since last renderer present
    deltatime = starttime - endtime;

    // draw game state
    video.progress(deltatime);

    SDL_RenderPresent(app.renderer);

    endtime = SDL_GetTicks();
    deltatime = endtime - starttime;
    if (deltatime <= (1000 / FPS)) {
      SDL_Delay((1000 / FPS) - deltatime);
    }
  }
}

int main(int argc, char *argv[]) {
  // silence the compiler
  (void)argv[0];
  (void)argc;

  init();
  
  app.fonts = loadFonts();

  loop();

  close();

  return 0;
}
