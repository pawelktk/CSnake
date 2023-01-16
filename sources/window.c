#include "window.h"

bool window_allow_input = 1;
enum direction window_queued_input = right;
void window_handle_input() {

  if (IsKeyDown(KEY_RIGHT) && snake_direction != left) {
    window_queued_input = right;
    window_allow_input = 0;
  } else if (IsKeyDown(KEY_LEFT) && snake_direction != right) {
    window_queued_input = left;
    window_allow_input = 0;
  } else if (IsKeyDown(KEY_UP) && snake_direction != down) {
    window_queued_input = up;
    window_allow_input = 0;
  } else if (IsKeyDown(KEY_DOWN) && snake_direction != up) {
    window_queued_input = down;
    window_allow_input = 0;
  }
  // if (window_allow_input==1) window_apply_queued_input();
}
void window_apply_queued_input() {
  snake_direction = window_queued_input;
  window_allow_input = true;
}

void window_display_board() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText(TextFormat("Score: %i", score),
           (TILE_SIZE * BOARD_SIZE -
            MeasureText(TextFormat("Score: %i", score), 20)) /
               2,
           TILE_SIZE * BOARD_SIZE + 15, 20, DARKGRAY);
  for (int i = 0; i < board_size_x; i++) {
    for (int j = 0; j < board_size_y; j++) {
      if (board[i][j] == 0)
        DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, GRAY);
      else if (board[i][j] == 1)
        DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                      MAROON);
      else if (board[i][j] == 2)
        DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
    }
  }
  EndDrawing();
}

void window_display_game_over() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawText("GAME OVER!",
           (TILE_SIZE * BOARD_SIZE - MeasureText("GAME OVER!", 20)) / 2,
           (TILE_SIZE * BOARD_SIZE) / 2, 20, DARKGRAY);

  DrawText(TextFormat("Score: %i", score),
           (TILE_SIZE * BOARD_SIZE -
            MeasureText(TextFormat("Score: %i", score), 20)) /
               2,
           (TILE_SIZE * BOARD_SIZE) / 2 + 25, 20, DARKGRAY);
  EndDrawing();
}
