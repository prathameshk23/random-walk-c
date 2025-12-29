#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define SIZE 10

typedef struct {
  int vx, vy;
} Velocity;

Velocity get_rand_v() {
  int choice = rand() / (RAND_MAX / 4);
  switch (choice) {
  case 0: // up
    return (Velocity){0, -1};
  case 1: // down
    return (Velocity){0, 1};
  case 2: // right
    return (Velocity){1, 0};
  case 3: // left
    return (Velocity){-1, 0};
  }
  fprintf(stderr, "Bad random value %d\n", choice);
  exit(-1);
}

int main(int argc, const char *argv[]) {

  int num_agenst;
  if (argc == 1) {
    num_agenst = 5;
  } else if (argc == 2) {
    num_agenst = atoi(argv[1]);
  } else {
    printf("Usage: %s <num-agents>\n", argv[0]);
    return -1;
  }

  srand(time(NULL));

  SDL_Window *window;
  SDL_Surface *surface;

  window = SDL_CreateWindow("Random walk", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  surface = SDL_GetWindowSurface(window);

  SDL_Rect rect = (SDL_Rect){WIDTH / 2, HEIGHT / 2, 2, 2};
  SDL_FillSurfaceRect(surface, &rect, 0xFFFFFF);

  int app_running = 1;

  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        app_running = 0;
      }
    }

    Velocity vel = get_rand_v();

    for (int i = 0; i < SIZE; i++) {
      rect.x += vel.vx;
      rect.y += vel.vy;
      SDL_FillSurfaceRect(surface, &rect, 0xFFFFFF);
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(20);
  }
}
