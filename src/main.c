#include <stdio.h>
#include <stdlib.h>

#define SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"

#include "./loop_handler.c"

int main(int argc, char **argv) {

  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING)!= 0){
      fprintf(stderr, "%s", SDL_GetError());
      return -1;
  }

  if (!(window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN))) {
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  screenSurface = SDL_GetWindowSurface(window);
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
  SDL_UpdateWindowSurface(window);

  screen_loop((Loop_handler){window, screenSurface, renderer});

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
