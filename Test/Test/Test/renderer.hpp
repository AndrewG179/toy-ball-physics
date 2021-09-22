#ifndef MORPHEUS_RENDERER_HPP
#define MORPHEUS_RENDERER_HPP

#include "SDL.h"

// it's better to use a namespace,
// but it would be harder to use this class in educational purposes
class Renderer {
 public:
  Renderer();
  ~Renderer();

  void clear();
  void draw_rectangle(int x, int y, int width, int height);
  void draw_circle(int x, int y, int radius, int red, int green, int blue);
  void present();

 private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;

  Renderer(const Renderer& that);
  auto operator=(const Renderer& that) -> Renderer&;
  Renderer(const Renderer&& that) noexcept;
  auto operator=(const Renderer&& that) noexcept -> Renderer&&;
};

#endif  // MORPHEUS_RENDERER_HPP