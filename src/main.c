#include <stdio.h>
#include <time.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360
#include "./fonts.h"
#define FONT_SIZE 120
#define FONT_DEFAULT_RW OpenSansRegularFont

SDL_Event event;
SDL_Texture *time_texture, *date_texture;
SDL_Surface *time_surface, *date_surface;
SDL_Color bg_color = (SDL_Color){16, 16, 16, 255};
SDL_Color theme_color = (SDL_Color){0xff, 0xff, 0xff};
SDL_Rect time_rect, date_rect;
TTF_Font *time_font, *date_font;
int quit = 0;

time_t currentTime;
struct tm *timeinfo;

void update(SDL_Window* window, SDL_Renderer* renderer);

int main() {
  SDL_Init(SDL_INIT_EVENTS);

  SDL_Window* window = SDL_CreateWindow("Clock",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
  );
  if (!window) {
    fprintf(stderr, "%s", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    fprintf(stderr, "%s", SDL_GetError());
    return 1;
  }

  TTF_Init();

  SDL_RWops *font_rw = SDL_RWFromMem((void*)FONT_DEFAULT_RW, sizeof(FONT_DEFAULT_RW) - 1);
  if (!(time_font = TTF_OpenFontRW(font_rw, 0, FONT_SIZE)) || !(date_font = TTF_OpenFontRW(font_rw, 0, FONT_SIZE / 3))) {
    fprintf(stderr, "%s", TTF_GetError());
    return 2;
  }

  while (!quit) {
    update(window, renderer);
    SDL_Delay(100);
  }

  TTF_CloseFont(date_font);
  TTF_CloseFont(time_font);
  TTF_Quit();

  SDL_FreeRW(font_rw);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

void update(SDL_Window* window, SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  SDL_RenderClear(renderer);

  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) quit = 1;
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
    }
  }

  char time_text[32], date_text[32];
  time(&currentTime);
  timeinfo = localtime(&currentTime);
  strftime(time_text, sizeof(time_text), "%H:%M:%S", timeinfo);
  strftime(date_text, sizeof(date_text), "%a %Y/%m/%d", timeinfo);
  int timeW, timeH, dateW, dateH;

  time_surface = TTF_RenderText_Blended(time_font, time_text, theme_color);
  time_texture = SDL_CreateTextureFromSurface(renderer, time_surface);
  SDL_QueryTexture(time_texture, NULL, NULL, &timeW, &timeH);
  time_rect = (SDL_Rect){(SCREEN_WIDTH - timeW) / 2, (SCREEN_HEIGHT - timeH) / 3, timeW, timeH};

  date_surface = TTF_RenderText_Blended(date_font, date_text, theme_color);
  date_texture = SDL_CreateTextureFromSurface(renderer, date_surface);
  SDL_QueryTexture(date_texture, NULL, NULL, &dateW, &dateH);
  date_rect = (SDL_Rect){(SCREEN_WIDTH - dateW) / 2, SCREEN_HEIGHT / 2 + dateH, dateW, dateH};

  SDL_RenderCopy(renderer, time_texture, NULL, &time_rect);
  SDL_RenderCopy(renderer, date_texture, NULL, &date_rect);

  SDL_RenderPresent(renderer);

  SDL_DestroyTexture(time_texture);
  SDL_FreeSurface(time_surface);
  SDL_DestroyTexture(date_texture);
  SDL_FreeSurface(date_surface);
}
