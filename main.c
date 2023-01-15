#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct node {
  int x;
  int y;
  struct node *next;
} node_t;
int board[300][300];
// 0 - empty
// 1 - snake
// 2 - apple
int board_size_x;
int board_size_y;
node_t *snake_head = NULL;
node_t *snake_tail = NULL;
bool snake_ate_apple = 0;
enum direction { up, down, left, right };
enum direction snake_direction;

typedef struct tile {
  int x;
  int y;
} tile_t;
tile_t free_tiles[300 * 300];
int free_tiles_count = 0;

void free_tiles_update_index();

typedef struct apple {
  int x;
  int y;
  int apple_type; // not used
} apple_t;
apple_t apples[300 * 300];
int apple_count = 0;

void apple_add(int x, int y);
void apple_add_randomly();

void snake_push_head(int x, int y);
void snake_pop_tail();
void snake_init();
int snake_next_x();
int snake_next_y();
bool snake_will_collide();
void snake_move();

void board_place_snake();
void board_clear();
void board_init(int size_x, int size_y);
void board_print();
void board_place_apples();

void game_init();
void game_get_direction();
void game_update();

void free_tiles_update_index() {
  free_tiles_count = 0;
  for (int i = 0; i < board_size_x; i++)
    for (int j = 0; j < board_size_y; j++) {
      if (board[i][j] == 0) {
        free_tiles[free_tiles_count].x = i;
        free_tiles[free_tiles_count].y = j;
        free_tiles_count++;
      }
    }
}
void apple_add(int x, int y) {
  apples[apple_count].x = x;
  apples[apple_count].y = y;
  apple_count++;
}
void apple_remove(int apple_i) {
  for (int i = apple_i; i < apple_count - 1; i++) {
    apples[i] = apples[i + 1];
  }
  apple_count--;
}
void apple_add_randomly() {
  tile_t random_tile = free_tiles[rand() % free_tiles_count];
  apple_add(random_tile.x, random_tile.y);
}

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

void snake_move() {
  snake_push_head(snake_next_x(), snake_next_y());
  if (snake_ate_apple == 0)
    snake_pop_tail();
}

void board_place_snake() {
  for (node_t *i = snake_tail; i != NULL; i = i->next)
    board[i->x][i->y] = 1;
}

void board_place_apples() {
  for (int i = 0; i < apple_count; i++) {
    board[apples[i].x][apples[i].y] = 2;
  }
}

void board_clear() {
  for (int i = 0; i < board_size_x; i++)
    for (int j = 0; j < board_size_y; j++)
      board[i][j] = 0;
}
void board_init(int size_x, int size_y) {
  board_size_x = size_x;
  board_size_y = size_y;
  board_clear();
}
void board_print() {
  for (int i = 0; i < board_size_y + 2; i++)
    printf("#");
  printf("\n");
  for (int i = 0; i < board_size_x; i++) {
    printf("#");
    for (int j = 0; j < board_size_y; j++) {
      if (board[i][j] == 0)
        printf(" ");
      else if (board[i][j] == 1)
        printf("O");
      else if (board[i][j] == 2)
        printf("@");
    }
    printf("#\n");
  }
  for (int i = 0; i < board_size_y + 2; i++)
    printf("#");
  printf("\n");
}

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
