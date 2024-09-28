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

#define ZONE_MATRIX_INIT           {.start = {0,0}, \
                                    .end = {0,0}, \
                                    .row = 0, \
                                    .col = 0, \
                                    .z_width = 0, \
                                    .z_height = 0, \
                                    .z = NULL, \
                                    .swipe_bottom_handler = NULL, \
                                    .swipe_top_handler = NULL, \
                                    .swipe_left_handler = NULL, \
                                    .swipe_right_handler = NULL, }

#define DISPLAY_IF_INIT            {.matrix_number = 0, \
                                    .matrix_if = NULL, \
                                    .swipe_left_handler = NULL, \
                                    .swipe_right_handler = NULL, \
                                    .swipe_top_handler = NULL, \
                                    .swipe_bottom_handler = NULL, }

// #define ZONE_MATRIX_NUMBER_IN_IF    3

typedef struct point_t {
    int x;
    int y;
} point_t;

typedef struct zone_t {
    point_t p1;
    point_t p2;
    void* content;
    bool has_border;
    void (*point_handler)();
    void (*long_point_handler)();
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

typedef struct _display_if {
    void (*swipe_right_handler)();
    void (*swipe_left_handler)();
    void (*swipe_top_handler)();
    void (*swipe_bottom_handler)();
    uint8_t matrix_number;
    zone_matrix_t** matrix_if;
} display_if_t;

void display_create_zone_matrix( zone_matrix_t *zm, zone_t* zone_array, uint row, uint col, point_t start, point_t end );
void display_draw_zone( zone_t z, uint16_t color );
zone_matrix_t* display_find_zone_matrix_from_coordiantes(zone_matrix_t** mode_if, uint16_t matrix_number, uint16_t x, uint16_t y);
zone_t* display_find_zone_from_coordinates( zone_matrix_t *zm, uint16_t x, uint16_t y );
point_t display_point_init( int x , int y );
zone_t display_zone_init();
zone_matrix_t display_zone_matrix_init();
  


#endif