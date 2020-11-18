#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <string>

using namespace std;

#define FONT_SIZE 16

typedef struct FontAssets {
    TTF_Font *menu;
    TTF_Font *score;
    TTF_Font *game_over;
} FontAssets;

enum class FontFace {
    FiraMonoRegular,
    FiraMonoBold
};

struct FontStyle {
    FontFace face;
    int size;
};

const unordered_map<FontFace, string> font_faces = {
    {FontFace::FiraMonoRegular, "assets/FiraCode-Regular.ttf"},
    {FontFace::FiraMonoBold, "assets/FiraCode-bold.ttf"}
};


FontAssets loadFonts();
