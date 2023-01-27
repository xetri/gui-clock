#include <stdio.h>
#include <stdlib.h>

#define SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"

#include "./loop_handler.c"

int main(int argc, char **argv) {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
      fprintf(stderr, "%s", SDL_GetError());
      return -1;
  }

  SDL_Window* window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window){
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
  if (!renderer){
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
  if (!screenSurface) {
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  screen_loop((Loop_handler){window, screenSurface, renderer});

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
