#pragma once
#include "main.h"

extern bool window_allow_input;
void window_handle_input();
void window_display_board();
void window_display_game_over();
void window_apply_queued_input();
extern enum direction window_queued_input;
