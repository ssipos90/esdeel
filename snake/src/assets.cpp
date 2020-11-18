#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "./assets.hpp"
#include "./types.hpp"

using namespace std;

TTF_Font *loadFontFile(std::string path, int psize);
TTF_Font *loadFont(FontFace face, int psize);

FontAssets loadFonts() {
  FontAssets _fonts;
  _fonts.menu = loadFont(FontFace::FiraMonoBold, 20); 
  _fonts.score = loadFont(FontFace::FiraMonoRegular, 16); 
  _fonts.game_over = loadFont(FontFace::FiraMonoBold, 30); 

  return _fonts;
}

TTF_Font *loadFont(FontFace face, int psize) {
  string path = font_faces.at(face);

  return loadFontFile(path, psize);
}

TTF_Font *loadFontFile(std::string path, int psize) {
  auto _path = path.c_str();
  TTF_Font *font = TTF_OpenFont(_path, psize);
  if (font == NULL) {
    fprintf(stderr, "unable to load font %s. TTF_Error: %s\n", _path,
            TTF_GetError());
    exit(1);
  }

  return font;
}
