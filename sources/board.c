#include "board.h"

int board[300][300];
int board_size_x;
int board_size_y;

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
