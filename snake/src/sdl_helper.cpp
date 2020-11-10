#include <SDL2/SDL.h>
#include <string>

#include "./sdl_helper.hpp"

void *scp(void *ptr, std::string label, int exitCode) {
  if (ptr == nullptr) {
    fprintf(stderr, "SDL error (%s): %s\n", label.c_str(), SDL_GetError());
    exit(exitCode);
  }

  return ptr;
}

int scc(int code, std::string label, int exitCode) {
  if (code < 0) {
    fprintf(stderr, "SDL error (%s): %s\n", label.c_str(), SDL_GetError());
    exit(exitCode);
  }

  return code;
}
