#include "snake.h"

node_t *snake_head = NULL;
node_t *snake_tail = NULL;
bool snake_ate_apple = 0;
enum direction snake_direction;

void snake_push_head(int x, int y) {
  node_t *new_head = malloc(sizeof(node_t));
  new_head->next = NULL;
  new_head->x = x;
  new_head->y = y;
  if (snake_head != NULL) {
    snake_head->next = new_head;
  } else {
    snake_tail = new_head;
  }
  snake_head = new_head;
}

void snake_pop_tail() {
  node_t *new_tail = snake_tail->next;
  free(snake_tail);
  snake_tail = new_tail;
}
void snake_init() {
  snake_push_head(0, 0);
  snake_push_head(0, 1);
  snake_direction = right;
}
int snake_next_x() {
  if (snake_direction == right || snake_direction == left)
    return snake_head->x;
  else if (snake_direction == up)
    return snake_head->x - 1;
  else
    return snake_head->x + 1;
}
int snake_next_y() {
  if (snake_direction == up || snake_direction == down)
    return snake_head->y;
  else if (snake_direction == left)
    return snake_head->y - 1;
  else
    return snake_head->y + 1;
}
bool snake_will_collide() {
  // if(snake_next_x()==snake_head->x&&snake_next_y()==snake_head->y)
  // {snake_reverse_direction(); return 0;}
  if ((snake_direction == up && snake_head->x == 0) ||
      (snake_direction == down && snake_head->x == board_size_x - 1) ||
      (snake_direction == left && snake_head->y == 0) ||
      (snake_direction == right && snake_head->y == board_size_y - 1))
    return 1;
  int next_x = snake_next_x();
  int next_y = snake_next_y();
  for (node_t *i = snake_tail; i != snake_head; i = i->next)
    if (i->x == next_x && i->y == next_y)
      return 1;
  return 0;
}
void snake_eat_apple() {
  for (int i = 0; i < apple_count; i++) {
    if (snake_next_x() == apples[i].x && snake_next_y() == apples[i].y) {
      apple_remove(i);
      snake_ate_apple = 1;
      break;
    }
  }
}

void snake_reverse_direction() {
  if (snake_direction == up)
    snake_direction = down;
  else if (snake_direction == down)
    snake_direction = up;
  else if (snake_direction == right)
    snake_direction = left;
  else if (snake_direction == left)
    snake_direction = right;
}

void snake_move() {
  snake_push_head(snake_next_x(), snake_next_y());
  if (snake_ate_apple == 0)
    snake_pop_tail();
}
