#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "./assets.hpp"
#include "./types.hpp"

using namespace std;

void loadAssets(Assets &_assets) {
  for (auto const &[name, asset] : assets) {
    switch (asset.type) {
      case AssetType::Font: 
        _assets.fonts.insert(pair<string, TTF_Font*>{
          name,
          loadFont(asset.path, FONT_SIZE)
        });
      break;
      case AssetType::Image:
        _assets.images.insert(pair<string, SDL_Surface*>{
          name,
          loadImage(asset.path)
        });
      break;
    default:
      fprintf(stderr, "Unknown asset type.");
      break;
    }
    fprintf(stdout, "%s", name.c_str());
  }
}

TTF_Font *loadFont(std::string path, int psize) {
  auto _path = path.c_str();
  TTF_Font *font = TTF_OpenFont(_path, psize);
  if (font == NULL) {
    fprintf(stderr, "unable to load font %s. TTF_Error: %s\n", _path,
            TTF_GetError());
    exit(1);
  }

  return font;
}

SDL_Surface *loadImage(std::string path) {
  auto _path = path.c_str();
  SDL_Surface *surface = IMG_Load(_path);
  if (surface == NULL) {
    fprintf(stderr, "unable to load image %s. IMG_Error: %s\n", _path,
            IMG_GetError());
    exit(1);
  }

  return surface;
}
