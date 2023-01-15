#pragma once
#include "main.h"
typedef struct tile {
  int x;
  int y;
} tile_t;

extern tile_t free_tiles[300 * 300];
extern int free_tiles_count;

void free_tiles_update_index() ;


typedef struct apple {
  int x;
  int y;
  int apple_type; // not used
} apple_t;

extern apple_t apples[300 * 300];
extern int apple_count;

void apple_add(int x, int y) ;
void apple_remove(int apple_i) ;
void apple_add_randomly() ;
