#include "main.h"

void game_init();
void game_get_direction();
void game_update();

void game_init() {
  srand(time(NULL));
  board_init(10, 10);
  snake_init();
  board_place_snake();
  free_tiles_update_index();
  apple_add_randomly();
  board_place_apples();
  board_print();
}

void game_get_direction() {
  printf("Direction: ");
  char buffer[20];
  scanf("%s", buffer);
  char x = buffer[0];
  if (x == 'l')
    snake_direction = left;
  else if (x == 'r')
    snake_direction = right;
  else if (x == 'u')
    snake_direction = up;
  else if (x == 'd')
    snake_direction = down;
}
int score = 0;
void game_update() {
  game_get_direction();
  if (snake_will_collide()) {
    printf("GAME OVER");
    exit(0);
  }
  snake_eat_apple();
  snake_move();
  board_clear();
  board_place_snake();
  if (snake_ate_apple) {
    free_tiles_update_index();
    if (free_tiles_count == 0) {
      printf("YOU WON!");
      exit(0);
    }
    apple_add_randomly();
    snake_ate_apple = 0;
    score++;
  }
  board_place_apples();
  board_print();
}

int main() {
  game_init();
  while (1)
    game_update();
}
