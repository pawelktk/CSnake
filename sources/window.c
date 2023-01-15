#include "window.h"

void window_handle_input() {
  if (IsKeyDown(KEY_RIGHT) && snake_direction != left)
    snake_direction = right;
  if (IsKeyDown(KEY_LEFT) && snake_direction != right)
    snake_direction = left;
  if (IsKeyDown(KEY_UP) && snake_direction != down)
    snake_direction = up;
  if (IsKeyDown(KEY_DOWN) && snake_direction != up)
    snake_direction = down;
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
