#include "apple.h"

tile_t free_tiles[300 * 300];
int free_tiles_count = 0;
apple_t apples[300 * 300];
int apple_count = 0;

void free_tiles_update_index() {
  free_tiles_count = 0;
  for (int i = 0; i < board_size_x; i++)
    for (int j = 0; j < board_size_y; j++) {
      if (board[i][j] == 0) {
        free_tiles[free_tiles_count].x = i;
        free_tiles[free_tiles_count].y = j;
        free_tiles_count++;
      }
    }
}
void apple_add(int x, int y) {
  apples[apple_count].x = x;
  apples[apple_count].y = y;
  apple_count++;
}
void apple_remove(int apple_i) {
  for (int i = apple_i; i < apple_count - 1; i++) {
    apples[i] = apples[i + 1];
  }
  apple_count--;
}
void apple_add_randomly() {
  tile_t random_tile = free_tiles[rand() % free_tiles_count];
  apple_add(random_tile.x, random_tile.y);
}
