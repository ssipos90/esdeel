#ifndef SDL_HELPER_H_
#define SDL_HELPER_H_

#include <SDL2/SDL.h>
#include <string>

void *scp(void *ptr, std::string label, int exitCode = 1);
int scc(int code, std::string label, int exitCode = 1);

#endif // SDL_HELPER
