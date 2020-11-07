#include <SDL2/SDL_error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "./errors.hpp"

int scc(int code, std::string label) {
  if (code < 0) {
    fprintf(stderr, "SDL_Error (%s): %s\n", label.c_str(), SDL_GetError());
    exit(1);
  }
 return code; 
}

void *scp(void *ptr, std::string label) {
  if (ptr == nullptr) {
    fprintf(stderr, "SDL_GetError (%s): %s\n", label.c_str(), SDL_GetError());
    exit(1);
  }
 return ptr; 
}
