#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include "./assets.hpp"

typedef struct App {
  SDL_Renderer *renderer;
  SDL_Window *window;
  SDL_Surface *screen;
  SDL_Event event;
  FontAssets fonts;
  bool exit = false;
} App;

enum ResourceImages {
  IMAGE_DEFAULT,
  IMAGE_UP,
  IMAGE_DOWN,
  IMAGE_LEFT,
  IMAGE_RIGHT,
  IMAGE_TOTAL
};

enum ResourceTextures {
  TEXTURE_UP,
  TEXTURE_DOWN,
  TEXTURE_LEFT,
  TEXTURE_RIGHT,
  TEXTURE_TOTAL
};

enum class Direction { UP, DOWN, LEFT, RIGHT };

typedef struct Position {
  int x;
  int y;
} Position;
