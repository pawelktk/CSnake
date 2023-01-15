#pragma once
#include "main.h"
extern int board[300][300];
// 0 - empty
// 1 - snake
// 2 - apple
extern int board_size_x;
extern int board_size_y;

void board_place_snake();
void board_place_apples();
void board_clear();
void board_init(int size_x, int size_y);
void board_print();