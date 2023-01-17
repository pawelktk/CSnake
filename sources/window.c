#include "window.h"
bool window_allow_input = 1;
bool menu_game_started = 0;
enum menu_option menu_highlighted_option = play;
int update_delay = 3;

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
}
void window_apply_queued_input() {
  snake_direction = window_queued_input;
  window_allow_input = true;
}

void window_display_board() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText(TextFormat("Score: %i", score),
           window_center_x_text((char *)TextFormat("Score: %i", score), 20),
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

  DrawText("GAME OVER!", window_center_x_text("GAME OVER!", 20),
           window_center_y(), 20, DARKGRAY);

  DrawText(TextFormat("Score: %i", score),
           window_center_x_text((char *)TextFormat("Score: %i", score), 20),
           window_center_y() + 25, 20, DARKGRAY);
  EndDrawing();
}
void window_display_menu() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawText("CSnake", window_center_x_text("CSnake", 60), 20, 60, DARKGRAY);
  window_draw_button(window_center_x_text("    ", 30), 100, play, "Play");
  window_draw_button(window_center_x_text("    ", 30), 150, quit, "Quit");
  EndDrawing();
}

int window_center_x() { return (TILE_SIZE * BOARD_SIZE) / 2; }

int window_center_y() { return (TILE_SIZE * BOARD_SIZE) / 2; }
int window_center_x_text(char *text, int font_size) {
  return (TILE_SIZE * BOARD_SIZE - MeasureText(text, font_size)) / 2;
}

void window_draw_button(int x, int y, enum menu_option option, char *text) {
  int button_size_x = 80;
  int button_size_y = 40;
  if (menu_highlighted_option == option) {
    DrawRectangle(x, y, button_size_x, button_size_y, GOLD);
    DrawText(text, x + 10, (y + button_size_y / 2) - 15, 30, BLACK);
  } else {
    DrawRectangle(x, y, button_size_x, button_size_y, LIGHTGRAY);
    DrawText(text, x + 10, (y + button_size_y / 2) - 15, 30, BLACK);
  }
}
void window_handle_input_menu() {
  if (IsKeyPressed(KEY_UP))
    menu_highlighted_option =
        (options_end + (menu_highlighted_option + 1)) % options_end;
  if (IsKeyPressed(KEY_DOWN))
    menu_highlighted_option =
        (options_end + (menu_highlighted_option - 1)) % options_end;
  if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
    if (menu_highlighted_option == quit) {
      exit(0);
    } else if (menu_highlighted_option == play) {
      menu_game_started = true;
    }
  }
}
