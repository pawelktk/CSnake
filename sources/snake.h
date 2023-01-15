#pragma once
#include "main.h"
typedef struct node {
  int x;
  int y;
  struct node *next;
} node_t;

extern node_t *snake_head;
extern node_t *snake_tail;
extern bool snake_ate_apple;

enum direction { up, down, left, right };
extern enum direction snake_direction;

void snake_push_head(int x, int y);
void snake_pop_tail();
void snake_init();
int snake_next_x();
int snake_next_y();
bool snake_will_collide();
void snake_eat_apple();

void snake_move();
void snake_reverse_direction();
