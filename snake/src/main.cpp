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

#include "./sdl_helper.hpp"
#include "./Game.hpp"
#include "./config.hpp"
#include "./types.hpp"
#include "./media.hpp"

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

  app.screen = (SDL_Surface *) scp(SDL_GetWindowSurface(app.window), "create surface");
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


void drawGrid() {
  SDL_SetRenderDrawColor(app.renderer, 0x20, 0x20, 0x20, 0x00);
  for (int i = 1; i < GRID_Y; i++) {
    SDL_RenderDrawLine(app.renderer, 0, CELL_HEIGHT * i, GRID_X * CELL_WIDTH,
                       CELL_HEIGHT * i);
  }
  for (int i = 1; i < GRID_X; i++) {
    SDL_RenderDrawLine(app.renderer, CELL_WIDTH * i, 0, CELL_WIDTH * i,
                       GRID_Y * CELL_HEIGHT);
  }
}


void loop() {
  srand(time(0));

  SDL_Rect pieceSquare = {0, 0, CELL_WIDTH, CELL_HEIGHT};

  Uint32 starttime;
  Uint32 endtime;
  Uint32 deltatime;
  Game *game = new Game();
  while (!app.exit) {
    starttime = SDL_GetTicks();
    while (SDL_PollEvent(&app.event) != 0) {
      if (app.event.type == SDL_QUIT) {
        app.exit = true;
        break;
      } else {
        game->handleEvent(app.event);
      }
    }

    game->progress(starttime - endtime);


    SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(app.renderer);

    drawGrid();

    // TODO extract to video renderer disco video->render(game); or smt
    SDL_SetRenderDrawColor(app.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    const auto pieces = game->getPieces();

    for (int i = 0; i < sizeof(pieces) / sizeof(pieces[0]); i++) {
      pieceSquare.x = pieces[i][0] * CELL_WIDTH;
      pieceSquare.y = pieces[i][1] * CELL_HEIGHT;
      SDL_RenderFillRect(app.renderer, &pieceSquare);
    }

    SDL_RenderPresent(app.renderer);
    endtime = SDL_GetTicks();
    deltatime = endtime - starttime;
    if (deltatime <= (1000 / FPS)) {
      SDL_Delay((1000 / FPS) - deltatime);
    }
  }
}

int main(int argc, char *args[]) {
  // Start up SDL and create window
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
