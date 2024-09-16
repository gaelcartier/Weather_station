#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../board.h"
#include "../lcd/lcd.h"
#include "../font/font.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/timer.h"

#include <string.h>

typedef struct point_t {
    int x;
    int y;
} point_t;

typedef struct zone_t {
    point_t p1;
    point_t p2;
    void* content;
    bool has_border;
} zone_t;

typedef struct zone_matrix_t {
    point_t start, end;
    uint row, col;
    uint z_width, z_height;
    zone_t *z; // pointer to zone_t array - size = col x row
    void (*swipe_right_handler)();
    void (*swipe_left_handler)();
    void (*swipe_top_handler)();
    void (*swipe_bottom_handler)();
} zone_matrix_t;

void display_create_zone_matrix( zone_matrix_t *zm, zone_t* zone_array, uint row, uint col, point_t start, point_t end );
void display_draw_zone( zone_t z, uint16_t color );
  


#endif