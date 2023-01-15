#pragma once
#include "main.h"
extern int score;
extern bool game_over;
void game_init(int size_x, int size_y);
void game_get_direction();
void game_update();
