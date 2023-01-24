#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#ifndef SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_ttf.h"
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

typedef struct {
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Renderer *renderer;
} Loop_handler;

void screen_loop(Loop_handler handler) {

  TTF_Init();
  bool quit = false;
  time_t currentTime;
  struct tm *timeinfo;
  int fontSize = 100;

  SDL_Color color = {16, 16, 16, 255};
  SDL_Event event;

  SDL_Surface *time_surface;
  TTF_Font *osFont;

  SDL_Color time_color = {0xff, 0xff, 0xff};
  SDL_Rect time_rect;

  char *time_text = (char *)malloc((int)sizeof(char *) * sizeof(char));
  if (!(osFont = TTF_OpenFont("assets\\fonts\\open-sans\\OpenSans-Light.ttf",
                              fontSize))) {
    printf("Error: %s", TTF_GetError());
    quit = true;
  }

  SDL_Texture *time_texture = NULL;
  int rect_w, rect_h;

  while (!quit) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        quit = true;
    }

    SDL_SetRenderDrawColor(handler.renderer, color.r, color.g, color.b,
                           color.a);
    SDL_RenderClear(handler.renderer);

    time(&currentTime);
    timeinfo = localtime(&currentTime);
    sprintf(time_text, "%d:%d:%ds", timeinfo->tm_hour, timeinfo->tm_min,
            timeinfo->tm_sec);

    time_surface = TTF_RenderText_Solid(osFont, time_text, time_color);
    time_texture = SDL_CreateTextureFromSurface(handler.renderer, time_surface);

    SDL_QueryTexture(time_texture, NULL, NULL, &rect_w, &rect_h);
    time_rect = (SDL_Rect){(SCREEN_WIDTH / 2) - rect_w / 2,
                           (SCREEN_HEIGHT / 2) - rect_h / 2, rect_w, rect_h};

    SDL_RenderCopy(handler.renderer, time_texture, NULL, &time_rect);

    SDL_RenderPresent(handler.renderer);
  }

  free(time_text);
  TTF_CloseFont(osFont);
  TTF_Quit();
}
