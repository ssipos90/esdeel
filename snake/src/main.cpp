#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./Video.hpp"
#include "./Game.hpp"
#include "./config.hpp"
#include "./media.hpp"
#include "./sdl_helper.hpp"
#include "./types.hpp"

typedef struct App {
  SDL_Renderer *renderer;
  SDL_Window *window;
  SDL_Surface *screen;
  SDL_Texture *textures[TEXTURE_TOTAL];
  SDL_Surface *images[IMAGE_TOTAL];
  SDL_Event event;
  bool exit = false;
} App;

auto app = App{};

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
  // Deallocate images
  for (int i = 0; i < IMAGE_TOTAL; i++) {
    SDL_FreeSurface(app.images[i]);
    app.images[i] = NULL;
  }

  // destroy textures
  for (int i = 0; i < TEXTURE_TOTAL; i++) {
    SDL_DestroyTexture(app.textures[i]);
    app.textures[i] = NULL;
  }

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
  Video video(app.renderer);
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

    // progress game stuff
    game.progress(deltatime);

    // draw game state
    video.draw(&game);

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

  // Load media
  // if (!loadImages(app.screen->format, app.images)) {
  //   printf("Failed to load media!\n");
  //   return 2;
  // }

  // if (!loadTextures(app.renderer, app.textures)) {
  //   printf("Failed to load media!\n");
  //   return 2;
  // }

  loop();

  close();

  return 0;
}
