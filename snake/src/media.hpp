#pragma once

#include <SDL2/SDL.h>
#include <string>

const std::string images[] = {
    "assets/press.png", // KEY_PRESS_SURFACE_DEFAULT
    "assets/up.png",    // KEY_PRESS_SURFACE_UP
    "assets/down.png",  // KEY_PRESS_SURFACE_DOWN
    "assets/left.png",  // KEY_PRESS_SURFACE_LEFT
    "assets/right.png"  // KEY_PRESS_SURFACE_RIGHT
};

const std::string textures[] = {
    "assets/press.png", // KEY_PRESS_SURFACE_DEFAULT
    "assets/up.png",    // KEY_PRESS_SURFACE_UP
    "assets/down.png",  // KEY_PRESS_SURFACE_DOWN
    "assets/left.png",  // KEY_PRESS_SURFACE_LEFT
    "assets/right.png"  // KEY_PRESS_SURFACE_RIGHT
};

SDL_Surface* loadImage(std::string path);

SDL_Texture *convertToTexture(SDL_Renderer *renderer, SDL_Surface *surface);
SDL_Texture *loadTexture(SDL_Renderer* renderer, std::string path);
bool loadTextures(SDL_Renderer* renderer, SDL_Texture *textures[]);

SDL_Surface *loadOptimizedImage(SDL_PixelFormat* format, std::string path);
bool loadImages(SDL_PixelFormat* format, SDL_Surface *images[]);
