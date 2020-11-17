#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

using namespace std;

#define FONT_SIZE 16

enum class AssetType {
    Font,
    Image
};

struct Asset {
  string path;
  AssetType type;
};

struct Assets {
    map<string, SDL_Surface*> images;
    map<string, TTF_Font*> fonts;
};

const map<string, Asset> assets = {
    {"FiraMono-Regular", {"assets/FiraCode-Regular.ttf", AssetType::Font}},
    {"FiraMono-Bold", {"assets/FiraCode-bold.ttf", AssetType::Font}}
};

void loadAssets();

TTF_Font *loadFont(std::string path, int psize);
SDL_Surface *loadImage(std::string path);
