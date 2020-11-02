#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "media.hpp"
#include "enums.hpp"

SDL_Surface *loadImage(std::string path) {
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (surface == NULL) {
    std::cout << "Unable to load image " << path
              << "! SDL_image Error: " << IMG_GetError() << std::endl;
  }

  return surface;
}

bool loadImages(SDL_PixelFormat *format, SDL_Surface *_images[]) {
  SDL_Surface *image;
  for (int i = 0; i < IMAGE_TOTAL; i++) {
    image = loadOptimizedImage(format, images[i].c_str());
    if (image == NULL) {
      return false;
    }

    _images[i] = image;
  }

  return true;
}

SDL_Surface *loadOptimizedImage(SDL_PixelFormat *format, std::string path) {
  auto loadedSurface = loadImage(path);
  if (loadedSurface == NULL) {
      return NULL;
  }

  auto optimizedSurface = SDL_ConvertSurface(loadedSurface, format, 0);

  SDL_FreeSurface(loadedSurface);

  if (optimizedSurface == NULL) {
    std::cout << "Unable to optimize image " << path
              << "! SDL Error: " << SDL_GetError() << std::endl;
  }

  return optimizedSurface;
}

bool loadTextures(SDL_Renderer *renderer, SDL_Texture *_textures[]) {
  SDL_Texture *texture;
  for (int i = 0; i < TEXTURE_TOTAL; i++) {
    texture = loadTexture(renderer, textures[i]);
    if (texture == NULL) {
      return false;
    }

    _textures[i] = texture;
  }

  return true;
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, std::string path) {
  auto image = loadImage(path);

  if (image == NULL) {
    return NULL;
  }

  return convertToTexture(renderer, image);
}

SDL_Texture *convertToTexture(SDL_Renderer *renderer, SDL_Surface *surface) {
  auto texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == NULL) {
    std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
  }

  return texture;
}
