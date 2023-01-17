#pragma once
#include "main.h"

extern bool window_allow_input;
void window_handle_input();
void window_display_board();
void window_display_game_over();
void window_apply_queued_input();
extern enum direction window_queued_input;

int window_center_x();
int window_center_y();
int window_center_x_text(char *text, int font_size);
void window_display_menu();

extern bool menu_game_started;
enum menu_option { play, quit, options_end };
extern enum menu_option menu_highlighted_option;
extern int update_delay;

void window_draw_button(int x, int y, enum menu_option option, char *text);
void window_handle_input_menu();
