#include "renderer.hpp"

#include <cassert>
#include <cstdio>

#include "SDL.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Renderer::Renderer() {
  // it's better to throw an error,
  // but it would be harder to use this class in educational purposes
  assert(SDL_Init(SDL_INIT_VIDEO) == 0);

  window_ = SDL_CreateWindow("morpheus", 0, 0, SCREEN_WIDTH,
                                         SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  // it's better to throw an error,
  // but it would be harder to use this class in educational purposes                                       
  assert(window_ != nullptr);
  
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  // it's better to throw an error,
  // but it would be harder to use this class in educational purposes
  assert(renderer_ != nullptr);
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
}

void Renderer::draw_rectangle(int x, int y, int width, int height) {
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;
  SDL_RenderFillRect(renderer_, &rect);
}

void Renderer::draw_circle(int x, int y, int radius, int red, int green, int blue) {
  SDL_SetRenderDrawColor(renderer_, red, green, blue, 255);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer_, x + dx, y + dy);
      }
    }
  }
}

void Renderer::present() { SDL_RenderPresent(renderer_); }