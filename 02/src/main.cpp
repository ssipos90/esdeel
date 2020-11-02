#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <cstring>
#include <map>

#include "config.hpp"
#include "assets.hpp"
#include "enums.hpp"
#include "media.hpp"

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

struct Piece {
  unsigned x;
  unsigned y;
  Piece *prev = NULL;
  Piece *next = NULL;
};

class Snake {
  static const int acc = 1;

public:
  Snake () {
    for (int i = 1; i < GRID_SIZE - 1; i++) {
      tail[i].prev = &tail[i - 1];
      tail[i].next = &tail[i + 1 ];
    }

    head = &tail[0];

    tail[0].x = 0;
    tail[0].y = 0;
    tail[0].prev = &tail[GRID_SIZE - 1];
    tail[0].next = &tail[1];

    tail[GRID_SIZE - 1].prev = &tail[GRID_SIZE - 2];
    tail[GRID_SIZE - 1].next = &tail[0];
  }

  void go(unsigned dir) {
    if (dir < DIR_UP || dir > DIR_RIGHT) {
      std::cerr << "Unknown direction" << std::endl;
      return;
    }

    if(dir == direction) {
      return;
    }

    int sum = dir + direction;
    if (sum == 1 || sum == 5) {
      std::cerr << "cannot go in opposite direction" << std::endl;
      return;
    }
      
    direction = dir;
  }

  void move() {
    switch(direction) {
    case DIR_UP:
      moveUp();
      break;
    case DIR_DOWN:
      moveDown();
      break;
    case DIR_LEFT:
      moveLeft();
      break;
    case DIR_RIGHT:
      moveRight();
      break;
    }
  }

  unsigned** getPieces() {
    unsigned **pieces = new unsigned*[clen];
    int i = 0;
    Piece *p = head;
    do {
      pieces[i++] = new unsigned[2]{
        p->x,
        p->y
      };
      p = p->next;
    } while (p != NULL);

    return pieces;
  }

private:
  unsigned direction = DIR_RIGHT;
  int vel = 10;
  int clen = 1;
  Piece *head;
  Piece tail[GRID_SIZE];

  void moveUp() {
  }
  void moveDown() {
  }
  void moveLeft() {
  }
  void moveRight() {
    head->next->x = head->x + 1;
    head->next->y = head->y;
    Piece *prev = head->prev;
    while(prev != NULL) {
      prev = head->prev;
    }
    if(prev) {
      prev->x = NULL;
  }
};

void handleEvent(Snake *snake) {
  if (app.event.type == SDL_KEYDOWN) {
    switch (app.event.key.keysym.sym) {
    case SDLK_UP:
      snake->go(DIR_UP);
      break;
    case SDLK_DOWN:
      break;
    case SDLK_LEFT:
      break;
    case SDLK_RIGHT:
      break;
    }
  }
}

void loop() {
  Snake snake;

  Uint32 starttime;
  Uint32 deltatime;
  while (!app.exit) {
    starttime = SDL_GetTicks();
    while (SDL_PollEvent(&app.event) != 0) {
      if (app.event.type == SDL_QUIT) {
        app.exit = true;
        break;
      }
      handleEvent(&snake);
    }
    snake.move();

    SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear( app.renderer );

    SDL_Rect pieceSquare;
    auto pieces = snake.getPieces();
    for (int i = 0; i < sizeof(pieces); i++) {
      pieceSquare.x = pieces[i][0];
      pieceSquare.y = pieces[i][1];
    }

    SDL_RenderPresent(app.renderer);
    deltatime = SDL_GetTicks() - starttime;
    if (deltatime <= (1000 / FPS)) {
      SDL_Delay((1000 / FPS) - deltatime);
    }
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
