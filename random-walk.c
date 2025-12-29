#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define SIZE 10
#define AGENT_SIZE 2

typedef struct {
  int vx, vy;
} Velocity;

typedef struct {
  int x, y;
  Uint32 color;
} Agent;

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

void create_agents(Agent *pagents, int num_agents) {
  for (int i = 0; i < num_agents; i++) {
    pagents[0] = (Agent){WIDTH / 2, HEIGHT / 2, 0xFFFFFF};
  }
}

void move_agent(SDL_Surface *psurface, Agent *pagent) {
  Velocity vel = get_rand_v();

  for (int i = 0; i < SIZE; i++) {
    pagent->x += vel.vx;
    pagent->y += vel.vy;
    SDL_Rect rect = (SDL_Rect){pagent->x, pagent->y, AGENT_SIZE, AGENT_SIZE};
    SDL_FillSurfaceRect(psurface, &rect, pagent->color);
  }
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

  SDL_Window *pwindow;
  SDL_Surface *psurface;

  pwindow = SDL_CreateWindow("Random walk", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  psurface = SDL_GetWindowSurface(pwindow);

  Agent *pagents = calloc(num_agenst, sizeof(Agent));

  create_agents(pagents, num_agenst);

  int app_running = 1;

  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        app_running = 0;
      }
    }

    for (int i = 0; i < num_agenst; i++) {
      move_agent(psurface, &pagents[i]);
    }

    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(20);
  }
  free(pagents);
}
