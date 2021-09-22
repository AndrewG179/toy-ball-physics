#include <cstdlib>

#include "renderer.hpp"

struct Ball {
  int size;
  int x;
  int y;
  int v_x;
  int v_y;
  int r;
  int g;
  int b;
};

void move_ball(Ball *ball);
void collide_ball_wall(Ball *ball, int field_height, int field_width);
void collide_ball_ball(Ball *ball_one, Ball *ball_two);

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  Renderer renderer;

  const int field_height = 600;
  const int field_width = 800;

  const int balls_array_size = 10;
  Ball balls[balls_array_size] = {};
 
  for (int i = 0; i < balls_array_size; i++) {
    balls[i].v_x = rand() % 4 + 1;
    balls[i].v_y = rand() % 4 + 1;
    balls[i].x = rand() % field_width + 1;
    balls[i].y = rand() % field_height + 1;
    balls[i].r = rand() % 255;
    balls[i].g = rand() % 255;
    balls[i].b = rand() % 255;
    balls[i].size = 12;
  }


  bool quit = false;
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    renderer.clear();

    for (int i = 0; i < balls_array_size; i++) {
      renderer.draw_circle(balls[i].x, balls[i].y, balls[i].size, balls[i].r, balls[i].g, balls[i].b);
      move_ball(&balls[i]);
      collide_ball_wall(&balls[i], field_height, field_width);
      for (int j = i; j < balls_array_size; j++) {
        collide_ball_ball(&balls[i], &balls[j]);
      }
    }

    renderer.present();
    SDL_Delay(15);
  }

  return 0;
  
}

void move_ball(Ball *ball) {
  ball->x += ball->v_x;
  ball->y += ball->v_y;
}

void collide_ball_wall(Ball *ball, int field_height, int field_width) {
  if (ball->x > field_width - ball->size / 2 || ball->x < ball->size / 2) {
    ball->v_x = -ball->v_x;
  }
  if (ball->y > field_height - ball->size / 2 || ball->y < ball->size / 2) {
    ball->v_y = -ball->v_y;
  }
}

void collide_ball_ball(Ball *ball_one, Ball *ball_two) {
  if ((ball_two->y - ball_one->y) * (ball_two->y - ball_one->y) + (ball_two->x - ball_one->x) * (ball_two->x - ball_one->x) < ball_one->size * ball_two->size) {
    int temp_speed_x = ball_two->v_x;
    int temp_speed_y = ball_two->v_y;
    ball_two->v_x = ball_one->v_x;
    ball_two->v_y= ball_one->v_y;
    ball_one->v_x = temp_speed_x;
    ball_one->v_y = temp_speed_y;
  }
}
