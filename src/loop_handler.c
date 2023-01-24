#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#ifndef SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#endif

#define SCREEN_WIDTH 620
#define SCREEN_HEIGHT 310

typedef struct {
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Renderer *renderer;
} Loop_handler;

SDL_Color color = {16, 16, 16, 255};
time_t currentTime;
struct tm *timeinfo;

int fontSize = 100;
char *fontPath = "assets\\fonts\\OpenSans\\OpenSans-Regular.ttf";

char *parseWeekday(int tm);

void screen_loop(Loop_handler handler) {
  SDL_Event event;

  TTF_Init();
  SDL_Color clock_color = {0xff, 0xff, 0xff};
  TTF_Font *time_font;
  TTF_Font *date_font;

  char *time_text = (char *)malloc((int)sizeof(char *));
  SDL_Texture *time_texture = NULL;
  SDL_Surface *time_surface;
  SDL_Rect time_rect;

  char *date_text = (char *)malloc((int)sizeof(char *));
  SDL_Surface *date_surface;
  SDL_Texture *date_texture = NULL;
  SDL_Rect date_rect;

  if (!(time_font = TTF_OpenFont(fontPath, fontSize)) ||
      !(date_font = TTF_OpenFont(fontPath, fontSize / 3))) {
    printf("Error: %s", TTF_GetError());
    exit(-1);
  }

  int timeW, timeH, dateW, dateH;
  bool quit = false;

  SDL_SetRenderDrawColor(handler.renderer, color.r, color.g, color.b, color.a);

  while (!quit) {
    SDL_RenderClear(handler.renderer);

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
        exit(0); // not good way to exit
      }
    }

    // updating time to current
    time(&currentTime);
    timeinfo = localtime(&currentTime);
    sprintf(time_text, "%d:%d:%ds", timeinfo->tm_hour, timeinfo->tm_min,
            timeinfo->tm_sec);
    sprintf(date_text, "%s %d/%d/%d", parseWeekday(timeinfo->tm_wday),
            timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

    //@rendering time
    time_surface = TTF_RenderText_Blended(time_font, time_text, clock_color);
    time_texture = SDL_CreateTextureFromSurface(handler.renderer, time_surface);
    SDL_QueryTexture(time_texture, NULL, NULL, &timeW, &timeH);
    time_rect = (SDL_Rect){(SCREEN_WIDTH - timeW) / 2,
                           (SCREEN_HEIGHT - timeH) / 3, timeW, timeH};

    //@rendering date
    date_surface = TTF_RenderText_Blended(date_font, date_text, clock_color);
    date_texture = SDL_CreateTextureFromSurface(handler.renderer, date_surface);
    SDL_QueryTexture(date_texture, NULL, NULL, &dateW, &dateH);
    date_rect = (SDL_Rect){(SCREEN_WIDTH - dateW) / 2,
                           SCREEN_HEIGHT / 2 + dateH, dateW, dateH};

    SDL_RenderCopy(handler.renderer, time_texture, NULL, &time_rect);
    SDL_RenderCopy(handler.renderer, date_texture, NULL, &date_rect);

    SDL_RenderPresent(handler.renderer);

    //@freeing memory
    SDL_FreeSurface(time_surface);
    SDL_FreeSurface(date_surface);
    SDL_DestroyTexture(time_texture);
    SDL_DestroyTexture(date_texture);
  }

  free(time_text);
  free(date_text);
  TTF_CloseFont(time_font);
  TTF_CloseFont(date_font);
  TTF_Quit();
}

char *parseWeekday(int tm) {

  char *wday;

  switch (tm) {
  case 0:
    wday = "Sun";
    break;
  case 1:
    wday = "Mon";
    break;
  case 2:
    wday = "Tue";
    break;
  case 3:
    wday = "Wed";
    break;
  case 4:
    wday = "Thu";
    break;
  case 5:
    wday = "Fri";
    break;
  case 6:
    wday = "Sat";
    break;
  }

  return wday;
}
