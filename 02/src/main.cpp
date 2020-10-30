#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <cstring>
#include <map>

#include "config.hpp"
#include "enums.hpp"
#include "media.hpp"
#include "Dot.hpp"

typedef struct {
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
bool init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  // Create window
  app.window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (app.window == NULL) {
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
  if (app.renderer == NULL) {
    std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
           IMG_GetError());
    return false;
  }

  // Get window surface
  app.screen = SDL_GetWindowSurface(app.window);
  return true;
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
  IMG_Quit();
  SDL_Quit();
}

void loop() {
  // Top left corner viewport
  Dot dot;

  while (!app.exit) {
    while (SDL_PollEvent(&app.event) != 0) {
      if (app.event.type == SDL_QUIT) {
        app.exit = true;
        break;
      }
      dot.handleEvent(app.event);
    }
    dot.move();

    SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear( app.renderer );

    dot.render(app.renderer);

    SDL_RenderPresent(app.renderer);
    SDL_Delay(30);
  }
}

int main(int argc, char *args[]) {
  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
    return 1;
  }

  // Load media
  if (!loadImages(app.screen->format, app.images)) {
    printf("Failed to load media!\n");
    return 2;
  }
  if (!loadTextures(app.renderer, app.textures)) {
    printf("Failed to load media!\n");
    return 2;
  }

  loop();

  close();
  return 0;
}
