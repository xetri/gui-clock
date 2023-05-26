#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "./handler.c"

int main(int argc, char **argv) {
  SDL_Init(0);

  SDL_Window* window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, 0);
  if (!window) {
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer){
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  loop((Handler){window, renderer});

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
