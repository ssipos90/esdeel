#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "assets.hpp"

SDL_Surface* loadImage(std::string path);

SDL_Texture *convertToTexture(SDL_Renderer *renderer, SDL_Surface *surface);
SDL_Texture *loadTexture(SDL_Renderer* renderer, std::string path);
bool loadTextures(SDL_Renderer* renderer, SDL_Texture *textures[]);

SDL_Surface *loadOptimizedImage(SDL_PixelFormat* format, std::string path);
bool loadImages(SDL_PixelFormat* format, SDL_Surface *images[]);

