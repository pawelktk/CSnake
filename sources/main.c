#include "main.h"
#include "board.h"
#include "game.h"
#include "raylib.h"
#include "snake.h"
/*int main() {
  game_init();
  while (1)
    game_update();
}*/

#define TILE_SIZE 30
#define BOARD_SIZE 20
int main(void) {
  game_init(BOARD_SIZE, BOARD_SIZE);
  const int screenWidth = TILE_SIZE * BOARD_SIZE;
  const int screenHeight = TILE_SIZE * BOARD_SIZE + 45;

  InitWindow(screenWidth, screenHeight, "CSnake");

  SetTargetFPS(30);
  int frames = 0;
  while (!WindowShouldClose()) {
    if (game_over) {
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
      continue;
    }
    if (IsKeyDown(KEY_RIGHT)&&snake_direction!=left)
      snake_direction = right;
    if (IsKeyDown(KEY_LEFT)&&snake_direction!=right)
      snake_direction = left;
    if (IsKeyDown(KEY_UP)&&snake_direction!=down)
      snake_direction = up;
    if (IsKeyDown(KEY_DOWN)&&snake_direction!=up)
      snake_direction = down;
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
          DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                        GRAY);
        else if (board[i][j] == 1)
          DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                        MAROON);
        else if (board[i][j] == 2)
          DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                        RED);
      }
    }
    EndDrawing();
    frames++;
    if (frames == 10) {
      game_update();
      frames = 0;
    }
  }
  CloseWindow();
  return 0;
}
