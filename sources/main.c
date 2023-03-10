#include "main.h"
#include "window.h"

int main(void) {
  game_init(BOARD_SIZE, BOARD_SIZE);
  const int screenWidth = TILE_SIZE * BOARD_SIZE;
  const int screenHeight = TILE_SIZE * BOARD_SIZE + 45;

  InitWindow(screenWidth, screenHeight, "CSnake");

  SetTargetFPS(30);
  int frames = 0;
  while (!WindowShouldClose()) {
    if (game_over) {
      window_display_game_over();
      continue;
    } else if (!menu_game_started) {
      window_display_menu();
      window_handle_input_menu();
      continue;
    }
    window_handle_input();
    window_display_board();
    frames++;
    if (frames == update_delay) {
      window_apply_queued_input();
      game_update();
      frames = 0;
    }
  }
  CloseWindow();
  return 0;
}
